#ifndef __COLOR_MANAGER_BASE__H__
#define __COLOR_MANAGER_BASE__H__

#include "ColorToolKit.h"
#include "../XercesWrapper/XercesWrapper.h"
using namespace XercesWrapperNS;

enum ColorManagerType
{
	CM_CONTINU_SECTION,		//离散配色,分成多个区间,每个区间一个颜色
	CM_GRADUAL,				//渐变配色
	CM_SCATTER,				//离散配色,一个整形数据(int)设置一个配色数据
	CM_THRESHOLD			//根据阈值配色
};

class CColorManagerBase
{
public:
	CColorManagerBase(ColorManagerType t);
	virtual ~CColorManagerBase(){}
	
public:
	void SetName(const char *pName);
	const char * GetName() { return m_szName;}

	ColorManagerType GetType() { return m_type;}
	virtual COLORGBA GetDataColor(double dataValue) = 0;
	virtual bool ReadFromXMlFile(const char *pFile){return false;}
	virtual bool ReadFromXMlFile(XmlDocument* pXmlFile){return false;}
	void SetLowerColorSame(bool bSame);
	void SetUpperColorSame(bool bSame);
	bool IsLowerColorSame() const;
	bool IsUpperColorSame() const;
protected:
	bool m_bLowerColorSame;
	bool m_bUpperColorSame;
	char m_szName[128];
	ColorManagerType m_type;
};

#endif