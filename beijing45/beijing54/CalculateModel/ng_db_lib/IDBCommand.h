#ifndef _I_DB_COMMAND_H_
#define _I_DB_COMMAND_H_
#include "NGDBDefined.h"
#include "DBData.h"
namespace NGDBCom
{
	interface IDBConnection;
	interface IDataReader;
	interface NGDBDLL_API IDBCommand
	{
	protected:
		DBText db_err_msg;
	public:
		IDBCommand(void);
		virtual ~IDBCommand(void);
	public:
		
	public:
		virtual int ExecuteNoQuery(const char* sql) = 0;

		virtual IDataReader* ExecuteReader(const char* sql) = 0;

		virtual bool BeginTransaction(void)=0;

		virtual bool RollBack(void) = 0;

		virtual bool Commit(void) = 0;


		virtual bool CloseTransaction(void) = 0;

		virtual void SetCommandTimeout(int timeout) = 0;
		// 
		virtual bool InsertBLOB(const char* sql, void* blob, unsigned int bloblength);
	};
}
#endif