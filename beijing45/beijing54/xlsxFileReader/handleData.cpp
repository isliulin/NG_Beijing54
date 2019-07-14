#include "pch.h"
#include "handleData.h"


handleRoadData::handleRoadData(std::string filename)
{
	this->roadFileName = filename; 
	minx = 1000000;
	maxx = 0;
	miny = 1000000;
	maxy = 0;
	
}

void handleRoadData::readRoadFileAsVector() 
{
	
	excel *roadExcel = new excel(roadFileName.c_str(), 0, 1);
	if (!roadExcel) 
	{
		return ;
	}
	int rowNum = roadExcel->getRowNum();
	int colNum = roadExcel->getColNum();
	
	for (int i =1;i<rowNum;i++) 
	{	
		roadData rd;
		for (int j = 0; j < colNum; j++) 
		{
			
			switch (j)
			{
			case 0:
				rd.mData_id = roadExcel->readnumInt(i,j);
				break;
			case 1:
				rd.mData_time = roadExcel->readnumInt(i,j);
				break;
			case 2:
				rd.mElectric = roadExcel->readnumDouble(i, j);
				break;
			case 10:
				rd.mBattery = roadExcel->readnumDouble(i, j);
				break;
			case 11:
				rd.mLng = roadExcel->readnumDouble(i, j);
				break;
			case 12:
				rd.mLat = roadExcel->readnumDouble(i, j);
				break;
			default:
				break;
			}
		}
		if (rd.mLng <= 100.0 || rd.mLat <= 30.0||rd.mLng>=200)
			continue;
		minx = minx < rd.mLng ? minx : rd.mLng;
		maxx = maxx > rd.mLng ? maxx : rd.mLng;
		miny = miny < rd.mLat ? miny : rd.mLat;
		maxy = maxy > rd.mLat ? maxy : rd.mLat;
		mRoadData[0].push_back(rd);
	}
	



}