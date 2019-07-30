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


//��ͼ��������
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

//profile�ṹ��
struct  NG_MAP_API NGProfile
{
public:
	NGProfile();
	~NGProfile();
	void Reset();

	bool Resize(int nSize);

	void Clear();

	int nSize;     //�������ɵĵ���ܸ���

	//edit by jjj 2013.7.7
	long nPointsNum;		//�������ϵ�ĸ���
	long *pImgCoordX;		//�������ϵ������
	long *pImgCoordY;
	short *pImgData;		//����ֵ
	double *pDistance;		//����
};
//��ͼ�ӿ���
struct NG_MAP_API INGMapGeo
{
	INGMapGeo();
	virtual ~INGMapGeo();

	virtual bool ReadMapData(const char *pszFilePath)=0;	//��ȡldf�ļ�
	virtual bool ReadMapDataCOM(const char *pszFilePath, double xmin, double ymin, double xmax, double ymax, double resolution, int nCoordSys) = 0;

	virtual short ShortElement(int x,int y)=0;				//��ȡ��ͼ��(x,y)��������ֵ��(x,y)������ֵ
	virtual short ShortElement(double dx, double dy, int CoordSys)=0;       //��ȡ��ͼ��(dx,dy)��������ֵ��(dx,dy)�Ǿ�������ֵ
	virtual void SetShortElement(double dx, double dy, int CoordSys, short val)=0;	// ���õ�ͼֵ

	virtual short GetDefaultValue() = 0;					//��ͼȱʡֵ
	virtual bool HitTile(int nImgX,int nImgY, POINT& ptPos)=0;	//����������ĸ�����

	virtual double GetMapLowerLeftXCoord()=0;				//��ͼ���½����� 
	virtual double GetMapLowerLeftYCoord()=0;				
	virtual double GetResolutionX()=0;						//ÿ������֮��ľ���
	virtual double GetResolutionY()=0;
	virtual int GetMapWidth()=0;							//��ͼ���ص����
	virtual int GetMapHeight()=0;
	virtual int GetMapXTileConnts()=0;						//��ͼX�����ĸ���
	virtual int GetMapYTileConnts()=0;						//��ͼY�����ĸ���
	virtual int GetMapXTilePixels()=0;						//��ͼÿ����X�������ظ���
	virtual int GetMapYTilePixels()=0;						//��ͼÿ����Y�������ظ���

	virtual const char *GetPresentationFilePath() = 0;		//��ɫ�ļ�
	virtual const char *GetDefaultLayerName() = 0;			//��ͼ����
	virtual const char *GetCoordShortName()=0;				//����ϵ����
	virtual const char *GetMapDataTypeName()=0;	
	virtual const char *GetMapDataPrefixName()=0;			//���ļ���ǰ׺
	virtual int	GetMapDataType()=0;							//��ͼ�������MT_TOPO��MT_MORPH��

	virtual NGProfile *GetProfile(POINT &ptBegin, POINT &ptEnd,NGProfile*pProfile)=0;	//������ͼ���������꣬�����������������

	virtual void ReleaseTitleData(POINT &ptPos)=0;			//�ͷ�ĳһ���ͼ����
	virtual void ReleaseMapData()=0;						//�ͷ����е�ͼ������ add 2011.8.8

};

/*
add 2013.5.13 jjj
������դ���ͼ�ӿ���

��������ͼ����һ�����ͼ��,��ͬͼ��������������ǵķֱ��ʲ���ͬ
������ͼ����(��ͼ�����ʼ�����꣬����ϵ�Ⱦ���ͬ)
������1����ͼ�ֱ�������2��
��������ֱ��� Ϊ 20 m
level0:	20m		=	20m*1		= 20*2<<0
level1:	40m		=	20m*2		= level0*2<<1
level2:	80m		=	level1*2	= level0*2<<2
level3:	160m	=	level2*2	= level0*2<<3
level4:	320m	=	level3*2	= level0*2<<4
level5:	640m	=	level4*2	= level0*2<<5
etc...

�����Ҫ��ȡĳ��ͼ��ĵ�ͼ����,����
bool SetActiveLayer(unsigned int lay)����,���в��� lay:
lay = 0		-->�����ֱ��ʵ�ͼ,level0
lay = 1		-->�����ֱ��ʵ�ͼ,level1
lay = 2		-->�����ֱ��ʵ�ͼ,level2
etc...
*/
struct NG_MAP_API IPyramidMapGeo
{
	IPyramidMapGeo();
	virtual ~IPyramidMapGeo();

	virtual bool ReadPyramidMap(const char *pFilePath)=0;	//��ȡդ���ͼ

	virtual unsigned int GetLayers()=0;						//��ȡ����������
	virtual bool SetActiveLayer(unsigned int lay)=0;		//���ûͼ��
	virtual unsigned int GetActiveLayer()=0;
	virtual INGMapGeo* GetActiveLayerPtr()=0;				//��ȡ����ͼ��ĵ�ͼ�ӿڶ���,�ⲿ����

	//��������ͼ������ͼ�����½���ͬ����ͼ�����ͬ,����ϵ��ͬ,ȱʡֵ��ͬ
	virtual double GetMapLowerLeftXCoord()=0;				//��ͼ���½����� 
	virtual double GetMapLowerLeftYCoord()=0;				
	virtual int	GetMapDataType()=0;							//��ͼ�������MT_TOPO��MT_MORPH��
	virtual const char *GetCoordShortName()=0;
	virtual short GetDefaultValue() = 0;					//��ͼȱʡֵ

	//��������ͼ������ͼ�����½�������ͬ
	virtual double Get_Layer0_ResolutionX()=0;				//ÿ������֮��ľ���
	virtual double Get_Layer0_ResolutionY()=0;

	double Get_Layer_ResolutionX(unsigned int lay);			//ÿ������֮��ľ���
	double Get_Layer_ResolutionY(unsigned int lay);
};


extern "C"  NG_MAP_API INGMapGeo *NG_CreateMapGeo();		//����һ����ͼ���ݶ���
extern "C"  NG_MAP_API void NG_ReleaseMapGeo(INGMapGeo *PMap);//�ͷŵ�ͼ���ݶ���

extern "C"  NG_MAP_API IPyramidMapGeo *NG_Create_Pyramid_MapGeo();		//����һ����ͼ���ݶ���
extern "C"  NG_MAP_API void NG_Release_Pyramid_MapGeo(IPyramidMapGeo *PMap);//�ͷŵ�ͼ���ݶ���

extern "C"  NG_MAP_API INGMapGeo * NG_FindGisMap(const char * gismapPath);
extern "C"  NG_MAP_API void NG_ReleaseGisMap(const char * gismapPath);

#endif