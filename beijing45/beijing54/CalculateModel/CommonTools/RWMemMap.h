/*
ÄÚ´æÓ³ÉäÀà
jjj 2013.7.1 
*/
#ifndef __RW_MEM__MAP__H__
#define __RW_MEM__MAP__H__

class RWMemMap
{
public:
	RWMemMap();
	virtual ~RWMemMap();
	
public:
	virtual bool CreateMapping(unsigned long bytes);
	virtual void UnMapping();
	
	virtual void* GetData(){ return m_pData; }
	virtual bool IsNewData(){return false;}
	unsigned long  GetSize(){ return m_Size; }

private:
	RWMemMap(const RWMemMap &other){};
	RWMemMap &operator=(const RWMemMap &other) { return *this;}

protected:
	void*	m_pData;
	unsigned long	m_Size;
#if defined(_WIN32) || defined(__WIN32__)
	void*	m_hMapFile;	//Windows ÄÚ´æÓ³Éä¾ä±ú
#endif	
	
};

#endif
