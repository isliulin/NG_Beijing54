#include <stdio.h>
#include <string.h>
#include <float.h>

#include "GeoShape.h"

CGeoPolygon::CGeoPolygon()
{
	m_nCoordSys = 0;
	m_nPointsNum = 0;
	m_nSize = 0;
	m_pPointData = NULL;
}

CGeoPolygon::~CGeoPolygon()
{
	ReleaseData();
}

CGeoPolygon::CGeoPolygon(int nPointNum)
{
	m_nCoordSys = 0;
	m_nSize = nPointNum;
	m_nPointsNum = nPointNum;

	m_pPointData = new CDoublePoint[m_nSize];
	memset(m_pPointData, 0, sizeof(CDoublePoint)*m_nSize);
}

CGeoPolygon::CGeoPolygon( CGeoPolygon& polygon )
{
	m_nCoordSys = polygon.m_nCoordSys;
	m_bClosed = polygon.m_bClosed;

	if(polygon.m_nSize != 0)
	{
		m_pPointData = new CDoublePoint[polygon.m_nSize];

		m_nSize = polygon.m_nSize;
		m_nPointsNum = polygon.m_nPointsNum;

		memcpy(m_pPointData, polygon.m_pPointData, sizeof(CDoublePoint)*polygon.m_nSize);
	}
	else
	{
		m_pPointData = NULL;
		m_nSize = 0;
		m_nPointsNum = 0;
	}
}
//���������С
bool CGeoPolygon::Resize(int nSize)
{
	if(m_nSize < nSize)
	{
		ReleaseData();

		m_nSize = nSize;

		m_nPointsNum = 0;
		try
		{
			m_pPointData = new CDoublePoint[m_nSize];

			if(m_pPointData == NULL)
			{
				throw "no memory";
			}
			else
			{
				memset(m_pPointData, 0, sizeof(CDoublePoint)*m_nSize);
			}
		}
		catch (...)
		{
			if(m_pPointData != NULL)
			{
				delete []m_pPointData;
				m_pPointData = NULL;
			}

			return false;
		}

		return true;
	}
	else
	{
		return true;
	}
}

//��0
void CGeoPolygon::Reset()
{
	if(m_nSize != 0)
	{
		memset(m_pPointData, 0, sizeof(CDoublePoint)*m_nSize);
		m_nPointsNum = 0;
	}
}

//�ͷſռ�
void CGeoPolygon::ReleaseData()
{
	if(m_nSize != 0)
	{
		delete []m_pPointData;
		m_pPointData = NULL;

		m_nPointsNum = 0;
		m_nSize = 0;
	}
}

//��������أ� ��ֵ����
CGeoPolygon& CGeoPolygon::operator=( CGeoPolygon& polygon )
{
	if(m_nSize != 0)
	{
		ReleaseData();
	}
	m_nCoordSys = polygon.m_nCoordSys;
	m_bClosed = polygon.m_bClosed;

	if(polygon.m_nSize != 0)
	{
		m_pPointData = new CDoublePoint[polygon.m_nSize];

		m_nSize = polygon.m_nSize;
		m_nPointsNum = polygon.m_nPointsNum;

		memcpy(m_pPointData, polygon.m_pPointData, sizeof(CDoublePoint)*polygon.m_nSize);
	}
	else
	{
		m_pPointData = NULL;
		m_nSize = 0;
		m_nPointsNum = 0;
	}

	return *this;
}

//�������д���ļ�
bool CGeoPolygon::WriteToFile( const char* filename )
{
	//���ļ�
	FILE* file = NULL;
	if(file==fopen( filename, "wb"))
	{
		//�ļ��򿪳ɹ�  --д����
		//д���Ƿ��յı�ʶ
		fwrite(&m_bClosed, sizeof(m_bClosed), 1, file);

		//д���ĸ���
		fwrite(&m_nPointsNum, sizeof(m_nPointsNum), 1, file);

		//д������ϵ���
		fwrite(&m_nCoordSys, sizeof(m_nCoordSys), 1, file);

		//�����еĵ�д��
		fwrite(m_pPointData, sizeof(CDoublePoint), m_nPointsNum, file);

		//�ر��ļ�
		fclose(file);

		return true;
	}
	return false;
}

bool CGeoPolygon::ReadFromFile( const char * filename )
{
	//���ļ�
	FILE* file = NULL;
	if(file==fopen(filename, "rb"))
	{
		//��ȡ�Ƿ��յı�ʶ
		fread(&m_bClosed, sizeof(m_bClosed), 1, file);

		//��ȡ��ĸ���
		fread(&m_nPointsNum, sizeof(m_nPointsNum), 1, file);

		//��ȡ����ϵ���
		fread(&m_nCoordSys, sizeof(m_nCoordSys), 1, file);

		if(m_nSize < m_nPointsNum)
		{
			int nPointsNum = m_nPointsNum;

			//���ݵ�ĸ�����������ռ�
			Resize(m_nPointsNum);

			m_nPointsNum = nPointsNum;
		}

		//��ȡ���еĵ�
		fread(m_pPointData, sizeof(CDoublePoint), m_nPointsNum, file);

		//�ر��ļ�
		fclose(file);

		return true;
	}
	return false;
}
