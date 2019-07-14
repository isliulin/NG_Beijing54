#ifndef __DATAMODEL_CALIBRATIONPARAM_h
#define __DATAMODEL_CALIBRATIONPARAM_h

#include "ComputeParam.h"

//测试数据结构
struct ScmDriveTestData
{
	//测试点经度
	double mdX;
	//测试点纬度
	double mdY;
	//测试点信号值 --可能是场强、功率等
	double mdValue;
};

//传播模型修正参数
struct ScmCalibrationParam
{
	//测试数据的发射机参数
	Compute_Antenna* mpComputeAntenna;

	//测试数据的接收机参数
	RX_Antenna* mpRXAntenna;

	//地图参数
	ICalGis_MapManger* mpGisAdapter;

	//测试数据类别 -场强，电平等
	ECoverResultType meDriveTestType;

	//测试数据位置的坐标系
	int mnCoordSys;

	//测试数据数组
	std::vector<ScmDriveTestData> mvDriveTestDatas;
};

#endif