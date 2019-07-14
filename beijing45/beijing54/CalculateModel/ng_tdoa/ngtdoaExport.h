#include "..\LocaltionLib\NGTDOADataStruct.h"


/*****************************************************************************
// �ļ���:		 
// ��д��:	�	  
// ��д����:2015.12	  
// ��Ҫ���� TDOA��λ�㷨�ĵ����ӿ�
// ����ĵ����ƣ�
// ����ĵ��汾��
// ����ĵ�����ID 
// �޸ļ�¼:		 
//
// (C) 2017  Ng-networks
*****************************************************************************/


#ifndef __NG_CALCULATE_EXPORT_H__
#define __NG_CALCULATE_EXPORT_H__


extern "C"
{

	//tdoa
	int NG_Localtion_Algorithm(NGIQData* datas , unsigned int num , const char* presultpath);


	int NG_Localtion_Algorithm_Point_float(NGIQData_float* datas , unsigned int num , const char* pLicenseFile,  double *x,double *y);
	//�������ƣ�NG_Localtion_Algorithm_Point
	//ԭ�����ݼ��վ�ɼ���IQ���ݣ�������λ���
	//���������datas�������վ��IQ���ݣ�˳�����У��������վ��IQ���ݸ�ʽ�μ��ṹ��NGIQData
	//          num�����붨λ�ļ��վ����
	//          pLicenseFile����Ȩlicense�ļ���
	//���������x��y�������λ������꣬WGS84����ϵ
	int NG_Localtion_Algorithm_Point(NGIQData* datas , unsigned int num , const char* pLicenseFile,  double *x,double *y);
	//ԭ���ø�����mac��ַ���ļ��еıȽ�
	//pszMac���豸Mac��ַ
	//szLicFileName: License �ļ�·��
	//����ֵ��
	int NG_CheckMacLicense(const char* pszMac, const char* pLicenseFile);


};
#endif
