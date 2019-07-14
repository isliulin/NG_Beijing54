// Copyright 2016, ng-networks Co.Ltd
// All rights reserved.
// Author: Deng Chenjiong (deng.chenjiong@ng-networks.cn)

//���ļ��Ǳ���������ȡ�㷨��ͷ�ļ����������ֱ�����ȡ�㷨���ɸ������ѡ��
//
//80%����:
//    int EightyPercent_Method(map<unsigned __int64,vector<short>>& specimenData, short& noiseValue);
//��ֵ�б��㷨��
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

/*****�ӿ�˵����****/
//��ֵ�б𷨣���̬�������ߣ�:ExtractBackroundNoises
//��80%����(�̶���ƽ):EightyPercent_Method��

//��ȡ���������㷨
int ExtractBackroundNoises(map<unsigned __int64,vector<short>>& specimenData, map<unsigned __int64,short>& noise, double db=DET_VALUE);

//80%����
int EightyPercent_Method(map<unsigned __int64,vector<short>>& specimenData, short& noiseValue);

//���ҵ�����͵�80%����
bool GetAllMeasuredValuesInOneBusinessType(map<unsigned __int64,vector<short>>& specimenData, vector<short>& avgValues, double startFreqMhz, double endFreqMhz);
int EightPercent_MethodInBusinessType(map<unsigned __int64,vector<short>>& specimenData, short& noiseValue, double startFreqMhz, double endFreqMhz,double Ratio);

int EightPercent_MethodInBusinessType_new( map<unsigned __int64,vector<short>>& specimenData, short& noise, double startFreqMhz, double endFreqMhz ,double Ratio );

int EightPercent_MethodInBusinessType_SHnew( map<unsigned __int64,vector<short>>& specimenData, short& noise, double startFreqMhz, double endFreqMhz ,double Ratio );

bool GetAllMeasuredValuesInOneBusinessType(map<unsigned __int64,vector<short>>& specimenData, vector<short>& avgValues, double startFreqMhz, double endFreqMhz,std::vector<int>& dataInPeriods);
int EightPercent_MethodInBusinessType(map<unsigned __int64,vector<short>>& specimenData, short& noiseValue, double startFreqMhz, double endFreqMhz,double Ratio,std::vector<int>& dataInPeriods);
//��ֵ�б�
int DoNerghborValueDistinguish(map<unsigned __int64,vector<short>>& specimenData, double db, map<unsigned __int64,short>& noise);

//�����ֵ����
bool CalculateSpectrumAVG(map<unsigned __int64,vector<short>>& specimenData, vector<FreqData>& avgValues);

//��ȡ����ƽ��ֵ(�����ۼӺ����)
bool GetArithmeticMean(std::vector<FreqData>& vData, int numData, short& meanValue);

//���ҵ�����͵ļ����ŵ��ۻ���ǿ��80%�㷨
int EightPercent_MethodTotalInBusinessType( CNGDataProcess_js &dataProcess, short& noise, double startFreqMhz, double endFreqMhz ,double stepMHz,double Ratio );

bool GetTotalValuesInOneBusinessType( CNGDataProcess_js &dataProcess, vector<short>& avgValues, double startFreqMhz, double endFreqMhz, double stepMHz );
#endif