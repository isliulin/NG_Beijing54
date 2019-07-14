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
	double** m_ppdMargin;//ַͬ���ŵ�����
	double** m_ppdDis;//ַͬ���ŵľ���
	int* m_pIntNum;
	CCoLocationResult* m_pCoLocationResult;
	bool** m_ppCoAdj;

	int m_nTrxNumber;
	int m_nRxNumber;

	//���յ�ĳ�ǿ����
	double** m_pdFst;
	double** m_pdTempFst;
	double** m_ppdProcteRate;

	//ÿ������̨���ܵ����ŵ�������û�и��ž͸�ֵΪ-1
	int** m_pnIntIndex;

	//�������ļ�·��
	string m_strProratePath;

	Compute_Antenna_Extra *m_pTrxAnt;			//��·����̨����
	Compute_Antenna_Extra *m_pRxAnt;			//��·����̨����

	double m_dPDFLineWidth;
	double m_dFont;
	Compute_ParaMain* m_pComputeParaMain;
	float m_dRxEmin;
	double* m_pdCI;//��·���ŷ���ʱ�� ҲҪ����ӵ�CIֵ
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
