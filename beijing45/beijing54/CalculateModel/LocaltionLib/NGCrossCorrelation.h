#ifndef CROSS_CORRELATION_H
#define CROSS_CORRELATION_H

#include "NGTDOADataStruct.h"
#include "fftpf.h"


//用于计算信号的互相关性的类，
//从两个输入数据中计算并返回TDOA值,单位ns

class NGCrossCorrelation
{
public:

	//计算data1的第a份记录和data2的第b份记录的相关性，将采集得到的IQ分成几份进行相关性计算，然后取均值
	static double GetTDOAInNsByBurst(NGIQData& data1 , NGIQData& data2 , bool& bSucceed);

	static double GetTDOAInNsByBurst(NGIQData_float& data1 , NGIQData_float& data2 , bool& bSucceed);

	//频域滤波法
	static void DoFreqFilter(int*& pdatas , int length , double fs , double band);

	static void DoFreqFilter(float*& pdatas , int length , double fs , double band);


	//根据广义互相关算法计算TDOA值，计算速度快,bSucceed返回false则信号没有相关性，isEven 判断采样方式是否是偶次采样，偶次采样要频谱反转
	//适用于宽带信号
	static double GetTDOAInNsbyGeneralized(IQData& data1,IQData& data2,bool isEven,bool& bSucceed);

	//根据广义互相关算法计算TDOA值，计算速度快,bSucceed返回false则信号没有相关性
	//适用于宽带信号
	static double GetTDOAInNsbyGeneralized(NGIQData& data1,NGIQData& data2,bool& bSucceed);

private:
	NGCrossCorrelation(){};
	~NGCrossCorrelation(){};//将默认构造函数私有化，防止定义对象

	//将采集得到的IQ分成几份进行相关性计算，然后取均值
	static double GetTDOAIndexByBurst(int* pSignal1,int* pSignal2,int s1,int s2,bool& bSucceed);

	static double GetTDOAIndexByBurst(float* pSignal1,float* pSignal2,int s1,int s2,bool& bSucceed);

	//使用广义互相关，获取最相关系数结果,输入两个IQ数据流，以及两个数据流的长度
	static CrossCorrelationResult GetCrossResultsbyGeneralized(TDComplex* pSignal1,TDComplex* pSignal2,int s1,int s2);

	static CrossCorrelationResult GetCrossResultsbyGeneralized(int* pSignal1,int* pSignal2,int s1,int s2);




	//根据x = -1 , 0 , 1处的值，计算抛物线顶点处的x值
	static double GetTDOAValue(double y1 , double y2 , double y3);

	static void CalculateRelationCoefs(int* pSignal1 , int* pSignal2 , int length , vector<double>& coefs);

	static void CalculateRelationCoefs(float* pSignal1 , float* pSignal2 , int length , vector<double>& coefs);

	static const int dlength = 4096 ;//每次计算相关性时的IQ数据长度

	/*
Function: NG_Hilbert
			  //离散希尔伯特变换
Para: 
Input:  
	TDComplex *pSignal     待计算的原始数据，不可为空
		int ulSiglen  原始数据的长度
Output: 
	splab::Vector<TDComplex>& result
explain:  相当于MATLAB的 Rslt=hilbert(signal);
	*********************************************************************************************/
	static void NG_Hilbert(TDComplex *pSignal, int ulSiglen,splab::Vector<TDComplex>& result);

	static void NG_Hilbert(TDVector& signal);
};
#endif