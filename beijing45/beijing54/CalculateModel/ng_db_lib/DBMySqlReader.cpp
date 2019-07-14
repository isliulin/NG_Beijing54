#ifdef USE_MYSQL
#include "DBMySqlReader.h"
#include <stdio.h>
#include <new>
DBMySqlReader::DBMySqlReader(MYSQL * pcon)
{
	p_con = pcon;
	p_stmt = NULL;
	lastRow = 0;
	bResultEnd = true;
}

DBMySqlReader::~DBMySqlReader(void)
{
	Close();
}

bool DBMySqlReader::Query( const char* sql )
{
	if(sql)
	{
		Close();
		int res = mysql_query(p_con,sql);
		if(res)
		{
			DBText err = mysql_error(p_con);
			throw err;
		}
		p_stmt = mysql_store_result(p_con);
		lastRow = 0;
		bResultEnd = false;
		if(p_stmt == NULL)
		{
			const char * ex = mysql_error(p_con);
			if(ex!=NULL&&*ex!='\0')
			{
				DBText err = ex;
				throw err;
			}
		}
	}

	return (p_stmt != NULL);
}

void DBMySqlReader::Close()
{
	if(p_stmt != NULL)
	{
		mysql_free_result(p_stmt);
		fields.clear();
		lastRow = 0;
		p_stmt = NULL;
	}
}

bool DBMySqlReader::Read( void )
{
	if(p_stmt!=NULL)
	{
		//if(mysql_eof(p_stmt))
		//	return false;
		data_row = mysql_fetch_row(p_stmt);
		return data_row!=NULL;
	}
	return false;
}

bool DBMySqlReader::GetFields()
{
	if(fields.empty())
	{
		if(p_stmt != NULL)
		{
			int cout = mysql_num_fields(p_stmt);
			MYSQL_FIELD *pFilds = mysql_fetch_fields(p_stmt);
			for(int i=0;i<cout;i++)
			{
				std::string field = pFilds[i].name;
				fields.push_back(field);
			}
		}
	}
	return !fields.empty();
}

int DBMySqlReader::GetColumnIndex( const char *name )
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

index_int DBMySqlReader::GetFieldsCount( void )
{
	if(!fields.empty())
		return fields.size();
	else if(p_stmt!=NULL)
	{
		return mysql_num_fields(p_stmt);
	}
	return 0;
}

index_int DBMySqlReader::GetResultCount( void )
{
	if(p_stmt!=NULL)
		return (index_int)mysql_num_rows(p_stmt);
	return 0;
}

DBText DBMySqlReader::GetName( index_int index )
{
	if(GetFields())
	{
		if(index>0&&(unsigned int)index<fields.size())
			return DBText(fields[index].c_str());
	}
	return DBText();
}

NGDBCom::DBBool DBMySqlReader::GetBoolean( const char* name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return GetBoolean(index);
		}
	}
	return DBBool();
}

NGDBCom::DBBool DBMySqlReader::GetBoolean( index_int index )
{
    DBBool val;
	if(index<0||index>=GetFieldsCount())
		return val;
	if(data_row!=NULL)
	{
		const char * pData = data_row[index];
		if(pData!=NULL)
		{
			int dbvalue = 0;
			sscanf(pData,"%d",&dbvalue);
			val = (dbvalue!=0);
		}			
	}
	return val;
}

NGDBCom::DBByte DBMySqlReader::GetByte( const char* name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return GetByte(index);
		}
	}
	return DBByte();
}

NGDBCom::DBByte DBMySqlReader::GetByte( index_int index )
{
	DBByte val;
	if(index<0||index>=GetFieldsCount())
		return val;
	if(data_row!=NULL)
	{
		const char * pData = data_row[index];
		if(pData!=NULL)
		{
			val =  pData[0];
		}			
	}
	return val;
}

NGDBCom::DBBlob DBMySqlReader::GetBlob( const char*name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return GetBlob(index);
		}
	}
	return DBBlob();
}

NGDBCom::DBBlob DBMySqlReader::GetBlob( index_int index )
{
	DBBlob value;
	if(p_stmt!=NULL)
	{
		if(!IsDBNull(index))
		{
			const void * v = data_row[index];
			unsigned long *FieldLength = mysql_fetch_lengths(p_stmt);
			unsigned int blobsize = FieldLength[index];
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

NGDBCom::DBChar DBMySqlReader::GetChar( const char*name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return GetChar(index);
		}
	}
	return DBChar();
}

NGDBCom::DBChar DBMySqlReader::GetChar( index_int index )
{
	DBChar val;
	if(index<0||index>=GetFieldsCount())
		return val;
	if(data_row!=NULL)
	{
		const char * pData = data_row[index];
		if(pData!=NULL)
		{
			val =  pData[0];
		}			
	}
	return val;
}

NGDBCom::DBText DBMySqlReader::GetText( const char*name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return GetText(index);
		}
	}
	return DBText();
}

NGDBCom::DBText DBMySqlReader::GetText( index_int index )
{
	DBText val;
	if(index<0||index>=GetFieldsCount())
		return val;
	if(data_row!=NULL)
	{
		const char * pData = data_row[index];
		if(pData!=NULL)
		{
			val =  pData;
		}			
	}
	return val;
}

NGDBCom::DBDatetime DBMySqlReader::GetDatetime( const char* name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return GetDatetime(index);
		}
	}
	return DBDatetime();
}

NGDBCom::DBDatetime DBMySqlReader::GetDatetime( index_int index )
{
	DBDatetime val;
	if(index<0||index>=GetFieldsCount())
		return val;
	if(data_row!=NULL)
	{
		const char * pData = data_row[index];
		if(pData!=NULL)
		{
			tm temp;
			memset(&temp,0,sizeof(tm));
			StringToTM((const char*)pData,temp);
			val = temp;
		}			
	}
	return val;
}

NGDBCom::DBDouble DBMySqlReader::GetDouble( const char* name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return GetDouble(index);
		}
	}
	return DBDouble();
}

NGDBCom::DBDouble DBMySqlReader::GetDouble( index_int index )
{
	DBDouble val;
	if(index<0||index>=GetFieldsCount())
		return val;
	if(data_row!=NULL)
	{
		const char * pData = data_row[index];
		char *stop;
		if(pData!=NULL)
		{		
			double dbvalue = 0;
			sscanf(pData,"%lf",&dbvalue);
			val = dbvalue;
		}			
	}
	return val;
}

NGDBCom::DBFloat DBMySqlReader::GetFloat( const char*name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return GetFloat(index);
		}
	}
	return DBFloat();
}

NGDBCom::DBFloat DBMySqlReader::GetFloat( index_int index )
{
	DBFloat val;
	if(index<0||index>=GetFieldsCount())
		return val;
	if(data_row!=NULL)
	{
		const char * pData = data_row[index];
		char *stop;
		if(pData!=NULL)
		{		
			float dbvalue =0;
			sscanf(pData,"%f",&dbvalue);
			val = (float)dbvalue;
		}			
	}
	return val;
}

NGDBCom::DBInt16 DBMySqlReader::GetInt16( const char*name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return GetInt16(index);
		}
	}
	return DBInt16();
}

NGDBCom::DBInt16 DBMySqlReader::GetInt16( index_int index )
{
	DBInt16 val;
	if(index<0||index>=GetFieldsCount())
		return val;
	if(data_row!=NULL)
	{
		const char * pData = data_row[index];
		if(pData!=NULL)
		{
			long dbvalue = 0;
			sscanf(pData,"%i",&dbvalue);
			val = (short)dbvalue;
		}			
	}
	return val;
}

NGDBCom::DBInt32 DBMySqlReader::GetInt32( const char*name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return GetInt32(index);
		}
	}
	return DBInt32();
}

NGDBCom::DBInt32 DBMySqlReader::GetInt32( index_int index )
{
	DBInt32 val;
	if(index<0||index>=GetFieldsCount())
		return val;
	if(data_row!=NULL)
	{
		const char * pData = data_row[index];
		char *stop;
		if(pData!=NULL)
		{
			int dbvalue = 0;
			sscanf(pData,"%d",&dbvalue);
			val = (int)dbvalue;
		}			
	}
	return val;
}

NGDBCom::DBInt64 DBMySqlReader::GetInt64( const char*name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return GetInt64(index);
		}
	}
	return DBInt64();
}

NGDBCom::DBInt64 DBMySqlReader::GetInt64( index_int index )
{
	DBInt64 val;
	if(index<0||index>=GetFieldsCount())
		return val;
	if(data_row!=NULL)
	{
		const char * pData = data_row[index];
		char *stop;
		if(pData!=NULL)
		{
			long long dbvalue = 0;
			sscanf(pData,"%lld",&dbvalue);
			val = dbvalue;
		}			
	}
	return val;
}

bool DBMySqlReader::IsDBNull( const char*name )
{
	if(p_stmt!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			return IsDBNull(index);
		}
	}
	return true;
}

bool DBMySqlReader::IsDBNull( index_int index )
{
	if(index<0||index>=GetFieldsCount())
		return true;
	if(data_row!=NULL)
	{
		const char * pData = data_row[index];
		if(pData && pData[0]!='\0')
			return false;
	}
	return true;
}

#endif