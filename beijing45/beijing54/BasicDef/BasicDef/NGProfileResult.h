#pragma once
#include <string.h>
#include <vector>
#include <string>
typedef std::vector<double> stdDoubleVector;
typedef std::string STDtring;
class CNGProfileResult
{
public:
	CNGProfileResult(void);
	virtual ~CNGProfileResult(void);
public:
	STDtring m_field_unit;
	int m_map_coordindex;
	int m_MaxBarrierPer_Index;//视通最弱的点下标
	stdDoubleVector m_longitude_v;//经度集
	stdDoubleVector m_latitude_v;//纬度集
	stdDoubleVector m_distance_v;//距离集
	stdDoubleVector m_height_v;//高度集
	stdDoubleVector m_clutter_v;//地貌集
	stdDoubleVector m_conductivity_v;//电导率集
	stdDoubleVector m_field_v;//场强集
	stdDoubleVector m_fresnel_up_v;//费涅尔上限集
	stdDoubleVector m_fresnel_down_v;//费涅尔下限集
	stdDoubleVector m_BarrierPer_v;//障碍百分比集
    double m_RxAngle;//接收遮蔽角
	double m_TxAngle;//发射遮蔽角

	//发射台的参数  高度 经纬度 发射频率
	double mFromlongitude;
	double mFromlatitude;
	double mStartheight;//不包含地形高度
	double mFrequencyMhz;
	//接受台的参数 高度 经纬度
	double mTolongitude;
	double mTolatitude;
	double mEndheight;//不包含地形高度

public: 
	void Clear();
	bool IsValid() const;
	unsigned int GetSize() const;
};

class CNGShortWaveResult
{
public:
	CNGShortWaveResult(void)
	{
		mnYear = 2013;
		mnMonth = 1;
		memset(mpBMUF, 0, 24*sizeof(float));
		memset(mpBLUF, 0, 24*sizeof(float));
		memset(mpOperMUF, 0, 24*sizeof(float));
		memset(mpOptMUF, 0, 24*sizeof(float));
	}
	virtual ~CNGShortWaveResult(void){}
public:
	int mnYear;         //年
	int mnMonth;        //月份
	float mpBMUF[24];   //基本最大可用频率数组 24个小时
	float mpBLUF[24];   //基本最小可用频率数组 24个小时
	float mpOperMUF[24];//工作MUF数组 24个小时
	float mpOptMUF[24]; //最佳工作频率 24个小时

};