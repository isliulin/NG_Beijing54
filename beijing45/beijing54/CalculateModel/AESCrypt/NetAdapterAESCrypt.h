#ifndef _NETADAPTER_AESCRYPT_H_
#define _NETADAPTER_AESCRYPT_H_

#pragma once
#include <string>
#include <map>

#if defined(_WIN32) || defined(__WIN32__)
#include <Windows.h>
#else
typedef int                 BOOL;
typedef char       BYTE;
typedef unsigned int        UINT;
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

typedef BYTE TIME8Bytes[8] ;				//时间,8个字节

enum NetAdapterAESErrorStatus
{
	NetAdapterAES_Ok						=  0,
	NetAdapterAES_AdapterDisMatch			=  1,	//网卡匹配错误
	NetAdapterAES_TimeExpired				=  2,	//时间过期
	NetAdapterAES_FileNotExist				=  3,	//License文件不存在
	NetAdapterAES_Error						=  4,	//其他错误
	NetAdapterAES_TimeModified				=  5,	//机器时间被篡改
	NetAdapterAES_PasswordIncorrect         =  6    //密钥错误，可能是软件与授权（license文件）不对应
};

class SuperString
{
public:
	SuperString(const char *ptext) { m_textString = ptext; }
	SuperString(const std::string &text) { m_textString = text; }

	//比较运算符
	bool operator==(const SuperString &that) const ;
	bool operator!=(const SuperString &text) const ;
	bool operator>=(const SuperString &that) const ;
	bool operator<=(const SuperString &text) const ;
	bool operator>(const SuperString &that) const ;
	bool operator<(const SuperString &text) const ;

	//类型自动转换
	operator std::string() {return m_textString; }

public:
	std::string  m_textString;
};


//网卡加密
class CNetAdapterAESCrypt
{
public:
	CNetAdapterAESCrypt();
	~CNetAdapterAESCrypt();

public:
	//读取加密后的文件
	int		ReadCryptFile(const char  *infp);
	int		WriteCryptFile(const char  *outfp);

	//添加几个函数 --liuqingmei
	//直接获取文件中存储的时间
	int GetLastTime(const char *infp, TIME8Bytes& TimestampNsec);	

	//设置电脑当前的时间
	int UpdateCurrentTime(const char *infp);
	
	//获取上次更新的时间
	int GetUpdateTime(TIME8Bytes& TimestampNsec);

	//设置加密网卡地址
	bool	SetCryptMacAddress(const BYTE *pAddress,UINT AddressLength);
	bool	GetCryptMacAddress(BYTE *pAddress,UINT &AddressLength);

	//是否需要网卡加密
	void	EnableMacAes(bool Enable) { m_MacAES_Enable = Enable;}
	bool	IsMacAesEnable() { return m_MacAES_Enable;}

	//设置到期时间
	void	SetCryptExpiredTime(const TIME8Bytes TimestampNsec);	//Unix Time Stamp Nano Seconds
	void	GetCryptExpiredTime(TIME8Bytes& TimestampNsec);

	//设置用户密码
	bool	SetPassWord(const char *pPassword,int PassLen);
	bool	GetPassWord(char *pPassword,int &PassLen);

	//添加和获取功能模块
	bool	AddModel(const char *pModelName,BOOL bUseable);
	bool	GetModel(const char *pModelName,BOOL &bUseable);

private:
	//key	-->功能模块名称
	//value	-->功能模块是否可用
	std::map<SuperString,BOOL>m_ModelData;

	//MAC网卡
	UINT m_MacAddressLength;
	BYTE m_MacAddress[16];

	//到期时间
	TIME8Bytes m_TimestampNsec;

	//文件中记录的当前时间
	TIME8Bytes m_TimestampLastWrite;

	//用户密码
	int m_PassWordLen;
	char m_szPassWord[32];

	//是否需要网卡加密
	bool m_MacAES_Enable;		//如果不需要网卡加密,则仅使用时间加密

};

#endif