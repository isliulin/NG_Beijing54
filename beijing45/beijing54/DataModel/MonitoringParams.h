#ifndef _MONITORINGPARAMS_H_
#define _MONITORINGPARAMS_H_

#include <string>
#include <vector>
#include "../DataModel/EnumDef.h"
#include "../BasicDef/GeoShape.h"
#include "EnumDef.h"

//typedef struct SingleFrequency
//{
// //mBeginMhz=mCenterFreqMhz-mBandMhz/2
// //mEndMhz=mCenterFreqMhz+mBandMhz/2
// float mCenterFreqMhz;//用频频率
// float mBandMhz;//用频带宽
// float mBeginMhz;//起始频率
// float mEndMhz;//终止频率
//}SingleFrequency;





//监测范围测试发射机

struct AssumeTRXParam
{
 float mTRXHeight;
 EHeightType   mTRXHeightType;//，0:海拔高度 1:地面以上高度 2:建筑物以上的高度
 float mTRXErip;
 std::string mTRXEripUnit;
 float mTRXFreq;
 std::string mTRXFreqUnit;

};


#endif

