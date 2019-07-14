#include <stdio.h>
#include <string.h>
#include <math.h>

#include "NGCalGisMapManager.h"
#include "../KoordTrans/KoordTrans/KoordTrans.h"
#include "../EarthCoordCompute/EarthCoordManage.h"

#pragma warning(disable:4996)

#define INVALID_MAP_DATA -990

/*****************************************************************************/
//��������: CalLinePara
//��������: ����ֱ��ax+by+c=0�ĸ���ϵ��ֵ
//�������:
//         nBSPosX:
//         nBSPosY:
//         nCurPosX:
//         nCurPosY: ֱ�������������
//�������:
//         dXPara:
//         dYPara:
//         dConPara: ֱ��ϵ��,��a��b��c
//����ֵ:  void
/****************************************************************************/
void CalLinePara(int    nBSPosX,
				 int    nBSPosY,
				 int    nCurPosX,
				 int    nCurPosY,
				 double  &dXPara,
				 double  &dYPara,
				 double  &dConPara)
{
	int nXDelta;
	int nYDelta;

	nXDelta = labs( nCurPosX - nBSPosX );
	nYDelta = labs( nCurPosY - nBSPosY );

	//��������غ�
	if((nXDelta==nYDelta) && (nXDelta == 0))
	{		
		return;
	}

	if( nXDelta > nYDelta )
	{
		dYPara = 1;
		dXPara = -1 * ((double)( nCurPosY - nBSPosY )) / ( nCurPosX - nBSPosX );
		dConPara = ( (double)(nBSPosX*nCurPosY - nCurPosX*nBSPosY) ) / ( nCurPosX - nBSPosX );
	}
	else
	{
		dXPara = 1;
		dYPara = -1 * ((double)( nCurPosX - nBSPosX )) / ( nCurPosY - nBSPosY );
		dConPara = ( (double)(nBSPosY*nCurPosX - nCurPosY*nBSPosX) ) / ( nCurPosY - nBSPosY );
	}
	return;
}

//�ж�������ͼ������Ϣ�Ƿ���ͬ
//������Ϣ��:����ϵ���,��ͼ���½�����,��ͼ�ֱ���
bool IsMapBaseDataEqual(IPyramidMapGeo *pMap1,IPyramidMapGeo *pMap2)
{
	long sysNum1 = ng_GetCoordNoFromName(pMap1->GetCoordShortName());
	long sysNum2 = ng_GetCoordNoFromName(pMap2->GetCoordShortName());
	if (sysNum1 != sysNum2)		//����ϵ��Ų���ͬ,����false
		return false;

	//�鿴���½ǵ������Ƿ���ͬ
	double x1 = pMap1->GetMapLowerLeftXCoord();
	double x2 = pMap2->GetMapLowerLeftXCoord();
	if (fabs(x1-x2) > 1E-8)
		return false;

	double y1 = pMap1->GetMapLowerLeftYCoord();
	double y2 = pMap2->GetMapLowerLeftYCoord();
	if (fabs(y1-y2) > 1E-8)
		return false;

	//�鿴��ͼ�ֱ����Ƿ���ͬ
	double rx1 = pMap1->GetActiveLayerPtr()->GetResolutionX();
	double rx2 = pMap2->GetActiveLayerPtr()->GetResolutionX();
	if (fabs(rx1-rx2) > 1E-8)
		return false;

	double ry1 = pMap1->GetActiveLayerPtr()->GetResolutionY();
	double ry2 = pMap2->GetActiveLayerPtr()->GetResolutionY();
	if (fabs(ry1-ry2) > 1E-8)
		return false;

	return true;
}

CNGCalGisMapManger::CNGCalGisMapManger()
{
	for (int i = 0; i <CALMAP_ALL;i ++)
	{
		m_pCalMap[i] = NULL;
		memset(m_szCalMapFilePath[i],0,MAX_FILE_PATH);
	}
	m_pTopoMap = NULL;
	
	eProfileType = ICalGis_MapManger::PROFILER_NG;

	m_bTopoNeeded = true;
	m_bMorphoNeeded = false;
	m_bConductNeeded = false;

	m_nCoordSys = -1;
	m_XLowLeft = 0.0;
	m_YLowLeft = 0.0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_Xspacing = 0.0;
	m_Yspacing = 0.0;

	ng_geo_init();
}

CNGCalGisMapManger::~CNGCalGisMapManger()
{	
	DeleteAllCalMap();
}

void CNGCalGisMapManger::EnableMap_Topo(bool bEnale)
{
	if (bEnale != m_bTopoNeeded)
	{
		m_bTopoNeeded = bEnale;
		UpdateMap();
	}
}

void CNGCalGisMapManger::EnableMap_Conduct(bool bEnale)
{
	if (bEnale != m_bConductNeeded)
	{
		m_bConductNeeded = bEnale;
		UpdateMap();
	}
}

void CNGCalGisMapManger::EnableMap_Clutter(bool bEnale)
{
	if (bEnale != m_bMorphoNeeded)
	{
		m_bMorphoNeeded = bEnale;
		UpdateMap();
	}
}

bool CNGCalGisMapManger::SetCalMapFilePath(CalMapType mapType,const char *pFilePath)
{
	if((mapType == ICalGis_MapManger::CALMAP_INDOOR) || 
	   (mapType == ICalGis_MapManger::CALMAP_VECTOR))
	{
		strcpy(m_szCalMapFilePath[mapType],pFilePath);
		return true;
	}
	
	NG_Release_Pyramid_MapGeo(m_pCalMap[mapType]);	//�ͷ�ԭʼ��ͼ
	m_szCalMapFilePath[mapType][0]='\0';
	//////////////////////////////////////////////////////////////////////////
	
	IPyramidMapGeo *pMap = NG_Create_Pyramid_MapGeo();
	if (!pMap->ReadPyramidMap(pFilePath))
	{
		NG_Release_Pyramid_MapGeo(pMap);
		pMap = NULL;
		return false;
	}

	if (CALMAP_CON == mapType)
	{
		m_bConductNeeded = true;
	}

	if(CALMAP_DOM == mapType)
	{
		m_bMorphoNeeded = true;
	}

	m_pCalMap[mapType] = pMap;
	if(pFilePath)
	strcpy(m_szCalMapFilePath[mapType],pFilePath);
	UpdateMap();

	return true;
}

void CNGCalGisMapManger::DeleteCalMap(CalMapType mapType)
{
	if(m_pCalMap[mapType] != NULL)
	{
		if (m_pTopoMap == m_pCalMap[mapType])
			m_pTopoMap = NULL;

		NG_Release_Pyramid_MapGeo(m_pCalMap[mapType]);
		m_pCalMap[mapType] = NULL;	

		UpdateMap();
	}
}

void CNGCalGisMapManger::DeleteAllCalMap()
{
	//ɾ����ͼ
	for (int i = 0; i <CALMAP_ALL;i ++)
	{
		DeleteCalMap((CalMapType)i);
	}
}

void CNGCalGisMapManger::ReleaseCalMapData(CalMapType mapType)
{
	if(m_pCalMap[mapType] != NULL)
	{
		m_pCalMap[mapType]->GetActiveLayerPtr()->ReleaseMapData();
	}
}

//�ͷż��ص��ڴ��еĵ�ͼ����,���ǵ�ͼ��Ϣ����
void CNGCalGisMapManger::ReleaseAllCalMapData()
{
	for (int i = 0; i <CALMAP_ALL;i ++)
	{
		ReleaseCalMapData((CalMapType)i);
	}
}

void CNGCalGisMapManger::UpdateMap()
{	
	if(m_pCalMap[CALMAP_DSM] != NULL)						//����ѡ��DSM
		m_pTopoMap = m_pCalMap[CALMAP_DSM];					//û��DSM,��ʹ��DEM
	else if(m_pCalMap[CALMAP_DEM] != NULL)
		m_pTopoMap = m_pCalMap[CALMAP_DEM];

	IPyramidMapGeo *pDestMap = NULL;
	if(m_bTopoNeeded && m_pTopoMap != NULL)		//�����Ҫ�߳�ͼ�������,����ѡ��߳�ͼ
		pDestMap = m_pTopoMap;
	else if(m_bConductNeeded && m_pCalMap[CALMAP_CON] != NULL)
		pDestMap = m_pCalMap[CALMAP_CON];

	if(pDestMap != NULL)
	{
		m_nHeight = pDestMap->GetActiveLayerPtr()->GetMapHeight();
		m_nWidth = pDestMap->GetActiveLayerPtr()->GetMapWidth();

		m_XLowLeft = pDestMap->GetMapLowerLeftXCoord();
		m_YLowLeft = pDestMap->GetMapLowerLeftYCoord();

		m_Xspacing = pDestMap->GetActiveLayerPtr()->GetResolutionX();
		m_Yspacing = pDestMap->GetActiveLayerPtr()->GetResolutionY();

		m_nCoordSys = ng_GetCoordNoFromName(pDestMap->GetCoordShortName());

		if(ng_IsGeoSystem(m_nCoordSys))
		{
			eProfileType = ICalGis_MapManger::PROFILER_GEO;
		}
	}
}

CalGis_Profile* CNGCalGisMapManger::GetProfileNG(double xBegin, double yBegin, double xEnd, double yEnd,
												 double xRes, double yRes, CalGis_Profile *pProfile)
{
	CalGis_Profile* pProfileLocal = NULL;

	//��ȡprofile��ÿ�������Ϣֵ	
	if( (m_bTopoNeeded && (m_pTopoMap == NULL)) &&
		(m_bConductNeeded && (m_pCalMap[CALMAP_CON] == NULL)) )
	{
		pProfile->noPoints = 0;
		return pProfile;			
	}

	//���Ȼ�ȡ��ʼ�����ֹ����������ʼ���ڸ����ֱ����µ�����
	int nxBegin = 0, nyBegin = 0;
	int nxEnd = 0, nyEnd = 0;

	nxBegin = (xBegin - m_XLowLeft)/xRes;
	nyBegin = (yBegin - m_YLowLeft)/yRes;
	nxEnd = (xEnd - m_XLowLeft)/xRes;
	nyEnd = (yEnd - m_YLowLeft)/yRes;

	//��ȡprofile
	pProfileLocal = GetProfileLocal(nxBegin, nyBegin, nxEnd, nyEnd, xRes, yRes, pProfile);
	if((pProfileLocal == NULL) || (pProfileLocal->noPoints<=0))
	{
		return NULL;
	}

	//Ȼ�����profile��ÿ����ľ�������
	for(int i=0; i<=pProfileLocal->noPoints; i++)
	{
		pProfileLocal->xPathCoord[i] = m_XLowLeft + pProfileLocal->xIndex[i]*xRes + xRes/2;
		pProfileLocal->yPathCoord[i] = m_YLowLeft + pProfileLocal->yIndex[i]*yRes + yRes/2;
	}

	for(int i=0; i<=pProfile->noPoints; i++)
	{
		//��ȡ�õ�ĸ߶�ֵ
		if(m_bTopoNeeded && (m_pCalMap[CALMAP_DEM] != NULL))
		{
			pProfile->height[i] = (double)(m_pCalMap[CALMAP_DEM]->GetActiveLayerPtr()->ShortElement(pProfileLocal->xPathCoord[i], pProfileLocal->yPathCoord[i], m_nCoordSys));
			if(pProfile->height[i] < INVALID_MAP_DATA)
			{
				pProfile->height[i] = 0.0;
			}
			if(m_pCalMap[CALMAP_DHM] != NULL)
			{
				pProfile->building[i] = (double)(m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->ShortElement(pProfileLocal->xPathCoord[i], pProfileLocal->yPathCoord[i], m_nCoordSys));
				if(pProfile->building[i] < INVALID_MAP_DATA)
				{
					pProfile->building[i] = 0.0;
				}
			}
			else if(m_pCalMap[CALMAP_DSM] != NULL)
			{
				double dTemp = m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->ShortElement(pProfileLocal->xPathCoord[i], pProfileLocal->yPathCoord[i], m_nCoordSys);
				if(dTemp < INVALID_MAP_DATA)
				{
					dTemp = 0.0;
				}
				pProfile->building[i] = (dTemp)-pProfile->height[i];
			}

			if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
			{
				double dTemp = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(pProfileLocal->xPathCoord[i], pProfileLocal->yPathCoord[i], m_nCoordSys);
				if(dTemp < INVALID_MAP_DATA)
				{
					dTemp = 0.0;
				}
				pProfile->conductivity[i] = dTemp;
			}
		}
		else if(m_bTopoNeeded && (m_pCalMap[CALMAP_DSM] != NULL))
		{
			double dValue = (double)(m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->ShortElement(pProfileLocal->xPathCoord[i], pProfileLocal->yPathCoord[i], m_nCoordSys));
			if(dValue < INVALID_MAP_DATA)
			{
				dValue = 0;
			}
			if(m_pCalMap[CALMAP_DHM] != NULL)
			{
				pProfile->building[i]  = (double)(m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->ShortElement(pProfileLocal->xPathCoord[i], pProfileLocal->yPathCoord[i], m_nCoordSys));
				if(pProfile->building[i] < INVALID_MAP_DATA)
				{
					pProfile->building[i] = 0;
				}						

				pProfile->height[i] = dValue - pProfile->building[i];
			}
			else
			{
				pProfile->height[i] = dValue;
			}

			if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
			{
				double dTemp = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(pProfileLocal->xPathCoord[i], pProfileLocal->yPathCoord[i], m_nCoordSys);
				if(dTemp < INVALID_MAP_DATA)
				{
					dTemp = 0.0;
				}
				pProfile->conductivity[i] = dTemp;						
			}
		}				
		else if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
		{
			double dValue = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(pProfileLocal->xPathCoord[i], pProfileLocal->yPathCoord[i], m_nCoordSys);
			if(dValue < INVALID_MAP_DATA)
			{
				dValue = 0.0;
			}
			pProfile->conductivity[i] = dValue;
		}
		else
		{
			return NULL;
		}

		if(m_bMorphoNeeded)
		{
			pProfile->clutter[i] = m_pCalMap[CALMAP_DOM]->GetActiveLayerPtr()->ShortElement(pProfileLocal->xPathCoord[i], pProfileLocal->yPathCoord[i], m_nCoordSys);
			if(pProfile->clutter[i] < INVALID_MAP_DATA)
			{
				pProfile->clutter[i] = 0;
			}
		}
	}//end of for	

	return pProfile;
}

CalGis_Profile* CNGCalGisMapManger::GetProfileGeo(double xBegin, double yBegin, double xEnd, double yEnd,
												  double xRes, double yRes, CalGis_Profile *pProfile)
{
	CalGis_Profile* pProfileLocal = NULL;

	//--�����жϵ�ͼ�Ƿ�����Ҫ��
	if( (m_bTopoNeeded && (m_pTopoMap == NULL)) &&
		(m_bConductNeeded && (m_pCalMap[CALMAP_CON] == NULL)) )
	{
		pProfile->noPoints = 0;
		return pProfile;			
	}

	//���Ȼ�ȡ�����ͽ��յ�֮��profile�ϵĵ�ľ�γ������;���
	if(!GetProfile(xBegin,  yBegin,  xEnd,  yEnd, xRes, yRes, pProfile) || (pProfile->noPoints <= 0))
	{
		return NULL;
	}

	long x = 0, y = 0;

	for(int i=0; i<=pProfile->noPoints; i++)
	{
		//����ǰ����ע�͵��Ĳ������������д����Ч��ֻ�������ı��������ص�֮��Ĺ�ϵ
		x = (long)(floor((pProfile->xPathCoord[i] - m_XLowLeft)/xRes));
		y = (long)(floor((pProfile->yPathCoord[i] - m_YLowLeft)/yRes));	

		pProfile->xIndex[i] = x;
		pProfile->yIndex[i] = y;
	}

	double dx = 0, dy = 0;
	for(int i=0; i<=pProfile->noPoints; i++)
	{
		dx = pProfile->xPathCoord[i];
		dy = pProfile->yPathCoord[i];

		//��ȡ�õ�ĸ߶�ֵ
		if(m_bTopoNeeded && (m_pCalMap[CALMAP_DEM] != NULL))
		{
			pProfile->height[i] = (double)(m_pCalMap[CALMAP_DEM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys));
			if(pProfile->height[i] < INVALID_MAP_DATA)
			{
				pProfile->height[i] = 0.0;
			}
			if(m_pCalMap[CALMAP_DHM] != NULL)
			{
				pProfile->building[i] = (double)(m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys));
				if(pProfile->building[i] < INVALID_MAP_DATA)
				{
					pProfile->building[i] = 0.0;
				}
			}
			else if(m_pCalMap[CALMAP_DSM] != NULL)
			{
				double dTemp = m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
				if(dTemp < INVALID_MAP_DATA)
				{
					dTemp = 0.0;
				}
				pProfile->building[i] = (dTemp)-pProfile->height[i];
			}

			if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
			{
				double dTemp = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
				if(dTemp < INVALID_MAP_DATA)
				{
					dTemp = 0.0;
				}
				pProfile->conductivity[i] = dTemp;
			}
		}
		else if(m_bTopoNeeded && (m_pCalMap[CALMAP_DSM] != NULL))
		{
			double dValue = (double)(m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys));
			if(dValue < INVALID_MAP_DATA)
			{
				dValue = 0;
			}
			if(m_pCalMap[CALMAP_DHM] != NULL)
			{
				pProfile->building[i]  = (double)(m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys));
				if(pProfile->building[i] < INVALID_MAP_DATA)
				{
					pProfile->building[i] = 0;
				}						

				pProfile->height[i] = dValue - pProfile->building[i];
			}
			else
			{
				pProfile->height[i] = dValue;
			}

			if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
			{
				double dTemp = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
				if(dTemp < INVALID_MAP_DATA)
				{
					dTemp = 0.0;
				}
				pProfile->conductivity[i] = dTemp;						
			}
		}				
		else if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
		{
			double dValue = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
			if(dValue < INVALID_MAP_DATA)
			{
				dValue = 0.0;
			}
			pProfile->conductivity[i] = dValue;
		}
		else
		{
			return NULL;
		}

		if(m_bMorphoNeeded)
		{
			pProfile->clutter[i] = m_pCalMap[CALMAP_DOM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
			if(pProfile->clutter[i] < INVALID_MAP_DATA)
			{
				pProfile->clutter[i] = 0;
			}
		}
	}//end of for	

	return pProfile;	
}

CalGis_Profile* CNGCalGisMapManger::GetProfileLocal(int nBSPosX, int nBSPosY, int nCurPosX, int nCurPosY, 
													double dxRes, double dyRes, CalGis_Profile *pProfile)
{
	if(pProfile==NULL)
		return NULL;
	//profile �ռ�����
	pProfile->Reset();

	int xDir = 0;
	int yDir = 0;
	double dXPara = 0.0;
	double dYPara = 0.0;
	double dConPara = 0.0;
	int vertPath = 0;
	int horiPath = 0;
	int nXPos = 0;
	int nYPos = 0;
	int i = 0;

	if((nCurPosX == nBSPosX) && (nCurPosY == nBSPosY))
	{
		pProfile->noPoints = 0;
		return pProfile;
	}
	xDir = (nCurPosX>=nBSPosX)? 1:-1;
	yDir = (nCurPosY>=nBSPosY)? 1:-1;

	horiPath = 2 * nBSPosX;
	vertPath = 2 * nBSPosY;

	CalLinePara( nBSPosX, nBSPosY, nCurPosX, nCurPosY, dXPara, dYPara, dConPara );

	if( dYPara == 1 )
	{
		double temp = 0.0;
		int noPoints = labs( nBSPosX - nCurPosX ) ;
		if(noPoints >= pProfile->nSize)
		{
			pProfile->ReSize(noPoints);
		}
		pProfile->noPoints = noPoints ;
		temp = sqrt(pow((double)(nBSPosX-nCurPosX),2) + pow((double)(nBSPosY-nCurPosY),2)) * dyRes/(pProfile->noPoints);		
		for( i=0; i <= pProfile->noPoints; i++ )
		{
			nXPos = horiPath>>1;
			nYPos = vertPath>>1;
			pProfile->xIndex[i] = nXPos;
			pProfile->yIndex[i] = nYPos;			
			pProfile->distance[i] = (double)(i) * temp; 

			horiPath = horiPath + 2 * xDir;
			vertPath = vertPath + 1 * yDir;
			if( dXPara*horiPath + dYPara*vertPath + 2*dConPara > 0 )
			{
				vertPath = vertPath - 1;
			}
			else
			{
				vertPath = vertPath + 1;
			}
		}
	}
	else
	{
		double temp = 0.0;

		int noPoints = labs( nBSPosY - nCurPosY );
		if(noPoints >= pProfile->nSize)
		{
			pProfile->ReSize(noPoints);
		}
		pProfile->noPoints = noPoints;

		temp = sqrt(pow((double)(nBSPosX-nCurPosX),2) + pow((double)(nBSPosY-nCurPosY),2)) * dxRes/(pProfile->noPoints);

		for( i=0; i <= pProfile->noPoints; i++ )
		{
			nXPos = horiPath>>1;
			nYPos = vertPath>>1;

			pProfile->xIndex[i] = nXPos;
			pProfile->yIndex[i] = nYPos;

			pProfile->distance[i] = (double)(i) * temp;//cProfile.noPoints)*cProfile.distance[cProfile.noPoints];

			horiPath = horiPath + 1 * xDir;
			vertPath = vertPath + 2 * yDir;
			if( dXPara*horiPath + dYPara*vertPath + 2*dConPara > 0 )
			{
				horiPath = horiPath - 1;
			}
			else
			{
				horiPath = horiPath + 1;
			}
		}
	}
	return pProfile;
}

unsigned int CNGCalGisMapManger::GetCalLayers()
{
	int nRet = 0;

	if (m_bTopoNeeded && m_pTopoMap != NULL)	
	{
		nRet = m_pTopoMap->GetLayers();
	}
	else if (m_bConductNeeded && m_pCalMap[CALMAP_CON] != NULL)				
	{
		nRet = m_pCalMap[CALMAP_CON]->GetLayers();
	}

	return nRet;
}

bool CNGCalGisMapManger::SetActiveCalLayer(unsigned int lay)
{
	bool bRet = false;

	if (m_bTopoNeeded && m_pTopoMap != NULL)	
	{
		bRet = m_pTopoMap->SetActiveLayer(lay);
	}
	else if (m_bConductNeeded && m_pCalMap[CALMAP_CON] != NULL)				
	{
		bRet = m_pCalMap[CALMAP_CON]->SetActiveLayer(lay);
	}

	UpdateMap();

	return bRet;
}

unsigned int CNGCalGisMapManger::GetActiveCalLayer()
{
	int nRet = 0;

	if (m_bTopoNeeded && m_pTopoMap != NULL)	
	{
		nRet = m_pTopoMap->GetActiveLayer();
	}
	else if (m_bConductNeeded && m_pCalMap[CALMAP_CON] != NULL)				
	{
		nRet = m_pCalMap[CALMAP_CON]->GetActiveLayer();
	}

	return nRet;
}

CalGis_Profile *CNGCalGisMapManger::GetProfile(long xBegin, long yBegin, long xEnd, long yEnd,CalGis_Profile *pGisProfile)
{
	NGProfile* ngprofile = NULL;
	NGProfile tempProfile;

	POINT ptBegin;
	ptBegin.x = xBegin, ptBegin.y = yBegin;
	POINT ptEnd;
	ptEnd.x = xEnd, ptEnd.y = yEnd;

	//�����Ҫ�߳�ͼ������dem��ͼ����
	if(m_bTopoNeeded && (m_pCalMap[CALMAP_DEM] != NULL))
	{
		ngprofile = m_pCalMap[CALMAP_DEM]->GetActiveLayerPtr()->GetProfile(ptBegin, ptEnd,&tempProfile);
		
		if(ngprofile==NULL || ngprofile->nPointsNum <= 0)
		{
			return NULL;
		}

		//���profile�Ŀռ䲻������profile����������Ҫ����
		if(ngprofile->nPointsNum >= pGisProfile->nSize)
		{			
			if(pGisProfile->ReSize(ngprofile->nPointsNum)==false)
				return NULL;
			pGisProfile->noPoints = ngprofile->nPointsNum;
		}
		else
		{
			pGisProfile->noPoints = ngprofile->nPointsNum;
		}

		int nSize = pGisProfile->noPoints + 1;  //proile ͼ�д洢�ռ�Ĵ�С

		memcpy( pGisProfile->xIndex, ngprofile->pImgCoordX, sizeof(long) * nSize );
		memcpy( pGisProfile->yIndex, ngprofile->pImgCoordY, sizeof(long) * nSize );
		memcpy( pGisProfile->distance, ngprofile->pDistance, sizeof(double) * nSize );

		for(int i=0; i<=ngprofile->nPointsNum; i++)
		{
			pGisProfile->height[i] = (double)(ngprofile->pImgData[i]);
		}	

		//�����Ҫ�絼�ʵ�ͼ�����ҵ絼�ʵ�ͼ��Ϊ��
		if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
		{
			ngprofile = m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->GetProfile(ptBegin, ptEnd,&tempProfile);
			if(ngprofile==NULL)
				return NULL;
			for(int i=0; i<=ngprofile->nPointsNum; i++)
			{
				pGisProfile->conductivity[i] = (double)(ngprofile->pImgData[i]);
			}
		}

		if(m_pCalMap[CALMAP_DHM] != NULL)//���dhm����,���ȡbuilding�߶�
		{
			ngprofile = m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->GetProfile(ptBegin, ptEnd,&tempProfile);
			if(ngprofile==NULL)
				return NULL;
			for(int i=0; i<=ngprofile->nPointsNum; i++)
			{
				pGisProfile->building[i] = (double)(ngprofile->pImgData[i]);
			}					
		}
		else if(m_pCalMap[CALMAP_DSM] != NULL)//���dsm����,��ͨ��dsm��dem��ȡbuilding�߶�
		{
			ngprofile = m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->GetProfile(ptBegin, ptEnd,&tempProfile);
			if(ngprofile==NULL)
				return NULL;
			for(int i=0; i<=ngprofile->nPointsNum; i++)
			{
				pGisProfile->building[i] = (double)(ngprofile->pImgData[i]) - pGisProfile->height[i];
			}
		}
		else
		{
			memset(pGisProfile->building, 0, sizeof(double)*nSize);
		}
	}
	else if(m_bTopoNeeded && (m_pCalMap[CALMAP_DSM] != NULL))
	{
		ngprofile = m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->GetProfile(ptBegin, ptEnd,&tempProfile);
		if(ngprofile==NULL)
			return NULL;
		if(ngprofile->nPointsNum <= 0)
		{
			return NULL;
		}

		//���ngprofile�Ŀռ䲻������ngprofile����������Ҫ����
		if(ngprofile->nPointsNum >= pGisProfile->nSize)
		{			
			if(pGisProfile->ReSize(ngprofile->nPointsNum)==false)
				return NULL;
		}
		pGisProfile->noPoints = ngprofile->nPointsNum;

		int nSize = pGisProfile->noPoints + 1;

		memcpy(pGisProfile->xIndex, ngprofile->pImgCoordX, sizeof(long) * nSize);
		memcpy(pGisProfile->yIndex, ngprofile->pImgCoordY, sizeof(long) * nSize);
		memcpy(pGisProfile->distance, ngprofile->pDistance, sizeof(double) * nSize);

		for(int i=0; i<=ngprofile->nPointsNum; i++)
		{
			pGisProfile->height[i] = (double)(ngprofile->pImgData[i]);
		}	

		if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
		{
			ngprofile = m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->GetProfile(ptBegin, ptEnd,&tempProfile);
			if(ngprofile==NULL)
				return NULL;
			for(int i=0; i<=ngprofile->nPointsNum; i++)
			{
				pGisProfile->conductivity[i] = (double)(ngprofile->pImgData[i]);
			}
		}

		//����dsm �� dhm, ����������ͼ����һ��dem
		if(m_pCalMap[CALMAP_DHM] != NULL)
		{
			ngprofile = m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->GetProfile(ptBegin, ptEnd,&tempProfile);			
			if(ngprofile==NULL)
				return NULL;
			for(int i=0; i<=ngprofile->nPointsNum; i++)
			{
				pGisProfile->building[i] = (double)(ngprofile->pImgData[i]);
				pGisProfile->height[i] = pGisProfile->height[i] - pGisProfile->building[i];
			}
		}
		else//���û��dhm��dsm�洢��height��
		{
			memset(pGisProfile->building, 0, sizeof(double)*nSize);
		}	
	}
	else if(m_bTopoNeeded)//�����ҪTopoͼ�����ߵ���һ����˵����Ŀ��û�и߳�ͼ���򷵻ؿ�
	{
		return NULL;
	}
	else if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
	{
		ngprofile = m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->GetProfile(ptBegin, ptEnd,&tempProfile);
		if(ngprofile==NULL)
			return NULL;
		if(ngprofile->nPointsNum <= 0)
		{
			return NULL;
		}

		//���ngprofile�Ŀռ䲻������ngprofile����������Ҫ����
		if(ngprofile->nPointsNum >= pGisProfile->nSize)
		{			
			if(pGisProfile->ReSize(ngprofile->nPointsNum)==false)
				return NULL;
		}

		pGisProfile->noPoints = ngprofile->nPointsNum;

		int nSize = pGisProfile->noPoints + 1;

		memcpy(pGisProfile->xIndex, ngprofile->pImgCoordX, sizeof(long) * nSize);
		memcpy(pGisProfile->yIndex, ngprofile->pImgCoordY, sizeof(long) * nSize);
		memcpy(pGisProfile->distance, ngprofile->pDistance, sizeof(double) * nSize);

		for(int i=0; i<=ngprofile->nPointsNum; i++)
		{
			pGisProfile->conductivity[i] = (double)(ngprofile->pImgData[i]);
		}
	}
	else
	{
		return NULL;
	}

	if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
	{
		//�����������ת��Ϊ��γ������
		for(int i=0; i<=ngprofile->nPointsNum; i++)
		{
			GetCoordinateFromMap(pGisProfile->xIndex[i],pGisProfile->yIndex[i], 
				pGisProfile->xPathCoord[i], pGisProfile->yPathCoord[i], 103);			
		}
	}


	//edit@20131009,������Ч�߶Ⱥͼ������䶼��Ҫ����DEM��DHM��������ʱ����յ�����DEM�ϣ���ʱ������DSM
	//�ϣ������ڴ�����յ�ʱ����Щ��ͬ��Ŀǰ���������ֲ�ͬ������Ϊ����DSM֮�ϣ����ֻ��dem����dem֮��
	//��ʱ�����޸� 	
	if(m_bTopoNeeded)
	{		
		for(int i=0; i<=ngprofile->nPointsNum; i++)
		{
			pGisProfile->height[i] = pGisProfile->height[i] + pGisProfile->building[i];
			pGisProfile->building[i] = 0.0;

			//ͬʱ������������ת��Ϊ��ͼ��ͬ����ϵ������
			GetCoordinateFromMap(pGisProfile->xIndex[i],pGisProfile->yIndex[i], 
				                 pGisProfile->xPathCoord[i], pGisProfile->yPathCoord[i], m_nCoordSys);

		}
	}

	if(m_bMorphoNeeded)
	{
		ngprofile = m_pCalMap[CALMAP_DOM]->GetActiveLayerPtr()->GetProfile(ptBegin, ptEnd,&tempProfile);					
		if(ngprofile==NULL)
			return NULL;
		memcpy(pGisProfile->clutter, ngprofile->pImgData, sizeof(short)*(ngprofile->nPointsNum+1));		
	}
	else
	{
		memset(pGisProfile->clutter, 0, sizeof(short)*(pGisProfile->noPoints+1) );
	}

	return pGisProfile;
}

//(xBegin, yBegin) �� ��xEnd, yEnd) ��������ϵ����eProfileType�Ĳ�ͬ����ͬ
CalGis_Profile* CNGCalGisMapManger::GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType,CalGis_Profile *pProfile)
{	
	//_ASSERT(pProfile != NULL);
	if(pProfile==NULL)
		return NULL;
	//profile �ռ�����
	pProfile->Reset();

	switch(eProfileType)
	{
	case PROFILER_NG: 
		{
			//��(xBegin, yBegin) �� ��xEnd, yEnd)�ӵ�ͼ����ϵ��ͬ�����꣬ת��Ϊ�������
			long nxBegin = 0, nyBegin = 0;
			long nxEnd = 0, nyEnd = 0;
			GetMapCoordinate(xBegin, yBegin, m_nCoordSys, nxBegin, nyBegin);
			GetMapCoordinate(xEnd, yEnd, m_nCoordSys, nxEnd, nyEnd);

			return GetProfile(nxBegin, nyBegin, nxEnd, nyEnd,pProfile);		
		}
	case PROFILER_GEO:
		{
			//���Ȼ�ȡ�����ͽ��յ�֮��profile�ϵĵ�ľ�γ������;���
			if(!GetProfile(xBegin,  yBegin,  xEnd,  yEnd,pProfile) || (pProfile->noPoints <= 0))
			{
				return NULL;
			}

			//��ȡprofile�ϵ���������
			//--�����жϵ�ͼ�Ƿ�����Ҫ��
			if( (m_bTopoNeeded && (m_pTopoMap == NULL)) &&
				(m_bConductNeeded && (m_pCalMap[CALMAP_CON] == NULL)) )
			{
				pProfile->noPoints = 0;
				return pProfile;			
			}
			long x = 0, y = 0;

			for(int i=0; i<=pProfile->noPoints; i++)
			{
				//����ǰ����ע�͵��Ĳ������������д����Ч��ֻ�������ı��������ص�֮��Ĺ�ϵ
				x = (long)((pProfile->xPathCoord[i] - m_XLowLeft)/m_Xspacing);
				y = (long)((pProfile->yPathCoord[i] - m_YLowLeft)/m_Yspacing);	

				pProfile->xIndex[i] = x;
				pProfile->yIndex[i] = y;
			}

			double dx = 0, dy = 0;
			for(int i=0; i<=pProfile->noPoints; i++)
			{
				dx = pProfile->xPathCoord[i];
				dy = pProfile->yPathCoord[i];
				//��ȡ�õ�ĸ߶�ֵ
				if(m_bTopoNeeded && (m_pCalMap[CALMAP_DEM] != NULL))
				{
					pProfile->height[i] = (double)(m_pCalMap[CALMAP_DEM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys));
					if(pProfile->height[i] < INVALID_MAP_DATA)
					{
						pProfile->height[i] = 0.0;
					}
					if(m_pCalMap[CALMAP_DHM] != NULL)
					{
						pProfile->building[i] = (double)(m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys));
						if(pProfile->building[i] < INVALID_MAP_DATA)
						{
							pProfile->building[i] = 0.0;
						}
					}
					else if(m_pCalMap[CALMAP_DSM] != NULL)
					{
						double dTemp = m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
						if(dTemp < INVALID_MAP_DATA)
						{
							dTemp = 0.0;
						}
						pProfile->building[i] = (dTemp)-pProfile->height[i];
					}

					if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
					{
						double dTemp = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
						if(dTemp < INVALID_MAP_DATA)
						{
							dTemp = 0.0;
						}
						pProfile->conductivity[i] = dTemp;
					}
				}
				else if(m_bTopoNeeded && (m_pCalMap[CALMAP_DSM] != NULL))
				{
					double dValue = (double)(m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys));
					if(dValue < INVALID_MAP_DATA)
					{
						dValue = 0;
					}
					if(m_pCalMap[CALMAP_DHM] != NULL)
					{
						pProfile->building[i]  = (double)(m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys));
						if(pProfile->building[i] < INVALID_MAP_DATA)
						{
							pProfile->building[i] = 0;
						}						
						
						pProfile->height[i] = dValue - pProfile->building[i];
					}
					else
					{
						pProfile->height[i] = dValue;
					}

					if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
					{
						double dTemp = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
						if(dTemp < INVALID_MAP_DATA)
						{
							dTemp = 0.0;
						}
						pProfile->conductivity[i] = dTemp;						
					}
				}				
				else if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
				{
					double dValue = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
					if(dValue < INVALID_MAP_DATA)
					{
						dValue = 0.0;
					}
					pProfile->conductivity[i] = dValue;
				}
				else
				{
					return NULL;
				}

				if(m_bMorphoNeeded)
				{
					pProfile->clutter[i] = m_pCalMap[CALMAP_DOM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
					if(pProfile->clutter[i] < INVALID_MAP_DATA)
					{
						pProfile->clutter[i] = 0;
					}
				}
			}//end of for	

			return pProfile;
		}//end of case PROFILER_GEO:
	}//end of switch(eProfileType)

	return NULL;
}

//add by Liuqingmei@20161102
//��ȡָ���ֱ��ʵ�profile
CalGis_Profile* CNGCalGisMapManger::GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, 
											   EProfilerType eProfileType, double xRes, double yRes, CalGis_Profile *pProfile)
{	
	if(pProfile==NULL)
		return NULL;
	//profile �ռ�����
	pProfile->Reset();

	switch(eProfileType)
	{
	case PROFILER_NG: 
		{
			return GetProfileNG(xBegin, yBegin, xEnd, yEnd, xRes, yRes, pProfile);				
		}
	case PROFILER_GEO:
		{
			return GetProfileGeo(xBegin, yBegin, xEnd, yEnd, xRes, yRes, pProfile);			
		}
	default: return NULL;
	}
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

//ָ����ȡ��profile��𣬲���ָ��profile�п��ǵĵ�ĸ���
//eProfileType:Profile�����
//noPoints��ָ����profile�е�ĸ���
CalGis_Profile* CNGCalGisMapManger::GetProfile( double xBegin, double yBegin, double xEnd, double yEnd, 
											   EProfilerType eProfileType, int noPoints,CalGis_Profile *pProfile )
{
	if(noPoints <= 0)
	{
		return NULL;
	}
	//profile �ռ�����
	if(noPoints>=pProfile->nSize)
	{
		pProfile->ReSize(noPoints);
	}
	pProfile->noPoints = noPoints;

	pProfile->xPathCoord[0] = xBegin;
	pProfile->yPathCoord[0] = yBegin;
	pProfile->xPathCoord[noPoints] = xEnd;
	pProfile->yPathCoord[noPoints] = yEnd;
	if(eProfileType == ICalGis_MapManger::PROFILER_NG) //һ���ƽ���ͼ
	{
		//�ȴ�����ʼ�����ֹ���ֵ,��ʼ�����ֹ��洢���Ǿ�γ������
		MapCoordTrans(m_nCoordSys, 103, xBegin, yBegin, &(pProfile->xStart), &(pProfile->yStart));
		MapCoordTrans(m_nCoordSys, 103, xEnd, yEnd, &(pProfile->xEnd), &(pProfile->yEnd));
			
		//Ȼ�����profile�е�ĸ����߲�ͬ��·��
		double dxTemp = xBegin - xEnd;
		double dyTemp = yBegin - yEnd;
		double dDisM = sqrt(dxTemp*dxTemp + dyTemp*dyTemp);
		if(pProfile->noPoints != 1)
		{
			//���ݾ���͵�������profile�ϵ������			
			double dStepM = dDisM / noPoints;
			double dxStep = dxTemp / noPoints;
			double dyStep = dyTemp / noPoints;
			for(long i=1; i<noPoints; i++)
			{
				pProfile->xPathCoord[i] = xBegin + i*dxStep;
				pProfile->yPathCoord[i] = yBegin + i*dyStep;
				pProfile->distance[i] = i * dStepM;
			}			
		}
		pProfile->distance[noPoints] = dDisM;		
	}
	else if(eProfileType == ICalGis_MapManger::PROFILER_GEO) //GEO����ͼ
	{
		//�ȴ�����ʼ�����ֹ���ֵ,��ʼ�����ֹ��洢���Ǿ�γ������
		pProfile->xStart = xBegin;
		pProfile->yStart = yBegin;
		pProfile->xEnd = xEnd;
		pProfile->yEnd = yEnd;

		double dDisM = 0.0;
		double dStepM = 0.0;
		EarthCoord2D earth2D;		
		double dA = 0;
		double dF = 0;
		//��ȡ��ͼ����ϵ��Ӧ�ĵ�����ͱ�ƽ�� 
		ng_GetProjEllipSoid_AF(m_nCoordSys,&dA,&dF);
		earth2D.Set_CurrentEllipSoid_AF(dA,1.0/dF);

		DecimalToRad(xBegin, earth2D.m_LonRad1);
		DecimalToRad(yBegin, earth2D.m_LatRad1);

		DecimalToRad(xEnd, earth2D.m_LonRad2);
		DecimalToRad(yEnd, earth2D.m_LatRad2);

		//���㷽��;���
		earth2D.CalDistance2D();
		dDisM = earth2D.m_DistEllip;
		dStepM = dDisM / noPoints;
		for(long i=1; i<noPoints; i++)
		{
			earth2D.m_DistEllip = dStepM*i;
			earth2D.CalDirect2D();
			RadToDecimal(earth2D.m_LonRad2, pProfile->xPathCoord[i]);
			RadToDecimal(earth2D.m_LatRad2, pProfile->yPathCoord[i]);			
			pProfile->distance[i] = earth2D.m_DistEllip;
		}

		pProfile->distance[noPoints] = dDisM;
	}	
	
	//��ȡprofile�ϵ���������
	//--�����жϵ�ͼ�Ƿ�����Ҫ��
	if( (m_bTopoNeeded && (m_pTopoMap == NULL)) &&
		(m_bConductNeeded && (m_pCalMap[CALMAP_CON] == NULL)) )
	{
		return NULL;				
	}
	long x = 0, y = 0;

	for(int i=0; i<=pProfile->noPoints; i++)
	{
		//����ǰ����ע�͵��Ĳ������������д����Ч��ֻ�������ı��������ص�֮��Ĺ�ϵ
		x = (long)((pProfile->xPathCoord[i] - m_XLowLeft)/m_Xspacing);
		y = (long)((pProfile->yPathCoord[i] - m_YLowLeft)/m_Yspacing);	

		pProfile->xIndex[i] = x;
		pProfile->yIndex[i] = y;
	}

	double dx = 0, dy = 0;
	for(int i=0; i<=pProfile->noPoints; i++)
	{
		dx = pProfile->xPathCoord[i];
		dy = pProfile->yPathCoord[i];

		//��ȡ�õ�ĸ߶�ֵ
		if(m_bTopoNeeded && (m_pCalMap[CALMAP_DEM] != NULL))
		{
			int nValue = 0;
			nValue = m_pCalMap[CALMAP_DEM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
			if(nValue  < INVALID_MAP_DATA)
			{
				nValue  = 0;
			}
			pProfile->height[i] = nValue;

			if(m_pCalMap[CALMAP_DHM] != NULL)
			{
				pProfile->building[i] = (double)(m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys));
				if(pProfile->building[i] < INVALID_MAP_DATA)
				{
					pProfile->building[i] = 0.0;
				}
			}
			else if(m_pCalMap[CALMAP_DSM] != NULL)
			{
				nValue = m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
				if(nValue < INVALID_MAP_DATA)
				{
					pProfile->building[i] = 0;
				}
				else
				{
					pProfile->building[i] = (double)(nValue)-pProfile->height[i];
				}				
			}

			if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
			{
				double dValue = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
				if(dValue < INVALID_MAP_DATA)
				{
					dValue = 0.0;
				}
				pProfile->conductivity[i] = dValue;
			}
		}
		else if(m_bTopoNeeded && (m_pCalMap[CALMAP_DSM] != NULL))
		{
			if(m_pCalMap[CALMAP_DHM] != NULL)
			{
				short nValue = m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
				if(nValue < INVALID_MAP_DATA)
				{
					pProfile->building[i] = 0;
				}
				else
				{
					pProfile->building[i] = nValue;
				}
				nValue = m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
				if(nValue < INVALID_MAP_DATA)
				{
					pProfile->height[i] = 0;
				}
				else
				{
					pProfile->height[i] = nValue - pProfile->building[i];
				}				
			}
			else
			{
				short nValue = m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
				if(nValue < INVALID_MAP_DATA)
				{
					pProfile->height[i] = 0;
				}
				else
				{
					pProfile->height[i] = nValue;
				}			
			}

			if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
			{
				double dValue = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
				if(dValue < INVALID_MAP_DATA)
				{
					dValue = 0.0;
				}
				pProfile->conductivity[i] = dValue;			
			}
		}				
		else if(m_bConductNeeded && (m_pCalMap[CALMAP_CON] != NULL))
		{
			double dValue = (double)m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
			if(dValue < INVALID_MAP_DATA)
			{
				dValue = 0.0;
			}
			pProfile->conductivity[i] = dValue;			
		}
		else
		{
			return NULL;
		}

		if(m_bMorphoNeeded)
		{
			pProfile->clutter[i] = m_pCalMap[CALMAP_DOM]->GetActiveLayerPtr()->ShortElement(dx, dy, m_nCoordSys);
			if(pProfile->clutter[i] < INVALID_MAP_DATA)
			{
				pProfile->clutter[i] = 0;
			}
		}
	}//end of for	

	return pProfile;
}
CalGis_Profile* CNGCalGisMapManger::GetMapProfile(double xBegin, double yBegin, double xEnd, double yEnd,CalGis_Profile *pProfile)
{
	return GetProfile(xBegin,yBegin,xEnd,yEnd,eProfileType,pProfile);
}


//��ȡ������ʼ�����ֹ��֮�������ͼ��Ϣ����ʼ�����ֹ�������ϵ���ͼ����ϵ��ͬ
//˵���� �ú���ֻ���ڵ�ͼ����ϵΪgeo map��ʱ��ʹ�ã������ͼ����ϵ����geo��ʹ�øú���
//����Ը�
//�ú����������profile�еľ�γ�����꣬ (xBegin, yBegin) ����ʼ�����꣬��xEnd,yEnd)
//����ֹ������
bool CNGCalGisMapManger::GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, CalGis_Profile *pProfile)
{
	if(pProfile==NULL)
		return false;
	//���ȼ���profile�е�ĸ���
	int nPoints = 0;
	double xDiff = fabs(xEnd - xBegin);
	double yDiff = fabs(yEnd - yBegin);
	long nXDiff = long(xDiff / m_Xspacing + 0.5);
	long nYDiff = long(yDiff / m_Yspacing + 0.5);

	if(nXDiff == nYDiff && nXDiff == 0)
	{
		pProfile->noPoints = -1;
		return true;
	}

	if(nXDiff > nYDiff)
	{
		nPoints = nXDiff;
	}
	else
	{
		nPoints = nYDiff;
	}
	pProfile->noPoints = nPoints;	
	if(nPoints >= pProfile->nSize)
	{
		if(!pProfile->ReSize(nPoints))
			return false;
		pProfile->noPoints = nPoints;	
	}

	//���㷢���ͽ��յ�֮��ľ���
	EarthCoord2D earth2D;
	double dA = 0;
	double dF = 0;
	//��ȡ��ͼ����ϵ��Ӧ�ĵ�����ͱ�ƽ�� 
	ng_GetProjEllipSoid_AF(m_nCoordSys,&dA,&dF);
	earth2D.Set_CurrentEllipSoid_AF(dA,1.0/dF);
	//earth2D.Set_CurrentEllipSoid_Index(0);

	DecimalToRad(xBegin, earth2D.m_LonRad1);
	DecimalToRad(yBegin, earth2D.m_LatRad1);

	DecimalToRad(xEnd, earth2D.m_LonRad2);
	DecimalToRad(yEnd, earth2D.m_LatRad2);

	//���㷽��;���
	earth2D.CalDistance2D();

	//��ȡ����ͷ���
	double dDistanceM = earth2D.m_DistEllip;
	double dAziRad = earth2D.m_AzRad1;

	//���ݵ�ĸ�����ȡ�ֱ���
	double dResM = dDistanceM / nPoints;	

	//Ȼ������С���ľ�����㺯������ÿ����ľ�γ������
	//���ȴ����һ��������һ����
	pProfile->xPathCoord[0] = xBegin;
	pProfile->yPathCoord[0] = yBegin;
	pProfile->distance[0] = 0.0;

	pProfile->xPathCoord[nPoints] = xEnd;
	pProfile->yPathCoord[nPoints] = yEnd;
	pProfile->distance[nPoints] = dDistanceM;

	pProfile->xStart = xBegin;
	pProfile->yStart = yBegin;
	pProfile->xEnd = xEnd;
	pProfile->yEnd = yEnd;

	double dDisTmpM = dResM;
	for(int i=1; i<nPoints; i++)
	{
		earth2D.m_DistEllip = dDisTmpM;

		//�����i���������
		earth2D.CalDirect2D();

		//ȡ����i���������
		RadToDecimal(earth2D.m_LonRad2, pProfile->xPathCoord[i]);
		RadToDecimal(earth2D.m_LatRad2, pProfile->yPathCoord[i]);
		pProfile->distance[i] = dDisTmpM;

		dDisTmpM = dDisTmpM + dResM;
	}

	return true;
}

bool CNGCalGisMapManger::GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, 
									double xRes, double yRes, CalGis_Profile *pProfile)
{
	if(pProfile==NULL)
		return false;
	//���ȼ���profile�е�ĸ���
	int nPoints = 0;
	double xDiff = fabs(xEnd - xBegin);
	double yDiff = fabs(yEnd - yBegin);
	long nXDiff = long(xDiff / xRes + 0.5);
	long nYDiff = long(yDiff / yRes + 0.5);

	if(nXDiff == nYDiff && nXDiff == 0)
	{
		pProfile->noPoints = -1;
		return true;
	}

	if(nXDiff > nYDiff)
	{
		nPoints = nXDiff;
	}
	else
	{
		nPoints = nYDiff;
	}
	pProfile->noPoints = nPoints;	
	if(nPoints >= pProfile->nSize)
	{
		if(!pProfile->ReSize(nPoints))
			return false;
		pProfile->noPoints = nPoints;	
	}

	//���㷢���ͽ��յ�֮��ľ���
	EarthCoord2D earth2D;
	double dA = 0;
	double dF = 0;
	//��ȡ��ͼ����ϵ��Ӧ�ĵ�����ͱ�ƽ�� 
	ng_GetProjEllipSoid_AF(m_nCoordSys,&dA,&dF);
	earth2D.Set_CurrentEllipSoid_AF(dA,1.0/dF);
	//earth2D.Set_CurrentEllipSoid_Index(0);

	DecimalToRad(xBegin, earth2D.m_LonRad1);
	DecimalToRad(yBegin, earth2D.m_LatRad1);

	DecimalToRad(xEnd, earth2D.m_LonRad2);
	DecimalToRad(yEnd, earth2D.m_LatRad2);

	//���㷽��;���
	earth2D.CalDistance2D();

	//��ȡ����ͷ���
	double dDistanceM = earth2D.m_DistEllip;
	double dAziRad = earth2D.m_AzRad1;

	//���ݵ�ĸ�����ȡ�ֱ���
	double dResM = dDistanceM / nPoints;	

	//Ȼ������С���ľ�����㺯������ÿ����ľ�γ������
	//���ȴ����һ��������һ����
	pProfile->xPathCoord[0] = xBegin;
	pProfile->yPathCoord[0] = yBegin;
	pProfile->distance[0] = 0.0;

	pProfile->xPathCoord[nPoints] = xEnd;
	pProfile->yPathCoord[nPoints] = yEnd;
	pProfile->distance[nPoints] = dDistanceM;

	pProfile->xStart = xBegin;
	pProfile->yStart = yBegin;
	pProfile->xEnd = xEnd;
	pProfile->yEnd = yEnd;

	double dDisTmpM = dResM;
	for(int i=1; i<nPoints; i++)
	{
		earth2D.m_DistEllip = dDisTmpM;

		//�����i���������
		earth2D.CalDirect2D();

		//ȡ����i���������
		RadToDecimal(earth2D.m_LonRad2, pProfile->xPathCoord[i]);
		RadToDecimal(earth2D.m_LatRad2, pProfile->yPathCoord[i]);
		pProfile->distance[i] = dDisTmpM;

		dDisTmpM = dDisTmpM + dResM;
	}

	return true;
}


//��ȡ����ͼ�ĸ߶�
short CNGCalGisMapManger::GetTopoValue(long x, long y)
{
	//_ASSERT(m_pTopoMap != NULL);
	//Modify by liuqingmei,Ŀǰ������ֻ��Ϊ�˱�֤����
	if(m_pTopoMap != NULL)
	{
		return m_pTopoMap->GetActiveLayerPtr()->ShortElement(x,y);
	}
	else
	{
		return 0;
	}	
}

//��ȡ����ͼ�ĸ߶�
short CNGCalGisMapManger::GetDemHeight(long x, long y)
{
	short nHeight = 0;
	if(m_pCalMap[CALMAP_DEM] != NULL)
	{
		nHeight = m_pCalMap[CALMAP_DEM]->GetActiveLayerPtr()->ShortElement(x, y);
	}
	return nHeight;
}


short CNGCalGisMapManger::GetClutterValue(long x, long y)
{
	short nClutter = -1;
	if(m_pCalMap[CALMAP_DOM] != NULL)
	{
		nClutter = m_pCalMap[CALMAP_DOM]->GetActiveLayerPtr()->ShortElement(x, y);
	}
	return nClutter;
}

//��ȡ�������潨����͵��εĸ߶�ֵ
short CNGCalGisMapManger::GetDsmHeight(long x, long y)
{
	short height = 0;
	if(m_pCalMap[CALMAP_DSM] != NULL)
	{
		height = m_pCalMap[CALMAP_DSM]->GetActiveLayerPtr()->ShortElement(x, y);
	}
	else if((m_pCalMap[CALMAP_DEM] != NULL)&&(m_pCalMap[CALMAP_DHM] != NULL))
	{
		//�������Ĭ��ֵ
		if(m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->ShortElement(x,y) == m_pCalMap[CALMAP_DHM]->GetDefaultValue()) 
		{
			height = m_pCalMap[CALMAP_DEM]->GetActiveLayerPtr()->ShortElement(x, y);
		}
		else
		{
			height = m_pCalMap[CALMAP_DEM]->GetActiveLayerPtr()->ShortElement(x, y) + m_pCalMap[CALMAP_DHM]->GetActiveLayerPtr()->ShortElement(x, y);
		}
	}
	else if(m_pCalMap[CALMAP_DEM] != NULL)
	{
		height = m_pCalMap[CALMAP_DEM]->GetActiveLayerPtr()->ShortElement(x, y);
	}

	return height;
}

//�ýӿڼٶ�x,y���������ͼ����ϵ��ͬ
short CNGCalGisMapManger::GetTopoValue(double x, double y)
{	
	double dXTmp = x;
	double dYTmp = y;

	//�Ƚ���������ת��Ϊ�������	
	double xLowLeft = m_XLowLeft + m_Xspacing/2.0;
	double yLowLeft = m_YLowLeft + m_Xspacing/2.0;

	long xOut = 0;
	long yOut = 0;

	//����ͼ��ͬ������ת��Ϊ������� --����m_Xspacing/2.0��Ϊ����������
	xOut = (int)((dXTmp - xLowLeft + m_Xspacing/2.0)/m_Xspacing);
	yOut = (int)((dYTmp - yLowLeft + m_Yspacing/2.0)/m_Yspacing);

	return GetTopoValue(xOut, yOut);
}

//�ýӿڼٶ�x,y���������ͼ����ϵ��ͬ
short CNGCalGisMapManger::GetDemHeight(double x, double y)
{	
	double dXTmp = x;
	double dYTmp = y;

	//�Ƚ���������ת��Ϊ�������	
	double xLowLeft = m_XLowLeft + m_Xspacing/2.0;
	double yLowLeft = m_YLowLeft + m_Xspacing/2.0;

	long xOut = 0;
	long yOut = 0;

	//����ͼ��ͬ������ת��Ϊ������� --����m_Xspacing/2.0��Ϊ����������
	xOut = (int)((dXTmp - xLowLeft + m_Xspacing/2.0)/m_Xspacing);
	yOut = (int)((dYTmp - yLowLeft + m_Yspacing/2.0)/m_Yspacing);

	return GetDemHeight(xOut, yOut);
}

//��ȡ���ڵ�ͼ���������
bool CNGCalGisMapManger::GetMapCoordinate(double xPoint, double yPoint, int nCoordSys, long& xOut, long& yOut)
{
	//������������ת��Ϊ��ͼ����ϵ��ͬ������
	double dXTmp = xPoint;
	double dYTmp = yPoint;
	if(nCoordSys != m_nCoordSys)
	{
		//ng_geo_init();
		ng_geo_trans(nCoordSys, m_nCoordSys, xPoint, yPoint, &dXTmp, &dYTmp);
	}

	//edit by LiuQingmei --�����޸ĵ�ԭ�򣬵�ͼ�и����ĸ߶�ʵ������һ��ƽ��ֵ
	//�������5�׵ľ��ȣ������ĸ߶Ⱦ���5�׸����ڵ�ƽ���߶�
	double xLowLeft = m_XLowLeft + m_Xspacing/2.0;
	double yLowLeft = m_YLowLeft + m_Xspacing/2.0;

	//����ͼ��ͬ������ת��Ϊ������� --����m_Xspacing/2.0��Ϊ����������
	xOut = (int)((dXTmp - xLowLeft + m_Xspacing/2.0)/m_Xspacing);
	yOut = (int)((dYTmp - yLowLeft + m_Yspacing/2.0)/m_Yspacing);

	return true;
}

//��ȡ���ͼ����ϵ��ͬ������
bool CNGCalGisMapManger::GetMapCoordinate(double xPoint, double yPoint, int nCoordSys, double& xOut, double& yOut)
{
	//������������ת��Ϊ��ͼ����ϵ��ͬ������
	xOut = xPoint;
	yOut = yPoint;

	if(nCoordSys != m_nCoordSys)
	{
		//ng_geo_init();
		ng_geo_trans(nCoordSys, m_nCoordSys, xPoint, yPoint, &xOut, &yOut);
	}

	return true;
}

//���ݵ�ͼ����������ȡ��Ӧ����ϵ������  --�������ĵ������
bool CNGCalGisMapManger::GetCoordinateFromMap(long xPoint, long yPoint, double& xOut, double& yOut, int nCoordSys)
{
	//���������ת��ΪUTM����
	double dXTmp = xPoint*m_Xspacing + m_Xspacing/2.0 + m_XLowLeft ;
	double dYTmp = yPoint*m_Yspacing + m_Yspacing/2.0 + m_YLowLeft;

	//�жϸ���������ϵ���ͼ������ϵ�Ƿ���ͬ,�����ͬ,����Ҫת������	
	if(nCoordSys != m_nCoordSys)
	{
		//ng_geo_init();
		ng_geo_trans(m_nCoordSys, nCoordSys, dXTmp, dYTmp, &xOut, &yOut);
	}
	else
	{
		xOut = dXTmp;
		yOut = dYTmp;
	}

	return true;
}

bool CNGCalGisMapManger::MapCoordTrans( long fromSys, long toSys, double fromX, double fromY,double *toX,  double *toY)
{
	if(fromSys != toSys)
	{
		ng_geo_trans(fromSys, toSys, fromX, fromY, toX, toY);
	}
	else
	{
		*toX = fromX;
		*toY = fromY;
	}

	return true;
}

//��������λ�ô���ֵ�Ƿ�����Чֵ
bool CNGCalGisMapManger::isInvalidValue(double x, double y, int CoordSys)
{
	if(m_pTopoMap != NULL)
	{
		if(m_pTopoMap->GetActiveLayerPtr()->ShortElement(x, y, CoordSys) == m_pTopoMap->GetDefaultValue())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(m_pCalMap[CALMAP_CON] != NULL)
	{
		if(m_pCalMap[CALMAP_CON]->GetActiveLayerPtr()->ShortElement(x, y, CoordSys) == m_pCalMap[CALMAP_CON]->GetDefaultValue())
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

//�жϸ����ĵ��Ƿ��ڵ�ͼ����
bool CNGCalGisMapManger::IsPointOutofMap(long xPoint, long yPoint, long nCoordSys)
{
	long x = xPoint;
	long y = yPoint;

	//-1��ʾ�������
	if(nCoordSys != -1)
	{
		//�������-1��Ҫ��һЩת������

	}
	long nWidth = GetMapWidth();
	long nHeight = GetMapHeight();

	if((x<0) || (x>=nWidth))
	{
		return true;
	}

	if((y<0) || (y>=nHeight))
	{
		return true;
	}

	return false;
}

//�жϸ����ĵ��Ƿ��ڵ�ͼ����
bool CNGCalGisMapManger::IsPointOutofMap(double xPoint, double yPoint, long nCoordSys)
{		
	long nWidth = GetMapWidth();
	long nHeight = GetMapHeight();

	double xTemp = xPoint;
	double yTemp = yPoint;

	long x = 0;
	long y = 0;

	//��������������ϵ���ͼ������ϵ��ͬ������Ҫ��������ת�� 
	if(nCoordSys != m_nCoordSys)
	{
		ng_geo_init();
		ng_geo_trans(nCoordSys, m_nCoordSys, xPoint, yPoint, &xTemp, &yTemp);
	}

	x = (long)((xTemp - m_XLowLeft)/m_Xspacing + 0.5);
	y = (long)((yTemp - m_YLowLeft)/m_Yspacing + 0.5);

	if((x<0) || (x>=nWidth))
	{
		return true;
	}

	if((y<0) || (y>=nHeight))
	{
		return true;
	}

	return false;
}

const bool CNGCalGisMapManger::HasMapType( CalMapType mapType )
{
	if(mapType>-1 && mapType<CALMAP_ALL)
		return (m_pCalMap[mapType] != NULL);
	return false;
}


//////////////////////////////////////////////////////////////////////////
ICalGis_MapManger *NG_Create_CalGisMapManger()
{
	ICalGis_MapManger *pRet = new CNGCalGisMapManger;
	return pRet;
}

void NG_Release_CalGisMapManger(ICalGis_MapManger *PMap)
{
	if (PMap != NULL)
		delete PMap;
}
