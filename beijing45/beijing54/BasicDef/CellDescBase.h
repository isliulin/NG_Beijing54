
#pragma once

#include <string>
#include "DataTypes.h"
#include "PowerIndBm.h"
#include "GeoShape.h"


class CellDescBase 
{
  public:

	  inline CellDescBase(){m_RadiusIndex=0;mPCI=0;m_AntennaGain = 0;}
   //! free allocated memory
	  inline virtual ~CellDescBase(){}

   virtual  float GetCenterFreqMHz();


 public:

	//参与计算的信息
 	//小区cellid
 	std::string m_CID;
 	//导频信道号
 	int m_channelNo;
	//载频数
	int m_carrierNum;
	// 水平方位角
	AngleInDeg	m_aglAzimuth;
	// 机械下倾角
	AngleInDeg	m_aglMechaniclTilt;
	// 电下倾角
	AngleInDeg  m_aglElectriclTilt;
	//下倾角=机械下倾角+电下倾角
	AngleInDeg  m_aglTilt;
	// 导频功率 gsm 数据库是erp, td, lte是output
    PowerIndBm	m_pilotPower;
	//TRX power+AtennaGain
	PowerIndBm  m_erp;
	// 最大发射功率
	PowerIndBm	m_maxTransPower;
	// 天线高度
    float		m_dHeight;
	//经纬度信息
	CGeoPoint   m_coord;
    //天线型号
	std::string m_antennaType;

	//中心频率
	float m_frequency;
	//中心带宽
	float m_bandwidth;
	//CCCH频道数
	int m_CCCHChannelNum;
	//最大增益
	int m_AntennaGain;	//  2 gsm,3 td,4 lte
	int  m_netType;
	//子载波间隔
	int m_numScs;
	int  m_RadiusIndex;//0主城区,1县城,2农村
	
	//系统类型
	std::string m_SystemType;
	//常用的信息
	std::string m_CellName;//小区名称
	std::string m_SiteName;//基站名称
	std::string m_SiteID;//基站站号
	std::string m_City;//所属地市
	std::string m_CellularType;//室内室外
	int mPCI;

};



















