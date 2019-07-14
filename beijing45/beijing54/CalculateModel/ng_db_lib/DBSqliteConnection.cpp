#ifdef USE_SQLITE

#include "DBSqliteConnection.h"
#include "DBSqliteCommand.h"
#include <string>

DBSqliteConnection::DBSqliteConnection(void)
{
	p_con = NULL;
	p_cmd = NULL;
	db_type = 1;
}

DBSqliteConnection::~DBSqliteConnection(void)
{
	if(p_con!=NULL)
		Close();
}

bool DBSqliteConnection::Open( void )
{
	try
	{
		if(db_status == DBConClose)
		{
			if(SQLITE_OK == sqlite3_open(db_con_string.c_str(),&p_con))
			{
				if(p_con!=NULL)
					db_status = DBConOpen;
			}
		}
	}
	catch(...)
	{
		std::string e = "Open ";
		e+=db_con_string;
		e+="failed!";
		DBText err = e.c_str();
		throw err;
	}
	return (db_status == DBConOpen);	
}

bool DBSqliteConnection::Close( void )
{
	if(db_status == DBConOpen)
	{
		ClearCommand();
		if(SQLITE_OK == sqlite3_close(p_con))
		{
			p_con = NULL;
		}
		db_status = DBConClose;
	}
	return (p_con == NULL);
}

void DBSqliteConnection::ClearCommand( void )
{
	if(p_cmd!=NULL)
	{
		delete p_cmd;
		p_cmd = NULL;
	}
}

IDBCommand* DBSqliteConnection::CreateCommand( void )
{
	if(p_cmd == NULL)
	{
		if(p_con!=NULL)
		{
			p_cmd = new DBSqliteCommand(p_con);
		}
	}
	return p_cmd;
}

#endif/*USE_SQLITE*/