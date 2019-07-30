#ifndef __STATION_ESTABLISH_ANALYSE_PARAM_h
#define __STATION_ESTABLISH_ANALYSE_PARAM_h
#include "../BasicDef/GeoShape.h"
#include "../DataModel/EnumDef.h"
#include <string>

struct TxCoverInfo
{
	TxCoverInfo()
	{
		mdFreqMhz = 0.0;
		mdBWMhz = 0.0;
		mdAreaNoInterf = 0.0;
		mdAreaInterf = 0.0;
	}
	//台站ID
	std::string mID;
	//台站名称
	std::string mName;

	std::string mstrEquID;
	//位置
	CGeoPoint mLocation;
	//频率
	double mdFreqMhz;
	//带宽
	double mdBWMhz;

	//不存在干扰时台站的覆盖面积
	double mdAreaNoInterf;
	//存在干扰时台站的覆盖面积
	double mdAreaInterf;
	//台站的信号强度覆盖结果图文件
	std::string mFieldSthFileName;
	//台站的CI结果图文件
	std::string mCIFileName;
};
//设台分析时：与可能受影响的发射机相互受影响的干扰分析结果
typedef struct _AddStation_InterfAnalyse_Result
{
	//新增台站对现网台站的干扰
	std::vector<TxCoverInfo> mvTxInfoList;

	//现网台站对新增台站的干扰
	TxCoverInfo mAddStationCoverInfo;
}AddStationInterfResult;

struct InterModulationInfo
{
	//调制的类别
	std::vector<InterModType> mveInterModType; 

	//调制阶数
	int mnOrder;

	//F1的信息
	int mnIndex1;   //F1台站的索引
	std::string mstrID1;
	std::string mstrEquID1;
	std::string mStationName1;
	double mdFreqMhz1;
	double mdLevel1;  //F1台站在接收机处的功率
	double mdFieldSth1;  //F1台站在接收机处的场强

	//F2的信息
	int mnIndex2;
	std::string mstrID2;
	std::string mstrEquID2;
	std::string mStationName2;
	double mdFreqMhz2;	
	double mdLevel2;  //F2台站在接收机处的功率
	double mdFieldSth2;  //F2台站在接收机处的场强

	//F3的信息
	int mnIndex3;   //F3台站的索引
	std::string mstrID3;
	std::string mstrEquID3;
	std::string mStationName3;
	double mdFreqMhz3;	
	double mdLevel3;  //F3台站在接收机处的功率
	double mdFieldSth3;  //F3台站在接收机处的场强
};

struct InterModulationResult
{
	//接收机的信息
	std::string mstrRxID;
	std::string mstrRxEquID;
	std::string mStationName;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;

	//产生互调干扰的列表
	std::vector<InterModulationInfo> mvInterModulationInfo;
};

struct BlockInterfInfo
{
	int mnIndex;   //产生阻塞干扰的索引
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //在被阻塞接收机处的信号值	
	double mdFieldSth;//在被阻塞接收机处的场强
	double mdProtectRatio; //与被干扰台站之间的保护率
};

struct BlockInterfResult
{
	//接收机信息
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;

	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxBlockLevel; //阻塞门限
	double mdLevel;  //预收信号的功率
	double mdFieldSth;//预收信号的场强	

	std::vector<BlockInterfInfo> mvBlockInterfInfo;
};

//镜频干扰的参数
struct MirrorInterfInfo
{
	int mnIndex;   //产生镜频干扰的索引
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //在被镜频干扰接收机处的功率值	
	double mdFieldSth;//在被镜频干扰接收机处的场强值
	double mdProtectRadio; // 干扰机和预收台站之间的保护率
};

struct MirrorInterfResult
{
	//接收机信息
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxThresholddBm; //接收门限
	double mdImgFreqAtt;  //镜频衰减
	double mdLevel;  //预收信号的功率
	double mdFieldSth;//预收信号的场强	

	std::vector<MirrorInterfInfo> mvImageInterfInfo;
};

//中频干扰的参数
struct MidInterfInfo
{
	int mnIndex;   //产生中频干扰的索引
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //在被中频干扰接收机处的功率值	
	double mdFieldSth;//在被中频干扰接收机处的场强
	double mdProtectRadio; // 干扰机和预收台站之间的保护率
};

struct MidInterfResult
{
	//接收机信息
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxThresholddBm; //接收门限
	double mdLevel;  //预收信号的功率
	double mdFieldSth;//预收信号的场强
	double mdMidFreqAtt;  //中频衰减

	std::vector<MidInterfInfo> mvMidInterfInfo;
};

//谐波干扰的参数
struct HarmonicsInterfInfo
{
	int mnHarmNum;  //谐波次数
	int mnIndex;   //产生谐波干扰的索引
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //在被谐波干扰接收机处的功率值	
	double mdFieldSth;//在被谐波干扰接收机处的场强
	double mdHarmAtt;//谐波衰减
	double mdProtectRadio;
};

struct HarmonicsInterfResult
{
	//接收机信息
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxThresholddBm; //接收门限
	double mdLevel;  //预收信号的功率
	double mdFieldSth;//预收信号的场强
	
	std::vector<HarmonicsInterfInfo> mvHarmonicsInterfInfo;
};

struct SquriousInterfInfo
{
	int mnIndex;  //产生杂散干扰的台站的索引
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //在被干扰接收机处的信号功率
	double mdFieldSth; //在被干扰接收机处的信好强度
	double mdProtectRatio; //与被干扰台站之间的保护率
};

struct SquriousInterfResult
{
	//接收机信息
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxSquriousLevel; //能容忍的杂散门限
	double mdLevel;  //预收信号的功率
	double mdFieldSth;//预收信号的场强

	std::vector<SquriousInterfInfo> mvSquriousInterfInfo;
};

struct DegradationAnalyseResult
{
	//接收机信息
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstRxrEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxThresholddBm;
	double mdRxSNThresholddB;

    double mdFieldSth; //欲收信号的强度
	double mdLevel;    //预收信号的功率

	double mdOldSNValue;
	double mdNewSNValue;
};

struct AddStationAllResult
{
	int mnAddStationInterfStatus;
	int mnInterfModulationStatus;
	int mnBlockInterfStatus;
    int mnSquriousInterfStatus;
	int mnDegradationAnalyseStatus;
	AddStationInterfResult* mpAddStationInterfResult;	
	std::vector<InterModulationResult>* mpvInterfModulationResult;
	std::vector<BlockInterfResult>* mpvBlockInterfResult;
	std::vector<SquriousInterfResult>* mpvSquriousInterfResult;
	std::vector<DegradationAnalyseResult>* mpvDegradationAnalyseResult;
};

struct CoAdjInterfInfo
{
	int mnIndex; //产生干扰的台站的索引
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //在被干扰接收机处的功率值
	double mdFieldSth;//在被干扰接收机处的场强值
	double mdProtectRatio; //与被干扰台站之间的保护率
};

struct CoAdjInterfResult
{
	//链路信息
	//发射机信息
	std::string mstrTxID;
	std::string mstrTxName;
	std::string mstrTxEquID;
	double mdTxFreqMhz;
	double mdTxLongitude;
	double mdTxLatitude;

	//接收机信息
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdThresholddBm; //门限值
	
	double mdFieldSth; // 欲收信号强度
	double mdLevel;    //欲收信号功率

	std::vector<CoAdjInterfInfo> mvCoAdjInterfInfo;
	std::string mResultFilename;
};


#endif