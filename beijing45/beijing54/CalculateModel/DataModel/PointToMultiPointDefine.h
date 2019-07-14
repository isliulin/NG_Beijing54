#ifndef __POINT__TO__MULTIPOINT__DEFINE__H__
#define __POINT__TO__MULTIPOINT__DEFINE__H__

#include "DataGuidDefine.h"

/*
  多点站址定义一个基站位置,然后定义一到多个扇区(这和组是相同的),然后每一个扇区可以链接多个客户
  台站
*/

typedef struct tagMP_Sector
{
	EMC_DATA_GUID *pSectorStatinId;			//扇区台站id
	int		clientStationCount;				//扇区链接的客户台站个数
	EMC_DATA_GUID *pClientStatinId;			//链接的客户台站id
}MP_Sector;

typedef struct tagMP_Station
{
	EMC_Base	baseInfo;					//基本信息
	double	longitude;						//多点站址经度
	double	latitude;						//多点站址纬度
	bool	isTemplate;						//是否模板多点站址
	int		sectorCount;					//此多点站址内扇区个数
	MP_Sector *pSector;						//扇区

}MP_Station;


#endif	/* __POINT__TO__MULTIPOINT__DEFINE__H__ */