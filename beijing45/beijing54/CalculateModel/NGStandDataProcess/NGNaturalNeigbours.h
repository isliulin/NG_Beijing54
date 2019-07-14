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


	//邻区插值
	int DoNatNeInterpolation(NGDataVector& sites,double resultion,double minx,double miny,double maxx,double maxy,NGPOINT bottom,const char* presultfile);
	
private:

	//获取泰森多边形
	bool GetVoronoi(double minDist = 0 );

	bool GeneratorEdges();//构建多边形，边顺序排列


	bool CalTriMCC(NGPOINT p1,NGPOINT p2,NGPOINT p3,NGPOINT& center);
	//计算三角形的外接圆圆心

	void SwapBE(NGEdge& edge);//交换线段的开始和结束点

	void DoPXInterpolation(NGPOINT PX,int index,std::map<int,float>& weights);////计算待插值点PX对应的泰森多边形在原来的泰森多边形里的权重,点PX在第index个泰森多边形内

	inline double Distance(NGPOINT p1,NGPOINT p2){return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));}

	//计算三角形面积，输入三个顶点
	float CalTriArea(const NGPOINT& p1,const NGPOINT& p2,const NGPOINT& p3);/*{return fabs(p1.x*p2.y + p2.x*p3.y+p3.x*p1.y - p1.x*p3.y - p2.x*p1.y - p3.x*p1.y);}*/

	NGEdge GetExtraEdge(NGPOINT& begin,NGPOINT& polyBegin,vector<NGEdge>& edges);

	void DeleteSameEdge(vector<NGEdge>& edges,vector<NGEdge>& bedges);//线段首位两点相同或者线段两端的离散点相同，则删除一个

	//获取两点的中垂线
	NGLine GetPerLine(NGPOINT p1, NGPOINT p2);

	bool PointInSeg(const NGPOINT& point,int leftIndex,int rightIndex);//判断点是否在由两个离散点确定的线段上
	bool PointInSeg(const NGPOINT& point,const NGEdge& edge);

	int GetSameNeigbours(int aIndex,int bIndex,int index);//获取两个泰森多边形相同的邻区的索引

	void CalWeights(const NGPOINT& PX,vector<NGPOINT>& polys,const vector<int>& allIndexs,int index,std::map<int,float>& weights);//计算待插值点在所有邻区的权值

	void GetIntersectEdge(int aIndex,int bIndex,int cIndex,int& e1,int& e2);

	float CalPolygonArea(const vector<NGPOINT>& points);//计算多边形面积，多边形由点顺序组成

	bool GetMinRect(int index,double& rectMinX,double& rectMaxX,double& rectMinY,double& rectMaxY);

	bool PtInPolygon(int index , const NGPOINT& PX);////判断点是否在第index个多边形内
	bool PtInPolygon(vector<NGEdge>& edges , const NGPOINT& PX);////判断点是否在多边形内

	bool PtInFrame(const NGPOINT& PX);//判断第index个离散点是否在边框内

	bool GetSegIntersect(NGEdge& edge,NGLine line,NGPOINT& interPoint);//计算线段和直线的交点

	int CalWeightofPXInIndex(const NGPOINT& PX,int index,int beforeSite,std::map<int,float>& weights);//计算PX在某个泰森多边形内的权重，并获取下一个邻区的索引
	
	int DoSmoothHandle(const char* presultfile);//平滑处理
	
	void GetMinframe();//获取离散点的凸包

	void DestoryMemory();

	double CalPointValue(int index,std::map<int,float>& weights);

	double CalPointValue(int index,vector<int>& pxIndexs,vector<float>& pxWeights);
	bool InitMemory(NGDataVector& sites);
private:
	NGPolygon* m_polygons;//生成的泰森多边形

	NGPolygon m_frame;//包围所有路程数据的最小多边形

	NGPOINT m_bottom;
	vector<NGPOINT>  mSites;//离散点

	int mSiteCount;//离散点个数

	double m_Resultion;//插值分辨率
	//std::map<int,float> weights;

	short m_MaxValue;
    
	double m_width,m_height;//宽和高
	double m_MinX,m_MaxX,m_MinY,m_MaxY;//包围的矩形框

	long marea_width , marea_height;

	bool* m_pointStatus;//用于判断点是否在凸包内

	float* m_BinResult;
	string m_old_md5;//用所有的路测点坐标计算出的MD5码，用于判断前后两次路测点是否一样
	vector<NGVoronoiWeight> m_allweights;//保存所有点的权重
public:
	double leftLon;
	double bottomLat;
	void SetWGSLeftBottom(double l,double b){leftLon = l;bottomLat = b;}

};

#endif
