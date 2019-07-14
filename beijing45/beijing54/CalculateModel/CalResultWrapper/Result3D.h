#ifndef __CAL__RESULT__3D__H__
#define __CAL__RESULT__3D__H__

#include "CalResultWrapper.h"
#include "../BasicDef/DataTypes.h"

class RESULT_API Result3D
{
public:
	static Result3D* Create();
	static Result3D* Create(int nHorizonSize, int nVerticalSize);
	static bool	Destroy(Result3D* pDestroy);

public://构造析构函数
	Result3D(int nHorizonSize, int nVerticalSize);
	Result3D();
	~Result3D();

public:
	//重新申请大小
	int ReSize(int nHorizonSize, int nVerticalSize);

	//空间重置
	void Reset();

	//清理空间
	void Clear();

	//获取结果的点列表
	CDoublePoint** GetPointList(){return m_pp3DPoints;}

	//设置给定索引处的点
	int SetPoint(int nHorIndex, int nVerIndex, CDoublePoint& point);

    //获取给定索引处的点
	int GetPoint(int nHorIndex, int nVerIndex, CDoublePoint& point);

	//获取坐标系
	int GetCoordSys(){ return m_nCoordSys; }

	//设置坐标系
	void SetCoordSys(int inSys) { m_nCoordSys = inSys; }

	//设置角度
	void SetAngle(int nHStartAngle, int nHEndAngle, int nVStartAngle, int nVEndAngle, int nHStep, int nVStep);

	//获取角度
	void GetAngle(int& nHStartAngle, int& nHEndAngle, int& nVStartAngle, int& nVEndAngle, int& nHStep, int& nVStep);

	//获取二维空间的大小
	void Size(int& nHorizonSize, int& nVerticalSize);

	//获取实际点的个数
	void GetPointsNum(int& nHorPointsNum, int& nVerPointsNum);	

	int WriteToFile(const char* filename);
	int ReadFromFile(const char * filename);

private:	
	//结果中水平方向的大小
	int m_nHorizonSize;

	//结果中垂直方向的大小
	int m_nVerticalSize;

	//结果中水平方向点的个数
	int m_nHorPointsNum;

	//结果中垂直方向点的个数
	int m_nVerPointsNum;

	//角度范围
	int m_nHStartAngle;  //水平方向起始角度
	int m_nHEndAngle;    //水平方向终止角度
	int m_nVStartAngle;  //垂直方向起始角度
	int m_nVEndAngle;    //垂直方向终止角度

	//角度步长
	int m_nHStep;        //水平方向角度步长
	int m_nVStep;        //垂直方向角度步长

	//点集
	//点使用的坐标系序号
	int m_nCoordSys;  

	//点集
	CDoublePoint** m_pp3DPoints;  	
protected:
	void SwapData();
};
#endif