
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

// #define  ERROR_ENGLISH

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
	case NG_FREQUENCY_PARAM_ERROR: return "The frequency_parameter's range is illegal";
	case NG_USER_TERMINATE: return "user Stop!";
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




	
	//#define CALIBRATIO_BASE_ERROR   6000

	case CALIBRATION_FREQ_OUTOFRANGE: return "Frequency out of calibration model range";
	case CALIBRATION_FAILED:		  return "Model calibration failed";

	//#define INTERFERENCE_BASE_ERROR	7000
	case NO_MATCH_FREQ: return "rx's frequency is not match with tx's frequency,,need't calculate";
    case NO_NEW_INTSTATION: return "no new interference station,need't calculate";
	//#define EMCCAL_BASE_ERROR   8000
	case NO_SUPPORTED_RESULT_TYPE: return "";
	case NO_STATION_IN_SHAP: return "There is not station in the area,no need to calculate";
	case NUSUPPORT_BAND_NULL:return "Power spectral flux density is not supported for 0 band calculations";

	//#define PERFROMANCE_BASE_ERROR   9000
	case NO_PERFORMANCE_COVERAGE: return "There is not Exist Coverage";

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
	case SIGNAL_TOO_BAD: return "Signal is too bad to cause that the result is not exact ";
	case LESS_3_STATION_RECEIVE_SIGNAL:return "Num of stations received signal less than 3";
	case LOCATION_ERROR: return "The coordinate of the monitor is wrong";

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
    case SITESELECTION_NO_SITE: return "No site";

	////SITEWORKSTATUS_BASE_ERROR 30000

	//SPECTRUMANALYSIS_BASE_ERROR 31000
	case NO_MATCH_RESULTTYPE: return "No match resulttype";


	//SIGNALSUPPERSSION_ERROR  32000
	case NO_MATCH_INTSTATION: return "no interfer station is int frequency band ,need't Supper";
	case NO_EXIST_INTER: return "There is no need to suppress interference";
	case NO_SUPPORTED_MULTIPLE_FREQ: return "Multiple frequency bands are not supported";
	case NO_POWERLIST: return "No Candidate Power List";
	case NUMBER_CROSS_THE_BOUNDARY: return "Cross the Boundary";
	case NO_COVERAGE: return "Cannot reach the coverage";
	case NO_EXIST_DEPLOYMENT_AREA: return "There is no deployment_area";

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

   case STANDDATAFREQ_NOTMATCH:return "Stand scan file frequency information is not match";
   case FILTER_NOISE_FREQUENCY_ERROR:return "frequency is not same in Stand scan file information  ";
   case STANDCHECKCODE_ERROR: return "Stand scan file checkcode is error ";

   //37000
   case  DRIVER_TEST_POINT_NOT_ENOUGTH : return "The discrete point num is not enougth";
	 //38000;
   case NO_TARGET_FREQ:return "Monitor file has no datas in target FreqBand ";
	   //3900
   case TX_STATION_NO_COVERAGE: return "The pre reception desk is not covered in calculation area";
   case NEW_STATION_NO_COVERAGE: return "The new station is not covered in calculation area";
   case NO_COADJ_TXSTATION_COVERAGEAREA: return "No sites in coverage area,need't calculate";
   case NEW_STATION_NO_INTER: return "The new station is not interfere in calculation area";

	   //41000 
   case NG_NO_FREQASSIGN: return "Lack of frequency_assign results"; 
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
	case NG_FREQUENCY_PARAM_ERROR: return "频率参数范围非法";
	case NG_NULL_PROJECTGUID:      return "Project GUID为空";
    case NG_XML_MARK_ERROR: return "xml 不是流也不是文件";
	case NG_USER_TERMINATE: return "用户终止操作";
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
	case XML_PARAM_WRONG: return "XML文件参数错误";
	case CSV_FORMAT_WRONG: return "CSV文件格式错误";
	case INVALID_MSI_OR_PAT_FILE: return "无效的天线文件";
	case FILE_FORMAT_ERROR: return "文件格式错误";


	
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
	case NG_STATIONMAPNOTMATCH: return "台站超出计算地图边界";
	case NG_POINTMAPNOTMATCH: return "计算点不在地图内";
	case NG_GETPROFILEWRONG: return "获取profile出错，可能的原因接收和发射点位置几乎相同";
	case  NG_CALCULATE_SHAP_ERROR:return "计算区域类型错误";
	case NG_Resolution_NOTMATCH:return "分辨率不匹配";
	case NG_NO_MAP_DATA:return "没有地图数据";
	case NG_NO_VECTOR_MAP_DATA: return "缺少矢量地图";
	case NG_MAP_READ_WRONG: return "读取地图失败";
	case NG_NO_INDOOR_TEMPLATE_MAP: return "缺少室内模板地图";
	case NG_CalculateResolution_Error: return "计算分辨率有误";

		//#define STATION_BASE_ERROR   4000
	case ONE_STATION_IS_NOT_EXIST:return "某个台站不存在,可能台站不在数据库中";
	case NO_STATION: return "没有一个台站,可能台站不在数据库中";
	case NO_TX_STATION: return "没有一个发射机,可能台站不在数据库中";
	case NO_RX_STATION: return "没有一个接收机，可能台站不在数据库中" ;
	case NO_MONITOR_STATION: return "没有监测节点，可能信息不在数据库中";
	case TX_RX_SITE_NO_MATCH: return "链路分析中接收站和发射站不匹配";
	case NO_INT_STATION : return "没有干扰台,不需要计算";
	case NO_ASSIGN_STATION:return "没有指配站";
	case SQL_STATION_PARAM_ERROR:return "数据库台站参数错误";
	case XML_STATION_PARAM_ERROR:return "台站参数错误";
		//
	case LOCATION_PARAMETER_RANGE_IS_ILLEGAL:  return "台站位置参数范围非法";
	case HEIGHT_PARAMETER_RANGE_IS_ILLEGAL:  return "计算高度参数范围非法 只支持(0~1000)m";
	case POWER_PARAMETER_RANGE_IS_ILLEGAL:return "发射功率参数范围非法 只支持(-4~90)dBm";
	case THRESHOLDDBM_PARAMETER_RANGE_IS_ILLEGAL: return "计算门限参数范围非法 只支持(-120~-50)dBm";
	case THRESHOLDDBUVM_PARAMETER_RANGE_IS_ILLEGAL: return "计算门限参数范围非法";
	case CITHRESHOLD_PARAMETER_RANGE_IS_ILLEGAL:  return "计算CI门限参数范围非法 只支持(-50~50)dB";
	case AZIMUTH_PARAMETER_RANGE_IS_ILLEGAL	:  return "方位角参数范围非法 只支持(0~360)度";
	case DOWNTILT_PARAMETER_RANGE_IS_ILLEGAL:  return "下倾角参数范围非法 只支持(-90~90)度";
	case GAIN_PARAMETER_RANGE_IS_ILLEGAL: return "天线增益范围非法 只支持(-50~50)dBi";
	case LOSS_PARAMETER_RANGE_IS_ILLEGAL:  return "天线损耗范围非法 只支持(-100~100)dB";
	case FREQUENCY_PARAMETER_RANGE_IS_ILLEGAL:  return "频率范围非法 只支持(0.3~40)MHz";
	case XML_RXHEIGHT_PARAM_ERROR	:return "xml中接收高度参数错误";
	//#define TRANSMODEL_BASE_ERROR   5000
	case TRANSMODEL_NO_EXIST: return "无效的传播模型";
	case TRANSMODEL533LIB_EXEC_FAIL: return "533库调用失败";
	case TRANSMODEL_FREQ_OUTOFRANGE: return "频率超出选定的传播模型的适用范围";
	case TRNAMODEL_HEIGHT_OUTOFRANGE: return "接收端或者发射端天线高度超出选定的传播模型适用范围";
	case TRANSMODEL_FREQ_BAND_ERROR: return "频率带宽参数错误";
	case TRANSMODEL_NOT_SAME: return "内部传播模型参数不一致";
	case NO_TRANSMODEL_PARAM: return "内部传播模型参数为空";
	case POLYLINE_TOO_FEW_POINT: return "折线点少于2个";
	case TRANSMODEL_NOT_SUPPORT_RESULT_TYPE: return "传播模型不支持当前结果类型";
	case STRAIGHT_LINE_IDENTICAL: return "线矢量重合(传播模型)";
	case STRAIGHT_LINE_PARALLEL: return "线矢量平行(传播模型)";
	case STRAIGHT_LINE_VERTICAL: return "线矢量与y轴垂直(传播模型)";
	case NO_TRANSMODEL: return "未指定计算传播模型";
	
		//#define TRANSMODEL533_BASE_ERROR   5500
	case TRANS533_IONOS_ERROR:  return "533 模型读取二进制数据失败";
	case TRANS533_REC_TOO_CLOSE_ERROR: return "533 模型接收点和发射点距离过近";
	case TRANS533_ANT_ELEANGLE_TOO_SMALL_ERROR: return "533 模型天线仰角太小，小于设定的门限值"; //天线仰角太小，小于门
	case TRANS533_DAY_NOELAYER_ERROR: return "533 模型因夜间或者距离过远，不考虑E层场强"; 
	case TRANS533_RESULTTYPE_NOTSUPPORT: return "533 模型目前只支持场强计算";
	case TRANS533_MAP_NOTSUPPORT: return "533 模型目前只支持经纬度地图计算";
	case TRANS533_LATITUDE_OUT: return "533 模型计算位置的纬度超过[-90，90]范围";
	case TRANS533_UTCHOUR_OUT: return "533 模型计算UTC时间超过[0，24]范围";
	
	//#define CALIBRATIO_BASE_ERROR   6000

	case CALIBRATION_FREQ_OUTOFRANGE: return "频率超出选定的传播模型的适用范围";
	case CALIBRATION_FAILED:          return "模型校正未能正确执行";
	case CALIBRATION_TWO_FEW_POINT:   return "模型校正文件中点数太少";

	//#define INTERFERENCE_BASE_ERROR   7000
	case NO_MATCH_FREQ: return "接收站和发射站频率不匹配,无需计算干扰";
	case NO_NEW_INTSTATION: return "没有新增干扰站,无需计算干扰";

	//#define EMCCAL_BASE_ERROR   8000
    case NO_SUPPORTED_RESULT_TYPE: return "不支持的结果类型";
	case NO_STATION_IN_SHAP: return "区域内没有满足要求的计算台站，无需计算";
	case NUSUPPORT_BAND_NULL: return "不支持0带宽计算功率谱通量密度";
	//#define PERFROMANCE_BASE_ERROR   9000
	case NO_PERFORMANCE_COVERAGE: return "收发站在选定的矢量区域内无覆盖，无需计算";

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
    case NO_FP_SAMPLE_LIB_FOR_MONI_STATION:return "该监测节点未训练指纹样本库";
    case FAIL_TO_READ_STATION_DATEBASE_INFO: return"读取台站数据库失败";
	case FAIL_TO_CREATE_SPECTRUM_LIB_DATE: return "无法创建频谱样本库数据 "; 
	case FAIL_TO_GET_SPECIAL_SPECTRUM_DATE: return "输入的扫频数据无指定参数的频谱信息"; 
	case THE_INPUT_PARA_MEMORY_IS_SHORT: return "输入参数内存不足"; 
	case NO_SPECIAL_FREQ_POINT: return "未找到指定频点"; 
    case ERROR_TO_TIME_RANGE: return "时间范围非法"; 
    case ERROR_TO_FREQ_RANGE: return "频率范围非法"; 
    case FAIL_TO_READ_SCAN_FILE: return "读取扫频文件失败"; 
    case NO_SPECTRUM_LIB_FILE_IN_MONI_STATION: return "该监测节点还未创建频谱库"; 
	case NO_SPECTRUM_LIB_FILE_THIS_TIME_RANGE: return "该时段缺失背景频谱库";
	case NO_SPECTRUM_LIB_FILE_THIS_FREQ_RANGE: return "该频段内未创建频谱库";	
	case NO_ABNORMAL_FREQ: return "此次监管无异常";
	case TRAIN_SCAN_FILE_ERROR:return "训练过程中发现扫频数据中存在异常频点";
	case TRAIN_SCAN_FILE_TIME_ERROR: return "训练时扫频数据时间信息有误";
	case DELETE_TRAIN_FILE_FAILED: return "删除训练文件失败";
	case TRAIN_STOP:return "停止训练";
	case SUPERVISE_DATA_SHORT:return "监管数据少于100条";

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

	case NG_OPENSPECTRUMDBWRONG: return "打开数据库失败";
	case NG_READSPECTRUMDBWRONG:return "读背景频谱库失败";
	case NG_WRITESPECTRUMDBWRONG:return "写背景频谱库失败";
	case NG_GETDATABASEERROR:return "获取数据库连接失败";

    
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
	case FREQASSIGN_OCCUPYFILE_ERROR: return "未读取到扫频占用度分析文件";
	
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
	case WORK_MODEL_TYPE_ERROR: return "监测节点工作模型类型错误，只支持1~3";
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

	//#define INTERMODULATION_BASE_ERROR  21000
	case INTERMODULATIONORDER_ERROR : return "互调阶数错误，只支持3和5";

	//#define PROJECTCONFIG_BASE_ERROR  22000
	case DATABASE_CONFIG_ERROR: return "数据库配置错误";
	case MAP_CONFIG_ERROR : return "地图配置错误";
	case USER_CAL_PARAM_ERROR : return "用户设置的参数文件错误";
	case TRANSMODEL_CONFIG_ERROR: return "传播模型初始化失败";
	case PATHLOSS_PATH_CONFIG_ERROR:return "路径损耗目录配置错误";
	case BUSINESS_BAND_CONFIG_ERROR: return "业务频段路径配置错误";
	case BORDER_COORDINATION_CONFIG_ERROR: return "协调协议路径配置错误";
	case MAX_COVERAGE_RADIUS_CONFIG_ERROR: return "不同功率频率对应的最大半径文件配置错误";
	case LICENSECHECK_PATH_CONFIG_ERROR: return "狗检测文件配置错误";

	//#define HARMONICSINT_BASE_ERROR  23000
	case HARMONICSPARAM_ERROR: return "谐波参数错误，只支持2~13";


	//BoundaryCoordinate_BASE_ERROR 24000
	case NO_INTERFERENCE: return "边界与覆盖轮廓没有交集，不存在干扰";
    case AREA_INCLUDE :return "两区域是子集关系";
	case WRONGCLOSEDBOUNDARY: return "未找到闭合的边界线";
	case CALSITECONTOURWRONG: return "计算待协调站轮廓线失败";
	case NOT_SUPPORT_FREEMODEL: return "自由空间传播模型不适用于边界协调";
	case WRONGBORDEREXCELHEADER: return "协调文件表头错误";
	case CSVWRITE_USE_DATA_TOO_LITTLE: return "报表生成用数据量过少";
	case CSVFILENETWOKR_TYPE_NOMATCH: return "没有匹配的网络制式";

		
	//TDOA_BASE_ERROR 25000
	case STATIONS_NOT_ENOUGH: return "监测节点的个数必须3个及以上";
	case SIGNAL_NO_CROSSRELATION: return " 信号相关性不够";
	case TIME_NO_MIXED: return "监测节点设备同步时间失败";
	case FILE_NUM_NOT_EQUAL_STATION: return "文件和监测节点数目不匹配";
	case UNSUPPORT_LOCATIONTYPE: return "不支持的定位方式";
    case RESULT_BAD: return "信号源太差，不满足定位要求，无法定位";
	case SIGNAL_TOO_BAD: return "信号太差，定位得到结果准确性太差";
	case LESS_3_STATION_RECEIVE_SIGNAL:return "可以接收到信号的监测节点数目少于3个";
	case LOCATION_ERROR: return "监测节点经纬度错误";

	//AOA_BASE_ERROR 26000
	case NO_SOURCE_IN_MONITOR_AREA: return "在监测范围内无指定频率的未知发射源";
	case AZIMUTH_CALCULATE_EXCEPTION: return "方位角计算值异常";


	//SOURCETRACK_BASE_ERROR 27000
	case STATION_NOT_RECEIVE_SIGNAL: return "信号强度太小 ";


	//SOURCEANALYSIS_BASE_ERROR 28000

	case SOURCEAREAR_COMPUTE_PARAM_ERROR: return "参数错误";
	case SOURCEAREAR_MONITOR_DATA_ERROR: return "监测数据文件读取失败";
    case SOURCEAREAR_UNSUPPORT_DATATYPE: return "监测数据文件只支持power类型";
    case SOURCEAREAR_DATA_NO_MATCH_EROR: return "监测数据文件和监测节点不匹配";
	
	//SITESELECTION_BASE_ERROR 29000
	case EVALUATECOVERRADIUS_ERROR: return "计算覆盖半径失败,可能选择的传播模型不适用";
    case SITESELECTION_NO_VALIDPOINT: return "选址密度已经小于10倍地图分辨率，可能水域太多,请检查参数设置是否合理";
	case SITESELECTION_NO_SITE: return "未设置候选站址";
	case SITESELECTION_SITE_FEW:return "待优化站址总数小于设定监测类型基本站址数要求";

	////SITEWORKSTATUS_BASE_ERROR 30000
	case SITEWORKSTATUS_SUPPORT_ONLY_ONE_STATION: return "仅支持一个台站进行工作情况分析";
	case NO_TIME_INTERSECTION: return "监测文件的监测时间无交集";
	case DISMATCH_STATIONS_AND_FILES: return "监测文件与监测节点数目不同";
	case NO_FREQUENCY_INTERSECTION: return "台站频率与监测文件频段无相关性";

	//SPECTRUMANALYSIS_BASE_ERROR 31000
	case NO_MATCH_RESULTTYPE: return "不匹配的结果类型，只支持功率和场强";

	//SIGNALSUPPERSSION_ERROR  32000
	case NO_MATCH_INTSTATION: return "压制频段需在压制设备频段范围内";
	case NO_COVERAGE: return "达不到覆盖";
	case NO_EXIST_INTER: return "不存在干扰区域，无需布站压制";
	case NO_SUPPORTED_MULTIPLE_FREQ: return "不支持同时压制多个频段";
	case NO_POWERLIST: return "没有候选功率";
	case NUMBER_CROSS_THE_BOUNDARY: return "数据发生越界";
	case NO_EXIST_DEPLOYMENT_AREA: return "不存在可部站区域";

		//33000
    case NO_TIMEINFO: return "没有时间信息";
    case NO_SIMULATORINFO: return "没有仿真结果";
    case MONITOR_FREQ_TOO_LESS :return "监测数据文件频点太少";
	case NO_COVERED_STATION: return "没有台站覆盖计算区域,可能是筛选距离过小导致";
	case EXCEL_LIB_ERROR: return "excel库错误";

		//
	case READ_ROADVECTORFILE_ERROR: return "读取路径矢量文件失败";
	case NO_SUPPORTED_CALCULATEAREA: return "不支持的区域类型";
	case GET_ROADVECTOR_ERROR: return "获取边界矢量失败，可能是计算区域与边界线无交集";
	case NO_SUPPORTED_SERVICE_TYPE: return "配置协议文件中无该业务类型协议方案";
	case NO_SUPPORTED_FREQ: return "配置协议文件中无某业务类型某频点的协议方案";

		//35000
	case NO_EXIST_STRONG_RADIATION: return "不存在强辐射，没有健康隐患";


   //36000
    case FREQUENCY_OUTOF_MONITORDATA: return "设置的频率范围不在监测数据的频段范围内";
	case TIME_OUTOF_MONITORDATA: return "设置的时间范围不在监测数据的时间范围内";
    case TOO_FEW_DATARECORD: return "监测数据记录条数为0";
	case PREPROCESS_ERROR: return "监测数据预处理出错";
	case INVALIDSCANFORMAT: return "无效的扫频文件格式";
	case STANDDATAFREQ_NOTMATCH:return "国家扫频文件名频率信息与数据信息不一致";
	case FILTER_NOISE_FREQUENCY_ERROR:return "国家扫频文件去噪时,每条记录对应频点不一致";
	case STANDCHECKCODE_ERROR: return "国家扫频文件数据校验码错误";
    case NG_MONITORFILE_OPEN_ERROR: return "无法读取指定的监测扫频文件";
	case INVALID_MONITOR_DATA: return "监测数据内容无效";
	case READ_FILE_NEW_MERRORY_ERROR:return "读取监测文件申请内存失败";


		//37000
	case DRIVER_TEST_POINT_NOT_ENOUGTH : return "用于插值的离散点数目太少";
	case MEMORY_WRONG:return "插值申请内存失败";
	case POINT_CAN_NOT_NULL: return "插值指针为空";
	case PARAM_WRONG: return "插值参数错误";
	case DB_NULL: return "插值数据库为空";
	case FILE_FORM_WRONG:return "插值文件格式错误";
	case PATH_NOT_ACCESS:return "文件夹无访问权限";
	case NO_TRAGET_FREQ_FILE:return "没有对应的频点文件";
	case NO_PARAM:return "没有输入参数";
		//	case TIME_OUT_RANGE:return ""
		//#define NO_SOURCE_FILE NATURALBASECODE+9//没有源文件
		//#define DRIVER_TEST_POINT_NOT_ENOUGTH NATURALBASECODE+10//路测点太少
		//#define NO_PARAM NATURALBASECODE +11 //没有输入参数
		//#define NO_TRAGET_FREQ_FILE NATURALBASECODE + 12 //没有对应的频点文件
		//#define PATH_NOT_ACCESS NATURALBASECODE +13 //文件夹无访问权限
		//	case :DRIVER_TEST_POINT_NOT_ENOUGTH : return "用于插值的离散点数目太少";
		//38000;
	case NO_TARGET_FREQ:return "扫频文件没有目标频段数据";
	case TX_STATION_NO_COVERAGE:return "该参数配置下,欲收台站无覆盖,无需计算";//"欲收台站对计算区域无覆盖,无需计算";
	case NEW_STATION_NO_COVERAGE:return "该参数配置下,新建站无覆盖,无需计算";//"新建台站对计算区域无覆盖,无需计算";
	case NO_COADJ_TXSTATION_COVERAGEAREA: return "新建站覆盖范围内没有预收台，无需计算";
	case NEW_STATION_NO_INTER: return "新建台对计算区域无干扰";
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
	case NG_IMPORT_NULLFILE: return "导入文件内容为空";
	case NG_IMPORT_FILE_FAIL: return "数据导入失败";
	case NG_IMPORT_FILE_PART_FAIL: return "部分数据导入失败";
	case NG_TABLEHEADERDISMATCHED: return "导入文件表头错误";
	case NG_IMPORT_FILE_HAS_REPEAT: return "部分台站已存在";

		//41000 
	case NG_NO_FREQASSIGN: return "缺失频率指配结果"; 

		// 43000 
	case NG_CONTOURLINE_FAILED : return "等值线提取失败";

	case NG_STATION_STATUS_NO_MONITOR:return "发射站覆盖范围内没有监测节点";
	case NG_XML_NO_MONSTATION :return "输入XML中没有监测节点";
	case NG_FPRINT_NO_MONSTATION:return "指纹数据库中没有输入的监测节点";
	case NG_NO_TX_STATION_FREQRANGE:return "发射台数据库中没有输入频段的台站";
	case NG_NO_TX_STATION_SPECIFIC: return "发射台数据库中没有输入GUID的台站";
	case NG_NOT_GIVEN_STATION_SPECIFIC: return "特定台站指纹训练缺少台站GUID";
	case NG_GIVEN_STATION_NOT_IN_OBJSERVICE: return "特定台站频率超出指纹库适用范围";

		//46000
	case NG_NO_CALTYPE:return "未定义计算结果类型";
	case NG_NO_COVERAGE: return "无覆盖，不能计算";
	case NG_NO_INT: return "无干扰，不能计算";

		//53000 二进制结果截取功能
	case NG_ARER_ERROR : return "未指定区域";
	case NG_NO_IMPORT_COORDSYS: return "不支持的坐标系，目前只支持经纬度";

	default:
		return "未知错误，也许参数配置不正确";
	}

}
#endif  

