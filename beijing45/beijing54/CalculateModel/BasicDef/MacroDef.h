#pragma once

#include "NG_ErrorCode.h"

#define	MAX_SLOPE		6000000.0
// �������Ƚ�ֵ
#define FLOAT_CMPERE	0.000001
// ���������
#define FloatEqu(d1, d2) (fabs(d1 - d2) <=  FLOAT_CMPERE)

//��Чֵ����
#define INVALID_VALUE	-9999

//δ����ֵ����
#define UNCALCULATE		((short)(0x8181))
// add by jie-z@2013.07.14 Char�ͼ�����δ����ֵ
#define UNCALCULATECHAR		((char)(0x81))

//Ĭ�ϷŴ����� ,short��ʾ float,double��ʱ��ʹ��
#define DEFAULTFACTOR 10

#define C_DEGREE2M 111000.0; //ĿǰĬ�ϰ���1�ȶ�Ӧ111km

//���ٵ�ֵ
#define CLIGHT 299792458.000

#ifndef PI
#define PI 3.1415926535897932
#endif

#define HALF_PI  (1.5707963267948965)
#define PI_2 (6.283185307179586)

// ADD BY JIE-Z@2013/06/24
//������������
#define BOLTZMANNCONST 1.38e-23

//ϵͳ�����¶�T0
#define SYSNOISETEMP 290

//��������
#define ERDRADIUS 6370000.0
//�����ƽ��
#define EARTHFLATTENING 1/298.257223563

#define INVALID_MAP_DATA (UNCALCULATE+1)

/* Define NULL pointer value */
#ifndef NULL
#    define NULL    0
#endif

#define DBM_TO_DBUV 113

//����������size
#ifndef PolygonPointsNum
#define PolygonPointsNum  360
#endif


#define MAXCALRADIUSKM   200 //������뾶km



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
	// �ڴ����ʧ���߼�
}*/



//MONITORFORMAT_TO_DBM ��򿪣���ȡɨƵ�ļ�CScanFreqMonitorFile����ȡ���Զ�������ת��dBm
//MONITORFORMAT_TO_DBM��رգ�ԭʼ������ʲô���;���ʲô���ͣ�����ת��
#define MONITORFORMAT_TO_DBM   1


enum ReportType
{
	TXT,
	PDF,
	eSTRUCT
};
void SetReportType(ReportType eReportType);
ReportType GetReportType();

// ���վ�豸�ۺ�״̬
enum EStationStatusTypeCombined
{
	STAT_TYP_COMB_FAULT = -1,	// ����
	STAT_TYP_COMB_READY = 0,	// ����
	STAT_TYP_COMB_PROTECT = 1,	// ����
	STAT_TYP_COMB_SPECTRUM = 2,	// ɨƵ
	STAT_TYP_COMB_IQ = 3,		// IQ����
	STAT_TYP_COMB_SOUND = 4,	// ��Ƶ
	STAT_TYP_COMB_TASK = 5,	    // �������
	STAT_TYP_MONTHLYREPORT_TASK = 6		// �±�����
};

// ���վ�豸����״̬
enum EStationStatusType
{
	STAT_TYP_READY = 0,		// �豸����
	STAT_TYP_WORKING = 1,	// ������
	STAT_TYP_NOT_CONNECTED = 2,	// �豸δ����
	STAT_TYP_FAULT = 3		// �豸����
};

// ���վ�豸��������
enum EStationWorkingType
{
	WORK_TYP_PROTECT = 0,	// ����
	WORK_TYP_STUDY = 1,		// ѵ��
	WORK_TYP_RT_SPECTRUM = 2,		// ʵʱƵ��
	WORK_TYP_SPECTRUM_SITUATION = 3,	// Ƶ��̬��
	WORK_TYP_SPECTRUM_TASK = 4,		// �������
	WORK_TYP_MONTHLYREPORT_TASK = 5		// �±�����
};

// ���վ�豸��������
enum EStationDataType
{
	DATA_TYP_SPECTURM = 0,	// ɨƵ����
	DATA_TYP_IQ = 1,		// IQ����
	DATA_TYP_SOUND = 2		// ��Ƶ����
};

#define   _WINDOWS_VERSION  
#ifdef _WINDOWS_VERSION  //windowsƽ̨
//WINDOWS��򿪣�����windowsϵͳ������EXCEL���ȡ��̨����EXCEL���


#else //linuxƽ̨



#endif 

