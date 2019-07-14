#ifndef _I_DB_CONNECTION_H_
#define _I_DB_CONNECTION_H_
#include "NGDBDefined.h"
#include "DBData.h"
namespace NGDBCom
{

	interface IDBCommand;

	enum DBConnectionState
	{
		DBConClose,
		DBConOpen
	};
	interface NGDBDLL_API IDBConnection
	{
	protected:
		DBText db_con_string;
		DBConnectionState db_status;
		int db_type;
	public:
		IDBConnection(void);
		virtual ~IDBConnection(void);
	public:
		// 打开数据库连接
		virtual bool Open(void) = 0;
		// 关闭数据库连接
		virtual bool Close(void) = 0;
		//打开数据库
		bool Open(const char* connectionString);
		//设置连接字符
		void SetConnectionString(const char*connectionString);
		//获取连接状态
		DBConnectionState GetStatus(void);
		//创建一个Command实例
		virtual IDBCommand* CreateCommand(void) = 0;
		//
		int GetDBType();

	protected:
		//清除以创建的Command对象
		virtual void ClearCommand(void) = 0;
	};
}
#endif