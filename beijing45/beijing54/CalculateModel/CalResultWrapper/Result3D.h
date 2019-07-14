#ifndef __CAL__RESULT__3D__H__
#define __CAL__RESULT__3D__H__

#include "CalResultWrapper.h"
#include "../BasicDef/DataTypes.h"

class RESULT_API Result3D
{
public:
	static Result3D* Create();
	static Result3D* Create(int nHorizonSize, int nVerticalSize);
	static bool	Destroy(Result3D* pDestroy);

public://������������
	Result3D(int nHorizonSize, int nVerticalSize);
	Result3D();
	~Result3D();

public:
	//���������С
	int ReSize(int nHorizonSize, int nVerticalSize);

	//�ռ�����
	void Reset();

	//����ռ�
	void Clear();

	//��ȡ����ĵ��б�
	CDoublePoint** GetPointList(){return m_pp3DPoints;}

	//���ø����������ĵ�
	int SetPoint(int nHorIndex, int nVerIndex, CDoublePoint& point);

    //��ȡ�����������ĵ�
	int GetPoint(int nHorIndex, int nVerIndex, CDoublePoint& point);

	//��ȡ����ϵ
	int GetCoordSys(){ return m_nCoordSys; }

	//��������ϵ
	void SetCoordSys(int inSys) { m_nCoordSys = inSys; }

	//���ýǶ�
	void SetAngle(int nHStartAngle, int nHEndAngle, int nVStartAngle, int nVEndAngle, int nHStep, int nVStep);

	//��ȡ�Ƕ�
	void GetAngle(int& nHStartAngle, int& nHEndAngle, int& nVStartAngle, int& nVEndAngle, int& nHStep, int& nVStep);

	//��ȡ��ά�ռ�Ĵ�С
	void Size(int& nHorizonSize, int& nVerticalSize);

	//��ȡʵ�ʵ�ĸ���
	void GetPointsNum(int& nHorPointsNum, int& nVerPointsNum);	

	int WriteToFile(const char* filename);
	int ReadFromFile(const char * filename);

private:	
	//�����ˮƽ����Ĵ�С
	int m_nHorizonSize;

	//����д�ֱ����Ĵ�С
	int m_nVerticalSize;

	//�����ˮƽ�����ĸ���
	int m_nHorPointsNum;

	//����д�ֱ�����ĸ���
	int m_nVerPointsNum;

	//�Ƕȷ�Χ
	int m_nHStartAngle;  //ˮƽ������ʼ�Ƕ�
	int m_nHEndAngle;    //ˮƽ������ֹ�Ƕ�
	int m_nVStartAngle;  //��ֱ������ʼ�Ƕ�
	int m_nVEndAngle;    //��ֱ������ֹ�Ƕ�

	//�ǶȲ���
	int m_nHStep;        //ˮƽ����ǶȲ���
	int m_nVStep;        //��ֱ����ǶȲ���

	//�㼯
	//��ʹ�õ�����ϵ���
	int m_nCoordSys;  

	//�㼯
	CDoublePoint** m_pp3DPoints;  	
protected:
	void SwapData();
};
#endif