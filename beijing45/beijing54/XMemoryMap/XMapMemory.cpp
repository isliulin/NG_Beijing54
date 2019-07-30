#include "XMapMemory.h"
#include "XMutexSem.h"

CXMapMemory::CXMapMemory(const char * pszName)
{
	if(pszName!=NULL)
		m_MapName = pszName;
	else
		m_MapName = "XMapMemory";
	m_bAskDelMemory = false;
}

CXMapMemory::~CXMapMemory(void)
{
	Clear();
}

CXMapMemory * CXMapMemory::GetMapMemory()
{
	static CXMapMemory mapMem;
	return &mapMem;
}

CXMemoryMatrix * CXMapMemory::FindMatrix( const string& mapName,bool bMutex )
{
	CXMemoryMatrix * pMatrix = NULL;
	CXMutexSem mutex(m_MapName.c_str());
	if(bMutex)
		mutex.Lock();
	MMatrixIterator findIt = m_map.find(mapName);
	if(findIt==m_map.end())
	{
		if(bMutex)
			mutex.UnLock();
		return NULL;
	}
	else
	{
		CXMemoryMatrix * pMatrix = findIt->second;
		if(pMatrix!=NULL)
			pMatrix->m_usedindex ++;
	}
	if(bMutex)
		mutex.UnLock();
	return pMatrix;
}

CXMemoryMatrix * CXMapMemory::CreateMatrix( const string& mapName,unsigned int datasize )
{

	CXMemoryMatrix * pMatrix = NULL;
	CXMutexSem mutex(m_MapName.c_str());
	mutex.Lock();
	pMatrix = FindMatrix(mapName,false);
	if(pMatrix==NULL)
	{
		pMatrix = new CXMemoryMatrix(mapName,this);
		if(pMatrix!=NULL)
		{
			if(datasize>0)
				pMatrix->InitMemory(datasize);
			pMatrix->m_usedindex++;
			m_map.insert(make_pair(mapName,pMatrix));
		}
	}
	mutex.UnLock();
	return pMatrix;
}

void CXMapMemory::ReleaseMatrix( const string& mapName )
{
	CXMemoryMatrix * pMatrix = NULL;
	CXMutexSem mutex(m_MapName.c_str());
	mutex.Lock();
	MMatrixIterator findIt = m_map.find(mapName);
	if(findIt!=m_map.end())
		pMatrix = findIt->second;
	if(pMatrix!=NULL)
	{
		if(pMatrix->m_usedindex>0)
			pMatrix->m_usedindex --;
		if(pMatrix->m_usedindex == 0)
		{
			m_map.erase(findIt);
			delete pMatrix;
		}
	}
	mutex.UnLock();

}

void CXMapMemory::Clear()
{
	CXMutexSem mutex(m_MapName.c_str());
	mutex.Lock();
	CXMemoryMatrix * pMatrix = NULL;
	MMatrixIterator It;
	for(It=m_map.begin();It!=m_map.end();It++)
	{
		pMatrix = It->second;
		if(pMatrix)
			delete pMatrix;
	}
	m_map.clear();
	m_bAskDelMemory = false;
	mutex.UnLock();
}

unsigned _INT64 CXMapMemory::GetTotalSize()
{
	unsigned _INT64 totalsize = 0;
	CXMutexSem mutex(m_MapName.c_str());
	mutex.Lock();
	CXMemoryMatrix * pMatrix = NULL;
	MMatrixIterator It;
	for(It=m_map.begin();It!=m_map.end();It++)
	{
		pMatrix = It->second;
		if(pMatrix)
			totalsize += pMatrix->GetMemorySize();
	}

	mutex.UnLock();
	return totalsize;
}

void CXMapMemory::AskDeleteMemory(bool bDelMem)
{
	m_bAskDelMemory = bDelMem;
}

bool CXMapMemory::IsAskDeleteMemory() const
{
	return m_bAskDelMemory;
}
