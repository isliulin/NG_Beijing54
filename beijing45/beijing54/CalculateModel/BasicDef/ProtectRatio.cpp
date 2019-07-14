#include <math.h>
#include "ProtectRatio.h"

//先暂时定义在这里，根据欲收和干扰台站的频率和带宽之间的关系
double GetProtectRatioDME(double dWantFreqMhz, double dWantBWMhz, double dInterfFreqMhz, double dInterfBWMhz)
{
	double dPRatio = -1999;

	//获取较大的带宽
	double dMaxBW = dWantBWMhz >= dInterfBWMhz?dWantBWMhz:dInterfBWMhz;

	//获取两者之间的频率差值的绝对值
	double dFreqDiffMhz = fabs(dWantFreqMhz - dInterfFreqMhz);

	if(dFreqDiffMhz <= dMaxBW)
	{
		//认为是同频
		dPRatio = 8;		
	}
	else if(dFreqDiffMhz <= 2*dMaxBW)
	{
		//认为是邻频
		dPRatio = 3;
	}

	return dPRatio;
}
