#ifndef __CAL__RESULT_WRAPPER__H__
#define __CAL__RESULT_WRAPPER__H__

#if defined(CALRESULTWRAPPER_LIB)|| defined(_LIB)
	#define RESULT_API
#else
	#if defined(_WIN32) || defined(__WIN32__)
		#ifdef CALRESULTWRAPPER_EXPORTS
			#define RESULT_API __declspec(dllexport)
		#else
			#define RESULT_API __declspec(dllimport)
			#pragma comment(lib,"CalResultWrapper.lib")
		#endif 
	#else 
		#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
			#define RESULT_API __attribute__ ((visibility("default")))
		#else
			#define RESULT_API
		#endif	// __GNUC__		
	#endif		// WIN32 / !WIN32
#endif			

//#define USE_ZLIB


#include "../BasicDef/DataTypes.h"
#include "../DataModel/EnumDef.h"
#include "../BasicDef/MacroDef.h"

#endif   /* __CAL__RESULT_WRAPPER__H__ */