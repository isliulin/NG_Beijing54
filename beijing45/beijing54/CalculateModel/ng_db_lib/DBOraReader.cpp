/*
 * DBOraReader.cpp
 *
 *  Created on: May 15, 2013
 *      Author: chenxing
 */
#ifdef USE_OCCI

#include "DBOraReader.h"
#include <new>
DBOraReader::DBOraReader(Statement *pstmt) {
	// TODO Auto-generated constructor stub
	p_stmt = pstmt;
	p_rs = NULL;
	lastRow = 0;
}

DBOraReader::~DBOraReader() {
	// TODO Auto-generated destructor stub
	Close();
}

void DBOraReader::Close()
{
	if(p_stmt!=NULL && p_rs!=NULL)
	{
		p_rs->cancel();
		p_stmt->closeResultSet(p_rs);
	}
	p_rs = NULL;
	cols.clear();
	sqlData.Clear();
	lastRow = 0;
}

void DBOraReader::Query(const char* sql)
{
	if(sql&&p_stmt!=NULL)
	{
		this->Close();
		sqlData = sql;
		p_rs = p_stmt->executeQuery(sql);
		lastRow = 0;
	}
}
bool DBOraReader::GetColumnList()
{
	if(cols.empty())
	{
		if(p_rs!=NULL)
			cols = p_rs->getColumnListMetaData();
	}
	return !cols.empty();
}

int DBOraReader::GetColumnIndex(const char *name)
{
	if(GetColumnList())
	{
		int count = cols.size();
		for(int index=0;index<count;index++)
		{
			std::string colnumName = cols[index].getString(MetaData::ATTR_NAME);
			if(strcmpnocase(colnumName.c_str(),name)==0)		
				return index;
		}
	}
	return -1;
}


DBBool DBOraReader::GetBoolean(const char* name)
{
	DBBool value;
	if(p_rs!=NULL)
	{

		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			index++;
			if(!p_rs->isNull(index))
			{
				int dbvalue = p_rs->getInt(index);
				value = (dbvalue!=0);
			}
		}

	}
	return value;
}
DBBool DBOraReader::GetBoolean(index_int index)
{
	DBBool value;
	if(p_rs!=NULL)
	{
		index++;
		if(!p_rs->isNull(index))
		{
			int dbvalue = p_rs->getInt(index);
			value = (dbvalue!=0);
		}
	}
	return value;
}

DBByte DBOraReader::GetByte(const char* name)
{
	DBByte value;
	if(p_rs!=NULL)
	{
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			index++;
			if(!p_rs->isNull(index))
			{
				Bytes bytes =p_rs->getBytes(index);
				if(bytes.isNull())
					value = bytes.byteAt(0);
			}
		}
	}
	return value;
}
DBByte DBOraReader::GetByte(index_int index)
{
	DBByte value;
	if(p_rs!=NULL)
	{
		index++;
		if(!p_rs->isNull(index))
		{
			Bytes bytes =p_rs->getBytes(index);
			if(bytes.isNull())
				value = bytes.byteAt(0);
		}
	}
	return value;
}

 DBBlob DBOraReader::GetBlob(const char*name)
{
	 DBBlob value;
	 if(p_rs!=NULL)
	 {
			int index = -1;
			if(-1!=(index =GetColumnIndex(name)))
			{
				index++;
				if(!p_rs->isNull(index))
				{
					Blob blob = p_rs->getBlob(index);
					unsigned int blobsize = blob.length();
					byte * bytes = new(std::nothrow) byte[blobsize];
					if(bytes)
					{
						blob.read(0,bytes,blobsize,0);
						value.SetValue(bytes,blobsize,true);
					}
				}
			}
	 }
	 return value;
}
DBBlob DBOraReader::GetBlob(index_int index)
{
	 DBBlob value;
	 if(p_rs!=NULL)
	 {
		 index++;
		if(!p_rs->isNull(index))
		{
			Blob blob = p_rs->getBlob(index);
			unsigned int blobsize = blob.getChunkSize();
			byte * bytes = new(std::nothrow) byte[blobsize];
			if(bytes)
			{
				blob.read(0,bytes,blobsize,0);
				value.SetValue(bytes,blobsize,true);
			}
		}
	 }
	 return value;
}

DBChar DBOraReader::GetChar(const char*name)
{
	 DBChar value;
	 if(p_rs!=NULL)
	 {
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			index++;
			if(!p_rs->isNull(index))
			{
				Bytes bytes =p_rs->getBytes(index);
				if(bytes.isNull())
					value = (char)bytes.byteAt(0);
			}
		}
	 }
	 return value;
}
 DBChar DBOraReader::GetChar(index_int index)
{
	 DBChar value;
	 if(p_rs!=NULL)
	 {
		 index++;
		if(!p_rs->isNull(index))
		{
			Bytes bytes =p_rs->getBytes(index);
			if(bytes.isNull())
				value = (char)bytes.byteAt(0);
		}
	 }
	 return value;
}

DBText DBOraReader::GetText(const char*name)
{
	 DBText value;
	 if(p_rs!=NULL)
	 {
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			index++;
			if(!p_rs->isNull(index))
			{
				std::string v = p_rs->getString(index).c_str();
				if(!v.empty())
					value = v.c_str();
			}
		}
	 }
	 return value;
}
DBText DBOraReader::GetText(index_int index)
{
	 DBText value;
	 if(p_rs!=NULL)
	 {
		 index++;
		if(!p_rs->isNull(index))
		{
			std::string v= p_rs->getString(index).c_str();
			if(!v.empty())
				value = v.c_str();
		}
	 }
	 return value;
}

DBDatetime DBOraReader::GetDatetime(const char* name)
{
	 DBDatetime value;
	 if(p_rs!=NULL)
	 {
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			index++;
			if(!p_rs->isNull(index))
			{
				Timestamp temptime = p_rs->getTimestamp(index);
				int year;
				unsigned int mon,day,hour,minu,sec,fs;
				temptime.getDate(year,mon,day);
				temptime.getTime(hour,minu,sec,fs);
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
DBDatetime DBOraReader::GetDatetime(index_int index)
{
	 DBDatetime value;
	 if(p_rs!=NULL)
	 {
		 index++;
		if(!p_rs->isNull(index))
		{
			
			Timestamp temptime = p_rs->getTimestamp(index);
			int year;
			unsigned int mon,day,hour,minu,sec,fs;
			temptime.getDate(year,mon,day);
			temptime.getTime(hour,minu,sec,fs);
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
	 return value;
}

DBDouble DBOraReader::GetDouble(const char* name)
{
	DBDouble value;
	 if(p_rs!=NULL)
	 {
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			index++;
			if(!p_rs->isNull(index))
			{
				double temp = p_rs->getDouble(index);
				value = temp;
			}
		}
	 }
	 return value;

}
DBDouble DBOraReader::GetDouble(index_int index)
{
	DBDouble value;
	 if(p_rs!=NULL)
	 {
		 index++;

		if(!p_rs->isNull(index))
		{
			double temp = p_rs->getDouble(index);
			value = temp;
		}
	 }
	 return value;
}

DBFloat DBOraReader::GetFloat(const char* name)
{
	DBFloat value;
	 if(p_rs!=NULL)
	 {
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			index++;
			if(!p_rs->isNull(index))
			{
				float temp = p_rs->getFloat(index);
				value = temp;
			}
		}
	 }
	 return value;

}
DBFloat DBOraReader::GetFloat(index_int index)
{
	DBFloat value;
	 if(p_rs!=NULL)
	 {
		 index++;
		if(!p_rs->isNull(index))
		{
			float temp = p_rs->getFloat(index);
			value = temp;
		}
	 }
	 return value;
}

DBInt16 DBOraReader::GetInt16(const char*name)
{
	DBInt16 value;
	if(p_rs!=NULL)
	 {
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			index++;
			if(!p_rs->isNull(index))
			{
				int temp = p_rs->getInt(index);
				value = (short)temp;
			}
		}
	 }
	 return value;
}

DBInt16 DBOraReader::GetInt16(index_int index)
{
	DBInt16 value;
	if(p_rs!=NULL)
	 {
		index++;
		if(!p_rs->isNull(index))
		{
			int temp = p_rs->getInt(index);
			value = (short)temp;
		}
	 }
	 return value;
}


DBInt32 DBOraReader::GetInt32(const char*name)
{
	DBInt32 value;
	if(p_rs!=NULL)
	 {
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			index++;
			if(!p_rs->isNull(index))
			{
				int temp = p_rs->getInt(index);
				value = (int16)temp;
			}
		}
	 }
	 return value;
}

DBInt32 DBOraReader::GetInt32(index_int index)
{
	DBInt32 value;
	if(p_rs!=NULL)
	 {
		index++;
		if(!p_rs->isNull(index))
		{
			int temp = p_rs->getInt(index);
			value = (int32)temp;
		}
	 }
	 return value;
}

DBInt64 DBOraReader::GetInt64(const char*name)
{
	DBInt64 value;
	if(p_rs!=NULL)
	 {
		int index = -1;
		if(-1!=(index =GetColumnIndex(name)))
		{
			index++;
			if(!p_rs->isNull(index))
			{
				int temp = p_rs->getInt(index);
				value = (int64)temp;
			}
		}
	 }
	 return value;
}

DBInt64 DBOraReader::GetInt64(index_int index)
{
	DBInt64 value;
	if(p_rs!=NULL)
	 {
		index++;
		if(!p_rs->isNull(index))
		{
			int temp = p_rs->getInt(index);
			value = (int64)temp;
		}
	 }
	 return value;
}

index_int DBOraReader::GetFieldsCount(void)
{
	if(GetColumnList())
	{
		return (index_int)cols.size();
	}
	return 0;
}

DBText DBOraReader::GetName(index_int index)
{
	if(GetColumnList())
	{
		const char * v = cols[index].getString(MetaData::ATTR_NAME).c_str();
		return DBText(v);
	}
	return DBText();
}
bool DBOraReader::IsDBNull(const char*name)
{
	if(p_rs!=NULL)
	{
		int index=-1;
		if(-1!=(index=GetColumnIndex(name)))
		{
			index++;
			return p_rs->isNull(index);
		}
	}
	return true;
}
bool DBOraReader::IsDBNull(index_int index)
{
	if(p_rs!=NULL)
	{
		index++;
		return p_rs->isNull(index);
	}
	return true;
}

bool DBOraReader::Read(void)
{
	if(p_rs!=NULL)
	{
		if(p_rs->next()!=ResultSet::END_OF_FETCH)
		{
			lastRow ++;
			return true;
		}
	}
	return false;
}

index_int DBOraReader::GetResultCount(void)
{
	if(p_rs!=NULL)
	{
		int rowcount = lastRow;
		if(p_rs->status()!=ResultSet::END_OF_FETCH)
		{
			while(p_rs->next()!=ResultSet::END_OF_FETCH)
				rowcount++;
		}
		if(rowcount!=lastRow)
		{
			p_rs->cancel();
			p_stmt->closeResultSet(p_rs);
			unsigned int index = 0;
			p_rs = p_stmt->executeQuery(sqlData.c_str());
			while(index<lastRow&&p_rs->next()!=ResultSet::END_OF_FETCH)
			{
				index ++;
			}
		}
		return rowcount;
	}
	return 0;
}

#endif/*USE_OCCI*/