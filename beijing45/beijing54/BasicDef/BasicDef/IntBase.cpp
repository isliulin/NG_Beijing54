#include "IntBase.h"

CIntBase::CIntBase(void)
{
	m_pdFst = NULL;
	m_pdTempFst = NULL;
	m_ppdProcteRate = NULL;
	m_pnIntIndex = NULL;

	m_ppdMargin = NULL;
	m_ppdDis = NULL;
	m_pIntNum = NULL;
	m_ppCoAdj =  NULL;
	m_pdCI = NULL;

	m_nTrxNumber = 0;
	m_nRxNumber = 0;
	m_dPDFLineWidth = 20.0;
	m_dFont = 10;
		
}

CIntBase::~CIntBase(void)
{
	if (m_pdCI != NULL)
	{
		delete []m_pdCI;
		m_pdCI = NULL;
	} 
	if (m_pnIntIndex != NULL)
	{
		for (int i=0;i<m_nRxNumber;i++)
		{
			if (m_pnIntIndex[i] != NULL)
			{
				delete []m_pnIntIndex[i];
			}
		}
		delete []m_pnIntIndex;
		m_pnIntIndex = NULL;
	} 

	if (m_pdFst != NULL)
	{
		for (int i=0;i<m_nRxNumber;i++)
		{
			if (m_pdFst[i] != NULL)
			{
				delete []m_pdFst[i];
			}
		}
		delete []m_pdFst;
		m_pdFst = NULL;
	} 
	if (m_pdTempFst != NULL)
	{
		for (int i=0;i<m_nRxNumber;i++)
		{
			if (m_pdTempFst[i] != NULL)
			{
				delete []m_pdTempFst[i];
			}
		}
		delete []m_pdTempFst;
		m_pdTempFst = NULL;
	} 
	if (m_ppCoAdj != NULL)
	{
		for (int i=0;i<m_nRxNumber;i++)
		{
			if (m_ppCoAdj[i] != NULL)
			{
				delete []m_ppCoAdj[i];
			}
		}
		delete []m_ppCoAdj;
		m_ppCoAdj = NULL;
	} 
	if (m_ppdMargin != NULL)
	{
		for (int i=0;i<m_nRxNumber;i++)
		{
			if (m_ppdMargin[i] != NULL)
			{
				delete []m_ppdMargin[i];
			}
		}
		delete []m_ppdMargin;
		m_ppdMargin = NULL;
	} 
	if (m_ppdDis != NULL)
	{
		for (int i=0;i<m_nRxNumber;i++)
		{
			if (m_ppdDis[i] != NULL)
			{
				delete []m_ppdDis[i];
			}
		}
		delete []m_ppdDis;
		m_ppdDis = NULL;
	}
	if (m_pIntNum != NULL)
	{
		delete []m_pIntNum;
		m_pIntNum = NULL;
	} 
}

void CIntBase::InitColCalParam( CCoLocationResult* pCoLocationResult ,int nRxNum,int nTrxNum,Compute_Antenna_Extra *pTrxAnt,Compute_Antenna_Extra *pRxAnt, Compute_ParaMain* pComputeParaMain,const char *pProrateFile )
{
	if (pProrateFile != NULL)
		m_strProratePath = pProrateFile;	//保护率文件

	m_pCoLocationResult = pCoLocationResult;
	m_nTrxNumber = nTrxNum;
	m_nRxNumber = nRxNum;		

	m_pTrxAnt = pTrxAnt;
	m_pRxAnt = pRxAnt;
	m_pComputeParaMain = pComputeParaMain;

	//m_dRxEmin = pRxAnt[0].mdThresholddBm +77.216 +20*log10(m_pTrxAnt[0].mdFreqMhz);

	m_ppCoAdj = new bool *[m_nRxNumber];
	for (int x = 0;x < m_nRxNumber ;x ++)
	{
		m_ppCoAdj[x] = NULL;
		m_ppCoAdj[x] = new bool[m_nTrxNumber];
	}
	InitPara();

	ReadProtectRate cReadProtectRate;
	for (int i=0;i<m_nRxNumber;i++)
	{
		for (int j=0;j<m_nTrxNumber;j++)
		{
			if(j == i)
			{
				m_ppdProcteRate[i][j] = -9999.0;
				continue;
			}
			double dFreqDiffMhz = abs(m_pRxAnt[i].mdFreqMhz - m_pTrxAnt[j].mdFreqMhz) ;
			double dBWMhz = (m_pRxAnt[i].mdRXBandwidthMHz + m_pTrxAnt[j].mdBandwidthHz*(1e-6))/2.0;
			if (dFreqDiffMhz <= dBWMhz)
			{
				cReadProtectRate.LoadXML(m_strProratePath.c_str(),false,0,m_ppdProcteRate[i][j]);
				m_ppCoAdj[i][j] = true;
			}
			else if (dFreqDiffMhz <= 2*dBWMhz)
			{
				cReadProtectRate.LoadXML(m_strProratePath.c_str(),false,1,m_ppdProcteRate[i][j]);
				m_ppCoAdj[i][j] = false;
			}
			else
			{
				m_ppdProcteRate[i][j] = -9999.0;
			}
		}
	}

	m_ppdMargin = new double *[m_nRxNumber];
	for (int x = 0;x < m_nRxNumber ;x ++)
	{
		m_ppdMargin[x] = NULL;
		m_ppdMargin[x] = new double[m_nTrxNumber];
	}
	m_ppdDis = new double *[m_nRxNumber];
	for (int x = 0;x < m_nRxNumber ;x ++)
	{
		m_ppdDis[x] = NULL;
		m_ppdDis[x] = new double[m_nTrxNumber];
	}

	m_pIntNum = new int[m_nRxNumber];
}

bool CIntBase::AnalyseCol()
{
	CalRXFst();
	if (m_nReturnValue == NG_SUCCESS)
	{
		CalCol();
		SortInt();
		WriteColData();
	}
	return true;
}

bool CIntBase::WriteColData()
{
	return true;
}
double CIntBase::CalDis( const CGeoPoint& p1,const CGeoPoint& p2 )
{
	EarthCoord2D earth2D;
	double dA = 0;
	static double dF = 0;
	//获取地图坐标系对应的地球长轴和扁平率 
	ng_GetProjEllipSoid_AF(103,&dA,&dF);
	earth2D.Set_CurrentEllipSoid_AF(dA,1.0/dF);

	DecimalToRad(p1.m_Point.x, earth2D.m_LonRad1);
	DecimalToRad(p1.m_Point.y, earth2D.m_LatRad1);

	DecimalToRad(p2.m_Point.x, earth2D.m_LonRad2);
	DecimalToRad(p2.m_Point.y, earth2D.m_LatRad2);


	//计算方向和距离
	earth2D.CalDistance2D();
	return earth2D.m_DistEllip;
}

bool CIntBase::CalRXFst( bool bCalCollocationInt /*= false*/ )
{
	IComputePrediction* pComputePrediction = NULL;
	if (bCalCollocationInt)
	{

	}
	else
	{
		pComputePrediction = NG_CreateComputeObj(eInterfAnalyseModel);
	}	
	//确保计算场强
	m_pComputeParaMain->meResultType = eFieldSth;
	CGeoPoint point;
	for (int i=0;i<m_nRxNumber;i++)
	{
		point = m_pRxAnt[i].mLocation;		//接收台位置信息
		m_pComputeParaMain->mdRXHeightM = m_pRxAnt[i].mdAntHeightM;
		m_pComputeParaMain->meHeightType = eAGroundL;

		for (int j=0;j<m_nTrxNumber;j++)
		{
			m_nReturnValue = pComputePrediction->DoCalculte(&m_pTrxAnt[j], m_pComputeParaMain, &point, NULL, NULL, m_pdFst[i][j]);
			if (m_nReturnValue != NG_SUCCESS)
			{
#if 0
				NG_ReleaseComputeObj(pComputePrediction);
				pComputePrediction = NULL;
				return false;
#else
				if (m_nReturnValue == TRANSMODEL_FREQ_OUTOFRANGE)
				{
					m_pdFst[i][j] = UNCALCULATE;
					m_nReturnValue = NG_SUCCESS;
				}
				else
				{
					NG_ReleaseComputeObj(pComputePrediction);
					pComputePrediction = NULL;
					return false;
				}
#endif
			}
			m_pdTempFst[i][j] = m_pdFst[i][j];			
		}
	}

	//add by jjj 2013.7.15
	NG_ReleaseComputeObj(pComputePrediction);
	pComputePrediction = NULL;

	return true;
}

bool CIntBase::SortInt()
{
	int nTemp;
	double dFstTemp;
	for (int i=0;i<m_nRxNumber;i++)
	{
		for (int j=0;j<m_nTrxNumber;j++)
		{
			for (int k=j+1;k<m_nTrxNumber;k++)
			{
				if (m_pdTempFst[i][j]<m_pdTempFst[i][k])
				{
					nTemp = m_pnIntIndex[i][j];
					m_pnIntIndex[i][j] = m_pnIntIndex[i][k];
					m_pnIntIndex[i][k] = nTemp;

					dFstTemp = m_pdTempFst[i][j];
					m_pdTempFst[i][j] = m_pdTempFst[i][k];
					m_pdTempFst[i][k] = dFstTemp;
				}
			}
		}
	}
	return true;
}

bool CIntBase::CalCol()
{
	return true;
}

void CIntBase::InitPara()
{
	m_pdCI = new double[m_nRxNumber];
	m_pdFst = new double *[m_nRxNumber];
	for (int x = 0;x < m_nRxNumber ;x ++)
	{
		m_pdFst[x] = NULL;
		m_pdFst[x] = new double[m_nTrxNumber];
	}
	m_pdTempFst = new double *[m_nRxNumber];
	for (int x = 0;x < m_nRxNumber ;x ++)
	{
		m_pdTempFst[x] = NULL;
		m_pdTempFst[x] = new double[m_nTrxNumber];
	}
	m_ppdProcteRate = new double *[m_nRxNumber];
	for (int x = 0;x < m_nRxNumber ;x ++)
	{
		m_ppdProcteRate[x] = NULL;
		m_ppdProcteRate[x] = new double[m_nTrxNumber];
	}
	m_pnIntIndex = new int *[m_nRxNumber];
	for (int x = 0;x < m_nRxNumber ;x ++)
	{
		m_pnIntIndex[x] = NULL;
		m_pnIntIndex[x] = new int[m_nTrxNumber];
	}
}

bool CIntBase::CalRxCI()
{
	double dintValue = 0.0f;

	for (int i=0;i<m_nRxNumber;i++)
	{
		double fEMinUV = pow(10, m_dRxEmin/5);
		dintValue = fEMinUV;
		for (int j=0;j<m_nTrxNumber;j++)
		{
			if (i != j)
			{
				if (m_pdFst[i][j] >-200.0 && m_ppdProcteRate[i][j]>-1000.0)
				{
					dintValue += (double)pow(10, (m_pdFst[i][j] + m_ppdProcteRate[i][j])/5.0);

				}
			}
		}
		dintValue = 5*log10(dintValue);
		m_pdCI[i] = m_pdFst[i][i] - dintValue;
	}
	return true;
}