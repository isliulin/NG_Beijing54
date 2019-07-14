#include "NGLogPrint.h"
#include <string>
#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <sstream>
#include <map>
using namespace std;
#include <stdarg.h>

//锁开关
class NGLogLock
{
public:
	NGLogLock(){omp_init_lock(&_logLock);}
	~NGLogLock(){omp_destroy_lock(&_logLock);}
protected:
	omp_lock_t _logLock;
public:
	void Lock(){omp_set_lock(&_logLock);}
	void UnLock(){omp_unset_lock(&_logLock);}
};

//一个记录进度回调的结构
struct NGProcessLogInfo
{
	E_NGProcessStatus status;
	NG_ProcessLog pFun;
	NGProcessLogInfo()
	{
		status = NGProcess_Run;
		pFun = 0;
	}
};
//一个管理进度回调的类
class NGProcessManager
{
public:
	NGProcessManager(){}
	~NGProcessManager(){Clear();}
protected:
	NGLogLock pm_lock;
	map<string,NGProcessLogInfo> ProcessMap;
public:
	void Clear()
	{
		pm_lock.Lock();
		ProcessMap.clear();
		pm_lock.UnLock();
	}
public:
	void SetFun(const char * processId,NG_ProcessLog pFun)
	{	
		if(processId == 0)
			return;
		string s_p(processId);
		pm_lock.Lock();

		map<string,NGProcessLogInfo>::iterator it = ProcessMap.find(s_p);
		if(it!=ProcessMap.end())
		{
			it->second.pFun = pFun;
		}
		else
		{
			NGProcessLogInfo info;
			info.pFun = pFun;
			ProcessMap.insert(make_pair(s_p,info));
		}
		pm_lock.UnLock();
		
	}

	void SetStatus(const char * processId,E_NGProcessStatus status)
	{
		if(processId == 0)
			return;
		string s_p(processId);
		pm_lock.Lock();

		map<string,NGProcessLogInfo>::iterator it = ProcessMap.find(s_p);
		if(it!=ProcessMap.end())
		{
			it->second.status = status;
		}
		else
		{
			NGProcessLogInfo info;
			info.status = status;
			ProcessMap.insert(make_pair(s_p,info));
		}
		pm_lock.UnLock();
	}

	NGProcessLogInfo Find(const char * processId)
	{		
		NGProcessLogInfo info;
		if(processId == 0)
			return info;
		string s_p(processId);

		pm_lock.Lock();
		map<string,NGProcessLogInfo>::iterator it = ProcessMap.find(s_p);
		if(it!=ProcessMap.end())
		{
			info= it->second;		
		}
		pm_lock.UnLock();
		return info;
	}

	void Remove(const char* processId)
	{
		if(processId == 0)
			return;
		string s_p(processId);
		pm_lock.Lock();
		map<string,NGProcessLogInfo>::iterator it = ProcessMap.find(s_p);
		if(it!=ProcessMap.end())
		{
			ProcessMap.erase(it);		
		}
		pm_lock.UnLock();
	}
};

//一般log的控制变量
static int g_LogFlag = NGLOG_Error; // log 开关
static std::string g_logPath; //log 输出文件路径
static NGLogLock g_logLock; // log 锁
static NG_LogOutput g_pfun = 0; //log输出回调函数

//缺省的进度回调函数
static NG_ProcessLog g_DefProcessFun= 0;
static NGProcessManager g_ProcessMgr;

//是否开启调试log的输出

NGLOG_API void NG_SetLogCallbackFun( NG_LogOutput pfun )
{
	g_pfun = pfun;
}


NGLOG_API void NG_OpenLog( int flag )
{
	g_logLock.Lock();
	g_LogFlag = flag;
	g_logLock.UnLock();
}

NGLOG_API void NG_SetLogConfigPath(const char* logPath )
{
	g_logLock.Lock();
	g_logPath = logPath?logPath:"";
	g_logLock.UnLock();
}

void WriteLog( const char * module,const char * str )
{
	if(str==0)
		return;
	time_t ct = time(0);
	tm * ctm = localtime(&ct);
	char logtime[20] = {0};
	sprintf(logtime,"%04d-%02d-%02d %02d:%02d:%02d",
		ctm->tm_year+1900,ctm->tm_mon+1,ctm->tm_mday,
		ctm->tm_hour,ctm->tm_min,ctm->tm_sec);
	std::ostringstream temp;
	temp <<logtime<<'\t' <<(module?module:"")<<'\t'<<(str?str:"")<<"\r\n";
	if(g_pfun)
		g_pfun(temp.str().c_str());
	if(g_logPath.empty())
		return;

	g_logLock.Lock();
	try
	{	
		static char logfile [300] = {0};
		sprintf(logfile,"%s/NGLog%04d%02d%02d.txt",g_logPath.c_str(),ctm->tm_year+1900,ctm->tm_mon+1,ctm->tm_mday);
		printf("%s\n",temp.str().c_str());
		FILE * pf = fopen(logfile,"a+");
		if(pf)
		{
			fprintf(pf,"%s",temp.str().c_str());
			fclose(pf);
		}
	}
	catch (...)
	{
	}
	g_logLock.UnLock();
}


NGLOG_API void NG_WriteLogf( int flag,const char * module,const char * strFormat,... )
{
	if(flag&g_LogFlag)
	{
		va_list argp;
		va_start(argp,strFormat);
		char buf[1024] = {0};
		vsnprintf(buf,sizeof(buf),strFormat,argp);
		va_end(argp);
		WriteLog(module,buf);
	}
}


NGLOG_API void NG_WriteLog( int flag,const char * module,const char * str )
{
	if(flag&g_LogFlag)
		WriteLog(module,str);
}



NGLOG_API void NG_SetProcessCallbackFun( const char * processId,NG_ProcessLog pfun )
{
	if(processId == 0)
		g_DefProcessFun = pfun;
	else
		g_ProcessMgr.SetFun(processId,pfun);
}

NGLOG_API void NG_WriteProcessLog( const char * processId,int total, int finished )
{
	NGProcessLogInfo info = g_ProcessMgr.Find(processId);
	if(info.pFun)
		info.pFun(processId,total,finished);
	else if(g_DefProcessFun)
		g_DefProcessFun(processId,total,finished);

}

NGLOG_API void NG_RemoveProcessLog( const char * processId)
{
	g_ProcessMgr.Remove(processId);
}

NGLOG_API void NG_SetProcessStatus( const char * processId,E_NGProcessStatus status )
{
	if(processId)
		g_ProcessMgr.SetStatus(processId,status);
}

NGLOG_API E_NGProcessStatus NG_GetProcessStatus( const char * processId )
{
	if(!processId)
		return NGProcess_Run;
	NGProcessLogInfo info = g_ProcessMgr.Find(processId);
	return info.status;
}










