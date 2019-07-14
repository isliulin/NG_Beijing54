#ifndef __CONTOURDLL_H__
#define __CONTOURDLL_H__

#if defined(CONTOURDLL_LIB)|| defined(_LIB)
	#define CON_API
#else
	#if defined(_WIN32) || defined(__WIN32__)
		#ifdef CONTOURMODULE_EXPORTS
			#define CON_API __declspec(dllexport)
		#else
			#define CON_API __declspec(dllimport)
		#endif // CONTOURMODULE_EXPORTS
	#else 
		#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
			#define CON_API __attribute__ ((visibility("default")))
		#else
			#define CON_API
		#endif	// __GNUC__		
	#endif		// WIN32 / !WIN32
#endif			// CONTOURDLL_LIB

#endif   /* __CONTOURDLL_DLL_H_ */