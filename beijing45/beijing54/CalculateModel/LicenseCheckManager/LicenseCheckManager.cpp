#define _CRT_RAND_S
#include "LicenseCheckManager.h"
#include "../BasicDef/MacroDef.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

#define HP_UX 0
#define LINUX 0
#define SOLARIS 0

//#define AES_CODE
//#define UNDONGLED

//#define RANDOM_CHECK_LICENSE

#if defined(_WIN32) || defined(__WIN32__)
#include <Windows.h>
#include <shlwapi.h>
#pragma comment( lib, "Dongle.lib" )
#elif SOLARIS || LINUX
#include <errno.h>
#elif HP_UX
#define _PSTAT64
#include <sys/pstat.h>
#include <errno.h>
#endif

#pragma warning(disable:4996)

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#include <AESCryptLib.h>

void logfile(const char* strOut)
{
	return;

	std::cout << strOut<<'\n';
    std::string sParam = "/home/log.txt";
    std::ofstream file;
    file.open(sParam.c_str(), std::ios_base::app | std::ios_base::out);
    if(file.is_open())
    {
        file<<strOut<<std::endl;
        file.close();
    }
    else
    {
        std::cout<<"Open log file fail!"<<std::endl;
    }
}
//获取引用程序所在文件目录
void GetModuleFileDirectory(char *pFileDir)
{
	const int _MAX_PATH_L = 260;
	char szTemp[_MAX_PATH_L] = {0};
#if defined(_WIN32) || defined(__WIN32__)   
	GetModuleFileNameA(NULL, szTemp, _MAX_PATH_L);
#elif LINUX
    char sysfile[25] = "/proc/self/exe";
    if(-1 == readlink(sysfile, szTemp, namelen))
    {
        sprintf(szTemp, "readlinkError:%s\n", strerror(errno));
        return;
    }
#elif SOLARIS
    //logfile("before getexecname");
    //std::cout<<"before getexecname"<<std::endl;
    std::string sParam = getexecname(); //trunc the exe file name

    //std::cout<<sParam.c_str()<<std::endl;
    if('/' == sParam.at(0))
    {
        //logfile("getexecname abs path");
        //std::cout<<"getexecname abs path"<<std::endl;
        strcpy(szTemp, sParam.c_str()); //abs path
    }
    else if(sParam.substr(0,2) == "./")
    {
        //logfile("getexecname ./ path");
        //std::cout<<"getexecname ./ path"<<std::endl;
        char szTemp2[256];
        getcwd(szTemp2, 256);
        std::string strcwdPath = szTemp2;
        //std::string strdebug = "getexecname: "+ strcwdPath;
        //logfile(strdebug.c_str());
        //std::cout<<"getexecname: "<<strcwdPath<<std::endl;
        std::string strout = strcwdPath + sParam.substr(1);
        strcpy(szTemp, strout.c_str());
        //std::cout<<"getexecname ./ path"<<szTemp<<std::endl;
    }
    else if(sParam.substr(0,3) == "../")
    {
        char szTemp2[256];
        getcwd(szTemp2, 256);
        std::string strcwdPath = szTemp2;
        std::string strout = strcwdPath + "/" + sParam;

        //logfile(strout.c_str());
        strcpy(szTemp, strout.c_str());
    }
    else if(sParam.find('/') == std::string::npos)
    {
        //std::cout<<"getexecname no / path"<<std::endl;
        char szTemp2[256];
        getcwd(szTemp2, 256);
        std::string strcwdPath = szTemp2;
        //std::cout<<"getexecname: "<<strcwdPath<<std::endl;
        //std::string strdebug = "getexecname: "+ strcwdPath;
        //logfile(strdebug.c_str());

        std::string strout = strcwdPath + "/" + sParam;
        strcpy(szTemp, strout.c_str());
        //std::cout<<"getexecname no / path"<<szTemp<<std::endl;

        //logfile(szTemp);
    }
    else
    {
        //logfile("else");
        std::cout<<"else no process"<<std::endl;
    }

    //std::cout<<szTemp<<std::endl;

    int nLen = strlen(szTemp);
	if (nLen > 0)
	{
		int nLoc = 0;
		for (nLoc = nLen-1; nLoc >= 0;nLoc --)
		{
			if (szTemp[nLoc] == '\\' || szTemp[nLoc] == '/' )
			{
				szTemp[nLoc] = 0;
				break;
			}
		}
	}

    //find the object file in the exe file path
    FILE* pf;
    char cmd[100];
    char buf[100];
    sprintf(cmd, "find %s -name XTRACalWrapper",  szTemp);
    //logfile(cmd);
    //std::cout<<"cmd:"<<cmd<<std::endl;
    pf  = popen(cmd, "r");
    if(pf == NULL)
    {
        std::cout<<"popen fail"<<std::endl;
    }
    fgets(buf, 100, pf);
    pclose(pf);

    //std::cout<<buf<<std::endl;
    //logfile(buf);

    std::string sEXEPath = szTemp;
    sParam = buf;  //the result of find
    if('/' == sParam.at(0))
    {
        strcpy(szTemp, sParam.c_str());
    }
    else if(sParam.substr(0,2) == "./")
    {
        std::string strout = sEXEPath + sParam.substr(1);
        strcpy(szTemp, strout.c_str());
    }
    else if(sParam.substr(0,3) == "../")
    {
        std::string strout = sEXEPath + "/" + sParam;
        strcpy(szTemp, strout.c_str());
    }
    else if(sParam.find('/') == std::string::npos)
    {
        std::string strout = sEXEPath + "/" + sParam;
        strcpy(szTemp, strout.c_str());
    }
#elif HP_UX
	struct pst_status s;
	if (pstat_getproc(&s,sizeof(s),0,getpid()) == -1) 
	{
		perror("pstat_getproc");
		logfile("pstat_getproc error");
		return;// EXIT_FAILURE;
	}

  if (pstat_getpathname(szTemp,sizeof(szTemp),&s.pst_fid_text) == -1)
  {
		perror("pstat_getpathname");
		logfile("pstat_getpathname error");
		return;// EXIT_FAILURE;
  }
#endif
	logfile(szTemp);
  //Modify by CX 20150610.减少两次无必要的循环
	int lastPathChar = -1;
	for(int nLoc = 0;nLoc<_MAX_PATH_L;nLoc++)
	{
		if (szTemp[nLoc] == '\\' || szTemp[nLoc] == '/' )
		{
			lastPathChar = nLoc;
			pFileDir[nLoc] = '/';
		}
		else pFileDir[nLoc] = szTemp[nLoc];
		if(pFileDir[nLoc] == '\0')
			break;
	}
	if(lastPathChar!=-1)
		pFileDir[lastPathChar]='\0';

	logfile(pFileDir);
	/*
	nLen = strlen(szTemp);
	if (nLen > 0)
	{
		int nLoc = 0;
		for (nLoc = nLen-1; nLoc >= 0;nLoc --)
		{
			if (szTemp[nLoc] == '\\' || szTemp[nLoc] == '/' )
			{
				szTemp[nLoc] = 0;
				break;
			}
		}

		strcpy(pFileDir,szTemp);
	}
	*/
}

bool PathRemoveFileNameLocal(char *pFilePath)
{
	if (pFilePath == NULL)
		return false;

	/*
	char* ptr = pFilePath + strlen(pFilePath);
	while (ptr > pFilePath && *(ptr-1)!='/' && *(ptr-1)!='\\')
		ptr--;
	//ptr 如果 > pFilePath,说明查找到 /,或者\,则将其修改为0
	if (ptr > pFilePath)
		*(ptr-1) = 0;
	*/
	//Modify by CX 20150610
	char * ptr = NULL;
	while(*pFilePath)
	{
		if((*pFilePath=='/')||(*pFilePath=='\\'))
			ptr = pFilePath;
		pFilePath++;
	}

	//不保留最后的"/"或"\"
	if(ptr)*(ptr)='\0';
		

	return true;
}

#if 0  //有读和写
int NG_CheckRightAESExist(const char *pLicenseFile)
{
    //logfile("in NG_CheckRightAESExist");
    //std::cout<<"in NG_CheckRightAESExist"<<std::endl;
	int nRet = 0;
	int nRetLic = EMC_SUCCESS;
	int nRetXCal = EMC_SUCCESS;
	char szFilePath[260];
	if (pLicenseFile == NULL)	//license文件为空,则使用默认文件
	{
		GetModuleFileDirectory(szFilePath);
		strcat(szFilePath, "/XTRACalWrapper");
	}
	else
	{
		strcpy(szFilePath, pLicenseFile);
	}

	//获取一个随机数
	srand( GetTickCount());
	int nRand = rand();
	int nValue = nRand % 50;
	CNetAdapterAESCrypt aes;
	char  szPassword[] = "NG_EMC_VERSION_1.0";	//密码
	aes.SetPassWord(szPassword,(int)(strlen(szPassword)));

	/*
	TIME8Bytes lastWrite;
	if(NetAdapterAES_Ok == aes.GetLastTime(szFilePath, lastWrite))
	{
			time_t tm = time(NULL);
			time_t last = 0;
			memcpy(&last, lastWrite, sizeof(last));
			std::cout<<tm<<' '<<last<<'\n';
	}
	*/


	if(nValue <= 5)
	{
		//获取上次更新的时间
		TIME8Bytes lastWriteTime;
		nRet = aes.GetLastTime(szFilePath, lastWriteTime);
		if(NetAdapterAES_Ok == nRet)
		{
			//跟当前时间比较
			time_t tm = time(NULL);
			time_t last = 0;
			memcpy(&last, lastWriteTime, sizeof(last));
			if(last > tm)
			{
				logfile(szFilePath);
				logfile("1TimeOut");
				nRetLic = EMC_TIMEMODIFIED;
			}
			else
			{
				logfile(szFilePath);
				logfile("1Success");
				nRetLic = EMC_SUCCESS;
			}
		}
		else if(NetAdapterAES_FileNotExist == nRet)
		{
			nRetLic = NG_OPENLICENSEFILEFAIL;
		}
		else 
		{
			nRetLic = EMC_LICENSEWRONG;
			logfile(szFilePath);
			logfile("1LicenseWrong");
		}		
	}
	else if((nValue >= 6) && (nValue <= 40))
	{
		//更新当前时间到文件中
		nRet = aes.UpdateCurrentTime(szFilePath);
		if (nRet == NetAdapterAES_TimeExpired)
		{
			nRetLic = EMC_LICENSEEXPIRED;
			logfile(szFilePath);
			logfile("2TimeOut");
		}
		else if(nRet == NetAdapterAES_TimeModified)
		{
			nRetLic = EMC_TIMEMODIFIED;
			logfile(szFilePath);
			logfile("2TimeModify");
		}
		else if(nRet == NetAdapterAES_AdapterDisMatch)
		{
			nRetLic = NG_LICENSEWRONG;
			logfile(szFilePath);
			logfile("2AdapterDisMatch");
		}
		else if(nRet == NetAdapterAES_Ok)
		{
			logfile(szFilePath);
			logfile("2Success");
			nRetLic = EMC_SUCCESS;
		}
		else
		{
			logfile(szFilePath);
			logfile("2LicenseWrong");
			nRetLic = EMC_LICENSEWRONG;
		}
	}
	else if((nValue >= 41) && (nValue <= 50))
	{
		nRet = aes.ReadCryptFile(szFilePath);
		if (nRet == NetAdapterAES_TimeExpired)
		{
			logfile(szFilePath);
			logfile("3TimeOut");
			nRetLic = EMC_LICENSEEXPIRED;
		}
		else if(nRet == NetAdapterAES_TimeModified)
		{
			logfile(szFilePath);
			logfile("3TimeModify");
			nRetLic = EMC_TIMEMODIFIED;
		}
		else if(nRet == NetAdapterAES_AdapterDisMatch)
		{
			nRetLic = NG_LICENSEWRONG;
			logfile(szFilePath);
			logfile("3AdapterDisMatch");
		}
		else if(nRet == NetAdapterAES_Ok)
		{
			logfile(szFilePath);
			logfile("3Success");
			nRetLic = EMC_SUCCESS;
		}
		else
		{
			logfile(szFilePath);
			logfile("3LicenseWrong");
			nRetLic = EMC_LICENSEWRONG;
		}
	}
	if( nValue >=10 && nValue <= 40 )
	{
		PathRemoveFileNameLocal(szFilePath);
		strcat(szFilePath,"/XTRACalculate");
		//更新当前时间到文件中
		nRet = aes.UpdateCurrentTime(szFilePath);
		if (nRet == NetAdapterAES_TimeExpired)
		{
			logfile(szFilePath);
			logfile("4TimeOut");
			nRetXCal = EMC_LICENSEEXPIRED;
		}
		else if(nRet == NetAdapterAES_TimeModified)
		{
			logfile(szFilePath);
			logfile("4TimeModify");
		    nRetXCal = EMC_TIMEMODIFIED;
		}
		else if(nRet == NetAdapterAES_AdapterDisMatch)
		{
			nRetXCal = NG_LICENSEWRONG;
			logfile(szFilePath);
			logfile("4AdapterDisMatch");
		}
		else if(nRet == NetAdapterAES_Ok)
		{
			logfile(szFilePath);
			logfile("4Success");
			nRetXCal = EMC_SUCCESS;
		}
		else
		{
			logfile(szFilePath);
			logfile("4LicenseWrong");
			nRetXCal = EMC_LICENSEWRONG;
		}
	}
	if(nRetXCal != EMC_SUCCESS)
	{
		return nRetXCal;
	}
	return nRetLic;
}
#else
//考虑到并行只能读
int NG_CheckRightAESExist(const char *pLicenseFile)
{
    //logfile("in NG_CheckRightAESExist");
    //std::cout<<"in NG_CheckRightAESExist"<<std::endl;
	int nRet = 0;
	int nRetLic = EMC_SUCCESS;
	int nRetXCal = EMC_SUCCESS;
	char szFilePath[260];
	if ((pLicenseFile == NULL) || (pLicenseFile[0] == 0))	//license文件为空,则使用默认文件
	{
		GetModuleFileDirectory(szFilePath);
		strcat(szFilePath, "/XTRACalWrapper");
	}
	else
	{
		strcpy(szFilePath, pLicenseFile);
	}

	CNetAdapterAESCrypt aes;
	char  szPassword[] = "NG_EMC_VERSION_1.0";	//密码
	aes.SetPassWord(szPassword,(int)(strlen(szPassword)));

	nRet = aes.ReadCryptFile(szFilePath);
	if (nRet == NetAdapterAES_TimeExpired)
	{
		logfile(szFilePath);
		logfile("3TimeOut");
		nRetLic = EMC_LICENSEEXPIRED;
	}
	else if(nRet == NetAdapterAES_TimeModified)
	{
		logfile(szFilePath);
		logfile("3TimeModify");
		nRetLic = EMC_TIMEMODIFIED;
	}
	else if(nRet == NetAdapterAES_AdapterDisMatch)
	{
		nRetLic = NG_LICENSEWRONG;
		logfile(szFilePath);
		logfile("3AdapterDisMatch");
	}
	else if(nRet == NetAdapterAES_Ok)
	{
		logfile(szFilePath);
		logfile("3Success");
		nRetLic = EMC_SUCCESS;
	}
	else
	{
		logfile(szFilePath);
		logfile("3LicenseWrong");
		nRetLic = EMC_LICENSEWRONG;
	}
	return nRetLic;
}
#endif

int NG_CheckRightSentinelDongleExist(const char *pLicenseFile, EModelType eModelType)
{
	int iRet = EMC_SUCCESS;
	try
	{			
		switch(eModelType)
		{
		case eBaseModel:
			{
				char szFilePath[MAX_PATH];
				if (pLicenseFile == NULL)	//license文件为空,则使用默认文件
				{
					GetModuleFileDirectory(szFilePath);
					strcat(szFilePath,"\\License\\License.txt");
				}
				else
				{
					strcpy(szFilePath,pLicenseFile);
				}
#ifdef RANDOM_CHECK_LICENSE
				//获取一个随机数
				srand( GetTickCount());
				int nRand = rand();
				int nValue = nRand % 50;

				if( (nValue>=8 && nValue<=15)||
					(nValue>=23 && nValue<=28)||  
					(nValue>=36 && nValue<=45) )
#endif
				{
// 					FILE* pStream = fopen(szFilePath, "rt");
// 					if(pStream)
// 					{
// 						char licenseCode[100];
// 						fgets(licenseCode, 100, pStream);
// 						fclose(pStream);
					    char* licenseCode = "KEE5F2EE0T0EEDMECE83F0EE8TMSMTET"; 
						iRet = CheckCustomerCode(licenseCode);						
// 					}
// 					else
// 					{
// 						return NG_OPENLICENSEFILEFAIL;
// 					}					
				}
				break;
			}
		case eUNKNOWNModel:
			{
				//生成一个随机数，如果随机数在一定范围内，就检测response
				srand( GetTickCount());
				int nRand = rand();
				int nValue = nRand % 50;

				if( (nValue>=5 && nValue<=8)||
					(nValue>=18 && nValue<=23)||  
					(nValue>=38 && nValue<=43) )
				{
					iRet = CheckQueryResponse();					
				}
				break;
			}
		default://只检测指定的模块是否授权
			{
#ifdef RANDOM_CHECK_LICENSE
				srand( GetTickCount());
				int nRand = rand();
				int nValue = nRand % 100;

				if( (nValue>=10 && nValue<=20)||
					(nValue>=35 && nValue<=45)||  
					(nValue>=55 && nValue<=70)||
					(nValue>=85 && nValue<=95) )
#endif
				{
					iRet = CheckModelLicense(eModelType);					
				}
				break;
			}
		}
	}
	catch (...)
	{	
		return NG_DONGLECHECK_EXCEPTION;
	}
	int nRet = EMC_SUCCESS;
	switch(iRet)
	{
	case EMC_SUCCESS:
		{
			nRet = iRet;
			break;
		}
	case 9:
		{
			nRet = NG_LICENSEDONGLENOTMATCH;
			break;
		}
	case 226:
		{
			nRet = NG_NORIGHTDONGLE; 
			break;
		}
	case 304:
		{
			nRet = NG_NOSERVERDONGLE;
			break;
		}
	case 11:
		{
			nRet = NG_NOMODELLICENSE;
			break;
		}
	case 227:
		{
			nRet = NG_LICENSEEXPIRED;
			break;
		}
	case 223:
		{
			nRet = NG_TIMEMODIFIED;
			break;
		}
	default:
		{
			nRet = DONGLE_BASE_ERROR + iRet;
			break;
		}
	}
	return nRet;	
}

int NG_CheckLicense_Wrapper(const char *pLicenseFile,  EModelType eModelType)
{
#ifdef UNDONGLED
	return NG_CheckLicense(pLicenseFile, eModelType, 0);
#else
#ifdef AES_CODE
	return NG_CheckLicense(pLicenseFile, eModelType, 2);
#else
	return NG_CheckLicense(pLicenseFile, eModelType, 1);
#endif
#endif

}

int NG_GetLicenseType()
{
	int nLicType = 1;
#ifdef UNDONGLED
	nLicType = 0;
#else
#ifdef AES_CODE
	nLicType = 2;
#else
	nLicType = 1;
#endif
#endif

	return nLicType;
}

//nCheckType:加密检测类别，0：不检测；1：硬件狗检测，2：软加密检测
int NG_CheckLicense(const char *pLicenseFile,  EModelType eModelType, int nCheckType)
{   
    int nRet = NG_SUCCESS;
	switch(nCheckType)
	{
	case 0:
		{
			nRet = 0;
			break;
		}
	case 1:
		{
			nRet = NG_CheckRightSentinelDongleExist(pLicenseFile, eModelType);
			break;
		}
	case 2:
		{
			nRet = NG_CheckRightAESExist(pLicenseFile);
			break;
		}
	default:
		{
			nRet = NG_UNKNOWNLICENSECHECK;
			break;
		}
	}

	return nRet;
}
