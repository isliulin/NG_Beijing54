//��
#ifndef __STATION__GROUP__DEFINE__H__
#define __STATION__GROUP__DEFINE__H__

#include "DataGuidDefine.h"

/*
��
һ�������һ�����̨վ,��Щ̨վ����һ������,�鶨����һ������λ��,���е�̨վλ�þ�
����ڴ�����λ��,�ƶ�һ���������λ�õ�����һ���ط�,�����е�����̨վλ��Ҳ������ͬ
�ĸı�

�����������,��Ϳ��Գ�Ϊһ����
*/
typedef struct tagSG_StationGroup
{
	EMC_Base	baseInfo;					//������Ϣ
	double	longitude;						//�龭��
	double	latitude;						//��γ��
	double	heightASL;						//�麣�θ߶�
	bool	isTemplate;						//�Ƿ�ģ����
	EMC_DATA_GUID parentSiteId;				//����id
	double	xOffsetParentSite;				//������ڸ����X�������(m)
	double	yOffsetParentSite;				//������ڸ����y�������(m)
	double	zOffsetParentSite;				//������ڸ����z�������(m)
	int		stationCount;					//�����ڵ�����̨վ
	EMC_DATA_GUID *pStatinId;				//̨վid

}SG_StationGroup;


#endif	/* __STATION__GROUP__DEFINE__H__ */