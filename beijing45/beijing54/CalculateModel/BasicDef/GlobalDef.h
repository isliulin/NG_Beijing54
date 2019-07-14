#ifndef __BASICDEF_GLOBALDEFINE_h
#define __BASICDEF_GLOBALDEFINE_h

#include <assert.h>
#include <string>

#include <float.h>
#include <iostream>
#include <math.h>
#include "MacroDef.h"
#include <time.h>

typedef unsigned char u_char;

typedef signed char s_char;

//! 32 bit Unsigned int definition
typedef unsigned int u_int4;
//! 16 bit unsigned int
typedef unsigned short int u_int2;
typedef signed short int s_int2;
//! 32 bit int definition
typedef int          s_int4;

//不能更改已有的，否则文件读出来的有问题
typedef enum NGDataInterpretationType
{
	NG_UNKNOWN_DATATYPE = 0,
	NG_INT,    //等同于NG_INT4
	NG_CHAR,  // this is an unsigned char u_char
	NG_SIGNED_CHAR,//s_char
	NG_UINT2,// u_int2
	NG_UINT4,//u_int4
	NG_INT2, //s_int2
	NG_INT4,// s_int4
	NG_ARRAY, // some kind of array
	NG_FLOAT
};


#define __new new//new(__FILE__,__LINE__)

#define _cond_delete_array(what) if (what) delete[] what; what=0;
#define _cond_delete(what) if (what) delete what; what=0;

inline void NGGlobal_StrCpy(char*& dest, const char* source)
{
	int nLen = strlen(source)+1;
	dest =  new char[nLen];
	//strcpy_s(dest, strlen(source)+1,source);	Linux下没有strcpy_s函数
	strcpy(dest, source);
}

inline void NGGlobal_StrCat(char*& dest, const char* to_add)
{
	char* temp = dest;
	int nLen = strlen(temp)+strlen(to_add)+1;
	dest =  new char[nLen];
	//strcpy_s(dest, strlen(temp)+strlen(to_add)+1,temp);
	strcpy(dest, temp);
	strcat(dest, to_add);
	delete[] temp;
}

double CalNFresnelZoneRadius(double dtm, double drm, int n, double freqMhz)
{
	double rf = 0;
	// Convert the unit MHZ to HZ
	freqMhz = freqMhz * 1000000;

	rf = sqrt(CLIGHT * n * drm * dtm / (2 * freqMhz * (drm + dtm)));
	return rf;
}
void UnicodeToUTF_8(char* pOut,wchar_t* pText)
{

	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后

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
char* GetLocTime()
{
	time_t rawtime;
	time(&rawtime);

	char*pTime = ctime(&rawtime);
	int nLen = strlen(pTime);
	pTime[nLen-1] = 0;
	return pTime;
}
#endif
