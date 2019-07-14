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
// float mCenterFreqMhz;//��ƵƵ��
// float mBandMhz;//��Ƶ����
// float mBeginMhz;//��ʼƵ��
// float mEndMhz;//��ֹƵ��
//}SingleFrequency;





//��ⷶΧ���Է����

struct AssumeTRXParam
{
 float mTRXHeight;
 EHeightType   mTRXHeightType;//��0:���θ߶� 1:�������ϸ߶� 2:���������ϵĸ߶�
 float mTRXErip;
 std::string mTRXEripUnit;
 float mTRXFreq;
 std::string mTRXFreqUnit;

};


#endif

