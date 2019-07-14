#ifndef __AESCRYPT_H__
#define __AESCRYPT_H__

#pragma once
#include <stdio.h>

#define _UNIX__
//加密解密返回值
enum AESErrorStatus
{
	AES_Ok							=  0,
	AES_File_OpenError				=  1,
	AES_File_ReadError				=  2,
	AES_File_WriteError				=  3,
	AES_CryptAcquireContextFailed	=  4,
	AES_CryptGenRandomFailed		=  5,
	AES_PassWordIncorrect			=  6,		//密码不正确
	AES_HMACAltered					=  7,		//HMAC验证不正确
	AES_NoData						=  8,
	AES_DeDataError					=  9,
	AES_IVKEYCREATE_FAILED			=  10
};

class CAESCrypt
{
public:
	CAESCrypt();
	~CAESCrypt();

public:
	//对文件进行加密解密
	//加密写入文件
	int EnCrypt_File(const char  *infp, const char   *outfp, const char* passwd, int passlen);
	int EnCrypt_File(FILE *infp, long nFileSize,FILE *outfp, const char* passwd, int passlen);

	//加密写入内存
	int EnCrypt_File(const char  *infp, char *&pOutBuffer,long &BufferLen, const char* passwd, int passlen);
	int EnCrypt_File(FILE *infp, long nFileSize,char *&pOutBuffer,long &BufferLen, const char* passwd, int passlen);

	//解密写入文件
	int DeCrypt_File(const char  *infp, const char   *outfp, const char* passwd, int passlen);
	int DeCrypt_File(FILE *infp, long nFileSize,FILE *outfp, const char* passwd, int passlen);

	//解密写入内存
	int DeCrypt_File(const char  *infp, char *&pOutBuffer,long &BufferLen, const char* passwd, int passlen);
	int DeCrypt_File(FILE *infp, long nFileSize,char *&pOutBuffer,long &BufferLen,const char* passwd, int passlen);

	//对内存进行加密解密
	//加密写入文件
	int EnCrypt_Buffer(const char *pInBuffer,long InBufferLen,
		const char   *outfp, const char* passwd, int passlen);
	int EnCrypt_Buffer(const char *pInBuffer,long InBufferLen,
		FILE *outfp, const char* passwd, int passlen);

	//加密写入内存
	int EnCrypt_Buffer(const char *pInBuffer,long InBufferLen,
		char *&pOutBuffer,long &BufferLen, const char* passwd, int passlen);

	//解密写入文件
	int DeCrypt_Buffer(const char *pInBuffer,long InBufferLen,
		const char   *outfp, const char* passwd, int passlen);
	int DeCrypt_Buffer(const char *pInBuffer,long InBufferLen,
		FILE *outfp, const char* passwd, int passlen);

	//解密写入内存
	int DeCrypt_Buffer(const char *pInBuffer,long InBufferLen,
		char *&pOutBuffer,long &BufferLen, const char* passwd, int passlen);

	//生成随机的IV-key,IV
	bool CreateRandomIVKey(unsigned char IV[16],unsigned char iv_key[48]);

private:
	CAESCrypt(const CAESCrypt &that){}
	CAESCrypt & operator =(const CAESCrypt &that) { return *this;}

public:
	int m_IV_Rounds;
	int m_RandomCounts;				//生成随机数循环次数
	char m_Ipad;
	char m_Opad;

private:
	char *m_pOutBuffer;	//加密解密内存
	long m_OutBufferLen;			//加密解密内存大小
};

#endif // __AESCRYPT_H__


