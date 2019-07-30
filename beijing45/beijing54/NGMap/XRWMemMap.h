#pragma once
#include "../CommonTools/RWMemMap.h"
#include <string>
using namespace std;
class CXRWMemMap :
	public RWMemMap
{
public:
	CXRWMemMap(const string& name);
	virtual ~CXRWMemMap(void);
protected:
	string m_name;
	void * m_pMemoryData;
	bool m_bIsNewData;
public:
	virtual bool CreateMapping(unsigned long bytes);
	virtual void UnMapping();
	virtual void * GetData(){return m_pMemoryData;}
	virtual bool IsNewData();
};
