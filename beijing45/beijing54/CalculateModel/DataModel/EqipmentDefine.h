//�豸�ṹ�嶨��
#ifndef __EQUIPMENT__DEFINE__H__
#define __EQUIPMENT__DEFINE__H__

#include "DataGuidDefine.h"
#include "EnumDef.h"

//����˥������
typedef struct tagEq_Cable_Attenuation
{
	double	freq_MHz;						//Ƶ��,��λ:MHz
	double	attenuation;					//Ƶ�ʶ�Ӧ��˥��(db/m)
}Eq_Cable_Attenuation;

//����
typedef struct tagEq_Cable
{
	EMC_Base	baseInfo;					//������Ϣ
	double	freq_Min_MHz;					//Ƶ������(��Сֵ),��λ:MHz
	double	freq_Max_MHz;					//Ƶ������(���ֵ)
	int		att_Count;						//����˥���������
	Eq_Cable_Attenuation *pAtt;				//����˥������
}Eq_Cable;

//���߼�����ʽ
typedef struct tagEq_Antenna_Polarization
{
	int		code;							//������ʽ���
	char	szName[DATA_NAME_MAX];			//��������Ӧ������
}Eq_Antenna_Polarization;

//���߸���
typedef struct tagEq_Antenna_Pattern_Item
{
	double	angle;							//�Ƕ�
	double	angleGain;						//�Ƕ�����
}Eq_Antenna_Pattern_Item;

typedef struct tagEq_Antenna_Pattern
{
	int		angle_Count;					//�Ƕȸ���
	Eq_Antenna_Pattern_Item *pPatternItem;	//�Ƕ�����
}Eq_Antenna_Pattern;

//����
typedef struct tagEq_Antenna
{
	EMC_Base	baseInfo;					//������Ϣ
	double	maxGain;						//�����������
	double	electrical_tilt;				//���ߵ����
	double	freq_Min_MHz;					//����Ƶ������(��Сֵ),��λ:MHz
	double	freq_Max_MHz;					//����Ƶ������(���ֵ),��λ:MHz
	int		polCode;						//������ʽ���
	double	polCrossIso;					//���漫������,��λ:db
	Eq_Antenna_Pattern HPattern;			//ˮƽ��������
	Eq_Antenna_Pattern VPattern;			//��ֱ��������
}Eq_Antenna;

//����ģʽ
typedef enum AntennaModel
{
	SIMPLE_INTERPOLATION_ANT = 0, //�򵥲�ֵ
	HPI_ANT,
	MOMENTUM_ANT,
	OMNI_ANT,
};
//����˥��
typedef struct tagEq_IMAttenuation
{
	double	att2;							//2 �λ���˥��,��λ:db
	double	att3;							//3 �λ���˥��,��λ:db
}Eq_IMAttenuation;

//г��˥��
typedef struct tagEq_HarmonicmAttenuation
{
	double	att2;							//2 ��г��˥��,��λ:db
	double	att3;							//3 ��г��˥��,��λ:db
	double	att4;							//4 ��г��˥��,��λ:db
	double	att5;							//5 ��г��˥��,��λ:db
	double	att6;							//6 ��г��˥��,��λ:db
	double	att7;							//7 ��г��˥��,��λ:db
	double	att8;							//8 ��г��˥��,��λ:db
	double	att9;							//9 ��г��˥��,��λ:db
	double	att10;							//10 ��г��˥��,��λ:db
	double	att11;							//11 ��г��˥��,��λ:db
	double	att12;							//12 ��г��˥��,��λ:db
	double	att13;							//13 ��г��˥��,��λ:db
}Eq_HarmonicmAttenuation;

//��Ƶ˥��
typedef struct tagEq_ImageFreqAttenuation
{
	double	att;							//��Ƶ˥��,��λ:db
}Eq_ImageFreqAttenuation;

//��Ƶ˥��
typedef struct tagEq_MidFreqAttenuation
{
	double	att;							//��Ƶ˥��,��λ:db
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

//���ֵ��Ʒ�ʽ
typedef struct tagEq_DigitalModulation
{
	DigitalModulationType type;		//���Ʒ�ʽ
	double	modulationFactor;		//����ϵ��
	double	dataRate;				//������,��λ:kbites/m
}Eq_DigitalModulation;

//Ƶ������
typedef struct tagEq_SpAttenuation_Item
{
	double	freq_DiffKHz;					//Ƶ�ʲ�ֵ,��λ:KHz
	double	att;							//˥��
}Eq_SpAttenuation_Item;

typedef struct tagEq_SpAttenuation
{
	int		freq_Count;						//����
	Eq_SpAttenuation_Item *pSpAttItem;		//Ƶ��˥��
}Eq_SpAttenuation;

//�����
typedef struct tagEq_Transmitter
{
	EMC_Base	baseInfo;					//������Ϣ
	double	power;							//����,��λ:dBW
	double	freq_Min_MHz;					//����Ƶ������(��Сֵ),��λ:MHz
	double	freq_Max_MHz;					//����Ƶ������(���ֵ),��λ:MHz
	double	need_BandWidth;					//��Ҫ����
	double	occupied_Bandwidth;				//ռ�ô���
	bool	isDigital;						//�Ƿ�Ϊ����
	Eq_DigitalModulation digitalMod;		//���ֵ���
	Eq_SpAttenuation SpAtt;					//Ƶ������
	Eq_IMAttenuation IMAtt;					//����˥��
	Eq_HarmonicmAttenuation harmonicAtt;	//г��˥��
}Eq_Transmitter;

//���ջ�
typedef struct tagEq_Receiver
{
	EMC_Base	baseInfo;					//������Ϣ
	double	freq_Min_MHz;					//����Ƶ������(��Сֵ),��λ:MHz
	double	freq_Max_MHz;					//����Ƶ������(���ֵ),��λ:MHz
	double	need_BandWidth;					//��Ҫ����
	double	impedance;						//�迹,ohm
	double	req_Si;							//Ҫ����Ÿɱ�,db
	double	req_sn;							//50%������Ҫ��������,dBm
	double	req_sn90;						//90%������Ҫ��������,dBm
	double	receive_sense;					//����������,dBm
	double	receive_sense90;				//90%����������,dBm
	double	noise;							//����ϵ��,dB
	double	process_gain;					//��������
	double	block_level;					//������ƽ,dbm		jjj add 2013.8.6
	double	stray_rest_ratio;				//��ɢ���Ʊ�,dbm	jjj add 2013.8.6
	bool	isDigital;						//�Ƿ�Ϊ����
	Eq_DigitalModulation digitalMod;		//���ֵ���
	Eq_SpAttenuation SpAtt;					//Ƶ������
	Eq_IMAttenuation IMAtt;					//����˥��
	double	block_Level;					//������ƽ,dBm
	bool	isMidFreqFixed;					//��Ƶ�Ƿ�̶�
	double	mid_BandWidth;					//��Ƶ����
	double midFreqMHz;							//��ƵƵ��
	Eq_MidFreqAttenuation midFreqAtt;		//��Ƶ˥��
	Eq_ImageFreqAttenuation ImgFreqAtt;		//��Ƶ˥��
	ELCType locType;						//��������
	
}Eq_Receiver;

//�˲���
typedef struct tagEq_Filter
{
	EMC_Base	baseInfo;					//������Ϣ
	double	freq_Min_MHz;					//����Ƶ������(��Сֵ),��λ:MHz
	double	freq_Max_MHz;					//����Ƶ������(���ֵ),��λ:MHz
	double	freq_Ref_MHz;					//�ο�Ƶ��,��λ:MHz
	Eq_SpAttenuation SpAtt;					//Ƶ������
}Eq_Filter;

#endif	/* __EQUIPMENT__DEFINE__H__ */

