#pragma once
#include "ExportDll.h"
#include "NGString.h"

typedef NGString STDString;


#include <time.h>

#ifdef _MSC_VER
typedef unsigned __int64 u_ng_int64;
#else
#include <inttypes.h>
typedef uint64_t u_ng_int64;
#endif


#ifndef COLORREF
typedef unsigned long COLORREF ;
#endif
#ifndef RGB
#define RGB(r,g,b) (COLORREF)(((r)&0xFF)|((g)&0xFF)<<8|((b)&0xFF)<<16)
#define GetRValue(c) ((BYTE)(c&0xFF))
#define GetGValue(c) ((BYTE)((c>>8)&0xFF))
#define GetBValue(c) ((BYTE)((c>>16)&0xFF))
#endif


class NGSTRING_API NGStringManager
{
public:
	NGStringManager(void);
	virtual ~NGStringManager(void);
	static bool IsEmptyString(const char * str);
	static bool IsSameString(const char * str1, const char * str2);
	static bool IsSameNString(const char * str1, const char * str2,int n);
	static bool IsSameStringNoCase(const char * str1, const char * str2);
	static bool IsSameNStringNoCase(const char * str1, const char * str2,int n);
	static void SpliteString(const char * str,NGVector<NGString>& strlist,char c=' ');
	static bool SpliteKeyValue(const char*str,NGString& key ,NGString &value);
	static NGString GetFilePath(const char * filename);
	static NGString GetFileSuffix(const char * filename);
	static NGString GetFileName(const char*filename,bool bsuffix=false);
	static bool CheckFileAccess(const char *filename,int mode=0);
	static void ListFileInPath(const char * dir,NGVector<NGString>& filelist,bool deep = false);
	static void ListSubDirInPath(const char * dir,NGVector<NGString>& dirlist);
	static void ConvertToUnixFilePath(NGString & path);
	static bool MakeDirectory(const char * dir);

	static void SpliteCSVString(const char * str,NGVector<NGString>& strlist);
	static NGString CleanCSVString(const char*p1,const char* p2);
	static double ToDouble(const char*str);
	static int ToInt(const char*str);
	static u_ng_int64 ToUInt64(const char * str);

	static void ConvertFromInt(char * buf,int iV);
	static void ConvertFromUInt64(char * buf, u_ng_int64 i64V);
	static void ConvertFromDouble(char* buf, double dV,int iPres =8);
	static void ConvertFromFloat(char * buf,float fV,int iPres = 8);

	
	static tm ToTime(const char*str);

	static COLORREF ToColor(const char*str);
	static COLORREF MapToColor(const char*str);
	static bool IsAllAscii(const char*str);
	static bool IsUTF8NGString(const char * str);
	static void UnicodeToUTF_8(char* pOut,const wchar_t* pText);
	static void ANSIToUTF8( char *pOut,const char* pText );
	
	static void GBKToUTF8(NGString & o_UTF,const char * i_pGBK);
	static void UTF8ToGBK(NGString & o_GBK,const char * i_pUTF8);

	static int code_convert( const char* from_charset, const char* to_charset, const char* inbuf,size_t inlen, char* outbuf, size_t outlen );
	
	static bool  IsLittleEndian();
	static void Swapnbytes(void * data,int n);

	static NGString GetCurrentTimeString();
	static u_ng_int64 GetCurrentTimeInit64();
};

#ifndef IS_LittleEndian
#define IS_LittleEndian NGStringManager::IsLittleEndian()
#endif

#ifndef SWAP_DATA_ORDER
#define SWAP_DATA_ORDER(X) NGStringManager::Swapnbytes(&X,sizeof(X))
#endif

#ifndef IF_SWAP_DTAT_ORDER
#define IF_SWAP_DTAT_ORDER(F,X) if(F) SWAP_DATA_ORDER(X);
#endif