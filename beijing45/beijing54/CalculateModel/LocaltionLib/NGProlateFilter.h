#ifndef NG_PROLATE_FILTER_H
#define NG_PROLATE_FILTER_H

#include "LowPassFilter.h"

//椭圆滤波器
class CNGProlateFilter:public LowPassFilter
{
public:
	CNGProlateFilter(double bandWidth, double stopBandFreq, double sampleRate, double attenuationIndB=20);
	~CNGProlateFilter(void);

private:
	void GetFilterCoefficient();//获取滤波系数

	double Ellik( double phi, double m );

	double Polevl( double x, const double* coef, int N);

	double Ellpk(double x);

	int Ellpj( double u, double m,  double& sn, double& cn, double& dn, double& ph);

	double Cay(double q);

	int Zp2tf(int order, vector<TDComplex> zzeros, vector<TDComplex> zpoles);

	int Sp2Zp(double Op, int order, TDComplex* szeros,int zsize, TDComplex* spoles,int psize,
		vector<TDComplex>& zzeros, vector<TDComplex>& zpoles);
};

#endif