#ifndef _SCANFREQMONITORFILE_H_
#define _SCANFREQMONITORFILE_H_

#include <string.h>
#include "StandScanFreqMonitorFile.h"



//Basicdef/MacroDef.h ����ĺ�MONITORFORMAT_TO_DBM
//MONITORFORMAT_TO_DBM ��򿪣���ȡɨƵ�ļ�CScanFreqMonitorFile����ȡ���Զ�������ת��dBm
//MONITORFORMAT_TO_DBM��رգ�ԭʼ������ʲô���;���ʲô���ͣ�����ת��

typedef struct ngtime
{
	short wYear;
	short wMonth;
	short wDay;
	short wHour;
	short wMinute;
	short wSecond;
	short wMilliseconds;
    
	ngtime()
	{
		wYear=0;
		wMonth=0;
		wDay=0;
		wHour=0;
		wMinute=0;
		wSecond=0;
		wMilliseconds=0;
	}

	//����һ��ʱ��Ƚϵĺ���
	bool operator<(const ngtime& scmngtime)
	{		
		//�Ƚ����
		if(this->wYear < scmngtime.wYear)
		{
			return true;
		}
		if(this->wYear > scmngtime.wYear)
		{
			return false;
		}

		//�Ƚ��·�
		if(this->wMonth < scmngtime.wMonth)
		{
			return true;
		}
		if(this->wMonth > scmngtime.wMonth)
		{
			return false;
		}

		//�Ƚ�����
		if(this->wDay < scmngtime.wDay)
		{
			return true;
		}
		if(this->wDay > scmngtime.wDay)
		{
			return false;
		}


		if(this->wHour < scmngtime.wHour)
		{
			return true;
		}
		if(this->wHour > scmngtime.wHour)
		{
			return false;
		}


		if(this->wMinute < scmngtime.wMinute)
		{
			return true;
		}
		if(this->wMinute > scmngtime.wMinute)
		{
			return false;
		}


		if(this->wSecond < scmngtime.wSecond)
		{
			return true;
		}
		if(this->wSecond > scmngtime.wSecond)
		{
			return false;
		}


		if(this->wMilliseconds < scmngtime.wMilliseconds)
		{
			return true;
		}
		if(this->wMilliseconds > scmngtime.wMilliseconds)
		{
			return false;
		}

		return false;
	}

	//����һ��ʱ��Ƚϵĺ���
	bool operator>(const ngtime& scmngtime)
	{		
		//�Ƚ����
		if(this->wYear < scmngtime.wYear)
		{
			return false;
		}
		if(this->wYear > scmngtime.wYear)
		{
			return true;
		}

		//�Ƚ��·�
		if(this->wMonth < scmngtime.wMonth)
		{
			return false;
		}
		if(this->wMonth > scmngtime.wMonth)
		{
			return true;
		}

		//�Ƚ�����
		if(this->wDay < scmngtime.wDay)
		{
			return false;
		}
		if(this->wDay > scmngtime.wDay)
		{
			return true;
		}


		if(this->wHour < scmngtime.wHour)
		{
			return false;
		}
		if(this->wHour > scmngtime.wHour)
		{
			return true;
		}


		if(this->wMinute < scmngtime.wMinute)
		{
			return false;
		}
		if(this->wMinute > scmngtime.wMinute)
		{
			return true;
		}


		if(this->wSecond < scmngtime.wSecond)
		{
			return false;
		}
		if(this->wSecond > scmngtime.wSecond)
		{
			return true;
		}


		if(this->wMilliseconds < scmngtime.wMilliseconds)
		{
			return false;
		}
		if(this->wMilliseconds > scmngtime.wMilliseconds)
		{
			return true;
		}

		return false;
	}

	//t1 >= t2
	bool operator>=(const ngtime& t)
	{
		if ( *this < t )
		{
			return false;
		}

		return true;
	}

	//t1 <= t2
	bool operator<=(const ngtime& t)
	{
		if ( *this > t )
		{
			return false;
		}

		return true;
	}

	//t1 == t2 
	bool operator==(const ngtime& t)
	{
		if ( *this < t || *this > t )
		{
			return false;
		}

		return true;
	}

}ngtime;

struct ValueInTime
{   
	ngtime tTime;
	float* pdLevelValue;
	long nValueNumber;
	float lon;
	float lat;
	//float height;
	ValueInTime();
	ValueInTime(long nValueNumber);
	//copy���캯��
	ValueInTime(const ValueInTime& scmValueInTime);
	//��ֵ����
	ValueInTime& operator=(const ValueInTime& scmValueInTime);
	//��������
	~ValueInTime();
};






class CScanFreqMonitorFile
{
public:
	CScanFreqMonitorFile();

/*
#ifndef STAND_MONITORFORMAT_V1
CScanFreqMonitorFile(eScanFreqFormat FormatType=eNGScanFreqV1);
#else
CScanFreqMonitorFile(eScanFreqFormat FormatType=eStandScanFreqV1);
#endif*/

    virtual ~CScanFreqMonitorFile();	
	int ReadFile(const char *filename);
	
	//���һ���ӿڣ�����ȫ�ֱ���������Ҫÿ�������ڴ棬ֻ������Ҫ�Ŀռ�ȱ����ռ��ʱ��������
	int ReadFile_Reserve(const char*strDataPath);
	//ȫ�ֱ����ͷ��ڴ�Ľӿ�
	void freeGlobalvar();

	int ReadFileHead(const char *filename);	
	int GetDataType(){return m_DataType;}
	int TryReadHead( const char *filename, eScanFreqFormat &headtype );
protected:
	bool IsLittleEndian();
	void SwapData(void * data,int n);
	void Clear();
	int ReadNGV1(const char *filename);
	int ReadStandV1(const char *filename,eScanFreqFormat headtype);
	int ReadStandV1_Reserve(const char *filename,eScanFreqFormat headtype);
	int ReadNGV1Head(const char *filename);
	int ReadStandV1Head(const char *filename,eScanFreqFormat headtype);
	int ReadStandV2(const char *filename);
	int ReadStandV2Head(const char *filename);
	int CheckNGV1Head(const char *filename);
	//RMDF: Radio Monitoring Data Format 
	//�ο������̲�Ƶ�μ��������ݴ洢�ṹ�����淶
	int ReadRMDFFile(const char* filename);
	int ReadRMDFFileHead(const char* filename);

	//����Ҫ�Ŀռ��С�����ڱ����ռ��Сʱ������������ռ�
	int ResizeFreqBuffer(int nSize);	

	//����Ҫ�Ŀռ��С�����ڱ����ռ��Сʱ������������ռ�
	int ResizeValueInTimeBuffer(int nRecordSize, int nFreqSize);
public:
	unsigned int m_nTotalRecordCount;
	short  m_DataType;//0����[dBm],1��ƽ[dBuV],2��ǿ[dBuV/m]
	double m_dFreqMhzdf;//Ƶ�ʵļ��
	double m_dFreqMhzMin;//��СƵ��
	double m_dFreqMhzMax;
	ngtime mfromtime;
	ngtime mendtime;
	ValueInTime* m_pValueInTime;
	unsigned int m_nValueInTimeSize; //�����Ŀռ��С 
	unsigned int m_nTotalFreqCount;
	double* m_pFrequencyMHz;	
	unsigned int m_nFreqSize; //�����Ŀռ��С 
	unsigned short m_ScanTimeMs;//�������
	char mStationID[51];
	eScanFreqFormat mFormat;
};
#endif
