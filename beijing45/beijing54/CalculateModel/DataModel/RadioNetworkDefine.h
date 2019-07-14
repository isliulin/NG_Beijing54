//网络结构体定义
#ifndef __RADIO__NETWORK__DEFINE__H__
#define __RADIO__NETWORK__DEFINE__H__

#include "DataGuidDefine.h"

/*
网络
一个网络包含一到多个台站,这些台站在同一时刻只能有一个台站在发射或接收信号,
这样,一个网络内部的台站不会存在干扰
一个网络内部的台站使用相同的频率,一个网络的主要数据包含:
	网络级别
	网络内的所有台站id
	主控台站id
	主发射频率,主接收频率
	备用发射频率,备用接收频率
*/
typedef struct tagRN_RadioNetwork
{
	EMC_Base	baseInfo;					//基本信息
	EMC_DATA_GUID	masterStationInNetId;	//主控站id
	bool	isTemplate;						//是否为模板网络
	bool	isPrioritised;					//是否优先的
	bool	useMainFrequencies;				//是否使用主频率
	double	mainHailingTxFq;				//主发射频率
	double	mainHailingRxFq;				//主接收频率
	double	reserveHailingTxFq;				//备用发射频率
	double	reserveHailingRxFq;				//备用接收频率
	double	frequencyBandStartTxFq;			//发射频率下限
	double	frequencyBandStopTxFq;			//发射频率上限
	double	frequencyBandStartRxFq;			//接收频率下限
	double	frequencyBandStopRxFq;			//接收频率上限
	int		stationClassCount;				//网络兼容台站类别个数
	EMC_DATA_GUID StationClassId;			//台站类别指针
	int		stationCount;					//此网络内的所有台站
	EMC_DATA_GUID *pStatinId;				//台站id
}RN_RadioNetwork;


#endif	/* __RADIO__NETWORK__DEFINE__H__ */