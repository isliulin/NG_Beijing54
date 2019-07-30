#ifndef __FILE_TOOLS__H__
#define __FILE_TOOLS__H__

//�ж��ļ��Ƿ����
bool IsFileExistsA(const char *pFilePath);
bool IsFileExistsW(const wchar_t *pFilePath);

//��ȡ�ļ����ڵ��ļ�Ŀ¼
bool PathRemoveFileNameA(char *pFilePath);
bool PathRemoveFileNameW(wchar_t *pFilePath);

//��ȡ�ļ�����
bool GetFileNameA(const char *pFilePath,char *pOutFileName);
bool GetFileNameW(const wchar_t *pFilePath,wchar_t *pOutFileName);

//��ȡ�޺�׺�����ļ�����
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
