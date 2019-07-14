#ifndef __CREATE_COLOR_MANAGER__H__
#define __CREATE_COLOR_MANAGER__H__
#include <vector>

#include "ColorManagerBase.h"

//��ȡ��ɫ�ļ�,��ָ������������һ����ɫ������
CColorManagerBase * CreateColorManger_FromFile(const char *pColorFile,const char *pName);

//��ȡ��ɫ�ļ�,����������ɫ������
bool CreateColorManger_FromFile(const char *pColorFile,std::vector<CColorManagerBase *> &ColorManageVector);

//����һ��������ɫ������
CColorManagerBase * CreateColorManger_FromData(const char *pName,double dmin,double dmax,COLORGBA mincolor,COLORGBA maxClor);

void ClearColorManager(CColorManagerBase* pColorManager);
CColorManagerBase * CreateDefalutPathLossColor();
CColorManagerBase * CreateDefaultContinuColor();
CColorManagerBase * CreateColorManager(ColorManagerType type);
CColorManagerBase * CreateDefaultGradualColor();
#endif