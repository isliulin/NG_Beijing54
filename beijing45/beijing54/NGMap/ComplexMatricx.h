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
//һ���Σ�����ֵ����ͬ


class CNGMapGeo;
class TILEINFO 
{
protected:
	bool bInMemory;					// ��ͼ�������Ƿ���ؽ��ڴ�ӳ��		// ��ͼ����������·��
	void * pTileMatrix;		// ��ͼ������,
	omp_lock_t m_omplock;
protected:
    CNGMapGeo *m_pManager;
	int m_xInd;
	int m_yInd;
public:
	TILEINFO();
	~TILEINFO();
protected:
	short m_DefaultValue;	//��ͼȱʡֵ
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