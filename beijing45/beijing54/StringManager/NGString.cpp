#include "NGString.h"
#include <string.h>
#include <ctype.h>
#include <new>

#include <stdlib.h>

#define NG_ISCHAR(ch) ((ch<=0x5a && ch>=0x41)||(ch<=0x7a && ch>=0x61))
#define NG_IGNORECASE 0x20

const char* ngnocase_strstr(const char* str1, const char* str2)
{	
	if (!str2||!(*str2)|!str1)
		return NULL;
	const char* cp = str1;
	const char* s1;
	const char* s2;

	while(*cp)
	{
		s1=cp;
		s2=str2;

		while(*s1 && *s2
			&& (!(*s1-*s2) || (((*s1-*s2)==NG_IGNORECASE || (*s2-*s1)==NG_IGNORECASE) && NG_ISCHAR(*s1) && NG_ISCHAR(*s2)) ))
		{
			s1++,s2++;
		}

		if (!(*s2))
		{
			return (cp);
		}

		cp++;
	}

	return NULL;
}


NGString::NGString()
{
	p_str = 0;
	csize = 0;
}

NGString::NGString( const NGString & str )
{
	p_str = 0;
	csize = 0;
	if(!str.empty())
	{
		csize  = str.csize;
		p_str = new(std::nothrow) char[csize+1];
		if(p_str)
			strcpy(p_str,str.p_str);
		else
			csize = 0;
	}
}

NGString::NGString( const char * c_str )
{
	p_str = 0;
	csize = 0;
	if(c_str)
	{
		csize= strlen(c_str);
		p_str = new(std::nothrow) char[csize+1];
		if(p_str)
			strcpy(p_str,c_str);
		else
			c_str = 0;
	}
}

NGString::NGString( const char * c_str,size_t len )
{
	p_str = 0;
	csize = 0;
	if(c_str)
	{
		csize= strlen(c_str);
		if(csize>len)
			csize = len;
		p_str = new(std::nothrow) char[csize+1];
		if(p_str)
		{
			strncpy(p_str,c_str,csize);
			p_str[csize]='\0';
		}
		else
			c_str = 0;
	}
}


NGString::NGString( const char* p_start,const char * p_end )
{
	p_str = 0;
	csize = 0;
	if(p_end>p_start)
	{
		csize = p_end - p_start;
		p_str = new (std::nothrow)char [csize+1];
		if(p_str)
		{
			strncpy(p_str,p_start,csize);
			p_str[csize] = '\0';
		}
		else
			csize = 0;
	}
	 
}

NGString::~NGString()
{
	clear();
}

NGString& NGString::operator=( const NGString & str )
{
	if(&str == this)
		return *this;
	//
	if(p_str) delete [] p_str;
	p_str = 0;
	csize  = str.csize;
	if(csize !=0)
	{
		p_str = new(std::nothrow) char[csize+1];
		if(p_str)
			strcpy(p_str,str.p_str);
		else
			csize = 0;
	}

	return *this;
}

NGString& NGString::operator=( const char* c_str )
{
	if(c_str == p_str)
		return *this;
	if(p_str) delete [] p_str;
	p_str = 0;
	csize = 0;
	if(c_str)
	{
		csize = strlen(c_str);
		p_str = new(std::nothrow) char[csize+1];
		if(p_str)
			strcpy(p_str,c_str);
		else
			csize = 0;
	}
	return *this;
}

NGString& NGString::operator += (const NGString &str)
{
	if(str.empty())
		return *this;

	size_t total = this->csize + str.csize;
	char * p_temp = new(std::nothrow) char [total+1];
	if(p_temp)
	{
		if(p_str)
			strcpy(p_temp,p_str);
		if(str.p_str)
			strcat(p_temp,str.p_str);
	}
	if(p_str) delete [] p_str;
	p_str = p_temp;
	csize = p_temp?total:0;
	return *this;
}
NGString& NGString::operator += (const char* c_str)
{
	if(c_str==0||c_str[0]=='\0')
		return *this;
	size_t total = this->csize + strlen(c_str);
	char * p_temp = new(std::nothrow) char [total+1];
	if(p_temp)
	{
		if(p_str)
			strcpy(p_temp,p_str);
		if(c_str)
			strcat(p_temp,c_str);
	}
	if(p_str) delete [] p_str;
	p_str = p_temp;
	csize = p_temp?total:0;

	return *this;
}

NGString& NGString::operator += (const char c)
{
	if(c=='\0')
		return *this;
	size_t total = this->csize + 1;
	char * p_temp = new(std::nothrow) char [total+1];
	if(p_temp)
	{
		if(p_str)
			strcpy(p_temp,p_str);
		p_temp[total-1] = c;
		p_temp[total]='\0';
	}
	if(p_str) delete [] p_str;
	p_str = p_temp;
	csize = p_temp?total:0;

	return *this;
}


NGString NGString::operator+ (const NGString & str)
{
	NGString temp(*this);
	temp += str;
	return temp;
}
NGString NGString::operator+ (const char* c_str)
{
	NGString temp(*this);
	temp += c_str;
	return temp;
}



bool NGString::operator == (const char * c_str)
{
	if((c_str == NULL)
		||(c_str[0] == '\0'))
		return empty();
	if(!empty())
		return strcmp(p_str,c_str)==0;
	return false;
}

bool NGString::operator != (const char * c_str)
{
	return !(*this == c_str);
}
bool NGString::operator == (const NGString & str)
{
	return (*this == str.p_str);
}
bool NGString::operator != (const NGString & str)
{
	return !(*this == str.p_str);
}

char NGString::operator [](int i) const
{
	if((i>=csize)||(p_str==NULL))
		return '\0';
	return p_str[i];
}

NGString operator+ (const char * c_str,const NGString & str)
{
	NGString temp(c_str);
	temp += str;
	return temp;
}
const char * NGString::c_str() const
{
	return p_str?p_str:"";
}

bool NGString::empty() const
{
	return (p_str==0)||(p_str[0] == '\0');
}

size_t NGString::size() const
{
	return csize;
}

NGString NGString::substr( size_t offset,size_t len ) const
{
	if((offset<csize)&&p_str)
	{
		return NGString(p_str+offset,len);
	}

	return NGString();
}

void NGString::clear()
{
	if(p_str) delete []p_str;
	p_str = 0;
	csize = 0;
}

int NGString::refind( const char c ) const
{
	const char * pTemp = p_str+csize;
	while(pTemp!=p_str)
	{
		if(*pTemp == c)
			return pTemp-p_str;
		pTemp --;
	}
	return (*pTemp==c)?0:-1;
}

int NGString::find( const char c,size_t startindex ) const
{
	if((startindex>=csize) || (p_str==NULL))
		return -1;
	const char * pTemp = p_str+startindex;
	while(*pTemp)
	{
		if(*pTemp == c)
			return pTemp-p_str;
		pTemp ++;
	}
	return -1;
}

int NGString::find( const char * c_str,size_t startindex ) const
{
	if((startindex>=csize) || (p_str==NULL))
		return -1;
	if((c_str == NULL)||c_str[0]=='\0')
		return -1;
	char *p = strstr(p_str,c_str);
	return p?p-p_str:-1;
}

int NGString::findignorecase( const char* c_str,size_t startindex/*=0*/ ) const
{
	if((startindex>=csize) || (p_str==NULL))
		return -1;
	if((c_str == NULL)||c_str[0]=='\0')
		return -1;
	const char *p = ngnocase_strstr(p_str,c_str);
	return p?p-p_str:-1;
}

int NGString::find( NGString & str,size_t startindex ) const
{
	return find(str.p_str,startindex);
}

int NGString::findignorecase( NGString & str,size_t startindex ) const
{
	return findignorecase(str.p_str,startindex);
}

void NGString::replace( const char * newstr,const char *oldstr )
{
	if((newstr==NULL)||(oldstr==NULL))
		return;
	size_t len_old = strlen(oldstr);
	int off = -1;
	size_t start = 0;
	bool breplace = false;
	NGString temp;
	while((off=find(oldstr,start)!=-1))
	{
		breplace = true;
		temp.append(*this,start,off-start);
		temp += newstr;
		start = off+len_old;
	}
	if(breplace)
	{
		if(start<csize)
			temp.append(*this,start,csize-start);
		*this = temp;
	}
}

void NGString::append( const char * c_str,size_t len )
{
	if((c_str==NULL)||(c_str[0]=='\0'))
		return;
	size_t maxlen = strlen(c_str);

	size_t minlen = (maxlen)<len?(maxlen):len;

	char * p_temp = new(std::nothrow) char [csize+minlen+1];
	if(p_temp)
	{
		if(p_str)
			strcpy(p_temp,p_str);
		if(c_str)
			strncat(p_temp,c_str,minlen);
		p_temp[csize+minlen] = '\0';
	}
	if(p_str) delete [] p_str;
	p_str = p_temp;
	csize = p_temp?csize+minlen:0;

	return ;

}

void NGString::append( const NGString& str,size_t start,size_t len )
{
	if(str.empty()||(start>=str.csize))
		return;
	append(str.p_str+start,len);
	
}

int NGString::compare( const char* c_str )
{
	if((c_str==NULL)||(c_str[0]=='\0'))
	{
		if(empty())
			return 0;
		return 1;
	}
	if(empty())
		return -1;
	return strcmp(p_str,c_str);

}

void NGString::toUpper()
{
	if(p_str)
	{
		for(unsigned i=0;i<csize;i++)
			p_str[i] = toupper(p_str[i]);
			
	}
}

void NGString::toLower()
{
	if(p_str)
	{
		for(unsigned i=0;i<csize;i++)
			p_str[i] = tolower(p_str[i]);

	}
}

void NGString::trimLeft()
{
	if(empty())
		return;
	size_t off=0;
	char * p_c = p_str;
	while(*p_c)
	{
		if((*p_c != ' ')
			&&(*p_c != '\t')
			&&(*p_c!= '\r')
			&&(*p_c != '\n'))
			break;
			off ++;
			p_c++;
	}
	//¿Õ×Ö·û
	if(off == csize)
	{
		clear();
		return;
	}
	//
	if(off != 0)
	{
		size_t len = csize-off;
		char * p_temp = new (std::nothrow) char[len+1];
		if(p_temp)
		{
			strcpy(p_temp,p_c);
			delete [] p_str;
			p_str = p_temp;
			csize = len;
		}
	}
}

void NGString::trimRight()
{
	if(empty())
		return;
	size_t off=csize;

	for(size_t i=csize-1;i>=0;i--)
	{
		if((p_str[i] != ' ')
			&&(p_str[i] != '\t')
			&&(p_str[i]!= '\r')
			&&(p_str[i] != '\n'))
		{
			off = i;
			break;
		}
	}
	//¿Õ×Ö·û
	if(off == 0)
	{
		clear();
		return;
	}
	//
	if(off != csize)
	{
		size_t len = off;
		char * p_temp = new (std::nothrow) char[len+1];
		if(p_temp)
		{
			strncpy(p_temp,p_str,len);
			p_temp[len]='\0';
			delete [] p_str;
			p_str = p_temp;
			csize = len;
		}
	}
}

void NGString::trim()
{
	if(empty())
		return;
	int loff = -1;
	int roff = csize;
	for(int i=0;i<csize;i++)
	{
		if((loff==-1)
			&&((p_str[i] != ' ')
			&&(p_str[i] != '\t')
			&&(p_str[i]!= '\r')
			&&(p_str[i] != '\n'))
			)
		{
			loff = i;
		}
		if((roff==csize)
			&&((p_str[csize-i-1] != ' ')
			&&(p_str[csize-i-1] != '\t')
			&&(p_str[csize-i-1]!= '\r')
			&&(p_str[csize-i-1] != '\n'))
			)
		{
			roff= csize-i-1;
		}
		if((loff!=-1)&&(roff!=csize))
			break;
	}

	//no trim
	if((loff == 0)&&(roff == csize-1))
		return;
	// all trim
	if(((loff==-1)||(roff == csize))
		||(roff<loff))
	{
		clear();
		return;
	}
	//part
	const char* p_s = p_str+loff;
	size_t len = roff - loff+1;
	char * p_temp = new (std::nothrow) char[len+1];
	if(p_temp)
	{
		strncpy(p_temp,p_s,len);
		p_temp[len]='\0';
		delete [] p_str;
		p_str = p_temp;
		csize = len;
	}


}




