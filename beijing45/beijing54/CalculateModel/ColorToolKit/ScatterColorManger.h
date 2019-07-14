#ifndef __SCATTER__COLOR_MANAGER__H__
#define __SCATTER__COLOR_MANAGER__H__

#include "ColorManagerBase.h"
#include <map>

//离散颜色管理器
class CScatterColorManager: public CColorManagerBase
{
public:
	CScatterColorManager();
	virtual ~CScatterColorManager();

public:
	//返回给定值的颜色
	COLORGBA GetDataColor(double dataValue);
	COLORGBA GetDataColor(int dataValue);
	int GetDataColorIndex(int dataValue);

	//设置一个值对应的颜色
	void SetDataColor(int dataValue,const COLORGBA &c);

	//设置缺省颜色,如果颜色表中找不到给定数据值,则返回缺省颜色
	void SetDefaultColor(const COLORGBA &c);
	void GetDefaultColor(COLORGBA &c);

	//颜色总的个数
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