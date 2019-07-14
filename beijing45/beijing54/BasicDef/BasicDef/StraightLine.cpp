#include "MacroDef.h"
#include <math.h>
#include "StraightLine.h"

CStraightLine::CStraightLine(void)
{
	m_dSlope = 0.0;
	m_dConst = 0.0;
}

/************************************************************************/
// CStraightLine
// 描述：直线类构造函数
// 参数：double inSlope：斜率
// double inConst：常数项
/************************************************************************/
CStraightLine::CStraightLine(double inSlope, double inConst)
{
	m_dSlope = inSlope;
	m_dConst = inConst;
}

CStraightLine::~CStraightLine(void)
{
}

/************************************************************************/
// GetStdEquationCoeff
// 获得标准方程参数
// 输出参数：double& outXCoeff：X项系数
//	double& outYCoeff：Y项系数
//	double& outConst：常数项
//	返回值：是否获取成功
/************************************************************************/
bool CStraightLine::GetStdEquationCoeff(double& outXCoeff, double& outYCoeff, double& outConst)
{
	// 如果斜率趋近于无穷大或无穷小则将Y系数置0
	if (FloatEqu(m_dSlope, MAX_SLOPE) || FloatEqu(m_dSlope, -MAX_SLOPE))	// x = -c
	{
		outYCoeff = 0.0;
		outXCoeff = 1.0;
		outConst  = m_dConst;
	}
	else if (FloatEqu(m_dSlope, 0.0))	// y = c
	{
		outXCoeff = 0.0;
		outYCoeff = 1.0;
		outConst  = -m_dConst;
	}
	else if (m_dSlope <= 1.0 && m_dSlope >= -1.0) // y - kx - c = 0
	{
		outXCoeff = -m_dSlope;
		outYCoeff = 1.0;
		outConst  = -m_dConst;
	}
	else	// -(1/k)y + x + (c/k) = 0
	{
		outXCoeff = 1.0;
		outYCoeff = -(1.0 / m_dSlope);
		outConst  = m_dConst / m_dSlope;
	}
	return true;
}

/************************************************************************/
// GetSlopeEquationPara
// 描述：获取斜率方程系数
// 输出参数：double& outSlope：
//	double& outConst：
// 返回值：是否获取成功
/************************************************************************/
bool CStraightLine::GetSlopeEquationCoeff(double& outSlope, double& outConst)
{
	outSlope = m_dSlope;
	outConst = m_dConst;
	return true;
}


/************************************************************************/
// GetLineRelation
// 描述：获取两直线间关系
// 输出参数：CStraightLine& inLine：另一条直线
// 返回值：直线关系
/************************************************************************/
eStraightLineRelation CStraightLine::GetLineRelation(CStraightLine& inLine)
{
	if (FloatEqu(m_dSlope, MAX_SLOPE))
	{
		if (FloatEqu(inLine.m_dSlope, MAX_SLOPE))
		{
			if (FloatEqu(m_dConst, inLine.m_dConst))
			{
				return Overlap;	// 重合
			}
			else
			{
				return Parallel; // 平行
			}
		}
		else
		{
			if (FloatEqu(inLine.m_dSlope, 0.0))
			{
				return Vertical;	// 垂直
			}
			else
			{
				return Crossed;		// 相交
			}
		}
	}
	else if (FloatEqu(m_dSlope, 0.0))
	{
		if (FloatEqu(inLine.m_dSlope, 0.0))
		{
			if (FloatEqu(m_dConst, inLine.m_dConst))
			{
				return Overlap;
			}
			else
			{
				return Parallel;
			}
		}
		else
		{
			if (FloatEqu(inLine.m_dSlope, MAX_SLOPE))
			{
				return Vertical;
			}
			else
			{
				return Crossed;
			}
		}
	}
	else
	{
		if (FloatEqu(m_dSlope, inLine.m_dSlope))
		{
			if (FloatEqu(m_dConst, inLine.m_dConst))
			{
				return Overlap;
			}
			else
			{
				return Parallel;
			}
		}
		else
		{
			if (FloatEqu(m_dSlope * inLine.m_dSlope, -1.0))
			{
				return Vertical;
			}
			else
			{
				return Crossed;
			}
		}
	}
}

// 通过x值计算y值
double CStraightLine::GetY(double x)
{
	if (!FloatEqu(fabs(m_dSlope), MAX_SLOPE)) // 斜率不是无效值
	{
		return (long)(x * m_dSlope + m_dConst);
	}
	else
	{
		return 0;
	}
}

// 通过y值计算x值
double CStraightLine::GetX(double y)
{
	if (!FloatEqu(m_dSlope, 0.0)) // 斜率不为0
	{
		return (long)((y - m_dConst) / m_dSlope);
	}
	else
	{
		return 0;
	}
}

// 计算直线斜率静态函数
bool CStraightLine::CalSlopeEquationCoeff(const double& x1, const double& y1, const double& x2, const double& y2, double& outSlope, double& outConst)
{
	if (!FloatEqu((x2 - x1), 0.0))
	{
		outSlope = (y2 - y1) / (x2 - x1); // k = (y2-y1)/(x2-x1)
		outConst = y1 - (outSlope * x1); // c = y1 - kx1
	}
	else // 垂直于X轴，斜率无穷大
	{
		outSlope = MAX_SLOPE;
		outConst = -x1;
	}
	return true;
}