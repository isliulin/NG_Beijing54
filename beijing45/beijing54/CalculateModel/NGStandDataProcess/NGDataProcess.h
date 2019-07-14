#ifndef NG_DATA_PROCESS_H
#define NG_DATA_PROCESS_H

#include <vector>
#include <map>
#include <string>
#include "CNGPreDefine.h"

using namespace std;

class CNGDataProcess
{
public:
	CNGDataProcess(void);
	~CNGDataProcess(void);


	//对某个频点的数据进行数据融合
	static void ProcessSamePoint(NGDataVector& sites,double resultion);

	int DecodeStandData(const char* pSrcDir,const char* pResultDir);//解析国家标准路测数据，输入文件夹

	int StandDataDilute(const char* pSrcDir,unsigned __int32 freqBand,const char* pResultFile);
private:
	int DecodeStandData(const char* pfile);//解析国家标准路测数据

	int StandDataDilute(const char* pfile);
	int ReadOneRecord(FILE* fp,BinHead& head,bool shouldswap); //读取一行数据

	int ReadOneRecord(FILE* fp,bool shouldswap);

	void WriteToStandFile(const char* pfile);

	inline double Distance(double x1,double y1,double x2,double y2){return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));}

	void swap(void * data,int n);//交换字节序

	vector<string> GetFilesByDir(const char* pDirPath);

	void WriteSingleToCSVFile(const char* pResultDir);

	void WriteSingleToBinFile(const char* pResultDir);

	void DoAverage_Filter(vector<short>& sites);

private:
	map<unsigned __int64 ,vector<short>> m_allDatas;//一个文件中的路测数据

	vector<BinHead> m_allheads;//保存所有的头，用于判断下一个点是否和上一个点距离太远，GPS不准的点应该舍弃

	map<unsigned __int64 ,vector<NGLocation>> m_allLocations;//频点对应的路测位置，每一段路测数据测试的频段不一样，所以要保存路测电数据

	//稀释数据时需要的成员变量
	vector<short> freqDatas;
	BinHead m_head;
	unsigned __int32 m_diluBand;//稀释成的目标带宽
	const char* m_pResultFile;

	//缓存大小
	short* m_pdata;
    unsigned int m_dataLength;
};

#endif