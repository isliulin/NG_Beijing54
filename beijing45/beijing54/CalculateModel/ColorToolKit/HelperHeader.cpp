#include <string.h>
#include "HelperHeader.h"
#include <algorithm>
#include <stdio.h>

#pragma warning(disable:4996)

/*
 *	转大写
 */
void ToUpperString(string &str)
{
	transform(str.begin(),str.end(),str.begin(),(int (*)(int))toupper);
}
/*
 *	转小写
 */
void ToLowerString(string &str)
{
	transform(str.begin(), str.end(), str.begin(), (int (*)(int))tolower);
}


DWORD ConvertStr2ColorData(const string &strColor)
{
	DWORD nRet = 0;
	string strColorUpper = strColor;
	ToLowerString(strColorUpper);
	DWORD r=0,g=0,b=0;
	sscanf(strColorUpper.c_str(),"#%02x%02x%02x",&r,&g,&b);
	nRet = RGB(r,g,b);
	return nRet;
}
