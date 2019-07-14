/*
2013.3.13 jjj
�����ͼ������,֧�ֶ�ֱ��ʵ�ͼ(��������ͼ)
	�����ͼ�������ӿ���Ҫ���㷨�ṩ����ʹ�õĵ�������(�߶�����,��ò
����,�絼������,�˿ڷֲ����ݵ�)

	����Ҫ�Ľӿ���GetProfile,��ȡ�����ϵ����е�ĵ�������
	�����ͼ�ж�ֱ���,�����֮ǰ���Ե���SetActiveCalLayer���趨����
ʹ�õķֱ���,Ĭ�������ʹ�õ������ֵ�ͼ�Ļ����ֱ���

	������1����ͼ�ֱ�������2��
	��������ֱ��� Ϊ 20 m
		level0:	20m		=	20m*1		= 20*2<<0
		level1:	40m		=	20m*2		= level0*2<<1
		level2:	80m		=	level1*2	= level0*2<<2
		level3:	160m	=	level2*2	= level0*2<<3
		level4:	320m	=	level3*2	= level0*2<<4
		level5:	640m	=	level4*2	= level0*2<<5
		etc...

	�����Ҫ��ȡĳ��ͼ��ĵ�ͼ����,����
		bool SetActiveCalLayer(unsigned int lay)����,���в��� lay:
		lay = 0		-->�����ֱ��ʵ�ͼ,level0
		lay = 1		-->�����ֱ��ʵ�ͼ,level1
		lay = 2		-->�����ֱ��ʵ�ͼ,level2
		etc...

2013.3.13	v1.0

*/
#ifndef __I__CAL__GIS_MANAGER__H__
#define __I__CAL__GIS_MANAGER__H__

#include "CalGisProfile.h"

/*
	����ʹ�õ�ͼ������
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

	//�����ͼ���
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

	//�����ͼ����:dsm,dem,dhm,dom,pop,con,����ʹ�õ�ͼ����
	virtual bool SetCalMapFilePath(CalMapType mapType,const char *pFilePath)=0;
	//��ȡ�����ͼ·��
	virtual const char *GetCalMapFilePath(CalMapType mapType)=0;
	virtual const bool HasMapType(CalMapType mapType) = 0;
	virtual void DeleteCalMap(CalMapType mapType)=0;
	virtual void DeleteAllCalMap()=0;						//ɾ����ͼ
	virtual void ReleaseCalMapData(CalMapType mapType)=0;	//���ͷŵ�ͼ�ڴ�����
	virtual void ReleaseAllCalMapData()=0;

	//����ʱ����ѡ��ͬ�ֱ��ʵĵ�ͼ
	virtual unsigned int GetCalLayers()=0;					//��ȡ����������
	virtual bool SetActiveCalLayer(unsigned int lay)=0;		//���ûͼ��
	virtual unsigned int GetActiveCalLayer()=0;

	//��ȡ��ͼ���е�һЩ��Ϣ 
	virtual short GetMapCoordSys()=0;						//����ϵ���
	virtual long GetMapWidth()=0;							//��ȡ���
	virtual long GetMapHeight()=0;							//��ȡ�߶�
	virtual double GetResolutionX()=0;						//��ȡˮƽ����
	virtual double GetResolutionY()=0;						//��ȡ��ֱ���򾫶�
	virtual double GetMapLowerLeftXCoord()=0;				//��ͼ���½����� 
	virtual double GetMapLowerLeftYCoord()=0;

	//profile ��غ���		
	//��������������Ҫ�Ľ�
	virtual CalGis_Profile* GetProfile(long xBegin, long yBegin, long xEnd, long yEnd,CalGis_Profile *pProfile)=0;

	//ָ����ȡ��profile�����
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType,CalGis_Profile *pProfile)=0;
	//��ȡָ���ֱ��ʵ�profile,profile��������������ƽ�������ȡ��Ӧ�����棬����ָ���ķֱ���
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType, 
		double xRes, double yRes, CalGis_Profile *pProfile) = 0;
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType, int noPoints,CalGis_Profile *pProfile)=0;

	//��ͼ�߶�ֵ��ȡ
	virtual short GetTopoValue(long x, long y)=0;			//��ȡ����ͼ�ĸ߶�
	virtual short GetDsmHeight(long x, long y)=0;			//��ȡ�������潨����͵��εĸ߶�ֵ
	virtual short GetDemHeight(long x, long y)=0;			//��ȡ���εĸ߶�ֵ
	virtual short GetClutterValue(long x, long y) = 0;

	virtual short GetTopoValue(double x, double y)=0;			//��ȡ����ͼ�ĸ߶�
	virtual short GetDemHeight(double x, double y)=0;			//��ȡ����ͼ�ĸ߶�
	
	//�ж�x,yλ�ô���ֵ�Ƿ�����Чֵ
	virtual bool isInvalidValue(double x, double y, int CoordSys)=0;

	//�жϸ����ĵ��Ƿ��ڵ�ͼ����
	virtual bool IsPointOutofMap(long xPoint, long yPoint, long nCoordSys)=0;
	//�жϸ����ĵ��Ƿ��ڵ�ͼ����
	virtual bool IsPointOutofMap(double xPoint, double yPoint, long nCoordSys)=0;

	//����ת������
	//��ȡ���ڵ�ͼ���������
	virtual bool GetMapCoordinate(double xPoint, double yPoint, int nCoordSys, long& xOut, long& yOut)=0;
	//��ȡ���ͼ����ϵ��ͬ������
	virtual bool GetMapCoordinate(double xPoint, double yPoint, int nCoordSys, double& xOut, double& yOut)=0;
	//���ݵ�ͼ����������ȡ��Ӧ����ϵ������
	virtual bool GetCoordinateFromMap(long xPoint, long yPoint, double& xOut, double& yOut, int nCoordSys)=0;
	//����ת��
	virtual bool MapCoordTrans(long fromSys, long toSys, double fromX, double fromY,double *toX,  double *toY)=0;

};
 
extern "C"  GISMAP_API ICalGis_MapManger *NG_Create_CalGisMapManger();				//������ͼ����������
extern "C"  GISMAP_API void NG_Release_CalGisMapManger(ICalGis_MapManger *PMap);	//�ͷŵ�ͼ����������

#endif