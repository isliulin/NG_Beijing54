#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#if defined(_WIN32) || defined(__WIN32__)
#define _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#include <WinCrypt.h>
#include <io.h>
#pragma warning(disable:4996)
#else
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h> // getopt
#include <assert.h>
#include <stdlib.h> // malloc
#include <time.h> // time
#endif

#include "aes.h"
#include "sha256.h"
#include "AESCrypt.h"

typedef struct
{
	char aes[3];
	char version;
	char last_block_size;
} aescrypt_hdr;

typedef unsigned char sha256_t[32];


long getFileSize(const char *path)
{
	long fileSize = 0;
	struct stat statBuff;
	if (stat(path, &statBuff) == 0)
	{
		fileSize = statBuff.st_size;
	}
	return fileSize;
}

CAESCrypt::CAESCrypt()
{
	m_IV_Rounds = 4096;
	m_RandomCounts = 512;

	m_Ipad = 0X39;
	m_Opad = 0X5C;

	m_pOutBuffer = NULL;
	m_OutBufferLen = 0;
}

CAESCrypt::~CAESCrypt()
{
	if (m_pOutBuffer != NULL)
		delete []m_pOutBuffer;
}

//生成随机数IV,IV-key
#if defined(_WIN32) || defined(__WIN32__)
bool CAESCrypt::CreateRandomIVKey(unsigned 	char IV[16],unsigned char iv_key[48])
{
	sha256_context              sha_ctx;
	sha256_t                    digest;
	int                         i, j;
	unsigned char               buffer[32];
	HCRYPTPROV                  hProv;
	DWORD                       result_code;
	// Prepare for random number generation
	if (!CryptAcquireContext(&hProv,NULL,NULL,PROV_RSA_FULL,CRYPT_VERIFYCONTEXT))
	{
		result_code = GetLastError();
		if (GetLastError() == NTE_BAD_KEYSET)
		{
			if (!CryptAcquireContext(&hProv,NULL,NULL,PROV_RSA_FULL,CRYPT_NEWKEYSET|CRYPT_VERIFYCONTEXT))
			{
				result_code = GetLastError();
			}
			else
			{
				result_code = ERROR_SUCCESS;
			}
		}

		if (result_code != ERROR_SUCCESS)
		{
			fprintf(stderr, "Could not acquire handle to crypto context");
			return false;
		}
	}

	//生成48字节的随机数iv_key
	memset(iv_key, 0, 48);
	for (i=0; i<48; i+=16)
	{
		memset(buffer, 0, 32);
		sha256_starts(&sha_ctx);
		for(j=0; j<m_RandomCounts; j++)
		{
			if (!CryptGenRandom(hProv,32,(BYTE *) buffer))
			{
				fprintf(stderr, "Windows is unable to generate random digits");
				return false;
			}
			sha256_update(&sha_ctx, buffer, 32);
		}
		sha256_finish(&sha_ctx, digest);
		memcpy(iv_key+i, digest, 16);
	}

	//生成16字节的随机数IV
	// Create a random IV
	sha256_starts(  &sha_ctx);

	for (i=0; i<m_RandomCounts; i++)
	{
		if (!CryptGenRandom(hProv,
			32,
			(BYTE *) buffer))
		{
			fprintf(stderr, "Windows is unable to generate random digits");
			CryptReleaseContext(hProv, 0);
			return  false;
		}
		sha256_update(  &sha_ctx,
			buffer,
			32);
	}

	sha256_finish(  &sha_ctx, digest);

	memcpy(IV, digest, 16);

	// We're finished collecting random data
	CryptReleaseContext(hProv, 0);

	return true;
}
#else
bool CAESCrypt::CreateRandomIVKey(unsigned char IV[16],unsigned char iv_key[48])
{
	sha256_context              sha_ctx;
	sha256_t                    digest;
	int                         i, j, n;
	unsigned char               buffer[32];
	time_t                      current_time;
	pid_t                       process_id;
	FILE                        *randfp = NULL;

	// Open the source for random data.  Note that while the entropy
	// might be lower with /dev/urandom than /dev/random, it will not
	// fail to produce something.  Also, we're going to hash the result
	// anyway.
	if ((randfp = fopen("/dev/urandom", "r")) == NULL)
	{
		perror("Error open /dev/urandom:");
		return  false;
	}

	// Create the 16-octet IV and 32-octet encryption key
	// used for encrypting the plaintext file.  We do
	// not trust the rand() function, so we improve on
	// that by also hashing the random digits and using
	// only a portion of the hash.  This IV and key
	// generation could be replaced with any good random
	// source of data.
	memset(iv_key, 0, 48);
	for (i=0; i<48; i+=16)
	{
		memset(buffer, 0, 32);
		sha256_starts(&sha_ctx);
		for(j=0; j<m_RandomCounts; j++)
		{
			if ((n = fread(buffer, 1, 32, randfp)) != 32)
			{
				fprintf(stderr, "Error: Couldn't read from /dev/urandom : %d\n",n);
				fclose(randfp);
				return  false;
			}
			sha256_update(&sha_ctx, buffer, 32);
		}
		sha256_finish(&sha_ctx, digest);
		memcpy(iv_key+i, digest, 16);
	}

	// We will use an initialization vector comprised of the current time
	// process ID, and random data, all hashed together with SHA-256.
	current_time = time(NULL);
	for(i = 0; i < 8; i++)
	{
		buffer[i] = (char)
			(current_time >> (i * 8));
	}
	process_id = getpid();
	for(i = 0; i < 8; i++)
	{
		buffer[i+8] = (char)
			(process_id >> (i * 8));
	}

	sha256_starts(  &sha_ctx);
	sha256_update(  &sha_ctx, buffer, 16);

	for (i=0; i<m_RandomCounts; i++)
	{
		if (fread(buffer, 1, 32, randfp) != 32)
		{
			fprintf(stderr, "Error: Couldn't read from /dev/random\n");
			fclose(randfp);
			return  false;
		}
		sha256_update(  &sha_ctx,
			buffer,
			32);
	}

	sha256_finish(  &sha_ctx, digest);

	memcpy(IV, digest, 16);

	// We're finished collecting random data
	fclose(randfp);

	return true;
}
#endif

int CAESCrypt::EnCrypt_File(const char  *infp, const char   *outfp, const char* passwd, int passlen)
{
	unsigned long nFileSize = getFileSize(infp);

	FILE *pinfp = fopen(infp, "rb");
	if (pinfp == NULL)
		return AES_File_OpenError;

	FILE *pOutfp = fopen(outfp, "wb");
	if (pOutfp == NULL)
	{
		fclose(pinfp);
		return AES_File_OpenError;
	}

	int Ret = EnCrypt_File(pinfp,nFileSize,pOutfp,passwd,passlen);

	fclose(pinfp);
	fclose(pOutfp);

	return Ret;
}

int CAESCrypt::DeCrypt_File(const char  *infp, const char   *outfp, const char* passwd, int passlen)
{
	unsigned long nFileSize = getFileSize(infp);

	FILE *pinfp = fopen(infp, "rb");
	if (pinfp == NULL)
		return AES_File_OpenError;

	FILE *pOutfp = fopen(outfp, "wb");
	if (pOutfp == NULL)
	{
		fclose(pinfp);
		return AES_File_OpenError;
	}

	int Ret = DeCrypt_File(pinfp,nFileSize,pOutfp,passwd,passlen);

	fclose(pinfp);
	fclose(pOutfp);

	return Ret;
}

int CAESCrypt::EnCrypt_File(FILE *infp, long nFileSize,FILE *outfp, const char* passwd, int passlen)
{
	aes_context                 aes_ctx;
	sha256_context              sha_ctx;
	aescrypt_hdr                aeshdr;
	sha256_t                    digest;
	unsigned char               IV[16];
	unsigned char               iv_key[48];
	int                         i, j, n;
	unsigned char               buffer[32];
	unsigned char               ipad[64], opad[64];

	if (nFileSize == 0)
	{
		fclose(infp);
		return AES_NoData;	//文件没有内容,不予加密
	}
	//随机数IV,IV-key生成失败,返回
	if (!CreateRandomIVKey(IV,iv_key))
	{
		return AES_IVKEYCREATE_FAILED;
	}

	//写入随机数IV
	// Write the initialization vector to the file
	if (fwrite(IV, 1, 16, outfp) != 16)
	{
		fprintf(stderr, "Error: Could not write out initialization vector\n");
		return  AES_File_WriteError;
	}

	//由IV和用户密码生成key,设其名称为 key1
	// Hash the IV and password 8192 times
	memset(digest, 0, 32);
	memcpy(digest, IV, 16);
	for(i=0; i<m_IV_Rounds; i++)
	{
		sha256_starts(&sha_ctx);
		sha256_update(&sha_ctx, digest, 32);
		sha256_update(&sha_ctx,(unsigned char*)passwd,(unsigned long)passlen);
		sha256_finish(&sha_ctx,digest);
	}

	//设置key1
	// Set the AES encryption key
	aes_set_key(&aes_ctx, digest, 256);

	// Set the ipad and opad arrays with values as
	// per RFC 2104 (HMAC).  HMAC is defined as
	//   H(K XOR opad, H(K XOR ipad, text))
	memset(ipad, m_Ipad, 64);
	memset(opad, m_Opad, 64);

	for(i=0; i<32; i++)
	{
		ipad[i] ^= digest[i];
		opad[i] ^= digest[i];
	}

	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, ipad, 64);

	//对48字节的iv_key使用key1来加密,写入文件
	// Encrypt the IV and key used to encrypt the plaintext file,
	// writing that encrypted text to the output file.
	for(i=0; i<48; i+=16)
	{
		// Place the next 16 octets of IV and key buffer into
		// the input buffer.
		memcpy(buffer, iv_key+i, 16);

		// XOR plain text block with previous encrypted
		// output (i.e., use CBC)
		for(j=0; j<16; j++)
		{
			buffer[j] ^= IV[j];
		}

		// Encrypt the contents of the buffer
		aes_encrypt(&aes_ctx, buffer, buffer);

		// Concatenate the "text" as we compute the HMAC
		sha256_update(&sha_ctx, buffer, 16);

		// Write the encrypted block
		if (fwrite(buffer, 1, 16, outfp) != 16)
		{
			fprintf(stderr, "Error: Could not write iv_key data\n");
			return  AES_File_WriteError;
		}

		// Update the IV (CBC mode)
		memcpy(IV, buffer, 16);
	}

	//在要加密内容之前写入HMAC
	// Write the HMAC
	sha256_finish(&sha_ctx, digest);
	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, opad, 64);
	sha256_update(&sha_ctx, digest, 32);
	sha256_finish(&sha_ctx, digest);
	// Write the encrypted block
	if (fwrite(digest, 1, 32, outfp) != 32)
	{
		fprintf(stderr, "Error: Could not write iv_key HMAC\n");
		return  AES_File_WriteError;
	}

	// Re-load the IV and encryption key with the IV and
	// key to now encrypt the datafile.  Also, reset the HMAC
	// computation.
	memcpy(IV, iv_key, 16);

	// Set the AES encryption key
	aes_set_key(&aes_ctx, iv_key+16, 256);

	// Set the ipad and opad arrays with values as
	// per RFC 2104 (HMAC).  HMAC is defined as
	//   H(K XOR opad, H(K XOR ipad, text))
	memset(ipad, m_Ipad/*0x36*/, 64);
	memset(opad, m_Opad/*0x5C*/, 64);

	for(i=0; i<32; i++)
	{
		ipad[i] ^= iv_key[i+16];
		opad[i] ^= iv_key[i+16];
	}

	// Wipe the IV and encryption mey from memory
	memset(iv_key, 0, 48);

	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, ipad, 64);

	aeshdr.last_block_size = 0;		//需要初始化为0
	//16位字节循环加密
	while ((n = (int)fread(buffer, 1, 16, infp)) > 0)
	{
		// XOR plain text block with previous encrypted
		// output (i.e., use CBC)
		for(i=0; i<16; i++)
		{
			buffer[i] ^= IV[i];
		}

		// Encrypt the contents of the buffer
		//数据加密
		aes_encrypt(&aes_ctx, buffer, buffer);

		// Concatenate the "text" as we compute the HMAC
		sha256_update(&sha_ctx, buffer, 16);

		// Write the encrypted block
		if (fwrite(buffer, 1, 16, outfp) != 16)
		{
			fprintf(stderr, "Error: Could not write to output file\n");
			return  AES_File_WriteError;
		}

		// Update the IV (CBC mode)
		//将上一次的要加密数据作为下一次加密的输入参数
		//这样只有正确解密了上一次的数据,下一次的解密才能正常进行
		memcpy(IV, buffer, 16);

		// Assume this number of octets is the file modulo
		//最后一次加密的内容可能小于16字节,这里记录其字节数
		aeshdr.last_block_size = n;
	}

	// Check to see if we had a read error
	if (n < 0)
	{
		fprintf(stderr, "Error: Couldn't read input file\n");
		return  AES_File_ReadError;
	}

	//将最后一次加密的数据字节数<=16写入文件
	// Write the file size modulo
	buffer[0] = (char) (aeshdr.last_block_size & 0x0F);
	if (fwrite(buffer, 1, 1, outfp) != 1)
	{
		fprintf(stderr, "Error: Could not write the file size modulo\n");
		return  AES_File_WriteError;
	}

	//要加密内容之后再写入HMAC
	// Write the HMAC
	sha256_finish(&sha_ctx, digest);
	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, opad, 64);
	sha256_update(&sha_ctx, digest, 32);
	sha256_finish(&sha_ctx, digest);
	if (fwrite(digest, 1, 32, outfp) != 32)
	{
		fprintf(stderr, "Error: Could not write the file HMAC\n");
		return  AES_File_WriteError;
	}

	return AES_Ok;
}

int CAESCrypt::EnCrypt_File(const char  *infp,char *&pOutBuffer,long &BufferLen, const char* passwd, int passlen)
{
	unsigned long nFileSize = getFileSize(infp);

	FILE *pinfp = fopen(infp, "rb");
	if (pinfp == NULL)
		return AES_File_OpenError;

	int Ret = EnCrypt_File(pinfp,nFileSize,pOutBuffer,BufferLen,passwd,passlen);

	fclose(pinfp);

	return Ret;
}
int CAESCrypt::EnCrypt_File(FILE *infp, long nFileSize,char *&pOutBuffer,long &BufferLen, const char* passwd, int passlen)
{
	aes_context                 aes_ctx;
	sha256_context              sha_ctx;
	aescrypt_hdr                aeshdr;
	sha256_t                    digest;
	unsigned char               IV[16];
	unsigned char               iv_key[48];
	int                         i, j, n;
	unsigned char               buffer[32];
	unsigned char               ipad[64], opad[64];

	if (nFileSize == 0)
	{
		fclose(infp);
		return AES_NoData;	//文件没有内容,不予加密
	}
	//随机数IV,IV-key生成失败,返回
	if (!CreateRandomIVKey(IV,iv_key))
	{
		return AES_IVKEYCREATE_FAILED;
	}

	//计算内存大小
	long InfileBytes = nFileSize;

	long EnRows = InfileBytes/16;		//加密行数,每一次加密16字节
	if (InfileBytes%16 != 0)
		EnRows ++ ;

	//加密文件总的大小
	//16			IV
	//48			iv_key 加密后数据
	//32			文件头HMAC
	//EnRows*16		文件加密内容
	//1				文件最后一个字节给出最后一行要加密的字符个数
	//32			文件结尾HMAC
	long nAesBytes = 16+48+32+1+32;		//非文件内容
	long AllOutBufferLen = nAesBytes+EnRows*16;

	if (m_pOutBuffer == NULL)
	{
		m_pOutBuffer = new char [AllOutBufferLen];
		m_OutBufferLen = AllOutBufferLen;
		memset(m_pOutBuffer,0,m_OutBufferLen);
	}
	else
	{
		if (m_OutBufferLen < AllOutBufferLen)
		{
			delete []m_pOutBuffer;

			m_pOutBuffer = new char [AllOutBufferLen];
			m_OutBufferLen = AllOutBufferLen;
			memset(m_pOutBuffer,0,m_OutBufferLen);
		}
	}

	char *pWriteBuffer = m_pOutBuffer;

	//1.写入随机数IV
	memcpy(pWriteBuffer,IV,16);
	pWriteBuffer += 16;

	//由IV和用户密码生成key,设其名称为 key1
	// Hash the IV and password 8192 times
	memset(digest, 0, 32);
	memcpy(digest, IV, 16);
	for(i=0; i<m_IV_Rounds; i++)
	{
		sha256_starts(&sha_ctx);
		sha256_update(&sha_ctx, digest, 32);
		sha256_update(&sha_ctx,(unsigned char*)passwd,(unsigned long)passlen);
		sha256_finish(&sha_ctx,digest);
	}

	//设置key1
	// Set the AES encryption key
	aes_set_key(&aes_ctx, digest, 256);

	// Set the ipad and opad arrays with values as
	// per RFC 2104 (HMAC).  HMAC is defined as
	//   H(K XOR opad, H(K XOR ipad, text))
	memset(ipad, m_Ipad, 64);
	memset(opad, m_Opad, 64);

	for(i=0; i<32; i++)
	{
		ipad[i] ^= digest[i];
		opad[i] ^= digest[i];
	}

	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, ipad, 64);

	//对48字节的iv_key使用key1来加密,写入文件
	// Encrypt the IV and key used to encrypt the plaintext file,
	// writing that encrypted text to the output file.
	for(i=0; i<48; i+=16)
	{
		// Place the next 16 octets of IV and key buffer into
		// the input buffer.
		memcpy(buffer, iv_key+i, 16);

		// XOR plain text block with previous encrypted
		// output (i.e., use CBC)
		for(j=0; j<16; j++)
		{
			buffer[j] ^= IV[j];
		}

		// Encrypt the contents of the buffer
		aes_encrypt(&aes_ctx, buffer, buffer);

		// Concatenate the "text" as we compute the HMAC
		sha256_update(&sha_ctx, buffer, 16);

		//2.写入iv_key加密后的数据
		// Write the encrypted block
		memcpy(pWriteBuffer,buffer,16);
		pWriteBuffer += 16;

		// Update the IV (CBC mode)
		memcpy(IV, buffer, 16);
	}

	//在要加密内容之前写入HMAC
	// Write the HMAC
	sha256_finish(&sha_ctx, digest);
	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, opad, 64);
	sha256_update(&sha_ctx, digest, 32);
	sha256_finish(&sha_ctx, digest);

	//3.写入文件头 HMAC
	// Write the encrypted block
	memcpy(pWriteBuffer,digest,32);
	pWriteBuffer += 32;

	// Re-load the IV and encryption key with the IV and
	// key to now encrypt the datafile.  Also, reset the HMAC
	// computation.
	memcpy(IV, iv_key, 16);

	// Set the AES encryption key
	aes_set_key(&aes_ctx, iv_key+16, 256);

	// Set the ipad and opad arrays with values as
	// per RFC 2104 (HMAC).  HMAC is defined as
	//   H(K XOR opad, H(K XOR ipad, text))
	memset(ipad, m_Ipad/*0x36*/, 64);
	memset(opad, m_Opad/*0x5C*/, 64);

	for(i=0; i<32; i++)
	{
		ipad[i] ^= iv_key[i+16];
		opad[i] ^= iv_key[i+16];
	}

	// Wipe the IV and encryption mey from memory
	memset(iv_key, 0, 48);

	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, ipad, 64);

	aeshdr.last_block_size = 0;		//需要初始化为0

	//16位字节循环加密
	long RowIndex = 0;
	while ((n = (int)fread(buffer, 1, 16, infp)) > 0)
	{
		// XOR plain text block with previous encrypted
		// output (i.e., use CBC)
		for(i=0; i<16; i++)
		{
			buffer[i] ^= IV[i];
		}

		// Encrypt the contents of the buffer
		//数据加密
		aes_encrypt(&aes_ctx, buffer, buffer);

		// Concatenate the "text" as we compute the HMAC
		sha256_update(&sha_ctx, buffer, 16);

		//4.文件16字节加密存储
		// Write the encrypted block
		memcpy(pWriteBuffer,buffer,16);
		pWriteBuffer += 16;

		// Update the IV (CBC mode)
		//将上一次的要加密数据作为下一次加密的输入参数
		//这样只有正确解密了上一次的数据,下一次的解密才能正常进行
		memcpy(IV, buffer, 16);

		// Assume this number of octets is the file modulo
		//最后一次加密的内容可能小于16字节,这里记录其字节数
		aeshdr.last_block_size = n;

		RowIndex ++ ;
		if (RowIndex >= EnRows)
			break;
	}

	// Check to see if we had a read error
	if (n < 0)
	{
		fprintf(stderr, "Error: Couldn't read input file\n");
		return  AES_File_ReadError;
	}

	//5.将最后一次加密的数据字节数<=16写入文件
	// Write the file size modulo
	buffer[0] = (char) (aeshdr.last_block_size & 0x0F);
	memcpy(pWriteBuffer,buffer,1);
	pWriteBuffer += 1;

	//6.要加密内容之后再写入HMAC
	// Write the HMAC
	sha256_finish(&sha_ctx, digest);
	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, opad, 64);
	sha256_update(&sha_ctx, digest, 32);
	sha256_finish(&sha_ctx, digest);

	memcpy(pWriteBuffer,digest,32);

	//给外部使用
	pOutBuffer = m_pOutBuffer;
	BufferLen = m_OutBufferLen;

	return AES_Ok;
}

int CAESCrypt::DeCrypt_File(FILE *infp, long nFileSize,FILE *outfp, const char* passwd, int passlen)
{
	aes_context                 aes_ctx;
	sha256_context              sha_ctx;
	aescrypt_hdr                aeshdr;
	sha256_t                    digest;
	unsigned char               IV[16];
	unsigned char               iv_key[48];
	int                         i, j, n, bytes_read;
	unsigned char               buffer[64], buffer2[32];
	unsigned char               *head, *tail;
	unsigned char               ipad[64], opad[64];
	int                         reached_eof = 0;

	//读取IV(16字节)
	// Read the initialization vector from the file
	if ((bytes_read = (int) fread(IV, 1, 16, infp)) != 16)
	{
		if (feof(infp))
		{
			fprintf(stderr, "Error: Input file is too short.\n");
		}
		else
		{
			perror("Error reading the initialization vector:");
		}
		return  AES_File_ReadError;
	}

	//通过IV和用户输入密码来逆运算出key
	memset(digest, 0, 32);
	memcpy(digest, IV, 16);
	for(i=0; i<m_IV_Rounds; i++)
	{
		sha256_starts(  &sha_ctx);
		sha256_update(  &sha_ctx, digest, 32);
		sha256_update(  &sha_ctx,
			(unsigned char*)passwd,
			(unsigned long)passlen);
		sha256_finish(  &sha_ctx,
			digest);
	}

	//设置由IV和用户输入密码生成的key,设其名称为 key1
	// Set the AES encryption key
	aes_set_key(&aes_ctx, digest, 256);

	// Set the ipad and opad arrays with values as
	// per RFC 2104 (HMAC).  HMAC is defined as
	//   H(K XOR opad, H(K XOR ipad, text))
	memset(ipad, m_Ipad, 64);
	memset(opad, m_Opad, 64);

	for(i=0; i<32; i++)
	{
		ipad[i] ^= digest[i];
		opad[i] ^= digest[i];
	}

	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, ipad, 64);

	//读取48字节的数据,该48字节数据由iv_key被 key1加密后的数据
	//解密后得到iv_key
	{
		for(i=0; i<48; i+=16)
		{
			if ((bytes_read = (int) fread(buffer, 1, 16, infp)) != 16)
			{
				if (feof(infp))
				{
					fprintf(stderr, "Error: Input file is too short.\n");
				}
				else
				{
					perror("Error reading input file IV and key:");
				}
				return  AES_File_ReadError;
			}

			memcpy(buffer2, buffer, 16);

			sha256_update(&sha_ctx, buffer, 16);
			aes_decrypt(&aes_ctx, buffer, buffer);

			// XOR plain text block with previous encrypted
			// output (i.e., use CBC)
			for(j=0; j<16; j++)
			{
				iv_key[i+j] = (buffer[j] ^ IV[j]);
			}

			// Update the IV (CBC mode)
			memcpy(IV, buffer2, 16);
		}

		// Verify that the HMAC is correct
		sha256_finish(&sha_ctx, digest);
		sha256_starts(&sha_ctx);
		sha256_update(&sha_ctx, opad, 64);
		sha256_update(&sha_ctx, digest, 32);
		sha256_finish(&sha_ctx, digest);

		if ((bytes_read = (int) fread(buffer, 1, 32, infp)) != 32)
		{
			if (feof(infp))
			{
				fprintf(stderr, "Error: Input file is too short.\n");
			}
			else
			{
				perror("Error reading input file digest:");
			}
			return  AES_File_ReadError;
		}

		//读取的digest和计算的digest比较
		if (memcmp(digest, buffer, 32))
		{
			fprintf(stderr, "Error: Message has been altered or password is incorrect\n");
			return  AES_PassWordIncorrect;
		}

		// Re-load the IV and encryption key with the IV and
		// key to now encrypt the datafile.  Also, reset the HMAC
		// computation.
		memcpy(IV, iv_key, 16);

		//文件内容解密,使用的key为iv_key的后32个字节,设其名称为key2
		// Set the AES encryption key
		aes_set_key(&aes_ctx, iv_key+16, 256);

		// Set the ipad and opad arrays with values as
		// per RFC 2104 (HMAC).  HMAC is defined as
		//   H(K XOR opad, H(K XOR ipad, text))
		memset(ipad, m_Ipad/*0x36*/, 64);
		memset(opad, m_Opad/*0x5C*/, 64);

		for(i=0; i<32; i++)
		{
			ipad[i] ^= iv_key[i+16];
			opad[i] ^= iv_key[i+16];
		}

		// Wipe the IV and encryption mey from memory
		memset(iv_key, 0, 48);

		sha256_starts(&sha_ctx);
		sha256_update(&sha_ctx, ipad, 64);
	}

	//文件内容解密,使用的key为iv_key的后32个字节,即key2
	// Decrypt the balance of the file

	// Attempt to initialize the ring buffer with contents from the file.
	// Attempt to read 48 octets of the file into the ring buffer.
	//先读取48字节,如果小于48字节，说明没有加密数据,不需要解密
	if ((bytes_read = (int) fread(buffer, 1, 48, infp)) < 48)
	{
		if (!feof(infp))
		{
			perror("Error reading input file ring:");
			return  AES_File_ReadError;
		}
		else
		{
			// If there are less than 48 octets, the only valid count
			// is 32 for version 0 (HMAC) and 33 for version 1 or
			// greater files ( file size modulo + HMAC)
			//没有加密数据,则读取的内容必须为33字节,32字节的结尾 HMAC,1字节的最后一个加密内容大小
			if (bytes_read != 33)
			{
				fprintf(stderr, "Error: Input file is corrupt (1:%d).\n",
					bytes_read);
				return AES_File_ReadError;
			}
			else
			{
				// The first octet must be the indicator of the
				// last block size.
				aeshdr.last_block_size = (buffer[0] & 0x0F);

				// If this initial read indicates there is no encrypted
				// data, then there should be 0 in the last_block_size field
				//没有加密内容,则aeshdr.last_block_size应该为0
				if (aeshdr.last_block_size != 0)
				{
					fprintf(stderr, "Error: Input file is corrupt (2).\n");
					return AES_File_ReadError;
				}
			}
			reached_eof = 1;	//没有需要解密的内容,则设置文件读取完毕标志
		}
	}


	head = buffer + 48;
	tail = buffer;

	while(!reached_eof)			//如果有加密的数据,则数据至少为32+1+16=49字节
	{
		// Check to see if the head of the buffer is past the ring buffer
		if (head == (buffer + 64))
		{
			head = buffer;
		}

		//读取的内容小于16字节,说明是最后一次要加密的内容
		if ((bytes_read = (int) fread(head, 1, 16, infp)) < 16)
		{
			if (!feof(infp))
			{
				perror("Error reading input file:");
				return  AES_File_ReadError;
			}
			else
			{
				if ((tail + 16) < (buffer + 64))
				{
					aeshdr.last_block_size = (tail[16] & 0x0F);
				}
				else
				{
					aeshdr.last_block_size = (buffer[0] & 0x0F);
				}

				// Indicate that we've reached the end of the file
				reached_eof = 1;	//读取
			}
		}

		// Process data that has been read.  Note that if the last
		// read operation returned no additional data, there is still
		// one one ciphertext block for us to process if this is a v0 file.
		if ((bytes_read > 0))
		{
			// Advance the head of the buffer forward
			head += 16;

			memcpy(buffer2, tail, 16);

			sha256_update(&sha_ctx, tail, 16);

			//解密
			aes_decrypt(&aes_ctx, tail, tail);

			// XOR plain text block with previous encrypted
			// output (i.e., use CBC)
			for(i=0; i<16; i++)
			{
				tail[i] ^= IV[i];
			}

			// Update the IV (CBC mode)
			memcpy(IV, buffer2, 16);

			// If this is the final block, then we may
			// write less than 16 octets
			//实际加密数据的长度,如果到达文件结尾,则 n == aeshdr.last_block_size
			n = ((!reached_eof) || (aeshdr.last_block_size == 0)) ? 16 : aeshdr.last_block_size;

			// Write the decrypted block
			if ((i = (int) fwrite(tail, 1, n, outfp)) != n)
			{
				perror("Error writing decrypted block:");
				return  AES_File_WriteError;
			}

			// Move the tail of the ring buffer forward
			tail += 16;
			if (tail == (buffer+64))
			{
				tail = buffer;
			}
		}
	}

	//检验加密之后的数据是否正确
	// Verify that the HMAC is correct
	sha256_finish(&sha_ctx, digest);
	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, opad, 64);
	sha256_update(&sha_ctx, digest, 32);
	sha256_finish(&sha_ctx, digest);

	// Copy the HMAC read from the file into buffer2
	memcpy(buffer2, tail+1, 15);
	tail += 16;
	if (tail == (buffer + 64))
	{
		tail = buffer;
	}
	memcpy(buffer2+15, tail, 16);
	tail += 16;
	if (tail == (buffer + 64))
	{
		tail = buffer;
	}
	memcpy(buffer2+31, tail, 1);

	if (memcmp(digest, buffer2, 32))
	{
		fprintf(stderr, "Error: Message has been altered and should not be trusted\n");

		return AES_HMACAltered;
	}

	return AES_Ok;
}


int CAESCrypt::DeCrypt_File(const char  *infp, char *&pOutBuffer,long &BufferLen, const char* passwd, int passlen)
{
	unsigned long nFileSize = getFileSize(infp);

	FILE *pinfp = fopen(infp, "rb");
	if (pinfp == NULL)
		return AES_File_OpenError;

	int Ret = DeCrypt_File(pinfp,nFileSize,pOutBuffer,BufferLen,passwd,passlen);

	fclose(pinfp);

	return Ret;
}

int CAESCrypt::DeCrypt_File(FILE *infp, long nFileSize,char *&pOutBuffer,long &BufferLen,const char* passwd, int passlen)
{
	aes_context                 aes_ctx;
	sha256_context              sha_ctx;
	aescrypt_hdr                aeshdr;
	sha256_t                    digest;
	unsigned char               IV[16];
	unsigned char               iv_key[48];
	int                         i, j, n, bytes_read;
	unsigned char               buffer[64], buffer2[32];
	unsigned char               *head, *tail;
	unsigned char               ipad[64], opad[64];
	int                         reached_eof = 0;

	//加密文件总的大小
	//16			IV
	//48			iv_key 加密后数据
	//32			文件头HMAC
	//EnRows*16		文件加密内容
	//1				文件最后一个字节给出最后一行要加密的字符个数
	//32			文件结尾HMAC
	long nAesBytes = 16+48+32+1+32;		//非文件内容

	//计算内存大小
	long InfileBytes = nFileSize;
	if (InfileBytes < nAesBytes)	//文件不正确
		return AES_File_ReadError;

	long AllOutBufferLen = InfileBytes-nAesBytes;	//加密行数据
	long DeRows = AllOutBufferLen/16;				//加密行数,每一次加密16字节
	if (AllOutBufferLen%16 != 0)					//文件加密字节总数为16字节整数倍
		return AES_File_ReadError;

	if (m_pOutBuffer == NULL)
	{
		m_pOutBuffer = new char [AllOutBufferLen];
		m_OutBufferLen = AllOutBufferLen;
		memset(m_pOutBuffer,0,m_OutBufferLen);
	}
	else
	{
		if (m_OutBufferLen < AllOutBufferLen)
		{
			delete []m_pOutBuffer;

			m_pOutBuffer = new char [AllOutBufferLen];
			m_OutBufferLen = AllOutBufferLen;
			memset(m_pOutBuffer,0,m_OutBufferLen);
		}
	}

	char *pWriteBuffer = m_pOutBuffer;

	//读取IV(16字节)
	// Read the initialization vector from the file
	if ((bytes_read = (int) fread(IV, 1, 16, infp)) != 16)
	{
		if (feof(infp))
		{
			fprintf(stderr, "Error: Input file is too short.\n");
		}
		else
		{
			perror("Error reading the initialization vector:");
		}
		return  AES_File_ReadError;
	}

	//通过IV和用户输入密码来逆运算出key
	memset(digest, 0, 32);
	memcpy(digest, IV, 16);
	for(i=0; i<m_IV_Rounds; i++)
	{
		sha256_starts(  &sha_ctx);
		sha256_update(  &sha_ctx, digest, 32);
		sha256_update(  &sha_ctx,
			(unsigned char*)passwd,
			(unsigned long)passlen);
		sha256_finish(  &sha_ctx,
			digest);
	}

	//设置由IV和用户输入密码生成的key,设其名称为 key1
	// Set the AES encryption key
	aes_set_key(&aes_ctx, digest, 256);

	// Set the ipad and opad arrays with values as
	// per RFC 2104 (HMAC).  HMAC is defined as
	//   H(K XOR opad, H(K XOR ipad, text))
	memset(ipad, m_Ipad, 64);
	memset(opad, m_Opad, 64);

	for(i=0; i<32; i++)
	{
		ipad[i] ^= digest[i];
		opad[i] ^= digest[i];
	}

	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, ipad, 64);

	//读取48字节的数据,该48字节数据由iv_key被 key1加密后的数据
	//解密后得到iv_key
	{
		for(i=0; i<48; i+=16)
		{
			if ((bytes_read = (int) fread(buffer, 1, 16, infp)) != 16)
			{
				if (feof(infp))
				{
					fprintf(stderr, "Error: Input file is too short.\n");
				}
				else
				{
					perror("Error reading input file IV and key:");
				}
				return  AES_File_ReadError;
			}

			memcpy(buffer2, buffer, 16);

			sha256_update(&sha_ctx, buffer, 16);
			aes_decrypt(&aes_ctx, buffer, buffer);

			// XOR plain text block with previous encrypted
			// output (i.e., use CBC)
			for(j=0; j<16; j++)
			{
				iv_key[i+j] = (buffer[j] ^ IV[j]);
			}

			// Update the IV (CBC mode)
			memcpy(IV, buffer2, 16);
		}

		// Verify that the HMAC is correct
		sha256_finish(&sha_ctx, digest);
		sha256_starts(&sha_ctx);
		sha256_update(&sha_ctx, opad, 64);
		sha256_update(&sha_ctx, digest, 32);
		sha256_finish(&sha_ctx, digest);

		if ((bytes_read = (int) fread(buffer, 1, 32, infp)) != 32)
		{
			if (feof(infp))
			{
				fprintf(stderr, "Error: Input file is too short.\n");
			}
			else
			{
				perror("Error reading input file digest:");
			}
			return  AES_File_ReadError;
		}

		//读取的digest和计算的digest比较
		if (memcmp(digest, buffer, 32))
		{
			fprintf(stderr, "Error: Message has been altered or password is incorrect\n");
			return  AES_PassWordIncorrect;
		}

		// Re-load the IV and encryption key with the IV and
		// key to now encrypt the datafile.  Also, reset the HMAC
		// computation.
		memcpy(IV, iv_key, 16);

		//文件内容解密,使用的key为iv_key的后32个字节,设其名称为key2
		// Set the AES encryption key
		aes_set_key(&aes_ctx, iv_key+16, 256);

		// Set the ipad and opad arrays with values as
		// per RFC 2104 (HMAC).  HMAC is defined as
		//   H(K XOR opad, H(K XOR ipad, text))
		memset(ipad, m_Ipad/*0x36*/, 64);
		memset(opad, m_Opad/*0x5C*/, 64);

		for(i=0; i<32; i++)
		{
			ipad[i] ^= iv_key[i+16];
			opad[i] ^= iv_key[i+16];
		}

		// Wipe the IV and encryption mey from memory
		memset(iv_key, 0, 48);

		sha256_starts(&sha_ctx);
		sha256_update(&sha_ctx, ipad, 64);
	}

	//文件内容解密,使用的key为iv_key的后32个字节,即key2
	// Decrypt the balance of the file

	// Attempt to initialize the ring buffer with contents from the file.
	// Attempt to read 48 octets of the file into the ring buffer.
	//先读取48字节,如果小于48字节，说明没有加密数据,不需要解密
	if ((bytes_read = (int) fread(buffer, 1, 48, infp)) < 48)
	{
		if (!feof(infp))
		{
			perror("Error reading input file ring:");
			return  AES_File_ReadError;
		}
		else
		{
			// If there are less than 48 octets, the only valid count
			// is 32 for version 0 (HMAC) and 33 for version 1 or
			// greater files ( file size modulo + HMAC)
			//没有加密数据,则读取的内容必须为33字节,32字节的结尾 HMAC,1字节的最后一个加密内容大小
			if (bytes_read != 33)
			{
				fprintf(stderr, "Error: Input file is corrupt (1:%d).\n",
					bytes_read);
				return AES_File_ReadError;
			}
			else
			{
				// The first octet must be the indicator of the
				// last block size.
				aeshdr.last_block_size = (buffer[0] & 0x0F);

				// If this initial read indicates there is no encrypted
				// data, then there should be 0 in the last_block_size field
				//没有加密内容,则aeshdr.last_block_size应该为0
				if (aeshdr.last_block_size != 0)
				{
					fprintf(stderr, "Error: Input file is corrupt (2).\n");
					return AES_File_ReadError;
				}
			}
			reached_eof = 1;	//没有需要解密的内容,则设置文件读取完毕标志
		}
	}


	head = buffer + 48;
	tail = buffer;

	while(!reached_eof)			//如果有加密的数据,则数据至少为32+1+16=49字节
	{
		// Check to see if the head of the buffer is past the ring buffer
		if (head == (buffer + 64))
		{
			head = buffer;
		}

		//读取的内容小于16字节,说明是最后一次要加密的内容
		if ((bytes_read = (int) fread(head, 1, 16, infp)) < 16)
		{
			if (!feof(infp))
			{
				perror("Error reading input file:");
				return  AES_File_ReadError;
			}
			else
			{
				if ((tail + 16) < (buffer + 64))
				{
					aeshdr.last_block_size = (tail[16] & 0x0F);
				}
				else
				{
					aeshdr.last_block_size = (buffer[0] & 0x0F);
				}

				// Indicate that we've reached the end of the file
				reached_eof = 1;	//读取
			}
		}

		// Process data that has been read.  Note that if the last
		// read operation returned no additional data, there is still
		// one one ciphertext block for us to process if this is a v0 file.
		if ((bytes_read > 0))
		{
			// Advance the head of the buffer forward
			head += 16;

			memcpy(buffer2, tail, 16);

			sha256_update(&sha_ctx, tail, 16);

			//解密
			aes_decrypt(&aes_ctx, tail, tail);

			// XOR plain text block with previous encrypted
			// output (i.e., use CBC)
			for(i=0; i<16; i++)
			{
				tail[i] ^= IV[i];
			}

			// Update the IV (CBC mode)
			memcpy(IV, buffer2, 16);

			// If this is the final block, then we may
			// write less than 16 octets
			//实际加密数据的长度,如果到达文件结尾,则 n == aeshdr.last_block_size
			n = ((!reached_eof) || (aeshdr.last_block_size == 0)) ? 16 : aeshdr.last_block_size;

			// Write the decrypted block
			memcpy(pWriteBuffer,tail,n);
			pWriteBuffer += n;

			// Move the tail of the ring buffer forward
			tail += 16;
			if (tail == (buffer+64))
			{
				tail = buffer;
			}
		}
	}

	//检验加密之后的数据是否正确
	// Verify that the HMAC is correct
	sha256_finish(&sha_ctx, digest);
	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, opad, 64);
	sha256_update(&sha_ctx, digest, 32);
	sha256_finish(&sha_ctx, digest);

	// Copy the HMAC read from the file into buffer2
	memcpy(buffer2, tail+1, 15);
	tail += 16;
	if (tail == (buffer + 64))
	{
		tail = buffer;
	}
	memcpy(buffer2+15, tail, 16);
	tail += 16;
	if (tail == (buffer + 64))
	{
		tail = buffer;
	}
	memcpy(buffer2+31, tail, 1);

	if (memcmp(digest, buffer2, 32))
	{
		fprintf(stderr, "Error: Message has been altered and should not be trusted\n");

		return AES_HMACAltered;
	}

	pOutBuffer = m_pOutBuffer;
	if (DeRows >= 1)
		BufferLen = (DeRows-1)*16 + aeshdr.last_block_size;
	else
		BufferLen = aeshdr.last_block_size;

	return AES_Ok;
}

//////////////////////////////////////////////////////////////////////////
int CAESCrypt::EnCrypt_Buffer(const char *pInBuffer,long InBufferLen,
							  const char   *outfp, const char* passwd, int passlen)
{
	FILE *pOutfp = fopen(outfp, "wb");
	if (pOutfp == NULL)
		return AES_File_WriteError;

	int Ret = EnCrypt_Buffer(pInBuffer,InBufferLen,pOutfp,passwd,passlen);

	fclose(pOutfp);

	return Ret ;
}

int CAESCrypt::EnCrypt_Buffer(const char *pInBuffer,long InBufferLen,
							  FILE *outfp, const char* passwd, int passlen)
{
	char *pOutBuffer = NULL;
	long BufferLen = 0;
	int Ret = EnCrypt_Buffer(pInBuffer,InBufferLen,pOutBuffer,BufferLen,passwd,passlen);
	if (Ret == AES_Ok && outfp != NULL)
	{
		fwrite(pOutBuffer,1,BufferLen,outfp);
	}

	return Ret;
}

//加密写入内存
int CAESCrypt::EnCrypt_Buffer(const char *pInBuffer,long InBufferLen,
							  char *&pOutBuffer,long &BufferLen, const char* passwd, int passlen)
{
	if (pInBuffer == NULL || InBufferLen <= 0)
		return AES_NoData;

	aes_context                 aes_ctx;
	sha256_context              sha_ctx;
	aescrypt_hdr                aeshdr;
	sha256_t                    digest;
	unsigned char               IV[16];
	unsigned char               iv_key[48];
	int                         i, j;
	unsigned char               buffer[32];
	unsigned char               ipad[64], opad[64];

	//随机数IV,IV-key生成失败,返回
	if (!CreateRandomIVKey(IV,iv_key))
	{
		return AES_IVKEYCREATE_FAILED;
	}

	//计算内存大小
	long InfileBytes = InBufferLen;

	long EnRows = InfileBytes/16;		//加密行数,每一次加密16字节
	if (InfileBytes%16 != 0)
	{
		EnRows ++ ;
		aeshdr.last_block_size = (char)(InfileBytes%16);
	}
	else
		aeshdr.last_block_size = 16;//最后一次加密的内容可能小于16字节,这里记录其字节数

	//加密文件总的大小
	//16			IV
	//48			iv_key 加密后数据
	//32			文件头HMAC
	//EnRows*16		文件加密内容
	//1				文件最后一个字节给出最后一行要加密的字符个数
	//32			文件结尾HMAC
	long nAesBytes = 16+48+32+1+32;		//非文件内容
	long AllOutBufferLen = nAesBytes+EnRows*16;

	if (m_pOutBuffer == NULL)
	{
		m_pOutBuffer = new char [AllOutBufferLen];
		m_OutBufferLen = AllOutBufferLen;
		memset(m_pOutBuffer,0,m_OutBufferLen);
	}
	else
	{
		if (m_OutBufferLen < AllOutBufferLen)
		{
			delete []m_pOutBuffer;

			m_pOutBuffer = new char [AllOutBufferLen];
			m_OutBufferLen = AllOutBufferLen;
			memset(m_pOutBuffer,0,m_OutBufferLen);
		}
	}

	char *pWriteBuffer = m_pOutBuffer;

	//1.写入随机数IV
	memcpy(pWriteBuffer,IV,16);
	pWriteBuffer += 16;

	//由IV和用户密码生成key,设其名称为 key1
	// Hash the IV and password 8192 times
	memset(digest, 0, 32);
	memcpy(digest, IV, 16);
	for(i=0; i<m_IV_Rounds; i++)
	{
		sha256_starts(&sha_ctx);
		sha256_update(&sha_ctx, digest, 32);
		sha256_update(&sha_ctx,(unsigned char*)passwd,(unsigned long)passlen );
		sha256_finish(&sha_ctx,digest);
	}

	//设置key1
	// Set the AES encryption key
	aes_set_key(&aes_ctx, digest, 256);

	// Set the ipad and opad arrays with values as
	// per RFC 2104 (HMAC).  HMAC is defined as
	//   H(K XOR opad, H(K XOR ipad, text))
	memset(ipad, m_Ipad, 64);
	memset(opad, m_Opad, 64);

	for(i=0; i<32; i++)
	{
		ipad[i] ^= digest[i];
		opad[i] ^= digest[i];
	}

	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, ipad, 64);

	//对48字节的iv_key使用key1来加密,写入文件
	// Encrypt the IV and key used to encrypt the plaintext file,
	// writing that encrypted text to the output file.
	for(i=0; i<48; i+=16)
	{
		// Place the next 16 octets of IV and key buffer into
		// the input buffer.
		memcpy(buffer, iv_key+i, 16);

		// XOR plain text block with previous encrypted
		// output (i.e., use CBC)
		for(j=0; j<16; j++)
		{
			buffer[j] ^= IV[j];
		}

		// Encrypt the contents of the buffer
		aes_encrypt(&aes_ctx, buffer, buffer);

		// Concatenate the "text" as we compute the HMAC
		sha256_update(&sha_ctx, buffer, 16);

		//2.写入iv_key加密后的数据
		// Write the encrypted block
		memcpy(pWriteBuffer,buffer,16);
		pWriteBuffer += 16;

		// Update the IV (CBC mode)
		memcpy(IV, buffer, 16);
	}

	//在要加密内容之前写入HMAC
	// Write the HMAC
	sha256_finish(&sha_ctx, digest);
	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, opad, 64);
	sha256_update(&sha_ctx, digest, 32);
	sha256_finish(&sha_ctx, digest);

	//3.写入文件头 HMAC
	// Write the encrypted block
	memcpy(pWriteBuffer,digest,32);
	pWriteBuffer += 32;

	// Re-load the IV and encryption key with the IV and
	// key to now encrypt the datafile.  Also, reset the HMAC
	// computation.
	memcpy(IV, iv_key, 16);

	// Set the AES encryption key
	aes_set_key(&aes_ctx, iv_key+16, 256);

	// Set the ipad and opad arrays with values as
	// per RFC 2104 (HMAC).  HMAC is defined as
	//   H(K XOR opad, H(K XOR ipad, text))
	memset(ipad, m_Ipad, 64);
	memset(opad, m_Opad, 64);

	for(i=0; i<32; i++)
	{
		ipad[i] ^= iv_key[i+16];
		opad[i] ^= iv_key[i+16];
	}

	// Wipe the IV and encryption mey from memory
	memset(iv_key, 0, 48);

	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, ipad, 64);

	//16位字节循环加密
	const char *pInReadBuffer = pInBuffer;
	for (int x = 0; x < EnRows;x ++)
	{
		if (x < EnRows-1)
			memcpy(buffer,pInReadBuffer,16);
		else
			memcpy(buffer,pInReadBuffer,aeshdr.last_block_size);

		// XOR plain text block with previous encrypted
		// output (i.e., use CBC)
		for(i=0; i<16; i++)
		{
			buffer[i] ^= IV[i];
		}

		// Encrypt the contents of the buffer
		//数据加密
		aes_encrypt(&aes_ctx, buffer, buffer);

		// Concatenate the "text" as we compute the HMAC
		sha256_update(&sha_ctx, buffer, 16);

		//4.文件16字节加密存储
		// Write the encrypted block
		memcpy(pWriteBuffer,buffer,16);
		pWriteBuffer += 16;

		// Update the IV (CBC mode)
		//将上一次的要加密数据作为下一次加密的输入参数
		//这样只有正确解密了上一次的数据,下一次的解密才能正常进行
		memcpy(IV, buffer, 16);

		pInReadBuffer += 16;
	}

	//5.将最后一次加密的数据字节数<=16写入文件
	// Write the file size modulo
	buffer[0] = (char) (aeshdr.last_block_size & 0x0F);
	memcpy(pWriteBuffer,buffer,1);
	pWriteBuffer += 1;

	//6.要加密内容之后再写入HMAC
	// Write the HMAC
	sha256_finish(&sha_ctx, digest);
	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, opad, 64);
	sha256_update(&sha_ctx, digest, 32);
	sha256_finish(&sha_ctx, digest);

	memcpy(pWriteBuffer,digest,32);

	//给外部使用
	pOutBuffer = m_pOutBuffer;
	BufferLen = m_OutBufferLen;

	return AES_Ok;
}

//解密写入文件
int CAESCrypt::DeCrypt_Buffer(const char *pInBuffer,long InBufferLen,
							  const char   *outfp, const char* passwd, int passlen)
{
	FILE *pOutfp = fopen(outfp, "wb");
	if (pOutfp == NULL)
		return AES_File_WriteError;

	int Ret = DeCrypt_Buffer(pInBuffer,InBufferLen,pOutfp,passwd,passlen);

	fclose(pOutfp);

	return Ret ;
}

int CAESCrypt::DeCrypt_Buffer(const char *pInBuffer,long InBufferLen,
							  FILE *outfp, const char* passwd, int passlen)
{
	char *pOutBuffer = NULL;
	long BufferLen = 0;
	int Ret = DeCrypt_Buffer(pInBuffer,InBufferLen,pOutBuffer,BufferLen,passwd,passlen);
	if (Ret == AES_Ok && outfp != NULL)
	{
		fwrite(pOutBuffer,1,BufferLen,outfp);
	}

	return Ret;
}


//解密写入内存
int CAESCrypt::DeCrypt_Buffer(const char *pInBuffer,long InBufferLen,
							  char *&pOutBuffer,long &BufferLen, const char* passwd, int passlen)
{
	if (pInBuffer == NULL || InBufferLen <= 0)
		return AES_NoData;

	aes_context                 aes_ctx;
	sha256_context              sha_ctx;
	aescrypt_hdr                aeshdr;
	sha256_t                    digest;
	unsigned char               IV[16];
	unsigned char               iv_key[48];
	int                         i, j;
	unsigned char               buffer[64], buffer2[32];
	unsigned char               *tail;
	unsigned char               ipad[64], opad[64];
	int                         reached_eof = 0;

	//加密文件总的大小
	//16			IV
	//48			iv_key 加密后数据
	//32			文件头HMAC
	//EnRows*16		文件加密内容
	//1				文件最后一个字节给出最后一行要加密的字符个数
	//32			文件结尾HMAC
	long nAesBytes = 16+48+32+1+32;		//非文件内容

	//计算内存大小
	long InBytes = InBufferLen;
	if (InBytes < nAesBytes)			//文件不正确
		return AES_DeDataError;

	long AllOutBufferLen = InBytes-nAesBytes;		//加密行数据
	long DeRows = AllOutBufferLen/16;				//加密行数,每一次加密16字节
	if (AllOutBufferLen%16 != 0)					//文件加密字节总数为16字节整数倍
		return AES_DeDataError;

	if (m_pOutBuffer == NULL)
	{
		m_pOutBuffer = new char [AllOutBufferLen];
		m_OutBufferLen = AllOutBufferLen;
		memset(m_pOutBuffer,0,m_OutBufferLen);
	}
	else
	{
		if (m_OutBufferLen < AllOutBufferLen)
		{
			delete []m_pOutBuffer;

			m_pOutBuffer = new char [AllOutBufferLen];
			m_OutBufferLen = AllOutBufferLen;
			memset(m_pOutBuffer,0,m_OutBufferLen);
		}
	}

	char *pWriteBuffer = m_pOutBuffer;
	const char *pInReadBuffer = pInBuffer;

	//读取IV(16字节)
	// Read the initialization vector from the file
	memcpy(IV,pInReadBuffer,16);
	pInReadBuffer += 16;

	//通过IV和用户输入密码来逆运算出key
	memset(digest, 0, 32);
	memcpy(digest, IV, 16);
	for(i=0; i<m_IV_Rounds; i++)
	{
		sha256_starts(  &sha_ctx);
		sha256_update(  &sha_ctx, digest, 32);
		sha256_update(  &sha_ctx,
			(unsigned char*)passwd,
			(unsigned long)passlen);
		sha256_finish(  &sha_ctx,
			digest);
	}

	//设置由IV和用户输入密码生成的key,设其名称为 key1
	// Set the AES encryption key
	aes_set_key(&aes_ctx, digest, 256);

	// Set the ipad and opad arrays with values as
	// per RFC 2104 (HMAC).  HMAC is defined as
	//   H(K XOR opad, H(K XOR ipad, text))
	memset(ipad, m_Ipad, 64);
	memset(opad, m_Opad, 64);

	for(i=0; i<32; i++)
	{
		ipad[i] ^= digest[i];
		opad[i] ^= digest[i];
	}

	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, ipad, 64);

	//读取48字节的数据,该48字节数据由iv_key被 key1加密后的数据
	//解密后得到iv_key
	{
		for(i=0; i<48; i+=16)
		{
			memcpy(buffer,pInReadBuffer,16);
			pInReadBuffer += 16;

			memcpy(buffer2, buffer, 16);

			sha256_update(&sha_ctx, buffer, 16);
			aes_decrypt(&aes_ctx, buffer, buffer);

			// XOR plain text block with previous encrypted
			// output (i.e., use CBC)
			for(j=0; j<16; j++)
			{
				iv_key[i+j] = (buffer[j] ^ IV[j]);
			}

			// Update the IV (CBC mode)
			memcpy(IV, buffer2, 16);
		}

		//HMAC检验是否正确
		// Verify that the HMAC is correct
		sha256_finish(&sha_ctx, digest);
		sha256_starts(&sha_ctx);
		sha256_update(&sha_ctx, opad, 64);
		sha256_update(&sha_ctx, digest, 32);
		sha256_finish(&sha_ctx, digest);

		memcpy(buffer,pInReadBuffer,32);
		pInReadBuffer += 32;

		//读取的digest和计算的digest比较
		if (memcmp(digest, buffer, 32))
		{
			fprintf(stderr, "Error: Message has been altered or password is incorrect\n");
			return  AES_PassWordIncorrect;
		}

		// Re-load the IV and encryption key with the IV and
		// key to now encrypt the datafile.  Also, reset the HMAC
		// computation.
		memcpy(IV, iv_key, 16);

		//文件内容解密,使用的key为iv_key的后32个字节,设其名称为key2
		// Set the AES encryption key
		aes_set_key(&aes_ctx, iv_key+16, 256);

		// Set the ipad and opad arrays with values as
		// per RFC 2104 (HMAC).  HMAC is defined as
		//   H(K XOR opad, H(K XOR ipad, text))
		memset(ipad, m_Ipad, 64);
		memset(opad, m_Opad, 64);

		for(i=0; i<32; i++)
		{
			ipad[i] ^= iv_key[i+16];
			opad[i] ^= iv_key[i+16];
		}

		// Wipe the IV and encryption mey from memory
		memset(iv_key, 0, 48);

		sha256_starts(&sha_ctx);
		sha256_update(&sha_ctx, ipad, 64);
	}

	//文件内容解密,使用的key为iv_key的后32个字节,即key2
	// Decrypt the balance of the file

	tail = buffer;
	for (int x = 0; x < DeRows;x ++)
	{
		memcpy(tail,pInReadBuffer,16);
		pInReadBuffer+= 16;

		memcpy(buffer2, tail, 16);

		sha256_update(&sha_ctx, tail, 16);

		//解密
		aes_decrypt(&aes_ctx, tail, tail);

		// XOR plain text block with previous encrypted
		// output (i.e., use CBC)
		for(i=0; i<16; i++)
		{
			tail[i] ^= IV[i];
		}

		// Update the IV (CBC mode)
		memcpy(IV, buffer2, 16);

		// Write the decrypted block
		memcpy(pWriteBuffer,tail,16);
		pWriteBuffer += 16;
	}

	//检验加密之后的数据是否正确
	// Verify that the HMAC is correct
	sha256_finish(&sha_ctx, digest);
	sha256_starts(&sha_ctx);
	sha256_update(&sha_ctx, opad, 64);
	sha256_update(&sha_ctx, digest, 32);
	sha256_finish(&sha_ctx, digest);

	//最后一行字节数
	aeshdr.last_block_size = *pInReadBuffer;
	pInReadBuffer += 1;

	// Copy the HMAC read from the file into buffer2
	memcpy(buffer2, pInReadBuffer, 32);

	if (memcmp(digest, buffer2, 32))
	{
		fprintf(stderr, "Error: Message has been altered and should not be trusted\n");

		return AES_HMACAltered;
	}

	pOutBuffer = m_pOutBuffer;
	if (DeRows >= 1)
		BufferLen = (DeRows-1)*16 + aeshdr.last_block_size;
	else
		BufferLen = aeshdr.last_block_size;

	return AES_Ok;
}
