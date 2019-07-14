#include "RWMemMap.h"

#if defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#endif

RWMemMap::RWMemMap() 
: m_pData(0), 
m_Size(0)
{
#if defined(_WIN32) || defined(__WIN32__)
	m_hMapFile = NULL;		//Windows 内存映射句柄
#endif
}

RWMemMap::~RWMemMap()
{
	UnMapping();
}

bool RWMemMap::CreateMapping(unsigned long bytes)
{
	UnMapping();

#if defined(_WIN32) || defined(__WIN32__)
	m_hMapFile = CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,bytes,NULL);	
	if (m_hMapFile != NULL)
	{
		m_pData = MapViewOfFile(m_hMapFile,FILE_MAP_ALL_ACCESS,0,0,0);
		if (m_pData != NULL)
			return true;
	}
#else
	//创建匿名的内存映射
	void *pMap = mmap(0, bytes, PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,0,0);
	if (MAP_FAILED != pMap)
	{
		m_pData = pMap;
		m_Size = bytes;

		return true;
	}
#endif

	return false;
}

void RWMemMap::UnMapping()
{
#if defined(_WIN32) || defined(__WIN32__)
	if (m_hMapFile != NULL)	
	{
		CloseHandle(m_hMapFile);

		if (m_pData != NULL)
		{
			UnmapViewOfFile(m_pData);
		}
	}
	m_pData = NULL;
	m_hMapFile = NULL;
#else
	if(m_pData)
	{
		munmap(m_pData, m_Size);
		m_pData = NULL;
		m_Size = 0;
	}
#endif
}
