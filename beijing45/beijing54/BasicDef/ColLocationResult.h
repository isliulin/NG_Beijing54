#pragma once
#include <string>
struct _TCoLocationRes
{
	std::string tx_id;
	double freq; //MHz
	double bandwidth;//kHz
	double EIRP;
	double YL;//余量
	double pro_int;//干扰概率
	double distance;//距离
	double int_field;//干扰强度
	bool f_coadj;//同邻频干扰时true:同频 false：邻频
	int nHarmonics;
	_TCoLocationRes()
	{
		freq = 0; //MHz
		bandwidth = 0;//kHz
		EIRP = 0;
		YL = 0;//余量
		pro_int = 100;//干扰概率
		distance = 0;//距离
		int_field = 0;//干扰强度
		f_coadj = true;//同邻频干扰时指定是同频还是邻频
		nHarmonics = 2;
	}
};
class CCoLocationResult
{
public:
	std::string rx_id;
	double rx_freq;
	double rx_band;
	CCoLocationResult(void);
	virtual ~CCoLocationResult(void);
protected:
	_TCoLocationRes *CoAdjInt;
	int nCoadj;
	//
	_TCoLocationRes *BlockInt;
	int nBlock;
	//
	_TCoLocationRes *IFInt;
	int nIF;
	//
	_TCoLocationRes * MFInt;
	int nMF;
	//
	_TCoLocationRes * HarmonicsInt;
	int nHarm;
	//
	_TCoLocationRes * ModulationInt;
	int nModu;
	//
public:
	_TCoLocationRes * GetCoAdjRes(int & num,bool bCreateNew = false);
	_TCoLocationRes * GetBlockRes(int & num,bool bCreateNew = false);
	_TCoLocationRes * GetIFRes(int & num,bool bCreateNew = false);
	_TCoLocationRes * GetMFRes(int & num,bool bCreateNew = false);
	_TCoLocationRes * GetHarmonicsRes(int & num,bool bCreateNew = false);
	_TCoLocationRes * GetModulationRes(int & num,bool bCreateNew = false);
protected:
	_TCoLocationRes * GetCoLocationRes(int & num,_TCoLocationRes *& pRes,int & nRes, bool bCreateNew = false);
};
