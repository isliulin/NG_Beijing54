#include "dataTypeChange.h"
double dataTypeChange::dbmTomw(double dbm) 
{
	double mw = dbm;
	mw /= 10;
	mw = pow(10, mw);
	return mw;
}

double dataTypeChange::mwToDbm(double mw)
{
	double dbm = mw;
	dbm = log10(mw);
	dbm=dbm*10;
	return dbm;
}