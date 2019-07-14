#include "stdafx.h"
#include "NGRectangle.h"
#include <math.h>

CNGRectangle::CNGRectangle(void)
{

}

CNGRectangle::CNGRectangle(CNGPoint ptLeftBottom, CNGPoint ptRightTop)
{
	SetPoints(ptLeftBottom, ptRightTop);
}

CNGRectangle::CNGRectangle(int left, int bottom, int right, int top)
{
	SetPoints(left, bottom, right, top);
}

long CNGRectangle::Width()
{
	return abs(m_ptLeftBottom.m_nX - m_ptRightTop.m_nX) + 1;
}

// �߶�
long CNGRectangle::Height()
{
	return abs(m_ptLeftBottom.m_nY - m_ptRightTop.m_nY) + 1;
}


bool CNGRectangle::SetPoints(CNGPoint ptLeftBottom, CNGPoint ptRightTop)
{
	m_ptLeftBottom = ptLeftBottom;
	m_ptRightTop = ptRightTop;
	return true;
}

bool CNGRectangle::SetPoints(int left, int bottom, int right, int top)
{
	m_ptLeftBottom.m_nX = left;
	m_ptLeftBottom.m_nY = bottom;
	m_ptRightTop.m_nX = right;
	m_ptRightTop.m_nY = top;
	return true;
}

// ����Ϊ�������
bool CNGRectangle::SetRegular()
{
	if (m_ptLeftBottom.m_nX > m_ptRightTop.m_nX) // ���ҽ���
	{
		long nSwp			= m_ptRightTop.m_nX;
		m_ptRightTop.m_nX	= m_ptLeftBottom.m_nX;
		m_ptLeftBottom.m_nX = nSwp;
	}
	if (m_ptLeftBottom.m_nY > m_ptRightTop.m_nY)	// ���½���
	{
		long nSwp			= m_ptRightTop.m_nY;
		m_ptRightTop.m_nY	= m_ptLeftBottom.m_nY;
		m_ptLeftBottom.m_nY = nSwp;
	}
	return true;
}

// ����������εĽ����ɣ�ǰ�������������Ѿ��жϹ����н�������������
CNGRectangle CNGRectangle::GetIntersectRect(CNGRectangle rect)
{
	CNGRectangle rtReturn;
	this->SetRegular();
	rect.SetRegular();
	// ��
	if (rect.m_ptLeftBottom.m_nX > this->m_ptLeftBottom.m_nX)
	{
		rtReturn.m_ptLeftBottom.m_nX = rect.m_ptLeftBottom.m_nX;
	} 
	else
	{
		rtReturn.m_ptLeftBottom.m_nX = this->m_ptLeftBottom.m_nX;
	}
	// ��
	if (rect.m_ptLeftBottom.m_nY > this->m_ptLeftBottom.m_nY)
	{
		rtReturn.m_ptLeftBottom.m_nY = rect.m_ptLeftBottom.m_nY;
	} 
	else
	{
		rtReturn.m_ptLeftBottom.m_nY = this->m_ptLeftBottom.m_nY;
	}
	// ��
	if (rect.m_ptRightTop.m_nX < this->m_ptRightTop.m_nX)
	{
		rtReturn.m_ptRightTop.m_nX = rect.m_ptRightTop.m_nX;
	} 
	else
	{
		rtReturn.m_ptRightTop.m_nX = this->m_ptRightTop.m_nX;
	}
	// ��
	if (rect.m_ptRightTop.m_nY < this->m_ptRightTop.m_nY)
	{
		rtReturn.m_ptRightTop.m_nY = rect.m_ptRightTop.m_nY;
	} 
	else
	{
		rtReturn.m_ptRightTop.m_nY = this->m_ptRightTop.m_nY;
	}
	return rtReturn;
}

// �жϵ��Ƿ����ھ��ο���
bool CNGRectangle::IsPointInRect(const CNGPoint& point)
{
	if (point.m_nX >= m_ptLeftBottom.m_nX && point.m_nX <= m_ptRightTop.m_nX &&
		point.m_nY >= m_ptLeftBottom.m_nY && point.m_nY <= m_ptRightTop.m_nY)
	{
		return true;
	}
	else
	{
		return false;
	}
}