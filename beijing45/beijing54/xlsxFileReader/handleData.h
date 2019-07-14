#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include "xlsxFileReader.h"
#include "dataDef.h"
using namespace std;

class EXCEL_API handleRoadData 
{
private:
	string roadFileName;
public:
	double minx;
	double maxx;
	double miny;
	double maxy;
public:
	vector<roadData> *mRoadData=new vector<roadData>[1];
public:
	handleRoadData(string filename); 
	~handleRoadData() 
	{
		delete mRoadData;
		mRoadData = NULL;
	}
public:
	void readRoadFileAsVector();

	
};
