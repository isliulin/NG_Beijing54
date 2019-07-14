#include "NGNaturalNeigbours.h"
#include <algorithm>
#include <assert.h>
#include <float.h>
#include "../KoordTrans/KoordTrans.h"
#include "ErrorCode.h"
#include "NGMD5Tool.h"

bool CMPNGVector(NGPlaneVector p1,NGPlaneVector p2){
	return p1.angle < p2.angle;
}


CNGNaturalNeigbours::CNGNaturalNeigbours(void)
{
	m_polygons = NULL;
	m_pointStatus = NULL;
	m_BinResult = NULL;
	m_Resultion = 0 ;
	m_old_md5 = "";
}

CNGNaturalNeigbours::~CNGNaturalNeigbours(void)
{
	DestoryMemory();
}


bool CNGNaturalNeigbours::GetVoronoi(double minDist /*= 0 */)
{
	VoronoiDiagramGenerator vdg;
	if ( !vdg.generateVoronoi(mSites,0,m_width,0,m_height,minDist) )
	{
		return false;
	}

	NG_DELETE_ARRAY(m_polygons);
	m_polygons = new(std::nothrow) NGPolygon[mSiteCount];//̩ɭ����κ���ɢ��һһ��Ӧ
	if (NULL == m_polygons )
	{
		return false;
	}
	vdg.resetIterator();
	NGEdge edge;
	while(vdg.GetNext(edge.begin,edge.end,edge.leftIndex,edge.rightIndex)){

		edge.area = Distance(edge.begin ,edge.end) *Distance(mSites[edge.leftIndex] , mSites[edge.rightIndex]) /4;
		m_polygons[edge.leftIndex].edges.push_back(edge);

		m_polygons[edge.rightIndex].edges.push_back(edge);

	}
	return GeneratorEdges();//�Զ���εı߽���������β���������������Ķ����
}

bool CNGNaturalNeigbours::GeneratorEdges()
{
	for ( int i = 0 ; i < mSiteCount ; i ++ )
	{
		vector<NGEdge> tempEdges;
		tempEdges.swap(m_polygons[i].edges);
		vector<NGEdge> bedges;
		DeleteSameEdge(tempEdges,bedges);
		if (tempEdges.size() == 0 )
		{
			continue;//̩ɭ�����������һ����
		}
		bool hasNext = false;
		for ( int j = 1 ; j < tempEdges.size() ; j ++)
		{
			//�жϵ�һ���߶ν�β�Ƿ���������߶�����
			if (tempEdges[0].end == tempEdges[j].begin || tempEdges[0].end == tempEdges[j].end )
			{
				hasNext = true;
				break;
			}
		}
		if (!hasNext)
		{
			SwapBE(tempEdges[0]);//���û����������λ����
		}
		vector<NGEdge> edges;
		edges.push_back(tempEdges[0]);
		tempEdges.erase(tempEdges.begin());
		while(tempEdges.size() > 0)
		{
			int size = tempEdges.size();
			for ( int j = 0 ; j< tempEdges.size() ; j ++)
			{
				//���ĳ���ߵĿ�ʼ���߽�β����֪����εıߵĽ�β�غ�
				if (tempEdges[j].begin == edges[edges.size()-1].end)
				{
					edges.push_back(tempEdges[j]);
					tempEdges.erase(tempEdges.begin()+j);
				}else if (tempEdges[j].end == edges[edges.size()-1].end)
				{
					SwapBE(tempEdges[j]);
					edges.push_back(tempEdges[j]);
					tempEdges.erase(tempEdges.begin()+j);
				}
			}
			//ѭ������û��ɾ��һ�����ݣ�˵�������������ʱ�������ε�ȱ�ڴ�
			if (size == tempEdges.size())
			{
				//����ȱ�ڴ��ıߣ�������£������һ�����ڱ߿򴦣���һ���ߺ���߿��غ�
				NGEdge extra = GetExtraEdge(edges[edges.size()-1].end,edges[0].begin,tempEdges);
				extra.area = CalTriArea(extra.begin,extra.end,mSites[i]);
				extra.leftIndex = extra.rightIndex = i;
				edges.push_back(extra);
				//polygons[i].isBound = true;
			}
		}
		if ((edges[0]).begin !=edges[edges.size()-1].end)
		{
			//����������β�������������һ��ȱ�ڴ��ı�
			NGEdge edge;
			edge.begin = edges[edges.size()-1].end;
			edge.end = edges[0].begin;
			edge.area = CalTriArea(edge.begin,edge.end,mSites[i]);
			edge.leftIndex = edge.rightIndex = i;
			edges.push_back(edge);
			//polygons[i].isBound = true;
		}

		for ( int j = 0 ; j < edges.size() ; j ++)
		{
			int m = (j+1)%edges.size();
			for (int k = 0 ; k < bedges.size() ; )
			{
				if (PointInSeg(bedges[k].begin,edges[j]))
				{
					if (edges[j].end == bedges[k].begin)
					{
						edges.insert(edges.begin() +j +1,bedges[k]);
						bedges.erase(bedges.begin() +k);
					}else if (edges[j].begin == bedges[k].begin)
					{
						edges.insert(edges.begin() +j,bedges[k]);
						bedges.erase(bedges.begin() +k);
					}
				}else{
					k++;
				}
			}
		}
		//�����Ӧ����ɢ�㲻�ڶ�����ڣ���ô��Ӷ���ıߣ�����ɢ�������ȥ�������ֻ���ĸ��������ɢ��ʱ�����
		if ( !PtInPolygon(edges,mSites[i]))
		{
			//������ڵ���ɢ�㲻�ڶ������
			for (int j = 0 ; j < edges.size() ; j ++)
			{
				if (edges[j].leftIndex == i && edges[j].rightIndex == i )
				{
					NGEdge e1,e2;
					e1.begin = edges[j].begin;
					e1.end = mSites[i];
					e1.area = 0 ;
					e1.leftIndex = i ;
					e1.rightIndex = i ; 
					e2.leftIndex = i ;
					e2.rightIndex = i ;
					e2.begin = mSites[i];
					e2.end = edges[j].end;
					e2.area = 0 ;
					edges[j] = e1;
					edges.insert(edges.begin() + j + 1 ,e2);
					break;
				}
			}
		}
		m_polygons[i].edges.swap(edges);
		for ( int k = 0 ; k < m_polygons[i].edges.size() ; k++)
		{
			m_polygons[i].area += m_polygons[i].edges[k].area;//�������ε����
		}
	}
	return true;
}

void CNGNaturalNeigbours::SwapBE(NGEdge& edge)
{
	NGPOINT temp = edge.begin;
	edge.begin = edge.end;
	edge.end = temp;
}

NGEdge CNGNaturalNeigbours::GetExtraEdge(NGPOINT& begin,NGPOINT& polyBegin,vector<NGEdge>& edges)
{
	NGEdge extra;
	extra.begin = begin;
	extra.end = begin;
	vector<NGPOINT> points;
	points.push_back(polyBegin);
	for ( int i = 0 ; i < edges.size() ; i ++)
	{
		points.push_back(edges[i].begin);
		points.push_back(edges[i].end);
	}
	for ( int i = 0 ; i < points.size() ; i ++)
	{
		if (points[i] == begin)
		{
			continue;
		}
		//Ҫ�½�һ���ߵ�ʱ��ֻ�����ڱ߽���
		if (fabs(points[i].x)< 0.000001  || fabs(points[i].x - m_width) < 0.000001 || fabs(points[i].y)< 0.000001   || fabs(points[i].y - m_height)<0.000001)
		{
			extra.end = points[i];
			break;
		}
	}
	return extra;
}

void CNGNaturalNeigbours::DeleteSameEdge(vector<NGEdge>& edges,vector<NGEdge>& bedges)
{
	for ( int j = 0 ; j < edges.size() ; )
	{
		//ɾ��һЩ�߶�����Ϊ������
		if (edges[j].begin == edges[j].end)
		{
			bedges.push_back(edges[j]);
			edges.erase(edges.begin() + j);
		}else{
			j ++;
		}
	}
	for ( int  j = 0 ; j < edges.size() ; )
	{
		//ɾ���ظ����߶Σ����ߵ���ɢ����ͬ
		bool isRepeat =false;
		for ( int k = j+1 ; k < edges.size(); k ++)
		{
			if (edges[j].leftIndex == edges[k].leftIndex &&edges[j].rightIndex == edges[k].rightIndex ||
				edges[j].leftIndex == edges[k].rightIndex &&edges[j].rightIndex == edges[k].leftIndex )
			{
				edges.erase(edges.begin() + j);
				isRepeat = true;
			}
		}
		if (!isRepeat)
		{
			j++;
		}
	}
}

float CNGNaturalNeigbours::CalTriArea(const NGPOINT& p1,const NGPOINT& p2,const NGPOINT& p3)
{
	float a = Distance(p1,p2);
	float b = Distance(p1,p3);
	float c = Distance(p2,p3);
	float p = (a+b+c)/2;
	return sqrt(p*(p-a)*(p-b)*(p-c));

}

//�������ֵ���Ӧ��̩ɭ�������ԭ����̩ɭ��������Ȩ��,��PX�ڵ�index��̩ɭ�������
void CNGNaturalNeigbours::DoPXInterpolation(NGPOINT PX,int index,std::map<int,float>& weights)
{

	vector<NGEdge>& edges=m_polygons[index].edges;
	NGLine perline = GetPerLine(PX,mSites[index]);//�ȼ������ֵ������ڵ�̩ɭ����ε���ɢ����д���
	int size = edges.size();
	vector<NGPOINT> points;//�����д��ߺ�̩ɭ����εĽ���
	vector<int> allIndex;//���潻�����ڵı�
	vector<int> nextSites;//���潻�����ڵıߵ�����һ����ɢ��
	points.reserve(10);
	allIndex.reserve(2);
	nextSites.reserve(2);
	weights.clear();
	for (int i = 0 ; i < size ; i ++ )
	{
		NGPOINT interPoint;
		if (GetSegIntersect(edges[i],perline,interPoint))
		{
			points.push_back(interPoint);
			int aIndex = edges[i].leftIndex == index? edges[i].rightIndex : edges[i].leftIndex;
			if (aIndex != index)
			{
				nextSites.push_back(aIndex);
			}
			allIndex.push_back(i);
		}
	}
	CalWeights(PX,points,allIndex,index,weights);
	int cIndex = index;
	int dIndex = index;
	int aIndex , bIndex;
	bool hasLast = false;
	bool hasNext = false;
	if (nextSites.size() == 0 )
	{
		return;//���û������ֱ�ӷ���
	}else if (nextSites.size() == 1)
	{
		aIndex = nextSites[0];
		if (aIndex == index)
		{
			return;//���ֻ��һ��������������������
		}else{
			hasNext = true;
		}
	}else{
		aIndex = nextSites[0];
		bIndex = nextSites[1];
		if (aIndex == index && bIndex == index)
		{
			return;//����ڱ߽���
		}else if (aIndex == index)//���ֻ��һ���������䱾����ȡ����һ������
		{
			hasNext = true;
			aIndex = bIndex;
		}else if (bIndex == index)
		{
			hasNext = true;
		}
	}
	//�����һ�μ����ĳ�������Ѿ�����߽磨ֻ�ڱ����̩ɭ������ڱ߽��ϵ�ʱ��Ż���ִ������
	if (!hasNext)
	{
		while(true){
			//����PX��aIndex,bIndex������Ȩ�أ���������һ����������
			int nextAIndex = CalWeightofPXInIndex(PX,aIndex,cIndex,weights);
			int nextBIndex = CalWeightofPXInIndex(PX,bIndex,dIndex,weights);
			if (weights.find(nextBIndex) != weights.end() && weights.find(nextAIndex) != weights.end())
			{
				break;//����õ�����С���Ѿ������
			}
			if (weights.find(nextAIndex) != weights.end())
			{
				cIndex = bIndex;
				aIndex = nextBIndex;
				hasNext = true;
				break;
			}
			if (weights.find(nextBIndex) != weights.end())
			{
				cIndex = aIndex;
				aIndex = nextAIndex;
				hasNext = true;
				break;
			}
			if (nextBIndex == -1 && nextAIndex == -1)
			{
				//����õ�����������Ϊ-1��������ǣ�PX��aIndex����bIndex���д��ߺͶ�Ӧ��̩ɭ�����ֻ��һ������
				break;
			}
			if (nextAIndex == -1)
			{
				cIndex = bIndex;
				aIndex = nextBIndex;
				hasNext = true;
				break;
			}
			if (nextBIndex == -1)
			{
				cIndex = aIndex;
				aIndex = nextAIndex;
				hasNext = true;
				break;
			}
			if (nextBIndex == nextAIndex)
			{
				hasLast = true;
				cIndex = aIndex;
				aIndex = nextAIndex;
				break;
			}
			if (nextAIndex == bIndex && nextBIndex == aIndex)
			{
				//���������PX������������������������㵽�����õ���һ���������෴�ķ����ϵ����������һ������
				break;
			}
			if (nextBIndex == bIndex &&nextAIndex == aIndex)
			{
				break;//����������򶼼��㵽�߽���
			}
			if (nextAIndex == aIndex)
			{
				//���ĳ��������㵽�߽��ϣ�������һ�����㷽��û�е���߽�
				hasNext = true;
				cIndex = bIndex;
				aIndex = nextBIndex;
				break;
			}
			if (nextBIndex == bIndex)
			{
				//���ĳ��������㵽�߽��ϣ�������һ�����㷽��û�е���߽�
				hasNext = true;
				cIndex = aIndex;
				aIndex = nextAIndex;
				break;
			}
			//�������㷽�򶼻�������
			cIndex = aIndex;
			dIndex = bIndex;
			aIndex = nextAIndex;
			bIndex = nextBIndex;
		}
		if (hasLast)
		{
			//���������PX��ż��������������PX���ڵ�̩ɭ������⣬����������㵽��ͬ������
			CalWeightofPXInIndex(PX,aIndex,index,weights);
		}
	}	
	while (hasNext)
	{
		//�����������һ��������㵽�˱߽��ϣ�����һ������û�У������������ֱ���÷���Ҳ����߽�
		int nextSite = CalWeightofPXInIndex(PX,aIndex,cIndex,weights);
		//�������õ�����һ������û���ˣ������ڱ߽��ϣ������Ѿ��������
		hasNext = nextSite != -1 && nextSite != aIndex && weights.find(nextSite) == weights.end();
		cIndex = aIndex;
		aIndex = nextSite;
	}
}

//�������㹹�ɵ������ε����ԲԲ��
bool CNGNaturalNeigbours::CalTriMCC(NGPOINT p1,NGPOINT p2,NGPOINT p3,NGPOINT& center)
{
	double a = (p1.x-p2.x)*(p2.y-p3.y);
	double b = (p1.y-p2.y)*(p2.x-p3.x);
	if (fabs(a-b)<0.0001)
	{
		return false;//���㹲�ߣ�û�����Բ
	}
	double u1 = (p2.x*p2.x - p1.x*p1.x + p2.y*p2.y - p1.y*p1.y)/2;
	double u2 = (p3.x*p3.x - p1.x*p1.x + p3.y*p3.y - p1.y*p1.y)/2;
	double d11 = p2.x - p1.x;
	double d12 = p2.y - p1.y;
	double d21 = p3.x - p1.x;
	double d22 = p3.y - p1.y;
	center.x = (u1*d22 - u2*d12)/(d11*d22 - d21*d12);
	center.y = (u2*d11 - u1*d21)/(d11*d22 - d21*d12);
	return true;
}

//��ȡ������д���
NGLine CNGNaturalNeigbours::GetPerLine(NGPOINT p1, NGPOINT p2)
{
	NGLine result;
	result.a = 2*(p2.x - p1.x);
	result.b = 2*(p2.y - p1.y);
	result.c = p1.x*p1.x + p1.y*p1.y - p2.x*p2.x - p2.y*p2.y;
	return result;
}

//�ж�ֱ���Ƿ����߶���
bool CNGNaturalNeigbours::PointInSeg(const NGPOINT& point,int leftIndex,int rightIndex)
{
	for (int i = 0 ; i < m_polygons[leftIndex].edges.size() ; i ++)
	{
		//��ȡ����һ����ɢ�������
		int index = m_polygons[leftIndex].edges[i].leftIndex == leftIndex? m_polygons[leftIndex].edges[i].rightIndex :m_polygons[leftIndex].edges[i].leftIndex;
		if (index == rightIndex)
		{
			return PointInSeg(point,m_polygons[leftIndex].edges[i]);
		}
	}
	return false;
}

bool CNGNaturalNeigbours::PointInSeg(const NGPOINT& point,const NGEdge& edge)
{
	double deltaX1 = point.x - edge.begin.x;
	double deltaX2 = point.x - edge.end.x;
	double deltaY1 = point.y - edge.begin.y;
	double deltaY2 = point.y - edge.end.y;
	deltaX1 = fabs(deltaX1) < 0.00001 ? 0 :deltaX1;
	deltaX2 = fabs(deltaX2) < 0.00001 ? 0 :deltaX2;
	deltaY1 = fabs(deltaY1) < 0.00001 ? 0 :deltaY1;
	deltaY2 = fabs(deltaY2) < 0.00001 ? 0 :deltaY2;
	if (fabs(deltaX1 * deltaY2 - deltaX2 * deltaY1) < 0.0001 && deltaX1 * deltaX2 <= 0 && deltaY1 * deltaY2 <=0)
	{
		return true;
	}
	return false;
}

int CNGNaturalNeigbours::GetSameNeigbours(int aIndex,int bIndex,int index )
{
	for (int i = 0 ; i < m_polygons[aIndex].edges.size() ; i ++)
	{
		int cIndex = m_polygons[aIndex].edges[i].leftIndex == aIndex ? m_polygons[aIndex].edges[i].rightIndex : m_polygons[aIndex].edges[i].leftIndex;
		if (cIndex == aIndex)
		{
			continue;
		}
		for (int j = 0 ; j < m_polygons[bIndex].edges.size() ; j ++)
		{
			int dIndex =  m_polygons[bIndex].edges[j].leftIndex == bIndex ? m_polygons[bIndex].edges[j].rightIndex : m_polygons[bIndex].edges[j].leftIndex;
			if (dIndex == bIndex)
			{
				continue;
			}
			if (dIndex ==  cIndex && dIndex != index )
			{
				return dIndex;
			}
		}
	}
	return -1;
}

void CNGNaturalNeigbours::CalWeights(const NGPOINT& PX,vector<NGPOINT>& polys,const vector<int>& allIndexs,int index,std::map<int,float>& weights)
{
	int size = polys.size();
	if (size <=1)
	{
		return;
	}
	int e1 = allIndexs[0],e2 = allIndexs[1];//�Ȼ�ȡ�͵�һ�����ཻ��ԭ���ı�
//	SwapBE(index);
	vector<NGEdge>& edges = m_polygons[index].edges;
	NGPOINT end = edges[e2].begin;
	polys.push_back(end);
	bool isLast = false;
	while(!isLast){
		for (int i = 0 ; i < edges.size() ; i ++)
		{
			if (edges[i].end == end)
			{
				if (i == e1)
				{
					isLast = true;
					break;
				}
				end = edges[i].begin;
				polys.push_back(end);
			}
		}
	}

	float weight = CalPolygonArea(polys);
	float d1 = Distance(end,PX);
	float d2 = Distance(end,mSites[index]);
	weight = weight/(m_polygons[index].area);
	if (d2 < d1)
	{
		weight = 1 - weight;
	}
	weights.insert(std::make_pair(index,weight));
}


void CNGNaturalNeigbours::GetIntersectEdge(int aIndex,int bIndex,int cIndex,int& e1,int& e2)
{
	for (int i = 0 ; i < m_polygons[bIndex].edges.size() ; i ++)
	{
		int index = m_polygons[bIndex].edges[i].leftIndex == bIndex? m_polygons[bIndex].edges[i].rightIndex:m_polygons[bIndex].edges[i].leftIndex;
		if (index == aIndex)
		{
			e1 =i;
		}
		if (index == cIndex )
		{
			e2 = i;
		}
	}
}

float CNGNaturalNeigbours::CalPolygonArea(const vector<NGPOINT>& points)
{
	if (points.size() <3)
	{
		return 0 ;
	}
	float area = 0 ;
	for (int i = 1 ; i < points.size() -1; i ++)
	{
		area += CalTriArea(points[0],points[i],points[i+1]);
	}
	return area;
}


int CNGNaturalNeigbours::DoNatNeInterpolation(NGDataVector& sites,double resultion,double minx,double miny,double maxx,double maxy,NGPOINT bottom,const char* presultfile)
{
	if (NULL == presultfile)
	{
		return POINT_CAN_NOT_NULL;
	}
	if (sites.size() < 4)
	{
		return DRIVER_TEST_POINT_NOT_ENOUGTH;
	}
	m_Resultion = resultion;
	m_MinX = minx ;
	m_MaxX = maxx ;
	m_MinY = miny ;
	m_MaxY = maxy ;
	m_width = m_MaxX - m_MinX;
	m_height = m_MaxY - m_MinY;
	m_bottom = bottom;
	marea_width=m_width/m_Resultion;
	marea_height=m_height/m_Resultion;
	CNGMD5Tool tool;
	string pointMD5 = tool.getMD5Code(sites);
	FILE* fp = fopen(pointMD5.c_str(),"rb");
	if ( NULL != fp)
	{
		printf("MD5\n");
		//����ļ����ڣ�����ͬ��·����Ѿ�������ˣ����ļ��ж�ȡ���е������Ȩ��
		if (!InitMemory(sites))
		{
			return MEMORY_WRONG;
		}
		fseek(fp,0,SEEK_END);
		int fileLength = ftell(fp);
		fseek(fp,0,SEEK_SET);
		int head[4];
		while( fileLength > ftell(fp)){
			fread(head,4,4,fp);
			vector<int> pxIndexs(head[3]);
			vector<float> pxWeights(head[3]);
			for (int i = 0 ; i < head[3] ; i ++)
			{
				fread(&pxIndexs[i],4,1,fp);
				fread(&pxWeights[i],4,1,fp);
			}
			m_BinResult[head[1] * marea_width + head[0] ]= CalPointValue(head[2],pxIndexs,pxWeights);
		}
		fclose(fp);
	}else
	{
		printf("NO MD5\n");
		DestoryMemory();
		m_BinResult = new(std::nothrow) float[marea_width*marea_height];
		if (NULL == m_BinResult)
		{
			return MEMORY_WRONG;
		}
		InitMemory(sites);
		m_pointStatus = new(std::nothrow) bool[marea_width*marea_height];
		if (NULL == m_pointStatus)
		{
			return MEMORY_WRONG;
		}
		memset(m_pointStatus,0,sizeof(bool)*marea_width*marea_height);

		if (!GetVoronoi())
		{
			return MEMORY_WRONG;//����̩ɭ�����ʧ��
		}
		GetMinframe();
		//��ʼ��ֵ
		fp =fopen(pointMD5.c_str(),"wb");
#pragma omp parallel for
		for (int i = 0 ; i < mSiteCount ; i ++)
		{
			double rectMinX,rectMaxX,rectMinY,rectMaxY;//�����Χ����ε���С��Ӿ���
			if (!GetMinRect(i,rectMinX,rectMaxX,rectMinY,rectMaxY))
			{
				continue;
			}
			for (double j = rectMinX; j <= rectMaxX ; j += m_Resultion)
			{
				for (double k = rectMinY ; k <= rectMaxY ; k += m_Resultion)
				{
					int xIndex = j/m_Resultion;
					int yIndex = k/m_Resultion;
					if (xIndex <0 || xIndex >= marea_width || yIndex <0 || yIndex >=marea_height)
					{
						continue;
					}
					NGPOINT PX;
					PX.x = j;
					PX.y = k;
					if (m_pointStatus[yIndex*marea_width+xIndex]&&PtInPolygon(i,PX))
					{
						//������ڶ������
						if (PX == mSites[i])
						{
							//��������֪����ɢ���غ�
							continue;
						}
						map<int,float> weights;
						DoPXInterpolation(PX,i,weights);//��δ֪���ֵ
						m_BinResult[yIndex * marea_width + xIndex] = CalPointValue(i,weights);
						int num = weights.size();
#pragma omp critical
						{
							fwrite(&xIndex,4,1,fp);
							fwrite(&yIndex,4,1,fp);
							fwrite(&i,4,1,fp);
							fwrite(&num,4,1,fp);
							map<int,float>::iterator it ;
							for (it = weights.begin() ; it != weights.end() ; ++it)
							{
								fwrite(&(it->first),4,1,fp);
								fwrite(&(it->second),4,1,fp);
							}
						}
					}
				}
			}
		}	
		fclose(fp);
	}
	
	return DoSmoothHandle(presultfile);
}



bool CNGNaturalNeigbours::GetMinRect(int index,double& rectMinX,double& rectMaxX,double& rectMinY,double& rectMaxY)
{
	if (m_polygons[index].edges.size() == 0 )
	{
		return false;
	}
	rectMinX = m_polygons[index].edges[0].begin.x;
	rectMaxX = rectMinX;
	rectMinY = m_polygons[index].edges[0].begin.y;
	rectMaxY = rectMinY;

	for (int i = 0 ; i < m_polygons[index].edges.size() ; i ++)
	{
		rectMinX = min(m_polygons[index].edges[i].begin.x,rectMinX);
		rectMaxX = max(m_polygons[index].edges[i].begin.x,rectMaxX);
		rectMinY = min(m_polygons[index].edges[i].begin.y,rectMinY);
		rectMaxY = max(m_polygons[index].edges[i].begin.y,rectMaxY);
		rectMinX = min(m_polygons[index].edges[i].end.x,rectMinX);
		rectMaxX = max(m_polygons[index].edges[i].end.x,rectMaxX);
		rectMinY = min(m_polygons[index].edges[i].end.y,rectMinY);
		rectMaxY = max(m_polygons[index].edges[i].end.y,rectMaxY);
	}
	rectMinX = (int)((rectMinX - m_MinX)/m_Resultion )*m_Resultion + m_MinX;
	rectMinY = (int)((rectMinY - m_MinY)/m_Resultion )*m_Resultion + m_MinY;
	return true;
}

//�жϵ��Ƿ��ڵ�index���������
bool CNGNaturalNeigbours::PtInPolygon(int index , const NGPOINT& PX)
{
	return PtInPolygon(m_polygons[index].edges,PX);
}

bool CNGNaturalNeigbours::PtInPolygon(vector<NGEdge>& edges , const NGPOINT& PX)
{
	int nCross = 0;	
	//	int count = 0 ;
	for (int i = 0; i < edges.size(); i++) 
	{
		if (PointInSeg(PX,edges[i]))
		{
			return true;//�������̩ɭ����α���
		}
		NGPOINT& p1 = edges[i].begin;  
		NGPOINT& p2 = edges[i].end;  

		// ��� y=p.y �� p1p2 �Ľ���  

		if ( p1.y == p2.y )      // p1p2 �� y=p0.yƽ��
			continue;

		if ( PX.y <  min(p1.y, p2.y) )   // ������p1p2�ӳ�����
			continue;
		if ( PX.y > max(p1.y, p2.y) )   // ������p1p2�ӳ�����
			continue;

		//	count ++;
		// �󽻵�� X ���� --------------------------------------------------------------
		double x = (double)(PX.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
		if ( x >= PX.x ) 
		{
			nCross++;       // ֻͳ�Ƶ��߽���
			//�������������p1p2�Ķ˵㣬��ô��������Ҳ�ཻ��������һ�����㣬�����ظ�
			if (fabs(x - p2.x) < 0.00001 || fabs(x - p1.x) < 0.00001)
			{
				i++;
			}
		}
	}

	// ���߽���Ϊż�������ڶ����֮�� ---
	return (/*count != 1 &&*/ nCross % 2 == 1);
}


//�����߶κ�ֱ�ߵĽ��㣬true�����н���
bool CNGNaturalNeigbours::GetSegIntersect(NGEdge& edge,NGLine line,NGPOINT& interPoint)
{
	if (edge.begin == edge.end)
	{
		//����߶�����һ����,����false�����߶�����һ���߶ε��Ӽ�
		return false;
	}
	NGLine eline;
	eline.a = (edge.end.y - edge.begin.y);
	eline.b = (edge.begin.x - edge.end.x);
	eline.c = edge.end.x * edge.begin.y - edge.begin.x * edge.end.y;
	double delta = eline.a*line.b - eline.b* line.a;
	if (fabs(delta) < 0.000001)
	{
		return false;//����ֱ��ƽ��
	}
	//��������ֱ�ߵĽ���
	interPoint.x = (eline.b*line.c - eline.c*line.b)/delta;
	interPoint.y = (eline.c*line.a - eline.a*line.c)/delta;
	//�жϵ��Ƿ����߶���
	return PointInSeg(interPoint,edge);
}


int CNGNaturalNeigbours::CalWeightofPXInIndex(const NGPOINT& PX,int index,int beforeSite,std::map<int,float>& weights)
{
	if (index < 0)
	{
		return -1;
	}
//	SwapBE(index);
	vector<NGEdge>& edges=m_polygons[index].edges;
	NGLine perline = GetPerLine(PX,mSites[index]);//�ȼ������ֵ������ڵ�̩ɭ����ε���ɢ����д���
	int size = edges.size();
	vector<NGPOINT> points;//�����д��ߺ�̩ɭ����εĽ���
	vector<int> allIndex;//���潻�����ڵı�
	points.reserve(10);
	allIndex.reserve(2);
	int nextSite = -1;
	for (int i = 0 ; i < size ; i ++ )
	{
		NGPOINT interPoint;
		if (GetSegIntersect(edges[i],perline,interPoint))
		{
			points.push_back(interPoint);
			int aIndex = edges[i].leftIndex == index? edges[i].rightIndex : edges[i].leftIndex;
			if (aIndex != beforeSite)
			{
				nextSite = aIndex;
			}
			allIndex.push_back(i);
		}
	}
	CalWeights(PX,points,allIndex,index,weights);
	return nextSite;
}

int CNGNaturalNeigbours::DoSmoothHandle(const char* presultfile)
{
	if(NULL == m_BinResult || NULL == presultfile){
		return POINT_CAN_NOT_NULL;
	}
	
	double lngResultion = m_Resultion / 111000.0;
	int outWidth = marea_width;
	int outHeight = marea_height;
	RasterResult BinResult;
	if (!BinResult.GenerateEmptyRaster(ePowerLevel,DATA_FLOAT,CRUNIT_DBUV_PER_M,103,leftLon,bottomLat,outWidth,outHeight,lngResultion,lngResultion))
	{
		return MEMORY_WRONG;
	}
	for (int i = 0 ; i < outWidth ; i ++)
	{
		double px = i*lngResultion+leftLon;
		for (int j = 0 ; j < outHeight ; j ++)
		{
			double py = j * lngResultion + bottomLat;
			double coordX,coordY;
			ng_geo_trans(103,PlaneCoord,px,py,&coordX,&coordY);
			int xIndex = (coordX - m_MinX)/m_Resultion;
			int yIndex = (coordY - m_MinY)/m_Resultion;
			if (xIndex >= marea_width || xIndex <0 || yIndex >= marea_height || yIndex < 0)
			{
				continue;
			}
			float fvalue =0;
			int sum = 0;
			int filterx1 = xIndex>0?xIndex-1:xIndex;
			int filterx2 = xIndex<marea_width-1?xIndex+1:xIndex;
			int filtery1 = yIndex>0?yIndex-1:yIndex;
			int filtery2 = yIndex<marea_height-1?yIndex+1:yIndex;
			for(int x = filterx1;x<=filterx2;x++)
			{
				for(int y=filtery1;y<=filtery2;y++)
				{
					float v = m_BinResult[y*marea_width+x];
					if(v>UNCALCULATE)
					{
						fvalue += v;
						sum ++;
					}
				}
			}
			if(sum>0)
			{
					BinResult.SetValue(i,j,fvalue/sum);
			}
		}
	}
	if (BinResult.WriteRaster(presultfile))
	{
		return SUCCESS;
	}
	return FAIL_TO_WRITE_FILE;
}

void CNGNaturalNeigbours::GetMinframe()
{
	//�Զ����һ������
	std::vector<NGPlaneVector> planeVectors;
	m_bottom.x -= m_MinX;
	m_bottom.y = -10; 
	for (int i = 0 ; i < mSiteCount ; i ++)
	{
		double length = Distance(mSites[i],m_bottom);
		if (fabs(length - 0 ) < 0.000001)
		{
			continue;
		}
		double angle = (mSites[i].x - m_bottom.x)/length;
		bool isNotFirst = false;
		for (int j = 0 ; j < planeVectors.size() ; j ++)
		{
			if (fabs(planeVectors[j].angle - angle)<0.00001)
			{
				isNotFirst = true;
				if (planeVectors[j].length < length)
				{
					planeVectors[j].length = length;
					planeVectors[j].index = i;
				}
				break;
			}
		}
		if (!isNotFirst)
		{
			NGPlaneVector plane;
			plane.index = i ;
			plane.angle = angle;
			plane.length = length;
			planeVectors.push_back(plane);
		}
	}
	std::sort(planeVectors.begin(),planeVectors.end(),CMPNGVector);
	bool isFine = false;
	while(!isFine){
		isFine = true;
		for (int j = 0 ; j < planeVectors.size() -2;)
		{
			NGPOINT p1 = mSites[planeVectors[j].index];
			NGPOINT p2 = mSites[planeVectors[j+1].index];
			NGPOINT p3 = mSites[planeVectors[j+2].index];
			double cross = (p2.x - p1.x)*(p3.y - p2.y) - (p2.y-p1.y)*(p3.x - p2.x);
			if (cross >= 0 )
			{
				planeVectors.erase(planeVectors.begin() +j +1);
				isFine = false;
			}else{
				j ++;
			}
		}
	}
	if (planeVectors.size() == 0 )
	{
		return;
	}
	NGEdge e;
	e.begin = m_bottom;
	e.end = mSites[planeVectors[0].index];
	m_frame.edges.clear();
	m_frame.edges.push_back(e);
	int size = planeVectors.size();
	for (int i = 0 ; i < size -1  ; i ++)
	{
		int j = i+1;
		e.begin = mSites[planeVectors[i].index];
		e.end = mSites[planeVectors[j].index];
		m_frame.edges.push_back(e);
	}
	e.begin = mSites[planeVectors[size -1].index];
	e.end = m_bottom;
	m_frame.edges.push_back(e);
	for (double i = m_MinX ; i <= m_MaxX ; i += m_Resultion)
	{
		for (double j = m_MinY ;  j <= m_MaxY ; j+= m_Resultion)
		{
			NGPOINT px;
			px.x = i  - m_MinX;
			px.y = j  - m_MinY;
			int xIndex =px.x  /m_Resultion;
			int yIndex = px.y/m_Resultion;
			if (xIndex <0 || xIndex >= marea_width || yIndex <0 || yIndex >=marea_height)
			{
				continue;
			}
			if (PtInFrame(px))
			{
				m_pointStatus[yIndex * marea_width + xIndex] = true;
			}else{
				m_pointStatus[yIndex * marea_width + xIndex] = false;
			}
		}
	}
}

bool CNGNaturalNeigbours::PtInFrame(const NGPOINT& px)
{
	int nCross = 0;	
	//	int count = 0 ;
	for (int i = 0; i < m_frame.edges.size(); i++) 
	{
		if (PointInSeg(px,m_frame.edges[i]))
		{
			return true;//�������̩ɭ����α���
		}
		NGPOINT& p1 = m_frame.edges[i].begin;  
		NGPOINT& p2 = m_frame.edges[i].end;  

		// ��� y=p.y �� p1p2 �Ľ���  

		if ( p1.y == p2.y )      // p1p2 �� y=p0.yƽ��
			continue;

		if ( px.y <  min(p1.y, p2.y) )   // ������p1p2�ӳ�����
			continue;
		if ( px.y > max(p1.y, p2.y) )   // ������p1p2�ӳ�����
			continue;

		//	count ++;
		// �󽻵�� X ���� --------------------------------------------------------------
		double x = (double)(px.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
		if ( x >= px.x ) 
			nCross++;       // ֻͳ�Ƶ��߽���
	}

	// ���߽���Ϊż�������ڶ����֮�� ---
	return (/*count != 1 &&*/ nCross % 2 == 1);
}


void CNGNaturalNeigbours::DestoryMemory()
{
	NG_DELETE_ARRAY(m_polygons);
	NG_DELETE_ARRAY(m_pointStatus);
	NG_DELETE_ARRAY(m_BinResult);
	mSites.clear();
	m_frame.edges.clear();
}

double CNGNaturalNeigbours::CalPointValue(int index,std::map<int,float>& weights)
{
	std::map<int,float>::iterator it ;
	double w = 0 ;
	double ws = 0 ;
	if (weights.size() == 1)
	{
		it = weights.begin();
		w = log10(fabs(it->second)) * mSites[it->first].value;
	}else{
		for ( it = weights.begin() ; it != weights.end() ; ++it)
		{
			w+= it->second* pow(10.0,mSites[it->first].value);
			ws += it->second;
		}
		w = log10(w/ws);
	}
	if (w == 0 || w != w || w > m_MaxValue)
	{
		w = mSites[index].value;
	}
	return w;
}

double CNGNaturalNeigbours::CalPointValue(int index,vector<int>& pxIndexs,vector<float>& pxWeights)
{
	double w = 0 ;
	double ws = 0 ;
	if (pxWeights.size() == 1)
	{
		w = log10(fabs(pxWeights[0])) * mSites[pxIndexs[0]].value;
	}else{
		for (int i = 0 ; i < pxIndexs.size() ; i ++)
		{
			w+= pxWeights[i] * pow(10.0,mSites[pxIndexs[i]].value);
			ws += pxWeights[i];
		}
		w  = log10(w/ws);
	}
	if (w == 0 || w != w || w > m_MaxValue)
	{
		w = mSites[index].value;
	}
	return w;
}

bool CNGNaturalNeigbours::InitMemory(NGDataVector& sites)
{
	if (NULL == m_BinResult)
	{
		m_BinResult = new(std::nothrow) float[marea_width*marea_height];
		if (NULL == m_BinResult)
		{
			return false;
		}
	}
	for (int i = 0 ; i < marea_height ; i++)
	{
		for (int j = 0 ; j < marea_width ; j++)
		{
			m_BinResult[i * marea_width + j ] = UNCALCULATE;
		}
	}
	mSiteCount = sites.size();
	mSites.resize(mSiteCount);
	m_MaxValue = -1000;
	for ( int i = 0 ; i < mSiteCount ; i++)
	{
		double x = sites[i].x - m_MinX;
		double y = sites[i].y - m_MinY;
		m_MaxValue = m_MaxValue > sites[i].value? m_MaxValue : sites[i].value;
		mSites[i].x = x ;
		mSites[i].y = y;
		mSites[i].value = sites[i].value;
		int xIndex = x/m_Resultion;
		int yIndex = y/m_Resultion;
		if (xIndex <0 || xIndex >= marea_width || yIndex <0 || yIndex >=marea_height)
		{
			continue;
		}
		m_BinResult[yIndex * marea_width + xIndex] = mSites[i].value;
	}
	return true;
}

