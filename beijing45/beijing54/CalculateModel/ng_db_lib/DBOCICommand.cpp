#ifdef USE_OCILIB

#include "DBOCICommand.h"
#include "DBOCIReader.h"
DBOCICommand::DBOCICommand(OCI_Connection *pcon)
{
	p_con = pcon;
	p_st = OCI_StatementCreate(p_con);
	p_reader = NULL;
	sTransIndex = 0;
	
}

DBOCICommand::~DBOCICommand(void)
{
	if(p_st)
		OCI_StatementFree(p_st);
	if(p_reader!=NULL)
	{
		delete p_reader;
	}
}

int DBOCICommand::ExecuteNoQuery( const char* sql )
{
	if(p_st)
	{
		return OCI_ExecuteStmt(p_st,sql);
	}
	return 0;
}

bool DBOCICommand::BeginTransaction( void )
{
	if(p_con)
	{
		++sTransIndex;	
		if(1 == sTransIndex)
			OCI_SetAutoCommit(p_con,false);
		return true;
	}
	return false;
}

bool DBOCICommand::RollBack( void )
{
	if(p_con)
	{
		if(1== sTransIndex )
			OCI_Rollback(p_con);
		return true;
	}
	return false;
}

bool DBOCICommand::Commit( void )
{
	if(p_con!=NULL)
	{
		if(1== sTransIndex)
			OCI_Commit(p_con);
		return true;
	}
	return false;
}

bool DBOCICommand::CloseTransaction( void )
{
	if(p_con!=NULL)
	{
		--sTransIndex ;
		if(0 == sTransIndex)
			OCI_SetAutoCommit(p_con,true);
		return true;
	}
	return false;
}

void DBOCICommand::SetCommandTimeout( int timeout )
{

}

bool DBOCICommand::InsertBLOB( const char* sql, void* blob, unsigned int bloblength )
{
	bool bOk = false;
	if(p_con!=NULL)
	{
		OCI_Prepare(p_st,sql);
		OCI_Lob * plob = OCI_LobCreate(p_con,OCI_BLOB);
		OCI_LobWrite(plob,blob,bloblength);
		OCI_BindLob(p_st,":1",plob);
		bOk = OCI_Execute(p_st)!=0;
		OCI_LobFree(plob);
		OCI_Commit(p_con);
	}
	return bOk;
}

IDataReader* DBOCICommand::ExecuteReader( const char* sql )
{

		if(sql&&CreateReader())
		{
			p_reader->Query(sql);
		}
		return p_reader;

}

bool DBOCICommand::CreateReader()
{
	if(p_reader == NULL)
	{
		if(p_st)
		{
			p_reader = new DBOCIReader(p_st);
		}
	}
	return p_reader!= NULL;
}

#endif