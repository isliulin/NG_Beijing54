#pragma once
#include <fstream>

using std::ifstream;
using std::wifstream;

//////////////////////////////////////////////////////////////////////////
//��ȡ�ı��ļ��࣬��Ҫ���ܶ��������ĵ��ı��ļ�������Ҳ�������ļ����к�����
//�����
//////////////////////////////////////////////////////////////////////////
#define BaseIfStream std::ifstream

class CCHSStdioFile:public BaseIfStream
{
public:
	CCHSStdioFile();
	virtual ~CCHSStdioFile();

	//��д�������
	void open(const char* pszFileName,ios_base::openmode _Mode);

private:
	char *m_pDefaultLoc;
};