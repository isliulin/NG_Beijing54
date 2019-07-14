#include "NG_ErrorCode.h"
#include <stdio.h>
//#include <string.h>
//typedef struct stErrCodeTable
//{
//    NG_INT32 lErrCode;
//	NG_UINT8 acErrInfo[100];
//}NG_STR_ERR_CODE_TABLE;
//
//NG_STR_ERR_CODE_TABLE g_astErrCodeInfoTable[] = 
//{
//	/************BEGIN: 公共模块错误码**************************/
//	{NG_UNKNOWN_ERROR, "Unknown error"},
//	{NG_SUCCESS, "success"},
//	{NG_PARAMWRONG, "Parameter is wrong"},
//	{NG_MEMORYWRONG, "Fail to application new memory"},
//	{POINTER_CAN_NOT_BE_EMPTY, "Pointer can not be empty"},
//	{THE_PARAMETER_FORMAT_IS_ILLEGAL, "The parameter format is illegal"},
//	{THE_PARAMETER_RANGE_IS_ILLEGAL, "The parameter range is illegal"},
//	{FAIL_TO_APPLICATION_NEW_MEMORY, "Fail to application new memory"},
//	{NG_NOTGETRESULT, "Can not be get result"},
//	{NG_NOTCALCULATE, "Calculate wrong"},
//	
//	/*********************文件错误码****************************************/
//	{FAIL_TO_OPEN_FILE, "Fail to open file"},
//	{THE_FILE_IS_NOT_EXIST, "The file is not exist"},
//	{THE_FILE_NAME_TOO_LONG, "The file name is too long"},
//    {FAIL_TO_GET_FILE_NAME, "Fail to get file name"},
//	{FAIL_TO_WRITE_FILE, "Fail to write file"},
//	{FAIL_TO_CREATE_FILE, "Fail to create file"},
//	{FILE_PATH_NULL_ERROR, "The file path is null"},
//
//	/**********BEGIN: 数据压缩和数据解压模块的错误码***********/
//	{FAIL_TO_RESOLVE_DECOMPRESS_FILE, "Fail to resolve decompress file"},
//	{THE_COMPRESS_SRC_FILE_NOT_OPEN, "The source compress file isn't opened"},
//	{THE_DECOMPRESS_SRC_FILE_NOT_OPEN, "The source decompress file isn't opened"},
//	{DATE_COMPRESS_ABNORMAL, "Date compress abnormal"},
//	{DATE_DECOMPRESS_ABNORMAL, "Date decompress abnormal"},
//	{DATE_DECOMPRESS_NORMAL_END, "Date decompress is normal ended"},
//	{DATE_COMPRESS_IS_NOT_NEEDED, "The date need not resolve"},
//	{DATE_DECOMPRESS_PARA_UNREASONABLE, "The decompress para is unreasonable"},
//	{FAIL_TO_GET_FILE_NAME, "Fail to get file name"},
//	/**********END: 数据压缩和数据解压模块的错误码***********/
//};
//
//NG_INT32 NG_GetErrorCodeInfo(NG_INT32 lErrCode, NG_UINT8 *&pcErrInfo)
//{
//	NG_UINT32 ulTableNum = sizeof(g_astErrCodeInfoTable)/sizeof(NG_STR_ERR_CODE_TABLE);
//
//	for (NG_UINT32 i = 0; i < ulTableNum; i++)
//	{
//		if (lErrCode == g_astErrCodeInfoTable[i].lErrCode)
//		{
//            pcErrInfo = g_astErrCodeInfoTable[i].acErrInfo;
//			return VOS_OK;
//		}
//	}
//
//	return VOS_ERR;
//}

#define  ERROR_ENGLISH

#ifdef  ERROR_ENGLISH
const char * NG_GetErrorCodeMessage(int nCode)
{
	switch(nCode)
	{
	case NG_SUCCESS:return "Succeed";
	//base
	//case NG_PARAMWRONG: return "Parameter is invalid";
	case NG_MEMORYWRONG: return "No enough memory";
	case POINTER_CAN_NOT_BE_EMPTY:return "Not a valid point, maybe no enough memory" ;
	case THE_PARAMETER_FORMAT_IS_ILLEGAL: return "The parameter's format is illegal";
	case THE_PARAMETER_RANGE_IS_ILLEGAL: return  "The parameter's range is illegal";
	case FAIL_TO_APPLICATION_NEW_MEMORY: return "Fail to application new memory";
	case NG_NOTGETRESULT:return "no good way can do";
	case NG_NOTCALCULATE:return "no good parameters for calculate";
	case NG_NO_CALCULATE_MODEL: return "No this trans-model";
	case GEOSHAPE_ERROR: return "Geo Shape is illegal";
	case INVALID_XMLFILE: return "Invalid xml format";
	case UNIT_NO_EXIST: return "Unit is not exist";
	case HEIGHT_TYOE_ERROR: return "Invalid height_type,only 0-2 is right";
	case NG_NO_RESULT_FILE: return "result filename is not exit";
	case NG_CLIENTVERSION_NOTRANSMODE:return "Client version unsupport the functional";
	case NG_FUNCTIONMODEL_NOTRANSMODE:return "The functional unsupport the transmodel";
	case NG_DB_ERROR:return "Database error";
	case NO_AREA_INFO:return "No area infomation";
	case NO_MATCH_RESULTFILE:return "The Result_Files and the Calculate_Stations does not match";
	case NG_FUNCTIONMODEL_UNSUPPORT_FREESPACE: return "The functional unsupport the transmodel freespace";
	//
	//#define FILE_BASE_ERROR					 1000
	case FAIL_TO_OPEN_FILE: return	"Not a valid file";
	case THE_FILE_IS_NOT_EXIST : return "File is not exist";
	case THE_FILE_NAME_TOO_LONG: return "File's is too long";
	case FAIL_TO_GET_FILE_NAME : return "File is empty";
	case FAIL_TO_WRITE_FILE : return "Can not write to file";
	case FAIL_TO_CREATE_FILE :return  "Can not create file";
	case FILE_PATH_NULL_ERROR: return "The file path is empty";
    case FAIL_TO_READ_FILE: return "Fail to read file";
    case FAIL_TO_DELETE_FILE: return "Fail to delete file";
	case LACK_DATA_FILE: return "Lack effective data file";
	case FILE_DATA_ERROR: return  "File content error";

	
	//#define DONGLE_BASE_ERROR   2000	
	case NG_LICENSEEXPIRED:
	case NG_OPENLICENSEFILEFAIL:
	case NG_TIMEMODIFIED:
	case NG_LICENSEWRONG:
	case NG_LICENSEDONGLENOTMATCH:
	case NG_NORIGHTDONGLE: 
	case NG_DONGLECHECK_EXCEPTION:
	case NG_NOSERVERDONGLE: return "Check wrong";
	case NG_TRANSMODELWRONG: return "Not a valid trans-model";
	case NG_NOMODELLICENSE: return "Not a valid model";
	case NG_NO_RIGHT_CMDONGLE: return "Codemeter check wrong, get the detail information from log file";
	//case NG_LICENSEEXPIRED:
	//case NG_OPENLICENSEFILEFAIL:
	//case NG_TIMEMODIFIED:  return "Check wrong";
	//case NG_TRANSMODELWRONG:"Not a valid trans-model";
	//case NG_LICENSEWRONG: return "Check wrong";
	
	//#define MAP_BASE_ERROR   3000
	case NG_NOAPPROPRIATEMAP: return "Map's coordination is not match";
	case NG_MAPCOORDNOTMATCH:  return "Map's coordination is not match";
	case NG_MAPPARAMWRONG: return "Map's parameters have valid value";
	case NG_STATIONMAPNOTMATCH: return "Station is not in map";
	case NG_POINTMAPNOTMATCH: return "Point is not in map";
	case NG_GETPROFILEWRONG: return "Can not get the profile of map";
	case  NG_CALCULATE_SHAP_ERROR:return "Not a valid calculation shape";
	case NG_Resolution_NOTMATCH:return "Resolution is not match";
	case NG_NO_MAP_DATA:return "No Map Data";

		//#define STATION_BASE_ERROR   4000
	case ONE_STATION_IS_NOT_EXIST:return "Station is not in database";
	case NO_STATION: return "NO stations,maybe stations are not in database";
	case NO_TX_STATION: return "No TX-Stations,maybe stations are not in database";
	case NO_RX_STATION: return "No RX-Stations,maybe stations are not in database" ;
	case NO_MONITOR_STATION: return "No Monitor Station ,maybe stations are not in database";
	case TX_RX_SITE_NO_MATCH: return "Link stations are not match";
	case NO_INT_STATION : return "No interference sites,need't calculate";
	case NO_ASSIGN_STATION:return "No statin need to be assigned";
	case SQL_STATION_PARAM_ERROR:return "Database station parameter error";
	//#define TRANSMODEL_BASE_ERROR   5000
	case TRANSMODEL_NO_EXIST: return "Invalid trans-model";
	case TRANSMODEL533LIB_EXEC_FAIL: return "533 lib call failed";
	case TRANSMODEL_FREQ_OUTOFRANGE: return "Frequency out of transmodel range";
	case TRNAMODEL_HEIGHT_OUTOFRANGE: return "Tx or rx antenna height out of transmodel range";
	case TRANSMODEL_FREQ_BAND_ERROR: return "The Frequency-Band param is error";
    case TRANSMODEL_NOT_SAME: return "Transmodel param is not same";
	case NO_TRANSMODEL_PARAM: return "Transmodel param is null";
	case POLYLINE_TOO_FEW_POINT: return "Polyline too few point";
	case NG_POINTER_CAN_NOT_BE_EMPTY: return "The path of the digital map(propagation model depends) is null";
	case NG_FAIL_TO_READ_FILE: return "Read the digital map(propagation model depends) fail";

	case NG_PropModel_NOProjPath: return "No input project path in propagation model";



	
	//#define CALIBRATIO_BASE_ERROR   6000

	case CALIBRATION_FREQ_OUTOFRANGE: return "Frequency out of calibration model range";
	case CALIBRATION_FAILED:		  return "Model calibration failed";

	//#define INTERFERENCE_BASE_ERROR	7000
	case NO_MATCH_FREQ: return "rx's frequency is not match with tx's frequency,,need't calculate";
    case NO_NEW_INTSTATION: return "no new interference station,need't calculate";
	//#define EMCCAL_BASE_ERROR   8000
	case NO_SUPPORTED_RESULT_TYPE: return "";

	//#define PERFROMANCE_BASE_ERROR   9000

	//#define LINKPROFILE_BASE_ERROR   10000
	case FRESNELNUM_ERROR: return "Not a valid Fresnel number";
	case LINK_TOO_NEAR: return "The points' distance is too little for map";
	case NO_LINK_POINTS: return "No Link";
	//
	//#define COMPRESS_BASE_ERROR	12000
	case FAIL_TO_RESOLVE_DECOMPRESS_FILE: return "Can't decompress to file"; 
	case  THE_COMPRESS_SRC_FILE_NOT_OPEN:  return "Can't open Compress file";
	case THE_DECOMPRESS_SRC_FILE_NOT_OPEN : return "Can't open decompress to file";
	case DATE_COMPRESS_ABNORMAL: return "Abnormal for compress";
	case DATE_DECOMPRESS_ABNORMAL: return "Abnormal for decompress";
	case DATE_DECOMPRESS_NORMAL_END: return "Decompress ok";
	case DATE_COMPRESS_IS_NOT_NEEDED : return "Not compress or decompress the data";
	case DATE_DECOMPRESS_PARA_UNREASONABLE: return "Decompress is not match for the data";

		//
	//#define SIGNAL_BASE_ERROR   13000
	case FAIL_TO_GET_RADAR_FEATURE_BY_DATE_SHORT: return "Too short data";
	case POS_INFO_EXCESS_MAX_NUM_BY_TEA_EN: return "Too many pluses number than max"; 
	case POS_INFO_EXCESS_MAX_NUM_BY_FREQ :return "Too many frequencies than max"  ;  
	case  COMBINE_POS_NUM_EXCESS_MAX_NUM : return "Too may pluses for combine";
	case THE_IQ_DATA_LENGTH_IS_NULL : return "No IQ data";
	case THE_THRESHOLD_IS_NOT_SET : return "No threshold setting";
	case THE_CARR_OR_SAM_FREQ_IS_NOT_SET: return "No sample frequency setting";
	case  THE_SYMBOL_RATE_IS_NOT_SET: return "No symbol rate setting";
	case THE_SAMPLE_FREQ_IS_ILLEGAL : return "The sample frequency is too lower";
	case FAIL_TO_READ_CSV_FILE	: return "Can't open SCV file";
	case THE_RADAR_DATA_LENGTH_IS_SHORT  : return "radar data is too short"; 
	case THE_FEATURE_RESULT_FILE_PATH_IS_NOT_SET  :return "No result's path setting";
	case FAIL_TO_OPEN_FEATURE_RESULT_FILE :return "Can't open result file";
	case  THE_FILE_PATH_IS_TOO_LONG:  return "File path too long";
	case  THE_SAMPLE_RATE_IS_NULL  : return "No sample frequency setting";
	case THE_SIGNAL_TYPE_IS_NULL  : return "No single type setting";  
	case  THE_MODEL_FILE_PATH_IS_NOT_SET: return "No model path setting" ;	
	case THE_FEATURE_FILE_PATH_IS_NOT_SET : return "No data path setting" ; 
	case THE_RECOGNITION_RESULT_FILE_PATH_IS_NOT_SET : return "No result path setting";
	case FAIL_TO_OPEN_RECOGNITION_RESULT_FILE : return "Can't open result file";
	case THE_SRC_FILE_PATH_IS_NOT_SET : return "No source file setting"; 
	case THE_FFT_DATE_IS_NULL: return "The FFT data is NULL"; 
	case FAIL_TO_FFT_TRANSFORM: return "Fail to FFT transform"; 
	case FAIL_TO_CAL_FEATURE_PARA: return "Fail to cal signal feature"; 
	case FAIL_TO_OPEN_MODEL_FILE: return "Fail to open model file"; 
	case FAIL_TO_RESOLVE_STATION_TYPE_TABLE: return "Fail to resolve station table"; 
	case NO_SPECIAL_STATION_ID_IN_TYPE_TABLE: return "No special station ID in table"; 
	case THE_STATION_TABLE_DATA_IS_NULL: return "The station table data is NULL"; 
	case THE_LIB_AND_STATION_TABLE_NOT_MATCH: return "The model and station table is not match"; 
	case FAIL_TO_RESOLVE_SAMPLE_LIB_FILE: return "Fail to resolve sample model file"; 
    case NO_FP_SAMPLE_LIB_FOR_MONI_STATION: return "No Fp lib file in the moni station";
    case FAIL_TO_READ_STATION_DATEBASE_INFO: return"Fail to read station database";
	case FAIL_TO_CREATE_SPECTRUM_LIB_DATE: return "Fail to create spectrum model data"; 
	case FAIL_TO_GET_SPECIAL_SPECTRUM_DATE: return "Fail to get special spectrum data"; 
	case THE_INPUT_PARA_MEMORY_IS_SHORT: return "The input para memory is short"; 
	case NO_SPECIAL_FREQ_POINT: return "No special freq point"; 
    case ERROR_TO_TIME_RANGE: return "The time range is illegal"; 
    case ERROR_TO_FREQ_RANGE: return "The freq range is illegal"; 
    case FAIL_TO_READ_SCAN_FILE: return "Fail to read scan file"; 
    case NO_SPECTRUM_LIB_FILE_IN_MONI_STATION: return "No spectrum lib file in the moni station"; 
    
    case NO_VALID_DIAGNOSIS_PARA: return "No valid diagnosis para"; 
    case DIAGNOSIS_RESULT_IS_NULL: return "The diagnosis result is NULL";
    case THE_TEXT_DATA_BASE_IS_NULL: return "The data base is NULL";
    case THE_SRC_RECORD_VALUE_INVALID: return "The src record value is invalid";
    case THE_BATCH_FILE_INVALID: return "The batch file is invalid";
    case THE_DIAGNOSIS_LEN_TOO_LONG: return "The diagnosis length too long";
    case THE_SRC_FILE_PATH_IS_NULL: return "The src file path is null";
    case THE_RECORD_DATA_IS_NULL: return "The record data is null";
    case FAIL_TO_READ_TEXT_DATA_BASE: return "Fail to read text data base";
    case FAIL_TO_WRITE_TEXT_DATA_BASE: return "Fail to write text data base";
    case TIME_BGEIN_END_INVALID: return "Time error from begin to end";
    case THE_TIME_FORMAT_INVALID: return "The time format is invalid";
    case THE_TIME_VALUE_INVALID: return "The time value is invalid";
    case FREQ_BGEIN_END_INVALID: return "Freq error from begin to end";
    
	//#define FUSION_BASE_ERROR 		   (14000)	  
	case FUSION_INTERPOLATION_ERROR:   return "Area interpolation error in monitor data fusion.";
	case FUSION_REVISE_ERROR:		  return "Interpolation calibration error in monitor data fusion.";

	//#define FREQPROTECT_BASE_ERROR   15000
	case NG_NOPROTECTIONINT :return "Station's frequency is not in band, not calculate for protected";

	
	//#define FREQASSIGN_BASE_ERROR   16000
		//#define FREQASSIGN_BASE_ERROR   16000
    case FREQASSIGN_TOO_FEW_FREQ: return "Too few frequency";
	case FREQASSIGN_QUALITY_BAD: return "Bad quality";
	case FREQASSIGN_FREQOFF_SMALL: return "Can't satisfy the frquency offset";
	case FREQASSIGN_CALORDER_ERROR: return "the order of calling is wrong";
	case FREQASSIGN_NO_CANDIDATEPREQ: return "Missing Candidate Frequency";

	//#define FREQCONFILICT_BASE_ERROR	 17000

	//#define DEPOLY_BASE_ERROR 	18000

	case PARAM_CLUSTTER_FREQUENCY_WRONG : return "The frequency number is not match for cluster number";
	case PLAN_TIME_ERROR: return "Error for planning time";
	case  NOT_COVERAGE: return "No good way for coverage the area";
	case UNSUPPORTED_MAP_COORD : return "The map's coordination is not match";
	case NOT_AVAILABLE_ROAD : return "No available road in the selection area"; 
	case  NO_COMMAND_DATE_AVAILABLE: return "No available monitor command, maybe the date is not match";
	case COMMAND_AND_WORKMODEL_NOT_MATCH: return "The monitor command number is not match the work mode";
	case COMMAND_PRIORITY_ERROR: return "The monitor command Priority is wrong,only 0-5 is right";
	case  CAL_PRIORITY_TYPE_ERROR:return "Invalid Priority-Type,only 0-1 is right";
	case TIME_TYPEL_NO_EXIST: return "Invalid Time-Type,only 0-4 is right";
	case WORK_MODEL_TYPE_ERROR: return "Invalid Monitor-work-model,only 1-3 is right";
	case MAX_SITE_COUNT_ERROR:return "The Max-Sit-Count Param is wrong";
	case COVERAGE_PER_ERROR: return "The target Coverage Param is wrong";
	case SIGNAL_TYPE_ERROR: return "The Signal-type Param is wrong,only 0-1 is right";
	case MONITOR_TIME_ERROR: return "The monitor-time Param is wrong";
	case RADAR_DETECT_PROB_ERROR: return "Listening Porbability Parameter Error";
	case RADAR_FALSE_PROB_ERROR: return "False Alarm Probability Parameter Error";
	case RADAR_MINRCS_ERROR: return "Parameter Error of Minimum Section Area";

	//#define  PROTECTION_BASE_ERROR   19000
	case NONOPROTECTIONFILE :return "No Protectedfile ";
	//#define  ISOSURFACE_BASE_ERROR   20000  

	//#define INTERMODULATION_BASE_ERROR  21000
	case INTERMODULATIONORDER_ERROR : return "Only 3 and 5 is right for inter-modulation order";

	//#define PROJECTCONFIG_BASE_ERROR	22000
	case DATABASE_CONFIG_ERROR: return "Config database error";
	case MAP_CONFIG_ERROR : return "Config map error";
	case USER_CAL_PARAM_ERROR : return "Config file error";
	case TRANSMODEL_CONFIG_ERROR: return "Config trans-model error";
    case PATHLOSS_PATH_CONFIG_ERROR:return "Config pathloss path error ";
	case USER_TERMINATED_ERROR: return "User terminated process!";

	
	//#define HARMONICSINT_BASE_ERROR  23000
	case HARMONICSPARAM_ERROR: return "Harmonics Param error";


	//BoundaryCoordinate_BASE_ERROR 24000
	case NO_INTERFERENCE: return "no interference";

	//TDOA_BASE_ERROR 25000
	case STATIONS_NOT_ENOUGH: return "There is not enough stations, num of monitor stations provided must be above 3";
	case SIGNAL_NO_CROSSRELATION: return " Signals of stations received have no relativity";
	case TIME_NO_MIXED: return "Monitor Stations failed to sync time";
	case FILE_NUM_NOT_EQUAL_STATION: return "Num of the data files is not equal stations' num, every monitor station provided should provide a data file";
	case UNSUPPORT_LOCATIONTYPE: return "Unsupport location type";
	case RESULT_BAD:return"Signal is too bad and result have no reference value";

	//AOA_BASE_ERROR 26000
	case NO_SOURCE_IN_MONITOR_AREA: return "There is no specified signal in monitor area.";
	


	//SOURCETRACK_BASE_ERROR 27000
	case STATION_NOT_RECEIVE_SIGNAL: return "Station can not monitor this freq signal ";


	//SOURCEANALYSIS_BASE_ERROR 28000

	case SOURCEAREAR_COMPUTE_PARAM_ERROR: return "Param error";
	case SOURCEAREAR_MONITOR_DATA_ERROR: return "Monitor file error";
	case SOURCEAREAR_UNSUPPORT_DATATYPE: return "only support powerlevel type";
	case SOURCEAREAR_DATA_NO_MATCH_EROR: return "monitor file is not match with monitor station";
	
	//SITESELECTION_BASE_ERROR 29000
	case EVALUATECOVERRADIUS_ERROR: return "calculate cover radius error,maybe transmodel is not suitable";
	case SITESELECTION_NO_VALIDPOINT: return "Too few candidate point,may be the water is too much";
  

	////SITEWORKSTATUS_BASE_ERROR 30000

	//SPECTRUMANALYSIS_BASE_ERROR 31000

	//SIGNALSUPPERSSION_ERROR  32000
	case NO_MATCH_INTSTATION: return "no interfer station is int frequency band ,need't Supper";
	case NO_EXIST_INTER: return "There is no need to suppress interference";
	case NO_SUPPORTED_MULTIPLE_FREQ: return "Multiple frequency bands are not supported";
	case NO_POWERLIST: return "No Candidate Power List";
	case NUMBER_CROSS_THE_BOUNDARY: return "Cross the Boundary";
	case NO_COVERAGE: return "Cannot reach the coverage";

   //33000
   case NO_TIMEINFO: return "No time infomation";
   case NO_SIMULATORINFO: return "No simulation result";
   case MONITOR_FREQ_TOO_LESS :return "Too few frequency in Monitor file ";
   case NO_COVERED_STATION:return "No covered station through radius sifting";
	   //  34000
   case READ_ROADVECTORFILE_ERROR: return "failed to read the road vector file";
   case NO_SUPPORTED_CALCULATEAREA: return "Unsupported Area Type";
   case GET_ROADVECTOR_ERROR: return "failed to get the boundary_road vector";

	//35000
   case NO_EXIST_STRONG_RADIATION: return "There is no strong radiation";

   //36000
   case FREQUENCY_OUTOF_MONITORDATA: return "Out of frequency range";
   case TIME_OUTOF_MONITORDATA: return "Out of time range";
   case TOO_FEW_DATARECORD: return "Too few records";
   case PREPROCESS_ERROR: return "Preprocess Monitor data file error";
   
   case INVALIDSCANFORMAT: return "Invalid scan file format";

   case STANDDATAFREQ_NOTMATCH:return "Stand scan file information is not match";
   case FILTER_NOISE_FREQUENCY_ERROR:return "frequency is not same in Stand scan file information  ";


   //37000
   case  DRIVER_TEST_POINT_NOT_ENOUGTH : return "The discrete point num is not enougth";
	 //38000;
   case NO_TARGET_FREQ:return "Monitor file has no datas in target FreqBand ";
	   //3900
   case TX_STATION_NO_COVERAGE: return "The pre reception desk is not covered in calculation area";
   case NEW_STATION_NO_COVERAGE: return "The new station is not covered in calculation area";
	   //44000
   case NG_UPDATE_FEEDER_STATUS_ERROR: return "Update feeder finished interference process failed!";
	   //48000
   case NG_NO_CELL_STATION: return "No cell in polygon in DB";
   case NG_NO_NEIGHBOR_CELL_STATION: return "No neighbor cell in DB";
   case NG_READVECTORFROMDB_ERROR: return "Polygon Error";
   case NG_AUTOMANUAL_PARAM_ERROR: return "Auto or manual param Error";
   case NG_MANUALSITENEIGHBORXML_ERROR: return "Manual xml Error";
   case NG_NEIGHBORNETTYPE_ERROR: return "Cell type param Error";
   case NG_NEIGHBORGAINLOSS_ERROR: return "Receive gain or loss param Error";
   case NG_NEIGHBORMAXNUM_ERROR: return "Max Neighbor Number param Error";
   case NG_READANTENNA_ERROR: return "Read Antenna from database Error";
	default:
		return "Unknown error.Maybe Parameter is not match";
	}
}

#else

const char * NG_GetErrorCodeMessage(int nCode)
{
	switch(nCode)
	{
	case NG_SUCCESS:return "成功";
	//base
	//case NG_PARAMWRONG: return "参数错误";
	case NG_MEMORYWRONG: return "内存不足";
	case POINTER_CAN_NOT_BE_EMPTY:return "无效指针,可能内存不足" ;
	case THE_PARAMETER_FORMAT_IS_ILLEGAL: return "参数格式非法";
	case THE_PARAMETER_RANGE_IS_ILLEGAL: return  "参数范围非法";
	case FAIL_TO_APPLICATION_NEW_MEMORY: return "内存不足";
	case NG_NOTGETRESULT:return "现有参数下，没有合适的解决方案";
	case NG_NOTCALCULATE:return "未进行有效计算";
	case NG_NO_CALCULATE_MODEL: return "没有计算模型";
	case GEOSHAPE_ERROR: return "Geo Shape 类型错误";
	case INVALID_XMLFILE: return "无效的xml格式";
	case UNIT_NO_EXIST: return "单位非法,只支持0~9";
	case HEIGHT_TYOE_ERROR: return "无效的高度类型";
	case NG_NO_RESULT_FILE: return "没有结果文件";
	case NG_CLIENTVERSION_NOTRANSMODE:return "客户未授权该传播模型";
	case NG_FUNCTIONMODEL_NOTRANSMODE:return "当前功能模块不支持该传播模型";
    case NG_DB_ERROR:return "数据库错误";
	case NO_AREA_INFO:return "没有指定区域信息";
	case NO_MATCH_RESULTFILE: return "结果文件数和对应的计算台站数不匹配";
	case NG_FUNCTIONMODEL_UNSUPPORT_FREESPACE: return "当前功能模块不支持自由空间传播模型";
	//
	//#define FILE_BASE_ERROR                    1000
	case FAIL_TO_OPEN_FILE: return  "打开文件失败";
	case THE_FILE_IS_NOT_EXIST : return "文件不存在";
	case THE_FILE_NAME_TOO_LONG: return "文件名太长";
	case FAIL_TO_GET_FILE_NAME : return "无法获取结果文件名";
	case FAIL_TO_WRITE_FILE : return "写文件失败";
	case FAIL_TO_CREATE_FILE :return  "创建文件失败";
	case FILE_PATH_NULL_ERROR: return "文件路径为空";
    case FAIL_TO_READ_FILE: return "读文件失败";
    case FAIL_TO_DELETE_FILE: return "删除文件失败";
	case LACK_DATA_FILE: return "缺失有效的数据文件";
	case FILE_DATA_ERROR: return  "文件内容错误";

	
	//#define DONGLE_BASE_ERROR   2000	
	case NG_LICENSEEXPIRED:
	case NG_OPENLICENSEFILEFAIL:
	case NG_TIMEMODIFIED:
	case NG_LICENSEWRONG:
	case NG_LICENSEDONGLENOTMATCH:
	case NG_NORIGHTDONGLE: 
	case NG_DONGLECHECK_EXCEPTION:
	case NG_NOSERVERDONGLE: return "狗检验错误";
	case NG_TRANSMODELWRONG: return "传播模型未授权";
	case NG_NOMODELLICENSE: return "功能模块未授权";
	case NG_TRANSMODELPARAMCREATE_ERROE:return "创建传播模型参数失败";
	//case NG_LICENSEEXPIRED:
	//case NG_OPENLICENSEFILEFAIL:
	//case NG_TIMEMODIFIED:  return "Check wrong";
	//case NG_TRANSMODELWRONG:"Not a valid trans-model";
	//case NG_LICENSEWRONG: return "Check wrong";
	
	//#define MAP_BASE_ERROR   3000
	case NG_NOAPPROPRIATEMAP: return "没有合适坐标系的地图";
	case NG_MAPCOORDNOTMATCH:  return "地图坐标系与计算要求不匹配";
	case NG_MAPPARAMWRONG: return "地图参数有错误";
	case NG_STATIONMAPNOTMATCH: return "台站超出计算地图边界，请重新配置计算地图";
	case NG_POINTMAPNOTMATCH: return "计算点不在地图内";
	case NG_GETPROFILEWRONG: return "获取profile出错，可能的原因接收和发射点位置几乎相同";
	case  NG_CALCULATE_SHAP_ERROR:return "计算区域类型错误";
	case NG_Resolution_NOTMATCH:return "分辨率不匹配";
	case NG_NO_MAP_DATA:return "没有地图数据";

		//#define STATION_BASE_ERROR   4000
	case ONE_STATION_IS_NOT_EXIST:return "某个台站不存在,可能台站不在数据库中";
	case NO_STATION: return "没有一个台站,可能台站不在数据库中";
	case NO_TX_STATION: return "没有一个发射机,可能台站不在数据库中";
	case NO_RX_STATION: return "没有一个接收机，可能台站不在数据库中" ;
	case NO_MONITOR_STATION: return "没有监测站，可能台站不在数据库中";
	case TX_RX_SITE_NO_MATCH: return "链路分析中接收站和发射站不匹配";
	case NO_INT_STATION : return "没有干扰台,不需要计算";
	case NO_ASSIGN_STATION:return "没有指配站";
	case SQL_STATION_PARAM_ERROR:return "数据库台站参数错误";
	//#define TRANSMODEL_BASE_ERROR   5000
	case TRANSMODEL_NO_EXIST: return "无效的传播模型";
	case TRANSMODEL533LIB_EXEC_FAIL: return "533库调用失败";
	case TRANSMODEL_FREQ_OUTOFRANGE: return "频率超出选定的传播模型的适用范围";
	case TRNAMODEL_HEIGHT_OUTOFRANGE: return "接收端或者发射端天线高度超出选定的传播模型适用范围";
	case TRANSMODEL_FREQ_BAND_ERROR: return "频率带宽参数错误";
	case TRANSMODEL_NOT_SAME: return "内部传播模型参数不一致";
	case NO_TRANSMODEL_PARAM: return "内部传播模型参数为空";
	case POLYLINE_TOO_FEW_POINT: return "折线点少于2个";

	//#define TRANSMODEL533_BASE_ERROR   5500
	case TRANS533_IONOS_ERROR:  return "533 模型读取二进制数据失败";
	case TRANS533_REC_TOO_CLOSE_ERROR: return "533 模型接收点和发射点距离过近";
	case TRANS533_ANT_ELEANGLE_TOO_SMALL_ERROR: return "533 模型天线仰角太小，小于设定的门限值"; //天线仰角太小，小于门
	case TRANS533_DAY_NOELAYER_ERROR: return "533 模型因夜间或者距离过远，不考虑E层场强"; 
	case TRANS533_RESULTTYPE_NOTSUPPORT: return "533 模型目前只支持场强计算";

	//#define CALIBRATIO_BASE_ERROR   6000

	case CALIBRATION_FREQ_OUTOFRANGE: return "频率超出选定的传播模型的适用范围";
	case CALIBRATION_FAILED:          return "模型校正未能正确执行";

	//#define INTERFERENCE_BASE_ERROR   7000
	case NO_MATCH_FREQ: return "接收站和发射站频率不匹配,无需计算干扰";
	case NO_NEW_INTSTATION: return "没有新增干扰站,无需计算干扰";

	//#define EMCCAL_BASE_ERROR   8000
    case NO_SUPPORTED_RESULT_TYPE: return "不支持的结果类型";
	//#define PERFROMANCE_BASE_ERROR   9000

	//#define LINKPROFILE_BASE_ERROR   10000
	case FRESNELNUM_ERROR: return "菲涅尔区号不存在，只支持0~5";
	case LINK_TOO_NEAR: return "链路距离太近";
	case NO_LINK_POINTS: return "没有链路";

	
	//11000
	case NG_NO_FREQOCCUPY_INTER: return"不存在频率上的干扰情况";
	//#define COMPRESS_BASE_ERROR   12000
	case FAIL_TO_RESOLVE_DECOMPRESS_FILE: return "解析数据压缩文件失败"; 
	case  THE_COMPRESS_SRC_FILE_NOT_OPEN:  return "数据压缩源文件未打开";
	case THE_DECOMPRESS_SRC_FILE_NOT_OPEN : return "数据解压源文件未打开";
	case DATE_COMPRESS_ABNORMAL: return "数据压缩失败";
	case DATE_DECOMPRESS_ABNORMAL: return "数据解压异常";
	case DATE_DECOMPRESS_NORMAL_END: return "数据解压成功";
	case DATE_COMPRESS_IS_NOT_NEEDED : return "当前数据无需执行数据压缩或解压时未使用解压算法";
	case DATE_DECOMPRESS_PARA_UNREASONABLE: return "当前数据解压参数不合理";

		//
	//#define SIGNAL_BASE_ERROR   13000
	case FAIL_TO_GET_RADAR_FEATURE_BY_DATE_SHORT: return " 雷达数据流太短，无法提取特征";
	case POS_INFO_EXCESS_MAX_NUM_BY_TEA_EN: return "根据teager能量计算出的有效脉冲个数超过最大值"; 
	case POS_INFO_EXCESS_MAX_NUM_BY_FREQ :return "根据瞬时频率计算出的有效脉冲个数超过最大值"  ;  
	case  COMBINE_POS_NUM_EXCESS_MAX_NUM : return "合并所有位置信息的个数超过最大值";
	case THE_IQ_DATA_LENGTH_IS_NULL : return "IQ数据个数为空";
	case THE_THRESHOLD_IS_NOT_SET : return "门限参数未设置";
	case THE_CARR_OR_SAM_FREQ_IS_NOT_SET: return "载波频率或者采样频率未设置";
	case  THE_SYMBOL_RATE_IS_NOT_SET: return "符号速率未设置";
	case THE_SAMPLE_FREQ_IS_ILLEGAL : return "采样频率过低";
	case FAIL_TO_READ_CSV_FILE  : return "读取CSV文件头失败";
	case THE_RADAR_DATA_LENGTH_IS_SHORT  : return " 雷达样本数据流过短,导致提取的特征无法建模 ，无法处理"; 
	case THE_FEATURE_RESULT_FILE_PATH_IS_NOT_SET  :return "特征集文件路径未设置";
	case FAIL_TO_OPEN_FEATURE_RESULT_FILE :return "打开特征集文件失败";
	case  THE_FILE_PATH_IS_TOO_LONG:  return "文件名路径长度太长 ";
	case  THE_SAMPLE_RATE_IS_NULL  : return "未设置采样率";
	case THE_SIGNAL_TYPE_IS_NULL  : return "未设置信号类型";  
	case  THE_MODEL_FILE_PATH_IS_NOT_SET: return "样本库文件路径未设置" ;  
	case THE_FEATURE_FILE_PATH_IS_NOT_SET : return "信号特征文本 路径未设置" ; 
	case THE_RECOGNITION_RESULT_FILE_PATH_IS_NOT_SET : return "识别结果文件路径未设置";
	case FAIL_TO_OPEN_RECOGNITION_RESULT_FILE : return "打开识别结果文件失败";
	case THE_SRC_FILE_PATH_IS_NOT_SET : return "原始信号文件路径未设置"; 
    case THE_FFT_DATE_IS_NULL: return "未进行FFT变换"; 
	case FAIL_TO_FFT_TRANSFORM: return "FFT失败"; 
	case FAIL_TO_CAL_FEATURE_PARA: return "计算通信信号特征失败"; 
	case FAIL_TO_OPEN_MODEL_FILE: return "打开样本库文件失败"; 
	case FAIL_TO_RESOLVE_STATION_TYPE_TABLE: return "解析台站类型表失败"; 
	case NO_SPECIAL_STATION_ID_IN_TYPE_TABLE: return "台站类型表无对应台站ID，请确认是否修改过台站类型表"; 
	case THE_STATION_TABLE_DATA_IS_NULL: return "台站类型表内数据为空"; 
	case THE_LIB_AND_STATION_TABLE_NOT_MATCH: return " 台站类型表与样本库数据不匹配"; 
	case FAIL_TO_RESOLVE_SAMPLE_LIB_FILE: return "解析样本库数据失败"; 
    case NO_FP_SAMPLE_LIB_FOR_MONI_STATION:return "该监测站未训练指纹样本库";
    case FAIL_TO_READ_STATION_DATEBASE_INFO: return"读取台站数据库失败";
	case FAIL_TO_CREATE_SPECTRUM_LIB_DATE: return "无法创建频谱样本库数据 "; 
	case FAIL_TO_GET_SPECIAL_SPECTRUM_DATE: return "输入的扫频数据无指定参数的频谱信息"; 
	case THE_INPUT_PARA_MEMORY_IS_SHORT: return "输入参数内存不足"; 
	case NO_SPECIAL_FREQ_POINT: return "未找到指定频点"; 
    case ERROR_TO_TIME_RANGE: return "时间范围非法"; 
    case ERROR_TO_FREQ_RANGE: return "频率范围非法"; 
    case FAIL_TO_READ_SCAN_FILE: return "读取扫频文件失败"; 
    case NO_SPECTRUM_LIB_FILE_IN_MONI_STATION: return "该监测站还未创建频谱库"; 

    case NO_VALID_DIAGNOSIS_PARA: return "未发现有效的诊断参数"; 
    case DIAGNOSIS_RESULT_IS_NULL: return "诊断结果为空";
    case THE_TEXT_DATA_BASE_IS_NULL: return "文本干扰知识库为空";
    case THE_SRC_RECORD_VALUE_INVALID: return "原始记录的值为无效值";
    case THE_BATCH_FILE_INVALID: return "批量文件内容非法";
    case THE_DIAGNOSIS_LEN_TOO_LONG: return "字段长度太长";
    case THE_SRC_FILE_PATH_IS_NULL: return "记录文件路径不能为空";
    case THE_RECORD_DATA_IS_NULL: return "记录为空";
    case FAIL_TO_READ_TEXT_DATA_BASE: return "读取文本干扰数据库失败";
    case FAIL_TO_WRITE_TEXT_DATA_BASE: return "写文本干扰数据库失败";
    case TIME_BGEIN_END_INVALID: return "起止时间非法";
    case THE_TIME_FORMAT_INVALID: return "时间格式非法";
    case THE_TIME_VALUE_INVALID: return "时间内容无效";
    case FREQ_BGEIN_END_INVALID: return "起止频率非法";

    
	//#define FUSION_BASE_ERROR            (14000)    
	case FUSION_INTERPOLATION_ERROR:   return "区域插值错误";
	case FUSION_REVISE_ERROR:         return "插值校正错误";

	//#define FREQPROTECT_BASE_ERROR   15000
	case NG_NOPROTECTIONINT :return "台站频率不在保护频段范围内";

	
	//#define FREQASSIGN_BASE_ERROR   16000
    case FREQASSIGN_TOO_FEW_FREQ: return "候选频点太少";
	case FREQASSIGN_QUALITY_BAD: return "候选频点质量太差";
	case FREQASSIGN_FREQOFF_SMALL: return "不能满足频差要求";
	case FREQASSIGN_CALORDER_ERROR: return "频率指配流程顺序错误";
	case FREQASSIGN_NO_CANDIDATEPREQ: return "缺失候选频点";
	
	//#define FREQCONFILICT_BASE_ERROR   17000

	//#define DEPOLY_BASE_ERROR     18000

	case PARAM_CLUSTTER_FREQUENCY_WRONG	: return "用频个数和聚类数设置错误";
	case PLAN_TIME_ERROR: return "计划时间错误";
	case  NOT_COVERAGE: return "最大布站数也达不到覆盖";
	case UNSUPPORTED_MAP_COORD : return "不支持的坐标系，在路线规划中，只支持经纬度坐标";
	case NOT_AVAILABLE_ROAD	: return "区域内没有可行的道路"; 
	case  NO_COMMAND_DATE_AVAILABLE: return "没有可用的监测要求，可能原因：设置的部署日期与监测要求提取日期不符";
	case COMMAND_AND_WORKMODEL_NOT_MATCH: return "监测要求数和工作模式不匹配";
	case COMMAND_PRIORITY_ERROR: return "监测优先级错误，只支持0~5";
	case  CAL_PRIORITY_TYPE_ERROR:return "计算监测优先级类型错误，只支持0~1";
	case TIME_TYPEL_NO_EXIST: return "时间类型类型错误，只支持0~4";
	case WORK_MODEL_TYPE_ERROR: return "监测站工作模型类型错误，只支持1~3";
	case MAX_SITE_COUNT_ERROR:return "允许的最大布站数错误，只支持1~200";
	case COVERAGE_PER_ERROR: return "目标覆盖错误，只支持1~3";
	case SIGNAL_TYPE_ERROR: return "信号类型错误，只支持1~3";
	case MONITOR_TIME_ERROR: return "监测时间错误，必须按指定格式输入，时间跨度最大是两年";
	case RADAR_DETECT_PROB_ERROR: return "雷达侦听概率参数错误，只支持0-100";
	case RADAR_FALSE_PROB_ERROR: return "雷达虚警概率参数错误，只支持0-100";
	case RADAR_MINRCS_ERROR: return "雷达最小目标截面积参数错误";

	//#define  PROTECTION_BASE_ERROR   19000
    case NONOPROTECTIONFILE :return "保护率文件不存在";
	//#define  ISOSURFACE_BASE_ERROR   20000  
	case CANNOTEXTRACTCONTOUR: return "无法提取等值线";

	//#define INTERMODULATION_BASE_ERROR  21000
	case INTERMODULATIONORDER_ERROR : return "互调阶数错误，只支持3和5";

	//#define PROJECTCONFIG_BASE_ERROR  22000
	case DATABASE_CONFIG_ERROR: return "数据库配置错误";
	case MAP_CONFIG_ERROR : return "地图配置错误";
	case USER_CAL_PARAM_ERROR : return "用户设置的参数文件错误";
	case TRANSMODEL_CONFIG_ERROR: return "传播模型初始化失败";
	case PATHLOSS_PATH_CONFIG_ERROR:return "路径损耗目录配置错误";

	//#define HARMONICSINT_BASE_ERROR  23000
	case HARMONICSPARAM_ERROR: return "谐波参数错误，只支持2~13";


	//BoundaryCoordinate_BASE_ERROR 24000
	case NO_INTERFERENCE: return "边界与覆盖轮廓没有交集，不存在干扰";
    case AREA_INCLUDE :return "两区域是子集关系";

		
	//TDOA_BASE_ERROR 25000
	case STATIONS_NOT_ENOUGH: return "监测站的个数必须3个及以上";
	case SIGNAL_NO_CROSSRELATION: return " 信号相关性不够";
	case TIME_NO_MIXED: return "监测站设备同步时间失败";
	case FILE_NUM_NOT_EQUAL_STATION: return "文件和监测站数目不匹配";
	case UNSUPPORT_LOCATIONTYPE: return "不支持的定位方式";
    case RESULT_BAD: return "信号源太差，不满足定位要求，无法定位";

	//AOA_BASE_ERROR 26000
	case NO_SOURCE_IN_MONITOR_AREA: return "在监测范围内无指定频率的未知发射源";
	case AZIMUTH_CALCULATE_EXCEPTION: return "方位角计算值异常";


	//SOURCETRACK_BASE_ERROR 27000
	case STATION_NOT_RECEIVE_SIGNAL: return "信号强度太小 ";


	//SOURCEANALYSIS_BASE_ERROR 28000

	case SOURCEAREAR_COMPUTE_PARAM_ERROR: return "参数错误";
	case SOURCEAREAR_MONITOR_DATA_ERROR: return "监测数据文件读取失败";
    case SOURCEAREAR_UNSUPPORT_DATATYPE: return "监测数据文件只支持power类型";
    case SOURCEAREAR_DATA_NO_MATCH_EROR: return "监测数据文件和监测站不匹配";
	
	//SITESELECTION_BASE_ERROR 29000
	case EVALUATECOVERRADIUS_ERROR: return "计算覆盖半径失败,可能选择的传播模型不适用";
    case SITESELECTION_NO_VALIDPOINT: return "合适的候选位置太少，可能水域太多";

	////SITEWORKSTATUS_BASE_ERROR 30000

	//SPECTRUMANALYSIS_BASE_ERROR 31000

	//SIGNALSUPPERSSION_ERROR  32000
	case NO_MATCH_INTSTATION: return "没有一个压制设备在待压制频段范围内，无需计算";
	case NO_COVERAGE: return "达不到覆盖";
	case NO_EXIST_INTER: return "不存在干扰区域，无需布站压制";
	case NO_SUPPORTED_MULTIPLE_FREQ: return "不支持同时压制多个频段";
	case NO_POWERLIST: return "没有候选功率";
	case NUMBER_CROSS_THE_BOUNDARY: return "数据发生越界";

		//33000
    case NO_TIMEINFO: return "没有时间信息";
    case NO_SIMULATORINFO: return "没有仿真结果";
    case MONITOR_FREQ_TOO_LESS :return "监测数据文件频点太少";
	case NO_COVERED_STATION: return "没有台站覆盖计算区域,可能是筛选距离过小导致";

		//
	case READ_ROADVECTORFILE_ERROR: return "读取路径矢量文件失败";
	case NO_SUPPORTED_CALCULATEAREA: return "不支持的区域类型";
	case GET_ROADVECTOR_ERROR: return "获取边界矢量失败，可能是计算区域与边界线无交集";

		//35000
	case NO_EXIST_STRONG_RADIATION: return "不存在强辐射，没有健康隐患";


   //36000
    case FREQUENCY_OUTOF_MONITORDATA: return "设置的频率范围不在监测数据的频段范围内";
	case TIME_OUTOF_MONITORDATA: return "设置的时间范围不在监测数据的时间范围内";
    case TOO_FEW_DATARECORD: return "监测数据记录太短";
	case PREPROCESS_ERROR: return "监测数据预处理出错";
	case INVALIDSCANFORMAT: return "无效的扫频文件格式";
	case STANDDATAFREQ_NOTMATCH:return "国家扫频文件名频率信息与数据信息不一致";
	case FILTER_NOISE_FREQUENCY_ERROR:return "国家扫频文件去噪时,每条记录对应频点不一致";
	case STANDCHECKCODE_ERROR: return "国家扫频文件数据校验码错误";
    case NG_MONITORFILE_OPEN_ERROR: return "无法读取指定的监测扫频文件";


		//37000
	case DRIVER_TEST_POINT_NOT_ENOUGTH : return "用于插值的离散点数目太少";
		//38000;
	case NO_TARGET_FREQ:return "扫频文件没有目标频段数据";
	case TX_STATION_NO_COVERAGE:return "欲收台站对计算区域无覆盖,无需计算";
	case NEW_STATION_NO_COVERAGE:return "新建台站对计算区域无覆盖,无需计算";
		//41000
	case NG_WRONGFIELDINEXCELS: return "EXCEL中固定字段错误";
	case NG_RADIO_ASSETS_CLASSIFICATION: return "无线电资产分类字段错误";
	case NG_ASSETS_CLASS_NAME: return "资产分类字段错误";
	case NG_ASSETS_SUBCLASS: return "资产子类字段错误";
	case NG_ACQUISITION_METHOD: return "取得方式字段错误";
	case NG_PROCUREMENT_ORGANIZATION_FORM: return "采购组织形式字段错误";
	case NG_PROPERTY_RIGHTS_FORM: return "产权形式字段错误";
	case NG_USE_STATUS: return "使用状况字段错误";
	case NG_USE_DIRECTION: return "使用方向字段错误";
	case NG_VALUE_TYPE: return "价值类型字段错误";
	case NG_IMPORT_OR_DOMESTIC: return "进口/国产字段错误";
	case NG_STATE_FINANCIAL_APPROPRIATION: return "国家财政性拨款字段错误";
	case NG_LOCAL_FINANCIAL_APPROPRIATION: return "地方财政性拨款字段错误";
	case NG_ASSETS_USE_STATUS: return "资产状态字段错误";

	default:
		return "未知错误，也许参数配置不正确";
	}

}
#endif  

