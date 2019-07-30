#include <locale.h>
#include <string.h>

#include "CHSStdioFile.h"

#pragma warning(disable:4996)

CCHSStdioFile::CCHSStdioFile()
{
	char *pLoc = setlocale(LC_CTYPE, "chs");
	if (pLoc != NULL)
	{
		m_pDefaultLoc = new char[strlen(pLoc)+1];
		strcpy(m_pDefaultLoc,pLoc);
	}
	else
		m_pDefaultLoc = NULL;
}

CCHSStdioFile::~CCHSStdioFile()
{
	if (m_pDefaultLoc != NULL)
	{
		setlocale(LC_CTYPE, m_pDefaultLoc);
		delete []m_pDefaultLoc;
	}
}

//重写这个函数
void CCHSStdioFile::open(const char* pszFileName,ios_base::openmode _Mode)
{
	return BaseIfStream::open(pszFileName, _Mode);
}

