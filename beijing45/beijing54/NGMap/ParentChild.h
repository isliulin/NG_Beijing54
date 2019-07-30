#ifndef __PARENT__CHILD__FILE__h__
#define __PARENT__CHILD__FILE__h__

#pragma once
#include "CHSStdioFile.h"
/*
文件格式如下

DataDescription]
XPixel                          = (long)              600
YPixel                          = (long)              600
BitsPerPixel                    = (long)              16
PixelDataType                   = (cstring)           "short"
FileType                        = (cstring)           "Binary"

*/

class CParentChildFile
{
public:
	CParentChildFile(const char* pszFileName);
	~CParentChildFile(void);

public:
	void GetElement(const char* pszParent,const char* pszChild,int &ElementValue);
	void GetElement(const char* pszParent,const char* pszChild,long &ElementValue);
	void GetElement(const char* pszParent,const char* pszChild,double &ElementValue);
	void GetElement(const char* pszParent,const char* pszChild,std::string &ElementValue);

private:
	bool GetElementString(const char* pszParent,const char* pszChild,std::string &strLine);
	bool MoveToElement(const char* pszParent,const char* pszChild);

private:
	CCHSStdioFile m_Readfile;
	bool m_bFileOK;
};

#endif