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
	void CalDistance2D();	//2D�������					
	void CalDirect2D();		//2D�����

	//��ǰʹ�õĳ�����ֵ�ͱ�ƽ��
	long Get_CurrentEllipSoid_Index();
	bool Set_CurrentEllipSoid_Index(long EllipIndex);
	void Get_CurrentEllipSoid_AF(double &dA,double &dF);
	bool Set_CurrentEllipSoid_AF(double dA,double dF);

public:
	double	m_LatRad1;			//��ʼ��A��γ�����꣬��λ:����
	double	m_LonRad1;
	double	m_AzRad1;			//��λ��(��A��B ʸ������ab)

	double	m_LatRad2;			//��ʼ��B��γ�����꣬��λ:����
	double	m_LonRad2;
	double	m_AzRad2;			//��λ��(��B��A ʸ������ba)

	double	m_DistEllip;		//EllipSoid ����

protected:
	double	m_dA;				//���򳤰��ᣬ��λ:m
	double	m_dF;				//�����ƽ�ʣ���λ:m
	double	m_ESQ;
	int		m_EllipIndex;
};

class COORD_API EarthCoord3D :public EarthCoord2D
{
public:
	EarthCoord3D();
	~EarthCoord3D();

public:
	void CalDistance3D();		//3D�������					
	void CalDirect3D();			//3D�����

	void CalDistance3DExt();	//3D�������,���������Ϣ					
	void CalDirect3DExt();		//3D�����

public:
	double	m_h1;				//A��߶�ֵ����λ:m
	double	m_h2;				//B��߶�ֵ����λ:m
	double	m_Distmm;			//Mark ����

	double	m_x1;				//A��XYZ����
	double	m_y1;
	double	m_z1;

	double	m_x2;				//B��XYZ����
	double	m_y2;
	double	m_z2;

	double	m_dx;				//XYZ�����ֵ
	double	m_dy;
	double	m_dz;

	double	m_dn;				//neu����
	double	m_de;
	double	m_du;

	bool	m_bZem;				//Zem��Ϣ
	double	m_ZdRad;
	double	m_ZnRad;
};

#endif