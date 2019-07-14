#ifndef __STRINGS_TOOLS__H__
#define __STRINGS_TOOLS__H__

#include <string>

using namespace std;

//���ֽ�ת�������ֽ�
bool ws2ms(const wchar_t *lpWideCharStr,char * lpMultiByteStr);

//���ֽ�ת�������ֽ�
bool ms2ws(const char * lpMultiByteStr,wchar_t *lpWideCharStr);

//ȥ��tstringǰ����ض��ַ�
void stringTrimA(string& inString, char chTarget=' ');
void stringTrimW(wstring& inString, wchar_t chTarget=' ');

//���ַ����е�ֵ��Ϊ��д
void stringUpperA(std::string& inoutString);
void stringUpperW(std::wstring& inoutString);

//���ַ����е�ֵ��ΪСд
void stringLowerA(std::string& inoutString);
void stringLowerW(std::wstring& inoutString);

#ifdef  UNICODE     
	#define stringTrim		stringTrimA
	#define stringUpper		stringUpperA
	#define stringLower		stringLowerA
#else   /* UNICODE */  
	#define stringTrim		stringTrimW
	#define stringUpper		stringUpperW
	#define stringLower		stringLowerW
#endif /* UNICODE */ 

#endif
