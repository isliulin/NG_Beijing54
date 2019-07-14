#pragma once
#include "ColLocationResult.h"
#include "../ComputePrediction/IComputePrediction.h"
#include <string>
#include "../XMLModuleLib/ReadProtectRate.h"
#include "..\EarthCoordCompute\EarthCoordManage.h"
#include "..\KoordTrans\KoordTrans\KoordTrans.h"
#include "..\Basicdef\MacroDef.h"
#include <math.h>
using namespace std;
class CIntBase
{
public:
	CIntBase(void);
	virtual ~CIntBase(void);
protected:
	double** m_ppdMargin;//同址干扰的余量
	double** m_ppdDis;//同址干扰的距离
	int* m_pIntNum;
	CCoLocationResult* m_pCoLocationResult;
	bool** m_ppCoAdj;

	int m_nTrxNumber;
	int m_nRxNumber;

	//接收点的场强数据
	double** m_pdFst;
	double** m_pdTempFst;
	double** m_ppdProcteRate;

	//每个接收台的受到干扰的索引，没有干扰就赋值为-1
	int** m_pnIntIndex;

	//保护率文件路径
	string m_strProratePath;

	Compute_Antenna_Extra *m_pTrxAnt;			//链路发射台数据
	Compute_Antenna_Extra *m_pRxAnt;			//链路接收台数据

	double m_dPDFLineWidth;
	double m_dFont;
	Compute_ParaMain* m_pComputeParaMain;
	float m_dRxEmin;
	double* m_pdCI;//链路干扰分析时候 也要算叠加的CI值
public:
	virtual void InitColCalParam(CCoLocationResult* pCoLocationResult ,int nRxNum,int nTrxNum,Compute_Antenna_Extra *pTrxAnt,Compute_Antenna_Extra *pRxAnt,
		Compute_ParaMain* pComputeParaMain,const char *pProrateFile);
	bool AnalyseCol();
public:
	int m_nReturnValue;

protected:
	virtual bool CalCol();
	virtual bool WriteColData();
	double CalDis(const CGeoPoint& p1,const CGeoPoint& p2 );
	virtual bool CalRXFst(bool bCalCollocationInt = false);
	virtual bool SortInt();
	virtual bool CalRxCI();
	void InitPara();
};
