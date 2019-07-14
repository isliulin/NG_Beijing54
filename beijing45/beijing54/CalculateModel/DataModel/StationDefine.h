//̨վ�ṹ�嶨��
#ifndef __STATION__DEFINE__H__
#define __STATION__DEFINE__H__

#include "DataGuidDefine.h"

//̨վ���
enum St_StationClassType
{
	//add more type here
	ST_NORMAL,								//��̨ͨվ
	ST_RADAR,								//�״�վ
	ST_RADAR_ARRAY,							//�״���
	ST_EARTH,								//����վ
	ST_SPACE,								//�ռ�վ
	ST_SITE,
	ST_CELL,
	ST_MONITOR
};

//
enum St_StationType
{
	ST_TRANSMITTER,							//����
	ST_RECEIVE,								//����
	ST_TRANSMITTER_AND_RECEIVE,				//�������
};

//̨վ���
typedef struct tagSt_StationClass
{
	EMC_DATA_GUID	id;						//���id
	char	szCode[4];						//̨վ����ּ�̷���
	char	szName[DATA_NAME_MAX];			//̨վ���˵������
	bool	isMobile;
	double	fee;
	double	fee_Per_Channel;
	double	fee_Per_Mobil;
}St_StationClass;

//̨վ������
typedef struct tagSt_StationClassGroup
{
	EMC_DATA_GUID	id;						//̨վ��id
	char	szName[DATA_NAME_MAX];			//̨վ�����˵������
	int		classCount;						//����̨վ������
	St_StationClass *pClass;				//����̨վ�����Ϣ
}St_StationClassGroup;

//̨վ�ķ����豸
typedef struct tagSt_StationTransDevice
{
	EMC_DATA_GUID	trans_id;				//̨վ�����豸ʹ�õķ����ID
	double	calTransFreq;					//����Ƶ��
	double  calTransBWKhz;                  //�������
	double	calPower;						//����ʹ�õķ��书��,���ɷ������ȡ
	EMC_DATA_GUID	ant_id;					//���������豸id,�������Ի�ȡ�����߸�������
	double	ant_Height;						//���߸߶�(�������ĸ߶�,��λ:m)
	double	ant_Azimuth;					//�������߷�λ��
	double	ant_Tilt;						//�������߻�е�����
	EMC_DATA_GUID	filter_id;				//����ʹ�õ��˲���id
	EMC_DATA_GUID	cable_id;				//����ʹ�õĵ���id
	double	cable_length;					//������³���
}St_StationTransDevice;

//̨վ�Ľ����豸
typedef struct tagSt_StationRecDevice
{
	EMC_DATA_GUID	recieve_id;				//̨վ�����豸ʹ�õĽ��ջ�ID
	double	calRecFreq;						//����Ƶ��
    double  calRecBWKhz;                    //���մ���
	EMC_DATA_GUID	ant_id;					//���������豸id,�������Ի�ȡ�����߸�������
	double	ant_Height;						//���߸߶�(�������ĸ߶�,��λ:m)
	double	ant_Azimuth;					//�������߷�λ��
	double	ant_Tilt;						//�������߻�е�����
	EMC_DATA_GUID	filter_id;				//����ʹ�õ��˲���id
	EMC_DATA_GUID	cable_id;				//����ʹ�õĵ���id
	double	cable_length;					//���յ��³���
	double	rxAddLoss;//���ո������(dB)
}St_StationRecDevice;

//̨վ������Ϣ
typedef struct tagSt_StationBase
{
	EMC_Base	baseInfo;					//������Ϣ
	double	longitude;						//̨վ����
	double	latitude;						//̨վγ��
	double	heightASL;						//̨վ���θ߶�
	St_StationType	stationType;			//̨վ���:���䣬���գ������շ�
	St_StationTransDevice Trans;			//�����豸
	St_StationRecDevice	Recieve;			//�����豸
	double	xOffset;						//��������X����ƫ��ֵ(m)
	double	yOffset;						//��������Y����ƫ��ֵ(m)
	double	zOffset;						//��������Z����ƫ��ֵ(m)
	EMC_DATA_GUID	claaId;					//̨վ���id,�ݴ����id̨վ�в�ͬ������
	EMC_DATA_GUID	stationGroup;			//̨վ���������id
	EMC_DATA_GUID	linkTo;					//����̨վid
	EMC_DATA_GUID	mPStationId;			//���վַid
	EMC_DATA_GUID	radioNetworkId;			//����id
}St_StationBase;

//����̨վ
//Site
typedef struct tagSt_SiteStation
{
	St_StationBase	stationBaseInfo;		//̨վ��������
	//add here
}St_SiteStation;

//����վ
typedef struct tagSt_EarthStation
{
	St_StationBase	stationBaseInfo;		//̨վ��������
	double	minAzimuth;
	double	maxAzimuth;
	double	niseTemp;
	double	minElevation;
}St_EarthStation;

//�ռ�վ
typedef struct tagSt_SpaceStation
{
	St_StationBase	stationBaseInfo;		//̨վ��������
	double	aimPointLong;					//��վ����׼��λ�þ���
	double	aimPointLat;					//��վ����׼��λ��γ��
	double	noiseTemp;						//�����¶�
	double	classIFL;						//��վ�ķ����ʶ
	bool	fqChangingTransponder;			//�Ƿ����Ƶ��ת��
	double	transponderGain;				//�ź�ת������
}St_SpaceStation;

//�״�
//�״������
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
	St_StationBase	stationBaseInfo;		//̨վ��������
	double	probabilityOfFalseAlarm;
	double	rangeResolution;				//����ֱ���
	double	timeBMA;
	double	minimumDistance;
	double	scan_speed;						//ɨ���ٶ�
	EMC_DATA_GUID	typeId;					//�״����id	
	int		searchSectorCount;		
	St_RadarSearchSector *pSearchSector;
}St_RadarStation;

//���վChannel
typedef struct tagSt_MonitorChannel
{
	St_StationRecDevice mon_recDevice;		//�������豸����
	double mon_Freq_Min_MHz;				//���Ƶ������
	double mon_Freq_Max_MHz;				//���Ƶ������
	double mon_sens;						//���������
	double mon_radius;						//���뾶,m
	
	St_StationRecDevice dir_recDevice;		//��������豸����
	double dir_Freq_Min_MHz;				//����Ƶ������
	double dir_Freq_Max_MHz;				//����Ƶ������
	double dir_sense;						//����������
}St_MonitorChannel;

//���վ
typedef struct tagSt_MonitorStation
{
	St_StationBase	stationBaseInfo;		//̨վ��������
	int		ChannelCount;		
	St_MonitorChannel *pChannel;
}St_MonitorStation;

//̨վ
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

//̨վ����
typedef struct tagSt_StationArray
{
	int StationCout;
	St_StationWrapper *pStation;
}St_StationArray;

#endif	/* __STATION__DEFINE__H__ */

