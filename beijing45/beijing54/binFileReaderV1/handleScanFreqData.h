#pragma once
#include "../CalculateModel/BasicDef/ScanFreqMonitorFile.h"
#include "binDataDef.h"
#include <iostream>
#include <vector>
#include "define.h"
using namespace std;

class BINFILEREADER_API handleScanFreqData
{
private:
	string name;
public:
	double maxx, maxy, minx, miny;
public :
	vector<scanFreqData> *mScanFreqData = new vector<scanFreqData>[1];
public:
	void handleData();
	handleScanFreqData(string name);

};

