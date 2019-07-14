#ifdef USE_OCCI

#ifndef DBORACONNECTION_H
#define DBORACONNECTION_H

#include "IDBConnection.h"
using namespace NGDBCom;
#include <occi.h>
#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment(lib,"oraocci11d.lib")
#else
#pragma comment(lib,"oraocci11.lib")
#endif //_DEBUG
#endif //_MSC_VER
using namespace oracle::occi;
class DBOraCommand;
class DBOraConnection : public IDBConnection
{
    public:
        DBOraConnection(const char* inuser,const char* inpwd);
        virtual ~DBOraConnection();
    protected:
		 DBText user;
		 DBText pwd;
         Environment *p_env;
         Connection *p_con;
         DBOraCommand *p_cmd;
    private:
    public:
        virtual bool Open(void);
		virtual bool Close(void);
		virtual IDBCommand* CreateCommand(void);
    protected:
		virtual void ClearCommand(void);
};

#endif // DBORACONNECTION_H
#endif //USE_OCCI