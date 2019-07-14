#include <string.h>
#include "CreateColorManager.h"
#include "ContinuSectionColor.h"
#include "GradualColorManger.h"
#include "ScatterColorManger.h"
#include "../CommonTools/FileTools.h"
#include "../XercesWrapper/XercesWrapper.h"

using namespace XercesWrapperNS;

ColorManagerType GetColorMagerType_FromName(const char *pName)
{
	ColorManagerType t = CM_CONTINU_SECTION;
	if (pName == NULL)
		return t;

	if (strcmp(pName,"Scatter") == 0)				//类别是离散配色
		return CM_SCATTER;
	else if (strcmp(pName,"ContinuSection") == 0)	//类似是连续配色,区间
		return CM_CONTINU_SECTION;
	else if (strcmp(pName,"Gradual") == 0)			//渐变配色
		return CM_GRADUAL;

	return t;
}

ColorManagerType GetColorMagerType_FromXMLFile(const char *pColorFile,const char *pName)
{
	ColorManagerType t = CM_CONTINU_SECTION;
	if (pColorFile == NULL || pName == NULL)
		return t;

	try
	{
		if (IsFileExistsA(pColorFile))
		{
			XmlDocument xmlFile;
			xmlFile.readFile(pColorFile);
			if (xmlFile.hasChild("ColorMap"))
			{
				xmlFile.gotoFirstChild("ColorMap");
				bool finished=false;
				do
				{
					const char *pTempName = xmlFile.getAttribute("name").asString();
					if (strcmp(pTempName,pName) == 0)						//定位到名称
					{
						pTempName = xmlFile.getAttribute("type").asString();
						return GetColorMagerType_FromName(pTempName);
					}

					if (xmlFile.isLastSibling("ColorMap"))
						finished = true;
					else
						xmlFile.gotoNextSibling("ColorMap");

				}while (!finished);
			}
		}
	}
	catch (...)
	{

	}

	return t;
}

CColorManagerBase * CreateColorManger_FromFile(const char *pColorFile,const char *pName)
{
	if (pColorFile == NULL)
		return NULL;
	ColorManagerType colorMgr_Type = GetColorMagerType_FromXMLFile(pColorFile,pName);
	CColorManagerBase * pColorMgr = CreateColorManager(colorMgr_Type);
	if(pColorMgr == NULL)
		return NULL;
	pColorMgr->SetName(pName);
	if(pColorMgr->ReadFromXMlFile(pColorFile))
		return pColorMgr;
	else
		ClearColorManager(pColorMgr);
	return NULL;
}

bool CreateColorManger_FromFile(const char *pColorFile,std::vector<CColorManagerBase *> &ColorManageVector)
{

	if (pColorFile == NULL)
		return false;

	bool bRet = false;
	ColorManagerType colorMgr_Type = CM_CONTINU_SECTION;
	ColorManageVector.clear();

	try
	{
		if (IsFileExistsA(pColorFile))
		{
			XmlDocument xmlFile;
			xmlFile.readFile(pColorFile);
			if (xmlFile.hasChild("ColorMap"))
			{
				xmlFile.gotoFirstChild("ColorMap");
				bool finished=false;
				do
				{
					const char *pTypeName = xmlFile.getAttribute("type").asString();
					colorMgr_Type = GetColorMagerType_FromName(pTypeName);	//获取到配色类别

					const char *pColorName = xmlFile.getAttribute("name").asString();

					CColorManagerBase *pColorMgr = CreateColorManager(colorMgr_Type);
					if(pColorMgr!=NULL)
					{
						pColorMgr->SetName(pColorName);

						if(pColorMgr->ReadFromXMlFile(&xmlFile))
						{
							ColorManageVector.push_back(pColorMgr);
						}
						else
						{
							ClearColorManager(pColorMgr);
						}


					}
					if (xmlFile.isLastSibling("ColorMap"))
						finished = true;
					else
						xmlFile.gotoNextSibling("ColorMap");

				}while (!finished);
				xmlFile.gotoFather();
				bRet = true;
			}//end if (xmlFile.hasChild("ColorMap"))
		}
	}
	catch (...)
	{
	}

	return bRet;
}

CColorManagerBase * CreateColorManger_FromData(const char *pName,
											   double dmin,double dmax,
											   COLORGBA mincolor,COLORGBA maxClor)
{
	if (pName == NULL)
		return NULL;

	CGradualColorManager *pDestColorMgr = new CGradualColorManager(dmin,dmax,mincolor,maxClor);
	pDestColorMgr->SetName(pName);

	return pDestColorMgr;
}

void ClearColorManager( CColorManagerBase* pColorManager )
{
	delete pColorManager;
}

CColorManagerBase * CreateDefalutPathLossColor()
{
	CContinuSectionColorManager * pColorMgr = new CContinuSectionColorManager();
	//
#define ColorCount 20
	double minvalue = 0;
	double deleta = 10;
	ContinuColor * Colors[ColorCount];
	for(int i=0;i<ColorCount;i++)
	{
		Colors[i] = new ContinuColor();
		Colors[i]->data_min = minvalue+i*deleta;
		Colors[i]->data_max = minvalue+(i+1)*deleta;
		Colors[i]->ColorRGB = RGBA(i*10,128-i*5,255-i*10,0);
	}
	pColorMgr->ModifyContinuColorTable(Colors,ColorCount);
	pColorMgr->SetName("pathloss");
#undef  ColorCount
	return pColorMgr;
}

CColorManagerBase * CreateDefaultContinuColor()
{

CContinuSectionColorManager * pColorMgr = new CContinuSectionColorManager();
#define ColorCount 25
	double minvalue = -100;
	double deleta = 10;
	ContinuColor * Colors[ColorCount];
	for(int i=0;i<ColorCount;i++)
	{
		Colors[i] = new ContinuColor();
		Colors[i]->data_min = minvalue+i*deleta;
		Colors[i]->data_max = minvalue+(i+1)*deleta;
		Colors[i]->ColorRGB = RGBA(255-i*10,200-i*5,i*10,0);
	}
	pColorMgr->ModifyContinuColorTable(Colors,ColorCount);
	pColorMgr->SetName("TempColor");
#undef  ColorCount
	return pColorMgr;
}



CColorManagerBase * CreateColorManager( ColorManagerType type )
{
	switch(type)
	{
	case CM_CONTINU_SECTION:		//离散配色,分成多个区间,每个区间一个颜色
		return new CContinuSectionColorManager();
	case CM_GRADUAL:				//渐变配色
		return new CGradualColorManager();
	case CM_SCATTER:
		return new CScatterColorManager();
	default:
		return NULL;
	}
}

CColorManagerBase * CreateDefaultGradualColor()
{
	CGradualColorManager * pColorMgr = new CGradualColorManager();
	pColorMgr->SetColorRange(RGB(0,128,255),RGB(255,0,0));
	pColorMgr->SetDataRange(-20,250);
	pColorMgr->SetName("TempColor");
	return pColorMgr;
}

