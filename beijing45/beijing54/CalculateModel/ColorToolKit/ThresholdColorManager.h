#ifndef __THRESHOLD__COLOR_MANAGER__H__
#define __THRESHOLD__COLOR_MANAGER__H__

#include "ColorManagerBase.h"

class ThresholdColorManager: public CColorManagerBase
{
public:
	ThresholdColorManager(double dmin=-50,double dmax=200,COLORGBA mincolor=RGB(0,0,255),COLORGBA maxClor = RGB(255,0,0));
	virtual ~ThresholdColorManager(void);

public:
	COLORGBA GetDataColor(double dataValue){return 0;}
	COLORGBA GetDataColor(double dataValue, double dThreshold);

private:
	double m_minValue;		//最小值
	double m_maxValue;		//最大值
	double m_delta;			//最大值和最小值的差值

	COLORGBA m_minColor;	//最小值对应的RGB颜色值
	COLORGBA m_MaxColor;	//最大值对应的RGB颜色值
};

#endif