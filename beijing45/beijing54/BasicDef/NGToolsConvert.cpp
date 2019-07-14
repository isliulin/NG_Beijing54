#include <math.h>
#include "NGToolsConvert.h"

CNGToolsConvert::CNGToolsConvert()
{

}
CNGToolsConvert::~CNGToolsConvert()
{

}

//将dBuv转换为dBm
double CNGToolsConvert::Convert_dBuV_dBmW(double fs_dBuV, double Frequenz_Mhz)
{
	return fs_dBuV - 77.216 - 20*log10( Frequenz_Mhz );

}

//将dBm转换为dBuv
double CNGToolsConvert::Convert_dBmW_dBuV(double power_dBmW, double Frequenz_Mhz)
{
	return power_dBmW + 77.216 + 20*log10(Frequenz_Mhz);
}

//将EIRP转换为ERP  powerdBx 表示功率是对数形式的，不是自然数形式
double CNGToolsConvert::Convert_EIRP_ERP(double powerdBx)
{
	return powerdBx - 2.15;
}

//将ERP转换为EIRP
double CNGToolsConvert::Convert_ERP_EIRP(double powerdBx)
{
	return powerdBx + 2.15;
}

double CNGToolsConvert::Convert_W_dBm(double powerW)
{
	return 30 + 10*log10(powerW);
}