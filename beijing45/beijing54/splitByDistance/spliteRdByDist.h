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
#include "../CalculateModel/BasicDef/NG_ErrorCode.h"
#include "../CalculateModel/CalResultWrapper/RasterResult.h"
#include <map>


class SPLITE_API spliteRoadData 
{
private:
	int needReadExcel;
	int needReadBin;
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
	void setHsfdName(string name) { this->hsfd->setName(name); }
	int readBIN();
	void readExcel();
	void getMaxRect();
	void generateNode();
	void setNeedReadExcel(int num) { this->needReadExcel = num; }
	void setNeedReadBin(int num) { this->needReadBin = num; }
private:

	RasterResult *ngz_ser1;
	RasterResult *ngz_ser2;
	RasterResult *ngz_ser3;
	RasterResult *ngz_ser4;
	RasterResult *ngz_ser5;
	RasterResult *ngz_ser6;
	RasterResult *ngz_ser7;
	RasterResult *ngz_ser8;
	RasterResult *ngz_Elec;
public:
	
	void generateRaster();


};
