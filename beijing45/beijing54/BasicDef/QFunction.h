#pragma once

#define QTABLE_NUM 40
#define QITABLE_NUM 99
struct QValue
{
	double dx;   //变量
	double dy;   //变量对应的值
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

public://公共的静态成员函数
	//根据输入的变量值，获取其QFunction对应的值
	static double QFunction(double inValue);

	//根据输入QFunction的值，获取自变量的值
	static double InverseQFunction(double inValue);
};
