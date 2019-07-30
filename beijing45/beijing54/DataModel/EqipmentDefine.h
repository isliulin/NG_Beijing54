//设备结构体定义
#ifndef __EQUIPMENT__DEFINE__H__
#define __EQUIPMENT__DEFINE__H__

#include "DataGuidDefine.h"
#include "EnumDef.h"

//电缆衰减属性
typedef struct tagEq_Cable_Attenuation
{
	double	freq_MHz;						//频率,单位:MHz
	double	attenuation;					//频率对应的衰减(db/m)
}Eq_Cable_Attenuation;

//电缆
typedef struct tagEq_Cable
{
	EMC_Base	baseInfo;					//基本信息
	double	freq_Min_MHz;					//频率下限(最小值),单位:MHz
	double	freq_Max_MHz;					//频率上限(最大值)
	int		att_Count;						//电缆衰减定义个数
	Eq_Cable_Attenuation *pAtt;				//电缆衰减数据
}Eq_Cable;

//天线极化方式
typedef struct tagEq_Antenna_Polarization
{
	int		code;							//极化方式类别
	char	szName[DATA_NAME_MAX];			//极化类别对应的名称
}Eq_Antenna_Polarization;

//天线覆型
typedef struct tagEq_Antenna_Pattern_Item
{
	double	angle;							//角度
	double	angleGain;						//角度增益
}Eq_Antenna_Pattern_Item;

typedef struct tagEq_Antenna_Pattern
{
	int		angle_Count;					//角度个数
	Eq_Antenna_Pattern_Item *pPatternItem;	//角度增益
}Eq_Antenna_Pattern;

//天线
typedef struct tagEq_Antenna
{
	EMC_Base	baseInfo;					//基本信息
	double	maxGain;						//天线最大增益
	double	electrical_tilt;				//天线电倾角
	double	freq_Min_MHz;					//工作频率下限(最小值),单位:MHz
	double	freq_Max_MHz;					//工作频率上限(最大值),单位:MHz
	int		polCode;						//极化方式类别
	double	polCrossIso;					//交叉极化隔离,单位:db
	Eq_Antenna_Pattern HPattern;			//水平方向增益
	Eq_Antenna_Pattern VPattern;			//竖直方向增益
}Eq_Antenna;

//天线模式
typedef enum AntennaModel
{
	SIMPLE_INTERPOLATION_ANT = 0, //简单插值
	HPI_ANT,
	MOMENTUM_ANT,
	OMNI_ANT,
};
//互调衰减
typedef struct tagEq_IMAttenuation
{
	double	att2;							//2 次互调衰减,单位:db
	double	att3;							//3 次互调衰减,单位:db
}Eq_IMAttenuation;

//谐波衰减
typedef struct tagEq_HarmonicmAttenuation
{
	double	att2;							//2 次谐波衰减,单位:db
	double	att3;							//3 次谐波衰减,单位:db
	double	att4;							//4 次谐波衰减,单位:db
	double	att5;							//5 次谐波衰减,单位:db
	double	att6;							//6 次谐波衰减,单位:db
	double	att7;							//7 次谐波衰减,单位:db
	double	att8;							//8 次谐波衰减,单位:db
	double	att9;							//9 次谐波衰减,单位:db
	double	att10;							//10 次谐波衰减,单位:db
	double	att11;							//11 次谐波衰减,单位:db
	double	att12;							//12 次谐波衰减,单位:db
	double	att13;							//13 次谐波衰减,单位:db
}Eq_HarmonicmAttenuation;

//镜频衰减
typedef struct tagEq_ImageFreqAttenuation
{
	double	att;							//镜频衰减,单位:db
}Eq_ImageFreqAttenuation;

//中频衰减
typedef struct tagEq_MidFreqAttenuation
{
	double	att;							//中频衰减,单位:db
}Eq_MidFreqAttenuation;

typedef enum DigitalModulationType
{
	DIGITAL_ASK, 
	DIGITAL_APK, 
	DIGITAL_FAM,
	DIGITAL_PSM,
	DIGITAL_DPSM,
	DIGITAL_MSM,
	DIGITAL_GMSM,
	DIGITAL_QAM,
	DIGITAL_OFDM
};

//数字调制方式
typedef struct tagEq_DigitalModulation
{
	DigitalModulationType type;		//调制方式
	double	modulationFactor;		//调制系数
	double	dataRate;				//数据率,单位:kbites/m
}Eq_DigitalModulation;

//频率特性
typedef struct tagEq_SpAttenuation_Item
{
	double	freq_DiffKHz;					//频率差值,单位:KHz
	double	att;							//衰减
}Eq_SpAttenuation_Item;

typedef struct tagEq_SpAttenuation
{
	int		freq_Count;						//个数
	Eq_SpAttenuation_Item *pSpAttItem;		//频率衰减
}Eq_SpAttenuation;

//发射机
typedef struct tagEq_Transmitter
{
	EMC_Base	baseInfo;					//基本信息
	double	power;							//功率,单位:dBW
	double	freq_Min_MHz;					//工作频率下限(最小值),单位:MHz
	double	freq_Max_MHz;					//工作频率上限(最大值),单位:MHz
	double	need_BandWidth;					//必要带宽
	double	occupied_Bandwidth;				//占用带宽
	bool	isDigital;						//是否为数字
	Eq_DigitalModulation digitalMod;		//数字调制
	Eq_SpAttenuation SpAtt;					//频率特性
	Eq_IMAttenuation IMAtt;					//互调衰减
	Eq_HarmonicmAttenuation harmonicAtt;	//谐波衰减
}Eq_Transmitter;

//接收机
typedef struct tagEq_Receiver
{
	EMC_Base	baseInfo;					//基本信息
	double	freq_Min_MHz;					//工作频率下限(最小值),单位:MHz
	double	freq_Max_MHz;					//工作频率上限(最大值),单位:MHz
	double	need_BandWidth;					//必要带宽
	double	impedance;						//阻抗,ohm
	double	req_Si;							//要求的信干比,db
	double	req_sn;							//50%检测概率要求的信噪比,dBm
	double	req_sn90;						//90%检测概率要求的信噪比,dBm
	double	receive_sense;					//接收灵敏度,dBm
	double	receive_sense90;				//90%接收灵敏度,dBm
	double	noise;							//噪声系数,dB
	double	process_gain;					//处理增益
	double	block_level;					//阻塞电平,dbm		jjj add 2013.8.6
	double	stray_rest_ratio;				//杂散抑制比,dbm	jjj add 2013.8.6
	bool	isDigital;						//是否为数字
	Eq_DigitalModulation digitalMod;		//数字调制
	Eq_SpAttenuation SpAtt;					//频率特性
	Eq_IMAttenuation IMAtt;					//互调衰减
	double	block_Level;					//阻塞电平,dBm
	bool	isMidFreqFixed;					//中频是否固定
	double	mid_BandWidth;					//中频带宽
	double midFreqMHz;							//中频频率
	Eq_MidFreqAttenuation midFreqAtt;		//中频衰减
	Eq_ImageFreqAttenuation ImgFreqAtt;		//镜频衰减
	ELCType locType;						//本振特征
	
}Eq_Receiver;

//滤波器
typedef struct tagEq_Filter
{
	EMC_Base	baseInfo;					//基本信息
	double	freq_Min_MHz;					//工作频率下限(最小值),单位:MHz
	double	freq_Max_MHz;					//工作频率上限(最大值),单位:MHz
	double	freq_Ref_MHz;					//参考频率,单位:MHz
	Eq_SpAttenuation SpAtt;					//频率特性
}Eq_Filter;

#endif	/* __EQUIPMENT__DEFINE__H__ */

