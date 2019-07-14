#ifdef USE_SQLSERVER
#pragma once
#include "DBSQLCommand.h"
#include "IDataReader.h"

class DBSQLReader :
	public IDataReader
{
protected:
	friend class DBSQLCommand;
	DBSQLReader(_ConnectionPtr&pcon);
	virtual ~DBSQLReader(void);
protected:
	_ConnectionPtr &p_con;
	_RecordsetPtr p_stmt;
protected:
	bool Query(const char* sql);
	unsigned int lastRow;
	bool bResultEnd;
public:
	virtual void Close();
	virtual DBBool GetBoolean(const char* name);
	virtual DBBool GetBoolean(index_int index);
	virtual DBByte GetByte(const char* name);
	virtual DBByte GetByte(index_int index);
	virtual DBBlob GetBlob(const char*name);
	virtual DBBlob GetBlob(index_int index);
	virtual DBChar GetChar(const char*name);
	virtual DBChar GetChar(index_int index);
	virtual DBText GetText(const char*name);
	virtual DBText GetText(index_int index);
	virtual DBDatetime GetDatetime(const char* name);
	virtual DBDatetime GetDatetime(index_int index);
	virtual DBDouble GetDouble(const char* name);
	virtual DBDouble GetDouble(index_int index);
	virtual DBFloat GetFloat(const char*name);
	virtual DBFloat GetFloat(index_int index);
	virtual DBInt16 GetInt16(const char*name);
	virtual DBInt16 GetInt16(index_int index);
	virtual DBInt32 GetInt32(const char*name);
	virtual DBInt32 GetInt32(index_int index);
	virtual DBInt64 GetInt64(const char*name);
	virtual DBInt64 GetInt64(index_int index);
	virtual index_int GetFieldsCount(void);
	virtual DBText GetName(index_int index);
	virtual bool IsDBNull(const char*name);
	virtual bool IsDBNull(index_int index);
	virtual bool Read(void);
	virtual index_int GetResultCount(void);
};
#endif
