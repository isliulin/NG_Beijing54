#ifdef USE_OCCI

#include "DBOraConnection.h"
#include "DBOraCommand.h"
DBOraConnection::DBOraConnection(const char* inuser,const char* inpwd)
{
    //ctor
	user = inuser;
	pwd = inpwd;
	//

    p_env = NULL;
    p_con = NULL;
    p_cmd = NULL;
	db_type = 2;
}

DBOraConnection::~DBOraConnection()
{
    //dtor
	ClearCommand();
    if(p_env!=NULL)
    {
    	if(p_con!=NULL)
    	{
    		p_env->terminateConnection(p_con);
    	}
        Environment::terminateEnvironment(p_env);
    }
}

bool DBOraConnection::Open()
{
	try
	{
		if(db_status == DBConClose)
		{
			if(db_con_string.GetValue())
			{
				if(p_env == NULL)
					//p_env = Environment::createEnvironment((Environment::Mode)(Environment::OBJECT|Environment::THREADED_UNMUTEXED));
					//p_env = Environment::createEnvironment("ZHS16GBK","UTF8");
					p_env = Environment::createEnvironment("ZHS16GBK","UTF8",Environment::THREADED_MUTEXED); 
					if(p_env == NULL)
					return false;

				p_con = p_env->createConnection(user.c_str(),pwd.c_str(),db_con_string.c_str());
				
				
				if(p_con == NULL)
				{
					Environment::terminateEnvironment(p_env);
					p_env = NULL;
					return false;
				}
			}
		}
		db_status = DBConOpen;
		return true;
	}
	catch(oracle::occi::SQLException &e)
	{
		DBText err = e.getMessage().c_str();
		throw err;
	}
}

 bool DBOraConnection::Close(void)
 {
	 try
	 {
		 if(db_status == DBConOpen)
		{
			 ClearCommand();
			 if(p_env !=NULL)
			 {
				 if(p_con!=NULL)
				 {
					 p_env->terminateConnection(p_con);
				 }
				 Environment::terminateEnvironment(p_env);
			 }
			 p_env = NULL;
			 p_con = NULL;
			 db_status = DBConClose;
			}
		 return true;
	}
	 catch(oracle::occi::SQLException & ex)
	 {
		 DBText err = ex.getMessage().c_str();
		 throw err;
	 }
	 
 }

IDBCommand* DBOraConnection::CreateCommand(void)
 {
	 if(p_cmd ==NULL)
	 {
		 if(p_con!=NULL)
		 {
			 p_cmd = new DBOraCommand(p_con);
		 }
	 }
	 return p_cmd;
 }
  void DBOraConnection::ClearCommand(void)
 {
	  if(p_cmd!=NULL)
	  {
		  delete p_cmd;
		  p_cmd = NULL;
	  }
 }

#endif/*USE_OCCI*/