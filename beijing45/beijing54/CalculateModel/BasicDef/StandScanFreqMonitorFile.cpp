
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <io.h>
#include "NG_ErrorCode.h"
using namespace std;
#include "StandScanFreqMonitorFile.h"
#include "MacroDef.h"

#define StandV1CheckCode 0xABCDABCD
#define StandV2CheckCode 0xBCDABCDA


CStandScanFreqMonitorFile::CStandScanFreqMonitorFile( eScanFreqFormat format /*= eUnknown*/ )
{
	mFormat = format;
}

CStandScanFreqMonitorFile::~CStandScanFreqMonitorFile()
{
	Clear();
}

void CStandScanFreqMonitorFile::swap(void * data,int n)
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


int CStandScanFreqMonitorFile::ReadStandv1(const char *filename)
{
	if (NULL == filename || _access(filename,0)!=0 )
	{
		return NG_MONITORFILE_OPEN_ERROR;//文件不存在
	}
	if (fp==NULL||strcmp(filename, tempfilename) != 0) // 判断是否处理同一个文件，继续上次未完的读取
	{
		fp = fopen(filename, "rb");
		tempfilename = filename;
	}
	if (NULL == fp)
	{
		return NG_MONITORFILE_OPEN_ERROR;//打开文件失败
	} 

	Clear();

	unsigned __int64 maxfreq; //目前hz
	unsigned __int64 minfreq; //目前hz
	bool bfirst=true;
	int countRecord = 0;//开始新一轮的读取，计数器归0
	while(feof(fp) == 0&&countRecord<=40) //每次读取10000 条数据
	{
		countRecord++;
		bool shouldswap = false;
		StandBinHeadV1 head;
		fread(&head,1,sizeof(head),fp);
		if (head.checkcode != StandV1CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == StandV1CheckCode)
			{
				shouldswap = true;
			}
			else
			{
				fclose(fp);

				if(mDatas.size()==0)
				{
					return INVALIDSCANFORMAT;//文件格式错误,有可能不是国家格式
				}
				else
				{
					return STANDCHECKCODE_ERROR;//校验码错误
				}
			}
		}
		if (shouldswap)
		{   
			swap(&head.ant_type,sizeof(head.ant_type));
			swap(&head.equ_no,sizeof(head.equ_no));
			swap(&head.year,sizeof(head.year));
			swap(&head.mon,sizeof(head.mon));
			swap(&head.day,sizeof(head.day));
			swap(&head.hour,sizeof(head.hour));
			swap(&head.minute,sizeof(head.minute));
			swap(&head.second,sizeof(head.second));
			swap(&head.misecond,sizeof(head.misecond));
			swap(&head.lon,sizeof(head.lon));
			swap(&head.lat,sizeof(head.lat));
			swap(&head.height,sizeof(head.height));
			swap(&head.startfreq,sizeof(head.startfreq));
			swap(&head.freqstep,sizeof(head.freqstep));
			swap(&head.freqcount,sizeof(head.freqcount));
		}

		StandDataItem * item;
		bool check = true;
		CATCHNEW(item = new StandDataItem(head.freqcount),check);
		if(!check || ( item == NULL))
		{
			
			item = NULL;
			return READ_FILE_NEW_MERRORY_ERROR;
		}
		item->mHead=head;
		int readlen=fread(item->mVal, 2,head.freqcount,fp);
		if(readlen==0)
		{
			continue;
		}
		if(shouldswap)
		{   
			for(int i=0;i<head.freqcount;i++)
			{
				swap(&(item->mVal[i]), sizeof(short)); 
			}

		}
		if(bfirst)
		{
          minfreq=head.startfreq;
		  maxfreq=head.startfreq+(unsigned __int64)(head.freqcount-1)*(unsigned __int64)head.freqstep;
		  bfirst=false;
		}
		else
		{
            unsigned __int64 tmpmax=head.startfreq+(unsigned __int64)(head.freqcount-1)*(unsigned __int64)head.freqstep;
			minfreq=minfreq<head.startfreq?minfreq:head.startfreq;
			maxfreq=maxfreq>tmpmax?maxfreq:tmpmax;
		}
		mDatas.push_back(item);
	
	}
	
	printf("取得的记录为：%d\n",countRecord);
    if(mDatas.size()>0)
    {
       m_dFreqMhzMin=minfreq/1000000.0;
       m_dFreqMhzMax=maxfreq/1000000.0;
    }
	if (feof(fp) != 0)
	{
		fclose(fp);
		tempfilename = NULL;
		return NG_SUCCESS;
	}
	else 
	{
		return NEED_READ_AGAIN ;
	}
	
}



int CStandScanFreqMonitorFile::ReadFile(const char*strDataPath)
{
	if (mFormat == eUnknown)
	{
		int nRes = CheckIsStandFormat(strDataPath);
		if (nRes == NG_SUCCESS)
		{
			mFormat = eStandScanFreqV1;
		}
		else if (nRes == INVALIDSCANFORMAT)
		{
			nRes = CheckIsStandV3Format(strDataPath);
			if (nRes == NG_SUCCESS)
			{
				mFormat = eStandScanFreqV3;
			}
		}
	}
	if(mFormat==eStandScanFreqV1)
	{
		return ReadStandv1(strDataPath);
	}
	else if (mFormat == eStandScanFreqV3)
	{
		return ReadStandv3(strDataPath);
	}
	else
	{
		return INVALIDSCANFORMAT;
	}
}


void CStandScanFreqMonitorFile::Clear()
{
	for(int i=0;i<mDatas.size();i++)
	{
		if(mDatas[i]!=NULL)
		{
			delete mDatas[i];
		}
	}
	mDatas.clear();
}

int CStandScanFreqMonitorFile::ReadFileHead(const char*filename)
{
	if (mFormat == eUnknown)
	{
		int nRes = CheckIsStandFormat(filename);
		if (nRes == NG_SUCCESS)
		{
			mFormat = eStandScanFreqV1;
		}
		else if (nRes == INVALIDSCANFORMAT)
		{
			nRes = CheckIsStandV3Format(filename);
			if (nRes == NG_SUCCESS)
			{
				mFormat = eStandScanFreqV3;
			}
		}
	}
	if(mFormat==eStandScanFreqV1)
	{
		return ReadStandv1head(filename);
	}
	else if (mFormat == eStandScanFreqV3)
	{
		return ReadStandv3head(filename);
	}
	else
	{
		return INVALIDSCANFORMAT;
	}
}
#define Head2016ValueCheck(head) ((head.lon>-180&&head.lon<180)&&(head.lat>-180&&head.lat<180)&&(head.startfreq<1e10&&head.startfreq>0)&&(head.freqstep<1e9&&head.freqstep>0)&&(head.freqcount<1e6&&head.freqcount>0))
int CStandScanFreqMonitorFile::CheckIsStandFormat( const char *filename )
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
	Clear();
	unsigned __int64 maxfreq; //目前hz
	unsigned __int64 minfreq; //目前hz
	bool bfirst=true;
	//	ng_geo_init();
	while(feof(fp) == 0)
	{
		bool shouldswap = false;
		StandBinHeadV1 head;
		fread(&head,1,sizeof(head),fp);
		if (head.checkcode != StandV1CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == StandV1CheckCode)
			{
				shouldswap = true;
			}
			else
			{
				fclose(fp);
				return INVALIDSCANFORMAT;//文件格式错误,有可能不是国家格式
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
			return INVALIDSCANFORMAT;//文件格式错误,有可能不是国家格式
		}
		
		fclose(fp);
		return NG_SUCCESS;

	}

	fclose(fp);
	return NG_SUCCESS;
}

int CStandScanFreqMonitorFile::ReadStandv3( const char *filename )
{

	if (NULL == filename || access(filename,0)!=0 )
	{
		return NG_MONITORFILE_OPEN_ERROR;//文件不存在
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return NG_MONITORFILE_OPEN_ERROR;//打开文件失败
	} 

	Clear();


	unsigned __int64 maxfreq; //目前hz
	unsigned __int64 minfreq; //目前hz
	bool bfirst=true;
	StandBinHeadV1 tmphead;

	while(feof(fp) == 0)
	{
		bool shouldswap = false;
		StandBinHeadV3 head;
		if(fread(&head,sizeof(head),1,fp) != 1)
		{
			continue;
		}
		if (head.checkcode != StandV1CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == StandV1CheckCode)
			{
				shouldswap = true;
			}
			else
			{
				fclose(fp);

				if(mDatas.size()==0)
				{
					return INVALIDSCANFORMAT;//文件格式错误,有可能不是国家格式
				}
				else
				{
					return STANDCHECKCODE_ERROR;//校验码错误
				}
			}
		}
		if (shouldswap)
		{   
			swap(&head.ant_type,sizeof(head.ant_type));
			swap(&head.equ_no,sizeof(head.equ_no));
			swap(&head.year,sizeof(head.year));
			swap(&head.mon,sizeof(head.mon));
			swap(&head.day,sizeof(head.day));
			swap(&head.hour,sizeof(head.hour));
			swap(&head.minute,sizeof(head.minute));
			swap(&head.second,sizeof(head.second));
			swap(&head.misecond,sizeof(head.misecond));
			swap(&head.lon,sizeof(head.lon));
			swap(&head.lat,sizeof(head.lat));
			swap(&head.scanspeed,sizeof(head.scanspeed));
			swap(&head.height,sizeof(head.height));
			swap(&head.startfreq,sizeof(head.startfreq));
			swap(&head.freqstep,sizeof(head.freqstep));
			swap(&head.freqcount,sizeof(head.freqcount));
		}

		//赋值操作转换成员数据
		tmphead.year = head.year;
		tmphead.mon = head.mon;
		tmphead.day = head.day;
		tmphead.hour = head.hour;
		tmphead.minute = head.minute;
		tmphead.second = head.second;
		tmphead.height = head.height;
		tmphead.lon = head.lon*1e-8;
		tmphead.lat = head.lat*1e-8;
		tmphead.startfreq = (unsigned __int64)head.startfreq;
		tmphead.freqstep = (unsigned int)head.freqstep;
		tmphead.freqcount = head.freqcount;

		StandDataItem * item = NULL;
		bool check = true;
		CATCHNEW(item = new StandDataItem(tmphead.freqcount),check);
		if(!check || ( item == NULL))
		{
		
			item = NULL;
			return READ_FILE_NEW_MERRORY_ERROR;
		}
		item->mHead=tmphead;
		int readlen=fread(item->mVal, 2,tmphead.freqcount,fp);
		if(readlen!=tmphead.freqcount)
		{
			if(item != NULL)
			{
				delete item;
				item = NULL;
			}
			continue;
		}
		if(shouldswap)
		{   
			for(int i=0;i<tmphead.freqcount;i++)
			{
				swap(&(item->mVal[i]), sizeof(short)); 
			}

		}
		if(bfirst)
		{
			minfreq=tmphead.startfreq;
			maxfreq=tmphead.startfreq+(unsigned __int64)(tmphead.freqcount-1)*(unsigned __int64)tmphead.freqstep;
			bfirst=false;
		}
		else
		{
			unsigned __int64 tmpmax=tmphead.startfreq+(unsigned __int64)(tmphead.freqcount-1)*(unsigned __int64)tmphead.freqstep;
			minfreq=minfreq<tmphead.startfreq?minfreq:tmphead.startfreq;
			maxfreq=maxfreq>tmpmax?maxfreq:tmpmax;
		}
		mDatas.push_back(item);

	}
	if(mDatas.size()>0)
	{
		m_dFreqMhzMin=minfreq/1000000.0;
		m_dFreqMhzMax=maxfreq/1000000.0;
	}
	fclose(fp);
	return NG_SUCCESS;
}

int CStandScanFreqMonitorFile::ReadStandv1head( const char *filename )
{
	if (NULL == filename || access(filename,0)!=0 )
	{
		return NG_MONITORFILE_OPEN_ERROR;//文件不存在
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return NG_MONITORFILE_OPEN_ERROR;//打开文件失败
	} 
	Clear();
	unsigned __int64 maxfreq; //目前hz
	unsigned __int64 minfreq; //目前hz
	bool bfirst=true;
	//	ng_geo_init();
	while(feof(fp) == 0)
	{
		bool shouldswap = false;
		StandBinHeadV1 head;
		fread(&head,1,sizeof(head),fp);
		if (head.checkcode != StandV1CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == StandV1CheckCode)
			{
				shouldswap = true;
			}
			else
			{
				fclose(fp);
				if(mDatas.size()==0)
				{
					return INVALIDSCANFORMAT;//文件格式错误,有可能不是国家格式
				}
				else
				{
					return STANDCHECKCODE_ERROR;//校验码错误
				}
			}
		}
		if (shouldswap)
		{	
			swap(&head.ant_type,sizeof(head.ant_type));
			swap(&head.equ_no,sizeof(head.equ_no));
			swap(&head.year,sizeof(head.year));
			swap(&head.mon,sizeof(head.mon));
			swap(&head.day,sizeof(head.day));
			swap(&head.hour,sizeof(head.hour));
			swap(&head.minute,sizeof(head.minute));
			swap(&head.second,sizeof(head.second));
			swap(&head.misecond,sizeof(head.misecond));
			swap(&head.lon,sizeof(head.lon));
			swap(&head.lat,sizeof(head.lat));
			swap(&head.height,sizeof(head.height));
			swap(&head.startfreq,sizeof(head.startfreq));
			swap(&head.freqstep,sizeof(head.freqstep));
			swap(&head.freqcount,sizeof(head.freqcount));
		}
		//只在中国，经度>纬度,因为数据有问题
		double curlng = head.lon>head.lat?head.lon:head.lat;
		double curlat = head.lat<head.lon?head.lat:head.lon;
		head.lon = curlng;
		head.lat = curlat;
		if (head.lon < 10 || head.lat < 10) //丢弃该条记录
		{
			int nRes = fseek(fp,2*head.freqcount , SEEK_CUR);
			if (nRes == 0 )
			{
				continue;
			}else
			{
				return FAIL_TO_READ_FILE;
			}
		}
		StandDataItem * item=new StandDataItem(); //不需要数据内存
		item->mHead=head;
		int nRes = fseek(fp,2*head.freqcount , SEEK_CUR);
		if (nRes != 0 )
		{
			//return FAIL_TO_READ_FILE;
			break;
		}
		if(bfirst)
		{
			minfreq=head.startfreq;
			maxfreq=head.startfreq+((unsigned __int64)head.freqcount-1)*(unsigned __int64)head.freqstep;
			bfirst=false;
		}
		else
		{
			unsigned __int64 tmpmax=head.startfreq+((unsigned __int64)head.freqcount-1)*(unsigned __int64)head.freqstep;
			minfreq=minfreq<head.startfreq?minfreq:head.startfreq;
			maxfreq=maxfreq>tmpmax?maxfreq:tmpmax;
		}
		mDatas.push_back(item);
	}
	if(mDatas.size()>0)
	{
		m_dFreqMhzMin=minfreq/1000000.0;
		m_dFreqMhzMax=maxfreq/1000000.0;
	}
	fclose(fp);
	return NG_SUCCESS;
}

int CStandScanFreqMonitorFile::ReadStandv3head( const char *filename )
{
	if (NULL == filename || access(filename,0)!=0 )
	{
		return NG_MONITORFILE_OPEN_ERROR;//文件不存在
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return NG_MONITORFILE_OPEN_ERROR;//打开文件失败
	} 
	Clear();
	unsigned __int64 maxfreq; //目前hz
	unsigned __int64 minfreq; //目前hz
	bool bfirst=true;
	StandBinHeadV1 tmphead;

	while(feof(fp) == 0)
	{
		bool shouldswap = false;
		StandBinHeadV3 head;
		fread(&head,1,sizeof(head),fp);
		if (head.checkcode != StandV1CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == StandV1CheckCode)
			{
				shouldswap = true;
			}
			else
			{
				fclose(fp);
				if(mDatas.size()==0)
				{
					return INVALIDSCANFORMAT;//文件格式错误,有可能不是国家格式
				}
				else
				{
					return STANDCHECKCODE_ERROR;//校验码错误
				}
			}
		}
		if (shouldswap)
		{	
			swap(&head.ant_type,sizeof(head.ant_type));
			swap(&head.equ_no,sizeof(head.equ_no));
			swap(&head.year,sizeof(head.year));
			swap(&head.mon,sizeof(head.mon));
			swap(&head.day,sizeof(head.day));
			swap(&head.hour,sizeof(head.hour));
			swap(&head.minute,sizeof(head.minute));
			swap(&head.second,sizeof(head.second));
			swap(&head.misecond,sizeof(head.misecond));
			swap(&head.lon,sizeof(head.lon));
			swap(&head.lat,sizeof(head.lat));
			swap(&head.scanspeed,sizeof(head.scanspeed));
			swap(&head.height,sizeof(head.height));
			swap(&head.startfreq,sizeof(head.startfreq));
			swap(&head.freqstep,sizeof(head.freqstep));
			swap(&head.freqcount,sizeof(head.freqcount));
		}
		//赋值操作转换成员数据
		tmphead.checkcode = head.checkcode;
		tmphead.equ_no = head.equ_no;
		tmphead.ant_type = head.ant_type;
		tmphead.year = head.year;
		tmphead.mon = head.mon;
		tmphead.day = head.day;
		tmphead.hour = head.hour;
		tmphead.minute = head.minute;
		tmphead.second = head.second;
		tmphead.misecond = head.misecond;
		tmphead.height = head.height;
		tmphead.lon = head.lon*1e-8;
		tmphead.lat = head.lat*1e-8;
		tmphead.startfreq = (unsigned __int64)head.startfreq;
		tmphead.freqstep = (unsigned int)head.freqstep;
		tmphead.freqcount = head.freqcount;

		StandDataItem * item=new StandDataItem(); //不需要数据内存
		item->mHead=tmphead;
		int nRes = fseek(fp,2*tmphead.freqcount , SEEK_CUR);
		if (nRes != 0 )
		{
			//return FAIL_TO_READ_FILE;
			break;
		}
		if(bfirst)
		{
			minfreq=tmphead.startfreq;
			maxfreq=tmphead.startfreq+((unsigned __int64)tmphead.freqcount-1)*(unsigned __int64)tmphead.freqstep;
			bfirst=false;
		}
		else
		{
			unsigned __int64 tmpmax=tmphead.startfreq+((unsigned __int64)tmphead.freqcount-1)*(unsigned __int64)tmphead.freqstep;
			minfreq=minfreq<tmphead.startfreq?minfreq:tmphead.startfreq;
			maxfreq=maxfreq>tmpmax?maxfreq:tmpmax;
		}
		mDatas.push_back(item);
	}
	if(mDatas.size()>0)
	{
		m_dFreqMhzMin=minfreq/1000000.0;
		m_dFreqMhzMax=maxfreq/1000000.0;
	}
	fclose(fp);
	return NG_SUCCESS;
}

#define Head2017ValueCheck(head) ((head.lon>-1.8e10&&head.lon<1.8e10)&&(head.lat>-1.8e10&&head.lat<1.e10)&&(head.startfreq<1e10&&head.startfreq>0)&&(head.freqstep<1e9&&head.freqstep>0)&&(head.freqcount<1e6&&head.freqcount>0))
int CStandScanFreqMonitorFile::CheckIsStandV3Format( const char *filename )
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
	Clear();
	unsigned __int64 maxfreq; //目前hz
	unsigned __int64 minfreq; //目前hz
	bool bfirst=true;
	//	ng_geo_init();
	while(feof(fp) == 0)
	{
		bool shouldswap = false;
		StandBinHeadV3 head;
		fread(&head,1,sizeof(head),fp);
		if (head.checkcode != StandV1CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == StandV1CheckCode)
			{
				shouldswap = true;
			}
			else
			{
				fclose(fp);
				return INVALIDSCANFORMAT;//文件格式错误,有可能不是国家格式

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
			return INVALIDSCANFORMAT;//文件格式错误,有可能不是国家格式
		}

		fclose(fp);
		return NG_SUCCESS;

	}

	fclose(fp);
	return NG_SUCCESS;
}


CStandScanFreqMonitorFileV2::CStandScanFreqMonitorFileV2()
{
	mFormat=eStandScanFreqV2;
	mDatas.clear();
}

CStandScanFreqMonitorFileV2::~CStandScanFreqMonitorFileV2()
{
	Clear();
}

int CStandScanFreqMonitorFileV2::ReadFileHead( const char*filename )
{
	if (NULL == filename || access(filename,0)!=0 )
	{
		return NG_MONITORFILE_OPEN_ERROR;//文件不存在
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return NG_MONITORFILE_OPEN_ERROR;//打开文件失败
	} 
	Clear();
	unsigned __int64 maxfreq; //目前hz
	unsigned __int64 minfreq; //目前hz
	bool bfirst=true;
	//	ng_geo_init();
	while(feof(fp) == 0)
	{
		bool shouldswap = false;
		StandBinHeadV2 head;
		fread(&head,1,sizeof(head),fp);
		if (head.checkcode != StandV2CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == StandV2CheckCode)
			{
				shouldswap = true;
			}
			else
			{
				fclose(fp);
				return INVALIDSCANFORMAT;
			}
		}
		if (shouldswap)
		{	
			swap(&head.ant_type,sizeof(head.ant_type));
			swap(&head.equ_no,sizeof(head.equ_no));
			swap(&head.year,sizeof(head.year));
			swap(&head.mon,sizeof(head.mon));
			swap(&head.day,sizeof(head.day));
			swap(&head.hour,sizeof(head.hour));
			swap(&head.minute,sizeof(head.minute));
			swap(&head.second,sizeof(head.second));
			swap(&head.misecond,sizeof(head.misecond));
			swap(&head.lon,sizeof(head.lon));
			swap(&head.lat,sizeof(head.lat));
			swap(&head.waveAngle,sizeof(head.waveAngle));
			swap(&head.height,sizeof(head.height));
			swap(&head.startfreq,sizeof(head.startfreq));
			swap(&head.freqstep,sizeof(head.freqstep));
			swap(&head.freqcount,sizeof(head.freqcount));
		}
		//只在中国，经度>纬度,因为数据有问题
		double curlng = head.lon>head.lat?head.lon:head.lat;
		double curlat = head.lat<head.lon?head.lat:head.lon;
		head.lon = curlng;
		head.lat = curlat;
		if (head.lon < 10 || head.lat < 10) //丢弃该条记录
		{
			int nRes = fseek(fp,2*head.freqcount , SEEK_CUR);
			if (nRes == 0 )
			{
				continue;
			}else
			{
				return FAIL_TO_READ_FILE;
			}
		}
		StandDataItemV2 * item=new StandDataItemV2(); //不需要数据内存
		item->mHead=head;
		int nRes = fseek(fp,2*head.freqcount , SEEK_CUR);
		if (nRes != 0 )
		{
			//return FAIL_TO_READ_FILE;
			break;
		}
		if(bfirst)
		{
			minfreq=head.startfreq;
			maxfreq=head.startfreq+((unsigned __int64)head.freqcount-1)*(unsigned __int64)head.freqstep;
			bfirst=false;
		}
		else
		{
			unsigned __int64 tmpmax=head.startfreq+((unsigned __int64)head.freqcount-1)*(unsigned __int64)head.freqstep;
			minfreq=minfreq<head.startfreq?minfreq:head.startfreq;
			maxfreq=maxfreq>tmpmax?maxfreq:tmpmax;
		}
		mDatas.push_back(item);
	}
	if(mDatas.size()>0)
	{
		m_dFreqMhzMin=minfreq/1000000.0;
		m_dFreqMhzMax=maxfreq/1000000.0;
	}
	fclose(fp);
	return NG_SUCCESS;
}

int CStandScanFreqMonitorFileV2::ReadFile( const char *filename )
{
	if(mFormat==eStandScanFreqV2)
	{
		return ReadStandV2(filename);
	}
	else
	{
		return INVALIDSCANFORMAT;
	}
}

int CStandScanFreqMonitorFileV2::ReadStandV2( const char *filename )
{
	if (NULL == filename || access(filename,0)!=0 )
	{
		return NG_MONITORFILE_OPEN_ERROR;//文件不存在
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return NG_MONITORFILE_OPEN_ERROR;//打开文件失败
	} 

	Clear();

	unsigned __int64 maxfreq; //目前hz
	unsigned __int64 minfreq; //目前hz
	bool bfirst=true;

	//	ng_geo_init();
	while(feof(fp) == 0)
	{
		bool shouldswap = false;
		StandBinHeadV2 head;
		fread(&head,1,sizeof(head),fp);
		if (head.checkcode != StandV2CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == StandV2CheckCode)
			{
				shouldswap = true;
			}
			else
			{
				fclose(fp);
				return INVALIDSCANFORMAT;
			}
		}
		if (shouldswap)
		{   
			swap(&head.ant_type,sizeof(head.ant_type));
			swap(&head.equ_no,sizeof(head.equ_no));
			swap(&head.year,sizeof(head.year));
			swap(&head.mon,sizeof(head.mon));
			swap(&head.day,sizeof(head.day));
			swap(&head.hour,sizeof(head.hour));
			swap(&head.minute,sizeof(head.minute));
			swap(&head.second,sizeof(head.second));
			swap(&head.misecond,sizeof(head.misecond));
			swap(&head.lon,sizeof(head.lon));
			swap(&head.lat,sizeof(head.lat));
			swap(&head.waveAngle,sizeof(head.waveAngle));
			swap(&head.height,sizeof(head.height));
			swap(&head.startfreq,sizeof(head.startfreq));
			swap(&head.freqstep,sizeof(head.freqstep));
			swap(&head.freqcount,sizeof(head.freqcount));
		}
		//只在中国，经度>纬度,因为数据有问题
		double curlng = head.lon>head.lat?head.lon:head.lat;
		double curlat = head.lat<head.lon?head.lat:head.lon;
		head.lon = curlng;
		head.lat = curlat;
		//if (head.lon < 10 || head.lat < 10) //丢弃该条记录
		//{
		//	int nRes = fseek(fp,2*head.freqcount , SEEK_CUR);
		//	if (nRes == 0 )
		//	{
		//		continue;
		//	}else
		//	{
		//		return FAIL_TO_READ_FILE;
		//	}
		//}

		StandDataItemV2 * item; 
		bool check = true;
		CATCHNEW(item=new StandDataItemV2(head.freqcount),check);
		if(!check || ( item == NULL))
		{
		
			item = NULL;
			return READ_FILE_NEW_MERRORY_ERROR;
		}
		item->mHead=head;
		int readlen=fread(item->mVal, 2,head.freqcount,fp);
		if(readlen==0)
		{
			continue;
		}
		if(shouldswap)
		{   
			for(int i=0;i<head.freqcount;i++)
			{
				swap(&(item->mVal[i]), sizeof(short)); 
			}

		}
		if(bfirst)
		{
			minfreq=head.startfreq;
			maxfreq=head.startfreq+(unsigned __int64)(head.freqcount-1)*(unsigned __int64)head.freqstep;
			bfirst=false;
		}
		else
		{
			unsigned __int64 tmpmax=head.startfreq+(unsigned __int64)(head.freqcount-1)*(unsigned __int64)head.freqstep;
			minfreq=minfreq<head.startfreq?minfreq:head.startfreq;
			maxfreq=maxfreq>tmpmax?maxfreq:tmpmax;
		}
		mDatas.push_back(item);

	}
	if(mDatas.size()>0)
	{
		m_dFreqMhzMin=minfreq/1000000.0;
		m_dFreqMhzMax=maxfreq/1000000.0;
	}
	fclose(fp);
	return NG_SUCCESS;
}

void CStandScanFreqMonitorFileV2::Clear()
{
	for(int i=0;i<mDatas.size();i++)
	{
		if(mDatas[i]!=NULL)
		{
			delete mDatas[i];
		}
	}
	mDatas.clear();
}

void CStandScanFreqMonitorFileV2::swap( void * data,int n )
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

#define Head2016DirectionValueCheck(head) ((head.lon>-180&&head.lon<180)&&(head.lat>-180&&head.lat<180)&&(head.startfreq<1e10&&head.startfreq>0)&&(head.freqstep<1e9&&head.freqstep>0)&&(head.freqcount<1e6&&head.freqcount>0))
int CStandScanFreqMonitorFileV2::CheckIsStandV2Format( const char *filename )
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
	Clear();
	unsigned __int64 maxfreq; //目前hz
	unsigned __int64 minfreq; //目前hz
	bool bfirst=true;
	//	ng_geo_init();
	while(feof(fp) == 0)
	{
		bool shouldswap = false;
		StandBinHeadV2 head;
		fread(&head,1,sizeof(head),fp);
		if (head.checkcode != StandV2CheckCode)
		{
			swap(&head.checkcode,4);
			if (head.checkcode == StandV2CheckCode)
			{
				shouldswap = true;
			}
			else
			{
				fclose(fp);
				return INVALIDSCANFORMAT;//文件格式错误,有可能不是国家格式

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

		if(!Head2016DirectionValueCheck(head))
		{
			fclose(fp);
			return INVALIDSCANFORMAT;//文件格式错误,有可能不是国家格式
		}

		fclose(fp);
		return NG_SUCCESS;

	}

	fclose(fp);
	return NG_SUCCESS;
}



