#include "NetAdapterAESCrypt.h"
#include "AESCrypt.h"
#include <time.h>
#include <string.h>
#if defined(_WIN32) || defined(__WIN32__)
#include "netadapter.h"
#else
//Linux下文件
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

#ifndef _UNIX__
#include <ifaddrs.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

#ifndef _UNIX__

//Linux下查找电脑上是否有匹配的网卡
bool FindMac(BYTE* pDestMacAddress)
{
	struct ifaddrs *ifaddr = NULL;
	if (getifaddrs(&ifaddr) == -1)
	{
		return false;
	}

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		freeifaddrs(ifaddr);
		return false;
	}

	bool bRet = false;
	struct ifreq ifr;
	for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
	{
		memset(&ifr, 0, sizeof(ifr));
		strcpy(ifr.ifr_name, ifa->ifa_name);
		if (ioctl(fd, SIOCGIFFLAGS, &ifr) == 0)
		{
			if (!(ifr.ifr_flags & IFF_LOOPBACK))
			{
				if (ioctl(fd, SIOCGIFHWADDR, &ifr) == 0)
				{
					char *pMac = (char *)ifr.ifr_hwaddr.sa_data;
					int cmpResult = memcmp(pMac,pDestMacAddress,6);
					if (cmpResult == 0)
					{
						bRet = true;	//查找到,跳出循环
						break;
					}
				}
			}
		}
	}
	close(fd);
	freeifaddrs(ifaddr);

	return bRet ;
}
#endif
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

bool SuperString::operator==(const SuperString &that) const
{
	if(strcmp(m_textString.c_str(),that.m_textString.c_str()) == 0)
		return true;

	return false;
}

bool SuperString::operator!=(const SuperString &that) const
{
	if(strcmp(m_textString.c_str(),that.m_textString.c_str()) == 0)
		return false;

	return true;
}

bool SuperString::operator>=(const SuperString &that) const
{
	if(strcmp(m_textString.c_str(),that.m_textString.c_str()) >= 0)
		return false;

	return true;
}

bool SuperString::operator<=(const SuperString &that) const
{
	if(strcmp(m_textString.c_str(),that.m_textString.c_str()) <= 0)
		return false;

	return true;
}

bool SuperString::operator>(const SuperString &that) const
{
	if(strcmp(m_textString.c_str(),that.m_textString.c_str()) > 0)
		return false;

	return true;
}

bool SuperString::operator<(const SuperString &that) const
{
	if(strcmp(m_textString.c_str(),that.m_textString.c_str()) < 0)
		return false;

	return true;
}

bool  IsLittleEndian()
{
	static unsigned short sV = 0x0001;
	return (*((char*)&sV)>0);
}

void Swapnbytes(void * data,int n)
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

CNetAdapterAESCrypt::CNetAdapterAESCrypt()
{
	m_MacAddressLength = 0;
	memset(m_MacAddress,0,sizeof(m_MacAddress));

	memset(m_TimestampNsec,0,sizeof(m_TimestampNsec));

	m_PassWordLen = 0;
	memset(m_szPassWord,0,sizeof(m_szPassWord));

	m_MacAES_Enable = TRUE;	//默认使用网卡加密
}

CNetAdapterAESCrypt::~CNetAdapterAESCrypt()
{

}

int CNetAdapterAESCrypt::ReadCryptFile(const char  *infp)
{
	char *pOutBuffer = NULL;
	long BufferLen = 0;
	CAESCrypt aes;
	long TimeMacBytes = sizeof(m_TimestampNsec) + sizeof(m_MacAddress) + sizeof(m_MacAES_Enable) + sizeof(m_TimestampLastWrite);//时间和网卡字节大小
	int nRet = aes.DeCrypt_File(infp,pOutBuffer,BufferLen,m_szPassWord,m_PassWordLen);
	if (nRet == AES_Ok && pOutBuffer != NULL && BufferLen >= TimeMacBytes)
	{
		int nRetLocal = NetAdapterAES_Ok;

		//1.获取时间
		char *pTemp = pOutBuffer;
		memcpy(m_TimestampNsec,pTemp,sizeof(m_TimestampNsec));
		pTemp += sizeof(m_TimestampNsec);

		time_t tm = time(NULL);		//获取当前时间
		time_t tmExpired = 0;
		memcpy(&tmExpired,m_TimestampNsec,sizeof(tmExpired));
		if(!IsLittleEndian())
			Swapnbytes(&tmExpired,sizeof(tmExpired));
		if (tm > tmExpired)
		{
			nRetLocal = NetAdapterAES_TimeExpired;
		}			

		//2.获取网卡地址
		memcpy(m_MacAddress,pTemp,sizeof(m_MacAddress));
		pTemp += sizeof(m_MacAddress);

		m_MacAddressLength = sizeof(m_MacAddress);

		//3.获取是否需要网卡加密
		memcpy(&m_MacAES_Enable,pTemp,sizeof(m_MacAES_Enable));
		pTemp += sizeof(m_MacAES_Enable);

		memcpy(m_TimestampLastWrite,pTemp,sizeof(m_TimestampLastWrite));
		pTemp += sizeof(m_TimestampLastWrite);

		//比较当前时间和记录在文档中的曾经的当前时间，
		int offset = 0;
		if(!IsLittleEndian())
		{
			offset = 8-sizeof(time_t);
			Swapnbytes(m_TimestampLastWrite,sizeof(m_TimestampLastWrite));
		}
			
		if(nRetLocal != NetAdapterAES_Ok)
		{
			return nRetLocal;
		}

		time_t tmLastWrite = 0;
		memcpy(&tmLastWrite,&m_TimestampLastWrite[offset],sizeof(tmLastWrite));

		if (tm < tmLastWrite)
			return NetAdapterAES_TimeModified;

		if(m_MacAES_Enable)	//网卡加密,则判断网卡是否正确
		{
			//////////////////////////////////////////////////////////////////////////
			//windows下获取网卡信息
#if defined(_WIN32) || defined(__WIN32__)
			CNetworkAdapter* pAdapters = NULL;
			int nAdaptersCounts = 0;

			EnumNetworkAdapters(pAdapters,nAdaptersCounts);
			if (pAdapters == NULL || nAdaptersCounts <= 0)
				return NetAdapterAES_AdapterDisMatch;	//没有获取到网卡信息

			int PrimaryIndex = 0;
			for (PrimaryIndex = 0; PrimaryIndex < nAdaptersCounts; PrimaryIndex ++)
			{
				UNNAMED CurAdapter = pAdapters[PrimaryIndex].GetAdapterAddressBytes();
				int cmpResult = memcmp(CurAdapter.ucAddress,m_MacAddress,CurAdapter.nLen);
				if (cmpResult == 0)	//查找到
				{
					break;
				}
			}
			if (PrimaryIndex == nAdaptersCounts)		//没有找到
			{
				delete []pAdapters;
				pAdapters = NULL;

				return NetAdapterAES_AdapterDisMatch;	//网卡不正确
			}

			delete []pAdapters;
			pAdapters = NULL;
#else
			//Linux下获取网卡地址
			#ifndef _UNIX__
			if (!FindMac(m_MacAddress))
			{
				return NetAdapterAES_AdapterDisMatch;	//网卡不正确
			}
			#else
			
			#endif
#endif
			//////////////////////////////////////////////////////////////////////////
		}

		//4.功能模块是否可用复制
		m_ModelData.clear();
		long ModleItemBytes = sizeof(BOOL) + 128;		//名称设置为128字节
		long AllModelBytes = BufferLen - TimeMacBytes;
		if (AllModelBytes > 0)							//
		{
			int nItems = AllModelBytes/ModleItemBytes;
			for (int x = 0;x < nItems;x ++)
			{
				AddModel((char *)pTemp,*(BOOL *)pTemp[128]);
				pTemp += ModleItemBytes;
			}
		}

		return NetAdapterAES_Ok;
	}
	else
	{
		if (nRet == AES_File_OpenError)
		{
			return NetAdapterAES_FileNotExist;
		}
		else if(nRet == AES_PassWordIncorrect)
		{
			return NetAdapterAES_PasswordIncorrect;
		}
		else
		{
			return NetAdapterAES_Error;
		}
	}
}

int CNetAdapterAESCrypt::WriteCryptFile(const char *outfp)
{
	long BufferLen = 0;
	CAESCrypt aes;

	long TimeMacBytes = sizeof(m_TimestampNsec) + sizeof(m_MacAddress) + sizeof(m_MacAES_Enable);//时间和网卡字节大小
	long ModleItemBytes = sizeof(BOOL) + 128;							//名称设置为128字节
	long CurTimeBytes = sizeof(m_TimestampNsec);
	long AllModelBytes = ModleItemBytes*m_ModelData.size();
	long AllBytes = TimeMacBytes + AllModelBytes + CurTimeBytes;
	char *pInBuffer = new char[AllBytes];
	char *pTemp = pInBuffer;

	//1.时间复制
	memcpy(pTemp,&m_TimestampNsec,sizeof(m_TimestampNsec));
	pTemp += sizeof(m_TimestampNsec);

	//2.网卡复制
	memcpy(pTemp,m_MacAddress,sizeof(m_MacAddress));
	pTemp += sizeof(m_MacAddress);

	//3.是否使用网卡加密
	memcpy(pTemp,&m_MacAES_Enable,sizeof(m_MacAES_Enable));
	pTemp += sizeof(m_MacAES_Enable);

	//当前时间复制
	time_t tm = time(NULL);		//获取当前时间
	int offset = 0;
	bool bisle = IsLittleEndian();
	if(!bisle)
	{
		offset = 8-sizeof(time_t);
	}
	memcpy(&m_TimestampLastWrite[offset], &tm, sizeof(tm));
	if(!bisle)
		Swapnbytes(m_TimestampLastWrite,sizeof(m_TimestampLastWrite));
	memcpy(pTemp, &m_TimestampLastWrite, sizeof(m_TimestampLastWrite));
	pTemp += sizeof(m_TimestampLastWrite);

	//4.功能模块是否可用复制
	std::map<SuperString,BOOL>::iterator it;
	int nNameLen = 0;
	for (it = m_ModelData.begin();it != m_ModelData.end();it ++)
	{
		const SuperString &Name = it->first;
		BOOL bUseable = it->second;

		nNameLen = min(Name.m_textString.length()+1,128);
		memcpy(pTemp,Name.m_textString.c_str(),nNameLen);
		memcpy(&pTemp[128],&bUseable,sizeof(BOOL));

		pTemp += ModleItemBytes;
	}

	int nRet = aes.EnCrypt_Buffer(pInBuffer,AllBytes,outfp,m_szPassWord,m_PassWordLen);

	delete []pInBuffer;
	pInBuffer = NULL;

	if (nRet == AES_Ok)
		return NetAdapterAES_Ok;
	else
		return NetAdapterAES_Error;
}

bool CNetAdapterAESCrypt::SetCryptMacAddress(const BYTE *pAddress,UINT AddressLength)
{
	if (pAddress == NULL || AddressLength <= 0)
		return false;

	m_MacAddressLength = min(AddressLength,16);
	memcpy(m_MacAddress,pAddress,m_MacAddressLength);

	return true;
}

bool CNetAdapterAESCrypt::GetCryptMacAddress(BYTE *pAddress,UINT &AddressLength)
{
	if (m_MacAddressLength == 0)
		return false;

	memcpy(pAddress,m_MacAddress,m_MacAddressLength);
	AddressLength = m_MacAddressLength;

	return true;
}

void CNetAdapterAESCrypt::SetCryptExpiredTime(const TIME8Bytes TimestampNsec)
{
	memcpy(m_TimestampNsec,TimestampNsec,sizeof(m_TimestampNsec));
}

void CNetAdapterAESCrypt::GetCryptExpiredTime(TIME8Bytes& TimestampNsec)
{
	memcpy(TimestampNsec,m_TimestampNsec,sizeof(m_TimestampNsec));
}

bool CNetAdapterAESCrypt::SetPassWord(const char *pPassword,int PassLen)
{
	if (pPassword == NULL || PassLen <= 0)
		return false;

	m_PassWordLen = min(PassLen,32);
	memcpy(m_szPassWord,pPassword,m_PassWordLen*sizeof(char));

	return true;
}

bool CNetAdapterAESCrypt::GetPassWord(char *pPassword,int &PassLen)
{
	if (m_PassWordLen == 0)
		return FALSE;

	memcpy(pPassword,m_szPassWord,m_PassWordLen);
	PassLen = m_PassWordLen;

	return true;
}

bool CNetAdapterAESCrypt::AddModel(const char *pModelName,BOOL bUseable)
{
	if (pModelName == NULL)
		return false;

	std::map<SuperString,BOOL>::iterator it;
	SuperString name = pModelName;
	m_ModelData.find(name);
	if (it != m_ModelData.end())
	{
		it->second = bUseable;
	}
	else
	{
		m_ModelData.insert(std::make_pair(name,bUseable));
	}

	return true;
}

bool CNetAdapterAESCrypt::GetModel(const char *pModelName,BOOL &bUseable)
{
	if (pModelName == NULL)
		return false;

	std::map<SuperString,BOOL>::iterator it;
	SuperString name = pModelName;
	it = m_ModelData.find(name);
	if (it != m_ModelData.end())
	{
		bUseable = it->second;

		return true;
	}

	return false;
}

int CNetAdapterAESCrypt::GetLastTime(const char *infp, TIME8Bytes& TimestampNsec )
{
	char *pOutBuffer = NULL;
	long BufferLen = 0;
	CAESCrypt aes;
	long TimeMacBytes = sizeof(m_TimestampNsec) + sizeof(m_MacAddress) + sizeof(m_MacAES_Enable) + sizeof(m_TimestampLastWrite);//时间和网卡字节大小
	int nRet = aes.DeCrypt_File(infp,pOutBuffer,BufferLen,m_szPassWord,m_PassWordLen);
	if (nRet == AES_Ok && pOutBuffer != NULL && BufferLen >= TimeMacBytes)
	{
		//1.获取时间
		char *pTemp = pOutBuffer;
		pTemp += sizeof(m_TimestampNsec);

		//2.获取网卡地址
		pTemp += sizeof(m_MacAddress);

		//3.获取是否需要网卡加密
		pTemp += sizeof(m_MacAES_Enable);

		memcpy(TimestampNsec,pTemp,sizeof(TimestampNsec));
		if(!IsLittleEndian())
			Swapnbytes(TimestampNsec,sizeof(TimestampNsec));
		int offset = 8-sizeof(time_t);
		for(int i=0;i<sizeof(time_t);i++)
			TimestampNsec[i] = TimestampNsec[offset+i];

		return NetAdapterAES_Ok;
	}
	else
	{
		if (nRet == AES_File_OpenError)
			return NetAdapterAES_FileNotExist;
		else
			return NetAdapterAES_Error;
	}
}

int CNetAdapterAESCrypt::UpdateCurrentTime(const char *infp)
{
	char *pOutBuffer = NULL;
	long BufferLen = 0;
	CAESCrypt aes;
	long TimeMacBytes = sizeof(m_TimestampNsec) + sizeof(m_MacAddress) + sizeof(m_MacAES_Enable) + sizeof(m_TimestampLastWrite);//时间和网卡字节大小
	long ModleItemBytes = sizeof(BOOL) + 128;
	int nRet = aes.DeCrypt_File(infp,pOutBuffer,BufferLen,m_szPassWord,m_PassWordLen);
	if (nRet == AES_Ok && pOutBuffer != NULL && BufferLen >= TimeMacBytes)
	{
		char* pInBuffer = new char[BufferLen];
		if(pInBuffer == NULL)
		{
			return NetAdapterAES_Error;
		}
		memcpy(pInBuffer, pOutBuffer, sizeof(char)*BufferLen);

		//1.获取时间
		char *pTemp = pInBuffer;
		memcpy(m_TimestampNsec,pTemp,sizeof(m_TimestampNsec));
		pTemp += sizeof(m_TimestampNsec);

		time_t tm = time(NULL);		//获取当前时间
		time_t tmExpired = 0;
		int offset = 0;
		if(!IsLittleEndian())
		{
			Swapnbytes(m_TimestampNsec,sizeof(m_TimestampNsec));
			offset = 8-sizeof(time_t);
		}
		
		memcpy(&tmExpired,&m_TimestampNsec[offset],sizeof(tmExpired));
		if (tm > tmExpired)
			return NetAdapterAES_TimeExpired;

		memcpy(m_MacAddress,pTemp,sizeof(m_MacAddress));
		pTemp += sizeof(m_MacAddress);

		//3.获取是否需要网卡加密
		memcpy(&m_MacAES_Enable,pTemp,sizeof(m_MacAES_Enable));
		pTemp += sizeof(m_MacAES_Enable);

		memcpy(m_TimestampLastWrite,pTemp,sizeof(m_TimestampLastWrite));

		//比较当前时间和记录在文档中的曾经的当前时间，
		time_t tmLastWrite = 0;
		if(!IsLittleEndian())
			Swapnbytes(m_TimestampLastWrite,sizeof(m_TimestampLastWrite));
		memcpy(&tmLastWrite,&m_TimestampLastWrite[offset],sizeof(tmLastWrite));
		if (tm < tmLastWrite)
			return NetAdapterAES_TimeModified;
		else
		{
			memcpy(&m_TimestampLastWrite[offset], &tm, sizeof(tm));
			if(!IsLittleEndian())
				Swapnbytes(m_TimestampLastWrite,sizeof(m_TimestampLastWrite));
			memcpy(pTemp, m_TimestampLastWrite, sizeof(m_TimestampLastWrite));

		}
		pTemp += sizeof(m_TimestampLastWrite);

		if(m_MacAES_Enable)	//网卡加密,则判断网卡是否正确
		{
			//////////////////////////////////////////////////////////////////////////
			//windows下获取网卡信息
#if defined(_WIN32) || defined(__WIN32__)
			CNetworkAdapter* pAdapters = NULL;
			int nAdaptersCounts = 0;

			EnumNetworkAdapters(pAdapters,nAdaptersCounts);
			if (pAdapters == NULL || nAdaptersCounts <= 0)
				return NetAdapterAES_AdapterDisMatch;	//没有获取到网卡信息

			int PrimaryIndex = 0;
			for (PrimaryIndex = 0; PrimaryIndex < nAdaptersCounts; PrimaryIndex ++)
			{
				UNNAMED CurAdapter = pAdapters[PrimaryIndex].GetAdapterAddressBytes();
				int cmpResult = memcmp(CurAdapter.ucAddress,m_MacAddress,CurAdapter.nLen);
				if (cmpResult == 0)	//查找到
				{
					break;
				}
			}
			if (PrimaryIndex == nAdaptersCounts)		//没有找到
			{
				delete []pAdapters;
				pAdapters = NULL;

				return NetAdapterAES_AdapterDisMatch;	//网卡不正确
			}

			delete []pAdapters;
			pAdapters = NULL;
#else
			//Linux下获取网卡地址
			#ifndef _UNIX__
			if (!FindMac(m_MacAddress))
			{
				return NetAdapterAES_AdapterDisMatch;	//网卡不正确
			}
			#else
			
			#endif
#endif
			//////////////////////////////////////////////////////////////////////////
		}

		//4.功能模块是否可用复制
		std::map<SuperString,BOOL>::iterator it;
		int nNameLen = 0;
		for (it = m_ModelData.begin();it != m_ModelData.end();it ++)
		{
			const SuperString &Name = it->first;
			BOOL bUseable = it->second;

			nNameLen = min(Name.m_textString.length()+1,128);
			memcpy(pTemp,Name.m_textString.c_str(),nNameLen);
			memcpy(&pTemp[128],&bUseable,sizeof(BOOL));

			pTemp += ModleItemBytes;
		}
		int nRet = aes.EnCrypt_Buffer(pInBuffer,BufferLen,infp,m_szPassWord,m_PassWordLen);

		if(pInBuffer != NULL)
		{
			delete []pInBuffer;
			pInBuffer = NULL;
		}

		if (nRet == AES_Ok)
			return NetAdapterAES_Ok;
		else
			return NetAdapterAES_Error;
	}
	else
	{
		if (nRet == AES_File_OpenError)
			return NetAdapterAES_FileNotExist;
		else
			return NetAdapterAES_Error;
	}
}

int CNetAdapterAESCrypt::GetUpdateTime( TIME8Bytes& TimestampNsec )
{
	memcpy(TimestampNsec,m_TimestampLastWrite,sizeof(m_TimestampNsec));
	return 0;
}

