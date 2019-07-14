/* 该文件定义恩巨网络所有对外输出的错误码，每个模块的对外输出错误码必须在此定义，定义的格式必须保持统一 */
#include "NG_CommonDefine.h"

#ifndef _NG_ERROR_CODE_H
#define _NG_ERROR_CODE_H

#pragma once


/**********************公共错误码*******************************/
#define NG_UNKNOWN_ERROR                   -1    //其他的错误都返回-1
#define NG_SUCCESS                         0//成功

#define BASE_ERROR                         100
#define NG_PARAMWRONG                      BASE_ERROR+1 //参数错误
#define NG_MEMORYWRONG                     BASE_ERROR+2 //内存申请失败
#define POINTER_CAN_NOT_BE_EMPTY           BASE_ERROR+3 // 指针不能为空 
#define THE_PARAMETER_FORMAT_IS_ILLEGAL    BASE_ERROR+4 // 参数格式非法 
#define THE_PARAMETER_RANGE_IS_ILLEGAL     BASE_ERROR+5 //参数范围非法 
#define FAIL_TO_APPLICATION_NEW_MEMORY     BASE_ERROR+6 // 申请内存失败
#define NG_NOTGETRESULT                    BASE_ERROR+7 //没有合适的方案
#define NG_NOTCALCULATE                    BASE_ERROR+8 //未进行有效计算
#define NG_NO_CALCULATE_MODEL			   BASE_ERROR+9 //没有计算模型
#define GEOSHAPE_ERROR                     BASE_ERROR+10 //GEOSHPAE类型错误
#define INVALID_XMLFILE                    BASE_ERROR+11 //xml文件格式破坏
#define UNIT_NO_EXIST                      BASE_ERROR+12 //单位非法  只支持0-9
#define HEIGHT_TYOE_ERROR                 BASE_ERROR+13 //高度类型非法  只支持0-2
#define NG_NO_RESULT_FILE                  BASE_ERROR+14 //没有结果文件
#define NG_CLIENTVERSION_NOTRANSMODE   DONGLE_BASE_ERROR+16 //客户版本未授权该模型
#define NG_FUNCTIONMODEL_NOTRANSMODE   DONGLE_BASE_ERROR+17 //功能模块不支持该传播模型
#define NG_DB_ERROR                        BASE_ERROR+18  //数据库错误
#define NO_AREA_INFO                       BASE_ERROR+19  //没有区域信息
#define NO_MATCH_RESULTFILE	              BASE_ERROR+20  //结果文件数和计算台站数不匹配
#define NG_FUNCTIONMODEL_UNSUPPORT_FREESPACE  BASE_ERROR+21  //功能不支持自由空间模型
#define NG_FREQUENCY_PARAM_ERROR			BASE_ERROR+22	//计算参数：频率范围非法
#define NG_NULL_PROJECTGUID                 BASE_ERROR+23   //Project GUID为空
/*********************文件错误码****************************************/
#define FILE_BASE_ERROR                    1000
#define FAIL_TO_OPEN_FILE                  FILE_BASE_ERROR+1 // 打开文件失败 
#define THE_FILE_IS_NOT_EXIST              FILE_BASE_ERROR+2 // 文件不存在
#define THE_FILE_NAME_TOO_LONG             FILE_BASE_ERROR+3 // 文件名太长
#define FAIL_TO_GET_FILE_NAME              FILE_BASE_ERROR+4 //无法获取结果文件名
#define FAIL_TO_WRITE_FILE                 FILE_BASE_ERROR+5 // 写文件失败 
#define FAIL_TO_CREATE_FILE                FILE_BASE_ERROR+6 // 创建文件失败
#define FILE_PATH_NULL_ERROR               FILE_BASE_ERROR+7 // 文件路径为空
#define FAIL_TO_READ_FILE                  FILE_BASE_ERROR+8 // 读文件失败 
#define FAIL_TO_DELETE_FILE                FILE_BASE_ERROR+9 // 删除文件失败 
#define LACK_DATA_FILE                     (FILE_BASE_ERROR+10) //缺数据文件
#define FILE_DATA_ERROR                     (FILE_BASE_ERROR+11) //文件内容错误
#define XML_PARAM_WRONG                    FILE_BASE_ERROR+12    //XML文件参数错误
#define CSV_FORMAT_WRONG                   FILE_BASE_ERROR+13    //CSV文件格式错误
#define INVALID_MSI_OR_PAT_FILE            FILE_BASE_ERROR+14    //无效的天线文件

/***********狗检测错误*******************************************/
#define DONGLE_BASE_ERROR   2000
#define NG_LICENSEDONGLENOTMATCH  DONGLE_BASE_ERROR+1  //狗和license文件不匹配
#define NG_NORIGHTDONGLE          DONGLE_BASE_ERROR+2   //未发现正确的硬件狗
#define NG_NOSERVERDONGLE         DONGLE_BASE_ERROR+3  //网络中未发现指定的硬件狗
#define NG_NOMODELLICENSE         DONGLE_BASE_ERROR+4  //模块 未授权
#define NG_LICENSEEXPIRED         DONGLE_BASE_ERROR+5  //license 已经过期
#define NG_OPENLICENSEFILEFAIL    DONGLE_BASE_ERROR+6  //打开license 文件失败
#define NG_TIMEMODIFIED           DONGLE_BASE_ERROR+7  //狗时间篡改
#define NG_TRANSMODELWRONG        DONGLE_BASE_ERROR+8  //传播模型未授权
#define NG_LICENSEWRONG           DONGLE_BASE_ERROR+9 //
#define NG_DONGLECHECK_EXCEPTION  DONGLE_BASE_ERROR+10 //硬件狗检测出现异常
#define NG_TRANSMODELPARAMCREATE_ERROE  DONGLE_BASE_ERROR+11 //传播模型参数创建失败
#define NG_UNKNOWNLICENSECHECK    DONGLE_BASE_ERROR+12 //未知加密方式
#define NG_NO_RIGHT_CMDONGLE      DONGLE_BASE_ERROR+13 //Codemeter错误，详情需要看日志




/***********地图错误码*******************************************/
#define MAP_BASE_ERROR   3000
#define NG_NOAPPROPRIATEMAP			MAP_BASE_ERROR+1   //没有合适坐标系的地图
#define NG_MAPCOORDNOTMATCH			MAP_BASE_ERROR+2 //地图坐标系与计算要求不匹配
#define NG_MAPPARAMWRONG			MAP_BASE_ERROR+3 //地图参数不正确
#define NG_STATIONMAPNOTMATCH		MAP_BASE_ERROR+4 //台站超出计算地图边界
#define NG_POINTMAPNOTMATCH			MAP_BASE_ERROR+5 //计算点不在地图内
#define NG_GETPROFILEWRONG			MAP_BASE_ERROR+6 //获取profile错误，可能原因：申请空间错误和接收发射点位置几近相同
#define NG_CALCULATE_SHAP_ERROR		MAP_BASE_ERROR+7 //计算区域错误
#define NG_Resolution_NOTMATCH		MAP_BASE_ERROR+8 //分辨率不匹配
#define NG_NO_MAP_DATA				MAP_BASE_ERROR+9 //没有地图数据
#define NG_RESULTCOORDINDEX_SAME    MAP_BASE_ERROR+10 //结果坐标系一致，无需转换
#define NG_NO_VECTOR_MAP_DATA       MAP_BASE_ERROR+11 //缺少矢量地图 
#define NG_MAP_READ_WRONG           MAP_BASE_ERROR+12 //地图读取失败
#define NG_NO_INDOOR_TEMPLATE_MAP   MAP_BASE_ERROR+13 //缺少室内模板地图

/***********台站错误码*******************************************/
#define STATION_BASE_ERROR   4000
#define ONE_STATION_IS_NOT_EXIST  STATION_BASE_ERROR+1 //某个台站不存在
#define NO_STATION                STATION_BASE_ERROR+2 //没有一个台站
#define NO_TX_STATION             STATION_BASE_ERROR+3 //没有一个发射机
#define NO_RX_STATION             STATION_BASE_ERROR+4 //没有一个接收机
#define NO_MONITOR_STATION        STATION_BASE_ERROR+5 //没有一个监测站
#define TX_RX_SITE_NO_MATCH		  STATION_BASE_ERROR+6 //链路分析中接收站和发射站不匹配
#define NO_INT_STATION            STATION_BASE_ERROR+7 //没有一个干扰机
#define NO_ASSIGN_STATION         STATION_BASE_ERROR+8 //没有指配站
#define SQL_STATION_PARAM_ERROR   STATION_BASE_ERROR+9 //数据库台站参数错误

#define NG_STATIONPREPROCESS_ERROR		43000
#define READ_RESOLUTION_FAILED			NG_STATIONPREPROCESS_ERROR+11  //读取分辨率失败
#define CREATE_PREPROCESSFILE_FAILED    NG_STATIONPREPROCESS_ERROR+12  //创建预处理文件失败
#define READ_PREPROCESS_STATION_FAILED	NG_STATIONPREPROCESS_ERROR+13  //读取预处理台站失败
#define TOOMUCH_PREPROCESS_STATION		NG_STATIONPREPROCESS_ERROR+14  //预处理台站过多
#define INPUT_PARAM_WRONG				NG_STATIONPREPROCESS_ERROR+15  //预处理输入参数错误
#define UPDATE_TXSTATION_NO_FAILED		NG_STATIONPREPROCESS_ERROR+16  //更新预处理编号错误
#define UPDATE_PREPROCESSPATH_FAILED	NG_STATIONPREPROCESS_ERROR+17  //更新预处理路径错误
#define PREPROCESS_LICENSE_ERROR		NG_STATIONPREPROCESS_ERROR+18  //预处理狗检测错误
#define READ_PRECALC_PARAM_FAILED		NG_STATIONPREPROCESS_ERROR+19  //读取分辨率失败
#define READ_LAST_PRECALCID_FAILED		NG_STATIONPREPROCESS_ERROR+20  //获取上次计算的ID失败
#define UPDATE_PROC_STATUS_I_FAILED		NG_STATIONPREPROCESS_ERROR+21  //更新处理过程表初试化失败
#define UPDATE_PROC_STATUS_S_FAILED		NG_STATIONPREPROCESS_ERROR+22  //更新处理过程表开始失败
#define CONFIG_READDEM_PATH_FAILED		NG_STATIONPREPROCESS_ERROR+23  //获取DEM路径失败
#define CHECK_CALC_FUNC_NOT_MATCH		NG_STATIONPREPROCESS_ERROR+24  //检查计算调用函数和处理的函数类型不匹配
#define READ_POPU_INFO_MAP_FAILED		NG_STATIONPREPROCESS_ERROR+25  //读取人口预处理结果信息失败
#define UPDATE_PROC_STATUS_F_FAILED		NG_STATIONPREPROCESS_ERROR+26  //更新处理过程表状态完成失败
#define READ_PATHLOSS_PREPROC_FAILED    NG_STATIONPREPROCESS_ERROR+27  //获取路损预处理文件失败
#define CALCPROCESS_LICENSE_ERROR		NG_STATIONPREPROCESS_ERROR+28 //计算处理过程狗检测错误
#define PREPROCESS_STASTION_SKIPPED     NG_STATIONPREPROCESS_ERROR+29  //预处理过程部分或全部台站失败
#define NO_VALIDE_GRID                  NG_STATIONPREPROCESS_ERROR+29  //不存在有效的栅格，可能是根据bestserver获取的台站都没有正确从数据库加载


/***********传播模型错误码*******************************************/
#define TRANSMODEL_BASE_ERROR   5000
#define TRANSMODEL_NO_EXIST		TRANSMODEL_BASE_ERROR+1 //传播模型不存在
#define TRANSMODEL533LIB_EXEC_FAIL TRANSMODEL_BASE_ERROR+2 //533库调用失败
#define TRANSMODEL_FREQ_OUTOFRANGE TRANSMODEL_BASE_ERROR+3  //频率超出传播模型适用范围
#define TRNAMODEL_HEIGHT_OUTOFRANGE TRANSMODEL_BASE_ERROR+4  //接收端或发射端天线高度超出传播模型适用范围
#define TRANSMODEL_FREQ_BAND_ERROR	TRANSMODEL_BASE_ERROR+5  //频率带宽参数错误
#define TRANSMODEL_NOT_SAME    TRANSMODEL_BASE_ERROR+6  //内部调用者的传播模型参数不一致
#define NO_TRANSMODEL_PARAM    TRANSMODEL_BASE_ERROR+7  //内部调用者的传播模型参数为空
#define POLYLINE_TOO_FEW_POINT  TRANSMODEL_BASE_ERROR+8  //折线点少于2个
#define TRANSMODEL_NOT_SUPPORT_RESULT_TYPE  TRANSMODEL_BASE_ERROR+9 //传播模型不支持当前计算结果类型
#define STRAIGHT_LINE_IDENTICAL TRANSMODEL_BASE_ERROR+10  //线矢量重合(传播模型)
#define STRAIGHT_LINE_PARALLEL  TRANSMODEL_BASE_ERROR+11  //线矢量平行(传播模型)
#define STRAIGHT_LINE_VERTICAL  TRANSMODEL_BASE_ERROR+12   //线矢量与y轴垂直(传播模型)

#define NG_PropModel_NOProjPath TRANSMODEL_BASE_ERROR + 301                   //传播模型计算未传入项目路径

#define NG_POINTER_CAN_NOT_BE_EMPTY   TRANSMODEL_BASE_ERROR + 325  //ITU电子地图路径为空
#define NG_FAIL_TO_READ_FILE   TRANSMODEL_BASE_ERROR + 326       //读取电子地图失败

#define TRANSMODEL533_BASE_ERROR   5500
#define TRANS533_IONOS_ERROR TRANSMODEL533_BASE_ERROR+1 //电离层参数读取失败
#define TRANS533_REC_TOO_CLOSE_ERROR TRANSMODEL533_BASE_ERROR+2 //接收点距离发射点过近，基本重合
#define TRANS533_ANT_ELEANGLE_TOO_SMALL_ERROR TRANSMODEL533_BASE_ERROR+3 //天线仰角太小，小于门限值
#define TRANS533_DAY_NOELAYER_ERROR TRANSMODEL533_BASE_ERROR+4 //因晚上或者距离太远，不考虑E层场强
#define TRANS533_RESULTTYPE_NOTSUPPORT TRANSMODEL533_BASE_ERROR+5 //短波模型533只支持场强计算


/************模型校正错误码******************************************************************/
#define CALIBRATION_BASE_ERROR   6000
#define CALIBRATION_FREQ_OUTOFRANGE CALIBRATION_BASE_ERROR+1  //频率超出传播模型适用范围
#define CALIBRATION_FAILED          CALIBRATION_BASE_ERROR+2  //模型校正未能正确执行
#define CALIBRATION_TOO_FEW_POINT   CALIBRATION_BASE_ERROR+3  //模型校正文件中点数太少


/************干扰分析错误码******************************************************************/
#define INTERFERENCE_BASE_ERROR   7000
#define NO_MATCH_FREQ   INTERFERENCE_BASE_ERROR+1  //接收站和发射站频率不匹配
#define NO_NEW_INTSTATION		   INTERFERENCE_BASE_ERROR+4 //没有新增干扰站



/************电磁分布计算错误码******************************************************************/
#define EMCCAL_BASE_ERROR   8000
#define NO_SUPPORTED_RESULT_TYPE  EMCCAL_BASE_ERROR+1  //不支持结果类型



/************效能分析计算错误码******************************************************************/
#define PERFROMANCE_BASE_ERROR   9000



/************链路计算错误码******************************************************************/
#define LINKPROFILE_BASE_ERROR   10000
#define FRESNELNUM_ERROR           LINKPROFILE_BASE_ERROR+1 //菲涅尔区号不存在,只有0~5有效
#define LINK_TOO_NEAR              LINKPROFILE_BASE_ERROR+2 //链路距离太近，数值不够
#define NO_LINK_POINTS             LINKPROFILE_BASE_ERROR+3 //没有指定链路


/************频率占用计算错误码******************************************************************/
#define FREQOCCUPY_BASE_ERROR   11000
#define NG_NO_FREQOCCUPY_INTER   FREQOCCUPY_BASE_ERROR+1  //不存在频率上的干扰




/************监测数据压缩处理错误码*************************************************************/
#define COMPRESS_BASE_ERROR   12000
/* 解析数据解压文件失败 */
#define FAIL_TO_RESOLVE_DECOMPRESS_FILE    (COMPRESS_BASE_ERROR + 1)
/* 数据压缩源文件未打开 */
#define THE_COMPRESS_SRC_FILE_NOT_OPEN     (COMPRESS_BASE_ERROR + 2)
/* 数据解压源文件未打开 */
#define THE_DECOMPRESS_SRC_FILE_NOT_OPEN   (COMPRESS_BASE_ERROR + 3)
/* 数据压缩异常 */
#define DATE_COMPRESS_ABNORMAL             (COMPRESS_BASE_ERROR + 4)
/* 数据解压异常 */
#define DATE_DECOMPRESS_ABNORMAL           (COMPRESS_BASE_ERROR + 5)
/* 数据解压正常结束 */
#define DATE_DECOMPRESS_NORMAL_END         (COMPRESS_BASE_ERROR + 6)
/* 当前数据无需执行数据压缩或解压时未使用解压算法 */
#define DATE_COMPRESS_IS_NOT_NEEDED        (COMPRESS_BASE_ERROR + 7)
/* 当前数据解压参数不合理 */
#define DATE_DECOMPRESS_PARA_UNREASONABLE  (COMPRESS_BASE_ERROR + 8)


/************信号识别处理错误码******************************************************************/
#define SIGNAL_BASE_ERROR   13000
/************雷达特征提取 错误码****************/
/* 雷达数据流太短，无法提取特征 */
#define FAIL_TO_GET_RADAR_FEATURE_BY_DATE_SHORT     (SIGNAL_BASE_ERROR + 1)
/* 根据teager能量计算出的有效脉冲个数超过最大值 */
#define POS_INFO_EXCESS_MAX_NUM_BY_TEA_EN           (SIGNAL_BASE_ERROR + 2)
/* 根据瞬时频率计算出的有效脉冲个数超过最大值 */
#define POS_INFO_EXCESS_MAX_NUM_BY_FREQ             (SIGNAL_BASE_ERROR + 3)
/* 合并所有位置信息的个数超过最大值 */
#define COMBINE_POS_NUM_EXCESS_MAX_NUM              (SIGNAL_BASE_ERROR + 4)



/************通信特征提取模块的错误码****************/
/* IQ数据个数为空 */
#define THE_IQ_DATA_LENGTH_IS_NULL                 (SIGNAL_BASE_ERROR + 20)
/* 门限参数未设置*/
#define THE_THRESHOLD_IS_NOT_SET                   (SIGNAL_BASE_ERROR + 21)
/*载波频率或者采样频率未设置*/
#define THE_CARR_OR_SAM_FREQ_IS_NOT_SET            (SIGNAL_BASE_ERROR + 22)
/*符号速率未设置*/
#define THE_SYMBOL_RATE_IS_NOT_SET                 (SIGNAL_BASE_ERROR + 23)
/*采样频率过低*/
#define THE_SAMPLE_FREQ_IS_ILLEGAL                 (SIGNAL_BASE_ERROR + 24)
/*读取CSV文件头失败*/
#define FAIL_TO_READ_CSV_FILE                      (SIGNAL_BASE_ERROR + 25)
/* 未进行FFT变换 */
#define THE_FFT_DATE_IS_NULL                       (SIGNAL_BASE_ERROR + 27) 
/* FFT失败 */
#define FAIL_TO_FFT_TRANSFORM                      (SIGNAL_BASE_ERROR + 28) 
/* 计算通信信号特征参数失败 */
#define FAIL_TO_CAL_FEATURE_PARA                   (SIGNAL_BASE_ERROR + 29)

/******************训练样本******************/
/* 雷达样本数据流过短,导致提取的特征无法建模 ，无法处理  */
#define THE_RADAR_DATA_LENGTH_IS_SHORT             (SIGNAL_BASE_ERROR + 40)
/* 特征集文件路径未设置*/
#define THE_FEATURE_RESULT_FILE_PATH_IS_NOT_SET    (SIGNAL_BASE_ERROR + 41)
/* 打开特征集文件失败*/
#define FAIL_TO_OPEN_FEATURE_RESULT_FILE           (SIGNAL_BASE_ERROR + 42)
/* 文件名路径长度太长 */
#define THE_FILE_PATH_IS_TOO_LONG                  (SIGNAL_BASE_ERROR + 43)
/* 未设置采样率 */ 
#define THE_SAMPLE_RATE_IS_NULL                    (SIGNAL_BASE_ERROR + 44) 
/* 未设置信号类型  */
#define THE_SIGNAL_TYPE_IS_NULL                    (SIGNAL_BASE_ERROR + 45) 

/******************信号识别错误码**************************************************/
/* 样本库文件路径未设置*/
#define THE_MODEL_FILE_PATH_IS_NOT_SET               (SIGNAL_BASE_ERROR + 60)
/* 信号特征文本 路径未设置*/
#define THE_FEATURE_FILE_PATH_IS_NOT_SET             (SIGNAL_BASE_ERROR + 61)
/* 识别结果文件路径未设置*/
#define THE_RECOGNITION_RESULT_FILE_PATH_IS_NOT_SET  (SIGNAL_BASE_ERROR + 62)
/* 打开识别结果文件失败*/
#define FAIL_TO_OPEN_RECOGNITION_RESULT_FILE         (SIGNAL_BASE_ERROR + 63)
/* 原始信号文件路径未设置*/
#define THE_SRC_FILE_PATH_IS_NOT_SET                 (SIGNAL_BASE_ERROR + 64)
/* 打开样本库文件失败 */
#define FAIL_TO_OPEN_MODEL_FILE                      (SIGNAL_BASE_ERROR + 65)
/* 解析台站类型表失败 */
#define FAIL_TO_RESOLVE_STATION_TYPE_TABLE           (SIGNAL_BASE_ERROR + 66)
/* 台站类型表无对应台站ID，请确认是否修改过台站类型表 */
#define NO_SPECIAL_STATION_ID_IN_TYPE_TABLE          (SIGNAL_BASE_ERROR + 67)
/* 台站类型表内数据为空 */
#define THE_STATION_TABLE_DATA_IS_NULL               (SIGNAL_BASE_ERROR + 68)
/* 台站类型表与样本库数据不匹配 */
#define THE_LIB_AND_STATION_TABLE_NOT_MATCH          (SIGNAL_BASE_ERROR + 69)
/* 解析样本库数据失败 */
#define FAIL_TO_RESOLVE_SAMPLE_LIB_FILE              (SIGNAL_BASE_ERROR + 70)
/* 读取台站数据库失败 */
#define FAIL_TO_READ_STATION_DATEBASE_INFO           (SIGNAL_BASE_ERROR + 71)
/* 该监测站未训练指纹样本库 */
#define NO_FP_SAMPLE_LIB_FOR_MONI_STATION            (SIGNAL_BASE_ERROR + 72)





/************频谱样本学习 的错误码************************************************************************/
/* 无法创建频谱样本库数据 */
#define FAIL_TO_CREATE_SPECTRUM_LIB_DATE             (SIGNAL_BASE_ERROR + 100)
/* 输入的扫频数据无指定参数的频谱信息  */
#define FAIL_TO_GET_SPECIAL_SPECTRUM_DATE            (SIGNAL_BASE_ERROR + 101)
/* 输入参数内存不足 */
#define THE_INPUT_PARA_MEMORY_IS_SHORT               (SIGNAL_BASE_ERROR + 102)
/* 未找到指定频点 */
#define NO_SPECIAL_FREQ_POINT                        (SIGNAL_BASE_ERROR + 103)
/* 时间范围非法 */
#define ERROR_TO_TIME_RANGE                          (SIGNAL_BASE_ERROR + 104)
/* 频率范围非法 */
#define ERROR_TO_FREQ_RANGE                          (SIGNAL_BASE_ERROR + 105)
/* 读取扫频文件失败 */
#define FAIL_TO_READ_SCAN_FILE                       (SIGNAL_BASE_ERROR + 106)
/* 该监测站还未创建频谱库 */
#define NO_SPECTRUM_LIB_FILE_IN_MONI_STATION         (SIGNAL_BASE_ERROR + 107)

/************文本干扰知识库 的错误码****************/
/* 未发现有效的诊断参数 */
#define NO_VALID_DIAGNOSIS_PARA                      (SIGNAL_BASE_ERROR + 120)
/* 诊断结果为空 */
#define DIAGNOSIS_RESULT_IS_NULL                     (SIGNAL_BASE_ERROR + 121)
/* 文本干扰知识库为空 */
#define THE_TEXT_DATA_BASE_IS_NULL                   (SIGNAL_BASE_ERROR + 122)
/* 原始记录的值为无效值 */
#define THE_SRC_RECORD_VALUE_INVALID                 (SIGNAL_BASE_ERROR + 123)
/* 批量文件内容非法 */
#define THE_BATCH_FILE_INVALID                       (SIGNAL_BASE_ERROR + 124)
/* 字段长度太长 */
#define THE_DIAGNOSIS_LEN_TOO_LONG                   (SIGNAL_BASE_ERROR + 125)
/* 记录文件路径不能为空 */
#define THE_SRC_FILE_PATH_IS_NULL                    (SIGNAL_BASE_ERROR + 126)
/* 记录为空 */
#define THE_RECORD_DATA_IS_NULL                      (SIGNAL_BASE_ERROR + 127)
/* 读取文本干扰数据库失败 */
#define FAIL_TO_READ_TEXT_DATA_BASE                  (SIGNAL_BASE_ERROR + 128)
/* 写文本干扰数据库失败 */
#define FAIL_TO_WRITE_TEXT_DATA_BASE                 (SIGNAL_BASE_ERROR + 129)
/* 起止时间非法 */
#define TIME_BGEIN_END_INVALID                       (SIGNAL_BASE_ERROR + 130)
/* 时间格式非法 */
#define THE_TIME_FORMAT_INVALID                      (SIGNAL_BASE_ERROR + 131)
/* 时间内容无效 */
#define THE_TIME_VALUE_INVALID                       (SIGNAL_BASE_ERROR + 132)
/* 起止频率非法 */
#define FREQ_BGEIN_END_INVALID                       (SIGNAL_BASE_ERROR + 133)




/************监测数据融合处理错误码******************************************************************/
#define FUSION_BASE_ERROR            (14000)               
#define FUSION_INTERPOLATION_ERROR   (FUSION_BASE_ERROR+1) //区域插值错误
#define FUSION_REVISE_ERROR          (FUSION_BASE_ERROR+2) //插值校正错误
#define NO_STATIONID_IN_MONITORFILE   (FUSION_BASE_ERROR+3) //监测数据文件里没有监测站ID


/************保护频段干扰处理错误码******************************************************************/
#define FREQPROTECT_BASE_ERROR   15000
#define  NG_NOPROTECTIONINT      FREQPROTECT_BASE_ERROR+1  //不在保护频率范围内





/************频率指配处理错误码******************************************************************/
#define FREQASSIGN_BASE_ERROR   16000
#define FREQASSIGN_TOO_FEW_FREQ   FREQASSIGN_BASE_ERROR+1  //频点太少
#define FREQASSIGN_QUALITY_BAD    FREQASSIGN_BASE_ERROR+2  //频点信号质量差
#define FREQASSIGN_FREQOFF_SMALL  FREQASSIGN_BASE_ERROR+3  //频差不能满足
#define FREQASSIGN_CALORDER_ERROR  FREQASSIGN_BASE_ERROR+4  //频率指配流程顺序错误
#define FREQASSIGN_NO_CANDIDATEPREQ FREQASSIGN_BASE_ERROR+5 //台站缺失候选频点


/***********用频冲突处理错误码******************************************************************/
#define FREQCONFILICT_BASE_ERROR   17000



/***********部署分析处理错误码******************************************************************/
#define DEPOLY_BASE_ERROR     18000
#define PARAM_CLUSTTER_FREQUENCY_WRONG		(DEPOLY_BASE_ERROR+1) //用频个数和聚类数设置错误
#define PLAN_TIME_ERROR						(DEPOLY_BASE_ERROR+2)  //计划时间错误
#define NOT_COVERAGE						(DEPOLY_BASE_ERROR+3) //最大布站数也达不到覆盖
#define UNSUPPORTED_MAP_COORD 				(DEPOLY_BASE_ERROR+4) //不支持的坐标系，在路线规划中，只支持经纬度坐标
#define NOT_AVAILABLE_ROAD	 				(DEPOLY_BASE_ERROR+5) //区域内没有可行的道路
#define NO_COMMAND_DATE_AVAILABLE			(DEPOLY_BASE_ERROR+6) //没有可用的监测要求，可能原因：设置的部署日期与监测要求提取日期不符
#define COMMAND_AND_WORKMODEL_NOT_MATCH		(DEPOLY_BASE_ERROR+7) //监测要求数和工作模式不匹配
#define COMMAND_PRIORITY_ERROR              (DEPOLY_BASE_ERROR+8) //监测优先级错误，只支持0~5
#define CAL_PRIORITY_TYPE_ERROR             (DEPOLY_BASE_ERROR+9) //计算监测优先级类型错误，只支持0~1
#define TIME_TYPEL_NO_EXIST                 (DEPOLY_BASE_ERROR+10) //时间类型类型错误，只支持0~4
#define WORK_MODEL_TYPE_ERROR                (DEPOLY_BASE_ERROR+11) //监测站工作模型类型错误，只支持1~3
#define MAX_SITE_COUNT_ERROR                (DEPOLY_BASE_ERROR+12) //允许的最大布站数错误，只支持1~200
#define COVERAGE_PER_ERROR                (DEPOLY_BASE_ERROR+13) //目标覆盖错误，只支持1~3
#define SIGNAL_TYPE_ERROR               (DEPOLY_BASE_ERROR+14) //信号类型错误，只支持1~3
#define MONITOR_TIME_ERROR                (DEPOLY_BASE_ERROR+15) //监测时间错误，必须按指定格式输入，时间跨度最大是两年
#define RADAR_DETECT_PROB_ERROR           (DEPOLY_BASE_ERROR+16) //雷达侦听概率参数错误，只支持0-100
#define RADAR_FALSE_PROB_ERROR            (DEPOLY_BASE_ERROR+17) //雷达虚警概率参数错误，只支持0-100
#define RADAR_MINRCS_ERROR		           (DEPOLY_BASE_ERROR+18) //雷达最小目标截面积参数错误



/******************保护率文件****************************************************/
#define  PROTECTION_BASE_ERROR   19000
#define  NONOPROTECTIONFILE      PROTECTION_BASE_ERROR+0  //保护率文件不存在
 
/******************等值线面提取错误码****************************************************/
#define  ISOSURFACE_BASE_ERROR   20000  
#define  CANNOTEXTRACTCONTOUR    ISOSURFACE_BASE_ERROR+1 //无法提取等值线




/******************互调干扰错误码****************************************************/
#define INTERMODULATION_BASE_ERROR  21000
#define INTERMODULATIONORDER_ERROR  INTERMODULATION_BASE_ERROR+1 //互调阶数错误,只支持3,5


/******************环境配置错误码****************************************************/
#define PROJECTCONFIG_BASE_ERROR  22000
#define DATABASE_CONFIG_ERROR    PROJECTCONFIG_BASE_ERROR+1 //数据库配置错误
#define MAP_CONFIG_ERROR         PROJECTCONFIG_BASE_ERROR+2 //地图配置错误
#define USER_CAL_PARAM_ERROR     PROJECTCONFIG_BASE_ERROR+3 //用户设置的参数文件错误
#define TRANSMODEL_CONFIG_ERROR  PROJECTCONFIG_BASE_ERROR+4 //传播模型初始化失败
#define PATHLOSS_PATH_CONFIG_ERROR PROJECTCONFIG_BASE_ERROR+5 //路径损耗路径配置错误
#define USER_TERMINATED_ERROR    PROJECTCONFIG_BASE_ERROR+6 //用户取消处理
#define POPULATION_FILE_ERROR    PROJECTCONFIG_BASE_ERROR+7 //人口文件配置错误

/******************谐波干扰错误码****************************************************/
#define HARMONICSINT_BASE_ERROR  23000
#define HARMONICSPARAM_ERROR  HARMONICSINT_BASE_ERROR+1 //谐波数错误,只支持2,到13

/******************边境协调错误码****************************************************/
#define BoundaryCoordinate_BASE_ERROR  24000
#define NO_INTERFERENCE    BoundaryCoordinate_BASE_ERROR+1 //边界与覆盖轮廓线没有交集，不存在干扰
#define AREA_INCLUDE       BoundaryCoordinate_BASE_ERROR+2 //两区域出于包含与被包含的关系


/*******************TDOA错误码************************************************************************/
#define TDOA_BASE_ERROR  25000
#define STATIONS_NOT_ENOUGH TDOA_BASE_ERROR+1 //监测站数目不够，必须是3个以上
#define SIGNAL_NO_CROSSRELATION TDOA_BASE_ERROR+2 //信号相关性不够
#define  TIME_NO_MIXED TDOA_BASE_ERROR+3                       //信号时间没有交集，时间同步失败
#define FILE_NUM_NOT_EQUAL_STATION TDOA_BASE_ERROR+4                      //文件数目和监测站数目不等
#define UNSUPPORT_LOCATIONTYPE   TDOA_BASE_ERROR+5                     //不支持的定位方式

#define RESULT_BAD TDOA_BASE_ERROR+6                        //信号太差，定位得到的结果太差

/*******************AOA错误码************************************************************************/
#define AOA_BASE_ERROR  26000
#define NO_SOURCE_IN_MONITOR_AREA AOA_BASE_ERROR+1 //监测范围内无指定频率发射源
#define AZIMUTH_CALCULATE_EXCEPTION AOA_BASE_ERROR+2 //方位角计算异常



/*******************发射源轨迹追踪错误码************************************************************************/
#define SOURCETRACK_BASE_ERROR  27000
#define STATION_NOT_RECEIVE_SIGNAL SOURCETRACK_BASE_ERROR+1 //文件中的信号强度为-150bm一下



/*******************发射源区域快速分析错误码************************************************************************/
#define SOURCEANALYSIS_BASE_ERROR  28000

#define SOURCEAREAR_COMPUTE_PARAM_ERROR   1+SOURCEANALYSIS_BASE_ERROR      //EMC计算参数错误,可认为没有读取到计算参数
#define SOURCEAREAR_MONITOR_DATA_ERROR    2+SOURCEANALYSIS_BASE_ERROR      //监测数据文件读取错误
#define SOURCEAREAR_DATA_NO_MATCH_EROR    3+SOURCEANALYSIS_BASE_ERROR     //无监测数据与监测站匹配
#define SOURCEAREAR_UNSUPPORT_DATATYPE    4+SOURCEANALYSIS_BASE_ERROR     //监测数据只支持dbm单位



/*******************站址选择错误码************************************************************************/
#define SITESELECTION_BASE_ERROR  29000
#define EVALUATECOVERRADIUS_ERROR        SITESELECTION_BASE_ERROR+1     //评估覆盖半径错误，可能传播模型不适应
#define SITESELECTION_NO_VALIDPOINT      SITESELECTION_BASE_ERROR+2     //合适的候选位置太少，可能水域太多



/*******************台站工作情况错误码************************************************************************/
#define SITEWORKSTATUS_BASE_ERROR  30000






/*******************频谱分析错误码************************************************************************/
#define SPECTRUMANALYSIS_BASE_ERROR  31000


/*******************信号压制错误码************************************************************************/
#define SIGNALSUPPERSSION_ERROR  32000
#define NO_MATCH_INTSTATION    SIGNALSUPPERSSION_ERROR+1  //没有一个干扰站与待压制的频段匹配
#define NO_EXIST_INTER			SIGNALSUPPERSSION_ERROR+2 //不存在被压制的信号
#define NO_SUPPORTED_MULTIPLE_FREQ	SIGNALSUPPERSSION_ERROR+3 //不支持多个频段同时压制
#define NO_POWERLIST			SIGNALSUPPERSSION_ERROR+4   //没有候选功率
#define	NUMBER_CROSS_THE_BOUNDARY SIGNALSUPPERSSION_ERROR+5 //台站数越界
#define NO_COVERAGE			   SIGNALSUPPERSSION_ERROR+6  //达不到覆盖



/*******************台站统计分析************************************************************************/
#define STATISTICREPORT_ERROR  33000
#define NO_TIMEINFO      STATISTICREPORT_ERROR+1  //没有时间信息 
#define NO_SIMULATORINFO      STATISTICREPORT_ERROR+2  //没有仿真信息 
#define MONITOR_FREQ_TOO_LESS STATISTICREPORT_ERROR+3  //监测文件频点太少
#define NO_COVERED_STATION    STATISTICREPORT_ERROR+4  //无覆盖台站（预估半径筛选）

/*******************边界协调错误码************************************************************************/
#define BOUNDARYCORRDINATION_ERROR  34000
#define READ_ROADVECTORFILE_ERROR    BOUNDARYCORRDINATION_ERROR+1  //读取道路矢量文件失败
#define NO_SUPPORTED_CALCULATEAREA   BOUNDARYCORRDINATION_ERROR+2  //不支持的计算区域类型
#define GET_ROADVECTOR_ERROR         BOUNDARYCORRDINATION_ERROR+3  //获取边界矢量失败，可能原因为计算区域与边界线没有交集

/*******************健康安全区分析错误码************************************************************************/
#define HEALTHAREAANANLYSIS_ERROR  35000
#define NO_EXIST_STRONG_RADIATION    HEALTHAREAANANLYSIS_ERROR+1  //不存在强辐射，没有健康隐患
//#define    HEALTHAREAANANLYSIS_ERROR+2  //不支持的计算区域类型


/************监测数据处理模块的错误码****************/
#define  MONITORDATAANALYSIS_ERROR  36000
#define  FREQUENCY_OUTOF_MONITORDATA  MONITORDATAANALYSIS_ERROR+1 //设置的频率范围不在监测数据的频段范围内
#define  TIME_OUTOF_MONITORDATA  MONITORDATAANALYSIS_ERROR+2 //设置的时间范围不在监测数据的时间范围内
#define  TOO_FEW_DATARECORD      MONITORDATAANALYSIS_ERROR+3 //监测数据记录太短
#define  PREPROCESS_ERROR        MONITORDATAANALYSIS_ERROR+4 //监测数据预处理失败
#define  INVALIDSCANFORMAT       MONITORDATAANALYSIS_ERROR+5 //无效的监测数据扫频格式
#define  STANDDATAFREQ_NOTMATCH       MONITORDATAANALYSIS_ERROR+6 //国家扫频文件名频率信息与数据信息不一致
#define  FILTER_NOISE_FREQUENCY_ERROR MONITORDATAANALYSIS_ERROR+7 //去噪时,每条记录对应频点不同
#define  STANDCHECKCODE_ERROR    MONITORDATAANALYSIS_ERROR+8  //国家扫频文件数据校验码错误
#define  NG_MONITORFILE_OPEN_ERROR    MONITORDATAANALYSIS_ERROR+9  //监测文件打开失败

#define NATURALBASECODE 37000
#define DRIVER_TEST_POINT_NOT_ENOUGTH NATURALBASECODE+10//路测点太少


//台站信号自动分析
#define NG_SIGNAL_DIS_BASECODE 38000
#define NO_TARGET_FREQ NG_SIGNAL_DIS_BASECODE + 1 //无法从台站和扫频中读取该频段信息





/*******************区域干扰分析错误码************************************************************************/
#define AREAINTERFERENCEANANLYSIS_ERROR  39000
#define TX_STATION_NO_COVERAGE    AREAINTERFERENCEANANLYSIS_ERROR+1  //预接收台站对计算区域无覆盖
#define NEW_STATION_NO_COVERAGE    AREAINTERFERENCEANANLYSIS_ERROR+2  //新建台站对计算区域无覆盖


//pathloss预处理
#define NG_PATHLOSSPREPROCESS_BASECODE 40000 
#define NG_NOBYPREPROCESS   NG_PATHLOSSPREPROCESS_BASECODE+1  //不走预处理流程，非错误码
#define PATHLOSS_NO_FILE_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+2  //读取文件失败，文件不存在
#define PATHLOSS_NO_MATCHED_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+3  //小区位置没有匹配预处理结果
#define PATHLOSS_NOT_MATCH_CELLAZ_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+4  //基站方位角不匹配
#define PATHLOSS_NOT_MATCH_CELLEL_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+5  //基站俯仰角不匹配
#define PATHLOSS_NOT_MATCH_ANT_HEIGHT_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+6  //天线高度不匹配
#define PATHLOSS_NOT_MATCH_TRAN_MODEL_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+7  //传播模型不匹配
#define PATHLOSS_NOT_MATCH_FREQ_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+8  //频率不匹配
#define PATHLOSS_NOT_MATCH_RADIUS_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+9  //计算半径不匹配
#define PATHLOSS_NOT_MATCH_RECV_HEIGHT_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+10  //接收高度不匹配


/***********************************导入表固定字段错误码*************************************/
#define NG_WRONGFIELDINEXCELS 41000 
#define NG_RADIO_ASSETS_CLASSIFICATION NG_WRONGFIELDINEXCELS+1//无线电资产分类
#define NG_ASSETS_CLASS_NAME NG_WRONGFIELDINEXCELS+2//资产分类名称
#define NG_ASSETS_SUBCLASS NG_WRONGFIELDINEXCELS+3
#define NG_ACQUISITION_METHOD NG_WRONGFIELDINEXCELS+4//取得方式
#define NG_PROCUREMENT_ORGANIZATION_FORM NG_WRONGFIELDINEXCELS+5//采购组织形式
#define NG_PROPERTY_RIGHTS_FORM NG_WRONGFIELDINEXCELS+6//产权形式
#define NG_USE_STATUS NG_WRONGFIELDINEXCELS+7//使用状况
#define NG_USE_DIRECTION NG_WRONGFIELDINEXCELS+8//使用方向
#define NG_VALUE_TYPE NG_WRONGFIELDINEXCELS+9//价值类型
#define NG_IMPORT_OR_DOMESTIC NG_WRONGFIELDINEXCELS+10//进口/国产
#define NG_STATE_FINANCIAL_APPROPRIATION NG_WRONGFIELDINEXCELS+11//国家财政性拨款
#define NG_LOCAL_FINANCIAL_APPROPRIATION NG_WRONGFIELDINEXCELS+12//地方财政性拨款
#define NG_ASSETS_USE_STATUS NG_WRONGFIELDINEXCELS+13//资产状态


/*******************台站批量导入错误码************************************************************************/
#define NG_STATIONLISTIMPORT_ERROR  42000
#define READ_STATIONFILE_FAILED    NG_STATIONLISTIMPORT_ERROR+1  //读取台站文件失败
#define NO_STSTION_IN_FILE    NG_STATIONLISTIMPORT_ERROR+2  //台站文件中未读到台站数据

/*******************数据库操作错误************************************************************************/
#define NG_DATABASE_ACCESS_ERROR  44000
#define NG_UPDATE_THREAD_STATUS_ERROR   NG_DATABASE_ACCESS_ERROR + 1	// 更新进程状态错误
#define NG_READ_CALC_PARAMETER_ERROR   NG_DATABASE_ACCESS_ERROR + 2		// 读取数据库参数错误
#define NG_UPDATE_FEEDER_STATUS_ERROR   NG_DATABASE_ACCESS_ERROR + 3	// 更新反馈状态错误
#define NG_UPDATE_PROCESS_STATUS_ERROR   NG_DATABASE_ACCESS_ERROR + 4	// 更新计算进程状态错误
#define NG_UPDATE_FUNC_DEFINITION_ERROR   NG_DATABASE_ACCESS_ERROR + 5	// 更新计算参数定义错误

/*******************处理过程错误************************************************************************/
#define NG_PROCESSING_ERROR  45000
#define NG_PROC_CREATE_PREDICTOR_ERROR   NG_PROCESSING_ERROR + 1	// 创建计算单元失败
#define NG_PROC_GEN_CALCAREA_ERROR    NG_PROCESSING_ERROR+2  //获取计算区域错误
#define NG_PROC_NET_TYPE_NOTVALID_ERROR    NG_PROCESSING_ERROR+3  //计算模块不支持的制式类型错误
#define NG_PROC_POPU_TOTAL_ZERO_ERROR    NG_PROCESSING_ERROR+4  //计算区域内总人口为零
#define NG_PROC_TRANSCAP_EQUA_NOT_SOLVED    NG_PROCESSING_ERROR+5  //UMTS多项式求解错误
#define NG_PROC_RESTATCL_TOO_MANY_CLASSES   NG_PROCESSING_ERROR+6  //重新计算覆盖等级分类超过最大数

/*******************结果处理错误码************************************************************************/
#define RESULT_ERROR_BASE 47000
#define RESULT_ERROR_NO_MEMORY RESULT_ERROR_BASE+1


/***定义内存分配失败的错误码***/
//NGZ内存分配失败
#define NGZ_RASTER_NOMEMORY RESULT_ERROR_NO_MEMORY+1
//NGZS内存分配失败
#define NGZS_RASTER_NOMEMORY RESULT_ERROR_NO_MEMORY+2
//NGR内存分配失败
#define NGR_RASTER_NOMEMORY RESULT_ERROR_NO_MEMORY+3
//NGB内存分配失败
#define NGB_RASTER_NOMEMORY RESULT_ERROR_NO_MEMORY+4

//GridResult 内存分配失败
#define NG_GRID_NOMEMORY RESULT_ERROR_NO_MEMORY+5

//LineResult 内存分配失败
#define NG_LINE_NOMEMORY RESULT_ERROR_NO_MEMORY+6

// 3DResult 内存分配失败
#define NG_3DR_NOMEMORY RESULT_ERROR_NO_MEMORY+6

/***定义其他错误码***/
#define RESULT_ERROR_OT_BASE RESULT_ERROR_BASE+100

//NGZ读文件名为空
#define  NGZ_R_FILENAME_NULL RESULT_ERROR_OT_BASE+1
//NGZ读取失败
#define NGZ_R_FILE_ERROR RESULT_ERROR_OT_BASE+2
//NGZ文件中无数据
#define NGZ_FILE_NULL_DATA RESULT_ERROR_OT_BASE+3
//NGZ取值点超出范围
#define NGZ_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+4
//NGZ写文件为空
#define NGZ_W_FILENAME_NULL RESULT_ERROR_OT_BASE+5
//NGZ写文件失败
#define NGZ_W_FILE_ERROR RESULT_ERROR_OT_BASE+6
//NGZ无数据可写
#define NGZ_W_NODATA RESULT_ERROR_OT_BASE+7

//NGZS读文件名为空
#define NGZS_R_FILENAME_NULL RESULT_ERROR_OT_BASE+11
//NGZS读取失败
#define NGZS_R_FILE_ERROR RESULT_ERROR_OT_BASE+12
//NGZS文件中无数据
#define NGZS_FILE_NULL_DATA RESULT_ERROR_OT_BASE+13
//NGZS取值点超出范围
#define NGZS_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+14
//NGZS写文件为空
#define NGZS_W_FILENAME_NULL RESULT_ERROR_OT_BASE+15
//NGZS写文件失败
#define NGZS_W_FILE_ERROR RESULT_ERROR_OT_BASE+16
//NGZS无数据可写
#define NGZS_W_NODATA RESULT_ERROR_OT_BASE+17

//NGR读文件名为空
#define  NGR_R_FILENAME_NULL RESULT_ERROR_OT_BASE+21
//NGR读取失败
#define NGR_R_FILE_ERROR RESULT_ERROR_OT_BASE+22
//NGR文件中无数据
#define NGR_FILE_NULL_DATA RESULT_ERROR_OT_BASE+23
//NGR取值点超出范围
#define NGR_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+24
//NGR写文件为空
#define NGR_W_FILENAME_NULL RESULT_ERROR_OT_BASE+25
//NGR写文件失败
#define NGR_W_FILE_ERROR RESULT_ERROR_OT_BASE+26
//NGR无数据可写
#define NGR_W_NODATA RESULT_ERROR_OT_BASE+27

//NGB读文件名为空
#define  NGB_R_FILENAME_NULL RESULT_ERROR_OT_BASE+31
//NGB读取失败
#define NGB_R_FILE_ERROR RESULT_ERROR_OT_BASE+32
//NGB文件中无数据
#define NGB_FILE_NULL_DATA RESULT_ERROR_OT_BASE+33
//NGB取值点超出范围
#define NGB_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+34
//NGB写文件为空
#define NGB_W_FILENAME_NULL RESULT_ERROR_OT_BASE+35
//NGB写文件失败
#define NGB_W_FILE_ERROR RESULT_ERROR_OT_BASE+36
//NGB无数据可写
#define NGB_W_NODATA RESULT_ERROR_OT_BASE+37


//NG Grid读文件名为空
#define  NG_GRID_R_FILENAME_NULL RESULT_ERROR_OT_BASE+41
//NG Grid读取失败
#define  NG_GRID_R_FILE_ERROR RESULT_ERROR_OT_BASE+42
//NG Grid文件中无数据
#define NG_GRID_FILE_NULL_DATA RESULT_ERROR_OT_BASE+43
//NG Grid取值点超出范围
#define NG_GRID_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+44
//NG Grid写文件为空
#define NG_GRID_W_FILENAME_NULL RESULT_ERROR_OT_BASE+45
//NG Grid写文件失败
#define NG_GRID_W_FILE_ERROR RESULT_ERROR_OT_BASE+46
//NG Grid无数据可写
#define NG_GRID_W_NODATA RESULT_ERROR_OT_BASE+47


//NG Line读文件名为空
#define  NG_LINE_R_FILENAME_NULL RESULT_ERROR_OT_BASE+51
//NG Line读取失败
#define  NG_LINE_R_FILE_ERROR RESULT_ERROR_OT_BASE+52
//NG Line文件中无数据
#define NG_LINE_FILE_NULL_DATA RESULT_ERROR_OT_BASE+53
//NG Line取值点超出范围
#define NG_LINE_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+54
//NG Line写文件为空
#define NG_LINE_W_FILENAME_NULL RESULT_ERROR_OT_BASE+55
//NG Line写文件失败
#define NG_LINE_W_FILE_ERROR RESULT_ERROR_OT_BASE+56
//NG Line无数据可写
#define NG_LINE_W_NODATA RESULT_ERROR_OT_BASE+57


//NG 3DR读文件名为空
#define  NG_3DR_R_FILENAME_NULL RESULT_ERROR_OT_BASE+61
//NG 3DR读取失败
#define  NG_3DR_R_FILE_ERROR RESULT_ERROR_OT_BASE+62
//NG 3DR文件中无数据
#define NG_3DR_FILE_NULL_DATA RESULT_ERROR_OT_BASE+63
//NG 3DR取值点超出范围
#define NG_3DR_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+64
//NG 3DR写文件为空
#define NG_3DR_W_FILENAME_NULL RESULT_ERROR_OT_BASE+65
//NG 3DR写文件失败
#define NG_3DR_W_FILE_ERROR RESULT_ERROR_OT_BASE+66
//NG 3DR无数据可写
#define NG_3DR_W_NODATA RESULT_ERROR_OT_BASE+67

/************************************************************************/
/* 邻区规划错误码                                                                     */
/************************************************************************/
#define NG_NEIGHBORPLAN_ERROR  48000
#define NG_NO_CELL_STATION             NG_NEIGHBORPLAN_ERROR + 1	//邻区规划中无待规划台站
#define NG_NO_NEIGHBOR_CELL_STATION    NG_NEIGHBORPLAN_ERROR + 2	//邻区规划中无待规划邻区台站
#define NG_READVECTORFROMDB_ERROR      NG_NEIGHBORPLAN_ERROR + 3	//读取邻区规划矢量错误
#define NG_AUTOMANUAL_PARAM_ERROR      NG_NEIGHBORPLAN_ERROR + 4	//邻区规划手动自动参数错误
#define NG_MANUALSITENEIGHBORXML_ERROR NG_NEIGHBORPLAN_ERROR + 5	//手动邻区规划邻区xml配置错误
#define NG_NEIGHBORNETTYPE_ERROR       NG_NEIGHBORPLAN_ERROR + 6	//邻区规划台站类型错误
#define NG_NEIGHBORGAINLOSS_ERROR      NG_NEIGHBORPLAN_ERROR + 7	//自动邻区规划中接收增益损耗参数错误
#define NG_NEIGHBORMAXNUM_ERROR        NG_NEIGHBORPLAN_ERROR + 8	//自动邻区规划中最大邻区个数参数错误
#define NG_READANTENNA_ERROR		   NG_NEIGHBORPLAN_ERROR + 9	//自动邻区规划中从数据库读取参数错误


/************BEGIN: 公共模块错误码**************************/



#define EMC_UNKNOWN_ERROR   NG_UNKNOWN_ERROR
#define EMC_SUCCESS NG_SUCCESS 
#define EMC_PARAMWRONG NG_PARAMWRONG
#define EMC_TRANSMODELWRONG NG_TRANSMODELWRONG 
#define EMC_LICENSEDONGLENOTMATCH NG_LICENSEDONGLENOTMATCH
#define EMC_NORIGHTDONGLE NG_NORIGHTDONGLE
#define EMC_NOSERVERDONGLE NG_NOSERVERDONGLE
#define EMC_NOMODELLICENSE NG_NOMODELLICENSE
#define EMC_LICENSEEXPIRED NG_LICENSEEXPIRED 
#define EMC_OPENLICENSEFILEFAIL NG_OPENLICENSEFILEFAIL
#define EMC_MEMORYWRONG NG_MEMORYWRONG
#define EMC_NOPROTECTIONINT NG_NOPROTECTIONINT
#define EMC_NOAPPROPRIATEMAP NG_NOAPPROPRIATEMAP 
#define EMC_LICENSEWRONG NG_LICENSEWRONG
#define EMC_TIMEMODIFIED NG_TIMEMODIFIED  




//NG_INT32 NG_GetErrorCodeInfo(NG_INT32 lErrCode, NG_UINT8 *&pcErrInfo);
const char * NG_GetErrorCodeMessage(int nCode);
#endif
