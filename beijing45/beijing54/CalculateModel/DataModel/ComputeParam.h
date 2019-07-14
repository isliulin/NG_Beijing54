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

//�������ߵĲ�����Ϣ ---��ʱ����ʵ�Ǹ���·�����������·��ֻ�Ƿ����������Խ��ջ��������Ϣ
typedef struct _Compute_Antenna
{
	//���һ��Ĭ�ϵĹ�����������
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
		mdThresholddBm = -110;//Ĭ��ֵ
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
	//����̨վ�����
	EStationType meStationType;

    //����Pathloss��Ҫ�Ĳ���
	CGeoPoint mLocation;  //����λ��
	double mdAntHeightM;     //���߸߶�(��ͼ֮�ϵĸ߶ȣ�
	double mdAntHeightASLM;  //���ߵĺ��θ߶�
	double mdFreqMhz;        //Ƶ��

	//���㳡ǿ��Ҫ�Ĳ���
	double mdPowerdBm;       //���书��
	EPowerType mePowerMode;         //(0 = output PA, 1 = EIRP, 2 = ERP)
	double mdAzimuth;        //���߷�λ��
	double mdDowntilt;       //���������
	double mdGaindBi;        //��������
	double mdFeederLossdB;   //�������
	double mdAddLossdB;      //�������
	IAntennaDiagramInterface* mpAntPattern;  //���߸��� --�������Ҫ������Ϊ�� --��ͷ����һ���ӿڵ�ָ��
	//����Ƶ�׹���ͨ���ܶ���Ҫ�Ĳ���
	//�������
	double mdBandwidthHz;

	//���ն˵Ĳ���
	//������չ��ʺ͹���ͨ���ܶ�������Ҫ�Ĳ���
	//�������ߵ�����
	double mdRXGaindBi;
	//��������
	double mdThresholddBm;
	//���մ���
	double mdRXBandwidthMHz;
	double mdRXAzimuth;        //�������߷�λ��
	double mdRXDowntilt;       //�������������

	//��ʼ��λ�ǣ��߽�Э�����״�����Э��վ��Ҫʹ��
	double mdStartAzimuth;
	//��ֹ��λ��
	double mdEndAzimuth;
	//��󸩽�
	double mdUpAngle;
	//��͸���
	double mdDownAngle;

	double mdRXAddLossdB;      //�����豸�ĸ������
	CGeoPoint mRXLocation;  //����λ��
	//�������ߵĸ���
	IAntennaDiagramInterface* mpRXAntPattern;
	double	mdstray_rest_ratio; //��ɢ���Ʊ�
	double mdBlockLevel;        //������ƽ
	double mdmidFreqAtt;//��Ƶ˥��
	double mdmid_BandWidthKHz;//��Ƶ����
	double mdMidFreqMhz;//��ƵƵ��
	double mdImgFreqAtt;//��Ƶ˥��
	ELCType meLCType;//��������
	bool bMidFreqFixed;//��Ƶ�Ƿ�̶�
}Compute_Antenna;


//ʱ��Ƭ
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
	EMC_Base	baseInfo;					//������Ϣ
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
	double mdRXHeightM;     //�������߸߶�
	EHeightType meHeightType;       //�������߸߶����--���Σ��������ϣ�����������

	ESpaceType meSpaceType;  //����ռ����2D,3D

	ELocationType meLocationType;  //̨վ��λ�����

	ECoverResultType meResultType; //������ --path loss, field, power, ��

	double mdXRes;  //�ֱ���,��λm
	double mdYRes;  //��ֱ����ֱ���,��λm

	ETransModel meTransModel; //����ģ�����
    void* mpTransModelParam;   //����ģ�Ͳ���

	ScmClutter* mpClutter;    //��ò����ز�����������ò�ĸ߶ȣ���ò����ĵ�

	ICalGis_MapManger* mpGisAdapter; //��ͼ��Ϣ --����Ҫʱ������Ϊ��
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
	int mnYear;         //��
	int mnMonth;        //�·�
	float mpBMUF[24];   //����������Ƶ������ 24��Сʱ
	float mpBLUF[24];   //��С����Ƶ������ 24��Сʱ
	float mpOperMUF[24];//����������Ƶ������ 24��Сʱ
	float mpOptMUF[24]; //���Ź���Ƶ�� 24��Сʱ
}ShortWave_Freq;

typedef struct _RX_Antenna
{
	//�������ߵ�����
	double mdGaindBi;
	//��������
	double mdThresholddBm;
	//���ջ����̵������
	double mdSNThresholddB;
	//����Ƶ��
	double mdFreqMhz;
	//���մ���
	double mdBandwidthMHz;
	//�������߷�λ��
	double mdAzimuth;
	//�������������
	double mdDowntilt;
	//�����豸�ĸ������
	double mdAddLossdB;
	//�������ߵĸ߶�
	double mdAntHeightM;
	//����λ��
	CGeoPoint mLocation;
	//�������ߵĸ���
	IAntennaDiagramInterface* mpAntPattern;
}RX_Antenna;

typedef struct _Rx_Station:public RX_Antenna
{
	std::string mID;//̨վID
	std::string mEquID; //�豸ID
	std::string mStationName;//̨վ����
    std::string mNET_TS;//��������
   _Rx_Station()
   {

   }
}Rx_Station;

typedef struct _InterModulation_Param
{
	//��������
	int mnOrder;
	//����ǵ����ƾ���
	double mdMaxDistance;
	//����ǵ�Ƶ�ʲ�ֵ
	double mdFreqDiffKhz;
	//����
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
