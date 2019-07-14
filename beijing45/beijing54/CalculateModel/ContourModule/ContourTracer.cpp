// ContourTracer.cpp: implementation of the CContourTracer class.
//
//////////////////////////////////////////////////////////////////////

#include "ContourTracer.h"
#include "2DMemAllocator.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CContourTracer::CContourTracer()
{
	m_ppGridData = NULL;
	m_ppOrigGridData = NULL;

	m_pCurveList = NULL;
	m_currentCurveLine = NULL;

	xSide = NULL;
	ySide = NULL;

}

CContourTracer::~CContourTracer()
{
	FreeMemory();
}



bool CContourTracer::ExecuteTracing(float value)
{
//	ASSERT( m_gridDataInfo.cols != 0 ); //在调用该函数之前必须调用SetGridDataInfo()函数设置网格数据信息

	if( value < m_gridDataInfo.zMin && value > m_gridDataInfo.zMax )
	{
		return false;
	}


	m_valueTracing = value;


	//1.为xSide和ySide分配内存空间
	AllocateMemory();

	//2.扫描网格纵横边，内插等值点
	//该函数之中，在计算等值点时，发现追踪值与网格点上的数据相同时，
	//在计算前，会都数据做修正(加上一小偏移值)
	InterpolateTracingValue(); 

	//3.先追踪开曲线
	TracingNonClosedContour();

	//4.再追踪闭曲线
	TracingClosedContour(); 

	//5.释放空间
	//FreeMemory();

	return true;
	



	
}

void CContourTracer::AllocateMemory()
{// 分配xSide，ySide空间
	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;
	
	if( xSide == NULL )
	{
		//网格中存在rows*(cols-1)条横边，所有需要为xSide分配rows*(cols-1)空间就行

		C2DMemAllocator::AllocMemory2D(xSide,rows,cols-1/*not cols*/);
	}
	
	if( ySide == NULL )
	{
		//网格中存在(rows-1)*cols条纵边，所有需要为ySide分配(rows-1)*cols空间就行

		C2DMemAllocator::AllocMemory2D(ySide,rows-1/*not rows*/,cols);
	}

	if (m_ppGridData == NULL)
	{
		C2DMemAllocator::AllocMemory2D(m_ppGridData, rows, cols);
	}
	
}

void CContourTracer::FreeMemory()
{
	
	if( xSide != NULL )
	{
		C2DMemAllocator::FreeMemory2D(xSide);
		xSide = NULL;
	}
	
	if( ySide != NULL )
	{
		C2DMemAllocator::FreeMemory2D(ySide);
		ySide = NULL;
	}

	if (m_ppGridData != NULL)
	{
		//释放空间
		C2DMemAllocator::FreeMemory2D(m_ppGridData);
		m_ppGridData = NULL;
	}
	
}



//扫描网格的纵、横边，并线性插值计算等值点的情况
//将各边上的等值点情况存储于xSide和ySide数组中，
// xSide存储所有横边上的等值线情况, ySide存储所有纵边上的等值点情况
//在插值计算时，对『与追踪值相等的数据』要进行修正处理后才计算，但在做修正处理时不要改变原来的数据
void CContourTracer::InterpolateTracingValue()
{
/*      网格点标识如下:
        
            (i+1,j)·--------·(i+1,j+1)
                    |        |
                    |        |
                    |        |
	                |        |
	         (i,j) ·--------·(i,j+1)

              i:表示行号(向上增加)
			  j:表示列号(向右增加)
			  标识一个网格交点时，行号在前，列号在右，如：(i,j)
*/
/*        xSide,ySide中存储r值，(w为追踪值)
          对于网格横边，r = (w - pData[i][j]) / (pData[i][j+1]-pData[i][j]);
		  对于网格纵边，r = (w - pData[i][j]) / (pData[i+1][j]-pData[i][j]);

		  由于浮点运算的误差，xSide[i][j],ySide[i][j]有可能等于1.0或0.0 
		  考虑如下情况：
		  1。当追踪值与网格点上的值很接近(但不相等)时，由于运算误差，就会等于1.0
		     比如追踪0值时，遇到如下边:
			       20 ·--------·-0.00000016   此边上有0值，但计算 (0-20)/(-0.00000016-20) == 1.0 

       
		  2。当网格边上两端点上的值相差很悬殊时。
		     比如追踪2值，遇到如下边：
		     1.70141E+038 ·--------·1   此边上有2值，计算(2-1.70141E+038) / (1-1.70141E+038) == 1.0 

        网格边上有等值点时，理论上比例值不会等于0或1；
		 但由于计算误差，我们在算法中判断时，认为0或1也是有等值点的

        所以xSide,ySide中存储的值是[0,1]的闭区间，不是(0,1)的开区间
*/
//	ASSERT( m_ppGridData!=NULL );
//	ASSERT( xSide != NULL );
//	ASSERT( ySide != NULL );
	
	int i,j;
	
	int   rows = m_gridDataInfo.rows;
	int   cols = m_gridDataInfo.cols;
	float  w   = m_valueTracing;
	float shift = 0.001f;  //修正值
 
 	for(i=0; i<rows ; i++)
 	{
 		for(j=0;j<cols;j++)
 		{
			m_ppGridData[i][j] = m_ppOrigGridData[i][j];
			if (m_ppGridData[i][j] == -32383 )
			{
				int num = 0;
				float sum = 0;
				for (int m = i-1; m <= i+1; m++)
				{
					for (int n = j-1; n <= j+1; n++)
					{
						if (m>-1&&m<rows&&n>-1&&n<cols&&(m_ppOrigGridData[m][n]!=-32383))
						{
							num++;
							sum += m_ppOrigGridData[m][n];
						}
					}
				}
				if (num > 0)
				{
					m_ppGridData[i][j] = sum/num;
				}
			}
			
			if (m_ppGridData[i][j] == w)
			{
				m_ppGridData[i][j] += shift;
			}
 		}
 	}
	
	float** pData = m_ppGridData;
	
	float H1,H2; //分别记录一条边的两个点上的数据值
	float flag; 
	

	for(i=0; i<rows ; i++)
	{
		if (pData[i][0] > w )
		{
			pData [i][0] = w- shift;
		}
		if (pData[i][cols-1]>w)
		{
			pData[i][cols-1] = w-shift;
		}
	}

	for(j=0;j<cols-1;j++)
	{
		if (pData[0][j] > w )
		{
			pData[0][j] = w- shift;
		}
		if (pData[rows-1][j]>w)
		{
			pData[rows-1][j] = w-shift;
		}
	}

	/* 扫描并计算横边上的等值点,有rows*(cols-1)条横边需要扫描*/
	for(i=0; i<rows ; i++)
	{
		for(j=0;j<cols-1;j++)
		{				
			/*考查横边(i,j)上的左交点(i,j)上的值pData[i][j]
			                 和右交点(i,j+1)的值pData[i][j+1]*/

			H1 = pData[i][j]; 			H2 = pData[i][j+1];
			
			if( H1 == H2 )
			{
				xSide[i][j] = -2.0f;
			}
			else
			{
				flag = (w-H1) * (w-H2);
				if( flag > 0 )
				{
					xSide[i][j] = -2.0f;
				}
				else if( flag < 0 )
				{
					xSide[i][j] = (w-H1) / (H2-H1) ; 
//					ASSERT(xSide[i][j]>=0 && xSide[i][j]<=1.0f);
				}
				else
				{
//					ASSERT(FALSE);
				}

			}
		}
	}

	/* 扫描并计算纵边上等值点,有(rows-1)*cols条纵边需要扫描*/
	for(i=0; i<rows-1;i++)
	{
		for(j=0; j<cols; j++)
		{			
			/*考查纵边(i,j)上的下交点(i,j)上的值pData[i][j]
			                 和上交点(i+1,j)的值pData[i+1][j]*/
                                             
			H1 = pData[i][j];            
			H2 = pData[i+1][j];		

			if( H1 == H2 )               
			{
				ySide[i][j] = -2.0f;
			}
			else
			{
				flag = (w-H1) * (w-H2);
				if( flag > 0 )
				{
					ySide[i][j] = -2.0f;
				}
				else if( flag < 0 )
				{/*
				 网格边上有等值点时，存储的值∈[0,1] (闭区间)
                 */
					ySide[i][j] = (w-H1) / (H2-H1) ; 
//					ASSERT(ySide[i][j]>=0 && ySide[i][j]<=1.0f);
				}
				else
				{
//					ASSERT(FALSE);
				}


			}

		}
	}
}

inline void CContourTracer::CalcAndSaveOnePointCoord(int i, int j, bool bHorizon,float &x, float &y)
{
	/*static*/ float deltX = (m_gridDataInfo.xMax - m_gridDataInfo.xMin) / ( m_gridDataInfo.cols - 1 );
	/*static*/ float deltY = (m_gridDataInfo.yMax - m_gridDataInfo.yMin) / ( m_gridDataInfo.rows - 1 );
	// should not be static, because diffirent input data has diffirent xyMin Max
	
	int rows = m_gridDataInfo.rows;
	int cols = m_gridDataInfo.cols;
	
	if( bHorizon )
	{//在横边上
		if(i<rows && j<cols-1)
		{
			x = m_gridDataInfo.xMin + ( j + xSide[i][j] ) * deltX;
			y = m_gridDataInfo.yMin + i * deltY;
			//Saving Coord
			CGeoPoint point(x,y);
			m_currentCurveLine->push_back(point);
		}

	}
	else
	{//在纵边上
		if(i<rows-1 && j<cols)
		{
			x = m_gridDataInfo.xMin + j * deltX;
			y = m_gridDataInfo.yMin + ( i + ySide[i][j] ) * deltY;
			CGeoPoint point(x,y);
			m_currentCurveLine->push_back(point);
		}

	}



}

//当下一个等值点找到后做相应的处理
void CContourTracer::HandlingAfterNextPointFounded(int i, int j, bool bHorizon)
{//参数说明：i,j分别是等值点所在边的编号，bHorizon指明所在边是横边还是纵边

	//当下一个等值点找到后做相应的处理,如下：
	//1.记录该等值点的i,j
	//2.计算并保存该等值点的坐标
	//3.标志该等值点所在边的已经搜索过

	//验证i∈[0,rows-1], j∈[0,cols-1]
//	ASSERT( i>=0 && i<=m_gridDataInfo.rows-1 && j>=0 && j<=m_gridDataInfo.cols-1 );

	//1.
	NextPoint.i = i;
	NextPoint.j = j;
    NextPoint.bHorV = bHorizon;

	//2.
	CalcAndSaveOnePointCoord(i,j,bHorizon,NextPoint.x,NextPoint.y);

	//3.
	if( NextPoint.bHorV )
	{
		xSide[i][j] = -2.0f; //已经追踪过
	}
	else
	{	
		ySide[i][j] = -2.0f; //已经追踪过
	}

}

bool CContourTracer::TracingNextPoint()
{
/*  
  1.先确定出等值线的前进方向(自下向上、由左向右、自上向下、由右向左，其中之一)
  2.再追踪下一个等值点

  前进方向可以如下判定：
    if( 当前点.行号 > 前一点.行号 )
    {
	    下---->上
	}
	else if( 当前点.列号 > 前一点.列号 )
    {
		左---->右
	}
    else if( 当前点在横边上 )
	{
		上---->下
	}
	else
	{
	     右---->左
	}
       
*/

	int rows = m_gridDataInfo.rows;
	int cols = m_gridDataInfo.cols;

	if(CurrentPoint.i > PreviousPoint.i )
	{
		//TRACE0("下--->上\n");
			return FromBottom2TopTracingV2();

	}
	else if(CurrentPoint.j > PreviousPoint.j )
	{
		//TRACE0("左--->右\n");
		return FromLeft2RightTracingV2();

		
	}
	else if( CurrentPoint.bHorV == true /*curPt_Col_X < CurrentPoint.x*/ ) 
	{//在横边上。CurrentPoint.bHorizon == TRUE 和 curPt_Col_X < CurrentPoint.x ，这两个条件等价
		
		
//		ASSERT( CurrentPoint.i <= PreviousPoint.i &&
//			    CurrentPoint.j <= PreviousPoint.j );

		//TRACE0("上--->下\n");
		return FromTop2BottomTracingV2();
	
	}
	else
	{
// 		ASSERT(CurrentPoint.bHorV==FALSE);//在纵边上
// 
// 		ASSERT( CurrentPoint.i <= PreviousPoint.i &&
// 				CurrentPoint.j <= PreviousPoint.j );
		
		//TRACE0("右--->左\n");
		return	FromRight2LeftTracingV2();
	
	}
	
}


//自下向上追踪函数(第二版本)
bool CContourTracer::FromBottom2TopTracingV2()
{
/*	                   横边(i+1,j)
                      xSide[i+1][j]

                           ↑
				(i+1,j)    ∣    (i+1,j+1)
					|-----------|
					|           |
	  纵边(i,j)---→|           |←----纵边(i,j+1)
      ySide[i][j]	|           |     ySide[i][j+1]
	                |           |
	                |-----·-----|    
				(i,j)      ↖     (i,j+1)
				             ＼
							   等前等值点
*/
//	ASSERT( CurrentPoint.i > PreviousPoint.i );   //当前点的行号 > 前一点的行号
//	ASSERT( CurrentPoint.bHorV == TRUE );
	

	int i = CurrentPoint.i; 
	int j = CurrentPoint.j;
	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;
	if((j+1>cols-1)||(i<0)||(i>=rows-1))
		return false;

	if( ySide[i][j] < ySide[i][j+1] )
	{
		if( ySide[i][j] > 0 )
			HandlingAfterNextPointFounded(i,j,false);
		else
			HandlingAfterNextPointFounded(i,j+1,false);
	}
	else if( ySide[i][j] == ySide[i][j+1] )
	{
		if( ySide[i][j] < 0 /*namely, ySide[i][j] == ySide[i][j+1] == -2.0*/)
		{
			HandlingAfterNextPointFounded(i+1,j,true);
		}
		else
		{
			float xSideIJ = (m_valueTracing - m_ppGridData[i][j]) / ( m_ppGridData[i][j+1] - m_ppGridData[i][j] );
			if( xSideIJ <=0.5f )
			{
				HandlingAfterNextPointFounded(i,j,false);
			}
			else
			{
				HandlingAfterNextPointFounded(i,j+1,false);
			}
		}
	}
	else if( ySide[i][j] > ySide[i][j+1] )
	{
		if( ySide[i][j+1] > 0 )
			HandlingAfterNextPointFounded(i,j+1,false);
		else
			HandlingAfterNextPointFounded(i,j,false);		
	}
	return true;
}


//由左向右追踪函数(第二版本)
bool CContourTracer::FromLeft2RightTracingV2()
{
//	ASSERT( CurrentPoint.j > PreviousPoint.j );
//	ASSERT( CurrentPoint.bHorV == FALSE );
	
	int i = CurrentPoint.i; 
	int j = CurrentPoint.j;	
	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;
	if((i+1>rows-1) ||(j<0)||(j>=cols-1))
		return false;

	if( xSide[i][j] < xSide[i+1][j] )
	{
		if( xSide[i][j] > 0 )
			HandlingAfterNextPointFounded(i,j,true);
		else
			HandlingAfterNextPointFounded(i+1,j,true);
	}
	else if( xSide[i][j] == xSide[i+1][j] )
	{
		if( xSide[i][j] < 0 /*namely, xSide[i][j] == xSide[i+1][j] == -2.0*/)
		{
			HandlingAfterNextPointFounded(i,j+1,false);
		}
		else
		{		
			float ySideIJ = ( m_valueTracing - m_ppGridData[i][j]) / ( m_ppGridData[i+1][j] - m_ppGridData[i][j] );
			if( ySideIJ <= 0.5f )
				HandlingAfterNextPointFounded(i,j,true);
			else
				HandlingAfterNextPointFounded(i+1,j,true);
		}
	}
	else if( xSide[i][j] > xSide[i+1][j] )
	{
		if( xSide[i+1][j] > 0 )
			HandlingAfterNextPointFounded(i+1,j,true);
		else
			HandlingAfterNextPointFounded(i,j,true);

	}
	return true;
}


//从上到下追踪子函数的第二版本
bool CContourTracer::FromTop2BottomTracingV2()
{
	
	int i = CurrentPoint.i; 
	int j = CurrentPoint.j;
	int cols = m_gridDataInfo.cols;
	if((i-1<0)||(j+1)>cols-1)
		return false;
	
	//比较：ySide[i-1][j]      ySide[i-1][j+1]
	//                 
	//               xSide[i-1][j] 
	
	if( ySide[i-1][j] < ySide[i-1][j+1] )
	{
		if( ySide[i-1][j] > 0 )
			HandlingAfterNextPointFounded(i-1,j,false);
		else
			HandlingAfterNextPointFounded(i-1,j+1,false);
	}
	else if( ySide[i-1][j] == ySide[i-1][j+1] )
	{
		if( ySide[i-1][j] < 0 /*即ySide[i-1][j] == ySide[i-1][j+1] ==-2*/) 
		{
			HandlingAfterNextPointFounded(i-1,j,true);//下一点在对面的横边上
		}
		else
		{
			
			//注意:这里需要重新计算xSide[i][j]，因为在上一次已经被置为-2.0
			float xSideIJ = ( m_valueTracing - m_ppGridData[i][j] ) / ( m_ppGridData[i][j+1] - m_ppGridData[i][j] );
			if(  xSideIJ <= 0.5f )
			{
				HandlingAfterNextPointFounded(i-1,j,false);
			}
			else
			{
				HandlingAfterNextPointFounded(i-1,j+1,false);
			}
		}
	}
	else if( ySide[i-1][j] > ySide[i-1][j+1] )
	{
		if( ySide[i-1][j+1] > 0 )
			HandlingAfterNextPointFounded(i-1,j+1,false);
		else
			HandlingAfterNextPointFounded(i-1,j,false);
	}
	
	return true;
}
		
//由右向左(第二版本)
bool CContourTracer::FromRight2LeftTracingV2()
{/*   
	                   横边(i+1,j-1)
                      xSide[i+1][j-1]
                           ∣
			  (i+1,j-1)    ↓    (i+1,j)
					|-----------|
					|           |
    纵边(i,j-1)--→ |           ·←----等前等值点(P2)
   ySide[i][j-1]    |           |     
	                |           |
	                |-----------|    
			  (i,j-1)     ↑   (i,j)
				          ∣   
						  横边(i,j-1)
						 xSide[i][j-1]	   
*/
//	ASSERT( CurrentPoint.bHorV == FALSE );
	int i = CurrentPoint.i; 
	int j = CurrentPoint.j;	
	int rows = m_gridDataInfo.rows;
	if((j-1<0)||(i+1>rows-1))
		return false;

	if( xSide[i][j-1] < xSide[i+1][j-1] )
	{
		if( xSide[i][j-1] > 0 )
			HandlingAfterNextPointFounded(i,j-1,true);
		else
			HandlingAfterNextPointFounded(i+1,j-1,true);
	}
	else if( xSide[i][j-1] == xSide[i+1][j-1] )
	{
		if( xSide[i][j-1] < 0 /*namely, xSide[i][j-1] == xSide[i+1][j-1] == -2.0f*/ )
		{
			HandlingAfterNextPointFounded(i,j-1,false);
		}
		else
		{
			float ySideIJ = ( m_valueTracing - m_ppGridData[i][j]) / ( m_ppGridData[i+1][j] - m_ppGridData[i][j] );
			if( ySideIJ <= 0.5f )
				HandlingAfterNextPointFounded(i,j-1,true);
			else
				HandlingAfterNextPointFounded(i+1,j-1,true);
		}
	}
	else if( xSide[i][j-1] > xSide[i+1][j-1] )
	{
		if( xSide[i+1][j-1] > 0 )
			HandlingAfterNextPointFounded(i+1,j-1,true);
		else
			HandlingAfterNextPointFounded(i,j-1,true);
		
	}
	return true;
	
}

//追踪一条开等值线
void CContourTracer::TracingOneNonClosedContour()
{
	CCurve* pCtrLine = new CCurve;
	m_pCurveList->push_back(pCtrLine);
	
	m_currentCurveLine = pCtrLine;
	
	//记录下线头所在边的i，j，横纵边标识
	int startPt_i = CurrentPoint.i; 
	int startPt_j = CurrentPoint.j;
	bool startPt_bHoriz = CurrentPoint.bHorV;
	
	//验证线头在边界上
// 	ASSERT( startPt_i == 0                     ||  /*线头在底边界上*/
// 		startPt_i == m_gridDataInfo.rows-1 ||  /*线头在上边界上*/
// 		startPt_j == 0                     ||  /*线头在左边界上*/
// 		startPt_j == m_gridDataInfo.cols-1     /*线头在右边界上*/ 
// 		);

	CalcAndSaveOnePointCoord(startPt_i,startPt_j,startPt_bHoriz,CurrentPoint.x,CurrentPoint.y); //计算出线头的坐标并保存

	
	if( startPt_bHoriz )
	{
		xSide[startPt_i][startPt_j] = -2.0f;
	}
	else
	{
		ySide[startPt_i][startPt_j] = -2.0f;
	}
	
	if(!TracingNextPoint())//追踪出NextPoint
	{
		m_pCurveList->pop_back();
		delete pCtrLine;
		return;
	} 
	
	PreviousPoint = CurrentPoint;
	CurrentPoint = NextPoint;
	
	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;
	
	
	//遇到网格边界就结束追踪
	
	//------2004/03/09修改------------------
	//为了不让浮点数计算的误差引起追踪结束条件的判断失误，
	//我们不能用『CurrentPoint.y <= yMin』来判断是否遇到底边框,
	//  也不能用『CurrentPoint.x <= xMin』来判断是否遇到左边框
	bool bIsFinish = (CurrentPoint.i == 0 && CurrentPoint.bHorV == true )  ||  /*遇到底边界,(注:不能仅仅用CurrentPoint.i == 0判断)*/
		(CurrentPoint.j == 0 && CurrentPoint.bHorV == false );  /*遇到左边界,(注:不能仅仅用CurrentPoint.j == 0判断)*/
	
	
	
	
	while( !bIsFinish )
	{
		if(!TracingNextPoint())
			break;
		
		PreviousPoint = CurrentPoint;
		CurrentPoint = NextPoint;
		
		bIsFinish = (CurrentPoint.i == 0 && CurrentPoint.bHorV == true )  ||
			(CurrentPoint.j == 0 && CurrentPoint.bHorV == false );
		
	}

	if(pCtrLine->size()<2)
	{
		m_pCurveList->pop_back();
		delete pCtrLine;
	}
}

//追踪开曲线
void CContourTracer::TracingNonClosedContour()
{//该函数的关键是找出开曲线的线头，并设置好追踪前进的方向的条件
	
	int i,j;
	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;	

	//1.搜索底边框	
	for(j=0; j<cols-1; j++)
	{
		if( IsHavingPoint(xSide[0][j]) )
		{
			/*按自下向上的前进方向虚设前一点的i,j*/
			PreviousPoint.i = -1; // 假设前一点在-1行,这样下一点到当前点的前进方向就是自下向上的
			PreviousPoint.j = j;
			PreviousPoint.bHorV = true;

			CurrentPoint.i = 0; //底边的行号为0，所以设置线头的i为0
			CurrentPoint.j = j;
			CurrentPoint.bHorV = true; //底边是横边

			TracingOneNonClosedContour();	
		}
	}

	//2.搜索左边框(左边框在第0列)
	for(i=0; i<rows-1; i++)
	{
		if( IsHavingPoint(ySide[i][0]) )
		{
			/*按由左向右的前进方向虚设前一点的i,j*/
			PreviousPoint.i = i; 
			PreviousPoint.j = -1; //假设前一点在-1列,使其满足左-->右的前进方向
			PreviousPoint.bHorV = false;
			
			CurrentPoint.i = i; 
			CurrentPoint.j = 0; //左边框在第0列，所以设置线头的j为0
			CurrentPoint.bHorV = false; 
			
			TracingOneNonClosedContour();	
		}
	}

	//3.搜索上边框

	float deltX = ( m_gridDataInfo.xMax-m_gridDataInfo.xMin ) / ( m_gridDataInfo.cols-1 );
    float curPt_Col_X = m_gridDataInfo.xMin + CurrentPoint.j * deltX; //当前等值点所在边(i,j)的所标识的j列的X坐标
	
	for(j=0; j<cols-1; j++)
	{
		if( IsHavingPoint(xSide[rows-1][j]) )
		{
			/*虚设出由上向下追踪的条件
			  由上向下追踪的条件如下： 	 
			  1. Not( CurrentPoint.i > PreviousPoint.i )
			  2. Not( CurrentPoint.j > PreviousPoint.j )
			  3. CurrentPoint.x > m_gridDataInfo.xMin + CurrentPoint.j * deltX; 即:要求在横边上
			*/
			PreviousPoint.i = rows-1; 
			PreviousPoint.j = j;
			PreviousPoint.bHorV = true;
			
			CurrentPoint.i = rows-1; //上边框的行号为rows-1
			CurrentPoint.j = j;
			CurrentPoint.bHorV = true; //使其符合第三个条件


			//第三个条件条件不用虚设，只要边上存在就会满足第三个条件，因为上边框是横边
//			if( CurrentPoint.x < curPt_Col_X )
//			{
//				CurrentPoint.x = curPt_Col_X + 1; //为了保证让其满足第3个条件
//			}
			
			
		 	
			TracingOneNonClosedContour();	
		}
	}

	//4.搜索右边框(在第cols-1列，注意列号是从0开始计数的)

	
	for(i=0; i<rows-1; i++)
	{
		if( IsHavingPoint(ySide[i][cols-1]) )
		{
			/*虚设出由右向左追踪的条件
			
			  由右向左追踪的条件如下： 	 
			  1. Not( CurrentPoint.i > PreviousPoint.i )
			  2. Not( CurrentPoint.j > PreviousPoint.j )
			  3. Not( CurrentPoint.x > m_gridDataInfo.xMin + CurrentPoint.j * deltX ); 要求在纵边上			
			*/
			PreviousPoint.i = i; 
			PreviousPoint.j = cols-1; 
			PreviousPoint.bHorV = false;
			
			CurrentPoint.i = i; 
			CurrentPoint.j = cols-1; //右边框在第cols-1列
			CurrentPoint.bHorV = false;  //使其符合第三个条件

//			//虚设出第三个条件
//			CurrentPoint.x = curPt_Col_X - 1;//减去1，使之比curPt_Col_X小
			
			TracingOneNonClosedContour();	
		}
	}
	
}

void CContourTracer::TracingClosedContour()
{
	
	
	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;

	//搜索所有的除了边框外的纵边,从左到右搜索每一列上的纵边，对于一列，从下到上搜索
	for(int j=1; j<cols-1; j++) //j从1开始
		for(int i=0; i<rows-1; i++) //i从0开始
		{
			if( IsHavingPoint(ySide[i][j])) 
			{
				TracingOneClosedContour(i,j);				
			}
			
		}
}

//从纵边开始追踪一条封闭等值线(注：是从纵边开始搜索)
void CContourTracer::TracingOneClosedContour(int startPt_i, int startPt_j)
{//参数i,j是该闭曲线的第一个等值点的i,j

	CCurve* pCtrLine = new CCurve;
	
	m_pCurveList->push_back(pCtrLine);
	m_currentCurveLine = pCtrLine;
	
	//虚设前一等值点的i,j，让其满足从左向右追踪的条件
	PreviousPoint.i = startPt_i;
	PreviousPoint.j = 0;
	PreviousPoint.bHorV = false;
	
	CurrentPoint.i = startPt_i;
	CurrentPoint.j = startPt_j;
	CurrentPoint.bHorV = false;   //是FALSE，因为是在纵边上
	


	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;
	if((CurrentPoint.i == rows-1)||(CurrentPoint.j == cols-1))
		return; 
	//	float startPt_x;
	//	float startPt_y;
	CalcAndSaveOnePointCoord(startPt_i,startPt_j,false/*线头在纵边上*/,CurrentPoint.x,CurrentPoint.y);
	
	if(!TracingNextPoint())
	{
		m_pCurveList->pop_back();
		delete pCtrLine;
		return;
	}
	
	PreviousPoint = CurrentPoint;
	CurrentPoint = NextPoint;
	
	bool bColsed = false;	
	while(!bColsed) 
	{
		if(!TracingNextPoint())
			break;
// 		if(CheckCurve(*pCtrLine))
// 		{
// 			bColsed = true;
// 			break;
// 		}
		
		PreviousPoint = CurrentPoint;
		CurrentPoint = NextPoint;

		//------2004/03/09修改------------------
		//用等值点所在边的标识i,j来判断曲线是否封闭，不用x、y坐标来比较，因为浮点数计算会出现误差
		bColsed = ( CurrentPoint.i == startPt_i ) && 
			( CurrentPoint.j == startPt_j ) && 
			( CurrentPoint.bHorV == false );


		//if((CurrentPoint.i == rows-1)
		//	||(CurrentPoint.j == cols-1)
		//	||(CurrentPoint.i == 0)
		//	||(CurrentPoint.j == 0))
		//	break; 
	}
	if(bColsed)
	{
		ySide[startPt_i][startPt_j] = -2.0f; //已经追踪过
		
	}
	//不闭合或就一个点，无意义
	if(!bColsed || pCtrLine->size()<3)
	{
		m_pCurveList->pop_back();
		delete pCtrLine;
	}

}

bool CContourTracer::CheckCurve( CCurve & curve )
{
	unsigned size = curve.size();
	if(size<1)
		return false;
	CGeoPoint p = curve[size-1];
	CCurve::iterator b = curve.begin();
	CCurve::iterator last = b;
	for(unsigned i=0;i<size-1;i++)
	{
		CGeoPoint p1 = curve[i];
		if(p1 == p)
		{
			curve.erase(b,last);
			return true;
		}
		last ++;
	}

	return false;

}

