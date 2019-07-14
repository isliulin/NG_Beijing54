#ifndef __DATA__GUID__DEFINE__H__
#define __DATA__GUID__DEFINE__H__

#define DATA_NAME_MAX		128				//名称字符串最大长度
#define DATA_REMARK_MAX		256				//说明文字字符串最大长度
#define GUID_BYTES			37				//GUID所占字节数

#include <string>
typedef char EMC_DATA_GUID[GUID_BYTES];

//设备基本信息
typedef struct tagEMC_Base
{
	EMC_DATA_GUID	id;						//台站id
	std::string	EquId;			//设备ID
	std::string StationName;				//台站名称
	/*EMC_DATA_GUID userid;					//id
	char	szRemark[DATA_REMARK_MAX];		//说明文字*/
	std::string StationAddr;
	std::string NET_TS;//技术体制Id
	std::string NET_TS_Name;//体制名称
	std::string NET_SVN;//通信业务/系统类型 id
	std::string NET_SVN_Name;//通信业务/系统类型 名称
}EMC_Base;

#endif	/* __DATA__GUID__DEFINE__H__ */