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

void CalVerticalAndHorizontalAngle(double dXBasePos, double dYBasePos, double dXCurPos, double dYCurPos, bool bGeoSys,
								                                   double inBsHeight, double inRtHeight, AngleInDeg dTilt,AngleInDeg dAzi,
								                                   double& px,double& py,double& pz)
{
	//��BS��Ϊ����ԭ�㣬����3ά����ϵ��X�Ĵ�С������������ΪX���ᣬ����Ϊy���ᣩ
	if (bGeoSys)
	{
		//����Ǿ�γ������ϵ
		//���㷢���ͽ��յ�֮��ľ���
		EarthCoord2D earth2D;
		earth2D.Set_CurrentEllipSoid_Index(0);

		DecimalToRad(dXBasePos, earth2D.m_LonRad1);
		DecimalToRad(dYBasePos, earth2D.m_LatRad1);

		DecimalToRad(dXCurPos, earth2D.m_LonRad2);
		DecimalToRad(dYCurPos, earth2D.m_LatRad2);

		//���㷽��;���
		earth2D.CalDistance2D();
		px = earth2D.m_DistEllip * sin(earth2D.m_AzRad1);
		py = earth2D.m_DistEllip * cos(earth2D.m_AzRad1);
	}else
	{
		py = dYCurPos - dYBasePos;
		px = dXCurPos -  dXBasePos;
	}

	pz = inRtHeight - inBsHeight;
	//�˴���������ϵ����ת���൱�ڵ�����ת
	//��λ������Z��˳ʱ����ת
	dAzi =   dAzi / 180 * PI;
	double sinangle = sin(dAzi) , cosangle = cos(dAzi);
	double temp  = px * cosangle - py * sinangle;
	py = px * sinangle + py * cosangle;
	px= temp;

	//����������X��˳ʱ����ת
	dTilt =  dTilt /180 * PI;
	sinangle = sin(dTilt) , cosangle = cos(dTilt);
	temp = py * cosangle - pz * sinangle;
	pz = py * sinangle  + pz * cosangle;
	py = temp;

	
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

//�����������֮���3D���룬��λM
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

		//���㷽��;���
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

//�жϵ��Ƿ����������ڲ�
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
//������������ȡ���ο����½����꣬���ο��ȸ߶�
//����������
//���������(in&out)rect������ȡ��Ϣ�ľ��ο�
//          dxMapLowLeft: ��ͼ���½�����x
//          dyMapLowLeft: ��ͼ���½�����y
//          nObjCoordSys: Ŀ������ϵ�����ͼ����ϵ��ͬ
//  (in&out)dxObjRes: Ŀ��ֱ���x������ʱ��λΪ�ף����ʱ��Ϊ��nObjCoordSys����ϵ��ͬ
//  (in&out)dyObjRes: Ŀ��ֱ���y������ʱ��λΪ�ף����ʱ��Ϊ��nObjCoordSys����ϵ��ͬ
//���������dxRectLowLeft: ���ο����½�����X
//          dyRectLowLeft: ���ο����½�����Y
//          nHeight: ���ο���Ŀ��ֱ����µĸ߶�
//          nWidth: ���ο���Ŀ��ֱ����µĿ��
//////////////////////////////////////////////////////////////////////////
int GetGeoRectInfo(CGeoRectangle& rect, double dxMapLowLeft, double dyMapLowLeft,  
				   int nObjCoordSys, double& dxObjRes, double& dyObjRes, 
				   double& dxRectLowLeft, double& dyRectLowLeft, int& nWidth, int& nHeight)
{
	const double C_Degree2M = C_DEGREE2M; //ĿǰĬ�ϰ���1�ȶ�Ӧ110km
	int nRet = NG_SUCCESS;	

	//�жϾ��ο������ϵ��Ŀ������ϵ�Ƿ���ͬ
	if(rect.m_nCoordSys != nObjCoordSys)
	{
		ng_geo_init();

		//�����ο������ת��ΪĿ������ϵ������
		ng_geo_trans(rect.m_nCoordSys, nObjCoordSys, rect.m_Corner1.x, rect.m_Corner1.y, 
			&(rect.m_Corner1.x), &(rect.m_Corner1.y));
		ng_geo_trans(rect.m_nCoordSys, nObjCoordSys, rect.m_Corner2.x, rect.m_Corner2.y, 
			&(rect.m_Corner2.x), &(rect.m_Corner2.y));

		rect.m_nCoordSys = nObjCoordSys;
	}

	//�жϷֱ��ʵ����,�ֱ�������ʱ��λΪ��,����Ǿ�γ�ȵ�ͼ����Ҫ���ֱ���ת��Ϊ��
	if(ng_IsGeoSystem(nObjCoordSys))
	{
		dxObjRes = dxObjRes / C_Degree2M;
		dyObjRes = dyObjRes / C_Degree2M;		
	}

	//�����������½�����
	dxRectLowLeft = floor((rect.m_Corner1.x - dxMapLowLeft)/dxObjRes)*dxObjRes + dxMapLowLeft;
	dyRectLowLeft = floor((rect.m_Corner1.y - dyMapLowLeft)/dyObjRes)*dyObjRes + dyMapLowLeft;

	//������ο�ĳ���
	nWidth = int((rect.m_Corner2.x - dxRectLowLeft)/dxObjRes) + 1;
	nHeight = int((rect.m_Corner2.y - dyRectLowLeft)/dyObjRes) + 1;

	return nRet;
}

//////////////////////////////////////////////////////////////////////////
//������������ȡԲ���о���
//����������
//�������: circle������ȡ���о��ε�Բ
//          nCoordSys��Բ�뾶������ϵ
//���������rect: ���о���
//          nDstCoordSys: Ŀ������ϵ 
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

	//Բ�������Ǿ�γ��
	if(ng_IsGeoSystem(circle.m_nCoordSys))
	{
		if(!ng_IsGeoSystem(nDstCoordSys))
		{
			//ת��ΪĿ������ϵ������
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
		else //Ŀ���Ƕ�
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
//����������ȡ����ε���Ӿ���
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
		return NG_SUCCESS;//��������� 
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

		//���㷽��;���
		earth2D.CalDistance2D();
		dDisM = earth2D.m_DistEllip;
		//��ȡ�Ƕ�
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

