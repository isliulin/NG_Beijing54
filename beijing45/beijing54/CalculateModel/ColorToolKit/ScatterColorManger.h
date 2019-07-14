#ifndef __SCATTER__COLOR_MANAGER__H__
#define __SCATTER__COLOR_MANAGER__H__

#include "ColorManagerBase.h"
#include <map>

//��ɢ��ɫ������
class CScatterColorManager: public CColorManagerBase
{
public:
	CScatterColorManager();
	virtual ~CScatterColorManager();

public:
	//���ظ���ֵ����ɫ
	COLORGBA GetDataColor(double dataValue);
	COLORGBA GetDataColor(int dataValue);
	int GetDataColorIndex(int dataValue);

	//����һ��ֵ��Ӧ����ɫ
	void SetDataColor(int dataValue,const COLORGBA &c);

	//����ȱʡ��ɫ,�����ɫ�����Ҳ�����������ֵ,�򷵻�ȱʡ��ɫ
	void SetDefaultColor(const COLORGBA &c);
	void GetDefaultColor(COLORGBA &c);

	//��ɫ�ܵĸ���
	int GetColorCount();
	bool GetDataColorInfo(int nIndex,COLORGBA &c);

	void ClearDataColor();

	bool ReadFromXMlFile(const char *pFile);
	bool ReadFromXMlFile(XmlDocument* pXmlFile);

private:
	std::map<int,COLORGBA>m_ColorData;
	COLORGBA m_DefaultDataColor;

};

#endif