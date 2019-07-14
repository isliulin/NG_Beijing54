#include "NGDataProcess.h"
#include "ErrorCode.h"
#include <io.h>
#include <direct.h>
#include <algorithm>
#include "..\KoordTrans\KoordTrans.h"



#define SAME_HEAD_NUM 16

#define FREQ_BAND_NUM 11

NGFreqBand TARGETFREQ[FREQ_BAND_NUM] = {
	                                                                                      NGFreqBand(875*1e5,108*1e6,100*1e3),
	                                                                                      NGFreqBand(870*1e6,879840000,1230000),
                                                                                          NGFreqBand(934*1e6,960*1e6,200*1e3),
																						  NGFreqBand(1805*1e6,1845*1e6,200*1e3),
                                                                                          NGFreqBand(1845*1e6,1875*1e6,15*1e6),
                                                                                          NGFreqBand(1880*1e6,1885*1e6,5*1e6),
																						  NGFreqBand(1885*1e6,1915*1e6,30*1e6),
																						  NGFreqBand(2010*1e6,2025*1e6,1600*1e3),
																						  NGFreqBand(2110*1e6,2130*1e6,20*1e6),
																						  NGFreqBand(2130*1e6,2155*1e6,5*1e6),
																						  NGFreqBand(2555*1e6,2655*1e6,20*1e6)
                                                                                          };



bool Smaller(const MonitorData& data1, const MonitorData& data2)
{
	if(data1.X < data2.X)
	{
		return true;
	}
	else if(data1.X == data2.X)
	{
		if(data1.Y < data2.Y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}	
}


CNGDataProcess::CNGDataProcess(void)
{
	m_dataLength = 10000;
	m_pdata = NULL;
}



CNGDataProcess::~CNGDataProcess(void)
{
	NG_DELETE_ARRAY(m_pdata);
}


void CNGDataProcess::DoAverage_Filter(vector<short>& sites)
{
	const int FILTER_NUMBER_ALL		= FilterWidth;
	const int FILTER_NUMBER_AHEAD	= (FILTER_NUMBER_ALL - 1)/2;	//当前点之前和之后参与滤波的点数。

	size_t unSize = sites.size();
	if(unSize < FILTER_NUMBER_ALL)
	{
		//如果文件长度小于均值滤波的长度，则直接返回
		return;
	}
	vector<short> mdValues(sites);
	double sum=0;
	vector<short>::iterator iter = sites.begin();
	vector<short>::iterator iterBefore = mdValues.begin();
	vector<short>::iterator iterAfter = mdValues.begin();
	for(size_t j=0; j< FILTER_NUMBER_ALL; j++, iterAfter++)
	{		
		sum = sum + *iterAfter;
		if(j < FILTER_NUMBER_AHEAD)
		{
			iter++;
		}			
	}
	*iter = sum / FILTER_NUMBER_ALL;

	//处理中间的部分
	iter++;
	for(size_t j=FILTER_NUMBER_AHEAD+1; j<unSize-FILTER_NUMBER_AHEAD; 
		j++, iterBefore++, iterAfter++, iter++)
	{
		sum += *iterAfter;
		sum -= *iterBefore;
		*iter = sum/FILTER_NUMBER_ALL;
	}
}



void CNGDataProcess::ProcessSamePoint(NGDataVector& sites,double resultion)
{
	vector<MonitorData> outDatas(sites.size());

	for (int i = 0 ; i < sites.size() ; i ++)
	{
		outDatas[i].X= (int)((sites[i].x- LowLeftX)/resultion);
		outDatas[i].Y = (int)((sites[i].y- LowLeftY)/resultion);
		outDatas[i].mdValue = sites[i].value;
	}
	std::sort(outDatas.begin(),outDatas.end(),Smaller);
	sites.clear();
	MonitorData data;
	sites.reserve(outDatas.size()/5);
	data = outDatas[0];
	int SameCount = 1;

	for (int i = 1 ; i < outDatas.size() ; i ++)
	{
		if (data.X == outDatas[i].X && data.Y == outDatas[i].Y)
		{
			data.mdValue += outDatas[i].mdValue;
			SameCount ++;

		}
		else
		{
			NGPOINT result;
			result.x= data.X * resultion + LowLeftX;
			result.y= data.Y * resultion + LowLeftY;
			result.value = data.mdValue/SameCount;
			sites.push_back(result);
			//下一次
			data = outDatas[i];
			SameCount = 1;
		}
	}

	//最后一次结果
	NGPOINT result;
	result.x= data.X * resultion + LowLeftX;
	result.y= data.Y * resultion + LowLeftY;
	result.value = data.mdValue/SameCount;
	sites.push_back(result);

}

int CNGDataProcess::DecodeStandData(const char* pSrcDir,const char* pResultDir)
{
	if (NULL == pSrcDir || access(pSrcDir,0) != 0 )
	{
		return POINT_CAN_NOT_NULL;//文件不存在
	}
	vector<string> files = GetFilesByDir(pSrcDir);
	if(files.size() == 0 ){
		return NO_SOURCE_FILE;
	}
	ng_geo_init();
	for (int i = 0 ; i < files.size() ; i ++)
	{
		DecodeStandData(files[i].c_str());
		map<unsigned __int64 ,vector<short>> :: iterator it;
		for ( it = m_allDatas.begin() ; it != m_allDatas.end() ; it ++)
		{
			DoAverage_Filter(it->second);
		}
		WriteSingleToBinFile(pResultDir);
	}
	return SUCCESS;
}


int CNGDataProcess::DecodeStandData(const char* pfile)
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
				fclose(fp);
				return FAIL_TO_READ_FILE;
			}
		}
		ReadOneRecord(fp,head,shouldswap);
	}
	fclose(fp);
	return SUCCESS;
}
int CNGDataProcess::ReadOneRecord(FILE* fp,BinHead& head,bool shouldswap)
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
	memset(m_pdata,0,2 * m_dataLength);
	int readSize = fread(m_pdata,2,head.freqcount,fp);
	if (head.freqcount != readSize)
	{
		return FAIL_TO_READ_FILE;
	}
	unsigned __int64 endfreq = head.startfreq + (unsigned __int64)head.freqstep * (unsigned __int64)head.freqcount;
	if (endfreq < TARGETFREQ[0].beginFreq || head.startfreq >TARGETFREQ[FREQ_BAND_NUM-1].endFreq )
	{
		return SUCCESS;
	}
	int size = m_allheads.size();
	if (size > 0)
	{
		BinHead& beforeHead = m_allheads[size - 1];
		double beforeLng,beforeLat,lng,lat;
		ng_geo_trans(103,PlaneCoord,beforeHead.lon,beforeHead.lat,&beforeLng,&beforeLat);
		ng_geo_trans(103,PlaneCoord,head.lon,head.lat,&lng,&lat);
		if (Distance(beforeLng,beforeLat,lng,lat) > 1e3)
		{
			return SUCCESS;
		}
	}
	if (shouldswap)
	{
		for (int i = 0 ; i < readSize ; i ++)
		{
			swap(&m_pdata[i],2);
		}
	}
	for (int i = 0 ; i < FREQ_BAND_NUM ; i ++)
	{
		if (endfreq < TARGETFREQ[i].beginFreq || head.startfreq >TARGETFREQ[i].endFreq )
		{
			continue;//如果该段数据的频段信息不在该频段内
		}
		for (unsigned __int64  freq = TARGETFREQ[i].beginFreq ; freq <=  TARGETFREQ[i].endFreq; freq += TARGETFREQ[i].freqStep)
		{
			//计算信道频率，根据带宽计算开始频率和结束频率，计算索引，对索引范围内的频点数据取平均值作为信道的场强
			unsigned __int64 fc1 = freq - TARGETFREQ[i].freqStep/2;
			unsigned __int64 fc2 = freq + TARGETFREQ[i].freqStep/2;
			int beginIndex = (fc1 - head.startfreq)/head.freqstep;
			int endIndex = (fc2 - head.startfreq)/head.freqstep;
			if (beginIndex >= (int)head.freqcount || endIndex < 0)
			{
				continue;//索引和数据范围没有重叠
			}
			//如果有重叠，则取交集
			beginIndex = beginIndex < 0 ? 0 : beginIndex;
			endIndex = endIndex >= (int)head.freqcount? head.freqcount - 1 : endIndex;
			int num = 0 ;
			double power = 0 ;
			for (int k = beginIndex ; k < endIndex ; k ++)
			{
				num ++;
				power += pow(10.0,m_pdata[k]/100.0);
			}
			if (num == 0 )
			{
				continue;
			}
			short cur = 100*log10(power/num);
			map<unsigned __int64 ,vector<short>>::iterator it = m_allDatas.find(freq);
			if (it == m_allDatas.end())
			{
				vector<short> datas(1,cur);
				m_allDatas.insert(std::make_pair(freq,datas));
				vector<NGLocation> locations(1,NGLocation(head.lon,head.lat));
				m_allLocations.insert(std::make_pair(freq,locations));
			}else{
				it->second.push_back(cur);
				m_allLocations[freq].push_back(NGLocation(head.lon,head.lat));
			}
		}
	}
	m_allheads.push_back(head);
	return SUCCESS;
}

void CNGDataProcess::swap(void * data,int n)
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


vector<string> CNGDataProcess::GetFilesByDir(const char* pDirPath)
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

void CNGDataProcess::WriteSingleToCSVFile(const char* pResultDir)
{
	if (access(pResultDir,0) != 0 )
	{
		mkdir(pResultDir);//如果文件夹不存在则创建文件夹
	}
	map<unsigned __int64 ,vector<short>>::iterator it;
	for ( it = m_allDatas.begin() ; it != m_allDatas.end() ; ++ it)
	{
		char temp[512];
		sprintf(temp,"%s\\Freq_%llu.csv",pResultDir,it->first);
		FILE* fp = fopen(temp,"a+");
		if (NULL == fp)
		{
			continue;
		}
		vector<short>& datas = it->second;
		vector<NGLocation>& locations = m_allLocations[it->first];
		for (int i = 0 ; i < datas.size() ; i ++)
		{
			fprintf(fp,"%f,%f,%hd\n",locations[i].x,locations[i].y,datas[i]);
		}
		datas.clear();
		locations.clear();
		fclose(fp);
	}
	m_allDatas.clear();
	m_allLocations.clear();
	m_allheads.clear();
}

void CNGDataProcess::WriteSingleToBinFile(const char* pResultDir)
{
	if (access(pResultDir,0) != 0 )
	{
		mkdir(pResultDir);//如果文件夹不存在则创建文件夹
	}
	map<unsigned __int64 ,vector<short>>::iterator it;
	for ( it = m_allDatas.begin() ; it != m_allDatas.end() ; ++ it)
	{
		char temp[512];
		sprintf(temp,"%s\\Freq_%llu.bin",pResultDir,it->first);
		FILE* fp = fopen(temp,"ab+");
		if (NULL == fp)
		{
			continue;
		}
		vector<short>& datas = it->second;
		vector<NGLocation>& locations = m_allLocations[it->first];
		for (int i = 0 ; i < datas.size() ; i ++)
		{
			fwrite(&locations[i].x,8,1,fp);
			fwrite(&locations[i].y,8,1,fp);
			fwrite(&datas[i],2,1,fp);
		}
		datas.clear();
		locations.clear();
		fclose(fp);
	}
	m_allDatas.clear();
	m_allLocations.clear();
	m_allheads.clear();
}



int CNGDataProcess::ReadOneRecord(FILE* fp,bool shouldswap)
{
	if (NULL == m_pdata || m_dataLength < m_head.freqcount)
	{
		NG_DELETE_ARRAY(m_pdata);
		m_dataLength = m_dataLength > m_head.freqcount? m_dataLength : m_head.freqcount;
		m_pdata = new(std::nothrow) short[m_dataLength];
		if (NULL == m_pdata)
		{
			fseek(fp,2*m_head.freqcount,SEEK_CUR);
			return  MEMORY_WRONG;
		}
	}
	memset(m_pdata,0,2 * m_dataLength);
	int readSize = fread(m_pdata,2,m_head.freqcount,fp);
	if (m_head.freqcount != readSize)
	{
		return FAIL_TO_READ_FILE;
	}
	if (shouldswap)
	{
		for (int i = 0 ; i < readSize ; i ++)
		{
			swap(&m_pdata[i],2);
		}
	}
	if (m_diluBand < m_head.freqstep)
	{
		return DILUTE_BAND_SMALLER;
	}
	unsigned __int32 step = m_diluBand / m_head.freqstep;
	for (int i = 0 ; i < readSize ; i += step)
	{
		freqDatas.push_back(m_pdata[i]);
	}
	return SUCCESS;
}



void CNGDataProcess::WriteToStandFile(const char* pfile)
{
	FILE* fp = fopen(pfile,"ab+");
	if (NULL == fp)
	{
		return;
	}
	m_head.freqcount = freqDatas.size();
	m_head.freqstep = m_diluBand;
	fwrite(&m_head,sizeof(BinHead),1,fp);
	for (int i = 0 ; i < freqDatas.size() ; i ++)
	{
		fwrite(&freqDatas[i],2,1,fp);
	}
	fclose(fp);
	freqDatas.clear();
}

int CNGDataProcess::StandDataDilute(const char* pSrcDir,unsigned __int32 freqBand,const char* pResultFile)
{
	if (NULL == pSrcDir || access(pSrcDir,0) != 0 )
	{
		return POINT_CAN_NOT_NULL;//文件不存在
	}
	vector<string> files = GetFilesByDir(pSrcDir);
	if(files.size() == 0 ){
		return NO_SOURCE_FILE;
	}
	m_diluBand = freqBand;
	m_pResultFile = pResultFile;
	for (int i = 0 ; i < files.size() ; i ++)
	{
		StandDataDilute(files[i].c_str());
	}
	return SUCCESS;
}

int CNGDataProcess::StandDataDilute(const char* pfile)
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
	//	ng_geo_init();
	while(feof(fp) == 0){
		bool shouldswap = false;
		fread(&m_head,1,sizeof(m_head),fp);
		if (m_head.checkcode != CheckCode)
		{
			swap(&m_head.checkcode,4);
			if (m_head.checkcode == CheckCode)
			{
				shouldswap = true;
			}else{
				fclose(fp);
				return FILE_FORM_WRONG;//文件格式错误
			}
		}
		if (shouldswap)
		{
			swap(&m_head.year,sizeof(m_head.year));
			swap(&m_head.lon,sizeof(m_head.lon));
			swap(&m_head.lat,sizeof(m_head.lat));
			swap(&m_head.startfreq,sizeof(m_head.startfreq));
			swap(&m_head.freqstep,sizeof(m_head.freqstep));
			swap(&m_head.freqcount,sizeof(m_head.freqcount));
		}
		//只在中国，经度>纬度,因为数据有问题
		double curlng = m_head.lon>m_head.lat?m_head.lon:m_head.lat;
		double curlat = m_head.lat<m_head.lon?m_head.lat:m_head.lon;
		m_head.lon = curlng;
		m_head.lat = curlat;
		if (m_head.lon < 10 || m_head.lat < 10)
		{
			int nRes = fseek(fp,2*m_head.freqcount , SEEK_CUR);
			if (nRes == 0 )
			{
				continue;
			}else{
				return FAIL_TO_READ_FILE;
			}
		}
		if (SUCCESS == ReadOneRecord(fp,shouldswap))
		{
			WriteToStandFile(m_pResultFile);
		}
		
	}
	fclose(fp);
	return SUCCESS;
}
