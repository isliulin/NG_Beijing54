#ifndef NG_KALMAN_H
#define NG_KALMAN_H

#include "matrix.h"
typedef splab::Matrix<double> NGMatrix;

//�������˲�����һ�����Ż��Իع����ݴ����㷨��
//�������˲����Ը���ǰһʱ�̵ı���ֵ������Լ�ϵͳ�Ĳ���������������ʱ�̵Ĳ���ֵ�����������ʱ�̵����Ż��Իع�ֵ��
//���ĳһ����������ͻ�䣬�����ʹ�ÿ������˲���

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
	//�������˲�����
	//xPrev    ǰһʱ�̵�״ֵ̬
	//SMed     ������ʱ�̵Ĳ���ֵ������ֵ������״ֵ̬����������ͬ
	//QMatrix  ϵͳ���̵������ķ���
	//RMatrix  �������ķ���
	void updateSysMatrix(NGMatrix& a);
	//����ϵͳ״̬����AMatrix,�Լ�A��ת�þ���
public:
	NGMatrix PCOV;//ϵͳ״̬�ķ������ÿ�ο������˲������ P
private:
	NGMatrix AMatrix;//ϵͳ�������� A
	NGMatrix HMatrix;//����ϵͳ���� H
	NGMatrix ATran,HTran;//A,H�����ת��
	NGMatrix IMatrix;//��λ���󣬽�����ϵͳ״ֵ̬������ͬ
};

#endif