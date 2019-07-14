#ifdef USE_SQLSERVER
#include "DBSQLReader.h"
#include <time.h>
DBSQLReader::DBSQLReader(_ConnectionPtr&pcon):
p_con(pcon)
{
	//p_stmt.CreateInstance(__uuidof(Recordset));
}

DBSQLReader::~DBSQLReader(void)
{
}

void DBSQLReader::Close()
{
	if(p_stmt)
	{
		p_stmt.Release();
	}
}



bool DBSQLReader::Query( const char* sql )
{
	if(sql)
	{
		Close();
		p_stmt.CreateInstance(__uuidof(Recordset));
		_bstr_t cmdText(sql);
		try
		{
			p_stmt->Open((_variant_t)cmdText,p_con.GetInterfacePtr(),adOpenStatic, adLockOptimistic, adCmdText);
			//p_stmt->MoveFirst();
			lastRow = 0;
			bResultEnd = false;
		}
		catch(_com_error e)
		{
			DBText err = e.ErrorMessage();
			throw err;
		}
		return true;
	}
	return false;
}

index_int DBSQLReader::GetResultCount( void )
{
	if(p_stmt.GetInterfacePtr()!=NULL)
	{
		return (int)(p_stmt->RecordCount);
	}
	return 0;
}

bool DBSQLReader::Read( void )
{
	if(p_stmt.GetInterfacePtr()!=NULL)
	{
		if (!p_stmt->adoEOF)
		{
			if(lastRow == 0)
				p_stmt->MoveFirst();
			else
				p_stmt->MoveNext();
			lastRow ++;
			return (!p_stmt->adoEOF);
		}	
	}
	return false;
}

NGDBCom::DBBool DBSQLReader::GetBoolean( const char* name )
{
	DBBool value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((_bstr_t)name));
	if(vGet.vt!=VT_NULL)
		value = (bool)vGet;
	return value;
}

NGDBCom::DBBool DBSQLReader::GetBoolean( index_int index )
{
	DBBool value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((long)index));
	if(vGet.vt!=VT_NULL)
		value = (bool)vGet;
	return value;
}

NGDBCom::DBByte DBSQLReader::GetByte( const char* name )
{
	DBByte value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((_bstr_t)name));
	if(vGet.vt!=VT_NULL&&vGet.vt!=VT_EMPTY)
		value = (byte)vGet;
	return value;
}

NGDBCom::DBByte DBSQLReader::GetByte( index_int index )
{
	DBByte value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((long)index));
	if(vGet.vt!=VT_NULL&&vGet.vt!=VT_EMPTY)
		value = (byte)vGet;
	return value;
}

NGDBCom::DBBlob DBSQLReader::GetBlob( const char*name )
{
	DBBlob value;
	FieldPtr field =  p_stmt->GetFields()->GetItem(_variant_t((_bstr_t)name));
	if(field.GetInterfacePtr()!=NULL)
	{
		long size = field->ActualSize;
		_variant_t vGet =field->GetChunk(size);
		if(vGet.vt!=VT_EMPTY&&vGet.vt!=VT_NULL)
		{
			BYTE * pBuf = (BYTE*)GlobalAlloc(GMEM_FIXED,size);
			SafeArrayAccessData(vGet.parray,(void**)&pBuf);
			value.SetValue(pBuf,size);
			SafeArrayUnaccessData(vGet.parray);
			GlobalFree((HGLOBAL)(void*)pBuf);
		}

	}
	return value;

}

NGDBCom::DBBlob DBSQLReader::GetBlob( index_int index )
{
	DBBlob value;
	FieldPtr field =  p_stmt->GetFields()->GetItem(_variant_t((long)index));
	if(field.GetInterfacePtr()!=NULL)
	{
		long size = field->ActualSize;
		_variant_t vGet =field->GetChunk(size);
		if(vGet.vt!=VT_EMPTY&&vGet.vt!=VT_NULL)
		{
			BYTE * pBuf = (BYTE*)GlobalAlloc(GMEM_FIXED,size);
			SafeArrayAccessData(vGet.parray,(void**)&pBuf);
			value.SetValue(pBuf,size);
			SafeArrayUnaccessData(vGet.parray);
			GlobalFree((HGLOBAL)(void*)pBuf);
		}
	}
	return value;
}

NGDBCom::DBChar DBSQLReader::GetChar( const char*name )
{
	DBChar value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((_bstr_t)name));
	if(vGet.vt!=VT_NULL&&vGet.vt!=VT_EMPTY)
		value = (byte)vGet;
	return value;
}

NGDBCom::DBChar DBSQLReader::GetChar( index_int index )
{
	DBChar value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((long)index));
	if(vGet.vt!=VT_NULL&&vGet.vt!=VT_EMPTY)
		value = (byte)vGet;
	return value;
}

NGDBCom::DBText DBSQLReader::GetText( const char*name )
{
	DBText value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((_bstr_t)name));
	if(vGet.vt!=VT_NULL&&vGet.vt!=VT_EMPTY)
	{
		_bstr_t str(vGet.bstrVal);
		char * pStr = (char*)str;
		value = pStr;
	}
	return value;
}

NGDBCom::DBText DBSQLReader::GetText( index_int index )
{
	DBText value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((long)index));
	if(vGet.vt!=VT_NULL&&vGet.vt!=VT_EMPTY)
	{
		_bstr_t str(vGet.bstrVal);
		char * pStr = (char*)str;
		value = pStr;
	}
	return value;
}

NGDBCom::DBDatetime DBSQLReader::GetDatetime( const char* name )
{
	 DBDatetime value;
	 _variant_t vGet = p_stmt->GetCollect(_variant_t((_bstr_t)name));
	 if(vGet.vt!=VT_NULL&&vGet.vt!=VT_EMPTY)
	 {
		 time_t time = (long)vGet;
		 tm *temp = gmtime(&time);
		value = *temp;
	 }
	 return value;
	
}

NGDBCom::DBDatetime DBSQLReader::GetDatetime( index_int index )
{
	DBDatetime value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((long)index));
	if(vGet.vt!=VT_NULL&&vGet.vt!=VT_EMPTY)
	{
		time_t time = (long)vGet;
		tm *temp = gmtime(&time);
		value = *temp;
	}
	return value;
}

NGDBCom::DBDouble DBSQLReader::GetDouble( const char* name )
{
	DBDouble value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((_bstr_t)name));
	if(vGet.vt!=VT_NULL)
		value = (double)vGet;
	return value;
}

NGDBCom::DBDouble DBSQLReader::GetDouble( index_int index )
{
	DBDouble value;
	try{
		_variant_t vGet = p_stmt->GetCollect(_variant_t((long)index));
		if(vGet.vt!=VT_NULL)
			value = (double)vGet;
		return value;
	}
	catch(_com_error err)
	{
		string ste=err.ErrorMessage();
	}
	return value;
}

NGDBCom::DBFloat DBSQLReader::GetFloat( const char*name )
{
	DBFloat value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((_bstr_t)name));
	if(vGet.vt!=VT_NULL)
		value = (float)vGet;
	return value;
}

NGDBCom::DBFloat DBSQLReader::GetFloat( index_int index )
{
	DBFloat value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((long)index));
	if(vGet.vt!=VT_NULL)
		value = (float)vGet;
	return value;
}

NGDBCom::DBInt16 DBSQLReader::GetInt16( const char*name )
{
	DBInt16 value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((_bstr_t)name));
	if(vGet.vt!=VT_NULL)
		value = (short)vGet;
	return value;
}

NGDBCom::DBInt16 DBSQLReader::GetInt16( index_int index )
{
	DBInt16 value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((long)index));
	if(vGet.vt!=VT_NULL)
		value = (short)vGet;
	return value;
}

NGDBCom::DBInt32 DBSQLReader::GetInt32( const char*name )
{
	DBInt32 value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((_bstr_t)name));
	if(vGet.vt!=VT_NULL)
		value = (int)vGet;
	return value;
}

NGDBCom::DBInt32 DBSQLReader::GetInt32( index_int index )
{
	DBInt32 value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((long)index));
	if(vGet.vt!=VT_NULL)
		value = (int)vGet;
	return value;
}

NGDBCom::DBInt64 DBSQLReader::GetInt64( const char*name )
{
	DBInt64 value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((_bstr_t)name));
	if(vGet.vt!=VT_NULL)
		value = (int64)vGet;
	return value;
}

NGDBCom::DBInt64 DBSQLReader::GetInt64( index_int index )
{
	DBInt64 value;
	_variant_t vGet = p_stmt->GetCollect(_variant_t((long)index));
	if(vGet.vt!=VT_NULL)
		value = (int64)vGet;
	return value;
}

index_int DBSQLReader::GetFieldsCount( void )
{
	if(p_stmt.GetInterfacePtr()!=NULL)
		return p_stmt->GetFields()->GetCount();
	return 0;
}

DBText DBSQLReader::GetName( index_int index )
{
	DBText name;
	if(p_stmt.GetInterfacePtr()!=NULL)
	{
		char* pBuf = (char*) p_stmt->GetFields()->GetItem(_variant_t((long)index))->GetName();
		name = pBuf;
	}
	return name;
}

bool DBSQLReader::IsDBNull( const char*name )
{
	_variant_t vGet = p_stmt->GetCollect(_variant_t((_bstr_t)name));
	return (vGet.vt==VT_NULL);

}

bool DBSQLReader::IsDBNull( index_int index )
{
	_variant_t vGet = p_stmt->GetCollect(_variant_t((long)index));
	return (vGet.vt==VT_NULL);
}

#endif



