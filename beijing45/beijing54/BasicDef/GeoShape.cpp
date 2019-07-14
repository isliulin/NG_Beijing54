#include <stdio.h>
#include <string.h>
#include <float.h>
#include <iostream>
#include <vector>

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

bool CGeoPolygon::ReadFromTxtFile( const char *filename )
{
	//打开文件
	FILE* file = NULL;

	/*if(file=fopen(filename, "rb"))
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
	}*/

	if(file=fopen(filename, "r"))
	{
		int tempi;
		double tempf1, tempf2;

		//读取是否封闭的标识
		fscanf(file, "%d\n", &tempi);
		m_bClosed = tempi;

		//读取点的个数
		fscanf(file, "%d\n", &tempi);
		m_nPointsNum = tempi;

		//读取坐标系编号
		fscanf(file, "%d\n", &tempi);
		m_nCoordSys = tempi;

		if(m_nSize < m_nPointsNum)
		{
			int nPointsNum = m_nPointsNum;

			//根据点的个数重新申请空间
			Resize(m_nPointsNum);

			m_nPointsNum = nPointsNum;
		}

		//读取所有的点
		for (int i = 0; i < m_nPointsNum; i++)
		{
			fscanf(file, "%lf, %lf\n", &tempf1, &tempf2);
			m_pPointData[i].x = tempf1;
			m_pPointData[i].y = tempf2;
		}

		//关闭文件
		fclose(file);

		return true;
	}

	return false;
}


bool CGeoPolygon::ReadFromStream( std::istream &instream  )
{
	//打开文件
	if(instream)
	{
		int tempi;
		double tempf1, tempf2;
		char tempc;

		/*//读取是否封闭的标识
		instream >> tempi >> tempc;
		m_bClosed = tempi;

		//读取点的个数
		instream >> tempi >> tempc;
		m_nPointsNum = tempi;

		//读取坐标系编号
		instream >> tempi >> tempc;
		m_nCoordSys = tempi;*/
		m_bClosed = 1;
		m_nCoordSys = 103;
		m_nPointsNum = 0;

		std::vector<double> longitudes, latitudes;
		instream >> tempc;
		//读取所有的点
		while (true)
		{
			instream >> tempc;
			if (tempc != '[' || instream.eof())
			{
				break;
			}

			instream >> tempf1 >> tempc >> tempf2 >> tempc;

			latitudes.push_back(tempf1);
			longitudes.push_back(tempf2);

			instream >> tempc;
		}

		m_nPointsNum = latitudes.size() + 1;

		if(m_nSize < m_nPointsNum)
		{
			int nPointsNum = m_nPointsNum;

			//根据点的个数重新申请空间
			Resize(m_nPointsNum);

			m_nPointsNum = nPointsNum;
		}

		for (int i = 0; i < m_nPointsNum - 1; i++)
		{
			m_pPointData[i].x = longitudes[i];
			m_pPointData[i].y = latitudes[i];
		}
		m_pPointData[m_nPointsNum-1].x = longitudes[0];
		m_pPointData[m_nPointsNum-1].y = latitudes[0];

		return true;
	}

	return false;
}


bool CGeoPolygon::ReadFromFile( const char * filename )
{
	//打开文件
	FILE* file = NULL;

	if(file=fopen(filename, "rb"))
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