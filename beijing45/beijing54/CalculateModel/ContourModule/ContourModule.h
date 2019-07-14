
#ifndef __CONTOURMODULE_H__
#define __CONTOURMODULE_H__

#include "ContourDll.h"

//
typedef void *ContourHandle;
typedef void *ContourLevelHandle;

struct Contour_Point 
{
	double x;
	double y;
};

struct Contour_Item 
{
	int nPointCount;
	Contour_Point *pPoint;
};

struct Contour_List
{
	int nContourCount;
	Contour_Item* pContourList;
};

//创建等值线
extern "C" CON_API ContourHandle CreateContour(const char *pFilePath,float *pLevel,int nLevelCount);

//直接从内存数据创建等值线句柄
extern "C" CON_API ContourHandle CreateContourEX(void * pRasterData,float *pLevel,int nLevelCount);

//删除等值线
extern "C" CON_API void DeleteContour(ContourHandle h);

//将等值线数据写入到文件
extern "C" CON_API bool WriteContourToFile(ContourHandle h,const char *pFilePath);

//读取等值线数据
extern "C" CON_API ContourHandle ReadContourFromFile(const char *pFilePath);

//个数
extern "C" CON_API int GetContorLevelCount(ContourHandle h);

extern "C" CON_API float GetContourLevel(ContourHandle h,int nIndex);

//通过等值线获取所有等值线
extern "C" CON_API Contour_List *GetContourByLevel(ContourHandle h,float ContourLevel);

//删除Contour_List
extern "C" CON_API void DeleteContourList(Contour_List * list);


//
//Contour_Item *GetContourLevel(ContourLevelHandle levelHandle,int nIndex);


#endif
