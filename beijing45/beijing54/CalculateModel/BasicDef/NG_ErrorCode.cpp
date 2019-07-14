
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
//	/************BEGIN: ����ģ�������**************************/
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
//	/*********************�ļ�������****************************************/
//	{FAIL_TO_OPEN_FILE, "Fail to open file"},
//	{THE_FILE_IS_NOT_EXIST, "The file is not exist"},
//	{THE_FILE_NAME_TOO_LONG, "The file name is too long"},
//    {FAIL_TO_GET_FILE_NAME, "Fail to get file name"},
//	{FAIL_TO_WRITE_FILE, "Fail to write file"},
//	{FAIL_TO_CREATE_FILE, "Fail to create file"},
//	{FILE_PATH_NULL_ERROR, "The file path is null"},
//
//	/**********BEGIN: ����ѹ�������ݽ�ѹģ��Ĵ�����***********/
//	{FAIL_TO_RESOLVE_DECOMPRESS_FILE, "Fail to resolve decompress file"},
//	{THE_COMPRESS_SRC_FILE_NOT_OPEN, "The source compress file isn't opened"},
//	{THE_DECOMPRESS_SRC_FILE_NOT_OPEN, "The source decompress file isn't opened"},
//	{DATE_COMPRESS_ABNORMAL, "Date compress abnormal"},
//	{DATE_DECOMPRESS_ABNORMAL, "Date decompress abnormal"},
//	{DATE_DECOMPRESS_NORMAL_END, "Date decompress is normal ended"},
//	{DATE_COMPRESS_IS_NOT_NEEDED, "The date need not resolve"},
//	{DATE_DECOMPRESS_PARA_UNREASONABLE, "The decompress para is unreasonable"},
//	{FAIL_TO_GET_FILE_NAME, "Fail to get file name"},
//	/**********END: ����ѹ�������ݽ�ѹģ��Ĵ�����***********/
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
	case NG_SUCCESS:return "�ɹ�";
	//base
	//case NG_PARAMWRONG: return "��������";
	case NG_MEMORYWRONG: return "�ڴ治��";
	case POINTER_CAN_NOT_BE_EMPTY:return "��Чָ��,�����ڴ治��" ;
	case THE_PARAMETER_FORMAT_IS_ILLEGAL: return "������ʽ�Ƿ�";
	case THE_PARAMETER_RANGE_IS_ILLEGAL: return  "������Χ�Ƿ�";
	case NG_NOTGETRESULT:return "���в����£�û�к��ʵĽ������";
	case NG_NOTCALCULATE:return "δ������Ч����";
	case NG_NO_CALCULATE_MODEL: return "û�м���ģ��";
	case GEOSHAPE_ERROR: return "Geo Shape ���ʹ���";
	case INVALID_XMLFILE: return "��Ч��xml��ʽ";
	case UNIT_NO_EXIST: return "��λ�Ƿ�,ֻ֧��0~9";
	case HEIGHT_TYOE_ERROR: return "��Ч�ĸ߶�����";
	case NG_NO_RESULT_FILE: return "û�н���ļ�";
	case NG_CLIENTVERSION_NOTRANSMODE:return "�ͻ�δ��Ȩ�ô���ģ��";
	case NG_FUNCTIONMODEL_NOTRANSMODE:return "��ǰ����ģ�鲻֧�ָô���ģ��";
    case NG_DB_ERROR:return "���ݿ����";
	case NO_AREA_INFO:return "û��ָ��������Ϣ";
	case NO_MATCH_RESULTFILE: return "����ļ����Ͷ�Ӧ�ļ���̨վ����ƥ��";
	case NG_FUNCTIONMODEL_UNSUPPORT_FREESPACE: return "��ǰ����ģ�鲻֧�����ɿռ䴫��ģ��";
	case NG_FREQUENCY_PARAM_ERROR: return "Ƶ�ʲ�����Χ�Ƿ�";
	case NG_NULL_PROJECTGUID:      return "Project GUIDΪ��";
    case NG_XML_MARK_ERROR: return "xml ������Ҳ�����ļ�";
	case NG_USER_TERMINATE: return "�û���ֹ����";
	//
	//#define FILE_BASE_ERROR                    1000
	case FAIL_TO_OPEN_FILE: return  "���ļ�ʧ��";
	case THE_FILE_IS_NOT_EXIST : return "�ļ�������";
	case THE_FILE_NAME_TOO_LONG: return "�ļ���̫��";
	case FAIL_TO_GET_FILE_NAME : return "�޷���ȡ����ļ���";
	case FAIL_TO_WRITE_FILE : return "д�ļ�ʧ��";
	case FAIL_TO_CREATE_FILE :return  "�����ļ�ʧ��";
	case FILE_PATH_NULL_ERROR: return "�ļ�·��Ϊ��";
    case FAIL_TO_READ_FILE: return "���ļ�ʧ��";
    case FAIL_TO_DELETE_FILE: return "ɾ���ļ�ʧ��";
	case LACK_DATA_FILE: return "ȱʧ��Ч�������ļ�";
	case FILE_DATA_ERROR: return  "�ļ����ݴ���";
	case XML_PARAM_WRONG: return "XML�ļ���������";
	case CSV_FORMAT_WRONG: return "CSV�ļ���ʽ����";
	case INVALID_MSI_OR_PAT_FILE: return "��Ч�������ļ�";
	case FILE_FORMAT_ERROR: return "�ļ���ʽ����";


	
	//#define DONGLE_BASE_ERROR   2000	
	case NG_LICENSEEXPIRED:
	case NG_OPENLICENSEFILEFAIL:
	case NG_TIMEMODIFIED:
	case NG_LICENSEWRONG:
	case NG_LICENSEDONGLENOTMATCH:
	case NG_NORIGHTDONGLE: 
	case NG_DONGLECHECK_EXCEPTION:
	case NG_NOSERVERDONGLE: return "���������";
	case NG_TRANSMODELWRONG: return "����ģ��δ��Ȩ";
	case NG_NOMODELLICENSE: return "����ģ��δ��Ȩ";
	case NG_TRANSMODELPARAMCREATE_ERROE:return "��������ģ�Ͳ���ʧ��";
	//case NG_LICENSEEXPIRED:
	//case NG_OPENLICENSEFILEFAIL:
	//case NG_TIMEMODIFIED:  return "Check wrong";
	//case NG_TRANSMODELWRONG:"Not a valid trans-model";
	//case NG_LICENSEWRONG: return "Check wrong";
	
	//#define MAP_BASE_ERROR   3000
	case NG_NOAPPROPRIATEMAP: return "û�к�������ϵ�ĵ�ͼ";
	case NG_MAPCOORDNOTMATCH:  return "��ͼ����ϵ�����Ҫ��ƥ��";
	case NG_MAPPARAMWRONG: return "��ͼ�����д���";
	case NG_STATIONMAPNOTMATCH: return "̨վ���������ͼ�߽�";
	case NG_POINTMAPNOTMATCH: return "����㲻�ڵ�ͼ��";
	case NG_GETPROFILEWRONG: return "��ȡprofile�������ܵ�ԭ����պͷ����λ�ü�����ͬ";
	case  NG_CALCULATE_SHAP_ERROR:return "�����������ʹ���";
	case NG_Resolution_NOTMATCH:return "�ֱ��ʲ�ƥ��";
	case NG_NO_MAP_DATA:return "û�е�ͼ����";
	case NG_NO_VECTOR_MAP_DATA: return "ȱ��ʸ����ͼ";
	case NG_MAP_READ_WRONG: return "��ȡ��ͼʧ��";
	case NG_NO_INDOOR_TEMPLATE_MAP: return "ȱ������ģ���ͼ";
	case NG_CalculateResolution_Error: return "����ֱ�������";

		//#define STATION_BASE_ERROR   4000
	case ONE_STATION_IS_NOT_EXIST:return "ĳ��̨վ������,����̨վ�������ݿ���";
	case NO_STATION: return "û��һ��̨վ,����̨վ�������ݿ���";
	case NO_TX_STATION: return "û��һ�������,����̨վ�������ݿ���";
	case NO_RX_STATION: return "û��һ�����ջ�������̨վ�������ݿ���" ;
	case NO_MONITOR_STATION: return "û�м��ڵ㣬������Ϣ�������ݿ���";
	case TX_RX_SITE_NO_MATCH: return "��·�����н���վ�ͷ���վ��ƥ��";
	case NO_INT_STATION : return "û�и���̨,����Ҫ����";
	case NO_ASSIGN_STATION:return "û��ָ��վ";
	case SQL_STATION_PARAM_ERROR:return "���ݿ�̨վ��������";
	case XML_STATION_PARAM_ERROR:return "̨վ��������";
		//
	case LOCATION_PARAMETER_RANGE_IS_ILLEGAL:  return "̨վλ�ò�����Χ�Ƿ�";
	case HEIGHT_PARAMETER_RANGE_IS_ILLEGAL:  return "����߶Ȳ�����Χ�Ƿ� ֻ֧��(0~1000)m";
	case POWER_PARAMETER_RANGE_IS_ILLEGAL:return "���书�ʲ�����Χ�Ƿ� ֻ֧��(-4~90)dBm";
	case THRESHOLDDBM_PARAMETER_RANGE_IS_ILLEGAL: return "�������޲�����Χ�Ƿ� ֻ֧��(-120~-50)dBm";
	case THRESHOLDDBUVM_PARAMETER_RANGE_IS_ILLEGAL: return "�������޲�����Χ�Ƿ�";
	case CITHRESHOLD_PARAMETER_RANGE_IS_ILLEGAL:  return "����CI���޲�����Χ�Ƿ� ֻ֧��(-50~50)dB";
	case AZIMUTH_PARAMETER_RANGE_IS_ILLEGAL	:  return "��λ�ǲ�����Χ�Ƿ� ֻ֧��(0~360)��";
	case DOWNTILT_PARAMETER_RANGE_IS_ILLEGAL:  return "����ǲ�����Χ�Ƿ� ֻ֧��(-90~90)��";
	case GAIN_PARAMETER_RANGE_IS_ILLEGAL: return "�������淶Χ�Ƿ� ֻ֧��(-50~50)dBi";
	case LOSS_PARAMETER_RANGE_IS_ILLEGAL:  return "������ķ�Χ�Ƿ� ֻ֧��(-100~100)dB";
	case FREQUENCY_PARAMETER_RANGE_IS_ILLEGAL:  return "Ƶ�ʷ�Χ�Ƿ� ֻ֧��(0.3~40)MHz";
	case XML_RXHEIGHT_PARAM_ERROR	:return "xml�н��ո߶Ȳ�������";
	//#define TRANSMODEL_BASE_ERROR   5000
	case TRANSMODEL_NO_EXIST: return "��Ч�Ĵ���ģ��";
	case TRANSMODEL533LIB_EXEC_FAIL: return "533�����ʧ��";
	case TRANSMODEL_FREQ_OUTOFRANGE: return "Ƶ�ʳ���ѡ���Ĵ���ģ�͵����÷�Χ";
	case TRNAMODEL_HEIGHT_OUTOFRANGE: return "���ն˻��߷�������߸߶ȳ���ѡ���Ĵ���ģ�����÷�Χ";
	case TRANSMODEL_FREQ_BAND_ERROR: return "Ƶ�ʴ����������";
	case TRANSMODEL_NOT_SAME: return "�ڲ�����ģ�Ͳ�����һ��";
	case NO_TRANSMODEL_PARAM: return "�ڲ�����ģ�Ͳ���Ϊ��";
	case POLYLINE_TOO_FEW_POINT: return "���ߵ�����2��";
	case TRANSMODEL_NOT_SUPPORT_RESULT_TYPE: return "����ģ�Ͳ�֧�ֵ�ǰ�������";
	case STRAIGHT_LINE_IDENTICAL: return "��ʸ���غ�(����ģ��)";
	case STRAIGHT_LINE_PARALLEL: return "��ʸ��ƽ��(����ģ��)";
	case STRAIGHT_LINE_VERTICAL: return "��ʸ����y�ᴹֱ(����ģ��)";
	case NO_TRANSMODEL: return "δָ�����㴫��ģ��";
	
		//#define TRANSMODEL533_BASE_ERROR   5500
	case TRANS533_IONOS_ERROR:  return "533 ģ�Ͷ�ȡ����������ʧ��";
	case TRANS533_REC_TOO_CLOSE_ERROR: return "533 ģ�ͽ��յ�ͷ����������";
	case TRANS533_ANT_ELEANGLE_TOO_SMALL_ERROR: return "533 ģ����������̫С��С���趨������ֵ"; //��������̫С��С����
	case TRANS533_DAY_NOELAYER_ERROR: return "533 ģ����ҹ����߾����Զ��������E�㳡ǿ"; 
	case TRANS533_RESULTTYPE_NOTSUPPORT: return "533 ģ��Ŀǰֻ֧�ֳ�ǿ����";
	case TRANS533_MAP_NOTSUPPORT: return "533 ģ��Ŀǰֻ֧�־�γ�ȵ�ͼ����";
	case TRANS533_LATITUDE_OUT: return "533 ģ�ͼ���λ�õ�γ�ȳ���[-90��90]��Χ";
	case TRANS533_UTCHOUR_OUT: return "533 ģ�ͼ���UTCʱ�䳬��[0��24]��Χ";
	
	//#define CALIBRATIO_BASE_ERROR   6000

	case CALIBRATION_FREQ_OUTOFRANGE: return "Ƶ�ʳ���ѡ���Ĵ���ģ�͵����÷�Χ";
	case CALIBRATION_FAILED:          return "ģ��У��δ����ȷִ��";
	case CALIBRATION_TWO_FEW_POINT:   return "ģ��У���ļ��е���̫��";

	//#define INTERFERENCE_BASE_ERROR   7000
	case NO_MATCH_FREQ: return "����վ�ͷ���վƵ�ʲ�ƥ��,����������";
	case NO_NEW_INTSTATION: return "û����������վ,����������";

	//#define EMCCAL_BASE_ERROR   8000
    case NO_SUPPORTED_RESULT_TYPE: return "��֧�ֵĽ������";
	case NO_STATION_IN_SHAP: return "������û������Ҫ��ļ���̨վ���������";
	case NUSUPPORT_BAND_NULL: return "��֧��0������㹦����ͨ���ܶ�";
	//#define PERFROMANCE_BASE_ERROR   9000
	case NO_PERFORMANCE_COVERAGE: return "�շ�վ��ѡ����ʸ���������޸��ǣ��������";

	//#define LINKPROFILE_BASE_ERROR   10000
	case FRESNELNUM_ERROR: return "���������Ų����ڣ�ֻ֧��0~5";
	case LINK_TOO_NEAR: return "��·����̫��";
	case NO_LINK_POINTS: return "û����·";

	
	//11000
	case NG_NO_FREQOCCUPY_INTER: return"������Ƶ���ϵĸ������";
	//#define COMPRESS_BASE_ERROR   12000
	case FAIL_TO_RESOLVE_DECOMPRESS_FILE: return "��������ѹ���ļ�ʧ��"; 
	case  THE_COMPRESS_SRC_FILE_NOT_OPEN:  return "����ѹ��Դ�ļ�δ��";
	case THE_DECOMPRESS_SRC_FILE_NOT_OPEN : return "���ݽ�ѹԴ�ļ�δ��";
	case DATE_COMPRESS_ABNORMAL: return "����ѹ��ʧ��";
	case DATE_DECOMPRESS_ABNORMAL: return "���ݽ�ѹ�쳣";
	case DATE_DECOMPRESS_NORMAL_END: return "���ݽ�ѹ�ɹ�";
	case DATE_COMPRESS_IS_NOT_NEEDED : return "��ǰ��������ִ������ѹ�����ѹʱδʹ�ý�ѹ�㷨";
	case DATE_DECOMPRESS_PARA_UNREASONABLE: return "��ǰ���ݽ�ѹ����������";

		//
	//#define SIGNAL_BASE_ERROR   13000
	case FAIL_TO_GET_RADAR_FEATURE_BY_DATE_SHORT: return " �״�������̫�̣��޷���ȡ����";
	case POS_INFO_EXCESS_MAX_NUM_BY_TEA_EN: return "����teager�������������Ч��������������ֵ"; 
	case POS_INFO_EXCESS_MAX_NUM_BY_FREQ :return "����˲ʱƵ�ʼ��������Ч��������������ֵ"  ;  
	case  COMBINE_POS_NUM_EXCESS_MAX_NUM : return "�ϲ�����λ����Ϣ�ĸ����������ֵ";
	case THE_IQ_DATA_LENGTH_IS_NULL : return "IQ���ݸ���Ϊ��";
	case THE_THRESHOLD_IS_NOT_SET : return "���޲���δ����";
	case THE_CARR_OR_SAM_FREQ_IS_NOT_SET: return "�ز�Ƶ�ʻ��߲���Ƶ��δ����";
	case  THE_SYMBOL_RATE_IS_NOT_SET: return "��������δ����";
	case THE_SAMPLE_FREQ_IS_ILLEGAL : return "����Ƶ�ʹ���";
	case FAIL_TO_READ_CSV_FILE  : return "��ȡCSV�ļ�ͷʧ��";
	case THE_RADAR_DATA_LENGTH_IS_SHORT  : return " �״���������������,������ȡ�������޷���ģ ���޷�����"; 
	case THE_FEATURE_RESULT_FILE_PATH_IS_NOT_SET  :return "�������ļ�·��δ����";
	case FAIL_TO_OPEN_FEATURE_RESULT_FILE :return "���������ļ�ʧ��";
	case  THE_FILE_PATH_IS_TOO_LONG:  return "�ļ���·������̫�� ";
	case  THE_SAMPLE_RATE_IS_NULL  : return "δ���ò�����";
	case THE_SIGNAL_TYPE_IS_NULL  : return "δ�����ź�����";  
	case  THE_MODEL_FILE_PATH_IS_NOT_SET: return "�������ļ�·��δ����" ;  
	case THE_FEATURE_FILE_PATH_IS_NOT_SET : return "�ź������ı� ·��δ����" ; 
	case THE_RECOGNITION_RESULT_FILE_PATH_IS_NOT_SET : return "ʶ�����ļ�·��δ����";
	case FAIL_TO_OPEN_RECOGNITION_RESULT_FILE : return "��ʶ�����ļ�ʧ��";
	case THE_SRC_FILE_PATH_IS_NOT_SET : return "ԭʼ�ź��ļ�·��δ����"; 
    case THE_FFT_DATE_IS_NULL: return "δ����FFT�任"; 
	case FAIL_TO_FFT_TRANSFORM: return "FFTʧ��"; 
	case FAIL_TO_CAL_FEATURE_PARA: return "����ͨ���ź�����ʧ��"; 
	case FAIL_TO_OPEN_MODEL_FILE: return "���������ļ�ʧ��"; 
	case FAIL_TO_RESOLVE_STATION_TYPE_TABLE: return "����̨վ���ͱ�ʧ��"; 
	case NO_SPECIAL_STATION_ID_IN_TYPE_TABLE: return "̨վ���ͱ��޶�Ӧ̨վID����ȷ���Ƿ��޸Ĺ�̨վ���ͱ�"; 
	case THE_STATION_TABLE_DATA_IS_NULL: return "̨վ���ͱ�������Ϊ��"; 
	case THE_LIB_AND_STATION_TABLE_NOT_MATCH: return " ̨վ���ͱ������������ݲ�ƥ��"; 
	case FAIL_TO_RESOLVE_SAMPLE_LIB_FILE: return "��������������ʧ��"; 
    case NO_FP_SAMPLE_LIB_FOR_MONI_STATION:return "�ü��ڵ�δѵ��ָ��������";
    case FAIL_TO_READ_STATION_DATEBASE_INFO: return"��ȡ̨վ���ݿ�ʧ��";
	case FAIL_TO_CREATE_SPECTRUM_LIB_DATE: return "�޷�����Ƶ������������ "; 
	case FAIL_TO_GET_SPECIAL_SPECTRUM_DATE: return "�����ɨƵ������ָ��������Ƶ����Ϣ"; 
	case THE_INPUT_PARA_MEMORY_IS_SHORT: return "��������ڴ治��"; 
	case NO_SPECIAL_FREQ_POINT: return "δ�ҵ�ָ��Ƶ��"; 
    case ERROR_TO_TIME_RANGE: return "ʱ�䷶Χ�Ƿ�"; 
    case ERROR_TO_FREQ_RANGE: return "Ƶ�ʷ�Χ�Ƿ�"; 
    case FAIL_TO_READ_SCAN_FILE: return "��ȡɨƵ�ļ�ʧ��"; 
    case NO_SPECTRUM_LIB_FILE_IN_MONI_STATION: return "�ü��ڵ㻹δ����Ƶ�׿�"; 
	case NO_SPECTRUM_LIB_FILE_THIS_TIME_RANGE: return "��ʱ��ȱʧ����Ƶ�׿�";
	case NO_SPECTRUM_LIB_FILE_THIS_FREQ_RANGE: return "��Ƶ����δ����Ƶ�׿�";	
	case NO_ABNORMAL_FREQ: return "�˴μ�����쳣";
	case TRAIN_SCAN_FILE_ERROR:return "ѵ�������з���ɨƵ�����д����쳣Ƶ��";
	case TRAIN_SCAN_FILE_TIME_ERROR: return "ѵ��ʱɨƵ����ʱ����Ϣ����";
	case DELETE_TRAIN_FILE_FAILED: return "ɾ��ѵ���ļ�ʧ��";
	case TRAIN_STOP:return "ֹͣѵ��";
	case SUPERVISE_DATA_SHORT:return "�����������100��";

    case NO_VALID_DIAGNOSIS_PARA: return "δ������Ч����ϲ���"; 
    case DIAGNOSIS_RESULT_IS_NULL: return "��Ͻ��Ϊ��";
    case THE_TEXT_DATA_BASE_IS_NULL: return "�ı�����֪ʶ��Ϊ��";
    case THE_SRC_RECORD_VALUE_INVALID: return "ԭʼ��¼��ֵΪ��Чֵ";
    case THE_BATCH_FILE_INVALID: return "�����ļ����ݷǷ�";
    case THE_DIAGNOSIS_LEN_TOO_LONG: return "�ֶγ���̫��";
    case THE_SRC_FILE_PATH_IS_NULL: return "��¼�ļ�·������Ϊ��";
    case THE_RECORD_DATA_IS_NULL: return "��¼Ϊ��";
    case FAIL_TO_READ_TEXT_DATA_BASE: return "��ȡ�ı��������ݿ�ʧ��";
    case FAIL_TO_WRITE_TEXT_DATA_BASE: return "д�ı��������ݿ�ʧ��";
    case TIME_BGEIN_END_INVALID: return "��ֹʱ��Ƿ�";
    case THE_TIME_FORMAT_INVALID: return "ʱ���ʽ�Ƿ�";
    case THE_TIME_VALUE_INVALID: return "ʱ��������Ч";
    case FREQ_BGEIN_END_INVALID: return "��ֹƵ�ʷǷ�";

	case NG_OPENSPECTRUMDBWRONG: return "�����ݿ�ʧ��";
	case NG_READSPECTRUMDBWRONG:return "������Ƶ�׿�ʧ��";
	case NG_WRITESPECTRUMDBWRONG:return "д����Ƶ�׿�ʧ��";
	case NG_GETDATABASEERROR:return "��ȡ���ݿ�����ʧ��";

    
	//#define FUSION_BASE_ERROR            (14000)    
	case FUSION_INTERPOLATION_ERROR:   return "�����ֵ����";
	case FUSION_REVISE_ERROR:         return "��ֵУ������";

	//#define FREQPROTECT_BASE_ERROR   15000
	case NG_NOPROTECTIONINT :return "̨վƵ�ʲ��ڱ���Ƶ�η�Χ��";

	
	//#define FREQASSIGN_BASE_ERROR   16000
    case FREQASSIGN_TOO_FEW_FREQ: return "��ѡƵ��̫��";
	case FREQASSIGN_QUALITY_BAD: return "��ѡƵ������̫��";
	case FREQASSIGN_FREQOFF_SMALL: return "��������Ƶ��Ҫ��";
	case FREQASSIGN_CALORDER_ERROR: return "Ƶ��ָ������˳�����";
	case FREQASSIGN_OCCUPYFILE_ERROR: return "δ��ȡ��ɨƵռ�öȷ����ļ�";
	
	//#define FREQCONFILICT_BASE_ERROR   17000

	//#define DEPOLY_BASE_ERROR     18000

	case PARAM_CLUSTTER_FREQUENCY_WRONG	: return "��Ƶ�����;��������ô���";
	case PLAN_TIME_ERROR: return "�ƻ�ʱ�����";
	case  NOT_COVERAGE: return "���վ��Ҳ�ﲻ������";
	case UNSUPPORTED_MAP_COORD : return "��֧�ֵ�����ϵ����·�߹滮�У�ֻ֧�־�γ������";
	case NOT_AVAILABLE_ROAD	: return "������û�п��еĵ�·"; 
	case  NO_COMMAND_DATE_AVAILABLE: return "û�п��õļ��Ҫ�󣬿���ԭ�����õĲ�����������Ҫ����ȡ���ڲ���";
	case COMMAND_AND_WORKMODEL_NOT_MATCH: return "���Ҫ�����͹���ģʽ��ƥ��";
	case COMMAND_PRIORITY_ERROR: return "������ȼ�����ֻ֧��0~5";
	case  CAL_PRIORITY_TYPE_ERROR:return "���������ȼ����ʹ���ֻ֧��0~1";
	case TIME_TYPEL_NO_EXIST: return "ʱ���������ʹ���ֻ֧��0~4";
	case WORK_MODEL_TYPE_ERROR: return "���ڵ㹤��ģ�����ʹ���ֻ֧��1~3";
	case MAX_SITE_COUNT_ERROR:return "��������վ������ֻ֧��1~200";
	case COVERAGE_PER_ERROR: return "Ŀ�긲�Ǵ���ֻ֧��1~3";
	case SIGNAL_TYPE_ERROR: return "�ź����ʹ���ֻ֧��1~3";
	case MONITOR_TIME_ERROR: return "���ʱ����󣬱��밴ָ����ʽ���룬ʱ�������������";
	case RADAR_DETECT_PROB_ERROR: return "�״��������ʲ�������ֻ֧��0-100";
	case RADAR_FALSE_PROB_ERROR: return "�״��龯���ʲ�������ֻ֧��0-100";
	case RADAR_MINRCS_ERROR: return "�״���СĿ��������������";

	//#define  PROTECTION_BASE_ERROR   19000
    case NONOPROTECTIONFILE :return "�������ļ�������";
	//#define  ISOSURFACE_BASE_ERROR   20000  

	//#define INTERMODULATION_BASE_ERROR  21000
	case INTERMODULATIONORDER_ERROR : return "������������ֻ֧��3��5";

	//#define PROJECTCONFIG_BASE_ERROR  22000
	case DATABASE_CONFIG_ERROR: return "���ݿ����ô���";
	case MAP_CONFIG_ERROR : return "��ͼ���ô���";
	case USER_CAL_PARAM_ERROR : return "�û����õĲ����ļ�����";
	case TRANSMODEL_CONFIG_ERROR: return "����ģ�ͳ�ʼ��ʧ��";
	case PATHLOSS_PATH_CONFIG_ERROR:return "·�����Ŀ¼���ô���";
	case BUSINESS_BAND_CONFIG_ERROR: return "ҵ��Ƶ��·�����ô���";
	case BORDER_COORDINATION_CONFIG_ERROR: return "Э��Э��·�����ô���";
	case MAX_COVERAGE_RADIUS_CONFIG_ERROR: return "��ͬ����Ƶ�ʶ�Ӧ�����뾶�ļ����ô���";
	case LICENSECHECK_PATH_CONFIG_ERROR: return "������ļ����ô���";

	//#define HARMONICSINT_BASE_ERROR  23000
	case HARMONICSPARAM_ERROR: return "г����������ֻ֧��2~13";


	//BoundaryCoordinate_BASE_ERROR 24000
	case NO_INTERFERENCE: return "�߽��븲������û�н����������ڸ���";
    case AREA_INCLUDE :return "���������Ӽ���ϵ";
	case WRONGCLOSEDBOUNDARY: return "δ�ҵ��պϵı߽���";
	case CALSITECONTOURWRONG: return "�����Э��վ������ʧ��";
	case NOT_SUPPORT_FREEMODEL: return "���ɿռ䴫��ģ�Ͳ������ڱ߽�Э��";
	case WRONGBORDEREXCELHEADER: return "Э���ļ���ͷ����";
	case CSVWRITE_USE_DATA_TOO_LITTLE: return "��������������������";
	case CSVFILENETWOKR_TYPE_NOMATCH: return "û��ƥ���������ʽ";

		
	//TDOA_BASE_ERROR 25000
	case STATIONS_NOT_ENOUGH: return "���ڵ�ĸ�������3��������";
	case SIGNAL_NO_CROSSRELATION: return " �ź�����Բ���";
	case TIME_NO_MIXED: return "���ڵ��豸ͬ��ʱ��ʧ��";
	case FILE_NUM_NOT_EQUAL_STATION: return "�ļ��ͼ��ڵ���Ŀ��ƥ��";
	case UNSUPPORT_LOCATIONTYPE: return "��֧�ֵĶ�λ��ʽ";
    case RESULT_BAD: return "�ź�Դ̫������㶨λҪ���޷���λ";
	case SIGNAL_TOO_BAD: return "�ź�̫���λ�õ����׼ȷ��̫��";
	case LESS_3_STATION_RECEIVE_SIGNAL:return "���Խ��յ��źŵļ��ڵ���Ŀ����3��";
	case LOCATION_ERROR: return "���ڵ㾭γ�ȴ���";

	//AOA_BASE_ERROR 26000
	case NO_SOURCE_IN_MONITOR_AREA: return "�ڼ�ⷶΧ����ָ��Ƶ�ʵ�δ֪����Դ";
	case AZIMUTH_CALCULATE_EXCEPTION: return "��λ�Ǽ���ֵ�쳣";


	//SOURCETRACK_BASE_ERROR 27000
	case STATION_NOT_RECEIVE_SIGNAL: return "�ź�ǿ��̫С ";


	//SOURCEANALYSIS_BASE_ERROR 28000

	case SOURCEAREAR_COMPUTE_PARAM_ERROR: return "��������";
	case SOURCEAREAR_MONITOR_DATA_ERROR: return "��������ļ���ȡʧ��";
    case SOURCEAREAR_UNSUPPORT_DATATYPE: return "��������ļ�ֻ֧��power����";
    case SOURCEAREAR_DATA_NO_MATCH_EROR: return "��������ļ��ͼ��ڵ㲻ƥ��";
	
	//SITESELECTION_BASE_ERROR 29000
	case EVALUATECOVERRADIUS_ERROR: return "���㸲�ǰ뾶ʧ��,����ѡ��Ĵ���ģ�Ͳ�����";
    case SITESELECTION_NO_VALIDPOINT: return "ѡַ�ܶ��Ѿ�С��10����ͼ�ֱ��ʣ�����ˮ��̫��,������������Ƿ����";
	case SITESELECTION_NO_SITE: return "δ���ú�ѡվַ";
	case SITESELECTION_SITE_FEW:return "���Ż�վַ����С���趨������ͻ���վַ��Ҫ��";

	////SITEWORKSTATUS_BASE_ERROR 30000
	case SITEWORKSTATUS_SUPPORT_ONLY_ONE_STATION: return "��֧��һ��̨վ���й����������";
	case NO_TIME_INTERSECTION: return "����ļ��ļ��ʱ���޽���";
	case DISMATCH_STATIONS_AND_FILES: return "����ļ�����ڵ���Ŀ��ͬ";
	case NO_FREQUENCY_INTERSECTION: return "̨վƵ�������ļ�Ƶ���������";

	//SPECTRUMANALYSIS_BASE_ERROR 31000
	case NO_MATCH_RESULTTYPE: return "��ƥ��Ľ�����ͣ�ֻ֧�ֹ��ʺͳ�ǿ";

	//SIGNALSUPPERSSION_ERROR  32000
	case NO_MATCH_INTSTATION: return "ѹ��Ƶ������ѹ���豸Ƶ�η�Χ��";
	case NO_COVERAGE: return "�ﲻ������";
	case NO_EXIST_INTER: return "�����ڸ����������貼վѹ��";
	case NO_SUPPORTED_MULTIPLE_FREQ: return "��֧��ͬʱѹ�ƶ��Ƶ��";
	case NO_POWERLIST: return "û�к�ѡ����";
	case NUMBER_CROSS_THE_BOUNDARY: return "���ݷ���Խ��";
	case NO_EXIST_DEPLOYMENT_AREA: return "�����ڿɲ�վ����";

		//33000
    case NO_TIMEINFO: return "û��ʱ����Ϣ";
    case NO_SIMULATORINFO: return "û�з�����";
    case MONITOR_FREQ_TOO_LESS :return "��������ļ�Ƶ��̫��";
	case NO_COVERED_STATION: return "û��̨վ���Ǽ�������,������ɸѡ�����С����";
	case EXCEL_LIB_ERROR: return "excel�����";

		//
	case READ_ROADVECTORFILE_ERROR: return "��ȡ·��ʸ���ļ�ʧ��";
	case NO_SUPPORTED_CALCULATEAREA: return "��֧�ֵ���������";
	case GET_ROADVECTOR_ERROR: return "��ȡ�߽�ʸ��ʧ�ܣ������Ǽ���������߽����޽���";
	case NO_SUPPORTED_SERVICE_TYPE: return "����Э���ļ����޸�ҵ������Э�鷽��";
	case NO_SUPPORTED_FREQ: return "����Э���ļ�����ĳҵ������ĳƵ���Э�鷽��";

		//35000
	case NO_EXIST_STRONG_RADIATION: return "������ǿ���䣬û�н�������";


   //36000
    case FREQUENCY_OUTOF_MONITORDATA: return "���õ�Ƶ�ʷ�Χ���ڼ�����ݵ�Ƶ�η�Χ��";
	case TIME_OUTOF_MONITORDATA: return "���õ�ʱ�䷶Χ���ڼ�����ݵ�ʱ�䷶Χ��";
    case TOO_FEW_DATARECORD: return "������ݼ�¼����Ϊ0";
	case PREPROCESS_ERROR: return "�������Ԥ�������";
	case INVALIDSCANFORMAT: return "��Ч��ɨƵ�ļ���ʽ";
	case STANDDATAFREQ_NOTMATCH:return "����ɨƵ�ļ���Ƶ����Ϣ��������Ϣ��һ��";
	case FILTER_NOISE_FREQUENCY_ERROR:return "����ɨƵ�ļ�ȥ��ʱ,ÿ����¼��ӦƵ�㲻һ��";
	case STANDCHECKCODE_ERROR: return "����ɨƵ�ļ�����У�������";
    case NG_MONITORFILE_OPEN_ERROR: return "�޷���ȡָ���ļ��ɨƵ�ļ�";
	case INVALID_MONITOR_DATA: return "�������������Ч";
	case READ_FILE_NEW_MERRORY_ERROR:return "��ȡ����ļ������ڴ�ʧ��";


		//37000
	case DRIVER_TEST_POINT_NOT_ENOUGTH : return "���ڲ�ֵ����ɢ����Ŀ̫��";
	case MEMORY_WRONG:return "��ֵ�����ڴ�ʧ��";
	case POINT_CAN_NOT_NULL: return "��ֵָ��Ϊ��";
	case PARAM_WRONG: return "��ֵ��������";
	case DB_NULL: return "��ֵ���ݿ�Ϊ��";
	case FILE_FORM_WRONG:return "��ֵ�ļ���ʽ����";
	case PATH_NOT_ACCESS:return "�ļ����޷���Ȩ��";
	case NO_TRAGET_FREQ_FILE:return "û�ж�Ӧ��Ƶ���ļ�";
	case NO_PARAM:return "û���������";
		//	case TIME_OUT_RANGE:return ""
		//#define NO_SOURCE_FILE NATURALBASECODE+9//û��Դ�ļ�
		//#define DRIVER_TEST_POINT_NOT_ENOUGTH NATURALBASECODE+10//·���̫��
		//#define NO_PARAM NATURALBASECODE +11 //û���������
		//#define NO_TRAGET_FREQ_FILE NATURALBASECODE + 12 //û�ж�Ӧ��Ƶ���ļ�
		//#define PATH_NOT_ACCESS NATURALBASECODE +13 //�ļ����޷���Ȩ��
		//	case :DRIVER_TEST_POINT_NOT_ENOUGTH : return "���ڲ�ֵ����ɢ����Ŀ̫��";
		//38000;
	case NO_TARGET_FREQ:return "ɨƵ�ļ�û��Ŀ��Ƶ������";
	case TX_STATION_NO_COVERAGE:return "�ò���������,����̨վ�޸���,�������";//"����̨վ�Լ��������޸���,�������";
	case NEW_STATION_NO_COVERAGE:return "�ò���������,�½�վ�޸���,�������";//"�½�̨վ�Լ��������޸���,�������";
	case NO_COADJ_TXSTATION_COVERAGEAREA: return "�½�վ���Ƿ�Χ��û��Ԥ��̨���������";
	case NEW_STATION_NO_INTER: return "�½�̨�Լ��������޸���";
		//41000
	case NG_WRONGFIELDINEXCELS: return "EXCEL�й̶��ֶδ���";
	case NG_RADIO_ASSETS_CLASSIFICATION: return "���ߵ��ʲ������ֶδ���";
	case NG_ASSETS_CLASS_NAME: return "�ʲ������ֶδ���";
	case NG_ASSETS_SUBCLASS: return "�ʲ������ֶδ���";
	case NG_ACQUISITION_METHOD: return "ȡ�÷�ʽ�ֶδ���";
	case NG_PROCUREMENT_ORGANIZATION_FORM: return "�ɹ���֯��ʽ�ֶδ���";
	case NG_PROPERTY_RIGHTS_FORM: return "��Ȩ��ʽ�ֶδ���";
	case NG_USE_STATUS: return "ʹ��״���ֶδ���";
	case NG_USE_DIRECTION: return "ʹ�÷����ֶδ���";
	case NG_VALUE_TYPE: return "��ֵ�����ֶδ���";
	case NG_IMPORT_OR_DOMESTIC: return "����/�����ֶδ���";
	case NG_STATE_FINANCIAL_APPROPRIATION: return "���Ҳ����Բ����ֶδ���";
	case NG_LOCAL_FINANCIAL_APPROPRIATION: return "�ط������Բ����ֶδ���";
	case NG_ASSETS_USE_STATUS: return "�ʲ�״̬�ֶδ���";
	case NG_IMPORT_NULLFILE: return "�����ļ�����Ϊ��";
	case NG_IMPORT_FILE_FAIL: return "���ݵ���ʧ��";
	case NG_IMPORT_FILE_PART_FAIL: return "�������ݵ���ʧ��";
	case NG_TABLEHEADERDISMATCHED: return "�����ļ���ͷ����";
	case NG_IMPORT_FILE_HAS_REPEAT: return "����̨վ�Ѵ���";

		//41000 
	case NG_NO_FREQASSIGN: return "ȱʧƵ��ָ����"; 

		// 43000 
	case NG_CONTOURLINE_FAILED : return "��ֵ����ȡʧ��";

	case NG_STATION_STATUS_NO_MONITOR:return "����վ���Ƿ�Χ��û�м��ڵ�";
	case NG_XML_NO_MONSTATION :return "����XML��û�м��ڵ�";
	case NG_FPRINT_NO_MONSTATION:return "ָ�����ݿ���û������ļ��ڵ�";
	case NG_NO_TX_STATION_FREQRANGE:return "����̨���ݿ���û������Ƶ�ε�̨վ";
	case NG_NO_TX_STATION_SPECIFIC: return "����̨���ݿ���û������GUID��̨վ";
	case NG_NOT_GIVEN_STATION_SPECIFIC: return "�ض�̨վָ��ѵ��ȱ��̨վGUID";
	case NG_GIVEN_STATION_NOT_IN_OBJSERVICE: return "�ض�̨վƵ�ʳ���ָ�ƿ����÷�Χ";

		//46000
	case NG_NO_CALTYPE:return "δ�������������";
	case NG_NO_COVERAGE: return "�޸��ǣ����ܼ���";
	case NG_NO_INT: return "�޸��ţ����ܼ���";

		//53000 �����ƽ����ȡ����
	case NG_ARER_ERROR : return "δָ������";
	case NG_NO_IMPORT_COORDSYS: return "��֧�ֵ�����ϵ��Ŀǰֻ֧�־�γ��";

	default:
		return "δ֪����Ҳ��������ò���ȷ";
	}

}
#endif  

