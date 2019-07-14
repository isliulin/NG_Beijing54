#ifndef _STANDSCANFREQMONITORFILE_H_
#define _STANDSCANFREQMONITORFILE_H_
#include <string.h>
#include <vector>
enum eScanFreqFormat
{
	eUnknown=-1,
	eNGScanFreqV1=0,//����Ŀǰ�Ѿ�ʹ�õ�ɨƵ�ļ���ʽ��������γ����Ϣ
	eStandScanFreqV1=1,//���Ҹ�ʽ
	eStandScanFreqV2=2,//���Ҹ�ʽ��������
	eStandScanFreqV3=3,//2017����Ҹ�ʽ
	eRadioMonitor = 4 //���̲�Ƶ�μ���ļ�
};
#ifdef _MSC_VER
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif // _MSC_VER
//���Ҹ�ʽv1ͷ��Ϣ
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
	unsigned __int64 startfreq; //Ŀǰhz
	unsigned int freqstep;//Ŀǰhz
	unsigned int freqcount;
};

//���Ҹ�ʽv2ͷ��Ϣ,��������в����ֶΣ����ڱ߾�Э����
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
	unsigned __int64 startfreq; //Ŀǰhz
	unsigned int freqstep;//Ŀǰhz
	unsigned int freqcount;
};

//2017���Ҹ�ʽͷ��Ϣ
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
//���Ҹ�ʽһ����¼��Ϣ
typedef struct StandDataItem
{
    StandBinHeadV1 mHead;
	short *mVal; //10��ʵ�����ݹ��Ҹ�ʽ
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



//����·���ȡ��
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
	void swap(void * data,int n);//�����ֽ���
public:
	std::vector<StandDataItem*> mDatas;
	double m_dFreqMhzMin;//��СƵ��
	double m_dFreqMhzMax;//���Ƶ��
	eScanFreqFormat mFormat;
};

//���Ҹ�ʽһ����¼��Ϣ
typedef struct StandDataItemV2
{
	StandBinHeadV2 mHead;
	short *mVal; //10��ʵ�����ݹ��Ҹ�ʽ
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
//����·���ȡ��
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
	void swap(void * data,int n);//�����ֽ���

public:
	std::vector<StandDataItemV2*> mDatas;
	double m_dFreqMhzMin;//��СƵ��
	double m_dFreqMhzMax;//���Ƶ��
	eScanFreqFormat mFormat;
};


#endif
