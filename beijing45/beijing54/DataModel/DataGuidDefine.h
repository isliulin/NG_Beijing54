#ifndef __DATA__GUID__DEFINE__H__
#define __DATA__GUID__DEFINE__H__

#define DATA_NAME_MAX		128				//�����ַ�����󳤶�
#define DATA_REMARK_MAX		256				//˵�������ַ�����󳤶�
#define GUID_BYTES			37				//GUID��ռ�ֽ���

#include <string>
typedef char EMC_DATA_GUID[GUID_BYTES];

//�豸������Ϣ
typedef struct tagEMC_Base
{
	EMC_DATA_GUID	id;						//̨վid
	std::string	EquId;			//�豸ID
	std::string StationName;				//̨վ����
	/*EMC_DATA_GUID userid;					//id
	char	szRemark[DATA_REMARK_MAX];		//˵������*/
	std::string StationAddr;
	std::string NET_TS;//��������Id
	std::string NET_TS_Name;//��������
	std::string NET_SVN;//ͨ��ҵ��/ϵͳ���� id
	std::string NET_SVN_Name;//ͨ��ҵ��/ϵͳ���� ����
}EMC_Base;

#endif	/* __DATA__GUID__DEFINE__H__ */