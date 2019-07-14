/*
 * DBOraCommand.cpp
 *
 *  Created on: May 15, 2013
 *      Author: chenxing
 */
#ifdef USE_OCCI

#include "DBOraCommand.h"
#include "DBOraReader.h"
DBOraCommand::~DBOraCommand() {
	// TODO Auto-generated destructor stub
	if(p_reader!=NULL)
		delete p_reader;
	if(p_con!=NULL && p_stmt!=NULL)
		p_con->terminateStatement(p_stmt);

}
DBOraCommand::DBOraCommand(Connection*pcon) {
	// TODO Auto-generated constructor stub
	p_con = pcon;
	p_stmt = NULL;
	p_reader = NULL;
	sTransIndex = 0;
}

bool DBOraCommand::CreateStmt()
{
	if(p_stmt == NULL)
	{
		if(p_con!=NULL)
		{
			p_stmt = p_con->createStatement();
			p_stmt->setAutoCommit(true);
		}
	}
	if(p_reader!=NULL)
		p_reader->Close();
	return p_stmt!=NULL;
}
int DBOraCommand::ExecuteNoQuery(const char* sql)
{
	try
	{
		if(!sql&&CreateStmt())
		{
			return p_stmt->executeUpdate(sql);
		}
		return 0;
	}
	catch(oracle::occi::SQLException& ex)
	{
		DBText err = ex.getMessage().c_str();
		throw err;
	}

}

bool DBOraCommand::CreateReader()
{
	if(p_reader == NULL)
	{
		if(CreateStmt())
		{
			p_reader = new DBOraReader(p_stmt);
		}
	}
	return p_reader!= NULL;
}
IDataReader* DBOraCommand::ExecuteReader(const char* sql)
{
	try
	{
		if(sql&&CreateReader())
		{
			p_reader->Query(sql);
		}
		return p_reader;
	}
	catch (oracle::occi::SQLException&ex)
	{
		DBText err = ex.getMessage().c_str();
		throw err;
	}
	

}

bool DBOraCommand::BeginTransaction(void)
{	
	if(CreateStmt())
	{	
		++sTransIndex;	
		if(1 == sTransIndex)
			p_stmt->setAutoCommit(false);
		return true;
	}
	return false;
}

bool DBOraCommand::RollBack(void)
{
	if(p_con!=NULL)
	{
		if(1== sTransIndex )
			p_con->rollback();
		return true;
	}
	return false;
}

bool DBOraCommand::Commit(void)
{
	if(p_con!=NULL)
	{
		if(1== sTransIndex)
			p_con->commit();
		return true;
	}
	return false;
}
bool DBOraCommand::CloseTransaction(void)
{
	if(CreateStmt())
	{
		--sTransIndex ;
		if(0 == sTransIndex)
			p_stmt->setAutoCommit(true);
		return true;
	}
	return false;
}

void DBOraCommand::SetCommandTimeout(int timeout)
{
	//none
}
bool DBOraCommand::InsertBLOB(const char* sql, void* blob, unsigned int bloblength)
{
	try
	{
		if(sql&&CreateStmt())
		{
			p_stmt->setSQL(sql);
			Blob tempblob;
			unsigned int writelen = 0;
			if((writelen=tempblob.writeChunk(0,(unsigned char*)blob,bloblength,0))==bloblength)
			{
				p_stmt->setBlob(1,tempblob);
				if(p_stmt->executeUpdate()>0)
					return true;
			}
		}
		return false;
	}
	catch(oracle::occi::SQLException& ex)
	{
		DBText err = ex.getMessage().c_str();
		throw err;
	}
}

#endif /*USE_OCCI*/