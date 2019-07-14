#pragma once

/************************************************************************/
// CPowerIndBm
// 功率类 用dBm表示
/************************************************************************/
class CPowerIndBm
{
public:
	CPowerIndBm(void);
	CPowerIndBm(double);
	virtual ~CPowerIndBm(void);
	// 功率值
	double	m_Value;
	// 获取功率值(单位W)
	double	GetPowerInW();
	// 设置功率值(单位W)
	bool	SetPowerInW(double inPower);
	// 获取功率(单位dBuv/m)
	double	GetPowerIndBuv(double inFreq);
	// 设置功率(单位dBuv/m)
	bool	SetPowerIndBuv(double inPower, double inFreq);
	// 转换为double型
	operator double();
	// 从double型转换
	CPowerIndBm& operator = (double inPower);


};
// 功率（单位：dBm）
typedef CPowerIndBm PowerIndBm;