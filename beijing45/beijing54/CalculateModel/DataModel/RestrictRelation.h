#ifndef __DATAMODEL_RESTRICTRELATION_h
#define __DATAMODEL_RESTRICTRELATION_h

#include <string>
#include "../BasicDef/GeoShape.h"
#include "../DataModel/EnumDef.h"

struct ScmRelationStation        //关系台站
{
	std::string mID;   //台站ID
	double mdFreqMhz;  //台站的频率
	double mdBWHz;   //台站的带宽
	CGeoPoint mLocation; //台站位置
	double mdAntHeightM; //台站的天线高度，地图之上的高度
	ELocationType meLocationType;  //台站的位置类别
	std::string mResultFileName; //计算的结果文件
	short mnRelation;    //台站的关系
};


#endif