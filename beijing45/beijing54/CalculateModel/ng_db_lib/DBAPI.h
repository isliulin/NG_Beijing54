#ifndef _INCLUDE_DBAPI_H
#define _INCLUDE_DBAPI_H 1099
#include "NGDBLib.h"
#include <vector>
#include <fstream>
using namespace std;

/****数据库上下文信息结构(新版本所必须字段)**********************/
typedef struct SDatabaseInfo
{
	char m_init;						/*是否初始化过标志位，Y：已连接初始化  其余为非连接初始化*/
	char m_hasconn;						/*未使用*/
	char m_ctxflag;						/*1-SQLITE,2-ORCAL,3-MYSQL,4-SQLSERVER*/
	char m_sessionid[40];				/*未使用*/
	char m_username[30+1];				/*连接用户名*/
	char m_passwd[30+1];				/*连接用户口令*/
	char error_msg[500];				/*最近一次操作的错误*/
	int m_cxnum;             			/*未使用*/
	int m_cxid[10];          			/*未使用*/
	void * m_ctx;						/*连接句柄上下文在Connect_Database_Zd赋值，通过Disconnect_Database取消*/
}SDatabaseInfo;


/*查询上下文信息*/
typedef struct SQueryDataInfo
{      
	char m_init;   					/*是否初始化过标志位，Y：已查询初始化  其余为非查询初始化*/
	char m_sessionid[40];		/*未使用*/
	int m_rowsCount;			/*按请求的记录数或实际可获取的记录数设置，在Query_Data_Begin中赋值*/
	int m_queryid;
}SQueryDataInfo;

#if 1
/* 文本干扰知识库记录的数据结构 */
typedef struct stTextRecordInfo
{
    string sRecordId;
    
    /* 干扰时间段 */
	unsigned int ulTimeBgn;   //开始时间
	unsigned int ulTimeEnd;   //结束时间
	
    string sInterPlace;   //干扰地点 
    
        /* 干扰频段 */
	double dFreqBgn;  //开始频点
	double dFreqEnd;  //终止频点
	unsigned int ulInterNum;     //干扰次数              
    unsigned int ulInterSrcType; //干扰源类型 
    unsigned int ulInfluCarrier; //干扰影响的载体
    unsigned int ulInterRslt;    //干扰导致的结果

    string sInterTitle;          //干扰案例的标题 
    string sOther;               //其它备注 
    string sSrcFilePath;         //案例源文件路径
}STR_TEXT_RECORD_INFO;

#endif

/* 监测站数据结构 */
typedef struct stMonitorStationInfo
{
	string sGuid;
	string sIP; 

}STR_MONITORSTATION_INFO;


/* 采集任务数据结构 */
typedef struct stMonitorPlanInfo
{
	string				id;
	double				freqstart;
	double				freqend;
	double				freqcenter;
	int 				type;
	string 				stationids;
	int 				status;
	unsigned int 		timestart;
	double 				duration;  
	double				bandwidth;
	int 				recurrencetype;
	string				recurrence;
	unsigned int		startdate;
	unsigned int		enddate;
	string				stat_guid;
	double				abnormal_duration;
	double				abnormal_tolerance;
	
}STR_MONITORPLAN_INFO;

/*月报任务数据结构*/
typedef struct stMonthlyReportInfo
{
	string				taskID;
	string				monthly;
	string				day;
	string				hour;
	int					duration;
	string				reportDate;
	string				reportTemplet;
}STR_MonthlyReport_INFO;

/*定位任务数据结构*/

struct stLocationProject{
	string guid;
	string project_name;
	string project_path;
	double project_start_time;
	double project_stop_time;
	unsigned int project_location_count;
	double project_center_freq;
	double project_band;
	double project_sample_rate;
	int    project_device_type;
	string project_user;
	int project_type;
};


#ifdef __cplusplus
extern "C" {
#endif
NGDBDLL_API int Connect_Database_Zd(const char *szUserName,const char *szPassword,const char *szConn,SDatabaseInfo *stDbInfo);

NGDBDLL_API int Disconnect_Database(SDatabaseInfo *stDbInfo);

NGDBDLL_API int Execute_Sql(SDatabaseInfo *stDbInfo,char * szSqlContent);

NGDBDLL_API int CreateNewGuidByDB(SDatabaseInfo *stDbInfo,char * stGuid);

NGDBDLL_API int QueryDataBySql(SDatabaseInfo *stDbInfo, char* stSql, char* stValue);

NGDBDLL_API int QueryDataBySqlFP(SDatabaseInfo *stDbInfo, char* stSql, char* stValue1, char* stValue2, char* stValue3);

NGDBDLL_API int QueryAllTextBaseDataBySql(SDatabaseInfo *stDbInfo, char* stSql, vector<STR_TEXT_RECORD_INFO> &vTestData);

NGDBDLL_API int Query_Data_File(SDatabaseInfo * stDbInfo,char * szSqlContent,char *szFileName);

/*检测监测站的在线状态*/
NGDBDLL_API int QueryAllMonitorStationDataBySql(SDatabaseInfo *stDbInfo, char* stSql, vector<STR_MONITORSTATION_INFO> &vMoStationData);
NGDBDLL_API int QueryAllMonitorPlanDataBySql(SDatabaseInfo *stDbInfo, char* stSql, vector<stMonitorPlanInfo> &vMoPlanData);

/*获取当前月报任务信息*/
NGDBDLL_API int QueryMonthlyReportPlanBySql(SDatabaseInfo *stDbInfo, char* stSql, vector<stMonthlyReportInfo> &VMoPlanData);

/*设台台站查询*/
NGDBDLL_API int QueryNgStationPositionBySql(SDatabaseInfo *stDbInfo, char* stSql, double& dLon, double& dlat);
NGDBDLL_API int QueryMonitorStationIpBySql(SDatabaseInfo *stDbInfo, char* stSql, string& sGuid, string& sIP);
NGDBDLL_API int QueryMonitorStationStatusBySql(SDatabaseInfo *stDbInfo, char* stSql, int &status, int &workType, int &dataType);

/*定位任务查询*/
NGDBDLL_API int QueryLocationProjectById(SDatabaseInfo *stDbInfo, const char* id, stLocationProject& project);

//查询符合要求的监测站
NGDBDLL_API int GetMonitorIDsByDB(SDatabaseInfo *stDbInfo, char * stSql, std::vector<string> &monitorIDs);

NGDBDLL_API int Query_Data_Begin(SDatabaseInfo * stDbInfo, SQueryDataInfo *stQDInfo ,char * szSqlContent,int iCount);
NGDBDLL_API int Query_Data_Body(SDatabaseInfo * stDbInfo,  SQueryDataInfo *stQDInfo ,char * szRecBuf);
NGDBDLL_API int Query_Data_End(SDatabaseInfo * stDbInfo ,SQueryDataInfo *stQDInfo );


/*取得出错信息函数*/
NGDBDLL_API int Get_ErrorMsg(SDatabaseInfo * stDbInfo,char szErrorMsg[500]);


/*长事务开始函数*/
NGDBDLL_API int Trans_Begin(SDatabaseInfo * stDbInfo);

/*长事务结束函数*/
NGDBDLL_API int Trans_End(SDatabaseInfo * stDbInfo);

/*长事务提交函数*/
NGDBDLL_API int Trans_Commit(SDatabaseInfo * stDbInfo);

/*长事务回滚函数*/
NGDBDLL_API int Trans_Rollback(SDatabaseInfo * stDbInfo);

#ifdef __cplusplus
}
#endif
#endif