#include "spliteRdByDist.h"
#include "../CalculateModel/CalResultWrapper/RasterResult.h"
#include <math.h>
#include "../CalculateModel/BasicDef/GlobalFunction.h"
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <Windows.h>
using namespace std;
#define DATA_LEVEL_500 (500.0/111000.0) 
#define DATA_LEVEL_200 (200.0/111000.0)
#define DATA_LEVEL_100 (100.0/111000)
#define DATA_LEVEL_50 (50.0/111000.0)

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

	nodeData_50 = new map<long int, roadNode>[1];
	nodeData_200 = new map<long int, roadNode>[1];

	threeNodeVector = new vector<double*>[1];
	//threeRoadValue = new double[35];
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
	ngb_ser1->~RasterResult();
	ngb_ser2->~RasterResult();
	ngb_ser3->~RasterResult();
	ngb_ser4->~RasterResult();
	ngb_ser5->~RasterResult();
	ngb_ser6->~RasterResult();
	ngb_ser7->~RasterResult();
	ngb_ser8->~RasterResult();
	ngb_Elec->~RasterResult();

	ngb_ser1 = NULL;
	ngb_ser2 = NULL;
	ngb_ser3 = NULL;
	ngb_ser4 = NULL;
	ngb_ser5 = NULL;
	ngb_ser6 = NULL;
	ngb_ser7 = NULL;
	ngb_ser8 = NULL;
	ngb_Elec = NULL;

	ngb_ser1_Node->~RasterResult();
	ngb_ser2_Node->~RasterResult();
	ngb_ser3_Node->~RasterResult();
	ngb_ser4_Node->~RasterResult();
	ngb_ser5_Node->~RasterResult();
	ngb_ser6_Node->~RasterResult();
	ngb_ser7_Node->~RasterResult();
	ngb_ser8_Node->~RasterResult();
	ngb_Elec_Node->~RasterResult();

	ngb_ser1_Node = NULL;
	ngb_ser2_Node = NULL;
	ngb_ser3_Node = NULL;
	ngb_ser4_Node = NULL;
	ngb_ser5_Node = NULL;
	ngb_ser6_Node = NULL;
	ngb_ser7_Node = NULL;
	ngb_ser8_Node = NULL;
	ngb_Elec_Node = NULL;
	
}

void spliteRoadData::getMaxRect() 
{
	minx = hrd->minx-0.02;
	miny = hrd->miny-0.02;
	maxx = hrd->maxx+0.02;
	maxy = hrd->maxy+0.02;

}
void spliteRoadData::generateNode()
{
	int excel = 0;
	int bin = 0;
	int rowNum=0;
	int colNum=0;
	double DATA_LEVEL = 0.0;
	int rd_col = 0;
	int rd_row = 0;
	int sfd_col = 0;
	int sfd_row = 0;
	readExcel();
	getMaxRect();
	vector<roadData>::iterator it_rd = mRoadData[0].begin();
	
	
	
	if (needReadExcel == 1) 
	{
		/*readExcel();
		getMaxRect();*/
		while (it_rd != mRoadData[0].end())
		{
			for (int pixlLevel = 1; pixlLevel <= 2; pixlLevel++)
			{
				switch (pixlLevel)
				{
				case 1:
					nodeData = NULL;
					DATA_LEVEL = DATA_LEVEL_50;
					nodeData = nodeData_50;
					break;
				case 2:
					nodeData = NULL;
					DATA_LEVEL = DATA_LEVEL_200;
					nodeData = nodeData_200;
				default:
					break;
				}
				rowNum = (int)(((maxy - miny) / DATA_LEVEL)+0.5) ;
				colNum = (int)(((maxx - minx) / DATA_LEVEL)+0.5) ;
				int positionMove = (int)log10(colNum) + 1;

				roadData rd = *it_rd;
				rd_col = (int)(((rd.mLng - minx) / DATA_LEVEL)+0.5) ;
				rd_row = (int)(((rd.mLat - miny) / DATA_LEVEL)+0.5) ;
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
				temp_LonAll = rn.lon*rn.excelNodeNum;
				temp_LonAll += rd.mLng;
				rn.lon = temp_LonAll / (rn.excelNodeNum + 1);

				//更新纬度
				temp_latAll = rn.lat*rn.excelNodeNum;
				temp_latAll += rd.mLat;
				rn.lat = temp_latAll / (rn.excelNodeNum + 1);

				//更新battery
				temp_battery = rn.battery*rn.excelNodeNum;
				temp_battery += rd.mBattery;
				rn.battery = temp_battery / (rn.excelNodeNum + 1);

				//更新elec
				temp_elec = rn.elec*rn.excelNodeNum;
				temp_elec += rd.mElectric;
				rn.elec = temp_elec / (rn.excelNodeNum + 1);

				//node 增加
				rn.excelNodeNum += 1;
				rn.excelNodeNum += 1;

				/*nodeData[0].erase(it_map);
				nodeData[0].insert(pair<long int,roadNode>(index,rn));*/
				nodeData[0][index] = rn;
				nodeData = NULL;
				
				if (pixlLevel == 2)
					it_rd++;
			}
		}
	}
	if (needReadBin == 1)
	{
		while (readBIN() == NEED_READ_AGAIN)
		{
			vector<scanFreqData>::iterator it_sfd = mFreqData[0].begin();
			while (it_sfd != mFreqData[0].end())
			{
				for (int pixlLevel = 1; pixlLevel <= 2; pixlLevel++)
				{
					switch (pixlLevel)
					{
					case 1:
						DATA_LEVEL = DATA_LEVEL_50;
						nodeData = nodeData_50;
						break;
					case 2:
						DATA_LEVEL = DATA_LEVEL_200;
						nodeData = nodeData_200;
						break;
					default:
						break;
					}
					rowNum = (int)(((maxy - miny) / DATA_LEVEL)+0.5) ;
					colNum = (int)(((maxx - minx) / DATA_LEVEL)+0.5) ;
					int positionMove = (int)log10(colNum) + 1;
					//printf("当前数据节点 第%d个分辨率下得行数为：%d , 列数为：%d \n",pixlLevel,rowNum,colNum);
					scanFreqData sfd = *it_sfd;
					sfd_col = (int)(((sfd.lon - minx) / DATA_LEVEL)+0.5) ;
					sfd_row = (int)(((sfd.lat - miny) / DATA_LEVEL)+0.5) ;
					/*if (sfd_row > 1500)
						printf("error");*/
					long int index = (long int)(sfd_row*pow(10, positionMove)) + sfd_col;

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
					rn.time = sfd.time;
					temp_LonAll = rn.lon*rn.binNodeNum;
					temp_LonAll += sfd.lon;
					rn.lon = temp_LonAll / (rn.binNodeNum + 1);

					//更新纬度
					temp_latAll = rn.lat*rn.binNodeNum;
					temp_latAll += sfd.lat;
					rn.lat = temp_latAll / (rn.binNodeNum + 1);
					//更新业务1
					temp_1 = rn.serNo1*rn.binNodeNum;
					temp_1 += sfd.severiceNo1;
					rn.serNo1 = temp_1 / (rn.binNodeNum + 1);
					//更新业务2
					temp_2 = rn.serNo2*rn.binNodeNum;
					temp_2 += sfd.severiceNo2;
					rn.serNo2 = temp_2 / (rn.binNodeNum + 1);
					//更新业务3
					temp_3 = rn.serNo3*rn.binNodeNum;
					temp_3 += sfd.severiceNo3;
					rn.serNo3 = temp_3 / (rn.binNodeNum + 1);
					//更新业务4
					temp_4 = rn.serNo4*rn.binNodeNum;
					temp_4 += sfd.severiceNo4;
					rn.serNo4 = temp_4 / (rn.binNodeNum + 1);
					//更新业务5
					temp_5 = rn.serNo5*rn.binNodeNum;
					temp_5 += sfd.severiceNo5;
					rn.serNo5 = temp_5 / (rn.binNodeNum + 1);
					//更新业务6
					temp_6 = rn.serNo6*rn.binNodeNum;
					temp_6 += sfd.severiceNo6;
					rn.serNo6 = temp_6 / (rn.binNodeNum + 1);
					//更新业务7
					temp_7 = rn.serNo7*rn.binNodeNum;
					temp_7 += sfd.severiceNo7;
					rn.serNo7 = temp_7 / (rn.binNodeNum + 1);
					//更新业务8
					temp_8 = rn.serNo8*rn.binNodeNum;
					temp_8 += sfd.severiceNo8;
					rn.serNo8 = temp_8 / (rn.binNodeNum + 1);
					// 更新serviceCount
					temp_count = rn.serCount*rn.binNodeNum;
					temp_count += sfd.severiceCount;
					rn.serCount = temp_count / (rn.binNodeNum + 1);
					//node 增加
					rn.roadNodeNum += 1;
					rn.binNodeNum += 1;

					//nodeData[0].erase(it_map);
					//nodeData[0].insert(pair<long int, roadNode>(index, rn));
					nodeData[0][index] = rn;
					nodeData = NULL;
					if(pixlLevel==2)
						it_sfd++;
				}
			}
			hsfd->clearData();
		}
		if (mFreqData[0].size() != 0)
		{
			vector<scanFreqData>::iterator it_sfd = mFreqData[0].begin();
			while (it_sfd != mFreqData[0].end())
			{
				for (int pixlLevel = 1; pixlLevel <= 2; pixlLevel++)
				{
					switch (pixlLevel)
					{
					case 1:
						DATA_LEVEL = DATA_LEVEL_50;
						nodeData = nodeData_50;
						break;
					case 2:
						DATA_LEVEL = DATA_LEVEL_200;
						nodeData = nodeData_200;
						break;
					default:
						break;
					}
					rowNum = (int)(((maxy - miny) / DATA_LEVEL)+0.5) ;
					colNum = (int)(((maxx - minx) / DATA_LEVEL)+0.5) ;
					int positionMove = (int)log10(colNum) + 1;
					scanFreqData sfd = *it_sfd;
					sfd_col = (int)(((sfd.lon - minx) / DATA_LEVEL)+0.5) ;
					sfd_row = (int)(((sfd.lat - miny) / DATA_LEVEL)+0.5) ;
					/*if (sfd_row > 1500)
						printf("error");*/
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
					rn.time = sfd.time;
					temp_LonAll = rn.lon*rn.binNodeNum;
					temp_LonAll += sfd.lon;
					rn.lon = temp_LonAll / (rn.binNodeNum + 1);

					//更新纬度
					temp_latAll = rn.lat*rn.binNodeNum;
					temp_latAll += sfd.lat;
					rn.lat = temp_latAll / (rn.binNodeNum + 1);
					//更新业务1
					temp_1 = rn.serNo1*rn.binNodeNum;
					temp_1 += sfd.severiceNo1;
					rn.serNo1 = temp_1 / (rn.binNodeNum + 1);
					//更新业务2
					temp_2 = rn.serNo2*rn.binNodeNum;
					temp_2 += sfd.severiceNo2;
					rn.serNo2 = temp_2 / (rn.binNodeNum + 1);
					//更新业务3
					temp_3 = rn.serNo3*rn.binNodeNum;
					temp_3 += sfd.severiceNo3;
					rn.serNo3 = temp_3 / (rn.binNodeNum + 1);
					//更新业务4
					temp_4 = rn.serNo4*rn.binNodeNum;
					temp_4 += sfd.severiceNo4;
					rn.serNo4 = temp_4 / (rn.binNodeNum + 1);
					//更新业务5
					temp_5 = rn.serNo5*rn.binNodeNum;
					temp_5 += sfd.severiceNo5;
					rn.serNo5 = temp_5 / (rn.binNodeNum + 1);
					//更新业务6
					temp_6 = rn.serNo6*rn.binNodeNum;
					temp_6 += sfd.severiceNo6;
					rn.serNo6 = temp_6 / (rn.binNodeNum + 1);
					//更新业务7
					temp_7 = rn.serNo7*rn.binNodeNum;
					temp_7 += sfd.severiceNo7;
					rn.serNo7 = temp_7 / (rn.binNodeNum + 1);
					//更新业务8
					temp_8 = rn.serNo8*rn.binNodeNum;
					temp_8 += sfd.severiceNo8;
					rn.serNo8 = temp_8 / (rn.binNodeNum + 1);
					// 更新serviceCount
					temp_count = rn.serCount*rn.binNodeNum;
					temp_count += sfd.severiceCount;
					rn.serCount = temp_count / (rn.binNodeNum + 1);
					//node 增加
					rn.roadNodeNum += 1;
					rn.binNodeNum += 1;

					//nodeData[0].erase(it_map);
					//nodeData[0].insert(pair<long int, roadNode>(index, rn));
					nodeData[0][index] = rn;
					nodeData = NULL;
					if (pixlLevel == 2)
						it_sfd++;
					
				}
			}
			hsfd->clearData();
		}
	}
	printf("excel : %d, bin :%d",excel,bin);
}

void spliteRoadData::generateRaster() 
{

	for (int pixlLevel = 1; pixlLevel <= 2; pixlLevel++)
	{
		double DATA_LEVEL = 0.0;
		string sizeofPixl="";
		switch (pixlLevel)
		{
		case 1:
			DATA_LEVEL = DATA_LEVEL_50;
			nodeData = nodeData_50;
			sizeofPixl = "S";
			break;
		case 2:
			DATA_LEVEL = DATA_LEVEL_200;
			nodeData = nodeData_200;
			sizeofPixl = "B";
			break;
		default:
			break;
		}
		int rowNum = 0;
		int colNum = 0;

		rowNum = (int)(((maxy - miny) / DATA_LEVEL)+0.5) ;
		colNum = (int)(((maxx - minx) / DATA_LEVEL)+0.5) ;
		int width = colNum*size;
		int height = rowNum*size;
		double pixl = DATA_LEVEL/size;
		for (int i = 1; i <= 9; i++)
		{
			switch (i)
			{

			case 1:
				ngb_ser1=new NGBRasterResult();
				ngb_ser1->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN,0, minx, miny, width, height, pixl, pixl);
				ngb_ser1->SetDefaultValue(UNCALCULATE);

				ngb_ser1_Node = new NGBRasterResult();
				ngb_ser1_Node->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser1_Node->SetDefaultValue(UNCALCULATE);
				
				break;
			case 2:
				ngb_ser2 = new NGBRasterResult();
				ngb_ser2->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser2->SetDefaultValue(UNCALCULATE);

				ngb_ser2_Node = new NGBRasterResult();
				ngb_ser2_Node->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser2_Node->SetDefaultValue(UNCALCULATE);
				break;
			case 3:
				ngb_ser3 = new NGBRasterResult();
				ngb_ser3->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser3->SetDefaultValue(UNCALCULATE);

				ngb_ser3_Node = new NGBRasterResult();
				ngb_ser3_Node->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser3_Node->SetDefaultValue(UNCALCULATE);
				break;
			case 4:
				ngb_ser4 = new NGBRasterResult();
				ngb_ser4->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser4->SetDefaultValue(UNCALCULATE);

				ngb_ser4_Node = new NGBRasterResult();
				ngb_ser4_Node->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser4_Node->SetDefaultValue(UNCALCULATE);
				break;
			case 5:
				ngb_ser5 = new NGBRasterResult();
				ngb_ser5->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser5->SetDefaultValue(UNCALCULATE);

				ngb_ser5_Node = new NGBRasterResult();
				ngb_ser5_Node->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser5_Node->SetDefaultValue(UNCALCULATE);
				break;
			case 6:
				ngb_ser6 = new NGBRasterResult();
				ngb_ser6->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser6->SetDefaultValue(UNCALCULATE);

				ngb_ser6_Node = new NGBRasterResult();
				ngb_ser6_Node->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser6_Node->SetDefaultValue(UNCALCULATE);
				break;
			case 7:
				ngb_ser7 = new NGBRasterResult();
				ngb_ser7->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser7->SetDefaultValue(UNCALCULATE);

				ngb_ser7_Node = new NGBRasterResult();
				ngb_ser7_Node->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser7_Node->SetDefaultValue(UNCALCULATE);
				break;
			case 8:
				ngb_ser8 = new NGBRasterResult();
				ngb_ser8->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser8->SetDefaultValue(UNCALCULATE);

				ngb_ser8_Node = new NGBRasterResult();
				ngb_ser8_Node->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_ser8_Node->SetDefaultValue(UNCALCULATE);
				break;
			case 9:
				ngb_Elec = new NGBRasterResult();
				ngb_Elec->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_Elec->SetDefaultValue(UNCALCULATE);

				ngb_Elec_Node = new NGBRasterResult();
				ngb_Elec_Node->GenerateEmptyRaster(eUnknownResult, DATA_DOUBLE, CRUNIT_UNKOWN, 0, minx, miny, width, height, pixl, pixl);
				ngb_Elec_Node->SetDefaultValue(UNCALCULATE);
				break;
			default:
				break;
			}

			for (auto it = nodeData[0].begin(); it != nodeData[0].end(); it++)
			{
				roadNode temp2 = it->second;

				int y = temp2.rowNum;
				int x = temp2.colNum;
				for (int k1 = 0; k1 < size; k1++) {
					for (int k2 = 0; k2 < size; k2++) {
						switch (i)
						{

						case 1:
							ngb_ser1->SetValue(x*size + k1, y*size + k2, temp2.serNo1 / (temp2.serCount / 100.0));
							break;
						case 2:
							ngb_ser2->SetValue(x*size + k1, y*size + k2, temp2.serNo2 / (temp2.serCount / 100.0));
							break;
						case 3:
							ngb_ser3->SetValue(x*size + k1, y*size + k2, temp2.serNo3 / (temp2.serCount / 100.0));
							break;
						case 4:
							ngb_ser4->SetValue(x*size + k1, y*size + k2, temp2.serNo4 / (temp2.serCount / 100.0));
							break;
						case 5:
							ngb_ser5->SetValue(x*size + k1, y*size + k2, temp2.serNo5 / (temp2.serCount / 100.0));
							break;
						case 6:
							ngb_ser6->SetValue(x*size + k1, y*size + k2, temp2.serNo6 / (temp2.serCount / 100.0));
							break;
						case 7:
							ngb_ser7->SetValue(x*size + k1, y*size + k2, temp2.serNo7 / (temp2.serCount / 100.0));
							break;
						case 8:
							ngb_ser8->SetValue(x*size + k1, y*size + k2, temp2.serNo8 / (temp2.serCount / 100.0));
							break;
						case 9:
							ngb_Elec->SetValue(x*size + k1, y*size + k2, temp2.elec);
							break;

						}
					}
				}
			}
			char * filename = new char[100];
			switch (i)
			{

			case 1:
				sprintf(filename,"ser1_%s.ngb",sizeofPixl.c_str());
				ngb_ser1->WriteRaster(filename);
				generateMergeRaster(DATA_LEVEL, 1);
				sprintf(filename, "ser1Node_%s.ngb", sizeofPixl.c_str());
				ngb_ser1_Node->WriteRaster(filename);
				delete ngb_ser1_Node;
				ngb_ser1_Node = NULL;
				delete ngb_ser1;
				ngb_ser1 = NULL;
				
				break;
			case 2:
				sprintf(filename, "ser2_%s.ngb", sizeofPixl.c_str());
				ngb_ser2->WriteRaster(filename);
				generateMergeRaster(DATA_LEVEL, 2);
				sprintf(filename, "ser2Node_%s.ngb", sizeofPixl.c_str());
				ngb_ser2_Node->WriteRaster(filename);
				delete ngb_ser2_Node;
				ngb_ser2_Node = NULL;
				delete ngb_ser2;
				ngb_ser2 = NULL;
				break;
			case 3:
				sprintf(filename, "ser3_%s.ngb", sizeofPixl.c_str());
				ngb_ser3->WriteRaster(filename);
				generateMergeRaster(DATA_LEVEL, 3);
				sprintf(filename, "ser3Node_%s.ngb", sizeofPixl.c_str());
				ngb_ser3_Node->WriteRaster(filename);
				delete ngb_ser3_Node;
				ngb_ser3_Node = NULL;
				delete ngb_ser3;
				ngb_ser3 = NULL;
				break;
			case 4:
				sprintf(filename, "ser4_%s.ngb", sizeofPixl.c_str());
				ngb_ser4->WriteRaster(filename);
				generateMergeRaster(DATA_LEVEL, 4);
				sprintf(filename, "ser4Node_%s.ngb", sizeofPixl.c_str());
				ngb_ser4_Node->WriteRaster(filename);
				delete ngb_ser4_Node;
				ngb_ser4_Node = NULL;
				delete ngb_ser4;
				ngb_ser4 = NULL;
				break;
			case 5:
				sprintf(filename, "ser5_%s.ngb", sizeofPixl.c_str());
				ngb_ser5->WriteRaster(filename);
				generateMergeRaster(DATA_LEVEL, 5);
				sprintf(filename, "ser5Node_%s.ngb", sizeofPixl.c_str());
				ngb_ser5_Node->WriteRaster(filename);
				delete ngb_ser5_Node;
				ngb_ser5_Node = NULL;
				delete ngb_ser5;
				ngb_ser5 = NULL;
				break;
			case 6:
				sprintf(filename, "ser6_%s.ngb", sizeofPixl.c_str());
				ngb_ser6->WriteRaster(filename);
				generateMergeRaster(DATA_LEVEL, 6);
				sprintf(filename, "ser6Node_%s.ngb", sizeofPixl.c_str());
				ngb_ser6_Node->WriteRaster(filename);
				delete ngb_ser6_Node;
				ngb_ser6_Node = NULL;
				delete ngb_ser6;
				ngb_ser6 = NULL;
				break;
			case 7:
				sprintf(filename, "ser7_%s.ngb", sizeofPixl.c_str());
				ngb_ser7->WriteRaster(filename);
				generateMergeRaster(DATA_LEVEL, 7);
				sprintf(filename, "ser7Node_%s.ngb", sizeofPixl.c_str());
				ngb_ser7_Node->WriteRaster(filename);
				delete ngb_ser7_Node;
				ngb_ser7_Node = NULL;
				delete ngb_ser7;
				ngb_ser7 = NULL;
				break;
			case 8:
				sprintf(filename, "ser8_%s.ngb", sizeofPixl.c_str());
				ngb_ser8->WriteRaster(filename);
				generateMergeRaster(DATA_LEVEL, 8);
				sprintf(filename, "ser8Node_%s.ngb", sizeofPixl.c_str());
				ngb_ser8_Node->WriteRaster(filename);
				delete ngb_ser8_Node;
				ngb_ser8_Node = NULL;
				delete ngb_ser8;
				ngb_ser8 = NULL;
				break;
			case 9:
				sprintf(filename, "Elec_%s.ngb", sizeofPixl.c_str());
				ngb_Elec->WriteRaster(filename);
				generateMergeRaster(DATA_LEVEL, 9);
				sprintf(filename, "ElecNode_%s.ngb", sizeofPixl.c_str());
				ngb_Elec_Node->WriteRaster(filename);
				delete ngb_Elec_Node;
				ngb_Elec_Node = NULL;
				delete ngb_Elec;
				ngb_Elec = NULL;
				break;

			default:
				break;
			}
		}
	}
}

double transfrom(double num) 
{
	double returnNum = 0.0;
	if (num > 116) 
	{
		double tempNum = 0.0;
		returnNum = 116;
		tempNum = (num - 116)*100;
		returnNum = returnNum + (double)(int(tempNum) / 60.0);
		tempNum = (tempNum - (int)tempNum)*100;
		returnNum = returnNum + (double)(int(tempNum) / 3600.0);
	}
	else if (num > 40)
	{
		double tempNum = 0.0;
		returnNum = 40;
		tempNum = (num - 40) * 100;
		returnNum = returnNum + (double)(int(tempNum) / 60.0);
		tempNum = (tempNum - (int)tempNum) * 100;
		returnNum = returnNum + (double)(int(tempNum) / 3600.0);
	}
	else 
	{
		
			double tempNum = 0.0;
			returnNum = 39;
			tempNum = (num - 39) * 100;
			returnNum = returnNum + (double)(int(tempNum) / 60.0);
			tempNum = (tempNum - (int)tempNum) * 100;
			returnNum = returnNum + (double)(int(tempNum) / 3600.0);
		
	}
	return returnNum;
}
void spliteRoadData::generateMergeRaster(double DATA_LEVEL, int i)
{
	// init data
	double *threeRoadValue=new double[35];
	int rangeStart = 0;
	int rangeEnd = 0;
	int x_s = 0, x_e = 0;
	int y_s = 0, y_e = 0;
	RasterResult *tempSer = NULL;
	RasterResult *tempMergeSer = NULL;
	int roadCount = 0;
	// confirm which ser to be merge
	switch (i)
	{
	case 1:
		tempSer = ngb_ser1;
		tempMergeSer = ngb_ser1_Node;
		break;
	case 2:
		tempSer = ngb_ser2;
		tempMergeSer = ngb_ser2_Node;
		break;
	case 3:
		tempSer = ngb_ser3;
		tempMergeSer = ngb_ser3_Node;
		break;
	case 4:
		tempSer = ngb_ser4;
		tempMergeSer = ngb_ser4_Node;
		break;
	case 5:
		tempSer = ngb_ser5;
		tempMergeSer = ngb_ser5_Node;
		break;
	case 6:
		tempSer = ngb_ser6;
		tempMergeSer = ngb_ser6_Node;
		break;
	case 7:
		tempSer = ngb_ser7;
		tempMergeSer = ngb_ser7_Node;
		break;
	case 8:
		tempSer = ngb_ser8;
		tempMergeSer = ngb_ser8_Node;
		break;
	case 9:
		tempSer = ngb_Elec;
		tempMergeSer = ngb_Elec_Node;
		break;
	default:
		break;
	}

	//Calucate area_1;
	for (rangeStart = 0; rangeStart < 24; rangeStart+=2)
	{
		//confirm the begin index and end index
			rangeEnd = rangeStart + 1;

		// get x range
		double lon1 = 0.0;
		double lat1 = 0.0;
		double lon2 = 0.0;
		double lat2 = 0.0;

		lon1 = transfrom(area_1[rangeStart][0]);
		lon2 = transfrom(area_1[rangeEnd][0]);
		x_s = (int)(((lon1 - minx) / DATA_LEVEL) + 0.5)*size;
		x_e = (int)(((lon2 - minx) / DATA_LEVEL) + 0.5)*size;
		if (x_s > x_e)
		{
			int temp = x_e;
			x_e = x_s;
			x_s = temp;
		}	
		// get y range
		lat1 = transfrom(area_1[rangeStart][1]);
		lat2 = transfrom(area_1[rangeEnd][1]);
		y_s = (int)(((lat1 - miny) / DATA_LEVEL) + 0.5)*size;
		y_e = (int)(((lat2 - miny) / DATA_LEVEL) + 0.5)*size;
		if (y_s > y_e)
		{
			int temp = y_e;
			y_e = y_s;
			y_s = temp;
		}
		//merge the value in range
		double serCount = 0.0;
		int serNum = 0;
		for (int range_i = x_s; range_i <= x_e; range_i++)
		{
			for (int range_j = y_s; range_j <= y_e; range_j++)
			{
				double temp = 0;
				tempSer->GetDataByIndex(range_i,range_j,temp);
				if (temp >= 0 && temp <= 100)
				{
					if (temp>0)
						serNum += 1;
					serCount += temp;
				}
			}
		}
		if (serNum == 0)
			serNum = serNum + 1;

		threeRoadValue[roadCount] = serCount / serNum;
		roadCount++;
		for (int range_i = x_s; range_i <= x_e; range_i++)
		{

			for (int range_j = y_s; range_j <= y_e; range_j++)
			{
				double temp = 0;
				tempSer->GetDataByIndex(range_i, range_j, temp);
				if (temp >= 0 && temp <= 100)
				{
					if (range_i == x_s || range_i == x_e || range_j == y_s || range_j == y_e)
						tempMergeSer->SetValue(range_i, range_j, -50);
					else
						tempMergeSer->SetValue(range_i, range_j,(serCount / serNum));
				}
				
				
			}
		}
		//complete the merge
	}

	//Calcuate area_2;
	for (rangeStart = 0; rangeStart < 24; rangeStart+=2)
	{
		//confirm the begin index and end index
			rangeEnd = rangeStart + 1;

		// get x range
		double lon1 = 0.0;
		double lat1 = 0.0;
		double lon2 = 0.0;
		double lat2 = 0.0;

		lon1 = transfrom(area_2[rangeStart][0]);
		lon2 = transfrom(area_2[rangeEnd][0]);
		x_s = (int)(((lon1 - minx) / DATA_LEVEL) + 0.5)*size;
		x_e = (int)(((lon2 - minx) / DATA_LEVEL) + 0.5)*size;
		if (x_s > x_e)
		{
			int temp = x_e;
			x_e = x_s;
			x_s = temp;
		}
		// get y range
		lat1 = transfrom(area_2[rangeStart][1]);
		lat2 = transfrom(area_2[rangeEnd][1]);
		y_s = (int)(((lat1 - miny) / DATA_LEVEL) + 0.5)*size;
		y_e = (int)(((lat2 - miny) / DATA_LEVEL) + 0.5)*size;
		if (y_s > y_e)
		{
			int temp = y_e;
			y_e = y_s;
			y_s = temp;
		}

		//merge the value in range
		double serCount = 0.0;
		int serNum = 0;
		for (int range_i = x_s; range_i <= x_e; range_i++)
		{
			for (int range_j = y_s; range_j <= y_e; range_j++)
			{
				double temp = 0;
				tempSer->GetDataByIndex(range_i, range_j, temp);
				if (temp >= 0 && temp <= 100)
				{
					if (temp>0)
						serNum += 1;
					serCount += temp;
				}
			}
		}
		if (serNum == 0)
			serNum = serNum + 1;

		threeRoadValue[roadCount] = serCount / serNum;
		
		roadCount++;
		for (int range_i = x_s; range_i <= x_e; range_i++)
		{

			for (int range_j = y_s; range_j <= y_e; range_j++)
			{
				double temp = 0;
				tempSer->GetDataByIndex(range_i, range_j, temp);
				if (temp >= 0 && temp <= 100)
				{
					if (range_i == x_s || range_i == x_e || range_j == y_s || range_j == y_e)
						tempMergeSer->SetValue(range_i, range_j, -50);
					else
						tempMergeSer->SetValue(range_i, range_j,(serCount / serNum));
				}
				
			}
		}
	}

	//Calcuate area_3
	for (rangeStart = 0; rangeStart < 6; rangeStart += 2)
	{
		//confirm the begin index and end index
		rangeEnd = rangeStart + 1;

		// get x range
		double lon1 = 0.0;
		double lat1 = 0.0;
		double lon2 = 0.0;
		double lat2 = 0.0;

		lon1 = transfrom(area_3[rangeStart][0]);
		lon2 = transfrom(area_3[rangeEnd][0]);
		x_s = (int)(((lon1 - minx) / DATA_LEVEL) + 0.5)*size;
		x_e = (int)(((lon2 - minx) / DATA_LEVEL) + 0.5)*size;
		if (x_s > x_e)
		{
			int temp = x_e;
			x_e = x_s;
			x_s = temp;
		}
		// get y range
		lat1 = transfrom(area_3[rangeStart][1]);
		lat2 = transfrom(area_3[rangeEnd][1]);
		y_s = (int)(((lat1 - miny) / DATA_LEVEL) + 0.5)*size;
		y_e = (int)(((lat2 - miny) / DATA_LEVEL) + 0.5)*size;
		if (y_s > y_e)
		{
			int temp = y_e;
			y_e = y_s;
			y_s = temp;
		}

		//merge the value in range
		double serCount = 0.0;
		int serNum = 0;
		for (int range_i = x_s; range_i <= x_e; range_i++)
		{
			for (int range_j = y_s; range_j <= y_e; range_j++)
			{
				double temp = 0;
				tempSer->GetDataByIndex(range_i, range_j, temp);
				if (temp >= 0 && temp <= 100)
				{
					if (temp>0)
						serNum += 1;
					serCount += temp;
				}
			}
		}
		if (serNum == 0)
			serNum = serNum + 1;

		threeRoadValue[roadCount] = serCount / serNum;
		roadCount++;
		for (int range_i = x_s; range_i <= x_e; range_i++)
		{

			for (int range_j = y_s; range_j <= y_e; range_j++)
			{
				double temp = 0;
				tempSer->GetDataByIndex(range_i, range_j, temp);
				if (temp >= 0 && temp <= 100)
				{
					/*if (range_i == x_s || range_i == x_e || range_j == y_s || range_j == y_e)
					tempMergeSer->SetValue(range_i, range_j, -50);
					else*/
					tempMergeSer->SetValue(range_i, range_j, (serCount / serNum));
				}
			}
		}


		//complete the merge
	}
	//Calcuate area_4;
	for (rangeStart = 0; rangeStart < 6; rangeStart += 2)
	{
		//confirm the begin index and end index
		rangeEnd = rangeStart + 1;

		// get x range
		double lon1 = 0.0;
		double lat1 = 0.0;
		double lon2 = 0.0;
		double lat2 = 0.0;

		lon1 = transfrom(area_4[rangeStart][0]);
		lon2 = transfrom(area_4[rangeEnd][0]);
		x_s = (int)(((lon1 - minx) / DATA_LEVEL) + 0.5)*size;
		x_e = (int)(((lon2 - minx) / DATA_LEVEL) + 0.5)*size;
		if (x_s > x_e)
		{
			int temp = x_e;
			x_e = x_s;
			x_s = temp;
		}
		// get y range
		lat1 = transfrom(area_4[rangeStart][1]);
		lat2 = transfrom(area_4[rangeEnd][1]);
		y_s = (int)(((lat1 - miny) / DATA_LEVEL) + 0.5)*size;
		y_e = (int)(((lat2 - miny) / DATA_LEVEL) + 0.5)*size;
		if (y_s > y_e)
		{
			int temp = y_e;
			y_e = y_s;
			y_s = temp;
		}

		//merge the value in range
		double serCount = 0.0;
		int serNum = 0;
		for (int range_i = x_s; range_i <= x_e; range_i++)
		{
			for (int range_j = y_s; range_j <= y_e; range_j++)
			{
				double temp = 0;
				tempSer->GetDataByIndex(range_i, range_j, temp);
				if (temp >= 0 && temp <= 100)
				{
					if (temp>0)
						serNum += 1;
					serCount += temp;
				}
			}
		}
		if (serNum == 0)
			serNum = serNum + 1;

		threeRoadValue[roadCount] = serCount / serNum;
		roadCount++;
		for (int range_i = x_s; range_i <= x_e; range_i++)
		{

			for (int range_j = y_s; range_j <= y_e; range_j++)
			{
				double temp = 0;
				tempSer->GetDataByIndex(range_i, range_j, temp);
				if (temp >= 0 && temp <= 100)
				{/*
				 if (range_i == x_s || range_i == x_e || range_j == y_s || range_j == y_e)
				 tempMergeSer->SetValue(range_i, range_j, -50);
				 else*/
					tempMergeSer->SetValue(range_i, range_j, (serCount / serNum));
				}
			}
		}

	}
	
	threeNodeVector[0].push_back(threeRoadValue);
	
	
}

