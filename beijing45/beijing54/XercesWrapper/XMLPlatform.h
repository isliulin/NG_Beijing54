#ifndef INCLUDED_XMLPLATFORM_H
#define INCLUDED_XMLPLATFORM_H

#if defined(XERCESWRAPPER_LIB)
	#define XML_API
#else
	#if defined(_WIN32) || defined(__WIN32__)
		#ifdef XERCESWRAPPER_EXPORTS
			#define XML_API __declspec(dllexport)
		#else
			#define XML_API __declspec(dllimport)
		#endif 
	#else 
		#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
			#define XML_API __attribute__ ((visibility("default")))
		#else
			#define XML_API
		#endif	// __GNUC__		
	#endif		// WIN32 / !WIN32
#endif

#endif