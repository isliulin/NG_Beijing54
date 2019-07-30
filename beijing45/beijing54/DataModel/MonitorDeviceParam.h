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

//����Դ�����ź�����
enum SignalType
{
	//eUnk = 0,
	eContinueSignal = 0,  //�����ź�
	ePulseSignal = 1,//�����ź�
};

//�������ȼ��ķ���
enum CalPriorityType
{
	eMax=0,//ȡ���ֵ
	eWeihth=1//��Ȩ
};
//ʱ����
enum TimeType
{
	//eUnknown=0,//δ֪
	eUn_Cycle=0,//���ظ�
	eDay_Cycle=1,//�������ظ�
	eWeek_Cycle=2,//�����ظ�
	eMonth_Cycle=3,//�����ظ�
	eDateless=4//�����޵Ĺ���

};


typedef struct SingleFrequency
{
	//mBeginMhz=mCenterFreqMhz-mBandMhz/2
	//mEndMhz=mCenterFreqMhz+mBandMhz/2
	float mCenterFreqMhz;//��ƵƵ��
	float mBandMhz;//��Ƶ����
	float mBeginMhz;//��ʼƵ��
	float mEndMhz;//��ֹƵ��

	SingleFrequency()
	{
		mCenterFreqMhz=900;
		mBandMhz=1;
	}
}SingleFrequency;

//��Ƶ�ƻ���
typedef struct CFrequencyPlanData
{

	CFrequencyPlanData()
	{
		mBeginSeconds=0;
		mEndSeconds=0;
		mPriority=0;
	}

	std::string mID;//����ԴID
	unsigned int       mBeginSeconds;//�����ĳһʱ����ʱ�䣬��λ��s
	unsigned int       mEndSeconds;//�����ĳһʱ����ʱ�䣬��λ��s
	CGeoPoint   mPoint;//���ȡ�γ��
	int       mPriority;//0~5,0���
	SignalType mType;//����Դ���ź�����
	SingleFrequency mFrequencys;
}CFrequencyPlanData;


//���Ҫ��
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
	unsigned int       mBeginSeconds;//�����ĳһʱ����ʱ�䣬��λ��s
	unsigned int       mEndSeconds;//�����ĳһʱ����ʱ�䣬��λ��s
	int         mPriority;//
	//std::vector<SingleFrequency> mFrequencys;
	SingleFrequency mFrequencys;//edit by xiangl
	SignalType mType;//�������ź�����
}CMonitoringCommandData;

//�豸�Ĺ���ģʽ
enum MonitorWorkModel
{
	eMeasure=1,//����
	eDirection,//����
	eAllAround//ȫ��ɨ��
};

struct _Device_Compute_Antenna:
public _Compute_Antenna_Extra
{
	SingleFrequency mFrequency;//������Ƶ��
	MonitorWorkModel mWorkModel;//����ģʽ
	//SignalType mType;//����Դ���ź�����
	int       mPriority;//����������������ȼ� //0~5,0���
	int       mBlockPrior;//�����ε�����������ȼ����ޣ���������ļ�����ȼ��������(>)�����ޣ��������ε����豸�������еĹ���

	_Device_Compute_Antenna()
	{
		mWorkModel=eAllAround;
		mPriority=5;
		mBlockPrior=1;
	}
};
typedef _Device_Compute_Antenna Device_Compute_Antenna;

//ĳ���ĳ��������
typedef struct CGeoAzimuth : public CGeoPoint
{
	//CGeoPoint mpoint;
	double mdAzimuthBegin;//��ʼ�������귽λ�ǣ����������᷽��ı�����˳ʱ��������ʼ����ֱ�߼�ļн�
	double mdSpan;//���    0��<mdSpan<360��

	CGeoAzimuth()
	{
		mdAzimuthBegin=0;
		mdSpan=0;
	}
}CGeoAzimuth;

#endif
