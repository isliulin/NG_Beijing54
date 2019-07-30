#ifndef __POINT__TO__MULTIPOINT__DEFINE__H__
#define __POINT__TO__MULTIPOINT__DEFINE__H__

#include "DataGuidDefine.h"

/*
  ���վַ����һ����վλ��,Ȼ����һ���������(���������ͬ��),Ȼ��ÿһ�������������Ӷ���ͻ�
  ̨վ
*/

typedef struct tagMP_Sector
{
	EMC_DATA_GUID *pSectorStatinId;			//����̨վid
	int		clientStationCount;				//�������ӵĿͻ�̨վ����
	EMC_DATA_GUID *pClientStatinId;			//���ӵĿͻ�̨վid
}MP_Sector;

typedef struct tagMP_Station
{
	EMC_Base	baseInfo;					//������Ϣ
	double	longitude;						//���վַ����
	double	latitude;						//���վַγ��
	bool	isTemplate;						//�Ƿ�ģ����վַ
	int		sectorCount;					//�˶��վַ����������
	MP_Sector *pSector;						//����

}MP_Station;


#endif	/* __POINT__TO__MULTIPOINT__DEFINE__H__ */