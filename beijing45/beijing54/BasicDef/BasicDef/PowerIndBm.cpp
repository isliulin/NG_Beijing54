#include "StdAfx.h"
#include "PowerIndBm.h"
#include <math.h>

CPowerIndBm::CPowerIndBm(void)
: m_Value(0.0)
{
}

CPowerIndBm::CPowerIndBm(double inPower)
: m_Value(inPower)
{	
}

CPowerIndBm::~CPowerIndBm(void)
{
}

// ��ȡ����ֵ(��λW)
double	CPowerIndBm::GetPowerInW()
{
	// ��dBmת��ΪW
	return pow(10.0, (m_Value - 30.0) / 10.0);
}

// ���ù���ֵ(��λW)
bool	CPowerIndBm::SetPowerInW(double inPower)
{
	// dBm = 30 + 10log(W)
	m_Value = 30.0 + 10.0 * log10(inPower);
	return true;
}

/************************************************************************/
// ��ȡ����(��λdB��v/m)
// ������double inFreq��Ƶ��
/************************************************************************/
double	CPowerIndBm::GetPowerIndBuv(double inFreq)
{
	// dB��v/m = dBm + 77.216 + 20log(f)
	return m_Value + 77.216 + 20 * log10(inFreq);
}

/************************************************************************/
// ���ù���ֵ(��λdB��v/m)
// ������double inFreq��Ƶ��
/************************************************************************/
bool	CPowerIndBm::SetPowerIndBuv(double inPower, double inFreq)
{
	m_Value = inPower - 77.216 - 20 * log10(inFreq);
	return true;
}

// ת��Ϊdouble��
CPowerIndBm::operator double()
{
	return m_Value;
}

// ��double��ת��
CPowerIndBm& CPowerIndBm::operator = (double inPower)
{
	this->m_Value = inPower;
	return *this;
}