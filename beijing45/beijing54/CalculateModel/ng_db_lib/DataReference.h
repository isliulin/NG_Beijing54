#ifndef _I_DATAREFERENCE_H_
#define _I_DATAREFERENCE_H_


class NGDBDLL_API DataReference
{
public:
	DataReference(void);
	DataReference(const DataReference& temp);
	~DataReference(void);
protected:
	unsigned long * pRefCount;
protected:
	// 产生一个新的数据应用
	void GenerateNewRef(void);
	//判断数据是否当前唯一索引
	bool IsOnly(void);
	//脱离与其他索引实例的共享关系
	void ClearRef(void);
public:
	void AddRef(const DataReference& temp);
};
#endif