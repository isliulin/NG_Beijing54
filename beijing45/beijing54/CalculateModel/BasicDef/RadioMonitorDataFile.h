#pragma once
#include <vector>
/*
超短波频段监测基础数据存储结构
*/
// #define RMDF_CHECKCODE "RMDF"

#pragma pack(push, 1)

struct RMDFHeadFrame
{
	char	checkCode[4];	//固定为"RMDF"
	__int32	fileLen;
	__int16	fileType;
	char    blockFlag[4];	//固定为"fmt" 最后一位补'/0'
	__int32	dataInfoLen;	//数据信息长度
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
	
	char	dataFlag[4];/*固定为"data"*/
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

	char	dataFlag[4];/*固定为"data"*/
	__int32	dataLen;
};

struct DataFrame
{
	/*元素标识*/
	unsigned char preserveFlag[5];//保留位
	unsigned char overlayFlag;
	unsigned char positionFlag;
	unsigned char timeFlag;
	
	/*位置*/
	__int64	longitude;
	__int64	latitude;
	__int16	antHeight;

	/*时间*/
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
	__int32	freqSum;//一个扫描周期的总频点数
	double	rangeStartFreqHz;
	__int32	freqPointIndex;
	__int32 freqCount;//当前频段的频点数
};
#pragma pack(pop)


//频段
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
//频谱数据
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
	/*扫频数据*/
	SpectrumInfoFrame	m_RMDFHeadInfo;
	std::vector<SpectrumFramDataItem*> m_spectrumDatas;
	/*IQ数据*/
	IQInfoFrame			m_IQHeadInfo;
	std::vector<IQFrameDataItem*> m_IQDatas;
};
