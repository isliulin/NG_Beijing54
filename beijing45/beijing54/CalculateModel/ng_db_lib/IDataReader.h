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
		//获取bool字段值
		virtual DBBool GetBoolean(const char* name)=0;
		virtual DBBool GetBoolean(index_int index)=0;
		//获取Byte型字段值
		virtual DBByte GetByte(const char* name)=0;
		virtual DBByte GetByte(index_int index)=0;
		//获取Blob字段值
		virtual DBBlob GetBlob(const char*name)=0;
		virtual DBBlob GetBlob(index_int index)=0;
		//获取char字段值
		virtual DBChar GetChar(const char*name)=0;
		virtual DBChar GetChar(index_int index)=0;
		//获取Text字段值
		virtual DBText GetText(const char*name)=0;
		virtual DBText GetText(index_int index)=0;
		//获取Datetime字段
		virtual DBDatetime GetDatetime(const char* name)=0;
		virtual DBDatetime GetDatetime(index_int index)=0;
		//获取Double字段
		virtual DBDouble GetDouble(const char* name)=0;
		virtual DBDouble GetDouble(index_int index)=0;

		//获取Float字段
		virtual DBFloat GetFloat(const char*name)=0;
		virtual DBFloat GetFloat(index_int index)=0;
		//获取int16字段
		virtual DBInt16 GetInt16(const char*name)=0;
		virtual DBInt16 GetInt16(index_int index)=0;
		//获取int32字段
		virtual DBInt32 GetInt32(const char*name)=0;
		virtual DBInt32 GetInt32(index_int index)=0;
		//获取int64字段
		virtual DBInt64 GetInt64(const char*name)=0;
		virtual DBInt64 GetInt64(index_int index)=0;
		//获取字段数量
		virtual index_int GetFieldsCount(void)=0;
		//获取字段名称
		virtual DBText GetName(index_int index)=0;
		//判断字段当前值是否为DBNUll值
		virtual bool IsDBNull(const char*name)=0;
		virtual bool IsDBNull(index_int index) = 0;
		//判断是否有记录可读，自动逐行记录读取
		virtual bool Read(void)=0;
		virtual index_int GetResultCount(void)=0;
	};
}
#endif