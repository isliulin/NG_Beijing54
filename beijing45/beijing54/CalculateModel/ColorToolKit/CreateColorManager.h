#ifndef __CREATE_COLOR_MANAGER__H__
#define __CREATE_COLOR_MANAGER__H__
#include <vector>

#include "ColorManagerBase.h"

//读取配色文件,和指定的名称生成一个配色管理器
CColorManagerBase * CreateColorManger_FromFile(const char *pColorFile,const char *pName);

//读取配色文件,生成所有配色管理器
bool CreateColorManger_FromFile(const char *pColorFile,std::vector<CColorManagerBase *> &ColorManageVector);

//生成一个渐变配色管理器
CColorManagerBase * CreateColorManger_FromData(const char *pName,double dmin,double dmax,COLORGBA mincolor,COLORGBA maxClor);

void ClearColorManager(CColorManagerBase* pColorManager);
CColorManagerBase * CreateDefalutPathLossColor();
CColorManagerBase * CreateDefaultContinuColor();
CColorManagerBase * CreateColorManager(ColorManagerType type);
CColorManagerBase * CreateDefaultGradualColor();
#endif