#pragma once
#include <string>
#include <time.h>
#include "../DataModel/EnumDef.h"

#define NG_LONGITUDE 0x01
#define NG_LATITUDE 0x02

using namespace std;

string Get_UnitStr(CalResult_Unit unit);

std::string GetLocTime2Str();

string Get_CurrentTimeString();

std::string GetmillitmTimeString();

string Get_ShapeStyle(CalResult_AreaType tStyle);

// string Get_CoverResultTypeStr(ECoverResultType ResultType);

string Get_TransModelStr(ETransModel tTransModel);

string Get_TransModelID(ETransModel model);

string Get_CalculateTypeID(ECoverResultType resulttype);

std::string Get_FunctionTypeID(ECalculateFunctionType functiontype);

/*string Get_NewFileName(string filepath,CalResult_AreaType ShapeType,ECoverResultType ResultType,ETransModel model);*/

string GetTransLongLat(double value,unsigned type);