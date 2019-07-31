#pragma once


double area_1[13][2] = { 
	{ 116.131288,39.591551 },{ 116.19390,40.04451 },{ 116.251469,40.05966 },{ 116.303356,39.585468 },
	{116.32502,39.561552},{116.323963,39.514624},{116.291693,39.483453},{116.251221,39.462157},
	{116.202794,39.461967},{116.153131,39.472806},{116.125064,39.504741},{116.123086,39.55159}
};
double area_2[13][2] = {
	{116.161581,39.575690},{116.202176,39.585563},{116.242401,39.59415},{116.28401,39.575406},
	{},{},{},{},
	{},{},{},{}
};
struct roadNode
{
	int colNum;
	int rowNum;
	double lon;
	double lat;
	double serNo1;
	double serNo2;
	double serNo3;
	double serNo4;
	double serNo5;
	double serNo6;
	double serNo7;
	double serNo8;
	double serCount;
	double elec;
	double battery;
	int excelNodeNum;
	int roadNodeNum;
	int binNodeNum;
	roadNode()
	{
		colNum = 0;
		rowNum = 0;
		lon=0.0;
		lat=0.0;
		serNo1=0.0;
		serNo2=0.0;
		serNo3=0.0;
		serNo4=0.0;
		serNo5=0.0;
		serNo6=0.0;
		serNo7=0.0;
		serNo8=0.0;
		serCount = 0.0;
		elec=0.0;
		battery=0.0;
		excelNodeNum = 0;
		roadNodeNum = 0;
		binNodeNum = 0;
	}
};