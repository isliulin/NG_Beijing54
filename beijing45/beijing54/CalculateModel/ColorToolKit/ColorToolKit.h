/*��ɫ������
2013.5.23 jjj
*/
#ifndef __COLOR_TOOLKIT__H__
#define __COLOR_TOOLKIT__H__

#ifndef _WINDOWS_
#define _WINDOWS_
	#ifndef _MSC_VER
		// define portable types for 32-bit / 64-bit OS
		#include <inttypes.h>
		typedef uint8_t BYTE;
		typedef uint16_t WORD;
		typedef uint32_t DWORD;
	#else
		// MS is not C99 ISO compliant
		typedef unsigned char BYTE;
		typedef unsigned short WORD;
		typedef unsigned long DWORD;
	#endif // _MSC_VER
#endif

//COLORREF ����ֽ�:a ����ֽ�:r
typedef DWORD   COLORGBA;

#ifndef RGB
#define RGB(r,g,b)          ((COLORGBA)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

#ifndef RGBA
#define RGBA(r,g,b,a)       ((COLORGBA)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
#endif

#ifndef LOBYTE
#define LOBYTE(w)           ((BYTE)(((DWORD)(w)) & 0xff))
#endif

#ifndef GetRValue
#define GetRValue(rgb)      (LOBYTE(rgb))
#endif

#ifndef GetGValue
#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
#endif

#ifndef GetBValue
#define GetBValue(rgb)      (LOBYTE((rgb)>>16))
#endif

#ifndef GetAValue
#define  GetAValue(rgba)	(LOBYTE((rgba)>>24))
#endif

//��ɫ˵������
enum {MAX_COLOR_INFO = 128};

typedef struct tagContinuColor
{
	double data_min;				//������Сֵ,���� ����Ϊ [,)  data_min<= data < data_max
	double data_max;				//�������ֵ
	COLORGBA ColorRGB;				//�������Ӧ��RGB��ɫ
}ContinuColor;

#endif   /* __COLOR_TOOLKIT__H__ */