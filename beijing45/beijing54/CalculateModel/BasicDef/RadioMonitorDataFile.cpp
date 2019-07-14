#include <stdlib.h>
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <fstream>
#include <io.h>
#include "RadioMonitorDataFile.h"
#include "NG_ErrorCode.h"
#include "..\..\NGLog\NGLogPrint.h"

CRadioMonitorDataFile::CRadioMonitorDataFile(void)
{
}

CRadioMonitorDataFile::~CRadioMonitorDataFile(void)
{
	clear();
}

int CRadioMonitorDataFile::ReadFile_Spectrum( const char* filename )
{
	if (NULL == filename || access(filename,0)!=0 )
	{
		return NG_MONITORFILE_OPEN_ERROR;//文件不存在
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return NG_MONITORFILE_OPEN_ERROR;//打开文件失败
	} 

	bool shouldswap = false;
	fread(&m_RMDFHead,1,sizeof(RMDFHeadFrame),fp);
	if (!CheckHead(m_RMDFHead.checkCode))
	{
		swap(&m_RMDFHead.checkCode,4);
		if (CheckHead(m_RMDFHead.checkCode))
		{
			shouldswap = true;
		}
		else
		{
			fclose(fp);
			return INVALIDSCANFORMAT;
		}
	}

	fread(&m_RMDFHeadInfo,1,sizeof(RMDFHeadFrame),fp);
	if (shouldswap)
	{
		swap(&m_RMDFHeadInfo.monitorFacilityID,14);
		swap(&m_RMDFHeadInfo.monitorDeviceID,36);
		swap(&m_RMDFHeadInfo.monitorType,2);
		swap(&m_RMDFHeadInfo.longitude,sizeof(__int64));
		swap(&m_RMDFHeadInfo.latitude,sizeof(__int64));
		swap(&m_RMDFHeadInfo.antHeight,sizeof(__int16));
		swap(&m_RMDFHeadInfo.begingTimeSec,sizeof(__int32));
		swap(&m_RMDFHeadInfo.measureTimeSec,sizeof(__int16));
		swap(&m_RMDFHeadInfo.startFreqHz,sizeof(double));
		swap(&m_RMDFHeadInfo.stopFreqHz,sizeof(double));
		swap(&m_RMDFHeadInfo.stepHz,sizeof(float));
		swap(&m_RMDFHeadInfo.polarMethod,2);
		swap(&m_RMDFHeadInfo.dataFlag,4);
		swap(&m_RMDFHeadInfo.dataLen,sizeof(__int32));
	}

	while(feof(fp) == 0)
	{
		SpectrumFramDataItem *pframedataItem = new SpectrumFramDataItem;
		fread(&pframedataItem->dataFrameHead,1,sizeof(DataFrame),fp);
		if (shouldswap)
		{
			swap(&pframedataItem->dataFrameHead.preserveFlag,5*sizeof(unsigned char));
			swap(&pframedataItem->dataFrameHead.overlayFlag,sizeof(unsigned char));
			swap(&pframedataItem->dataFrameHead.positionFlag,sizeof(unsigned char));
			swap(&pframedataItem->dataFrameHead.timeFlag,sizeof(unsigned char));
			swap(&pframedataItem->dataFrameHead.longitude,sizeof(__int64));
			swap(&pframedataItem->dataFrameHead.latitude,sizeof(__int64));
			swap(&pframedataItem->dataFrameHead.antHeight,sizeof(__int16));
			swap(&pframedataItem->dataFrameHead.year,sizeof(__int16));
			swap(&pframedataItem->dataFrameHead.month,sizeof(__int8));
			swap(&pframedataItem->dataFrameHead.day,sizeof(__int8));
			swap(&pframedataItem->dataFrameHead.hour,sizeof(__int8));
			swap(&pframedataItem->dataFrameHead.minite,sizeof(__int8));
			swap(&pframedataItem->dataFrameHead.second,sizeof(__int8));
			swap(&pframedataItem->dataFrameHead.nanosec,sizeof(__int32));
		}
		
		/*频段逐个读取*/
		int freqcount = 0; 
		int bflag = true;
		while(bflag)
		{
			ScanRangeItem rangeItem;
			fread(&rangeItem.scanRangeHead,1,sizeof(ScanRangeHead),fp);
			if (shouldswap)
			{
				swap(&rangeItem.scanRangeHead.freqSum,sizeof(__int32));
				swap(&rangeItem.scanRangeHead.rangeStartFreqHz,sizeof(double));
				swap(&rangeItem.scanRangeHead.freqPointIndex,sizeof(__int32));
				swap(&rangeItem.scanRangeHead.freqCount,sizeof(__int32));
			}
			freqcount += rangeItem.scanRangeHead.freqCount;
			rangeItem.pRangeValue = new __int16[rangeItem.scanRangeHead.freqCount];
			int readlen=fread(rangeItem.pRangeValue,sizeof(__int16),rangeItem.scanRangeHead.freqCount,fp);
			if (shouldswap)
			{
				for (int i=0;i<rangeItem.scanRangeHead.freqCount;i++)
				{
					swap(&rangeItem.pRangeValue[i],sizeof(__int16));
				}
			}
			
			pframedataItem->vRangeData.push_back(rangeItem);

			if (readlen == 0)
				bflag = false;

			if (freqcount >= rangeItem.scanRangeHead.freqSum)
				bflag = false;
		}

		m_spectrumDatas.push_back(pframedataItem);
	}
	fclose(fp);

	return NG_SUCCESS;
}


int CRadioMonitorDataFile::ReadFile_IQ( const char* filename )
{
	if (filename == NULL || access(filename,0)!=0 )
	{
		return NG_MONITORFILE_OPEN_ERROR;
	}

	FILE* fp = fopen(filename,"rb");
	if (fp == NULL)
	{
		return NG_MONITORFILE_OPEN_ERROR;//文件不存在
	}

	bool shouldswap = false;
	fread(&m_RMDFHead,1,sizeof(RMDFHeadFrame),fp);
	if (!CheckHead(m_RMDFHead.checkCode))
	{
		swap(&m_RMDFHead.checkCode,4);
		if (CheckHead(m_RMDFHead.checkCode))
		{
			shouldswap = true;
		}
		else
		{
			fclose(fp);
			return INVALIDSCANFORMAT;
		}
	}
	
	fread(&m_RMDFHeadInfo,1,sizeof(RMDFHeadFrame),fp);
	if (shouldswap)
	{
		swap(&m_RMDFHeadInfo.monitorFacilityID,14);
		swap(&m_RMDFHeadInfo.monitorDeviceID,36);
		swap(&m_RMDFHeadInfo.monitorType,2);
		swap(&m_RMDFHeadInfo.longitude,sizeof(__int64));
		swap(&m_RMDFHeadInfo.latitude,sizeof(__int64));
		swap(&m_RMDFHeadInfo.antHeight,sizeof(__int16));
		swap(&m_RMDFHeadInfo.begingTimeSec,sizeof(__int32));
		swap(&m_RMDFHeadInfo.measureTimeSec,sizeof(__int16));
		swap(&m_RMDFHeadInfo.startFreqHz,sizeof(double));
		swap(&m_RMDFHeadInfo.stopFreqHz,sizeof(double));
		swap(&m_RMDFHeadInfo.polarMethod,2);
		swap(&m_RMDFHeadInfo.dataFlag,4);
		swap(&m_RMDFHeadInfo.dataLen,sizeof(__int32));
	}

	while(feof(fp) == 0)
	{
		IQFrameDataItem *pframedataItem = new IQFrameDataItem;

		fread(&pframedataItem->dataFrameHead,1,sizeof(DataFrame),fp);
		if (shouldswap)
		{
			swap(&pframedataItem->dataFrameHead.preserveFlag,5*sizeof(unsigned char));
			swap(&pframedataItem->dataFrameHead.overlayFlag,sizeof(unsigned char));
			swap(&pframedataItem->dataFrameHead.positionFlag,sizeof(unsigned char));
			swap(&pframedataItem->dataFrameHead.timeFlag,sizeof(unsigned char));
			swap(&pframedataItem->dataFrameHead.longitude,sizeof(__int64));
			swap(&pframedataItem->dataFrameHead.latitude,sizeof(__int64));
			swap(&pframedataItem->dataFrameHead.antHeight,sizeof(__int16));
			swap(&pframedataItem->dataFrameHead.year,sizeof(__int16));
			swap(&pframedataItem->dataFrameHead.month,sizeof(__int8));
			swap(&pframedataItem->dataFrameHead.day,sizeof(__int8));
			swap(&pframedataItem->dataFrameHead.hour,sizeof(__int8));
			swap(&pframedataItem->dataFrameHead.minite,sizeof(__int8));
			swap(&pframedataItem->dataFrameHead.second,sizeof(__int8));
			swap(&pframedataItem->dataFrameHead.nanosec,sizeof(__int32));
		}

		fread(&pframedataItem->iqdataCount,1,sizeof(__int16),fp);
		if (shouldswap)
		{
			swap(&pframedataItem->iqdataCount,sizeof(__int16));
		}

		pframedataItem->pIQdata = new __int16[pframedataItem->iqdataCount*2];

		int readlen=fread(&pframedataItem->pIQdata,sizeof(__int16),pframedataItem->iqdataCount*2,fp);
		if (shouldswap)
		{
			for (int i=0;i<pframedataItem->iqdataCount;i++)
			{
				swap(&pframedataItem->pIQdata[i],sizeof(__int16));
			}
		}

		if (readlen == 0)
			break;

		m_IQDatas.push_back(pframedataItem);	
	}
	fclose(fp);

	return NG_SUCCESS;
}



int CRadioMonitorDataFile::CheckIsRMDFFormat( const char* filename )
{
	if (NULL == filename || access(filename,0)!=0 )
	{
		return THE_FILE_IS_NOT_EXIST;//文件不存在
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return FAIL_TO_OPEN_FILE;//打开文件失败
	} 

	bool shouldswap = false;
	fread(&m_RMDFHead,1,sizeof(RMDFHeadFrame),fp);
	if (!CheckHead(m_RMDFHead.checkCode))
	{
		swap(&m_RMDFHead.checkCode,4);
		if (CheckHead(m_RMDFHead.checkCode))
		{
			shouldswap = true;
		}
		else
		{
			fclose(fp);
			return INVALIDSCANFORMAT;
		}
	}

	fclose(fp);
	return NG_SUCCESS;
}



void CRadioMonitorDataFile::swap( void *data,int n )
{
	char * cdata = (char*)data;
	int bn = n/2;
	char tmp;
	for(int i=0;i<bn;i++)
	{
		tmp = cdata[i];
		cdata[i] = cdata[n-1-i];
		cdata[n-1-i] = tmp;
	}
}

void CRadioMonitorDataFile::clear()
{
	for (int i=0;i<m_spectrumDatas.size();i++)
	{
		if (m_spectrumDatas[i] != NULL)
		{
			delete m_spectrumDatas[i];
			m_spectrumDatas[i] = NULL;
		}
	}

	for (int i=0;i<m_IQDatas.size();i++)
	{
		if (m_IQDatas[i] != NULL)
		{
			delete m_IQDatas[i];
			m_IQDatas[i] = NULL;
		}
	}
}

bool CRadioMonitorDataFile::CheckHead( char *head )
{
	if (head[0] == 'R'&&head[1] == 'M'&&head[2] == 'D'&&head[3] == 'F')
	{
		return true;
	}
	return false;
}
