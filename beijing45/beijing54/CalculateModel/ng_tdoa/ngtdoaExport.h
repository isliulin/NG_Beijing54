#include "..\LocaltionLib\NGTDOADataStruct.h"


/*****************************************************************************
// 文件名:		 
// 编写者:	李冬	  
// 编写日期:2015.12	  
// 简要描述 TDOA定位算法的导出接口
// 设计文档名称：
// 设计文档版本号
// 设计文档禅道ID 
// 修改记录:		 
//
// (C) 2017  Ng-networks
*****************************************************************************/


#ifndef __NG_CALCULATE_EXPORT_H__
#define __NG_CALCULATE_EXPORT_H__


extern "C"
{

	//tdoa
	int NG_Localtion_Algorithm(NGIQData* datas , unsigned int num , const char* presultpath);


	int NG_Localtion_Algorithm_Point_float(NGIQData_float* datas , unsigned int num , const char* pLicenseFile,  double *x,double *y);
	//函数名称：NG_Localtion_Algorithm_Point
	//原理：根据监测站采集的IQ数据，给出定位结果
	//输入参数：datas：各监测站的IQ数据，顺序排列，单个监测站的IQ数据格式参见结构体NGIQData
	//          num：参与定位的监测站个数
	//          pLicenseFile：授权license文件名
	//输出参数：x，y：输出定位点的坐标，WGS84坐标系
	int NG_Localtion_Algorithm_Point(NGIQData* datas , unsigned int num , const char* pLicenseFile,  double *x,double *y);
	//原理：用给定的mac地址与文件中的比较
	//pszMac：设备Mac地址
	//szLicFileName: License 文件路径
	//返回值：
	int NG_CheckMacLicense(const char* pszMac, const char* pLicenseFile);


};
#endif
