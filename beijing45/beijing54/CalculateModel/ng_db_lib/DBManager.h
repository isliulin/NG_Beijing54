#ifndef _DB_MANAGER_H_
#define _DB_MANAGER_H_


#include "NGDBDefined.h"
#include "IDBConnection.h"
#include "IDBCommand.h"
#include "IDataReader.h"
using namespace NGDBCom;
class NGDBDLL_API DBManager
{
protected:
	IDBConnection * pCon;
	IDBCommand* pCmd;
	IDataReader*pReader;
protected:
	DBText db_err_msg;
public:
	DBManager(IDBConnection* inPCon);
	virtual ~DBManager(void);
public:
	DBText GetLastErrorMsg(){return db_err_msg;}
	void SetConnection(IDBConnection* inPCon);

	int ExecuteNonQuery(const char* sql);
	//int ExecuteNonQuery(string sql){return ExecuteNonQuery(sql.c_str());}
	bool ExecuteReader(const char*  sql);
	//bool ExecuteReader(string sql){return ExecuteReader(sql.c_str());}
	bool BeginTransaction(void);
	bool RollBack(void);
	bool Commit(void);
	bool CloseTransaction(void);
	void SetCommandTimeout(int timeout);
	bool InsertBlob(const char* sql, void* blob, int bloblength);
	DBBool GetBoolean(const char * name);
	DBBool GetBoolean(index_int index);
	DBBool GetSBoolean(const char * name);
	DBBool GetSBoolean(index_int index);
	DBByte GetByte(const char* name);
	DBByte GetByte(index_int index);
	DBBlob GetBlob(const char* name);
	DBBlob GetBlob(index_int index);
	DBChar GetChar(const char* name);
	DBChar GetChar(index_int index);
	DBDouble GetDouble(const char* name);
	DBDouble GetDouble(index_int index);
	DBFloat GetFloat(const char* name);
	DBFloat GetFloat(index_int index);
	DBInt16 GetInt16(const char* name);
	DBInt16 GetInt16(index_int index);
	DBInt32 GetInt32(const char* name);
	DBInt32 GetInt32(index_int index);
	DBInt64 GetInt64(const char* name);
	DBInt64 GetInt64(index_int index);
	DBDatetime GetDatetime(const char* name);
	DBDatetime GetDatetime(index_int index);
	DBText GetText(const char* name);
	DBText GetText(index_int index);
	index_int GetFieldsCount(void);
	DBText GetName(index_int index);
	bool IsDBNull(const char* name);
	bool IsDBNull(index_int index);
	bool Read(void);
	void CloseReader(void);
	index_int GetResultCount(void);
	STDstring CreateNewGuid();
};
#endif