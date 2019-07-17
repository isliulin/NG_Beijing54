#include "handleScanFreqData.h"
#include "NG_ErrorCode.h"
#include "dataTypeChange.h"
handleScanFreqData::handleScanFreqData(string name) 
{
	this->name = name;
	maxx = 0.0;
	maxy = 0.0;
	minx = 10000000.0;
	miny = 10000000.0;
	mScanFreqData->reserve(1000);
	
}
int handleScanFreqData::handleData()
{
	CScanFreqMonitorFile G_cMonitorScanInfo;
	int returnCode=G_cMonitorScanInfo.ReadFile_Reserve(name.c_str());
	double *pFrequenceyMHZ =G_cMonitorScanInfo.m_pFrequencyMHz;
	int valueInTimeSize = G_cMonitorScanInfo.m_nValueInTimeSize;
	ValueInTime *pvalueInTime =G_cMonitorScanInfo.m_pValueInTime;
	scanFreqData sfd;
	for (int i = 0; i < valueInTimeSize; i++)
	{
		double lon = pvalueInTime[i].lon;
		double lat = pvalueInTime[i].lat;
		//音频广播
		double ser11 = 0.0; //中波调幅广播
		double ser12 = 0.0; //短波调幅广播
		double ser13 = 0.0; //调频广播
		 //电视及数字广播
		double ser21 = 0.0; //
		double ser22 = 0.0; // 甚高频和超高频
		double ser23 = 0.0;//
		double ser24 = 0.0;//
		 //通信
		double ser31 = 0.0; //
		double ser32 = 0.0; // 集群通信

		double ser33 = 0.0; //
		double ser34 = 0.0; //
		double ser35 = 0.0; //
		double ser36 = 0.0; // 数字微波通信 
		double ser37 = 0.0; //

		double ser38 = 0.0; // 短距离微波通信

		double ser39 = 0.0; // 移动通信
		double ser310 = 0.0; //
		double ser311 = 0.0; //
		

		float * pLevelValue = pvalueInTime[i].pdLevelValue;
		int valueNumber = pvalueInTime[i].nValueNumber;
		for (int j = 0; j < valueNumber; j++)
		{
			double levelValue = dataTypeChange::dbmTomw(pLevelValue[j]);
			if (0.525<=pFrequenceyMHZ[j]&&pFrequenceyMHZ[j]<=108) //音频业务
			{
				if (0.525<=pFrequenceyMHZ[j]&&pFrequenceyMHZ[j]<=1.605)
				{
					ser11 += levelValue;
				}
				else if (3.5 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 29.7)
				{
					ser12 += levelValue;
				}
				else if (88 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 108)
				{
					ser13 += levelValue;
				}
			}
			if (48.5 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 870)
			{
				if (48.5 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 92)
				{
					ser21 += levelValue;
				}
				else if (167 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 223)
				{
					ser22 += levelValue;
				}
				else if (223 < pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 443)
				{
					ser23 += levelValue;
				}
				else if (443 < pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 870)
				{
					ser24 += levelValue;
				}
			}
			if (351 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 6425) 
			{
				if (351 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 389) 
				{
					ser31 += levelValue;
				}
				if (806 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 866)
				{
					ser32 += levelValue;
				}
				if (1427 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 1525)
				{
					ser33 += levelValue;
				}
				if (3600 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 4200)
				{
					ser34 += levelValue;
				}
				if (4400<= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 5000)
				{
					ser35 += levelValue;
				}
				if (5925 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 6425)
				{
					ser36 += levelValue;
				}
				if (2400 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 2483.5)
				{
					ser37 += levelValue;
				}
				if (825 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 960)
				{
					ser38 += levelValue;
				}
				if (1710 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 2170)
				{
					ser39 += levelValue;
				}
				if (2300 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 2400)
				{
					ser310 += levelValue;
				}
				if (2500 <= pFrequenceyMHZ[j] && pFrequenceyMHZ[j] <= 2690)
				{
					ser311 += levelValue;
				}
			}
		}
		sfd.lat = lat;
		sfd.lon = lon;
		sfd.severiceNo1 = ser11;
		sfd.severiceNo2 = ser12;
		sfd.severiceNo3 = ser13;
		sfd.severiceNo4 = ser21+ser22+ser23+ser24;
		sfd.severiceNo5 = ser31 + ser32;
		sfd.severiceNo6 = ser33 + ser34 + ser35 + ser36;
		sfd.severiceNo7 = ser37;
		sfd.severiceNo8 = ser38 + ser39 + ser310 + ser311;


		mScanFreqData[0].push_back(sfd);
	
	}
	
	
	return returnCode;
}

void  handleScanFreqData::clear() 
{
	maxx = 0.0;
	maxy = 0.0;
	minx = 10000000.0;
	miny = 10000000.0;
	mScanFreqData->clear();
	mScanFreqData->shrink_to_fit();
}

handleScanFreqData::~handleScanFreqData() 
{
	clear();
}