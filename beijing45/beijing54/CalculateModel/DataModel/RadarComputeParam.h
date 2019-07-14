#ifndef __DATAMODEL_RADAR_COMPUTEPARAM_h
#define __DATAMODEL_RADAR_COMPUTEPARAM_h

#include "ComputeParam.h"

//雷达计算发射机的一些参数
struct Radar_Compute_Antenna:public Compute_Antenna
{
	//起始方位角
	double mdStartAzimuth;

	//终止方位角
	double mdEndAzimuth;

	//最大俯角
	double mdUpAngle;

	//最低俯角
	double mdDownAngle;

	// 接收灵敏度(接收机额定场强)  --50%概率
	double mdRx_sensedBm;

	//接收灵敏度  --90%概率
	double mdRx_sense90dBm;

	// ADD BY JIE-Z@2013/07/03
	// 接收机带宽
	double m_dRecvBandwidth;

	// 雷达正常工作所需要的最小接收信干比(接收机额定载干比)
	double m_dMinSIR;

	// 系统损耗
	double m_dSystemLoss;

	// 接收滤波损耗
	double m_dFilterLoss;

	// 天线极化方向识别损耗
	double m_dXPDLoss;

};

struct Radar_Compute_ParaMain:public Compute_ParaMain
{
	//干扰台站列表
	// UPD BY JIE-Z@2013/06/19
    Radar_Compute_Antenna* mpInterfList;	

	//干扰台站个数
	int mnInterfNum; 

	//侦听概率
	double mdDetectProb;

	// ADD BY JIE-Z@2013/06/19
	// 虚警概率
	double mdFlaseAlarmProb;

	//目标截面积
	double mdRCS;	

	//天线是否是固定的
	bool mbFixAnt;

	Radar_Compute_ParaMain()
	{
		 mpInterfList = NULL;	

		//干扰台站个数
		mnInterfNum = 0; 

		//侦听概率
		mdDetectProb = 50;

		// ADD BY JIE-Z@2013/06/19
		// 虚警概率
		 mdFlaseAlarmProb = 0.01;

		//目标截面积
		 mdRCS = 1;	

		//天线是否是固定的
		mbFixAnt = false;
	}
};

#endif