#ifndef __ComplexMatrix_h__
#define __ComplexMatrix_h__

#include <omp.h>

#include <string>
enum EDirection
{
	eRowsTopToBottom,
	eRowsBottomToTop
};

enum EByteOrder
{
	eBigEndian,
	eLittleEndian
};

//Source File Type
enum FileType
{
	FT_UNKNOWN = -1,
	TIFFFILE = 0,
	LZWTIFF,
	UserDefined,
	ASCII,
	ColorTable,
	Binary,
	LSMatrixFile,
	Asc,
	X_Y_Value,
	BandGroup,//(Bil,Bip,Bsq)
	Planet,
	TopoData,
	CoverageData
};

//Pixel Type
enum BitType{
	_8Bit = 0,
	_8BitUnsigned,	
	_16BitSigned
};
//一个段，数据值都相同


class CNGMapGeo;
class TILEINFO 
{
protected:
	bool bInMemory;					// 地图块数据是否加载进内存映射		// 地图块数据物理路径
	void * pTileMatrix;		// 地图块数据,
	omp_lock_t m_omplock;
protected:
    CNGMapGeo *m_pManager;
	int m_xInd;
	int m_yInd;
public:
	TILEINFO();
	~TILEINFO();
protected:
	short m_DefaultValue;	//地图缺省值
protected:
	short ShortValueInMemory(int x,int y);
	void SetShortValueInMemory(int x,int y, short val);
	void ReadDataFromMap();
	void CheckSameValue();
public:
	bool HasMatrix(){return pTileMatrix!=NULL;}
	short ShortElement(int x,int y);
	void SetShortElement(int x,int y, short val);
	void InitMapInfo(CNGMapGeo *pManager,int xindex,int yindex);
	void ReleaseData();
};

#endif