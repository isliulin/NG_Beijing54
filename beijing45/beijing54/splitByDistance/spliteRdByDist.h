#pragma once
#include"pch.h"
#include <Windows.h>
#include "exportDefine.h"
#include <iostream>
#include <vector>
#include "../CalculateModel/BasicDef/ScanFreqMonitorFile.h"
#include "../xlsxFileReader/handleData.h"
#include "../binFileReaderV1/handleScanFreqData.h"
#include "../xlsxFileReader/dataDef.h"
#include "../xlsxFileReader/libexcel/include_cpp/libxl.h"
#include "../binFileReaderV1/binDataDef.h"
#include "dataDef.h"
#include <map>

class SPLITE_API spliteRoadData 
{
private:
	handleRoadData *hrd;
	handleScanFreqData *hsfd;
public:
	double minx;
	double miny;
	double maxx;
	double maxy;
public :	
	vector<roadData> *mRoadData ;
	vector<scanFreqData> *mFreqData;
public:
	map<long int,roadNode> *nodeData;
public :
	spliteRoadData(string excelFileName,string binFileName);
	~spliteRoadData();

	void readBIN();
	void readExcel();
	void getMaxRect();
	void generateNode();
};
