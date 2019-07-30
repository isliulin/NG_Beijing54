#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include "INGMapGeo.h"

using namespace std;

NGProfile::NGProfile()
{
	nSize = 0;
	nPointsNum = 0;				//剖面线上点的个数
	pImgCoordX = NULL;			//剖面线上点的坐标
	pImgCoordY = NULL;
	pImgData = NULL;		//数据值
	pDistance = NULL;			
}

NGProfile::~NGProfile()
{
	Clear();
}
void NGProfile::Reset()
{
	if(nSize != 0)
	{
		nPointsNum = 0;
		memset(pImgCoordX, 0, sizeof(long)*nSize);
		memset(pImgCoordY, 0, sizeof(long)*nSize);
		memset(pImgData, 0, sizeof(short)*nSize);
		memset(pDistance, 0, sizeof(double)*nSize);
	}
}

bool NGProfile::Resize(int nSize)
{
	//添加内存申请size判断，超过1M，不予计算 add xiangl
	if (nSize>=1048576)
		return false;

	Clear();

	try{
		if(nSize != 0)
		{
			this->nSize = nSize + 1;
			this->nPointsNum = 0;
			pImgCoordX = new long[this->nSize];
			memset(pImgCoordX, 0, sizeof(long)*(this->nSize));

			pImgCoordY = new long[this->nSize];
			memset(pImgCoordY, 0, sizeof(long)*(this->nSize));

			pImgData = new short[this->nSize];
			memset(pImgData, 0, sizeof(short)*(this->nSize));

			pDistance = new double[this->nSize];
			memset(pDistance, 0, sizeof(double)*(this->nSize));
		}
	}catch(std::bad_alloc){
		return false;
	}
	return true;
}

void NGProfile::Clear()
{
	if(nSize != 0)
	{
		if (pImgCoordX != NULL)
		{
			delete []pImgCoordX;
			pImgCoordX = NULL;
		}

		if (pImgCoordY != NULL)
		{
			delete []pImgCoordY;
			pImgCoordY = NULL;
		}

		if (pImgData != NULL)
		{
			delete []pImgData;
			pImgData = NULL;
		}

		if (pDistance != NULL)
		{
			delete []pDistance;
			pDistance = NULL;
		}
		nSize = 0;
		nPointsNum = 0;
	}

}

INGMapGeo::INGMapGeo()
{
}

INGMapGeo::~INGMapGeo()
{
}

//金字塔地图
IPyramidMapGeo::IPyramidMapGeo()
{

}

IPyramidMapGeo::~IPyramidMapGeo()
{

}

double IPyramidMapGeo::Get_Layer_ResolutionX(unsigned int lay)
{
	double r0_x = Get_Layer0_ResolutionX();
	if (lay > 0)
	{
		unsigned int d = 2<<lay;
		r0_x *= d;
	}

	return r0_x;
}

double IPyramidMapGeo::Get_Layer_ResolutionY(unsigned int lay)
{
	double r0_y = Get_Layer0_ResolutionY();
	if (lay > 0)
	{
		unsigned int d = 2<<lay;
		r0_y *= d;
	}

	return r0_y;
}

