#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
struct roadData
{
	int mData_id;//0
	int mData_time;//1
	double mElectric;//2
	double mBattery;//10
	double mLng;//11
	double mLat;//12
	vector<string> p;
	roadData()
	{
		mData_id=0;//0
		mData_time=0;//1
		mElectric=0.0;//2
		mBattery=0.0;//10
		mLng=0.0;//11
		mLat=0.0;//12	
		
	}
};