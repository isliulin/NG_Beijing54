#pragma once
#include "../CalculateModel/BasicDef/GeoShape.h"


class CPolygonFunction
{
public:
	CPolygonFunction(CGeoPolygon *pRect);
	virtual ~CPolygonFunction();
    bool GetMaxRect(double &minx,double &miny,double &maxx,double &maxy);
	bool PtInPolygon (CDoublePoint p);
private:
 CGeoPolygon *mpPolygon;
};


