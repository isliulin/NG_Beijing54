#pragma once

#include "INGMapGeo.h"
#include "ComplexMatricx.h"
#include <string>
#include <map>
using namespace std;
//��ͼ����Ϣ


class CNGMapGeo :public INGMapGeo
{
	friend class TILEINFO;
public:
	CNGMapGeo();
	virtual ~CNGMapGeo();

	enum {NameBytes = 64};
	enum {MAX_FILE_PATH = 260};
	
public:
	virtual bool ReadMapData(const char *pszFilePath);						//��ȡldf�ļ�
	virtual bool ReadMapDataCOM(const char *pszFilePath, double xmin, double ymin, double xmax, double ymax, double resolution, int nCoordSys);

	virtual short ShortElement(int x,int y);								//��ȡ��ͼ��(x,y)��������ֵ	
	virtual short ShortElement(double dx, double dy, int CoordSys);
	virtual void SetShortElement(double dx, double dy, int CoordSys, short val);	// ���õ�ͼֵ
	virtual short GetDefaultValue(){return m_DefaultValue;}					//��ͼȱʡֵ
	virtual bool HitTile(int nImgX,int nImgY, POINT& ptPos);				//����������ĸ�����

	virtual double GetMapLowerLeftXCoord(){return m_XLowLeft;}				//��ͼ���½����� 
	virtual double GetMapLowerLeftYCoord(){return m_YLowLeft;}				
	virtual double GetResolutionX(){return m_Xspacing;}						//ÿ������֮��ľ���
	virtual double GetResolutionY(){return m_Yspacing;}
	virtual int GetMapWidth(){return m_nWidth;}								//��ͼ���ص����
	virtual int GetMapHeight(){return m_nHeight;}
	virtual int GetMapXTileConnts(){return m_nXBlocks;}						//��ͼX�����ĸ���
	virtual int GetMapYTileConnts(){return m_nYBlocks;}						//��ͼY�����ĸ���
	virtual int GetMapXTilePixels(){return m_Tile_nX;}						//��ͼÿ����X�������ظ���
	virtual int GetMapYTilePixels(){return m_Tile_nY;}						//��ͼÿ����Y�������ظ���

	virtual const char *GetPresentationFilePath(){return szPresentFilePath;}//��ɫ�ļ�
	virtual const char *GetDefaultLayerName(){return szLayerName;}			//��ͼ����
	virtual const char *GetCoordShortName(){return szCoordShortName;}		//����ϵ����
	virtual const char *GetMapDataTypeName(){return szMapDataTypeName;}	
	virtual const char *GetMapDataPrefixName(){return szMapDataPrefixName;}
	virtual int	GetMapDataType();											//��ͼ�������MT_TOPO��MT_MORPH��
	
	virtual NGProfile *GetProfile(POINT &ptBegin, POINT &ptEnd,NGProfile *pProfile);
	
	virtual void ReleaseTitleData(POINT &ptPos);							//�ͷ�ĳһ���ͼ����
	virtual void ReleaseMapData();											//�ͷ����е�ͼ������ add 2011.8.8				
protected:		
	void ReleaseParticalTitle(int xIndex,int yIndex,int resverblock); //����Ҫ���صĿ����ݣ��ͷ�һ��������
	int CreateDefaultFile( const char * szFileName, double xmin, double ymin, double xmax, double ymax, double resolution, int nCoorSys );
	int CreateDefaultBinaryFile();
protected:
	double	m_XLowLeft;
	double	m_YLowLeft;						//���½�����ֵ
	double m_Xspacing;
	double m_Yspacing;						//�ֱ��ʣ�ÿ�������ص�֮��ľ���
	double m_XAreaExtend;					//���ŵ�ͼ��С
	double m_YAreaExtend;
	int m_Tile_nX;							//ÿһ�����ص����
	int m_Tile_nY;							//ÿһ�����ص����
	int m_nWidth;							//���ŵ�ͼ���ص����
	int m_nHeight;
	short m_DefaultValue;					//��ͼȱʡֵ
	int m_nCoordSys;

	//Add by Liuqingmei@20111207
	FileType m_eFileType;					//�ļ������,��Binary, Tiff��
	BitType m_eBitType;						//�ļ������ص�����,��char, unsigned char, short��

	EByteOrder m_eByteOrder;  //�ֽ���
	EDirection m_eDirection;  //���ݴ洢����Rows_Top_To_Bottom/Rows_Bottom_To_Top

	char szCurrTileDir[MAX_FILE_PATH];
	char szPresentFilePath[MAX_FILE_PATH];
	char szLayerName[NameBytes];
	char szCoordShortName[NameBytes];
	char szMapDataTypeName[NameBytes];
	char szMapDataPrefixName[NameBytes];

	TILEINFO *m_pTileInfo;
	int m_nXBlocks;							//X �����ͼ�����
	int m_nYBlocks;							//Y �����ͼ�����

	//NGProfile *m_pProfile;					//

	std::string m_strDir;					//ldf�ļ�����Ŀ¼
	std::string m_strDataFileFormat;

	bool m_bReadOnlyFlag;					//��ͼ����ֻ����־
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