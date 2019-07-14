#ifndef __DATAMODEL_COMPUTEPARAM_h
#define __DATAMODEL_COMPUTEPARAM_h

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

//发射天线的参数信息 ---有时候其实是个链路，如果不是链路，只是发射机，则忽略接收机方面的信息
typedef struct _Compute_Antenna
{
	//添加一个默认的构造析构函数
	_Compute_Antenna()
	{
		mdAntHeightM = 0.0;
		mdAntHeightASLM = 0.0;
		mdFreqMhz = 802.0;

		mdPowerdBm = 70;
		mePowerMode = eEIRP;
		mdAzimuth = 0.0;
		mdDowntilt = 0.0;
		mdStartAzimuth = 0;
		mdEndAzimuth = 0 ;
		mdUpAngle = 0 ;
		mdDownAngle = 0 ;
		mdGaindBi = 0.0;
		mdFeederLossdB = 0.0;
		mdAddLossdB = 0.0;
		mpAntPattern = NULL;
		mdBandwidthHz = 500000;

		mLocation.m_nCoordSys = 103;
		mLocation.m_Point.x = 0;
		mLocation.m_Point.y = 0;
		mLocation.m_Point.z = 0;

		mdRXGaindBi = 0.0;
		mdThresholddBm = -110;//默认值
		mdRXBandwidthMHz = 0.5;
		mdRXAzimuth = 0.0;
		mdRXDowntilt = 0.0;
		mdRXAddLossdB = 0.0;
		mpRXAntPattern = NULL;
		mRXLocation.m_nCoordSys = 0;
		mRXLocation.m_Point.x = 0;
		mRXLocation.m_Point.y = 0;
		mRXLocation.m_Point.z = 0;
		mdMidFreqMhz = 10.7;
		meLCType = eBothLC;
	}

	virtual ~_Compute_Antenna()
	{

	}
	//发射台站的类别
	EStationType meStationType;

    //计算Pathloss需要的参数
	CGeoPoint mLocation;  //天线位置
	double mdAntHeightM;     //天线高度(地图之上的高度）
	double mdAntHeightASLM;  //天线的海拔高度
	double mdFreqMhz;        //频率

	//计算场强需要的参数
	double mdPowerdBm;       //发射功率
	EPowerType mePowerMode;         //(0 = output PA, 1 = EIRP, 2 = ERP)
	double mdAzimuth;        //天线方位角
	double mdDowntilt;       //天线下倾角
	double mdGaindBi;        //天线增益
	double mdFeederLossdB;   //馈线损耗
	double mdAddLossdB;      //附加损耗
	IAntennaDiagramInterface* mpAntPattern;  //天线覆型 --如果不需要可以置为空 --回头换成一个接口的指针
	//计算频谱功率通量密度需要的参数
	//发射带宽
	double mdBandwidthHz;

	//接收端的参数
	//计算接收功率和功率通量密度另外需要的参数
	//接收天线的增益
	double mdRXGaindBi;
	//接收门限
	double mdThresholddBm;
	//接收带宽
	double mdRXBandwidthMHz;
	double mdRXAzimuth;        //接收天线方位角
	double mdRXDowntilt;       //接收天线下倾角

	//起始方位角；边界协调中雷达类型协调站需要使用
	double mdStartAzimuth;
	//终止方位角
	double mdEndAzimuth;
	//最大俯角
	double mdUpAngle;
	//最低俯角
	double mdDownAngle;

	double mdRXAddLossdB;      //接收设备的附加损耗
	CGeoPoint mRXLocation;  //天线位置
	//接收天线的覆型
	IAntennaDiagramInterface* mpRXAntPattern;
	double	mdstray_rest_ratio; //杂散抑制比
	double mdBlockLevel;        //阻塞电平
	double mdmidFreqAtt;//中频衰减
	double mdmid_BandWidthKHz;//中频带宽
	double mdMidFreqMhz;//中频频率
	double mdImgFreqAtt;//镜频衰减
	ELCType meLCType;//本振特征
	bool bMidFreqFixed;//中频是否固定
}Compute_Antenna;


//时间片
typedef struct _Timeslice
{
 struct tm mBegin;
 time_t    mDurationSec;
 _Timeslice()
 {
   mDurationSec=0;
 }
}Timeslice;



typedef struct _Work_Time
{

 std::vector<Timeslice> mTimeLice;
 
 _Work_Time()
 {
  
 }
 

}Work_Time;


struct _Compute_Antenna_Extra:
public _Compute_Antenna
{
	EMC_Base	baseInfo;					//基本信息
	int equip_no;
	double* m_pdHarmAtt;
	Work_Time mTimes;
	_Compute_Antenna_Extra()
	{
		m_pdHarmAtt = NULL;
		equip_no = 0;
	}
	virtual ~_Compute_Antenna_Extra()
	{
		if (m_pdHarmAtt != NULL)
		{
			delete []m_pdHarmAtt;
			m_pdHarmAtt = NULL;
		}
	}
	bool CreateHarmAtt(int nHarmNum)
	{
		if(m_pdHarmAtt!=NULL)
			delete []m_pdHarmAtt;
		m_pdHarmAtt = NULL;
		if (nHarmNum >0)
		{
			if (m_pdHarmAtt != NULL)
			{
				delete []m_pdHarmAtt;
				m_pdHarmAtt = NULL;
			}
			m_pdHarmAtt = new double[nHarmNum];
			for(int i=0;i<nHarmNum;i++)
				m_pdHarmAtt[i]= 200;
			return true;
		}
		else
		{
			return false;
		}
	}
};
typedef _Compute_Antenna_Extra Compute_Antenna_Extra;
typedef struct _Compute_Station
{
	std::string mID;
	std::string mName;
    Compute_Antenna *mpComputeAntenna;
   _Compute_Station()
   {
     mpComputeAntenna=0;
   }

}Compute_Station;

typedef struct _Compute_ParaMain
{
	_Compute_ParaMain()
	{
		mdRXHeightM = 0.0;
		meHeightType = eAGroundL;

		meSpaceType = e2D;
		meResultType = ePathloss;

		meLocationType = eOnGround;

		mdXRes = 1;
		mdYRes = 1;

		meTransModel = eFreeSpace;
		mpTransModelParam = NULL;

		mpGisAdapter = NULL;
		mpClutter = NULL;
	}
	virtual ~_Compute_ParaMain()
	{

	}
	double mdRXHeightM;     //接收天线高度
	EHeightType meHeightType;       //接收天线高度类别--海拔，地面以上，建筑物以上

	ESpaceType meSpaceType;  //计算空间类别：2D,3D

	ELocationType meLocationType;  //台站的位置类别

	ECoverResultType meResultType; //结果类别 --path loss, field, power, 等

	double mdXRes;  //分辨率,单位m
	double mdYRes;  //垂直方向分辨率,单位m

	ETransModel meTransModel; //传播模型类别
    void* mpTransModelParam;   //传播模型参数

	ScmClutter* mpClutter;    //地貌的相关参数，包含地貌的高度，地貌的损耗等

	ICalGis_MapManger* mpGisAdapter; //地图信息 --不需要时可以置为空
}Compute_ParaMain;

typedef struct _ShortWave_Freq
{
	_ShortWave_Freq()
	{
		mnYear = 2013;
		mnMonth = 1;
		memset(mpBMUF, 0, 24*sizeof(float));
		memset(mpBLUF, 0, 24*sizeof(float));
		memset(mpOperMUF, 0, 24*sizeof(float));
		memset(mpOptMUF, 0, 24*sizeof(float));
	}
	int mnYear;         //年
	int mnMonth;        //月份
	float mpBMUF[24];   //基本最大可用频率数组 24个小时
	float mpBLUF[24];   //最小可用频率数组 24个小时
	float mpOperMUF[24];//工作最大可用频率数组 24个小时
	float mpOptMUF[24]; //最优工作频率 24个小时
}ShortWave_Freq;

typedef struct _RX_Antenna
{
	//接收天线的增益
	double mdGaindBi;
	//接收门限
	double mdThresholddBm;
	//接收机容忍的信噪比
	double mdSNThresholddB;
	//接收频率
	double mdFreqMhz;
	//接收带宽
	double mdBandwidthMHz;
	//接收天线方位角
	double mdAzimuth;
	//接收天线下倾角
	double mdDowntilt;
	//接收设备的附加损耗
	double mdAddLossdB;
	//接收天线的高度
	double mdAntHeightM;
	//天线位置
	CGeoPoint mLocation;
	//接收天线的覆型
	IAntennaDiagramInterface* mpAntPattern;
}RX_Antenna;

typedef struct _Rx_Station:public RX_Antenna
{
	std::string mID;//台站ID
	std::string mEquID; //设备ID
	std::string mStationName;//台站名称
    std::string mNET_TS;//技术体制
   _Rx_Station()
   {

   }
}Rx_Station;

typedef struct _InterModulation_Param
{
	//互调阶数
	int mnOrder;
	//最大考虑的限制距离
	double mdMaxDistance;
	//最大考虑的频率差值
	double mdFreqDiffKhz;
	//门限
	double mdThresholddBm;
}InterModulationParam;

// typedef struct Compute_Antenna_APPLY : public Compute_Antenna_Extra
// {	
// 	string mAuthor;
// 	string mApplyDepartment;
// 	string mApplyTime;
// 	Compute_Antenna_APPLY()
// 	{
// 
// 	}
// 	virtual ~Compute_Antenna_APPLY()
// 	{
// 
// 	}
// }Compute_Antenna_APPLY;

#endif
