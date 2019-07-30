#pragma once
#include <fstream>

using std::ifstream;
using std::wifstream;

//////////////////////////////////////////////////////////////////////////
//读取文本文件类，主要是能读包含中文的文本文件，另外也处理了文件名中含中文
//的情况
//////////////////////////////////////////////////////////////////////////
#define BaseIfStream std::ifstream

class CCHSStdioFile:public BaseIfStream
{
public:
	CCHSStdioFile();
	virtual ~CCHSStdioFile();

	//重写这个函数
	void open(const char* pszFileName,ios_base::openmode _Mode);

private:
	char *m_pDefaultLoc;
};