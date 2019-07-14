#ifdef USE_MYSQL
#include "DBMySqlCommand.h"
#include "DBMySqlReader.h"

DBMySqlCommand::DBMySqlCommand( MYSQL * pcon )
{
	p_con = pcon;
	p_reader = NULL;
	sTransIndex = 0;
}
DBMySqlCommand::~DBMySqlCommand(void)
{
	if(p_reader!=NULL)
	{
		delete p_reader;
	}
}

bool DBMySqlCommand::CreateReader()
{
	if(p_reader==NULL)
	{
		p_reader = new DBMySqlReader(p_con);
	}
	return (p_reader!=NULL);
}

int DBMySqlCommand::ExecuteNoQuery( const char* sql )
{
	int res = mysql_query(p_con,sql);
	if(res)
	{
		DBText err= mysql_error(p_con);
		throw err;
	}
	return 0;
}

IDataReader* DBMySqlCommand::ExecuteReader( const char* sql )
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

bool DBMySqlCommand::BeginTransaction( void )
{
	if(p_con)
	{
		++sTransIndex;	
		if(1 == sTransIndex)
			mysql_autocommit(p_con,false);
		return true;
	}
	return false;
}

bool DBMySqlCommand::RollBack( void )
{
	if(p_con!=NULL)
	{
		if(1== sTransIndex )
			mysql_rollback(p_con);
		return true;
	}
	return false;
}

bool DBMySqlCommand::Commit( void )
{
	if(p_con!=NULL)
	{
		if(1== sTransIndex)
			mysql_commit(p_con);
		return true;
	}
	return false;
}

bool DBMySqlCommand::CloseTransaction( void )
{
	if(p_con!=NULL)
	{
		--sTransIndex ;
		if(0 == sTransIndex)
			mysql_autocommit(p_con,true);
		return true;
	}
	return false;
}

void DBMySqlCommand::SetCommandTimeout( int timeout )
{

}

bool DBMySqlCommand::InsertBLOB( const char * sql, void* blob, unsigned int bloblength )
{
	bool bOk = false;
	if(p_con!=NULL)
	{
		MYSQL_STMT *p_stmt = NULL;
		if(p_stmt = mysql_stmt_init(p_con))
		{
			MYSQL_BIND bind[1];
			bind[0].buffer = blob;
			unsigned long bl = bloblength;
			bind[0].length = &bl;
			bind[0].is_null = 0;
			bind[0].buffer_type = MYSQL_TYPE_BLOB;
			if(mysql_stmt_prepare(p_stmt,sql,strlen(sql)))
			{
				if(mysql_stmt_bind_param(p_stmt,bind))
				{
					mysql_stmt_execute(p_stmt);
				}
			}
			mysql_stmt_free_result(p_stmt);
		}
	}
	return bOk;
}
#endif