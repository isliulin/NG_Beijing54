#ifndef NG_TDOA_DATA_STRUCT_H
#define NG_TDOA_DATA_STRUCT_H

//����TDOA�㷨���õ������ݽṹ
//Writed by �

#include <vector>
#include <complex>
//�����ɾ��ָ�������ָ��
#define NG_DELETE_ARRAY(pArray) if(pArray!=NULL)\
								                                  {delete[] pArray;\
								                                   pArray=NULL;}
#define NG_DELETE_POINT(pPoint) if(pPoint!=NULL)\
											                    {delete pPoint;\
											                     pPoint=NULL;}
#define  NGPI                    3.14159265358979

#define NGSNR 100 //���ڶ�ȡIQʱ���ж�ȡ�õ�IQ�����ǵ��뻹���ź�ֵ

#define EXP8 2980.9579870417283 //����exp(8.0)

#define NOSIGNAL -100 //�ж��Ƿ��ǵ��������

//#define PlaneCoordCode 249//Ϊ����������ȣ�����γ������ת����ĳ��ƽ������

#define NOCORRELATION 0.10//���ϵ��С��0.3ʱ����ʾ�źŲ����

#define CSPEED 2.99792458458e+8//�źŴ������ٶ�

#define  MAPRESULTION 5   //դ��ֱ���

#define RandomDis   1000 //����ģ������ʱ�򣬸��ݵ�һ�ε�ģ������������������Ľ��

#define ResultRadius 400

#define HYPERPOINTNUM 361 //˫����ȡ�����

#define IQSIGNALTHRESHOLD  -60 //����IQ����õ��ĳ�ǿ����

#define NGMAX(A,B) (A>B? A : B)
#define NGMIN(A,B) (A<B? A : B)

using std::vector;

typedef std::complex<double> TDComplex;//һ��IQ�ź�
typedef vector<TDComplex> TDFDomain;//Ƶ����������
typedef vector<double> TDVector;




//�µ������洢IQ���ݼ������
struct NGIQData
{
	double mLongitude ;//���վ��γ����Ϣ
	double mLatitude ;
	double mCenterFreq ;//����Ƶ��
	double mSampleRate;//�����ٶȣ�������(MHz)
	double mBandWidth;//�źŴ���(MHz)
	unsigned int mSamplesPerPackets ;//ÿ����¼�������� 
	int* mDatas ;//IQ��������[mSamplesPerPacket * 2] // IQ�����洢
	//ʱ���
	unsigned int	mTimestampNSecs;//ʱ��� ��λ ns
	unsigned int	mTimestampSecs;//ʱ��� ��λs,     t=  mTimestampsec + mTimestampNsec * 1e-9;
	NGIQData(){
		mDatas = NULL ;
	}
};

struct NGIQData_float
{
	double mLongitude ;//���վ��γ����Ϣ
	double mLatitude ;
	double mCenterFreq ;//����Ƶ��
	double mSampleRate;//�����ٶȣ�������(MHz)
	double mBandWidth;//�źŴ���(MHz)
	unsigned int mSamplesPerPackets ;//ÿ����¼�������� 
	float* mDatas ;//IQ��������[mSamplesPerPacket * 2] // IQ�����洢
	//ʱ���
	unsigned int	mTimestampNSecs;//ʱ��� ��λ ns
	unsigned int	mTimestampSecs;//ʱ��� ��λs,     t=  mTimestampsec + mTimestampNsec * 1e-9;
	NGIQData_float(){
		mDatas = NULL ;
	}
};


//�ŵ�����
enum ChannelEnviroment
{
	DownTown,//������
	NormalCity,//һ������
	Suburbs,//����
	Suburban//Զ��
};

//�����洢IQ���ݼ������
struct IQData
{
	TDComplex* mSignals;//IQ�ź�����
	unsigned int mSamplesPerPacket;//������
	double mSampleRate;//�����ٶȣ�������(Hz)
	double mBandWidth;//����
	int	mTimestampNsec;//ʱ��� ��λ ns
	int	mTimestampsec;//ʱ��� ��λs,     t=  mTimestampsec + mTimestampNsec * 1e-9;
	IQData(){
		mSignals = NULL;
	}
};

//���ϵ���������
//0.00-��0.30    ΢��� �����������
//��0.30-��0.50  ʵ��� 
//��0.50-��0.80  �������
//��0.80-��1.00  �߶���� 
//�������ϵ������ļ�����  TDOA�㷨
struct CrossCorrelationResult
{
	CrossCorrelationResult(int sampleDelay=0,double corrCoefficient=0,double startTimeNanoSec=0)
	{
		mSampleDelay=sampleDelay;
		mMaxCorrCoefficient=corrCoefficient;
		mStartTimeNanoSec=startTimeNanoSec;
	}
	double mMaxCorrCoefficient;//���Ļ����ϵ��
	double mStartTimeNanoSec;//����ؼ���Ŀ�ʼʱ�ƣ���λns
	int mSampleDelay;//Data1��ʱ������������ʾǰ�ƣ�������ʾ����
};

//�������ͣ���γ�Ⱥ�ƽ������ϵ
enum CoordType
{
	LngLatCoord=103,
	PlaneCoord,
};
//̨վλ��
struct NGPostion
{
	NGPostion(double x=0,double y=0,CoordType type=LngLatCoord,ChannelEnviroment mchEment=DownTown)
	{
		Y=y;
		X=x;
		mType=type;
		chEment=mchEment;
	}
	double	X;//����
	double	Y; //γ��
	float weight;//ÿ����λ����ĸ���
	double radius;//ÿ����λ������ڻ�����ͼʱ�İ뾶
	ChannelEnviroment chEment;//̨վ���ڵ��ŵ�����
	CoordType mType;//��������,Ϊ��γ��ʱ��X���ȣ�Yγ��
};

struct NGHyperbola
{
	//���㣬�Լ���������ľ����
	NGPostion focalpoint1;
	NGPostion focalpoint2;
	double disfdiff;
};

struct NGHyperPolar
{
	double a2,b2,c2,angle,deltaX,deltaY;//˫���߼����귽��  x^2/a2 - y^2/b2 = 1 ,  x = p*cos(O + angle) + deltaX,y = p * sin(O + angle) + deltaY
	                                                             //��ԭ��Ϊ���ĵ�˫���ߣ���ʱ����תangle�Ƕȣ������Ƶ���deltaX,deltaY)

	bool isLeft ;//��ʾ����֧��������֧����
};

static inline bool POSBigger(NGPostion pos1,NGPostion pos2)
{
	return pos1.weight > pos2.weight;
}


static inline bool POSLitter(NGPostion pos1,NGPostion pos2)
{
	return pos1.weight < pos2.weight;
}
struct NGPOAPostion
{
	NGPOAPostion(NGPostion pos,double rssi,double dev)
	{
		mPos=pos;
		mRssi=rssi;
		mDev=dev;
	}
	NGPostion mPos;//��ĳ�����վΪ�ο�̨վ����õ��Ľ�����Լ��ü��վ��õ��ź�ǿ��ֵ�ͷ���
	double mRssi;
	double mDev;
};

//����̨վTDOA�������
struct NGTDOAResult
{
	NGTDOAResult(int A=0,int B=0, double tdoainNS=0)
	{
		a=A;
		b=B;
		mTDOAinNS=tdoainNS;
	}
	int a,b;//����̨վ���
	double mTDOAinNS;//a,b,̨վ��TDOAֵ
};

struct NGCircle
{
	NGPostion center;//Բ��
	double radius;//�뾶
};

struct NGPOAResult
{
	NGPOAResult(int A,int B,double mRatio)
	{
		a=A;
		b=B;
		ratio=mRatio;
	}
	int a,b;
	double ratio;//a,b����̨վ��δ̨֪վ����ı�ֵ��Da/Db
};

//struct NGLine
//{
//	double a,b,c;//ֱ��a*x+b*y=c;
//};


//�߶�
struct NGSegment
{
	NGPostion p1 ,p2 ;
};

#endif