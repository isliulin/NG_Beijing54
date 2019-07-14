#pragma once
#ifdef _LIB
#define NGLOG_API
#else 
#ifdef _WIN32
#ifdef NGLOG_EXPORTS
#define NGLOG_API _declspec(dllexport)
#else
#define NGLOG_API  _declspec(dllimport)
#pragma comment(lib,"NGLog.lib")
#endif //NGLOG_EXPORTS
#else
#define NGLOG_API
#endif //_WIN32
#endif // _LIB

/*
	Log 库，实现对log信息的输出控制。
	目的:通过全局的Log控制使底层不需要关心日志功能的开关,
	底层不再需要维护删除日志和开启日志的两份代码的编辑，
	将日志输出留在代码内，是否输出以及输出到什么地方都有顶层设置

	日志分为两种:
	一种是流程日志，输出流程日志用于跟踪代码流程
	一种是调试日志，用于在调试过程中输出信息，在调试结束关闭输出

	使用全局的进度回调控制机制，可以将底层的计算进度告知顶层
	
*/

//定义日志输出标签，以下标签不存在等级关系，使用掩码方式确定开关量匹配

//不输出日志
#define NGLOG_No 0x0
//错误输出
#define NGLOG_Error 0x01
//警告输出
#define NGLOG_Warning 0x02
//信息输出
#define NGLOG_Info 0x04
//调试输出
#define NGLOG_Debug 0x08
//流程跟踪
#define NGLOG_Trace 0x10
//通用的Debug日志标签
#define NGLOG_AllDebug 0x0F
//开启所有日志输出功能
#define NGLOG_All 0xFF


typedef void (*NG_LogOutput)(const char*); //设置的日志输出回调函数格式

typedef void (*NG_ProcessLog)(const char * processId,int total,int finished); //设置进度调用回调函数格式

enum E_NGProcessStatus
{
	NGProcess_Run,
	NGProcess_Cancel
};

extern "C"
{

	/*
	设置是否开启log输出功能
	openLog -- log开关,false 将关闭所有输出功能
	DeugLog -- 开关输出调试的log信息
	*/
	NGLOG_API void NG_OpenLog(int flag);

	/*设置是否开启log输出功能
	openLog -- log开关,false 将关闭所有输出功能
	logPath -- 设置文件形式输出目录，log文件自动以日期名称输出
	建议由最顶层调用,内部不建议调用
	*/
	NGLOG_API void NG_SetLogConfigPath(const char* logPath);

	/*设置log输出的回调函数
	pfun --是一个log输出的回调函数
	建议由顶层调用，可以用于界面log展示，内部不建议调用
	*/
	NGLOG_API void NG_SetLogCallbackFun(NG_LogOutput pfun);

	/*写log信息
	module -- 标识信息的来源模块名
	str -- 要输出的log信息
	*/
	NGLOG_API void NG_WriteLog(int flag,const char * module,const char * str);

	/*
	使用和printf相同的格式化输出方式
	*/
	NGLOG_API void NG_WriteLogf(int flag,const char * module,const char * strFormat,...);

	/*
	设置进度回调函数,可输出计算进度信息
	如果processId为空,则标识为默认的回调函数,未指定processId的回调函数将使用默认回调函数
	*/


	//设置移除进度回调函数
	NGLOG_API void NG_SetProcessCallbackFun(const char * processId,NG_ProcessLog pfun);
	NGLOG_API void NG_RemoveProcessLog(const char * processId);
	/*写入进度信息*/
	NGLOG_API void NG_WriteProcessLog(const char * processId,int total, int finished);
	/*设置获取进度状态*/
	NGLOG_API void NG_SetProcessStatus(const char * processId,E_NGProcessStatus status);
	NGLOG_API E_NGProcessStatus  NG_GetProcessStatus(const char * processId);
	

};
