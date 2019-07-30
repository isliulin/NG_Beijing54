#ifndef __DATAMODEL_COMPUTERESULT_h
#define __DATAMODEL_COMPUTERESULT_h
//结果的一些结构体
//线的覆盖分析结果
class CLineComputeResult
{
public:
	int m_nSize;  //结果大小
	int m_nPointsNo; //结果中点的个数

	//点集
	int m_nCoordSys;  //点使用的坐标系序号
	CDoublePoint* m_pPointList;  //点集
	float* m_pValueList; //值列表
};

#endif