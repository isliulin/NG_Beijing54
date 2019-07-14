#include "StringTools.h"
#include <stdlib.h>
#if defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#else
#include <unistd.h>
#endif	 

#define TRANS_BUFFER	32

bool ws2ms(const wchar_t *lpWideCharStr,char * lpMultiByteStr)
{
	if (lpWideCharStr == NULL || lpMultiByteStr == NULL)
		return false;

	int length = 0;

#ifdef _WIN32
	length = WideCharToMultiByte(GetACP(),0,lpWideCharStr,-1,0,0,0,0);
	if (length > 0)
	{
		length = WideCharToMultiByte(GetACP(),0,lpWideCharStr,-1,lpMultiByteStr,length,0,0);
	}
#else
	length = wcstombs(0, lpWideCharStr, 0)+1;	//length-->不包含null字符
	if (length > 0)
	{
		length = wcstombs(lpMultiByteStr,lpWideCharStr,length);
	}
#endif

	if (length > 0)
		return true;
	else
		return false;
}

bool ms2ws(const char * lpMultiByteStr,wchar_t *lpWideCharStr)
{
	if (lpWideCharStr == NULL || lpMultiByteStr == NULL)
		return false;

	int length = 0;

#ifdef _WIN32
	length = MultiByteToWideChar(GetACP(), 0, lpMultiByteStr, -1, 0, 0);
	if (length > 0)
	{
		length = MultiByteToWideChar(GetACP(), 0, lpMultiByteStr, -1, lpWideCharStr, length);
	}
#else
	length = mbstowcs(0, lpMultiByteStr, 0)+1;
	if (length > 0)	
	{
		length = mbstowcs(lpWideCharStr, lpMultiByteStr, length);
	}
#endif

	if (length > 0)
		return true;
	else
		return false;
}


//去除tstring前后的特定字符
void stringTrimA(string& inString, char chTarget)
{
	std::basic_string<char>::size_type nStart = inString.find_first_not_of(chTarget);
	std::basic_string<char>::size_type nEnd = inString.find_last_not_of(chTarget);

	//全是查找的字符
	if(nStart == string::npos)
	{
		inString.clear(); //清空
	}
	else if(nEnd-nStart+1 < inString.length())
	{
		inString = inString.substr(nStart, nEnd - nStart + 1);
	}
}

void stringTrimW(wstring& inString, wchar_t chTarget)
{
	std::basic_string<wchar_t>::size_type nStart = inString.find_first_not_of(chTarget);
	std::basic_string<wchar_t>::size_type nEnd = inString.find_last_not_of(chTarget);

	//全是查找的字符
	if(nStart == string::npos)
	{
		inString.clear(); //清空
	}
	else if(nEnd-nStart+1 < inString.length())
	{
		inString = inString.substr(nStart, nEnd - nStart + 1);
	}
}

void stringUpperA(std::string& inoutString)
{
	std::string::iterator p1;
	std::string::iterator p1End = inoutString.end();
	for(p1 = inoutString.begin(); p1 != p1End; p1++)
	{
		*p1 = toupper(*p1);
	}
}

void stringUpperA(std::wstring& inoutString)
{
	std::wstring::iterator p1;
	std::wstring::iterator p1End = inoutString.end();
	for(p1 = inoutString.begin(); p1 != p1End; p1++)
	{
		*p1 = toupper(*p1);
	}
}

void stringLowerA(std::string& inoutString)
{
	std::string::iterator p1;
	std::string::iterator p1End = inoutString.end();
	for(p1 = inoutString.begin(); p1 != p1End; p1++)
	{
		*p1 = tolower(*p1);
	}
}

void stringLowerW(std::wstring& inoutString)
{
	std::wstring::iterator p1;
	std::wstring::iterator p1End = inoutString.end();
	for(p1 = inoutString.begin(); p1 != p1End; p1++)
	{
		*p1 = tolower(*p1);
	}
}