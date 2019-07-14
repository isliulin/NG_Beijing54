#ifdef USE_MYSQL
#include "DBMySqlConnection.h"
#include "DBMySqlCommand.h"
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <stdio.h>
DBMySqlConnection::DBMySqlConnection(const char * inuser,const char * inpwd)
{
	user = inuser;
	pwd = inpwd;
	p_con = NULL;
	p_cmd = NULL;
	db_type = 3;
}

DBMySqlConnection::~DBMySqlConnection(void)
{
	if(p_con!=NULL)
		Close();
}

void SpliteConnectString(const char * str,vector<string>& strlist,char c)
{
	strlist.clear();
	if(str == NULL)
		return;
	const char* pstart = str;
	const char *pend = str;
	while(*pend!='\0')
	{
		if(*pend == c)
		{
			string temp(pstart,pend);
			strlist.push_back(temp);
			pstart=pend+1;
		}
		++pend;
	}
	if(pend!=pstart)
	{
		string temp(pstart,pend);
		strlist.push_back(temp);
	}
}


bool DBMySqlConnection::Open( void )
{
	if(p_con==NULL)
	{
		p_con = new MYSQL;
		mysql_init(p_con);
	}
	try
	{
		if(db_status == DBConClose)
		{
			unsigned int port = 3306;
			string dbname;
			string host = "localhost";
			vector<string> conlist;
			SpliteConnectString(db_con_string.c_str(),conlist,':');
			if(conlist.size()==1)
				dbname = conlist[0];
			else if(conlist.size() == 2)
			{
				host = conlist[0];
				dbname = conlist[1];
			}
			else if(conlist.size() >= 3)
			{
				host = conlist[0];
				sscanf(conlist[1].c_str(),"%u",&port);
				dbname = conlist[2];
			}

			if(mysql_real_connect(p_con,host.c_str(),user.c_str(),pwd.c_str(),dbname.c_str(),port,NULL,0)!=NULL)
			{
					db_status = DBConOpen;
			}
		}
	}
	catch(...)
	{
		delete p_con;
		p_con = NULL;
		std::string e = "Open ";
		e+=db_con_string;
		e+="failed!";
		DBText err = e.c_str();
		throw err;
	}
	return (db_status == DBConOpen);	
}

bool DBMySqlConnection::Close( void )
{
	if(db_status == DBConOpen)
	{
		ClearCommand();
		mysql_close(p_con);
		delete p_con;
		p_con = NULL;
		db_status = DBConClose;
	}
	return (p_con == NULL);
}

IDBCommand* DBMySqlConnection::CreateCommand( void )
{
	if(p_cmd == NULL)
	{
		if(p_con!=NULL)
		{
			p_cmd = new DBMySqlCommand(p_con);
		}
	}
	return p_cmd;
}

void DBMySqlConnection::ClearCommand( void )
{
	if(p_cmd!=NULL)
	{
		delete p_cmd;
		p_cmd = NULL;
	}
}
#endif