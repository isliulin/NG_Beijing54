#ifndef __C_ScanLine_Algorithm_h
#define __C_ScanLine_Algorithm_h

#include <vector>
#include "GeoShape.h"

//定义一个边
struct Edge
{
       double    x;       //交点的x坐标
       double    dx;
       double    yMax;    //边的最大y值
	   double    yMin;    //该边的最小y值     
};

typedef Edge* PEdge;

struct EdgeNode
{
	Edge edgeValue;

	EdgeNode* pNextEdge;
};

struct EdgeLink
{
	EdgeNode* pHead; //头指针
	EdgeNode* pTail; //尾指针
};

//定义边的表
struct EdgeTable
{
	double yMax;   //所有边中的最大y值
	double yMin;   //所有边中的最小y值

	double xMax;   //所有边中的最大x值
	double xMin;   //所有边中的最小x值

	double yStep;  //边集列表的step

	int nEdgeNum;  //边的个数

	//边集
	EdgeNode* pEdge;

	int nEdgeSetNum;

    EdgeLink* pEdgeLink;  //边集数组

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