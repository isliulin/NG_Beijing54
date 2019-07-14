#ifndef __LICENSE_CHECK__MANAGER___H__
#define __LICENSE_CHECK__MANAGER___H__

#include "dongle_check_export.h"
#include "../DataModel/EnumDef.h"

//���license�ļ�
//pLicenseFile license�ļ�����·��
//ֻ��kernelModel��Ҫ���øýӿڣ������Ķ�����NG_CheckLicense_Wrapper
extern "C" int NG_CheckLicense(const char *pLicenseFile,  EModelType eModelType, int nCheckType=1);

extern "C" int NG_CheckLicense_Wrapper(const char *pLicenseFile,  EModelType eModelType);

extern "C" int NG_GetLicenseType();


#endif