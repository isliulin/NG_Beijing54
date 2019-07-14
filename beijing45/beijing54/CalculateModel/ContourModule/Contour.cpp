// Contour.cpp: implementation of the CContour class.
//
//////////////////////////////////////////////////////////////////////


#include "ContourTracer.h"
#include "ContourValues.h"
#include "Contour.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContour::CContour(CGeoData* pOwner)
{
	m_pDataOwner = pOwner;
//	m_pContourDrawer = NULL;
//	m_Contours.RemoveAll();
	m_Contours.clear();
	m_bReGenerated = false;

}


CContour::~CContour()
{
	RemoveAllContours();
	
// 	if( m_pContourDrawer != NULL )
// 		delete m_pContourDrawer;
}

void CContour::GenerateContours()
{//���ɵ�ֵ��

	int numContours = GetNumberOfValues();
	if( numContours <= 0 )
		return;


	if( this->IsHavingContours() )
	{
		this->RemoveAllContours();
	}

	CContourTracer Tracer;
	
	//����ֵ��׷������������
	Tracer.SetGridDataInfo(m_pDataOwner->GetDataInfo());
	Tracer.SetInput(m_pDataOwner->GetGridData());

	CCurveList *pCurveList;
	for(int i=0; i<numContours; i++)
	{
		pCurveList = new CCurveList;
		if(pCurveList==NULL)
		{
			return;
		}

		Tracer.SetOutput(pCurveList);
		if( !Tracer.ExecuteTracing(m_contourValues.GetValue(i)) )
		{
			delete pCurveList;
		}
		else
		{
			m_Contours.push_back(pCurveList);
		}		

	}

	m_bReGenerated = true; //���������˵�ֵ��

}

void CContour::RemoveAllContours()
{
	int num = m_Contours.size();
	if( num > 0 )
	{
		CCurveList* pCurveList;
		for(int i=0; i<num; i++)
		{
			pCurveList = this->m_Contours[i];	
//			ASSERT( pCurveList!=NULL );
			
		//	POSITION pos = pCurveList->GetHeadPosition();
			//vector<CCurve*>::iterator it = pCurveList->begin();
			int j = 0;
			
			while (j!=pCurveList->size()) 
			{
				//delete pCurveList->GetNext(pos);
				delete pCurveList->at(j);
				j++;
			}
			delete pCurveList;
		}

		//m_Contours.RemoveAll();
		m_Contours.clear();
	}
}

void CContour::EditContourLevels()
{/*
	CEditContourLevelDlg levelDlg(m_contourValues);


	ASSERT(m_pDataOwner!=NULL);
	levelDlg.SetZMinMax(m_pDataOwner->GetDataInfo().zMin,m_pDataOwner->GetDataInfo().zMax);

	if( levelDlg.DoModal() == IDOK )
	{
		m_contourValues = levelDlg.m_Levels;

		GenerateContours();

	}*/

}

void CContour::GenerateDefaultContourValues()
{//����ȱʡֵ(10�ȷ�)

//	ASSERT(m_pDataOwner!=NULL);
	float zMin = m_pDataOwner->GetDataInfo().zMin;
	float zMax = m_pDataOwner->GetDataInfo().zMax;

	float inc = (zMax-zMin)/29; //10�ȷ�

	float val;

	for(val= zMin; val<=zMax; val+=inc)
	{
		m_contourValues.AddValue(val);
	}
}

void CContour::CreateDrawer()
{
	/*if (m_pContourDrawer == NULL)
	{
		m_pContourDrawer = new CContourDrawer(this);
	}*/
	//CContourObjArray arr = m_pContourDrawer->GetContourSets();
}


/*
void CContour::Draw(CDC* pDC,const CRect& drawRect)
{
	//���Ƶ�ֵ��

    if( m_pContourDrawer == NULL)
	{
		m_pContourDrawer = new CContourDrawer(this);
	}

	ASSERT(m_pContourDrawer!=NULL);

	m_pContourDrawer->DoDraw(pDC,drawRect);

	m_bReGenerated = FALSE;

}
*/
