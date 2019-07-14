/* 该文件定义编码的最通用的一些宏，所有文件都需要包含该文件，优先级最高 */

#ifndef _NG_COMMON_DEFINE_H
#define _NG_COMMON_DEFINE_H


//数据类型重新定义
typedef void NG_VOID;
typedef char NG_UINT8;
typedef short NG_INT16;
typedef unsigned short NG_UINT16;
typedef int NG_INT32;
typedef unsigned int NG_UINT32;
typedef bool NG_BOOL;
typedef double NG_DOUBLE;
typedef float NG_FLOAT32;
typedef long double NG_LONG_DOUBLE;


#define VOS_OK 0
#define VOS_ERR 1
#define NG_TRUE true
#define NG_FALSE false

#define CONTINUE_IF(EXP) 	if(EXP) \
							continue;

#define BREAK_IF(EXP)		if(EXP) \
							break;

#define RETURN_VOID_IF(EXP) if(EXP) \
							return;

#define RETURN_IF(EXP, RET) if(EXP) \
							return (RET); 
						
#define GOTO_IF(EXP, EXIT)  if(EXP) \
							goto EXIT;
							
#define DELETE(pstNew)      if(NULL != pstNew){ \
							delete []pstNew;	\
							pstNew = NULL;}

#define FREE(pstNew)	    if(NULL != pstNew){ \
							free(pstNew);       \
							pstNew = NULL;}

#define FCLOSE(fFile)       if(NULL != fFile){  \
							fclose(fFile);		\
							fFile = NULL;}


#define GetMin2(a,b) ((a) < (b) ? (a) : (b))
#define GetMax2(a,b) ((a) > (b) ? (a) : (b))


/* try-catch 定义 */
#define __TRY NG_UINT32 __errorcode = 0x7FFFFFCC;\
	          NG_UINT32 __errorline = 0x7FFFFFFF;

#define __CATCH __tabErr:

#define ERR_PROC() {__errorline = __LINE__; goto __tabErr;}
#define THROW(errcode) {__errorcode = errcode; ERR_PROC()}
#define THROW_IF(expr, errcode) {if(expr) {THROW(errcode)}}
#define EXEC(func) {if(VOS_OK != (__errorcode = (NG_UINT32)(func))) {ERR_PROC()}}
#define EXEC_ERR(func, errcode) { if(VOS_OK != (func)) {THROW(errcode)}}

#define ERR_CODE (__errorcode)
#define ERR_LINE (__errorline)

#endif