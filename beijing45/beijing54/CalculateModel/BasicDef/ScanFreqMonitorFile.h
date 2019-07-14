#ifndef _SCANFREQMONITORFILE_H_
#define _SCANFREQMONITORFILE_H_

#include <string.h>
#include "StandScanFreqMonitorFile.h"



//Basicdef/MacroDef.h 里面的宏MONITORFORMAT_TO_DBM
//MONITORFORMAT_TO_DBM 宏打开，读取扫频文件CScanFreqMonitorFile，读取类自动将数据转成dBm
//MONITORFORMAT_TO_DBM宏关闭，原始数据是什么类型就是什么类型，不做转换

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

	//重载一个时间比较的函数
	bool operator<(const ngtime& scmngtime)
	{		
		//比较年份
		if(this->wYear < scmngtime.wYear)
		{
			return true;
		}
		if(this->wYear > scmngtime.wYear)
		{
			return false;
		}

		//比较月份
		if(this->wMonth < scmngtime.wMonth)
		{
			return true;
		}
		if(this->wMonth > scmngtime.wMonth)
		{
			return false;
		}

		//比较日期
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

	//重载一个时间比较的函数
	bool operator>(const ngtime& scmngtime)
	{		
		//比较年份
		if(this->wYear < scmngtime.wYear)
		{
			return false;
		}
		if(this->wYear > scmngtime.wYear)
		{
			return true;
		}

		//比较月份
		if(this->wMonth < scmngtime.wMonth)
		{
			return false;
		}
		if(this->wMonth > scmngtime.wMonth)
		{
			return true;
		}

		//比较日期
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
	//copy构造函数
	ValueInTime(const ValueInTime& scmValueInTime);
	//赋值函数
	ValueInTime& operator=(const ValueInTime& scmValueInTime);
	//析构函数
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
	
	//添加一个接口，利用全局变量，不需要每次申请内存，只是在需要的空间比保留空间大时重新申请
	int ReadFile_Reserve(const char*strDataPath);
	//全局变量释放内存的接口
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
	//参考《超短波频段检测基础数据存储结构技术规范
	int ReadRMDFFile(const char* filename);
	int ReadRMDFFileHead(const char* filename);

	//当需要的空间大小不大于保留空间大小时，不重新申请空间
	int ResizeFreqBuffer(int nSize);	

	//当需要的空间大小不大于保留空间大小时，不重新申请空间
	int ResizeValueInTimeBuffer(int nRecordSize, int nFreqSize);
public:
	unsigned int m_nTotalRecordCount;
	short  m_DataType;//0功率[dBm],1电平[dBuV],2场强[dBuV/m]
	double m_dFreqMhzdf;//频率的间距
	double m_dFreqMhzMin;//最小频率
	double m_dFreqMhzMax;
	ngtime mfromtime;
	ngtime mendtime;
	ValueInTime* m_pValueInTime;
	unsigned int m_nValueInTimeSize; //保留的空间大小 
	unsigned int m_nTotalFreqCount;
	double* m_pFrequencyMHz;	
	unsigned int m_nFreqSize; //保留的空间大小 
	unsigned short m_ScanTimeMs;//采样间隔
	char mStationID[51];
	eScanFreqFormat mFormat;
};
#endif
