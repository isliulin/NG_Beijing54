#include "XMemoryMatrix.h"
#include "XMapMemory.h"
#include "XMutexSem.h"
#if defined(_WIN32)||defined(_WIN64)
#include <windows.h>
#define __USEWINDOWS 1
#else
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#endif

CXMemoryMatrix::CXMemoryMatrix(const string& mapName,CXMapMemory * pMemoryMap)
{
	m_memoryMap = pMemoryMap;
	m_mapName = mapName;
	m_usedindex = 0;
	m_pData = 0;
	m_memsize = 0;
	m_pMapHandle = 0;
	m_bIsAllocData = false;
}

CXMemoryMatrix::~CXMemoryMatrix(void)
{
	if(!m_bIsAllocData)
	{
#ifdef __USEWINDOWS
		if(m_pData)
			UnmapViewOfFile(m_pData);
		if(m_pMapHandle)
			CloseHandle(m_pMapHandle);
#else
		if(m_pData)
			munmap(m_pData,m_memsize);
#endif
	}
	else
	{
		delete []((char*)m_pData);
	}

	m_pData = NULL;
	m_pMapHandle = NULL;
	m_memsize = 0;
}

void * CXMemoryMatrix::InitMemory( unsigned int datasize)
{
	CXMutexSem mutex;
	mutex.Lock();
	if(m_pData!=0)
	{
		mutex.UnLock();
		return m_pData;
	}

#ifdef __USEWINDOWS
	string mapName = m_mapName;
	mapName.replace(0,3,"Global\\");
	//去除空格
	size_t findSpace = string::npos;
	while((findSpace=mapName.find(' '))!=string::npos)
	{
		mapName.erase(findSpace,1);
	}
	//内存映射
	if(m_pMapHandle == NULL)
		m_pMapHandle = OpenFileMappingA(FILE_MAP_ALL_ACCESS,FALSE,mapName.c_str());
	if(m_pMapHandle==NULL)
	{
		m_pMapHandle = CreateFileMappingA(INVALID_HANDLE_VALUE,
		NULL,PAGE_READWRITE,0,datasize,mapName.c_str());
	}
	if(m_pMapHandle!=NULL)
	{
		m_pData = MapViewOfFile(m_pMapHandle,FILE_MAP_ALL_ACCESS,0,0,datasize);
		m_memsize = datasize;
	}
#else
	void *pMap = mmap(0, datasize, PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,0,0);
	if (MAP_FAILED != pMap)
	{
		m_pData = pMap;
		m_memsize = datasize;
	}
#endif
	try
	{
		if(m_pData == 0)
		{
			m_pData = (void *)new char[datasize];

			if(m_pData!=NULL)
			{
				m_memsize = datasize;
				m_bIsAllocData = true;
			}
		}
	}
	catch(...)
	{

	}

	//如果内存分配失败,可以要求释放一些无用的内存
	if(m_memoryMap!=0)
	{
		m_memoryMap->AskDeleteMemory(m_pData==NULL);
	}
	mutex.UnLock();

	return m_pData;
}

void * CXMemoryMatrix::GetMemory()
{
#ifdef __USEWINDOWS
	if(m_pData==NULL && m_pMapHandle!=NULL)
		m_pData = MapViewOfFile(m_pMapHandle,FILE_MAP_ALL_ACCESS,0,0,m_memsize);
#endif
	return m_pData;
}

void * CXMemoryMatrix::GetMemory() const
{
	return m_pData;
}

unsigned int CXMemoryMatrix::GetMemorySize() const
{
	return m_memsize;
}

void CXMemoryMatrix::FlashMemory()
{
#ifdef __USEWINDOWS
	if(m_pMapHandle!=NULL && m_pData!=NULL)
		FlushViewOfFile(m_pData,m_memsize);
#endif
}

void CXMemoryMatrix::UmMapData()
{
#ifdef __USEWINDOWS
	if(m_pMapHandle!=NULL&&m_pData!=NULL)
	{
		UnmapViewOfFile(m_pData);
		m_pData = 0;
	}
#endif
}
