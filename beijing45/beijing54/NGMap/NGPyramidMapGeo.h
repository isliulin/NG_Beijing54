#ifndef __NG__PYRAMID_MAP_GEO__H__
#define __NG__PYRAMID_MAP_GEO__H__

#include "INGMapGeo.h"
#include <map>

class CNGPyramiMapGeo:public IPyramidMapGeo
{
public:
	CNGPyramiMapGeo();
	virtual ~CNGPyramiMapGeo();

	enum {NameBytes = 64};
	enum {MAX_FILE_PATH = 260};

public:
	virtual bool ReadPyramidMap(const char *pFilePath);						//读取栅格地图
	
	virtual unsigned int GetLayers(){return m_Maps.size();}					//获取金字塔层数
	virtual bool SetActiveLayer(unsigned int lay);							//设置活动图层
	virtual unsigned int GetActiveLayer(){return m_AcitveLayer;}
	virtual INGMapGeo* GetActiveLayerPtr(){return m_pAcitvieLayerMap;}		//获取激活图层的地图接口对象

	//金字塔地图的所有图层左下角相同，地图类别相同,坐标系相同,缺省值相同
	virtual double GetMapLowerLeftXCoord(){return m_XLowLeft;}				//地图左下角坐标 
	virtual double GetMapLowerLeftYCoord(){return m_YLowLeft;}				
	virtual int	GetMapDataType() { return m_MapDataType;}					//地图数据类别，MT_TOPO，MT_MORPH等
	virtual const char *GetCoordShortName(){return szCoordShortName;}
	virtual short GetDefaultValue(){return m_DefaultValue;}

	virtual double Get_Layer0_ResolutionX(){return m_Xspacing0;}			//每两个点之间的距离
	virtual double Get_Layer0_ResolutionY(){return m_Yspacing0;}

protected:
	void ClearAllData();

protected:
	short m_DefaultValue;								//地图缺省值
	int m_MapDataType;
	double	m_XLowLeft;
	double	m_YLowLeft;									//左下角坐标值
	double m_Xspacing0;
	double m_Yspacing0;	
	char szCoordShortName[NameBytes];

	std::map<unsigned int,INGMapGeo *> m_Maps;
	INGMapGeo *m_pAcitvieLayerMap;
	unsigned int m_AcitveLayer;

};



#endif