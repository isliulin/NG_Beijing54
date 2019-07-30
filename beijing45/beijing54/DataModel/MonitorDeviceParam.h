#ifndef __DATAMODEL_MONITORDEVICEPARAM_h
#define __DATAMODEL_MONITORDEVICEPARAM_h

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string>

#include "../CalGisMapWrapper/ICalGisMapManager.h"
#include "../BasicDef/GeoShape.h"
#include "../AntennaDiagram/AntennaDiagramInterface.h"
#include "../NGModelParamWrapper/ModelParamWrapperExport.h"
#include "EnumDef.h"
#include "DataGuidDefine.h"
#include "MonitoringParams.h"

//辐射源发射信号类型
enum SignalType
{
	//eUnk = 0,
	eContinueSignal = 0,  //连续信号
	ePulseSignal = 1,//脉冲信号
};

//计算优先级的方法
enum CalPriorityType
{
	eMax=0,//取最大值
	eWeihth=1//加权
};
//时间类
enum TimeType
{
	//eUnknown=0,//未知
	eUn_Cycle=0,//不重复
	eDay_Cycle=1,//按天数重复
	eWeek_Cycle=2,//按周重复
	eMonth_Cycle=3,//按月重复
	eDateless=4//无期限的工作

};


typedef struct SingleFrequency
{
	//mBeginMhz=mCenterFreqMhz-mBandMhz/2
	//mEndMhz=mCenterFreqMhz+mBandMhz/2
	float mCenterFreqMhz;//用频频率
	float mBandMhz;//用频带宽
	float mBeginMhz;//起始频率
	float mEndMhz;//终止频率

	SingleFrequency()
	{
		mCenterFreqMhz=900;
		mBandMhz=1;
	}
}SingleFrequency;

//用频计划类
typedef struct CFrequencyPlanData
{

	CFrequencyPlanData()
	{
		mBeginSeconds=0;
		mEndSeconds=0;
		mPriority=0;
	}

	std::string mID;//辐射源ID
	unsigned int       mBeginSeconds;//相对于某一时间点的时间，单位：s
	unsigned int       mEndSeconds;//相对于某一时间点的时间，单位：s
	CGeoPoint   mPoint;//经度、纬度
	int       mPriority;//0~5,0最高
	SignalType mType;//辐射源的信号类型
	SingleFrequency mFrequencys;
}CFrequencyPlanData;


//监测要求
typedef struct CMonitoringCommandData
{

	CMonitoringCommandData()
	{
		mArea=NULL;
		mBeginSeconds=0;
		mEndSeconds=0;
		mPriority=0;
		mType=(SignalType)1;
	}
	~CMonitoringCommandData()
	{
		if(mArea)delete mArea; 
	}


	CGeoPolygon *mArea;
	unsigned int       mBeginSeconds;//相对于某一时间点的时间，单位：s
	unsigned int       mEndSeconds;//相对于某一时间点的时间，单位：s
	int         mPriority;//
	//std::vector<SingleFrequency> mFrequencys;
	SingleFrequency mFrequencys;//edit by xiangl
	SignalType mType;//待监测的信号类型
}CMonitoringCommandData;

//设备的工作模式
enum MonitorWorkModel
{
	eMeasure=1,//测量
	eDirection,//测向
	eAllAround//全向扫描
};

struct _Device_Compute_Antenna:
public _Compute_Antenna_Extra
{
	SingleFrequency mFrequency;//工作的频段
	MonitorWorkModel mWorkModel;//工作模式
	//SignalType mType;//辐射源的信号类型
	int       mPriority;//进行这个工作的优先级 //0~5,0最高
	int       mBlockPrior;//能屏蔽掉该任务的优先级门限，即新任务的监测优先级必须大于(>)该门限，才能屏蔽掉该设备正在试行的工作

	_Device_Compute_Antenna()
	{
		mWorkModel=eAllAround;
		mPriority=5;
		mBlockPrior=1;
	}
};
typedef _Device_Compute_Antenna Device_Compute_Antenna;

//某点的某方向区域
typedef struct CGeoAzimuth : public CGeoPoint
{
	//CGeoPoint mpoint;
	double mdAzimuthBegin;//起始方向坐标方位角，由坐标纵轴方向的北端起，顺时针量到起始方向直线间的夹角
	double mdSpan;//跨度    0°<mdSpan<360°

	CGeoAzimuth()
	{
		mdAzimuthBegin=0;
		mdSpan=0;
	}
}CGeoAzimuth;

#endif
