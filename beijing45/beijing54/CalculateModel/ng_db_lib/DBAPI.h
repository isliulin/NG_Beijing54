#ifndef _INCLUDE_DBAPI_H
#define _INCLUDE_DBAPI_H 1099
#include "NGDBLib.h"
#include <vector>
#include <fstream>
using namespace std;

/****���ݿ���������Ϣ�ṹ(�°汾�������ֶ�)**********************/
typedef struct SDatabaseInfo
{
	char m_init;						/*�Ƿ��ʼ������־λ��Y�������ӳ�ʼ��  ����Ϊ�����ӳ�ʼ��*/
	char m_hasconn;						/*δʹ��*/
	char m_ctxflag;						/*1-SQLITE,2-ORCAL,3-MYSQL,4-SQLSERVER*/
	char m_sessionid[40];				/*δʹ��*/
	char m_username[30+1];				/*�����û���*/
	char m_passwd[30+1];				/*�����û�����*/
	char error_msg[500];				/*���һ�β����Ĵ���*/
	int m_cxnum;             			/*δʹ��*/
	int m_cxid[10];          			/*δʹ��*/
	void * m_ctx;						/*���Ӿ����������Connect_Database_Zd��ֵ��ͨ��Disconnect_Databaseȡ��*/
}SDatabaseInfo;


/*��ѯ��������Ϣ*/
typedef struct SQueryDataInfo
{      
	char m_init;   					/*�Ƿ��ʼ������־λ��Y���Ѳ�ѯ��ʼ��  ����Ϊ�ǲ�ѯ��ʼ��*/
	char m_sessionid[40];		/*δʹ��*/
	int m_rowsCount;			/*������ļ�¼����ʵ�ʿɻ�ȡ�ļ�¼�����ã���Query_Data_Begin�и�ֵ*/
	int m_queryid;
}SQueryDataInfo;

#if 1
/* �ı�����֪ʶ���¼�����ݽṹ */
typedef struct stTextRecordInfo
{
    string sRecordId;
    
    /* ����ʱ��� */
	unsigned int ulTimeBgn;   //��ʼʱ��
	unsigned int ulTimeEnd;   //����ʱ��
	
    string sInterPlace;   //���ŵص� 
    
        /* ����Ƶ�� */
	double dFreqBgn;  //��ʼƵ��
	double dFreqEnd;  //��ֹƵ��
	unsigned int ulInterNum;     //���Ŵ���              
    unsigned int ulInterSrcType; //����Դ���� 
    unsigned int ulInfluCarrier; //����Ӱ�������
    unsigned int ulInterRslt;    //���ŵ��µĽ��

    string sInterTitle;          //���Ű����ı��� 
    string sOther;               //������ע 
    string sSrcFilePath;         //����Դ�ļ�·��
}STR_TEXT_RECORD_INFO;

#endif

/* ���վ���ݽṹ */
typedef struct stMonitorStationInfo
{
	string sGuid;
	string sIP; 

}STR_MONITORSTATION_INFO;


/* �ɼ��������ݽṹ */
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

/*�±��������ݽṹ*/
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

/*��λ�������ݽṹ*/

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

/*�����վ������״̬*/
NGDBDLL_API int QueryAllMonitorStationDataBySql(SDatabaseInfo *stDbInfo, char* stSql, vector<STR_MONITORSTATION_INFO> &vMoStationData);
NGDBDLL_API int QueryAllMonitorPlanDataBySql(SDatabaseInfo *stDbInfo, char* stSql, vector<stMonitorPlanInfo> &vMoPlanData);

/*��ȡ��ǰ�±�������Ϣ*/
NGDBDLL_API int QueryMonthlyReportPlanBySql(SDatabaseInfo *stDbInfo, char* stSql, vector<stMonthlyReportInfo> &VMoPlanData);

/*��̨̨վ��ѯ*/
NGDBDLL_API int QueryNgStationPositionBySql(SDatabaseInfo *stDbInfo, char* stSql, double& dLon, double& dlat);
NGDBDLL_API int QueryMonitorStationIpBySql(SDatabaseInfo *stDbInfo, char* stSql, string& sGuid, string& sIP);
NGDBDLL_API int QueryMonitorStationStatusBySql(SDatabaseInfo *stDbInfo, char* stSql, int &status, int &workType, int &dataType);

/*��λ�����ѯ*/
NGDBDLL_API int QueryLocationProjectById(SDatabaseInfo *stDbInfo, const char* id, stLocationProject& project);

//��ѯ����Ҫ��ļ��վ
NGDBDLL_API int GetMonitorIDsByDB(SDatabaseInfo *stDbInfo, char * stSql, std::vector<string> &monitorIDs);

NGDBDLL_API int Query_Data_Begin(SDatabaseInfo * stDbInfo, SQueryDataInfo *stQDInfo ,char * szSqlContent,int iCount);
NGDBDLL_API int Query_Data_Body(SDatabaseInfo * stDbInfo,  SQueryDataInfo *stQDInfo ,char * szRecBuf);
NGDBDLL_API int Query_Data_End(SDatabaseInfo * stDbInfo ,SQueryDataInfo *stQDInfo );


/*ȡ�ó�����Ϣ����*/
NGDBDLL_API int Get_ErrorMsg(SDatabaseInfo * stDbInfo,char szErrorMsg[500]);


/*������ʼ����*/
NGDBDLL_API int Trans_Begin(SDatabaseInfo * stDbInfo);

/*�������������*/
NGDBDLL_API int Trans_End(SDatabaseInfo * stDbInfo);

/*�������ύ����*/
NGDBDLL_API int Trans_Commit(SDatabaseInfo * stDbInfo);

/*������ع�����*/
NGDBDLL_API int Trans_Rollback(SDatabaseInfo * stDbInfo);

#ifdef __cplusplus
}
#endif
#endif