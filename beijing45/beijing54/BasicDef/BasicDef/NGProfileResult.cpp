#include "NGProfileResult.h"

CNGProfileResult::CNGProfileResult(void)
{
	m_map_coordindex = -1;
	m_MaxBarrierPer_Index = -1;
}

CNGProfileResult::~CNGProfileResult(void)
{
}

void CNGProfileResult::Clear()
{
	m_map_coordindex = -1;
	m_MaxBarrierPer_Index = -1;
	m_field_unit.clear();
	m_longitude_v.clear();//���ȼ�
	m_latitude_v.clear();//γ�ȼ�
	m_distance_v.clear();//���뼯
	m_height_v.clear();//�߶ȼ�
	m_clutter_v.clear();//��ò��
	m_conductivity_v.clear();//�絼�ʼ�
	m_field_v.clear();//��ǿ��
	m_fresnel_up_v.clear();//���������޼�
	m_fresnel_down_v.clear();//���������޼�
	m_BarrierPer_v.clear();
}

bool CNGProfileResult::IsValid() const
{
	int nLongitude = m_longitude_v.size();
	int nLatitude = m_latitude_v.size();
	return ((nLatitude == nLongitude)&&nLongitude>0);
}

unsigned int CNGProfileResult::GetSize() const
{
	return m_latitude_v.size();
}
