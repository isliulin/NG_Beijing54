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
	// ����һ���µ�����Ӧ��
	void GenerateNewRef(void);
	//�ж������Ƿ�ǰΨһ����
	bool IsOnly(void);
	//��������������ʵ���Ĺ����ϵ
	void ClearRef(void);
public:
	void AddRef(const DataReference& temp);
};
#endif