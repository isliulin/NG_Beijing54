#ifndef NG_BAND_PASS_FILTER_H
#define NG_BAND_PASS_FILTER_H

#include "NGTDOADataStruct.h"
//ͨ��Ƶ�����˲��㷨��ʵ�ִ�ͨ�˲���
class CNGBandPassFilter
{
private:
	CNGBandPassFilter(void){};
	~CNGBandPassFilter(void){};

public:
	//��ͨ������õ��ź��˲�������λMHz
	static void DoSignalFiltering(IQData& srcData,int Index);

};

#endif