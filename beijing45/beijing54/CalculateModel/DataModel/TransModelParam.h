#ifndef _NG_DataModel_TransModelParam_h
#define _NG_DataModel_TransModelParam_h

#include "../DataModel/EnumDef.h"

//�������
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

//���ɿռ䴫��ģ��
struct ScmFreeSpacePara
{    
	ScmFreeSpacePara()
	{
		//������������
		mdKfactor = 1.33333;
		mbUseKfactor = false;
		mbUse3DDistance=false;

		mDiffParam.mnDiffractionModel = 2;
	}
	bool mbUseKfactor;		//�Ƿ��ǵ�������
	bool mbUse3DDistance;   //�Ƿ�ʹ��3D����
	double mdKfactor;        //������������

	ScmDiffParam mDiffParam;
};

//SUI����ģ��
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
	double mdRoodLossA;        //���ɿռ���Ĳ���a
	double mdRoodLossB;        //���ɿռ���Ĳ���b
	double mdRoodLossC;        //���ɿռ���Ĳ���c
	double mdHeightFactor;     //�������߸߶����������
	double mdSFactor;          //s����Ӱ˥�䣩����	

	ScmDiffParam mDiffParam;
};

//Oku hata ����ģ�Ͳ���
struct ScmOkuHataPara
{
	 ScmOkuHataPara()
	{
		//��ʼ��ΪĬ�ϲ���
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

	//hataģ�͵�ϵ��
	double ma0;
	double ma1;
	double ma2;
	double ma3;
	double ma4;	

	//������Ч�߶ȵķ�ʽ
	int mnCalHeffMethod;

	//����б�������ķ�ʽ
	 int mnSlopeCorrection;

	 //б�������ľ���
	 double mdSlopeCorrDisM; 

	 //�Ƿ��б������ȡƽ��
	 short mnSlopeCorrAverage;

	 //�Ƿ���л���������
	 int mnAmbientCorr;

	 //��ò�������
	 int mnMorphoCorr;

	 //��ò����ȡƽ���ľ���
	 double mdMorphoDisM;

	 //�Ƿ����20����������
	 int mnFlagCloseRangeExponent;

	//�������
	ScmDiffParam mDiffParam;
};


//1546 ����ģ�Ͳ���
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

		//������������
		mdKfactor = 1.33333;

		mdMaxDistanceKM = 16.0;//km

		mDiffParam.mnDiffractionModel = 0;
	}
	//����ģ��ָ������
	double mdTimeProb;          //ʱ�����
	double mdLocationProb;      //�ص����
	
	//����ѡ��
	bool mbUseTXClearance;      //������ڱν�����
	bool mbUseRXClearance;      //���ն��ڱν�����
	bool mbMobileAntCorr;       //���ն������߶�����
	bool mbUseLandSeaDis;       //��ˮ½���ģ��	

	//��������
	double mdKfactor;            //������������
	double mdMaxDistanceKM;      //���ն��ڱν��������ǵ�������

	//�������	
	ScmDiffParam mDiffParam;	
};

//1546 ����ģ�Ͳ���
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

		//������������
		mdKfactor = 1.33333;

		mdMaxDistanceKM = 16.0;//km

		mDiffParam.mnDiffractionModel = 0;
	}
	//����ģ��ָ������
	double mdTimeProb;          //ʱ�����
	double mdLocationProb;      //�ص����

	//����ѡ��
	bool mbUseTXClearance;      //������ڱν�����
	bool mbUseRXClearance;      //���ն��ڱν�����
	bool mbMobileAntCorr;       //���ն������߶�����
	bool mbUseLandSeaDis;       //��ˮ½���ģ��	
	bool mbUseScater;           //�Ƿ���ɢ�� 

	//��������
	double mdKfactor;            //������������
	double mdMaxDistanceKM;      //���ն��ڱν��������ǵ�������

	//�������	
	ScmDiffParam mDiffParam;	
};

//370 ����ģ�Ͳ���
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
	double mdTimeProb;            //ʱ�����
	double mdLocationProb;      //�ص����
	
	bool mbUseRXClearance;   //���ն��ڱν�����	
	bool mbUseLandSeaDis;     //��ˮ½���ģ��
	bool mbUseTerrainRoughness; //�õ�����᫶�����

	double mdMaxDistanceKM;      //���ն��ڱν��������ǵ�������
};

//��ͨ����ģ��
struct ScmLosPara
{
	ScmLosPara()
	{
		mdKfactor = 1.33333;
	}
	double mdKfactor; 
};

//Longly Rice����ģ�Ͳ���
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
	//������������
	double mdKfactor; 

	//�絼��
	double mdConductivitySm;

	//��Խ�糣��
	double mdPermitivity;

	//Situation����
	double mdSituationProb;

	//ʱ�����
	double mdTimeProb;

	//�ص����
	double mdLoctionProb;

	//����0:�����1:��½���ȴ���2:�������ȴ���3:ɳĮ��4:�´���½�ԣ�5:�еȺ���½·��6:�´�����
	int mnClimateMode;

	//������� SingleMessage=0,Accidental,Mobile,Broadcast};
	int mnServiceMode;	
};

//ITU618����ģ�Ͳ���
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
	//������������
	double mdKfactor;

	//�Ƿ���������������
	bool mbCalKFactor;

	//ˮ���ܶ�
	double mdWaterVapourDensity; 

	//�Ƿ����ˮ���ܶ�
	bool mbCalWaterVapourDensity;

	//rain height
	double mdRainHeight;

	//�Ƿ����rainheight
	bool mbCalRainHeight;

	//rain rate
	double mdRainRate;

	//�Ƿ����RainRate
	bool mbCalRainRate;

	//elevation angle
	double mdElevationAngle;

	//�Ƿ�������
	bool mbCalElevationAngle;

	//�Ƿ�ʹ�÷�����ЧӦ
	bool mbUseFaradayEffect;

    //�Ƿ�ʹ������˥��
	bool mbUseGasAttenuation;

	//�Ƿ�ʹ������˥��
	bool mbUseRainAttenuation;

	//�Ƿ�ʹ��ɢ��˥��
	bool mbUseDefocussingAttenuation;

	double mdElectronContent;

	double mdStrengthEarthMagneticField;

	double mdTimeProbability; //ʱ�����

	//�¶�
	double mdTemperature;

	//����ѹǿ
	double mdAirPressure;

	//
	ScmDiffParam mDiffParam;
};

//Walfish Ikegami����ģ�Ͳ���
struct ScmWalfishIkegamiPara
{
	ScmWalfishIkegamiPara()
	{
		//���ɿռ䣨��ͨ��
		md1 = 32.4;
		md2 = 20.0;
		md3 = 20.0;

		// ���ɿռ䣨����ͨ��
		ms1 = 42.6;
		ms2 = 26.0;
		ms3 = 20.0;

		//MSDϵ��
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

		//rtsϵ��
		mr1 = -16.9;
		mr2 = -10.0;
		mr3 = 0.354;
		mr4 = 2.5;
		mr5 = 0.075;
		mr6 = 4.0;
		mr7 = -0.114;

		//ͳ�Ʋ���
		mbCalAverValue = false;  //Ŀǰ������Ϊ���ü���
		mphi_Grad = 32.5;	 
		mb_m = 2;
		mw_m = 8;	 
		mh_m = 12.0;
		// Ȩ��
		m_rts = 1;		// roof top to street diffraction and scatter
		m_msd = 1;		// multiple screen diffraction
		//��Чֵ��Χ
		mminDistance_m = 20.0; //min distance
		mmaxDistance_m = 5000; //max distance
		mminFrequenz_MHz = 800;
		mmaxFrequenz_MHz = 2000;

        mdKfactor = 1.33333;
		mbUseEarthCurvature = false;
	}
	//���ɿռ䣨��ͨ��
	double				md1;			// 32.4
	double				md2;			// 20.0
	double				md3;			// 20.0
	// ���ɿռ䣨����ͨ��
	double				ms1;			// 42.6
	double				ms2;			// 26.0
	double				ms3;			// 20.0
	//MSDϵ��
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
	//rtsϵ��
	double				mr1;			// -16.9
	double				mr2;			// -10.0
	double				mr3;			// 0.354
	double				mr4;			// 2.5
	double				mr5;			// 0.075
	double				mr6;			// 4.0
	double				mr7;			// -0.114
	//ͳ�Ʋ���
	bool                mbCalAverValue;    //�Ƿ�������漸��ͳ�Ʋ���
	double				mphi_Grad;	 
	double				mb_m;		 
	double				mw_m;		 
	double				mh_m;		 
	// Ȩ��
	double				m_rts;		// roof top to street diffraction and scatter
	double				m_msd;		// multiple screen diffraction
	//��Чֵ��Χ
	double				mminDistance_m; //min distance
	double				mmaxDistance_m; //max distance
	double				mminFrequenz_MHz;
	double				mmaxFrequenz_MHz;

	bool                mbUseEarthCurvature;
	double              mdKfactor;
	
	long                mnMorphoNum;
	long		    *mpMorphoMapper;
};

//ITU530����ģ�Ͳ���
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
	
	double  mTimeProb;  //ʱ�����
	double	mRainRate;	
	double	mTemperature_C;
	double	mHumidity_g_m3;	
	double	mGeoClimateFactor;
	short	mKfactorStatic;
	short	mStatisticMonth;
};

//ITU530����ģ�Ͳ���
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

	double  mTimeProb;  //ʱ�����

	double	mRefractiveIndex1Km;
	double	mTerrainRoughness;
	double	mRainRate;
	double	mPressure_hPa;
	double	mTemperature_C;
	double	mHumidity_g_m3;

	long	*mpMorphoMapper;

	double	mStatisticsTime;  //ͳ��ʱ��

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

//Lee����ģ�Ͳ���
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
	bool mbUseEarthCurvature;   //�Ƿ�ʹ�õ�������
	bool mbUseMorphoData;       //�Ƿ�ʹ�õ�ò����
	bool mbUse3DDistance;       //�Ƿ�ʹ��3D����
	bool mbUseSlopeCorrection; //�Ƿ�ʹ��б������
	
	double mdKfactor; //������������
	double mdExponentN;//Ƶ��ϵ��n
	double mdSlopeGamma; //�������Ӧ�

	ScmDiffParam mDiffParam;	
};

//���մ���ģ�Ͳ���
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
	bool mbUseEarthCurvature;   //�Ƿ�ʹ�õ�������
	bool mbUseMorphoData;       //�Ƿ�ʹ�õ�ò����
	bool mbUse3DDistance;       //�Ƿ�ʹ��3D����
	
	double mdKfactor; //������������

	ScmDiffParam mDiffParam;	
};

//533�̲�����ģ�Ͳ���
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
	int mManMadeNoiseType;//��Ϊ������� 1:���� 2:סլ�� 3:ũ�� 4:�������
	double mdMinElevation;  //��С����,��λ��
	char mszBinDataPath[256];//�̲�����ģ���õ��ĵ�������
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
	double mdTimeProcGra;//ʱ������ݶ�
	double mTemperature_C;
	double mdWaterVapourDensity; //ˮ�����ܶ�
	double mdReflectLoss;   //�������
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
		//����Щ��������Ĭ��ֵ
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
	long   nSunSpotNumber;  //�������ӵ�����
	long   nMonth;		//��									// 1-12
	double	dHour;			//Сʱ		
};

//add by Liuqingmei@20130220
//�ز��Ĵ���ģ�Ͳ���
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

		nCalMode = 1; //Ĭ��ΪMillington,Ŀǰ�����֣�һ��ΪEffective������һ��ΪMillington
		nCurveSelect = 0; //Ŀǰ����ֻ��һ�֣�ITU368

		nPolarType = 1;

		bConsiderTopo = false;
	}
	
	//��ӱ���
	double dPermittivity; //��糣��
	double dConductivitymSm;//�絼�ʣ���λms/m

	GeologyType gtype;//��ַ���

	double dRefractivity ;//���������������
	double dScaleHeight ; //������߶� km

	int nCalMode;    //���㷽ʽ
	int nCurveSelect;//����ģ������ѡ��	

	int nPolarType;// ������ʽ 1 �� ��ֱ���� 2��ˮƽ����

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

		bTroposphericScatter = 0; //Ĭ�ϲ�����		
		bBuildEntryLoss = 0;
		bTerminalClutterLoss = 0;
	}

	float timeProb;            //ʱ�����
	float locationProb;      //�ص����

	//�Ƿ��Ƕ�����ɢ��
	short bTroposphericScatter;

	short bBuildEntryLoss;  //0:�����㣬1������
	short bTerminalClutterLoss;  //�ն˵�ò�������	

	//ɢ��ģ�͵�N0ֵ
	double N0;

	//���������Ч�뾶��dNֵ
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

	bool mbUseEarthCurvature;   //�Ƿ�ʹ�õ�������
	//bool mbUseMorphoData;       //�Ƿ�ʹ�õ�ò����

	double mdKfactor; //������������

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

	bool mbUseEarthCurvature;   //�Ƿ�ʹ�õ�������
	//bool mbUseMorphoData;       //�Ƿ�ʹ�õ�ò����

	double mdKfactor; //������������

	ScmDiffParam mDiffParam;
};

struct ScmITU567ModelPara
{
	ScmITU567ModelPara()
	{
		mdTimeProc = 0.5;
		mdLocProc = 0.5;
	}
	
	double mdTimeProc;  //ʱ�����
	double mdLocProc;   //�ص����
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
	double mdTimeProcGra;//ʱ������ݶ�
	double mTemperature_C;
	double mdWaterVapourDensity; //ˮ�����ܶ�
	double mdRefractivity;   //������
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
// 	double mdWaterVapourDensity; //ˮ�����ܶ�
// 	double mdPresurehPa;   //��ѹ
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

	//������ʽ
	short mnPolarization;  //0: ˮƽ������1:��ֱ����

	//������������
	double mdKfactor;

	//��Խ�糣��
	double mdRelativePermittivity;

	//��Ч�絼��
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
	double mdKfactor; //������������
	double mdTXTimeProb;  //����̨վʱ�����
	double mdRXTimeProb; //����̨վʱ�����
	short  mnEqupmentType; //1:�����豸��2�������豸
};

struct ScmNearFieldPara
{

};

#endif