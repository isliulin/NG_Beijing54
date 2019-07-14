//#include "StdAfx.h"
#include "ContourGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
ContourGenerator::ContourGenerator(void)
{
	m_pContour = NULL;
}

ContourGenerator::~ContourGenerator(void)
{
	if( m_pContour!=NULL )
		delete m_pContour;
}

bool ContourGenerator::GenerateContour(const char* resultpath)
{
	if (!m_GeoData.ReadData(resultpath))
	{
		return false;
	}
	if( m_pContour!=NULL)
	{
		delete m_pContour;
		m_pContour = NULL; 
	}

	if(m_pContour==NULL)
	{
		m_pContour = new CContour;
		m_pContour->SetDataOwner(&m_GeoData);
	}
	m_pContour->SetContourValues(m_ContourValue);
	m_pContour->GenerateContours();
	if (m_pContour!= NULL&&m_pContour->IsHavingContours())
	{
		return true;
	}

	return false;
}

bool ContourGenerator::GenerateContour( void * pData,bool bRasterData )
{
	if(pData==NULL)
		return false;
	if(!bRasterData || !m_GeoData.SetRasterData(pData))
		return false;
	if( m_pContour!=NULL)
	{
		delete m_pContour;
		m_pContour = NULL; 
	}

	if(m_pContour==NULL)
	{
		m_pContour = new CContour;
		m_pContour->SetDataOwner(&m_GeoData);
	}
	m_pContour->SetContourValues(m_ContourValue);
	m_pContour->GenerateContours();
	if (m_pContour!= NULL&&m_pContour->IsHavingContours())
	{
		return true;
	}

	return false;
}

bool ContourGenerator::WriteContours(const char* outputPath )
{
	FILE* pFile = fopen(outputPath,"wb");
	if (pFile == NULL)
	{
		return false;
	}

	//start Write Binary
	CContourArray arr = m_pContour->GetContours();
	float fValue;
	//CCurveList* pCurveList;
	int contoursize = arr.size();
	fwrite(&contoursize,sizeof(int),1,pFile);
	for (int i=0;i<contoursize;i++)
	{
		fValue = m_pContour->GetValue(i);//��ֵ��ֵ
		CCurveList* pCurveList = arr[i];//���е�ֵ������
		int CurveListSize = pCurveList->size();
		vector<CCurve*>::iterator iter = pCurveList->begin();
		CCurve* pCtrLine = NULL;	
		fwrite(&fValue,sizeof(fValue),1,pFile);//д���ֵ��ֵ
		fwrite(&CurveListSize,sizeof(CurveListSize),1,pFile);//д���ֵ�߸���
		while(iter!=pCurveList->end())
		{
			pCtrLine = *iter;
			int pointcount = pCtrLine->size();
			fwrite(&pointcount,sizeof(int),1,pFile);//д�µ�ĸ���
			for (int j=0;j<pointcount;j++)
			{
				CGeoPoint onepoint = pCtrLine->at(j);
				fwrite(&onepoint,sizeof(CGeoPoint),1,pFile);
			}
			
			/*fwrite(&(pCurveList->at(0)),pointcount*sizeof(CGeoPoint),pointcount,pFile);*/
			iter++;
		}
	}
	fclose(pFile);
	return true;
	//delete pFile;
}

bool ContourGenerator::ReadContours(const char* inPath )
{
	FILE* pFile = fopen(inPath,"rb");
	if (pFile == NULL)
	{
		return false;
	}

	if( m_pContour!=NULL)
	{
		delete m_pContour;
		m_pContour = NULL; 
	}

	if(m_pContour==NULL)
	{
		m_pContour = new CContour;
		//m_pContour->SetDataOwner(&m_GeoData);
	}

	int contourCount;//��ֵ��ֵ
	fread(&contourCount,sizeof(int),1,pFile);
	for (int i=0;i<contourCount;i++)
	{
		CCurveList* curveList = new CCurveList;
		float fValue = -99999;//��ֵ��ֵ
		fread(&fValue,sizeof(fValue),1,pFile);
		m_pContour->AddContourValue(fValue);//����value
		int NContourNum = 0;//��ֵ������
		fread(&NContourNum,sizeof(int),1,pFile);
		for (int j=0;j<NContourNum;j++)
		{
			CCurve* curve = new CCurve;
			int pointCount = 0;//��ĸ���
			fread(&pointCount,sizeof(int),1,pFile);
			for (int k=0;k<pointCount;k++)
			{
				CGeoPoint onePoint;
				fread(&onePoint,sizeof(CGeoPoint),1,pFile);
				curve->push_back(onePoint);
			}
			curveList->push_back(curve);
		}
		m_pContour->GetContours().push_back(curveList);
	}
	fclose(pFile);
	return true;
}

CCurveList* ContourGenerator::GetContoursByLevel( float level )
{
	int ContourCount = m_pContour->GetContours().size();
	for (int i=0;i<ContourCount;i++)
	{
		if (level == m_pContour->GetValue(i))
		{
			return m_pContour->GetContours().at(i);
		}
	}
	return NULL;
}
