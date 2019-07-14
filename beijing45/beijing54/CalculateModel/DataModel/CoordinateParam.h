#ifndef __COORDINATTE_PARAM_h
#define __COORDINATTE_PARAM_h

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string>

#include "EnumDef.h"
using namespace std;

typedef struct AddStationParam
{
	string mName;
	double mLg;
	double mLa;
	double mHeight;
	double mFreqBMHz;
	double mFreqEMHz;
	double mPowerdBm;
}AddStationParam;

typedef struct AddStationParam  AddIntStationParam;

typedef struct CoordinateStationParam
{
	string mID;
	string mName;
	double mdLg;
	double mdLa;
	double mdAntHeightASLM;
	double mdFreqMHz;
	double mdGaindBi;        //天线增益
	double mdPowerdBm;
	double mdAzimuth;        //天线方位角
	double mdUpAng;			 //天线仰角
}CoordinateStationParam;

typedef struct BorderCoordParam
{
	BorderCoordParam()
{
		mbIsInBorder = false;
		meHeightType = eAGroundL;
	}
	string mStatID;
	string mStatName;
	string mBusinessType;
	double mdStatFreqMHz;
	double mdStatLong;
	double mdStatLat;
	double mdThresholdDbuvm;
	double mdRxHeight;
	EHeightType meHeightType;
	int mnTransId;
	bool mbIsInBorder;
}BorderCoordParam;

struct frequencyBand 
{
	double sstartFreqMhz;
	double sendFreqMhz;
	double smeasures;
};

struct FreqsMonData
{
	double freqMhz;
	double value;
};

struct directionData
{
	double dstartFreqMhz;
	double dendFreqMhz;
	double dlongitude;
	double dlatitude;
	double dangle;
	bool   isOtherSignal;
};


#endif
