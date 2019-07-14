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
	m_longitude_v.clear();//经度集
	m_latitude_v.clear();//纬度集
	m_distance_v.clear();//距离集
	m_height_v.clear();//高度集
	m_clutter_v.clear();//地貌集
	m_conductivity_v.clear();//电导率集
	m_field_v.clear();//场强集
	m_fresnel_up_v.clear();//费涅尔上限集
	m_fresnel_down_v.clear();//费涅尔下限集
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
