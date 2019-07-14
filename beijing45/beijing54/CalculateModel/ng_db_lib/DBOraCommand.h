/*
 * DBOraCommand.h
 *
 *  Created on: May 15, 2013
 *      Author: chenxing
 */
#ifdef USE_OCCI

#ifndef DBORACOMMAND_H_
#define DBORACOMMAND_H_
#include "DBOraConnection.h"
#include "IDBCommand.h"
class DBOraReader;
class DBOraCommand:public NGDBCom::IDBCommand
{
protected:
	virtual ~DBOraCommand();
	DBOraCommand(Connection*pcon);
	friend class DBOraConnection;
protected:
	Connection *p_con;
	Statement *p_stmt;
	DBOraReader *p_reader;
protected:
	bool CreateStmt();
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

#endif /* DBORACOMMAND_H_ */
#endif /*USE_OCCI*/
