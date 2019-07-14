#pragma once
#include "IDBFile.h"

class CDBFile :
	public IDBFile
{
public:
	CDBFile(IDBConnection*p_con);
	~CDBFile(void);
public:
	virtual bool FileToDB(const char* filename,const char * tablename=0);
	virtual bool DBToFile(const char* filename,const char *table);
};
