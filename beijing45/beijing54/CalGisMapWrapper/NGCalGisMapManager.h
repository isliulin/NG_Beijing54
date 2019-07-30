#ifndef __NG__CAL__GIS_MANAGER__H__
#define __NG__CAL__GIS_MANAGER__H__

#include "../NGMap/INGMapGeo.h"
#include "ICalGisMapManager.h"

class CNGCalGisMapManger:public ICalGis_MapManger
{
public:
	CNGCalGisMapManger();
	~CNGCalGisMapManger();

public:
	virtual void EnableMap_Topo(bool bEnale);
	virtual bool IsEnableMap_Topo() { return m_bTopoNeeded;}

	virtual void EnableMap_Conduct(bool bEnale);
	virtual bool IsEnableMap_Conduct() { return m_bConductNeeded;}

	virtual void EnableMap_Clutter(bool bEnale);
	virtual bool IsEnableMap_Clutter() { return m_bMorphoNeeded;}

	const bool HasMapType(CalMapType mapType);

	//地图设置:dsm,dem,dhm,dom,pop,con,计算使用地图数据
	virtual bool SetCalMapFilePath(CalMapType mapType,const char *pFilePath);		//dsm
	virtual const char *GetCalMapFilePath(CalMapType mapType) { return m_szCalMapFilePath[mapType];}
	virtual void DeleteCalMap(CalMapType mapType);
	virtual void DeleteAllCalMap();
	virtual void ReleaseCalMapData(CalMapType mapType);	//仅释放地图内存数据
	virtual void ReleaseAllCalMapData();
	
	//设置计算使用的图层
	virtual unsigned int GetCalLayers();				//获取金字塔层数
	virtual bool SetActiveCalLayer(unsigned int lay);	//设置计算图层
	virtual unsigned int GetActiveCalLayer();

	//获取地图公有的一些信息
	virtual short GetMapCoordSys(){ return m_nCoordSys; }
	virtual long GetMapWidth(){ return m_nWidth; }				//获取宽度
	virtual long GetMapHeight(){ return m_nHeight; }			//获取高度
	virtual double GetResolutionX(){ return m_Xspacing; }		//获取水平精度
	virtual double GetResolutionY(){ return m_Yspacing; }		//获取垂直方向精度
	virtual double GetMapLowerLeftXCoord(){ return m_XLowLeft;}	//地图左下角坐标 
	virtual double GetMapLowerLeftYCoord(){ return m_YLowLeft;}

	//////////////////////////////////////////////////////////////////////////
	//获取profile相关的函数
	//获取给定起点和终点之间的profile，其中起点和终点的坐标为索引，根据地图起始点和分辨率获取的相对坐标
	virtual CalGis_Profile* GetProfile(long xBegin, long yBegin, long xEnd, long yEnd,CalGis_Profile *pProfile);

	//指定获取的profile的类别，profile会根据球面坐标或平面坐标获取相应的剖面，按照地图的分辨率
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType,CalGis_Profile *pProfile);

	//获取指定分辨率的profile,profile会根据球面坐标或平面坐标获取相应的剖面，按照指定的分辨率
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType, 
		double xRes, double yRes, CalGis_Profile *pProfile);

	//指定获取的profile类别，并且指定profile中考虑的点的个数
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType, 
		int noPoints,CalGis_Profile *pProfile);
	//////////////////////////////////////////////////////////////////////////

	//获取地形图的高度
	virtual short GetTopoValue(long x, long y);

	//获取DEM图的高度
	virtual short GetDemHeight(long x, long y);

	//获取包含地面建筑物和地形的高度值
	virtual short GetDsmHeight(long x, long y);

	//获取建筑物高度，如果没有地图返回-1；
	virtual short GetDhmHeight(long x,long y);

	//获取clutter数据，如果没有clutter地图，则返回-1；
	virtual short GetClutterValue(long x, long y);

	virtual short GetTopoValue(double x, double y);			//获取地形图的高度

	//获取DEM图的高度
	virtual short GetDemHeight(double x, double y);

	//释放加载到内存中的地图数据,但是地图信息还在

	//判断x,y位置处的值是否是有效值
	virtual bool isInvalidValue(int x, int y);
	//判断给定的点是否在地图外面
	virtual bool IsPointOutofMap(long xPoint, long yPoint, long nCoordSys);
	//判断给定的点是否在地图外面
	virtual bool IsPointOutofMap(double xPoint, double yPoint, long nCoordSys);

	//坐标转换
	//获取关于地图的相对坐标
	virtual bool GetMapCoordinate(double xPoint, double yPoint, int nCoordSys, long& xOut, long& yOut);
	//获取与地图坐标系相同的坐标
	virtual bool GetMapCoordinate(double xPoint, double yPoint, int nCoordSys, double& xOut, double& yOut);
	//根据地图的相对坐标获取相应坐标系的坐标
	virtual bool GetCoordinateFromMap(long xPoint, long yPoint, double& xOut, double& yOut, int nCoordSys);
	virtual bool MapCoordTrans( long fromSys, long toSys, double fromX, double fromY,double *toX,  double *toY);

protected:
	void UpdateMap();

	//获取平面坐标系下指定分辨率的链路
	CalGis_Profile* GetProfileNG(double xBegin, double yBegin, double xEnd, double yEnd,
		double xRes, double yRes, CalGis_Profile *pProfile);

	//获取球面坐标系下指定分辨率的链路
	CalGis_Profile* GetProfileGeo(double xBegin, double yBegin, double xEnd, double yEnd,
		double xRes, double yRes, CalGis_Profile *pProfile);

	CalGis_Profile* GetProfileLocal(int nBSPosX, int nBSPosY, int nCurPosX, int nCurPosY, 
		double dxRes, double dyRes, CalGis_Profile *pProfile);

	//获取给定起始点和终止点之间的剖面图信息，起始点和终止点的坐标系与地图坐标系相同
	//说明： 该函数只是在地图坐标系为geo map的时候使用，如果地图坐标系不是geo，使用该函数
	//后果自负
	//该函数负责产生profile中的经纬度坐标， (xBegin, yBegin) 是起始点坐标，（xEnd,yEnd)
	//是终止点坐标
	bool GetProfile(double xBegin, double yBegin, double xEnd, double yEnd,CalGis_Profile *pProfile);	

	bool GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, double xRes, double yRes, CalGis_Profile *pProfile);

	CalGis_Profile* GetMapProfile(double xBegin, double yBegin, double xEnd, double yEnd,CalGis_Profile *pProfile);

protected:
	IPyramidMapGeo *m_pCalMap[CALMAP_ALL];
	IPyramidMapGeo *m_pTopoMap;

	enum {MAX_FILE_PATH = 260};
	char m_szCalMapFilePath[CALMAP_ALL][MAX_FILE_PATH];

	ICalGis_MapManger::EProfilerType eProfileType;

	bool m_bTopoNeeded;				//是否需要高程图
	bool m_bMorphoNeeded;
	bool m_bConductNeeded;			//是否需要电导率图

	//地图的公有信息
	int m_nCoordSys;				//起始点坐标的坐标系信息
	double m_XLowLeft;
	double m_YLowLeft;
	double m_Xspacing;
	double m_Yspacing;				//分辨率，每两个像素点之间的距离;	
	long m_nWidth;
	long m_nHeight;

};

#endif