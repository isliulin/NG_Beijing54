#pragma once

struct roadNode
{
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
	double elec;
	double battery;
	int excelNodeNum;
	int roadNodeNum;
	int binNodeNum;
	roadNode()
	{
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
		elec=0.0;
		battery=0.0;
		excelNodeNum = 0;
		roadNodeNum = 0;
		binNodeNum = 0;
	}
};