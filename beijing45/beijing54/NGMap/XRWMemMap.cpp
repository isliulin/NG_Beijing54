#include "XRWMemMap.h"
#include "../XMemoryMap/XMapMemory.h"

CXRWMemMap::CXRWMemMap(const string& name)
{
	m_name = name;
	m_bIsNewData = true;
}

CXRWMemMap::~CXRWMemMap(void)
{
	UnMapping();
}

bool CXRWMemMap::CreateMapping( unsigned long bytes )
{
	CXMapMemory * pMapMemory = CXMapMemory::GetMapMemory();
	CXMemoryMatrix * pMatrix = pMapMemory->FindMatrix(m_name);
	if(pMatrix!=NULL)
		m_bIsNewData = false;
	else
	{
		pMatrix =pMapMemory->CreateMatrix(m_name,bytes);
		m_bIsNewData = true;
	}
	if(pMatrix==NULL)
		return false;
	if(bytes!=pMatrix->GetMemorySize())
	{
		pMapMemory->ReleaseMatrix(m_name);
		return false;
	}
	m_pMemoryData = pMatrix->GetMemory();
	m_Size = bytes;
	return true;

}

void CXRWMemMap::UnMapping()
{
	CXMapMemory * pMapMemory = CXMapMemory::GetMapMemory();
	pMapMemory->ReleaseMatrix(m_name);
	m_pMemoryData = NULL;
	m_Size = 0;
}

bool CXRWMemMap::IsNewData()
{
	return m_bIsNewData;
}
