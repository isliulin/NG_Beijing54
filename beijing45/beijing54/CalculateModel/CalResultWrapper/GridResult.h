#ifndef __CAL__GRID__RESULT__H__
#define __CAL__GRID__RESULT__H__

#include "CalResultWrapper.h"
#include "../BasicDef/DataTypes.h"


//网格化的3D结果
class RESULT_API GridResult
{
public:
	static GridResult* Create();
	static GridResult* Create(int nSize);
	static void	Destroy(GridResult*);

public:
	GridResult(void);
	GridResult(int nSize);
	~GridResult(void);

public:
	//重新申请大小
	int ReSize(int nSize);

	//空间重置
	void Reset();

	//清理空间
	void Clear();

	//设置给定索引处的点
	int SetPoint(int nIndex, CDoublePoint& point, float fValue);

	//获取给定索引处的点
	int GetPoint(int nIndex, CDoublePoint& point, float& fValue);

	//获取坐标系
	int GetCoordSys(){ return m_nCoordSys; }

	//设置坐标系
	void SetCoordSys(int inSys) { m_nCoordSys = inSys; }

	//获取空间的大小
	void Size(int& nSize) { nSize = m_nSize; };

	//获取实际点的个数
	void GetPointsNum(int& nPointsNum){ nPointsNum = m_nPointsNum; }

	int WriteToFile(const char* filename);
	int ReadFromFile(const char * filename);

private:
	//结果大小
	int m_nSize;

	//结果中点的个数
	int m_nPointsNum;

	//点集
	//点使用的坐标系序号
	int m_nCoordSys;

	//点集
	CDoublePoint* m_p3DPoints;
	float* m_pValues;
protected:
	void SwapData();
};


#endif
