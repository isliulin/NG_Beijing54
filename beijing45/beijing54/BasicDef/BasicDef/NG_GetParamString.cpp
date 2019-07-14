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

//��ȡ��ǰʱ��
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
	sprintf(date,"%d��%02d��%02d�� %02d:%02d:%02d",pt->tm_year+1900,
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
		shapeStr = "��_";
		break;
	case CAL_LINE:
		shapeStr = "��_";
		break;
	case CAL_AREA_RECT:
		shapeStr = "����_";
		break;
	case CAL_AREA_POLYGON:
		shapeStr= "�����_";
		break;
	case CAL_AREA_CIRCLE:
		shapeStr= "Բ_";
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
// 		ResultTypestr = "·�����_";
// 		break;
// 	case eFieldSth:
// 		ResultTypestr = "��ǿ����_";
// 		break;
// 	case ePowerLevel:
// 		ResultTypestr = "���չ���_";
// 		break;
// 	case eSignalStrength:
// 		ResultTypestr = "�ź�ǿ��_";
// 		break;
// 	case ePowerFluxDensity:
// 		ResultTypestr = "����ͨ���ܶ�_";
// 		break;
// 	case eSpectrumPowerFluxDensity:
// 		ResultTypestr = "Ƶ�׹���ͨ���ܶ�_";
// 		break;
// 	case eRequiredPower:
// 		ResultTypestr = "���跢�书�ʼ���_";
// 		break;
// 	case eLosRestHeight:
// 		ResultTypestr = "������ٿ�����ͨ�ļ���_";
// 		break;
// 	case eCoAdjIntArea:
// 		ResultTypestr = "ͬ��Ƶ���ŷ������_";
// 		break;
// 	case eBlockInArea:
// 		ResultTypestr = "�������ŷ������_";
// 		break;
// 	case eProtectionBandIntOneByOne:
// 		ResultTypestr = "Ƶ�α���_";
// 		break;
// 	case eProtectionBandIntSum:
// 		ResultTypestr = "Ƶ�α����ۺϷ���_";
// 		break;
// 	case eCoverProbality:
// 		ResultTypestr = "���Ǹ���_";
// 		break;
// 	case eOpticalVisibility:
// 		ResultTypestr = "��ͨͼ_";
// 		break;
// 	case eRadarCrossSection:
// 		ResultTypestr = "�״��ʶ������_";
// 		break;
// 	case eRadarDetectProb:
// 		ResultTypestr = "�״�������_";
// 		break;
// 	case eSignalNoise:
// 		ResultTypestr = "CIֵ���_";//?????
// 		break;
// 	case eReceivedPower:
// 		ResultTypestr = "�̶����ջ��Ľ��ܹ���_";
// 		break;
// 	case eNetworkCoverage:
// 		ResultTypestr = "����_";
// 		break;
// 	case eMaxServerCount:
// 		ResultTypestr = "���������_";
// 		break;
// 	case eBestServer:
// 		ResultTypestr = "��ѷ���_";
// 		break;
// 	case eClearanceAngle:
// 		ResultTypestr = "��϶��_";
// 		break;
// 	case eFrequencyOccupy:
// 		ResultTypestr = "Ƶ��ռ��_";
// 		break;
// 	case eSpectrumAnalysis:
// 		ResultTypestr = "Ƶ�׷���_";
// 		break;
// 	case eCommunicationArea:
// 		ResultTypestr = "ͨ�ų�ͨ����_";
// 		break;
// 	case eMonitorCoverage:
// 		ResultTypestr = "��⸲��_";
// 		break;
// 	case eMonitorSiteSelection:
// 		ResultTypestr = "�������滮_";
// 		break;
// 	case eStationStatus:
// 		ResultTypestr = "̨վ����״̬_";
// 		break;
// 	case eProbality:
// 		ResultTypestr = "����_";
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
		transModelStr = "���ɿռ䴫��ģ��_";
		break;
	case eCost231Hata1:
		transModelStr = "Cost231 hata1ģ��_";
		break;
	case eITURP1546:
		transModelStr = "ITU1546ģ��_";
		break;
	case eITURP370:
		transModelStr = "ITU370ģ��_";
		break;
	case eLONGLEYRICE:
		transModelStr = "LONGLEY-RICE����ģ��_";
		break;
	case eITU533ShortWave:
		transModelStr = "ITU533 �̲�ģ��_";
		break;
	case eITU530MicWave:
		transModelStr = "ITU530 V10΢��ģ��_";
		break;
	case eITU618:
		transModelStr = "ITU618��˥ģ��_";
		break;
	case eAeroNautical:
		transModelStr = "����ģ��_";
		break;
	case eLOSModel:
		transModelStr = "��ͨģ��_";
		break;
	case eDiffractionModel:
		transModelStr = "����ģ��_";
		break;
	case eIRT3D:
		transModelStr = "IRT 3DModel����ģ��__";
		break;
	case eCost231Hata2:
		transModelStr = "Cost231Hata2����ģ��_";
		break;
	case eModifiedHata:
		transModelStr = "ModifiedHata����ģ��_";
		break;
	case eLeeModel:
		transModelStr = "Lee �ҵ����ģ��_";
		break;
	case eWalfishIkegami:
		transModelStr = "WalfishIkegamiModel����ģ��__";
		break;
	case eSkyWave:
		transModelStr = "�첨_";
		break;
	case eGroundWave:
		transModelStr = "�ز�_";
		break;
	case eITU452_10:
		transModelStr = "ITU452-10����ģ��_";
		break;
	case eITU526:
		transModelStr = "eITU526����ģ��_";
		break;
	case eSUIModel:
		transModelStr = "SUI����ģ��_";
		break;
	case eIRT3D_CELL:
		transModelStr = "eIRT3D_CELL����ģ��_";
		break;
	case eEgliModel:
		transModelStr = "eEgliModel����ģ��_";
		break;
	case eITU452:
		transModelStr = "ITU452����ģ��_";
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
			sprintf(charray,"����%d��%d��%d��",degree,min,sec);
		else
			sprintf(charray,"��γ%d��%d��%d��",degree,min,sec);
	}
	else if (value<0)
	{
		if(type&NG_LONGITUDE)
			sprintf(charray,"����%d��%d��%d��",degree,min,sec);
		else
			sprintf(charray,"��γ %d��%d��%d��",degree,min,sec);
	}
	else
	{
		sprintf(charray,"%d��%d��%d��",degree,min,sec);
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