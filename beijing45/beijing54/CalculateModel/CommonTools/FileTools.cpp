#include "FileTools.h"
#include "StringTools.h"

#include <wchar.h>
#include <stdio.h>
#include <string.h>

#if defined(_WIN32) || defined(__WIN32__)
#include <io.h>
#else
#include <unistd.h>
#endif	

#pragma warning(disable:4996)

//判断文件是否存在
bool IsFileExistsA(const char *pFilePath)
{
	if (pFilePath == NULL)
		return false;

	if (access(pFilePath,0) == 0)
		return true;

	return false;
}

bool IsFileExistsW(const wchar_t *pFilePath)
{
	if (pFilePath == NULL)
		return false;

	char szTemp[1024];
	memset(szTemp,0,sizeof(szTemp));
	ws2ms(pFilePath,szTemp);
	if (access(szTemp,0) == 0)
		return true;

	return false;
}

bool PathRemoveFileNameA(char *pFilePath)
{
	if (pFilePath == NULL)
		return false;

	char* ptr = pFilePath + strlen(pFilePath);
	while (ptr > pFilePath && *(ptr-1)!='/' && *(ptr-1)!='\\')
		ptr--;
	//ptr 如果 > pFilePath,说明查找到 /,或者\,则将其修改为0
	if (ptr > pFilePath)
		*(ptr-1) = 0;

	return true;
}

bool PathRemoveFileNameW(wchar_t *pFilePath)
{
	if (pFilePath == NULL)
		return false;

	wchar_t* ptr = pFilePath + wcslen(pFilePath);
	while (ptr > pFilePath && *(ptr-1)!='/' && *(ptr-1)!='\\')
		ptr--;
	//ptr 如果 > pFilePath,说明查找到 /,或者\,则将其修改为0
	if (ptr > pFilePath)
		*(ptr-1) = 0;

	return true;
}

bool GetFileNameA(const char *pFilePath,char *pOutFileName)
{
	if (pFilePath == NULL || pOutFileName == NULL)
		return false;

	const char* ptr = pFilePath + strlen(pFilePath);	//最后一个字符
	while (ptr > pFilePath && *(ptr-1)!='/' && *(ptr-1)!='\\')
		ptr--;
	//ptr 如果 > pFilePath,说明查找到
	if (ptr > pFilePath)
	{
		strcpy(pOutFileName,ptr);
	}
	else	//未找到
	{
		strcpy(pOutFileName,pFilePath);
	}

	return true;
}

bool GetFileNameW(const wchar_t *pFilePath,wchar_t *pOutFileName)
{
	if (pFilePath == NULL || pOutFileName == NULL)
		return false;

	const wchar_t* ptr = pFilePath + wcslen(pFilePath);	//最后一个字符
	while (ptr > pFilePath && *(ptr-1)!='/' && *(ptr-1)!='\\')
		ptr--;
	//ptr 如果 > pFilePath,说明查找到
	if (ptr > pFilePath)
	{
		wcscpy(pOutFileName,ptr);
	}
	else	//未找到
	{
		wcscpy(pOutFileName,pFilePath);
	}

	return true;
}

bool GetFileNameNoSuffixA(const char *pFilePath,char *pOutFileName)
{
	//先获取文件名称
	if(GetFileNameA(pFilePath,pOutFileName))
	{
		char* ptr = pOutFileName + strlen(pOutFileName);	//最后一个字符
		while (ptr > pOutFileName && *(ptr-1)!='.')
			ptr--;
		//ptr 如果 > pFilePath,说明查找到
		if (ptr > pOutFileName)
		{
			*(ptr-1) = 0;	//将 . 后面的字符去掉
		}
	}
	return true;
}

bool GetFileNameNoSuffixW(const wchar_t *pFilePath,wchar_t *pOutFileName)
{
	//先获取文件名称
	if(GetFileNameW(pFilePath,pOutFileName))
	{
		wchar_t* ptr = pOutFileName + wcslen(pOutFileName);	//最后一个字符
		while (ptr > pOutFileName && *(ptr-1)!='.')
			ptr--;
		//ptr 如果 > pFilePath,说明查找到
		if (ptr > pOutFileName)
		{
			*(ptr-1) = 0;	//将 . 后面的字符去掉
		}
	}
	return true;
}
