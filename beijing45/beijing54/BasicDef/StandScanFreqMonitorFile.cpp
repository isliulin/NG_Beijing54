

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <io.h>
#include "NG_ErrorCode.h"
using namespace std;
#include "StandScanFreqMonitorFile.h"

#define StandV1CheckCode 0xABCDABCD

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


int CStandScanFreqMonitorFile::ReadStandV1(const char *filename)
{
	if (NULL == filename || access(filename,0)!=0 )
	{
		return NG_MONITORFILE_OPEN_ERROR;//�ļ�������
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return NG_MONITORFILE_OPEN_ERROR;//���ļ�ʧ��
	} 

	Clear();


   unsigned __int64 maxfreq; //Ŀǰhz
   unsigned __int64 minfreq; //Ŀǰhz
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
				  return INVALIDSCANFORMAT;//�ļ���ʽ����,�п��ܲ��ǹ��Ҹ�ʽ
				}
				else
				{
                   return STANDCHECKCODE_ERROR;//У�������
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
		//ֻ���й�������>γ��,��Ϊ����������
		double curlng = head.lon>head.lat?head.lon:head.lat;
		double curlat = head.lat<head.lon?head.lat:head.lon;
		head.lon = curlng;
		head.lat = curlat;
		if (head.lon < 10 || head.lat < 10) //����������¼
		{
			int nRes = fseek(fp,2*head.freqcount , SEEK_CUR);
			if (nRes == 0 )
			{
				continue;
			}else
			{
				fclose(fp);
				return FAIL_TO_READ_FILE;
			}
		}

		StandDataItem * item=new StandDataItem(head.freqcount);
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



int CStandScanFreqMonitorFile::ReadFile(const char*strDataPath)
{
 if(mFormat==eStandScanFreqV1)
	{
      return ReadStandV1(strDataPath);
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
	if (NULL == filename || access(filename,0)!=0 )
	{
		return NG_MONITORFILE_OPEN_ERROR;//�ļ�������
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return NG_MONITORFILE_OPEN_ERROR;//���ļ�ʧ��
	} 
	Clear();
	unsigned __int64 maxfreq; //Ŀǰhz
	unsigned __int64 minfreq; //Ŀǰhz
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
				  return INVALIDSCANFORMAT;//�ļ���ʽ����,�п��ܲ��ǹ��Ҹ�ʽ
				}
				else
				{
                   return STANDCHECKCODE_ERROR;//У�������
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
		//ֻ���й�������>γ��,��Ϊ����������
		double curlng = head.lon>head.lat?head.lon:head.lat;
		double curlat = head.lat<head.lon?head.lat:head.lon;
		head.lon = curlng;
		head.lat = curlat;
		if (head.lon < 10 || head.lat < 10) //����������¼
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
		StandDataItem * item=new StandDataItem(); //����Ҫ�����ڴ�
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

int CStandScanFreqMonitorFile::CheckIsStandFormat(const char *filename)
{
	if (NULL == filename || access(filename,0)!=0 )
	{
		return THE_FILE_IS_NOT_EXIST;//�ļ�������
	}
	FILE* fp = fopen(filename,"rb");
	if (NULL == fp)
	{
		return FAIL_TO_OPEN_FILE;//���ļ�ʧ��
	} 
	Clear();
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
				return INVALIDSCANFORMAT;//�ļ���ʽ����,�п��ܲ��ǹ��Ҹ�ʽ
			
			}
		}

        fclose(fp);
	    return NG_SUCCESS;
	
	}
	
	fclose(fp);
	return NG_SUCCESS;
}



