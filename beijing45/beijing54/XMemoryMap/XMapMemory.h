#pragma once
#include "XMemoryMatrix.h"

#ifdef _WIN32
#define _INT64 __int64
#else
#define _INT64 long long
#endif // _WIN32
class XMEMORYMAP_API CXMapMemory
{
protected:
	CXMapMemory(const char * pszName = NULL);
	virtual ~CXMapMemory(void);
public:
	static CXMapMemory * GetMapMemory();//获取管理数据单体
protected:
	MMatrixMap m_map;
	string m_MapName;
    bool m_bAskDelMemory;
public:
	CXMemoryMatrix * FindMatrix(const string& mapName,bool bMutex = true);
	CXMemoryMatrix * CreateMatrix(const string& mapName,unsigned int datasize);
	void ReleaseMatrix(const string& mapName);
	unsigned _INT64 GetTotalSize();
	void Clear();
	void AskDeleteMemory(bool bDelMem=true);
	bool IsAskDeleteMemory() const;
};
