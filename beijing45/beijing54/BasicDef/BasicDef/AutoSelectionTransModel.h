#ifndef _AUTOSELECTIONTRANSMODEL_H
#define  _AUTOSELECTIONTRANSMODEL_H

#include "../DataModel/EnumDef.h"

ETransModel GetAutoModelIDEntry(double FreqMHz);

void*  GetClassicModelParamByModeIDEntry(ETransModel ModelID);
void  ReleaseClassicModelParamEntry(void* pModelParam);












#endif 