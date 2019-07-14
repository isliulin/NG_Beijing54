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

// 高度
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

// 设置为规则矩形
bool CNGRectangle::SetRegular()
{
	if (m_ptLeftBottom.m_nX > m_ptRightTop.m_nX) // 左右交换
	{
		long nSwp			= m_ptRightTop.m_nX;
		m_ptRightTop.m_nX	= m_ptLeftBottom.m_nX;
		m_ptLeftBottom.m_nX = nSwp;
	}
	if (m_ptLeftBottom.m_nY > m_ptRightTop.m_nY)	// 上下交换
	{
		long nSwp			= m_ptRightTop.m_nY;
		m_ptRightTop.m_nY	= m_ptLeftBottom.m_nY;
		m_ptLeftBottom.m_nY = nSwp;
	}
	return true;
}

// 获得两个矩形的交集∩，前提是两个矩形已经判断过必有交集条件下适用
CNGRectangle CNGRectangle::GetIntersectRect(CNGRectangle rect)
{
	CNGRectangle rtReturn;
	this->SetRegular();
	rect.SetRegular();
	// 左
	if (rect.m_ptLeftBottom.m_nX > this->m_ptLeftBottom.m_nX)
	{
		rtReturn.m_ptLeftBottom.m_nX = rect.m_ptLeftBottom.m_nX;
	} 
	else
	{
		rtReturn.m_ptLeftBottom.m_nX = this->m_ptLeftBottom.m_nX;
	}
	// 下
	if (rect.m_ptLeftBottom.m_nY > this->m_ptLeftBottom.m_nY)
	{
		rtReturn.m_ptLeftBottom.m_nY = rect.m_ptLeftBottom.m_nY;
	} 
	else
	{
		rtReturn.m_ptLeftBottom.m_nY = this->m_ptLeftBottom.m_nY;
	}
	// 右
	if (rect.m_ptRightTop.m_nX < this->m_ptRightTop.m_nX)
	{
		rtReturn.m_ptRightTop.m_nX = rect.m_ptRightTop.m_nX;
	} 
	else
	{
		rtReturn.m_ptRightTop.m_nX = this->m_ptRightTop.m_nX;
	}
	// 上
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

// 判断点是否落在矩形框内
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