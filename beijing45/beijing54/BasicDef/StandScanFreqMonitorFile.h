#ifndef _STANDSCANFREQMONITORFILE_H_
#define _STANDSCANFREQMONITORFILE_H_
#include <string.h>
#include <vector>
enum eScanFreqFormat
{
eUnknown=-1,
eNGScanFreqV1=0,//����Ŀǰ�Ѿ�ʹ�õ�ɨƵ�ļ���ʽ��������γ����Ϣ
eStandScanFreqV1=1,//���Ҹ�ʽ

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

CStandScanFreqMonitorFile()
{

  mFormat=eStandScanFreqV1;
}
virtual ~CStandScanFreqMonitorFile();
int ReadFileHead(const char*filename);
int ReadFile(const char *filename);
int CheckIsStandFormat(const char *filename);
protected:
int ReadStandV1(const char *filename);	
void Clear();
void swap(void * data,int n);//�����ֽ���
public:

std::vector<StandDataItem*> mDatas;
double m_dFreqMhzMin;//��СƵ��
double m_dFreqMhzMax;//���Ƶ��
eScanFreqFormat mFormat;


};


#endif
