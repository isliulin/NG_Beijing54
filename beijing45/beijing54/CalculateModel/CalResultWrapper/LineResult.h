#ifndef __CAL__LINE__RESULT__H__
#define __CAL__LINE__RESULT__H__

#include "CalResultWrapper.h"
#include "../BasicDef/DataTypes.h"
#include "../DataModel/EnumDef.h"

class RESULT_API LineResult
{
public:
	static LineResult* Create();
	static LineResult* Create(int inSize);
	static bool	Destroy(LineResult* pDestroy);

public://构造析构函数
	LineResult(long noPoints);
	LineResult();
	~LineResult();

public:

	//重新申请大小
	int ReSize(int nSize);

	//空间重置
	void Reset();

	//清理空间
	void Clear();
	//获取值列表
	float* GetValueList(){return m_pValueList;}

	//设置第index点的值
	int SetPointValue(int index, CDoublePoint& point, float value);

	//获取第index点的值
	int GetPointValue(int index, CDoublePoint& point, float& value);

	//获取坐标系
	int GetCoordSys(){ return m_nCoordSys; }

	//设置坐标系
	void SetCoordSys(int inSys) { m_nCoordSys = inSys; }

	//获取空间的大小
	long Size() {return m_nSize; }

	//获取实际点的个数
	long GetPointsNum(){ return m_nNoPoints; }

	//获取计算结果的单位类别
	CalResult_Unit GetCalResultDataUnit() { return m_eDataUnit;}

	//设置计算结果的单位类别
	void SetCalResultDataUnit(CalResult_Unit inUnit) { m_eDataUnit = inUnit; }

private:
	//结果大小
	long m_nSize; 

	//结果中点的个数
	long m_nNoPoints;

	//点集
	//点使用的坐标系序号
	int m_nCoordSys;  

	//点集
	CDoublePoint* m_pPointList;  

	//值列表
	float* m_pValueList; 

	//结果的单位类别
	CalResult_Unit m_eDataUnit;
	//当为大端数据时需交换字节序
protected:
	void SwapData();

public:
	int ReadFromFile(const char * file);
	int WriteToFile(const char* file); 
};
#endif