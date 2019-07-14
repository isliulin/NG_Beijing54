#pragma once
#include "DataTypes.h"

// ֱ��λ�ù�ϵö��
enum eStraightLineRelation
{
	Parallel = 0x00,	// ƽ��
	Overlap	 = 0x02,	// �غ�
	Crossed	 = 0x03,	// �ཻ
	Vertical = 0x07		// ��ֱ
};

/************************************************************************/
// CStraightLine
// ����ֱ����(ֱ�߷���)
/************************************************************************/
class CStraightLine
{
public:
	// ����ֱ��б�ʾ�̬����
	static bool CalSlopeEquationCoeff(const double& x1, const double& y1, const double& x2, const double& y2, double& outSlope, double& outConst);
public:
	// ����
	CStraightLine(void);
	/************************************************************************/
	// CStraightLine
	// ������ֱ���๹�캯��
	// ������double inSlope��б��
	// double inConst��������
	/************************************************************************/
	CStraightLine(double inSlope, double inConst);

	// ����
	virtual ~CStraightLine(void);

	/************************************************************************/
	// GetStdEquationCoeff
	// ��ñ�׼���̲���
	// ���������double& outXCoeff��X��ϵ��
	//	double& outYCoeff��Y��ϵ��
	//	double& outConst��������
	//	����ֵ���Ƿ��ȡ�ɹ�
	/************************************************************************/
	bool GetStdEquationCoeff(double& outXCoeff, double& outYCoeff, double& outConst);
	
	/************************************************************************/
	// GetSlopeEquationPara
	// ��������ȡб�ʷ���ϵ��
	// ���������double& outSlope��
	//	double& outConst��
	// ����ֵ���Ƿ��ȡ�ɹ�
	/************************************************************************/
	bool GetSlopeEquationCoeff(double& outSlope, double& outConst);
	
	/************************************************************************/
	// GetLineRelation
	// ��������ȡ��ֱ�߼��ϵ
	// ������CStraightLine& inLine����һ��ֱ��
	// ����ֵ��ֱ�߹�ϵ
	/************************************************************************/
	eStraightLineRelation GetLineRelation(CStraightLine& inLine);

	// ��ȡֱ��б��
	double GetSlope() { return m_dSlope; }
	// ͨ��xֵ����yֵ
	double GetY(double x);
	// ͨ��yֵ����xֵ
	double GetX(double y);

private:
	// ֱ��б��
	double m_dSlope;
	// ������
	double m_dConst;
};
