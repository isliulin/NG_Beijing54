
#include <math.h>
#include "PixelIterator.h"



CDoubleRectangle::CDoubleRectangle(void)
{

}

CDoubleRectangle::CDoubleRectangle(CDoublePoint2D ptLeftBottom, CDoublePoint2D ptRightTop)
{
	SetPoints(ptLeftBottom, ptRightTop);
}

CDoubleRectangle::CDoubleRectangle(double left, double bottom, double right, double top)
{
	SetPoints(left, bottom, right, top);
}




bool CDoubleRectangle::SetPoints(CDoublePoint2D ptLeftBottom, CDoublePoint2D ptRightTop)
{
	m_ptLeftBottom = ptLeftBottom;
	m_ptRightTop = ptRightTop;
	return true;
}

bool CDoubleRectangle::SetPoints(double left, double bottom, double right, double top)
{
	m_ptLeftBottom.x = left;
	m_ptLeftBottom.y = bottom;
	m_ptRightTop.x = right;
	m_ptRightTop.y = top;
	return true;
}

// 设置为规则矩形
bool CDoubleRectangle::SetRegular()
{
	if (m_ptLeftBottom.x > m_ptRightTop.x) // 左右交换
	{
		long nSwp			= m_ptRightTop.x;
		m_ptRightTop.x	= m_ptLeftBottom.x;
		m_ptLeftBottom.x = nSwp;
	}
	if (m_ptLeftBottom.y > m_ptRightTop.y)	// 上下交换
	{
		long nSwp			= m_ptRightTop.y;
		m_ptRightTop.y	= m_ptLeftBottom.y;
		m_ptLeftBottom.y = nSwp;
	}
	return true;
}

// 获得两个矩形的交集∩，前提是两个矩形已经判断过必有交集条件下适用
CDoubleRectangle CDoubleRectangle::GetIntersectRect(CDoubleRectangle rect)
{
	CDoubleRectangle rtReturn;
	this->SetRegular();
	rect.SetRegular();
	// 左
	if (rect.m_ptLeftBottom.x > this->m_ptLeftBottom.x)
	{
		rtReturn.m_ptLeftBottom.x = rect.m_ptLeftBottom.x;
	} 
	else
	{
		rtReturn.m_ptLeftBottom.x = this->m_ptLeftBottom.x;
	}
	// 下
	if (rect.m_ptLeftBottom.y > this->m_ptLeftBottom.y)
	{
		rtReturn.m_ptLeftBottom.y = rect.m_ptLeftBottom.y;
	} 
	else
	{
		rtReturn.m_ptLeftBottom.y = this->m_ptLeftBottom.y;
	}
	// 右
	if (rect.m_ptRightTop.x < this->m_ptRightTop.x)
	{
		rtReturn.m_ptRightTop.x = rect.m_ptRightTop.x;
	} 
	else
	{
		rtReturn.m_ptRightTop.x = this->m_ptRightTop.x;
	}
	// 上
	if (rect.m_ptRightTop.y < this->m_ptRightTop.y)
	{
		rtReturn.m_ptRightTop.y = rect.m_ptRightTop.y;
	} 
	else
	{
		rtReturn.m_ptRightTop.y = this->m_ptRightTop.y;
	}
	return rtReturn;
}

// 判断点是否落在矩形框内
bool CDoubleRectangle::IsPointInRect(const CDoublePoint2D& point)
{
	if (point.x >= m_ptLeftBottom.x && point.x <= m_ptRightTop.x &&
		point.y >= m_ptLeftBottom.y && point.y <= m_ptRightTop.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

CRectInfo::CRectInfo(double pixelSize,
				   double minEasting,
				   double minNorthing,
				   double maxEasting,	
				   double maxNorthing) :
CDoubleRectangle(minEasting,
		minNorthing,
		maxEasting,	
		maxNorthing),
		m_nPixelSize(pixelSize)
{
}


CRectInfo::CRectInfo(const CRectInfo& rectInfo)
{
	*this = rectInfo;
}


/// Assignment operator
void CRectInfo::operator=(const CRectInfo& rectInfo)
{
	CDoubleRectangle& intRect = *this;
	intRect = (CDoubleRectangle&) rectInfo;
	m_nPixelSize = rectInfo.GetPixelSize();
}


long CRectInfo::GetNoOfPixelsX() const
{
	double size = m_ptRightTop.x- m_ptLeftBottom.x ;
	if(size < 0 || m_nPixelSize <= 0) return 0;
	return ceil((double)size/m_nPixelSize);	//不满一栅格的，补全一栅格
}

long CRectInfo::GetNoOfPixelsY() const 
{
	double size = m_ptRightTop.y - m_ptLeftBottom.y;
	if(size < 0 || m_nPixelSize <= 0) return 0;
	return ceil((double)size/m_nPixelSize);//不满一栅格的，补全一栅格
}




long 
CRectInfo::GetIndexForXCoord(double x) const
{
	long index = (x - m_ptLeftBottom.x)/m_nPixelSize;

	return index;
}

long CRectInfo::GetIndexForYCoord(double y) const
{
	long index = (y - m_ptLeftBottom.y)/m_nPixelSize;

	return index;
}


void
CRectInfo::clear()
{
	m_nPixelSize = 0;
}

// class CPixelIterator实现
CPixelIterator::CPixelIterator(const CRectInfo& rectInfo) :
m_rectInfo(rectInfo)
{
	m_nPixelSize = rectInfo.GetPixelSize();
	m_nZeroColCoord = rectInfo.GetMinEasting() + m_nPixelSize/2;
	m_nZeroRowCoord = rectInfo.GetMinNorthing() + m_nPixelSize/2;

	m_nLeftPixelNumber = 0;
	m_nRightPixelNumber = rectInfo.GetNoOfPixelsX() - 1;
	m_nBottomPixelNumber = 0;
	m_nTopPixelNumber = rectInfo.GetNoOfPixelsY() - 1;

	initCurrentValues();
}

//**************************************************************************
//构造函数
//rectInfo 待分析的矩形框
//leftBorderInMeter: 要计算交叉区域的矩形区域的左边界
//bottomBorderInMeter 下边界
//rightBorderInMeter 右边界
//topBorderInMeter 上边界
//**************************************************************************
CPixelIterator::CPixelIterator(const CRectInfo& rectInfo, 
							   double leftBorderInMeter,
							   double bottomBorderInMeter,
							   double rightBorderInMeter,
							   double topBorderInMeter) :
m_rectInfo(rectInfo)
{
	m_nPixelSize = rectInfo.GetPixelSize();
	m_nZeroColCoord = rectInfo.GetMinEasting()+ m_nPixelSize/2;
	m_nZeroRowCoord = rectInfo.GetMinNorthing() + m_nPixelSize/2;

    //无交集
	//重叠不满1栅格
	if(leftBorderInMeter>(rectInfo.GetMaxEasting()-m_nPixelSize)||bottomBorderInMeter>(rectInfo.GetMaxNorthing()-m_nPixelSize)) 
	{
		m_nLeftPixelNumber=m_nBottomPixelNumber=m_nRightPixelNumber=m_nTopPixelNumber=-1;
		m_bIterator=false;
		return ;
	}

	//重叠不满1栅格
	if(rightBorderInMeter<(rectInfo.GetMinEasting()-m_nPixelSize)||topBorderInMeter<(rectInfo.GetMinNorthing()-m_nPixelSize)) 
	{
		m_nLeftPixelNumber=m_nBottomPixelNumber=m_nRightPixelNumber=m_nTopPixelNumber=-1;
        m_bIterator=false;
		return ;
	}

	m_bIterator=true;
    m_nLeftPixelNumber=(leftBorderInMeter-rectInfo.GetMinEasting())/ m_nPixelSize;
	m_nBottomPixelNumber=(bottomBorderInMeter-rectInfo.GetMinNorthing())/ m_nPixelSize;
    m_nRightPixelNumber= (rightBorderInMeter-rectInfo.GetMinEasting())/ m_nPixelSize-1;
	m_nTopPixelNumber =(topBorderInMeter-rectInfo.GetMinNorthing())/ m_nPixelSize-1;


	if(m_nLeftPixelNumber<0)m_nLeftPixelNumber=0;
	if(m_nBottomPixelNumber<0)m_nBottomPixelNumber=0;
	
    //右上顶点不能超过范围
    if(m_nRightPixelNumber>(rectInfo.GetNoOfPixelsX()-1))m_nRightPixelNumber=rectInfo.GetNoOfPixelsX()-1;
	if(m_nTopPixelNumber>(rectInfo.GetNoOfPixelsY()-1))m_nTopPixelNumber=rectInfo.GetNoOfPixelsY()-1;
    

	initCurrentValues();
}

//
void 
CPixelIterator::initCurrentValues()
{ 
	m_nCurColPixelNumber = m_nLeftPixelNumber - 1;
	m_nCurRowPixelNumber = m_nBottomPixelNumber - 1;
	m_nCurColCoord = m_nZeroColCoord + m_nCurColPixelNumber * m_nPixelSize;
	m_nCurRowCoord = m_nZeroRowCoord + m_nCurRowPixelNumber * m_nPixelSize;
}

//
bool CPixelIterator::nextRow()
{
    if(m_nLeftPixelNumber==-1||m_nBottomPixelNumber==-1||m_nRightPixelNumber==-1||m_nTopPixelNumber==-1)
    {
       return false;
    }
	// Stop if next row is outside the intersected rectangle
	if(m_nCurRowPixelNumber >= m_nTopPixelNumber) {
		return false;
	}

	// Advance the row number and coordinate
	++m_nCurRowPixelNumber;
	m_nCurRowCoord += m_nPixelSize;	

	// Move one column in front of the intersecting interval
	m_nCurColPixelNumber = m_nLeftPixelNumber - 1;
	m_nCurColCoord = m_nZeroColCoord + m_nCurColPixelNumber * m_nPixelSize;;
	return true;
}


//
bool CPixelIterator::nextColumn()
{

    if(m_nLeftPixelNumber==-1||m_nBottomPixelNumber==-1||m_nRightPixelNumber==-1||m_nTopPixelNumber==-1)
    {
       return false;
    }
	if(m_nCurColPixelNumber >= m_nRightPixelNumber)
	{
		// If not, there is no successor column in this row
		return false;
	}

	else
	{
		// Advance one column within the same interval
		++m_nCurColPixelNumber;
		m_nCurColCoord += m_nPixelSize;
		return true;
	}
}
