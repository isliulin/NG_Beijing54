/*
2013.3.13 jjj
计算地图管理器,支持多分辨率地图(金字塔地图)
	计算地图管理器接口主要给算法提供计算使用的地理数据(高度数据,地貌
数据,电导率数据,人口分布数据等)

	最主要的接口是GetProfile,获取剖面上的所有点的地理数据
	如果地图有多分辨率,则计算之前可以调用SetActiveCalLayer来设定计算
使用的分辨率,默认情况下使用的是数字地图的基本分辨率

	层增加1，地图分辨率扩大2倍
	比如基本分辨率 为 20 m
		level0:	20m		=	20m*1		= 20*2<<0
		level1:	40m		=	20m*2		= level0*2<<1
		level2:	80m		=	level1*2	= level0*2<<2
		level3:	160m	=	level2*2	= level0*2<<3
		level4:	320m	=	level3*2	= level0*2<<4
		level5:	640m	=	level4*2	= level0*2<<5
		etc...

	如果需要获取某个图层的地图数据,调用
		bool SetActiveCalLayer(unsigned int lay)函数,其中参数 lay:
		lay = 0		-->基本分辨率地图,level0
		lay = 1		-->基本分辨率地图,level1
		lay = 2		-->基本分辨率地图,level2
		etc...

2013.3.13	v1.0

*/
#ifndef __I__CAL__GIS_MANAGER__H__
#define __I__CAL__GIS_MANAGER__H__

#include "CalGisProfile.h"

/*
	计算使用地图管理器
*/
struct  GISMAP_API ICalGis_MapManger
{
	ICalGis_MapManger();
	virtual ~ICalGis_MapManger();

	enum EProfilerType
	{
		BRESENHAM =0,
		PROFILER_NG = 1,
		PROFILER_SHORT = 2,
		PROFILER_GEO = 3
	};

	//计算地图类别
	enum CalMapType
	{
		CALMAP_DSM = 0,
		CALMAP_DEM = 1,
		CALMAP_DHM = 2,
		CALMAP_DOM = 3,
		CALMAP_POP = 4,
		CALMAP_CON = 5,
		CALMAP_INDOOR = 6,
		CALMAP_VECTOR = 7,
		CALMAP_ALL = 8
	};

	//
	virtual void EnableMap_Topo(bool bEnale)=0;
	virtual bool IsEnableMap_Topo()=0;

	virtual void EnableMap_Conduct(bool bEnale)=0;
	virtual bool IsEnableMap_Conduct()=0;

	virtual void EnableMap_Clutter(bool bEnale) = 0;
	virtual bool IsEnableMap_Clutter() = 0;

	virtual const bool HasTopoMap() = 0;

	//计算地图设置:dsm,dem,dhm,dom,pop,con,计算使用地图数据
	virtual bool SetCalMapFilePath(CalMapType mapType,const char *pFilePath)=0;
	//获取计算地图路径
	virtual const char *GetCalMapFilePath(CalMapType mapType)=0;
	virtual const bool HasMapType(CalMapType mapType) = 0;
	virtual void DeleteCalMap(CalMapType mapType)=0;
	virtual void DeleteAllCalMap()=0;						//删除地图
	virtual void ReleaseCalMapData(CalMapType mapType)=0;	//仅释放地图内存数据
	virtual void ReleaseAllCalMapData()=0;

	//计算时可以选择不同分辨率的地图
	virtual unsigned int GetCalLayers()=0;					//获取金字塔层数
	virtual bool SetActiveCalLayer(unsigned int lay)=0;		//设置活动图层
	virtual unsigned int GetActiveCalLayer()=0;

	//获取地图公有的一些信息 
	virtual short GetMapCoordSys()=0;						//坐标系编号
	virtual long GetMapWidth()=0;							//获取宽度
	virtual long GetMapHeight()=0;							//获取高度
	virtual double GetResolutionX()=0;						//获取水平精度
	virtual double GetResolutionY()=0;						//获取垂直方向精度
	virtual double GetMapLowerLeftXCoord()=0;				//地图左下角坐标 
	virtual double GetMapLowerLeftYCoord()=0;

	//profile 相关函数		
	//下面三个函数需要改进
	virtual CalGis_Profile* GetProfile(long xBegin, long yBegin, long xEnd, long yEnd,CalGis_Profile *pProfile)=0;

	//指定获取的profile的类别
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType,CalGis_Profile *pProfile)=0;
	//获取指定分辨率的profile,profile会根据球面坐标或平面坐标获取相应的剖面，按照指定的分辨率
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType, 
		double xRes, double yRes, CalGis_Profile *pProfile) = 0;
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType, int noPoints,CalGis_Profile *pProfile)=0;

	//地图高度值获取
	virtual short GetTopoValue(long x, long y)=0;			//获取地形图的高度
	virtual short GetDsmHeight(long x, long y)=0;			//获取包含地面建筑物和地形的高度值
	virtual short GetDemHeight(long x, long y)=0;			//获取地形的高度值
	virtual short GetClutterValue(long x, long y) = 0;

	virtual short GetTopoValue(double x, double y)=0;			//获取地形图的高度
	virtual short GetDemHeight(double x, double y)=0;			//获取地形图的高度
	
	//判断x,y位置处的值是否是有效值
	virtual bool isInvalidValue(double x, double y, int CoordSys)=0;

	//判断给定的点是否在地图外面
	virtual bool IsPointOutofMap(long xPoint, long yPoint, long nCoordSys)=0;
	//判断给定的点是否在地图外面
	virtual bool IsPointOutofMap(double xPoint, double yPoint, long nCoordSys)=0;

	//坐标转换函数
	//获取关于地图的相对坐标
	virtual bool GetMapCoordinate(double xPoint, double yPoint, int nCoordSys, long& xOut, long& yOut)=0;
	//获取与地图坐标系相同的坐标
	virtual bool GetMapCoordinate(double xPoint, double yPoint, int nCoordSys, double& xOut, double& yOut)=0;
	//根据地图的相对坐标获取相应坐标系的坐标
	virtual bool GetCoordinateFromMap(long xPoint, long yPoint, double& xOut, double& yOut, int nCoordSys)=0;
	//坐标转换
	virtual bool MapCoordTrans(long fromSys, long toSys, double fromX, double fromY,double *toX,  double *toY)=0;

};
 
extern "C"  GISMAP_API ICalGis_MapManger *NG_Create_CalGisMapManger();				//创建地图计算管理对象
extern "C"  GISMAP_API void NG_Release_CalGisMapManger(ICalGis_MapManger *PMap);	//释放地图计算管理对象

#endif