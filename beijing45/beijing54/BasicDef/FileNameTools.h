#ifndef __BASICDEF_FILENAMETOOLS_h
#define __BASICDEF_FILENAMETOOLS_h
class CFilenameTools
{
public:
	//�Ƴ��ļ�ȫ·���е��ļ���  --��ȡ�ļ����ڵ�·��
	static BOOL PathRemoveFileA(std::string &rfilename);

	//�Ƴ��ļ�ȫ·���е��ļ���  --��ȡ�ļ����ڵ�·��
	static BOOL PathRemoveFileW(std::wstring &rfilename);

	//�Ƴ��ļ�ȫ·���е��ļ���  --��ȡ�ļ����ڵ�·��
	static BOOL PathRemoveFile(tstring &rfilename);

	//�ж��ļ��Ƿ����
	static BOOL IsFileExist(LPCTSTR szFilePath);

	//��ȡ�ļ�ȫ·���е��ļ���
	static tstring GetFileName(const tstring &FilePath);

	//��ȡ�������ļ���׺���ļ���
	static tstring GetFileNameNoSuffix(const tstring &FilePath);




};


#endif
