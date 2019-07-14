

/*****************************************************************************
// 文件名:		 
// 编写者:	李冬	  
// 编写日期:2015.12	  
// 简要描述 TDOA定位算法中，根据IQ计算两个信号的相关性，然后根据计算得到的相关峰以及采样率计算时延
// 设计文档名称：
// 设计文档版本号
// 设计文档禅道ID 
// 修改记录:		 
//
// (C) 2017  Ng-networks
*****************************************************************************/

#ifndef CROSS_CORRELATION_H
#define CROSS_CORRELATION_H

#include "NGTDOADataStruct.h"



//用于计算信号的互相关性的类，
//从两个输入数据中计算并返回TDOA值,单位ns

class NGCrossCorrelation
{
public:

	static double GetTDOAInNsbyGeneralized(NGIQData& data1  ,NGIQData& data2, bool& bSucceed);
	//根据广义互相关算法计算TDOA值，计算速度快,bSucceed返回false则信号没有相关性


	//计算data1的第a份记录和data2的第b份记录的相关性，将采集得到的IQ分成几份进行相关性计算，然后取均值
	static double GetTDOAInNsByBurst(NGIQData& data1  ,NGIQData& data2  , bool& bSucceed);

	//计算两个跳频信号的时延估计，采集了1s中的数据，其中包含了多个频点的信号，每个频点出现在不同的时间段
	static int GetTDOAInNsofHopSignal(NGIQData& data1  ,NGIQData& data2 ,splab::Vector<TDComplex>&fdomians1,splab::Vector<TDComplex>& fdomains2 , int signalnum , vector<int>& sIndexs,int bandwidth  ,double& dValue);

	//跳频信号拆分
	static void SplitSignal(double centerfreq,splab::Vector<TDComplex>& domains,int& signalnum , vector<int>& sIndexs,int bandwidth);
private:
	NGCrossCorrelation(){};
	~NGCrossCorrelation(){};//将默认构造函数私有化，防止定义对象

	static CrossCorrelationResult GetCrossResultsbyGeneralized(short* pSignal1,short* pSignal2,int s1,int s2);
	//实用广义互相关，获取最相关系数结果,输入两个IQ数据流，以及两个数据流的长度

	
	//将采集得到的IQ分成几份进行相关性计算，然后取均值
	static double GetTDOAIndexByBurst(short* pSignal1,short* pSignal2,int s1,int s2,bool& bSucceed);

	static int GetTDOAIndexOfHopSignal(splab::Vector<TDComplex>&fdomians1,splab::Vector<TDComplex>& fdomains2,int signalnum , vector<int>& sIndexs,int bandwidth,double skipnum,double maxIndex,double& dValue);

	static double CalculateTDOA(splab::Vector<TDComplex>& signal1,splab::Vector<TDComplex>& signal2);
	static void CalculateRelationCoefs(short* pSignal1 , short* pSignal2 , int length , vector<double>& coefs);


	//根据x = -1 , 0 , 1处的值，计算抛物线顶点处的x值
	static double GetTDOAValue(double y1 , double y2 , double y3);
	static double ExtractBackroundNoises(vector<double>& datas);
	static const int dlength = 4096 ;//每次计算相关性时的IQ数据长度
};
#endif