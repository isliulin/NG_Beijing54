#pragma once

#include "DataTypes.h"

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

// 计算垂直方向角度
AngleInDeg CalVerticalAngle(double inBsHeight, double inRtHeight, double inDistance);

//计算水平方向角度
AngleInDeg CalHorizontalAngle(double dXBasePos, double dYBasePos, 
							  double dXCurPos, double dYCurPos,
							  bool bGeoSys);

//计算给定两点之间的距离，单位M
double CalDistanseM(double x1, double y1, double x2, double y2, bool bGeoSys);

//计算经纬度地图的一个栅格的面积
double CalLongLatArea(CDoublePoint& PointLeftLLC, CDoublePoint& PointRightLLC);

//获取算术平均值(避免累加后溢出)
template <typename T>
bool GetArithmeticMean(T* pData, int nNumData, T& meanValue)
{
	meanValue = 0;
	if (pData == NULL || nNumData <= 0)
	{
		meanValue = UNCALCULATE;
		return false;
	}

	for ( int i = 0; i < nNumData; i++ )
	{
		meanValue = meanValue + (pData[i] - meanValue) / (i + 1);
	}

	return true;
}