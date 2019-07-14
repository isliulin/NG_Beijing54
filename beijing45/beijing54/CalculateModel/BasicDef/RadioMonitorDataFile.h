#pragma once
#include <vector>
/*
���̲�Ƶ�μ��������ݴ洢�ṹ
*/
// #define RMDF_CHECKCODE "RMDF"

#pragma pack(push, 1)

struct RMDFHeadFrame
{
	char	checkCode[4];	//�̶�Ϊ"RMDF"
	__int32	fileLen;
	__int16	fileType;
	char    blockFlag[4];	//�̶�Ϊ"fmt" ���һλ��'/0'
	__int32	dataInfoLen;	//������Ϣ����
};

struct SpectrumInfoFrame
{
	char	monitorFacilityID[14];
	char	monitorDeviceID[36];
	char	monitorType[2];
	__int64	longitude;
	__int64	latitude;
	__int16	antHeight;
	__int32	begingTimeSec;
	__int16 measureTimeSec;
	double	startFreqHz;
	double	stopFreqHz;
	float	stepHz;
	char	polarMethod[2];
	
	char	dataFlag[4];/*�̶�Ϊ"data"*/
	__int32	dataLen;
};

struct IQInfoFrame
{
	char	monitorFacilityID[14];
	char	monitorDeviceID[36];
	char	monitorType[2];
	__int64	longitude;
	__int64	latitude;
	__int16	antHeight;
	__int32	begingTimeSec;
	__int16 measureTimeSec;
	double	centerFreqHz;
	float	bandHz;
	char	polarMethod[2];	

	char	dataFlag[4];/*�̶�Ϊ"data"*/
	__int32	dataLen;
};

struct DataFrame
{
	/*Ԫ�ر�ʶ*/
	unsigned char preserveFlag[5];//����λ
	unsigned char overlayFlag;
	unsigned char positionFlag;
	unsigned char timeFlag;
	
	/*λ��*/
	__int64	longitude;
	__int64	latitude;
	__int16	antHeight;

	/*ʱ��*/
	unsigned __int16	year;
	unsigned __int8		month;
	unsigned __int8		day;
	unsigned __int8		hour;
	unsigned __int8		minite;
	unsigned __int8		second;
	unsigned __int32	nanosec;
};


struct ScanRangeHead
{
	__int32	freqSum;//һ��ɨ�����ڵ���Ƶ����
	double	rangeStartFreqHz;
	__int32	freqPointIndex;
	__int32 freqCount;//��ǰƵ�ε�Ƶ����
};
#pragma pack(pop)


//Ƶ��
struct ScanRangeItem
{
	ScanRangeHead scanRangeHead;
	__int16 *pRangeValue;
	ScanRangeItem()
	{
		pRangeValue = NULL;
	}
	~ScanRangeItem()
	{
		if (pRangeValue != NULL)
		{
			delete [] pRangeValue;
			pRangeValue = NULL;
		}
	}
};
//Ƶ������
struct SpectrumFramDataItem
{
	DataFrame dataFrameHead;
	std::vector<ScanRangeItem> vRangeData;
};

struct IQFrameDataItem
{
	DataFrame dataFrameHead;
	__int16	  iqdataCount;
	__int16	  *pIQdata;
	~IQFrameDataItem()
	{
		if (pIQdata != NULL)
		{
			delete [] pIQdata;
			pIQdata = NULL;
		}
	}
};

class CRadioMonitorDataFile
{
public:
	CRadioMonitorDataFile(void);
	~CRadioMonitorDataFile(void);
public:
	int ReadFile_Spectrum(const char* filename);
	int ReadFile_IQ(const char* filename);
	int CheckIsRMDFFormat(const char* filename);

private:
	bool CheckHead(char *head);
	void clear();
	void swap(void *data,int n);

public:
	RMDFHeadFrame		m_RMDFHead;
	/*ɨƵ����*/
	SpectrumInfoFrame	m_RMDFHeadInfo;
	std::vector<SpectrumFramDataItem*> m_spectrumDatas;
	/*IQ����*/
	IQInfoFrame			m_IQHeadInfo;
	std::vector<IQFrameDataItem*> m_IQDatas;
};
