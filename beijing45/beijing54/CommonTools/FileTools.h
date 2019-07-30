#ifndef __FILE_TOOLS__H__
#define __FILE_TOOLS__H__

//判断文件是否存在
bool IsFileExistsA(const char *pFilePath);
bool IsFileExistsW(const wchar_t *pFilePath);

//获取文件所在的文件目录
bool PathRemoveFileNameA(char *pFilePath);
bool PathRemoveFileNameW(wchar_t *pFilePath);

//获取文件名称
bool GetFileNameA(const char *pFilePath,char *pOutFileName);
bool GetFileNameW(const wchar_t *pFilePath,wchar_t *pOutFileName);

//获取无后缀名的文件名称
bool GetFileNameNoSuffixA(const char *pFilePath,char *pOutFileName);
bool GetFileNameNoSuffixW(const wchar_t *pFilePath,wchar_t *pOutFileName);

#ifdef  UNICODE     
	#define IsFileExists	IsFileExistsA
	#define PathRemoveFileName	PathRemoveFileNameA
	#define GetFileName			GetFileNameA
	#define GetFileNameNoSuffix GetFileNameNoSuffixA
#else   /* UNICODE */  
	#define IsFileExists	IsFileExistsW
	#define PathRemoveFileName	PathRemoveFileNameW
	#define GetFileName			GetFileNameW
	#define GetFileNameNoSuffix GetFileNameNoSuffixW
#endif /* UNICODE */ 

#endif
