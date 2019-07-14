#include "NG_GetParamString.h"
#include <sys/timeb.h>
#include <time.h>
#include <windows.h>
#include "GlobalDef.h"
// #include <io.h>
// #include <algorithm>

wchar_t* ConvertToWchar_t(const char *charStr)
{
	size_t strSize = strlen(charStr) + 1;
	wchar_t* Wstr = (wchar_t*)malloc( strSize * sizeof(wchar_t) );
	memset(Wstr, 0, sizeof(wchar_t)*strSize);
	MultiByteToWideChar(CP_ACP, 0, charStr, strSize, Wstr, strSize * sizeof(wchar_t));
	return Wstr;
}

char* ConvertToChar(const wchar_t *wcharStr)
{
	size_t wstrSize = WideCharToMultiByte(CP_ACP, 0, wcharStr, -1, NULL, 0, NULL, NULL) + 1;
	char* cstr = (char*)malloc( wstrSize * sizeof(char) );
	memset(cstr, 0, sizeof(char)*wstrSize);
	WideCharToMultiByte(CP_ACP, 0, wcharStr, -1, cstr, wstrSize, NULL, NULL);
	return cstr;
}

string Get_UnitStr(CalResult_Unit unit)
{
	string unitstr;
	switch (unit)
	{
	case CRUNIT_DB:
		unitstr = "DB";
		break;
	case CRUNIT_DBM:
		unitstr = "DBM";
		break;
	case CRUNIT_DBUV:
		unitstr = "DBUV";
		break;
	case CRUNIT_DBUV_PER_M:
		unitstr = "DBUV_PER_M";
		break;
	case CRUNIT_DBW_PER_M2:
		unitstr = "DBW_PER_M2";
		break;
	case CRUNIT_LOS_M:
		unitstr = "LOS_M";
		break;
	case CRUNIT_PERCENT:
		unitstr = "PERCENT";
		break;
	case CRUNIT_ANGLE:
		unitstr = "ANGLE";
		break;
	default:
		break;
	}
	return unitstr;
}

//获取当前时间
string Get_CurrentTimeString()
{
	timeb t;
	struct tm *pt;
	char date[200]={0};
	char millitm[200]={0};
	string datestr;
	ftime(&t);
	pt=localtime(&t.time);
	//strftime(date,127,"%Y%m%d_%H%M%S_",pt);
	//sprintf_s(millitm,127,"%d@",t.millitm);
	sprintf(date,"%d%02d%02d%02d%02d%02d%d",pt->tm_year+1900,
		pt->tm_mon+1,
		pt->tm_mday,
		pt->tm_hour,
		pt->tm_min,
		pt->tm_sec,
		t.millitm);
	datestr = date;
	return datestr;
}

std::string GetLocTime2Str()
{
	timeb t;
	struct tm *pt;
	char date[200]={0};
	ftime(&t);
	pt=localtime(&t.time);
	sprintf(date,"%d年%02d月%02d日 %02d:%02d:%02d",pt->tm_year+1900,
		pt->tm_mon+1,
		pt->tm_mday,
		pt->tm_hour,
		pt->tm_min,
		pt->tm_sec);

	std::string datestr=date;
	return datestr;
}

std::string GetLocTime2Str_UTF_8()
{
	char pTempChar[1024] = {0};
	string strTemp=GetLocTime2Str();
	if (!strTemp.empty())
	{
		wchar_t	wtempstr[250]={0};
		mbstowcs(wtempstr,strTemp.c_str(),249);
		UnicodeToUTF_8(pTempChar,wtempstr);
		strTemp = pTempChar;
	}
	else
		strTemp="";

	return strTemp;
}

string Get_ShapeStyle(CalResult_AreaType tStyle)
{
	string shapeStr;
	switch (tStyle)
	{
	case CAL_POINT:
		shapeStr = "点_";
		break;
	case CAL_LINE:
		shapeStr = "线_";
		break;
	case CAL_AREA_RECT:
		shapeStr = "矩形_";
		break;
	case CAL_AREA_POLYGON:
		shapeStr= "多边形_";
		break;
	case CAL_AREA_CIRCLE:
		shapeStr= "圆_";
		break;
	default:
		break;
	}
	return shapeStr;
}

// string Get_CoverResultTypeStr(ECoverResultType ResultType)
// {
// 	string ResultTypestr;
// 	switch (ResultType)
// 	{
// 	case ePathloss:
// 		ResultTypestr = "路径损耗_";
// 		break;
// 	case eFieldSth:
// 		ResultTypestr = "场强计算_";
// 		break;
// 	case ePowerLevel:
// 		ResultTypestr = "接收功率_";
// 		break;
// 	case eSignalStrength:
// 		ResultTypestr = "信号强度_";
// 		break;
// 	case ePowerFluxDensity:
// 		ResultTypestr = "功率通量密度_";
// 		break;
// 	case eSpectrumPowerFluxDensity:
// 		ResultTypestr = "频谱功率通量密度_";
// 		break;
// 	case eRequiredPower:
// 		ResultTypestr = "所需发射功率计算_";
// 		break;
// 	case eLosRestHeight:
// 		ResultTypestr = "还差多少可以视通的计算_";
// 		break;
// 	case eCoAdjIntArea:
// 		ResultTypestr = "同邻频干扰分析结果_";
// 		break;
// 	case eBlockInArea:
// 		ResultTypestr = "阻塞干扰分析结果_";
// 		break;
// 	case eProtectionBandIntOneByOne:
// 		ResultTypestr = "频段保护_";
// 		break;
// 	case eProtectionBandIntSum:
// 		ResultTypestr = "频段保护综合分析_";
// 		break;
// 	case eCoverProbality:
// 		ResultTypestr = "覆盖概率_";
// 		break;
// 	case eOpticalVisibility:
// 		ResultTypestr = "视通图_";
// 		break;
// 	case eRadarCrossSection:
// 		ResultTypestr = "雷达可识别截面积_";
// 		break;
// 	case eRadarDetectProb:
// 		ResultTypestr = "雷达侦测概率_";
// 		break;
// 	case eSignalNoise:
// 		ResultTypestr = "CI值结果_";//?????
// 		break;
// 	case eReceivedPower:
// 		ResultTypestr = "固定接收机的接受功率_";
// 		break;
// 	case eNetworkCoverage:
// 		ResultTypestr = "覆盖_";
// 		break;
// 	case eMaxServerCount:
// 		ResultTypestr = "最大服务个数_";
// 		break;
// 	case eBestServer:
// 		ResultTypestr = "最佳服务_";
// 		break;
// 	case eClearanceAngle:
// 		ResultTypestr = "余隙角_";
// 		break;
// 	case eFrequencyOccupy:
// 		ResultTypestr = "频率占用_";
// 		break;
// 	case eSpectrumAnalysis:
// 		ResultTypestr = "频谱分析_";
// 		break;
// 	case eCommunicationArea:
// 		ResultTypestr = "通信畅通覆盖_";
// 		break;
// 	case eMonitorCoverage:
// 		ResultTypestr = "监测覆盖_";
// 		break;
// 	case eMonitorSiteSelection:
// 		ResultTypestr = "监测区域规划_";
// 		break;
// 	case eStationStatus:
// 		ResultTypestr = "台站工作状态_";
// 		break;
// 	case eProbality:
// 		ResultTypestr = "概率_";
// 		break;
// 	default :
// 		break;
// 	}
// 	return ResultTypestr;
// }
// 
string Get_TransModelStr(ETransModel tTransModel)
{
	string transModelStr;
	switch (tTransModel)
	{
	case eFreeSpace:
		transModelStr = "自由空间传播模型_";
		break;
	case eCost231Hata1:
		transModelStr = "Cost231 hata1模型_";
		break;
	case eITURP1546:
		transModelStr = "ITU1546模型_";
		break;
	case eITURP370:
		transModelStr = "ITU370模型_";
		break;
	case eLONGLEYRICE:
		transModelStr = "LONGLEY-RICE传播模型_";
		break;
	case eITU533ShortWave:
		transModelStr = "ITU533 短波模型_";
		break;
	case eITU530MicWave:
		transModelStr = "ITU530 V10微波模型_";
		break;
	case eITU618:
		transModelStr = "ITU618雨衰模型_";
		break;
	case eAeroNautical:
		transModelStr = "航空模型_";
		break;
	case eLOSModel:
		transModelStr = "视通模型_";
		break;
	case eDiffractionModel:
		transModelStr = "绕射模型_";
		break;
	case eIRT3D:
		transModelStr = "IRT 3DModel传播模型__";
		break;
	case eCost231Hata2:
		transModelStr = "Cost231Hata2传播模型_";
		break;
	case eModifiedHata:
		transModelStr = "ModifiedHata传播模型_";
		break;
	case eLeeModel:
		transModelStr = "Lee 李建业传播模型_";
		break;
	case eWalfishIkegami:
		transModelStr = "WalfishIkegamiModel传播模型__";
		break;
	case eSkyWave:
		transModelStr = "天波_";
		break;
	case eGroundWave:
		transModelStr = "地波_";
		break;
	case eITU452_10:
		transModelStr = "ITU452-10传播模型_";
		break;
	case eITU526:
		transModelStr = "eITU526传播模型_";
		break;
	case eSUIModel:
		transModelStr = "SUI传播模型_";
		break;
	case eIRT3D_CELL:
		transModelStr = "eIRT3D_CELL传播模型_";
		break;
	case eEgliModel:
		transModelStr = "eEgliModel传播模型_";
		break;
	case eITU452:
		transModelStr = "ITU452传播模型_";
		break;
	default:
		break;
	}
	return transModelStr;
}



std::string Get_FunctionTypeID(ECalculateFunctionType functiontype)
{
	std::string Name;
	char temp[256];
	sprintf(temp,"%d_",functiontype);
	Name = temp;
	return Name;
}

string Get_CalculateTypeID(ECoverResultType resulttype)
{	
	std::string Name;
	char temp[256];
	sprintf(temp,"%d_",resulttype);
	Name = temp;
	return Name;
}

string Get_TransModelID(ETransModel model)
{
	std::string Name;
	char temp[256];
	sprintf(temp,"%d_",model);
	Name = temp;
	return Name;
}

string GetTransLongLat(double value,unsigned type)
{
	int min,sec,degree;
	degree = value;
	min = (value-degree)*60;
	sec = ((value-degree)*60-min)*60;

	string str;
	char charray[256]={0};
	if(value>0)
	{
		if(type&NG_LONGITUDE)
			sprintf(charray,"东经%d°%d′%d″",degree,min,sec);
		else
			sprintf(charray,"北纬%d°%d′%d″",degree,min,sec);
	}
	else if (value<0)
	{
		if(type&NG_LONGITUDE)
			sprintf(charray,"西经%d°%d′%d″",degree,min,sec);
		else
			sprintf(charray,"南纬 %d°%d′%d″",degree,min,sec);
	}
	else
	{
		sprintf(charray,"%d°%d′%d″",degree,min,sec);
	}
	str=charray;
	return str;
}

string GetTransLongLat_ESWN(double value, unsigned type)
{
	int min,degree;
	double sec;
	degree = value;
	min = (value-degree)*60;
	sec = ((value-degree)*60.0-min)*60.0;

	string str;
	char charray[256]={0};
	if(value>0)
	{
		if(type&NG_LONGITUDE)
			sprintf(charray,"%dE%d %.2f",degree,min,sec);
		else
			sprintf(charray,"%dN%d %.2f",degree,min,sec);
	}
	else if (value<0)
	{
		if(type&NG_LONGITUDE)
			sprintf(charray,"%dW%d %.2f",degree,min,sec);
		else
			sprintf(charray,"%dS%d %.2f",degree,min,sec);
	}
	else
	{
		sprintf(charray,"%d %d %.2f",degree,min,sec);
	}
	str=charray;
	return str;
}

string GetTransLongLat_UTF_8(double value,unsigned type)
{
	char pTempChar[1024] = {0};
	char strTemp[1024]={0};
	sprintf(strTemp,"%.6f(%s)",value,GetTransLongLat(value,type).c_str());
	wchar_t	wtempstr[250]={0};
	mbstowcs(wtempstr,strTemp,249);
	UnicodeToUTF_8(pTempChar,wtempstr);

	return pTempChar;
}