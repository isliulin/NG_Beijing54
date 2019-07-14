#ifndef _STANDSCANFREQMONITORFILE_H_
#define _STANDSCANFREQMONITORFILE_H_
#include <string.h>
#include <vector>
enum eScanFreqFormat
{
	eUnknown=-1,
	eNGScanFreqV1=0,//恩巨目前已经使用的扫频文件格式，不带经纬度信息
	eStandScanFreqV1=1,//国家格式
	eStandScanFreqV2=2,//国家格式测向数据
	eStandScanFreqV3=3,//2017年国家格式
	eRadioMonitor = 4 //超短波频段监测文件
};
#ifdef _MSC_VER
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif // _MSC_VER
//国家格式v1头信息
struct StandBinHeadV1	
{
	unsigned int checkcode;
	unsigned short equ_no;
	unsigned char ant_type;
	short year;
	char mon;
	char day;
	char hour;
	char minute;
	char second;
	short misecond;
	double lon;
	double lat;
	unsigned int height;
	unsigned __int64 startfreq; //目前hz
	unsigned int freqstep;//目前hz
	unsigned int freqcount;
};

//国家格式v2头信息,监测数据有测向字段，用于边境协调中
struct StandBinHeadV2	
{
	unsigned int checkcode;
	unsigned short equ_no;
	unsigned char ant_type;
	short year;
	char mon;
	char day;
	char hour;
	char minute;
	char second;
	short misecond;
	double lon;
	double lat;
	short  waveAngle;
	unsigned int height;
	unsigned __int64 startfreq; //目前hz
	unsigned int freqstep;//目前hz
	unsigned int freqcount;
};

//2017国家格式头信息
struct StandBinHeadV3	
{
	unsigned int checkcode;
	unsigned short equ_no;
	unsigned char ant_type;
	short year;
	char mon;
	char day;
	char hour;
	char minute;
	char second;
	unsigned short misecond;
	unsigned short scanspeed; // GH/s
	unsigned __int64 lon; // 1e-8
	unsigned __int64 lat; //1e-8
	short height; // 0.1
	double startfreq;
	float freqstep;
	unsigned int freqcount;
};
#ifdef _MSC_VER
#pragma pack(pop)
#else
#pragma pack()
#endif // _MSC_VER
//国家格式一条记录信息
typedef struct StandDataItem
{
    StandBinHeadV1 mHead;
	short *mVal; //10倍实际数据国家格式
	StandDataItem()
	{
      mVal=NULL;
	}
	StandDataItem(unsigned int Count)
	{ 
	   if(Count>0)
	   	{
           mVal=new short[Count];
		   memset(mVal,0x81,Count*sizeof(short));
	   	}
	   else
	   	{
          mVal=NULL;
	   	}
	}

	~StandDataItem()
	{
       if(mVal) delete []mVal;
	   mVal=NULL;
	}
	
}StandDataItem;



//国家路测读取类
class CStandScanFreqMonitorFile
{
public:
	CStandScanFreqMonitorFile(eScanFreqFormat format = eUnknown);
	virtual ~CStandScanFreqMonitorFile();
	int ReadFileHead(const char*filename);
	int ReadFile(const char *filename);
	int CheckIsStandFormat(const char *filename);
	int CheckIsStandV3Format(const char *filename);
protected:
	int ReadStandv1(const char *filename);
	int ReadStandv3(const char *filename);
	int ReadStandv1head(const char *filename);
	int ReadStandv3head(const char *filename);
	void Clear();
	void swap(void * data,int n);//交换字节序
public:
	std::vector<StandDataItem*> mDatas;
	double m_dFreqMhzMin;//最小频率
	double m_dFreqMhzMax;//最大频率
	eScanFreqFormat mFormat;
};

//国家格式一条记录信息
typedef struct StandDataItemV2
{
	StandBinHeadV2 mHead;
	short *mVal; //10倍实际数据国家格式
	StandDataItemV2()
	{
		mVal=NULL;
	}
	StandDataItemV2(unsigned int Count)
	{
		if(Count>0)
		{
			mVal=new short[Count];
			memset(mVal,0x81,Count*sizeof(short));
		}
		else
		{
			mVal=NULL;
		}
	}

	~StandDataItemV2()
	{
		if(mVal) delete []mVal;
		mVal=NULL;
	}	
}StandDataItemV2;
//国家路测读取类
class CStandScanFreqMonitorFileV2
{
public:
	CStandScanFreqMonitorFileV2();
	virtual ~CStandScanFreqMonitorFileV2();
	int ReadFileHead(const char*filename);
	int ReadFile(const char *filename);
	int CheckIsStandV2Format(const char *filename);

protected:
	int ReadStandV2(const char *filename);	
	void Clear();
	void swap(void * data,int n);//交换字节序

public:
	std::vector<StandDataItemV2*> mDatas;
	double m_dFreqMhzMin;//最小频率
	double m_dFreqMhzMax;//最大频率
	eScanFreqFormat mFormat;
};


#endif
