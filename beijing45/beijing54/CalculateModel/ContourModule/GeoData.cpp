// GeoData.cpp: implementation of the CGeoData class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "GeoData.h"

#include "2DMemAllocator.h"
#include "../CalResultWrapper/RasterResult.h"

#pragma warning(disable:4996)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeoData::CGeoData()
{
	m_ppGridData = NULL;
	memset(&m_DataInfo,0,sizeof(m_DataInfo));
}

CGeoData::~CGeoData()
{
	if( m_ppGridData!=NULL)
	{
		C2DMemAllocator::FreeMemory2D(m_ppGridData);
		m_ppGridData = NULL;
	}

}

bool CGeoData::SetRasterData( void * pRasterData )
{
	if(pRasterData == NULL)
		return false;
	RasterResult &data = *(RasterResult*)pRasterData;
	double dMax_Z = -9999;
	double dMin_Z = 9999;
	int nXSize = data.GetWidth();
	int nYSize = data.GetHeight();
	m_DataInfo.rows = nYSize;
	m_DataInfo.cols = nXSize;
	double left,bottom;
	data.GetLowerLeftCorner(left,bottom);
	m_DataInfo.xMin = left;
	m_DataInfo.yMin = bottom;
	m_DataInfo.xMax = left + m_DataInfo.cols*data.GetResolutionX();
	m_DataInfo.yMax = bottom + m_DataInfo.rows*data.GetResolutionY();

	if( m_ppGridData!=NULL)
	{
		C2DMemAllocator::FreeMemory2D(m_ppGridData);
		m_ppGridData = NULL;
	}

	///////////////////////////////////////
	//读网格数据
	//	ASSERT( m_ppGridData==NULL );
	if( !C2DMemAllocator::AllocMemory2D(m_ppGridData, m_DataInfo.rows, m_DataInfo.cols) )
	{
		return false;
	}

	for (int iY=0;iY<nYSize;iY++)
	{
		for (int iX=0;iX<nXSize;iX++)
		{
			double dValue = data.GetValueAsDouble(iX,iY);
			if (dValue < -1e4)
			{
				dValue = -32383;
			}
			m_ppGridData[iY][iX] = (float)dValue;
			if (dValue>dMax_Z)
			{
				dMax_Z = dValue;
			}
			if ((dValue<dMin_Z)&&(dValue+32383.00)!=0)
			{
				dMin_Z = dValue;
			}
		}
	}
	m_DataInfo.zMin = (float)dMin_Z;
	m_DataInfo.zMax = (float)dMax_Z;
	return true;
}

bool CGeoData::ReadData(const char* pathName)
{
	double dMax_Z = -9999;
	double dMin_Z = 9999;
	RasterResult data;
	if (data.ReadRaster(pathName)!=NG_SUCCESS)
	{
		return false;
	}

	int nXSize = data.GetWidth();
	int nYSize = data.GetHeight();
	m_DataInfo.rows = nYSize;
	m_DataInfo.cols = nXSize;
	double left,bottom;
	data.GetLowerLeftCorner(left,bottom);
	m_DataInfo.xMin = left;
	m_DataInfo.yMin = bottom;
	m_DataInfo.xMax = left + m_DataInfo.cols*data.GetResolutionX();
	m_DataInfo.yMax = bottom + m_DataInfo.rows*data.GetResolutionY();

	if( m_ppGridData!=NULL)
	{
		C2DMemAllocator::FreeMemory2D(m_ppGridData);
		m_ppGridData = NULL;
	}

	///////////////////////////////////////
	//读网格数据
//	ASSERT( m_ppGridData==NULL );
	if( !C2DMemAllocator::AllocMemory2D(m_ppGridData, m_DataInfo.rows, m_DataInfo.cols) )
	{
	//	AfxMessageBox("内存分配失败，数据读取没有成功!");
		return false;
	}

	for (int iY=0;iY<nYSize;iY++)
	{
		for (int iX=0;iX<nXSize;iX++)
		{
			double dValue = data.GetValueAsDouble(iX,iY);
			if (dValue < -1e4)
			{
				dValue = -32383;
			}
			m_ppGridData[iY][iX] = (float)dValue;
			if (dValue>dMax_Z)
			{
				dMax_Z = dValue;
			}
			if ((dValue<dMin_Z)&&(dValue+32383.00)!=0)
			{
				dMin_Z = dValue;
			}
		}
	}
	m_DataInfo.zMin = (float)dMin_Z;
	m_DataInfo.zMax = (float)dMax_Z;
	return true;

}


bool CGeoData::SaveData(string pathName)
{
	//ASSERT(m_ppGridData!=NULL);

	int i, j;
	float tmp;
	FILE* fpout = NULL;


	fpout = fopen(pathName.c_str(), "wt");
	if(fpout == 0){
		printf("   open file error!!!!!!!!!!!!\n");
		return false;
	}
	float gridZmin= 1.e38f;
	float gridZmax=-1.e38f;
	for(i= 0; i<m_DataInfo.rows; i++)
	{
		for(j=0; j<m_DataInfo.cols; j++)
		{
			tmp=m_ppGridData[i][j];
			if(tmp > gridZmax) gridZmax=tmp;
			if(tmp < gridZmin) gridZmin=tmp;
		}
	}

	m_DataInfo.zMax = gridZmax;
	m_DataInfo.zMin = gridZmin;

	fprintf(fpout,"DSAA\n");
	fprintf(fpout,"%d %d\n",m_DataInfo.cols,m_DataInfo.rows);
	fprintf(fpout,"%f %f\n",m_DataInfo.xMin,m_DataInfo.xMax);
	fprintf(fpout,"%f %f\n",m_DataInfo.yMin,m_DataInfo.yMax);
	fprintf(fpout,"%f %f\n",m_DataInfo.zMin,m_DataInfo.zMax);

	for(i= 0; i<m_DataInfo.rows; i++)
	{
		for(j=0; j<m_DataInfo.cols; j++)
		{


			if( (i*m_DataInfo.cols+j)%8 == 0 )
				fprintf(fpout,"\n");

			fprintf(fpout,"%11.5f ",m_ppGridData[i][j]);
		}
	}

	fclose(fpout);

	return true;
}



