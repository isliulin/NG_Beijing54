#ifndef __CAL__GISMAP_WRAPPER__H__
#define __CAL__GISMAP_WRAPPER__H__

#if defined(CALGISMAPWRAPPER_LIB)
	#define GISMAP_API
#else
	#if defined(_WIN32) || defined(__WIN32__)
		#ifdef CALGISMAPWRAPPER_EXPORTS
			#define GISMAP_API __declspec(dllexport)
		#else
			#define GISMAP_API __declspec(dllimport)
		#endif 
	#else 
		#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
			#define GISMAP_API __attribute__ ((visibility("default")))
		#else
			#define GISMAP_API
		#endif	// __GNUC__		
	#endif		// WIN32 / !WIN32
#endif			


#endif   /* __CAL__GISMAP_WRAPPER__H__ */