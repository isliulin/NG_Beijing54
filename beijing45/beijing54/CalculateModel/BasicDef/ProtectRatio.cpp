#include <math.h>
#include "ProtectRatio.h"

//����ʱ����������������պ͸���̨վ��Ƶ�ʺʹ���֮��Ĺ�ϵ
double GetProtectRatioDME(double dWantFreqMhz, double dWantBWMhz, double dInterfFreqMhz, double dInterfBWMhz)
{
	double dPRatio = -1999;

	//��ȡ�ϴ�Ĵ���
	double dMaxBW = dWantBWMhz >= dInterfBWMhz?dWantBWMhz:dInterfBWMhz;

	//��ȡ����֮���Ƶ�ʲ�ֵ�ľ���ֵ
	double dFreqDiffMhz = fabs(dWantFreqMhz - dInterfFreqMhz);

	if(dFreqDiffMhz <= dMaxBW)
	{
		//��Ϊ��ͬƵ
		dPRatio = 8;		
	}
	else if(dFreqDiffMhz <= 2*dMaxBW)
	{
		//��Ϊ����Ƶ
		dPRatio = 3;
	}

	return dPRatio;
}
