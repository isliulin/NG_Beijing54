#ifdef USE_SQLSERVER
#import "c:\Program Files (x86)\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#pragma once

#include "IDBConnection.h"
using namespace NGDBCom;

class DBSQLCommand;
class DBSQLConnection :
	public IDBConnection
{
public:
	DBSQLConnection(const char* inuser,const char* inpwd);
	virtual ~DBSQLConnection(void);
protected:
	_ConnectionPtr		m_pCon;
	DBSQLCommand *p_cmd;
private:
	DBText user;
	DBText pwd;
public:
	virtual bool Open(void);
	virtual bool Close(void);
	virtual IDBCommand* CreateCommand(void);
protected:
	virtual void ClearCommand(void);
};
#endif
