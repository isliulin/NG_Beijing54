#ifndef __CAL__GIS_PROFILE__H__
#define __CAL__GIS_PROFILE__H__

#include "CalGisMapWrapper.h"

/*
计算profile
profile 主要包含数据有:
	height			(dem or dsm) 高度
	clutter			地貌
	building		建筑物高度
	conductivity	电导率
	坐标信息
*/
//计算profile
class GISMAP_API CalGis_Profile 
{
public:	
	static CalGis_Profile* Create();
	static CalGis_Profile* Create(int inSize);
	static bool	Destroy(CalGis_Profile* pDestroy);

public:
	CalGis_Profile(long noPoints);
	CalGis_Profile();
	CalGis_Profile(const CalGis_Profile& that);		//add by jjj 2013.8.8 复制构造	
	CalGis_Profile& operator=(const CalGis_Profile& that);
	~CalGis_Profile();	

	//重新申请大小
	bool ReSize(int nSize);

	//空间重置
	void Reset();

	//清理空间
	void Clear();

public:
	long nSize;              //profile的大小
	long noPoints;           //Profile 中点的个数 --显式的置值

	//添加一个起始点坐标和终止点坐标
	double xStart;
	double yStart;
	double xEnd;
	double yEnd;

	long* xIndex;            //相对于地图起始点的坐标
	long* yIndex;
	double* xPathCoord;      //路径中点在地图中的绝对坐标(UTM或者WGS84)
	double* yPathCoord;
	double* distance;        //各点到发射站的距离
	double* height;          //各点的高度(dem或者dsm)
	double* building;        //建筑物高度
	short* clutter;          //各点的clutter值	
	short* zones;            //路径上各个点的气候区，0：A1，沿海陆地 ；1：A2，内陆 ；2：B海洋
	double* adaptedHeight;   //考虑曲率后的高度
	double* conductivity;	 //电导率
	double* lineOfSight;     //视通情况
	double* refractionIndex0m;
	double* refractionIndex1km;  //
	double* fieldSth;         
	short* gerechnet;
	double* RainRate;
	double* diffLoss;
	//double* RainRate;
};

#endif