#ifndef _NG_DB_DEFUNED_H_
#define _NG_DB_DEFUNED_H_

#if defined(NG_DB_LIB_LIB)|| defined(_LIB)
#define NGDBDLL_API
#else
#if defined(_WIN32) || defined(_WIN64)

#ifdef NG_DB_LIB_EXPORTS
#define NGDBDLL_API __declspec(dllexport)
#else
#define NGDBDLL_API __declspec(dllimport)
#pragma comment(lib,"ng_db_lib.lib")
#endif // NG_DB_LIB_EXPORTS
#else 
// try the gcc visibility support (see http://gcc.gnu.org/wiki/Visibility)
#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#ifndef GCC_HASCLASSVISIBILITY
#define GCC_HASCLASSVISIBILITY
#endif
#endif // __GNUC__
#if defined(GCC_HASCLASSVISIBILITY)
#define NGDBDLL_API __attribute__ ((visibility("default")))
#else
#define NGDBDLL_API
#endif	

//开关几种数据库的代码
//#define USE_SQLITE 
//#define USE_OCCI 
//#define USE_MYSQL
//#define USE_SQLSERVER
//#define USE_OCILIB

#endif // WIN32 / !WIN32
#endif // NG_DB_LIB_LIB



#ifndef interface
#define interface struct
#endif

#ifndef NULL
#define NULL 0
#endif

typedef short int16;
typedef int int32;
typedef long long int64;
typedef unsigned char byte;

typedef int32 index_int;

#include <string>
using namespace std;
typedef std::string STDstring;

#include <string.h>
#ifdef  _STRING_H
#define strcmpnocase strcasecmp
#elif defined(_INC_STRING)
#define  strcmpnocase _stricmp
#else
extern "C" NGDBDLL_API int ng_strcmpnocase(const char * str1, const char * str2);
#define strcmpnocase ng_strcmpnocase
#endif

extern "C" NGDBDLL_API void StringToTM(const char * strval,tm & tmval);

extern "C" NGDBDLL_API int * GetSupportDBType(int & DBSize);

extern "C" NGDBDLL_API char * GetDBNameByType(int DBType);
#endif