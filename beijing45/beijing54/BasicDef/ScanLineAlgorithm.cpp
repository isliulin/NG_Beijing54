#include <vector>
//#include <FLOAT.H>
#include <string.h>
#include <math.h>
#include <algorithm>
#include "DataTypes.h"
#include "ScanLineAlgorithm.h"

using namespace std;


#define MAX_EDGESET_NUM 500

//根据给定的两个端点，获取边
bool GetEdge(const CDoublePoint& p1, const CDoublePoint& p2, Edge& edge)
{
	if(p1.y == p2.y)
	{
		return false;   //与y扫描线平行，不用加入边集了
	}

	if(p1.y < p2.y)
	{
		edge.yMin = p1.y;
		edge.yMax = p2.y;
		edge.x = p1.x;  //第一个交点的坐标
	}
	else
	{
		edge.yMin = p2.y;
		edge.yMax = p1.y;
		edge.x = p2.x;  //第一个交点的坐标		
	}

	edge.dx = (p1.x - p2.x)/(p1.y - p2.y);

	return true;
}
//函数功能: 根据给定的多边形,生成边集列表
//输入参数: 多边形和ET表, y值间隔值
void CreateET(CDoublePoint* pVertex, int nVertexNum, EdgeTable& edgeTable, double dDeltaY)
{
	edgeTable.yStep = dDeltaY;

	//根据多边形顶点的个数获取边的个数
	edgeTable.nEdgeNum = nVertexNum;

	//申请边的存储空间
	edgeTable.pEdge = new EdgeNode[edgeTable.nEdgeNum];

	//清零
	memset(edgeTable.pEdge, 0, sizeof(EdgeNode)*edgeTable.nEdgeNum);

	//根据最大最小值和step获取边集数组中元素的个数
	edgeTable.nEdgeSetNum = (int)ceil((edgeTable.yMax - edgeTable.yMin)/edgeTable.yStep);

	//将边集大小控制在一定个数，目前设置为500组
	if(edgeTable.nEdgeSetNum > MAX_EDGESET_NUM )
	{
		edgeTable.nEdgeSetNum = MAX_EDGESET_NUM;

		edgeTable.yStep = (edgeTable.yMax - edgeTable.yMin) / (edgeTable.nEdgeSetNum - 1);
	}	

	//申请存储空间
	edgeTable.pEdgeLink = new EdgeLink[edgeTable.nEdgeSetNum];

	//清零
	memset(edgeTable.pEdgeLink, 0, sizeof(EdgeLink)*edgeTable.nEdgeSetNum);

	//然后针对多边形的每天边,构造其对应的edge结构,并根据该边的最小值插入到边集中
	Edge edgeTemp;
	for(int i=0; i<nVertexNum; i++)
	{
		//如果从顶点获取边成功
		if(GetEdge(pVertex[i%nVertexNum], pVertex[(i+1)%nVertexNum], edgeTemp))
		{
			edgeTable.pEdge[i].edgeValue = edgeTemp;
            edgeTable.pEdge[i].pNextEdge = NULL;

			//计算该边在编辑分组中的索引
			int index = -1;
			index = (int)((edgeTemp.yMin - edgeTable.yMin)/edgeTable.yStep);

			//将该边插入相应的索引中
			EdgeLink& edgelink = edgeTable.pEdgeLink[index];
			if(edgelink.pHead == NULL)
			{
				edgelink.pHead = &(edgeTable.pEdge[i]);
				edgelink.pTail = edgelink.pHead;
				edgelink.pTail->pNextEdge = NULL;
			}
			else
			{
				edgelink.pTail->pNextEdge = &(edgeTable.pEdge[i]);
                edgelink.pTail = edgelink.pTail->pNextEdge;
				edgelink.pTail->pNextEdge = NULL;
			}
		}
	}
}

//InsertAEL: 将边集表中所引i中的边都插入到AEL link(活性边链接)中
void InsertAEL(EdgeTable& edgeTable, EdgeLink& AELLink, int i)
{
	//如果ET的索引i不为空，则将其全部插入到ael中
	if(edgeTable.pEdgeLink[i].pHead != NULL)
	{
		EdgeNode* pNodeIterator = edgeTable.pEdgeLink[i].pHead;
		if(AELLink.pHead == NULL)
		{
			//将当前index的边加入ael中			
			EdgeNode* pNode = new EdgeNode();
			pNode->edgeValue = pNodeIterator->edgeValue;
			pNode->pNextEdge = NULL;
			AELLink.pHead = AELLink.pTail = pNode;
			pNodeIterator = pNodeIterator->pNextEdge;
		}
		
		while(pNodeIterator != NULL)
		{
			EdgeNode* pNode = new EdgeNode();
			pNode->edgeValue = pNodeIterator->edgeValue;
			pNode->pNextEdge = NULL;

			AELLink.pTail->pNextEdge = pNode;
			AELLink.pTail = pNode;

			pNodeIterator = pNodeIterator->pNextEdge;
		}
	}
}

//删除AEL中yMax已经小于给定yMax的边
void DeleteAEL(EdgeLink& AELLink, double yMax)
{	
	if(AELLink.pHead != NULL)
	{
		//先过滤掉出去头部的
		EdgeNode* pNode = AELLink.pHead->pNextEdge;	
		EdgeNode* pLaseNode = AELLink.pHead;
		
		//先处理中间的部分
		while(pNode != NULL && pNode != AELLink.pTail)  
		{
			if(pNode->edgeValue.yMax <= yMax)
			{
				//删除该节点
				pLaseNode->pNextEdge = pNode->pNextEdge;
				delete pNode;

				pNode = pLaseNode->pNextEdge;
			}
			else
			{
				pLaseNode = pNode;
				pNode = pNode->pNextEdge;
			}			
		}

		//处理链表尾
		if(pNode == AELLink.pTail)
		{
			if(pNode->edgeValue.yMax <= yMax)
			{
				pLaseNode->pNextEdge = pNode->pNextEdge;			
				AELLink.pTail = pLaseNode;

				delete pNode;
			}			
		}

		//再处理链表头
		if(AELLink.pHead != NULL && AELLink.pHead->edgeValue.yMax <= yMax )
		{
			//如果只有一个结点
			if(AELLink.pHead == AELLink.pTail)
			{
				delete AELLink.pHead;
				AELLink.pHead = AELLink.pTail = NULL;
			}
			else
			{
				pNode = AELLink.pHead;
				AELLink.pHead = AELLink.pHead->pNextEdge;
				delete pNode;
			}
		}		
	}

}

//获取并更新AEL中的交点值
void GetIntersections( EdgeLink& AELLink, double dYValue, double dDeltaY, std::vector<double>& vIntersectX)
{
	//如果当前活性表不为空, 则更新与当前扫描线的交点
	vIntersectX.clear();
	EdgeNode* pNode = AELLink.pHead;
	double deltaYMin = 0;
	
	while(pNode != NULL)
	{
		if(pNode->edgeValue.yMin <= dYValue) //相交,求交点
		{
			deltaYMin = dYValue - pNode->edgeValue.yMin < dDeltaY? dYValue - pNode->edgeValue.yMin:dDeltaY;			
			pNode->edgeValue.x = pNode->edgeValue.x + pNode->edgeValue.dx * deltaYMin;	
			vIntersectX.push_back(pNode->edgeValue.x);
		}

		pNode = pNode->pNextEdge;
	}
}

bool GenerateTemplate(CGeoPolygon& polygon, CGeoRectangle& polygonRect, CGeoRectangle& rect, double dxRes, double dyRes,
					 bool** ppbTemplate, long yHeight, long xWidth)
{
	//针对该多边形创建边集
	EdgeTable edgetable;

	edgetable.xMin = polygonRect.m_Corner1.x;
	edgetable.yMin = polygonRect.m_Corner1.y;
	edgetable.xMax = polygonRect.m_Corner2.x;
	edgetable.yMax = polygonRect.m_Corner2.y;
	CreateET(polygon.m_pPointData, polygon.m_nPointsNum,  edgetable, dyRes);	

	return UpdateResult(edgetable, rect, dxRes, dyRes, ppbTemplate, yHeight, xWidth);
}

//根据多边形的边集，更新模板
bool UpdateResult(EdgeTable& edgetable, CGeoRectangle& rect, double dxRes, double dyRes,
				  bool** ppbTemplate, long yHeight, long xWidth)
{
	//判断矩形和结果矩形是否有交集,如果有交集,则获取交集矩形
	//根据交集矩形,利用扫描线法填充多边形的内部区域
	double dYIndex = edgetable.yMin;
	double dXIndex = edgetable.xMin;
	int nIndex = -1;
	int nIndexLast = -1;

	std::vector<double> vIntersectX;
	double dYResolution = dyRes;
	double dXResolution = dxRes;
	double dLowLeftX = rect.m_Corner1.x;
	double dLowLeftY = rect.m_Corner1.y;
	long nWidth = xWidth;
	long nHeight = yHeight;

	int x = 0;
	int y = 0;

	short nValue = 0;

	EdgeLink AELLink;
	AELLink.pHead = AELLink.pTail = NULL;

	for( ;dYIndex<edgetable.yMax; dYIndex+= dYResolution)
	{
		//针对每条扫描线,计算其在edgetable中的索引
		nIndex = (int)((dYIndex - edgetable.yMin) / edgetable.yStep);
		if(nIndex != nIndexLast)
		{
			//将相应的边插入AEL中
			InsertAEL(edgetable, AELLink, nIndex);

			nIndexLast = nIndex;
		}

		//删除ymax小于dIndex的活性边
		DeleteAEL(AELLink, dYIndex);

		//计算当前活性边集合与当前扫描线的交点
		vIntersectX.clear();
		GetIntersections(AELLink, dYIndex, dYResolution, vIntersectX);			

		//然后根据交点之间的关系填充相应的位置
		if(vIntersectX.size() != 0)
		{
			//将交点排序,
			sort(vIntersectX.begin(), vIntersectX.end() );

			bool bOut = true;
			std::vector<double>::iterator iter = vIntersectX.begin();
			std::vector<double>::iterator iterEnd = vIntersectX.end();

			//针对扫描线上的每点, 四舍五入
			y = (int)((dYIndex - dLowLeftY + dYResolution/2.0)/dYResolution);
			if(y>=yHeight) continue;
			for(dXIndex=edgetable.xMin; dXIndex<edgetable.xMax; dXIndex+=dXResolution)
			{
				if(dXIndex < *iter)
				{
					if(!bOut) 
					{
						//获取该点的相对坐标
						x = (int)((dXIndex - dLowLeftX + dXResolution/2.0)/dXResolution);
						if(x>=xWidth) continue;

						//设置为true，表示在模板内
						ppbTemplate[y][x] = true;							
					}
				}
				else
				{
					bOut = !bOut;
					iter++;
					if(iter == iterEnd)
					{
						break;
					}
					if(!bOut) 
					{
						//获取该点的相对坐标
						x = (int)((dXIndex - dLowLeftX + dXResolution/2.0)/dXResolution);
						if(x>=xWidth) continue;

						//设置为true，表示在模板内
						ppbTemplate[y][x] = true;	
					}
				}							
			}//for(dXIndex=interRect.dLeft; dXIndex<interRect; dXIndex++)
		}//end of vIntersectX.size() != 0					
	}

	//如果AEL不为空，需要释放其中的数据
	if(AELLink.pHead != NULL)
	{
		EdgeNode* pNode = NULL;
		while(AELLink.pHead != NULL)
		{
			pNode = AELLink.pHead;
			AELLink.pHead = AELLink.pHead->pNextEdge;
			delete pNode;
		}
		AELLink.pHead = AELLink.pTail = NULL;
	}
	return true;
}