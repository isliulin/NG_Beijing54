

/*****************************************************************************
// �ļ���:		 
// ��д��:	�	  
// ��д����:2015.12	  
// ��Ҫ���� TDOA��λ�㷨�У�����IQ���������źŵ�����ԣ�Ȼ����ݼ���õ�����ط��Լ������ʼ���ʱ��
// ����ĵ����ƣ�
// ����ĵ��汾��
// ����ĵ�����ID 
// �޸ļ�¼:		 
//
// (C) 2017  Ng-networks
*****************************************************************************/

#ifndef CROSS_CORRELATION_H
#define CROSS_CORRELATION_H

#include "NGTDOADataStruct.h"



//���ڼ����źŵĻ�����Ե��࣬
//���������������м��㲢����TDOAֵ,��λns

class NGCrossCorrelation
{
public:

	static double GetTDOAInNsbyGeneralized(NGIQData& data1  ,NGIQData& data2, bool& bSucceed);
	//���ݹ��廥����㷨����TDOAֵ�������ٶȿ�,bSucceed����false���ź�û�������


	//����data1�ĵ�a�ݼ�¼��data2�ĵ�b�ݼ�¼������ԣ����ɼ��õ���IQ�ֳɼ��ݽ�������Լ��㣬Ȼ��ȡ��ֵ
	static double GetTDOAInNsByBurst(NGIQData& data1  ,NGIQData& data2  , bool& bSucceed);

	//����������Ƶ�źŵ�ʱ�ӹ��ƣ��ɼ���1s�е����ݣ����а����˶��Ƶ����źţ�ÿ��Ƶ������ڲ�ͬ��ʱ���
	static int GetTDOAInNsofHopSignal(NGIQData& data1  ,NGIQData& data2 ,splab::Vector<TDComplex>&fdomians1,splab::Vector<TDComplex>& fdomains2 , int signalnum , vector<int>& sIndexs,int bandwidth  ,double& dValue);

	//��Ƶ�źŲ��
	static void SplitSignal(double centerfreq,splab::Vector<TDComplex>& domains,int& signalnum , vector<int>& sIndexs,int bandwidth);
private:
	NGCrossCorrelation(){};
	~NGCrossCorrelation(){};//��Ĭ�Ϲ��캯��˽�л�����ֹ�������

	static CrossCorrelationResult GetCrossResultsbyGeneralized(short* pSignal1,short* pSignal2,int s1,int s2);
	//ʵ�ù��廥��أ���ȡ�����ϵ�����,��������IQ���������Լ������������ĳ���

	
	//���ɼ��õ���IQ�ֳɼ��ݽ�������Լ��㣬Ȼ��ȡ��ֵ
	static double GetTDOAIndexByBurst(short* pSignal1,short* pSignal2,int s1,int s2,bool& bSucceed);

	static int GetTDOAIndexOfHopSignal(splab::Vector<TDComplex>&fdomians1,splab::Vector<TDComplex>& fdomains2,int signalnum , vector<int>& sIndexs,int bandwidth,double skipnum,double maxIndex,double& dValue);

	static double CalculateTDOA(splab::Vector<TDComplex>& signal1,splab::Vector<TDComplex>& signal2);
	static void CalculateRelationCoefs(short* pSignal1 , short* pSignal2 , int length , vector<double>& coefs);


	//����x = -1 , 0 , 1����ֵ�����������߶��㴦��xֵ
	static double GetTDOAValue(double y1 , double y2 , double y3);
	static double ExtractBackroundNoises(vector<double>& datas);
	static const int dlength = 4096 ;//ÿ�μ��������ʱ��IQ���ݳ���
};
#endif