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
#include "../splitByDistance/dataDef.h"
int main()
{
	// CScanFreqMonitorFile G_cMonitorScanInfo;
	string filename1 = "C://Users//10379//Desktop//test.bin";
	//handleScanFreqData *ss = new handleScanFreqData(filename1.c_str());
	//ss->handleData();
	
	
	//
	////G_cMonitorScanInfo.ReadFile_Reserve(filename.c_str());
	string filename = "C://Users//10379//Desktop//test.xlsx";
	//
	//
	spliteRoadData *srd = new spliteRoadData(filename,filename1);
	srd->generateNode();
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
		outfileNode << temp2.lon << ',' << temp2.lat << ',' << temp2.serNo1 << ',' << temp2.serNo2 << ',' << temp2.serNo3 << ',' << temp2.serNo4 << ',' << temp2.serNo5 << ',' << temp2.serNo6 << ',' << temp2.serNo7 << ',' << temp2.serNo8 << ',' << temp2.elec<<','<<temp2.battery<<endl;
	}
	outfileNode.close();
	
	int a = 1;
	

}

