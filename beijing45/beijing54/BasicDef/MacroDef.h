#pragma once 

#include "NG_ErrorCode.h"
#include <sys/timeb.h>

#define	MAX_SLOPE		6000000.0
// 浮点数比较值
#define FLOAT_CMPERE	0.000001
// 浮点数相等
#define FloatEqu(d1, d2) (fabs(d1 - d2) <=  FLOAT_CMPERE)

//无效值定义
#define INVALID_VALUE	-9999

//未计算值定义
#define UNCALCULATE		((short)(0x8181))	
// add by jie-z@2013.07.14 Char型计算结果未定义值
#define UNCALCULATECHAR		((char)(0x81))

//默认放大因子 ,short表示 float,double的时候使用
#define DEFAULTFACTOR 10

#define C_DEGREE2M (111000.0) //目前默认按照1度对应111km

//光速的值
#define CLIGHT 299792458.000

#ifndef PI
#define PI 3.1415926535897932
#endif

#ifndef F_D2R
#define F_D2R (3.1415926535897932 / 180.00)
#endif

#define HALF_PI  (1.5707963267948965)
#define PI_2 (6.283185307179586)

// ADD BY JIE-Z@2013/06/24
//波尔茨曼常数
#define BOLTZMANNCONST 1.38e-23

//系统噪声温度T0
#define SYSNOISETEMP 290

//地球曲率
#define ERDRADIUS 6370000.0
//地球扁平率
#define EARTHFLATTENING 1/298.257223563

#define INVALID_MAP_DATA -990

/* Define NULL pointer value */
#ifndef NULL
#    define NULL    0
#endif

#define DBM_TO_DBUV 113

//覆盖轮廓线size
#ifndef PolygonPointsNum
#define PolygonPointsNum  360
#endif


#define MAXCALRADIUSKM   200 //最大计算半径km



#define CATCHNEW(X,B) try{X; B=true;}catch(const bad_alloc & e){B=false;}

// 计时操作
#define GET_CLOCK_TICKS(t) {ftime(&t);}
#define GET_DIFFTIME(s,e,buf) { double st = s.time +s.millitm/1000.0; double et = e.time +e.millitm/1000.0;sprintf(buf,"run time %.3fs\n",(et-st));}
#define GET_TIMEINSEC(s,e,timeInSec) { double st = s.time +s.millitm/1000.0; double et = e.time +e.millitm/1000.0; timeInSec = et-st;}

/*example:
int * p = new int[100];

new way:

bool check = true;
int * p=NULL;
CATCHNEW( p = new int[100],check)
if(!check || (p==0))
{
	// 内存分配失败逻辑
}*/


//宏用来区分扫频数据是国家格式还是恩巨格式
//广州、广东不要开宏
//上海频谱地图开宏
//#define STAND_MONITORFORMAT_V1  

enum ReportType
{
	TXT, 
	PDF,
	eSTRUCT
};
void SetReportType(ReportType eReportType);
ReportType GetReportType();

typedef enum {
	NET_TYPE_ALL = -1,
	GSM = 2,
	UMTS = 3,
	LTE = 4,
	STATION_5G=5,	
	WIFI = 10,
	DTV = 15
} E_SITE_TYPE;


enum EManualOrAuto
{
	eManual = 0,
	eAuto   = 1
};

// down-link up-link type
typedef enum eCommLinkType
{
	LinkTypeUl = 0,
	LinkTypeDl = 1
};

typedef enum {
	TRAF_TYPE_FTP = 0
} E_5G_TRAFFIC_TYPE;

#define ENGLISH_VERSION 1
