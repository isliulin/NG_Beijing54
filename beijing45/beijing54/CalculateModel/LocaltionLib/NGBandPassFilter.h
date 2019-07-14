#ifndef NG_BAND_PASS_FILTER_H
#define NG_BAND_PASS_FILTER_H

#include "NGTDOADataStruct.h"
//通过频率域滤波算法，实现带通滤波器
class CNGBandPassFilter
{
private:
	CNGBandPassFilter(void){};
	~CNGBandPassFilter(void){};

public:
	//带通采样获得的信号滤波，带宽单位MHz
	static void DoSignalFiltering(IQData& srcData,int Index);

};

#endif