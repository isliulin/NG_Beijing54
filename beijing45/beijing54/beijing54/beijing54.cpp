#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "../CalculateModel/BasicDef/NG_ErrorCode.h"
#include "ScanFreqMonitorFile.h"
#include "StandScanFreqMonitorFile.h"
#include "handleScanFreqData.h"
#include "binDataDef.h"
#include "../splitByDistance/spliteRdByDist.h"
#include <string>
#include <stdio.h>
#include <iomanip>
#include "../splitByDistance/dataDef.h"
#include "../BasicDef/globalfunction.h"
int main()
{
#if 1
	// CScanFreqMonitorFile G_cMonitorScanInfo;
	string filename1 = "C://Users//10379//Desktop//test.bin";
	string filename2 = "D://GJUNWORKDATA//beijingDATA//Beijing45Data//16-20-08_10MHz-6GHz-EN-45.bin";
	string filename3= "D://GJUNWORKDATA//beijingDATA//Beijing45Data//10-44-48_10MHz-6GHz-SE45.bin";
	string filename4 = "D://GJUNWORKDATA//beijingDATA//Beijing45Data//13-57-27_10MHz-6GHz-wn5.bin";
	//handleScanFreqData *ss = new handleScanFreqData(filename1.c_str());
	//ss->handleData();
	
	
	//
	////G_cMonitorScanInfo.ReadFile_Reserve(filename.c_str());
	string filename = "C://Users//10379//Desktop//test.xlsx";
	spliteRoadData *srd = new spliteRoadData(filename,"");
	srd->setNGBSize(1);
	for (int i = 1; i <= 10; i++)
	{
		char* filename=NULL;
		filename = new char[100];
		sprintf(filename, "D://GJUNWORKDATA//beijingDATA//Beijing45Data//%d.bin", i);
		string name = filename;
		srd->setHsfdName(filename);
		if (i == 1)
		{
			srd->setNeedReadExcel(1);
			srd->setNeedReadBin(1);
		}
		else {
			srd->setNeedReadExcel(0);
			
		}
		srd->generateNode();
	}

	srd->generateRaster();
	
	vector<roadData> *rd = srd->mRoadData;
	vector<scanFreqData> *sfd = srd->mFreqData;
	map<long int, roadNode> *rn50 = srd->nodeData_50;
	map<long int, roadNode> *rn200 = srd->nodeData_200;

	/*spliteRoadData *srd = new spliteRoadData(filename,filename1);
	srd->readBIN(filename1);
	delete srd;*/
	/*map<long int, roadNode> *ll = srd->nodeData;
	map<long int, roadNode>::iterator llyt= ll[0].begin();
	roadNode lpok = llyt->second;*/
	//ofstream outfileExcel("excelData.txt",ios::out);
	ofstream outfileNode50("NodeData50.txt", ios::out);
	ofstream outfileNode200("NodeData200.txt", ios::out);
	
	/*for (auto it = rd[0].begin(); it != rd[0].end(); it++) 
	{
		roadData temp1 = *it;
		outfileExcel << temp1.mLng << ',' << temp1.mLat << ',' << temp1.mElectric << ',' << temp1.mBattery << endl;
	}
	outfileExcel.close();
	for (auto it = sfd[0].begin(); it != sfd[0].end(); it++)
	{
		scanFreqData temp2 = *it;
		outfileBin << temp2.lon << ',' << temp2.lat << ',' << temp2.severiceNo1 << ',' << temp2.severiceNo2 << ',' << temp2.severiceNo3<< ',' << temp2.severiceNo4 << ',' << temp2.severiceNo5 << ',' << temp2.severiceNo6 << ',' << temp2.severiceNo7 << ',' << temp2.severiceNo8 << ',' << endl;
	}
	outfileBin.close();*/
	for (auto it = rn50[0].begin(); it != rn50[0].end(); it++)
	{
		roadNode temp2 = it->second;
		outfileNode50 <<std::setprecision(11)<< temp2.lon<<',';
		outfileNode50 << std::setprecision(11) << temp2.lat << ',';
		outfileNode50 << std::setprecision(11) << temp2.time<< ',';
		outfileNode50 << std::setprecision(11) << temp2.serCount<<',';
 		outfileNode50 << std::setprecision(11) << temp2.serNo1 << ',';
		outfileNode50 << std::setprecision(11) << temp2.serNo2 << ',';
		outfileNode50 << std::setprecision(11) << temp2.serNo3 << ',';
		outfileNode50 << std::setprecision(11) << temp2.serNo4 << ',';
		outfileNode50 << std::setprecision(11) << temp2.serNo5 << ',';
		outfileNode50 << std::setprecision(11) << temp2.serNo6 << ',';
		outfileNode50 << std::setprecision(11) << temp2.serNo7 << ',';
		outfileNode50 << std::setprecision(11) << temp2.serNo8 << ',';
		outfileNode50 << std::setprecision(11) << temp2.elec << ',';
		outfileNode50 << std::setprecision(11) << temp2.battery << ',';
		outfileNode50 << std::setprecision(11) << temp2.binNodeNum << ',';
		outfileNode50 << std::setprecision(11) << temp2.roadNodeNum << ',';
		outfileNode50 << std::setprecision(11) << temp2.excelNodeNum << ',';
		outfileNode50 << std::setprecision(11) << temp2.rowNum << ',';
		outfileNode50 << std::setprecision(11) << temp2.colNum << endl;

	}
	outfileNode50.close();
	for (auto it = rn200[0].begin(); it != rn200[0].end(); it++)
	{
		roadNode temp2 = it->second;
		outfileNode200 << std::setprecision(11) << temp2.lon << ',';
		outfileNode200 << std::setprecision(11) << temp2.lat << ',';
		outfileNode200 << std::setprecision(11) << temp2.time << ',';
		outfileNode200 << std::setprecision(11) << temp2.serCount << ',';
		outfileNode200 << std::setprecision(11) << temp2.serNo1 << ',';
		outfileNode200 << std::setprecision(11) << temp2.serNo2 << ',';
		outfileNode200 << std::setprecision(11) << temp2.serNo3 << ',';
		outfileNode200 << std::setprecision(11) << temp2.serNo4 << ',';
		outfileNode200 << std::setprecision(11) << temp2.serNo5 << ',';
		outfileNode200 << std::setprecision(11) << temp2.serNo6 << ',';
		outfileNode200 << std::setprecision(11) << temp2.serNo7 << ',';
		outfileNode200 << std::setprecision(11) << temp2.serNo8 << ',';
		outfileNode200 << std::setprecision(11) << temp2.elec << ',';
		outfileNode200 << std::setprecision(11) << temp2.battery << ',';
		outfileNode200 << std::setprecision(11) << temp2.binNodeNum << ',';
		outfileNode200 << std::setprecision(11) << temp2.roadNodeNum << ',';
		outfileNode200 << std::setprecision(11) << temp2.excelNodeNum << ',';
		outfileNode200 << std::setprecision(11) << temp2.rowNum << ',';
		outfileNode200 << std::setprecision(11) << temp2.colNum << endl;

	}
	outfileNode200.close();
	vector<double *> *mhn = srd->threeNodeVector;
	ofstream threeNode("threeNode.txt",ios::out);
	for (auto it = mhn[0].begin(); it != mhn[0].end(); it++) 
	{
		double* temp = *it;
		for(int i=0;i<30;i++)
			threeNode << std::setprecision(11) << temp[i] << ',';
		threeNode << endl;
	}

	int a = 1;
#else
	string filename = "C://Users//10379//Desktop//test.xlsx";

	handleRoadData *hrd = new handleRoadData(filename);
	hrd->readRoadFileAsVector;
	int maxx, minx, maxy, miny;
	maxx = hrd->maxx;
	maxy = hrd->maxy;
	minx = hrd->minx;
	miny = hrd->miny;

	int height = (int)(CalDistanseM(minx, maxy, minx, miny, true) / 5) + 1;
	int width = (int)(CalDistanseM(maxx, miny, minx, miny, true) / 5) + 1;

	double pixl = 5 / 111000;


	ifstream inFile("NodeData.txt");


#endif

}

