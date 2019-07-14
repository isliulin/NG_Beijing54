#ifndef NG_PARA_H
#define NG_PARA_H
#pragma once
#include <string>
#include <time.h>
#include "../DataModel/EnumDef.h"



#define NG_LONGITUDE 0x01
#define NG_LATITUDE 0x02

using namespace std;

wchar_t* ConvertToWchar_t(const char *charStr);

char* ConvertToChar(const wchar_t *wcharStr);

string Get_UnitStr(CalResult_Unit unit);

std::string GetLocTime2Str();

std::string GetLocTime2Str_UTF_8();

string Get_CurrentTimeString();

string Get_ShapeStyle(CalResult_AreaType tStyle);

// string Get_CoverResultTypeStr(ECoverResultType ResultType);

string Get_TransModelStr(ETransModel tTransModel);

string Get_TransModelID(ETransModel model);

string Get_CalculateTypeID(ECoverResultType resulttype);

std::string Get_FunctionTypeID(ECalculateFunctionType functiontype);

/*string Get_NewFileName(string filepath,CalResult_AreaType ShapeType,ECoverResultType ResultType,ETransModel model);*/

string GetTransLongLat(double value,unsigned type);

string GetTransLongLat_ESWN(double value, unsigned type);

string GetTransLongLat_UTF_8(double value,unsigned type);

#endif