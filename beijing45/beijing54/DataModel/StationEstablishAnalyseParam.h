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
	//̨վID
	std::string mID;
	//̨վ����
	std::string mName;

	std::string mstrEquID;
	//λ��
	CGeoPoint mLocation;
	//Ƶ��
	double mdFreqMhz;
	//����
	double mdBWMhz;

	//�����ڸ���ʱ̨վ�ĸ������
	double mdAreaNoInterf;
	//���ڸ���ʱ̨վ�ĸ������
	double mdAreaInterf;
	//̨վ���ź�ǿ�ȸ��ǽ��ͼ�ļ�
	std::string mFieldSthFileName;
	//̨վ��CI���ͼ�ļ�
	std::string mCIFileName;
};
//��̨����ʱ���������Ӱ��ķ�����໥��Ӱ��ĸ��ŷ������
typedef struct _AddStation_InterfAnalyse_Result
{
	//����̨վ������̨վ�ĸ���
	std::vector<TxCoverInfo> mvTxInfoList;

	//����̨վ������̨վ�ĸ���
	TxCoverInfo mAddStationCoverInfo;
}AddStationInterfResult;

struct InterModulationInfo
{
	//���Ƶ����
	std::vector<InterModType> mveInterModType; 

	//���ƽ���
	int mnOrder;

	//F1����Ϣ
	int mnIndex1;   //F1̨վ������
	std::string mstrID1;
	std::string mstrEquID1;
	std::string mStationName1;
	double mdFreqMhz1;
	double mdLevel1;  //F1̨վ�ڽ��ջ����Ĺ���
	double mdFieldSth1;  //F1̨վ�ڽ��ջ����ĳ�ǿ

	//F2����Ϣ
	int mnIndex2;
	std::string mstrID2;
	std::string mstrEquID2;
	std::string mStationName2;
	double mdFreqMhz2;	
	double mdLevel2;  //F2̨վ�ڽ��ջ����Ĺ���
	double mdFieldSth2;  //F2̨վ�ڽ��ջ����ĳ�ǿ

	//F3����Ϣ
	int mnIndex3;   //F3̨վ������
	std::string mstrID3;
	std::string mstrEquID3;
	std::string mStationName3;
	double mdFreqMhz3;	
	double mdLevel3;  //F3̨վ�ڽ��ջ����Ĺ���
	double mdFieldSth3;  //F3̨վ�ڽ��ջ����ĳ�ǿ
};

struct InterModulationResult
{
	//���ջ�����Ϣ
	std::string mstrRxID;
	std::string mstrRxEquID;
	std::string mStationName;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;

	//�����������ŵ��б�
	std::vector<InterModulationInfo> mvInterModulationInfo;
};

struct BlockInterfInfo
{
	int mnIndex;   //�����������ŵ�����
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //�ڱ��������ջ������ź�ֵ	
	double mdFieldSth;//�ڱ��������ջ����ĳ�ǿ
	double mdProtectRatio; //�뱻����̨վ֮��ı�����
};

struct BlockInterfResult
{
	//���ջ���Ϣ
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;

	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxBlockLevel; //��������
	double mdLevel;  //Ԥ���źŵĹ���
	double mdFieldSth;//Ԥ���źŵĳ�ǿ	

	std::vector<BlockInterfInfo> mvBlockInterfInfo;
};

//��Ƶ���ŵĲ���
struct MirrorInterfInfo
{
	int mnIndex;   //������Ƶ���ŵ�����
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //�ڱ���Ƶ���Ž��ջ����Ĺ���ֵ	
	double mdFieldSth;//�ڱ���Ƶ���Ž��ջ����ĳ�ǿֵ
	double mdProtectRadio; // ���Ż���Ԥ��̨վ֮��ı�����
};

struct MirrorInterfResult
{
	//���ջ���Ϣ
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxThresholddBm; //��������
	double mdImgFreqAtt;  //��Ƶ˥��
	double mdLevel;  //Ԥ���źŵĹ���
	double mdFieldSth;//Ԥ���źŵĳ�ǿ	

	std::vector<MirrorInterfInfo> mvImageInterfInfo;
};

//��Ƶ���ŵĲ���
struct MidInterfInfo
{
	int mnIndex;   //������Ƶ���ŵ�����
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //�ڱ���Ƶ���Ž��ջ����Ĺ���ֵ	
	double mdFieldSth;//�ڱ���Ƶ���Ž��ջ����ĳ�ǿ
	double mdProtectRadio; // ���Ż���Ԥ��̨վ֮��ı�����
};

struct MidInterfResult
{
	//���ջ���Ϣ
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxThresholddBm; //��������
	double mdLevel;  //Ԥ���źŵĹ���
	double mdFieldSth;//Ԥ���źŵĳ�ǿ
	double mdMidFreqAtt;  //��Ƶ˥��

	std::vector<MidInterfInfo> mvMidInterfInfo;
};

//г�����ŵĲ���
struct HarmonicsInterfInfo
{
	int mnHarmNum;  //г������
	int mnIndex;   //����г�����ŵ�����
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //�ڱ�г�����Ž��ջ����Ĺ���ֵ	
	double mdFieldSth;//�ڱ�г�����Ž��ջ����ĳ�ǿ
	double mdHarmAtt;//г��˥��
	double mdProtectRadio;
};

struct HarmonicsInterfResult
{
	//���ջ���Ϣ
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxThresholddBm; //��������
	double mdLevel;  //Ԥ���źŵĹ���
	double mdFieldSth;//Ԥ���źŵĳ�ǿ
	
	std::vector<HarmonicsInterfInfo> mvHarmonicsInterfInfo;
};

struct SquriousInterfInfo
{
	int mnIndex;  //������ɢ���ŵ�̨վ������
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //�ڱ����Ž��ջ������źŹ���
	double mdFieldSth; //�ڱ����Ž��ջ������ź�ǿ��
	double mdProtectRatio; //�뱻����̨վ֮��ı�����
};

struct SquriousInterfResult
{
	//���ջ���Ϣ
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxSquriousLevel; //�����̵���ɢ����
	double mdLevel;  //Ԥ���źŵĹ���
	double mdFieldSth;//Ԥ���źŵĳ�ǿ

	std::vector<SquriousInterfInfo> mvSquriousInterfInfo;
};

struct DegradationAnalyseResult
{
	//���ջ���Ϣ
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstRxrEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdRxThresholddBm;
	double mdRxSNThresholddB;

    double mdFieldSth; //�����źŵ�ǿ��
	double mdLevel;    //Ԥ���źŵĹ���

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
	int mnIndex; //�������ŵ�̨վ������
	std::string mstrID;
	std::string mstrEquID;
	std::string mStationName;
	double mdFreqMhz;
	double mdEirpdBm;
	double mdLongitude;
	double mdLatitude;
	double mdLevel;  //�ڱ����Ž��ջ����Ĺ���ֵ
	double mdFieldSth;//�ڱ����Ž��ջ����ĳ�ǿֵ
	double mdProtectRatio; //�뱻����̨վ֮��ı�����
};

struct CoAdjInterfResult
{
	//��·��Ϣ
	//�������Ϣ
	std::string mstrTxID;
	std::string mstrTxName;
	std::string mstrTxEquID;
	double mdTxFreqMhz;
	double mdTxLongitude;
	double mdTxLatitude;

	//���ջ���Ϣ
	std::string mstrRxID;
	std::string mstrRxName;
	std::string mstrRxEquID;
	double mdRxFreqMhz;
	double mdRxLongitude;
	double mdRxLatitude;
	double mdRxAntHeight;
	double mdThresholddBm; //����ֵ
	
	double mdFieldSth; // �����ź�ǿ��
	double mdLevel;    //�����źŹ���

	std::vector<CoAdjInterfInfo> mvCoAdjInterfInfo;
	std::string mResultFilename;
};


#endif