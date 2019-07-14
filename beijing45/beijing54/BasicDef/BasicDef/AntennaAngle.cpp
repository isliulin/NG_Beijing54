#include <stdio.h>
#include <string.h>

#include "AntennaAngle.h"


CAntennaAngle::CAntennaAngle(void)
{
	m_nHorDirRealNum = 0;
	m_nVerDirRealNum = 0;
	m_nHorDirectionNum	= 0;
	m_nVerDirectionNum	= 0;
	m_pHorizontalList	= NULL;
	m_pVerticalList		= NULL;
}

CAntennaAngle::CAntennaAngle(int nHorDirectionNum, int nVerDirectionNum)
{
	m_nHorDirRealNum = 0;
	m_nVerDirRealNum = 0;

	m_nHorDirectionNum = nHorDirectionNum;
	m_nVerDirectionNum = nVerDirectionNum;

	m_pHorizontalList = NULL;
	m_pVerticalList = NULL;
	// 创建新的空列表
	CreateNewLists();
}

// 拷贝构造函数
CAntennaAngle::CAntennaAngle(const CAntennaAngle& SrcAntenna)
{
	m_nHorDirRealNum = SrcAntenna.m_nHorDirRealNum;
	m_nVerDirRealNum = SrcAntenna.m_nVerDirRealNum;

	m_nHorDirectionNum = SrcAntenna.m_nHorDirectionNum;
	m_nVerDirectionNum = SrcAntenna.m_nVerDirectionNum;
	m_pHorizontalList = NULL;
	m_pVerticalList = NULL;

	// 建空表
	CreateNewLists();
	memcpy(this->m_pHorizontalList, SrcAntenna.m_pHorizontalList, sizeof(AntennaLossItem) * m_nHorDirectionNum);
	memcpy(this->m_pVerticalList, SrcAntenna.m_pVerticalList, sizeof(AntennaLossItem) * m_nVerDirectionNum);
}

// 析构
CAntennaAngle::~CAntennaAngle(void)
{
	// 清除列表
	ClearLists();
}

// 创建新的空列表
bool CAntennaAngle::CreateNewLists()
{
	if((0 != m_nHorDirectionNum) && (NULL == m_pHorizontalList))
	{
		m_pHorizontalList = new AntennaLossItem[m_nHorDirectionNum];
		memset(m_pHorizontalList, 0x00, sizeof(AntennaLossItem) * m_nHorDirectionNum);
	}

	if((0 != m_nVerDirectionNum) && (NULL == m_pVerticalList))
	{
		m_pVerticalList		= new AntennaLossItem[m_nVerDirectionNum];
		memset(m_pVerticalList, 0x00, sizeof(AntennaLossItem) * m_nVerDirectionNum);
	}
	
	return true;
}

// 清空列表
bool CAntennaAngle::ClearLists()
{
	if(0 != m_nHorDirectionNum || 0 != m_nVerDirectionNum)
	{
		if (NULL != m_pHorizontalList)
		{
			delete [] m_pHorizontalList;
			//::GlobalFree((HGLOBAL)m_pHorizontalList);
			m_pHorizontalList = NULL;
		}
		if (NULL != m_pVerticalList)
		{
			delete [] m_pVerticalList;
			//::GlobalFree((HGLOBAL)m_pVerticalList);
			m_pVerticalList = NULL;
		}
		m_nHorDirectionNum = 0;
		m_nVerDirectionNum = 0;
	}
	return true;
}

//重置
void CAntennaAngle::Reset()
{
	if(m_pHorizontalList != NULL)
	{
		memset(m_pHorizontalList, 0, sizeof(AntennaLossItem) * m_nHorDirectionNum);
		m_nHorDirRealNum = 0;
	}

	if(m_pVerticalList != NULL)
	{
		memset(m_pVerticalList, 0, sizeof(AntennaLossItem) * m_nVerDirectionNum);
		m_nVerDirRealNum = 0;
	}
}

// 初始化天线角度
void CAntennaAngle::InitAngle(int nHorDirectionNum, int nVerDirectionNum)
{
	// 先把列表清空
	ClearLists();

	// 重新初始化列表
	m_nHorDirectionNum = nHorDirectionNum;
	m_nVerDirectionNum = nVerDirectionNum;
	
	CreateNewLists();
}

//获取天线给定角度的损耗值---此处需要换一种方法，因为角度已经不连续
double CAntennaAngle::GetHorizontalLoss(double angle) const
{
	if(m_nHorDirRealNum == 0)
	{
		return 0;
	}
	// 将角度限定在0~360之间
	while (angle < 0)
	{
		angle += 360;
	}
	while (angle >= 360)
	{
		angle -= 360;
	}

	double loss = 0.0;

	double loss_1 = 0.0;
	double loss_2 = 0.0;

	double angle_1 = 0.0;
	double angle_2 = 0.0;

	AngleInDeg deg360(360);

	if(angle<m_pHorizontalList[0].Angle)//如果给定的角度<角度0
	{
		angle_1 = m_pHorizontalList[m_nHorDirRealNum-1].Angle - deg360;
		angle_2 = m_pHorizontalList[0].Angle;

		loss_1 = m_pHorizontalList[m_nHorDirRealNum-1].Loss;
		loss_2 = m_pHorizontalList[0].Loss;
	}
	else if(angle>=m_pHorizontalList[m_nHorDirRealNum-1].Angle) //如果给定的角度〉最后一个角度
	{
		angle_1 = m_pHorizontalList[m_nHorDirRealNum-1].Angle;
		angle_2 = m_pHorizontalList[0].Angle + deg360;

		loss_1 = m_pHorizontalList[m_nHorDirRealNum-1].Loss;
		loss_2 = m_pHorizontalList[0].Loss;
	}
	else
	{
		for(int i=1; i<m_nHorDirRealNum; i++)
		{
			if(angle<m_pHorizontalList[i].Angle) //如果给定的角度<i对应的角度
			{
				loss_1 = m_pHorizontalList[i-1].Loss;
				loss_2 = m_pHorizontalList[i].Loss;

				angle_1 = m_pHorizontalList[i-1].Angle;
				angle_2 = m_pHorizontalList[i].Angle;

				break;
			}
		}
	}

	loss = loss_1;

	// interpolate:
	loss += (loss_2 - loss_1)/(angle_2 - angle_1) * (angle - angle_1);

	return loss;
}

// 获取垂直方向损耗
double CAntennaAngle::GetVerticalLoss(double angle) const
{
	if(m_nVerDirRealNum == 0)
	{
		return 0;
	}

	while (angle<0)
	{
		angle+=360;
	}
	while (angle>360)
	{
		angle-=360;
	}

	double loss = 0.0;

	double loss_1 = 0.0;
	double loss_2 = 0.0;

	double angle_1 = 0.0;
	double angle_2 = 0.0;

	AngleInDeg deg360(360);

	if(angle<m_pVerticalList[0].Angle)//如果给定的角度<角度0
	{
		angle_1 = m_pVerticalList[m_nVerDirRealNum-1].Angle - deg360;
		angle_2 = m_pVerticalList[0].Angle;

		loss_1 = m_pVerticalList[m_nVerDirRealNum-1].Loss;
		loss_2 = m_pVerticalList[0].Loss;
	}
	else if(angle>=m_pVerticalList[m_nVerDirRealNum-1].Angle) //如果给定的角度〉最后一个角度
	{
		angle_1 = m_pVerticalList[m_nVerDirRealNum-1].Angle;
		angle_2 = m_pVerticalList[0].Angle + deg360;

		loss_1 = m_pVerticalList[m_nVerDirRealNum-1].Loss;
		loss_2 = m_pVerticalList[0].Loss;
	}
	else
	{
		for(int i=1; i<m_nVerDirRealNum; i++)
		{
			if(angle<m_pVerticalList[i].Angle) //如果给定的角度<i对应的角度
			{
				loss_1 = m_pVerticalList[i-1].Loss;
				loss_2 = m_pVerticalList[i].Loss;

				angle_1 = m_pVerticalList[i-1].Angle;
				angle_2 = m_pVerticalList[i].Angle;	

				break;
			}
		}
	}

	loss = loss_1;

	// interpolate:
	loss += (loss_2 - loss_1)/(angle_2 - angle_1) * (angle - angle_1);

	return loss;
}

// 获取增益值
LossIndB CAntennaAngle::GetLoss(double h_angle, double v_angle) const
{
	while (h_angle < 0)
		h_angle += 360;
	while (h_angle >= 360)
		h_angle -= 360;

	double horizontal_gain = GetHorizontalLoss(h_angle);
	double vertical_gain = GetVerticalLoss(v_angle);

	float Loss = (float)(horizontal_gain + vertical_gain);			

	if ( Loss > 100) 
	{
		Loss = 100;
	}
	return (LossIndB)Loss;
}

	// 等号运算符重载
CAntennaAngle& CAntennaAngle::operator=(const CAntennaAngle& SrcAntennaAngle)
{
	ClearLists();
	m_nHorDirectionNum = SrcAntennaAngle.m_nHorDirectionNum;
	m_nVerDirectionNum = SrcAntennaAngle.m_nVerDirectionNum;
	// 建空表
	CreateNewLists();
	
	memcpy(this->m_pHorizontalList, SrcAntennaAngle.m_pHorizontalList, sizeof(AntennaLossItem) * m_nHorDirectionNum);
	memcpy(this->m_pVerticalList, SrcAntennaAngle.m_pVerticalList, sizeof(AntennaLossItem) * m_nVerDirectionNum);

	return *this;
}

// 设置水平损耗
bool CAntennaAngle::SetHorizontalLoss(int Index, AngleInDeg inAngle, LossIndB inLoss)
{
	m_pHorizontalList[Index].Loss  = inLoss;
	m_pHorizontalList[Index].Angle = inAngle;
	return true;
}

// 设置水平损耗
bool CAntennaAngle::SetHorizontalLoss(AngleInDeg inAngle, LossIndB inLoss)
{
	int nIndex = (int)inAngle;
	return SetHorizontalLoss(nIndex, inAngle, inLoss);
}

// 设置垂直损耗
bool CAntennaAngle::SetVerticalLoss(AngleInDeg inAngle, LossIndB inLoss)
{
	int nIndex = (int)inAngle;
	return SetVerticalLoss(nIndex, inAngle, inLoss);
}
// 设置水平损耗
bool CAntennaAngle::SetVerticalLoss(int Index, AngleInDeg inAngle, LossIndB inLoss)
{
	m_pVerticalList[Index].Loss  = inLoss;
	m_pVerticalList[Index].Angle = inAngle;
	return true;
}