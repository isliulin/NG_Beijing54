#include "DataTypes.h"
#include <math.h>
#include <float.h>
#include "MacroDef.h"
#include "../EarthCoordCompute/EarthCoordManage.h"
#include "GlobalFunction.h"

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

//�жϵ��Ƿ��ڶ������
bool PtInPolygon (CDoublePoint& p, CDoublePoint* ptPolygon, int nCount)
{
	int nCross = 0;	
	for (int i = 0; i < nCount; i++) 
	{
		CDoublePoint& p1 = ptPolygon[i];  
		CDoublePoint& p2 = ptPolygon[(i + 1) % nCount];

		// ��� y=p.y �� p1p2 �Ľ���  

		if ( p1.y == p2.y )      // p1p2 �� y=p0.yƽ��
			continue;

		if ( p.y <  min(p1.y, p2.y) )   // ������p1p2�ӳ�����
			continue;
		if ( p.y >= max(p1.y, p2.y) )   // ������p1p2�ӳ�����
			continue;

		// �󽻵�� X ���� --------------------------------------------------------------
		double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;

		if ( x > p.x ) 
			nCross++;       // ֻͳ�Ƶ��߽���
	}

	// ���߽���Ϊż�������ڶ����֮�� ---
	return (nCross % 2 == 1);
}

//��㵽����λ������ߵ�������� ---KM
//Pt2PolygonDis
//p�����жϵĵ�
//ptPolygon������λ��������ϵĵ�
//nCount: ����λ��������ϵ�ĸ���
//bClosed: �Ƿ�պ�
//����ֵ����λΪkm
double Pt2PolygonDis (CDoublePoint& p, CDoublePoint* ptPolygon, int nCount, bool bClosed)
{
	//�ӵ�0���㿪ʼһ��һ�����
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

	dMinDis = DBL_MAX;//��λM
	if(bClosed)
	{
		nEndIndex = nCount;
	}
	else //������Ƿ�յģ�����Ҫ�������һ����͵�һ����
	{
		nEndIndex = nCount - 1;
	}
	for(int i=1; i<=nEndIndex; i++)
	{
		//��i���i-1����p��ľ���ͽǶȹ�ϵ
		DecimalToRad(ptPolygon[i-1].x, earth2D.m_LonRad1);
		DecimalToRad(ptPolygon[i-1].y, earth2D.m_LatRad1);

		DecimalToRad(ptPolygon[i%nCount].x, earth2D.m_LonRad2);
		DecimalToRad(ptPolygon[i%nCount].y, earth2D.m_LatRad2);

		earth2D.CalDistance2D();

		dAzi1 = earth2D.m_AzRad1;
		dAzi2 = earth2D.m_AzRad2;

		//����i���p�ĽǶȺ;����ϵ
		earth2D.m_LonRad1 = dPxRad;
		earth2D.m_LatRad1 = dPyRad;

		earth2D.CalDistance2D();
		dDisp2 = earth2D.m_DistEllip;
		dAzip2 = earth2D.m_AzRad2;

		//�жϽǶȺ;���֮��Ĺ�ϵ
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

		if(dAngle1 >= HALF_PI) //�۽�
		{
			dTmpMinDis = dDisp1;
		}
		else if(dAngle2 >= HALF_PI) //�ڶ������Ƕ۽�
		{
			dTmpMinDis = dDisp2;
		}
		else
		{
			//�������Ƕȶ�Ϊ���ʱ,��Ҫ��㵽����ľ���
			dTmpMinDis = dDisp1*sin(dAngle1);
		}

		if(dTmpMinDis < dMinDis)
		{
			dMinDis = dTmpMinDis;
		}
		//�滻��һ�εĽǶȺ;���
		dAzip1 = dAzip2;
		dDisp1 = dDisp2;
	}

	return dMinDis*(1e-3);  //ת��Ϊkm
}

// ���㴹ֱ����Ƕ�
AngleInDeg CalVerticalAngle(double inBsHeight, double inRtHeight, double inDistance)
{
	return atan((inBsHeight - inRtHeight) / inDistance) * 180.0 / PI;	
}

//����ˮƽ����Ƕ�
AngleInDeg CalHorizontalAngle(double dXBasePos, double dYBasePos, 
							  double dXCurPos, double dYCurPos,
							  bool bGeoSys)
{	
	AngleInDeg angle = 0;

	if(bGeoSys)
	{
		//���㷢���ͽ��յ�֮��ľ���
		EarthCoord2D earth2D;
		earth2D.Set_CurrentEllipSoid_Index(0);

		DecimalToRad(dXBasePos, earth2D.m_LonRad1);
		DecimalToRad(dYBasePos, earth2D.m_LatRad1);

		DecimalToRad(dXCurPos, earth2D.m_LonRad2);
		DecimalToRad(dYCurPos, earth2D.m_LatRad2);

		//���㷽��;���
		earth2D.CalDistance2D();

		//��ȡ�Ƕ�
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

//��������֮��ľ���
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

		//���㷽��;���
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

//���㾭γ�ȵ�ͼ��һ��դ������
double CalLongLatArea(CDoublePoint& PointLeftLLC, CDoublePoint& PointRightLLC)
{
	EarthCoord2D earth2D;
	earth2D.Set_CurrentEllipSoid_Index(0);

	DecimalToRad(PointLeftLLC.x, earth2D.m_LonRad1);
	DecimalToRad(PointLeftLLC.y, earth2D.m_LatRad1);

	DecimalToRad(PointRightLLC.x, earth2D.m_LonRad2);
	DecimalToRad(PointLeftLLC.y, earth2D.m_LatRad2);

	//���㷽��;���
	earth2D.CalDistance2D();

	double dWidth = earth2D.m_DistEllip;
	DecimalToRad(PointLeftLLC.x, earth2D.m_LonRad1);
	DecimalToRad(PointLeftLLC.y, earth2D.m_LatRad1);

	DecimalToRad(PointLeftLLC.x, earth2D.m_LonRad2);
	DecimalToRad(PointRightLLC.y, earth2D.m_LatRad2);

	//���㷽��;���
	earth2D.CalDistance2D();
	double dHeight = earth2D.m_DistEllip;
	double dArea = dWidth*dHeight;
	return dArea;
}