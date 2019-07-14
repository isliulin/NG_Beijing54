#pragma once
#include <vector>
#include <string>

using namespace std;

class CNGFrequencyPreselResult
{
public:
	CNGFrequencyPreselResult(void);
	virtual ~CNGFrequencyPreselResult(void);
public:
	std::string txId;
	std::string rxId;
public:
	std::vector<double> DownlinkPowerList;
	std::vector<int> DownlinkInterfercountList;
	std::vector<double> DownlinkQualityList;
	std::vector<double> DownlinkCIList;
	std::vector<double>DownlinkFreqList;

	std::vector<double> UplinkPowerList;
	std::vector<int> UplinkInterfercountList;
	std::vector<double> UplinkQualityList;
	std::vector<double> UplinkCIList;
	std::vector<double> UplinkFreqList;
public: 
	void Clear();
	bool IsDownLinkValid() const;
	bool IsUpLinkValid() const;
	unsigned int GetDownLinkSize() const;
	unsigned int GetUpLinkSize() const;
};

typedef struct AssignFreqInfo
{
	float mFreqMHz;
	float mQuality;
	short mTRFlag;//0,发射接收，1发射，2接收

}AssignFreqInfo;


typedef struct _OccupyStationInfo
{
	double mPowerLevel;//台站本身的发射功率
	double mCI;
	string mUserId;
	string mUserName;
	string mUserEquId;
	bool operator <(const _OccupyStationInfo& rhs) const //升序排序
	{
		return mPowerLevel<rhs.mPowerLevel;
	}
	bool operator >(const _OccupyStationInfo& rhs) const //降序排序
	{
		return mPowerLevel>rhs.mPowerLevel;
	}
}OccupyStationInfo;


typedef struct _occupyinfo
{
	double mFreqMhz;
	double mPowerLevel;//占用台站中的最大干扰站
	unsigned int mOccupyCount;
	float  mQuality;
	std::vector<OccupyStationInfo> mOccupyList;

	bool operator <(const _occupyinfo& rhs) const //升序排序
	{
		return mQuality<rhs.mQuality;
	}
	bool operator >(const _occupyinfo& rhs) const //降序排序
	{
		return mQuality>rhs.mQuality;
	}

}occupyinfo;

class CNGFrequencyOccupyResult
{
public:
	CNGFrequencyOccupyResult(void){}
	virtual ~CNGFrequencyOccupyResult(void)
	{
		Clear();
	}
	void Clear()
	{

		mResults.clear();
		mAssignFreqInfo.clear();
		//mStationCount=0;
		mNeedAssignFreqCount=0;
	}
public:
	std::vector<occupyinfo> mResults; //按频率排序
	//int mStationCount;//干扰站数
	std::vector<AssignFreqInfo> mAssignFreqInfo;//指配方案
	int mNeedAssignFreqCount;//指配目标数

public: 
};
