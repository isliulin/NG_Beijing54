
#include "IDBConnection.h"

namespace NGDBCom
{

	IDBConnection::IDBConnection(void)
	{
		db_status = DBConClose;
		db_type = -1;
	}

	IDBConnection::~IDBConnection(void)
	{

	}

	void IDBConnection::SetConnectionString(const char* connectionString)
	{
		db_con_string  = connectionString;
	}

	bool IDBConnection::Open(const char* connectionString)
	{
		SetConnectionString(connectionString);
		return Open();
	}
	DBConnectionState IDBConnection::GetStatus(void)
	{
		return db_status;
	}

	int IDBConnection::GetDBType()
	{
		return db_type;
	}

}


