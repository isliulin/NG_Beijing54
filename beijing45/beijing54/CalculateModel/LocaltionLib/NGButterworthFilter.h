#ifndef NG_BUTTER_WORTH_FILTER_H
#define NG_BUTTER_WORTH_FILTER_H

#include "LowPassFilter.h"

//巴特沃斯滤波器
class CNGButterworthFilter:public LowPassFilter
{
public:
	CNGButterworthFilter(double bandWidth, double stopBandFreq, double sampleRate, double attenuationIndB=20);
	~CNGButterworthFilter(void);


private:
	void GetFilterCoefficient();//获取滤波系数
};

#endif