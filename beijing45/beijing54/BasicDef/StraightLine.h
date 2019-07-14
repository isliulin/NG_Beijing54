#pragma once
#include "DataTypes.h"

// 直线位置关系枚举
enum eStraightLineRelation
{
	Parallel = 0x00,	// 平行
	Overlap	 = 0x02,	// 重合
	Crossed	 = 0x03,	// 相交
	Vertical = 0x07		// 垂直
};

/************************************************************************/
// CStraightLine
// 运算直线类(直线方程)
/************************************************************************/
class CStraightLine
{
public:
	// 计算直线斜率静态函数
	static bool CalSlopeEquationCoeff(const double& x1, const double& y1, const double& x2, const double& y2, double& outSlope, double& outConst);
public:
	// 构造
	CStraightLine(void);
	/************************************************************************/
	// CStraightLine
	// 描述：直线类构造函数
	// 参数：double inSlope：斜率
	// double inConst：常数项
	/************************************************************************/
	CStraightLine(double inSlope, double inConst);

	// 析构
	virtual ~CStraightLine(void);

	/************************************************************************/
	// GetStdEquationCoeff
	// 获得标准方程参数
	// 输出参数：double& outXCoeff：X项系数
	//	double& outYCoeff：Y项系数
	//	double& outConst：常数项
	//	返回值：是否获取成功
	/************************************************************************/
	bool GetStdEquationCoeff(double& outXCoeff, double& outYCoeff, double& outConst);
	
	/************************************************************************/
	// GetSlopeEquationPara
	// 描述：获取斜率方程系数
	// 输出参数：double& outSlope：
	//	double& outConst：
	// 返回值：是否获取成功
	/************************************************************************/
	bool GetSlopeEquationCoeff(double& outSlope, double& outConst);
	
	/************************************************************************/
	// GetLineRelation
	// 描述：获取两直线间关系
	// 参数：CStraightLine& inLine：另一条直线
	// 返回值：直线关系
	/************************************************************************/
	eStraightLineRelation GetLineRelation(CStraightLine& inLine);

	// 获取直线斜率
	double GetSlope() { return m_dSlope; }
	// 通过x值计算y值
	double GetY(double x);
	// 通过y值计算x值
	double GetX(double y);

private:
	// 直线斜率
	double m_dSlope;
	// 常数项
	double m_dConst;
};
