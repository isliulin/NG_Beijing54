#pragma once
#include <string>
struct _TCoLocationRes
{
	std::string tx_id;
	double freq; //MHz
	double bandwidth;//kHz
	double EIRP;
	double YL;//����
	double pro_int;//���Ÿ���
	double distance;//����
	double int_field;//����ǿ��
	bool f_coadj;//ͬ��Ƶ����ʱtrue:ͬƵ false����Ƶ
	int nHarmonics;
	_TCoLocationRes()
	{
		freq = 0; //MHz
		bandwidth = 0;//kHz
		EIRP = 0;
		YL = 0;//����
		pro_int = 100;//���Ÿ���
		distance = 0;//����
		int_field = 0;//����ǿ��
		f_coadj = true;//ͬ��Ƶ����ʱָ����ͬƵ������Ƶ
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
