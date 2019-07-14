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

// 获取功率值(单位W)
double	CPowerIndBm::GetPowerInW()
{
	// 从dBm转换为W
	return pow(10.0, (m_Value - 30.0) / 10.0);
}

// 设置功率值(单位W)
bool	CPowerIndBm::SetPowerInW(double inPower)
{
	// dBm = 30 + 10log(W)
	m_Value = 30.0 + 10.0 * log10(inPower);
	return true;
}

/************************************************************************/
// 获取功率(单位dBμv/m)
// 参数：double inFreq：频率
/************************************************************************/
double	CPowerIndBm::GetPowerIndBuv(double inFreq)
{
	// dBμv/m = dBm + 77.216 + 20log(f)
	return m_Value + 77.216 + 20 * log10(inFreq);
}

/************************************************************************/
// 设置功率值(单位dBμv/m)
// 参数：double inFreq：频率
/************************************************************************/
bool	CPowerIndBm::SetPowerIndBuv(double inPower, double inFreq)
{
	m_Value = inPower - 77.216 - 20 * log10(inFreq);
	return true;
}

// 转换为double型
CPowerIndBm::operator double()
{
	return m_Value;
}

// 从double型转换
CPowerIndBm& CPowerIndBm::operator = (double inPower)
{
	this->m_Value = inPower;
	return *this;
}