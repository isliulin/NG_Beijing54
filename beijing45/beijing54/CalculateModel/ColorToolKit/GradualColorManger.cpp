#include "GradualColorManger.h"
#include "RGBHSLCalFun.h"
#include "HelperHeader.h"
#include "../CommonTools/FileTools.h"


CGradualColorManager::CGradualColorManager(double dmin,
										   double dmax,
										   COLORGBA mincolor,
										   COLORGBA maxClor)
:CColorManagerBase(CM_GRADUAL)// 
{
	m_minValue = dmin;
	m_maxValue = dmax;
	m_minColor = mincolor;
	m_MaxColor = maxClor;

	CalDeltaData();
}

CGradualColorManager::~CGradualColorManager()
{

}

COLORGBA CGradualColorManager::GetDataColor(double dataValue)
{
	if(dataValue<-9000)
		return 0;
	if (dataValue < m_minValue)
	{
		if(m_bLowerColorSame)
			return m_minColor;
		else
			return 0;
	}
	else if (dataValue >m_maxValue)
	{
		if(m_bUpperColorSame)
			return m_MaxColor;
		else
			return 0;
	}
	else		//值落在最小值和最大值之间
	{
		double dRate = (dataValue - m_minValue)/m_delta;
		BYTE H = (BYTE)(m_deltaH*dRate + m_minH);
		BYTE S = (BYTE)(m_deltaS*dRate + m_minS);
		BYTE L = (BYTE)(m_deltaL*dRate + m_minL);

		BYTE Red = 0;
		BYTE Green = 0;
		BYTE Blue = 0;
		HSL2RGB(H, S, L, Red, Green, Blue);

		return (RGB(Red,Green,Blue));
	}
}

void CGradualColorManager::SetDataRange(double dmin,double dmax)
{
	m_minValue = dmin;
	m_maxValue = dmax;
	CalDeltaData();
}
void CGradualColorManager::GetDataRange(double &dmin,double &dmax)
{
	dmin = m_minValue;
	dmax = m_maxValue;
}

void CGradualColorManager::SetColorRange(COLORGBA mincolor,COLORGBA maxClor)
{
	m_minColor = mincolor;
	m_MaxColor = maxClor;
	CalDeltaData();
}
void CGradualColorManager::GetColorRange(COLORGBA &mincolor,COLORGBA &maxClor)
{
	mincolor =  m_minColor;
	maxClor = m_MaxColor;
}

void CGradualColorManager::CalDeltaData()
{
	m_delta = m_maxValue-m_minValue;

	RGB2HSL(GetRValue(m_minColor),GetGValue(m_minColor),GetBValue(m_minColor), m_minH, m_minS, m_minL);
	RGB2HSL(GetRValue(m_MaxColor),GetGValue(m_MaxColor),GetBValue(m_MaxColor), m_maxH, m_maxS, m_maxL);

	m_deltaH = m_maxH -m_minH;
	m_deltaS = m_maxS -m_minS;
	m_deltaL = m_maxL -m_minL;
}

bool CGradualColorManager::ReadFromXMlFile( const char *pFile )
{
	if (pFile == NULL || !IsFileExistsA(pFile))
		return false;

	try
	{
		XmlDocument xmlFile;
		xmlFile.readFile(pFile);
		if (xmlFile.hasChild("ColorMap"))
		{
			bool isFinishColorMap = false;
			xmlFile.gotoFirstChild("ColorMap");
			do
			{
				string MapName = xmlFile.getAttribute("name").asString();
				string AttName = GetName();
				if (MapName == AttName)
				{
					return ReadFromXMlFile(&xmlFile);
				}
				if (xmlFile.isLastSibling("ColorMap"))
				{
					isFinishColorMap = true;
				}
				else
				{
					xmlFile.gotoNextSibling();
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

bool CGradualColorManager::ReadFromXMlFile( XmlDocument* pXmlFile )
{
	if (pXmlFile == NULL)
		return false;
	m_bLowerColorSame = pXmlFile->getAttribute("LowerSame").asBool();
	m_bUpperColorSame = pXmlFile->getAttribute("UpperSame").asBool();
	//
	m_minValue = pXmlFile->getAttribute("min").asDouble();
	m_maxValue = pXmlFile->getAttribute("max").asDouble();

	string maxRGBColor = pXmlFile->getAttribute("maxRGBColor").asString();
	string minRGBColor = pXmlFile->getAttribute("minRGBColor").asString();
	m_minColor = ConvertStr2ColorData(minRGBColor);
	m_MaxColor = ConvertStr2ColorData(maxRGBColor);

	CalDeltaData();
	return true;
}
