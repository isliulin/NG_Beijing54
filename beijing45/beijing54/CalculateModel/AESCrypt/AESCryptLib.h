//2012.9.11 jjj

#ifndef __AESCRYPT_LIB__H__
#define __AESCRYPT_LIB__H__

#include "AESCryptVersion.h"

#if !defined(_AES_EXCLUDE_AES)
#include "aes.h"
#endif

#if !defined(_AES_EXCLUDE_AESCRYPT)
#include "AESCrypt.h"
#endif

#if !defined(_AES_EXCLUDE_NETADAPTER)
#include "netadapter.h"
#endif

#if !defined(_AES_EXCLUDE_NETADAPTER_AESCRYPT)
#include "NetAdapterAESCrypt.h"
#endif

#if defined(_WIN32) || defined(__WIN32__)
//VC版本
#if _MSC_VER < 1200
#define _AESLIB_VISUALSTUDIO_VERSION "vc50"
#endif
#if _MSC_VER == 1200
#define _AESLIB_VISUALSTUDIO_VERSION "vc60"
#endif
#if _MSC_VER == 1300
#define _AESLIB_VISUALSTUDIO_VERSION "vc70"
#endif
#if _MSC_VER == 1310
#define _AESLIB_VISUALSTUDIO_VERSION "vc71"
#endif
#if _MSC_VER == 1400
#define _AESLIB_VISUALSTUDIO_VERSION "vc80"
#endif
#if _MSC_VER == 1500
#define _AESLIB_VISUALSTUDIO_VERSION "vc90"
#endif
#if _MSC_VER == 1600
#define _AESLIB_VISUALSTUDIO_VERSION "vc100"
#endif

#ifndef _AESLIB_VISUALSTUDIO_VERSION
#error "Unknown Visual Studio version"
#endif

#define _AESLIB_FILE_VERSION_STRING_(x) #x
#define _AESLIB_FILE_VERSION_STRING(x) _AESLIB_FILE_VERSION_STRING_(x)
#define _AESLIB_FILE_VERSION _AESLIB_FILE_VERSION_STRING(_AESLIB_VERSION_PREFIX)

//AESLIB为静态库,分为MT,MD两种版本
//每种版本又有debug,release两类
//每一类里再分成unioce和非unioce两种
//共2*2*2 = 8 中静态库
//MD版本的静态库后缀第一个字符为 D 
#if defined(_DLL)		//MD	//#if defined(_DLL)
	#if defined(_DEBUG)
		#if defined(_UNICODE)
			#define _AESLIB_PROJECT_CONFIGURATION "DSUD"
		#else
			#define _AESLIB_PROJECT_CONFIGURATION "DSD"
		#endif // _UNICODE
	#else
		#if defined(_UNICODE)
			#define _AESLIB_PROJECT_CONFIGURATION "DSU"
		#else
			#define _AESLIB_PROJECT_CONFIGURATION "DS"
		#endif // _UNICODE
	#endif // _DEBUG
#else						//MT
	#if defined(_DEBUG)
		#if defined(_UNICODE)
			#define _AESLIB_PROJECT_CONFIGURATION "SUD"
		#else
			#define _AESLIB_PROJECT_CONFIGURATION "SD"
		#endif // _UNICODE
	#else
		#if defined(_UNICODE)
			#define _AESLIB_PROJECT_CONFIGURATION "SU"
		#else
			#define _AESLIB_PROJECT_CONFIGURATION "S"
		#endif // _UNICODE
	#endif // _DEBUG
#endif // !defined(_AFXDLL)

#if defined(_WIN64)
#define _AESLIB_PLATFORM "x64"
#else
#define _AESLIB_PLATFORM ""
#endif

#ifndef _AESLIB_NOAUTOLINK
#pragma comment(lib, "AESCrypt"  _AESLIB_FILE_VERSION _AESLIB_VISUALSTUDIO_VERSION _AESLIB_PLATFORM _AESLIB_PROJECT_CONFIGURATION ".lib")
#pragma message("Automatically linking with AESCrypt" _AESLIB_FILE_VERSION _AESLIB_VISUALSTUDIO_VERSION _AESLIB_PLATFORM _AESLIB_PROJECT_CONFIGURATION ".lib")
#endif //_AESLIB_NOAUTOLINK

#if !defined(_DLL) && !defined(_AESLIB_NOAUTOLIBIGNORE)
#ifdef _DEBUG
#pragma comment(linker, "/NODEFAULTLIB:libcd.lib")
#else
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")
#endif
#endif
#endif


#endif // __AESCRYPT_LIB__H__