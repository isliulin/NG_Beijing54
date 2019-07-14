#include "XmlStringManager.h"
#include <string.h>
#include <stdlib.h>

#include<stdio.h>
#ifdef _WIN32
#include "iconv.h"
#else
#include <iconv.h>
#endif

#ifndef NULL
#define NULL 0
#endif

const int MAXTEMPMEM = 300;



XmlStringManager::XmlStringManager(void)
{
}


XmlStringManager::~XmlStringManager(void)
{
}

bool XmlStringManager::IsSameString(const char * str1, const char * str2)
{
	return (strcmp(str1,str2)==0);
}
bool XmlStringManager::IsSameNString(const char * str1, const char * str2,int n)
{
	return (strncmp(str1,str2,n)==0);
}
bool XmlStringManager::IsSameStringNoCase(const char * str1, const char * str2)
{
    #ifdef _WIN32
        return (stricmp(str1,str2)==0);
    #else
        return (strcasecmp(str1,str2)==0);
    #endif // _WIN32
}


bool XmlStringManager::SpliteKeyValue( const char*str,string& key ,string &val )
{
	vector<string> strlist;
	SpliteString(str,strlist,'=');
	if(strlist.size()>=2)
	{
		key = strlist[0];
		val = strlist[1];
		return true;
	}
	return false;
}

void XmlStringManager::SpliteString(const char * str,vector<string>& strlist,char c)
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
			string temp(pstart,pend);
			strlist.push_back(temp);
			pstart=pend+1;
		}
		++pend;
	}
	if(pend!=pstart)//字符串结束
	{
		string temp(pstart,pend);
		strlist.push_back(temp);
	}
}


string XmlStringManager::CleanCSVString( const char*p1,const char* p2 )
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
		return string("");
	else
		return string(pStart,pEnd);
}

void XmlStringManager::SpliteCSVString( const char * str,vector<string>& strlist )
{
	strlist.clear();
	if(str == NULL)
		return ;
	const char* pstart = str;
	const char *pend = str;
	const char quote = '\"';
	const char comma = ',';
	int quotecount= 0;
	while(*pend!='\0')
	{
		if(*pend==quote)
		{
			if((pend==str||*(pend-1)!='\\'))
				quotecount++;
		}
		if(*pend == comma && (quotecount%2==0))
		{
			string temp = CleanCSVString(pstart,pend);
			strlist.push_back(temp);
			pstart=pend+1;
		}
		++pend;
	}
	if(pend!=pstart)//字符串结束
	{
		string temp= CleanCSVString(pstart,pend);
		strlist.push_back(temp);
	}
}

bool XmlStringManager::IsSameNStringNoCase(const char * str1, const char * str2,int n)
{
    #ifdef _WIN32
        return (strnicmp(str1,str2,n)==0);
    #else
        return (strncasecmp(str1,str2,n)==0);
    #endif // _WIN32

}

string XmlStringManager::GetFilePath(const char * filename)
{
	const char * p = filename;
	int nLen = -1;
	while(*p!='\0')
	{
		if((*p=='\\')
			||(*p=='/'))
		nLen = p-filename;
		p++;
	}
	return string(filename,nLen+1);
}

string XmlStringManager::GetFileName( const char*filename,bool bsuffix/*=false*/ )
{
	const char * p = filename;
	const char *pBegin = filename;
	const char *pEnd = NULL;
	while(*p!='\0')
	{
		if((*p=='\\')
			||(*p=='/'))
			pBegin = p+1;
		else if(*p=='.')
			pEnd = p;
		p++;
	}
	if(!bsuffix)
	{
		if(pEnd == NULL)
			return string(pBegin);
		else
			return string(pBegin,pEnd);
	}
	return string(pBegin);
}

string XmlStringManager::GetFileSuffix(const char * filename)
{
	int nlen = strlen(filename);
	const char * p = filename;
	const char *pTemp = NULL;
	while(*p!='\0')
	{
		if(*p++ == '.')
			pTemp = p;//实际已经是“.”的后一个位置
	}
	if(pTemp!=NULL)
		return string(pTemp);
	return string("");
}

bool XmlStringManager::IsEmptyString(const char*str)
{
	if(str == NULL)
		return true;
	while(*str!='\0')
	{
		if(*str!=' '
			||*str!=','
			||*str!='\t')
		return false;
		str++;
	}
	return true;
}

double XmlStringManager::ToDouble(const char*str)
{
	double dValue = 0;
	sscanf(str,"%lf",&dValue);
	return dValue;

}

int XmlStringManager::ToInt(const char*str)
{
	int iValue = 0;
	sscanf(str,"%d",&iValue);
	return iValue;
}


void XmlStringManager::UnicodeToUTF_8( char* pOut,const wchar_t* pText )
{

	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	if(pText==NULL)
		return ;
	while (*pText!=0)
	{
		char* pchar = (char *)pText;
		if(*pText>=0x0800)
		{

			pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
			pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
			pOut[2] = (0x80 | (pchar[0] & 0x3F));
			pOut +=3;
		}
		else if(*pText>=0x0080)
		{
			pOut[0]=(0xC0|((pchar[1]&0x07)<<2))+((pchar[0]&0xC0)>>6);
			pOut[1]=(0x80|(pchar[0]&0x3F));
			pOut+=2;
		}
		else
		{
			pOut[0] = pchar[0];
			pOut += 1;
		}
		pText++;
	}
	*pOut = '\0';

	return;
}



bool XmlStringManager::IsAllAscii( const char*str )
{
	if(str == NULL)
		return true;
	while(*str!='\0')
	{
		if(!isascii(*str))
			return false;
		str++;
	}
	return true;
}

tm XmlStringManager::ToTime( const char*strval )
{
	tm tmval;
	memset(&tmval,0,sizeof(tmval));
	if(strval == NULL)
		return tmval;
	int date=0;
	int time = 0;
	const char *p1 = strval;
	const char *pT = strval;
	while(*p1)
	{
		if(*p1 == '-') date++;
		if(*p1 == ':') time++;
		if((time==0)
			&&(*p1 == ' '||*p1=='T'||*p1=='\t')) pT = p1+1;
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
	return tmval;
}



int code_convert( const char* from_charset, const char* to_charset, const char* inbuf,size_t inlen, char* outbuf, size_t outlen )
{
	iconv_t cd;
#ifdef _WIN32
	const char** pin = &inbuf;  
#else
	char** pin = (char**)&inbuf;  
#endif

	char** pout = &outbuf;

	cd = iconv_open(to_charset,from_charset);  

	if(cd == 0)
		return -1;

	size_t len = iconv(cd,pin,&inlen,pout,&outlen);

	iconv_close(cd);

	return (int)len;  
}


void XmlStringManager::GBKToUTF8( string & o_UTF,const char * i_pGBK )
{
	if(IsAllAscii(i_pGBK))
	{
		o_UTF = i_pGBK;
		return;
	}
	///////////////////////////////////////
	size_t inlen = strlen(i_pGBK);
	size_t outlen = (int)(inlen*1.5)+2;
	char * pout = new char[outlen];
	memset(pout,0,outlen);
	if(code_convert("gbk","utf-8",i_pGBK,inlen,pout,outlen)!=-1)
	{
		o_UTF = pout;
	}
	else
	{
		o_UTF = i_pGBK;
	}
	delete [] pout;

}

void XmlStringManager::UTF8ToGBK( string & o_GBK,const char * i_pUTF8 )
{
	if(IsAllAscii(i_pUTF8))
	{
		o_GBK = i_pUTF8;
		return;
	}
	size_t inlen = strlen(i_pUTF8);
	size_t outlen =inlen+2;
	char * pout = new char[outlen];
	memset(pout,0,outlen);
	if(code_convert("utf-8","gbk",i_pUTF8,inlen,pout,outlen)!=-1)
	{
		o_GBK = pout;
	}
	else
	{
		o_GBK = i_pUTF8;
	}
	delete [] pout;

}









