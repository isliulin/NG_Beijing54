
#pragma once

#include <string>
#include "DataTypes.h"
#include "PowerIndBm.h"
#include "GeoShape.h"


class CellDescBase 
{
  public:

	  inline CellDescBase(){m_RadiusIndex=0;mPCI=0;m_AntennaGain = 0;}
   //! free allocated memory
	  inline virtual ~CellDescBase(){}

   virtual  float GetCenterFreqMHz();


 public:

	//����������Ϣ
 	//С��cellid
 	std::string m_CID;
 	//��Ƶ�ŵ���
 	int m_channelNo;
	//��Ƶ��
	int m_carrierNum;
	// ˮƽ��λ��
	AngleInDeg	m_aglAzimuth;
	// ��е�����
	AngleInDeg	m_aglMechaniclTilt;
	// �������
	AngleInDeg  m_aglElectriclTilt;
	//�����=��е�����+�������
	AngleInDeg  m_aglTilt;
	// ��Ƶ���� gsm ���ݿ���erp, td, lte��output
    PowerIndBm	m_pilotPower;
	//TRX power+AtennaGain
	PowerIndBm  m_erp;
	// ����书��
	PowerIndBm	m_maxTransPower;
	// ���߸߶�
    float		m_dHeight;
	//��γ����Ϣ
	CGeoPoint   m_coord;
    //�����ͺ�
	std::string m_antennaType;

	//����Ƶ��
	float m_frequency;
	//���Ĵ���
	float m_bandwidth;
	//CCCHƵ����
	int m_CCCHChannelNum;
	//�������
	int m_AntennaGain;	//  2 gsm,3 td,4 lte
	int  m_netType;
	//���ز����
	int m_numScs;
	int  m_RadiusIndex;//0������,1�س�,2ũ��
	
	//ϵͳ����
	std::string m_SystemType;
	//���õ���Ϣ
	std::string m_CellName;//С������
	std::string m_SiteName;//��վ����
	std::string m_SiteID;//��վվ��
	std::string m_City;//��������
	std::string m_CellularType;//��������
	int mPCI;

};



















