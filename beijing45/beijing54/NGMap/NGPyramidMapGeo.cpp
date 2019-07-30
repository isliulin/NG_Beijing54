#include <stdio.h>
#include <math.h>
#include <string.h>
#include "NGPyramidMapGeo.h"

char gSzLdf_FileName[] = "LAYERDESCRIPTIONFILE.LDF";
char gSzLayer_Prex[] = "ImagePyramid/Layer";

#pragma warning(disable:4996)

CNGPyramiMapGeo::CNGPyramiMapGeo()
{
	m_DefaultValue = 0;
	m_MapDataType = NG_MT_UNKNOWN_MAP_TYPE;
	m_XLowLeft = 0;
	m_YLowLeft = 0;						//左下角坐标值
	m_Xspacing0 = 0;
	m_Yspacing0 = 0;	

	m_pAcitvieLayerMap = NULL;
	m_AcitveLayer = 0;

	memset(szCoordShortName,0,NameBytes);
}

CNGPyramiMapGeo::~CNGPyramiMapGeo()
{
	ClearAllData();
}

void CNGPyramiMapGeo::ClearAllData()
{
	std::map<unsigned int,INGMapGeo *>::iterator it;
	for (it = m_Maps.begin();it != m_Maps.end();it ++)
	{
		if (it->second != NULL)
		{
			NG_ReleaseMapGeo(it->second);
		}
	}
	m_Maps.clear();
	m_pAcitvieLayerMap = NULL;
}

bool CNGPyramiMapGeo::ReadPyramidMap(const char *pFilePath)
{
	ClearAllData();

	if (pFilePath == NULL)
		return false;

	m_pAcitvieLayerMap = NG_CreateMapGeo();
	if (!m_pAcitvieLayerMap->ReadMapData(pFilePath))
	{
		NG_ReleaseMapGeo(m_pAcitvieLayerMap);
		m_pAcitvieLayerMap = NULL;

		return false;
	}

	//layer 0
	m_DefaultValue = m_pAcitvieLayerMap->GetDefaultValue();
	m_MapDataType = m_pAcitvieLayerMap->GetMapDataType();
	m_XLowLeft = m_pAcitvieLayerMap->GetMapLowerLeftXCoord();
	m_YLowLeft = m_pAcitvieLayerMap->GetMapLowerLeftYCoord();
	m_Xspacing0 = m_pAcitvieLayerMap->GetResolutionX();
	m_Yspacing0 = m_pAcitvieLayerMap->GetResolutionY();
	strcpy(szCoordShortName,m_pAcitvieLayerMap->GetCoordShortName());

	m_AcitveLayer = 0;
	m_Maps.insert(std::make_pair(m_AcitveLayer,m_pAcitvieLayerMap));

	//地图文件目录
	//char szFileDir[MAX_FILE_PATH];
	//strcpy(szFileDir,pFilePath);
	//int nLen = strlen(szFileDir);
	//for (int i = nLen-1;i >= 0;i --)
	//{
	//	if (szFileDir[i] == '\\' || szFileDir[i] == '/')
	//	{
	//		szFileDir[i] = 0;
	//		break;
	//	}
	//}
	//strcat(szFileDir,"/");
	//strcat(szFileDir,gSzLayer_Prex);

	//读取其他图层
	//char szLayerTemp[16];
	//char szTemp[MAX_FILE_PATH];
	//INGMapGeo * pMapGeo = NULL;
	//for (unsigned int i = 1; i < 6;i ++)	//最多5层
	//{
 //       sprintf(szLayerTemp,"%d",i);
	//	//itoa(i,szLayerTemp,10);
	//	strcpy(szTemp,szFileDir);
	//	strcat(szTemp,szLayerTemp);			//加上层名称
	//	strcat(szTemp,"/");
	//	strcat(szTemp,gSzLdf_FileName);		//ldf文件

	//	pMapGeo = NG_CreateMapGeo();
	//	if (!pMapGeo->ReadMapData(szTemp))
	//	{
	//		NG_ReleaseMapGeo(pMapGeo);
	//		pMapGeo = NULL;

	//		break;		//读取失败，跳出循环
	//	}

	//	m_Maps.insert(std::make_pair(i,pMapGeo));
	//}

	return true;
}

bool CNGPyramiMapGeo::SetActiveLayer(unsigned int lay)
{
	std::map<unsigned int,INGMapGeo *>::iterator it = m_Maps.find(lay);
	if (it != m_Maps.end())
	{
		m_pAcitvieLayerMap = it->second;
		return true;
	}

	return false;
}


IPyramidMapGeo *NG_Create_Pyramid_MapGeo()
{
	IPyramidMapGeo *pRet = new CNGPyramiMapGeo;
	return pRet;
}

void NG_Release_Pyramid_MapGeo(IPyramidMapGeo *PMap)
{
	if (PMap != NULL)
		delete PMap;
}