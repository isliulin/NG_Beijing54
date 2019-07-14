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
	//�����ֵ���ú�����SetDataRange��SetColorRange�б�����,GetDataColor 
	//������ֱ��ʹ����Щ��ֵ������Ϊ�˿��ټ���
	void CalDeltaData();	

private:
	double m_minValue;		//��Сֵ
	double m_maxValue;		//���ֵ
	double m_delta;			//���ֵ����Сֵ�Ĳ�ֵ

	COLORGBA m_minColor;	//��Сֵ��Ӧ��RGB��ɫֵ
	COLORGBA m_MaxColor;	//���ֵ��Ӧ��RGB��ɫֵ

	//H,S,Lֵ
	BYTE m_minH;
	BYTE m_minS;
	BYTE m_minL;

	BYTE m_maxH;
	BYTE m_maxS;
	BYTE m_maxL;	

	//HSL ��ֵ
	int m_deltaH;				
	int m_deltaS;
	int m_deltaL;

};

#endif