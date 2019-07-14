#ifndef __COLOR_MANAGER_BASE__H__
#define __COLOR_MANAGER_BASE__H__

#include "ColorToolKit.h"
#include "../XercesWrapper/XercesWrapper.h"
using namespace XercesWrapperNS;

enum ColorManagerType
{
	CM_CONTINU_SECTION,		//��ɢ��ɫ,�ֳɶ������,ÿ������һ����ɫ
	CM_GRADUAL,				//������ɫ
	CM_SCATTER,				//��ɢ��ɫ,һ����������(int)����һ����ɫ����
	CM_THRESHOLD			//������ֵ��ɫ
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