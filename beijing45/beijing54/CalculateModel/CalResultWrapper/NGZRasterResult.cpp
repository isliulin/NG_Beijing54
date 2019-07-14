#include <stdio.h>
#include "NGZRasterResult.h"
#include "../StringManager/StringManager.h"
#include "../KoordTrans/KoordTrans/KoordTrans.h"
#include "../BasicDef/NG_ErrorCode.h"
#include "ResultHeadCheck.h"
#include "CalResultWrapper.h"

#ifdef USE_ZLIB
#include "../HDFSFileWR/SearchIfStream.h"
#include "../HDFSFileWR/ZipOfStream.h"
#else
#include <fstream>
#endif


#ifndef ResultDataTypeSize
#define ResultDataTypeSize(size,datatype) switch(datatype){\
	case DATA_DOUBLE:size = 8;break; \
	case DATA_FLOAT: \
	case DATA_INT4: \
	case DATA_UINT4:size = 4;break;\
	case DATA_INT2:\
	case DATA_UINT2:size =2;break;\
	case DATA_CHAR:\
	case DATA_UCHAR:size = 1;break;\
	default:size = 0;break;\
	}
#endif

#ifndef ResultDataTypeSet
#define ResultDataTypeSet(v,datatype,p,n) switch(datatype){\
	case DATA_DOUBLE:*(((double*)(p))+n) = (double)v ;break; \
	case DATA_FLOAT:*(((float*)(p))+n) = (float)v ;break; \
	case DATA_INT4: *(((int*)(p))+n) = (int)v ;break;\
	case DATA_UINT4: *(((unsigned *)(p))+n) = (unsigned)v ;break;\
	case DATA_INT2: *(((short*)(p))+n) = (short)v ;break; \
	case DATA_UINT2: *(((unsigned short*)(p))+n) = (unsigned short)v ;break;\
	case DATA_CHAR:*(((char*)(p))+n) = (char)v ;break;\
	case DATA_UCHAR: *(((unsigned char*)(p))+n) = (unsigned char)v ;break;\
	default:break;\
	}
#endif

#ifndef ResultDataTypeGet
#define ResultDataTypeGet(v,datatype,p,n) switch(datatype){\
	case DATA_DOUBLE:v = *(((double*)(p))+n);break; \
	case DATA_FLOAT:v = *(((float*)(p))+n);break; \
	case DATA_INT4:v = *(((int*)(p))+n);break;\
	case DATA_UINT4:v = *(((unsigned *)(p))+n);break;\
	case DATA_INT2:v = *(((short*)(p))+n);break; \
	case DATA_UINT2:v = *(((unsigned short*)(p))+n);break;\
	case DATA_CHAR:v = *(((char*)(p))+n);break;\
	case DATA_UCHAR:v = *(((unsigned char*)(p))+n);break;\
	default:break;\
	}
#endif



//////////////////////////////////////////////////////////////////////////
NGZRasterResult::NGZRasterResult()
{

	head.w = 0; //宽
	head.h = 0; //高

	head.leftPos = 0; //左基准值
	head.bottomPos = 0;//下基准值
	head.xResolution = 1; //x方向分辨率
	head.yResolution = 1;//y方向分辨率
	head.eDataType = UNKNOWN_DATATYPE;
	head.geoSys = 0;//系统坐标系

	pCount = 0;//分组数目
	p_RasterData = 0;
	//
	dataCount = 1024*1024*16;//每个块最大16M 
}

NGZRasterResult::~NGZRasterResult()
{
	ReleaseData();
}

int NGZRasterResult::GenerateEmptyRaster( ECoverResultType iResultType,
										  CalResult_DataType dataType,
										  CalResult_Unit iResultUnit, 
										  int iGeoSys,
										  double iLeft,double iBottom,
										  unsigned int iw,unsigned int ih,
										  double iXResolution, double iYResolution,
										  float ifactor/*=1.0f*/ )
{
	//
	head.eResultType = iResultType;
	head.eResultUnit = iResultUnit;
	head.geoSys = iGeoSys;
	head.leftPos = iLeft;
	head.bottomPos = iBottom;
	head.xResolution = iXResolution==0?1:iXResolution;
	head.yResolution = iYResolution == 0?1:iYResolution;
	head.eDataType = dataType;
	return CreateData(iw,ih,true);
	
}

int NGZRasterResult::CreateData( unsigned iw,unsigned ih,bool setDefault )
{
	ReleaseData();
	head.w = iw;
	head.h = ih;
	//
	unsigned long long total =head.w*head.h;
	pCount =(unsigned) (total/dataCount +1);
	p_RasterData = new (std::nothrow)void * [pCount];
	if(p_RasterData == 0)
		return NGZ_RASTER_NOMEMORY;
	for(unsigned int i=0;i<pCount;i++)
	{
		p_RasterData[i] = 0;
	}
	//create data memory
	bool isok = true;
	unsigned datasize = 0;
	ResultDataTypeSize(datasize,head.eDataType);
	for(unsigned int j=0;j<pCount-1;j++)
	{
		p_RasterData[j] = malloc(dataCount*datasize);
		if(p_RasterData[j] == 0)
		{
			isok = false;
			break;
		}
		if(setDefault)
		{
			memset(p_RasterData[j],dataCount*datasize,0x81);
		}
	}

	if(isok)
	{
		unsigned int cutdatacount = (unsigned)(total - (pCount-1)*dataCount);
		p_RasterData[pCount-1] = malloc(cutdatacount*datasize);
		if(p_RasterData[pCount-1] == 0)
			isok = false;
		else if(setDefault)
		{
			memset(p_RasterData[pCount-1],cutdatacount*datasize,0x81);
		}

	}

	if(!isok)
	{
		ReleaseData();
		return NGZ_RASTER_NOMEMORY;
	}
	return 0;
}


int NGZRasterResult::ReadRaster(const char* filename)
{

	if(filename==0)
		return NGZ_R_FILENAME_NULL;
#ifdef USE_ZLIB
	SearchIfStream file(filename, 0);
#else
	std::locale::global(std::locale(""));
	std::ifstream file(filename,std::ios_base::in | std::ios_base::binary);
	std::locale::global(std::locale("C"));
#endif
	if (!file.good())
		return NGZ_R_FILE_ERROR;

	try
	{
		ReleaseData();
		//读头部信息
		file.read((char*)&head, sizeof(head));
		SwapHead(head);
		unsigned dataszie = 0;
		ResultDataTypeSize(dataszie,head.eDataType);
		bool bHasData = false;
		file.read((char*)&bHasData,sizeof(bHasData));
		if(bHasData)
		{	
			int res = CreateData(head.w,head.h,false);
			if(0 == res)
			{
				for(unsigned int i=0;i<pCount-1;i++)
					file.read((char*)p_RasterData[i],dataszie*dataCount);
				unsigned long long  total =head.w*head.h;
				unsigned int cutdatacount = (unsigned int)(total - (pCount-1)*dataCount);
				file.read((char*)(p_RasterData[pCount-1]),dataszie*cutdatacount);
				//
				SwapData();	
				return 0;
			}
			else
				return res;
		}
	}
	catch (...)
	{
		file.close();
		return NGZ_R_FILE_ERROR;
	}
	return NGZ_R_FILE_ERROR;
}

void NGZRasterResult::SwapHead( NGZRasterHeader & head )
{
	if(!IS_LittleEndian)
	{
		SWAP_DATA_ORDER(head.eResultType);
		SWAP_DATA_ORDER(head.eResultUnit);
		SWAP_DATA_ORDER(head.eDataType);
		SWAP_DATA_ORDER(head.geoSys);
		SWAP_DATA_ORDER(head.leftPos);
		SWAP_DATA_ORDER(head.bottomPos);
		SWAP_DATA_ORDER(head.xResolution);
		SWAP_DATA_ORDER(head.yResolution);
		SWAP_DATA_ORDER(head.w);
		SWAP_DATA_ORDER(head.h);
	}
}

void NGZRasterResult::SwapData()
{
	if(!p_RasterData)return;
	if(IS_LittleEndian)
		return;
	unsigned dataszie = 0;
	ResultDataTypeSize(dataszie,head.eDataType);

	unsigned long long total =head.w*head.h;

	for(unsigned int j=0;j<pCount-1;j++)
	{	
		char * p = (char*)p_RasterData[j];
		for(unsigned int k=0;k<dataCount;k++)
			NGStringManager::Swapnbytes(p+k*dataszie,dataszie);
	}

	unsigned int cutdatacount = (unsigned)(total - (pCount-1)*dataCount);
	{
		char * p = (char*)p_RasterData[pCount-1];
		for(unsigned int k=0;k<cutdatacount;k++)
			NGStringManager::Swapnbytes(p+k*dataszie,dataszie);
	}
}


int NGZRasterResult::ReadRasterBound( const char* filename )
{
#ifdef USE_ZLIB
	SearchIfStream file(filename, 0);
#else
	std::locale::global(std::locale(""));
	std::ifstream file(filename,std::ios_base::in | std::ios_base::binary);
	std::locale::global(std::locale("C"));
#endif

	if (!file.good())
		return NGZ_R_FILE_ERROR;
	try
	{
		ReleaseData();
		//读头部信息
		file.read((char*)&head, sizeof(head));
		SwapHead(head);
		file.close();
		return 0;
	}
	catch (...)
	{
		file.close();
		return NGZ_R_FILE_ERROR;
	}
}

double NGZRasterResult::GetValueAsDouble( int x, int y ) const
{
	double val = 0;
	if(p_RasterData)
	{
		unsigned int pos = y*head.w + x;
		unsigned int pIndex = pos/dataCount;
		unsigned int vIndex = pos - pIndex*dataCount;
		ResultDataTypeGet(val,head.eDataType,p_RasterData[pIndex],vIndex);
	}
	return val;
}

void NGZRasterResult::SetValue( int x,int y,double v )
{
	if(p_RasterData)
	{
		unsigned int pos = y*head.w + x;
		unsigned int pIndex = pos/dataCount;
		unsigned int vIndex = pos - pIndex*dataCount;
		ResultDataTypeSet(v,head.eDataType,p_RasterData[pIndex],vIndex);
	}
}

bool NGZRasterResult::GetValueByPos( double posX,double posY,double& val ) const
{
	if((posX<head.leftPos)||(posX<head.bottomPos))
		return false;
	unsigned int x = (unsigned int)((posX-head.leftPos)/head.xResolution);
	if(x>=head.w)
		return false;
	unsigned int y = (unsigned int)((posX-head.bottomPos)/head.yResolution);
	if(y>=head.h)
		return false;
	val = GetValueAsDouble(x,y);
	return true;
}

void NGZRasterResult::GetDataOnResolutionByIndex( unsigned int x, unsigned int y,double resolution,double& val ) const
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
		ResultDataTypeGet(val,head.eDataType,p_RasterData[pIndex],vIndex);
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
				double iv = 0;
				ResultDataTypeGet(iv,head.eDataType,p_RasterData[pIndex],vIndex);
				if(IS_RESULTVALUE_VALID(iv))
				{
					totalvalue += iv;
					totalcount++;
				}

			}
		}

		if(totalcount == 0)
			val = 0x8181;
		else
			val = totalvalue/totalcount;
	}
}

bool NGZRasterResult::GetDataByPos( double xpos,double ypos, int sys,double &val ) const
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
	val = GetValueAsDouble(x,y);
	return true;
}



void NGZRasterResult::GetBound( double &l,double &b, double &r, double &t, int sys ) const
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

int NGZRasterResult::WriteRaster( const char* filename )
{
#ifdef USE_ZLIB
	ZipOfStream file(filename);
#else
	std::locale::global(std::locale(""));
	std::ofstream file(filename,std::ios_base::out | std::ios_base::binary);
	std::locale::global(std::locale("C"));
#endif
	if (!file.good())
		return NGZ_W_FILE_ERROR;
	unsigned long long total =head.w*head.h;
	//注意，两者交换顺序要
	SwapData();
	SwapHead(head);
	try
	{
		file.write((char*)&head,sizeof(head));
		bool bHasData = p_RasterData!=0;
		file.write((char*)&bHasData,sizeof(bHasData));
		unsigned datasize = 0;
		ResultDataTypeSize(datasize,head.eDataType);
		if(bHasData)
		{
			for(unsigned int i=0;i<pCount-1;i++)
				file.write((char*)p_RasterData[i],dataCount*datasize);
			unsigned int cutdatacount =(unsigned)(total - (pCount-1)*dataCount);
			file.write((char*)p_RasterData[pCount-1],cutdatacount*datasize);
		}
		//交换回原来的数据
		SwapHead(head);
		SwapData();
		return 0;
	}
	catch(...)
	{
		//交换回原来的数据
		SwapHead(head);
		SwapData();
		return NGZ_W_FILE_ERROR;
	}

}


#ifdef USE_ZLIB
void SeekSearchIfStream(SearchIfStream& file,unsigned int seekCount)
{
	char * seekData = new char[seekCount];
	if(seekData!=NULL)
	{
		file.read(seekData,seekCount);
		delete []seekData;
	}
	else
	{
		char seekTempData[1024];
		while(seekCount>1024)
		{
			file.read(seekTempData,1024);
			seekCount -= 1024;
		}
		if(seekCount>0)
		{
			file.read(seekTempData,seekCount);
		}
	}
}
#else
#define SeekSearchIfStream(file,offsize) file.seekg(offsize,std::ios::cur)
#endif


int NGZRasterResult::ReadIndexDataFromFile( const char * filename,int x, int y,double &val )
{

#ifdef USE_ZLIB
	SearchIfStream file(filename, 0);
#else
	std::locale::global(std::locale(""));
	std::ifstream file(filename,std::ios_base::out | std::ios_base::binary);
	std::locale::global(std::locale("C"));
#endif
	if (!file.good())
		return NGZ_R_FILE_ERROR;
	try
	{
		NGZRasterHeader temphead;
		file.read((char*)&temphead,sizeof(temphead));
		SwapHead(temphead);
		bool bHasData = false;
		file.read((char*)&bHasData,sizeof(bHasData));
		if(!bHasData)
			return NGZ_FILE_NULL_DATA;
		unsigned datasize = 0;
		ResultDataTypeSize(datasize,temphead.eDataType);
		unsigned offset = y*temphead.w+x;
		SeekSearchIfStream(file,offset*datasize);
		char tempdata[8] = {-1};
		file.read(tempdata,datasize);
		if(!IS_LittleEndian)
			NGStringManager::Swapnbytes((void*)tempdata,datasize);
		ResultDataTypeGet(val,temphead.eDataType,(void*)tempdata,0);
		return 0;
	}
	catch(...)
	{
		return NGZ_R_FILE_ERROR;
	}
}

int NGZRasterResult::ReadPosDataFromFile( const char * filename,double xpos, double ypos,double &val,int sys/*=0*/ )
{

#ifdef USE_ZLIB
	SearchIfStream file(filename, 0);
#else
	std::locale::global(std::locale(""));
	std::ifstream file(filename,std::ios_base::out | std::ios_base::binary);
	std::locale::global(std::locale("C"));
#endif
	if (!file.good())
		return NGZ_R_FILE_ERROR;
	try
	{
		NGZRasterHeader temphead;
		file.read((char*)&temphead,sizeof(temphead));
		SwapHead(temphead);
		bool bHasData = false;
		file.read((char*)&bHasData,sizeof(bHasData));
		if(!bHasData)
			return NGZ_FILE_NULL_DATA;
		if((sys!=0)&&(sys!=temphead.geoSys))
		{
			ng_geo_init();
			ng_geo_trans(sys,temphead.geoSys,xpos,ypos,&xpos,&ypos);
		}
		///////////////////////////////////////////////////////////////////////////////


		if((xpos<temphead.leftPos)||(ypos<temphead.bottomPos))
		{

			return NGZ_POSITION_NOTINBOUND;
		}
		unsigned int x = (unsigned int)((xpos-temphead.leftPos)/temphead.xResolution);
		if(x>=temphead.w)
		{
			return NGZ_POSITION_NOTINBOUND;
		}
		unsigned int y = (unsigned int)((ypos-temphead.bottomPos)/temphead.yResolution);
		if(y>=temphead.h)
		{
			return NGZ_POSITION_NOTINBOUND;
		}
		unsigned datasize = 0;
		ResultDataTypeSize(datasize,temphead.eDataType);
		unsigned offset = y*head.w+x;
		SeekSearchIfStream(file,offset*datasize);
		char tempdata[8] = {-1};
		file.read(tempdata,datasize);
		if(!IS_LittleEndian)
			NGStringManager::Swapnbytes((void*)tempdata,datasize);
		ResultDataTypeGet(val,temphead.eDataType,(void*)tempdata,0);
		return 0;
	}
	catch(...)
	{
		return NGZ_R_FILE_ERROR;
	}
}

void NGZRasterResult::ReleaseData()
{
	if(p_RasterData && pCount>0)
	{
		for(unsigned int i=0;i<pCount;i++)
		{
			if(p_RasterData[i])
				free(p_RasterData[i]);
		}
		delete [] p_RasterData;
	}
	pCount = 0;//分组数目
	p_RasterData = 0;
}

bool NGZRasterResult::CheckFile( const char * ifilename )
{
	if(!ifilename) return false;
	try
	{
#ifdef USE_ZLIB
		SearchIfStream file(ifilename, 0);
#else
		std::locale::global(std::locale(""));
		std::ifstream file(ifilename,std::ios_base::in | std::ios_base::binary);
		std::locale::global(std::locale("C"));
#endif
		if (file.good())
		{
			NGZRasterHeader temphead;
			file.read((char*)&temphead,sizeof(temphead));
			SwapHead(temphead);

			return CHECK_VALUE_BETWEEN(temphead.leftPos,-1e8,1e8)&&CHECK_VALUE_BETWEEN(temphead.bottomPos,-1e8,1e8)&&CHECK_VALUE_BETWEEN(temphead.geoSys,0,1000);
		}
	}
	catch (...)
	{
		return false;
	}

	return false;
}





