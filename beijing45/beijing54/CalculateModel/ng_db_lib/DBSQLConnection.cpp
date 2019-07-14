#ifdef USE_SQLSERVER
#include "DBSQLConnection.h"
#include "DBSQLCommand.h"
#include <string>
class SQLINITCom
{
public:
	SQLINITCom(){::CoInitialize(NULL);}
	~SQLINITCom(){::CoUninitialize();}
};

SQLINITCom comInit;


DBSQLConnection::DBSQLConnection(const char* inuser,const char* inpwd)
{
	p_cmd = NULL;
	user = inuser;
	pwd = inpwd;
	db_type = 4;
}

DBSQLConnection::~DBSQLConnection(void)
{
	Close();
}

bool DBSQLConnection::Open( void )
{
	try
	{
		if(db_status == DBConClose)
		{
			
			m_pCon.CreateInstance(__uuidof(Connection));
			HRESULT hr = m_pCon->Open(db_con_string.c_str(),user.c_str(),pwd.c_str(),adModeUnknown);//adModeUnknown
			if (SUCCEEDED(hr))
			{
				db_status = DBConOpen;
			}
		}
	}
	catch(_com_error er)
	{ 
		std::string e = "Open ";
		e+=db_con_string;
		e+="failed!";
		DBText err = e.c_str(); 
		throw err;
	}
	return (db_status == DBConOpen);	
}

bool DBSQLConnection::Close( void )
{
	if(db_status == DBConOpen)
	{
		ClearCommand();
		if(SUCCEEDED(m_pCon->Close()))
		{
			m_pCon.Release();
		}
		db_status = DBConClose;
	}
	return (DBConClose == db_status);
}

IDBCommand* DBSQLConnection::CreateCommand( void )
{
	if(p_cmd==NULL)
	{
		if(db_status != DBConClose)
		{
			p_cmd = new DBSQLCommand(m_pCon);
		}
	}
	return p_cmd;
}

void DBSQLConnection::ClearCommand( void )
{
	if(p_cmd!=NULL)
	{
		delete p_cmd;
		p_cmd = NULL;
	}
}

#endif

