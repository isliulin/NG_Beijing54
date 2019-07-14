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
//	ASSERT( m_gridDataInfo.cols != 0 ); //�ڵ��øú���֮ǰ�������SetGridDataInfo()������������������Ϣ

	if( value < m_gridDataInfo.zMin && value > m_gridDataInfo.zMax )
	{
		return false;
	}


	m_valueTracing = value;


	//1.ΪxSide��ySide�����ڴ�ռ�
	AllocateMemory();

	//2.ɨ�������ݺ�ߣ��ڲ��ֵ��
	//�ú���֮�У��ڼ����ֵ��ʱ������׷��ֵ��������ϵ�������ͬʱ��
	//�ڼ���ǰ���ᶼ����������(����һСƫ��ֵ)
	InterpolateTracingValue(); 

	//3.��׷�ٿ�����
	TracingNonClosedContour();

	//4.��׷�ٱ�����
	TracingClosedContour(); 

	//5.�ͷſռ�
	//FreeMemory();

	return true;
	



	
}

void CContourTracer::AllocateMemory()
{// ����xSide��ySide�ռ�
	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;
	
	if( xSide == NULL )
	{
		//�����д���rows*(cols-1)����ߣ�������ҪΪxSide����rows*(cols-1)�ռ����

		C2DMemAllocator::AllocMemory2D(xSide,rows,cols-1/*not cols*/);
	}
	
	if( ySide == NULL )
	{
		//�����д���(rows-1)*cols���ݱߣ�������ҪΪySide����(rows-1)*cols�ռ����

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
		//�ͷſռ�
		C2DMemAllocator::FreeMemory2D(m_ppGridData);
		m_ppGridData = NULL;
	}
	
}



//ɨ��������ݡ���ߣ������Բ�ֵ�����ֵ������
//�������ϵĵ�ֵ������洢��xSide��ySide�����У�
// xSide�洢���к���ϵĵ�ֵ�����, ySide�洢�����ݱ��ϵĵ�ֵ�����
//�ڲ�ֵ����ʱ���ԡ���׷��ֵ��ȵ����ݡ�Ҫ�������������ż��㣬��������������ʱ��Ҫ�ı�ԭ��������
void CContourTracer::InterpolateTracingValue()
{
/*      ������ʶ����:
        
            (i+1,j)��--------��(i+1,j+1)
                    |        |
                    |        |
                    |        |
	                |        |
	         (i,j) ��--------��(i,j+1)

              i:��ʾ�к�(��������)
			  j:��ʾ�к�(��������)
			  ��ʶһ�����񽻵�ʱ���к���ǰ���к����ң��磺(i,j)
*/
/*        xSide,ySide�д洢rֵ��(wΪ׷��ֵ)
          ���������ߣ�r = (w - pData[i][j]) / (pData[i][j+1]-pData[i][j]);
		  ���������ݱߣ�r = (w - pData[i][j]) / (pData[i+1][j]-pData[i][j]);

		  ���ڸ����������xSide[i][j],ySide[i][j]�п��ܵ���1.0��0.0 
		  �������������
		  1����׷��ֵ��������ϵ�ֵ�ܽӽ�(�������)ʱ�������������ͻ����1.0
		     ����׷��0ֵʱ���������±�:
			       20 ��--------��-0.00000016   �˱�����0ֵ�������� (0-20)/(-0.00000016-20) == 1.0 

       
		  2��������������˵��ϵ�ֵ��������ʱ��
		     ����׷��2ֵ���������±ߣ�
		     1.70141E+038 ��--------��1   �˱�����2ֵ������(2-1.70141E+038) / (1-1.70141E+038) == 1.0 

        ��������е�ֵ��ʱ�������ϱ���ֵ�������0��1��
		 �����ڼ������������㷨���ж�ʱ����Ϊ0��1Ҳ���е�ֵ���

        ����xSide,ySide�д洢��ֵ��[0,1]�ı����䣬����(0,1)�Ŀ�����
*/
//	ASSERT( m_ppGridData!=NULL );
//	ASSERT( xSide != NULL );
//	ASSERT( ySide != NULL );
	
	int i,j;
	
	int   rows = m_gridDataInfo.rows;
	int   cols = m_gridDataInfo.cols;
	float  w   = m_valueTracing;
	float shift = 0.001f;  //����ֵ
 
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
	
	float H1,H2; //�ֱ��¼һ���ߵ��������ϵ�����ֵ
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

	/* ɨ�貢�������ϵĵ�ֵ��,��rows*(cols-1)�������Ҫɨ��*/
	for(i=0; i<rows ; i++)
	{
		for(j=0;j<cols-1;j++)
		{				
			/*������(i,j)�ϵ��󽻵�(i,j)�ϵ�ֵpData[i][j]
			                 ���ҽ���(i,j+1)��ֵpData[i][j+1]*/

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

	/* ɨ�貢�����ݱ��ϵ�ֵ��,��(rows-1)*cols���ݱ���Ҫɨ��*/
	for(i=0; i<rows-1;i++)
	{
		for(j=0; j<cols; j++)
		{			
			/*�����ݱ�(i,j)�ϵ��½���(i,j)�ϵ�ֵpData[i][j]
			                 ���Ͻ���(i+1,j)��ֵpData[i+1][j]*/
                                             
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
				 ��������е�ֵ��ʱ���洢��ֵ��[0,1] (������)
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
	{//�ں����
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
	{//���ݱ���
		if(i<rows-1 && j<cols)
		{
			x = m_gridDataInfo.xMin + j * deltX;
			y = m_gridDataInfo.yMin + ( i + ySide[i][j] ) * deltY;
			CGeoPoint point(x,y);
			m_currentCurveLine->push_back(point);
		}

	}



}

//����һ����ֵ���ҵ�������Ӧ�Ĵ���
void CContourTracer::HandlingAfterNextPointFounded(int i, int j, bool bHorizon)
{//����˵����i,j�ֱ��ǵ�ֵ�����ڱߵı�ţ�bHorizonָ�����ڱ��Ǻ�߻����ݱ�

	//����һ����ֵ���ҵ�������Ӧ�Ĵ���,���£�
	//1.��¼�õ�ֵ���i,j
	//2.���㲢����õ�ֵ�������
	//3.��־�õ�ֵ�����ڱߵ��Ѿ�������

	//��֤i��[0,rows-1], j��[0,cols-1]
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
		xSide[i][j] = -2.0f; //�Ѿ�׷�ٹ�
	}
	else
	{	
		ySide[i][j] = -2.0f; //�Ѿ�׷�ٹ�
	}

}

bool CContourTracer::TracingNextPoint()
{
/*  
  1.��ȷ������ֵ�ߵ�ǰ������(�������ϡ��������ҡ��������¡�������������֮һ)
  2.��׷����һ����ֵ��

  ǰ��������������ж���
    if( ��ǰ��.�к� > ǰһ��.�к� )
    {
	    ��---->��
	}
	else if( ��ǰ��.�к� > ǰһ��.�к� )
    {
		��---->��
	}
    else if( ��ǰ���ں���� )
	{
		��---->��
	}
	else
	{
	     ��---->��
	}
       
*/

	int rows = m_gridDataInfo.rows;
	int cols = m_gridDataInfo.cols;

	if(CurrentPoint.i > PreviousPoint.i )
	{
		//TRACE0("��--->��\n");
			return FromBottom2TopTracingV2();

	}
	else if(CurrentPoint.j > PreviousPoint.j )
	{
		//TRACE0("��--->��\n");
		return FromLeft2RightTracingV2();

		
	}
	else if( CurrentPoint.bHorV == true /*curPt_Col_X < CurrentPoint.x*/ ) 
	{//�ں���ϡ�CurrentPoint.bHorizon == TRUE �� curPt_Col_X < CurrentPoint.x �������������ȼ�
		
		
//		ASSERT( CurrentPoint.i <= PreviousPoint.i &&
//			    CurrentPoint.j <= PreviousPoint.j );

		//TRACE0("��--->��\n");
		return FromTop2BottomTracingV2();
	
	}
	else
	{
// 		ASSERT(CurrentPoint.bHorV==FALSE);//���ݱ���
// 
// 		ASSERT( CurrentPoint.i <= PreviousPoint.i &&
// 				CurrentPoint.j <= PreviousPoint.j );
		
		//TRACE0("��--->��\n");
		return	FromRight2LeftTracingV2();
	
	}
	
}


//��������׷�ٺ���(�ڶ��汾)
bool CContourTracer::FromBottom2TopTracingV2()
{
/*	                   ���(i+1,j)
                      xSide[i+1][j]

                           ��
				(i+1,j)    �O    (i+1,j+1)
					|-----------|
					|           |
	  �ݱ�(i,j)---��|           |��----�ݱ�(i,j+1)
      ySide[i][j]	|           |     ySide[i][j+1]
	                |           |
	                |-----��-----|    
				(i,j)      �I     (i,j+1)
				             ��
							   ��ǰ��ֵ��
*/
//	ASSERT( CurrentPoint.i > PreviousPoint.i );   //��ǰ����к� > ǰһ����к�
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


//��������׷�ٺ���(�ڶ��汾)
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


//���ϵ���׷���Ӻ����ĵڶ��汾
bool CContourTracer::FromTop2BottomTracingV2()
{
	
	int i = CurrentPoint.i; 
	int j = CurrentPoint.j;
	int cols = m_gridDataInfo.cols;
	if((i-1<0)||(j+1)>cols-1)
		return false;
	
	//�Ƚϣ�ySide[i-1][j]      ySide[i-1][j+1]
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
		if( ySide[i-1][j] < 0 /*��ySide[i-1][j] == ySide[i-1][j+1] ==-2*/) 
		{
			HandlingAfterNextPointFounded(i-1,j,true);//��һ���ڶ���ĺ����
		}
		else
		{
			
			//ע��:������Ҫ���¼���xSide[i][j]����Ϊ����һ���Ѿ�����Ϊ-2.0
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
		
//��������(�ڶ��汾)
bool CContourTracer::FromRight2LeftTracingV2()
{/*   
	                   ���(i+1,j-1)
                      xSide[i+1][j-1]
                           �O
			  (i+1,j-1)    ��    (i+1,j)
					|-----------|
					|           |
    �ݱ�(i,j-1)--�� |           ����----��ǰ��ֵ��(P2)
   ySide[i][j-1]    |           |     
	                |           |
	                |-----------|    
			  (i,j-1)     ��   (i,j)
				          �O   
						  ���(i,j-1)
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

//׷��һ������ֵ��
void CContourTracer::TracingOneNonClosedContour()
{
	CCurve* pCtrLine = new CCurve;
	m_pCurveList->push_back(pCtrLine);
	
	m_currentCurveLine = pCtrLine;
	
	//��¼����ͷ���ڱߵ�i��j�����ݱ߱�ʶ
	int startPt_i = CurrentPoint.i; 
	int startPt_j = CurrentPoint.j;
	bool startPt_bHoriz = CurrentPoint.bHorV;
	
	//��֤��ͷ�ڱ߽���
// 	ASSERT( startPt_i == 0                     ||  /*��ͷ�ڵױ߽���*/
// 		startPt_i == m_gridDataInfo.rows-1 ||  /*��ͷ���ϱ߽���*/
// 		startPt_j == 0                     ||  /*��ͷ����߽���*/
// 		startPt_j == m_gridDataInfo.cols-1     /*��ͷ���ұ߽���*/ 
// 		);

	CalcAndSaveOnePointCoord(startPt_i,startPt_j,startPt_bHoriz,CurrentPoint.x,CurrentPoint.y); //�������ͷ�����겢����

	
	if( startPt_bHoriz )
	{
		xSide[startPt_i][startPt_j] = -2.0f;
	}
	else
	{
		ySide[startPt_i][startPt_j] = -2.0f;
	}
	
	if(!TracingNextPoint())//׷�ٳ�NextPoint
	{
		m_pCurveList->pop_back();
		delete pCtrLine;
		return;
	} 
	
	PreviousPoint = CurrentPoint;
	CurrentPoint = NextPoint;
	
	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;
	
	
	//��������߽�ͽ���׷��
	
	//------2004/03/09�޸�------------------
	//Ϊ�˲��ø�����������������׷�ٽ����������ж�ʧ��
	//���ǲ����á�CurrentPoint.y <= yMin�����ж��Ƿ������ױ߿�,
	//  Ҳ�����á�CurrentPoint.x <= xMin�����ж��Ƿ�������߿�
	bool bIsFinish = (CurrentPoint.i == 0 && CurrentPoint.bHorV == true )  ||  /*�����ױ߽�,(ע:���ܽ�����CurrentPoint.i == 0�ж�)*/
		(CurrentPoint.j == 0 && CurrentPoint.bHorV == false );  /*������߽�,(ע:���ܽ�����CurrentPoint.j == 0�ж�)*/
	
	
	
	
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

//׷�ٿ�����
void CContourTracer::TracingNonClosedContour()
{//�ú����Ĺؼ����ҳ������ߵ���ͷ�������ú�׷��ǰ���ķ��������
	
	int i,j;
	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;	

	//1.�����ױ߿�	
	for(j=0; j<cols-1; j++)
	{
		if( IsHavingPoint(xSide[0][j]) )
		{
			/*���������ϵ�ǰ����������ǰһ���i,j*/
			PreviousPoint.i = -1; // ����ǰһ����-1��,������һ�㵽��ǰ���ǰ����������������ϵ�
			PreviousPoint.j = j;
			PreviousPoint.bHorV = true;

			CurrentPoint.i = 0; //�ױߵ��к�Ϊ0������������ͷ��iΪ0
			CurrentPoint.j = j;
			CurrentPoint.bHorV = true; //�ױ��Ǻ��

			TracingOneNonClosedContour();	
		}
	}

	//2.������߿�(��߿��ڵ�0��)
	for(i=0; i<rows-1; i++)
	{
		if( IsHavingPoint(ySide[i][0]) )
		{
			/*���������ҵ�ǰ����������ǰһ���i,j*/
			PreviousPoint.i = i; 
			PreviousPoint.j = -1; //����ǰһ����-1��,ʹ��������-->�ҵ�ǰ������
			PreviousPoint.bHorV = false;
			
			CurrentPoint.i = i; 
			CurrentPoint.j = 0; //��߿��ڵ�0�У�����������ͷ��jΪ0
			CurrentPoint.bHorV = false; 
			
			TracingOneNonClosedContour();	
		}
	}

	//3.�����ϱ߿�

	float deltX = ( m_gridDataInfo.xMax-m_gridDataInfo.xMin ) / ( m_gridDataInfo.cols-1 );
    float curPt_Col_X = m_gridDataInfo.xMin + CurrentPoint.j * deltX; //��ǰ��ֵ�����ڱ�(i,j)������ʶ��j�е�X����
	
	for(j=0; j<cols-1; j++)
	{
		if( IsHavingPoint(xSide[rows-1][j]) )
		{
			/*�������������׷�ٵ�����
			  ��������׷�ٵ��������£� 	 
			  1. Not( CurrentPoint.i > PreviousPoint.i )
			  2. Not( CurrentPoint.j > PreviousPoint.j )
			  3. CurrentPoint.x > m_gridDataInfo.xMin + CurrentPoint.j * deltX; ��:Ҫ���ں����
			*/
			PreviousPoint.i = rows-1; 
			PreviousPoint.j = j;
			PreviousPoint.bHorV = true;
			
			CurrentPoint.i = rows-1; //�ϱ߿���к�Ϊrows-1
			CurrentPoint.j = j;
			CurrentPoint.bHorV = true; //ʹ����ϵ���������


			//���������������������裬ֻҪ���ϴ��ھͻ������������������Ϊ�ϱ߿��Ǻ��
//			if( CurrentPoint.x < curPt_Col_X )
//			{
//				CurrentPoint.x = curPt_Col_X + 1; //Ϊ�˱�֤���������3������
//			}
			
			
		 	
			TracingOneNonClosedContour();	
		}
	}

	//4.�����ұ߿�(�ڵ�cols-1�У�ע���к��Ǵ�0��ʼ������)

	
	for(i=0; i<rows-1; i++)
	{
		if( IsHavingPoint(ySide[i][cols-1]) )
		{
			/*�������������׷�ٵ�����
			
			  ��������׷�ٵ��������£� 	 
			  1. Not( CurrentPoint.i > PreviousPoint.i )
			  2. Not( CurrentPoint.j > PreviousPoint.j )
			  3. Not( CurrentPoint.x > m_gridDataInfo.xMin + CurrentPoint.j * deltX ); Ҫ�����ݱ���			
			*/
			PreviousPoint.i = i; 
			PreviousPoint.j = cols-1; 
			PreviousPoint.bHorV = false;
			
			CurrentPoint.i = i; 
			CurrentPoint.j = cols-1; //�ұ߿��ڵ�cols-1��
			CurrentPoint.bHorV = false;  //ʹ����ϵ���������

//			//���������������
//			CurrentPoint.x = curPt_Col_X - 1;//��ȥ1��ʹ֮��curPt_Col_XС
			
			TracingOneNonClosedContour();	
		}
	}
	
}

void CContourTracer::TracingClosedContour()
{
	
	
	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;

	//�������еĳ��˱߿�����ݱ�,����������ÿһ���ϵ��ݱߣ�����һ�У����µ�������
	for(int j=1; j<cols-1; j++) //j��1��ʼ
		for(int i=0; i<rows-1; i++) //i��0��ʼ
		{
			if( IsHavingPoint(ySide[i][j])) 
			{
				TracingOneClosedContour(i,j);				
			}
			
		}
}

//���ݱ߿�ʼ׷��һ����յ�ֵ��(ע���Ǵ��ݱ߿�ʼ����)
void CContourTracer::TracingOneClosedContour(int startPt_i, int startPt_j)
{//����i,j�Ǹñ����ߵĵ�һ����ֵ���i,j

	CCurve* pCtrLine = new CCurve;
	
	m_pCurveList->push_back(pCtrLine);
	m_currentCurveLine = pCtrLine;
	
	//����ǰһ��ֵ���i,j�����������������׷�ٵ�����
	PreviousPoint.i = startPt_i;
	PreviousPoint.j = 0;
	PreviousPoint.bHorV = false;
	
	CurrentPoint.i = startPt_i;
	CurrentPoint.j = startPt_j;
	CurrentPoint.bHorV = false;   //��FALSE����Ϊ�����ݱ���
	


	int cols = m_gridDataInfo.cols;
	int rows = m_gridDataInfo.rows;
	if((CurrentPoint.i == rows-1)||(CurrentPoint.j == cols-1))
		return; 
	//	float startPt_x;
	//	float startPt_y;
	CalcAndSaveOnePointCoord(startPt_i,startPt_j,false/*��ͷ���ݱ���*/,CurrentPoint.x,CurrentPoint.y);
	
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

		//------2004/03/09�޸�------------------
		//�õ�ֵ�����ڱߵı�ʶi,j���ж������Ƿ��գ�����x��y�������Ƚϣ���Ϊ�����������������
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
		ySide[startPt_i][startPt_j] = -2.0f; //�Ѿ�׷�ٹ�
		
	}
	//���պϻ��һ���㣬������
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

