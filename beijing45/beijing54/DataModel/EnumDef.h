#ifndef __DATAMODEL_ENUMDEF_h
#define __DATAMODEL_ENUMDEF_h

//台站类别的枚举
enum EStationType
{
    eUnknownStation = 0,
	eOntTimeRadar = 1,
	eInterPhone = 2,
	eRelayStation = 3
};

enum EBusinessType
{
	eNormal = 0,
	eMediumShort = 1
};

//功率类型
enum EPowerType
{
	eOutputPA = 0,
	eEIRP = 1,
	eERP = 2
};

//计算空间类别
enum ESpaceType
{
	e2D = 0,
	e3D = 1
};

//台站位置情况
enum ELocationType
{
	eOnGround = 0,   //地面台站
	eInAir = 1       //空中台站
};

//高度类别
enum EHeightType
{
	eASeaL = 0,  //海拔高度
	eAGroundL = 1,  //地面以上高度
	eABuildingL = 2 //建筑物之上的高度
};

//覆盖分析计算结果类别
enum ECoverResultType
{
	eUnknownResult = -1,				//未知类型
	ePathloss = 0,						//路径损耗
	eFieldSth = 1,						//场强计算
	ePowerLevel = 2,					//接收功率
	eSignalStrength = 3,				//信号强度
	ePowerFluxDensity = 4,				//功率通量密度
    eSpectrumPowerFluxDensity = 5,		//频谱功率通量密度
	eRequiredPower = 6,					//所需发射功率计算
	eLosRestHeight = 7,					//还差多少可以视通的计算
	eCoAdjIntArea = 8,					//同邻频干扰分析结果
	eBlockInArea = 9,					//阻塞干扰分析结果
	eCoverProbality=12,					//覆盖概率
	eOpticalVisibility = 13,			//视通图
	eRadarCrossSection = 14,			//雷达可识别截面积
	eRadarDetectProb = 15,				//雷达侦测概率
	eSignalNoise = 16,					//信噪比
	eReceivedPower = 17,				//该结果表示的含义为：接收机固定，移动发射机在每个像素点时接收机的接收功率	
	eNetworkCoverage = 18,				//覆盖
	eMaxServerCount = 19,				//最大服务个数
	eBestServer = 20,					//最佳服务
	eClearanceAngle = 21,				//余隙角
	eCommunicationArea=24,//通信畅通覆盖
	eMonitorCoverage=25,//监测覆盖	
	eMonitorSiteSelection=26,//监测区域规划
	eStationStatus=27,      //台站工作状态
	eProbality=28,//概率
	eIntermodulationInt=33,		//互调干扰
	eSpuriousInt=34,		//杂散干扰
	eMirrorInt=35,			//镜频干扰
	eIntermedianInt=36,		//中频干扰
	eHarmonicInt=37,		//谐波干扰
	eBasebandUp=38,			//减敏分析
	eCalHealthArea=42,		//健康安全区,1:安全区 2:中间区 3:危险区
	eSourceAreaAnalysis=43,		//发射源区域快速定位
	eLongMediumShortWave=44,		//长中短波分析
	eUltrashortWave=45,		//超短波分析
	eMicrowave=46,		//微波分析
	eComprehensive=47,		//综合分析
	eObjectSupperssion=48,				//对象压制
	eAreaSupperssion=49,				//区域压制
	eNetworkEvaluation=50,				//监测部署性能评估
	eNetworkSiteSelection=51,					//智能监测网优化
	eNetworkPlan=52,						//智能监测部署
	eBMUF=53, 							 //基本最大可用
	eBLUF=54,  							 //最小可用频率
	eOperMUF=55,						 //工作最大可用
	eOptMUF=56,							 //最优工作频率
	eTimeOccupy=57,                      //时间占用度（陆工大）
	eFreqOccupy=58,                      //频率占用度（陆工大）
	ePowerDensity=59,                    //功率谱密度系数（陆工大）
	eBackPower=60,                       //背景信号强度系数（陆工大）
	eFreqCover=61,                       //频谱重合度系数（陆工大）
	eSpaceDensity=62,                    //电磁信号密度空间密度（陆工大）
	eFreqDensity=63,                     //电磁信号密度频率密度（陆工大）
};

enum ECalculateFunctionType
{
	E_FUNCTION_NULL=-1,
	E_FUNCTION_COVERAGE=0,//计算覆盖的模块功能
	E_FUNCTION_COVERAGESUM=32,//计算综合覆盖的模块功能
	E_FUNCTION_INTCOVERAGE=1,//干扰覆盖的模块功能
	E_FUNCTION_MO_COVERAGE=2,//计算监测覆盖的模块功能
	E_FUNCTION_FREQ_ASSIGN=3, //计算频率指配的模块功能
	E_FUNCTION_LINK_FREQ_ASSIGN=4, //计算链路频率指配的模块功能
	E_FUNCTION_INTLINK=5, //链路干扰分析模块功能
	E_FUNCTION_INTAREA=6, //区域干扰分析模块功能
	E_FUNCTION_INTFREQBAD=7,//保护频带干扰模块功能
	E_FUNCTION_FREQ_OCCUPY=8,//频率占用模块功能(频率预选)
	E_FUNCTION_PERFANCR=9, //台站覆盖能力
	E_FUNCTION_PERFANCRSUM=31, //台站综合覆盖能力
	E_FUNCTION_LINKPROFILE=10,//链路profile模块功能
	E_FUNCTION_SPECTRUMANALYSIS=11,//频谱资源模块功能
	E_FUNCTION_MONITOR_COVERAGE_ANALYSIS=12,//监测覆盖分析
	E_FUNCTION_AOALOCALIZATION=13 ,//AOA定位
	E_FUNCTION_MONITOR_SITESELECTION=14,//监测部署分析,监测区域规划
	E_FUNCTION_MONITORDATAFUSION=15, //监测数据融合
	E_FUNCTION_STATIONSTATUS=16, //台站工作情况分析
	E_FUNCTION_SIGNAL_SUPPRESSION=17,//信号压制
	E_FUNCTION_TDOAPOA=18,//TDOA,POA算法
	E_FUNCTION_TRAJECTORY=19,//轨迹分析
	E_FUNCTION_STATISTICAL_ANALYSIS=20, //台站数据统计分析
	E_FUNCTION_STATISTICAL_REPORT=21,    //监测数据统计报表
	E_FUNCTION_BOUNDARYCOORDINATION=22,  //边境协调
	E_FUNCTION_PROTECTAREAANALYSIS=23,   //保护区计算
	E_FUNCTION_SOURCEAREAANALYSIS=24,     //发射源区域快速定位
	E_FUNCTION_PATHLOSSPREPROCESS=25,     //路径损耗预处理
	E_FUNCTION_SIGNAL_DIS=26,                             //监测信号分析
	E_FUNCTION_STATION_STATUS=27,                  //台站工作状态分析
	E_FUNCTION_SUPERVERSION=28,                       //台站监管分析
	E_FUNCTION_CONTOUR=29,					//台站覆盖轮廓线计算
	E_FUNCTION_HEALTHAREAANALYSIS=30,			//健康安全区计算
	E_FUNCTION_NETWORKSANALYSIS=33,				//网络分析
	E_FUNCTION_NETANA_MAXSERVICE=E_FUNCTION_NETWORKSANALYSIS+1,//网络分析-最大服务
	E_FUNCTION_NETANA_MAXFIELD=E_FUNCTION_NETWORKSANALYSIS+2,//网络分析-最大场强
	E_FUNCTION_NETANA_MAXSERVICE_NUM=E_FUNCTION_NETWORKSANALYSIS+3,//网络分析-最大服务数量
	E_FUNCTION_NETANA_AVAIFIELD=E_FUNCTION_NETWORKSANALYSIS+4,//网络分析-可用场强
	E_FUNCTION_NETANA_CI=E_FUNCTION_NETWORKSANALYSIS+5,//网络分析-覆盖余量
	E_FUNCTION_NETANA_COVEPROBABILITY=E_FUNCTION_NETWORKSANALYSIS+6,//网络分析-覆盖概率
	E_FUNCTION_NETANA_BESTSERVICE=E_FUNCTION_NETWORKSANALYSIS+7,//网络分析-最佳服务
	E_FUNCTION_NETANA_BESTSERVICEFIELD=E_FUNCTION_NETWORKSANALYSIS+8,//网络分析-最佳服务强度
	E_FUNCTION_NETANA_BESTSERVICENUM=E_FUNCTION_NETWORKSANALYSIS+9,//网络分析-最佳服务数量
	E_FUNCTION_NETANA_MAXINT_TOT=E_FUNCTION_NETWORKSANALYSIS+10,//网络分析-最强干扰tot
	E_FUNCTION_NETANA_MAXINTFIELD_TOT=E_FUNCTION_NETWORKSANALYSIS+11,//网络分析-最强干扰强度tot
	E_FUNCTION_NETANA_MAXINT_BOCOV=E_FUNCTION_NETWORKSANALYSIS+12,//网络分析-最强干扰no Cov
	E_FUNCTION_SHORTWAVE_BCR=46,				//BCR
	E_FUNCTION_SHORTWAVE_MUF=47,				//临界频率

};

//监测覆盖分析计算结果类别
enum EMonitorResultType
{
	eSingleCover = 0,  //单站覆盖
	eNetworkCover = 1, //网络覆盖
	eNetworkDirCover = 2, //网络侧向覆盖
	eNetworkLocCover = 3  //网络定位覆盖
};

//SUI传播模型区域类型
enum ArealType
{
	aTown = 1,        //A类型，市区
	aOutskirts = 2,   //B类型，市郊
	aVillage = 3      //C类型，乡村
};

//传播模型类别
enum ETransModel
{
	eTransNull = -1,  //没有设置传播模型,自动选择传播模型 
	eFreeSpace = 0,   //自由空间传播模型
	eCost231Hata1 = 1, //Cost231 hata1模型
	eITURP1546 = 2,   //ITU1546模型	
	eITURP370 = 3,    //ITU370模型
	eLONGLEYRICE = 4, //LONGLEY-RICE传播模型
	eITU533ShortWave = 5, //ITU533 短波模型
	eITU530V10MicWave = 6,  //ITU530 V10微波模型
	eITU618 = 7,        //ITU618雨衰模型
	eAeroNautical = 8,  //航空模型
	eLOSModel = 9,  //视通模型
	eDiffractionModel = 10, //绕射模型
	eIRT3D = 11,    //IRT 3D
    eCost231Hata2 = 12,  //Cost231Hata2传播模型
	eLeeModel = 13,       //Lee 李建业传播模型
	eWalfishIkegami = 14,	
	eSUIModel = 16,       //SUI传播模型
	eGroundWave = 17,     //地波
	eSkyWave = 18,        //天波
	eITU452  = 19,        //ITU452传播模型
	eITU452_10 = 20,      //ITU452-10传播模型
	eFlatEarth = 21,    
	eEgliModel = 22,
	eITU1812 = 23,
	eITU567 = 24,
	eITU619 = 25,
	eHCM = 26,
	eITU676 = 27,
	eITU526 = 28,
	eITU530MicWave = 29,
	eITU1147 = 30,
	eITURP1546_4 = 31,
	eIRT3D_CELL = 32,
	eRaytracing=33,
	eCEPT = 34,
	eAP28 = 35,
	eAP30 = 36,
	eITUSM1448 = 37,
	eNearField = 38,
	eMixedWave = 39
};

//计算结果单位
typedef enum CalResult_Unit
{
	CRUNIT_UNKOWN			= -1,	//未知单位
	CRUNIT_DB				= 0,	//dB
	CRUNIT_DBM				= 1,	//dBm
	CRUNIT_DBUV				= 2,	//dBum
	CRUNIT_DBUV_PER_M		= 3,	//dBum/m
	CRUNIT_DBW_PER_M2		= 4,	//dBw/m2
	CRUNIT_DBW_PER_M2_HZ	= 5,	//dBw/Hz/m2
	CRUNIT_LOS_M            = 6,    //m 差多少米视通
	CRUNIT_PERCENT          =7,		//百分比 
	CRUNIT_RCS_M2           =8,
	CRUNIT_ANGLE			=9,		//角度(度)
	CRUNIT_NUMBER			=10,		//个数
	CRUNIT_FREQMHz				=11     //频率 
};

//数据类别
typedef enum CalResult_DataType
{
	UNKNOWN_DATATYPE = 0,
	DATA_DOUBLE,					//double
	DATA_FLOAT,						//float
	DATA_CHAR,						//char
	DATA_UCHAR,				//unsigned char
	DATA_INT2,						//short
	DATA_UINT2,						//unsigned short
	DATA_INT4,						//int
	DATA_UINT4,						//unsigned int		
};

//区域计算结果类别
typedef enum CalResult_AreaType
{
	CAL_AREA_UNKNOWN = 0,	
	CAL_AREA_RECT,						//矩形计算区域
	CAL_AREA_CIRCLE,					//圆形计算区域
	CAL_AREA_POLYGON,					//多边形计算区域

	CAL_POINT,
	CAL_POLYLINE,
	CAL_PROFILE,
	CAL_LINE
};


//////////////////////////////////////////////////////////////////////////
//定义模块分类的enum
enum EModelType
{
	eUNKNOWNModel = -1,
	eBaseModel = 0,
	eComputePredictionModel = 1,    //计算模块
	eBaseTransModel = 2,  //基本的传播模型模块
	eIRT3DModel = 3,       //3D传播模型
	eInterfAnalyseModel = 4,     //综合干扰分析模块
	eMicwaveLinkAnalyseModel = 5,        //微波链路分析模块
	eShortwaveLinkAnalyseModel = 6,       //
	eFreqAssignModel = 7,         //频率指配模块
	eRadarPerformanceModel = 8,   //雷达效能分析模块
	eCommunicationPerformanceModel = 9,
	eInterfPerformanceModel = 10,
	eProtectFreqSpanModel = 11,
	eMonitorDistributeOptModel = 12,
	eMonitorDeviceInterfaceModel = 13,
	eNewProject = 14,
	e3DShowModel = 15,
	eLongleyRiceModel = 16,
	eITU618Model = 17,
	eMicWave530 = 18,
	eShortWave533 = 19,
	eAirPlaneModel = 20,  //航空模型
	eLeeTransModel = 21,  //李建业模型
	eWalfishIkegamiModel = 22, //Walfish Ikegami模型
	eSUILicenseModel = 23,
	eEgliLicModel = 24,
	eFlatEarthLicModel = 25,
	eITU567LicModel = 26,
	eITU1812LicModel = 27,
	eITU452LicModel = 28,
	eITU452_10LicModel = 29,
	eITU526LicModel = 30,
	eFrequencyOccupyModel=31,//频率占用
	
};

enum ELCType
{
	eHighLC=1,
	eLowLC=2,
	eBothLC=3
};

enum InterModType
{
	TwoF1SubtrasrtF2 = 0,//2F1-F2
	TwoF2SubtrasrtF1,//2F2-F1
	F1AddF2SubtrasrtF3,//F1+F2-F3
	F1AddF3SubtrasrtF2,//F1+F3-F2
	F2AddF3SubtrasrtF1,//F2+F3-F1
	/////////////////////////////五阶
	ThreeF1SubtrasrtTwoF2,//3F1-2F2
	ThreeF2SubtrasrtTwoF1,//3F2-2F1
};

//计算区域的类型  add by xiangl
enum ShapeStyle
{
	eKnow = 0,
	eRect = 1, //矩形
	ePolygon = 2, //多边形
	eCircle  = 3,  //圆
	eAzimuth = 4//大致方向
};

//结果文件类型
enum ResultFileType
{
	eResult_Point=0,//点结果
	eResult_Line,//线结果
	eResult_2D,//二维面结果
	eResult_3D,//三维立体结果
	eResult_XML,//xml
	eResult_Other//其他报表
};

enum CICalculateType
{
	eCI_ADD=0,   //叠加
	eCI_MAX=1    //取最大值
};

typedef CICalculateType MergeCalculateType;

#define IS_RESULTVALUE_VALID(d) (((d)>-10000)&&((d)!=0x81)&&((d)!=0x8181)&&((d)<10000))

#endif
