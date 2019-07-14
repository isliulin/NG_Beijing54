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
	*填充函数
	*处理后应满足bits≡448(mod512),字节就是bytes≡56（mode64)
	*填充方式为先加一个1,其它位补零
	*最后加上64位的原来长度
	*/
	vector<unsigned int> add(const string& str);
	void mainLoop(unsigned int M[]);
	string changeHex(int a);
private:
	//strByte的长度
	unsigned int m_Length;
	//A,B,C,D的临时变量
	unsigned int atemp;
	unsigned int btemp;
	unsigned int ctemp;
	unsigned int dtemp;
};

#endif
