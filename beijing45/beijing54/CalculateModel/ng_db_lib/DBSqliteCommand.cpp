#ifdef USE_SQLITE

#include "DBSqliteCommand.h"
#include "DBSqliteReader.h"

DBSqliteCommand::DBSqliteCommand(sqlite3 *pcon)
{
	p_con = pcon;
	p_reader = NULL;
	sTransIndex = 0;
}

DBSqliteCommand::~DBSqliteCommand(void)
{
	if(p_reader!=NULL)
	{
		delete p_reader;
	}
}

int DBSqliteCommand::ExecuteNoQuery( const char* sql )
{
	int nRows = 0;
	char *pErr = NULL;
	if(SQLITE_OK == sqlite3_exec(p_con,sql,NULL,NULL,&pErr))
	{
		nRows = sqlite3_changes(p_con);
	}
	if(pErr!=NULL)
	{
		DBText err = pErr;
		sqlite3_free(pErr);
		throw err;
	}
	return nRows;
}

IDataReader* DBSqliteCommand::ExecuteReader( const char* sql )
{
	bool bOK = false;
	if(CreateReader())
	{
		bOK = p_reader->Query(sql);
	}
	if(bOK)
		return p_reader;
	return NULL;
}

bool DBSqliteCommand::CreateReader()
{
	if(p_reader==NULL)
	{
		p_reader = new DBSqliteReader(p_con);
	}
	return (p_reader!=NULL);

}

bool DBSqliteCommand::BeginTransaction( void )
{
	if(p_con)
	{
		++sTransIndex;	
		if(1 == sTransIndex)
			ExecuteNoQuery("begin transaction");
		return true;
	}
	return false;
}

bool DBSqliteCommand::RollBack( void )
{
	if(p_con)
	{
		if(1== sTransIndex)
			ExecuteNoQuery("rollback transaction");
		return true;
	}
	return false;
}

bool DBSqliteCommand::Commit( void )
{
	if(p_con)
	{
		if(1==sTransIndex)
			ExecuteNoQuery("commit transaction");
		return true;
	}
	return false;
}

bool DBSqliteCommand::CloseTransaction( void )
{
	if(p_con)
	{
		sTransIndex --;
		if(0 == sTransIndex)
			return 0!=sqlite3_get_autocommit(p_con);
		return true;
	}
	return false;
	
}

void DBSqliteCommand::SetCommandTimeout( int timeout )
{
	// none
}

bool DBSqliteCommand::InsertBLOB( const char* sql, void* blob, unsigned int bloblength )
{
	bool bOk = false;
	if(p_con!=NULL)
	{
		sqlite3_stmt *p_stmt = NULL;
		if(SQLITE_OK == sqlite3_prepare(p_con,sql,-1,&p_stmt,NULL))
		{
			if(SQLITE_OK == sqlite3_bind_blob(p_stmt,1,blob,(int)bloblength,NULL))
			if(SQLITE_ERROR != sqlite3_step(p_stmt))
			{
				bOk = true;
			}
			else
			{
				DBText err = sqlite3_errmsg(p_con);
				sqlite3_finalize(p_stmt);
				p_stmt = NULL;
				throw err;
			}
		}
		if(p_stmt!=NULL)
			sqlite3_finalize(p_stmt);
	}
	return bOk;

}

#endif /*USE_SQLITE*/