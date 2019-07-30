//组
#ifndef __STATION__GROUP__DEFINE__H__
#define __STATION__GROUP__DEFINE__H__

#include "DataGuidDefine.h"

/*
组
一个组包含一到多个台站,这些台站构成一个整体,组定义了一个中心位置,组中的台站位置均
相对于此中心位置,移动一个组的中心位置到另外一个地方,则组中的所有台站位置也发生相同
的改变

组可以有子组,组就可以成为一颗树
*/
typedef struct tagSG_StationGroup
{
	EMC_Base	baseInfo;					//基本信息
	double	longitude;						//组经度
	double	latitude;						//组纬度
	double	heightASL;						//组海拔高度
	bool	isTemplate;						//是否模板组
	EMC_DATA_GUID parentSiteId;				//父组id
	double	xOffsetParentSite;				//组相对于父组的X方向距离(m)
	double	yOffsetParentSite;				//组相对于父组的y方向距离(m)
	double	zOffsetParentSite;				//组相对于父组的z方向距离(m)
	int		stationCount;					//此组内的所有台站
	EMC_DATA_GUID *pStatinId;				//台站id

}SG_StationGroup;


#endif	/* __STATION__GROUP__DEFINE__H__ */