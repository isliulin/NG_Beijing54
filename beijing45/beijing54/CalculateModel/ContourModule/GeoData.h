// GeoData.h: interface for the CGeoData class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __GEODATA_H__
#define __GEODATA_H__

#include "GeoStruct.h"
#include <string>
using namespace std;
class  CGeoData  
{
public:
	CGeoData();
	virtual ~CGeoData();

public:
	//´ÅÅÌÎÄ¼þ²Ù×÷
	bool ReadData(const char* pathName);
	bool SetRasterData(void * pRasterData);
	bool SaveData(string pathName);

	//
	CGridDataInfo& GetDataInfo(){return m_DataInfo;}
	float** GetGridData(){return m_ppGridData;}

private:
	CGridDataInfo m_DataInfo;
	float ** m_ppGridData;

private:
	CGeoData(const CGeoData&);
	CGeoData& operator=(const CGeoData&);


};

#endif // !defined(AFX_GEODATA_H__5DFAFE72_948C_402A_B470_3721DB3DA1D8__INCLUDED_)
