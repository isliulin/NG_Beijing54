#include "Result3D.h"
#include <stdio.h>
#include <string.h>
#include "../StringManager/StringManager.h"
#include "../BasicDef/NG_ErrorCode.h"
#include <new>

#ifdef USE_ZLIB
#include "../HDFSFileWR/SearchIfStream.h"
#include "../HDFSFileWR/ZipOfStream.h"
#else
#include <fstream>
#endif
// 创建
Result3D* Result3D::Create()
{
	return new Result3D();
}

// 创建(包含空间大小)
Result3D* Result3D::Create( int nHorizonSize, int nVerticalSize )
{
	return new Result3D(nHorizonSize, nVerticalSize);
}

bool Result3D::Destroy( Result3D* pDestroy )
{
	if(pDestroy != NULL)
	{
		delete pDestroy;
		pDestroy = NULL;
	}

	return true;
}

Result3D::Result3D( int nHorizonSize, int nVerticalSize )
{
	m_nHorizonSize = nHorizonSize;
	m_nVerticalSize = nVerticalSize;
	 
	m_nHorPointsNum = 0;
	m_nVerPointsNum = 0;
	
	m_pp3DPoints = new CDoublePoint*[m_nHorizonSize];
	for(int i = 0; i<m_nHorizonSize; i++)
	{
		m_pp3DPoints[i] = new CDoublePoint[m_nVerticalSize];
		memset(m_pp3DPoints[i], 0, sizeof(CDoublePoint)*m_nVerticalSize);
	}	
}

Result3D::Result3D()
{
	m_nHorizonSize = 0;
	m_nVerticalSize = 0;

	m_nHorPointsNum = 0;
	m_nVerPointsNum = 0;

	m_pp3DPoints = NULL;
}

Result3D::~Result3D()
{
	Clear();
}

int Result3D::ReSize( int nHorizonSize, int nVerticalSize )
{
	//只要有一个方向的空间不满足要求，则重新申请
	if((m_nHorizonSize < nHorizonSize) || (m_nVerticalSize < nVerticalSize))
	{
		Clear();
		m_nHorizonSize = nHorizonSize;
		m_nVerticalSize = nVerticalSize;

		m_nHorPointsNum = 0;
		m_nVerPointsNum = 0;

		m_pp3DPoints = new (std::nothrow)CDoublePoint*[m_nHorizonSize];
		if(m_pp3DPoints == 0)
			return NG_3DR_NOMEMORY;
		bool memoryOK = true;
		for(int i = 0; i<m_nHorizonSize; i++)
		{
			m_pp3DPoints[i] = new (std::nothrow)CDoublePoint[m_nVerticalSize];
			if(m_pp3DPoints[i] == 0)
			{
				memoryOK = false;
				break;
			}
			memset(m_pp3DPoints[i], 0, sizeof(CDoublePoint)*m_nVerticalSize);
		}
		if(!memoryOK)
	{
			Clear();
			return NG_3DR_NOMEMORY;
	}

	}
	else
	{
		Reset();
	}
	return 0;
}

void Result3D::Reset()
{
	m_nHorPointsNum = 0;
	m_nVerPointsNum = 0;

	for(int i = 0; i<m_nHorizonSize; i++)
	{			
		memset(m_pp3DPoints[i], 0, sizeof(CDoublePoint)*m_nVerticalSize);
	}
}

void Result3D::Clear()
{
	if(m_pp3DPoints != NULL)
	{
		for(int i=0; i<m_nHorizonSize; i++)
		{
			if(m_pp3DPoints[i])
			delete []m_pp3DPoints[i];
			m_pp3DPoints[i] = NULL;
		}
		delete []m_pp3DPoints;
		m_pp3DPoints = NULL;
	}
	
	m_nHorizonSize = 0;
	m_nVerticalSize = 0;
	m_nHorPointsNum = 0;
	m_nVerPointsNum = 0;	
}

int Result3D::SetPoint( int nHorIndex, int nVerIndex, CDoublePoint& point )
{
	//如果设置的索引位置超出存储空间的范围，则直接返回错误
	if((nHorIndex >= m_nHorizonSize) || (nVerIndex >= m_nVerticalSize))
	{
		return NG_3DR_POSITION_NOTINBOUND;
	}
	
	m_pp3DPoints[nHorIndex][nVerIndex] = point;	

	//设置点的个数的值
	if(nHorIndex >= m_nHorPointsNum)
	{
		m_nHorPointsNum = nHorIndex + 1;
	}
	
	if(nVerIndex >= m_nVerPointsNum)
	{
		m_nVerPointsNum = nVerIndex + 1;
	}

	return 0;
}

int Result3D::GetPoint( int nHorIndex, int nVerIndex, CDoublePoint& point)
{
	if( (nHorIndex >= m_nHorizonSize) || (nVerIndex >= m_nVerticalSize) )
	{
		return NG_LINE_POSITION_NOTINBOUND;		
	}	
	else
	{
		point = m_pp3DPoints[nHorIndex][nVerIndex];		
		return 0;
	}
}

void Result3D::Size( int& nHorizonSize, int& nVerticalSize )
{
	nHorizonSize = m_nHorizonSize;
	nVerticalSize = m_nVerticalSize;
}

void Result3D::GetPointsNum( int& nHorPointsNum, int& nVerPointsNum )
{
	nHorPointsNum = m_nHorPointsNum;
	nVerPointsNum = m_nVerPointsNum;
}

void Result3D::SwapData()
{
		for(int iH=0;iH<m_nHorPointsNum;iH++)
		{
			for(int iV=0;iV<m_nVerPointsNum;iV++)
			{
				SWAP_DATA_ORDER(m_pp3DPoints[iH][iV].x);
				SWAP_DATA_ORDER(m_pp3DPoints[iH][iV].y);
				SWAP_DATA_ORDER(m_pp3DPoints[iH][iV].z);
			}
		}
}

int Result3D::WriteToFile( const char* filename )
{
#ifdef USE_ZLIB
	ZipOfStream file(filename);
#else
	std::locale::global(std::locale(""));
	std::ofstream file(filename,std::ios_base::out | std::ios_base::binary);
	std::locale::global(std::locale("C"));
#endif
	if (!file.good())
		return NG_3DR_W_FILE_ERROR;
	if(!m_pp3DPoints)
		return NG_3DR_W_NODATA;
	bool bIsLE =IS_LittleEndian;
	try
	{
		int nTemp = m_nCoordSys;
		IF_SWAP_DTAT_ORDER(!bIsLE,nTemp);
		file.write((char*)&nTemp,sizeof(nTemp));
		//
		nTemp = m_nHStartAngle;
		IF_SWAP_DTAT_ORDER(!bIsLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));
		//
		nTemp = m_nHEndAngle;
		IF_SWAP_DTAT_ORDER(!bIsLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));
		//
		nTemp = m_nVStartAngle;
		IF_SWAP_DTAT_ORDER(!bIsLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));

		//
		nTemp = m_nVEndAngle;
		IF_SWAP_DTAT_ORDER(!bIsLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));

		//
		nTemp = m_nHStep;
		IF_SWAP_DTAT_ORDER(!bIsLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));

		//
		nTemp = m_nVStep;
		IF_SWAP_DTAT_ORDER(!bIsLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));

		//
		nTemp = m_nHorPointsNum;
		IF_SWAP_DTAT_ORDER(!bIsLE,nTemp);
		file.write((char*)&nTemp,sizeof(nTemp));

		//
		nTemp=m_nVerPointsNum;
		IF_SWAP_DTAT_ORDER(!bIsLE,nTemp);
		file.write((char*)&nTemp,sizeof(nTemp));
		
		if(!bIsLE)SwapData();
		for(int iH=0;iH<m_nHorPointsNum;iH++)
		{
			file.write((char*)m_pp3DPoints[iH], 
				sizeof(CDoublePoint)*m_nVerPointsNum);
		}
		if(!bIsLE)SwapData();
	}
	catch (...)
	{
		return NG_3DR_W_FILE_ERROR;
	}
	return 0;
}

int Result3D::ReadFromFile( const char * filename )
{
#ifdef USE_ZLIB
	SearchIfStream file(filename, 0);
#else
	std::locale::global(std::locale(""));
	std::ifstream file(filename,std::ios_base::in | std::ios_base::binary);
	std::locale::global(std::locale("C"));
#endif
	if (!file.good())
		return NG_3DR_R_FILE_ERROR;
	bool bIsLE = IS_LittleEndian;
	try
	{
		file.read((char*)&m_nCoordSys,sizeof(m_nCoordSys));
		IF_SWAP_DTAT_ORDER(!bIsLE,m_nCoordSys);

		file.read((char*)&m_nHStartAngle, sizeof(m_nHStartAngle));
		IF_SWAP_DTAT_ORDER(!bIsLE,m_nHStartAngle);

		file.read((char*)&m_nHEndAngle, sizeof(m_nHEndAngle));
		IF_SWAP_DTAT_ORDER(!bIsLE,m_nHEndAngle);

		file.read((char*)&m_nVStartAngle, sizeof(m_nVStartAngle));
		IF_SWAP_DTAT_ORDER(!bIsLE,m_nVStartAngle);

		file.read((char*)&m_nVEndAngle, sizeof(m_nVEndAngle));
		IF_SWAP_DTAT_ORDER(!bIsLE,m_nVEndAngle);

		file.read((char*)&m_nHStep, sizeof(m_nHStep));
		IF_SWAP_DTAT_ORDER(!bIsLE,m_nHStep);

		file.read((char*)&m_nVStep, sizeof(m_nVStep));
		IF_SWAP_DTAT_ORDER(!bIsLE,m_nVStep);

		int nH,nV;
		file.read((char*)&nH,sizeof(nH));
		IF_SWAP_DTAT_ORDER(!bIsLE,nH);

		file.read((char*)&nV,sizeof(nV));
		IF_SWAP_DTAT_ORDER(!bIsLE,nV);

		Clear();
		int nres = ReSize(nH,nV);
		if(0!=nres)
			return nres;
		for(int iH=0;iH<nH;iH++)
		{
			file.read((char*)m_pp3DPoints[iH],
				sizeof(CDoublePoint)*nV);
		}
		m_nHorPointsNum = nH;
		m_nVerPointsNum = nV;
		if((m_nHorPointsNum>m_nHorizonSize)||
			(m_nVerPointsNum>m_nVerticalSize))
		{
			Clear();
			return NG_3DR_R_FILE_ERROR;
		}
		//
		if(!bIsLE)SwapData();
	}
	catch (...)
	{
		Clear();
		return NG_3DR_R_FILE_ERROR;
	}
	return 0;
}

void Result3D::SetAngle( int nHStartAngle, int nHEndAngle, int nVStartAngle, int nVEndAngle, int nHStep, int nVStep )
{
	m_nHStartAngle = nHStartAngle;
	m_nHEndAngle = nHEndAngle;

	m_nVStartAngle = nVStartAngle;
	m_nVEndAngle = nVEndAngle;

	m_nHStep = nHStep;
	m_nVStep = nVStep;
}

void Result3D::GetAngle( int& nHStartAngle, int& nHEndAngle, int& nVStartAngle, int& nVEndAngle, int& nHStep, int& nVStep )
{
	nHStartAngle = m_nHStartAngle;
	nHEndAngle = m_nHEndAngle;
	nVStartAngle = m_nVStartAngle;
	nVEndAngle = m_nVEndAngle;

	nHStep = m_nHStep;
	nVStep = m_nVStep;
}