#pragma once
#include"pch.h"
#include <Windows.h>
#include "exportDefine.h"
#include <iostream>
#include <ostream>
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
	int size;
	double minx;
	double miny;
	double maxx;
	double maxy;
	vector<double*> *threeNodeVector;
public :	
	vector<roadData> *mRoadData ;
	vector<scanFreqData> *mFreqData;
public:
	map<long int, roadNode> *nodeData;
	map<long int,roadNode> *nodeData_50;
	map<long int, roadNode> *nodeData_200;
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
	void setNGBSize(int size) { this->size = size; }
private:

	RasterResult *ngb_ser1;
	RasterResult *ngb_ser1_Node;
	RasterResult *ngb_ser2;
	RasterResult *ngb_ser2_Node;
	RasterResult *ngb_ser3;
	RasterResult *ngb_ser3_Node;
	RasterResult *ngb_ser4;
	RasterResult *ngb_ser4_Node;
	RasterResult *ngb_ser5;
	RasterResult *ngb_ser5_Node;
	RasterResult *ngb_ser6;
	RasterResult *ngb_ser6_Node;
	RasterResult *ngb_ser7;
	RasterResult *ngb_ser7_Node;
	RasterResult *ngb_ser8;
	RasterResult *ngb_ser8_Node;
	RasterResult *ngb_Elec;
	RasterResult *ngb_Elec_Node;
	
public:
	//void generThreeNode(string flag,int i);
	void generateRaster(); //generate S/B RasterResult (ser1-ser8)
	void generateMergeRaster(double DATA_LEVEL,int i); // generate ser1_Node;
	//void generateMergeRaster_1(double DATA_LEVEL, int i);
};
