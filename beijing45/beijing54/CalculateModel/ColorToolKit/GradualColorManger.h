#ifndef __GRADUAL__COLOR_MANAGER__H__
#define __GRADUAL__COLOR_MANAGER__H__

#include "ColorManagerBase.h"



class CGradualColorManager: public CColorManagerBase
{
public:
	CGradualColorManager(double dmin=-50,double dmax=200,COLORGBA mincolor=RGB(0,0,255),COLORGBA maxClor = RGB(255,0,0));
	virtual ~CGradualColorManager();

public:
	COLORGBA GetDataColor(double dataValue);

	void SetDataRange(double dmin,double dmax);
	void GetDataRange(double &dmin,double &dmax);

	void SetColorRange(COLORGBA mincolor,COLORGBA maxClor);
	void GetColorRange(COLORGBA &mincolor,COLORGBA &maxClor);

	bool ReadFromXMlFile(const char *pFile);
	bool ReadFromXMlFile(XmlDocument* pXmlFile);

private:
	//计算差值，该函数在SetDataRange，SetColorRange中被调用,GetDataColor 
	//函数中直接使用这些差值，这样为了快速计算
	void CalDeltaData();	

private:
	double m_minValue;		//最小值
	double m_maxValue;		//最大值
	double m_delta;			//最大值和最小值的差值

	COLORGBA m_minColor;	//最小值对应的RGB颜色值
	COLORGBA m_MaxColor;	//最大值对应的RGB颜色值

	//H,S,L值
	BYTE m_minH;
	BYTE m_minS;
	BYTE m_minL;

	BYTE m_maxH;
	BYTE m_maxS;
	BYTE m_maxL;	

	//HSL 差值
	int m_deltaH;				
	int m_deltaS;
	int m_deltaL;

};

#endif