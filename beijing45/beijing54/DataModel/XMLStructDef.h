#ifndef __STRUCTDET__H__
#define __STRUCTDET__H__

#include <string>
#include "../BasicDef/DataTypes.h"
#include "../BasicDef/GeoShape.h"
#include "../NGModelParamWrapper/ModelParamWrapperExport.h"
#include "TransModelParam.h"
#include <vector>

using namespace std;
struct station{
	string id;
	int type;
};
struct FrequencyBand{
	double from;
	double to;
	double step;
};
struct stationlist{
// 	string* stationid;
// 	int count;
	vector<string> stationid;
};
struct InterfStationList{
// 	int interstationcount;
// 	string* interfstationlist;
	vector<string> interfstationlist;
};
struct RectZone{
// 	int rectcount;
// 	CGeoRectangle* rectlist;
	vector<CGeoRectangle> rectlist;
};
struct PointZone{
// 	int pcount;
// 	CGeoPoint* pointlist;
	vector<CGeoPoint> pointlist;
};
struct CalPolygon{
	//int coordSys;
	double aslm;
	//vector<CGeoPoint> pointlist;
	CGeoPolygon polygon;
};
struct CalPolyLine{
	CGeoPolygon polyLine;
};

struct CalculateObj {
	//int space;
	int value;
	string type;
	CGeoRectangle Recttype;//矩形类别
	PointZone pointtype;//点类别
	CalPolygon polygontype;//多边形类别
	CalPolyLine polylinetype;//折线类别
	CGeoLine LineType;//线类型
	CGeoCircle CircleType;//

};
struct Location{
	long coordSys;
	double x;
	double y;
};
struct Height{
	double agl;
	double asl;
	string unit;
};
struct Freq{
	double value;
	string unit;
};
struct SenderParam{
	CGeoPoint location;
	//Location location;
	Height height;
	Freq freq;
};
struct ReceiverPoint
{
	long coordSys;
	double x;
	double y;
	double z;
};

struct FreeSpacePara{
	ScmFreeSpacePara freespaceparam;
	ScmClutter *pclutter;
	FreeSpacePara()
	{
		pclutter = NULL;
	}
	~FreeSpacePara()
	{
		if (pclutter != NULL)
		{
			delete pclutter;
		}
	}
	
};
struct OkuHataPara{
	ScmOkuHataPara okuHatapara;
	ScmClutter *pclutter;
	OkuHataPara(){
		pclutter = NULL;
	}
	~OkuHataPara()
	{
		if (pclutter != NULL)
		{
			delete pclutter;
		}
	}
};
struct ITU1546Para
{
	ScmITU1546Para itu1546param;
	ScmClutter *pclutter;
	ITU1546Para()
	{
		pclutter = NULL;
	}
	~ITU1546Para()
	{
		if (pclutter != NULL)
		{
			delete pclutter;
		}
	}
};
struct	ITU370Para{
	ScmITU370Para itu370param;
	ScmClutter *pclutter;
	ITU370Para()
	{
		pclutter = NULL;
	}
	~ITU370Para()
	{
		if (pclutter != NULL)
		{
			delete pclutter;
		}
	}
};
struct LONGLEYRICEPara{
	ScmClutter *pclutter;
	//.....
	LONGLEYRICEPara()
	{
		pclutter = NULL;
	}
	~LONGLEYRICEPara()
	{
		if (pclutter != NULL)
		{
			delete pclutter;
		}
	}
};
struct ITU533ShortWave{
	ScmClutter *pclutter;
	//.....
	ITU533ShortWave()
	{
		pclutter = NULL;
	}
	~ITU533ShortWave()
	{
		if (pclutter != NULL)
		{
			delete pclutter;
		}
	}
};
struct ITU530MicWave{
	ScmClutter *pclutter;
	//....
	ITU530MicWave()
	{
		pclutter = NULL;
	}
	~ITU530MicWave()
	{
		if (pclutter != NULL)
		{
			delete pclutter;
		}
	}
};
struct ITU618{
	ScmClutter *pclutter;
	//...
	ITU618()
	{
		pclutter = NULL;
	}
	~ITU618()
	{
		if (pclutter != NULL)
		{
			delete pclutter;
		}
	}
};
struct AeroNautical{
	ScmClutter *pclutter;
	//...
	AeroNautical()
	{
		pclutter = NULL;
	}
	~AeroNautical()
	{
		if (pclutter != NULL)
		{
			delete pclutter;
		}
	}
};

// struct TransModel{
// 	string modelid;
// 	string name;
// 	//double model_kfactor;
// 	double MinHillDisM;
// 	double MinTXDisM;
// 	int Difftype;
// 	ClutterParam clutterparam;
// };

struct RXAntHeight {
	double value;
	EHeightType type;
};
struct Frequency{
	double start;
	double end;
	string unit;
	double bandwidth;
};
struct ResultResolution{
	int xres;
	int yres;
};
struct TransModel{
	ETransModel transid;
	string transname;
};
typedef station STATIONList;

#endif