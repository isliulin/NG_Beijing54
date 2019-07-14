
#ifdef USE_SQLITE

#ifndef _DBSQLITE_CONNECTION
#define _DBSQLITE_CONNECTION

#include "IDBConnection.h"
using namespace NGDBCom;
#include "sqlite3.h"
#ifdef _MSC_VER
#pragma comment(lib,"sqlite3.lib")
#endif

class DBSqliteCommand;
class DBSqliteConnection :
	public IDBConnection
{
public:
	DBSqliteConnection(void);
	virtual ~DBSqliteConnection(void);
	sqlite3 *p_con;
	DBSqliteCommand *p_cmd;
private:
public:
	virtual bool Open(void);
	virtual bool Close(void);
	virtual IDBCommand* CreateCommand(void);
protected:
	virtual void ClearCommand(void);
};
#endif
#endif/*USE_SQLITE*/