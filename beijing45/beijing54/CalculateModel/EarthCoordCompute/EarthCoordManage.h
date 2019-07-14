#ifndef __INCLUDED_EARTHCOORD__MANAGE__H__
#define __INCLUDED_EARTHCOORD__MANAGE__H__

#pragma once

#include "EarthCoordCompute.h"

class COORD_API EarthCoord2D
{
public:
	EarthCoord2D();
	~EarthCoord2D();

public:
	void CalDistance2D();	//2D距离计算					
	void CalDirect2D();		//2D点计算

	//当前使用的长半轴值和扁平率
	long Get_CurrentEllipSoid_Index();
	bool Set_CurrentEllipSoid_Index(long EllipIndex);
	void Get_CurrentEllipSoid_AF(double &dA,double &dF);
	bool Set_CurrentEllipSoid_AF(double dA,double dF);

public:
	double	m_LatRad1;			//起始点A经纬度坐标，单位:弧度
	double	m_LonRad1;
	double	m_AzRad1;			//方位角(从A到B 矢量连线ab)

	double	m_LatRad2;			//起始点B经纬度坐标，单位:弧度
	double	m_LonRad2;
	double	m_AzRad2;			//方位角(从B到A 矢量连线ba)

	double	m_DistEllip;		//EllipSoid 距离

protected:
	double	m_dA;				//地球长半轴，单位:m
	double	m_dF;				//地球扁平率，单位:m
	double	m_ESQ;
	int		m_EllipIndex;
};

class COORD_API EarthCoord3D :public EarthCoord2D
{
public:
	EarthCoord3D();
	~EarthCoord3D();

public:
	void CalDistance3D();		//3D距离计算					
	void CalDirect3D();			//3D点计算

	void CalDistance3DExt();	//3D距离计算,计算更多信息					
	void CalDirect3DExt();		//3D点计算

public:
	double	m_h1;				//A点高度值，单位:m
	double	m_h2;				//B点高度值，单位:m
	double	m_Distmm;			//Mark 距离

	double	m_x1;				//A点XYZ坐标
	double	m_y1;
	double	m_z1;

	double	m_x2;				//B点XYZ坐标
	double	m_y2;
	double	m_z2;

	double	m_dx;				//XYZ坐标差值
	double	m_dy;
	double	m_dz;

	double	m_dn;				//neu坐标
	double	m_de;
	double	m_du;

	bool	m_bZem;				//Zem信息
	double	m_ZdRad;
	double	m_ZnRad;
};

#endif