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

	//�ý��������Ĭ��ֵΪdb
	m_eDataUnit = CRUNIT_DB;
}

LineResult::~LineResult()
{
	Clear();	
}

//���������С
int LineResult::ReSize(int nSize)
{
	if(m_nSize < nSize)
	{
		//���ԭ���Ŀռ�
		Clear();

		//�����µĴ洢�ռ�
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

//�ռ�����
void LineResult::Reset()
{
	m_nNoPoints = 0;

	memset(m_pPointList, 0, sizeof(CDoublePoint)*(m_nSize));
	memset(m_pValueList, 0, sizeof(float)*(m_nSize));
}

//����ռ�
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

// ����
LineResult* LineResult::Create()
{
	return new LineResult();
}

// ����(�����ռ��С)
LineResult* LineResult::Create(int inSize)
{
	return new LineResult(inSize);
}

// ����
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

		//1.դ��λ
		file.read((char*)&nTemp, sizeof(nTemp));
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		m_eDataUnit = (CalResult_Unit)nTemp;

		//2.����ϵ���
		//Linux�� Windows�� long ��С��һ��,����ʹ��int
		file.read((char*)&nTemp, sizeof(nTemp));
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		m_nCoordSys = nTemp;

		//3.������
		
		file.read((char*)&nTemp, sizeof(nTemp));
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		int nres = ReSize(nTemp);
		if(0!=nres)
			return nres;
		m_nNoPoints = nTemp;

		//4.��Ӧ����ֵ
		file.read((char*)(void*)m_pPointList,sizeof(CDoublePoint)*m_nNoPoints);
		//5.��Ӧ���ֵ
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

		//1.դ��λ
		nTemp = m_eDataUnit;
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));


		//2.����ϵ���
		//Linux�� Windows�� long ��С��һ��,����ʹ��int
		nTemp = m_nCoordSys;
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));

		//3.������
		nTemp = m_nNoPoints;
		IF_SWAP_DTAT_ORDER(!isLE,nTemp);
		file.write((char*)&nTemp, sizeof(nTemp));
		
		//��������
		if(!isLE)SwapData();
		//4.��Ӧ����ֵ
		file.write((char*)(void*)m_pPointList,sizeof(CDoublePoint)*m_nNoPoints);
		//5.��Ӧ���ֵ
		file.write((char*)(void*)m_pValueList,sizeof(float)*m_nNoPoints);
		//��������ݽ�������
		if(!isLE)SwapData();
		return 0;
	}
	catch (...)
	{
		return NG_LINE_W_FILE_ERROR;
	}
}
