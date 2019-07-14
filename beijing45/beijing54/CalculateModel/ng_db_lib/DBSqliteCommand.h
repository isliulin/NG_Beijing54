
#ifdef USE_SQLITE

#ifndef _DBSQLITE_COMMAND
#define _DBSQLITE_COMMAND

#include "DBSqliteConnection.h"
#include "IDBCommand.h"

class DBSqliteReader;
class DBSqliteCommand :
	public IDBCommand
{
protected:
	friend class DBSqliteConnection;
	DBSqliteCommand(sqlite3*p_con);
	virtual ~DBSqliteCommand(void);
protected:
	sqlite3 * p_con;
	DBSqliteReader *p_reader;
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
#endif /*USE_SQLITE*/