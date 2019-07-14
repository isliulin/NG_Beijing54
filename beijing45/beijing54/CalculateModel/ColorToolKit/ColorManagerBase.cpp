#include "ColorManagerBase.h"
#include <string.h>

#pragma warning(disable:4996)

CColorManagerBase::CColorManagerBase(ColorManagerType t)
{
	m_bLowerColorSame = false;
	m_bUpperColorSame = false;
	m_type = t;
	memset(m_szName,0,sizeof(m_szName));
}

void CColorManagerBase::SetName(const char *pName)
{
	if (pName != NULL)
	{
		strcpy(m_szName,pName);
	}
}

void CColorManagerBase::SetLowerColorSame( bool bSame )
{
	m_bLowerColorSame = bSame;
}

void CColorManagerBase::SetUpperColorSame( bool bSame )
{
	m_bUpperColorSame = bSame;
}

bool CColorManagerBase::IsLowerColorSame() const
{
	return m_bLowerColorSame;
}

bool CColorManagerBase::IsUpperColorSame() const
{
	return m_bUpperColorSame;
}