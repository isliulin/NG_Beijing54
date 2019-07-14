#ifndef CHEBYSHEV_FILTER_H
#define CHEBYSHEV_FILTER_H

#include "LowPassFilter.h"



//切比雪夫I型滤波器，通带内有纹波，过渡带较陡急
class ChebyshevFilter:public LowPassFilter
{
public:
	ChebyshevFilter(double bandWidth, double stopBandFreq, double sampleRate, double attenuationIndB=20);
	~ChebyshevFilter(void);

private:
	void GetFilterCoefficient();//获取滤波系数
};
#endif