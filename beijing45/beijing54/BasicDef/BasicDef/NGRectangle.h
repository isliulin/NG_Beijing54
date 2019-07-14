#pragma once
#include "DataTypes.h"

class CNGPoint
{
public:
	// 横坐标
	long m_nX;
	// 纵坐标
	long m_nY;
	
	// 构造
	CNGPoint(void):m_nX(0), m_nY(0)
	{

	}
	// 有参构造函数
	CNGPoint(long x, long y):m_nX(x), m_nY(y)
	{

	}
	// 判断相等运算符重载
	bool operator == (CNGPoint& refPoint);

};


/************************************************************************/
// CNGRectangle类
// 描述:矩形类
/************************************************************************/
class CNGRectangle
{
protected:
	// 左下角
	CNGPoint m_ptLeftBottom;
	// 右上角
	CNGPoint m_ptRightTop;

public:
	CNGRectangle(void);
	CNGRectangle(CNGPoint ptLeftBottom, CNGPoint ptRightTop);
	CNGRectangle(int left, int bottom, int right, int top);

	// 宽度
	long Width();
	// 高度
	long Height();


	bool SetPoints(CNGPoint ptLeftBottom, CNGPoint ptRightTop);
	bool SetPoints(int left, int bottom, int right, int top);
	// 获得两个矩形的交集∩
	CNGRectangle GetIntersectRect(CNGRectangle rect);
	// 设置为规则矩形
	bool SetRegular();
	// 判断点是否落在矩形框内
	bool IsPointInRect(const CNGPoint& point);

	CNGPoint GetLeftBottomPoint(){return m_ptLeftBottom;}
	CNGPoint GetRightTopPoint(){return m_ptRightTop;}
	
};