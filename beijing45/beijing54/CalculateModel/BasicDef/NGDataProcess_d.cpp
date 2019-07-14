#include "NGDataProcess_d.h"
#include "../BasicDef/NG_ErrorCode.h"
#include "Macrodef.h"
#include <io.h>
#include <direct.h>
#include <algorithm>

int CNGDataProcess_d::DecodeStandDataFromDir(const char* pSrcDir)
{
	if (NULL == pSrcDir || access(pSrcDir,0) != 0 )
	{
		return POINT_CAN_NOT_NULL;//文件不存在
	}
	vector<string> files = GetFilesByDir(pSrcDir);
	if(files.size() == 0 ){
		return NO_SOURCE_FILE;
	}
	for (int i = 0 ; i < files.size() ; i ++)
	{
		DecodeStandData(files[i].c_str());
		//WriteSingleToCSVFile(pResultDir);
	}
	return NG_SUCCESS;
}


int CNGDataProcess_d::DecodeStandData(const char* pfile)
{
	if (NULL == pfile || access(pfile,0)!=0 )
	{
		return POINT_CAN_NOT_NULL;//文件不存在
	}
	FILE* fp = fopen(pfile,"rb");
	if (NULL == fp)
	{
		return FAIL_TO_OPEN_FILE;//打开文件失败
	}
	if (!GetRecordNum(fp,m_RecordNum))
	{
		fclose(fp);
		return FILE_FORM_WRONG;
	}
	m_allheads.reserve(m_RecordNum);
	fseek(fp,0,SEEK_SET);
	//	ng_geo_init();
	while(feof(fp) == 0){
		bool shouldswap = false;
		BinHead head;
		fread(&head,1,sizeof(head),fp);	

		if (head.checkcode != CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == CheckCode)
			{
				shouldswap = true;
			}else{
				fclose(fp);
				return FILE_FORM_WRONG;//文件格式错误
			}
		}
		if (shouldswap)
		{
			swap(&head.year,sizeof(head.year));
			swap(&head.misecond,sizeof(head.misecond));
			swap(&head.lon,sizeof(head.lon));
			swap(&head.lat,sizeof(head.lat));
			swap(&head.startfreq,sizeof(head.startfreq));
			swap(&head.freqstep,sizeof(head.freqstep));
			swap(&head.freqcount,sizeof(head.freqcount));
		}
		//只在中国，经度>纬度,因为数据有问题
		double curlng = head.lon>head.lat?head.lon:head.lat;
		double curlat = head.lat<head.lon?head.lat:head.lon;
		head.lon = curlng;
		head.lat = curlat;
		if (head.lon < 10 || head.lat < 10)
		{
			int nRes = fseek(fp,2*head.freqcount , SEEK_CUR);
			if (nRes == 0 )
			{
				continue;
			}else{
				return FAIL_TO_READ_FILE;
			}
		}
		ReadOneRecord(fp,head,shouldswap);
	}
	fclose(fp);
	return NG_SUCCESS;
}
int CNGDataProcess_d::ReadOneRecord(FILE* fp,BinHead& head,bool shouldswap)
{
	if (NULL == m_pdata || m_dataLength < head.freqcount)
	{
		NG_DELETE_ARRAY(m_pdata);
		m_dataLength = m_dataLength > head.freqcount? m_dataLength : head.freqcount;
		m_pdata = new(std::nothrow) short[m_dataLength];
		if (NULL == m_pdata)
		{
			fseek(fp,2*head.freqcount,SEEK_CUR);
			return MEMORY_WRONG;
		}
	}
	int readSize = fread(m_pdata,2,head.freqcount,fp);
	if (head.freqcount != readSize)
	{
		NG_DELETE_ARRAY(m_pdata);
		return FAIL_TO_READ_FILE;
	}

	if (shouldswap)
	{
		for (int i = 0 ; i < readSize ; i ++)
		{
			swap(&m_pdata[i],2);
		}
	}
	
	m_allheads.push_back(head);
	
	for (int i = 0 ; i < head.freqcount ; i ++)
	{
		unsigned __int64 freq = head.startfreq + i * head.freqstep;
		map<unsigned __int64 ,vector<short>>::iterator it = m_allDatas.find(freq);
		if (it == m_allDatas.end())
		{
			vector<short> datas;
			datas.reserve(m_RecordNum);
			datas.push_back(m_pdata[i]);
			m_allDatas.insert(std::make_pair(freq,datas));
			//vector<NGLocation> locations(1,NGLocation(head.lon,head.lat));
			//m_allLocations.insert(std::make_pair(freq,locations));
		}else{
			it->second.push_back(m_pdata[i]);
			//m_allLocations[freq].push_back(NGLocation(head.lon,head.lat));
		}
	}
	return NG_SUCCESS;
}

void CNGDataProcess_d::swap(void * data,int n)
{
	char * cdata = (char*)data;
	int bn = n/2;
	char tmp;
	for(int i=0;i<bn;i++)
	{
		tmp = cdata[i];
		cdata[i] = cdata[n-1-i];
		cdata[n-1-i] = tmp;
	}
}


vector<string> CNGDataProcess_d::GetFilesByDir(const char* pDirPath)
{
	vector<string> fPath;
	string fileName;
	long hFile=0;
	struct _finddata_t fileinfo;
	if((hFile=_findfirst(fileName.assign(pDirPath).append("\\*").c_str(),&fileinfo))!=-1)
	{
		do 
		{
			if(fileinfo.attrib&_A_SUBDIR)
				continue;
			fPath.push_back(fileName.assign(pDirPath).append("\\").append(fileinfo.name));
		} while (_findnext(hFile,&fileinfo)==0);
		_findclose(hFile);
	}
	return fPath;
}

CNGDataProcess_d::CNGDataProcess_d(void)
{
	m_pdata = NULL;
	m_dataLength = 0 ;
}

CNGDataProcess_d::~CNGDataProcess_d(void)
{
	NG_DELETE_ARRAY(m_pdata);
}

bool CNGDataProcess_d::GetRecordNum(FILE* fp,unsigned int& num)
{
	if (NULL == fp || feof(fp) != 0 )
	{
		return false;
	}
	fseek(fp,0,SEEK_END);
	unsigned long fileLength = ftell(fp);
	fseek(fp,0,SEEK_SET);
	BinHead head;
	fread(&head,sizeof(BinHead),1,fp);
	if (head.checkcode != CheckCode)
	{
		swap(&head.checkcode,4);
		if (head.checkcode == CheckCode)
		{
			swap(&head.freqcount,sizeof(head.freqcount));
		}else{
			return false;
		}
	}
	num = sizeof(BinHead) + head.freqcount * 2;
	if ( fileLength < num )
	{
		return false;
	}
	num = fileLength / num;
	return (0 == fileLength%num);
}


int CNGDataProcess_js::DecodeStandDataFromDir(const char* pSrcDir)
{
	if (NULL == pSrcDir || access(pSrcDir,0) != 0 )
	{
		return POINT_CAN_NOT_NULL;//文件不存在
	}
	vector<string> files = GetFilesByDir(pSrcDir);
	if(files.size() == 0 ){
		return NO_SOURCE_FILE;
	}
	for (int i = 0 ; i < files.size() ; i ++)
	{
		DecodeStandData(files[i].c_str());
		//WriteSingleToCSVFile(pResultDir);
	}
	return NG_SUCCESS;
}


int CNGDataProcess_js::DecodeStandData(const char* pfile)
{
	if (mFormat == eUnknown)
	{
		int nRes = CheckIsStandFormat(pfile);
		if (nRes == NG_SUCCESS)
		{
			mFormat = eStandScanFreqV1;
		}
		else if (nRes == FILE_FORM_WRONG)
		{
			nRes = CheckIsStandV3Format(pfile);
			if (nRes == NG_SUCCESS)
			{
				mFormat = eStandScanFreqV3;
			}
		}
	}
	if(mFormat==eStandScanFreqV1)
	{
		return ReadStand(pfile);
	}
	else if (mFormat == eStandScanFreqV3)
	{
		return ReadStandv3(pfile);
	}
	else
	{
		return FILE_FORM_WRONG;
	}
}
int CNGDataProcess_js::ReadOneRecord(FILE* fp,StandBinHeadV3& head,bool shouldswap)
{
	if (NULL == m_pdata || m_dataLength < head.freqcount)
	{
		NG_DELETE_ARRAY(m_pdata);
		m_dataLength = m_dataLength > head.freqcount? m_dataLength : head.freqcount;
		m_pdata = new(std::nothrow) short[m_dataLength];
		if (NULL == m_pdata)
		{
			fseek(fp,2*head.freqcount,SEEK_CUR);
			return MEMORY_WRONG;
		}
	}
	int readSize = fread(m_pdata,2,head.freqcount,fp);
	if (head.freqcount != readSize)
	{
		NG_DELETE_ARRAY(m_pdata);
		return FAIL_TO_READ_FILE;
	}

	if (shouldswap)
	{
		for (int i = 0 ; i < readSize ; i ++)
		{
			swap(&m_pdata[i],2);
		}
	}

	m_allheads.push_back(head);

	for (int i = 0 ; i < head.freqcount ; i ++)
	{
		unsigned __int64 freq = head.startfreq + i * head.freqstep;
		map<unsigned __int64 ,vector<short>>::iterator it = m_allDatas.find(freq);
		if (it == m_allDatas.end())
		{
			vector<short> datas;
			datas.reserve(m_RecordNum);


			datas.push_back(m_pdata[i]);
			m_allDatas.insert(std::make_pair(freq,datas));
			//vector<NGLocation> locations(1,NGLocation(head.lon,head.lat));
			//m_allLocations.insert(std::make_pair(freq,locations));
		}else{

			it->second.push_back(m_pdata[i]);
			//m_allLocations[freq].push_back(NGLocation(head.lon,head.lat));
		}
	}
	return NG_SUCCESS;
}

void CNGDataProcess_js::swap(void * data,int n)
{
	char * cdata = (char*)data;
	int bn = n/2;
	char tmp;
	for(int i=0;i<bn;i++)
	{
		tmp = cdata[i];
		cdata[i] = cdata[n-1-i];
		cdata[n-1-i] = tmp;
	}
}


vector<string> CNGDataProcess_js::GetFilesByDir(const char* pDirPath)
{
	vector<string> fPath;
	string fileName;
	long hFile=0;
	struct _finddata_t fileinfo;
	if((hFile=_findfirst(fileName.assign(pDirPath).append("\\*").c_str(),&fileinfo))!=-1)
	{
		do 
		{
			if(fileinfo.attrib&_A_SUBDIR)
				continue;
			fPath.push_back(fileName.assign(pDirPath).append("\\").append(fileinfo.name));
		} while (_findnext(hFile,&fileinfo)==0);
		_findclose(hFile);
	}
	return fPath;
}

CNGDataProcess_js::CNGDataProcess_js(void)
{
	mFormat=eUnknown;
	m_pdata = NULL;
	m_dataLength = 0 ;
}

CNGDataProcess_js::~CNGDataProcess_js(void)
{
	mFormat=eUnknown;
	NG_DELETE_ARRAY(m_pdata);
}

bool CNGDataProcess_js::GetRecordNum(FILE* fp,unsigned int& num)
{
	if (NULL == fp || feof(fp) != 0 )
	{
		return false;
	}
	fseek(fp,0,SEEK_END);
	unsigned long fileLength = ftell(fp);
	fseek(fp,0,SEEK_SET);
	BinHead head;
	fread(&head,sizeof(BinHead),1,fp);
	if (head.checkcode != CheckCode)
	{
		swap(&head.checkcode,4);
		if (head.checkcode == CheckCode)
		{
			swap(&head.freqcount,sizeof(head.freqcount));
		}else{
			return false;
		}
	}
	num = sizeof(BinHead) + head.freqcount * 2;
	if ( fileLength < num )
	{
		return false;
	}
	num = fileLength / num;
	return (0 == fileLength%num);
}

bool CNGDataProcess_js::GetRecordNumV3(FILE* fp,unsigned int& num)
{
	if (NULL == fp || feof(fp) != 0 )
	{
		return false;
	}
	fseek(fp,0,SEEK_END);
	unsigned long fileLength = ftell(fp);
	fseek(fp,0,SEEK_SET);
	StandBinHeadV3 head;
	fread(&head,sizeof(StandBinHeadV3),1,fp);
	if (head.checkcode != CheckCode)
	{
		swap(&head.checkcode,4);
		if (head.checkcode == CheckCode)
		{
			swap(&head.freqcount,sizeof(head.freqcount));
		}else{
			return false;
		}
	}
	num = sizeof(StandBinHeadV3) + head.freqcount * 2;
	if ( fileLength < num )
	{
		return false;
	}
	num = fileLength / num;
	return (0 == fileLength%num);
}

#define Head2016ValueCheck(head) ((head.lon>-180&&head.lon<180)&&(head.lat>-180&&head.lat<180)&&(head.startfreq<1e10&&head.startfreq>0)&&(head.freqstep<1e9&&head.freqstep>0)&&(head.freqcount<1e6&&head.freqcount>0))
int CNGDataProcess_js::CheckIsStandFormat(const char *filename)
{
	if (NULL == filename || access(filename,0)!=0 )
	{
		return THE_FILE_IS_NOT_EXIST;//文件不存在
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return FAIL_TO_OPEN_FILE;//打开文件失败
	} 
	//Clear();
	unsigned __int64 maxfreq; //目前hz
	unsigned __int64 minfreq; //目前hz
	bool bfirst=true;
	//	ng_geo_init();
	while(feof(fp) == 0)
	{
		bool shouldswap = false;
		BinHead head;
		fread(&head,1,sizeof(head),fp);
		if (head.checkcode != CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == CheckCode)
			{
				shouldswap = true;
			}
			else
			{
				fclose(fp);
				return FILE_FORM_WRONG;//文件格式错误,有可能不是国家格式
			}
		}

		if(shouldswap)
		{
			swap(&head.year,sizeof(head.year));
			swap(&head.lon,sizeof(head.lon));
			swap(&head.lat,sizeof(head.lat));
			swap(&head.startfreq,sizeof(head.startfreq));
			swap(&head.freqstep,sizeof(head.freqstep));
			swap(&head.freqcount,sizeof(head.freqcount));
		}

		if(!Head2016ValueCheck(head))
		{
			fclose(fp);
			return FILE_FORM_WRONG;//文件格式错误,有可能不是国家格式
		}

		fclose(fp);
		return NG_SUCCESS;

	}

	fclose(fp);
	return NG_SUCCESS;
}

#define Head2017ValueCheck(head) ((head.lon>-1.8e10&&head.lon<1.8e10)&&(head.lat>-1.8e10&&head.lat<1.e10)/*&&(head.startfreq<1e10&&head.startfreq>0)*/&&(head.freqstep<1e9&&head.freqstep>0)&&(head.freqcount<1e6&&head.freqcount>0))
int CNGDataProcess_js::CheckIsStandV3Format(const char *filename)
{
	if (NULL == filename || access(filename,0)!=0 )
	{
		return THE_FILE_IS_NOT_EXIST;//文件不存在
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return FAIL_TO_OPEN_FILE;//打开文件失败
	} 
	//Clear();
	unsigned __int64 maxfreq; //目前hz
	unsigned __int64 minfreq; //目前hz
	bool bfirst=true;
	//	ng_geo_init();
	while(feof(fp) == 0)
	{
		bool shouldswap = false;
		StandBinHeadV3 head;
		fread(&head,1,sizeof(head),fp);
		if (head.checkcode != CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == CheckCode)
			{
				shouldswap = true;
			}
			else
			{
				fclose(fp);
				return FILE_FORM_WRONG;//文件格式错误,有可能不是国家格式

			}
		}

		if(shouldswap)
		{
			swap(&head.year,sizeof(head.year));
			swap(&head.lon,sizeof(head.lon));
			swap(&head.lat,sizeof(head.lat));
			swap(&head.startfreq,sizeof(head.startfreq));
			swap(&head.freqstep,sizeof(head.freqstep));
			swap(&head.freqcount,sizeof(head.freqcount));
		}

		if(!Head2017ValueCheck(head))
		{
			fclose(fp);
			return FILE_FORM_WRONG;//文件格式错误,有可能不是国家格式
		}

		fclose(fp);
		return NG_SUCCESS;

	}

	fclose(fp);
	return NG_SUCCESS;
}

int CNGDataProcess_js::ReadStand(const char *pfile)
{
	if (NULL == pfile || access(pfile,0)!=0 )
	{
		return POINT_CAN_NOT_NULL;//文件不存在
	}
	FILE* fp = fopen(pfile,"rb");
	if (NULL == fp)
	{
		return FAIL_TO_OPEN_FILE;//打开文件失败
	}
	if (!GetRecordNum(fp,m_RecordNum))
	{
		fclose(fp);
		return FILE_FORM_WRONG;
	}
	m_allheads.reserve(m_RecordNum);
	fseek(fp,0,SEEK_SET);
	//	ng_geo_init();
	while(feof(fp) == 0){
		bool shouldswap = false;
		BinHead head;
		fread(&head,1,sizeof(head),fp);	

		if (head.checkcode != CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == CheckCode)
			{
				shouldswap = true;
			}else{
				fclose(fp);
				return FILE_FORM_WRONG;//文件格式错误
			}
		}
		if (shouldswap)
		{
			swap(&head.year,sizeof(head.year));
			swap(&head.misecond,sizeof(head.misecond));
			swap(&head.lon,sizeof(head.lon));
			swap(&head.lat,sizeof(head.lat));
			swap(&head.startfreq,sizeof(head.startfreq));
			swap(&head.freqstep,sizeof(head.freqstep));
			swap(&head.freqcount,sizeof(head.freqcount));
		}
		//只在中国，经度>纬度,因为数据有问题
		double curlng = head.lon>head.lat?head.lon:head.lat;
		double curlat = head.lat<head.lon?head.lat:head.lon;
		head.lon = curlng;
		head.lat = curlat;
		/*if (head.lon < 10 || head.lat < 10)
		{
			int nRes = fseek(fp,2*head.freqcount , SEEK_CUR);
			if (nRes == 0 )
			{
				continue;
			}else{
				return FAIL_TO_READ_FILE;
			}
		}*/

		//将2016头转为2017头
		StandBinHeadV3 headV3;
		headV3.checkcode = head.checkcode;
		headV3.equ_no = head.equ_no;
		headV3.ant_type = head.ant_type;
		headV3.year = head.year;
		headV3.mon = head.mon;
		headV3.day = head.day;
		headV3.hour = head.hour;
		headV3.minute = head.minute;
		headV3.second = head.second;
		headV3.misecond = head.misecond;
		headV3.scanspeed = 0;
		headV3.lon = head.lon*1e8;
		headV3.lat = head.lat*1e8;
		headV3.height = head.height;

		headV3.startfreq = head.startfreq;
		headV3.freqstep = head.freqstep;
		headV3.freqcount = head.freqcount;

		ReadOneRecord(fp,headV3,shouldswap);
	}
	fclose(fp);
	return NG_SUCCESS;
}

int CNGDataProcess_js::ReadStandv3(const char *pfile)
{
	if (NULL == pfile || access(pfile,0)!=0 )
	{
		return POINT_CAN_NOT_NULL;//文件不存在
	}
	FILE* fp = fopen(pfile,"rb");
	if (NULL == fp)
	{
		return FAIL_TO_OPEN_FILE;//打开文件失败
	}
	if (!GetRecordNumV3(fp,m_RecordNum))
	{
		fclose(fp);
		return FILE_FORM_WRONG;
	}
	m_allheads.reserve(m_RecordNum);
	fseek(fp,0,SEEK_SET);
	//	ng_geo_init();
	while(feof(fp) == 0){
		bool shouldswap = false;
		StandBinHeadV3 head;
		if(fread(&head,sizeof(head),1,fp) != 1)
		{
			continue;
		}

		if (head.checkcode != CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == CheckCode)
			{
				shouldswap = true;
			}else{
				fclose(fp);
				return FILE_FORM_WRONG;//文件格式错误
			}
		}
		if (shouldswap)
		{
			swap(&head.year,sizeof(head.year));
			swap(&head.misecond,sizeof(head.misecond));
			swap(&head.lon,sizeof(head.lon));
			swap(&head.lat,sizeof(head.lat));
			swap(&head.startfreq,sizeof(head.startfreq));
			swap(&head.freqstep,sizeof(head.freqstep));
			swap(&head.freqcount,sizeof(head.freqcount));
		}
		//只在中国，经度>纬度,因为数据有问题
		double curlng = head.lon>head.lat?head.lon:head.lat;
		double curlat = head.lat<head.lon?head.lat:head.lon;
		head.lon = curlng;
		head.lat = curlat;
// 		if (head.lon < 10 || head.lat < 10)
// 		{
// 			int nRes = fseek(fp,2*head.freqcount , SEEK_CUR);
// 			if (nRes == 0 )
// 			{
// 				continue;
// 			}else{
// 				return FAIL_TO_READ_FILE;
// 			}
// 		}
		ReadOneRecord(fp,head,shouldswap);
	}
	fclose(fp);
	return NG_SUCCESS;
}
