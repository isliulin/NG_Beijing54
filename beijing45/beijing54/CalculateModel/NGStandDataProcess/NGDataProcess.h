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


	//��ĳ��Ƶ������ݽ��������ں�
	static void ProcessSamePoint(NGDataVector& sites,double resultion);

	int DecodeStandData(const char* pSrcDir,const char* pResultDir);//�������ұ�׼·�����ݣ������ļ���

	int StandDataDilute(const char* pSrcDir,unsigned __int32 freqBand,const char* pResultFile);
private:
	int DecodeStandData(const char* pfile);//�������ұ�׼·������

	int StandDataDilute(const char* pfile);
	int ReadOneRecord(FILE* fp,BinHead& head,bool shouldswap); //��ȡһ������

	int ReadOneRecord(FILE* fp,bool shouldswap);

	void WriteToStandFile(const char* pfile);

	inline double Distance(double x1,double y1,double x2,double y2){return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));}

	void swap(void * data,int n);//�����ֽ���

	vector<string> GetFilesByDir(const char* pDirPath);

	void WriteSingleToCSVFile(const char* pResultDir);

	void WriteSingleToBinFile(const char* pResultDir);

	void DoAverage_Filter(vector<short>& sites);

private:
	map<unsigned __int64 ,vector<short>> m_allDatas;//һ���ļ��е�·������

	vector<BinHead> m_allheads;//�������е�ͷ�������ж���һ�����Ƿ����һ�������̫Զ��GPS��׼�ĵ�Ӧ������

	map<unsigned __int64 ,vector<NGLocation>> m_allLocations;//Ƶ���Ӧ��·��λ�ã�ÿһ��·�����ݲ��Ե�Ƶ�β�һ��������Ҫ����·�������

	//ϡ������ʱ��Ҫ�ĳ�Ա����
	vector<short> freqDatas;
	BinHead m_head;
	unsigned __int32 m_diluBand;//ϡ�ͳɵ�Ŀ�����
	const char* m_pResultFile;

	//�����С
	short* m_pdata;
    unsigned int m_dataLength;
};

#endif