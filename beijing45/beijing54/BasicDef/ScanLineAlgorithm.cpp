#include <vector>
//#include <FLOAT.H>
#include <string.h>
#include <math.h>
#include <algorithm>
#include "DataTypes.h"
#include "ScanLineAlgorithm.h"

using namespace std;


#define MAX_EDGESET_NUM 500

//���ݸ����������˵㣬��ȡ��
bool GetEdge(const CDoublePoint& p1, const CDoublePoint& p2, Edge& edge)
{
	if(p1.y == p2.y)
	{
		return false;   //��yɨ����ƽ�У����ü���߼���
	}

	if(p1.y < p2.y)
	{
		edge.yMin = p1.y;
		edge.yMax = p2.y;
		edge.x = p1.x;  //��һ�����������
	}
	else
	{
		edge.yMin = p2.y;
		edge.yMax = p1.y;
		edge.x = p2.x;  //��һ�����������		
	}

	edge.dx = (p1.x - p2.x)/(p1.y - p2.y);

	return true;
}
//��������: ���ݸ����Ķ����,���ɱ߼��б�
//�������: ����κ�ET��, yֵ���ֵ
void CreateET(CDoublePoint* pVertex, int nVertexNum, EdgeTable& edgeTable, double dDeltaY)
{
	edgeTable.yStep = dDeltaY;

	//���ݶ���ζ���ĸ�����ȡ�ߵĸ���
	edgeTable.nEdgeNum = nVertexNum;

	//����ߵĴ洢�ռ�
	edgeTable.pEdge = new EdgeNode[edgeTable.nEdgeNum];

	//����
	memset(edgeTable.pEdge, 0, sizeof(EdgeNode)*edgeTable.nEdgeNum);

	//���������Сֵ��step��ȡ�߼�������Ԫ�صĸ���
	edgeTable.nEdgeSetNum = (int)ceil((edgeTable.yMax - edgeTable.yMin)/edgeTable.yStep);

	//���߼���С������һ��������Ŀǰ����Ϊ500��
	if(edgeTable.nEdgeSetNum > MAX_EDGESET_NUM )
	{
		edgeTable.nEdgeSetNum = MAX_EDGESET_NUM;

		edgeTable.yStep = (edgeTable.yMax - edgeTable.yMin) / (edgeTable.nEdgeSetNum - 1);
	}	

	//����洢�ռ�
	edgeTable.pEdgeLink = new EdgeLink[edgeTable.nEdgeSetNum];

	//����
	memset(edgeTable.pEdgeLink, 0, sizeof(EdgeLink)*edgeTable.nEdgeSetNum);

	//Ȼ����Զ���ε�ÿ���,�������Ӧ��edge�ṹ,�����ݸñߵ���Сֵ���뵽�߼���
	Edge edgeTemp;
	for(int i=0; i<nVertexNum; i++)
	{
		//����Ӷ����ȡ�߳ɹ�
		if(GetEdge(pVertex[i%nVertexNum], pVertex[(i+1)%nVertexNum], edgeTemp))
		{
			edgeTable.pEdge[i].edgeValue = edgeTemp;
            edgeTable.pEdge[i].pNextEdge = NULL;

			//����ñ��ڱ༭�����е�����
			int index = -1;
			index = (int)((edgeTemp.yMin - edgeTable.yMin)/edgeTable.yStep);

			//���ñ߲�����Ӧ��������
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

//InsertAEL: ���߼���������i�еı߶����뵽AEL link(���Ա�����)��
void InsertAEL(EdgeTable& edgeTable, EdgeLink& AELLink, int i)
{
	//���ET������i��Ϊ�գ�����ȫ�����뵽ael��
	if(edgeTable.pEdgeLink[i].pHead != NULL)
	{
		EdgeNode* pNodeIterator = edgeTable.pEdgeLink[i].pHead;
		if(AELLink.pHead == NULL)
		{
			//����ǰindex�ı߼���ael��			
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

//ɾ��AEL��yMax�Ѿ�С�ڸ���yMax�ı�
void DeleteAEL(EdgeLink& AELLink, double yMax)
{	
	if(AELLink.pHead != NULL)
	{
		//�ȹ��˵���ȥͷ����
		EdgeNode* pNode = AELLink.pHead->pNextEdge;	
		EdgeNode* pLaseNode = AELLink.pHead;
		
		//�ȴ����м�Ĳ���
		while(pNode != NULL && pNode != AELLink.pTail)  
		{
			if(pNode->edgeValue.yMax <= yMax)
			{
				//ɾ���ýڵ�
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

		//��������β
		if(pNode == AELLink.pTail)
		{
			if(pNode->edgeValue.yMax <= yMax)
			{
				pLaseNode->pNextEdge = pNode->pNextEdge;			
				AELLink.pTail = pLaseNode;

				delete pNode;
			}			
		}

		//�ٴ�������ͷ
		if(AELLink.pHead != NULL && AELLink.pHead->edgeValue.yMax <= yMax )
		{
			//���ֻ��һ�����
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

//��ȡ������AEL�еĽ���ֵ
void GetIntersections( EdgeLink& AELLink, double dYValue, double dDeltaY, std::vector<double>& vIntersectX)
{
	//�����ǰ���Ա�Ϊ��, ������뵱ǰɨ���ߵĽ���
	vIntersectX.clear();
	EdgeNode* pNode = AELLink.pHead;
	double deltaYMin = 0;
	
	while(pNode != NULL)
	{
		if(pNode->edgeValue.yMin <= dYValue) //�ཻ,�󽻵�
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
	//��Ըö���δ����߼�
	EdgeTable edgetable;

	edgetable.xMin = polygonRect.m_Corner1.x;
	edgetable.yMin = polygonRect.m_Corner1.y;
	edgetable.xMax = polygonRect.m_Corner2.x;
	edgetable.yMax = polygonRect.m_Corner2.y;
	CreateET(polygon.m_pPointData, polygon.m_nPointsNum,  edgetable, dyRes);	

	return UpdateResult(edgetable, rect, dxRes, dyRes, ppbTemplate, yHeight, xWidth);
}

//���ݶ���εı߼�������ģ��
bool UpdateResult(EdgeTable& edgetable, CGeoRectangle& rect, double dxRes, double dyRes,
				  bool** ppbTemplate, long yHeight, long xWidth)
{
	//�жϾ��κͽ�������Ƿ��н���,����н���,���ȡ��������
	//���ݽ�������,����ɨ���߷�������ε��ڲ�����
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
		//���ÿ��ɨ����,��������edgetable�е�����
		nIndex = (int)((dYIndex - edgetable.yMin) / edgetable.yStep);
		if(nIndex != nIndexLast)
		{
			//����Ӧ�ı߲���AEL��
			InsertAEL(edgetable, AELLink, nIndex);

			nIndexLast = nIndex;
		}

		//ɾ��ymaxС��dIndex�Ļ��Ա�
		DeleteAEL(AELLink, dYIndex);

		//���㵱ǰ���Ա߼����뵱ǰɨ���ߵĽ���
		vIntersectX.clear();
		GetIntersections(AELLink, dYIndex, dYResolution, vIntersectX);			

		//Ȼ����ݽ���֮��Ĺ�ϵ�����Ӧ��λ��
		if(vIntersectX.size() != 0)
		{
			//����������,
			sort(vIntersectX.begin(), vIntersectX.end() );

			bool bOut = true;
			std::vector<double>::iterator iter = vIntersectX.begin();
			std::vector<double>::iterator iterEnd = vIntersectX.end();

			//���ɨ�����ϵ�ÿ��, ��������
			y = (int)((dYIndex - dLowLeftY + dYResolution/2.0)/dYResolution);
			if(y>=yHeight) continue;
			for(dXIndex=edgetable.xMin; dXIndex<edgetable.xMax; dXIndex+=dXResolution)
			{
				if(dXIndex < *iter)
				{
					if(!bOut) 
					{
						//��ȡ�õ���������
						x = (int)((dXIndex - dLowLeftX + dXResolution/2.0)/dXResolution);
						if(x>=xWidth) continue;

						//����Ϊtrue����ʾ��ģ����
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
						//��ȡ�õ���������
						x = (int)((dXIndex - dLowLeftX + dXResolution/2.0)/dXResolution);
						if(x>=xWidth) continue;

						//����Ϊtrue����ʾ��ģ����
						ppbTemplate[y][x] = true;	
					}
				}							
			}//for(dXIndex=interRect.dLeft; dXIndex<interRect; dXIndex++)
		}//end of vIntersectX.size() != 0					
	}

	//���AEL��Ϊ�գ���Ҫ�ͷ����е�����
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