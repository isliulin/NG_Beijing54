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
// ������ֱ���๹�캯��
// ������double inSlope��б��
// double inConst��������
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
// ��ñ�׼���̲���
// ���������double& outXCoeff��X��ϵ��
//	double& outYCoeff��Y��ϵ��
//	double& outConst��������
//	����ֵ���Ƿ��ȡ�ɹ�
/************************************************************************/
bool CStraightLine::GetStdEquationCoeff(double& outXCoeff, double& outYCoeff, double& outConst)
{
	// ���б������������������С��Yϵ����0
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
// ��������ȡб�ʷ���ϵ��
// ���������double& outSlope��
//	double& outConst��
// ����ֵ���Ƿ��ȡ�ɹ�
/************************************************************************/
bool CStraightLine::GetSlopeEquationCoeff(double& outSlope, double& outConst)
{
	outSlope = m_dSlope;
	outConst = m_dConst;
	return true;
}


/************************************************************************/
// GetLineRelation
// ��������ȡ��ֱ�߼��ϵ
// ���������CStraightLine& inLine����һ��ֱ��
// ����ֵ��ֱ�߹�ϵ
/************************************************************************/
eStraightLineRelation CStraightLine::GetLineRelation(CStraightLine& inLine)
{
	if (FloatEqu(m_dSlope, MAX_SLOPE))
	{
		if (FloatEqu(inLine.m_dSlope, MAX_SLOPE))
		{
			if (FloatEqu(m_dConst, inLine.m_dConst))
			{
				return Overlap;	// �غ�
			}
			else
			{
				return Parallel; // ƽ��
			}
		}
		else
		{
			if (FloatEqu(inLine.m_dSlope, 0.0))
			{
				return Vertical;	// ��ֱ
			}
			else
			{
				return Crossed;		// �ཻ
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

// ͨ��xֵ����yֵ
double CStraightLine::GetY(double x)
{
	if (!FloatEqu(fabs(m_dSlope), MAX_SLOPE)) // б�ʲ�����Чֵ
	{
		return (long)(x * m_dSlope + m_dConst);
	}
	else
	{
		return 0;
	}
}

// ͨ��yֵ����xֵ
double CStraightLine::GetX(double y)
{
	if (!FloatEqu(m_dSlope, 0.0)) // б�ʲ�Ϊ0
	{
		return (long)((y - m_dConst) / m_dSlope);
	}
	else
	{
		return 0;
	}
}

// ����ֱ��б�ʾ�̬����
bool CStraightLine::CalSlopeEquationCoeff(const double& x1, const double& y1, const double& x2, const double& y2, double& outSlope, double& outConst)
{
	if (!FloatEqu((x2 - x1), 0.0))
	{
		outSlope = (y2 - y1) / (x2 - x1); // k = (y2-y1)/(x2-x1)
		outConst = y1 - (outSlope * x1); // c = y1 - kx1
	}
	else // ��ֱ��X�ᣬб�������
	{
		outSlope = MAX_SLOPE;
		outConst = -x1;
	}
	return true;
}