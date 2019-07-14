#ifndef __CONTOURGENERATOR_H__
#define __CONTOURGENERATOR_H__
#include "GeoData.h"
#include "Contour.h"
// #include "ContourDll.h"

class ContourGenerator
{
public:
	ContourGenerator(void);
	~ContourGenerator(void);
public:
	CGeoData m_GeoData;
	CContour* m_pContour;
	CContourValues m_ContourValue;//等值线数组
	CContour* GetContour(){return m_pContour;};
	bool GenerateContour(const char* resultpath);
	bool GenerateContour(void * pData,bool bRasterData);
	bool WriteContours(const char* outputPath);
	bool ReadContours(const char* inPath);
	int GetLevelCount(){return m_pContour->GetValueList().size();};
	CCurveList* GetContoursByLevel(float level);


};
#endif