#pragma once

#include "INGMapGeo.h"
#include "ComplexMatricx.h"
#include <string>
#include <map>
using namespace std;
//地图块信息


class CNGMapGeo :public INGMapGeo
{
	friend class TILEINFO;
public:
	CNGMapGeo();
	virtual ~CNGMapGeo();

	enum {NameBytes = 64};
	enum {MAX_FILE_PATH = 260};
	
public:
	virtual bool ReadMapData(const char *pszFilePath);						//读取ldf文件
	virtual bool ReadMapDataCOM(const char *pszFilePath, double xmin, double ymin, double xmax, double ymax, double resolution, int nCoordSys);

	virtual short ShortElement(int x,int y);								//获取地图中(x,y)处的数据值	
	virtual short ShortElement(double dx, double dy, int CoordSys);
	virtual void SetShortElement(double dx, double dy, int CoordSys, short val);	// 设置地图值
	virtual short GetDefaultValue(){return m_DefaultValue;}					//地图缺省值
	virtual bool HitTile(int nImgX,int nImgY, POINT& ptPos);				//计算点落在哪个块里

	virtual double GetMapLowerLeftXCoord(){return m_XLowLeft;}				//地图左下角坐标 
	virtual double GetMapLowerLeftYCoord(){return m_YLowLeft;}				
	virtual double GetResolutionX(){return m_Xspacing;}						//每两个点之间的距离
	virtual double GetResolutionY(){return m_Yspacing;}
	virtual int GetMapWidth(){return m_nWidth;}								//地图像素点个数
	virtual int GetMapHeight(){return m_nHeight;}
	virtual int GetMapXTileConnts(){return m_nXBlocks;}						//地图X方向块的个数
	virtual int GetMapYTileConnts(){return m_nYBlocks;}						//地图Y方向块的个数
	virtual int GetMapXTilePixels(){return m_Tile_nX;}						//地图每个块X方向像素个数
	virtual int GetMapYTilePixels(){return m_Tile_nY;}						//地图每个块Y方向像素个数

	virtual const char *GetPresentationFilePath(){return szPresentFilePath;}//配色文件
	virtual const char *GetDefaultLayerName(){return szLayerName;}			//地图名字
	virtual const char *GetCoordShortName(){return szCoordShortName;}		//坐标系名字
	virtual const char *GetMapDataTypeName(){return szMapDataTypeName;}	
	virtual const char *GetMapDataPrefixName(){return szMapDataPrefixName;}
	virtual int	GetMapDataType();											//地图数据类别，MT_TOPO，MT_MORPH等
	
	virtual NGProfile *GetProfile(POINT &ptBegin, POINT &ptEnd,NGProfile *pProfile);
	
	virtual void ReleaseTitleData(POINT &ptPos);							//释放某一块地图数据
	virtual void ReleaseMapData();											//释放所有地图块数据 add 2011.8.8				
protected:		
	void ReleaseParticalTitle(int xIndex,int yIndex,int resverblock); //根据要加载的块数据，释放一部分数据
	int CreateDefaultFile( const char * szFileName, double xmin, double ymin, double xmax, double ymax, double resolution, int nCoorSys );
	int CreateDefaultBinaryFile();
protected:
	double	m_XLowLeft;
	double	m_YLowLeft;						//左下角坐标值
	double m_Xspacing;
	double m_Yspacing;						//分辨率，每两个像素点之间的距离
	double m_XAreaExtend;					//整张地图大小
	double m_YAreaExtend;
	int m_Tile_nX;							//每一块像素点个数
	int m_Tile_nY;							//每一块像素点个数
	int m_nWidth;							//整张地图像素点个数
	int m_nHeight;
	short m_DefaultValue;					//地图缺省值
	int m_nCoordSys;

	//Add by Liuqingmei@20111207
	FileType m_eFileType;					//文件的类别,如Binary, Tiff等
	BitType m_eBitType;						//文件中像素的类型,如char, unsigned char, short等

	EByteOrder m_eByteOrder;  //字节序
	EDirection m_eDirection;  //数据存储方向，Rows_Top_To_Bottom/Rows_Bottom_To_Top

	char szCurrTileDir[MAX_FILE_PATH];
	char szPresentFilePath[MAX_FILE_PATH];
	char szLayerName[NameBytes];
	char szCoordShortName[NameBytes];
	char szMapDataTypeName[NameBytes];
	char szMapDataPrefixName[NameBytes];

	TILEINFO *m_pTileInfo;
	int m_nXBlocks;							//X 方向地图块个数
	int m_nYBlocks;							//Y 方向地图块个数

	//NGProfile *m_pProfile;					//

	std::string m_strDir;					//ldf文件所在目录
	std::string m_strDataFileFormat;

	bool m_bReadOnlyFlag;					//地图数据只读标志
};

struct CNGMapIndex
{
	INGMapGeo* pMap;
	int useindex;
};
class CNGGISMapManger
{
public:
	CNGGISMapManger();
	~CNGGISMapManger();
protected: 
	omp_lock_t m_lock;
	map<string,CNGMapIndex> gismaps;
public:
	INGMapGeo * Find(string mappath);
	void ReleaseMap(string mappath);

};