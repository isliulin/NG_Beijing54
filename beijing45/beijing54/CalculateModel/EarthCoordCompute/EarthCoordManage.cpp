#include "EarthCoordCompute.h"
#include "EarthCoordManage.h"

#pragma warning(disable:4996)

EarthCoord2D::EarthCoord2D()
{
	m_EllipIndex = 0;
	Set_CurrentEllipSoid_Index(0);

	m_LatRad1 = 0;			//起始点A经纬度坐标，单位:弧度
	m_LonRad1 = 0;
	m_AzRad1 = 0;			//方位角(从A到B 矢量连线ab)

	m_LatRad2 = 0;			//起始点B经纬度坐标，单位:弧度
	m_LonRad2 = 0;
	m_AzRad2 = 0;			//方位角(从B到A 矢量连线ba)

	m_DistEllip = 0;	//EllipSoid 距离
}

EarthCoord2D::~EarthCoord2D()
{

}


long EarthCoord2D::Get_CurrentEllipSoid_Index()
{
	return m_EllipIndex;
}

bool EarthCoord2D::Set_CurrentEllipSoid_Index(long EllipIndex)
{
	if (EllipIndex == -1)
		return false;

	if (Get_EllipSoid_AF(EllipIndex,m_dA,m_dF))
	{
		m_EllipIndex = EllipIndex;
		m_ESQ = m_dF*(2-m_dF);
		return true;
	}
	else
		return false;
}

void EarthCoord2D::Get_CurrentEllipSoid_AF(double &dA,double &dF)
{
	dA = m_dA;
	dF = m_dF;
}
bool EarthCoord2D::Set_CurrentEllipSoid_AF(double dA,double dF)
{
	double ss = 1.0/dF;
	if(200.0 <= ss && ss <= 310.0)
	{
		m_dA = dA;
		m_dF = dF;
		m_ESQ = m_dF*(2-m_dF);
		m_EllipIndex = -1;

		return true;
	}
	else
		return false;
}

void EarthCoord2D::CalDistance2D()
{
	Distance2D(m_LatRad1,m_LonRad1,m_LatRad2,m_LonRad2,m_AzRad1,m_AzRad2,m_DistEllip,m_dA,m_dF);
}

void EarthCoord2D::CalDirect2D()
{
	Direct2D(m_LatRad1,m_LonRad1,m_LatRad2,m_LonRad2,m_AzRad1,m_AzRad2,m_DistEllip,m_dA,m_dF);
}


//////////////////////////////////////////////////////////////////////////
EarthCoord3D::EarthCoord3D()
{
	m_h1 = 0;			//A点高度值，单位:m
	m_h2 = 0;			//B点高度值，单位:m
	m_Distmm = 0;		//Mark 距离

	m_x1 = 0;			//A点XYZ坐标
	m_y1 = 0;
	m_z1 = 0;

	m_x2 = 0;			//B点XYZ坐标
	m_y2 = 0;
	m_z2 = 0;

	m_dx = 0;			//XYZ坐标差值
	m_dy = 0;
	m_dz = 0;

	m_dn = 0;			//neu坐标
	m_de = 0;
	m_du = 0;

	m_bZem = 0;			//Zem信息
	m_ZdRad = 0;
	m_ZnRad = 0;
}

EarthCoord3D::~EarthCoord3D()
{

}

void EarthCoord3D::CalDistance3D()
{
	Distance3D(m_LatRad1,m_LonRad1,m_h1,m_LatRad2,m_LonRad2,m_h2,m_AzRad1,m_AzRad2,m_DistEllip,m_Distmm,m_dA,m_dF);
}
void EarthCoord3D::CalDirect3D()
{
	Direct3D(m_LatRad1,m_LonRad1,m_h1,m_LatRad2,m_LonRad2,m_h2,m_AzRad1,m_AzRad2,m_DistEllip,m_Distmm,m_dA,m_dF);
}

void EarthCoord3D::CalDistance3DExt()
{
	Distance3DExt(m_LatRad1,m_LonRad1,m_h1,m_LatRad2,m_LonRad2,m_h2,m_AzRad1,m_AzRad2,m_DistEllip,m_Distmm,
		m_dx,m_dy,m_dz,m_dn,m_de,m_du,m_bZem,m_ZdRad,m_ZnRad,m_dA,m_dF);

	GeodeticToxyz(m_LatRad1,m_LonRad1,m_h1,m_x1,m_y1,m_z1,m_dA,m_dF);
	GeodeticToxyz(m_LatRad2,m_LonRad2,m_h2,m_x2,m_y2,m_z2,m_dA,m_dF);
}
void EarthCoord3D::CalDirect3DExt()
{
	Direct3DExt(m_LatRad1,m_LonRad1,m_h1,m_LatRad2,m_LonRad2,m_h2,m_AzRad1,m_AzRad2,m_DistEllip,m_Distmm,
		m_dx,m_dy,m_dz,m_dn,m_de,m_du,m_bZem,m_ZdRad,m_ZnRad,m_dA,m_dF);

	GeodeticToxyz(m_LatRad1,m_LonRad1,m_h1,m_x1,m_y1,m_z1,m_dA,m_dF);
	GeodeticToxyz(m_LatRad2,m_LonRad2,m_h2,m_x2,m_y2,m_z2,m_dA,m_dF);
}


