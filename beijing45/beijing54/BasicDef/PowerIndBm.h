#pragma once

/************************************************************************/
// CPowerIndBm
// ������ ��dBm��ʾ
/************************************************************************/
class CPowerIndBm
{
public:
	CPowerIndBm(void);
	CPowerIndBm(double);
	virtual ~CPowerIndBm(void);
	// ����ֵ
	double	m_Value;
	// ��ȡ����ֵ(��λW)
	double	GetPowerInW();
	// ���ù���ֵ(��λW)
	bool	SetPowerInW(double inPower);
	// ��ȡ����(��λdBuv/m)
	double	GetPowerIndBuv(double inFreq);
	// ���ù���(��λdBuv/m)
	bool	SetPowerIndBuv(double inPower, double inFreq);
	// ת��Ϊdouble��
	operator double();
	// ��double��ת��
	CPowerIndBm& operator = (double inPower);


};
// ���ʣ���λ��dBm��
typedef CPowerIndBm PowerIndBm;