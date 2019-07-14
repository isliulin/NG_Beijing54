#ifndef __DATAMODEL_RESTRICTRELATION_h
#define __DATAMODEL_RESTRICTRELATION_h

#include <string>
#include "../BasicDef/GeoShape.h"
#include "../DataModel/EnumDef.h"

struct ScmRelationStation        //��ϵ̨վ
{
	std::string mID;   //̨վID
	double mdFreqMhz;  //̨վ��Ƶ��
	double mdBWHz;   //̨վ�Ĵ���
	CGeoPoint mLocation; //̨վλ��
	double mdAntHeightM; //̨վ�����߸߶ȣ���ͼ֮�ϵĸ߶�
	ELocationType meLocationType;  //̨վ��λ�����
	std::string mResultFileName; //����Ľ���ļ�
	short mnRelation;    //̨վ�Ĺ�ϵ
};


#endif