#define  _CRT_SECURE_NO_DEPRECATE
#include "DBAPI.h"
#include <fstream>

#ifdef USE_OCCI
#include "DBOraConnection.h"
#endif

#ifdef USE_SQLITE
#include "DBSqliteConnection.h"
#endif

#ifdef USE_MYSQL
#include "DBMySqlConnection.h"
#endif

#ifdef USE_SQLSERVER
#include "DBSQLConnection.h"
#endif

int Connect_Database_Zd(const char *szUserName, const char *szPassword,const char *szConn,SDatabaseInfo *stDbInfo )
{
	int res = -1;
	IDBConnection* pCon = NULL;
	
	try
	{
		pCon = CreateDBConnection(stDbInfo->m_ctxflag,szUserName,szPassword,szConn);
		if(pCon)
		{
			stDbInfo->m_ctx = pCon;
			stDbInfo->m_init = 'Y';
			stDbInfo->m_cxnum = 1;
			strncpy(stDbInfo->m_username,szUserName,30);
			strncpy(stDbInfo->m_passwd,szPassword,30);
			stDbInfo->m_ctx = pCon;
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		std::string err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"数据库打开失败！");
	}
	if(res == -1)
	{
		if(pCon!=NULL)
			CloseDBConnection(pCon);
		stDbInfo->m_ctx = NULL;
	}
	return res;
}

int Disconnect_Database( SDatabaseInfo *stDbInfo )
{
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;
	if(pCon!=NULL)
		CloseDBConnection(pCon);
	stDbInfo->m_ctx = NULL;
	stDbInfo->m_init = 'N';
	stDbInfo->m_cxnum = 0;
	return 0;
}

int Execute_Sql( SDatabaseInfo *stDbInfo,char * szSqlContent )
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;
	
	try
	{
		DBManager dbm(pCon);
		res = dbm.ExecuteNonQuery(szSqlContent);
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		std::string err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}

int CreateNewGuidByDB(SDatabaseInfo *stDbInfo, char * stGuid)
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		if(pCon)
		{
			string sql;
			STDstring sGuid;
			DBManager dbm(pCon);
			switch(pCon->GetDBType())
			{
			case 1://SQLITE
				break;
			case 2://Oracle
				{
					sql = "Select sys_guid() from dual";
				}
				break;
			case 3: //Mysql
				{
					sql = "select uuid()";
				}
				break;
			case 4: // SQL Server
				{
					sql = "select newid()";
				}
				break;
			}

			dbm.ExecuteReader(sql.c_str());
			if(dbm.Read())
				sGuid = dbm.GetText(0);
			dbm.CloseReader();

			strcpy(stGuid, sGuid.c_str());
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}

int GetMonitorIDsByDB(SDatabaseInfo *stDbInfo, char * stSql, std::vector<string> &monitorIDs)
{
	monitorIDs.clear();
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;
	try
	{
		if(pCon)
		{
			DBManager dbm(pCon);
			dbm.ExecuteReader(stSql);
			while(dbm.Read())
				monitorIDs.push_back(dbm.GetText(0).c_str());
			dbm.CloseReader();
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}

int QueryDataBySql(SDatabaseInfo *stDbInfo, char* stSql, char* stValue)
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		if(pCon)
		{
			STDstring sValue;
			DBManager dbm(pCon);

			dbm.ExecuteReader(stSql);
			if(dbm.Read())
				sValue = dbm.GetText(0);
			dbm.CloseReader();

			strcpy(stValue, sValue.c_str());
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}

int QueryDataBySqlFP(SDatabaseInfo *stDbInfo, char* stSql, char* stValue1, char* stValue2, char* stValue3)
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		if(pCon)
		{
			STDstring sValue1;
			STDstring sValue2;
			STDstring sValue3;
			DBManager dbm(pCon);

			dbm.ExecuteReader(stSql);
			while(dbm.Read())
			{
				sValue1 = dbm.GetText(0);
				sValue2 = dbm.GetText(1);
				sValue3 = dbm.GetText(2);
			}

			dbm.CloseReader();
			strcpy(stValue1, sValue1.c_str());
			strcpy(stValue2, sValue2.c_str());
			strcpy(stValue3, sValue3.c_str());
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}

int QueryAllTextBaseDataBySql(SDatabaseInfo *stDbInfo, char* stSql, vector<STR_TEXT_RECORD_INFO> &vTestData)
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		if(pCon)
		{
			STDstring sValue;
			DBManager dbm(pCon);

			dbm.ExecuteReader(stSql);
			while(dbm.Read())
			{
				STR_TEXT_RECORD_INFO stCurrRecord;
				int i = 0;
                /*stCurrRecord.sRecordId = dbm.GetText(i++);
				stCurrRecord.ulTimeBgn = dbm.GetInt32(i++);
				stCurrRecord.ulTimeEnd = dbm.GetInt32(i++);
                stCurrRecord.sInterPlace = dbm.GetText(i++);
                stCurrRecord.dFreqBgn = dbm.GetDouble(i++);
				stCurrRecord.dFreqEnd = dbm.GetDouble(i++);
				stCurrRecord.ulInterNum   =  dbm.GetInt32(i++);               
                stCurrRecord.ulInterSrcType = dbm.GetInt32(i++);
                stCurrRecord.ulInfluCarrier = dbm.GetInt32(i++);
                stCurrRecord.ulInterRslt = dbm.GetInt32(i++);

                stCurrRecord.sInterTitle = dbm.GetText(i++);
                stCurrRecord.sOther = dbm.GetText(i++);
				stCurrRecord.sSrcFilePath = dbm.GetText(i++);*/

                stCurrRecord.sRecordId = dbm.GetText(i++);
                stCurrRecord.dFreqBgn = dbm.GetDouble(i++);
				stCurrRecord.dFreqEnd = dbm.GetDouble(i++);
                stCurrRecord.ulInterNum   =  dbm.GetInt32(i++); 
                stCurrRecord.ulInterSrcType = dbm.GetInt32(i++);
                stCurrRecord.ulInfluCarrier = dbm.GetInt32(i++);
                stCurrRecord.ulInterRslt = dbm.GetInt32(i++);
                stCurrRecord.sInterTitle = dbm.GetText(i++);
                stCurrRecord.sOther = dbm.GetText(i++);
                stCurrRecord.sSrcFilePath = dbm.GetText(i++);
                
                stCurrRecord.sInterPlace = dbm.GetText(i++);
				stCurrRecord.ulTimeBgn = dbm.GetInt32(i++);
				stCurrRecord.ulTimeEnd = dbm.GetInt32(i++);		              
              			
			    vTestData.push_back(stCurrRecord);
			}
			dbm.CloseReader();
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}


int QueryAllMonitorStationDataBySql(SDatabaseInfo *stDbInfo, char* stSql, vector<STR_MONITORSTATION_INFO> &vMoStationData)
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		if(pCon)
		{
			STDstring sValue;
			DBManager dbm(pCon);

			dbm.ExecuteReader(stSql);
			while(dbm.Read())
			{
				STR_MONITORSTATION_INFO stCurrRecord;
				int i = 0;

                stCurrRecord.sGuid = dbm.GetText(i++);
                stCurrRecord.sIP = dbm.GetText(i++);	              
              			
			    vMoStationData.push_back(stCurrRecord);
			}
			dbm.CloseReader();
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}

NGDBDLL_API int QueryNgStationPositionBySql(SDatabaseInfo *stDbInfo, char* stSql, double& dLon, double& dlat)
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		if(pCon)
		{
			STDstring sValue;
			DBManager dbm(pCon);

			dbm.ExecuteReader(stSql);
			while(dbm.Read())
			{
				int i = 0;

				dLon = dbm.GetDouble(i++);
				dlat = dbm.GetDouble(i++);	              
			}
			dbm.CloseReader();
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}

NGDBDLL_API int QueryMonitorStationIpBySql(SDatabaseInfo *stDbInfo, char* stSql, string& sGuid, string& sIP)
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		if(pCon)
		{
			STDstring sValue;
			DBManager dbm(pCon);

			dbm.ExecuteReader(stSql);
			if (dbm.Read())
			{
				int i = 0;

				sGuid = dbm.GetText(i++);
				sIP = dbm.GetText(i++);         
			}
			dbm.CloseReader();
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}

NGDBDLL_API int QueryMonitorStationStatusBySql(SDatabaseInfo *stDbInfo, char* stSql, int &status, int &workType, int &dataType)
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		if(pCon)
		{
			STDstring sValue;
			DBManager dbm(pCon);

			dbm.ExecuteReader(stSql);
			if (dbm.Read())
			{
				int i = 0;

				status = dbm.GetInt32(i++);
				workType = dbm.GetInt32(i++);
				dataType = dbm.GetInt32(i++);         
			}
			dbm.CloseReader();
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}

int QueryAllMonitorPlanDataBySql(SDatabaseInfo *stDbInfo, char* stSql, vector<stMonitorPlanInfo> &vMoPlanData)
{
	vMoPlanData.clear();
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		if(pCon)
		{
			STDstring sValue;
			DBManager dbm(pCon);

			dbm.ExecuteReader(stSql);
			while(dbm.Read())
			{
				stMonitorPlanInfo stCurrRecord;
				int i = 0;

				stCurrRecord.id = dbm.GetText(i++);
				stCurrRecord.freqstart = dbm.GetDouble(i++);	
				stCurrRecord.freqend = dbm.GetDouble(i++);
				stCurrRecord.freqcenter = dbm.GetDouble(i++);
				stCurrRecord.type = dbm.GetInt32(i++);
				stCurrRecord.stationids = dbm.GetText(i++);
				stCurrRecord.status = dbm.GetInt32(i++);
				stCurrRecord.timestart = dbm.GetInt32(i++);
				stCurrRecord.duration = dbm.GetDouble(i++);
				stCurrRecord.bandwidth = dbm.GetDouble(i++);
				stCurrRecord.recurrencetype = dbm.GetInt32(i++);
				stCurrRecord.recurrence = dbm.GetText(i++);
				stCurrRecord.startdate = dbm.GetInt64(i++);
				stCurrRecord.enddate = dbm.GetInt64(i++);
				stCurrRecord.stat_guid = dbm.GetText(i++);
				i++; // 跳过timestamp
				stCurrRecord.abnormal_tolerance = dbm.GetDouble(i++);
				stCurrRecord.abnormal_duration = dbm.GetDouble(i++);

				vMoPlanData.push_back(stCurrRecord);
			}
			dbm.CloseReader();
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}

int QueryMonthlyReportPlanBySql(SDatabaseInfo *stDbInfo, char* stSql, vector<stMonthlyReportInfo> &vMoPlanData)
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		if(pCon)
		{
			STDstring sValue;
			DBManager dbm(pCon);

			dbm.ExecuteReader(stSql);
			while(dbm.Read())
			{
				stMonthlyReportInfo MoPlanData;
				int i = 0;

				MoPlanData.taskID = dbm.GetText(i++);
				MoPlanData.monthly = dbm.GetText(i++);	
				MoPlanData.day = dbm.GetText(i++);
				MoPlanData.hour = dbm.GetText(i++);
				MoPlanData.duration = dbm.GetInt32(i++);
				MoPlanData.reportDate = dbm.GetText(i++);
				MoPlanData.reportTemplet = dbm.GetText(i++);
				vMoPlanData.push_back(MoPlanData);
			}
			dbm.CloseReader();
			res = 0;
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}



int Query_Data_File( SDatabaseInfo * stDbInfo,char * szSqlContent,char *szFileName )
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;
	
	try
	{
		DBManager dbm(pCon);
		dbm.ExecuteReader(szSqlContent);
		res = 0;
		std::ofstream of;
		of.open(szFileName);
		int fieldcount = dbm.GetFieldsCount();
		int index=0;
		for(index = 0;index<fieldcount;index++)
		{
			of<<dbm.GetName(index);
			if(index<fieldcount-1)
				of<<',';
		}
		of<<'\n';
		//
		while(dbm.Read())
		{
			res++;
			for(index=0;index<fieldcount;index++)
			{
				std::string val = dbm.GetText(index).c_str();
				if(val.empty())
					of<<"NULL";
				else
				{
					of<<"'";
					of<<val.c_str();
					of<<"'";
				}
				if(index<fieldcount-1)
					of<<',';
			}
			of<<'\n';
		}
		of.close();
		dbm.CloseReader();
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		std::string err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"文件打开错误！");
	}
	return res;
}

int Query_Data_Begin( SDatabaseInfo * stDbInfo, SQueryDataInfo *stQDInfo ,char * szSqlContent,int iCount )
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;
	
	try
	{
		DBManager dbm(pCon);
		dbm.ExecuteReader(szSqlContent);
		int rc = dbm.GetResultCount();
		stQDInfo->m_init='Y';
		if(iCount<0)
			res = stQDInfo->m_rowsCount = rc;
		else
			res = stQDInfo->m_rowsCount = rc<iCount?rc:iCount;
		
	}
	catch (DBText& err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		std::string err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch (...)
	{
		strncpy(stDbInfo->error_msg,"准备读取失败",499);
	}
	
	return res;
}

int Query_Data_End( SDatabaseInfo * stDbInfo ,SQueryDataInfo *stQDInfo )
{
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		DBManager dbm(pCon);
		dbm.CloseReader();
		return 0;
	}
	catch(DBText& err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		std::string err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch (...)
	{
		
	}
	return -1;

}
int Query_Data_Body( SDatabaseInfo * stDbInfo, SQueryDataInfo *stQDInfo ,char * szRecBuf )
{
	std::string data;
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		DBManager dbm(pCon);
		int fieldcount = dbm.GetFieldsCount();
		res = 0;
		while(res<stQDInfo->m_rowsCount&&dbm.Read())
		{
			res++;
			for(int i=0;i<fieldcount;i++)
			{
				data += dbm.GetText(i).c_str();
				data+=";";
			}
			data+="\n";
		}
		strcpy(szRecBuf,data.c_str());
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		std::string err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch (...)
	{
		strncpy(stDbInfo->error_msg,"数据读取失败",499);
	}
	return res;
}

int Get_ErrorMsg( SDatabaseInfo * stDbInfo,char szErrorMsg[500] )
{
	strncpy(szErrorMsg,stDbInfo->error_msg,500);
	return 0;
}

int Trans_Begin( SDatabaseInfo * stDbInfo )
{
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		DBManager dbm(pCon);
		dbm.BeginTransaction();
		return 0;
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		std::string err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch (...)
	{
		
	}
	return -1;
}

int Trans_End( SDatabaseInfo * stDbInfo )
{
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		DBManager dbm(pCon);
		dbm.CloseTransaction();
		return 0;
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		std::string err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch (...)
	{
		
	}
	return -1;
}

int Trans_Commit( SDatabaseInfo * stDbInfo )
{
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		DBManager dbm(pCon);
		dbm.Commit();
		return 0;
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		std::string err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch (...)
	{
		
	}
	return -1;
}

int Trans_Rollback( SDatabaseInfo * stDbInfo )
{
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;

	try
	{
		DBManager dbm(pCon);
		dbm.RollBack();
		return 0;
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		std::string err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch (...)
	{
		
	}
	return -1;
}

int QueryLocationProjectById(SDatabaseInfo *stDbInfo, const char* id, stLocationProject& project)
{
	int res = -1;
	IDBConnection *pCon = (IDBConnection*)stDbInfo->m_ctx;
	try
	{
		if(pCon)
		{
			char stSql[400] = {'\0'};
			sprintf(stSql, "select GUID,PROJECT_NAME,PROJECT_PATH,PROJECT_START_TIME,PROJECT_STOP_TIME,PROJECT_LOCATION_COUNT,PROJECT_CENTER_FREQ,PROJECT_BAND,PROJECT_SAMPLE_RATE,PROJECT_USER,PROJECT_TYPE,PROJECT_DEVICE_TYPE from t_ng_location_project where guid = '%s'",id);
			DBManager dbm(pCon);
			dbm.ExecuteReader(stSql);
			if (dbm.Read())
			{
				int i = 0;
				project.guid = dbm.GetText(i++);
				project.project_name = dbm.GetText(i++);
				project.project_path = dbm.GetText(i++);
				project.project_start_time = dbm.GetDouble(i++);
				project.project_stop_time = dbm.GetDouble(i++);
				project.project_location_count = dbm.GetInt32(i++);
				project.project_center_freq = dbm.GetDouble(i++);
				project.project_band = dbm.GetDouble(i++);
				project.project_sample_rate = dbm.GetDouble(i++);
				project.project_user = dbm.GetText(i++);
				project.project_type = dbm.GetInt32(i++); 
				project.project_device_type = dbm.GetInt32(i++);
				res = 0;
			}
			dbm.CloseReader();
		}
	}
	catch(DBText &err)
	{
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#ifdef USE_OCCI
	catch(SQLException &ex)
	{
		STDstring err =ex.getMessage();
		strncpy(stDbInfo->error_msg,err.c_str(),499);
	}
#endif
	catch(...)
	{
		strcpy(stDbInfo->error_msg,"执行错误");
	}
	return res;
}
