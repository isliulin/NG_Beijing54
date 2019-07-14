#pragma once
#include <string>
#include <vector>
using namespace std;

#include <time.h>


class XmlStringManager
{
public:
	XmlStringManager(void);
	virtual ~XmlStringManager(void);
	static bool IsEmptyString(const char * str);
	static bool IsSameString(const char * str1, const char * str2);
	static bool IsSameNString(const char * str1, const char * str2,int n);
	static bool IsSameStringNoCase(const char * str1, const char * str2);
	static bool IsSameNStringNoCase(const char * str1, const char * str2,int n);
	static void SpliteString(const char * str,vector<string>& strlist,char c=' ');
	static bool SpliteKeyValue(const char*str,string& key ,string &value);
	static string GetFilePath(const char * filename);
	static string GetFileSuffix(const char * filename);
	static string GetFileName(const char*filename,bool bsuffix=false);
	static void SpliteCSVString(const char * str,vector<string>& strlist);
	static string CleanCSVString(const char*p1,const char* p2);
	static double ToDouble(const char*str);
	static int ToInt(const char*str);
	
	static tm ToTime(const char*str);

	static bool IsAllAscii(const char*str);
	static void UnicodeToUTF_8(char* pOut,const wchar_t* pText);

	static void GBKToUTF8(string & o_UTF,const char * i_pGBK);
	static void UTF8ToGBK(string & o_GBK,const char * i_pUTF8);
};

