#include "NGDBDefined.h"
#include "DataReference.h"

DataReference::DataReference(void)
{
	pRefCount = new unsigned long;
	*pRefCount = 0;
}
DataReference::DataReference(const DataReference& temp)
{
	pRefCount = temp.pRefCount;
	if(pRefCount!=NULL)
		(*pRefCount)++;
}
DataReference::~DataReference(void)
{
	if(pRefCount!=NULL)
	{
		if(*pRefCount == 0)
			delete pRefCount;
		else
			(*pRefCount)--;
	}
}

// 产生一个新的数据引用
void DataReference::GenerateNewRef(void)
{
	//如果计数已为0，表示并不与其他实例共享数据,则不必重新分配
	if(pRefCount !=NULL && *pRefCount!=0)
	{
		//脱离原来的引用
		(*pRefCount) --;
		pRefCount = NULL;
	}

	if(pRefCount == NULL)
	{
		pRefCount = new unsigned long;
		*pRefCount = 0;
	}

}

//判断当前是否是唯一索引
bool DataReference::IsOnly(void)
{
	if(pRefCount == NULL || *pRefCount == 0)
		return true;
	return false;
}

void DataReference::ClearRef(void)
{
	//如果计数已为0，表示并不与其他实例共享数据则不用删除
	if(pRefCount !=NULL && *pRefCount!=0)
	{
		//脱离原来的引用
		(*pRefCount) --;
		pRefCount = NULL;
	}
}

void DataReference::AddRef(const DataReference& temp)
{

	if(this!=&temp)
	{
		//如果计数已为0，表示并不与其他实例共享数据,则不必重新分配
		if(pRefCount !=NULL && (*pRefCount!=0))
		{
			//脱离原来的引用
			(*pRefCount) --;
			pRefCount = NULL;
		}
		if((pRefCount!=NULL)&&(*pRefCount == 0))
			delete pRefCount;
		//附加到新的索引上
		pRefCount = temp.pRefCount;
		if(pRefCount!=NULL)
			(*pRefCount)++;
	}
}
