// Contour.h: interface for the CContour class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTOUR_H__7ED2ACCB_E944_4543_AF11_2762F561CF69__INCLUDED_)
#define AFX_CONTOUR_H__7ED2ACCB_E944_4543_AF11_2762F561CF69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ContourValues.h"
#include "GeoStruct.h"
#include "GeoData.h"
#include <vector>
#include <list>
using namespace std;


/*===================��ֵ����=============================*/
//                   CContour
//�������ڱ����ֵ������,�����ֵ��ֵ����ֵ��׷�٣���ֵ�߻��ƣ��ȵ�....
//
//����ͱ༭��ֵ��ֵʱ������CContourValues�������
//�����ɵ�ֵ��ʱ������CContourTracer��ֵ��׷���������׷��
//�ڵ�ֵ�߻���ʱ������CContourDrawer������������
//
/*==============================================================*/


//typedef CArray<CGeoPoint,CGeoPoint&> CCurve; //һ����ֵ������
typedef vector<CGeoPoint> CCurve;
//typedef CTypedPtrList<CPtrList, CCurve*> CCurveList; //��ֵ����������(����ĳֵ�ĵ�ֵ�߲�����һ��)
typedef vector<CCurve*> CCurveList;
//typedef CTypedPtrArray<CPtrArray,CCurveList*> CContourArray; 
typedef vector<CCurveList*> CContourArray;

//#include "ContourDrawer.h"

class CContour  
{
public:

	CContour(CGeoData* pOwner=NULL);
	~CContour();

	//----��ֵ��ֵ����ز���-------------
	int GetNumberOfValues();
	void AddContourValue(float newVal);
	void DeleteContourValue(float oldVal);
	void ReplaceContourValue(float oldVal, float newVal);
	void GenerateContourValues(int numContours, float valStart, float valEnd);
	CValueList& GetValueList();
	float GetValue(int i);
	void SetValueList(CValueList& list);
	void GenerateDefaultContourValues();
	void EditContourLevels(); //�༭��ֵ��
	

	//----------------------------
	void GenerateContours();
	void RemoveAllContours();

	//----------�����������---------
	void SetDataOwner(CGeoData* pOwner)
	{
		//ASSERT(pOwner!=NULL); 
		
		m_pDataOwner = pOwner;
	}
	CGeoData* GetDataOwner()
	{
		return m_pDataOwner;
	}

	//-----׷�ٽ��---------
	CContourArray& GetContours()
	{
		return m_Contours;
	}
	CContourValues& GetContourValues()
	{
		return m_contourValues;
	}
	void SetContourValues(CContourValues val)
	{
		this->m_contourValues = val;
	}
	//-----�������---------------
	//void Draw(CDC* pDC,const CRect& drawRect);
	bool IsHavingContours(){ return m_Contours.size()>0;}
 //   void ModifyColorTable(){m_pContourDrawer->ModifyColorTable();}
	bool IsGeneratingAgain(){return m_bReGenerated;}
	void CreateDrawer();


public:
	CContourValues m_contourValues; //�����ֵ��ֵ
	CContourArray    m_Contours;    //��ֵ��׷�ٽ�����ڴ���
	//CContourTracer*  m_pContourTracer;
//	CContourDrawer*  m_pContourDrawer;
    CGeoData*       m_pDataOwner;

	bool m_bReGenerated; //ָʾ�������Ƿ���Ҫ��������Contour���ƶ���ı�־


private:
	CContour(const CContour& rhs); //not implimented
	CContour& operator=(const CContour& rhs);//not implimented
};

inline int CContour::GetNumberOfValues()
{
	return m_contourValues.GetNumberOfValues();
}

inline void CContour::AddContourValue(float newVal)
{
	m_contourValues.AddValue(newVal);
}

inline void CContour::DeleteContourValue(float oldVal)
{
	m_contourValues.DeleteValue(oldVal);
}

inline void CContour::ReplaceContourValue(float oldVal, float newVal)
{
	m_contourValues.ReplaceValue(oldVal,newVal);
}

inline void CContour::GenerateContourValues(int numContours, float valStart, float valEnd)
{
	m_contourValues.GenerateValues(numContours,valStart,valEnd);
}

inline CValueList& CContour::GetValueList()
{ 
	return m_contourValues.GetValueList(); 
}

inline float CContour::GetValue(int i)
{
	return m_contourValues.GetValue(i);
}

inline void CContour::SetValueList(CValueList& _list)
{
	m_contourValues.RemoveAllValues();

/*
	POSITION pos = list.GetHeadPosition();
	while(pos!=NULL)
	{
		m_contourValues.AddValue(list.GetNext(pos));
	}*/
	list<float>::iterator iter;
	for (iter=_list.begin();iter!=_list.end();iter++)
	{
		m_contourValues.AddValue(*iter);
	}

}


#endif // !defined(AFX_CONTOUR_H__7ED2ACCB_E944_4543_AF11_2762F561CF69__INCLUDED_)
