#ifndef __DATAMODEL_RADAR_COMPUTEPARAM_h
#define __DATAMODEL_RADAR_COMPUTEPARAM_h

#include "ComputeParam.h"

//�״���㷢�����һЩ����
struct Radar_Compute_Antenna:public Compute_Antenna
{
	//��ʼ��λ��
	double mdStartAzimuth;

	//��ֹ��λ��
	double mdEndAzimuth;

	//��󸩽�
	double mdUpAngle;

	//��͸���
	double mdDownAngle;

	// ����������(���ջ����ǿ)  --50%����
	double mdRx_sensedBm;

	//����������  --90%����
	double mdRx_sense90dBm;

	// ADD BY JIE-Z@2013/07/03
	// ���ջ�����
	double m_dRecvBandwidth;

	// �״�������������Ҫ����С�����Ÿɱ�(���ջ���ظɱ�)
	double m_dMinSIR;

	// ϵͳ���
	double m_dSystemLoss;

	// �����˲����
	double m_dFilterLoss;

	// ���߼�������ʶ�����
	double m_dXPDLoss;

};

struct Radar_Compute_ParaMain:public Compute_ParaMain
{
	//����̨վ�б�
	// UPD BY JIE-Z@2013/06/19
    Radar_Compute_Antenna* mpInterfList;	

	//����̨վ����
	int mnInterfNum; 

	//��������
	double mdDetectProb;

	// ADD BY JIE-Z@2013/06/19
	// �龯����
	double mdFlaseAlarmProb;

	//Ŀ������
	double mdRCS;	

	//�����Ƿ��ǹ̶���
	bool mbFixAnt;

	Radar_Compute_ParaMain()
	{
		 mpInterfList = NULL;	

		//����̨վ����
		mnInterfNum = 0; 

		//��������
		mdDetectProb = 50;

		// ADD BY JIE-Z@2013/06/19
		// �龯����
		 mdFlaseAlarmProb = 0.01;

		//Ŀ������
		 mdRCS = 1;	

		//�����Ƿ��ǹ̶���
		mbFixAnt = false;
	}
};

#endif