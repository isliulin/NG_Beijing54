#include <string.h>
#include <vector>
#include "CalGisProfile.h"
#include "../BasicDef/MacroDef.h"

CalGis_Profile::CalGis_Profile(long nSize)
{
	noPoints = 0;
	nSize = 0;

	xIndex = NULL;
	yIndex = NULL;

	xPathCoord = NULL;
	yPathCoord = NULL;

	distance = NULL;
	height = NULL;

	building = NULL;
	clutter = NULL;

	adaptedHeight = NULL;
	conductivity = NULL;

	lineOfSight = NULL;

	xStart = 0.0;
	yStart = 0.0;
	xEnd = 0.0;
	yEnd = 0.0;
	
	refractionIndex0m = NULL;
	refractionIndex1km = NULL;
	fieldSth = NULL;
	gerechnet = NULL;
	RainRate = NULL;
	diffLoss = NULL;

	ReSize(nSize);
}

CalGis_Profile::CalGis_Profile()
{
	noPoints = 0;
	nSize = 0;

	xIndex = NULL;
	yIndex = NULL;

	xPathCoord = NULL;
	yPathCoord = NULL;

	distance = NULL;
	height = NULL;

	building = NULL;
	clutter = NULL;

	adaptedHeight = NULL;
	conductivity = NULL;

	lineOfSight = NULL;

	xStart = 0.0;
	yStart = 0.0;
	xEnd = 0.0;
	yEnd = 0.0;

	refractionIndex0m = NULL;
	refractionIndex1km = NULL;
	fieldSth = NULL;
	gerechnet = NULL;
	RainRate = NULL;
	diffLoss = NULL;
	//RainRate = NULL;
}

CalGis_Profile::~CalGis_Profile()
{
	Clear();	
}

//重新申请大小
bool CalGis_Profile::ReSize(int nSize)
{
	//清除原来的空间
	Clear();

	//重新申请空间
	this->nSize = nSize+1;
	noPoints = 0;
	if(this->nSize<=0)	
	{
		this->nSize=0;
		return false;
	}
	//
	try
	{
		xIndex = new long[this->nSize];
		yIndex = new long[this->nSize];

		xPathCoord = new double[this->nSize];
		yPathCoord = new double[this->nSize];

		distance = new double[this->nSize];
		height = new double[this->nSize];

		building = new double[this->nSize];
		clutter = new short[this->nSize];

		adaptedHeight = new double[this->nSize];
		conductivity = new double[this->nSize]; 

		lineOfSight = new double[this->nSize]; 

	refractionIndex0m = new double[this->nSize];
	refractionIndex1km = new double[this->nSize];

	fieldSth = new double[this->nSize];
	gerechnet = new short[this->nSize];

	RainRate = new double[this->nSize];
	diffLoss = new double[this->nSize];
	}
	catch(...){
		return false;
	}
	

	memset(xIndex, 0, sizeof(long)*(this->nSize));
	memset(yIndex, 0, sizeof(long)*(this->nSize));

	memset(xPathCoord, 0, sizeof(double)*(this->nSize));
	memset(yPathCoord, 0, sizeof(double)*(this->nSize));

	memset(distance, 0, sizeof(double)*(this->nSize));
	memset(height, 0, sizeof(double)*(this->nSize));

	memset(building, 0, sizeof(double)*(this->nSize));
	memset(clutter, 0, sizeof(short)*(this->nSize));

	memset(adaptedHeight, 0, sizeof(double)*(this->nSize));
	memset(conductivity, 0, sizeof(double)*(this->nSize));

	memset(lineOfSight, 0, sizeof(double)*(this->nSize));

	memset(refractionIndex0m, 0, sizeof(double)*(this->nSize));
	memset(refractionIndex1km, 0, sizeof(double)*(this->nSize));
	
	memset(fieldSth, 0, sizeof(double)*(this->nSize));
	memset(gerechnet, 0, sizeof(short)*(this->nSize));

	memset(RainRate, 0, sizeof(double)*(this->nSize));
	memset(diffLoss, 0, sizeof(double)*(this->nSize));

   //memset(RainRate, 0, sizeof(double)*(this->nSize));



	//目前先暂时直接返回true，回头需要根据申请的情况返回
	return true;
}

//空间重置
void CalGis_Profile::Reset()
{
	noPoints = 0;
	if(xIndex)
		memset(xIndex, 0, sizeof(long)*(this->nSize));
	if(yIndex)
		memset(yIndex, 0, sizeof(long)*(this->nSize));
	if(xPathCoord)
		memset(xPathCoord, 0, sizeof(double)*(this->nSize));
	if(yPathCoord)
		memset(yPathCoord, 0, sizeof(double)*(this->nSize));
	if(distance)
		memset(distance, 0, sizeof(double)*(this->nSize));
	if(height)
		memset(height, 0, sizeof(double)*(this->nSize));
	if(building)
		memset(building, 0, sizeof(double)*(this->nSize));
	if(clutter)
		memset(clutter, 0, sizeof(short)*(this->nSize));
	if(adaptedHeight)
		memset(adaptedHeight, 0, sizeof(double)*(this->nSize));
	if(conductivity)
		memset(conductivity, 0, sizeof(double)*(this->nSize));
	if(lineOfSight)
		memset(lineOfSight, 0, sizeof(double)*(this->nSize));

	if(refractionIndex0m != NULL)
		memset(refractionIndex0m, 0, sizeof(double)*(this->nSize));
	if(refractionIndex1km != NULL)
		memset(refractionIndex1km, 0, sizeof(double)*(this->nSize));

	if(fieldSth != NULL)
		memset(fieldSth, 0, sizeof(double)*(this->nSize));
	if(gerechnet != NULL)
		memset(gerechnet, 0, sizeof(short)*(this->nSize));

	if(RainRate != NULL)
		memset(RainRate, 0, sizeof(double)*(this->nSize));
	if(diffLoss != NULL)
		memset(diffLoss, 0, sizeof(double)*(this->nSize));

	//if(RainRate)
	//	memset(RainRate, 0, sizeof(double)*(this->nSize));
}

//清理空间
void CalGis_Profile::Clear()
{
	if(xIndex != NULL)
	{
		delete []xIndex;
		xIndex = NULL;
	}
	if(yIndex != NULL)
	{
		delete []yIndex;
		yIndex = NULL;
	}

	if(xPathCoord != NULL)
	{
		delete[]xPathCoord;
		xPathCoord = NULL;
	}
	if(yPathCoord != NULL)
	{
		delete []yPathCoord;
		yPathCoord = NULL;
	}

	if(distance != NULL)
	{
		delete []distance;
		distance = NULL;
	}
	if(height != NULL)
	{
		delete []height;
		height = NULL;
	}

	if(building != NULL)
	{
		delete []building;
		building = NULL;
	}	
	if(clutter != NULL)
	{
		delete []clutter;
		clutter = NULL;
	}		

	if(adaptedHeight!=NULL)
	{
		delete []adaptedHeight;
		adaptedHeight = NULL;
	}

	if(conductivity != NULL)
	{
		delete []conductivity;
		conductivity = NULL;
	}

	if(lineOfSight != NULL)
	{
		delete []lineOfSight;
		lineOfSight = NULL;
	}

	if(refractionIndex0m != NULL)
	{
		delete []refractionIndex0m;
		refractionIndex0m = NULL;
	}

	if(refractionIndex1km != NULL)
	{
		delete []refractionIndex1km;
		refractionIndex1km = NULL;
	}

	if(fieldSth != NULL)
	{
		delete []fieldSth;
		fieldSth = NULL;
	}
	if(gerechnet!=NULL)
	{
		delete []gerechnet;
		gerechnet = NULL;
	}

	if(RainRate != NULL)
	{
		delete []RainRate;
		RainRate = NULL;
	}

	if(diffLoss != NULL)
	{
		delete []diffLoss;
		diffLoss = NULL;
	}
// 	if(RainRate!=NULL)
// 	{
// 		delete []RainRate;
// 		RainRate = NULL;
// 	}

	nSize = 0;
	noPoints = 0;
}

// 创建
CalGis_Profile* CalGis_Profile::Create()
{
	return new CalGis_Profile();
}

// 创建(包含空间大小)
CalGis_Profile* CalGis_Profile::Create(int inSize)
{
	return new CalGis_Profile(inSize);
}

// 销毁
bool CalGis_Profile::Destroy(CalGis_Profile* pDestroy)
{
	if (NULL != pDestroy)
	{
		delete pDestroy;
		pDestroy = NULL;
	}
	return true;
}

//add by jjj 2013.8.8
CalGis_Profile::CalGis_Profile(const CalGis_Profile& that)
{
	this->nSize = that.nSize;
	noPoints = that.noPoints;

	if (noPoints > 0)
	{
		xIndex = new long[this->nSize];
		yIndex = new long[this->nSize];

		xPathCoord = new double[this->nSize];
		yPathCoord = new double[this->nSize];

		distance = new double[this->nSize];
		height = new double[this->nSize];

		building = new double[this->nSize];
		clutter = new short[this->nSize];

		adaptedHeight = new double[this->nSize];
		conductivity = new double[this->nSize]; 

		lineOfSight = new double[this->nSize]; 

		memcpy(xIndex, that.xIndex, sizeof(long)*(this->nSize));
		memcpy(yIndex, that.yIndex, sizeof(long)*(this->nSize));

		memcpy(xPathCoord, that.xPathCoord, sizeof(double)*(this->nSize));
		memcpy(yPathCoord, that.yPathCoord, sizeof(double)*(this->nSize));

		memcpy(distance, that.distance, sizeof(double)*(this->nSize));
		memcpy(height, that.height, sizeof(double)*(this->nSize));

		memcpy(building, that.building, sizeof(double)*(this->nSize));
		memcpy(clutter, that.clutter, sizeof(short)*(this->nSize));

		memcpy(adaptedHeight, that.adaptedHeight, sizeof(double)*(this->nSize));
		memcpy(conductivity, that.conductivity, sizeof(double)*(this->nSize));

		memcpy(lineOfSight, that.lineOfSight, sizeof(double)*(this->nSize));
	}
	else
	{
		noPoints = 0;
		nSize = 0;

		xIndex = NULL;
		yIndex = NULL;

		xPathCoord = NULL;
		yPathCoord = NULL;

		distance = NULL;
		height = NULL;

		building = NULL;
		clutter = NULL;

		adaptedHeight = NULL;
		conductivity = NULL;

		lineOfSight = NULL;
	}
}

CalGis_Profile& CalGis_Profile::operator=(const CalGis_Profile& that)
{
	if (this == &that)
		return *this;

	Clear();

	if (noPoints > 0)
	{
		xIndex = new long[this->nSize];
		yIndex = new long[this->nSize];

		xPathCoord = new double[this->nSize];
		yPathCoord = new double[this->nSize];

		distance = new double[this->nSize];
		height = new double[this->nSize];

		building = new double[this->nSize];
		clutter = new short[this->nSize];

		adaptedHeight = new double[this->nSize];
		conductivity = new double[this->nSize]; 

		lineOfSight = new double[this->nSize]; 

		memcpy(xIndex, that.xIndex, sizeof(long)*(this->nSize));
		memcpy(yIndex, that.yIndex, sizeof(long)*(this->nSize));

		memcpy(xPathCoord, that.xPathCoord, sizeof(double)*(this->nSize));
		memcpy(yPathCoord, that.yPathCoord, sizeof(double)*(this->nSize));

		memcpy(distance, that.distance, sizeof(double)*(this->nSize));
		memcpy(height, that.height, sizeof(double)*(this->nSize));

		memcpy(building, that.building, sizeof(double)*(this->nSize));
		memcpy(clutter, that.clutter, sizeof(short)*(this->nSize));

		memcpy(adaptedHeight, that.adaptedHeight, sizeof(double)*(this->nSize));
		memcpy(conductivity, that.conductivity, sizeof(double)*(this->nSize));

		memcpy(lineOfSight, that.lineOfSight, sizeof(double)*(this->nSize));
	}

	return *this;
}