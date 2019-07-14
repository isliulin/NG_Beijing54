#include "DBFile.h"
#include <stdio.h>
#include <vector>
using namespace std;

IDBFile * IDBFile::CreateDBFile(IDBConnection *p_con)
{
	if(p_con==NULL)
		return NULL;
	return new CDBFile(p_con);
}
void  IDBFile::ReleaseDBFile(IDBFile * pDBFile)
{
	if(pDBFile!=NULL)
		delete pDBFile;
}

CDBFile::CDBFile(IDBConnection*p_con):
IDBFile(p_con)
{
}

CDBFile::~CDBFile(void)
{
}

void ReadFileLine(FILE* pFile,std::string& rs)
{
	const int MAXLINE = 300;
	char textline[MAXLINE];
	rs.clear();
	while(!feof(pFile))
	{
		textline[0]='\0';
		fgets(textline,MAXLINE,pFile);
		rs+=textline;
		if((strlen(textline)<MAXLINE-1)
			||(textline[MAXLINE-2]=='\r')
			||(textline[MAXLINE-2]=='\n'))
			break;	
	}
}

std::string CleanCSVString( const char*p1,const char* p2 )
{
	const char *p=p1;
	const char *pStart = NULL;
	const char *pEnd = p1;
	while((*p!='\0')&&(p<p2))
	{
		if(*p!=' '
			&&*p!='\t'
			&&*p!='\r'
			&&*p!='\n'
			&&*p!='\"')
		{
			if(pStart == NULL)
				pStart=p;
			pEnd = p+1;
		}
		p++;
	}
	if(pStart == NULL)
		return std::string("");
	else
		return std::string(pStart,pEnd);
}
void SpliteString(const char * str,vector<std::string>& strlist,char c)
{
	strlist.clear();
	if(str == NULL)
		return;
	const char* pstart = str;
	const char *pend = str;
	while(*pend!='\0')
	{
		if(*pend == c)
		{
			string temp = CleanCSVString(pstart,pend);
			strlist.push_back(temp);
			pstart=pend+1;
		}
		++pend;
	}
	if(pend!=pstart)//×Ö·û´®½áÊø
	{
		string temp = CleanCSVString(pstart,pend);
		strlist.push_back(temp);
	}
}

bool CDBFile::FileToDB( const char* filename,const char * table )
{
	FILE* pFile = fopen(filename,"r");
	if(pFile==NULL)
		return false;
	bool bReadOK = true;
	std::string tablename;
	std::string fieldHead;
	try
	{
		while(!feof(pFile))
		{
			if(table==0)
				ReadFileLine(pFile,tablename);
			else
				tablename = table;
			ReadFileLine(pFile,fieldHead);
		}
		DBManager dbm(m_pcon);
		std::string sql = "select * from ";sql+= tablename;
		dbm.ExecuteReader(sql.c_str());
		int nFieldCount = dbm.GetFieldsCount();
		vector<std::string> fieldList;
		SpliteString(fieldHead.c_str(),fieldList,',');
		if(fieldList.size()==nFieldCount)
		{
			vector<std::string> datalist;
			std::string dataline;
			while(!feof(pFile))
			{
				ReadFileLine(pFile,dataline);
				SpliteString(dataline.c_str(),datalist,',');
				if(datalist.size()<nFieldCount)
					continue;
				std::string inVal = "insert into ";
				inVal+= tablename;
				inVal+=" values(";
				for(int i=0;i<nFieldCount;i++)
				{
					if(datalist[i].empty())
						inVal+="NULL";
					else
					{
						inVal+="'";
						inVal+=datalist[i];
						inVal+="'";
					}
					if(i<nFieldCount-1)
						inVal+=",";
				}// for
				inVal +=")";
				dbm.ExecuteNonQuery(inVal.c_str());
			}//while
		}//if

	}//try
	catch(...)
	{
		bReadOK = false;
	}
	fclose(pFile);
	return bReadOK;
}

bool CDBFile::DBToFile( const char* filename,const char *table )
{
	FILE* pFile = fopen(filename,"w");
	if(pFile==NULL)
		return false;
	std::string wrs;
	//write Table
	wrs = table;wrs+="\r\n";
	fwrite(wrs.c_str(),sizeof(char),wrs.length(),pFile);
	DBManager dbm(m_pcon);
	std::string sql = "select * from "; sql+=table;
	if(!dbm.ExecuteReader(sql.c_str()))
		return false;
	//write col
	int nFilesCount = dbm.GetFieldsCount();
	wrs.clear();
	for(int f=0;f<nFilesCount;f++)
	{
		wrs += dbm.GetName(f);
		if(f<nFilesCount-1)
			wrs+=",";
	}
	wrs += "\r\n";
	fwrite(wrs.c_str(),sizeof(char),wrs.length(),pFile);
	//write data
	while(dbm.Read())
	{
		wrs.clear();
		for(int d=0;d<nFilesCount;d++)
		{
			wrs += dbm.GetText(d);
			if(d<nFilesCount-1)
				wrs+=",";
		}
		wrs+="\r\n";
		fwrite(wrs.c_str(),sizeof(char),wrs.length(),pFile);
	}
	
	fclose(pFile);
	return true;
}
