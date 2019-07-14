#ifndef __C_ScanLine_Algorithm_h
#define __C_ScanLine_Algorithm_h

#include <vector>
#include "GeoShape.h"

//����һ����
struct Edge
{
       double    x;       //�����x����
       double    dx;
       double    yMax;    //�ߵ����yֵ
	   double    yMin;    //�ñߵ���Сyֵ     
};

typedef Edge* PEdge;

struct EdgeNode
{
	Edge edgeValue;

	EdgeNode* pNextEdge;
};

struct EdgeLink
{
	EdgeNode* pHead; //ͷָ��
	EdgeNode* pTail; //βָ��
};

//����ߵı�
struct EdgeTable
{
	double yMax;   //���б��е����yֵ
	double yMin;   //���б��е���Сyֵ

	double xMax;   //���б��е����xֵ
	double xMin;   //���б��е���Сxֵ

	double yStep;  //�߼��б��step

	int nEdgeNum;  //�ߵĸ���

	//�߼�
	EdgeNode* pEdge;

	int nEdgeSetNum;

    EdgeLink* pEdgeLink;  //�߼�����

	EdgeTable()
	{
		yMin = 0.0;
		yMax = 0.0;

		yStep = 0.0;
		nEdgeNum = 0;
		nEdgeSetNum = 0;
		pEdge = NULL;
		pEdgeLink = NULL;
	}

	~EdgeTable()
	{
		if(pEdgeLink != NULL)
		{
			delete[]pEdgeLink;
			pEdgeLink = NULL;
		}
		if(pEdge != NULL)
		{
			delete []pEdge;
			pEdge = NULL;
		}
	}

};


void CreateET(CDoublePoint* pVertex, int nVertexNum, EdgeTable& edgeTable, double dDeltaY);


void InsertAEL(EdgeTable& edgeTable, EdgeLink& AELLink, int i);

void GetIntersections( EdgeLink& AELLink, double dYValue, double dDeltaY, std::vector<double>& vIntersectX);

void DeleteAEL(EdgeLink& AELLink, double yMax);

bool UpdateResult(EdgeTable& edgetable, CGeoRectangle& rect, double dxRes, double dyRes,
				  bool** ppbTemplate, long yHeight, long xWidth);

bool GenerateTemplate(CGeoPolygon& polygon, CGeoRectangle& polygonRect, CGeoRectangle& rect, double dxRes, double dyRes,
					 bool** ppbTemplate, long yHeight, long xWidth);



#endif