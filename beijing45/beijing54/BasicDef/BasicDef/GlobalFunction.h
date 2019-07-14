#pragma once

#include "DataTypes.h"
#include "GeoShape.h"
#include "../DataModel/EnumDef.h"
#include "../CalGisMapWrapper/ICalGisMapManager.h"

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


//�����������꣬��BS��Ϊ������ԭ�㣬����MS�����߸����еĽǶȣ���δ���Ƿ�λ�ǵ����أ����ߴ�ֱ�����ˮƽ���棬˳ʱ��Ƕȣ�
void CalVerticalAndHorizontalAngle(double dXBasePos, double dYBasePos, 
								   double dXCurPos, double dYCurPos,
								   bool bGeoSys,
								   double inBsHeight, double inRtHeight,
								   AngleInDeg dTilt,AngleInDeg dAzi,
								   double& px,double& py,double& pz);
// ���㴹ֱ����Ƕ�
AngleInDeg CalVerticalAngle(double inBsHeight, double inRtHeight, double inDistance);

//����ˮƽ����Ƕ�
AngleInDeg CalHorizontalAngle(double dXBasePos, double dYBasePos, 
							  double dXCurPos, double dYCurPos,
							  bool bGeoSys);

void CalDisMAzi(double x1, double y1, double x2, double y2, bool bGeoSys, double& dDisM, double& dAzi);

//�����������֮��ľ��룬��λM
double CalDistanseM(double x1, double y1, double x2, double y2, bool bGeoSys);

//�����������֮���3D���룬��λM
double Cal3DDistanseM(double x1, double y1, double z1, double x2, double y2, double z2, bool bGeoSys);

//���㾭γ�ȵ�ͼ��һ��դ������
double CalLongLatArea(CDoublePoint& PointLeftLLC, CDoublePoint& PointRightLLC);

//�жϵ��Ƿ����������ڲ�
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

