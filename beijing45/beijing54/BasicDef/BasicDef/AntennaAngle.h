#pragma once
#include "DataTypes.h"

// �������������Ƕȶ�����
struct AntennaLossItem 
{
	AntennaLossItem():Angle(0.0), Loss(0.0)	
	{

	}

	AntennaLossItem(const AntennaLossItem& SrcItem)
	{
		this->Angle = SrcItem.Angle;
		this->Loss = SrcItem.Loss;
	}

	AngleInDeg	Angle;	// �Ƕ�
	LossIndB	Loss;	// ��� Radiation at angle (dB above ERPVPK)--dBֵ
};

class CAntennaAngle
{
public:
	int m_nHorDirRealNum;

	int m_nVerDirRealNum;

	// ˮƽ�ķ������
	int m_nHorDirectionNum;
	// ��ֱ�ķ������
	int m_nVerDirectionNum;
	// ˮƽ��������б�
	AntennaLossItem* m_pHorizontalList;
	// ��ֱ��������б�
	AntennaLossItem* m_pVerticalList;
	
public:
	// ���캯��
	CAntennaAngle();
	CAntennaAngle(int nHorDirectionNum, int nVerDirectionNum);
	// �������캯��
	CAntennaAngle(const CAntennaAngle& SrcAntenna);
	// ��������
	~CAntennaAngle();
	//����
	void Reset();
	// ��ʼ���Ƕ�
	void InitAngle(int nHorDirectionNum, int nVerDirectionNum);
	// ��ȡˮƽ���
	double GetHorizontalLoss(double angle) const;
	// ����ˮƽ���
	bool SetHorizontalLoss(AngleInDeg inAngle, LossIndB inLoss);
	// ����ˮƽ���
	bool SetHorizontalLoss(int Index, AngleInDeg inAngle, LossIndB inLoss);
	// ��ȡ��ֱ���
	double GetVerticalLoss(double angle) const;
	// ���ô�ֱ���
	bool SetVerticalLoss(AngleInDeg inAngle, LossIndB inLoss);
	// ����ˮƽ���
	bool SetVerticalLoss(int Index, AngleInDeg inAngle, LossIndB inLoss);
	// ��ȡ����
	LossIndB GetLoss(double h_angle, double v_angle) const;
	// �Ⱥ����������
	CAntennaAngle& operator=(const CAntennaAngle& SrcAntennaAngle);
protected:
	// ����б�
	bool ClearLists();
	// �����µĿ��б�
	bool CreateNewLists();
};

