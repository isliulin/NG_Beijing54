#ifndef __DATAMODEL_Monitor_COMPUTEPARAM_h
#define __DATAMODEL_Monitor_COMPUTEPARAM_h

#include "ComputeParam.h"
#include "EqipmentDefine.h"


typedef struct VirtualMonitorTx //���ⷢ���豸
{

	float mFreqBandBeginMhz;
	float mFreqBandEndMhz;
	float mdRXEmin;//���վ������
	float mRXGain;//���վ��������
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



//���վ����
typedef struct Monitor_Antenna
{	
	std::string mID;
	std::string mName;
	std::string mEquID;
  
	CGeoPoint mLocation;     //λ��
	double mdAntHeightM;     //���߸߶�(��ͼ֮�ϵĸ߶ȣ�
	double mdAntHeightASLM;  //���ߵĺ��θ߶�

	double mdAzimuth;        //���߷�λ��
	double mdDowntilt;       //���������
	double mdFeederLossdB;   //�������
	double mdAddLossdB;      //�������
    IAntennaDiagramInterface* mpAnt;//���߸��� --�������Ҫ������Ϊ�� --��ͷ����һ���ӿڵ�ָ��
	//����������
	double mdSensedBm;

	//�Ƿ���Ҫ��һ�����Ե�Ƶ�ʷ�Χ��
}Monitor_Antenna;

//������ṹ
typedef struct Monitor_Compute_Param
{
	Monitor_Antenna mMonitorAntenna;
	Compute_Antenna mAssumeTRX;
	
	ETransModel meTransModel; //����ģ�����
	void* mpTransModelParam;   //����ģ�Ͳ���	

	double mdXRes;
	double mdYRes;

	//�������
	ECoverResultType meResultType;

	ICalGis_MapManger* mpGisAdapter; //��ͼ��Ϣ --����Ҫʱ������Ϊ��
}Monitor_Compute_Param;

#endif
