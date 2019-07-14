#include "ScatterColorManger.h"
#include "HelperHeader.h"
#include "../CommonTools/FileTools.h"
#include "../XercesWrapper/XercesWrapper.h"

CScatterColorManager::CScatterColorManager()
:CColorManagerBase(CM_SCATTER)
{
	m_DefaultDataColor = RGB(0,0,0);
}

CScatterColorManager::~CScatterColorManager()
{
	ClearDataColor();
}

void CScatterColorManager::ClearDataColor()
{
	m_ColorData.clear();
}

//返回给定值的颜色
COLORGBA CScatterColorManager::GetDataColor(int dataValue)
{
	COLORGBA c = 0;

	std::map<int,COLORGBA>::iterator it = m_ColorData.find(dataValue);
	if (it != m_ColorData.end())
		c = it->second;
	else if (m_bUpperColorSame && dataValue>0)
		c = m_ColorData.rbegin()->second;
	else
		c = m_DefaultDataColor;

	return c;
}

COLORGBA CScatterColorManager::GetDataColor( double dataValue )
{
	int val = (int)(dataValue+0.5);
	return GetDataColor(val);
}
//设置一个值对应的颜色
void CScatterColorManager::SetDataColor(int dataValue,const COLORGBA &c)
{
	std::map<int,COLORGBA>::iterator it = m_ColorData.find(dataValue);
	if (it != m_ColorData.end())
	{
		it->second = c;
	}
	else
	{
		COLORGBA NewColor = c;
		m_ColorData.insert(std::make_pair(dataValue,NewColor));
	}
}

//设置缺省颜色,如果颜色表中找不到给定数据值,则返回缺省颜色
void CScatterColorManager::SetDefaultColor(const COLORGBA &c)
{
	m_DefaultDataColor = c;
}

void CScatterColorManager::GetDefaultColor(COLORGBA &c)
{
	c = m_DefaultDataColor;
}

//颜色总的个数
int CScatterColorManager::GetColorCount()
{
	return m_ColorData.size();
}

bool CScatterColorManager::GetDataColorInfo(int nIndex,COLORGBA &c)
{
	if (nIndex < 0 || nIndex >= GetColorCount())
		return false;

	std::map<int,COLORGBA>::iterator it;
	int nTemp = 0;
	for (it = m_ColorData.begin(); it != m_ColorData.end();it ++,nTemp++)
	{
		if (nTemp == nIndex)
		{
			c = it->second;
			return true;
		}
	}

	return false;
}

bool CScatterColorManager::ReadFromXMlFile( const char *pFile )
{
	if (pFile == NULL || !IsFileExistsA(pFile))
		return false;

	try
	{
		XmlDocument xmlFile;
		xmlFile.readFile(pFile);
		if (xmlFile.hasChild("ColorMap"))
		{
			xmlFile.gotoFirstChild("ColorMap");
			bool isFinishColorMap = false;
			do
			{
				string MapName = xmlFile.getAttribute("name").asString();
				string attName = GetName();
				if (MapName == attName)
				{
					return ReadFromXMlFile(&xmlFile);
				}
				if (xmlFile.isLastSibling("ColorMap"))
				{
					isFinishColorMap = true;
				}
				else
				{
					xmlFile.gotoNextSibling("ColorMap");
				}
			} while (!isFinishColorMap);
			xmlFile.gotoFather();
		}
	}
	catch (...)
	{
		return false;
	}

	return false;
}

bool CScatterColorManager::ReadFromXMlFile( XmlDocument* pXmlFile )
{
	// return false;
	if (pXmlFile == NULL)
		return false;

	ClearDataColor();	//先清空数据
	m_bLowerColorSame = pXmlFile->getAttribute("LowerSame").asBool();
	m_bUpperColorSame = pXmlFile->getAttribute("UpperSame").asBool();

	if (pXmlFile->hasChild("Entry"))
	{
		pXmlFile->gotoFirstChild("Entry");
		bool isFinishEntry = false;
		do
		{
			int terrainType = pXmlFile->getAttribute("terrainType").asInt();

			string rgbcolor = pXmlFile->getAttribute("color").asString();
			COLORGBA col = ConvertStr2ColorData(rgbcolor);

			m_ColorData.insert(make_pair(terrainType,col));
			if (pXmlFile->isLastSibling("Entry"))
			{
				isFinishEntry =true;
			}
			else
			{
				pXmlFile->gotoNextSibling("Entry");
			}
		} while (!isFinishEntry);
		pXmlFile->gotoFather();		//Entry

		return true;
	}

	return false;
}

int CScatterColorManager::GetDataColorIndex( int dataValue )
{
	std::map<int,COLORGBA>::iterator it = m_ColorData.find(dataValue);
	if(it!=m_ColorData.end())
	{
		int nTemp = 0;
		for (it = m_ColorData.begin(); it != m_ColorData.end();it ++,nTemp++)
		{
			if (it->first == dataValue)
			{
				return nTemp;
			}
		}
	}
	return -1;
}
