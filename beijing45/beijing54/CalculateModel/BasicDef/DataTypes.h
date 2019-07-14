#pragma once

//定义一个双精度浮点型的点
class CDoublePoint2D
{
public:
	double x;
	double y;
};
class CDoublePoint
{
public:
	double x;
	double y;
	double z;
};

class CDoubleRect
{
public:
	double dLeft;
	double dTop;
	double dRight;
	double dBottom;
};

typedef double	AngleInDeg;

// 损耗（单位：dB）
typedef double LossIndB;