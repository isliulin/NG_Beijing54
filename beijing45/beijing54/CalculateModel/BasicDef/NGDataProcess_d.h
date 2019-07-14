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

	int DecodeStandDataFromDir(const char* pSrcDir);//解析国家标准路测数据，输入文件夹

	int DecodeStandData(const char* pfile);//解析国家标准路测数据

private:

	int ReadOneRecord(FILE* fp,BinHead& head,bool shouldswap); //读取一行数据


	void swap(void * data,int n);//交换字节序

	vector<string> GetFilesByDir(const char* pDirPath);


	bool GetRecordNum(FILE* fp,unsigned int& num);

public:
	map<unsigned __int64 ,vector<short>> m_allDatas;//一个文件中的路测数据

	vector<BinHead> m_allheads;

	//map<unsigned __int64 ,vector<NGLocation>> m_allLocations;//频点对应的路测位置，每一段路测数据测试的频段不一样，所以要保存路测点数据

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

	int DecodeStandDataFromDir(const char* pSrcDir);//解析国家标准路测数据，输入文件夹

	int DecodeStandData(const char* pfile);//解析国家标准路测数据

	int CheckIsStandFormat(const char *filename);
	int CheckIsStandV3Format(const char *filename);

	int ReadStand(const char *pfile);
	int ReadStandv3(const char *pfile);

private:

	int ReadOneRecord(FILE* fp,StandBinHeadV3& head,bool shouldswap); //读取一行数据


	void swap(void * data,int n);//交换字节序

	vector<string> GetFilesByDir(const char* pDirPath);


	bool GetRecordNum(FILE* fp,unsigned int& num);
	bool GetRecordNumV3(FILE* fp,unsigned int& num);

public:
	map<unsigned __int64 ,vector<short>> m_allDatas;//一个文件中的路测数据

	vector<StandBinHeadV3> m_allheads;

	//map<unsigned __int64 ,vector<NGLocation>> m_allLocations;//频点对应的路测位置，每一段路测数据测试的频段不一样，所以要保存路测点数据

private:

	short* m_pdata;
	unsigned int m_dataLength;

	unsigned int m_RecordNum;
	eScanFreqFormat mFormat;
};

#endif