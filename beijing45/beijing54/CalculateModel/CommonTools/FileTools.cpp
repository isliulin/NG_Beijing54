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

//�ж��ļ��Ƿ����
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
	//ptr ��� > pFilePath,˵�����ҵ� /,����\,�����޸�Ϊ0
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
	//ptr ��� > pFilePath,˵�����ҵ� /,����\,�����޸�Ϊ0
	if (ptr > pFilePath)
		*(ptr-1) = 0;

	return true;
}

bool GetFileNameA(const char *pFilePath,char *pOutFileName)
{
	if (pFilePath == NULL || pOutFileName == NULL)
		return false;

	const char* ptr = pFilePath + strlen(pFilePath);	//���һ���ַ�
	while (ptr > pFilePath && *(ptr-1)!='/' && *(ptr-1)!='\\')
		ptr--;
	//ptr ��� > pFilePath,˵�����ҵ�
	if (ptr > pFilePath)
	{
		strcpy(pOutFileName,ptr);
	}
	else	//δ�ҵ�
	{
		strcpy(pOutFileName,pFilePath);
	}

	return true;
}

bool GetFileNameW(const wchar_t *pFilePath,wchar_t *pOutFileName)
{
	if (pFilePath == NULL || pOutFileName == NULL)
		return false;

	const wchar_t* ptr = pFilePath + wcslen(pFilePath);	//���һ���ַ�
	while (ptr > pFilePath && *(ptr-1)!='/' && *(ptr-1)!='\\')
		ptr--;
	//ptr ��� > pFilePath,˵�����ҵ�
	if (ptr > pFilePath)
	{
		wcscpy(pOutFileName,ptr);
	}
	else	//δ�ҵ�
	{
		wcscpy(pOutFileName,pFilePath);
	}

	return true;
}

bool GetFileNameNoSuffixA(const char *pFilePath,char *pOutFileName)
{
	//�Ȼ�ȡ�ļ�����
	if(GetFileNameA(pFilePath,pOutFileName))
	{
		char* ptr = pOutFileName + strlen(pOutFileName);	//���һ���ַ�
		while (ptr > pOutFileName && *(ptr-1)!='.')
			ptr--;
		//ptr ��� > pFilePath,˵�����ҵ�
		if (ptr > pOutFileName)
		{
			*(ptr-1) = 0;	//�� . ������ַ�ȥ��
		}
	}
	return true;
}

bool GetFileNameNoSuffixW(const wchar_t *pFilePath,wchar_t *pOutFileName)
{
	//�Ȼ�ȡ�ļ�����
	if(GetFileNameW(pFilePath,pOutFileName))
	{
		wchar_t* ptr = pOutFileName + wcslen(pOutFileName);	//���һ���ַ�
		while (ptr > pOutFileName && *(ptr-1)!='.')
			ptr--;
		//ptr ��� > pFilePath,˵�����ҵ�
		if (ptr > pOutFileName)
		{
			*(ptr-1) = 0;	//�� . ������ַ�ȥ��
		}
	}
	return true;
}
