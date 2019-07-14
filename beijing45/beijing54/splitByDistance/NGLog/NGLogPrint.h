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
	Log �⣬ʵ�ֶ�log��Ϣ��������ơ�
	Ŀ��:ͨ��ȫ�ֵ�Log����ʹ�ײ㲻��Ҫ������־���ܵĿ���,
	�ײ㲻����Ҫά��ɾ����־�Ϳ�����־�����ݴ���ı༭��
	����־������ڴ����ڣ��Ƿ�����Լ������ʲô�ط����ж�������

	��־��Ϊ����:
	һ����������־�����������־���ڸ��ٴ�������
	һ���ǵ�����־�������ڵ��Թ����������Ϣ���ڵ��Խ����ر����

	ʹ��ȫ�ֵĽ��Ȼص����ƻ��ƣ����Խ��ײ�ļ�����ȸ�֪����
	
*/

//������־�����ǩ�����±�ǩ�����ڵȼ���ϵ��ʹ�����뷽ʽȷ��������ƥ��

//�������־
#define NGLOG_No 0x0
//�������
#define NGLOG_Error 0x01
//�������
#define NGLOG_Warning 0x02
//��Ϣ���
#define NGLOG_Info 0x04
//�������
#define NGLOG_Debug 0x08
//���̸���
#define NGLOG_Trace 0x10
//ͨ�õ�Debug��־��ǩ
#define NGLOG_AllDebug 0x0F
//����������־�������
#define NGLOG_All 0xFF


typedef void (*NG_LogOutput)(const char*); //���õ���־����ص�������ʽ

typedef void (*NG_ProcessLog)(const char * processId,int total,int finished); //���ý��ȵ��ûص�������ʽ

enum E_NGProcessStatus
{
	NGProcess_Run,
	NGProcess_Cancel
};

extern "C"
{

	/*
	�����Ƿ���log�������
	openLog -- log����,false ���ر������������
	DeugLog -- ����������Ե�log��Ϣ
	*/
	NGLOG_API void NG_OpenLog(int flag);

	/*�����Ƿ���log�������
	openLog -- log����,false ���ر������������
	logPath -- �����ļ���ʽ���Ŀ¼��log�ļ��Զ��������������
	������������,�ڲ����������
	*/
	NGLOG_API void NG_SetLogConfigPath(const char* logPath);

	/*����log����Ļص�����
	pfun --��һ��log����Ļص�����
	�����ɶ�����ã��������ڽ���logչʾ���ڲ����������
	*/
	NGLOG_API void NG_SetLogCallbackFun(NG_LogOutput pfun);

	/*дlog��Ϣ
	module -- ��ʶ��Ϣ����Դģ����
	str -- Ҫ�����log��Ϣ
	*/
	NGLOG_API void NG_WriteLog(int flag,const char * module,const char * str);

	/*
	ʹ�ú�printf��ͬ�ĸ�ʽ�������ʽ
	*/
	NGLOG_API void NG_WriteLogf(int flag,const char * module,const char * strFormat,...);

	/*
	���ý��Ȼص�����,��������������Ϣ
	���processIdΪ��,���ʶΪĬ�ϵĻص�����,δָ��processId�Ļص�������ʹ��Ĭ�ϻص�����
	*/


	//�����Ƴ����Ȼص�����
	NGLOG_API void NG_SetProcessCallbackFun(const char * processId,NG_ProcessLog pfun);
	NGLOG_API void NG_RemoveProcessLog(const char * processId);
	/*д�������Ϣ*/
	NGLOG_API void NG_WriteProcessLog(const char * processId,int total, int finished);
	/*���û�ȡ����״̬*/
	NGLOG_API void NG_SetProcessStatus(const char * processId,E_NGProcessStatus status);
	NGLOG_API E_NGProcessStatus  NG_GetProcessStatus(const char * processId);
	

};
