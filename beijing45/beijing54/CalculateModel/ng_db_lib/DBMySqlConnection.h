#ifdef USE_MYSQL
#pragma once
#if defined(_WIN32) || defined(__WIN32__)
#include <Windows.h>
#endif
#include <mysql.h>
#ifdef _MSC_VER
#pragma comment(lib,"libmysql.lib")
#endif
#include "IDBConnection.h"
using namespace NGDBCom;

class DBMySqlCommand;
class DBMySqlConnection :
	public IDBConnection
{
public:
	DBMySqlConnection(const char* inuser,const char* inpwd);
	virtual ~DBMySqlConnection(void);
	DBText user;
	DBText pwd;
	MYSQL *p_con;
	DBMySqlCommand *p_cmd;
private:
public:
	virtual bool Open(void);
	virtual bool Close(void);
	virtual IDBCommand* CreateCommand(void);
protected:
	virtual void ClearCommand(void);
};
#endif


