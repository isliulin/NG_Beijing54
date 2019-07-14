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
	short mTRFlag;//0,������գ�1���䣬2����

}AssignFreqInfo;


typedef struct _OccupyStationInfo
{
	double mPowerLevel;//̨վ����ķ��书��
	double mCI;
	string mUserId;
	string mUserName;
	string mUserEquId;
	bool operator <(const _OccupyStationInfo& rhs) const //��������
	{
		return mPowerLevel<rhs.mPowerLevel;
	}
	bool operator >(const _OccupyStationInfo& rhs) const //��������
	{
		return mPowerLevel>rhs.mPowerLevel;
	}
}OccupyStationInfo;


typedef struct _occupyinfo
{
	double mFreqMhz;
	double mPowerLevel;//ռ��̨վ�е�������վ
	unsigned int mOccupyCount;
	float  mQuality;
	std::vector<OccupyStationInfo> mOccupyList;

	bool operator <(const _occupyinfo& rhs) const //��������
	{
		return mQuality<rhs.mQuality;
	}
	bool operator >(const _occupyinfo& rhs) const //��������
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
	std::vector<occupyinfo> mResults; //��Ƶ������
	//int mStationCount;//����վ��
	std::vector<AssignFreqInfo> mAssignFreqInfo;//ָ�䷽��
	int mNeedAssignFreqCount;//ָ��Ŀ����

public: 
};
