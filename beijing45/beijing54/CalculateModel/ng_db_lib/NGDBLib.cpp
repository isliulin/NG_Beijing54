#include "NGDBLib.h"
#include "../../NGLog/NGLogPrint.h"

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

#ifdef USE_OCILIB
#include "DBOCIConnection.h"
#endif

IDBConnection * CreateDBConnection(int DBType,const char* user,const char*pwd,const char *con_str)
{
	IDBConnection *pCon = NULL;
	try
	{
		switch(DBType)
		{
		case USEDBSQLITE:
#ifdef USE_SQLITE
			pCon = new DBSqliteConnection();
#endif
			break;

		case USEDBORACLE:

#ifdef USE_OCCI
			pCon= new DBOraConnection(user,pwd);
			break;
#endif
#ifdef USE_OCILIB
			pCon= new DBOCIConnection(user,pwd);
			break;
#endif
			
		case USEDBMYSQL:
#ifdef USE_MYSQL
			pCon = new DBMySqlConnection(user,pwd);
#endif
			break;
		case USEDBSQLSERVER:
#ifdef USE_SQLSERVER
			pCon = new DBSQLConnection(user,pwd);
#endif
			break;
		case USEDBORACLEOCILIB:		
#ifdef USE_OCILIB
			pCon = new DBOCIConnection(user,pwd);
#endif
			break;
		}

		if(pCon!=NULL)
		{
			if(!pCon->Open(con_str))
			{
				CloseDBConnection(pCon);
				pCon = NULL;
				NG_WriteLog(NGLOG_Error,__FUNCTION__,"创建数据库连接异常!");
			}
		}
	}
#ifdef USE_OCCI
	catch (SQLException& e)
	{
		if(pCon!=NULL)
			CloseDBConnection(pCon);
		pCon = NULL;
		std::string err = e.getMessage();
	}
#endif
	catch(...)
	{
		if(pCon!=NULL)
			CloseDBConnection(pCon);
		pCon = NULL;
		NG_WriteLog(NGLOG_Error,__FUNCTION__,"创建数据库连接异常!");
	}

	return pCon;
}

void CloseDBConnection(IDBConnection * pCon)
{
	if(pCon!=NULL)
		delete pCon;
}