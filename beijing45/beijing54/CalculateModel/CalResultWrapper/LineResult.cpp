#include "LineResult.h"
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

LineResult::LineResult(long nSize)
{
	m_nSize = nSize;
	m_nNoPoints = 0;

	m_pPointList = new CDoublePoint[nSize];
	m_pValueList = new float[nSize];

	memset(m_pPointList, 0, sizeof(CDoublePoint)*(m_nSize));
	memset(m_pValueList, 0, sizeof(float)*(m_nSize));	
}

LineResult::LineResult()
{
	m_nSize = 0;
	m_nNoPoints = 0;

	m_pPointList = NULL;
	m_pValueList = NULL;

	//置结果的类别的默认值为db
	m_eDataUnit = CRUNIT_DB;
}

LineResult::~LineResult()
{
	Clear();	
}

//重新申请大小
int LineResult::ReSize(int nSize)
{
	if(m_nSize < nSize)
	{
		//清除原来的空间
		Clear();

		//申请新的存储空间
		m_pPointList = new(std::nothrow) CDoublePoint[nSize];
		m_pValueList = new(std::nothrow) float[nSize];

		if((m_pPointList != NULL) && (m_pValueList != NULL))
		{
			memset(m_pPointList, 0, sizeof(CDoublePoint)*(m_nSize));
			memset(m_pValueList, 0, sizeof(float)*(m_nSize));	

			m_nSize = nSize;
			return 0;
		}
		else
		{
			if(m_pPointList != NULL)
			{
				delete []m_pPointList;
				m_pPointList = NULL;
			}
			else if(m_pValueList != NULL)
			{		
				delete []m_pValueList;
				m_pValueList = NULL;
			}

			return NG_LINE_NOMEMORY;
		}		
	}

	return 0;
}

//空间重置
void LineResult::Reset()
{
	m_nNoPoints = 0;

	memset(m_pPointList, 0, sizeof(CDoublePoint)*(m_nSize));
	memset(m_pValueList, 0, sizeof(float)*(m_nSize));
}

//清理空间
void LineResult::Clear()
{
	if(m_pPointList != NULL)
	{
		delete []m_pPointList;
		m_pPointList = NULL;
	}
	if(m_pValueList != NULL)
	{
		delete []m_pValueList;
		m_pValueList = NULL;
	}

	m_nSize = 0;
	m_nNoPoints = 0;
}

// 创建
LineResult* LineResult::Create()
{
	return new LineResult();
}

// 创建(包含空间大小)
LineResult* LineResult::Create(int inSize)
{
	return new LineResult(inSize);
}

// 销毁
bool LineResult::Destroy(LineResult* pDestroy)
{
	if (NULL != pDestroy)
	{
		delete pDestroy;
		pDestroy = NULL;
	}
	return true;
}

int LineResult::SetPointValue( int index, CDoublePoint& point, float value )
{
	if(index >= m_nSize)
	{
		return NG_LINE_POSITION_NOTINBOUND;
	}
	m_pPointList[index] = point;
	m_pValueList[index] = value;

	if(index >= m_nNoPoints)
	{
		m_nNoPoints = index+1;
	}	

	return true;
}

int LineResult::GetPointValue( int index, CDoublePoint& point, float& value )
{
	if(index >= m_nNoPoints)
	{
		return NG_LINE_POSITION_NOTINBOUND;
	}
	else
	{
		point = m_pPointList[index];
		value = m_pValueList[index];
		return 0;
	}
}

void LineResult::SwapData()
{
	for(long index=0;index<m_nNoPoints;index++)
	{
		SWAP_DATA_ORDER(m_pPointList[index].x);
		SWAP_DATA_ORDER(m_pPointList[index].y);
		SWAP_DATA_ORDER(m_pPointList[index].z);
		SWAP_DATA_ORDER(m_pValueList[index]);
	}
}

int LineResult::ReadFromFile( const char * filename )
{
#ifdef USE_ZLIB
	SearchIfStream file(filename, 0);
#else
	std::locale::global(std::locale(""));
	std::ifstream file(filename,std::ios_base::in | std::ios_base::binary);
	std::locale::global(std::locale("C"));
#endif
	if (!file.good())
		return NG_LINE_R_FILE_ERROR;
	bool isLE = IS_LittleEndian;
	try
	{
		int nTemp = 0;

		//1.栅格单位
		file.read((char*)&nTemp, sizeof(nTemp));
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		m_eDataUnit = (CalResult_Unit)nTemp;

		//2.坐标系编号
		//Linux和 Windows下 long 大小不一样,这里使用int
		file.read((char*)&nTemp, sizeof(nTemp));
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		m_nCoordSys = nTemp;

		//3.数据量
		
		file.read((char*)&nTemp, sizeof(nTemp));
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		int nres = ReSize(nTemp);
		if(0!=nres)
			return nres;
		m_nNoPoints = nTemp;

		//4.对应坐标值
		file.read((char*)(void*)m_pPointList,sizeof(CDoublePoint)*m_nNoPoints);
		//5.对应结果值
		file.read((char*)(void*)m_pValueList,sizeof(float)*m_nNoPoints);
		
		if(!isLE)SwapData();
	}
	catch (...)
	{
		Clear();
		return NG_LINE_R_FILE_ERROR;
	}
	return 0;
}

int LineResult::WriteToFile( const char* filename )
{
	#ifdef USE_ZLIB
		ZipOfStream file(filename);
	#else
	std::locale::global(std::locale(""));
	std::ofstream file(filename,std::ios_base::out | std::ios_base::binary);
	std::locale::global(std::locale("C"));
	#endif
	if (!file.good())
		return NG_LINE_W_FILE_ERROR;

	bool isLE = IS_LittleEndian;
	try
	{
		int nTemp = 0;

		//1.栅格单位
		nTemp = m_eDataUnit;
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));


		//2.坐标系编号
		//Linux和 Windows下 long 大小不一样,这里使用int
		nTemp = m_nCoordSys;
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));

		//3.数据量
		nTemp = m_nNoPoints;
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));
		
		//交换数据
		if(!isLE)SwapData();
		//4.对应坐标值
		file.write((char*)(void*)m_pPointList,sizeof(CDoublePoint)*m_nNoPoints);
		//5.对应结果值
		file.write((char*)(void*)m_pValueList,sizeof(float)*m_nNoPoints);
		//将结果数据交换回来
		if(!isLE)SwapData();
		return 0;
	}
	catch (...)
	{
		return NG_LINE_W_FILE_ERROR;
	}
}
