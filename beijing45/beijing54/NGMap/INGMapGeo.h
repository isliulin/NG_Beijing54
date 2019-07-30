#ifndef __NG__MAPGEO__EXPORT__H__
#define __NG__MAPGEO__EXPORT__H__

#if defined(NGMAP_LIB)
	#define GISMAP_API
#else
	#if defined(_WIN32) || defined(__WIN32__)
		#ifdef NGMAP_EXPORTS
			#define NG_MAP_API __declspec(dllexport)
		#else
			#define NG_MAP_API __declspec(dllimport)
		#endif 
	#else 
		#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
			#define NG_MAP_API __attribute__ ((visibility("default")))
		#else
			#define NG_MAP_API
		#endif	// __GNUC__		
	#endif		// WIN32 / !WIN32
#endif	

#if defined(_WIN32) || defined(__WIN32__)
#include <Windows.h>
#else
typedef struct tagPOINT
{
	long  x;
	long  y;
} POINT;
#endif	


//地图类型描述
#define	NG_MT_TOPO				1
#define NG_MT_MORPH				2
#define	NG_MT_POPULATION		3
#define NG_MT_TRAFFIC			4
#define	NG_MT_ROAD_MAPS			5
#define	NG_MT_BOROUGH			6
#define	NG_MT_ORTHO_FOTO		7
#define	NG_MT_POPDENS			8
#define	NG_MT_BUILDING_HEIGHT	9
#define	NG_MT_CONDUCTIVITY		10
#define NG_MT_CUSTOM			11
#define	NG_MT_UNKNOWN_MAP_TYPE	-1

//profile结构体
struct  NG_MAP_API NGProfile
{
public:
	NGProfile();
	~NGProfile();
	void Reset();

	bool Resize(int nSize);

	void Clear();

	int nSize;     //可以容纳的点的总个数

	//edit by jjj 2013.7.7
	long nPointsNum;		//剖面线上点的个数
	long *pImgCoordX;		//剖面线上点的坐标
	long *pImgCoordY;
	short *pImgData;		//数据值
	double *pDistance;		//距离
};
//地图接口类
struct NG_MAP_API INGMapGeo
{
	INGMapGeo();
	virtual ~INGMapGeo();

	virtual bool ReadMapData(const char *pszFilePath)=0;	//读取ldf文件
	virtual bool ReadMapDataCOM(const char *pszFilePath, double xmin, double ymin, double xmax, double ymax, double resolution, int nCoordSys) = 0;

	virtual short ShortElement(int x,int y)=0;				//获取地图中(x,y)处的数据值，(x,y)是索引值
	virtual short ShortElement(double dx, double dy, int CoordSys)=0;       //获取地图中(dx,dy)处的数据值，(dx,dy)是绝对坐标值
	virtual void SetShortElement(double dx, double dy, int CoordSys, short val)=0;	// 设置地图值

	virtual short GetDefaultValue() = 0;					//地图缺省值
	virtual bool HitTile(int nImgX,int nImgY, POINT& ptPos)=0;	//计算点落在哪个块里

	virtual double GetMapLowerLeftXCoord()=0;				//地图左下角坐标 
	virtual double GetMapLowerLeftYCoord()=0;				
	virtual double GetResolutionX()=0;						//每两个点之间的距离
	virtual double GetResolutionY()=0;
	virtual int GetMapWidth()=0;							//地图像素点个数
	virtual int GetMapHeight()=0;
	virtual int GetMapXTileConnts()=0;						//地图X方向块的个数
	virtual int GetMapYTileConnts()=0;						//地图Y方向块的个数
	virtual int GetMapXTilePixels()=0;						//地图每个块X方向像素个数
	virtual int GetMapYTilePixels()=0;						//地图每个块Y方向像素个数

	virtual const char *GetPresentationFilePath() = 0;		//配色文件
	virtual const char *GetDefaultLayerName() = 0;			//地图名字
	virtual const char *GetCoordShortName()=0;				//坐标系名字
	virtual const char *GetMapDataTypeName()=0;	
	virtual const char *GetMapDataPrefixName()=0;			//块文件名前缀
	virtual int	GetMapDataType()=0;							//地图数据类别，MT_TOPO，MT_MORPH等

	virtual NGProfile *GetProfile(POINT &ptBegin, POINT &ptEnd,NGProfile*pProfile)=0;	//给定地图上两点坐标，返回剖面线数据情况

	virtual void ReleaseTitleData(POINT &ptPos)=0;			//释放某一块地图数据
	virtual void ReleaseMapData()=0;						//释放所有地图块数据 add 2011.8.8

};

/*
add 2013.5.13 jjj
金字塔栅格地图接口类

金字塔地图包含一到多个图层,不同图层的区别在于它们的分辨率不相同
其他地图属性(地图类别，起始点坐标，坐标系等均相同)
层增加1，地图分辨率扩大2倍
比如基本分辨率 为 20 m
level0:	20m		=	20m*1		= 20*2<<0
level1:	40m		=	20m*2		= level0*2<<1
level2:	80m		=	level1*2	= level0*2<<2
level3:	160m	=	level2*2	= level0*2<<3
level4:	320m	=	level3*2	= level0*2<<4
level5:	640m	=	level4*2	= level0*2<<5
etc...

如果需要获取某个图层的地图数据,调用
bool SetActiveLayer(unsigned int lay)函数,其中参数 lay:
lay = 0		-->基本分辨率地图,level0
lay = 1		-->基本分辨率地图,level1
lay = 2		-->基本分辨率地图,level2
etc...
*/
struct NG_MAP_API IPyramidMapGeo
{
	IPyramidMapGeo();
	virtual ~IPyramidMapGeo();

	virtual bool ReadPyramidMap(const char *pFilePath)=0;	//读取栅格地图

	virtual unsigned int GetLayers()=0;						//获取金字塔层数
	virtual bool SetActiveLayer(unsigned int lay)=0;		//设置活动图层
	virtual unsigned int GetActiveLayer()=0;
	virtual INGMapGeo* GetActiveLayerPtr()=0;				//获取激活图层的地图接口对象,外部调用

	//金字塔地图的所有图层左下角相同，地图类别相同,坐标系相同,缺省值相同
	virtual double GetMapLowerLeftXCoord()=0;				//地图左下角坐标 
	virtual double GetMapLowerLeftYCoord()=0;				
	virtual int	GetMapDataType()=0;							//地图数据类别，MT_TOPO，MT_MORPH等
	virtual const char *GetCoordShortName()=0;
	virtual short GetDefaultValue() = 0;					//地图缺省值

	//金字塔地图的所有图层左下角坐标相同
	virtual double Get_Layer0_ResolutionX()=0;				//每两个点之间的距离
	virtual double Get_Layer0_ResolutionY()=0;

	double Get_Layer_ResolutionX(unsigned int lay);			//每两个点之间的距离
	double Get_Layer_ResolutionY(unsigned int lay);
};


extern "C"  NG_MAP_API INGMapGeo *NG_CreateMapGeo();		//创建一个地图数据对象
extern "C"  NG_MAP_API void NG_ReleaseMapGeo(INGMapGeo *PMap);//释放地图数据对象

extern "C"  NG_MAP_API IPyramidMapGeo *NG_Create_Pyramid_MapGeo();		//创建一个地图数据对象
extern "C"  NG_MAP_API void NG_Release_Pyramid_MapGeo(IPyramidMapGeo *PMap);//释放地图数据对象

extern "C"  NG_MAP_API INGMapGeo * NG_FindGisMap(const char * gismapPath);
extern "C"  NG_MAP_API void NG_ReleaseGisMap(const char * gismapPath);

#endif