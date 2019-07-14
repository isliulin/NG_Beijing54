#ifdef USE_SQLITE

#include "DBSqliteReader.h"
#include <new>
DBSqliteReader::DBSqliteReader(sqlite3* pcon)
{
	p_con = pcon;
	p_stmt = NULL;
	lastRow = 0;
	bResultEnd = true;
}

DBSqliteReader::~DBSqliteReader(void)
{
	Close();
}

bool DBSqliteReader::Query( const char* sql )
{	
	if(sql)
	{
		Close();
		int nTest =  sqlite3_threadsafe();
		sqlite3_prepare(p_con,sql,-1,&p_stmt,NULL);
		lastRow = 0;
		bResultEnd = false;
		if(p_stmt == NULL)
		{
			const char * ex = sqlite3_errmsg(p_con);
			if(ex!=NULL&&*ex!='\0')
			{
				DBText err = ex;
				throw err;
			}
		}
	}

	return (p_stmt != NULL);
}

void DBSqliteReader::Close()
{
	if(p_stmt != NULL)
	{
		sqlite3_finalize(p_stmt);
		fields.clear();
		lastRow = 0;
		p_stmt = NULL;
	}
}

bool DBSqliteReader::Read( void )
{
	if(p_stmt!=NULL)
	{
		if(SQLITE_ROW == sqlite3_step(p_stmt))
		{
			lastRow ++;
			bResultEnd = false;
			return true;
		}
		else
			bResultEnd = true;
	}
	return false;
}

bool DBSqliteReader::GetFields()
{
	if(fields.empty())
	{
		if(p_stmt != NULL)
		{
			int cout = sqlite3_column_count(p_stmt);
			for(int i=0;i<cout;i++)
			{
				std::string field = sqlite3_column_name(p_stmt,i);
				fields.push_back(field);
			}
		}
	}
	return !fields.empty();
}

int DBSqliteReader::GetColumnIndex( const char *name )
{
	if(GetFields())
	{
		int count = fields.size();
		for(int index=0;index<count;index++)
		{
			std::string colnumName = fields[index];
			if(strcmpnocase(colnumName.c_str(),name)==0)		
				return index;
		}
	}
	return -1;
}

index_int DBSqliteReader::GetFieldsCount( void )
{
	if(!fields.empty())
		return fields.size();
	else if(p_stmt!=NULL)
	{
		return sqlite3_column_count(p_stmt);
	}
	return 0;
}
bool DBSqliteReader::IsDBNull( index_int index )
{
	if(index<0||index>=GetFieldsCount())
		return true;
	if(p_stmt!=NULL)
	{
		return (SQLITE_NULL == sqlite3_column_type(p_stmt,index));
	}
	return true;
}

bool DBSqliteReader::IsDBNull( const char*name )
{
	int index = GetColumnIndex(name);
	return IsDBNull(index);
}
NGDBCom::DBBool DBSqliteReader::GetBoolean( const char* name )
{
	DBBool value;
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			if(!IsDBNull(index))
			{				
				int dbvalue = sqlite3_column_int(p_stmt,index);
				value = (dbvalue!=0);
			}
		}
	}
	return value;
}

NGDBCom::DBBool DBSqliteReader::GetBoolean( index_int index )
{
	DBBool value;
	if(p_stmt!=NULL)
	{
		if(!IsDBNull(index))
		{
			int dbvalue = sqlite3_column_int(p_stmt,index);
			value = (dbvalue!=0);
		}
	}
	return value;
}

NGDBCom::DBByte DBSqliteReader::GetByte( const char* name )
{
	DBByte value;
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			if(!IsDBNull(index))
			{
				const unsigned char * v =sqlite3_column_text(p_stmt,index);
				if(v!=NULL)
					value = v[0];
			}
		}
	}
	return value;
}

NGDBCom::DBByte DBSqliteReader::GetByte( index_int index )
{
	DBByte value;
	if(p_stmt!=NULL)
	{
		if(!IsDBNull(index))
		{
			const unsigned char * v =sqlite3_column_text(p_stmt,index);
			if(v!=NULL)
				value = v[0];
		}
	}
	return value;
}

NGDBCom::DBBlob DBSqliteReader::GetBlob( const char*name )
{
	DBBlob value;
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			if(!IsDBNull(index))
			{
				const void * v = sqlite3_column_blob(p_stmt,index);
				unsigned int blobsize = sqlite3_column_bytes(p_stmt,index);
				byte * bytes = new(std::nothrow) byte[blobsize];
				if(bytes)
				{
					memcpy(bytes,v,blobsize);
					value.SetValue(bytes,blobsize,true);
				}

			}
		}
	}
	return value;
}

NGDBCom::DBBlob DBSqliteReader::GetBlob( index_int index )
{
	DBBlob value;
	if(p_stmt!=NULL)
	{
		if(!IsDBNull(index))
		{
			const void * v = sqlite3_column_blob(p_stmt,index);
			unsigned int blobsize = sqlite3_column_bytes(p_stmt,index);
			byte * bytes = new(std::nothrow) byte[blobsize];
			if(bytes)
			{
				memcpy(bytes,v,blobsize);
				value.SetValue(bytes,blobsize,true);
			}
		}
	}
	return value;
}

NGDBCom::DBChar DBSqliteReader::GetChar( const char*name )
{
	DBChar value;
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			if(!IsDBNull(index))
			{
				const unsigned char * v =sqlite3_column_text(p_stmt,index);
				if(v!=NULL)
					value = (char)v[0];
			}
		}
	}
	return value;
}

NGDBCom::DBChar DBSqliteReader::GetChar( index_int index )
{
	DBChar value;
	if(p_stmt!=NULL)
	{
		if(!IsDBNull(index))
		{
			const unsigned char * v =sqlite3_column_text(p_stmt,index);
			if(v!=NULL)
				value = (char)v[0];
		}
	}
	return value;
}

NGDBCom::DBText DBSqliteReader::GetText( const char*name )
{
	DBText value;
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			if(!IsDBNull(index))
			{
				const unsigned char * v = sqlite3_column_text(p_stmt,index);
				if(v!=NULL)
				{
					value = (const char*)v;
				}
			}
		}
	}
	return value;
}

NGDBCom::DBText DBSqliteReader::GetText( index_int index )
{
	DBText value;
	if(p_stmt!=NULL)
	{
		if(!IsDBNull(index))
		{
			const unsigned char * v = sqlite3_column_text(p_stmt,index);
			if(v!=NULL)
			{
				value = (const char*)v;
			}
		}
	}
	return value;
}

NGDBCom::DBDatetime DBSqliteReader::GetDatetime( const char* name )
{
	DBDatetime value;
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			if(!IsDBNull(index))
			{
				const unsigned char * v = sqlite3_column_text(p_stmt,index);	
				tm temp;
				memset(&temp,0,sizeof(tm));
				StringToTM((const char*)v,temp);
				value = temp;
			}
		}
	}
	return value;
}

NGDBCom::DBDatetime DBSqliteReader::GetDatetime( index_int index )
{
	DBDatetime value;
	if(p_stmt!=NULL)
	{
		if(!IsDBNull(index))
		{
			const unsigned char * v = sqlite3_column_text(p_stmt,index);	
			tm temp;
			memset(&temp,0,sizeof(tm));
			StringToTM((const char*)v,temp);
			value = temp;
		}
	}
	return value;
}

NGDBCom::DBDouble DBSqliteReader::GetDouble( const char* name )
{
	DBDouble value;
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			if(!IsDBNull(index))
			{
				double temp = sqlite3_column_double(p_stmt,index);
				value = temp;
			}
		}
	}
	return value;
}

NGDBCom::DBDouble DBSqliteReader::GetDouble( index_int index )
{
	DBDouble value;
	if(p_stmt!=NULL)
	{
		if(!IsDBNull(index))
		{
			double temp = sqlite3_column_double(p_stmt,index);
			value = temp;
		}
	}
	return value;
}

NGDBCom::DBFloat DBSqliteReader::GetFloat( const char*name )
{
	DBFloat value;
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			if(!IsDBNull(index))
			{
				float temp = (float)sqlite3_column_double(p_stmt,index);
				value = temp;
			}
		}
	}
	return value;
}

NGDBCom::DBFloat DBSqliteReader::GetFloat( index_int index )
{
	DBFloat value;
	if(p_stmt!=NULL)
	{
		if(!IsDBNull(index))
		{
			float temp = (float)sqlite3_column_double(p_stmt,index);
			value = temp;
		}
	}
	return value;
}

NGDBCom::DBInt16 DBSqliteReader::GetInt16( const char*name )
{
	DBInt16 value;
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			if(!IsDBNull(index))
			{
				int temp = sqlite3_column_int(p_stmt,index);
				value = (short)temp;
			}
		}
	}
	return value;
}

NGDBCom::DBInt16 DBSqliteReader::GetInt16( index_int index )
{
	DBInt16 value;
	if(p_stmt!=NULL)
	{

		if(!IsDBNull(index))
		{
			int temp = sqlite3_column_int(p_stmt,index);
			value = (short)temp;
		}
	}
	return value;
}

NGDBCom::DBInt32 DBSqliteReader::GetInt32( const char*name )
{
	DBInt32 value;
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			if(!IsDBNull(index))
			{
				int temp = sqlite3_column_int(p_stmt,index);
				value = (short)temp;
			}
		}
	}
	return value;
}

NGDBCom::DBInt32 DBSqliteReader::GetInt32( index_int index )
{
	DBInt32 value;
	if(p_stmt!=NULL)
	{
		if(!IsDBNull(index))
		{
			int temp = sqlite3_column_int(p_stmt,index);
			value = (short)temp;
		}

	}
	return value;
}

NGDBCom::DBInt64 DBSqliteReader::GetInt64( const char*name )
{
	DBInt64 value;
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			if(!IsDBNull(index))
			{
				int temp = sqlite3_column_int(p_stmt,index);
				value = (short)temp;
			}
		}
	}
	return value;
}

NGDBCom::DBInt64 DBSqliteReader::GetInt64( index_int index )
{
	DBInt64 value;
	if(p_stmt!=NULL)
	{

			if(!IsDBNull(index))
			{
				int temp = sqlite3_column_int(p_stmt,index);
				value = (short)temp;
			}
	}
	return value;
}

index_int DBSqliteReader::GetResultCount( void )
{
	if(p_stmt!=NULL)
	{
		unsigned int rowcount = lastRow;
		if(!bResultEnd)
		{
			while(sqlite3_step(p_stmt)==SQLITE_ROW)
				rowcount++;
			if(rowcount!=lastRow)
			{
				sqlite3_reset(p_stmt);
				unsigned int index = 0;
				while(index<lastRow&&sqlite3_step(p_stmt)==SQLITE_ROW)
					index++;
			}
		}
		return rowcount;
		
	}
	return 0;
}

DBText DBSqliteReader::GetName( index_int index )
{
	if(GetFields())
	{
		if(index>0&&(unsigned int)index<fields.size())
		return DBText(fields[index].c_str());
	}
	return DBText();
}
#endif/*USE_SQLITE*/