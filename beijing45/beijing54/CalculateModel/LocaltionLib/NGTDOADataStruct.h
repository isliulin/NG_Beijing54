#ifndef NG_TDOA_DATA_STRUCT_H
#define NG_TDOA_DATA_STRUCT_H

//声明TDOA算法中用到的数据结构
//Writed by 李冬

#include <vector>
#include <complex>
//定义宏删除指针和数组指针
#define NG_DELETE_ARRAY(pArray) if(pArray!=NULL)\
								                                  {delete[] pArray;\
								                                   pArray=NULL;}
#define NG_DELETE_POINT(pPoint) if(pPoint!=NULL)\
											                    {delete pPoint;\
											                     pPoint=NULL;}
#define  NGPI                    3.14159265358979

#define NGSNR 100 //用于读取IQ时，判断取得的IQ数据是底噪还是信号值

#define EXP8 2980.9579870417283 //常量exp(8.0)

#define NOSIGNAL -100 //判定是否是底噪额门限

//#define PlaneCoordCode 249//为方便计算距离等，将经纬度坐标转换成某种平面坐标

#define NOCORRELATION 0.10//相关系数小于0.3时，表示信号不相关

#define CSPEED 2.99792458458e+8//信号传播的速度

#define  MAPRESULTION 5   //栅格分辨率

#define RandomDis   1000 //用于模拟结果的时候，根据第一次的模拟结果，随机生成其他的结果

#define ResultRadius 400

#define HYPERPOINTNUM 361 //双曲线取点个数

#define IQSIGNALTHRESHOLD  -60 //根据IQ计算得到的场强门限

#define NGMAX(A,B) (A>B? A : B)
#define NGMIN(A,B) (A<B? A : B)

using std::vector;

typedef std::complex<double> TDComplex;//一个IQ信号
typedef vector<TDComplex> TDFDomain;//频谱数据类型
typedef vector<double> TDVector;




//新的用来存储IQ数据及其参数
struct NGIQData
{
	double mLongitude ;//监测站经纬度信息
	double mLatitude ;
	double mCenterFreq ;//中心频点
	double mSampleRate;//采样速度，样本率(MHz)
	double mBandWidth;//信号带宽(MHz)
	unsigned int mSamplesPerPackets ;//每个记录的样本数 
	int* mDatas ;//IQ数据数组[mSamplesPerPacket * 2] // IQ相间隔存储
	//时间戳
	unsigned int	mTimestampNSecs;//时间戳 单位 ns
	unsigned int	mTimestampSecs;//时间戳 单位s,     t=  mTimestampsec + mTimestampNsec * 1e-9;
	NGIQData(){
		mDatas = NULL ;
	}
};

struct NGIQData_float
{
	double mLongitude ;//监测站经纬度信息
	double mLatitude ;
	double mCenterFreq ;//中心频点
	double mSampleRate;//采样速度，样本率(MHz)
	double mBandWidth;//信号带宽(MHz)
	unsigned int mSamplesPerPackets ;//每个记录的样本数 
	float* mDatas ;//IQ数据数组[mSamplesPerPacket * 2] // IQ相间隔存储
	//时间戳
	unsigned int	mTimestampNSecs;//时间戳 单位 ns
	unsigned int	mTimestampSecs;//时间戳 单位s,     t=  mTimestampsec + mTimestampNsec * 1e-9;
	NGIQData_float(){
		mDatas = NULL ;
	}
};


//信道环境
enum ChannelEnviroment
{
	DownTown,//闹市区
	NormalCity,//一般市区
	Suburbs,//郊区
	Suburban//远郊
};

//用来存储IQ数据及其参数
struct IQData
{
	TDComplex* mSignals;//IQ信号数据
	unsigned int mSamplesPerPacket;//样本数
	double mSampleRate;//采样速度，样本率(Hz)
	double mBandWidth;//带宽
	int	mTimestampNsec;//时间戳 单位 ns
	int	mTimestampsec;//时间戳 单位s,     t=  mTimestampsec + mTimestampNsec * 1e-9;
	IQData(){
		mSignals = NULL;
	}
};

//相关系数与相关性
//0.00-±0.30    微相关 或者无相关性
//±0.30-±0.50  实相关 
//±0.50-±0.80  显著相关
//±0.80-±1.00  高度相关 
//进行相关系分析后的计算结果  TDOA算法
struct CrossCorrelationResult
{
	CrossCorrelationResult(int sampleDelay=0,double corrCoefficient=0,double startTimeNanoSec=0)
	{
		mSampleDelay=sampleDelay;
		mMaxCorrCoefficient=corrCoefficient;
		mStartTimeNanoSec=startTimeNanoSec;
	}
	double mMaxCorrCoefficient;//最大的互相关系数
	double mStartTimeNanoSec;//互相关计算的开始时移，单位ns
	int mSampleDelay;//Data1的时移量，正数表示前移，负数表示后移
};

//坐标类型：经纬度和平面坐标系
enum CoordType
{
	LngLatCoord=103,
	PlaneCoord,
};
//台站位置
struct NGPostion
{
	NGPostion(double x=0,double y=0,CoordType type=LngLatCoord,ChannelEnviroment mchEment=DownTown)
	{
		Y=y;
		X=x;
		mType=type;
		chEment=mchEment;
	}
	double	X;//经度
	double	Y; //纬度
	float weight;//每个定位结果的概率
	double radius;//每个定位结果用于画热力图时的半径
	ChannelEnviroment chEment;//台站所在的信道环境
	CoordType mType;//坐标类型,为经纬度时，X经度，Y纬度
};

struct NGHyperbola
{
	//焦点，以及到两焦点的距离差
	NGPostion focalpoint1;
	NGPostion focalpoint2;
	double disfdiff;
};

struct NGHyperPolar
{
	double a2,b2,c2,angle,deltaX,deltaY;//双曲线极坐标方程  x^2/a2 - y^2/b2 = 1 ,  x = p*cos(O + angle) + deltaX,y = p * sin(O + angle) + deltaY
	                                                             //以原点为中心的双曲线，逆时针旋转angle角度，中心移到（deltaX,deltaY)

	bool isLeft ;//表示是左支，还是右支曲线
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
	NGPostion mPos;//以某个监测站为参考台站计算得到的结果，以及该监测站测得的信号强度值和方差
	double mRssi;
	double mDev;
};

//两个台站TDOA分析结果
struct NGTDOAResult
{
	NGTDOAResult(int A=0,int B=0, double tdoainNS=0)
	{
		a=A;
		b=B;
		mTDOAinNS=tdoainNS;
	}
	int a,b;//两个台站编号
	double mTDOAinNS;//a,b,台站的TDOA值
};

struct NGCircle
{
	NGPostion center;//圆心
	double radius;//半径
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
	double ratio;//a,b两个台站与未知台站距离的比值，Da/Db
};

//struct NGLine
//{
//	double a,b,c;//直线a*x+b*y=c;
//};


//线段
struct NGSegment
{
	NGPostion p1 ,p2 ;
};

#endif