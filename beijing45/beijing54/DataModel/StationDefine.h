//台站结构体定义
#ifndef __STATION__DEFINE__H__
#define __STATION__DEFINE__H__

#include "DataGuidDefine.h"

//台站类别
enum St_StationClassType
{
	//add more type here
	ST_NORMAL,								//普通台站
	ST_RADAR,								//雷达站
	ST_RADAR_ARRAY,							//雷达组
	ST_EARTH,								//地球站
	ST_SPACE,								//空间站
	ST_SITE,
	ST_CELL,
	ST_MONITOR
};

//
enum St_StationType
{
	ST_TRANSMITTER,							//发射
	ST_RECEIVE,								//接收
	ST_TRANSMITTER_AND_RECEIVE,				//发射接收
};

//台站类别
typedef struct tagSt_StationClass
{
	EMC_DATA_GUID	id;						//类别id
	char	szCode[4];						//台站类别字简短符串
	char	szName[DATA_NAME_MAX];			//台站类别说明名称
	bool	isMobile;
	double	fee;
	double	fee_Per_Channel;
	double	fee_Per_Mobil;
}St_StationClass;

//台站类别分组
typedef struct tagSt_StationClassGroup
{
	EMC_DATA_GUID	id;						//台站组id
	char	szName[DATA_NAME_MAX];			//台站类别组说明名称
	int		classCount;						//组中台站类别个数
	St_StationClass *pClass;				//组中台站类别信息
}St_StationClassGroup;

//台站的发射设备
typedef struct tagSt_StationTransDevice
{
	EMC_DATA_GUID	trans_id;				//台站发射设备使用的发射机ID
	double	calTransFreq;					//发射频率
	double  calTransBWKhz;                  //发射带宽
	double	calPower;						//计算使用的发射功率,可由发射机获取
	EMC_DATA_GUID	ant_id;					//发射天线设备id,由它可以获取到天线覆型数据
	double	ant_Height;						//天线高度(距离地面的高度,单位:m)
	double	ant_Azimuth;					//发射天线方位角
	double	ant_Tilt;						//发射天线机械下倾角
	EMC_DATA_GUID	filter_id;				//发射使用的滤波器id
	EMC_DATA_GUID	cable_id;				//发射使用的电缆id
	double	cable_length;					//发射电缆长度
}St_StationTransDevice;

//台站的接收设备
typedef struct tagSt_StationRecDevice
{
	EMC_DATA_GUID	recieve_id;				//台站接收设备使用的接收机ID
	double	calRecFreq;						//接收频率
    double  calRecBWKhz;                    //接收带宽
	EMC_DATA_GUID	ant_id;					//接收天线设备id,由它可以获取到天线覆型数据
	double	ant_Height;						//天线高度(距离地面的高度,单位:m)
	double	ant_Azimuth;					//接收天线方位角
	double	ant_Tilt;						//接收天线机械下倾角
	EMC_DATA_GUID	filter_id;				//接收使用的滤波器id
	EMC_DATA_GUID	cable_id;				//接收使用的电缆id
	double	cable_length;					//接收电缆长度
	double	rxAddLoss;//接收附加损耗(dB)
}St_StationRecDevice;

//台站基本信息
typedef struct tagSt_StationBase
{
	EMC_Base	baseInfo;					//基本信息
	double	longitude;						//台站经度
	double	latitude;						//台站纬度
	double	heightASL;						//台站海拔高度
	St_StationType	stationType;			//台站类别:发射，接收，还是收发
	St_StationTransDevice Trans;			//发射设备
	St_StationRecDevice	Recieve;			//接收设备
	double	xOffset;						//相对于组的X方向偏移值(m)
	double	yOffset;						//相对于组的Y方向偏移值(m)
	double	zOffset;						//相对于组的Z方向偏移值(m)
	EMC_DATA_GUID	claaId;					//台站类别id,据此类别id台站有不同的数据
	EMC_DATA_GUID	stationGroup;			//台站所属的组的id
	EMC_DATA_GUID	linkTo;					//链接台站id
	EMC_DATA_GUID	mPStationId;			//多点站址id
	EMC_DATA_GUID	radioNetworkId;			//网络id
}St_StationBase;

//具体台站
//Site
typedef struct tagSt_SiteStation
{
	St_StationBase	stationBaseInfo;		//台站基本数据
	//add here
}St_SiteStation;

//地球站
typedef struct tagSt_EarthStation
{
	St_StationBase	stationBaseInfo;		//台站基本数据
	double	minAzimuth;
	double	maxAzimuth;
	double	niseTemp;
	double	minElevation;
}St_EarthStation;

//空间站
typedef struct tagSt_SpaceStation
{
	St_StationBase	stationBaseInfo;		//台站基本数据
	double	aimPointLong;					//基站的瞄准点位置经度
	double	aimPointLat;					//基站的瞄准点位置纬度
	double	noiseTemp;						//噪声温度
	double	classIFL;						//基站的服务标识
	bool	fqChangingTransponder;			//是否进行频率转换
	double	transponderGain;				//信号转发增益
}St_SpaceStation;

//雷达
//雷达类别定义
typedef struct tagSt_RadarType
{
	EMC_DATA_GUID	id;		
	char	szName[DATA_NAME_MAX];			
	double	Range1WP;
	double	Range2WP;
	double	Range1Mast;
	double	Range2Mast;
	int		CalcMethod1;
	int		CalcMethod2;
}St_RadarType;

typedef struct tagSt_RadarSearchSector
{
	double	startAngle;
	double	stopAngle;
	double	range;							//m
}St_RadarSearchSector;

typedef struct tagSt_RadarStation
{
	St_StationBase	stationBaseInfo;		//台站基本数据
	double	probabilityOfFalseAlarm;
	double	rangeResolution;				//距离分辨率
	double	timeBMA;
	double	minimumDistance;
	double	scan_speed;						//扫描速度
	EMC_DATA_GUID	typeId;					//雷达类别id	
	int		searchSectorCount;		
	St_RadarSearchSector *pSearchSector;
}St_RadarStation;

//监测站Channel
typedef struct tagSt_MonitorChannel
{
	St_StationRecDevice mon_recDevice;		//监测接收设备数据
	double mon_Freq_Min_MHz;				//监测频率下限
	double mon_Freq_Max_MHz;				//监测频率上限
	double mon_sens;						//监测灵敏度
	double mon_radius;						//监测半径,m
	
	St_StationRecDevice dir_recDevice;		//测向接收设备数据
	double dir_Freq_Min_MHz;				//测向频率下限
	double dir_Freq_Max_MHz;				//测向频率上限
	double dir_sense;						//测向灵敏度
}St_MonitorChannel;

//监测站
typedef struct tagSt_MonitorStation
{
	St_StationBase	stationBaseInfo;		//台站基本数据
	int		ChannelCount;		
	St_MonitorChannel *pChannel;
}St_MonitorStation;

//台站
typedef struct tagSt_StationWrapper
{
	St_StationClassType type;
	union 
	{
		//add more pointer here
		St_StationBase		*pNormalSite;
		St_RadarStation		*pRadar;
		St_EarthStation		*pEarth;
		St_SpaceStation		*pSpace;
		St_MonitorStation	*pMonitor;
		St_SiteStation		*pSite;
	};
}St_StationWrapper;

//台站数组
typedef struct tagSt_StationArray
{
	int StationCout;
	St_StationWrapper *pStation;
}St_StationArray;

#endif	/* __STATION__DEFINE__H__ */

