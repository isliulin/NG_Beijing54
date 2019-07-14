#pragma once

#include "DataTypes.h"
#include "GeoShape.h"
#include "../DataModel/EnumDef.h"
#include "../CalGisMapWrapper/ICalGisMapManager.h"

//判断点是否在多边形内
bool PtInPolygon (CDoublePoint& p, CDoublePoint* ptPolygon, int nCount);

//求点到多边形或者折线的最近距离 ---KM
//Pt2PolygonDis
//p：待判断的点
//ptPolygon：多边形或者折线上的点
//nCount: 多边形或者折线上点的个数
//bClosed: 是否闭合
//返回值：单位为km
double Pt2PolygonDis (CDoublePoint& p, CDoublePoint* ptPolygon, int nCount, bool bClosed);


//根据两点坐标，将BS作为球坐标原点，计算MS在天线覆型中的角度（尚未考虑方位角等因素，天线垂直剖面和水平剖面，顺时针角度）
void CalVerticalAndHorizontalAngle(double dXBasePos, double dYBasePos, 
								   double dXCurPos, double dYCurPos,
								   bool bGeoSys,
								   double inBsHeight, double inRtHeight,
								   AngleInDeg dTilt,AngleInDeg dAzi,
								   double& px,double& py,double& pz);
// 计算垂直方向角度
AngleInDeg CalVerticalAngle(double inBsHeight, double inRtHeight, double inDistance);

//计算水平方向角度
AngleInDeg CalHorizontalAngle(double dXBasePos, double dYBasePos, 
							  double dXCurPos, double dYCurPos,
							  bool bGeoSys);

void CalDisMAzi(double x1, double y1, double x2, double y2, bool bGeoSys, double& dDisM, double& dAzi);

//计算给定两点之间的距离，单位M
double CalDistanseM(double x1, double y1, double x2, double y2, bool bGeoSys);

//计算给定两点之间的3D距离，单位M
double Cal3DDistanseM(double x1, double y1, double z1, double x2, double y2, double z2, bool bGeoSys);

//计算经纬度地图的一个栅格的面积
double CalLongLatArea(CDoublePoint& PointLeftLLC, CDoublePoint& PointRightLLC);

//判断点是否在三角形内部
bool PtIn2DTriangle (double xA, double yA, double xB, double yB, double xC, double yC, double xP, double yP);

int GetGeoRectInfo(CGeoRectangle& rect, double dxMapLowLeft, double dyMapLowLeft,  
				   int nObjCoordSys, double& dxObjRes, double& dyObjRes, 
				   double& dxRectLowLeft, double& dyRectLowLeft, int& nWidth, int& nHeight);

int GetGeoRectofPolygon(CGeoPolygon& polygon, CGeoRectangle& rect);

int GetGeoRectofCircle(CGeoCircle& circle, CGeoRectangle& rect, int nDstCoordSys);

int GetRasterResultParam(CGeoShape* pShap, CalResult_AreaType type,ICalGis_MapManger* pGisAdapter,double& ResX,double& ResY
						 ,int nObjCoordSys ,double& dxRectLowLeft, double& dyRectLowLeft, int& nWidth, int& nHeight);

bool GetTransmodelFrequencyRange(ETransModel transId, double &freqMinMhz, double &freqMaxMhz);

bool IsFrequencyInTransmodelRange(ETransModel transId, double freqMhz);

	
// int GenerateGuid(char *guidStr);

