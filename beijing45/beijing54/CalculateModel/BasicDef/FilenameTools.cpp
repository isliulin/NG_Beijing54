//#include "stdafx.h"
#include "FilenameTools.h"

//移除文件全路径中的文件名 --即获取文件路径
BOOL CFilenameTools::PathRemoveFileA(std::string &rfilename)
{
	int nEnd = rfilename.rfind(_T('\\'));
	if(nEnd < 0)
	{
		nEnd = rfilename.rfind(_T('/'));
		if(nEnd < 0)
		{
			return FALSE;
		}
	}

	rfilename = rfilename.substr(0, nEnd);
	return TRUE;
}

BOOL CFilenameTools::PathRemoveFileW(std::wstring &rfilename)
{
	int nEnd = rfilename.rfind(_T('\\'));
	if(nEnd < 0)
	{
		nEnd = rfilename.rfind(_T('/'));
		if(nEnd < 0)
		{
			return FALSE;
		}
	}

	rfilename = rfilename.substr(0, nEnd);
	return TRUE;
}

//移除文件全路径中的文件名  --获取文件所在的路径
BOOL CFilenameTools::PathRemoveFile(tstring &rfilename)
{
#ifdef UNICODE
	return PathRemoveFileW(rfilename);
#else
	return PathRemoveFileA(rfilename);
#endif
}

//判断文件是否存在
BOOL CFilenameTools::IsFileExist(LPCTSTR szFilePath)
{
	HANDLE hFind;
	WIN32_FIND_DATA dataFind = {0};
	hFind = FindFirstFile(szFilePath, &dataFind);

	if (hFind==INVALID_HANDLE_VALUE) 
		return false;

	if(dataFind.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		return true;

	return false;
}

//从文件全路径中提取文件名 
tstring CFilenameTools::GetFileName(const tstring &FilePath)
{
	tstring strTmp = FilePath;
	int nEnd = strTmp.rfind(_T('\\'));
	if(nEnd < 0)
	{
		nEnd = strTmp.rfind(_T('/'));
	}

	if(nEnd >= 0)
	{
		strTmp = FilePath.substr(nEnd+1, FilePath.length() - nEnd);
	}
	
	return strTmp;
}

//获取不包含文件后缀的文件名
tstring CFilenameTools::GetFileNameNoSuffix(const tstring &FilePath)
{
	tstring strFileName = GetFileName(FilePath);
	int nEnd = strFileName.rfind(_T('.'));
	if(nEnd >= 0)
	{
		strFileName = strFileName.substr(0, nEnd);
	}
	
	return strFileName;
}