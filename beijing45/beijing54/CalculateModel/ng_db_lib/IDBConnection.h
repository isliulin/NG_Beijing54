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
		// �����ݿ�����
		virtual bool Open(void) = 0;
		// �ر����ݿ�����
		virtual bool Close(void) = 0;
		//�����ݿ�
		bool Open(const char* connectionString);
		//���������ַ�
		void SetConnectionString(const char*connectionString);
		//��ȡ����״̬
		DBConnectionState GetStatus(void);
		//����һ��Commandʵ��
		virtual IDBCommand* CreateCommand(void) = 0;
		//
		int GetDBType();

	protected:
		//����Դ�����Command����
		virtual void ClearCommand(void) = 0;
	};
}
#endif