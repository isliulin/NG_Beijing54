/*
 * DBOraReader.h
 *
 *  Created on: May 15, 2013
 *      Author: chenxing
 */
#ifdef USE_OCCI

#ifndef DBORAREADER_H_
#define DBORAREADER_H_

#include "IDataReader.h"
#include "DBOraCommand.h"

class DBOraReader: public NGDBCom::IDataReader {
protected:
	DBOraReader(Statement *pstmt);
	virtual ~DBOraReader();
	friend class DBOraCommand;
protected:
	Statement *p_stmt;
	ResultSet *p_rs;
	std::vector<MetaData>cols;
	void Query(const char * sql);
	bool GetColumnList();
	int GetColumnIndex(const char *name);
	DBText sqlData;
	unsigned lastRow;
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



#endif /* DBORAREADER_H_ */
#endif/*USE_OCCI*/