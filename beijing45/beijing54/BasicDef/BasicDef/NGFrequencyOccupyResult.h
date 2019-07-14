#pragma once
#include <vector>
#include <string>

typedef struct _occupyinfo
{   
	double mFreqMhz;
    unsigned int mOccupyCount;
	double mMaxPowerLevel;
	string mMaxPowerLevelUserId;
    string mUserName;
}occupyinfo;

class CNGFrequencyOccupyResult
{
public:
	CNGFrequencyOccupyResult(void){}
	virtual ~CNGFrequencyOccupyResult(void){}
public:
    std::vector<occupyinfo> mResults;
	int mStationCount;
public: 
};
