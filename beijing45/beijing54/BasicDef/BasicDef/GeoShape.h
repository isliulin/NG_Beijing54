#pragma once

#include "DataTypes.h"
#include <vector>

// add by jie-z@2012/06/20
/**
 * 增加所有形状的超类
 * 并修改现有的类，使其继承于CShape
 */
class CGeoShape
{
public:
	virtual ~CGeoShape(){}
public:
	long m_nCoordSys;   //点所在的坐标系编号
};

//空间中点的定义  --Z方向始终是高度信息，x，y方向会有不同的坐标系
class CGeoPoint : public CGeoShape //    upd by jie-z@2013/07/20
{
public:
//	long m_nCoordSys;   //点所在的坐标系编号    // del by jie-z@2013/07/20

	CDoublePoint m_Point;
};

//空间中线的定义 
class CGeoLine : public CGeoShape //    upd by jie-z@2013/07/20
{
public:
	//点所在的坐标系编号
//	long m_nCoordSys;       // del by jie-z@2013/07/20

	//起始点
	CDoublePoint m_SPoint;

	//终止点
	CDoublePoint m_EPoint;
};

//地图中矩形框的定义
class CGeoRectangle : public CGeoShape //    upd by jie-z@2013/07/20
{
public:
//	long m_nCoordSys;    // del by jie-z@2013/07/20

	//海拔高度
	double m_dASLM;

	//一个顶点
	CDoublePoint2D m_Corner1;

	//另外给定一个顶点
	CDoublePoint2D m_Corner2;
};

//地图中圆的定义
class CGeoCircle : public CGeoShape //    upd by jie-z@2013/07/20
{
public:
//	long m_nCoordSys;   //点所在的坐标系编号    // del by jie-z@2013/07/20

	//海拔高度
	double m_dASLM;

	//中心点坐标
	CDoublePoint2D m_Center;

	//半径
	double m_dRadiusKM;
};

class CGeoPolygon : public CGeoShape //    upd by jie-z@2013/07/20
{
public:
	CGeoPolygon();

	~CGeoPolygon();

	CGeoPolygon(int nPointNum);

	//copy构造函数
    CGeoPolygon( CGeoPolygon& polygon);

	//赋值函数
	CGeoPolygon& operator=(CGeoPolygon& polygon);

	//重新申请大小
	bool Resize(int nSize);

	//清0
	void Reset();

	//释放空间
	void ReleaseData();

	//将数据写入文件
	bool WriteToFile(const char* filename);

	//从文件中读取数据
	bool ReadFromFile(const char * filename);

	bool ReadFromTxtFile( const char *filename );
	bool ReadFromStream( std::istream &instream  );

	//是否封闭
	bool m_bClosed;

	//点的个数
	int m_nPointsNum;

	//总大小：指存储空间
	int m_nSize;

	//点坐标坐标系
//	int m_nCoordSys;    // del by jie-z@2013/07/20

	//点的集合
	CDoublePoint* m_pPointData;
};


// 各种形状栅格化后的结果集
class CRasterlizedRst
{
public:
	CRasterlizedRst() {
	}

	~CRasterlizedRst() {
		m_v2dPointData.clear();
	}

	//点坐标
	std::vector<CDoublePoint2D> m_v2dPointData;
};
