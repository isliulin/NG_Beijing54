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
	double m_minValue;		//��Сֵ
	double m_maxValue;		//���ֵ
	double m_delta;			//���ֵ����Сֵ�Ĳ�ֵ

	COLORGBA m_minColor;	//��Сֵ��Ӧ��RGB��ɫֵ
	COLORGBA m_MaxColor;	//���ֵ��Ӧ��RGB��ɫֵ
};

#endif