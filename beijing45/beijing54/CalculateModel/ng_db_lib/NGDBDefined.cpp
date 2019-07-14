#define  _CRT_SECURE_NO_DEPRECATE
#include "NGDBDefined.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int ng_strcmpnocase(const char * str1, const char * str2)
{
	if(str1 == str2)
		return 0;
	if(str1 == NULL)
		return -1;
	if(str2 == NULL)
		return 1;
	int cmpval = 0;
	while((*str1)&&(*str2))
	{
		char v1 = toupper(*str1++);
		char v2 = toupper(*str2++);
		cmpval = v1 - v2;
		if(cmpval!=0)
			break;
	}
	if(cmpval == 0)
		cmpval =(*str1)- (*str2);
	return cmpval;
}

void StringToTM(const char * strval,tm & tmval)
{
	memset(&tmval,0,sizeof(tmval));
	if(strval == NULL)
		return;
	int date=0;
	int time = 0;
	const char *p1 = strval;
	const char *pT = strval;
	while(*p1)
	{
		if(*p1 == '-') date++;
		if(*p1 == ':') time++;
		if((time==0)
			&&(*p1 == ' '||*p1=='T')) pT = p1+1;
		++p1;
	}
	if(date==2&&time==2)
	{
		sscanf(strval,"%d-%d-%d %d:%d:%d",
			&tmval.tm_year,
			&tmval.tm_mon,
			&tmval.tm_mday,
			&tmval.tm_hour,
			&tmval.tm_min,
			&tmval.tm_sec
			);
		tmval.tm_mon -=1;
		tmval.tm_year -=1900;
	}
	else if(date==2&&time==1)
	{
		sscanf(strval,"%d-%d-%d %d:%d",
			&tmval.tm_year,
			&tmval.tm_mon,
			&tmval.tm_mday,
			&tmval.tm_hour,
			&tmval.tm_min
			);
		tmval.tm_mon -=1;
		tmval.tm_year -=1900;
	}
	else if(date == 2)
	{
		sscanf(strval,"%d-%d-%d",
			&tmval.tm_year,
			&tmval.tm_mon,
			&tmval.tm_mday
			);
		tmval.tm_mon -=1;
		tmval.tm_year -=1900;
	}
	else if(time == 2)
	{
		sscanf(pT,"%d:%d:%d",
			&tmval.tm_hour,
			&tmval.tm_min,
			&tmval.tm_sec
			);
	}
	else if(time ==1)
	{
		sscanf(pT,"%d:%d",
			&tmval.tm_hour,
			&tmval.tm_min
			);
	}
}

int vDBType[4] = {0};

int * GetSupportDBType( int & DBSize )
{
	int index = 0;
#ifdef USE_SQLITE 
	vDBType[index] = 1;
	index++;
#endif
#ifdef USE_OCCI
	vDBType[index]=2;
	index ++;
#endif  
#ifdef USE_MYSQL
	vDBType[index]=3;
	index ++;
#endif
#ifdef USE_SQLSEVER
	vDBType[index]=4;
	index ++;
#endif
#ifdef USE_OCILIB
	vDBType[index]=5;
	index ++;
#endif
	DBSize = index;
	return vDBType;
}

char * GetDBNameByType( int DBType )
{
	switch(DBType)
	{
	case 1:
		return "SQLite";
	case 2:
		return "Oracle";
	case 3:
		return "MySQL";
	case 4:
		return "SQLServer";
	case 5:
		return "Oracle_OciLib";
	default:
		return "UnSupportedDB";
	}
}
