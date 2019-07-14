#ifdef USE_MYSQL
#pragma once
#include "DBMySqlConnection.h"
#include "IDBCommand.h"
class DBMySqlReader;
class DBMySqlCommand :
	public IDBCommand
{
protected:
	friend class DBMySqlConnection;
	DBMySqlCommand(MYSQL * pcon);
	virtual ~DBMySqlCommand(void);
protected:
	MYSQL * p_con;
	DBMySqlReader *p_reader;
protected:
	bool CreateReader();
private:
	short sTransIndex;
public:
	virtual int ExecuteNoQuery(const char* sql);
	virtual IDataReader* ExecuteReader(const char* sql);
	virtual bool BeginTransaction(void);
	virtual bool RollBack(void);
	virtual bool Commit(void);
	virtual bool CloseTransaction(void);
	virtual void SetCommandTimeout(int timeout);
	virtual bool InsertBLOB(const char* sql,  void* blob, unsigned int bloblength);
};
#endif
