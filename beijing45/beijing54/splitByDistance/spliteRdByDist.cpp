#include "spliteRdByDist.h"
#include "../CalculateModel/CalResultWrapper/RasterResult.h"
#include <math.h>
#include "../CalculateModel/BasicDef/GlobalFunction.h"
#include "math.h"
#define DATA_LEVEL (200.0/111000)
spliteRoadData::spliteRoadData(string efName,string bfName)
{
	
	needReadBin = 0;
	needReadExcel = 0;
	minx = 0.0;
	miny = 0.0;
	maxx = 0.0;
	maxy = 0.0;
	//
	hrd = new handleRoadData(efName);
	if (hrd == NULL) 
	{
		printf("handleRoadData Init is failed!");
		return;
	}

	hsfd = new handleScanFreqData(bfName.c_str());

	if (hsfd == NULL)
	{
		printf("handleScanFreqData Init is failed!");
		return;
	}
	mRoadData = new vector<roadData>[1];
	mFreqData = new vector<scanFreqData>[1];
	nodeData = new map<long int,roadNode>[1];
	ngz_ser1 = new RasterResult();
	ngz_ser2 = new RasterResult();
	ngz_ser3 = new RasterResult();
	ngz_ser4 = new RasterResult();
	ngz_ser5 = new RasterResult();
	ngz_ser6 = new RasterResult();
	ngz_ser7 = new RasterResult();
	ngz_ser8 = new RasterResult();
	ngz_Elec = new RasterResult();
	////处理excel文件，将结果以vector容器返回
	//hrd = new handleRoadData(efName);
	//hrd->readRoadFileAsVector();

	////获取vector 容器

	///*mRoadData = hrd->mRoadData;
	//mFreqData[0] = hfd->mScanFreqData;*/
	//int a = 1;
}

int spliteRoadData::readBIN()
{

	////处理bin文件，将结果以vector容器返回
	
	int flag=hsfd->handleData();
	mFreqData = hsfd->mScanFreqData;
	return flag;
}
void spliteRoadData::readExcel()
{

	////处理bin文件，将结果以vector容器返回

	hrd->readRoadFileAsVector();
	mRoadData = hrd->mRoadData;
}

spliteRoadData::~spliteRoadData() 
{
	delete hsfd;
	hsfd = NULL;
	delete hrd;
	hrd = NULL;
	delete mRoadData;
	mRoadData = NULL;
	delete mFreqData;
	mFreqData = NULL;
	minx = 0.0;
	miny = 0.0;
	maxx = 0.0;
	maxy = 0.0;
	ngz_ser1->~RasterResult();
	ngz_ser2->~RasterResult();
	ngz_ser3->~RasterResult();
	ngz_ser4->~RasterResult();
	ngz_ser5->~RasterResult();
	ngz_ser6->~RasterResult();
	ngz_ser7->~RasterResult();
	ngz_ser8->~RasterResult();
	ngz_Elec->~RasterResult();

	ngz_ser1 = NULL;
	ngz_ser2 = NULL;
	ngz_ser3 = NULL;
	ngz_ser4 = NULL;
	ngz_ser5 = NULL;
	ngz_ser6 = NULL;
	ngz_ser7 = NULL;
	ngz_ser8 = NULL;
	ngz_Elec = NULL;
	
}

void spliteRoadData::getMaxRect() 
{
	minx = hrd->minx-0.01;
	miny = hrd->miny-0.01;
	maxx = hrd->maxx+0.01;
	maxy = hrd->maxy+0.01;

}
void spliteRoadData::generateNode()
{
	int excel = 0;
	int bin = 0;
	int rowNum=0;
	int colNum=0;
	int rd_col = 0;
	int rd_row = 0;
	int sfd_col = 0;
	int sfd_row = 0;
	readExcel();
	getMaxRect();

	rowNum = (int)((maxy-miny) / DATA_LEVEL) + 1;
	colNum = (int)((maxx-minx) / DATA_LEVEL) + 1;
	int positionMove = (int)log10(colNum) + 1;
	
	
	
	printf("行数为：%d，列数为：%d", rowNum, colNum);

	vector<roadData>::iterator it_rd = mRoadData[0].begin();
	if (needReadExcel == 1) 
	{
		while (it_rd != mRoadData[0].end())
		{
			roadData rd = *it_rd;
			rd_col = (int)((rd.mLng - minx) / DATA_LEVEL) + 1;
			rd_row = (int)((rd.mLat - miny) / DATA_LEVEL) + 1;
			//简单编码
			long int index = (long int)(rd_row*pow(10, positionMove)) + rd_col;
			//map<long int, roadNode>::iterator it_map = nodeData[0].find(index);
			if (nodeData[0].count(index) == 0)
			{
				roadNode temp;
				nodeData[0].insert(pair<long int, roadNode>(index, temp));
			}
			excel++;
			double temp_LonAll = 0.0;
			double temp_latAll = 0.0;
			double temp_battery = 0.0;
			double temp_elec = 0.0;
			roadNode rn = nodeData[0][index];

			//更新经度
			rn.colNum = rd_col;
			rn.rowNum = rd_row;
			temp_LonAll = rn.lon*rn.roadNodeNum;
			temp_LonAll += rd.mLng;
			rn.lon = temp_LonAll / (rn.roadNodeNum + 1);

			//更新纬度
			temp_latAll = rn.lat*rn.roadNodeNum;
			temp_latAll += rd.mLat;
			rn.lat = temp_latAll / (rn.roadNodeNum + 1);

			//更新battery
			temp_battery = rn.battery*rn.roadNodeNum;
			temp_battery += rd.mBattery;
			rn.battery = temp_battery / (rn.roadNodeNum + 1);

			//更新elec
			temp_elec = rn.elec*rn.roadNodeNum;
			temp_elec += rd.mElectric;
			rn.elec = temp_elec / (rn.roadNodeNum + 1);

			//node 增加
			rn.excelNodeNum += 1;
			rn.roadNodeNum += 1;

			/*nodeData[0].erase(it_map);
			nodeData[0].insert(pair<long int,roadNode>(index,rn));*/
			nodeData[0][index] = rn;
			it_rd++;
		}
	}
	if (needReadBin == 1)
	{
		while (readBIN() == NEED_READ_AGAIN)
		{
			vector<scanFreqData>::iterator it_sfd = mFreqData[0].begin();
			while (it_sfd != mFreqData[0].end())
			{
				scanFreqData sfd = *it_sfd;
				sfd_col = (int)((sfd.lon-minx) / DATA_LEVEL)+ 1;
				sfd_row =(int)((sfd.lat-miny) / DATA_LEVEL) + 1;
				long int index =(long int)( sfd_row*pow(10, positionMove)) + sfd_col;

				//map<long int, roadNode>::iterator it_map = nodeData[0].find(index);
				if (nodeData[0].count(index) == 0)
				{
					roadNode temp;
					nodeData[0].insert(pair<long int, roadNode>(index, temp));
				}
				bin++;
				double temp_LonAll = 0.0;
				double temp_latAll = 0.0;
				double temp_1 = 0.0;
				double temp_2 = 0.0;
				double temp_3 = 0.0;
				double temp_4 = 0.0;
				double temp_5 = 0.0;
				double temp_6 = 0.0;
				double temp_7 = 0.0;
				double temp_8 = 0.0;
				double temp_count = 0.0;
				roadNode rn = nodeData[0][index];
				//更新经度
				rn.colNum = sfd_col;
				rn.rowNum = sfd_row;
				temp_LonAll = rn.lon*rn.roadNodeNum;
				temp_LonAll += sfd.lon;
				rn.lon = temp_LonAll / (rn.roadNodeNum + 1);

				//更新纬度
				temp_latAll = rn.lat*rn.roadNodeNum;
				temp_latAll += sfd.lat;
				rn.lat = temp_latAll / (rn.roadNodeNum + 1);
				//更新业务1
				temp_1 = rn.serNo1*rn.roadNodeNum;
				temp_1 += sfd.severiceNo1;
				rn.serNo1 = temp_1 / (rn.roadNodeNum + 1);
				//更新业务2
				temp_2 = rn.serNo2*rn.roadNodeNum;
				temp_2 += sfd.severiceNo2;
				rn.serNo2 = temp_2 / (rn.roadNodeNum + 1);
				//更新业务3
				temp_3 = rn.serNo3*rn.roadNodeNum;
				temp_3 += sfd.severiceNo3;
				rn.serNo3 = temp_3 / (rn.roadNodeNum + 1);
				//更新业务4
				temp_4 = rn.serNo4*rn.roadNodeNum;
				temp_4 += sfd.severiceNo4;
				rn.serNo4 = temp_4 / (rn.roadNodeNum + 1);
				//更新业务5
				temp_5 = rn.serNo5*rn.roadNodeNum;
				temp_5 += sfd.severiceNo5;
				rn.serNo5 = temp_5 / (rn.roadNodeNum + 1);
				//更新业务6
				temp_6 = rn.serNo6*rn.roadNodeNum;
				temp_6 += sfd.severiceNo6;
				rn.serNo6 = temp_6 / (rn.roadNodeNum + 1);
				//更新业务7
				temp_7 = rn.serNo7*rn.roadNodeNum;
				temp_7 += sfd.severiceNo7;
				rn.serNo7 = temp_7 / (rn.roadNodeNum + 1);
				//更新业务8
				temp_8 = rn.serNo8*rn.roadNodeNum;
				temp_8 += sfd.severiceNo8;
				rn.serNo8 = temp_8 / (rn.roadNodeNum + 1);
				// 更新serviceCount
				temp_count = rn.serCount*rn.roadNodeNum;
				temp_count += sfd.severiceCount;
				rn.serCount = temp_count / (rn.roadNodeNum + 1);
				//node 增加
				rn.roadNodeNum += 1;
				rn.binNodeNum += 1;

				//nodeData[0].erase(it_map);
				//nodeData[0].insert(pair<long int, roadNode>(index, rn));
				nodeData[0][index] = rn;
				it_sfd++;
			}
			hsfd->clear();
		}
		if (mFreqData[0].size() != 0)
		{
			vector<scanFreqData>::iterator it_sfd = mFreqData[0].begin();
			while (it_sfd != mFreqData[0].end())
			{
				scanFreqData sfd = *it_sfd;
				sfd_col = (int)((sfd.lon - minx) / DATA_LEVEL) + 1;
				sfd_row = (int)((sfd.lat - miny) / DATA_LEVEL) + 1;
				long int index = (long int)(sfd_row*pow(10, positionMove)) + sfd_col;

				//map<long int, roadNode>::iterator it_map = nodeData[0].find(index);
				if (nodeData[0].count(index))
				{
					roadNode temp;
					nodeData[0].insert(pair<long int, roadNode>(index, temp));
				}
				bin++;
				double temp_LonAll = 0.0;
				double temp_latAll = 0.0;
				double temp_1 = 0.0;
				double temp_2 = 0.0;
				double temp_3 = 0.0;
				double temp_4 = 0.0;
				double temp_5 = 0.0;
				double temp_6 = 0.0;
				double temp_7 = 0.0;
				double temp_8 = 0.0;
				double temp_count = 0.0;
				roadNode rn = nodeData[0][index];
				//更新经度
				rn.colNum = sfd_col;
				rn.rowNum = sfd_row;
				temp_LonAll = rn.lon*rn.roadNodeNum;
				temp_LonAll += sfd.lon;
				rn.lon = temp_LonAll / (rn.roadNodeNum + 1);

				//更新纬度
				temp_latAll = rn.lat*rn.roadNodeNum;
				temp_latAll += sfd.lat;
				rn.lat = temp_latAll / (rn.roadNodeNum + 1);
				//更新业务1
				temp_1 = rn.serNo1*rn.roadNodeNum;
				temp_1 += sfd.severiceNo1;
				rn.serNo1 = temp_1 / (rn.roadNodeNum + 1);
				//更新业务2
				temp_2 = rn.serNo2*rn.roadNodeNum;
				temp_2 += sfd.severiceNo2;
				rn.serNo2 = temp_2 / (rn.roadNodeNum + 1);
				//更新业务3
				temp_3 = rn.serNo3*rn.roadNodeNum;
				temp_3 += sfd.severiceNo3;
				rn.serNo3 = temp_3 / (rn.roadNodeNum + 1);
				//更新业务4
				temp_4 = rn.serNo4*rn.roadNodeNum;
				temp_4 += sfd.severiceNo4;
				rn.serNo4 = temp_4 / (rn.roadNodeNum + 1);
				//更新业务5
				temp_5 = rn.serNo5*rn.roadNodeNum;
				temp_5 += sfd.severiceNo5;
				rn.serNo5 = temp_5 / (rn.roadNodeNum + 1);
				//更新业务6
				temp_6 = rn.serNo6*rn.roadNodeNum;
				temp_6 += sfd.severiceNo6;
				rn.serNo6 = temp_6 / (rn.roadNodeNum + 1);
				//更新业务7
				temp_7 = rn.serNo7*rn.roadNodeNum;
				temp_7 += sfd.severiceNo7;
				rn.serNo7 = temp_7 / (rn.roadNodeNum + 1);
				//更新业务8
				temp_8 = rn.serNo8*rn.roadNodeNum;
				temp_8 += sfd.severiceNo8;
				rn.serNo8 = temp_8 / (rn.roadNodeNum + 1);
				// 更新serviceCount
				temp_count = rn.serCount*rn.roadNodeNum;
				temp_count += sfd.severiceCount;
				rn.serCount= temp_count / (rn.roadNodeNum + 1);
				//node 增加
				rn.roadNodeNum += 1;
				rn.binNodeNum += 1;

				//nodeData[0].erase(it_map);
				//nodeData[0].insert(pair<long int, roadNode>(index, rn));
				nodeData[0][index] = rn;
				it_sfd++;
			}
			hsfd->clear();
		}
	}
	printf("excel : %d, bin :%d",excel,bin);
}

void spliteRoadData::generateRaster() 
{

	
	int rowNum = 0;
	int colNum = 0;

	rowNum = (int)((maxy - miny) / DATA_LEVEL) + 1;
	colNum = (int)((maxx - minx) / DATA_LEVEL) + 1;
	int width = colNum;
	int height = rowNum;
	double pixl = DATA_LEVEL;
	for (int i = 1; i <= 9; i++)
	{
		switch (i)
		{

			case 1:
				ngz_ser1->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_PERCENT, 103, minx, miny, width, height, pixl, pixl);
				ngz_ser1->SetDefaultValue(UNCALCULATE);
				break;
			case 2 :
				ngz_ser2->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_PERCENT, 103, minx, miny, width, height, pixl, pixl);
				ngz_ser2->SetDefaultValue(UNCALCULATE);
				break;
			case 3:
				ngz_ser3->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_PERCENT, 103, minx, miny, width, height, pixl, pixl);
				ngz_ser3->SetDefaultValue(UNCALCULATE);
				break;
			case 4:
				ngz_ser4->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_PERCENT, 103, minx, miny, width, height, pixl, pixl);
				ngz_ser4->SetDefaultValue(UNCALCULATE);
				break;
			case 5:
				ngz_ser5->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_PERCENT, 103, minx, miny, width, height, pixl, pixl);
				ngz_ser5->SetDefaultValue(UNCALCULATE);
				break;
			case 6:
				ngz_ser6->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_PERCENT, 103, minx, miny, width, height, pixl, pixl);
				ngz_ser6->SetDefaultValue(UNCALCULATE);
				break;
			case 7:
				ngz_ser7->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_PERCENT, 103, minx, miny, width, height, pixl, pixl);
				ngz_ser7->SetDefaultValue(UNCALCULATE);
				break;
			case 8 :
				ngz_ser8->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_PERCENT, 103, minx, miny, width, height, pixl, pixl);
				ngz_ser8->SetDefaultValue(UNCALCULATE);
				break;
			case 9:
				ngz_Elec->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_PERCENT, 103, minx, miny, width, height, pixl, pixl);
				ngz_Elec->SetDefaultValue(UNCALCULATE);
				break;
			default:
				break;
		}

		for (auto it = nodeData[0].begin(); it != nodeData[0].end(); it++)
		{
			roadNode temp2 = it->second;

			int y = temp2.rowNum;
			int x = temp2.colNum;
			switch (i)
			{

			case 1: 
				ngz_ser1->SetValue(x, y, temp2.serNo1 / temp2.serCount);
				break;
			case 2:
				ngz_ser2->SetValue(x, y, temp2.serNo2 / temp2.serCount);
				break;
			case 3:
				ngz_ser3->SetValue(x, y, temp2.serNo3 / temp2.serCount);
				break;
			case 4:
				ngz_ser4->SetValue(x, y, temp2.serNo4 / temp2.serCount);
				break;
			case 5:
				ngz_ser5->SetValue(x, y, temp2.serNo5 / temp2.serCount);
				break;
			case 6:
				ngz_ser6->SetValue(x, y, temp2.serNo6 / temp2.serCount);
				break;
			case 7:
				ngz_ser7->SetValue(x, y, temp2.serNo7 / temp2.serCount);
				break;
			case 8:
				ngz_ser8->SetValue(x, y, temp2.serNo8 / temp2.serCount);
				break;
			case 9:
				ngz_Elec->SetValue(x, y, temp2.elec);
				break;
			
			}
		}

		switch (i)
		{

		case 1:
			ngz_ser1->WriteRaster("ser1.ngb");
			delete ngz_ser1;
			ngz_ser1 = NULL;
			break;
		case 2:
			ngz_ser2->WriteRaster("ser2.ngb");
			delete ngz_ser2;
			ngz_ser2 = NULL;
			break;
		case 3:
			ngz_ser3->WriteRaster("ser3.ngb");
			delete ngz_ser3;
			ngz_ser3 = NULL;
			break;
		case 4:
			ngz_ser4->WriteRaster("ser4.ngb");
			delete ngz_ser4;
			ngz_ser4 = NULL;
			break;
		case 5:
			ngz_ser5->WriteRaster("ser5.ngb");
			delete ngz_ser5;
			ngz_ser5 = NULL;
			break;
		case 6:
			ngz_ser6->WriteRaster("ser6.ngb");
			delete ngz_ser6;
			ngz_ser6 = NULL;
			break;
		case 7:
			ngz_ser7->WriteRaster("ser7.ngb");
			delete ngz_ser7;
			ngz_ser7 = NULL;
			break;
		case 8:
			ngz_ser8->WriteRaster("ser8.ngb");
			delete ngz_ser8;
			ngz_ser8 = NULL;
			break;
		case 9:
			ngz_Elec->WriteRaster("elec.ngb");
			delete ngz_Elec;
			ngz_Elec = NULL;
			break;
		
		default:
			break;
		}
	}
}

