#include "ThresholdColorManager.h"
#include "RGBHSLCalFun.h"
#include "HelperHeader.h"
#include "../CommonTools/FileTools.h"

ThresholdColorManager::ThresholdColorManager(double dmin,
											 double dmax,
											 COLORGBA mincolor,
											 COLORGBA maxClor)
:CColorManagerBase(CM_THRESHOLD)
{
	m_minValue = dmin;
	m_maxValue = dmax;
	m_minColor = mincolor;
	m_MaxColor = maxClor;
}

ThresholdColorManager::~ThresholdColorManager(void)
{
}

COLORGBA ThresholdColorManager::GetDataColor(double dataValue, double dThreshold)
{
	if(dataValue > dThreshold)
		return m_minColor;
	else
		return 0;
}