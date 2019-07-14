#ifndef NG_NATURAL_NEIGHBOURS_H
#define NG_NATURAL_NEIGHBOURS_H

#include "VoronoiDiagramGenerator.h"
#include <map>
#include "CNGPreDefine.h"
#include "ErrorCode.h"
#include "../CalResultWrapper/RasterResult.h"


class CNGNaturalNeigbours
{
public:
	CNGNaturalNeigbours(void);
	~CNGNaturalNeigbours(void);


	//������ֵ
	int DoNatNeInterpolation(NGDataVector& sites,double resultion,double minx,double miny,double maxx,double maxy,NGPOINT bottom,const char* presultfile);
	
private:

	//��ȡ̩ɭ�����
	bool GetVoronoi(double minDist = 0 );

	bool GeneratorEdges();//��������Σ���˳������


	bool CalTriMCC(NGPOINT p1,NGPOINT p2,NGPOINT p3,NGPOINT& center);
	//���������ε����ԲԲ��

	void SwapBE(NGEdge& edge);//�����߶εĿ�ʼ�ͽ�����

	void DoPXInterpolation(NGPOINT PX,int index,std::map<int,float>& weights);////�������ֵ��PX��Ӧ��̩ɭ�������ԭ����̩ɭ��������Ȩ��,��PX�ڵ�index��̩ɭ�������

	inline double Distance(NGPOINT p1,NGPOINT p2){return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));}

	//���������������������������
	float CalTriArea(const NGPOINT& p1,const NGPOINT& p2,const NGPOINT& p3);/*{return fabs(p1.x*p2.y + p2.x*p3.y+p3.x*p1.y - p1.x*p3.y - p2.x*p1.y - p3.x*p1.y);}*/

	NGEdge GetExtraEdge(NGPOINT& begin,NGPOINT& polyBegin,vector<NGEdge>& edges);

	void DeleteSameEdge(vector<NGEdge>& edges,vector<NGEdge>& bedges);//�߶���λ������ͬ�����߶����˵���ɢ����ͬ����ɾ��һ��

	//��ȡ������д���
	NGLine GetPerLine(NGPOINT p1, NGPOINT p2);

	bool PointInSeg(const NGPOINT& point,int leftIndex,int rightIndex);//�жϵ��Ƿ�����������ɢ��ȷ�����߶���
	bool PointInSeg(const NGPOINT& point,const NGEdge& edge);

	int GetSameNeigbours(int aIndex,int bIndex,int index);//��ȡ����̩ɭ�������ͬ������������

	void CalWeights(const NGPOINT& PX,vector<NGPOINT>& polys,const vector<int>& allIndexs,int index,std::map<int,float>& weights);//�������ֵ��������������Ȩֵ

	void GetIntersectEdge(int aIndex,int bIndex,int cIndex,int& e1,int& e2);

	float CalPolygonArea(const vector<NGPOINT>& points);//�������������������ɵ�˳�����

	bool GetMinRect(int index,double& rectMinX,double& rectMaxX,double& rectMinY,double& rectMaxY);

	bool PtInPolygon(int index , const NGPOINT& PX);////�жϵ��Ƿ��ڵ�index���������
	bool PtInPolygon(vector<NGEdge>& edges , const NGPOINT& PX);////�жϵ��Ƿ��ڶ������

	bool PtInFrame(const NGPOINT& PX);//�жϵ�index����ɢ���Ƿ��ڱ߿���

	bool GetSegIntersect(NGEdge& edge,NGLine line,NGPOINT& interPoint);//�����߶κ�ֱ�ߵĽ���

	int CalWeightofPXInIndex(const NGPOINT& PX,int index,int beforeSite,std::map<int,float>& weights);//����PX��ĳ��̩ɭ������ڵ�Ȩ�أ�����ȡ��һ������������
	
	int DoSmoothHandle(const char* presultfile);//ƽ������
	
	void GetMinframe();//��ȡ��ɢ���͹��

	void DestoryMemory();

	double CalPointValue(int index,std::map<int,float>& weights);

	double CalPointValue(int index,vector<int>& pxIndexs,vector<float>& pxWeights);
	bool InitMemory(NGDataVector& sites);
private:
	NGPolygon* m_polygons;//���ɵ�̩ɭ�����

	NGPolygon m_frame;//��Χ����·�����ݵ���С�����

	NGPOINT m_bottom;
	vector<NGPOINT>  mSites;//��ɢ��

	int mSiteCount;//��ɢ�����

	double m_Resultion;//��ֵ�ֱ���
	//std::map<int,float> weights;

	short m_MaxValue;
    
	double m_width,m_height;//��͸�
	double m_MinX,m_MaxX,m_MinY,m_MaxY;//��Χ�ľ��ο�

	long marea_width , marea_height;

	bool* m_pointStatus;//�����жϵ��Ƿ���͹����

	float* m_BinResult;
	string m_old_md5;//�����е�·�������������MD5�룬�����ж�ǰ������·����Ƿ�һ��
	vector<NGVoronoiWeight> m_allweights;//�������е��Ȩ��
public:
	double leftLon;
	double bottomLat;
	void SetWGSLeftBottom(double l,double b){leftLon = l;bottomLat = b;}

};

#endif
