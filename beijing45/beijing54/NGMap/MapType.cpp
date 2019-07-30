#include <stdio.h>
#include "NGMapGeo.h"
#include "MapType.h"

struct MapTypeItem 
{
	int nType;			//地貌类别编号
	const char *pText ;	//地貌类别字符串
};

static MapTypeItem MapDataType[] = 
{
	NG_MT_BOROUGH,			"Borough",
	NG_MT_CONDUCTIVITY,		"Conductivity",
	NG_MT_ORTHO_FOTO,		"OrthoFoto",
	NG_MT_POPULATION,		"Population",
	NG_MT_ROAD_MAPS,		"RoadMap",
	NG_MT_TOPO,				"Topo",
	NG_MT_MORPH,			"Morpho",
	NG_MT_TRAFFIC,			"Traffic",
	NG_MT_POPDENS,			"PopDens",
	NG_MT_BUILDING_HEIGHT,	"Building_Height",
	NG_MT_CUSTOM,			"Custom",
	NG_MT_UNKNOWN_MAP_TYPE,"Unknown_Data_Type"
};
#define NUMMAPDATATYPE ((int) (sizeof MapDataType / sizeof MapDataType [0]))

int GetDataTypeFromStr(const std::string &strDataType)
{
	std::string strTemp;
	for(int xx = 0;xx < NUMMAPDATATYPE;xx ++)
	{
		strTemp = std::string(MapDataType[xx].pText);
		if (strTemp == strDataType)
			return MapDataType[xx].nType;
	}
	return NG_MT_UNKNOWN_MAP_TYPE;
}

std::string GetStrFromDataType(int DataType)
{
	for(int xx = 0;xx < NUMMAPDATATYPE;xx ++)
	{
		if (MapDataType[xx].nType == DataType)
			return std::string(MapDataType[xx].pText);
	}
	return std::string("");
}