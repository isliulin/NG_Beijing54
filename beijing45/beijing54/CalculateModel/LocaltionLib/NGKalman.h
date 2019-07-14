#ifndef NG_KALMAN_H
#define NG_KALMAN_H

#include "matrix.h"
typedef splab::Matrix<double> NGMatrix;

//卡尔曼滤波器是一个最优化自回归数据处理算法。
//卡尔曼滤波可以根据前一时刻的变量值，方差，以及系统的测量误差和噪声误差，现时刻的测量值，计算出现在时刻的最优化自回归值。
//如果某一个变量不会突变，则可以使用卡尔曼滤波。

/*
  X(K|K-1)=A*X(K-1|K-1)
  P(K|K-1)=A*P(K-1|K-1)A^T+Q
  KA(K)=P(K|K-1)H^T[H*P(K|K-1)H^T+R]^-1
  X(K|K)=X(K-1|K-1)+KA(K)*(S(K)-H*X(K|K-1))
  P(K|K)=[E-KA(K)*H]P(K|K-1)
*/
class NGKalman
{
public:
	NGKalman(){};
	NGKalman(NGMatrix& a,NGMatrix& h,NGMatrix& cov);
	~NGKalman(void);
	NGMatrix filter(const NGMatrix& xPrev,const NGMatrix& SMed,const NGMatrix& QMatrix,const NGMatrix& RMatrix);
	//卡尔曼滤波函数
	//xPrev    前一时刻的状态值
	//SMed     变量该时刻的测量值，测量值个数和状态值个数无需相同
	//QMatrix  系统过程的噪声的方差
	//RMatrix  测量误差的方差
	void updateSysMatrix(NGMatrix& a);
	//更新系统状态矩阵AMatrix,以及A的转置矩阵
public:
	NGMatrix PCOV;//系统状态的方差矩阵，每次卡尔曼滤波后更新 P
private:
	NGMatrix AMatrix;//系统参数矩阵 A
	NGMatrix HMatrix;//测量系统参数 H
	NGMatrix ATran,HTran;//A,H矩阵的转置
	NGMatrix IMatrix;//单位矩阵，阶数和系统状态值个数相同
};

#endif