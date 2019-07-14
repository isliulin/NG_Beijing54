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
//重新申请大小
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

//清0
void CGeoPolygon::Reset()
{
	if(m_nSize != 0)
	{
		memset(m_pPointData, 0, sizeof(CDoublePoint)*m_nSize);
		m_nPointsNum = 0;
	}
}

//释放空间
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

//运算符重载： 赋值函数
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

//将多边形写入文件
bool CGeoPolygon::WriteToFile( const char* filename )
{
	//打开文件
	FILE* file = NULL;
	if(file==fopen( filename, "wb"))
	{
		//文件打开成功  --写数据
		//写入是否封闭的标识
		fwrite(&m_bClosed, sizeof(m_bClosed), 1, file);

		//写入点的个数
		fwrite(&m_nPointsNum, sizeof(m_nPointsNum), 1, file);

		//写入坐标系编号
		fwrite(&m_nCoordSys, sizeof(m_nCoordSys), 1, file);

		//将所有的点写入
		fwrite(m_pPointData, sizeof(CDoublePoint), m_nPointsNum, file);

		//关闭文件
		fclose(file);

		return true;
	}
	return false;
}

bool CGeoPolygon::ReadFromFile( const char * filename )
{
	//打开文件
	FILE* file = NULL;
	if(file==fopen(filename, "rb"))
	{
		//读取是否封闭的标识
		fread(&m_bClosed, sizeof(m_bClosed), 1, file);

		//读取点的个数
		fread(&m_nPointsNum, sizeof(m_nPointsNum), 1, file);

		//读取坐标系编号
		fread(&m_nCoordSys, sizeof(m_nCoordSys), 1, file);

		if(m_nSize < m_nPointsNum)
		{
			int nPointsNum = m_nPointsNum;

			//根据点的个数重新申请空间
			Resize(m_nPointsNum);

			m_nPointsNum = nPointsNum;
		}

		//读取所有的点
		fread(m_pPointData, sizeof(CDoublePoint), m_nPointsNum, file);

		//关闭文件
		fclose(file);

		return true;
	}
	return false;
}
