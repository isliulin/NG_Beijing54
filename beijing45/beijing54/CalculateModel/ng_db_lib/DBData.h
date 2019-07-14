#ifndef _DBDATA_H_
#define _DBDATA_H_
#include "NGDBDefined.h"
#include "DataReference.h"
namespace NGDBCom
{
	enum DBType
	{
		e_DB_NULL,
		e_DB_Bool,
		e_DB_Byte,
		e_DB_Char,
		e_DB_Text,
		e_DB_Double,
		e_DB_Float,
		e_DB_Int16,
		e_DB_Int32,
		e_DB_Int64,
		e_DB_Datetime,
		e_DB_Blob
	};

	class NGDBDLL_API DBData
	{
	public:
		DBData(void);
		virtual ~DBData(void);
	protected:
		bool bDBNull;
		DBType eDBType;

	public:
		// 
		void SetDBNull (bool DBNull);
		bool IsDBNull (void) const;
		//
		virtual const void* GetValue(void) const = 0;
		//
		virtual size_t Size(void) const = 0;
		//
		DBType GetDBType(void);
	};

	class NGDBDLL_API DBBool:public DBData
	{
	protected:
		bool dbvalue;
	public:
		DBBool();
		~DBBool();
		operator bool()const;
		DBBool& operator =(bool value);
		void SetValue(bool value);
		const void* GetValue(void)const;
		size_t Size(void) const;
	};

	class NGDBDLL_API DBByte:public DBData
	{
	protected:
		byte dbvalue;
	public :
		DBByte();
		~DBByte();
		operator byte()const;
		DBByte& operator=(byte value);
		void SetValue(byte value);
		const void* GetValue(void)const;
		size_t Size(void)const;
	};

	//
	class NGDBDLL_API DBBlob:public DBData,DataReference
	{
	public:
		DBBlob(void*value=NULL,size_t vsize =0,bool bCanDelete = false);
		~DBBlob(void);
		//
		DBBlob(const DBBlob& temp);
		protected:
		byte * dbvalue;
		size_t valsize;
		bool bDataCanDelete;
		void ClearData();
	public:
		void SetValue(void* value,size_t len,bool autodel=false);
		const void * GetValue(void)const;
		size_t Size(void)const {return valsize;}
		DBBlob& operator = (const DBBlob & temp);
	};

	class NGDBDLL_API DBChar:public DBData
	{
	protected:
		char dbvalue;
	public :
		DBChar();
		~DBChar();
		operator char()const; 
		DBChar& operator =(char value);
		void SetValue(char value);
		const void * GetValue(void)const; 
		size_t Size(void)const;
	};

	class NGDBDLL_API DBText:public DBData
	{
	protected:
		char* dbvalue;
		size_t size;
	public:
		void Clear();
	public:
		DBText();
		DBText(const char* value);
		DBText(const DBText & value);
		~DBText();
		operator const char*()const; 
		
		DBText& operator=(const char* value);
		DBText& operator=(DBText &value);

		const char * c_str() const;
		void SetValue(const char* value);
		const void* GetValue(void) const;
		size_t Size(void) const;
	};

	class NGDBDLL_API DBDatetime:public DBData
	{
	protected:
		tm dbvalue;
	public:
		DBDatetime();
		~DBDatetime();
		operator tm() const;
		DBDatetime& operator=(tm value);
		void SetValue(tm value);
		const void* GetValue(void) const;
		size_t Size(void)const; 
	};

	class NGDBDLL_API DBDouble:public DBData
	{
	protected:
		double dbvalue;
	public :
		DBDouble();
		~DBDouble();
		operator double()const;
		DBDouble& operator=(double value);
		void SetValue(double value);
		const void* GetValue(void) const;
		size_t Size(void) const; 
	};

	class NGDBDLL_API DBFloat:public DBData
	{
	protected:
		float dbvalue;
	public :
		DBFloat();
		~DBFloat();
		operator float() const;
		DBFloat& operator=(float value);
		void SetValue(float value);
		const void* GetValue(void) const;
		size_t Size(void) const;
	};

	class NGDBDLL_API DBInt16:public DBData
	{
	protected:
		int16 dbvalue;
	public:
		DBInt16();
		~DBInt16();
		operator int16()const;
		DBInt16& operator=(int16 value);
		void SetValue(int16 value);
		const void* GetValue(void)const;
		size_t Size(void)const;
	};

	class NGDBDLL_API DBInt32:public DBData
	{
	protected:
		int32 dbvalue;
	public:
		DBInt32();
		~DBInt32();
		operator int32()const; 
		DBInt32& operator=(int32 value);
		void SetValue(int32 value);
		const void* GetValue(void)const;
		size_t Size(void)const;
	};

	class NGDBDLL_API DBInt64:public DBData
	{
	protected:
		int64 dbvalue;
	public:
		DBInt64();
		~DBInt64();
		operator int64()const;
		DBInt64& operator=(int64 value);
		void SetValue(int64 value);
		const void* GetValue(void)const;
		size_t Size(void) const;
	};
}
#endif
