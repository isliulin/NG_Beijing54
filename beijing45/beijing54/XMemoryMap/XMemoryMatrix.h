#pragma once
#include "XMemoryMapHead.h"

#include <string>
#include <map>
using namespace std;

class CXMapMemory;
class XMEMORYMAP_API CXMemoryMatrix
{
protected:
	friend class CXMapMemory;
	CXMemoryMatrix(const string& mapName,CXMapMemory * pMemoryMap);
	virtual ~CXMemoryMatrix(void);
protected:
	CXMapMemory *m_memoryMap;
	string m_mapName;
	unsigned int m_usedindex;
	void * m_pData;
	unsigned int m_memsize;
	//
	void * m_pMapHandle;
	bool m_bIsAllocData;
protected:
	
public:
	void * InitMemory(unsigned int datasize);
	void * GetMemory();
	void * GetMemory() const;
	unsigned int GetMemorySize() const;
	void FlashMemory();
	void UmMapData();
};

typedef std::map<std::string,CXMemoryMatrix*> MMatrixMap;
typedef std::map<std::string,CXMemoryMatrix*>::iterator MMatrixIterator;


