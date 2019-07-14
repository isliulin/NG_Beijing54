
#include "IDBCommand.h"
#include "IDBConnection.h"
namespace NGDBCom
{
	IDBCommand::IDBCommand(void)
	{
	}

	IDBCommand::~IDBCommand(void)
	{
	}
	//
	bool IDBCommand::InsertBLOB(const char* sql, void* blob, unsigned int bloblength)
	{	
		return false;
	}
}



