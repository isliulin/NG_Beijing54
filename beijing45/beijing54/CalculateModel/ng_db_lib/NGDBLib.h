#ifndef _NG_DB_LIB_H_
#define _NG_DB_LIB_H_

#include "IDBConnection.h"
#include "DBManager.h"

#define USEDBSQLITE 1
#define USEDBORACLE 2
#define USEDBMYSQL 3
#define USEDBSQLSERVER 4
#define USEDBORACLEOCILIB 5

#ifdef __cplusplus
extern "C" {
#endif
NGDBDLL_API IDBConnection *  CreateDBConnection(int DBType,const char* user,const char*pwd,const char *con_str);
NGDBDLL_API void  CloseDBConnection(IDBConnection * pCon);
#ifdef __cplusplus
}
#endif
#endif
