#pragma once

#include "../BasicDef/DataTypes.h"


/************************************************************************/
// CNGRectangle类
// 描述:矩形类
/************************************************************************/
class CDoubleRectangle
{
protected:
	// 左下角
	CDoublePoint2D m_ptLeftBottom;
	// 右上角
	CDoublePoint2D m_ptRightTop;

public:
	CDoubleRectangle(void);
	CDoubleRectangle(CDoublePoint2D ptLeftBottom, CDoublePoint2D ptRightTop);
	CDoubleRectangle(double left, double bottom, double right, double top);

	// 宽度
	long Width();
	// 高度
	long Height();


	bool SetPoints(CDoublePoint2D ptLeftBottom, CDoublePoint2D ptRightTop);
	bool SetPoints(double left, double bottom, double right, double top);
	// 获得两个矩形的交集∩
	CDoubleRectangle GetIntersectRect(CDoubleRectangle rect);
	// 设置为规则矩形
	bool SetRegular();
	// 判断点是否落在矩形框内
	bool IsPointInRect(const CDoublePoint2D& point);

	CDoublePoint2D GetLeftBottomPoint(){return m_ptLeftBottom;}
	CDoublePoint2D GetRightTopPoint(){return m_ptRightTop;}
	
};


//rectinfo里面不满一栅格会补齐一个栅格
class CRectInfo:
	public CDoubleRectangle
{
public://构造函数/析构函数	
	CRectInfo(double nPixelSize = 0,
		      double nMinEasting = 0,
		      double nMinNorthing = 0,
		      double nMaxEasting = 0,	
		      double nMaxNorthing = 0);

	/// 
	CRectInfo(const CRectInfo& rectInfo);

public:

	/// Assignment operator (doesn't copy the bounding polygon and the intersecting rectangle)
	void operator=(const CRectInfo& rectInfo);
	//
	long GetNoOfPixelsX() const;

	
	long GetNoOfPixelsY() const;

	/// 
	double GetPixelSize() const { return m_nPixelSize; }

	/// 
		/// Coordinate for index
	long GetIndexForXCoord(double x) const;

	/// Coordinate for index
	long GetIndexForYCoord(double y) const;

	/// 
	long GetNoOfPixels() const { return GetNoOfPixelsX()*GetNoOfPixelsY(); }

	/// The left border coordinate in meter
	double GetMinEasting() const {return m_ptLeftBottom.x;}

	/// The right border coordinate in meter
	double GetMaxEasting() const {return m_ptRightTop.x;}

	/// The bottom (south) border coordinate in meter
	double GetMinNorthing() const {return m_ptLeftBottom.y;}

	/// The top (north) border coordinate in meter
	double GetMaxNorthing() const {return m_ptRightTop.y;}


	/// 
	void clear();

	/// 
	CDoubleRectangle GetRect() const { return CDoubleRectangle(*this); }

	//设置坐标系统
	void SetCoordSys(short nCoord) { m_nCoordSys = nCoord; }

	//设置精度值
	void SetPixelSize(double nPixelSize) { m_nPixelSize = nPixelSize; }

	//设置坐标系统
	short GetCoordSys() { return m_nCoordSys; }

	//设置精度值
	double GetPixelSize() { return m_nPixelSize; }

protected:

	///精度
	double m_nPixelSize;
	
	//矩形框的坐标系序号
	short m_nCoordSys;
};

class CPixelIterator
{
public:
	// 给定的矩形框
	CPixelIterator(const CRectInfo& rectInfo);

	//rectInfo 和 给定矩形边界的交集
	CPixelIterator(const CRectInfo& rectInfo,
		double left, double bottom, double right, double top);	

    //有无交集
	bool IsIterator(){return m_bIterator;}

	//给出下一行的行号,如果没有下一行给定为-1
	bool nextRow();

	//给出下一列的列号,如果没有下一列,则给定为-1
	bool nextColumn();

	///
	inline long GetCurColPixelNumber() const {return m_nCurColPixelNumber;}

	///
	inline long GetCurRowPixelNumber() const {return m_nCurRowPixelNumber;}

	///
	inline double GetCurColCoord() const {return m_nCurColCoord;}

	///
	inline double GetCurRowCoord() const {return m_nCurRowCoord;}


private:

	///
	void initCurrentValues();

	//精度
	double m_nPixelSize;

	///第0列坐标(栅格中心点)
	double m_nZeroColCoord;

	///第0列坐标(栅格中心点)
	double m_nZeroRowCoord;

	///左边的像素坐标
	long m_nLeftPixelNumber;

	///右边像素坐标
	long m_nRightPixelNumber;

	///下边像素坐标
	long m_nBottomPixelNumber;

	///上边像素坐标
	long m_nTopPixelNumber;

	///当前列像素坐标
	long m_nCurColPixelNumber;

	///当前行像素坐标
	long m_nCurRowPixelNumber;

	///当前列坐标(栅格中心点)
	double m_nCurColCoord;

	///当前行坐标(栅格中心点)
	double m_nCurRowCoord;

	///
	const CRectInfo& m_rectInfo;

	bool m_bIterator;

	};