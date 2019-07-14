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

// ����һ���µ���������
void DataReference::GenerateNewRef(void)
{
	//���������Ϊ0����ʾ����������ʵ����������,�򲻱����·���
	if(pRefCount !=NULL && *pRefCount!=0)
	{
		//����ԭ��������
		(*pRefCount) --;
		pRefCount = NULL;
	}

	if(pRefCount == NULL)
	{
		pRefCount = new unsigned long;
		*pRefCount = 0;
	}

}

//�жϵ�ǰ�Ƿ���Ψһ����
bool DataReference::IsOnly(void)
{
	if(pRefCount == NULL || *pRefCount == 0)
		return true;
	return false;
}

void DataReference::ClearRef(void)
{
	//���������Ϊ0����ʾ����������ʵ��������������ɾ��
	if(pRefCount !=NULL && *pRefCount!=0)
	{
		//����ԭ��������
		(*pRefCount) --;
		pRefCount = NULL;
	}
}

void DataReference::AddRef(const DataReference& temp)
{

	if(this!=&temp)
	{
		//���������Ϊ0����ʾ����������ʵ����������,�򲻱����·���
		if(pRefCount !=NULL && (*pRefCount!=0))
		{
			//����ԭ��������
			(*pRefCount) --;
			pRefCount = NULL;
		}
		if((pRefCount!=NULL)&&(*pRefCount == 0))
			delete pRefCount;
		//���ӵ��µ�������
		pRefCount = temp.pRefCount;
		if(pRefCount!=NULL)
			(*pRefCount)++;
	}
}
