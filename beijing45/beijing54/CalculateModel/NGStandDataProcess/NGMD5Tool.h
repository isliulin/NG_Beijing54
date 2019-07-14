#ifndef NG_MD5_TOOL_H
#define NG_MD5_TOOL_H

#include <string>
#include <vector>
#include "CNGPreDefine.h"

using namespace std;
class CNGMD5Tool
{
public:
	CNGMD5Tool(void){};
	~CNGMD5Tool(void){};

public:
	string getMD5Code(const string& source);
	string getMD5Code(const NGDataVector& sites);

private:
	/*
	*��亯��
	*�����Ӧ����bits��448(mod512),�ֽھ���bytes��56��mode64)
	*��䷽ʽΪ�ȼ�һ��1,����λ����
	*������64λ��ԭ������
	*/
	vector<unsigned int> add(const string& str);
	void mainLoop(unsigned int M[]);
	string changeHex(int a);
private:
	//strByte�ĳ���
	unsigned int m_Length;
	//A,B,C,D����ʱ����
	unsigned int atemp;
	unsigned int btemp;
	unsigned int ctemp;
	unsigned int dtemp;
};

#endif
