#ifndef  _I_DB_FILE_H
#define  _I_DB_FILE_H
#include "DBManager.h"

class NGDBDLL_API IDBFile
{
public:
	IDBFile(IDBConnection * p_con){m_pcon = p_con;}
	virtual ~IDBFile(void){}
	virtual bool FileToDB(const char* filename,const char * tablename=0)=0;
	virtual bool DBToFile(const char* filename,const char *table)=0;
protected:
	IDBConnection *m_pcon;
public:
	static IDBFile * CreateDBFile(IDBConnection *p_con);
	static void ReleaseDBFile(IDBFile * pDBFile);
};

#endif