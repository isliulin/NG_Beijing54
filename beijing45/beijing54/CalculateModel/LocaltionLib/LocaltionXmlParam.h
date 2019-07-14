
/*****************************************************************************
// 文件名:		 
// 编写者:	李冬	  
// 编写日期:2015.12	  
// 简要描述 TDOA定位算法需要的参数xml生成类,TDOA输入IQ数据文件，以及文件对应的监测站的经纬度信息
// 设计文档名称：
// 设计文档版本号
// 设计文档禅道ID 
// 修改记录:		 
//
// (C) 2017  Ng-networks
*****************************************************************************/


#ifndef NH_LOCALTION_PARAM_H
#define NH_LOCALTION_PARAM_H
#include <vector>
#include <string>
#include "..\..\XercesWrapper\XMLDocument.h"

using std::vector;
using std::string;
using namespace XercesWrapperNS;

#define XmlUseCode "utf-8"
#define NG_Environment "NG_Environment"
#define ParamsList "ParamsList"
#define NewIntStationList "NewIntStationList"
#define CalculateParam "CalculateParam"
#define Result "Result"

class CLocaltionXmlParam
{
public:
	CLocaltionXmlParam(void);
	~CLocaltionXmlParam(void);
public:
	virtual void AddMonitorStationAndFile(double x , double y ,const char *pIQPath);
	virtual void SetResult(const char * szSavePath,const char* szIndexResult);
	virtual bool WriteToXml(const char* paramxml);
public:
	vector<string> IQDataFiles;
	vector<double> posXs;//台站位置
	vector<double> posYs;
	string _savePath;//结果文件路径
	string _resultXml;//结果输出文件
protected:
	bool CalculateParamToXml(XmlDocument & xmldoc);
	bool DataFilesToXml(XmlDocument & xmldoc);
	bool WriteResultPathXml( string & savePath,string & resultXml,XmlDocument&xmldoc );
	bool SaveXmlToFile( XmlDocument&xmldoc,const char* szFilename );
};

#endif
