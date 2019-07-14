#ifndef CNG_PRE_DEFINED_STRUCT_H
#define CNG_PRE_DEFINED_STRUCT_H
#include <vector>
#include <math.h>
#include <map>

using namespace std;

#ifndef NG_DELETE_POINT
#define NG_DELETE_POINT(pPoint) if(pPoint!=NULL)\
                                                                  {delete pPoint;\
	                                                               pPoint=NULL;}
#endif

#ifndef NG_DELETE_ARRAY
#define NG_DELETE_ARRAY(pArray) if(pArray!=NULL)\
                                                                  {delete[] pArray;\
	                                                               pArray=NULL;}
#endif

#define SEEK_LENGTH 12
#define CheckCode 0xABCDABCD
#define MAPRESULTION 20

#define DATASIZE 18

#define UNCALCULATE		((short)(0x8181))	
#define  PlaneCoord 143 // 平面坐标编号
#define CSPEED 299792458.458
#define PI 3.1415926
#define  FilterWidth 3//均值滤波的宽度

#define LowLeftX 1495648.90786245
#define LowLeftY 3702131.35713364



#define NGAtoul(pSrc) strtoul(pSrc,NULL,10)//定义宏，字符串转换成unsigned long


#ifndef NULL
#define NULL 0
#endif
#define DELETED -2

#define le 0
#define re 1

//enum eScanFreqFormat
//{
//	eUnknown=-1,
//	//eNGScanFreqV1=0,//恩巨目前已经使用的扫频文件格式，不带经纬度信息
//	eStandScanFreqV1=1,//国家格式
//	//eStandScanFreqV2=2,//国家格式测向数据
//	eStandScanFreqV3=3,//2017年国家格式
//	//eRadioMonitor = 4 //超短波频段监测文件
//};

#ifdef _MSC_VER
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif // _MSC_VER
struct BinHead	
{
	unsigned int checkcode;
	unsigned short equ_no;
	unsigned char ant_type;
	short year;
	char mon;
	char day;
	char hour;
	char minute;
	char second;
	short misecond;
	double lon;
	double lat;
	unsigned int height;
	unsigned __int64 startfreq;
	unsigned int freqstep;
	unsigned int freqcount;
};

//2017国家格式头信息
//struct StandBinHeadV3	
//{
//	unsigned int checkcode;
//	unsigned short equ_no;
//	unsigned char ant_type;
//	short year;
//	char mon;
//	char day;
//	char hour;
//	char minute;
//	char second;
//	short misecond;
//	short scanspeed; // GH/s
//	unsigned __int64 lon; // 1e-8
//	unsigned __int64 lat; //1e-8
//	short height; // 0.1
//	double startfreq;
//	float freqstep;
//	unsigned int freqcount;
//};

#ifdef _MSC_VER
#pragma pack(pop)
#else
#pragma pack()
#endif // _MSC_VER

//频段数据
struct NGFreqBand{
	unsigned __int64 beginFreq;
	unsigned __int64 endFreq;
	unsigned int freqStep;

	NGFreqBand(unsigned __int64 be = 0,unsigned end = 0 ,unsigned int fp = 0 ){
		beginFreq = be;
		endFreq = end;
		freqStep = fp;
	}
};




struct	Freenode	
{
	struct	Freenode *nextfree;
};

struct FreeNodeArrayList
{
	struct	Freenode* memory;
	struct	FreeNodeArrayList* next;

};

struct	Freelist	
{
	struct	Freenode	*head;
	int		nodesize;
};

#if (defined(_WIN32) || defined(__WIN32__))
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif // WIN32
struct NGPOINT	
{
	double x;
	double y;
	short value;
	bool operator ==(const NGPOINT& p)
	{
		return fabs(x-p.x)< 1e-6 && fabs(y - p.y)< 1e-6;//判断两个点是否重合
	}
	bool operator !=(const NGPOINT& p){
		return !(*this==p);
	}
};
#if (defined(_WIN32) || defined(__WIN32__))
#pragma pack(pop)
#else
#pragma pack()
#endif // WIN32

//直线结构体
struct NGLine{
	double a;
	double b;
	double c;//a*x+b*y +c =0
};

struct NGEdge{
	NGPOINT begin;
	NGPOINT end;//泰森多边形的边的开始和结束点
	int rightIndex;
	int leftIndex;
	double area;//边和离散点组成的三角形面积
};
struct NGPolygon{
	vector<NGEdge> edges;
	float area;//多边形面积
	//bool isBound ; 
	NGPolygon(){
		area = 0 ;
		//	isBound = false;
		edges.reserve(10);
	}
};


//用于计算凸包的向量结构体
struct NGPlaneVector{
	int index;//离散点索引
	double angle;
	double length;//向量的长度，离散点index作为终点，所有离散点中y最小的点作为起点
};
// structure used both for sites and for vertices 

struct Site	
{
	struct	NGPOINT	coord;
	int		sitenbr;
	int		refcnt;
};



struct Edge	
{
	double   a,b,c;
	struct	Site 	*ep[2];
	struct	Site	*reg[2];
	int		edgenbr;

};

struct GraphEdge
{
	double x1,y1,x2,y2;
	int leftIndex,rightIndex;//泰森多边形边两边的离散点
	struct GraphEdge* next;

};


struct Halfedge 
{
	struct	Halfedge	*ELleft, *ELright;
	struct	Edge	*ELedge;
	int		ELrefcnt;
	char	ELpm;
	struct	Site	*vertex;
	double	ystar;
	struct	Halfedge *PQnext;
};




struct NGLocation{
	double x,y;
	NGLocation(double  X = 0 ,double Y = 0 ){
		x = X;
		y = Y;
	}
};



//路测数据结构体
struct ScmDriveTest
{
	double X;
	double Y;
	double mdValue;
	ScmDriveTest(double x = 0 , double y = 0 ){
		X = x ; 
		Y = y ; 
		mdValue = 0 ;
	}
};

////合并栅格点的时候用到
//struct MonitorData{
//	int X;
//	int Y;
//	double mdValue;
//};


struct NGSpetrum{
	unsigned __int64 freq;
	vector<short> datas;
	vector<NGLocation> locations;
	NGSpetrum(){
		datas.reserve(10000);
		locations.reserve(10000);
	}
};

//每一个待插值点的权重，会定义一个结构体数组，数目和栅格数目一致，无需保存xIndex,yIndex
struct NGVoronoiWeight{
	int siteIndex;//所在的泰森多边形索引
	//对应的邻区索引和权重
	vector<int> pxIndexs;
	vector<float> pxWeights;

	
};

typedef std::vector <NGPOINT> NGDataVector;
#endif