#ifdef USE_OCILIB
#include "DBOCIReader.h"
#include <new>

DBOCIReader::DBOCIReader( OCI_Statement *pstm )
{

	p_stmt = pstm;
	p_rs = NULL;
}

DBOCIReader::~DBOCIReader(void)
{
	Close();
}

void DBOCIReader::Close()
{
	if(p_stmt!=NULL && p_rs!=NULL)
	{
		p_rs = NULL;
	}
	p_rs = NULL;
}

void DBOCIReader::Query( const char * sql )
{
	if(p_stmt&&sql)
	{
		p_rs = NULL;

		if(OCI_ExecuteStmt(p_stmt,sql))
		{
			p_rs = OCI_GetResultset(p_stmt);
		}
	}
		
}

bool DBOCIReader::Read( void )
{
	return OCI_FetchNext(p_rs);
}

index_int DBOCIReader::GetResultCount( void )
{
	return p_rs? OCI_GetRowCount(p_rs):0;
}

index_int DBOCIReader::GetFieldsCount( void )
{
	return p_rs?OCI_GetColumnCount(p_rs):0;
}

bool DBOCIReader::IsDBNull( index_int index )
{
	if(p_rs)
	{
		const otext* p_text = OCI_GetString(p_rs,index+1);
		return p_text == NULL;

		/*OCI_Column * p_col = OCI_GetColumn(p_rs,index+1);
		if(p_col)
			return OCI_ColumnGetNullable(p_col)!=FALSE;*/
	}
	return true;
	
}

bool DBOCIReader::IsDBNull( const char*name )
{
	if(p_rs)
	{
		const otext* p_text = OCI_GetString2(p_rs,name);
		return p_text == NULL;
		/*index_int index  = OCI_GetColumnIndex(p_rs,name);
		return IsDBNull(index);*/
	}
	return true;
}

NGDBCom::DBText DBOCIReader::GetName( index_int index )
{
	DBText name;
	if(p_rs)
	{
		OCI_Column *p_col = OCI_GetColumn(p_rs,index+1);
		if(p_col)
			name = OCI_ColumnGetName(p_col);
	}
	return name;
}

NGDBCom::DBBool DBOCIReader::GetBoolean( const char* name )
{
	DBBool v;
	if(p_rs)
	{
		if(!IsDBNull(name))
		{
			int iv = OCI_GetInt2(p_rs,name);
			v = (iv!=0);
		}
	}
	return v;
}

NGDBCom::DBBool DBOCIReader::GetBoolean( index_int index )
{
	DBBool v;
	if(p_rs)
	{
		if(!IsDBNull(index))
		{
			int iv = OCI_GetInt(p_rs,index+1);
			v = (iv!=0);
		}
	}
	return v;
}

NGDBCom::DBByte DBOCIReader::GetByte( const char* name )
{
	DBByte value;
	if(p_rs)
	{
		if(!IsDBNull(name))
		{
			const otext * sv = OCI_GetString2(p_rs,name);
			if(sv)
				value = (byte)sv[0];
		}
	}
	return value;
}

NGDBCom::DBByte DBOCIReader::GetByte( index_int index )
{
	DBByte value;
	if(p_rs)
	{
		if(!IsDBNull(index))
		{
			const otext * sv = OCI_GetString(p_rs,index+1);
			if(sv)
				value = (byte)sv[0];
		}
	}
	return value;
}

NGDBCom::DBBlob DBOCIReader::GetBlob( const char*name )
{
	DBBlob v;
	if(p_rs)
	{
		if(!IsDBNull(name))
		{
			OCI_Lob *p_lob = OCI_GetLob2(p_rs,name);
			if(p_lob)
			{
				big_uint bs = OCI_LobGetLength(p_lob);
				byte * bytes = new(std::nothrow) byte[bs];
				if(bytes)
				{
					OCI_LobRead(p_lob,bytes,bs);
					v.SetValue(bytes,bs,true);
				}
			}
		}
	}
	return v;
}

NGDBCom::DBBlob DBOCIReader::GetBlob( index_int index )
{
	DBBlob v;
	if(p_rs)
	{
		if(!IsDBNull(index))
		{
			OCI_Lob *p_lob = OCI_GetLob(p_rs,index+1);
			if(p_lob)
			{
				big_uint bs = OCI_LobGetLength(p_lob);
				byte * bytes = new(std::nothrow) byte[bs];
				if(bytes)
				{
					OCI_LobRead(p_lob,bytes,bs);
					v.SetValue(bytes,bs,true);
				}
			}
		}
	}
	return v;
}

NGDBCom::DBChar DBOCIReader::GetChar( const char*name )
{
	DBChar value;
	if(p_rs)
	{
		if(!IsDBNull(name))
		{
			const otext * sv = OCI_GetString2(p_rs,name);
			if(sv)
				value = sv[0];
		}
	}
	return value;
}

NGDBCom::DBChar DBOCIReader::GetChar( index_int index )
{
	DBChar value;
	if(p_rs)
	{
		if(!IsDBNull(index))
		{
			const otext * sv = OCI_GetString(p_rs,index+1);
			if(sv)
				value = sv[0];
		}
	}
	return value;
}

NGDBCom::DBText DBOCIReader::GetText( const char*name )
{
	DBText value;
	if(p_rs)
	{
		if(!IsDBNull(name))
		{
			const otext * sv = OCI_GetString2(p_rs,name);
			if(sv)
				value = sv;
		}
	}
	return value;
}

NGDBCom::DBText DBOCIReader::GetText( index_int index )
{
	DBText value;
	if(p_rs)
	{
		if(!IsDBNull(index))
		{
			const otext * sv = OCI_GetString(p_rs,index+1);
			if(sv)
				value = sv;
		}
	}
	return value;
}

NGDBCom::DBDatetime DBOCIReader::GetDatetime( const char* name )
{
	DBDatetime value;
	if(p_rs!=NULL)
	{
		if(!IsDBNull(name))
		{
			OCI_Timestamp* temptime = OCI_GetTimestamp2(p_rs,name);
			if(temptime)
			{
				int year;
				int mon,day,hour,minu,sec,fs;
				OCI_TimestampGetDate(temptime,&year,&mon,&day);
				OCI_TimestampGetTime(temptime,&hour,&minu,&sec,&fs);
				tm temp;
				temp.tm_year = year;
				temp.tm_mon = mon;
				temp.tm_mday = day;
				temp.tm_hour = hour;
				temp.tm_min = minu;
				temp.tm_sec = sec;
				value = temp;
			}

		}
	}
	return value;
}

NGDBCom::DBDatetime DBOCIReader::GetDatetime( index_int index )
{
	DBDatetime value;
	if(p_rs!=NULL)
	{
		if(!IsDBNull(index))
		{
			OCI_Timestamp* temptime = OCI_GetTimestamp(p_rs,index+1);
			if(temptime)
			{
				int year;
				int mon,day,hour,minu,sec,fs;
				OCI_TimestampGetDate(temptime,&year,&mon,&day);
				OCI_TimestampGetTime(temptime,&hour,&minu,&sec,&fs);
				tm temp;
				temp.tm_year = year;
				temp.tm_mon = mon;
				temp.tm_mday = day;
				temp.tm_hour = hour;
				temp.tm_min = minu;
				temp.tm_sec = sec;
				value = temp;
			}
		}
	}
	return value;
}

NGDBCom::DBDouble DBOCIReader::GetDouble( const char* name )
{
	DBDouble value;
	if(p_rs)
	{
		if(!IsDBNull(name))
		{
			value = OCI_GetDouble2(p_rs,name);
		}
	}
	return value;
}

NGDBCom::DBDouble DBOCIReader::GetDouble( index_int index )
{
	DBDouble value;
	if(p_rs)
	{
		if(!IsDBNull(index))
		{
			value = OCI_GetDouble(p_rs,index+1);
		}
	}
	return value;
}

NGDBCom::DBFloat DBOCIReader::GetFloat( const char*name )
{
	DBFloat value;
	if(p_rs)
	{
		if(!IsDBNull(name))
		{
			value = OCI_GetFloat2(p_rs,name);
		}
	}
	return value;
}

NGDBCom::DBFloat DBOCIReader::GetFloat( index_int index )
{
	DBFloat value;
	if(p_rs)
	{
		if(!IsDBNull(index))
		{
			value = OCI_GetFloat(p_rs,index+1);

		}
	}
	return value;
}

NGDBCom::DBInt16 DBOCIReader::GetInt16( const char*name )
{
	DBInt16 value;
	if(p_rs)
	{
		if(!IsDBNull(name))
		{
			value = OCI_GetShort2(p_rs,name);
		}
	}
	return value;
}

NGDBCom::DBInt16 DBOCIReader::GetInt16( index_int index )
{
	DBInt16 value;
	if(p_rs)
	{
		if(!IsDBNull(index))
		{
			value = OCI_GetShort(p_rs,index+1);
		}
	}
	return value;
}

NGDBCom::DBInt32 DBOCIReader::GetInt32( const char*name )
{
	DBInt32 value;
	if(p_rs)
	{
		if(!IsDBNull(name))
		{
			value = OCI_GetInt2(p_rs,name);
		}
	}
	return value;
}

NGDBCom::DBInt32 DBOCIReader::GetInt32( index_int index )
{
	DBInt32 value;
	if(p_rs)
	{
		if(!IsDBNull(index))
		{
			value = OCI_GetInt(p_rs,index+1);
		}
	}
	return value;
}

NGDBCom::DBInt64 DBOCIReader::GetInt64( const char*name )
{
	DBInt64 value;
	if(p_rs)
	{
		if(!IsDBNull(name))
		{
			value = OCI_GetBigInt2(p_rs,name);
		}
	}
	return value;
}

NGDBCom::DBInt64 DBOCIReader::GetInt64( index_int index )
{
	DBInt64 value;
	if(p_rs)
	{
		if(!IsDBNull(index))
		{
			value = OCI_GetBigInt(p_rs,index+1);
		}
	}
	return value;
}

#endif
