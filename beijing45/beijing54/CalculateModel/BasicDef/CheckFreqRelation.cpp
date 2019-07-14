#include <math.h>
#include "CheckFreqRelation.h"

bool ISCoFreq(double RxFreq,double RxBand,double IntFreq,double IntBand)
{
	if ((RxFreq==IntFreq) || (fabsf(RxFreq-IntFreq)<(RxBand+IntBand)/2.0))
	{
		return true;
	}

	return false;
}

bool ISAdjFreq(double RxFreq,double RxBand,double IntFreq,double IntBand)
{
	double value = fabsf(RxFreq-IntFreq)-(RxBand+IntBand)/2.0;
	if (value<RxBand && value>0)
	{
		return true;
	}

	return false;
}

bool ISCoAdjFreq(double RxFreq,double RxBand,double IntFreq,double IntBand)
{
	if (ISCoFreq(RxFreq,RxBand,IntFreq,IntBand))
	{
		return true;
	}

	if (ISCoFreq(RxFreq,RxBand,IntFreq,IntBand))
	{
		return true;
	}

	return false;
}
