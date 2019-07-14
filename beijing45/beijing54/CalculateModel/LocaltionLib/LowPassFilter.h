#ifndef LOW_PASS_FILTER_H
#define LOW_PASS_FILTER_H

#include "NGTDOADataStruct.h"


//��ͨ�˲� ͨ��Ƶ��Ϊ0��_bandWidth,����Ƶ��Ϊ_bandWidth/2,��ѵ�ͨ�˲�����ֹƵ�ʵ��ڴ���
class LowPassFilter
{
public:
	LowPassFilter(double bandWidth, double stopBandFreq, double sampleRate, double attenuationIndB=20);
	virtual ~LowPassFilter(void);//����������
	//��Ա����
	void DoSignalFiltering(TDComplex* & pSignals,int length);
	//�������IQ�źŽ����˲�
	
protected:
	//�����˲�ʱ�Ĺ��ߺ���
	//˫����ת����ģ���˲�ת���������˲�����ȡ�����˲��Ĳ�ַ���ϵ��
	//����˵����BS ģ���˲��ķ���ϵ��B������AS��ģ���˲��ķ�ĸϵ��A����
	                 //BZ ת����������˲��ķ���ϵ��B������ AZ �����˲��ķ�ĸϵ��A����
	bool bilinear(TDVector BS,TDVector AS,TDVector& BZ,TDVector& AZ);
	//��ʽת�� (a0+a1x+a2x^2+...+amx^m)^n to b0+b1x+...+bmnx^mn
	TDVector powerConversion(TDVector a,int n);
	//��ʽת�� (a0+a1x+a2x^2+...+amx^m)(b0+b1x+...+bnx^n) to c0+c1x+...+c(m+n)x^(m+n)
	TDVector multiplyConversion(TDVector a,TDVector b);


	//��Ա����,��ͨ�˲�����f1=0,f2=_bandWidth
protected:                                   //��ӦMatlab �˲���������Ĳ���   ����ApassĬ��Ϊ1
	double mSampleRate;//������                       Fs
	double mAlphaPIndB;//ͨ���Ʋ������ڲ���                                                //Apass
	double mAlphaSIndB;//���˥��  ,20*��Ƶ��                                              //Astop
	double mFreqPassInHZ;//ͨ��Ƶ��                                                               //Fpass
	double mFreqStopInHZ;//��ֹƵ��                                                              //Fstop
	TDVector mFilterCoefficient;//�˲�ϵ��             Matlab �˲�����������ú����Ժ��Filter Coefficients,(B,A)����

};
#endif