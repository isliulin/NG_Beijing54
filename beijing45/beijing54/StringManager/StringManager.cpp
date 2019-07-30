#include "StringManager.h"
#include "NGString.h"
#include <stdlib.h>
#include<stdio.h>
#include <string.h>

#ifdef _MSC_VER
#include <io.h>
#include "iconv.h"
#include <direct.h>
#define MKDIR(x) {mkdir(x);}


#else
#include <iconv.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MKDIR(x) {mkdir(x,0777);}
#endif



#ifndef NULL
#define NULL 0
#endif

const int MAXTEMPMEM = 300;

NGStringManager::NGStringManager(void)
{
}


NGStringManager::~NGStringManager(void)
{
}

bool NGStringManager::IsSameString(const char * str1, const char * str2)
{
	return (strcmp(str1,str2)==0);
}
bool NGStringManager::IsSameNString(const char * str1, const char * str2,int n)
{
	return (strncmp(str1,str2,n)==0);
}
bool NGStringManager::IsSameStringNoCase(const char * str1, const char * str2)
{
    #ifdef _WIN32
        return (stricmp(str1,str2)==0);
    #else
        return (strcasecmp(str1,str2)==0);
    #endif // _WIN32
}


bool NGStringManager::SpliteKeyValue( const char*str,NGString& key ,NGString &val )
{
	NGVector<NGString> strlist;
	SpliteString(str,strlist,'=');
	if(strlist.size()>=2)
	{
		key = strlist[0];
		val = strlist[1];
		return true;
	}
	return false;
}

void NGStringManager::SpliteString(const char * str,NGVector<NGString>& strlist,char c)
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
			NGString temp(pstart,pend);
			strlist.push_back(temp);
			pstart=pend+1;
		}
		++pend;
	}
	if(pend!=pstart)//字符串结束
	{
		NGString temp(pstart,pend);
		strlist.push_back(temp);
	}
}


NGString NGStringManager::CleanCSVString( const char*p1,const char* p2 )
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
		return NGString("");
	else
		return NGString(pStart,pEnd);
}

void NGStringManager::SpliteCSVString( const char * str,NGVector<NGString>& strlist )
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
			NGString temp = CleanCSVString(pstart,pend);
			strlist.push_back(temp);
			pstart=pend+1;
		}
		++pend;
	}
	if(pend!=pstart)//字符串结束
	{
		NGString temp= CleanCSVString(pstart,pend);
		strlist.push_back(temp);
	}
}

bool NGStringManager::IsSameNStringNoCase(const char * str1, const char * str2,int n)
{
    #ifdef _WIN32
        return (strnicmp(str1,str2,n)==0);
    #else
        return (strncasecmp(str1,str2,n)==0);
    #endif // _WIN32

}

NGString NGStringManager::GetFilePath(const char * filename)
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
	return NGString(filename,nLen+1);
}

NGString NGStringManager::GetFileName( const char*filename,bool bsuffix/*=false*/ )
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
			return NGString(pBegin);
		else
			return NGString(pBegin,pEnd);
	}
	return NGString(pBegin);
}

NGString NGStringManager::GetFileSuffix(const char * filename)
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
		return NGString(pTemp);
	return NGString("");
}

bool NGStringManager::IsEmptyString(const char*str)
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

double NGStringManager::ToDouble(const char*str)
{
	double dValue = 0;
	sscanf(str,"%lf",&dValue);
	return dValue;

}

int NGStringManager::ToInt(const char*str)
{
	int iValue = 0;
	sscanf(str,"%d",&iValue);
	return iValue;
}

u_ng_int64 NGStringManager::ToUInt64( const char * str )
{
	u_ng_int64 uiValue = 0;
	sscanf(str,"%llu",&uiValue);
	return uiValue;
}


COLORREF NGStringManager::ToColor( const char*str )
{
	unsigned long r,g,b;
	sscanf(str,"#%02X%02X%02X",&r,&g,&b);
	return RGB(r,g,b);
}

COLORREF NGStringManager::MapToColor( const char*str )
{
	unsigned char c[3]={0};
	const char*p = str;
	int i=0;
	while(*p!='\0')
	{
		unsigned short temp = c[i%3]+(*p++);

		c[i%3]=(unsigned char)(temp&0x00FF);
		c[(i+1)%3]=(unsigned char)(temp&0xFF00);
	}
	return RGB(c[0],c[1],c[2]);
}

void NGStringManager::UnicodeToUTF_8( char* pOut,const wchar_t* pText )
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

#ifdef _WIN32
#include <windows.h>
void MultiByteToUTF8(char *pOut,const  char * str)
{
	int len = MultiByteToWideChar(CP_ACP,0,str,-1,NULL,0);
	wchar_t *wStr = new wchar_t[len+1];
	memset(wStr,0,sizeof(wchar_t)*(len+1));
	MultiByteToWideChar(CP_ACP,0,str,-1,wStr,len);
	len = WideCharToMultiByte(CP_UTF8,0,wStr,-1,NULL,0,NULL,NULL);
	//char * str_utf8 = new char[len+1];
	//memset(str_utf8,0,len+1);
	WideCharToMultiByte(CP_UTF8,0,wStr,-1,pOut,len,NULL,NULL);
	//STDNGString utf_8 = str_utf8;
	delete []wStr;
	//delete []str_utf8;
	//return utf_8;

}
#endif

void NGStringManager::ANSIToUTF8( char *pOut,const char* pText )
{
#ifdef _WIN32
	MultiByteToUTF8(pOut,pText);
#else

	if(pText == NULL)
		return;
	if(IsAllAscii(pText))
	{
		strcpy(pOut,pText);
	}
	else
	{
		wchar_t wstr[MAXTEMPMEM] = {0};
		mbstowcs(wstr,pText,MAXTEMPMEM);
		UnicodeToUTF_8(pOut,wstr);
	}
#endif
}

bool NGStringManager::IsAllAscii( const char*str )
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

tm NGStringManager::ToTime( const char*strval )
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


void NGStringManager::ListFileInPath( const char * dir,NGVector<NGString>& filelist,bool deep)
{
	if(dir==0)
		return;
#ifdef _MSC_VER
	NGString tempdir = dir;
	ConvertToUnixFilePath(tempdir);
	NGString fileName = tempdir;

	fileName += "/*";
	intptr_t hFile=0;
	struct _finddata_t fileinfo;
	if((hFile=_findfirst(fileName.c_str(),&fileinfo))!=-1)
	{
		do
		{
			if(fileinfo.attrib&_A_SUBDIR)
			{
				if(deep)
				{
					if (strcmp(".",fileinfo.name) == 0 || strcmp("..",fileinfo.name) == 0)
						continue;
					NGString subdir = tempdir;
					subdir +="/";
					subdir += fileinfo.name;
					ListFileInPath(subdir.c_str(),filelist,deep);
				}

			}
			else
			{
				NGString file = tempdir;
				file +="/";
				file += fileinfo.name;
				filelist.push_back(file);
			}

		} while (_findnext(hFile,&fileinfo)==0);
		_findclose(hFile);
	}
#else
	   struct dirent* ent = NULL;
	   DIR *pDir;
	   pDir=opendir(dir);
	   if(pDir == NULL)
		   return;
	   struct stat statbuf;          // 定义statbuf结构保存文件属性
	   while (NULL != (ent=readdir(pDir)))
	   {
		   NGString tempfile = dir;
		   tempfile += '/';
		   tempfile += ent->d_name;
		   lstat(tempfile.c_str(), &statbuf);
			if(S_IFDIR &statbuf.st_mode)    // 判断下一级成员是否是目录
			{
				if(deep)
				{
					if (strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name) == 0)
						continue;


					ListFileInPath(tempfile.c_str(), filelist,deep);              // 递归调用自身，扫描下一级目录的内容
				}

			}
			else
			{
				filelist.push_back(tempfile);
			}
	   }
	   closedir(pDir);
#endif

}

void NGStringManager::ListSubDirInPath( const char * dir,NGVector<NGString>& dirlist )
{
	if(dir==0)
		return;
#ifdef _MSC_VER
	NGString tempdir = dir;
	ConvertToUnixFilePath(tempdir);
	NGString fileName = tempdir;
	fileName += "/*";
	intptr_t hFile=0;
	struct _finddata_t fileinfo;
	if((hFile=_findfirst(fileName.c_str(),&fileinfo))!=-1)
	{
		do
		{
			if(fileinfo.attrib&_A_SUBDIR)
			{
				if (strcmp(".",fileinfo.name) == 0 || strcmp("..",fileinfo.name) == 0)
					continue;
				NGString subdir = tempdir;
				subdir +="/";
				subdir += fileinfo.name;
				dirlist.push_back(subdir);

			}
		} while (_findnext(hFile,&fileinfo)==0);
		_findclose(hFile);
	}
#else
	struct dirent* ent = NULL;
	DIR *pDir;
	pDir=opendir(dir);
	if(pDir == NULL)
		return;
	struct stat statbuf;          // 定义statbuf结构保存文件属性
	while (NULL != (ent=readdir(pDir)))
	{
		NGString tempfile = dir;
		tempfile += '/';
		tempfile += ent->d_name;
		lstat(tempfile.c_str(), &statbuf);
		if(S_IFDIR &statbuf.st_mode)    // 判断下一级成员是否是目录
		{

			if (strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name) == 0)
				continue;
			dirlist.push_back(tempfile);
	
		}
	}
	closedir(pDir);
#endif
}

bool NGStringManager::MakeDirectory( const char * dir )
{
	if(access(dir,0)!=0)
		MKDIR(dir);
	return (access(dir,0) == 0);

}


int NGStringManager::code_convert( const char* from_charset, const char* to_charset, const char* inbuf,size_t inlen, char* outbuf, size_t outlen )
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


void NGStringManager::GBKToUTF8( NGString & o_UTF,const char * i_pGBK )
{
	if(IsAllAscii(i_pGBK)
		||IsUTF8NGString(i_pGBK))
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

void NGStringManager::UTF8ToGBK( NGString & o_GBK,const char * i_pUTF8 )
{
	if(IsAllAscii(i_pUTF8)
		||!IsUTF8NGString(i_pUTF8))
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



bool  NGStringManager::IsLittleEndian()
{
	static unsigned short sV = 0x0001;
	return (*((char*)&sV)>0);
}
void NGStringManager::Swapnbytes(void * data,int n)
{
	char * cdata = (char*)data;
	int bn = n/2;
	char tmp;
	for(int i=0;i<bn;i++)
	{
		tmp = cdata[i];
		cdata[i] = cdata[n-1-i];
		cdata[n-1-i] = tmp;
	}
}

NGString NGStringManager::GetCurrentTimeString()
{
	time_t t = time((time_t*)0);
	struct tm * pt = localtime(&t);
	char datetime[200] = {0};
	sprintf(datetime,"%d%02d%02d%02d%02d%02d",
		pt->tm_year+1900,
		pt->tm_mon+1,
		pt->tm_mday,
		pt->tm_hour,
		pt->tm_min,
		pt->tm_sec);
	return NGString(datetime);
}

u_ng_int64 NGStringManager::GetCurrentTimeInit64()
{
	time_t t = time((time_t*)0);
	struct tm * pt = localtime(&t);

	u_ng_int64 curt = (pt->tm_year+1900)*1e10
		+(pt->tm_mon+1)*1e8
		+(pt->tm_mday)*1e6
		+(pt->tm_hour)*1e4
		+(pt->tm_min)*1e2
		+(pt->tm_sec);
	return curt;
}

bool NGStringManager::IsUTF8NGString( const char * str )
{
		short nBytes=0;//UFT8可用1-6个字节编码,ASCII用一个字节
		unsigned char chr;
		while(*str)
		{
			chr= *str;
			str++;
			if((chr&0x80) == 0 ) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
				continue;
			if(nBytes==0) //如果不是ASCII码,应该是多字节符,计算字节数
			{
				if(chr>=0x80)
				{
					if(chr>=0xFC&&chr<=0xFD)
						nBytes=6;
					else if(chr>=0xF8)
						nBytes=5;
					else if(chr>=0xF0)
						nBytes=4;
					else if(chr>=0xE0)
						nBytes=3;
					else if(chr>=0xC0)
						nBytes=2;
					else
						return false;

					nBytes--;
				}
			}
			else //多字节符的非首字节,应为 10xxxxxx
			{
				if( (chr&0xC0) != 0x80 )
					return false;
				nBytes--;
				if(nBytes == 0) // 只判断一个字符
					return true;
			}
		}
		if( nBytes > 0 ) //违返规则
			return false;

		return true;
}

void NGStringManager::ConvertToUnixFilePath( NGString & path )
{
	if(!path.empty())
	{
		char temp[300] = {0};
		const char * p = path.c_str();
		for(int i=0;i<300;i++)
		{
			temp[i] = p[i];
			if(temp[i]=='\\')
				temp[i] = '/';
			else if(temp[i] == '\0')
				break;
		}
	}
	
}

bool NGStringManager::CheckFileAccess( const char *filename,int mode/*=0*/ )
{
	if(!filename) return false;
	return access(filename,mode) == 0;
}

void NGStringManager::ConvertFromInt( char * buf,int iV )
{
	if(buf)
		sprintf(buf,"%d",iV);
}



void NGStringManager::ConvertFromDouble( char* buf, double dV,int iPres /*=8*/ )
{
	if(iPres<1)iPres=1;
	else if(iPres>20)iPres=20;
	char df[8] = {0};
	sprintf(df,"%%.%dlf",iPres);
	sprintf(buf,df,dV);
	//剪除后缀0
	bool bDot = false;
	char * p = &buf[1];
	char* pb = &buf[1];
	while(*pb)
	{
		if(*pb!='0')
			p = pb+1;
		if(*pb == '.')
			bDot = true;
		pb++;
	}
	if(bDot)
		*p = '\0';
	if(*(--p) == '.')*p = '\0'; //最后一位是小数点去除
}

void NGStringManager::ConvertFromFloat( char * buf,float fV,int iPres /*= 8*/ )
{
	return ConvertFromDouble(buf,fV,iPres);
}

void NGStringManager::ConvertFromUInt64( char * buf, u_ng_int64 i64V )
{
	if(buf)
		sprintf(buf,"%llu",i64V);

}





