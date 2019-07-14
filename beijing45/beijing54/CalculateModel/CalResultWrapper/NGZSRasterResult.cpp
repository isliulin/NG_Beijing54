#include <stdio.h>
#include "NGZSRasterResult.h"
#include "../KoordTrans/KoordTrans/KoordTrans.h"
#include "../HDFSFileWR/LocalFileMgr.h"
#include <new>
#include <limits>
#include "../StringManager/StringManager.h"
#include <string.h>
#include "../BasicDef/NG_ErrorCode.h"
#include "ResultHeadCheck.h"

#ifndef UNCALCULATE
#define UNCALCULATE		((short)(0x8181))
#endif

#define  MinRange UNCALCULATE+2
#define  MaxRange SHRT_MAX


//////////////////////////////////////////////////////////////////////////
NGZSRasterResult::NGZSRasterResult()
{
	//
	head.w = 0; //宽
	head.h = 0; //高

	head.leftPos = 0; //左基准值
	head.bottomPos = 0;//下基准值
	head.xResolution = 1; //x方向分辨率
	head.yResolution = 1;//y方向分辨率

	head.factor = 10; //数据缩放比例
	m_dfactorReciprocal = 1.0/head.factor;

	head.geoSys = 0;//系统坐标系

	head.eDataType = DATA_INT2;
	head.version = 1;
	head.reserved1 = 0;
	head.reserved2 = 0;
	head.bHasData = true;

	pCount = 0;//分组数目
	p_RasterData = 0;

	//
	dataCount = 1024*1024*16;//每个块最大16M 
}

NGZSRasterResult::~NGZSRasterResult()
{
	ReleaseData();
}


void NGZSRasterResult::ReleaseData()
{

	if(p_RasterData && pCount>0)
	{
		for(unsigned int i=0;i<pCount;i++)
		{
			if(p_RasterData[i])
				delete [] p_RasterData[i];
		}
		delete [] p_RasterData;
	}
	pCount = 0;//分组数目
	p_RasterData = 0;
}


int NGZSRasterResult::GenerateEmptyRaster( ECoverResultType iResultType,CalResult_DataType dataType,CalResult_Unit iResultUnit, int iGeoSys,double iLeft,double iBottom,unsigned int iw,unsigned int ih,double iXResolution, double iYResolution,float ifactor/*=10.0f*/ )
{
	head.eResultType = iResultType;
	head.eResultUnit = iResultUnit;
	head.geoSys = iGeoSys;
	head.leftPos = iLeft;
	head.bottomPos = iBottom;
	head.xResolution = iXResolution==0?1:iXResolution;
	head.yResolution = iYResolution == 0?1:iYResolution;
	return CreateData(iw,ih,true,ifactor);
}

int NGZSRasterResult::ReadRaster(const char* filename)
{
	LocalFileReader file(filename);
	if(file.open())
		return ReadDataFromFile(&file);
	return NGZS_R_FILE_ERROR;

}


int NGZSRasterResult::ReadRasterBound( const char* filename )
{
	LocalFileReader file(filename);
	if(file.open())
		return ReadHeaderInfoInFile( &file);
	return NGZS_R_FILE_ERROR;
}


int NGZSRasterResult::WriteRaster(const char* filename)
{
	LocalFileWriter file(filename);
	if(file.open())
		return WriteDataToFile( &file );
	return NGZS_W_FILE_ERROR;
}



int NGZSRasterResult::CreateData( unsigned int iw,unsigned int ih,bool setDefalut /*= true*/,float ifactor /*= 10.0f*/ )
{
	ReleaseData();
	head.factor =(short)(ifactor==0?1:ifactor);
	m_dfactorReciprocal = 1.0/head.factor;
	head.w = iw;
	head.h = ih;
	//
	unsigned long long total =head.w*head.h;
	pCount =(unsigned) (total/dataCount +1);
	p_RasterData = new (std::nothrow)short * [pCount];
	if(p_RasterData == 0)
		return NGZS_RASTER_NOMEMORY;
	for(unsigned int i=0;i<pCount;i++)
	{
		p_RasterData[i] = 0;
	}
	//create data memory
	bool isok = true;
	for(unsigned int j=0;j<pCount-1;j++)
	{
		p_RasterData[j] = new (std::nothrow) short [dataCount];
		if(p_RasterData[j] == 0)
		{
			isok = false;
			break;
		}
		// -10000为缺省值
		if(setDefalut)
		{
			for(unsigned int k=0;k<dataCount;k++)
				p_RasterData[j][k] =UNCALCULATE;
		}

	}

	if(isok)
	{
		unsigned int cutdatacount = (unsigned)(total - (pCount-1)*dataCount);
		p_RasterData[pCount-1] = new (std::nothrow) short[cutdatacount];
		if(p_RasterData[pCount-1] == 0)
			isok = false;
		else if(setDefalut)
		{
			// -10000为缺省值
			for(unsigned int k=0;k<cutdatacount;k++)
				p_RasterData[pCount-1][k] =UNCALCULATE;
		}

	}

	if(!isok)
	{
		ReleaseData();
		return NGZS_RASTER_NOMEMORY;
	}
	return 0;
}

double NGZSRasterResult::GetValueAsDouble( int x, int y ) const
{
	double val = MinRange;
	GetDataByIndex(x,y,val); 
	return val;
}

void NGZSRasterResult::SetValue( int x,int y,double v )
{
	SetDataByIndex(x,y,v);
}


void NGZSRasterResult::GetBound(double &l,double & b, double & r, double & t, int sys) const 
{	
	l = head.leftPos;
	b = head.bottomPos;
	r = l+ head.w * head.xResolution;
	t = b + head.h * head.yResolution;
	if((sys != 0)&&(sys != head.geoSys))
	{
		ng_geo_init();
		ng_geo_trans(head.geoSys,sys,l,b,&l,&b);
		ng_geo_trans(head.geoSys,sys,r,t,&r,&t);
	}
}



void NGZSRasterResult::SetDataByIndex( unsigned int x, unsigned int y,double val )
{
	if(p_RasterData)
	{
		unsigned int pos = y*head.w + x;
		unsigned int pIndex = pos/dataCount;
		unsigned int vIndex = pos - pIndex*dataCount;

		short sVal;

		if (val <= MinRange && val > SHRT_MIN)
		{
			sVal = (short)val;
		}
		else
		{
			sVal = (short)((val > MinRange*m_dfactorReciprocal && val <= MaxRange*m_dfactorReciprocal)?(val*head.factor):UNCALCULATE); 
		}

		p_RasterData[pIndex][vIndex] = sVal;
	}


}

void NGZSRasterResult::GetDataByIndex( unsigned int x, unsigned int y,double& val ) const
{
	if(p_RasterData)
	{
		unsigned int pos = y*head.w + x;
		unsigned int pIndex = pos/dataCount;
		unsigned int vIndex = pos - pIndex*dataCount;
		short sval = p_RasterData[pIndex][vIndex];
		val = sval>MinRange?(sval*m_dfactorReciprocal):sval;
	}

}

void NGZSRasterResult::GetDataOnResolutionByIndex(unsigned int x, unsigned int y,double resolution,double& val) const
{
	if(!p_RasterData)
		return;
	unsigned int xsize = (int)(resolution/head.xResolution)/2;
	unsigned int ysize = (int)(resolution/head.xResolution)/2;
	if(xsize<2&&ysize<2)
	{
		unsigned int pos = y*head.w + x;
		unsigned int pIndex = pos/dataCount;
		unsigned int vIndex = pos - pIndex*dataCount;
		short sval = p_RasterData[pIndex][vIndex];
		val = sval>MinRange?(sval*m_dfactorReciprocal):sval;
	}
	else
	{
		double totalvalue=0;
		unsigned int totalcount = 0;
		unsigned startXindex = x<xsize?0:x-xsize;
		unsigned startYindex = y<ysize?0:y-ysize;
		unsigned endXindex = x+xsize>=head.w?head.w-1:x+xsize;
		unsigned endYindex = y+ysize>=head.h?head.h-1:y+ysize;
		for(unsigned iy=startYindex;iy<=endYindex;iy++)
		{
			for(unsigned ix=startXindex;ix<=endXindex;ix++)
			{
				unsigned int pos = iy*head.w + ix;
				unsigned int pIndex = pos/dataCount;
				unsigned int vIndex = pos - pIndex*dataCount;
				short iv = p_RasterData[pIndex][vIndex];
				if(iv>MinRange)
				{
					totalvalue += iv;
					totalcount++;
				}

			}
		}

		if(totalcount == 0)
			val = UNCALCULATE;
		else
			val = totalvalue/totalcount/head.factor;
	}
}

bool NGZSRasterResult::SetDataByPos( double xpos,double ypos, double val )
{
	if((xpos<head.leftPos)||(ypos<head.bottomPos))
		return false;
	unsigned int x = (unsigned int)((xpos-head.leftPos)/head.xResolution);
	if(x>=head.w)
		return false;
	unsigned int y = (unsigned int)((ypos-head.bottomPos)/head.yResolution);
	if(y>=head.h)
		return false;
	SetDataByIndex(x,y,val);
	return true;

}

bool NGZSRasterResult::GetDataByPos( double xpos,double ypos, double &val ) const
{
	if((xpos<head.leftPos)||(ypos<head.bottomPos))
		return false;
	unsigned int x = (unsigned int)((xpos-head.leftPos)/head.xResolution);
	if(x>=head.w)
		return false;
	unsigned int y = (unsigned int)((ypos-head.bottomPos)/head.yResolution);
	if(y>=head.h)
		return false;
	GetDataByIndex(x,y,val);
	return true;
}


bool NGZSRasterResult::GetDataOnResolutionByPos( double xpos, double ypos,int sys,double resolution,double& val) const 
{
	if((sys!=0)&&(sys!=head.geoSys))
	{
		ng_geo_init();
		ng_geo_trans(sys,head.geoSys,xpos,ypos,&xpos,&ypos);
	}
	//
	if((xpos<head.leftPos)||(ypos<head.bottomPos))
		return false;
	unsigned int x = (unsigned int)((xpos-head.leftPos)/head.xResolution);
	if(x>=head.w)
		return false;
	unsigned int y = (unsigned int)((ypos-head.bottomPos)/head.yResolution);
	if(y>=head.h)
		return false;
	GetDataOnResolutionByIndex(x,y,resolution,val);
	return true;
}

bool  NGZSRasterResult::GetDataByPos(double xpos,double ypos, int sys,double &val) const
{
	if((sys!=0)&&(sys!=head.geoSys))
	{
		ng_geo_init();
		ng_geo_trans(sys,head.geoSys,xpos,ypos,&xpos,&ypos);
	}
	//
	if((xpos<head.leftPos)||(ypos<head.bottomPos))
		return false;
	unsigned int x = (unsigned int)((xpos-head.leftPos)/head.xResolution);
	if(x>=head.w)
		return false;
	unsigned int y = (unsigned int)((ypos-head.bottomPos)/head.yResolution);
	if(y>=head.h)
		return false;
	GetDataByIndex(x,y,val);
	return true;
}

int NGZSRasterResult::CreateEmptyData( ECoverResultType iResultType,CalResult_Unit iResultUnit,int iGeoSys,double iLeft,double iBottom, double iXResolution,double iYResolution,unsigned int iw,unsigned int ih,float ifactor/*=10.0f*/ )
{
	head.eResultType = iResultType;
	head.eResultUnit = iResultUnit;
	head.geoSys = iGeoSys;
	head.leftPos = iLeft;
	head.bottomPos = iBottom;
	head.xResolution = iXResolution==0?1:iXResolution;
	head.yResolution = iYResolution == 0?1:iYResolution;
	return CreateData(iw,ih,true,ifactor);
}


int NGZSRasterResult::ReadHeaderInfoInFile( IFileReader * ifr )
{
	if(!ifr||!ifr->isvalid())
		return NGZS_R_FILE_ERROR;
	try
	{
		ifr->gotohead();
		ifr->read(&head,sizeof(head));
		return 0;
	}
	catch(...)
	{
		return NGZS_R_FILE_ERROR;
	}
}


int NGZSRasterResult::ReadDataFromFile( IFileReader * ifr )
{
	if(!ifr||!ifr->isvalid())
		return NGZS_R_FILE_ERROR;
	try
	{
		ifr->gotohead();
		ifr->read(&head,sizeof(head));
		SwapHead(head);
		int res = CreateData(head.w,head.h,false,head.factor);
		if(res == 0)
		{
			for(unsigned int i=0;i<pCount-1;i++)
				ifr->read(p_RasterData[i],sizeof(short)*dataCount);
			//
			unsigned int total =head.w*head.h;
			unsigned int cutdatacount = total - (pCount-1)*dataCount;
			ifr->read(p_RasterData[pCount-1],sizeof(short)*cutdatacount);
			//
			SwapData();
			return 0;
		}
		return res;

	}
	catch(...)
	{
		return NGZS_R_FILE_ERROR;
	}
}




int NGZSRasterResult::ReadIndexDataFromFile( IFileReader * ifr,int x, int y,double & dVal )
{
	if(!ifr||!ifr->isvalid())
		return NGZS_R_FILE_ERROR;
	try
	{
		NGZSRasterHeader temphead;
		ifr->gotohead();
		ifr->read(&temphead,sizeof(temphead));
		SwapHead(temphead);
		unsigned offset = y*temphead.w+x;
		ifr->seek(offset*sizeof(short));
		short sVal = 0;
		ifr->read(&sVal,sizeof(short));
		if(!IS_LittleEndian)
			SWAP_DATA_ORDER(sVal);
		dVal = sVal*1.0/temphead.factor;
		return 0;
	}
	catch(...)
	{
		return NGZS_R_FILE_ERROR;
	}
}

int NGZSRasterResult::ReadIndexDataFromFile( const char * ifilename,int x, int y,double & dVal )
{
	LocalFileReader file(ifilename);
	if(file.open())
		return ReadIndexDataFromFile(&file,x,y,dVal);
	return NGZS_R_FILE_ERROR;
}



int NGZSRasterResult::ReadPosDataFromFile( const char * ifilename,double xpos, double ypos,double & dVal,int sys )
{
	LocalFileReader file(ifilename);
	if(file.open())
		return ReadPosDataFromFile(&file,xpos,ypos,dVal);
	return NGZS_R_FILE_ERROR;
}

int NGZSRasterResult::ReadPosDataFromFile( IFileReader * ifr,double xpos, double ypos,double & dVal,int sys )
{

	if(!ifr||!ifr->isvalid())
		return NGZS_R_FILE_ERROR;
	try
	{
		NGZSRasterHeader temphead;
		ifr->gotohead();
		ifr->read(&temphead,sizeof(temphead));
		SwapHead(temphead);

		if((sys!=0)&&(sys!=temphead.geoSys))
		{
			ng_geo_init();
			ng_geo_trans(sys,temphead.geoSys,xpos,ypos,&xpos,&ypos);
		}
		///////////////////////////////////////////////////////////////////////////////


		if((xpos<temphead.leftPos)||(ypos<temphead.bottomPos))
		{
			return NGZS_POSITION_NOTINBOUND;
		}
		unsigned int x = (unsigned int)((xpos-temphead.leftPos)/temphead.xResolution);
		if(x>=temphead.w)
		{
			return NGZS_POSITION_NOTINBOUND;
		}
		unsigned int y = (unsigned int)((ypos-temphead.bottomPos)/temphead.yResolution);
		if(y>=temphead.h)
		{
			return NGZS_POSITION_NOTINBOUND;
		}
		unsigned offset =(y*temphead.w+x);
		ifr->seek(offset*sizeof(short));
		short sVal = 0;
		ifr->read(&sVal,sizeof(short));
		if(!IS_LittleEndian)
			SWAP_DATA_ORDER(sVal);
		dVal = sVal*1.0/temphead.factor;
		return 0;
	}
	catch(...)
	{
		return NGZS_R_FILE_ERROR;
	}
}



int NGZSRasterResult::WriteDataToFile( IFileWriter *ifw )
{
	if(!p_RasterData)
		return NGZS_W_NODATA;
	if(!ifw||!ifw->isvalid())
		return NGZS_W_FILE_ERROR;
	unsigned long long total =head.w*head.h;
	//注意，两者交换顺序要
	SwapData();
	SwapHead(head);
	try
	{
		ifw->write(&head,sizeof(head));
		for(unsigned int i=0;i<pCount-1;i++)
			ifw->write(p_RasterData[i],dataCount*sizeof(short));
		
		unsigned int cutdatacount = (unsigned)(total - (pCount-1)*dataCount);
		ifw->write(p_RasterData[pCount-1],cutdatacount*sizeof(short));
		SwapHead(head);
		SwapData();
		return 0;
	}
	catch(...)
	{
		SwapHead(head);
		SwapData();
		return NGZS_W_FILE_ERROR;
	}

}


void NGZSRasterResult::SwapHead(NGZSRasterHeader & head)
{
	 if(!IS_LittleEndian)
	 {
		 SWAP_DATA_ORDER(head.w);
		 SWAP_DATA_ORDER(head.h);
		 SWAP_DATA_ORDER(head.leftPos);
		 SWAP_DATA_ORDER(head.bottomPos);
		 SWAP_DATA_ORDER(head.xResolution);
		 SWAP_DATA_ORDER(head.yResolution);
		 SWAP_DATA_ORDER(head.geoSys);
		 SWAP_DATA_ORDER(head.factor);
		 SWAP_DATA_ORDER(head.eResultType);
		 SWAP_DATA_ORDER(head.eResultUnit);
		 SWAP_DATA_ORDER(head.reserved1);
		 SWAP_DATA_ORDER(head.reserved2);
		 SWAP_DATA_ORDER(head.version);
	 }
}

void NGZSRasterResult::SwapData()
{
	if(!p_RasterData)return;
	if(IS_LittleEndian)
		return;

	unsigned long long total =head.w*head.h;

	for(unsigned int j=0;j<pCount-1;j++)
	{		
		for(unsigned int k=0;k<dataCount;k++)
			SWAP_DATA_ORDER(p_RasterData[j][k]);
	}

	unsigned int cutdatacount = (unsigned)(total - (pCount-1)*dataCount);
	for(unsigned int k=0;k<cutdatacount;k++)
		SWAP_DATA_ORDER(p_RasterData[pCount-1][k]);
}

bool NGZSRasterResult::CheckFile( const char * ifilename )
{

	if(!ifilename) return false;
	try
	{
		LocalFileReader file(ifilename);
		if(file.open())
		{
			NGZSRasterHeader temphead;
			file.read(&temphead,sizeof(temphead));
			SwapHead(temphead);

			return CHECK_VALUE_BETWEEN(temphead.leftPos,-1e8,1e8)&&CHECK_VALUE_BETWEEN(temphead.bottomPos,-1e8,1e8)&&CHECK_VALUE_BETWEEN(temphead.geoSys,0,1000)&&CHECK_VALUE_BETWEEN(temphead.factor,-1000,1000)&&CHECK_VALUE_BETWEEN(temphead.version,0,1000);
		}
	}
	catch (...)
	{
		return false;
	}

	return false;

}

NGZSRasterResult * NGZSRasterResult::CreateArray( int n )
{
	if(n<1)
		return NULL;
	return new NGZSRasterResult[n];
}

void NGZSRasterResult::DestroyArray( NGZSRasterResult *& pRasterResult )
{
	if(pRasterResult!=NULL)
		delete []pRasterResult;
	pRasterResult = NULL;
}

