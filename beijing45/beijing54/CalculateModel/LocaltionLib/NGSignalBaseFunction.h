
#ifndef NG_SIGNAL_BASE_FUNCTION_H
#define NG_SIGNAL_BASE_FUNCTION_H

#include "NGTDOADataStruct.h"



class CNGSignalBaseFunction
{

private:
	CNGSignalBaseFunction(void){};
	~CNGSignalBaseFunction(void){};

public:



	//根据焦点和距离差计算双曲线上的点
	static bool GetHypersPoints(const NGPostion& p1 , const NGPostion& p2 ,double distancedif , double dmax, vector<NGPostion>& hypoints);

	//计算双曲线的交点

	static bool CalHyperIntersection(const vector<NGPostion>& hypoint1 , const vector<NGPostion>& hypoint2 , vector<NGPostion>& interpoints);

private:
	//计算两点的距离
	static inline double Distance(const NGPostion& p1 , const NGPostion& p2);

	//计算两点连线和X轴的夹角
	static double GetPointABToX(const NGPostion& p1 , const NGPostion& p2);


	//计算坐标pos绕原点旋转某个角度后的坐标，仍保存在pos中
	static void CalPointRotate(NGPostion& pos , double d_turnAngle);

	//判断两个线段是否相交，若相交，则计算交点
	static bool CalSegmentIntersect(const NGSegment& s1 , const NGSegment& s2 , NGPostion& point);
};

#endif
