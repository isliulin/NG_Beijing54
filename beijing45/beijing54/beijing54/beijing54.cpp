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
#include "../splitByDistance/dataDef.h"
int main()
{
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
	vector<roadData> *rd = srd->mRoadData;
	vector<scanFreqData> *sfd = srd->mFreqData;
	map<long int, roadNode> *rn = srd->nodeData;
	/*spliteRoadData *srd = new spliteRoadData(filename,filename1);
	srd->readBIN(filename1);
	delete srd;*/
	/*map<long int, roadNode> *ll = srd->nodeData;
	map<long int, roadNode>::iterator llyt= ll[0].begin();
	roadNode lpok = llyt->second;*/
	ofstream outfileExcel("excelData.txt",ios::out);
	ofstream outfileBin("binData.txt", ios::out);
	ofstream outfileNode("NodeData.txt", ios::out);
	for (auto it = rd[0].begin(); it != rd[0].end(); it++) 
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
	outfileBin.close();
	for (auto it = rn[0].begin(); it != rn[0].end(); it++)
	{
		roadNode temp2 = it->second;
		outfileNode << temp2.colNum << ',' << temp2.rowNum << ','<<temp2.excelNodeNum<<','<<temp2.binNodeNum<<endl;
	}
	outfileNode.close();
	
	int a = 1;
	

}

