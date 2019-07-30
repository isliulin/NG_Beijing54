#ifndef _XMEMORY__MAP__HEAD__H__
#define _XMEMORY__MAP__HEAD__H__

#if defined(XMEMORYMAP_LIB)
#define XMEMORYMAP_API
#else
#if defined(_WIN32) || defined(__WIN32__)
#ifdef XMEMORYMAP_EXPORTS
#define XMEMORYMAP_API __declspec(dllexport)
#else
#define XMEMORYMAP_API __declspec(dllimport)
#endif 
#else 
#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#define XMEMORYMAP_API __attribute__ ((visibility("default")))
#else
#define XMEMORYMAP_API
#endif	// __GNUC__		
#endif		// WIN32 / !WIN32
#endif
#endif