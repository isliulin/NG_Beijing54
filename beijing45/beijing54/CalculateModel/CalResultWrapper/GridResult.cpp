#include <stdio.h>
#include <string.h>
#include "GridResult.h"
#include <new>

#include "../StringManager/StringManager.h"
#include "../BasicDef/NG_ErrorCode.h"

#ifdef USE_ZLIB
#include "../HDFSFileWR/SearchIfStream.h"
#include "../HDFSFileWR/ZipOfStream.h"
#else
#include <fstream>
#endif

GridResult* GridResult::Create()
{
	return new GridResult();
}

GridResult* GridResult::Create( int nSize )
{
	return new GridResult(nSize);
}

void GridResult::Destroy( GridResult* pResult )
{
	if(pResult != NULL)
	{
		delete pResult;
		pResult = NULL;
	}	
}

GridResult::GridResult(void)
{
	m_p3DPoints = NULL;
	m_pValues = NULL;
	m_nCoordSys = -1;
	m_nPointsNum = 0;
	m_nSize = 0;
}

GridResult::GridResult( int nSize )
{
	if(nSize != 0)
	{
		m_nCoordSys = -1;
		m_nPointsNum = 0;

		m_p3DPoints = new (std::nothrow)CDoublePoint[nSize];
		m_pValues = new (std::nothrow)float[nSize];	
		if(!m_pValues || !m_p3DPoints)
		{
			Clear();
			return;
		}

		m_nSize = nSize;
		m_nPointsNum = 0;

		memset(m_p3DPoints, 0, sizeof(CDoublePoint)*nSize);
		memset(m_pValues, 0, sizeof(float)*nSize);
	}
	else
	{
		m_p3DPoints = NULL;
		m_pValues = NULL;
		m_nCoordSys = -1;
		m_nPointsNum = 0;
		m_nSize = 0;
	}	
}

GridResult::~GridResult(void)
{
	Clear();
}

int GridResult::ReSize( int nSize )
{
	if(nSize > m_nSize)
	{
		Clear();

		m_nCoordSys = -1;
		m_nPointsNum = 0;

		m_p3DPoints = new(std::nothrow) CDoublePoint[nSize];
		m_pValues = new (std::nothrow)float[nSize];	
		if(!m_pValues || !m_p3DPoints)
		{
			Clear();
			return NG_GRID_NOMEMORY;
		}
		m_nSize = nSize;
		m_nPointsNum = 0;
		memset(m_p3DPoints, 0, sizeof(CDoublePoint)*nSize);
		memset(m_pValues, 0, sizeof(float)*nSize);
	}
	else
	{
		Reset();
	}

	return 0;
}

void GridResult::Reset()
{
	m_nPointsNum = 0;

	memset(m_p3DPoints, 0, sizeof(CDoublePoint)*m_nSize);
	memset(m_pValues, 0, sizeof(float)*m_nSize);
}

void GridResult::Clear()
{
	if(m_p3DPoints != NULL)
	{		
		delete []m_p3DPoints;
		m_p3DPoints = NULL;
	}
	if(m_pValues)
	{
		delete [] m_pValues;
	}

	m_nCoordSys = -1;
	m_nPointsNum = 0;
	m_nSize = 0;
}

int GridResult::SetPoint( int nIndex, CDoublePoint& point, float fValue )
{
	if(m_nSize > nIndex)
	{
		m_p3DPoints[nIndex] = point;
		m_pValues[nIndex] = fValue;

		if(nIndex >= m_nPointsNum)
		{
			m_nPointsNum = nIndex + 1;
		}
		return 0;
	}
	else
	{
		return NG_GRID_POSITION_NOTINBOUND;  //越界
	}
}

int GridResult::GetPoint( int nIndex, CDoublePoint& point, float& fValue )
{
	if(nIndex >= m_nPointsNum)
	{
		return NG_GRID_POSITION_NOTINBOUND;
	}
	else
	{
		point = m_p3DPoints[nIndex];
		fValue = m_pValues[nIndex];
		return 0;
	}
}

void GridResult::SwapData()
{
	for(int nIndex=0;nIndex<m_nPointsNum;nIndex++)
	{
		SWAP_DATA_ORDER(m_p3DPoints[nIndex].x);
		SWAP_DATA_ORDER(m_p3DPoints[nIndex].y);
		SWAP_DATA_ORDER(m_p3DPoints[nIndex].z);
		SWAP_DATA_ORDER(m_pValues[nIndex]);
	}
}

//将网格数据写入文件中
int GridResult::WriteToFile( const char* filename )
{
#ifdef USE_ZLIB
	ZipOfStream file(filename);
#else
	std::locale::global(std::locale(""));
	std::ofstream file(filename,std::ios_base::out | std::ios_base::binary);
	std::locale::global(std::locale("C"));
#endif
	if (!file.good())
		return NG_GRID_W_FILE_ERROR;
	bool bIsLE = IS_LittleEndian;
	try
	{
		int nTemp = m_nCoordSys;
		IF_SWAP_DTAT_ORDER(!bIsLE,nTemp);
		file.write((char*)&nTemp,sizeof(nTemp));
		//
		nTemp = m_nPointsNum;
		IF_SWAP_DTAT_ORDER(!bIsLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));
		if(!bIsLE)SwapData();
		for(int i=0; i<m_nPointsNum; i++)
		{
			file.write((char*)(&(m_p3DPoints[i])), sizeof(CDoublePoint));
			file.write((char*)(&(m_pValues[i])), sizeof(float));
		}	
		if(!bIsLE)SwapData();
	}
	catch (...)
	{
		return NG_GRID_W_FILE_ERROR;
	}
	return 0;
}

//从文件中读取网格数据
int GridResult::ReadFromFile( const char * filename )
{
#ifdef USE_ZLIB
	SearchIfStream file(filename, 0);
#else
	std::locale::global(std::locale(""));
	std::ifstream file(filename,std::ios_base::in | std::ios_base::binary);
	std::locale::global(std::locale("C"));
#endif
	if (!file.good())
		return NG_GRID_R_FILE_ERROR;
	bool bIsLE = IS_LittleEndian;
	try
	{
		int nPointsNum = 0;
		file.read((char*)&m_nCoordSys,sizeof(m_nCoordSys));
		IF_SWAP_DTAT_ORDER(!bIsLE,m_nCoordSys);

		file.read((char*)&nPointsNum, sizeof(nPointsNum));
		IF_SWAP_DTAT_ORDER(!bIsLE,nPointsNum);

		
		int nres = ReSize(nPointsNum);
		if(nres!=0)
			return nres;

		for(int i=0; i<nPointsNum; i++)
		{
			file.read((char*)(&(m_p3DPoints[i])), sizeof(CDoublePoint));
			file.read((char*)(&(m_pValues[i])), sizeof(float));
		}	
		m_nPointsNum = nPointsNum;
		if(!bIsLE)SwapData();
	}
	catch (...)
	{
		Clear();
		return NG_GRID_R_FILE_ERROR;
	}
	return 0;
}