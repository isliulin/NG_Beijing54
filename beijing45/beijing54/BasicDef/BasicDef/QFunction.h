#pragma once

#define QTABLE_NUM 40
#define QITABLE_NUM 99
struct QValue
{
	double dx;   //����
	double dy;   //������Ӧ��ֵ
};
class CQFunction
{
public:
	CQFunction(void);
	~CQFunction(void);

public:
	//Q function table
	static QValue m_QTable[QTABLE_NUM];

	//Q inverse function table
	static QValue m_QITable[QITABLE_NUM];

public://�����ľ�̬��Ա����
	//��������ı���ֵ����ȡ��QFunction��Ӧ��ֵ
	static double QFunction(double inValue);

	//��������QFunction��ֵ����ȡ�Ա�����ֵ
	static double InverseQFunction(double inValue);
};
