#include <stdio.h>

#include "ContinuSectionColor.h"
#include "HelperHeader.h"
#include "../CommonTools/FileTools.h"

#include "../XercesWrapper/XercesWrapper.h"

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif



CContinuSectionColorManager::CContinuSectionColorManager()
:CColorManagerBase(CM_CONTINU_SECTION)
{
	for (int i = 0 ;i<ContinuColor_MaxNumber ; i++)
	{
		m_ContinuColor[i] = NULL;
	}
	m_ContinuRealNumer = 0;
}

CContinuSectionColorManager::CContinuSectionColorManager(const CContinuSectionColorManager &pr)
:CColorManagerBase(CM_CONTINU_SECTION)
{
	for (int i = 0 ;i<ContinuColor_MaxNumber ; i++)
	{
		m_ContinuColor[i] = NULL;
	}
	m_ContinuRealNumer = min(pr.GetContinuColorRealNumer(),ContinuColor_MaxNumber);

	for (int i = 0; i < m_ContinuRealNumer; i++)
	{
		m_ContinuColor[i] = new ContinuColor;
		m_ContinuColor[i]->ColorRGB = pr.m_ContinuColor[i]->ColorRGB;
		m_ContinuColor[i]->data_min = pr.m_ContinuColor[i]->data_min;
		m_ContinuColor[i]->data_max = pr.m_ContinuColor[i]->data_max;
	}
}

CContinuSectionColorManager::~CContinuSectionColorManager()
{
	ClearDataColor();
}

void CContinuSectionColorManager::ClearDataColor()
{
	for (int i = 0 ;i< m_ContinuRealNumer ; i++)
	{
		if (m_ContinuColor[i] != NULL)
		{
			delete m_ContinuColor[i];
			m_ContinuColor[i] = NULL;
		}
	}
	m_ContinuRealNumer = 0;
}

const ContinuColor * CContinuSectionColorManager::GetContinuColorItem(int nIndex)
{
	if (nIndex < m_ContinuRealNumer
		&&nIndex>-1)
		return m_ContinuColor[nIndex];
	else
		return NULL;
}

int CContinuSectionColorManager::GetContinuColorIndex(double DataValue)
{
	int num = m_ContinuRealNumer;
	if(DataValue < m_ContinuColor[0]->data_min)				//value 值比最小区间最小值还要小
	{
		if(m_bLowerColorSame)
			return 0;
		else
			return -1;
	}
	else if(DataValue  > m_ContinuColor[num-1]->data_max )	//value 值比最大区间最大值还要大
	{
		if(m_bUpperColorSame)
			return num-1;
		else
			return -1;
	}
	else
	{
		for(int index = 0; index < num; index++)
		{
			if(m_ContinuColor[index]->data_max > DataValue)
				return index;
		}

		//最大值,如果m_ContinuColor[index]->f_max > value也不为 真
		return -1;
	}
}

COLORGBA CContinuSectionColorManager::GetDataColor(double dataValue)
{
	int nIndex = GetContinuColorIndex(dataValue);
	if(nIndex<0)
		return 0;
	return m_ContinuColor[nIndex]->ColorRGB;
}

void CContinuSectionColorManager::ModifyContinuColorTable(ContinuColor **ppContinuColor,int Color_Num)
{
	if (ppContinuColor != NULL && Color_Num > 0)
	{
		for (int i = 0 ;i<m_ContinuRealNumer ; i++)
		{
			if (m_ContinuColor[i] != NULL)
			{
				delete m_ContinuColor[i];
				m_ContinuColor[i] = NULL;
			}
		}
		m_ContinuRealNumer = min(Color_Num,ContinuColor_MaxNumber);

		for (int nIndex = 0;nIndex < m_ContinuRealNumer;nIndex ++)
		{
			m_ContinuColor[nIndex] = ppContinuColor[nIndex];	//指针赋值
		}

		for (int nIndex = m_ContinuRealNumer;nIndex < Color_Num;nIndex ++)
		{
			delete ppContinuColor[nIndex];	//指针赋值
		}
	}
}

bool CContinuSectionColorManager::ReadFromXMlFile( const char *pFile )
{
	if (pFile == NULL || !IsFileExistsA(pFile))
		return false;

	try
	{
		XmlDocument xmlFile;
		xmlFile.readFile(pFile);

		if (xmlFile.hasChild("ColorMap"))
		{
			bool isFinishMap = false;
			xmlFile.gotoFirstChild("ColorMap");
			do
			{
				string ColorMapName = xmlFile.getAttribute("name").asString();//colorMap的name属性
				string AttrName = GetName();
				if (ColorMapName == AttrName)
				{
					return ReadFromXMlFile(&xmlFile);
				}
				if (xmlFile.isLastSibling("ColorMap"))
				{
					isFinishMap = true;
				}
				else
				{
					xmlFile.gotoNextSibling("ColorMap");
				}
			} while (!isFinishMap);
			xmlFile.gotoFather();
		}
	}
	catch (...)
	{
		return false;
	}

	return false;
}

bool CContinuSectionColorManager::ReadFromXMlFile( XmlDocument* pXmlFile )
{
	if (pXmlFile == NULL)
		return false;

	ClearDataColor();	//先清空数据

	bool bRet = false;
	m_bLowerColorSame = pXmlFile->getAttribute("LowerSame").asBool();
	m_bUpperColorSame = pXmlFile->getAttribute("UpperSame").asBool();

	if (pXmlFile->hasChild("Ranges"))
	{
		pXmlFile->gotoChild("Ranges");
		if (pXmlFile->hasChild("RangeInfo"))
		{
			bool isFinishRangeInfo = false;
			pXmlFile->gotoFirstChild("RangeInfo");
			do
			{
				ContinuColor *pContinuColor = new ContinuColor;
				string rgbcolor = pXmlFile->getAttribute("RGBColor").asString();
				double Minvalue = pXmlFile->getAttribute("min").asFloat();
				double MaxValue = pXmlFile->getAttribute("max").asFloat();
				pContinuColor->ColorRGB = ConvertStr2ColorData(rgbcolor);
				pContinuColor->data_min = Minvalue;
				pContinuColor->data_max = MaxValue;
				m_ContinuColor[m_ContinuRealNumer] = pContinuColor;
				m_ContinuRealNumer++;
				//如果颜色区间太多,则最多读取ContinuColor_MaxNumber个区间
				if (m_ContinuRealNumer >= ContinuColor_MaxNumber || pXmlFile->isLastSibling("RangeInfo"))
				{
					isFinishRangeInfo = true;
				}
				else
				{
					pXmlFile->gotoNextSibling();
				}
			} while (!isFinishRangeInfo);
			pXmlFile->gotoFather();		//RangeInfo

			bRet =  true;
		}
		pXmlFile->gotoFather();			//Ranges
	}

	return bRet;
}

int CContinuSectionColorManager::GetColorCount() const
{
	return m_ContinuRealNumer;
}

