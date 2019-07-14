#pragma once
#ifdef USE_OCILIB

#include "DBOCIConnection.h"
#include "IDBCommand.h"
class DBOCIReader;
class DBOCICommand :
	public IDBCommand
{

protected:
	friend class DBOCIConnection;
	DBOCICommand(OCI_Connection *pcon);
	virtual ~DBOCICommand(void);
protected:
	OCI_Connection * p_con;
	OCI_Statement * p_st;
	DBOCIReader *p_reader;
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