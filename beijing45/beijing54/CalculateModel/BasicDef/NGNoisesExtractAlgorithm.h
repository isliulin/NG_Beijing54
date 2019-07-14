// Copyright 2016, ng-networks Co.Ltd
// All rights reserved.
// Author: Deng Chenjiong (deng.chenjiong@ng-networks.cn)

//该文件是背景噪声提取算法的头文件，包含两种背噪提取算法，可根据情况选用
//
//80%方法:
//    int EightyPercent_Method(map<unsigned __int64,vector<short>>& specimenData, short& noiseValue);
//邻值判别算法：
//    int ExtractBackroundNoises(map<unsigned __int64,vector<short>>& specimenData, map<unsigned __int64,short>& noise, double db=DET_VALUE);

#ifndef _NGNOISESEXTRACTALGORITHM_H_
#define _NGNOISESEXTRACTALGORITHM_H_

#include "../BasicDef/MacroDef.h"

#include <map>
#include <vector>
#include "NGDataProcess_d.h"
using namespace std;

#ifndef DET_VALUE
#define DET_VALUE 5 //db
#endif

#ifndef EIGHTY_VALUE
#define EIGHTY_VALUE 0.2
#endif

typedef struct _FreqData_
{
	unsigned __int64 freq;
	short value;
	_FreqData_():freq(0),value(UNCALCULATE)
	{}
}FreqData;

/*****接口说明：****/
//邻值判别法（动态噪声曲线）:ExtractBackroundNoises
//或80%方法(固定电平):EightyPercent_Method。

//提取背景噪声算法
int ExtractBackroundNoises(map<unsigned __int64,vector<short>>& specimenData, map<unsigned __int64,short>& noise, double db=DET_VALUE);

//80%方法
int EightyPercent_Method(map<unsigned __int64,vector<short>>& specimenData, short& noiseValue);

//针对业务类型的80%方法
bool GetAllMeasuredValuesInOneBusinessType(map<unsigned __int64,vector<short>>& specimenData, vector<short>& avgValues, double startFreqMhz, double endFreqMhz);
int EightPercent_MethodInBusinessType(map<unsigned __int64,vector<short>>& specimenData, short& noiseValue, double startFreqMhz, double endFreqMhz,double Ratio);

int EightPercent_MethodInBusinessType_new( map<unsigned __int64,vector<short>>& specimenData, short& noise, double startFreqMhz, double endFreqMhz ,double Ratio );

int EightPercent_MethodInBusinessType_SHnew( map<unsigned __int64,vector<short>>& specimenData, short& noise, double startFreqMhz, double endFreqMhz ,double Ratio );

bool GetAllMeasuredValuesInOneBusinessType(map<unsigned __int64,vector<short>>& specimenData, vector<short>& avgValues, double startFreqMhz, double endFreqMhz,std::vector<int>& dataInPeriods);
int EightPercent_MethodInBusinessType(map<unsigned __int64,vector<short>>& specimenData, short& noiseValue, double startFreqMhz, double endFreqMhz,double Ratio,std::vector<int>& dataInPeriods);
//邻值判别法
int DoNerghborValueDistinguish(map<unsigned __int64,vector<short>>& specimenData, double db, map<unsigned __int64,short>& noise);

//计算均值谱线
bool CalculateSpectrumAVG(map<unsigned __int64,vector<short>>& specimenData, vector<FreqData>& avgValues);

//获取算术平均值(避免累加后溢出)
bool GetArithmeticMean(std::vector<FreqData>& vData, int numData, short& meanValue);

//针对业务类型的计算信道累积场强的80%算法
int EightPercent_MethodTotalInBusinessType( CNGDataProcess_js &dataProcess, short& noise, double startFreqMhz, double endFreqMhz ,double stepMHz,double Ratio );

bool GetTotalValuesInOneBusinessType( CNGDataProcess_js &dataProcess, vector<short>& avgValues, double startFreqMhz, double endFreqMhz, double stepMHz );
#endif