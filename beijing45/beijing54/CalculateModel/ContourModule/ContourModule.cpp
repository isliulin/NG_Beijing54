// ContourModule.cpp : 定义 DLL 应用程序的导出函数。
//

#include "ContourModule.h"
#include "../CalResultWrapper/RasterResult.h"
#include "ContourValues.h"
#include "ContourGenerator.h"

// 这是导出变量的一个示例
//CONTOURMODULE_API int nContourModule=0;

// 这是导出函数的一个示例。
/*
CONTOURMODULE_API bool GenerateContour( char* resultPath,vector<float> contourVals ,char* outPutFile )
{
	ContourGenerator generator;

	for (int i=0;i<contourVals.size();i++)
	{
		generator.m_ContourValue.AddValue(contourVals[i]);
	}
	//generator.m_ContourValue = vals;
	generator.GenerateContour(resultPath);
	generator.WriteContours("E:\\NGEMC\\textContours.out");
	return true;
}*/

extern "C" ContourHandle CreateContourEX( void * pRasterData,float *pLevel,int nLevelCount )
{
	ContourGenerator *pContour = new ContourGenerator;

	for (int i=0;i<nLevelCount;i++)
	{
		pContour->m_ContourValue.AddValue(pLevel[i]);
	}
	//generator.m_ContourValue = vals;
	if (!pContour->GenerateContour(pRasterData,true))
	{
		delete pContour;
		return NULL;
	}
	return pContour;
}

extern "C" ContourHandle CreateContour( const char *pFilePath,float *pLevel,int nLevelCount )
{

	ContourGenerator *pContour = new ContourGenerator;

	for (int i=0;i<nLevelCount;i++)
	{
		pContour->m_ContourValue.AddValue(pLevel[i]);
	}
	//generator.m_ContourValue = vals;
	if (!pContour->GenerateContour(pFilePath))
	{
		delete pContour;
		return NULL;
	}
	return pContour;
}

extern "C" void DeleteContour( ContourHandle h )
{
	ContourGenerator *pContour = (ContourGenerator*)h;
	delete pContour;
	h = NULL;
}

extern "C" bool WriteContourToFile( ContourHandle h,const char *pFilePath )
{
	ContourGenerator *pContour = (ContourGenerator*)h;
	return pContour->WriteContours(pFilePath);
}

extern "C" ContourHandle ReadContourFromFile( const char *pFilePath )
{
	ContourGenerator *pContourGenerator = new ContourGenerator;
	bool isSuccess = false;
	if (pContourGenerator!= NULL)
	{
		isSuccess = pContourGenerator->ReadContours(pFilePath);
	}
	if (!isSuccess)
	{
		delete pContourGenerator;
		pContourGenerator = NULL;
	}
	return pContourGenerator;
}

extern "C" int GetContorLevelCount( ContourHandle h )
{
	ContourGenerator* pContourGenerator = (ContourGenerator*)h;
	return pContourGenerator->GetLevelCount();
}

extern "C" float GetContourLevel( ContourHandle h,int nIndex )
{
	ContourGenerator* pContourGenerator = (ContourGenerator*)h;
	return pContourGenerator->m_pContour->GetValue(nIndex);

}

extern "C" Contour_List* GetContourByLevel( ContourHandle h,float ContourLevel )
{
	ContourGenerator* pContourGenerator = (ContourGenerator*)h;
	CCurveList* list = pContourGenerator->GetContoursByLevel(ContourLevel);
	if (list==NULL)
	{
		return NULL;
	}
	Contour_List *contourList = NULL;
	contourList = new Contour_List;
	contourList->nContourCount = list->size();

	contourList->pContourList = new Contour_Item[contourList->nContourCount];

	for (int i=0;i<contourList->nContourCount;i++)
	{
		CCurve* pCurve = list->at(i);
		int pointCount = pCurve->size();
		
		Contour_Item item;
		item.nPointCount = pointCount;
		item.pPoint = new Contour_Point[pointCount];
		for (int j=0;j<pointCount;j++)
		{
			CGeoPoint point = pCurve->at(j);
			item.pPoint[j].x = point.x;
			item.pPoint[j].y = point.y;
		}
		contourList->pContourList[i] = item;
	}
	return contourList;
}

extern "C" void DeleteContourList( Contour_List * list )
{
	if (list != NULL)
	{
		for(int iContour=0;iContour<list->nContourCount;iContour++)
		{
			delete [] list->pContourList[iContour].pPoint;
		}
		delete [] list->pContourList;
		delete list;
	}
}



