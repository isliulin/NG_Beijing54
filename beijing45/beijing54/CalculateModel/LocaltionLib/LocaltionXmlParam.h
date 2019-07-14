
/*****************************************************************************
// �ļ���:		 
// ��д��:	�	  
// ��д����:2015.12	  
// ��Ҫ���� TDOA��λ�㷨��Ҫ�Ĳ���xml������,TDOA����IQ�����ļ����Լ��ļ���Ӧ�ļ��վ�ľ�γ����Ϣ
// ����ĵ����ƣ�
// ����ĵ��汾��
// ����ĵ�����ID 
// �޸ļ�¼:		 
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
	vector<double> posXs;//̨վλ��
	vector<double> posYs;
	string _savePath;//����ļ�·��
	string _resultXml;//�������ļ�
protected:
	bool CalculateParamToXml(XmlDocument & xmldoc);
	bool DataFilesToXml(XmlDocument & xmldoc);
	bool WriteResultPathXml( string & savePath,string & resultXml,XmlDocument&xmldoc );
	bool SaveXmlToFile( XmlDocument&xmldoc,const char* szFilename );
};

#endif
