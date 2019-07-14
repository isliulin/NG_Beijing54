
#include "DBManager.h"

DBManager::DBManager(IDBConnection* inPCon)
{
		pReader = NULL;
		pCmd = NULL;
		pCon = NULL;
		SetConnection(inPCon);
}

DBManager::~DBManager(void)
{
}

void DBManager::SetConnection(IDBConnection* inPCon)
{
	if(inPCon!=pCon)
	{
		//
		if(pReader)
		{
			pReader->Close();
		}
		//
		pReader = NULL;
		pCmd = NULL;
		pCon = NULL;
		//
		if(inPCon!=NULL)
		{
			pCon = inPCon;
			try
			{
				db_err_msg.Clear();
				inPCon->Open();
				pCmd = pCon->CreateCommand();
				pReader = pCmd->ExecuteReader(NULL);
			}
			catch(DBText & ex)
			{
				db_err_msg = ex;
			}

		}

	}
}

int DBManager::ExecuteNonQuery(const char* sql)
{
	try
	{
		db_err_msg.Clear();
		if(pCmd==NULL)
			return 0;
		if(pCon->GetStatus()!=DBConOpen)
			pCon->Open();
		return pCmd->ExecuteNoQuery(sql);
	}
	catch(DBText &ex)
	{
		db_err_msg = ex;
		//throw ex;
		return 0;
	}

}

bool DBManager::ExecuteReader(const char* sql)
{
	try
	{
		db_err_msg.Clear();
		if(pCmd == NULL)
			return false;
		if(pCon->GetStatus()!=DBConOpen)
			pCon->Open();
		pReader = pCmd->ExecuteReader(sql);
		return (pReader!=NULL);
	}
	catch(DBText &ex)
	{
		db_err_msg = ex;
	}
	return false;
}



bool DBManager::BeginTransaction(void)
{
	if(pCmd == NULL)
		return false;
	if(pCon->GetStatus()!=DBConOpen)
		pCon->Open();
	return pCmd->BeginTransaction();
}

bool DBManager::RollBack(void)
{
	if(pCmd == NULL)
		return false;
	return pCmd->RollBack();
}


bool DBManager::Commit(void)
{
	if(pCmd == NULL)
		return false;
	return pCmd->Commit();
}

bool DBManager::CloseTransaction(void)
{
	if(pCmd == NULL)
		return false;
	return pCmd->CloseTransaction();
}

void DBManager::SetCommandTimeout(int timeout)
{
	if(pCmd != NULL)
		pCmd->SetCommandTimeout(timeout);
}

bool DBManager::InsertBlob(const char* sql, void* blob, int bloblength)
{
	try
	{
		db_err_msg.Clear();
		if(pCmd == NULL)
		return false;
		return pCmd->InsertBLOB(sql,blob,bloblength);
	}
	catch(DBText &ex)
	{
		db_err_msg = ex;
		throw ex;
	}

}



DBBool DBManager::GetBoolean(const char * name)
{
	if(pReader == NULL)
		return DBBool();
	return pReader->GetBoolean(name);
}

DBBool DBManager::GetBoolean(index_int index)
{
	if(pReader == NULL)
		return DBBool();
	return pReader->GetBoolean(index);
}
DBBool DBManager::GetSBoolean(const char* name) {
	DBBool val;
	if(pReader!= NULL)
	{
		const char* s = pReader->GetText(name);
		if((strcmp(s,"y") == 0)
			||(strcmp(s,"Y") == 0)
			||(strcmp(s,"1")==0)
			||(strcmp(s,"-1")==0))
			val = true;
		else
			val = false;
	}
	return val;
}

DBBool DBManager::GetSBoolean(index_int index) {
	DBBool val;
	if(pReader!= NULL)
	{
		const char* s  = pReader->GetText(index);
		if((strcmp(s,"y") == 0)
			||(strcmp(s,"Y") == 0)
			||(strcmp(s,"1")==0)
			||(strcmp(s,"-1")==0))
			val = true;
		else
			val = false;
	}
	return val;
}
DBByte DBManager::GetByte(const char* name)
{
	if(pReader == NULL)
		return DBByte();
	return pReader->GetByte(name);
}

DBByte DBManager::GetByte(index_int index)
{
	if(pReader==NULL)
		return DBByte();
	return pReader->GetByte(index);
}

DBBlob DBManager::GetBlob(const char* name)
{
	if(pReader == NULL)
		return DBBlob();
	return pReader->GetBlob(name);
}

DBBlob DBManager::GetBlob(index_int index)
{
	if(pReader == NULL)
		return DBBlob();
	return pReader->GetBlob(index);
}

DBChar DBManager::GetChar(const char* name)
{
	if(pReader == NULL)
		return DBChar();
	return pReader->GetChar(name);
}

DBChar DBManager::GetChar(index_int index)
{
	if(pReader == NULL)
		return DBChar();
	return pReader->GetChar(index);
}


DBDouble DBManager::GetDouble(const char* name)
{
	if(pReader == NULL)
		return DBDouble();
	return pReader->GetDouble(name);
}

DBDouble DBManager::GetDouble(index_int index)
{
	if(pReader == NULL)
		return DBDouble();
	return pReader->GetDouble(index);
}

DBFloat DBManager::GetFloat(const char* name)
{
	if(pReader == NULL)
		return DBFloat();
	return pReader->GetFloat(name);
}


DBFloat DBManager::GetFloat(index_int index)
{
	if(pReader == NULL)
		return DBFloat();
	return pReader->GetFloat(index);
}

DBInt16 DBManager::GetInt16(const char* name)
{
	if(pReader == NULL)
		return DBInt16();
	return pReader->GetInt16(name);
}

DBInt16 DBManager::GetInt16(index_int index)
{
	if(pReader == NULL)
		return DBInt16();
	return pReader->GetInt16(index);
}

DBInt32 DBManager::GetInt32(const char* name)
{
	if(pReader == NULL)
		return DBInt32();
	return pReader->GetInt32(name);
}


DBInt32 DBManager::GetInt32(index_int index)
{
	if(pReader == NULL)
		return DBInt32();
	return pReader->GetInt32(index);
}

DBInt64 DBManager::GetInt64(const char* name)
{
	if(pReader == NULL)
		return DBInt64();
	return pReader->GetInt64(name);
}

DBInt64 DBManager::GetInt64(index_int index)
{
	if(pReader == NULL)
		return DBInt64();
	return pReader->GetInt64(index);
}

DBDatetime DBManager::GetDatetime(const char* name)
{
	if(pReader == NULL)
		return DBDatetime();
	return pReader->GetDatetime(name);
}

DBDatetime DBManager::GetDatetime(index_int index)
{
	if(pReader == NULL)
		return DBDatetime();
	return pReader->GetDatetime(index);
}

DBText DBManager::GetText(const char* name)
{
	if(pReader == NULL)
		return DBText();
	return pReader->GetText(name);
}

DBText DBManager::GetText(index_int index)
{
	if(pReader == NULL)
		return DBText();
	return pReader->GetText(index);
}

index_int DBManager::GetFieldsCount(void)
{
	if(pReader == NULL)
		return index_int(0);
	return pReader->GetFieldsCount();
}

DBText DBManager::GetName(index_int index)
{
	if(pReader == NULL)
		return DBText();
	return pReader->GetName(index);
}

bool DBManager::IsDBNull(const char* name)
{
	if(pReader == NULL)
		return true;
	return pReader->IsDBNull(name);
}

bool DBManager::IsDBNull(index_int index)
{
	if(pReader == NULL)
		return true;
	return pReader->IsDBNull(index);
}

bool DBManager::Read(void)
{
	if(pReader == NULL)
		return false;
	return pReader->Read();
}

void DBManager::CloseReader(void)
{
	if(pReader!=NULL)
		pReader->Close();
	pReader = NULL;
}



index_int DBManager::GetResultCount(void)
{
	if(pReader == NULL)
		return index_int(0);
	return pReader->GetResultCount();
}

STDstring DBManager::CreateNewGuid()
{
	STDstring sGuid;
	string sql;
	if(pCon)
	{
		switch(pCon->GetDBType())
		{
		case 1://SQLITE
			break;
		case 2://Oracle
			{
				sql = "Select sys_guid() from dual";
				ExecuteReader(sql.c_str());
				if(Read())
					sGuid = GetText(0);
				CloseReader();
			}
			break;
		case 3: //Mysql
			{
				sql = "select uuid()";
				ExecuteReader(sql.c_str());
				if(Read())
					sGuid = GetText(0);
				CloseReader();
			}
			break;
		case 4: // SQL Server
			{
				sql = "select newid()";
				ExecuteReader(sql.c_str());
				if(Read())
					sGuid = GetText(0);
				CloseReader();
			}
			break;
		}
	}
	//check if success 
	if(sGuid.empty())
	{
		sGuid = "124acdg2147cdf14d";
	}
	return sGuid;
}
