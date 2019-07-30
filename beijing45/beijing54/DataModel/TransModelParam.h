#ifndef _NG_DataModel_TransModelParam_h
#define _NG_DataModel_TransModelParam_h

#include "../DataModel/EnumDef.h"

//绕射参数
struct ScmDiffParam
{
	ScmDiffParam()
	{
		mdMinHillDisM = 1500;
		mdMinTXDisM = 100;
		mnDiffractionModel =2;
	}
	double mdMinHillDisM;
	double mdMinTXDisM;
	int mnDiffractionModel;
};

//自由空间传播模型
struct ScmFreeSpacePara
{    
	ScmFreeSpacePara()
	{
		//地球曲率因子
		mdKfactor = 1.33333;
		mbUseKfactor = false;
		mbUse3DDistance=false;

		mDiffParam.mnDiffractionModel = 2;
	}
	bool mbUseKfactor;		//是否考虑地球曲率
	bool mbUse3DDistance;   //是否使用3D距离
	double mdKfactor;        //地球曲率因子

	ScmDiffParam mDiffParam;
};

//SUI传播模型
struct SUIParam
{
	SUIParam()
	{
		meAreaType = aTown;
		mdRoodLossA = 4.6;
		mdRoodLossB = 0.007;
		mdRoodLossC = 12.6;
		mdHeightFactor = -10.8;
		mdSFactor = 5.2;

		mDiffParam.mnDiffractionModel = 0;
	}

	~SUIParam(){}

	ArealType meAreaType;
	double mdRoodLossA;        //自由空间损耗参数a
	double mdRoodLossB;        //自由空间损耗参数b
	double mdRoodLossC;        //自由空间损耗参数c
	double mdHeightFactor;     //接收天线高度修正项参数
	double mdSFactor;          //s（阴影衰落）参数	

	ScmDiffParam mDiffParam;
};

//Oku hata 传播模型参数
struct ScmOkuHataPara
{
	 ScmOkuHataPara()
	{
		//初始化为默认参数
		ma0 = 69.55;
		ma1 = 44.9;
		ma2 = 13.82;
		ma3 = 6.55;
		ma4 = 26.16;

		mnCalHeffMethod = 0;
		mnSlopeCorrection = 0;
		mdSlopeCorrDisM = 2000; //2km
		mnSlopeCorrAverage = 0;

		mnAmbientCorr = 1;
		mnMorphoCorr = 0;
		mdMorphoDisM = 1500;//1.5km

		mnFlagCloseRangeExponent = 1;

		mDiffParam.mnDiffractionModel = 2;
	}
	 ScmOkuHataPara(double a0, double a1, double a2, double a3, double a4)
	{
		this->ma0 = a0;
		this->ma1 = a1;
		this->ma2 = a2;
		this->ma3 = a3;
		this->ma4 = a4;		

		mnCalHeffMethod = 0;
		mnSlopeCorrection = 0;
		mdSlopeCorrDisM = 2000; //2km
		mnSlopeCorrAverage = 0;

		mnAmbientCorr = 1;
		mnMorphoCorr = 0;
		mdMorphoDisM = 1500;//1.5km

		mnFlagCloseRangeExponent = 1;

		mDiffParam.mnDiffractionModel = 0;
	}
	~ScmOkuHataPara()
	{
	}

	//hata模型的系数
	double ma0;
	double ma1;
	double ma2;
	double ma3;
	double ma4;	

	//计算有效高度的方式
	int mnCalHeffMethod;

	//进行斜坡修正的方式
	 int mnSlopeCorrection;

	 //斜坡修正的距离
	 double mdSlopeCorrDisM; 

	 //是否对斜坡修正取平均
	 short mnSlopeCorrAverage;

	 //是否进行环境的修正
	 int mnAmbientCorr;

	 //地貌修正类别
	 int mnMorphoCorr;

	 //地貌类型取平均的距离
	 double mdMorphoDisM;

	 //是否进行20公里外修正
	 int mnFlagCloseRangeExponent;

	//绕射参数
	ScmDiffParam mDiffParam;
};


//1546 传播模型参数
struct ScmITU1546Para
{    
	ScmITU1546Para()
	{
		mdTimeProb = 50;
		mdLocationProb = 50;

		mbUseTXClearance = false;
		mbUseRXClearance = true;
		mbMobileAntCorr = false;
		mbUseLandSeaDis = false;		

		//地球曲率因子
		mdKfactor = 1.33333;

		mdMaxDistanceKM = 16.0;//km

		mDiffParam.mnDiffractionModel = 0;
	}
	//传播模型指定概率
	double mdTimeProb;          //时间概率
	double mdLocationProb;      //地点概率
	
	//修正选择
	bool mbUseTXClearance;      //发射端遮蔽角修正
	bool mbUseRXClearance;      //接收端遮蔽角修正
	bool mbMobileAntCorr;       //接收端天晓高度修正
	bool mbUseLandSeaDis;       //用水陆混合模型	

	//其他参数
	double mdKfactor;            //地球曲率因子
	double mdMaxDistanceKM;      //接收端遮蔽角修正考虑的最大距离

	//绕射参数	
	ScmDiffParam mDiffParam;	
};

//1546 传播模型参数
struct ScmITU1546V4Para:public ScmITU1546Para
{    
	ScmITU1546V4Para()
	{
		mdTimeProb = 50;
		mdLocationProb = 50;

		mbUseTXClearance = true;
		mbUseRXClearance = true;
		mbMobileAntCorr = true;
		mbUseLandSeaDis = false;	
		mbUseScater = false;

		//地球曲率因子
		mdKfactor = 1.33333;

		mdMaxDistanceKM = 16.0;//km

		mDiffParam.mnDiffractionModel = 0;
	}
	//传播模型指定概率
	double mdTimeProb;          //时间概率
	double mdLocationProb;      //地点概率

	//修正选择
	bool mbUseTXClearance;      //发射端遮蔽角修正
	bool mbUseRXClearance;      //接收端遮蔽角修正
	bool mbMobileAntCorr;       //接收端天晓高度修正
	bool mbUseLandSeaDis;       //用水陆混合模型	
	bool mbUseScater;           //是否考虑散射 

	//其他参数
	double mdKfactor;            //地球曲率因子
	double mdMaxDistanceKM;      //接收端遮蔽角修正考虑的最大距离

	//绕射参数	
	ScmDiffParam mDiffParam;	
};

//370 传播模型参数
struct ScmITU370Para
{    
	ScmITU370Para()
	{
		mdTimeProb = 50;
		mdLocationProb = 50;
		
		mbUseRXClearance = true;		
		mbUseLandSeaDis = false;
		mbUseTerrainRoughness = false;		

		mdMaxDistanceKM = 16.0;//km		
	}
	double mdTimeProb;            //时间概率
	double mdLocationProb;      //地点概率
	
	bool mbUseRXClearance;   //接收端遮蔽角修正	
	bool mbUseLandSeaDis;     //用水陆混合模型
	bool mbUseTerrainRoughness; //用地形崎岖度修正

	double mdMaxDistanceKM;      //接收端遮蔽角修正考虑的最大距离
};

//视通传播模型
struct ScmLosPara
{
	ScmLosPara()
	{
		mdKfactor = 1.33333;
	}
	double mdKfactor; 
};

//Longly Rice传播模型参数
struct ScmLonglyRicePara
{
	ScmLonglyRicePara()
	{
		mdKfactor = 1.33333;
		mdConductivitySm = 0.05; 
		mdPermitivity = 25;
		mdSituationProb = 50.0;
		mdLoctionProb = 50.0;
		mdTimeProb = 50.0;
		mnClimateMode = 4;
		mnServiceMode = 3;		
	}
	//地球曲率因子
	double mdKfactor; 

	//电导率
	double mdConductivitySm;

	//相对介电常数
	double mdPermitivity;

	//Situation概率
	double mdSituationProb;

	//时间概率
	double mdTimeProb;

	//地点概率
	double mdLoctionProb;

	//气候0:赤道，1:大陆亚热带，2:海岸亚热带，3:沙漠，4:温带大陆性，5:中等海岸陆路，6:温带海岸
	int mnClimateMode;

	//服务类别 SingleMessage=0,Accidental,Mobile,Broadcast};
	int mnServiceMode;	
};

//ITU618传播模型参数
struct ScmITU618Para
{
	ScmITU618Para()
	{
		mdKfactor = 1.33333;
		mbCalKFactor = true;

		mdWaterVapourDensity = 7.35;
		mbCalWaterVapourDensity = false;

		mdRainHeight = 3;
		mbCalRainHeight = false;

		mdRainRate = 0.0;
		mbCalRainRate = false;

		mdElevationAngle = 0;
		mbCalElevationAngle = false;
		mbCalWaterVapourDensity=false;

		mbUseFaradayEffect = true;
		mbUseGasAttenuation = true;
		mbUseRainAttenuation = true;
		mbUseDefocussingAttenuation = true;
		
		mdElectronContent = 1e+18;
		mdStrengthEarthMagneticField = 0.0;
		mdTimeProbability = 0.01;  //0.01%

		mdTemperature = 25;
		mdAirPressure = 1014;

		mDiffParam.mnDiffractionModel = 2;
	}
	//地球曲率因子
	double mdKfactor;

	//是否计算地球曲率因子
	bool mbCalKFactor;

	//水汽密度
	double mdWaterVapourDensity; 

	//是否计算水汽密度
	bool mbCalWaterVapourDensity;

	//rain height
	double mdRainHeight;

	//是否计算rainheight
	bool mbCalRainHeight;

	//rain rate
	double mdRainRate;

	//是否计算RainRate
	bool mbCalRainRate;

	//elevation angle
	double mdElevationAngle;

	//是否计算倾角
	bool mbCalElevationAngle;

	//是否使用法拉第效应
	bool mbUseFaradayEffect;

    //是否使用气体衰减
	bool mbUseGasAttenuation;

	//是否使用雨量衰减
	bool mbUseRainAttenuation;

	//是否使用散焦衰减
	bool mbUseDefocussingAttenuation;

	double mdElectronContent;

	double mdStrengthEarthMagneticField;

	double mdTimeProbability; //时间概率

	//温度
	double mdTemperature;

	//大气压强
	double mdAirPressure;

	//
	ScmDiffParam mDiffParam;
};

//Walfish Ikegami传播模型参数
struct ScmWalfishIkegamiPara
{
	ScmWalfishIkegamiPara()
	{
		//自由空间（视通）
		md1 = 32.4;
		md2 = 20.0;
		md3 = 20.0;

		// 自由空间（非视通）
		ms1 = 42.6;
		ms2 = 26.0;
		ms3 = 20.0;

		//MSD系数
		mm1 = -18.0;
		mm2 = 54.0;
		mm3 = -0.8;
		mm4 = -1.6;
		mm5 = 18.0;
		mm6 = 33.0;
		mm7 = -15.0;
		mm8 = -4.0;
		mm9 = 0.7;
		mm10 = 925.0;
		mm11 = 1.5;

		//rts系数
		mr1 = -16.9;
		mr2 = -10.0;
		mr3 = 0.354;
		mr4 = 2.5;
		mr5 = 0.075;
		mr6 = 4.0;
		mr7 = -0.114;

		//统计参数
		mbCalAverValue = false;  //目前先设置为不用计算
		mphi_Grad = 32.5;	 
		mb_m = 2;
		mw_m = 8;	 
		mh_m = 12.0;
		// 权重
		m_rts = 1;		// roof top to street diffraction and scatter
		m_msd = 1;		// multiple screen diffraction
		//有效值范围
		mminDistance_m = 20.0; //min distance
		mmaxDistance_m = 5000; //max distance
		mminFrequenz_MHz = 800;
		mmaxFrequenz_MHz = 2000;

        mdKfactor = 1.33333;
		mbUseEarthCurvature = false;
	}
	//自由空间（视通）
	double				md1;			// 32.4
	double				md2;			// 20.0
	double				md3;			// 20.0
	// 自由空间（非视通）
	double				ms1;			// 42.6
	double				ms2;			// 26.0
	double				ms3;			// 20.0
	//MSD系数
	double				mm1;			// -18.0
	double				mm2;			// 54.0
	double				mm3;			// -0.8
	double				mm4;			// -1.6
	double				mm5;			// 18.0
	double				mm6;			// 33.0
	double				mm7;			// -15.0
	double				mm8;			// -4.0
	double				mm9;			// 0.7
	double				mm10;		// 925.0 
	double				mm11;		// 1.5
	//rts系数
	double				mr1;			// -16.9
	double				mr2;			// -10.0
	double				mr3;			// 0.354
	double				mr4;			// 2.5
	double				mr5;			// 0.075
	double				mr6;			// 4.0
	double				mr7;			// -0.114
	//统计参数
	bool                mbCalAverValue;    //是否计算下面几个统计参数
	double				mphi_Grad;	 
	double				mb_m;		 
	double				mw_m;		 
	double				mh_m;		 
	// 权重
	double				m_rts;		// roof top to street diffraction and scatter
	double				m_msd;		// multiple screen diffraction
	//有效值范围
	double				mminDistance_m; //min distance
	double				mmaxDistance_m; //max distance
	double				mminFrequenz_MHz;
	double				mmaxFrequenz_MHz;

	bool                mbUseEarthCurvature;
	double              mdKfactor;
	
	long                mnMorphoNum;
	long		    *mpMorphoMapper;
};

//ITU530传播模型参数
struct ScmITU530Para
{
	ScmITU530Para()
	{
		mbUseEarthCurvature = true;
		mdKfactor = 1.33333;
	    mTimeProb = 95;
		mRainRate = 22;		
		mTemperature_C = 15;
		mHumidity_g_m3 = 7.5;

		mGeoClimateFactor = 3.6e-9;
		mKfactorStatic = 0;
		mStatisticMonth = 0;	
	}
	bool    mbUseEarthCurvature;
	double  mdKfactor;
	
	double  mTimeProb;  //时间概率
	double	mRainRate;	
	double	mTemperature_C;
	double	mHumidity_g_m3;	
	double	mGeoClimateFactor;
	short	mKfactorStatic;
	short	mStatisticMonth;
};

//ITU530传播模型参数
struct ScmITU530V10Para
{
       ScmITU530V10Para()
	{
		mbUseEarthCurvature = true;
		mdKfactor = 1.33333;
		mPolarizationAngle = 0.0;
		mRefractiveIndex1Km = -325;
		mTerrainRoughness = 0;
		mRainRate = 22;
		mPressure_hPa = 1013;
		mTemperature_C = 15;
		mHumidity_g_m3 = 7.5;
		
		mStatisticsTime = 720;
		mFadingDepth = 1;
		
		mCalRefractiveIndex1Km = 0;
		mCalcRainRate = 0;
		mWorstMonth = 0;
		mGeoFlag = 0;

		mQ1 = 2.85;
		mBeta = 0.13;
		mHeightMeltingZone = 5000;
		mBinHeight = 100;	
		mTimeProb=50;
		
	}
	bool    mbUseEarthCurvature;
	double  mdKfactor;

	double	mPolarizationAngle;

	double  mTimeProb;  //时间概率

	double	mRefractiveIndex1Km;
	double	mTerrainRoughness;
	double	mRainRate;
	double	mPressure_hPa;
	double	mTemperature_C;
	double	mHumidity_g_m3;

	long	*mpMorphoMapper;

	double	mStatisticsTime;  //统计时长

	// Settings
	double	mFadingDepth;

	short	mCalRefractiveIndex1Km;
	short	mCalcRainRate;
	short	mWorstMonth;
	short	mGeoFlag;

	double mQ1;
	double mBeta;
	double mHeightMeltingZone;
	double mBinHeight;
};

//Lee传播模型参数
struct ScmLeePara
{
	ScmLeePara()
	{
		mbUseEarthCurvature = false;
		mbUseMorphoData = false;
		mbUse3DDistance = true;
		mbUseSlopeCorrection = false;
		
		mdKfactor = 1.33333;
		mdExponentN = 2.5;
		mdSlopeGamma = 20.0;

		mDiffParam.mnDiffractionModel = 0;
	}
	bool mbUseEarthCurvature;   //是否使用地球曲率
	bool mbUseMorphoData;       //是否使用地貌数据
	bool mbUse3DDistance;       //是否使用3D距离
	bool mbUseSlopeCorrection; //是否使用斜坡修正
	
	double mdKfactor; //地球曲率因子
	double mdExponentN;//频率系数n
	double mdSlopeGamma; //距离因子γ

	ScmDiffParam mDiffParam;	
};

//航空传播模型参数
struct ScmAeronauticalPara
{
	ScmAeronauticalPara()
	{
		mbUseEarthCurvature = false;
		mbUseMorphoData = true;
		mbUse3DDistance = true;
	
		mdKfactor = 1.33333;	

		mDiffParam.mnDiffractionModel = 0;
	}
	bool mbUseEarthCurvature;   //是否使用地球曲率
	bool mbUseMorphoData;       //是否使用地貌数据
	bool mbUse3DDistance;       //是否使用3D距离
	
	double mdKfactor; //地球曲率因子

	ScmDiffParam mDiffParam;	
};

//533短波传播模型参数
struct ScmShortWavePara
{
	ScmShortWavePara()
	{
		mdConductivity = 0.1;
		mdRelativePermitivity = 10;
		mnVersionNumber = 1;
		mdRequireSNR = 10;
		mManMadeNoiseType = 2;
		mdTimeProb = 50;
		mnYear = 2013;
		mnMonth = 10;
		mnHour = 17;
		mnSunSpotNumber = 140;
		mdMinElevation=6;
		mszBinDataPath[0] = 0;
	}
	double mdConductivity;
	double mdRelativePermitivity;
	int mnVersionNumber;
	double mdRequireSNR;
	double mdTimeProb;
	int mnYear;
	int mnMonth;
	int	mnHour;
	int	mnSunSpotNumber;	
	int mManMadeNoiseType;//人为噪声类别 1:城市 2:住宅区 3:农村 4:宁静乡村
	double mdMinElevation;  //最小仰角,单位度
	char mszBinDataPath[256];//短波传播模型用到的电离层参数
};

struct ScmITU452ModelPara
{
	ScmITU452ModelPara()
	{
		mbUseKFactor = false;
		mbUseMorphoData = false;
		mdKfactor = 1.33333;
		mdTimeProc = 12.0;
		mdTimeProcGra = 15.0;
		mTemperature_C = 15.0;
		mdWaterVapourDensity = 7.5;
		mdReflectLoss = 39.0;
	}

	bool mbUseKFactor;
	double mdKfactor;
	bool mbUseMorphoData;
	double mdTimeProc;
	double mdTimeProcGra;//时间概率梯度
	double mTemperature_C;
	double mdWaterVapourDensity; //水蒸气密度
	double mdReflectLoss;   //反射损耗
};

struct ScmITU452V10ModelPara
{
	ScmITU452V10ModelPara()
	{
		mdTimeProbPercent = 50.0;
		mdTemperatureDegree = 15.0;
		mdPresurehPa = 1015.0;
		mdDensityWater_g_cm3 = 7.5;
		mdHorizonDistanceSender_m = 100.0;
		mnWorstMonth = 0;
		mnCalTerrainAngle = 0;
	}

	double	mdTimeProbPercent;
	double	mdTemperatureDegree;
	double	mdPresurehPa;

	short	mnWorstMonth;
	short   mnCalTerrainAngle;
	
	double	mdDensityWater_g_cm3;		// Calculated in ducting, space,troposcatter //used in 676

	double	mdHorizonDistanceSender_m;		// Computed in view check
};

struct IRTCalPara
{
	IRTCalPara()
	{
		//给这些参数置上默认值
		nReflectionMode = 1;
		nClutterMode = 0;
		nServiceMode = 5;
		fReflectAttenuation = 20.0f;
	}
	short nReflectionMode;
	short nClutterMode;
	short nServiceMode;
	float fReflectAttenuation;
};

struct ScmSkyWavePara
{    
	ScmSkyWavePara()
	{
		nSunSpotNumber = 100;
		nMonth = 1;
		dHour = 0.0;
	}
	long   nSunSpotNumber;  //天阳黑子的数量
	long   nMonth;		//月									// 1-12
	double	dHour;			//小时		
};

//add by Liuqingmei@20130220
//地波的传播模型参数
enum GeologyType
{
	Good_Soil,
	Medium_Soil,
	Poor_Soil,
	Fresh_Water,
	Sea_Water,
	User_Defined
};
struct ScmGroundWavePara
{
	ScmGroundWavePara()
	{
		dPermittivity = 30;
		dConductivitymSm = 10.0;

		gtype = Good_Soil;
		dRefractivity = 315;
		dScaleHeight = 7.35;

		nCalMode = 1; //默认为Millington,目前有两种，一种为Effective，另外一种为Millington
		nCurveSelect = 0; //目前曲线只有一种，ITU368

		nPolarType = 1;

		bConsiderTopo = false;
	}
	
	//添加变量
	double dPermittivity; //介电常数
	double dConductivitymSm;//电导率，单位ms/m

	GeologyType gtype;//地址类别

	double dRefractivity ;//对流层大气折射率
	double dScaleHeight ; //对流层高度 km

	int nCalMode;    //计算方式
	int nCurveSelect;//传播模型曲线选择	

	int nPolarType;// 极化方式 1 ： 垂直极化 2：水平极化

	bool bConsiderTopo;
};

struct ScmITU1812ModelPara
{
	ScmITU1812ModelPara()
	{
		timeProb = 50;
		locationProb = 50;

		N0 = 330;
		dN = 45;

		bTroposphericScatter = 0; //默认不考虑		
		bBuildEntryLoss = 0;
		bTerminalClutterLoss = 0;
	}

	float timeProb;            //时间概率
	float locationProb;      //地点概率

	//是否考虑对流层散射
	short bTroposphericScatter;

	short bBuildEntryLoss;  //0:不计算，1：计算
	short bTerminalClutterLoss;  //终端地貌类型损耗	

	//散射模型的N0值
	double N0;

	//计算地球有效半径的dN值
	double dN;
};

struct ScmEgliModelPara
{
	ScmEgliModelPara()
	{
		mbUseEarthCurvature = false;
		//mbUseMorphoData = true;		

		mdKfactor = 1.33333;	

		mDiffParam.mnDiffractionModel = 0;
	}

	bool mbUseEarthCurvature;   //是否使用地球曲率
	//bool mbUseMorphoData;       //是否使用地貌数据

	double mdKfactor; //地球曲率因子

	ScmDiffParam mDiffParam;
};

struct ScmFlatEarthModelPara
{
	ScmFlatEarthModelPara()
	{
		mbUseEarthCurvature = false;
		//mbUseMorphoData = true;		

		mdKfactor = 1.33333;	

		mDiffParam.mnDiffractionModel = 0;
	}

	bool mbUseEarthCurvature;   //是否使用地球曲率
	//bool mbUseMorphoData;       //是否使用地貌数据

	double mdKfactor; //地球曲率因子

	ScmDiffParam mDiffParam;
};

struct ScmITU567ModelPara
{
	ScmITU567ModelPara()
	{
		mdTimeProc = 0.5;
		mdLocProc = 0.5;
	}
	
	double mdTimeProc;  //时间概率
	double mdLocProc;   //地点概率
};

typedef ScmITU618Para ScmITU676ModelPara;
// struct ScmITU619ModelPara
// {
// 	ScmITU619ModelPara()
// 	{
// 		
// 	}	
// };
typedef ScmITU618Para ScmITU619ModelPara;

struct ScmHCMModelPara
{
	ScmHCMModelPara()
	{
		mbUseKFactor = false;
		mbUseMorphoData = false;
		mdKfactor = 1.33333;
		mdTimeProc = 12.0;
		mdTimeProcGra = 15.0;
		mTemperature_C = 15.0;
		mdWaterVapourDensity = 7.5;
		mdRefractivity = 39.0;
	}

	bool mbUseKFactor;
	double mdKfactor;
	bool mbUseMorphoData;
	double mdTimeProc;
	double mdTimeProcGra;//时间概率梯度
	double mTemperature_C;
	double mdWaterVapourDensity; //水蒸气密度
	double mdRefractivity;   //折射率
};

// struct ScmITU676ModelPara
// {
// 	ScmITU676ModelPara()
// 	{
// 		mTemperature_C = 15;
// 		mdWaterVapourDensity = 7.5;
// 		mdPresurehPa = 1014;		
// 	}
// 
// 	double mTemperature_C;
// 	double mdWaterVapourDensity; //水蒸气密度
// 	double mdPresurehPa;   //气压
// 
// 	ScmDiffParam mDiffParam;
// };

struct ScmITU526ModelPara
{
	ScmITU526ModelPara()
	{
	   mnPolarization=0;
	   mdKfactor=1.33333;
	   mdRelativePermittivity=25;
	   mdEffectiveConductivity=0.05;
	}

	//极化方式
	short mnPolarization;  //0: 水平极化，1:垂直极化

	//地球曲率因子
	double mdKfactor;

	//相对介电常数
	double mdRelativePermittivity;

	//有效电导率
	double mdEffectiveConductivity;
};

struct ScmITUSM1448
{
	ScmITUSM1448()
	{
		mdKfactor = 1.33333;
		mdTXTimeProb = 50.0;
		mdRXTimeProb = 50.0;
		mnEqupmentType = 1;		
	}
	double mdKfactor; //地球曲率因子
	double mdTXTimeProb;  //发射台站时间概率
	double mdRXTimeProb; //接受台站时间概率
	short  mnEqupmentType; //1:发射设备，2：接收设备
};

struct ScmNearFieldPara
{

};

#endif