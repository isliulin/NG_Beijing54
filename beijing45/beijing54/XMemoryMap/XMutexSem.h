#pragma once
#include "XMemoryMapHead.h"
#include <string>
class XMEMORYMAP_API CXMutexSem
{
public:
	CXMutexSem(const char * name = NULL);
	virtual ~CXMutexSem(void);
protected:
	void * m_pObj;
	int semid;
	std::string m_name;
protected:
	void CreateMutexObj();
public:
	void Lock();
	void UnLock();
	bool IsValidObj() const;
};
