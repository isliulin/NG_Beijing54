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
	// �����µĿ��б�
	CreateNewLists();
}

// �������캯��
CAntennaAngle::CAntennaAngle(const CAntennaAngle& SrcAntenna)
{
	m_nHorDirRealNum = SrcAntenna.m_nHorDirRealNum;
	m_nVerDirRealNum = SrcAntenna.m_nVerDirRealNum;

	m_nHorDirectionNum = SrcAntenna.m_nHorDirectionNum;
	m_nVerDirectionNum = SrcAntenna.m_nVerDirectionNum;
	m_pHorizontalList = NULL;
	m_pVerticalList = NULL;

	// ���ձ�
	CreateNewLists();
	memcpy(this->m_pHorizontalList, SrcAntenna.m_pHorizontalList, sizeof(AntennaLossItem) * m_nHorDirectionNum);
	memcpy(this->m_pVerticalList, SrcAntenna.m_pVerticalList, sizeof(AntennaLossItem) * m_nVerDirectionNum);
}

// ����
CAntennaAngle::~CAntennaAngle(void)
{
	// ����б�
	ClearLists();
}

// �����µĿ��б�
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

// ����б�
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

//����
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

// ��ʼ�����߽Ƕ�
void CAntennaAngle::InitAngle(int nHorDirectionNum, int nVerDirectionNum)
{
	// �Ȱ��б����
	ClearLists();

	// ���³�ʼ���б�
	m_nHorDirectionNum = nHorDirectionNum;
	m_nVerDirectionNum = nVerDirectionNum;
	
	CreateNewLists();
}

//��ȡ���߸����Ƕȵ����ֵ---�˴���Ҫ��һ�ַ�������Ϊ�Ƕ��Ѿ�������
double CAntennaAngle::GetHorizontalLoss(double angle) const
{
	if(m_nHorDirRealNum == 0)
	{
		return 0;
	}
	// ���Ƕ��޶���0~360֮��
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

	if(angle<m_pHorizontalList[0].Angle)//��������ĽǶ�<�Ƕ�0
	{
		angle_1 = m_pHorizontalList[m_nHorDirRealNum-1].Angle - deg360;
		angle_2 = m_pHorizontalList[0].Angle;

		loss_1 = m_pHorizontalList[m_nHorDirRealNum-1].Loss;
		loss_2 = m_pHorizontalList[0].Loss;
	}
	else if(angle>=m_pHorizontalList[m_nHorDirRealNum-1].Angle) //��������ĽǶȡ����һ���Ƕ�
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
			if(angle<m_pHorizontalList[i].Angle) //��������ĽǶ�<i��Ӧ�ĽǶ�
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

// ��ȡ��ֱ�������
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

	if(angle<m_pVerticalList[0].Angle)//��������ĽǶ�<�Ƕ�0
	{
		angle_1 = m_pVerticalList[m_nVerDirRealNum-1].Angle - deg360;
		angle_2 = m_pVerticalList[0].Angle;

		loss_1 = m_pVerticalList[m_nVerDirRealNum-1].Loss;
		loss_2 = m_pVerticalList[0].Loss;
	}
	else if(angle>=m_pVerticalList[m_nVerDirRealNum-1].Angle) //��������ĽǶȡ����һ���Ƕ�
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
			if(angle<m_pVerticalList[i].Angle) //��������ĽǶ�<i��Ӧ�ĽǶ�
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

// ��ȡ����ֵ
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

	// �Ⱥ����������
CAntennaAngle& CAntennaAngle::operator=(const CAntennaAngle& SrcAntennaAngle)
{
	ClearLists();
	m_nHorDirectionNum = SrcAntennaAngle.m_nHorDirectionNum;
	m_nVerDirectionNum = SrcAntennaAngle.m_nVerDirectionNum;
	// ���ձ�
	CreateNewLists();
	
	memcpy(this->m_pHorizontalList, SrcAntennaAngle.m_pHorizontalList, sizeof(AntennaLossItem) * m_nHorDirectionNum);
	memcpy(this->m_pVerticalList, SrcAntennaAngle.m_pVerticalList, sizeof(AntennaLossItem) * m_nVerDirectionNum);

	return *this;
}

// ����ˮƽ���
bool CAntennaAngle::SetHorizontalLoss(int Index, AngleInDeg inAngle, LossIndB inLoss)
{
	m_pHorizontalList[Index].Loss  = inLoss;
	m_pHorizontalList[Index].Angle = inAngle;
	return true;
}

// ����ˮƽ���
bool CAntennaAngle::SetHorizontalLoss(AngleInDeg inAngle, LossIndB inLoss)
{
	int nIndex = (int)inAngle;
	return SetHorizontalLoss(nIndex, inAngle, inLoss);
}

// ���ô�ֱ���
bool CAntennaAngle::SetVerticalLoss(AngleInDeg inAngle, LossIndB inLoss)
{
	int nIndex = (int)inAngle;
	return SetVerticalLoss(nIndex, inAngle, inLoss);
}
// ����ˮƽ���
bool CAntennaAngle::SetVerticalLoss(int Index, AngleInDeg inAngle, LossIndB inLoss)
{
	m_pVerticalList[Index].Loss  = inLoss;
	m_pVerticalList[Index].Angle = inAngle;
	return true;
}