#pragma once

#include "DataTypes.h"

//�жϵ��Ƿ��ڶ������
bool PtInPolygon (CDoublePoint& p, CDoublePoint* ptPolygon, int nCount);

//��㵽����λ������ߵ�������� ---KM
//Pt2PolygonDis
//p�����жϵĵ�
//ptPolygon������λ��������ϵĵ�
//nCount: ����λ��������ϵ�ĸ���
//bClosed: �Ƿ�պ�
//����ֵ����λΪkm
double Pt2PolygonDis (CDoublePoint& p, CDoublePoint* ptPolygon, int nCount, bool bClosed);

// ���㴹ֱ����Ƕ�
AngleInDeg CalVerticalAngle(double inBsHeight, double inRtHeight, double inDistance);

//����ˮƽ����Ƕ�
AngleInDeg CalHorizontalAngle(double dXBasePos, double dYBasePos, 
							  double dXCurPos, double dYCurPos,
							  bool bGeoSys);

//�����������֮��ľ��룬��λM
double CalDistanseM(double x1, double y1, double x2, double y2, bool bGeoSys);

//���㾭γ�ȵ�ͼ��һ��դ������
double CalLongLatArea(CDoublePoint& PointLeftLLC, CDoublePoint& PointRightLLC);

//��ȡ����ƽ��ֵ(�����ۼӺ����)
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