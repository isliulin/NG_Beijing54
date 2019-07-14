#include "DataTypes.h"
#include <math.h>
#include <float.h>
#include <Guiddef.h>
#include <Objbase.h>
#include "MacroDef.h"
#include "../KoordTrans/KoordTrans/KoordTrans.h"
#include "../EarthCoordCompute/EarthCoordManage.h"
#include "GlobalFunction.h"

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

//判断点是否在多边形内
bool PtInPolygon (CDoublePoint& p, CDoublePoint* ptPolygon, int nCount)
{
	int nCross = 0;	
	for (int i = 0; i < nCount; i++) 
	{
		CDoublePoint& p1 = ptPolygon[i];  
		CDoublePoint& p2 = ptPolygon[(i + 1) % nCount];

		// 求解 y=p.y 与 p1p2 的交点  

		if ( p1.y == p2.y )      // p1p2 与 y=p0.y平行
			continue;

		if ( p.y <  min(p1.y, p2.y) )   // 交点在p1p2延长线上
			continue;
		if ( p.y >= max(p1.y, p2.y) )   // 交点在p1p2延长线上
			continue;

		// 求交点的 X 坐标 --------------------------------------------------------------
		double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;

		if ( x > p.x ) 
			nCross++;       // 只统计单边交点
	}

	// 单边交点为偶数，点在多边形之外 ---
	return (nCross % 2 == 1);
}

//求点到多边形或者折线的最近距离 ---KM
//Pt2PolygonDis
//p：待判断的点
//ptPolygon：多边形或者折线上的点
//nCount: 多边形或者折线上点的个数
//bClosed: 是否闭合
//返回值：单位为km
double Pt2PolygonDis (CDoublePoint& p, CDoublePoint* ptPolygon, int nCount, bool bClosed)
{
	//从第0个点开始一个一个算吧
	double dAzi1 = 0.0;
	double dAzi2 = 0.0;
	double dAzip1 = 0.0;
	double dAzip2 = 0.0;
	double dAngle1 = 0.0;
	double dAngle2 = 0.0;
	double dMinDis = 0.0;
	double dTmpMinDis = 0.0;
	double dDis1 = 0.0;
	double dDis2 = 0.0;
	double dDisp1 = 0.0;
	double dDisp2 = 0.0;
	double dPxRad = 0.0;
	double dPyRad = 0.0;
	int nEndIndex = nCount-1;

	DecimalToRad(p.x, dPxRad);
	DecimalToRad(p.y, dPyRad);

	EarthCoord2D earth2D;
	earth2D.Set_CurrentEllipSoid_Index(0);
	DecimalToRad(ptPolygon[0].x, earth2D.m_LonRad1);
	DecimalToRad(ptPolygon[0].y, earth2D.m_LatRad1);

	earth2D.m_LonRad2 = dPxRad;
	earth2D.m_LatRad2 = dPyRad;

	earth2D.CalDistance2D();
	dDisp1 = earth2D.m_DistEllip;
	dAzip1 = earth2D.m_AzRad1;

	dMinDis = DBL_MAX;//单位M
	if(bClosed)
	{
		nEndIndex = nCount;
	}
	else //如果不是封闭的，不需要计算最后一个点和第一个点
	{
		nEndIndex = nCount - 1;
	}
	for(int i=1; i<=nEndIndex; i++)
	{
		//求i点和i-1点与p点的距离和角度关系
		DecimalToRad(ptPolygon[i-1].x, earth2D.m_LonRad1);
		DecimalToRad(ptPolygon[i-1].y, earth2D.m_LatRad1);

		DecimalToRad(ptPolygon[i%nCount].x, earth2D.m_LonRad2);
		DecimalToRad(ptPolygon[i%nCount].y, earth2D.m_LatRad2);

		earth2D.CalDistance2D();

		dAzi1 = earth2D.m_AzRad1;
		dAzi2 = earth2D.m_AzRad2;

		//计算i点和p的角度和距离关系
		earth2D.m_LonRad1 = dPxRad;
		earth2D.m_LatRad1 = dPyRad;

		earth2D.CalDistance2D();
		dDisp2 = earth2D.m_DistEllip;
		dAzip2 = earth2D.m_AzRad2;

		//判断角度和距离之间的关系
		dAngle1 = fabs(dAzi1 - dAzip1);
		if(dAngle1 > PI)
		{
			dAngle1 = PI_2 - dAngle1;
		}
		dAngle2 = fabs(dAzi2 - dAzip2);
		if(dAngle2 >PI)
		{
			dAngle2 = PI_2 - dAngle2;
		}

		if(dAngle1 >= HALF_PI) //钝角
		{
			dTmpMinDis = dDisp1;
		}
		else if(dAngle2 >= HALF_PI) //第二个角是钝角
		{
			dTmpMinDis = dDisp2;
		}
		else
		{
			//当两个角度都为锐角时,需要求点到垂足的距离
			dTmpMinDis = dDisp1*sin(dAngle1);
		}

		if(dTmpMinDis < dMinDis)
		{
			dMinDis = dTmpMinDis;
		}
		//替换上一次的角度和距离
		dAzip1 = dAzip2;
		dDisp1 = dDisp2;
	}

	return dMinDis*(1e-3);  //转换为km
}

void CalVerticalAndHorizontalAngle(double dXBasePos, double dYBasePos, double dXCurPos, double dYCurPos, bool bGeoSys,
								                                   double inBsHeight, double inRtHeight, AngleInDeg dTilt,AngleInDeg dAzi,
								                                   double& px,double& py,double& pz)
{
	//将BS作为坐标原点，计算3维坐标系中X的大小，（正东方向为X正轴，正北为y正轴）
	if (bGeoSys)
	{
		//如果是经纬度坐标系
		//计算发射点和接收点之间的距离
		EarthCoord2D earth2D;
		earth2D.Set_CurrentEllipSoid_Index(0);

		DecimalToRad(dXBasePos, earth2D.m_LonRad1);
		DecimalToRad(dYBasePos, earth2D.m_LatRad1);

		DecimalToRad(dXCurPos, earth2D.m_LonRad2);
		DecimalToRad(dYCurPos, earth2D.m_LatRad2);

		//计算方向和距离
		earth2D.CalDistance2D();
		px = earth2D.m_DistEllip * sin(earth2D.m_AzRad1);
		py = earth2D.m_DistEllip * cos(earth2D.m_AzRad1);
	}else
	{
		py = dYCurPos - dYBasePos;
		px = dXCurPos -  dXBasePos;
	}

	pz = inRtHeight - inBsHeight;
	//此处考虑坐标系在旋转，相当于点逆旋转
	//方位角是绕Z轴顺时针旋转
	dAzi =   dAzi / 180 * PI;
	double sinangle = sin(dAzi) , cosangle = cos(dAzi);
	double temp  = px * cosangle - py * sinangle;
	py = px * sinangle + py * cosangle;
	px= temp;

	//俯仰角是绕X轴顺时针旋转
	dTilt =  dTilt /180 * PI;
	sinangle = sin(dTilt) , cosangle = cos(dTilt);
	temp = py * cosangle - pz * sinangle;
	pz = py * sinangle  + pz * cosangle;
	py = temp;

	
}

// 计算垂直方向角度
AngleInDeg CalVerticalAngle(double inBsHeight, double inRtHeight, double inDistance)
{
	return atan((inBsHeight - inRtHeight) / inDistance) * 180.0 / PI;	
}

//计算水平方向角度
AngleInDeg CalHorizontalAngle(double dXBasePos, double dYBasePos, 
							  double dXCurPos, double dYCurPos,
							  bool bGeoSys)
{	
	AngleInDeg angle = 0;

	if(bGeoSys)
	{
		//计算发射点和接收点之间的距离
		EarthCoord2D earth2D;
		earth2D.Set_CurrentEllipSoid_Index(0);

		DecimalToRad(dXBasePos, earth2D.m_LonRad1);
		DecimalToRad(dYBasePos, earth2D.m_LatRad1);

		DecimalToRad(dXCurPos, earth2D.m_LonRad2);
		DecimalToRad(dYCurPos, earth2D.m_LatRad2);

		//计算方向和距离
		earth2D.CalDistance2D();

		//获取角度
		RadToDecimal(earth2D.m_AzRad1, angle);
	}
	else
	{
		float delta_x = float(dXCurPos)-float(dXBasePos);
		float delta_y = float(dYCurPos)-float(dYBasePos);


		if (delta_y==0) angle = ((delta_x>=0) ? 90.0f : 270.0f);
		else angle = (float)(180.0 / PI * atan(delta_x / delta_y));

		if (delta_y<0)
		{
			angle = 180+angle;
		}
		if (angle<0) angle+=360.0;
	}

	return angle;	
}

//计算两点之间的距离
double CalDistanseM(double x1, double y1, double x2, double y2, bool bGeoSys)
{
	double dDisM = 0.0;
	if(bGeoSys)
	{
		EarthCoord2D earth2D;
		earth2D.Set_CurrentEllipSoid_Index(0);

		DecimalToRad(x1, earth2D.m_LonRad1);
		DecimalToRad(y1, earth2D.m_LatRad1);

		DecimalToRad(x2, earth2D.m_LonRad2);
		DecimalToRad(y2, earth2D.m_LatRad2);

		//计算方向和距离
		earth2D.CalDistance2D();
		dDisM = earth2D.m_DistEllip;
	}
	else
	{
		double delta_x = (x2)-(x1);
		double delta_y = (y2)-(y1);
		dDisM = sqrt(delta_x*delta_x + delta_y*delta_y);
	}
	return dDisM;
}

//计算给定两点之间的3D距离，单位M
double Cal3DDistanseM(double x1, double y1, double z1, double x2, double y2, double z2, bool bGeoSys)
{
	double dDisM = 0.0;
	if(bGeoSys)
	{
		EarthCoord3D earth3D;
		earth3D.Set_CurrentEllipSoid_Index((int)0);

		DecimalToRad(x1, earth3D.m_LonRad1);
		DecimalToRad(y1, earth3D.m_LatRad1);
		earth3D.m_h1 = z1;

		DecimalToRad(x2, earth3D.m_LonRad2);
		DecimalToRad(y2, earth3D.m_LatRad2);
		earth3D.m_h2 = z2;

		//计算方向和距离
		earth3D.CalDistance3D();
		dDisM = earth3D.m_Distmm;
	}
	else
	{
		double delta_x = (x2)-(x1);
		double delta_y = (y2)-(y1);
		double delta_z = (z2)-(z1);
		dDisM = sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z);
	}
	return dDisM;
}


//计算经纬度地图的一个栅格的面积
double CalLongLatArea(CDoublePoint& PointLeftLLC, CDoublePoint& PointRightLLC)
{
	EarthCoord2D earth2D;
	earth2D.Set_CurrentEllipSoid_Index(0);

	DecimalToRad(PointLeftLLC.x, earth2D.m_LonRad1);
	DecimalToRad(PointLeftLLC.y, earth2D.m_LatRad1);

	DecimalToRad(PointRightLLC.x, earth2D.m_LonRad2);
	DecimalToRad(PointLeftLLC.y, earth2D.m_LatRad2);

	//计算方向和距离
	earth2D.CalDistance2D();

	double dWidth = earth2D.m_DistEllip;
	DecimalToRad(PointLeftLLC.x, earth2D.m_LonRad1);
	DecimalToRad(PointLeftLLC.y, earth2D.m_LatRad1);

	DecimalToRad(PointLeftLLC.x, earth2D.m_LonRad2);
	DecimalToRad(PointRightLLC.y, earth2D.m_LatRad2);

	//计算方向和距离
	earth2D.CalDistance2D();
	double dHeight = earth2D.m_DistEllip;
	double dArea = dWidth*dHeight;
	return dArea;
}

//判断点是否在三角形内部
bool PtIn2DTriangle (double xA, double yA, double xB, double yB, double xC, double yC, double xP, double yP)
{
	double dABAP = (xB-xA)*(yP-yA) - (yB-yA)*(xP-xA);
	double dBCBP = (xC-xB)*(yP-yB) - (yC-yB)*(xP-xB);
	double dCACP = (xA-xC)*(yP-yC) - (yA-yC)*(xP-xC);

	if( ((dABAP >= 0) && (dBCBP >= 0) && (dCACP >= 0)) ||
		((dABAP <= 0) && (dBCBP <= 0) && (dCACP <= 0)) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////
//函数描述：获取矩形框左下角坐标，矩形框宽度高度
//参数描述：
//输入参数：(in&out)rect：待获取信息的矩形框
//          dxMapLowLeft: 地图左下角坐标x
//          dyMapLowLeft: 地图左下角坐标y
//          nObjCoordSys: 目标坐标系，与地图坐标系相同
//  (in&out)dxObjRes: 目标分辨率x，输入时单位为米，输出时变为与nObjCoordSys坐标系相同
//  (in&out)dyObjRes: 目标分辨率y，输入时单位为米，输出时变为与nObjCoordSys坐标系相同
//输出参数：dxRectLowLeft: 矩形框左下角坐标X
//          dyRectLowLeft: 矩形框左下角坐标Y
//          nHeight: 矩形框在目标分辨率下的高度
//          nWidth: 矩形框在目标分辨率下的宽度
//////////////////////////////////////////////////////////////////////////
int GetGeoRectInfo(CGeoRectangle& rect, double dxMapLowLeft, double dyMapLowLeft,  
				   int nObjCoordSys, double& dxObjRes, double& dyObjRes, 
				   double& dxRectLowLeft, double& dyRectLowLeft, int& nWidth, int& nHeight)
{
	const double C_Degree2M = C_DEGREE2M; //目前默认按照1度对应110km
	int nRet = NG_SUCCESS;	

	//判断矩形框的坐标系与目标坐标系是否相同
	if(rect.m_nCoordSys != nObjCoordSys)
	{
		ng_geo_init();

		//将矩形框的坐标转换为目标坐标系的坐标
		ng_geo_trans(rect.m_nCoordSys, nObjCoordSys, rect.m_Corner1.x, rect.m_Corner1.y, 
			&(rect.m_Corner1.x), &(rect.m_Corner1.y));
		ng_geo_trans(rect.m_nCoordSys, nObjCoordSys, rect.m_Corner2.x, rect.m_Corner2.y, 
			&(rect.m_Corner2.x), &(rect.m_Corner2.y));

		rect.m_nCoordSys = nObjCoordSys;
	}

	//判断分辨率的情况,分辨率输入时单位为米,如果是经纬度地图，需要将分辨率转换为度
	if(ng_IsGeoSystem(nObjCoordSys))
	{
		dxObjRes = dxObjRes / C_Degree2M;
		dyObjRes = dyObjRes / C_Degree2M;		
	}

	//计算对齐的左下角坐标
	dxRectLowLeft = floor((rect.m_Corner1.x - dxMapLowLeft)/dxObjRes)*dxObjRes + dxMapLowLeft;
	dyRectLowLeft = floor((rect.m_Corner1.y - dyMapLowLeft)/dyObjRes)*dyObjRes + dyMapLowLeft;

	//计算矩形框的长宽
	nWidth = int((rect.m_Corner2.x - dxRectLowLeft)/dxObjRes) + 1;
	nHeight = int((rect.m_Corner2.y - dyRectLowLeft)/dyObjRes) + 1;

	return nRet;
}

//////////////////////////////////////////////////////////////////////////
//函数描述：获取圆的切矩形
//参数描述：
//输入参数: circle：待获取外切矩形的圆
//          nCoordSys：圆半径的坐标系
//输出参数：rect: 外切矩形
//          nDstCoordSys: 目标坐标系 
//////////////////////////////////////////////////////////////////////////
int GetGeoRectofCircle(CGeoCircle& circle, CGeoRectangle& rect, int nDstCoordSys)
{
	int nRet = NG_SUCCESS;
	CGeoRectangle rectLocal;
	double dRadiusM = circle.m_dRadiusKM * (1e3);


	rectLocal.m_Corner1.x = circle.m_Center.x - dRadiusM;
	rectLocal.m_Corner2.x = circle.m_Center.x + dRadiusM;
	rectLocal.m_Corner1.y = circle.m_Center.y - dRadiusM;
	rectLocal.m_Corner2.y = circle.m_Center.y + dRadiusM;

	//圆的坐标是经纬度
	if(ng_IsGeoSystem(circle.m_nCoordSys))
	{
		if(!ng_IsGeoSystem(nDstCoordSys))
		{
			//转换为目标坐标系的坐标
			ng_geo_init();
			ng_geo_trans(circle.m_nCoordSys, nDstCoordSys, rectLocal.m_Corner1.x, rectLocal.m_Corner1.y,
				&(rect.m_Corner1.x), &(rect.m_Corner1.y));
			ng_geo_trans(circle.m_nCoordSys, nDstCoordSys, rectLocal.m_Corner2.x, rectLocal.m_Corner2.y,
				&(rect.m_Corner2.x), &(rect.m_Corner2.y));

			rect.m_nCoordSys = nDstCoordSys;
			rect.m_dASLM = circle.m_dASLM;			
		}
		else
		{
			rect = rectLocal;
			rect.m_nCoordSys = nDstCoordSys;
			rect.m_dASLM = circle.m_dASLM;	
		}		
	}
	else
	{
		if(!ng_IsGeoSystem(nDstCoordSys))
		{
			rect = rectLocal;
			rect.m_nCoordSys = nDstCoordSys;
			rect.m_dASLM = circle.m_dASLM;		
		}
		else //目标是度
		{
			ng_geo_init();
			ng_geo_trans(circle.m_nCoordSys, nDstCoordSys, rectLocal.m_Corner1.x, rectLocal.m_Corner1.y,
				&(rect.m_Corner1.x), &(rect.m_Corner1.y));
			ng_geo_trans(circle.m_nCoordSys, nDstCoordSys, rectLocal.m_Corner2.x, rectLocal.m_Corner2.y,
				&(rect.m_Corner2.x), &(rect.m_Corner2.y));

			rect.m_nCoordSys = nDstCoordSys;
			rect.m_dASLM = circle.m_dASLM;	
		}
	}

	return nRet;
}

//////////////////////////////////////////////////////////////////////////
//函数描述获取多边形的外接矩形
//////////////////////////////////////////////////////////////////////////
int GetGeoRectofPolygon(CGeoPolygon& polygon, CGeoRectangle& rect)
{
	int nRet = NG_SUCCESS;
	double xLeft = DBL_MAX;
	double yLow = DBL_MAX;
	double xRight = -DBL_MAX;
	double yTop = -DBL_MAX;

	if(polygon.m_nPointsNum == 0)
	{
		return NG_SUCCESS;//错误码待定 
	}
	for(int i = 0; i<polygon.m_nPointsNum; i++)
	{
		if(xLeft > polygon.m_pPointData[i].x)
		{
			xLeft = polygon.m_pPointData[i].x;
		}
		if(xRight < polygon.m_pPointData[i].x)
		{
			xRight = polygon.m_pPointData[i].x;
		}
		if(yLow > polygon.m_pPointData[i].y)
		{
			yLow = polygon.m_pPointData[i].y;
		}
		if(yTop < polygon.m_pPointData[i].y)
		{
			yTop = polygon.m_pPointData[i].y;
		}
	}

	rect.m_Corner1.x = xLeft;
	rect.m_Corner1.y = yLow;
	rect.m_Corner2.x = xRight;
	rect.m_Corner2.y = yTop;
	rect.m_dASLM = polygon.m_pPointData[0].z;
	rect.m_nCoordSys = polygon.m_nCoordSys;

	return nRet;
}

int GetRasterResultParam(CGeoShape* pShap, CalResult_AreaType type,ICalGis_MapManger* pGisAdapter,double& ResX,double& ResY
						 ,int nObjCoordSys,double& dxRectLowLeft, double& dyRectLowLeft, int& nWidth, int& nHeight)
{
	if (pShap==NULL) return NO_AREA_INFO;
	if(pGisAdapter==NULL) return NG_NO_MAP_DATA;

	//
	CGeoRectangle rect;
	double dxMapLowLeft,dyMapLowLeft;
	dxMapLowLeft = pGisAdapter->GetMapLowerLeftXCoord();
	dyMapLowLeft = pGisAdapter->GetMapLowerLeftYCoord();
	if (type==CAL_AREA_POLYGON)
	{
		GetGeoRectofPolygon(*(CGeoPolygon*)pShap,rect);
	}
	else if(type==CAL_AREA_CIRCLE)
	{
		GetGeoRectofCircle(*(CGeoCircle*)pShap, rect,pShap->m_nCoordSys);
	}
	else if (type==CAL_AREA_RECT)
	{
		rect = *((CGeoRectangle*)pShap);
	}
	else
	{
		return NG_NO_MAP_DATA;
	}

	//
	return GetGeoRectInfo(rect,dxMapLowLeft,dyMapLowLeft,nObjCoordSys,ResX,ResY,dxRectLowLeft,dyRectLowLeft,nWidth,nHeight);

}

bool GetTransmodelFrequencyRange( ETransModel transId, double &freqMinMhz, double &freqMaxMhz )
{
	if (transId < eTransNull)
	{
		return false;
	}
    freqMinMhz = -1;
    freqMaxMhz = -1;
	switch(transId)
	{
	case eTransNull:
	case eFreeSpace:
	case eLOSModel:
	case eDiffractionModel:
		{
			freqMinMhz = 0.000001;
			freqMaxMhz = 300000;
			break;
		}
	case eCost231Hata1:
		{
			freqMinMhz = 150;
			freqMaxMhz = 1500;
			break;
		}
	case eITURP1546:
	case eHCM:
	case eITURP1546_4:
	case eIRT3D:
	case eIRT3D_CELL:
	case eITU1812:
		{
			freqMinMhz = 30;
			freqMaxMhz = 3000;
			break;
		}
	case eITURP370:
		{
			freqMinMhz = 30;
			freqMaxMhz = 1000;
			break;
		}
	case eLONGLEYRICE:
		{
			freqMinMhz = 20;
			freqMaxMhz = 40000;
			break;
		}
	case eITU533ShortWave:
		{
			freqMinMhz = 3;
			freqMaxMhz = 30;
			break;
		}
	case eITU530MicWave:
	case eITU530V10MicWave:
		{
			freqMinMhz = 450;
			freqMaxMhz = 70000;
			break;
		}
	case eITU618:
	case eITU619:
	case eITU676:
	case eAP28:
	case eAP30:
		{
			freqMinMhz = 1000;
			freqMaxMhz = 55000;
			break;
		}
	case eAeroNautical:
		{
			freqMinMhz = 12.5;
			freqMaxMhz = 30000;
			break;
		}
	case eCost231Hata2:
		{
			freqMinMhz = 1500;
			freqMaxMhz = 2400;
			break;
		}
	case eModifiedHata:
		{
			freqMinMhz = 100;
			freqMaxMhz = 3000;
			break;
		}
	case eLeeModel:
		{
			freqMinMhz = 30;
			freqMaxMhz = 3000;
			break;	
		}
	case eWalfishIkegami:
		{
			freqMinMhz = 800;
			freqMaxMhz = 2000;
			break;
		}
	case eSUIModel:
		{
			freqMinMhz = 1000;
			freqMaxMhz = 6000;
			break;
		}
	case eSkyWave:
	case eITU1147:
		{
			freqMinMhz = 0.15;
			freqMaxMhz = 1.7;
			break;
		}
	case eGroundWave:
		{
			freqMinMhz = 0.01;
			freqMaxMhz = 30;
			break;
		}
	case eITU452:
	case eITU452_10:
		{
			freqMinMhz = 700;
			freqMaxMhz = 30000;
			break;
		}
	case eFlatEarth:
	case eEgliModel:
		{
			freqMinMhz = 30;
			freqMaxMhz = 10000;
			break;
		}
	case eITU567:
		{
			freqMinMhz = 30;
			freqMaxMhz = 1000;
			break;
		}
	case eITU526:
		{
			freqMinMhz = 30;
			freqMaxMhz = 1000;
			break;
		}
	case eCEPT:
		{
			freqMinMhz = 30;
			freqMaxMhz = 1000;
			break;
		}
	case eRaytracing:
		{
			freqMinMhz = 30;
			freqMaxMhz = 3000;
			break;
		}
	case eITU452MicWave:
		{
			freqMinMhz = 100;
			freqMaxMhz = 50000;
			break;
		}
	case eITU2001:
		{
			freqMinMhz = 300;
			freqMaxMhz = 50000;
			break;
		}
	default:
		{
			return false;
		}
	}
	return true;
}

bool IsFrequencyInTransmodelRange( ETransModel transId, double freqMhz )
{
	if (transId < eTransNull || freqMhz < 0)
	{
		return false;
	}
	double freqMaxMhz,freqMinMhz;
	if (GetTransmodelFrequencyRange(transId,freqMinMhz,freqMaxMhz))
	{
		if (freqMhz >= freqMinMhz && freqMhz <= freqMaxMhz )
		{
			return true;
		} 
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}

void CalDisMAzi(double x1, double y1, double x2, double y2, bool bGeoSys, double& dDisM, double& dAzi)
{
	dDisM = 0.0;
	dAzi = 0.0;
	if(bGeoSys)
	{
		EarthCoord2D earth2D;
		earth2D.Set_CurrentEllipSoid_Index((int)0);

		DecimalToRad(x1, earth2D.m_LonRad1);
		DecimalToRad(y1, earth2D.m_LatRad1);

		DecimalToRad(x2, earth2D.m_LonRad2);
		DecimalToRad(y2, earth2D.m_LatRad2);

		//计算方向和距离
		earth2D.CalDistance2D();
		dDisM = earth2D.m_DistEllip;
		//获取角度
		RadToDecimal(earth2D.m_AzRad1, dAzi);
	}
	else
	{
		double delta_x = (x2)-(x1);
		double delta_y = (y2)-(y1);
		dDisM = sqrt(delta_x*delta_x + delta_y*delta_y);

		if (delta_y==0) dAzi = ((delta_x>=0) ? 90.0f : 270.0f);
		else dAzi = (float)(180.0 / PI * atan(delta_x / delta_y));

		if (delta_y<0)
		{
			dAzi = 180+dAzi;
		}
		if (dAzi<0) dAzi+=360.0;
	}
	return;

}

/* int GenerateGuid(char *guidStr)
{
	int nRes = 0;

	GUID guid;

	if (CoCreateGuid(&guid))
	{
		nRes = NG_UNKNOWN_ERROR;
		return nRes;
	}

	sprintf(guidStr,
		"%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);

	return nRes;
}*/

