//#include "stdafx.h"
#include "GlobalCommonFuncs.h"

//去除tstring前后的特定字符
void TstringTrim(tstring& inString, TCHAR chTarget)
{
	std::basic_string<TCHAR>::size_type nStart = inString.find_first_not_of(chTarget);
	std::basic_string<TCHAR>::size_type nEnd = inString.find_last_not_of(chTarget);

	//全是查找的字符
	if(nStart == tstring::npos)
	{
		inString.empty(); //清空
	}
	else if(nStart > 0 || nEnd < inString.length()-1)
	{
		inString = inString.substr(nStart, nEnd - nStart + 1);
	}
}

//比较两个string串的关系 --忽略大小写
int Cmp_nocase(const tstring& str1, const tstring& str2)
{
	tstring::const_iterator p1 = str1.begin();
	tstring::const_iterator p2 = str2.begin();
	tstring::const_iterator p1End = str1.end();
	tstring::const_iterator p2End = str2.end();

	while((p1 != p1End) && (p2 != p2End))
	{
		if(toupper(*p1) < toupper(*p2))
		{
			return -1;
		}
		else if(toupper(*p1) > toupper(*p2))
		{
			return 1;
		}
		else
		{
			p1++;
			p2++;
		}
	}
	if((p1 == p1End) && (p2 == p2End))
	{
		return 0;
	}
	else if(p1 == p1End)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

//将串中的值变为大写
void AstringMakeUpper(std::string& inoutString)
{
	std::string::iterator p1;
	std::string::iterator p1End = inoutString.end();
	for(p1 = inoutString.begin(); p1 != p1End; p1++)
	{
		*p1 = toupper(*p1);
	}
}

//将串中的值变为大写
void WstringMakeUpper(std::wstring& inoutString)
{
	std::wstring::iterator p1;
	std::wstring::iterator p1End = inoutString.end();
	for(p1 = inoutString.begin(); p1 != p1End; p1++)
	{
		*p1 = toupper(*p1);
	}
}

//将串中的值变为大写
void TstringMakeUpper(tstring& inoutString)
{
#ifdef UNICODE
	WstringMakeUpper(inoutString);
#else
	AstringMakeUpper(inoutString);
#endif	
}


std::string WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen<= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen -1] = 0;
	std::string strTemp(pszDst);
	delete [] pszDst;
	return strTemp;
}
std::string ts2s(tstring& inputws)
{
#ifdef UNICODE
	return WChar2Ansi(inputws.c_str());
#else
	return inputws;
#endif
}
//Converting a Ansi string to WChar string
std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen)
{
	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
	if(nSize <= 0) return NULL;
	WCHAR *pwszDst = new WCHAR[nSize+1];
	if( NULL == pwszDst) return NULL;
	MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);
	pwszDst[nSize] = 0;
	if( pwszDst[0] == 0xFEFF) // skip Oxfeff
		for(int i = 0; i < nSize; i ++) 
			pwszDst[i] = pwszDst[i+1]; 
	std::wstring wcharString(pwszDst);
	delete pwszDst;
	return wcharString;
}
tstring s2ts(const std::string& s)
{
#ifdef UNICODE
	return Ansi2WChar(s.c_str(),s.size());
#else
	return s;
#endif	
}