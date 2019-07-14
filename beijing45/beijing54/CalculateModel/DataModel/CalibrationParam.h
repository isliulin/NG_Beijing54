#ifndef __DATAMODEL_CALIBRATIONPARAM_h
#define __DATAMODEL_CALIBRATIONPARAM_h

#include "ComputeParam.h"

//�������ݽṹ
struct ScmDriveTestData
{
	//���Ե㾭��
	double mdX;
	//���Ե�γ��
	double mdY;
	//���Ե��ź�ֵ --�����ǳ�ǿ�����ʵ�
	double mdValue;
};

//����ģ����������
struct ScmCalibrationParam
{
	//�������ݵķ��������
	Compute_Antenna* mpComputeAntenna;

	//�������ݵĽ��ջ�����
	RX_Antenna* mpRXAntenna;

	//��ͼ����
	ICalGis_MapManger* mpGisAdapter;

	//����������� -��ǿ����ƽ��
	ECoverResultType meDriveTestType;

	//��������λ�õ�����ϵ
	int mnCoordSys;

	//������������
	std::vector<ScmDriveTestData> mvDriveTestDatas;
};

#endif