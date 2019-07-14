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

typedef BYTE TIME8Bytes[8] ;				//ʱ��,8���ֽ�

enum NetAdapterAESErrorStatus
{
	NetAdapterAES_Ok						=  0,
	NetAdapterAES_AdapterDisMatch			=  1,	//����ƥ�����
	NetAdapterAES_TimeExpired				=  2,	//ʱ�����
	NetAdapterAES_FileNotExist				=  3,	//License�ļ�������
	NetAdapterAES_Error						=  4,	//��������
	NetAdapterAES_TimeModified				=  5,	//����ʱ�䱻�۸�
	NetAdapterAES_PasswordIncorrect         =  6    //��Կ���󣬿������������Ȩ��license�ļ�������Ӧ
};

class SuperString
{
public:
	SuperString(const char *ptext) { m_textString = ptext; }
	SuperString(const std::string &text) { m_textString = text; }

	//�Ƚ������
	bool operator==(const SuperString &that) const ;
	bool operator!=(const SuperString &text) const ;
	bool operator>=(const SuperString &that) const ;
	bool operator<=(const SuperString &text) const ;
	bool operator>(const SuperString &that) const ;
	bool operator<(const SuperString &text) const ;

	//�����Զ�ת��
	operator std::string() {return m_textString; }

public:
	std::string  m_textString;
};


//��������
class CNetAdapterAESCrypt
{
public:
	CNetAdapterAESCrypt();
	~CNetAdapterAESCrypt();

public:
	//��ȡ���ܺ���ļ�
	int		ReadCryptFile(const char  *infp);
	int		WriteCryptFile(const char  *outfp);

	//��Ӽ������� --liuqingmei
	//ֱ�ӻ�ȡ�ļ��д洢��ʱ��
	int GetLastTime(const char *infp, TIME8Bytes& TimestampNsec);	

	//���õ��Ե�ǰ��ʱ��
	int UpdateCurrentTime(const char *infp);
	
	//��ȡ�ϴθ��µ�ʱ��
	int GetUpdateTime(TIME8Bytes& TimestampNsec);

	//���ü���������ַ
	bool	SetCryptMacAddress(const BYTE *pAddress,UINT AddressLength);
	bool	GetCryptMacAddress(BYTE *pAddress,UINT &AddressLength);

	//�Ƿ���Ҫ��������
	void	EnableMacAes(bool Enable) { m_MacAES_Enable = Enable;}
	bool	IsMacAesEnable() { return m_MacAES_Enable;}

	//���õ���ʱ��
	void	SetCryptExpiredTime(const TIME8Bytes TimestampNsec);	//Unix Time Stamp Nano Seconds
	void	GetCryptExpiredTime(TIME8Bytes& TimestampNsec);

	//�����û�����
	bool	SetPassWord(const char *pPassword,int PassLen);
	bool	GetPassWord(char *pPassword,int &PassLen);

	//��Ӻͻ�ȡ����ģ��
	bool	AddModel(const char *pModelName,BOOL bUseable);
	bool	GetModel(const char *pModelName,BOOL &bUseable);

private:
	//key	-->����ģ������
	//value	-->����ģ���Ƿ����
	std::map<SuperString,BOOL>m_ModelData;

	//MAC����
	UINT m_MacAddressLength;
	BYTE m_MacAddress[16];

	//����ʱ��
	TIME8Bytes m_TimestampNsec;

	//�ļ��м�¼�ĵ�ǰʱ��
	TIME8Bytes m_TimestampLastWrite;

	//�û�����
	int m_PassWordLen;
	char m_szPassWord[32];

	//�Ƿ���Ҫ��������
	bool m_MacAES_Enable;		//�������Ҫ��������,���ʹ��ʱ�����

};

#endif