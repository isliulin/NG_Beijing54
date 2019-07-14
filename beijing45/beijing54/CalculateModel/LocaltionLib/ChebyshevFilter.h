#ifndef CHEBYSHEV_FILTER_H
#define CHEBYSHEV_FILTER_H

#include "LowPassFilter.h"



//�б�ѩ��I���˲�����ͨ�������Ʋ������ɴ��϶���
class ChebyshevFilter:public LowPassFilter
{
public:
	ChebyshevFilter(double bandWidth, double stopBandFreq, double sampleRate, double attenuationIndB=20);
	~ChebyshevFilter(void);

private:
	void GetFilterCoefficient();//��ȡ�˲�ϵ��
};
#endif