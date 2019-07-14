#pragma once

#include "NG_ErrorCode.h"

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

#define C_DEGREE2M 111000.0; //目前默认按照1度对应111km

//光速的值
#define CLIGHT 299792458.000

#ifndef PI
#define PI 3.1415926535897932
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

#define INVALID_MAP_DATA (UNCALCULATE+1)

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



//#define CATCHNEW(X,B) try{X; B=true;}catch(const std::bad_alloc){B=false;}

#define CATCHNEW(X,B) try{X; B=true;}catch(const std::bad_alloc){ B=false;}

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



//MONITORFORMAT_TO_DBM 宏打开，读取扫频文件CScanFreqMonitorFile，读取类自动将数据转成dBm
//MONITORFORMAT_TO_DBM宏关闭，原始数据是什么类型就是什么类型，不做转换
#define MONITORFORMAT_TO_DBM   1


enum ReportType
{
	TXT,
	PDF,
	eSTRUCT
};
void SetReportType(ReportType eReportType);
ReportType GetReportType();

// 监测站设备综合状态
enum EStationStatusTypeCombined
{
	STAT_TYP_COMB_FAULT = -1,	// 故障
	STAT_TYP_COMB_READY = 0,	// 空闲
	STAT_TYP_COMB_PROTECT = 1,	// 保障
	STAT_TYP_COMB_SPECTRUM = 2,	// 扫频
	STAT_TYP_COMB_IQ = 3,		// IQ数据
	STAT_TYP_COMB_SOUND = 4,	// 音频
	STAT_TYP_COMB_TASK = 5,	    // 监测任务
	STAT_TYP_MONTHLYREPORT_TASK = 6		// 月报任务
};

// 监测站设备工作状态
enum EStationStatusType
{
	STAT_TYP_READY = 0,		// 设备空闲
	STAT_TYP_WORKING = 1,	// 工作中
	STAT_TYP_NOT_CONNECTED = 2,	// 设备未连接
	STAT_TYP_FAULT = 3		// 设备故障
};

// 监测站设备工作类型
enum EStationWorkingType
{
	WORK_TYP_PROTECT = 0,	// 保障
	WORK_TYP_STUDY = 1,		// 训练
	WORK_TYP_RT_SPECTRUM = 2,		// 实时频谱
	WORK_TYP_SPECTRUM_SITUATION = 3,	// 频谱态势
	WORK_TYP_SPECTRUM_TASK = 4,		// 监测任务
	WORK_TYP_MONTHLYREPORT_TASK = 5		// 月报任务
};

// 监测站设备数据类型
enum EStationDataType
{
	DATA_TYP_SPECTURM = 0,	// 扫频数据
	DATA_TYP_IQ = 1,		// IQ数据
	DATA_TYP_SOUND = 2		// 音频数据
};

#define   _WINDOWS_VERSION  
#ifdef _WINDOWS_VERSION  //windows平台
//WINDOWS宏打开，可在windows系统上运用EXCEL库读取设台分析EXCEL表格


#else //linux平台



#endif 

