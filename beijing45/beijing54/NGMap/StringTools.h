#ifndef __STRINGS_TOOLS__H__
#define __STRINGS_TOOLS__H__

#include <string>

using namespace std;

//宽字节转换到多字节
bool ws2ms(const wchar_t *lpWideCharStr,char * lpMultiByteStr);

//多字节转换到宽字节
bool ms2ws(const char * lpMultiByteStr,wchar_t *lpWideCharStr);

//去除tstring前后的特定字符
void stringTrimA(string& inString, char chTarget=' ');
void stringTrimW(wstring& inString, wchar_t chTarget=' ');

//将字符串中的值变为大写
void stringUpperA(std::string& inoutString);
void stringUpperW(std::wstring& inoutString);

//将字符串中的值变为小写
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
