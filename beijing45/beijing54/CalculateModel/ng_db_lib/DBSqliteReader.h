#ifdef USE_SQLITE

#ifndef _DBSQLITE_READER
#define _DBSQLITE_READER

#include "DBSqliteCommand.h"
#include "IDataReader.h"
#include <vector>
#include <string>
class DBSqliteReader :
	public IDataReader
{
protected:
	friend class DBSqliteCommand;
	DBSqliteReader(sqlite3*pcon);
	virtual ~DBSqliteReader(void);
protected:
	sqlite3 *p_con;
	sqlite3_stmt *p_stmt;
	std::vector<std::string> fields;
protected:
	bool GetFields();
	int GetColumnIndex(const char *name);
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
#endif/*USE_SQLITE*/