#ifdef USE_OCILIB
#include "DBOCIConnection.h"
#include "DBOCICommand.h"
#include <omp.h>
#include "../../NGLog/NGLogPrint.h"

class OCIEvn
{
protected:
	static DBText OCIErrText;
	static void OCI_ErrHandler(OCI_Error *err)
	{
		OCIErrText = OCI_ErrorGetString(err);
		NG_WriteLog(NGLOG_Error,__FUNCTION__,OCIErrText.c_str());
	}
protected:
	int status;
	int initcount;
	omp_lock_t lock;
public: 
	OCIEvn()
	{
		status = 0;
		initcount = 0;
		omp_init_lock(&lock);
		//OCI_Initialize(OCI_ErrHandler, NULL, OCI_ENV_THREADED);
	}

	bool Init(){
		omp_set_lock(&lock);
		initcount++; 
		if(status==0)
			status = OCI_Initialize(OCI_ErrHandler, NULL, OCI_ENV_THREADED);
		omp_unset_lock(&lock);
		return status!=0;
	}
	void clearUp()
	{
		omp_set_lock(&lock);
		if(initcount>0)initcount --;
		if(initcount==0)
		{
			if(status)
			{
				OCI_Cleanup();
				status = 0;
			}
		}
		omp_unset_lock(&lock);
	}
	~OCIEvn(){
		omp_destroy_lock(&lock);
	}
	int GetStatus() const {return status;}
};
DBText OCIEvn::OCIErrText;
OCIEvn gEnv;

DBOCIConnection::DBOCIConnection( const char* inuser,const char* inpwd )
{
	//ctor
	user = inuser;
	pwd = inpwd;
	//

	p_con = NULL;
	p_cmd = NULL;

	db_type = 2;
	gEnv.Init();
}

DBOCIConnection::~DBOCIConnection(void)
{
	ClearCommand();
	if(p_con)
	{
		OCI_ConnectionFree(p_con);
	}
	gEnv.clearUp();
}

bool DBOCIConnection::Open( void )
{
	if((db_status == DBConClose)
		||(p_con==NULL))
	{
		if(db_con_string.GetValue())
		{
			try{
					p_con = OCI_CreateConnection(db_con_string,user,pwd,OCI_SESSION_DEFAULT);
				if(p_con)
					OCI_SetAutoCommit(p_con,true);
			}
			catch (string err)
			{
				string str_err=err;
			}
			if(p_con == NULL)
			{
				return false;
			}
		}
	}
	db_status = DBConOpen;
	return true;
}

bool DBOCIConnection::Close( void )
{
	if(db_status == DBConOpen)
	{
		ClearCommand();
		if(p_con)
		{
			OCI_ConnectionFree(p_con);
		}
		p_con = NULL;
		db_status = DBConClose;
	}
	return true;
}

IDBCommand* DBOCIConnection::CreateCommand( void )
{
	if(p_cmd ==NULL)
	{
		if(p_con!=NULL)
		{
			p_cmd = new DBOCICommand(p_con);
		}
	}
	return p_cmd;
}

void DBOCIConnection::ClearCommand( void )
{
	if(p_cmd!=NULL)
	{
		delete p_cmd;
		p_cmd = NULL;
	}
}

#endif
