#ifndef CROSS_CORRELATION_H
#define CROSS_CORRELATION_H

#include "NGTDOADataStruct.h"
#include "fftpf.h"


//���ڼ����źŵĻ�����Ե��࣬
//���������������м��㲢����TDOAֵ,��λns

class NGCrossCorrelation
{
public:

	//����data1�ĵ�a�ݼ�¼��data2�ĵ�b�ݼ�¼������ԣ����ɼ��õ���IQ�ֳɼ��ݽ�������Լ��㣬Ȼ��ȡ��ֵ
	static double GetTDOAInNsByBurst(NGIQData& data1 , NGIQData& data2 , bool& bSucceed);

	static double GetTDOAInNsByBurst(NGIQData_float& data1 , NGIQData_float& data2 , bool& bSucceed);

	//Ƶ���˲���
	static void DoFreqFilter(int*& pdatas , int length , double fs , double band);

	static void DoFreqFilter(float*& pdatas , int length , double fs , double band);


	//���ݹ��廥����㷨����TDOAֵ�������ٶȿ�,bSucceed����false���ź�û������ԣ�isEven �жϲ�����ʽ�Ƿ���ż�β�����ż�β���ҪƵ�׷�ת
	//�����ڿ���ź�
	static double GetTDOAInNsbyGeneralized(IQData& data1,IQData& data2,bool isEven,bool& bSucceed);

	//���ݹ��廥����㷨����TDOAֵ�������ٶȿ�,bSucceed����false���ź�û�������
	//�����ڿ���ź�
	static double GetTDOAInNsbyGeneralized(NGIQData& data1,NGIQData& data2,bool& bSucceed);

private:
	NGCrossCorrelation(){};
	~NGCrossCorrelation(){};//��Ĭ�Ϲ��캯��˽�л�����ֹ�������

	//���ɼ��õ���IQ�ֳɼ��ݽ�������Լ��㣬Ȼ��ȡ��ֵ
	static double GetTDOAIndexByBurst(int* pSignal1,int* pSignal2,int s1,int s2,bool& bSucceed);

	static double GetTDOAIndexByBurst(float* pSignal1,float* pSignal2,int s1,int s2,bool& bSucceed);

	//ʹ�ù��廥��أ���ȡ�����ϵ�����,��������IQ���������Լ������������ĳ���
	static CrossCorrelationResult GetCrossResultsbyGeneralized(TDComplex* pSignal1,TDComplex* pSignal2,int s1,int s2);

	static CrossCorrelationResult GetCrossResultsbyGeneralized(int* pSignal1,int* pSignal2,int s1,int s2);




	//����x = -1 , 0 , 1����ֵ�����������߶��㴦��xֵ
	static double GetTDOAValue(double y1 , double y2 , double y3);

	static void CalculateRelationCoefs(int* pSignal1 , int* pSignal2 , int length , vector<double>& coefs);

	static void CalculateRelationCoefs(float* pSignal1 , float* pSignal2 , int length , vector<double>& coefs);

	static const int dlength = 4096 ;//ÿ�μ��������ʱ��IQ���ݳ���

	/*
Function: NG_Hilbert
			  //��ɢϣ�����ر任
Para: 
Input:  
	TDComplex *pSignal     �������ԭʼ���ݣ�����Ϊ��
		int ulSiglen  ԭʼ���ݵĳ���
Output: 
	splab::Vector<TDComplex>& result
explain:  �൱��MATLAB�� Rslt=hilbert(signal);
	*********************************************************************************************/
	static void NG_Hilbert(TDComplex *pSignal, int ulSiglen,splab::Vector<TDComplex>& result);

	static void NG_Hilbert(TDVector& signal);
};
#endif