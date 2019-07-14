
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <io.h>
#include "NG_ErrorCode.h"
#include "Macrodef.h"
using namespace std;
#include "ScanFreqMonitorFile.h"



#define StandV1CheckCode 0xABCDABCD



ValueInTime::ValueInTime()
{
	pdLevelValue = NULL;
	nValueNumber = 0;
	//lon=0;
	//lat=0;
	//height=0;
}
ValueInTime::ValueInTime(long nValueNumber)
{
	nValueNumber = nValueNumber;
    pdLevelValue=NULL;
	if(nValueNumber>0)
	{
		pdLevelValue = new float[nValueNumber];
	    memset(pdLevelValue, 0, sizeof(float)*nValueNumber);
	}
	//lon=0;
	//lat=0;
	//height=0;
}
//copy构造函数
ValueInTime::ValueInTime(const ValueInTime& scmValueInTime)
{
	this->nValueNumber = scmValueInTime.nValueNumber;
	this->tTime.wYear= scmValueInTime.tTime.wYear;
	this->tTime.wMonth=scmValueInTime.tTime.wMonth;
	this->tTime.wDay=scmValueInTime.tTime.wDay;
	this->tTime.wHour=scmValueInTime.tTime.wHour;
	this->tTime.wMinute=scmValueInTime.tTime.wMinute;
	this->tTime.wSecond=scmValueInTime.tTime.wSecond;
	this->tTime.wMilliseconds=scmValueInTime.tTime.wMilliseconds;
    this->pdLevelValue = NULL;
	if(scmValueInTime.nValueNumber>0&&scmValueInTime.pdLevelValue!=NULL)
	{
		 this->pdLevelValue=new float[this->nValueNumber];
		 memcpy(this->pdLevelValue, scmValueInTime.pdLevelValue, sizeof(float)*this->nValueNumber);
	}
	else
	{
        this->nValueNumber=0;
	}
	//this->lon=scmValueInTime.lon;
//	this->lat=scmValueInTime.lat;
	//this->height=scmValueInTime.height;
	
}

//赋值函数
ValueInTime& ValueInTime::operator=(const ValueInTime& scmValueInTime)
{	
	
	if(pdLevelValue!=NULL)
	delete []pdLevelValue;
	pdLevelValue = NULL;
	
	nValueNumber = scmValueInTime.nValueNumber;
	tTime.wYear= scmValueInTime.tTime.wYear;
	tTime.wMonth=scmValueInTime.tTime.wMonth;
	tTime.wDay=scmValueInTime.tTime.wDay;
	tTime.wHour=scmValueInTime.tTime.wHour;
	tTime.wMinute=scmValueInTime.tTime.wMinute;
	tTime.wSecond=scmValueInTime.tTime.wSecond;
	tTime.wMilliseconds=scmValueInTime.tTime.wMilliseconds;

	if(nValueNumber > 0&&scmValueInTime.pdLevelValue!=NULL)
	{
	
		pdLevelValue = new float[scmValueInTime.nValueNumber];
		memcpy(pdLevelValue, scmValueInTime.pdLevelValue, sizeof(float)*scmValueInTime.nValueNumber);
	}
	else
	{
       nValueNumber=0;
	}
	//lon=scmValueInTime.lon;
	//lat=scmValueInTime.lat;
	//height=scmValueInTime.height;

	return (*this);
}
ValueInTime::~ValueInTime()
{
	
	if(pdLevelValue!=NULL)
	delete []pdLevelValue;
	pdLevelValue = NULL;
	nValueNumber=0;
	
}

CScanFreqMonitorFile::CScanFreqMonitorFile(/*eScanFreqFormat FormatType*/)
{
	m_nTotalFreqCount = 0;
	m_dFreqMhzdf=0;
	m_dFreqMhzMin=0;
	m_dFreqMhzMax=0;
	m_nTotalRecordCount=0;
	m_pValueInTime  =  NULL;

	m_pFrequencyMHz=NULL;
	m_ScanTimeMs=0;
	//mlon=0;
	//mlat=0;
	//height=0;
	//mFormat=FormatType;

    
	mFormat=eNGScanFreqV1;
	
}

CScanFreqMonitorFile::~CScanFreqMonitorFile()
{
  Clear();
}


bool CScanFreqMonitorFile::IsLittleEndian()
{
	static unsigned short sV = 0x0001;
	return (*((char*)&sV)>0);
}

void CScanFreqMonitorFile::SwapData(void * data,int n)
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


int CScanFreqMonitorFile:: ReadNGV1(const char *filename)
{
	if(filename==NULL||access(filename,0)!=0)
	{
	  return THE_FILE_IS_NOT_EXIST;
	}
	Clear();

	std::ifstream fin(filename, std::ios::binary|std::ios::in);
	if(!fin.is_open())
	{
		return FAIL_TO_OPEN_FILE;
	}

	bool bIsGE = !IsLittleEndian();

	//头信息
	fin.read((char*)&m_dFreqMhzMin, sizeof(m_dFreqMhzMin));
	fin.read((char*)&m_dFreqMhzdf, sizeof(m_dFreqMhzdf));
	fin.read((char*)&m_nTotalFreqCount, sizeof(m_nTotalFreqCount));
	fin.read((char*)&m_nTotalRecordCount,sizeof(m_nTotalRecordCount));
	fin.read((char*)&m_DataType, sizeof(m_DataType));
	fin.read((char*)&m_ScanTimeMs, sizeof(m_ScanTimeMs));

	fin.read((char*)&mfromtime.wYear, sizeof(short));
	fin.read((char*)&mfromtime.wMonth, sizeof(short));
	fin.read((char*)&mfromtime.wDay, sizeof(short));
	fin.read((char*)&mfromtime.wHour, sizeof(short));
	fin.read((char*)&mfromtime.wMinute, sizeof(short));
	fin.read((char*)&mfromtime.wSecond, sizeof(short));
	fin.read((char*)&mfromtime.wMilliseconds, sizeof(short));

	fin.read((char*)&mendtime.wYear, sizeof(short));
	fin.read((char*)&mendtime.wMonth, sizeof(short));
	fin.read((char*)&mendtime.wDay, sizeof(short));
	fin.read((char*)&mendtime.wHour, sizeof(short));
	fin.read((char*)&mendtime.wMinute, sizeof(short));
	fin.read((char*)&mendtime.wSecond, sizeof(short));
	fin.read((char*)&mendtime.wMilliseconds, sizeof(short));


	fin.read(mStationID, 50);

	if (bIsGE)
	{

		SwapData(&m_dFreqMhzMin, sizeof(m_dFreqMhzMin));
		SwapData(&m_dFreqMhzdf, sizeof(m_dFreqMhzdf));
		SwapData(&m_nTotalFreqCount, sizeof(m_nTotalFreqCount));
		SwapData(&m_nTotalRecordCount, sizeof(m_nTotalRecordCount));
		SwapData(&m_ScanTimeMs, sizeof(m_ScanTimeMs));
		
		SwapData(&mfromtime.wYear, sizeof(mfromtime.wYear));
		SwapData(&mfromtime.wMonth, sizeof(mfromtime.wMonth));
		SwapData(&mfromtime.wDay, sizeof(mfromtime.wDay));
		SwapData(&mfromtime.wHour, sizeof(mfromtime.wHour));
		SwapData(&mfromtime.wMinute, sizeof(mfromtime.wMinute));
		SwapData(&mfromtime.wSecond, sizeof(mfromtime.wSecond));
		SwapData(&mfromtime.wMilliseconds, sizeof(mfromtime.wMilliseconds));


		SwapData(&mendtime.wYear, sizeof(mendtime.wYear));
		SwapData(&mendtime.wMonth, sizeof(mendtime.wMonth));
		SwapData(&mendtime.wDay, sizeof(mendtime.wDay));
		SwapData(&mendtime.wHour, sizeof(mendtime.wHour));
		SwapData(&mendtime.wMinute, sizeof(mendtime.wMinute));
		SwapData(&mendtime.wSecond, sizeof(mendtime.wSecond));
		SwapData(&mendtime.wMilliseconds, sizeof(mendtime.wMilliseconds));

	}

		
	//数据
	m_pValueInTime=new ValueInTime[m_nTotalRecordCount];
	unsigned int currentcount=0;

	while(fin.peek() != EOF&&currentcount<m_nTotalRecordCount)
	{

		//ValueInTime *pdataItem=new ValueInTime(m_nTotalFreqCount) ;
		ValueInTime *pdataItem=&m_pValueInTime[currentcount] ;
		pdataItem->pdLevelValue=new float[m_nTotalFreqCount];
		pdataItem->nValueNumber = m_nTotalFreqCount;
		fin.read((char*)&pdataItem->tTime.wYear, sizeof(short));
		fin.read((char*)&pdataItem->tTime.wMonth, sizeof(short));
		fin.read((char*)&pdataItem->tTime.wDay, sizeof(short));
		fin.read((char*)&pdataItem->tTime.wHour, sizeof(short));
		fin.read((char*)&pdataItem->tTime.wMinute, sizeof(short));
		fin.read((char*)&pdataItem->tTime.wSecond, sizeof(short));
		fin.read((char*)&pdataItem->tTime.wMilliseconds, sizeof(short));
		fin.read((char*)pdataItem->pdLevelValue, m_nTotalFreqCount*sizeof(float));

		if(bIsGE)
		{

			SwapData(&pdataItem->tTime.wYear, sizeof(pdataItem->tTime.wYear));
			SwapData(&pdataItem->tTime.wMonth, sizeof(pdataItem->tTime.wMonth));
			SwapData(&pdataItem->tTime.wDay, sizeof(pdataItem->tTime.wDay));
			SwapData(&pdataItem->tTime.wHour, sizeof(pdataItem->tTime.wHour));
			SwapData(&pdataItem->tTime.wMinute, sizeof(pdataItem->tTime.wMinute));
			SwapData(&pdataItem->tTime.wSecond, sizeof(pdataItem->tTime.wSecond));
			SwapData(&pdataItem->tTime.wMilliseconds, sizeof(pdataItem->tTime.wMilliseconds));

			for(int i=0;i<m_nTotalFreqCount;i++)
			{
				SwapData(&(pdataItem->pdLevelValue[i]), sizeof(float));  

                			
#ifdef MONITORFORMAT_TO_DBM
	            if(m_DataType==2) //场强->功率
	            {
	                 double freqtmp=m_dFreqMhzMin+m_dFreqMhzdf*i;
	                 float valdbm=pdataItem->pdLevelValue[i]-20*log10(freqtmp)-77.216;
                     pdataItem->pdLevelValue[i]=valdbm;
				  
	            }
				else if(m_DataType==1)//电平->功率
				{
                     pdataItem->pdLevelValue[i]= pdataItem->pdLevelValue[i]-107;
				}
#endif
				

			}



 

		}


		currentcount++;

	}

	m_nTotalRecordCount=currentcount;

	if(m_pFrequencyMHz) delete []m_pFrequencyMHz;
	m_pFrequencyMHz=new double[m_nTotalFreqCount];
	for(int i=0;i<m_nTotalFreqCount;i++)
	{
		m_pFrequencyMHz[i]=m_dFreqMhzMin+i*m_dFreqMhzdf;
	}

	
	m_dFreqMhzMax=m_dFreqMhzMin+(m_nTotalFreqCount-1)*m_dFreqMhzdf;

#ifdef MONITORFORMAT_TO_DBM
   m_DataType=0;
#endif

	return NG_SUCCESS;
}


int CScanFreqMonitorFile::ReadStandV1(const char *filename)
{
	CStandScanFreqMonitorFile standfile;
	int ErrCode=standfile.ReadFile(filename);
	if(ErrCode!=NG_SUCCESS)
	{
		return ErrCode;
	}
	if(standfile.mDatas.size()==0)
	{
		return TOO_FEW_DATARECORD;
	}
	Clear();
	m_DataType=2;
	m_ScanTimeMs=1000;//先默认

	m_nTotalRecordCount=standfile.mDatas.size();
	m_dFreqMhzMin=standfile.m_dFreqMhzMin;
	m_dFreqMhzMax=standfile.m_dFreqMhzMax;
	m_dFreqMhzdf=standfile.mDatas[0]->mHead.freqstep/1000000.0;
    m_nTotalFreqCount=(standfile.m_dFreqMhzMax-standfile.m_dFreqMhzMin)/m_dFreqMhzdf+1;

	mfromtime.wYear=standfile.mDatas[0]->mHead.year;
	mfromtime.wMonth=standfile.mDatas[0]->mHead.mon;
	mfromtime.wDay=standfile.mDatas[0]->mHead.day;
	mfromtime.wHour=standfile.mDatas[0]->mHead.hour;
	mfromtime.wMinute=standfile.mDatas[0]->mHead.minute;
	mfromtime.wSecond=standfile.mDatas[0]->mHead.second;
	mfromtime.wMilliseconds=standfile.mDatas[0]->mHead.misecond;

	mendtime.wYear=standfile.mDatas[standfile.mDatas.size()-1]->mHead.year;
	mendtime.wMonth=standfile.mDatas[standfile.mDatas.size()-1]->mHead.mon;
	mendtime.wDay=standfile.mDatas[standfile.mDatas.size()-1]->mHead.day;
	mendtime.wHour=standfile.mDatas[standfile.mDatas.size()-1]->mHead.hour;
	mendtime.wMinute=standfile.mDatas[standfile.mDatas.size()-1]->mHead.minute;
	mendtime.wSecond=standfile.mDatas[standfile.mDatas.size()-1]->mHead.second;
	mendtime.wMilliseconds=standfile.mDatas[standfile.mDatas.size()-1]->mHead.misecond;

	if(m_pFrequencyMHz) delete []m_pFrequencyMHz;
	m_pFrequencyMHz=new double[m_nTotalFreqCount];
	for(int i=0;i<m_nTotalFreqCount;i++)
	{
		m_pFrequencyMHz[i]=m_dFreqMhzMin+i*m_dFreqMhzdf;
	}

	char tmpbuffer[200]={0};
	itoa(standfile.mDatas[0]->mHead.equ_no,tmpbuffer,10);
	sprintf(mStationID,"%s",tmpbuffer);

	m_pValueInTime=new ValueInTime[m_nTotalRecordCount];
	for(int i=0;i<m_nTotalRecordCount;i++)
	{
		int freqindex=0;

		StandDataItem* item=standfile.mDatas[i];
		m_pValueInTime[i].pdLevelValue=new float[m_nTotalFreqCount];
		m_pValueInTime[i].nValueNumber = m_nTotalFreqCount;
		m_pValueInTime[i].tTime.wYear=item->mHead.year;
		m_pValueInTime[i].tTime.wMonth=item->mHead.mon;
		m_pValueInTime[i].tTime.wDay=item->mHead.day;
		m_pValueInTime[i].tTime.wHour=item->mHead.hour;
		m_pValueInTime[i].tTime.wMinute=item->mHead.minute;
		m_pValueInTime[i].tTime.wSecond=item->mHead.second;
		m_pValueInTime[i].tTime.wMilliseconds=item->mHead.misecond;

		freqindex=(item->mHead.startfreq/1000000.0-m_dFreqMhzMin)/m_dFreqMhzdf;
		if(freqindex<0||(freqindex+item->mHead.freqcount-1)>=m_nTotalFreqCount)
		{
			continue ;
		}
		//有效值
		for(int index=0;index<item->mHead.freqcount;index++)
		{
			m_pValueInTime[i].pdLevelValue[freqindex+index]=item->mVal[index]/10.0;

#ifdef MONITORFORMAT_TO_DBM
		
		   double freqtmp=m_dFreqMhzMin+m_dFreqMhzdf*(freqindex+index);
		   float valdbm=m_pValueInTime[i].pdLevelValue[freqindex+index]-20*log10(freqtmp)-77.216;
		   m_pValueInTime[i].pdLevelValue[freqindex+index]=valdbm;
#endif

		}
		//无效值
		for(int index=0;index<freqindex;index++)
		{
			m_pValueInTime[i].pdLevelValue[index]=0x8181;
		}
		//无效值
		for(int index=freqindex+item->mHead.freqcount;index<m_nTotalFreqCount;index++)
		{
			m_pValueInTime[i].pdLevelValue[index]=0x8181;
		}
	}

#ifdef MONITORFORMAT_TO_DBM
		m_DataType=0;
#endif
	
	return NG_SUCCESS;
}



int CScanFreqMonitorFile::ReadFile(const char*strDataPath)
{

//因为国家格式有校验码，所以先看是否国家格式正确
   int ErrCode=ReadStandV1(strDataPath);
  if(INVALIDSCANFORMAT==ErrCode)
  	{
      ErrCode=ReadNGV1(strDataPath);
  	}

	return ErrCode;

}


void CScanFreqMonitorFile::Clear()
{
	if (m_pValueInTime != NULL)
	{
		delete []m_pValueInTime;
		m_pValueInTime = NULL;
	}
	if(m_pFrequencyMHz!=NULL)
	{
		delete []m_pFrequencyMHz;
		m_pFrequencyMHz=NULL;
	}
	m_nTotalFreqCount=0;
	m_nTotalRecordCount=0;
	m_dFreqMhzdf=0;
	m_dFreqMhzMin=0;
	m_dFreqMhzMax=0;
	m_DataType=0;
	memset(mStationID,0,51);
	m_ScanTimeMs=0;
}

int CScanFreqMonitorFile::ReadNGV1Head(const char *filename)
{
	if(filename==NULL||access(filename,0)!=0)
	{
		return THE_FILE_IS_NOT_EXIST;
	}
	Clear();

	std::ifstream fin(filename, std::ios::binary|std::ios::in);
	if(!fin.is_open())
	{
		return FAIL_TO_OPEN_FILE;
	}
	bool bIsGE = !IsLittleEndian();

	//头信息
	fin.read((char*)&m_dFreqMhzMin, sizeof(m_dFreqMhzMin));
	fin.read((char*)&m_dFreqMhzdf, sizeof(m_dFreqMhzdf));
	fin.read((char*)&m_nTotalFreqCount, sizeof(m_nTotalFreqCount));
	fin.read((char*)&m_nTotalRecordCount,sizeof(m_nTotalRecordCount));
	fin.read((char*)&m_DataType, sizeof(m_DataType));
	fin.read((char*)&m_ScanTimeMs, sizeof(m_ScanTimeMs));

	fin.read((char*)&mfromtime.wYear, sizeof(short));
	fin.read((char*)&mfromtime.wMonth, sizeof(short));
	fin.read((char*)&mfromtime.wDay, sizeof(short));
	fin.read((char*)&mfromtime.wHour, sizeof(short));
	fin.read((char*)&mfromtime.wMinute, sizeof(short));
	fin.read((char*)&mfromtime.wSecond, sizeof(short));
	fin.read((char*)&mfromtime.wMilliseconds, sizeof(short));

	fin.read((char*)&mendtime.wYear, sizeof(short));
	fin.read((char*)&mendtime.wMonth, sizeof(short));
	fin.read((char*)&mendtime.wDay, sizeof(short));
	fin.read((char*)&mendtime.wHour, sizeof(short));
	fin.read((char*)&mendtime.wMinute, sizeof(short));
	fin.read((char*)&mendtime.wSecond, sizeof(short));
	fin.read((char*)&mendtime.wMilliseconds, sizeof(short));


	fin.read(mStationID, 50);

	if (bIsGE)
	{

		SwapData(&m_dFreqMhzMin, sizeof(m_dFreqMhzMin));
		SwapData(&m_dFreqMhzdf, sizeof(m_dFreqMhzdf));
		SwapData(&m_nTotalFreqCount, sizeof(m_nTotalFreqCount));
		SwapData(&m_nTotalRecordCount, sizeof(m_nTotalRecordCount));
		SwapData(&m_ScanTimeMs, sizeof(m_ScanTimeMs));

		SwapData(&mfromtime.wYear, sizeof(mfromtime.wYear));
		SwapData(&mfromtime.wMonth, sizeof(mfromtime.wMonth));
		SwapData(&mfromtime.wDay, sizeof(mfromtime.wDay));
		SwapData(&mfromtime.wHour, sizeof(mfromtime.wHour));
		SwapData(&mfromtime.wMinute, sizeof(mfromtime.wMinute));
		SwapData(&mfromtime.wSecond, sizeof(mfromtime.wSecond));
		SwapData(&mfromtime.wMilliseconds, sizeof(mfromtime.wMilliseconds));


		SwapData(&mendtime.wYear, sizeof(mendtime.wYear));
		SwapData(&mendtime.wMonth, sizeof(mendtime.wMonth));
		SwapData(&mendtime.wDay, sizeof(mendtime.wDay));
		SwapData(&mendtime.wHour, sizeof(mendtime.wHour));
		SwapData(&mendtime.wMinute, sizeof(mendtime.wMinute));
		SwapData(&mendtime.wSecond, sizeof(mendtime.wSecond));
		SwapData(&mendtime.wMilliseconds, sizeof(mendtime.wMilliseconds));

	}

	
	m_dFreqMhzMax=m_dFreqMhzMin+(m_nTotalFreqCount-1)*m_dFreqMhzdf;

#ifdef MONITORFORMAT_TO_DBM
	m_DataType=0;
#endif


	return NG_SUCCESS;
}

int CScanFreqMonitorFile::ReadStandV1Head(const char *filename)
{
	CStandScanFreqMonitorFile standfile;
	int ErrCode=standfile.ReadFileHead(filename);
	if(ErrCode!=NG_SUCCESS)
	{
	  return ErrCode;
	}
	if(standfile.mDatas.size()==0)
	{
	  return TOO_FEW_DATARECORD;
	}
	Clear();
	m_DataType=2;
	m_ScanTimeMs=1000;//先默认

	m_nTotalRecordCount=standfile.mDatas.size();
	m_dFreqMhzMin=standfile.m_dFreqMhzMin;
	m_dFreqMhzMax=standfile.m_dFreqMhzMax;
	m_dFreqMhzdf=standfile.mDatas[0]->mHead.freqstep/1000000.0;
	m_nTotalFreqCount=(standfile.m_dFreqMhzMax-standfile.m_dFreqMhzMin)/m_dFreqMhzdf+1;

	mfromtime.wYear=standfile.mDatas[0]->mHead.year;
	mfromtime.wMonth=standfile.mDatas[0]->mHead.mon;
	mfromtime.wDay=standfile.mDatas[0]->mHead.day;
	mfromtime.wHour=standfile.mDatas[0]->mHead.hour;
	mfromtime.wMinute=standfile.mDatas[0]->mHead.minute;
	mfromtime.wSecond=standfile.mDatas[0]->mHead.second;
	mfromtime.wMilliseconds=standfile.mDatas[0]->mHead.misecond;

	mendtime.wYear=standfile.mDatas[standfile.mDatas.size()-1]->mHead.year;
	mendtime.wMonth=standfile.mDatas[standfile.mDatas.size()-1]->mHead.mon;
	mendtime.wDay=standfile.mDatas[standfile.mDatas.size()-1]->mHead.day;
	mendtime.wHour=standfile.mDatas[standfile.mDatas.size()-1]->mHead.hour;
	mendtime.wMinute=standfile.mDatas[standfile.mDatas.size()-1]->mHead.minute;
	mendtime.wSecond=standfile.mDatas[standfile.mDatas.size()-1]->mHead.second;
	mendtime.wMilliseconds=standfile.mDatas[standfile.mDatas.size()-1]->mHead.misecond;
  
	if(m_pFrequencyMHz) delete []m_pFrequencyMHz;
	m_pFrequencyMHz=new double[m_nTotalFreqCount];
	for(int i=0;i<m_nTotalFreqCount;i++)
	{
		m_pFrequencyMHz[i]=m_dFreqMhzMin+i*m_dFreqMhzdf;
	}
	char tmpbuffer[200]={0};
	itoa(standfile.mDatas[0]->mHead.equ_no,tmpbuffer,10);
	sprintf(mStationID,"%s",tmpbuffer);

#ifdef MONITORFORMAT_TO_DBM
	m_DataType=0;
#endif

	return NG_SUCCESS;
}


int CScanFreqMonitorFile::ReadFileHead(const char*strDataPath)
{

  //因为国家格式有校验码，所以先看是否国家格式正确
   int ErrCode=ReadStandV1Head(strDataPath);
   if(INVALIDSCANFORMAT==ErrCode)
  	{
      ErrCode=ReadNGV1Head(strDataPath);
  	}

	return ErrCode;

    
}

