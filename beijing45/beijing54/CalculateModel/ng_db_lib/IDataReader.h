#ifndef _I_DB_READER_H_
#define  _I_DB_READER_H_

#include "NGDBDefined.h"
#include "DBData.h"
namespace NGDBCom
{
	interface NGDBDLL_API IDataReader
	{
	public:
		IDataReader(void);
		virtual ~IDataReader(void);
	public:
		virtual void Close()=0;
		//��ȡbool�ֶ�ֵ
		virtual DBBool GetBoolean(const char* name)=0;
		virtual DBBool GetBoolean(index_int index)=0;
		//��ȡByte���ֶ�ֵ
		virtual DBByte GetByte(const char* name)=0;
		virtual DBByte GetByte(index_int index)=0;
		//��ȡBlob�ֶ�ֵ
		virtual DBBlob GetBlob(const char*name)=0;
		virtual DBBlob GetBlob(index_int index)=0;
		//��ȡchar�ֶ�ֵ
		virtual DBChar GetChar(const char*name)=0;
		virtual DBChar GetChar(index_int index)=0;
		//��ȡText�ֶ�ֵ
		virtual DBText GetText(const char*name)=0;
		virtual DBText GetText(index_int index)=0;
		//��ȡDatetime�ֶ�
		virtual DBDatetime GetDatetime(const char* name)=0;
		virtual DBDatetime GetDatetime(index_int index)=0;
		//��ȡDouble�ֶ�
		virtual DBDouble GetDouble(const char* name)=0;
		virtual DBDouble GetDouble(index_int index)=0;

		//��ȡFloat�ֶ�
		virtual DBFloat GetFloat(const char*name)=0;
		virtual DBFloat GetFloat(index_int index)=0;
		//��ȡint16�ֶ�
		virtual DBInt16 GetInt16(const char*name)=0;
		virtual DBInt16 GetInt16(index_int index)=0;
		//��ȡint32�ֶ�
		virtual DBInt32 GetInt32(const char*name)=0;
		virtual DBInt32 GetInt32(index_int index)=0;
		//��ȡint64�ֶ�
		virtual DBInt64 GetInt64(const char*name)=0;
		virtual DBInt64 GetInt64(index_int index)=0;
		//��ȡ�ֶ�����
		virtual index_int GetFieldsCount(void)=0;
		//��ȡ�ֶ�����
		virtual DBText GetName(index_int index)=0;
		//�ж��ֶε�ǰֵ�Ƿ�ΪDBNUllֵ
		virtual bool IsDBNull(const char*name)=0;
		virtual bool IsDBNull(index_int index) = 0;
		//�ж��Ƿ��м�¼�ɶ����Զ����м�¼��ȡ
		virtual bool Read(void)=0;
		virtual index_int GetResultCount(void)=0;
	};
}
#endif