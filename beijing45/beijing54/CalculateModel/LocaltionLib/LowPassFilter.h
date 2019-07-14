#ifndef LOW_PASS_FILTER_H
#define LOW_PASS_FILTER_H

#include "NGTDOADataStruct.h"


//低通滤波 通过频率为0—_bandWidth,中心频率为_bandWidth/2,最佳低通滤波器截止频率等于带宽
class LowPassFilter
{
public:
	LowPassFilter(double bandWidth, double stopBandFreq, double sampleRate, double attenuationIndB=20);
	virtual ~LowPassFilter(void);//虚析构函数
	//成员函数
	void DoSignalFiltering(TDComplex* & pSignals,int length);
	//对输入的IQ信号进行滤波
	
protected:
	//进行滤波时的工具函数
	//双线性转换，模拟滤波转换成数字滤波，获取数字滤波的差分方程系数
	//参数说明：BS 模拟滤波的分子系数B向量，AS，模拟滤波的分母系数A向量
	                 //BZ 转换后的数字滤波的分子系数B向量， AZ 数字滤波的分母系数A向量
	bool bilinear(TDVector BS,TDVector AS,TDVector& BZ,TDVector& AZ);
	//格式转换 (a0+a1x+a2x^2+...+amx^m)^n to b0+b1x+...+bmnx^mn
	TDVector powerConversion(TDVector a,int n);
	//格式转换 (a0+a1x+a2x^2+...+amx^m)(b0+b1x+...+bnx^n) to c0+c1x+...+c(m+n)x^(m+n)
	TDVector multiplyConversion(TDVector a,TDVector b);


	//成员变量,低通滤波器，f1=0,f2=_bandWidth
protected:                                   //对应Matlab 滤波器设计器的参数   参数Apass默认为1
	double mSampleRate;//采样率                       Fs
	double mAlphaPIndB;//通带纹波、带内波动                                                //Apass
	double mAlphaSIndB;//阻带衰减  ,20*倍频数                                              //Astop
	double mFreqPassInHZ;//通带频率                                                               //Fpass
	double mFreqStopInHZ;//截止频率                                                              //Fstop
	TDVector mFilterCoefficient;//滤波系数             Matlab 滤波器设计器设置好了以后的Filter Coefficients,(B,A)向量

};
#endif