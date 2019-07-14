#ifndef NG_DATA_PROCESS_H
#define NG_DATA_PROCESS_H

#include <vector>
#include <map>
#include <string>
#include "../NGStandDataProcess/CNGPreDefine.h"
#include "StandScanFreqMonitorFile.h"

using namespace std;


class CNGDataProcess_d
{
public:
	CNGDataProcess_d(void);
	~CNGDataProcess_d(void);

	int DecodeStandDataFromDir(const char* pSrcDir);//�������ұ�׼·�����ݣ������ļ���

	int DecodeStandData(const char* pfile);//�������ұ�׼·������

private:

	int ReadOneRecord(FILE* fp,BinHead& head,bool shouldswap); //��ȡһ������


	void swap(void * data,int n);//�����ֽ���

	vector<string> GetFilesByDir(const char* pDirPath);


	bool GetRecordNum(FILE* fp,unsigned int& num);

public:
	map<unsigned __int64 ,vector<short>> m_allDatas;//һ���ļ��е�·������

	vector<BinHead> m_allheads;

	//map<unsigned __int64 ,vector<NGLocation>> m_allLocations;//Ƶ���Ӧ��·��λ�ã�ÿһ��·�����ݲ��Ե�Ƶ�β�һ��������Ҫ����·�������

private:

	short* m_pdata;
	unsigned int m_dataLength;

	unsigned int m_RecordNum;
};

class CNGDataProcess_js
{
public:
	CNGDataProcess_js(void);
	~CNGDataProcess_js(void);

	int DecodeStandDataFromDir(const char* pSrcDir);//�������ұ�׼·�����ݣ������ļ���

	int DecodeStandData(const char* pfile);//�������ұ�׼·������

	int CheckIsStandFormat(const char *filename);
	int CheckIsStandV3Format(const char *filename);

	int ReadStand(const char *pfile);
	int ReadStandv3(const char *pfile);

private:

	int ReadOneRecord(FILE* fp,StandBinHeadV3& head,bool shouldswap); //��ȡһ������


	void swap(void * data,int n);//�����ֽ���

	vector<string> GetFilesByDir(const char* pDirPath);


	bool GetRecordNum(FILE* fp,unsigned int& num);
	bool GetRecordNumV3(FILE* fp,unsigned int& num);

public:
	map<unsigned __int64 ,vector<short>> m_allDatas;//һ���ļ��е�·������

	vector<StandBinHeadV3> m_allheads;

	//map<unsigned __int64 ,vector<NGLocation>> m_allLocations;//Ƶ���Ӧ��·��λ�ã�ÿһ��·�����ݲ��Ե�Ƶ�β�һ��������Ҫ����·�������

private:

	short* m_pdata;
	unsigned int m_dataLength;

	unsigned int m_RecordNum;
	eScanFreqFormat mFormat;
};

#endif