#ifndef __DATAMODEL_Monitor_COMPUTEPARAM_h
#define __DATAMODEL_Monitor_COMPUTEPARAM_h

#include "ComputeParam.h"
#include "EqipmentDefine.h"


typedef struct VirtualMonitorTx //虚拟发射设备
{

	float mFreqBandBeginMhz;
	float mFreqBandEndMhz;
	float mdRXEmin;//监测站的门限
	float mRXGain;//监测站接收增益
	float mVSignalHeight;
	float mVSignalEIRP;//errp
	VirtualMonitorTx()
	{
		mFreqBandBeginMhz=900;
		mFreqBandEndMhz=1800;
		mVSignalHeight=20;
		mVSignalEIRP=50;
		mdRXEmin=-100;
		mRXGain=10;
	}
}VirtualMonitorTx;



//监测站参数
typedef struct Monitor_Antenna
{	
	std::string mID;
	std::string mName;
	std::string mEquID;
  
	CGeoPoint mLocation;     //位置
	double mdAntHeightM;     //天线高度(地图之上的高度）
	double mdAntHeightASLM;  //天线的海拔高度

	double mdAzimuth;        //天线方位角
	double mdDowntilt;       //天线下倾角
	double mdFeederLossdB;   //馈线损耗
	double mdAddLossdB;      //附加损耗
    IAntennaDiagramInterface* mpAnt;//天线覆型 --如果不需要可以置为空 --回头换成一个接口的指针
	//接收灵敏度
	double mdSensedBm;

	//是否需要加一个测试的频率范围？
}Monitor_Antenna;

//监测计算结构
typedef struct Monitor_Compute_Param
{
	Monitor_Antenna mMonitorAntenna;
	Compute_Antenna mAssumeTRX;
	
	ETransModel meTransModel; //传播模型类别
	void* mpTransModelParam;   //传播模型参数	

	double mdXRes;
	double mdYRes;

	//计算类别
	ECoverResultType meResultType;

	ICalGis_MapManger* mpGisAdapter; //地图信息 --不需要时可以置为空
}Monitor_Compute_Param;

#endif
