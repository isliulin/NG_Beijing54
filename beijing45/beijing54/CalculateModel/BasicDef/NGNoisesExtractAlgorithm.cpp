// Copyright 2016, ng-networks Co.Ltd
// All rights reserved.
// Author: Deng Chenjiong (deng.chenjiong@ng-networks.cn)

#include "NGNoisesExtractAlgorithm.h"
#include "../BasicDef/NG_ErrorCode.h"
#include <algorithm>
#include <cmath>

//大小比较函数
bool FreqDataSort(FreqData& x,FreqData& y) { return (x.value < y.value); }

//背景噪声提取算法接口函数
int ExtractBackroundNoises(map<unsigned __int64,vector<short>>& specimenData, map<unsigned __int64,short>& noise, double db)
{
	int ret = NG_SUCCESS;

	if ( specimenData.empty() )
	{
		return MONITOR_FREQ_TOO_LESS;
	}

	if ( NG_SUCCESS != (ret=DoNerghborValueDistinguish(specimenData,db,noise)))
	{
		return ret;
	}

	return ret;
}

//80%方法
int EightyPercent_Method(map<unsigned __int64,vector<short>>& specimenData, short& noise)
{
	int ret = NG_SUCCESS;

	int numRecord = 0;
	int numTwenty = 0;
	vector<FreqData> avgValues;

	if (!CalculateSpectrumAVG(specimenData,avgValues))
	{
		return CALCULATE_SPECTRUM_AVG_ERROR;
	}

	std::sort(avgValues.begin(),avgValues.end(),FreqDataSort);
	numRecord = avgValues.size();
	numTwenty = ceil(numRecord * EIGHTY_VALUE);
	noise = UNCALCULATE;
	GetArithmeticMean(avgValues,numTwenty,noise);

	if ( UNCALCULATE != noise )
	{
		noise = noise * 0.1;
	}
	else
	{
		ret = EIGHTY_PERCENT_METHOD_ERROR;
	}

	return ret;
}

//邻值判别
int DoNerghborValueDistinguish(map<unsigned __int64,vector<short>>& specimenData, double db, map<unsigned __int64,short>& noise)
{
	int ret = NG_SUCCESS;

	vector<FreqData> avgValues;
	short firstValue = 0;
	double detValue = db;
	int numFreqs = 0;

	if (!CalculateSpectrumAVG(specimenData,avgValues))
	{
		return CALCULATE_SPECTRUM_AVG_ERROR;
	}

	//dbuv/m => dbm
	//国家标准数据中，频率：Hz，值:dbuv/m(在除以10之后)
	for (vector<FreqData>::iterator it = avgValues.begin(); it != avgValues.end(); ++it)
	{
		it->value = it->value*0.1;// - 77.216 - 20*log10((1e-6)*(it->freq));
	}

	//邻值判别
	numFreqs = avgValues.size();
	if ( numFreqs == 1 )
	{
        noise.insert(make_pair(avgValues.begin()->freq,avgValues.begin()->value));
		return ret;
	}
	else if (numFreqs < 1)
	{
		return NO_VALID_FREQ_ERROR;
	}

	/*******numFreqs >= 2********/

	if ( abs(avgValues[0].value - avgValues[1].value) > detValue )
	{
		if ( avgValues[0].value < avgValues[1].value )
		{
			avgValues[1].value = avgValues[0].value;
		}
		else
		{
			avgValues[0].value = avgValues[1].value;
		}
	}

	for (int i = 2; i < numFreqs; i++ )
	{
		if (avgValues[i-1].value - avgValues[i].value > detValue)
		{
			avgValues[i-2].value = avgValues[i].value;
			avgValues[i-1].value = avgValues[i].value;
		}

		if (avgValues[i-1].value > avgValues[i].value && avgValues[i-1].value - avgValues[i].value < detValue)
		{
			avgValues[i-1].value = (avgValues[i-2].value + avgValues[i].value) * 0.5;
		}

		if (avgValues[i].value - avgValues[i-1].value > detValue)
		{
			avgValues[i].value = avgValues[i-1].value;
		}
	}

	//平滑处理
	avgValues[0].value = (avgValues[0].value + avgValues[1].value) / 2;
	for (int i = 2; i < numFreqs; i++ )
	{
		avgValues[i-1].value = (avgValues[i-2].value + avgValues[i].value) / 2;
	}

	for ( vector<FreqData>::iterator itRlt = avgValues.begin(); itRlt != avgValues.end(); ++itRlt )
	{
		noise.insert(make_pair(itRlt->freq,itRlt->value));
	}

	return ret;
}

//计算均值谱线
bool CalculateSpectrumAVG(map<unsigned __int64,vector<short>>& specimenData, vector<FreqData>& avgValues)
{
	bool ret = true;
	short meanValue = 0;
	int numOneFreq = 0;

	for (map<unsigned __int64,vector<short>>::iterator itData = specimenData.begin(); itData != specimenData.end(); ++itData)
	{
		FreqData avrVl;
		meanValue = 0;
		numOneFreq = itData->second.size();
		avrVl.freq = itData->first;

		for ( int i = 0; i < numOneFreq; i++ )
		{
			meanValue = meanValue + (itData->second[i] - meanValue) / (i + 1);
		}

		if ( !itData->second.empty() )
		{
			avrVl.value = meanValue;
		}
		avgValues.push_back(avrVl);
	}

	return ret;
}

bool GetArithmeticMean(std::vector<FreqData>& vData, int numData, short& meanValue)
{
	meanValue = 0;
	double tempmeanvalue = 0;
	if (vData.empty())
	{
		meanValue = UNCALCULATE;
		return false;
	}

	for ( int i = 0; i < numData; i++ )
	{
		tempmeanvalue = tempmeanvalue + 1.0*(vData[i].value - tempmeanvalue)/(i + 1);
	}
	meanValue = tempmeanvalue;
	return true;
}

bool GetArithmeticMean(std::vector<short>& vData, int numData, short& meanValue)
{
	meanValue = 0;
	double tempmeanvalue = 0;
	if (vData.empty())
	{
		meanValue = UNCALCULATE;
		return false;
	}

	for ( int i = 0; i < numData; i++ )
	{
		tempmeanvalue = tempmeanvalue + 1.0*(vData[i] - tempmeanvalue)/(i + 1);
	}
	meanValue = tempmeanvalue;
	return true;
}

int EightPercent_MethodInBusinessType( map<unsigned __int64,vector<short>>& specimenData, short& noise, double startFreqMhz, double endFreqMhz ,double Ratio )
{
	int ret = NG_SUCCESS;

	int numRecord = 0;
	int numTwenty = 0;
	vector<short> avgValues;

	if (!GetAllMeasuredValuesInOneBusinessType(specimenData,avgValues,startFreqMhz,endFreqMhz))
	{
		return CALCULATE_SPECTRUM_AVG_ERROR;
	}

	if (0 == avgValues.size())
	{
		return NO_DATA_OF_THE_BAND;
	}

	std::sort(avgValues.begin(),avgValues.end());
	numRecord = avgValues.size();
	double num = EIGHTY_VALUE;
	if (Ratio >= 10 && Ratio <= 20)
	{
		num = Ratio/100.0;
	}
	numTwenty = ceil(numRecord * num);
	noise = UNCALCULATE;
	GetArithmeticMean(avgValues,numTwenty,noise);

	if ( UNCALCULATE != noise )
	{
		noise = noise * 0.1;
	}
	else
	{
		ret = EIGHTY_PERCENT_METHOD_ERROR;
	}

	return ret;

}

//上海网格化升级监测月报新增二八算法计算底噪的方法
//主要修改：计算信号在时间段内的平均值，然后排序，取20%的信号的均值作为噪声
int EightPercent_MethodInBusinessType_SHnew( map<unsigned __int64,vector<short>>& specimenData, short& noise, double startFreqMhz, double endFreqMhz ,double Ratio )
{
	int ret = NG_SUCCESS;

	int numRecord = 0;
	int numTwenty = 0;
	vector<double> avgValues;

	map<unsigned __int64,vector<short>>::iterator iterMap;
	map<unsigned __int64,vector<short>>::iterator iterMapEnd = specimenData.end();

	unsigned __int64 maxFreqHz = endFreqMhz * 1000000;
	unsigned __int64 minFreqHz = startFreqMhz * 1000000;

	double dAvg = 0.0;
	int nCount = 0;
	for(iterMap = specimenData.begin(); iterMap != iterMapEnd; iterMap++)
	{
		dAvg = 0.0;	
		nCount = 0;

		if (iterMap->first < minFreqHz || iterMap->first > maxFreqHz)
		{
			continue;
		}
		vector<short>& vDataList = iterMap->second;
		vector<short>::iterator iter;
		vector<short>::iterator iterEnd = vDataList.end();
		for(iter = vDataList.begin(); iter != iterEnd; iter++,nCount++)
		{
			float val=(*iter*1.0)/10.0;//原数据存的是10倍的dBuv值

#ifdef MONITORFORMAT_TO_DBM

			double freqtmp=iterMap->first/1000000;//MHz
			float valdbm=val-20*log10(freqtmp)-77.216;
			val = valdbm;
#endif

			double dTemp = pow(10.0, val/10.0);
			dAvg = dAvg + 1.0*(dTemp - dAvg)/(nCount+ 1);
			//dAvg = 10*log10(dAvg);
		}
		avgValues.push_back(dAvg);
	}	

	if (0 == avgValues.size())
	{
		return NO_DATA_OF_THE_BAND;
	}

	std::sort(avgValues.begin(),avgValues.end());
	numRecord = avgValues.size();
	double num = EIGHTY_VALUE;
	if (Ratio >= 10 && Ratio <= 20)
	{
		num = Ratio/100.0;
	}
	numTwenty = ceil(numRecord * num);
	noise = UNCALCULATE;

	double tempmeanvalue = 0;
	for ( int i = 0; i < numTwenty; i++ )
	{
		tempmeanvalue = tempmeanvalue + 1.0*(avgValues[i] - tempmeanvalue)/(i + 1);
	}
	if(numTwenty > 0)
	{
		noise = 10*log10(tempmeanvalue);
	}

	if ( UNCALCULATE != noise )
	{
		noise = noise ;
	}
	else
	{
		ret = EIGHTY_PERCENT_METHOD_ERROR;
	}

	return ret;

}



//新增二八算法计算底噪的方法
//主要修改：计算信号在时间段内的平均值，然后排序，取20%的信号的均值作为噪声
int EightPercent_MethodInBusinessType_new( map<unsigned __int64,vector<short>>& specimenData, short& noise, double startFreqMhz, double endFreqMhz ,double Ratio )
{
	int ret = NG_SUCCESS;

	int numRecord = 0;
	int numTwenty = 0;
	vector<double> avgValues;

	map<unsigned __int64,vector<short>>::iterator iterMap;
	map<unsigned __int64,vector<short>>::iterator iterMapEnd = specimenData.end();

	unsigned __int64 maxFreqHz = endFreqMhz * 1000000;
	unsigned __int64 minFreqHz = startFreqMhz * 1000000;

	double dAvg = 0.0;
	int nCount = 0;
	for(iterMap = specimenData.begin(); iterMap != iterMapEnd; iterMap++)
	{
		dAvg = 0.0;	
		nCount = 0;

		if (iterMap->first < minFreqHz || iterMap->first > maxFreqHz)
		{
			continue;
		}
		vector<short>& vDataList = iterMap->second;
		vector<short>::iterator iter;
		vector<short>::iterator iterEnd = vDataList.end();
		for(iter = vDataList.begin(); iter != iterEnd; iter++,nCount++)
		{
			double dTemp = pow(10.0, *iter/100.0);
			dAvg = dAvg + 1.0*(dTemp - dAvg)/(nCount+ 1);
		}
		avgValues.push_back(dAvg);
	}	

	if (0 == avgValues.size())
	{
		return NO_DATA_OF_THE_BAND;
	}

	std::sort(avgValues.begin(),avgValues.end());
	numRecord = avgValues.size();
	double num = EIGHTY_VALUE;
	if (Ratio >= 10 && Ratio <= 20)
	{
		num = Ratio/100.0;
	}
	numTwenty = ceil(numRecord * num);
	noise = UNCALCULATE;
	
	double tempmeanvalue = 0;
	for ( int i = 0; i < numTwenty; i++ )
	{
		tempmeanvalue = tempmeanvalue + 1.0*(avgValues[i] - tempmeanvalue)/(i + 1);
	}
	if(numTwenty > 0)
	{
		noise = 10*log10(tempmeanvalue);
	}

	if ( UNCALCULATE != noise )
	{
		noise = noise ;
	}
	else
	{
		ret = EIGHTY_PERCENT_METHOD_ERROR;
	}

	return ret;

}

int EightPercent_MethodTotalInBusinessType( CNGDataProcess_js &dataProcess, short& noise, double startFreqMhz, double endFreqMhz ,double stepMHz,double Ratio )
{
	int ret = NG_SUCCESS;

	int numRecord = 0;
	int numTwenty = 0;
	vector<short> avgValues;
	if (!GetTotalValuesInOneBusinessType(dataProcess,avgValues,startFreqMhz,endFreqMhz,stepMHz))
	{
		return CALCULATE_SPECTRUM_AVG_ERROR;
	}

	if (0 == avgValues.size())
	{
		return NO_DATA_OF_THE_BAND;
	}

	std::sort(avgValues.begin(),avgValues.end());
	numRecord = avgValues.size();
	double num = EIGHTY_VALUE;
	if (Ratio >= 10 && Ratio <= 20)
	{
		num = Ratio/100.0;
	}
	numTwenty = ceil(numRecord * num);
	noise = UNCALCULATE;
	GetArithmeticMean(avgValues,numTwenty,noise);


	if ( UNCALCULATE != noise )
	{
		noise = noise * 0.1;
	}
	else
	{
		ret = EIGHTY_PERCENT_METHOD_ERROR;
	}


	return ret;

}


bool GetAllMeasuredValuesInOneBusinessType( map<unsigned __int64,vector<short>>& specimenData, vector<short>& avgValues, double startFreqMhz, double endFreqMhz )
{
	bool ret = true;
	unsigned __int64 maxFreqHz = endFreqMhz * 1000000;
	unsigned __int64 minFreqHz = startFreqMhz * 1000000;
	unsigned int num = 0 ;
	for (map<unsigned __int64,vector<short>>::iterator itData = specimenData.begin(); itData != specimenData.end(); ++itData)
	{
		if (itData->first >= minFreqHz && itData->first <= maxFreqHz)
		{
			num +=itData->second.size(); 
		}
	}
	avgValues.reserve(num);

	for (map<unsigned __int64,vector<short>>::iterator itData = specimenData.begin(); itData != specimenData.end(); ++itData)
	{
		if (itData->first >= minFreqHz && itData->first <= maxFreqHz)
		{
			for ( unsigned int i = 0; i < itData->second.size(); i++ )
			{
				avgValues.push_back(itData->second[i]);
			}
		}
	}
	return ret;
}

bool GetTotalValuesInOneBusinessType( CNGDataProcess_js &dataProcess, vector<short>& avgValues, double startFreqMhz, double endFreqMhz, double stepMHz )
{
	bool ret = true;
	unsigned __int64 maxFreqHz = endFreqMhz * 1000000;
	unsigned __int64 minFreqHz = startFreqMhz * 1000000;
	unsigned __int64 stepHz = stepMHz * 1000000;
	unsigned int num = 0 ;
	int ChannelNum = (maxFreqHz-minFreqHz)/stepHz;
	map<unsigned __int64,vector<short>> specimenData = dataProcess.m_allDatas;
	map<unsigned __int64,vector<short>>::iterator itDataTemp = specimenData.begin();
	if (itDataTemp->first == NULL || itDataTemp->second.empty())
	{
		return false;
	}
	vector<StandBinHeadV3>::iterator itTemp = dataProcess.m_allheads.begin();
	unsigned int		dataStepHzTemp = itTemp->freqstep;  //数据步长
	unsigned __int64	dataStartFreqTemp = itTemp->startfreq;
	unsigned int        dataFreqNumTemp = dataProcess.m_allDatas.size();
	double dataEndFreqHz = dataStartFreqTemp + dataFreqNumTemp * dataStepHzTemp;//数据的截止频率
	if (dataEndFreqHz < minFreqHz)
	{
		return false;
	}

	num = ChannelNum  * (itDataTemp->second.size());//一个信道存一个累积场强
	avgValues.reserve(num);

	for ( int Index = 0 ; Index < itDataTemp->second.size(); Index ++ )
	{
		vector<StandBinHeadV3>::iterator it = dataProcess.m_allheads.begin();
		unsigned int		dataStepHz = it->freqstep;  //数据步长
		unsigned __int64	dataFreq = it->startfreq;


		int freqCount = ceil (1.0*(stepHz / dataStepHz) );//每个信道内存在多少实测频点

		if ( 0 >= freqCount )
		{
			return THE_PARAMETER_RANGE_IS_ILLEGAL;
		}

		while ( dataFreq < minFreqHz )
		{
			dataFreq += dataStepHz;
		}
		for ( dataFreq >= minFreqHz;dataFreq < maxFreqHz; dataFreq += freqCount* dataStepHz)
		{
			double TotalValue = 0;
			double val = 0;
			std::map<unsigned __int64,std::vector<short>>::iterator itFreqData = specimenData.find(dataFreq);
			for (int f = 0; f < freqCount;f++)
			{
				val = (itFreqData->second[Index])* 0.1;//文件中的数据是放大十倍的，这里先恢复
				TotalValue += pow(10,val/10);
			}
			TotalValue = 10*10*log10(TotalValue);//再放大十倍存入
			avgValues.push_back(TotalValue);
		}		
	}				
	return ret;
}

int EightPercent_MethodInBusinessType( map<unsigned __int64,vector<short>>& specimenData, short& noise, double startFreqMhz, double endFreqMhz ,double Ratio,std::vector<int>& dataInPeriods)
{
	int ret = NG_SUCCESS;

	int numRecord = 0;
	int numTwenty = 0;
	vector<short> avgValues;

	if (!GetAllMeasuredValuesInOneBusinessType(specimenData,avgValues,startFreqMhz,endFreqMhz,dataInPeriods))
	{
		return CALCULATE_SPECTRUM_AVG_ERROR;
	}

	if (0 == avgValues.size())
	{
		return NO_DATA_OF_THE_BAND;
	}

	std::sort(avgValues.begin(),avgValues.end());

	numRecord = avgValues.size();
	double num = EIGHTY_VALUE;
	if (Ratio >= 10 && Ratio <= 20)
	{
		num = Ratio/100.0;
	}
	numTwenty = ceil(numRecord * num);
	noise = UNCALCULATE;
	GetArithmeticMean(avgValues,numTwenty,noise);

	if ( UNCALCULATE != noise )
	{
		noise = noise * 0.1;
	}
	else
	{
		ret = EIGHTY_PERCENT_METHOD_ERROR;
	}
	return ret;

}

bool GetAllMeasuredValuesInOneBusinessType( map<unsigned __int64,vector<short>>& specimenData, vector<short>& avgValues, double startFreqMhz, double endFreqMhz,std::vector<int>& dataInPeriods )
{
	bool ret = true;
	unsigned __int64 maxFreqHz = endFreqMhz * 1000000;
	unsigned __int64 minFreqHz = startFreqMhz * 1000000;
	unsigned int num = 0 ;
	for (map<unsigned __int64,vector<short>>::iterator itData = specimenData.begin(); itData != specimenData.end(); ++itData)
	{
		if (itData->first >= minFreqHz && itData->first <= maxFreqHz)
		{
			num +=dataInPeriods.size(); 
		}
	}
	avgValues.reserve(num);
	for (map<unsigned __int64,vector<short>>::iterator itData = specimenData.begin(); itData != specimenData.end(); ++itData)
	{
		if (itData->first >= minFreqHz && itData->first <= maxFreqHz)
		{
			for ( unsigned int i = 0; i < dataInPeriods.size(); i++ )
			{
				avgValues.push_back(itData->second[dataInPeriods[i]]);
			}
		}
	}
	return ret;
}