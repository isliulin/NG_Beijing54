#if defined(STRINGMANAGER_LIB)|| defined(_LIB)
#define NGSTRING_API
#define NGSTRING_TEMPLATE
#else
#if defined(_WIN32) || defined(__WIN32__)
#ifdef STRINGMANAGER_EXPORTS
#define NGSTRING_API __declspec(dllexport)
#define NGSTRING_TEMPLATE __declspec(dllexport)
#else
#define NGSTRING_API __declspec(dllimport)
#pragma comment(lib,"StringManager.lib")
#define NGSTRING_TEMPLATE
#endif
#else
#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#define NGSTRING_API __attribute__ ((visibility("default")))
#define NGSTRING_TEMPLATE
#else
#define NGSTRING_API
#define NGSTRING_TEMPLATE
#endif	// __GNUC__
#endif		// WIN32 / !WIN32
#endif

