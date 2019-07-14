#pragma once
#include "DataTypes.h"

// 天线增益损耗与角度对照项
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

	AngleInDeg	Angle;	// 角度
	LossIndB	Loss;	// 损耗 Radiation at angle (dB above ERPVPK)--dB值
};

class CAntennaAngle
{
public:
	int m_nHorDirRealNum;

	int m_nVerDirRealNum;

	// 水平的方向个数
	int m_nHorDirectionNum;
	// 垂直的方向个数
	int m_nVerDirectionNum;
	// 水平方向损耗列表
	AntennaLossItem* m_pHorizontalList;
	// 垂直方向损耗列表
	AntennaLossItem* m_pVerticalList;
	
public:
	// 构造函数
	CAntennaAngle();
	CAntennaAngle(int nHorDirectionNum, int nVerDirectionNum);
	// 拷贝构造函数
	CAntennaAngle(const CAntennaAngle& SrcAntenna);
	// 析构函数
	~CAntennaAngle();
	//重置
	void Reset();
	// 初始化角度
	void InitAngle(int nHorDirectionNum, int nVerDirectionNum);
	// 获取水平损耗
	double GetHorizontalLoss(double angle) const;
	// 设置水平损耗
	bool SetHorizontalLoss(AngleInDeg inAngle, LossIndB inLoss);
	// 设置水平损耗
	bool SetHorizontalLoss(int Index, AngleInDeg inAngle, LossIndB inLoss);
	// 获取垂直损耗
	double GetVerticalLoss(double angle) const;
	// 设置垂直损耗
	bool SetVerticalLoss(AngleInDeg inAngle, LossIndB inLoss);
	// 设置水平损耗
	bool SetVerticalLoss(int Index, AngleInDeg inAngle, LossIndB inLoss);
	// 获取增益
	LossIndB GetLoss(double h_angle, double v_angle) const;
	// 等号运算符重载
	CAntennaAngle& operator=(const CAntennaAngle& SrcAntennaAngle);
protected:
	// 清空列表
	bool ClearLists();
	// 创建新的空列表
	bool CreateNewLists();
};

