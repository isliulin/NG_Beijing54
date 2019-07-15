#include "spliteRdByDist.h"
#include "../BasicDef/GlobalFunction.h"
#define DATA_LEVEL 5
#include <math.h>
#include "../CalculateModel/BasicDef/NG_ErrorCode.h"
spliteRoadData::spliteRoadData(string efName,string bfName)
{
	
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
}

void spliteRoadData::getMaxRect() 
{
	minx = hrd->minx < hsfd->minx ? hrd->minx : hsfd->minx;
	miny = hrd->miny < hsfd->miny ? hrd->miny : hsfd->miny;
	maxx= hrd->maxx > hsfd->maxx ? hrd->maxx : hsfd->maxx;
	maxy= hrd->maxy > hsfd->maxy ? hrd->maxy : hsfd->maxy;

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



	rowNum = CalDistanseM(minx,maxy,minx,miny,true)/DATA_LEVEL+1;
	colNum = CalDistanseM(maxx, miny, minx, miny, true) /DATA_LEVEL + 1;
	int positionMove = (int)log10(colNum)+1;
	printf("行数为：%d，列数为：%d",rowNum,colNum);
	
	

	readExcel();
	vector<roadData>::iterator it_rd = mRoadData[0].begin();
	while (it_rd!=mRoadData[0].end()) 
	{
		if (it_rd != mRoadData[0].end())
		{
			roadData rd = *it_rd;
			rd_col = CalDistanseM(rd.mLng, miny, minx, miny, true)/DATA_LEVEL+1;
			rd_row = CalDistanseM(minx, rd.mLat, minx, miny, true) / DATA_LEVEL + 1;
			//简单编码
			long int index = rd_row*pow(10, positionMove) + rd_col;
			nodeData[0].find(1);
			map<long int, roadNode>::iterator it_map = nodeData[0].find(index);
			if (it_map != nodeData[0].end())
			{
					excel++;
					double temp_LonAll = 0.0;
					double temp_latAll = 0.0;
					double temp_battery = 0.0;
					double temp_elec = 0.0;
					roadNode rn = nodeData[0][index];

					//更新经度
					temp_LonAll = rn.lon*rn.roadNodeNum;
					temp_LonAll += rd.mLng;
					rn.lon = temp_LonAll / (rn.roadNodeNum+1);

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

					nodeData[0].erase(it_map);
					nodeData[0].insert(pair<long int,roadNode>(index,rn));
					it_rd++;
			}
			else 
			{
				roadNode temp;
				nodeData[0].insert(pair<long int, roadNode>(index, temp));

			}
		}
	}
	while (readBIN() == NEED_READ_AGAIN) 
	{
		vector<scanFreqData>::iterator it_sfd = mFreqData[0].begin();
		while (it_sfd != mFreqData[0].end()) 
		{
			if (it_sfd != mFreqData[0].end())
			{
				scanFreqData sfd = *it_sfd;
				sfd_col = CalDistanseM(sfd.lon, miny, minx, miny, true) / DATA_LEVEL + 1;
				sfd_row = CalDistanseM(minx, sfd.lat, minx, miny, true) / DATA_LEVEL + 1;
				long int index = sfd_row*pow(10, positionMove) + sfd_col;

				map<long int, roadNode>::iterator it_map = nodeData[0].find(index);
				if (it_map != nodeData[0].end())
				{

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

					roadNode rn = nodeData[0][index];
					//更新经度
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

					//node 增加
					rn.roadNodeNum += 1;
					rn.binNodeNum += 1;

					nodeData[0].erase(it_map);
					nodeData[0].insert(pair<long int, roadNode>(index, rn));
					it_sfd++;
				}
				else
				{
					roadNode temp;
					nodeData[0].insert(pair<long int, roadNode>(index, temp));

				}
			}
		
		}
		hsfd->clear();
	}
	printf("excel : %d, bin :%d",excel,bin);
}