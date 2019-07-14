#ifdef USE_SQLSERVER
#pragma once
#include "DBSQLConnection.h"
#include "IDBCommand.h"

class DBSQLReader;
class DBSQLCommand :
	public IDBCommand
{	
protected:
	friend class DBSQLConnection;
	DBSQLCommand(_ConnectionPtr &p_con);
	virtual ~DBSQLCommand(void);
protected:
	_ConnectionPtr & p_con;
	DBSQLReader *p_reader;
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
