#pragma once
#include "DataTypes.h"

class CNGPoint
{
public:
	// ������
	long m_nX;
	// ������
	long m_nY;
	
	// ����
	CNGPoint(void):m_nX(0), m_nY(0)
	{

	}
	// �вι��캯��
	CNGPoint(long x, long y):m_nX(x), m_nY(y)
	{

	}
	// �ж�������������
	bool operator == (CNGPoint& refPoint);

};


/************************************************************************/
// CNGRectangle��
// ����:������
/************************************************************************/
class CNGRectangle
{
protected:
	// ���½�
	CNGPoint m_ptLeftBottom;
	// ���Ͻ�
	CNGPoint m_ptRightTop;

public:
	CNGRectangle(void);
	CNGRectangle(CNGPoint ptLeftBottom, CNGPoint ptRightTop);
	CNGRectangle(int left, int bottom, int right, int top);

	// ���
	long Width();
	// �߶�
	long Height();


	bool SetPoints(CNGPoint ptLeftBottom, CNGPoint ptRightTop);
	bool SetPoints(int left, int bottom, int right, int top);
	// ����������εĽ�����
	CNGRectangle GetIntersectRect(CNGRectangle rect);
	// ����Ϊ�������
	bool SetRegular();
	// �жϵ��Ƿ����ھ��ο���
	bool IsPointInRect(const CNGPoint& point);

	CNGPoint GetLeftBottomPoint(){return m_ptLeftBottom;}
	CNGPoint GetRightTopPoint(){return m_ptRightTop;}
	
};