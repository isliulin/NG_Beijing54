#include <math.h>
#include "NGToolsConvert.h"

CNGToolsConvert::CNGToolsConvert()
{

}
CNGToolsConvert::~CNGToolsConvert()
{

}

//��dBuvת��ΪdBm
double CNGToolsConvert::Convert_dBuV_dBmW(double fs_dBuV, double Frequenz_Mhz)
{
	return fs_dBuV - 77.216 - 20*log10( Frequenz_Mhz );

}

//��dBmת��ΪdBuv
double CNGToolsConvert::Convert_dBmW_dBuV(double power_dBmW, double Frequenz_Mhz)
{
	return power_dBmW + 77.216 + 20*log10(Frequenz_Mhz);
}

//��EIRPת��ΪERP  powerdBx ��ʾ�����Ƕ�����ʽ�ģ�������Ȼ����ʽ
double CNGToolsConvert::Convert_EIRP_ERP(double powerdBx)
{
	return powerdBx - 2.15;
}

//��ERPת��ΪEIRP
double CNGToolsConvert::Convert_ERP_EIRP(double powerdBx)
{
	return powerdBx + 2.15;
}

double CNGToolsConvert::Convert_W_dBm(double powerW)
{
	return 30 + 10*log10(powerW);
}