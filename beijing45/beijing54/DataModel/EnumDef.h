#ifndef __DATAMODEL_ENUMDEF_h
#define __DATAMODEL_ENUMDEF_h

//̨վ����ö��
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

//��������
enum EPowerType
{
	eOutputPA = 0,
	eEIRP = 1,
	eERP = 2
};

//����ռ����
enum ESpaceType
{
	e2D = 0,
	e3D = 1
};

//̨վλ�����
enum ELocationType
{
	eOnGround = 0,   //����̨վ
	eInAir = 1       //����̨վ
};

//�߶����
enum EHeightType
{
	eASeaL = 0,  //���θ߶�
	eAGroundL = 1,  //�������ϸ߶�
	eABuildingL = 2 //������֮�ϵĸ߶�
};

//���Ƿ������������
enum ECoverResultType
{
	eUnknownResult = -1,				//δ֪����
	ePathloss = 0,						//·�����
	eFieldSth = 1,						//��ǿ����
	ePowerLevel = 2,					//���չ���
	eSignalStrength = 3,				//�ź�ǿ��
	ePowerFluxDensity = 4,				//����ͨ���ܶ�
    eSpectrumPowerFluxDensity = 5,		//Ƶ�׹���ͨ���ܶ�
	eRequiredPower = 6,					//���跢�书�ʼ���
	eLosRestHeight = 7,					//������ٿ�����ͨ�ļ���
	eCoAdjIntArea = 8,					//ͬ��Ƶ���ŷ������
	eBlockInArea = 9,					//�������ŷ������
	eCoverProbality=12,					//���Ǹ���
	eOpticalVisibility = 13,			//��ͨͼ
	eRadarCrossSection = 14,			//�״��ʶ������
	eRadarDetectProb = 15,				//�״�������
	eSignalNoise = 16,					//�����
	eReceivedPower = 17,				//�ý����ʾ�ĺ���Ϊ�����ջ��̶����ƶ��������ÿ�����ص�ʱ���ջ��Ľ��չ���	
	eNetworkCoverage = 18,				//����
	eMaxServerCount = 19,				//���������
	eBestServer = 20,					//��ѷ���
	eClearanceAngle = 21,				//��϶��
	eCommunicationArea=24,//ͨ�ų�ͨ����
	eMonitorCoverage=25,//��⸲��	
	eMonitorSiteSelection=26,//�������滮
	eStationStatus=27,      //̨վ����״̬
	eProbality=28,//����
	eIntermodulationInt=33,		//��������
	eSpuriousInt=34,		//��ɢ����
	eMirrorInt=35,			//��Ƶ����
	eIntermedianInt=36,		//��Ƶ����
	eHarmonicInt=37,		//г������
	eBasebandUp=38,			//��������
	eCalHealthArea=42,		//������ȫ��,1:��ȫ�� 2:�м��� 3:Σ����
	eSourceAreaAnalysis=43,		//����Դ������ٶ�λ
	eLongMediumShortWave=44,		//���ж̲�����
	eUltrashortWave=45,		//���̲�����
	eMicrowave=46,		//΢������
	eComprehensive=47,		//�ۺϷ���
	eObjectSupperssion=48,				//����ѹ��
	eAreaSupperssion=49,				//����ѹ��
	eNetworkEvaluation=50,				//��ⲿ����������
	eNetworkSiteSelection=51,					//���ܼ�����Ż�
	eNetworkPlan=52,						//���ܼ�ⲿ��
	eBMUF=53, 							 //����������
	eBLUF=54,  							 //��С����Ƶ��
	eOperMUF=55,						 //����������
	eOptMUF=56,							 //���Ź���Ƶ��
	eTimeOccupy=57,                      //ʱ��ռ�öȣ�½����
	eFreqOccupy=58,                      //Ƶ��ռ�öȣ�½����
	ePowerDensity=59,                    //�������ܶ�ϵ����½����
	eBackPower=60,                       //�����ź�ǿ��ϵ����½����
	eFreqCover=61,                       //Ƶ���غ϶�ϵ����½����
	eSpaceDensity=62,                    //����ź��ܶȿռ��ܶȣ�½����
	eFreqDensity=63,                     //����ź��ܶ�Ƶ���ܶȣ�½����
};

enum ECalculateFunctionType
{
	E_FUNCTION_NULL=-1,
	E_FUNCTION_COVERAGE=0,//���㸲�ǵ�ģ�鹦��
	E_FUNCTION_COVERAGESUM=32,//�����ۺϸ��ǵ�ģ�鹦��
	E_FUNCTION_INTCOVERAGE=1,//���Ÿ��ǵ�ģ�鹦��
	E_FUNCTION_MO_COVERAGE=2,//�����⸲�ǵ�ģ�鹦��
	E_FUNCTION_FREQ_ASSIGN=3, //����Ƶ��ָ���ģ�鹦��
	E_FUNCTION_LINK_FREQ_ASSIGN=4, //������·Ƶ��ָ���ģ�鹦��
	E_FUNCTION_INTLINK=5, //��·���ŷ���ģ�鹦��
	E_FUNCTION_INTAREA=6, //������ŷ���ģ�鹦��
	E_FUNCTION_INTFREQBAD=7,//����Ƶ������ģ�鹦��
	E_FUNCTION_FREQ_OCCUPY=8,//Ƶ��ռ��ģ�鹦��(Ƶ��Ԥѡ)
	E_FUNCTION_PERFANCR=9, //̨վ��������
	E_FUNCTION_PERFANCRSUM=31, //̨վ�ۺϸ�������
	E_FUNCTION_LINKPROFILE=10,//��·profileģ�鹦��
	E_FUNCTION_SPECTRUMANALYSIS=11,//Ƶ����Դģ�鹦��
	E_FUNCTION_MONITOR_COVERAGE_ANALYSIS=12,//��⸲�Ƿ���
	E_FUNCTION_AOALOCALIZATION=13 ,//AOA��λ
	E_FUNCTION_MONITOR_SITESELECTION=14,//��ⲿ�����,�������滮
	E_FUNCTION_MONITORDATAFUSION=15, //��������ں�
	E_FUNCTION_STATIONSTATUS=16, //̨վ�����������
	E_FUNCTION_SIGNAL_SUPPRESSION=17,//�ź�ѹ��
	E_FUNCTION_TDOAPOA=18,//TDOA,POA�㷨
	E_FUNCTION_TRAJECTORY=19,//�켣����
	E_FUNCTION_STATISTICAL_ANALYSIS=20, //̨վ����ͳ�Ʒ���
	E_FUNCTION_STATISTICAL_REPORT=21,    //�������ͳ�Ʊ���
	E_FUNCTION_BOUNDARYCOORDINATION=22,  //�߾�Э��
	E_FUNCTION_PROTECTAREAANALYSIS=23,   //����������
	E_FUNCTION_SOURCEAREAANALYSIS=24,     //����Դ������ٶ�λ
	E_FUNCTION_PATHLOSSPREPROCESS=25,     //·�����Ԥ����
	E_FUNCTION_SIGNAL_DIS=26,                             //����źŷ���
	E_FUNCTION_STATION_STATUS=27,                  //̨վ����״̬����
	E_FUNCTION_SUPERVERSION=28,                       //̨վ��ܷ���
	E_FUNCTION_CONTOUR=29,					//̨վ���������߼���
	E_FUNCTION_HEALTHAREAANALYSIS=30,			//������ȫ������
	E_FUNCTION_NETWORKSANALYSIS=33,				//�������
	E_FUNCTION_NETANA_MAXSERVICE=E_FUNCTION_NETWORKSANALYSIS+1,//�������-������
	E_FUNCTION_NETANA_MAXFIELD=E_FUNCTION_NETWORKSANALYSIS+2,//�������-���ǿ
	E_FUNCTION_NETANA_MAXSERVICE_NUM=E_FUNCTION_NETWORKSANALYSIS+3,//�������-����������
	E_FUNCTION_NETANA_AVAIFIELD=E_FUNCTION_NETWORKSANALYSIS+4,//�������-���ó�ǿ
	E_FUNCTION_NETANA_CI=E_FUNCTION_NETWORKSANALYSIS+5,//�������-��������
	E_FUNCTION_NETANA_COVEPROBABILITY=E_FUNCTION_NETWORKSANALYSIS+6,//�������-���Ǹ���
	E_FUNCTION_NETANA_BESTSERVICE=E_FUNCTION_NETWORKSANALYSIS+7,//�������-��ѷ���
	E_FUNCTION_NETANA_BESTSERVICEFIELD=E_FUNCTION_NETWORKSANALYSIS+8,//�������-��ѷ���ǿ��
	E_FUNCTION_NETANA_BESTSERVICENUM=E_FUNCTION_NETWORKSANALYSIS+9,//�������-��ѷ�������
	E_FUNCTION_NETANA_MAXINT_TOT=E_FUNCTION_NETWORKSANALYSIS+10,//�������-��ǿ����tot
	E_FUNCTION_NETANA_MAXINTFIELD_TOT=E_FUNCTION_NETWORKSANALYSIS+11,//�������-��ǿ����ǿ��tot
	E_FUNCTION_NETANA_MAXINT_BOCOV=E_FUNCTION_NETWORKSANALYSIS+12,//�������-��ǿ����no Cov
	E_FUNCTION_SHORTWAVE_BCR=46,				//BCR
	E_FUNCTION_SHORTWAVE_MUF=47,				//�ٽ�Ƶ��

};

//��⸲�Ƿ������������
enum EMonitorResultType
{
	eSingleCover = 0,  //��վ����
	eNetworkCover = 1, //���縲��
	eNetworkDirCover = 2, //������򸲸�
	eNetworkLocCover = 3  //���綨λ����
};

//SUI����ģ����������
enum ArealType
{
	aTown = 1,        //A���ͣ�����
	aOutskirts = 2,   //B���ͣ��н�
	aVillage = 3      //C���ͣ����
};

//����ģ�����
enum ETransModel
{
	eTransNull = -1,  //û�����ô���ģ��,�Զ�ѡ�񴫲�ģ�� 
	eFreeSpace = 0,   //���ɿռ䴫��ģ��
	eCost231Hata1 = 1, //Cost231 hata1ģ��
	eITURP1546 = 2,   //ITU1546ģ��	
	eITURP370 = 3,    //ITU370ģ��
	eLONGLEYRICE = 4, //LONGLEY-RICE����ģ��
	eITU533ShortWave = 5, //ITU533 �̲�ģ��
	eITU530V10MicWave = 6,  //ITU530 V10΢��ģ��
	eITU618 = 7,        //ITU618��˥ģ��
	eAeroNautical = 8,  //����ģ��
	eLOSModel = 9,  //��ͨģ��
	eDiffractionModel = 10, //����ģ��
	eIRT3D = 11,    //IRT 3D
    eCost231Hata2 = 12,  //Cost231Hata2����ģ��
	eLeeModel = 13,       //Lee �ҵ����ģ��
	eWalfishIkegami = 14,	
	eSUIModel = 16,       //SUI����ģ��
	eGroundWave = 17,     //�ز�
	eSkyWave = 18,        //�첨
	eITU452  = 19,        //ITU452����ģ��
	eITU452_10 = 20,      //ITU452-10����ģ��
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

//��������λ
typedef enum CalResult_Unit
{
	CRUNIT_UNKOWN			= -1,	//δ֪��λ
	CRUNIT_DB				= 0,	//dB
	CRUNIT_DBM				= 1,	//dBm
	CRUNIT_DBUV				= 2,	//dBum
	CRUNIT_DBUV_PER_M		= 3,	//dBum/m
	CRUNIT_DBW_PER_M2		= 4,	//dBw/m2
	CRUNIT_DBW_PER_M2_HZ	= 5,	//dBw/Hz/m2
	CRUNIT_LOS_M            = 6,    //m ���������ͨ
	CRUNIT_PERCENT          =7,		//�ٷֱ� 
	CRUNIT_RCS_M2           =8,
	CRUNIT_ANGLE			=9,		//�Ƕ�(��)
	CRUNIT_NUMBER			=10,		//����
	CRUNIT_FREQMHz				=11     //Ƶ�� 
};

//�������
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

//������������
typedef enum CalResult_AreaType
{
	CAL_AREA_UNKNOWN = 0,	
	CAL_AREA_RECT,						//���μ�������
	CAL_AREA_CIRCLE,					//Բ�μ�������
	CAL_AREA_POLYGON,					//����μ�������

	CAL_POINT,
	CAL_POLYLINE,
	CAL_PROFILE,
	CAL_LINE
};


//////////////////////////////////////////////////////////////////////////
//����ģ������enum
enum EModelType
{
	eUNKNOWNModel = -1,
	eBaseModel = 0,
	eComputePredictionModel = 1,    //����ģ��
	eBaseTransModel = 2,  //�����Ĵ���ģ��ģ��
	eIRT3DModel = 3,       //3D����ģ��
	eInterfAnalyseModel = 4,     //�ۺϸ��ŷ���ģ��
	eMicwaveLinkAnalyseModel = 5,        //΢����·����ģ��
	eShortwaveLinkAnalyseModel = 6,       //
	eFreqAssignModel = 7,         //Ƶ��ָ��ģ��
	eRadarPerformanceModel = 8,   //�״�Ч�ܷ���ģ��
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
	eAirPlaneModel = 20,  //����ģ��
	eLeeTransModel = 21,  //�ҵģ��
	eWalfishIkegamiModel = 22, //Walfish Ikegamiģ��
	eSUILicenseModel = 23,
	eEgliLicModel = 24,
	eFlatEarthLicModel = 25,
	eITU567LicModel = 26,
	eITU1812LicModel = 27,
	eITU452LicModel = 28,
	eITU452_10LicModel = 29,
	eITU526LicModel = 30,
	eFrequencyOccupyModel=31,//Ƶ��ռ��
	
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
	/////////////////////////////���
	ThreeF1SubtrasrtTwoF2,//3F1-2F2
	ThreeF2SubtrasrtTwoF1,//3F2-2F1
};

//�������������  add by xiangl
enum ShapeStyle
{
	eKnow = 0,
	eRect = 1, //����
	ePolygon = 2, //�����
	eCircle  = 3,  //Բ
	eAzimuth = 4//���·���
};

//����ļ�����
enum ResultFileType
{
	eResult_Point=0,//����
	eResult_Line,//�߽��
	eResult_2D,//��ά����
	eResult_3D,//��ά������
	eResult_XML,//xml
	eResult_Other//��������
};

enum CICalculateType
{
	eCI_ADD=0,   //����
	eCI_MAX=1    //ȡ���ֵ
};

typedef CICalculateType MergeCalculateType;

#define IS_RESULTVALUE_VALID(d) (((d)>-10000)&&((d)!=0x81)&&((d)!=0x8181)&&((d)<10000))

#endif
