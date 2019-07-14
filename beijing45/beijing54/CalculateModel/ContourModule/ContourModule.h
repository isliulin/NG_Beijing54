
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

//������ֵ��
extern "C" CON_API ContourHandle CreateContour(const char *pFilePath,float *pLevel,int nLevelCount);

//ֱ�Ӵ��ڴ����ݴ�����ֵ�߾��
extern "C" CON_API ContourHandle CreateContourEX(void * pRasterData,float *pLevel,int nLevelCount);

//ɾ����ֵ��
extern "C" CON_API void DeleteContour(ContourHandle h);

//����ֵ������д�뵽�ļ�
extern "C" CON_API bool WriteContourToFile(ContourHandle h,const char *pFilePath);

//��ȡ��ֵ������
extern "C" CON_API ContourHandle ReadContourFromFile(const char *pFilePath);

//����
extern "C" CON_API int GetContorLevelCount(ContourHandle h);

extern "C" CON_API float GetContourLevel(ContourHandle h,int nIndex);

//ͨ����ֵ�߻�ȡ���е�ֵ��
extern "C" CON_API Contour_List *GetContourByLevel(ContourHandle h,float ContourLevel);

//ɾ��Contour_List
extern "C" CON_API void DeleteContourList(Contour_List * list);


//
//Contour_Item *GetContourLevel(ContourLevelHandle levelHandle,int nIndex);


#endif
