#ifndef __BASICDEF_FILENAMETOOLS_h
#define __BASICDEF_FILENAMETOOLS_h
class CFilenameTools
{
public:
	//移除文件全路径中的文件名  --获取文件所在的路径
	static BOOL PathRemoveFileA(std::string &rfilename);

	//移除文件全路径中的文件名  --获取文件所在的路径
	static BOOL PathRemoveFileW(std::wstring &rfilename);

	//移除文件全路径中的文件名  --获取文件所在的路径
	static BOOL PathRemoveFile(tstring &rfilename);

	//判断文件是否存在
	static BOOL IsFileExist(LPCTSTR szFilePath);

	//获取文件全路径中的文件名
	static tstring GetFileName(const tstring &FilePath);

	//获取不包含文件后缀的文件名
	static tstring GetFileNameNoSuffix(const tstring &FilePath);




};


#endif
