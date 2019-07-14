#if defined(HDFSFILEWR_LIB)
#define HDFSWR_API
#else
#if defined(_WIN32) || defined(__WIN32__)
#ifdef HDFSFILEWR_EXPORTS
#define HDFSWR_API __declspec(dllexport)
#else
#define HDFSWR_API __declspec(dllimport)
#pragma comment(lib,"HDFSFileWR.lib")
#endif
#else
#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#define HDFSWR_API __attribute__ ((visibility("default")))
#else
#define HDFSWR_API
#endif	// __GNUC__
#endif		// WIN32 / !WIN32
#endif