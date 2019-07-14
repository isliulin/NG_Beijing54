#include "DBData.h"
#include <new>

namespace NGDBCom
{

	DBData::DBData(void)
	{
		bDBNull = true;
		eDBType = e_DB_NULL;
	}

	DBData::~DBData(void)
	{
	}

	bool DBData::IsDBNull(void) const
	{
		return bDBNull;
	}
	//
	void DBData::SetDBNull(bool DBNull)
	{
		bDBNull = DBNull;
	}

	NGDBCom::DBType DBData::GetDBType(void)
	{
		{return eDBType;}
	}

	DBBool::DBBool()
	{
		dbvalue = false;
		eDBType=e_DB_Bool;
	}
	DBBool& DBBool::operator =(bool value)
	{
		dbvalue = value;
		bDBNull = false;
		return *this;
	}
	void DBBool::SetValue(bool value)
	{
		dbvalue = value;
		bDBNull = false;
	}

	DBBool::~DBBool()
	{

	}

	DBBool::operator bool() const
	{
		 { return dbvalue;}
	}

	const void* DBBool::GetValue(void) const
	{
		 {return &dbvalue;}
	}

	size_t DBBool::Size(void) const
	{
		 {return sizeof(dbvalue);}
	}

	DBByte::DBByte()
	{
		dbvalue = (byte)0;
		eDBType=e_DB_Byte;
	}
	DBByte& DBByte::operator=(byte value)
	{
		dbvalue = value;
		bDBNull = false;
		return *this;
	}
	void DBByte::SetValue(byte value)
	{
		dbvalue = value;
		bDBNull = false;
	}

	DBByte::operator byte() const
	{
		 {return dbvalue;}
	}

	const void* DBByte::GetValue(void) const
	{
		 {return &dbvalue;}
	}

	size_t DBByte::Size(void) const
	{
		 {return sizeof(dbvalue);}
	}

	DBByte::~DBByte()
	{

	}

	DBBlob::DBBlob(void*value,size_t vsize,bool bCanDelete):DataReference()
	{
			dbvalue = (byte*)value;
			valsize = vsize;
			bDataCanDelete = bCanDelete;
			eDBType = e_DB_Blob;
	}
	DBBlob::DBBlob(const DBBlob& temp):DataReference(temp)
	{
			dbvalue = temp.dbvalue;
			valsize = temp.valsize;
			bDataCanDelete=temp.bDataCanDelete;
			eDBType = e_DB_Blob;
	}
	void DBBlob::ClearData()
		{
			if(bDataCanDelete
				&&IsOnly()
				&& dbvalue!=NULL)
				delete []dbvalue;
			ClearRef();
			dbvalue = NULL;
			valsize = 0;
		}
	DBBlob::~DBBlob(void)
	{
		ClearData();
	}
	void DBBlob::SetValue(void* value,size_t len,bool autodel)
	{
		ClearData();
		GenerateNewRef();
		dbvalue = (byte*)value;
		valsize = len;
		bDataCanDelete = autodel;
		bDBNull = false;
	}

	DBBlob& DBBlob::operator = (const DBBlob & temp)
	{
		if(this!=&temp)
		{
			AddRef(temp);
			dbvalue = temp.dbvalue;
			valsize = temp.valsize;
			bDataCanDelete=temp.bDataCanDelete;
		}
		return *this;
	}

	const void * DBBlob::GetValue(void) const
	{
		 {return dbvalue;}
	}

	DBChar::DBChar()
	{
		dbvalue = (char)0;
		eDBType = e_DB_Char;
	}
	DBChar& DBChar::operator =(char value)
	{
		dbvalue = value;
		bDBNull = false;
		return *this;
	}

	void DBChar::SetValue(char value)
	{
		dbvalue = value;
		bDBNull = false;
	}

	DBChar::~DBChar()
	{

	}

	DBChar::operator char() const
	{
		{ return dbvalue;}
	}

	const void * DBChar::GetValue(void) const
	{
		{return &dbvalue;}
	}

	size_t DBChar::Size(void) const
	{
		{return sizeof(dbvalue);}
	}

	DBText::DBText()
	{
		eDBType = e_DB_Text;
		size = 0;
		dbvalue = NULL;
	}

	DBText::DBText( const char* value )
	{
		eDBType = e_DB_Text;
		size = 0;
		dbvalue = NULL;
		SetValue(value);
	}

	DBText::DBText(const DBText & value)
	{
		eDBType = e_DB_Text;
		size = 0;
		dbvalue = NULL;
		SetValue(value.dbvalue);

	}

	DBText& DBText::operator=(const char * value)
	{
		SetValue(value);
		return *this;
	}
	DBText& DBText::operator=(DBText &value)
	{
		if(*this == value)
			return *this;
		SetValue(value.dbvalue);
			return *this;
	}
	void DBText::SetValue(const char * value)
	{
		if(value==dbvalue)
			return;
		Clear();
		if(value == NULL)
			return;
		size = strlen(value);
		dbvalue = new (std::nothrow)char[size+1];
		if(dbvalue)
			strcpy(dbvalue,value);
		bDBNull = false;
	}

	DBText::~DBText()
	{
		Clear();
	}

	void DBText::Clear()
	{
		if(dbvalue) delete [] dbvalue;
		dbvalue = NULL;
		size = 0;
		bDBNull = true;
	}

	DBText::operator const char*() const
	{
		{return dbvalue?dbvalue:"";}
	}

	const char * DBText::c_str() const
	{
		 {return dbvalue?dbvalue:"";}
	}

	const void* DBText::GetValue(void) const
	{
		 {return dbvalue;}
	}

	size_t DBText::Size(void) const
	{
		{return size;}
	}

	DBDatetime::DBDatetime()
	{
		dbvalue.tm_year = 0;
		dbvalue.tm_mon = 0;
		dbvalue.tm_mday = 0;
		dbvalue.tm_hour = 0;
		dbvalue.tm_min = 0;
		dbvalue.tm_sec = 0;
		eDBType = e_DB_Datetime;
	}
	DBDatetime& DBDatetime::operator=(tm value)
	{
		dbvalue = value;
		bDBNull = false;
		return *this;
	}
	void DBDatetime::SetValue(tm value)
	{
		dbvalue = value;
		bDBNull = false;
	}

	DBDatetime::~DBDatetime()
	{

	}

	DBDatetime::operator tm() const
	{
		 {return dbvalue;}
	}

	const void* DBDatetime::GetValue(void) const
	{
		 {return &dbvalue;}
	}

	size_t DBDatetime::Size(void) const
	{
		{return sizeof(dbvalue);}
	}

	DBDouble::DBDouble()
	{
		dbvalue = 0.0;
		eDBType = e_DB_Double;
	}

	DBDouble& DBDouble::operator=(double value)
	{
		dbvalue = value;
		bDBNull = false;
		return *this;
	}

	void DBDouble::SetValue(double value)
	{
		dbvalue = value;
		bDBNull = false;
	}

	DBDouble::~DBDouble()
	{

	}

	DBDouble::operator double() const
	{
		{return dbvalue;}
	}

	const void* DBDouble::GetValue(void) const
	{
		 {return &dbvalue;}
	}

	size_t DBDouble::Size(void) const
	{
		{return sizeof(dbvalue);}
	}

	DBFloat::DBFloat()
	{
		dbvalue = 0.0f;
		eDBType = e_DB_Float;
	}
	DBFloat& DBFloat::operator=(float value)
	{
		dbvalue = value;
		bDBNull = false;
		return *this;
	}
	void DBFloat::SetValue(float value)
	{
		dbvalue = value;
		bDBNull = false;
	}

	size_t DBFloat::Size(void) const
	{
		 {return sizeof(dbvalue);}
	}

	const void* DBFloat::GetValue(void) const
	{
		 {return &dbvalue;}
	}

	DBFloat::operator float() const
	{
		 {return dbvalue;}
	}

	DBFloat::~DBFloat()
	{

	}

	DBInt16::DBInt16()
	{
		dbvalue = 0;
		eDBType = e_DB_Int16;
	}

	DBInt16& DBInt16::operator=(int16 value)
	{
		dbvalue = value;
		bDBNull = false;
		return *this;
	}
	void DBInt16::SetValue(int16 value)
	{
		dbvalue = value;
		bDBNull = false;
	}

	DBInt16::operator int16() const
	{
		 {return dbvalue;}
	}

	const void* DBInt16::GetValue(void) const
	{
		{return &dbvalue;}
	}

	size_t DBInt16::Size(void) const
	{
		 {return sizeof(dbvalue);}
	}

	DBInt16::~DBInt16()
	{

	}

	DBInt32::DBInt32()
	{
		dbvalue = 0;
		eDBType = e_DB_Int32;
	}

	DBInt32& DBInt32::operator=(int32 value)
	{
		dbvalue = value;
		bDBNull = false;
		return *this;
	}
	void DBInt32::SetValue(int32 value)
	{
		dbvalue = value;
		bDBNull = false;
	}

	DBInt32::~DBInt32()
	{

	}

	DBInt32::operator int32() const
	{
		{return dbvalue;}
	}

	const void* DBInt32::GetValue(void) const
	{
		 {return &dbvalue;}
	}

	size_t DBInt32::Size(void) const
	{
		 {return sizeof(dbvalue);}
	}

	DBInt64::DBInt64()
	{
		dbvalue = 0;
		eDBType = e_DB_Int64;
	}

	DBInt64& DBInt64::operator=(int64 value)
	{
		dbvalue = value;
		bDBNull = false;
		return *this;
	}
	void DBInt64::SetValue(int64 value)
	{
		dbvalue = value;
		bDBNull = false;
	}

	DBInt64::~DBInt64()
	{

	}

	DBInt64::operator int64() const
	{
		{return dbvalue;}
	}

	const void* DBInt64::GetValue(void) const
	{
		 {return &dbvalue;}
	}

	size_t DBInt64::Size(void) const
	{
		 {return sizeof(dbvalue);}
	}

}