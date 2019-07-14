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
#define HEIGHT_TYOE_ERROR                  BASE_ERROR+13 //高度类型非法  只支持0-2
#define NG_NO_RESULT_FILE                  BASE_ERROR+14 //没有结果文件
#define NG_CLIENTVERSION_NOTRANSMODE   DONGLE_BASE_ERROR+16 //客户版本未授权该模型
#define NG_FUNCTIONMODEL_NOTRANSMODE   DONGLE_BASE_ERROR+17 //功能模块不支持该传播模型
#define NG_DB_ERROR                        BASE_ERROR+18  //数据库错误
#define NO_AREA_INFO                       BASE_ERROR+19  //没有区域信息
#define NO_MATCH_RESULTFILE	              BASE_ERROR+20  //结果文件数和计算台站数不匹配
#define NG_FUNCTIONMODEL_UNSUPPORT_FREESPACE  BASE_ERROR+21  //功能不支持自由空间模型
#define NG_FREQUENCY_PARAM_ERROR			BASE_ERROR+22	//计算参数：频率范围非法
#define NG_NULL_PROJECTGUID                 BASE_ERROR+23   //Project GUID为空
#define NG_XML_MARK_ERROR                 BASE_ERROR+24   //xml 不是流也不是文件
#define NG_USER_TERMINATE                 BASE_ERROR+100   //用户终止




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
#define REPEAT_PAT_FILE					   FILE_BASE_ERROR+15	 //导入的天线型号在列表中已存在！
#define FILE_FORMAT_ERROR					FILE_BASE_ERROR+16 //数据格式不正确


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
#define NG_CalculateResolution_Error   MAP_BASE_ERROR+14 //计算分辨率有误


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

/*******************健康安全区分析错误码************************************************************************/
#define HEALTHAREAANANLYSIS_ERROR  35000
#define NO_EXIST_STRONG_RADIATION    HEALTHAREAANANLYSIS_ERROR+1  //不存在强辐射，没有健康隐患
//#define    HEALTHAREAANANLYSIS_ERROR+2  //不支持的计算区域类型

/************BEGIN: 公共模块错误码**************************/


/************监测数据处理模块的错误码****************/
#define  MONITORDATAANALYSIS_ERROR  36000
#define  FREQUENCY_OUTOF_MONITORDATA  MONITORDATAANALYSIS_ERROR+1 //设置的频率范围不在监测数据的频段范围内
#define  TIME_OUTOF_MONITORDATA  MONITORDATAANALYSIS_ERROR+2 //设置的时间范围不在监测数据的时间范围内


#define NATURALBASECODE 37000
#define MEMORY_WRONG NATURALBASECODE+2//申请内存失败
#define POINT_CAN_NOT_NULL NATURALBASECODE+3//指针为空
#define PARAM_WRONG NATURALBASECODE+4//参数错误
#define DB_NULL NATURALBASECODE+6//数据库为空
#define FILE_FORM_WRONG NATURALBASECODE+7//文件格式错误
#define TIME_OUT_RANGE NATURALBASECODE+8//超过授权时间
#define NO_SOURCE_FILE NATURALBASECODE+9//没有源文件
#define DRIVER_TEST_POINT_NOT_ENOUGTH NATURALBASECODE+10//路测点太少
#define NO_PARAM NATURALBASECODE +11 //没有输入参数
#define NO_TRAGET_FREQ_FILE NATURALBASECODE + 12 //没有对应的频点文件
#define PATH_NOT_ACCESS NATURALBASECODE +13 //文件夹无访问权限

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
#define XML_STATION_PARAM_ERROR   STATION_BASE_ERROR+10 //xml中台站参数错误

#define LOCATION_PARAMETER_RANGE_IS_ILLEGAL			STATION_BASE_ERROR+21  //台站位置参数范围非法 只支持(经度-180~180 纬度-90~90)m
#define HEIGHT_PARAMETER_RANGE_IS_ILLEGAL			STATION_BASE_ERROR+22  //计算高度参数范围非法 只支持(0~1000)m
#define POWER_PARAMETER_RANGE_IS_ILLEGAL			STATION_BASE_ERROR+23  //发射功率参数范围非法 只支持(-4~90)dBm
#define THRESHOLDDBM_PARAMETER_RANGE_IS_ILLEGAL		STATION_BASE_ERROR+24  //计算门限参数范围非法 只支持(-120~-50)dBm
#define THRESHOLDDBUVM_PARAMETER_RANGE_IS_ILLEGAL	STATION_BASE_ERROR+25  //计算门限参数范围非法 只支持(20~70)dBuV/m
#define CITHRESHOLD_PARAMETER_RANGE_IS_ILLEGAL		STATION_BASE_ERROR+26  //计算CI门限参数范围非法 只支持(-50~50)dB
#define AZIMUTH_PARAMETER_RANGE_IS_ILLEGAL			STATION_BASE_ERROR+27  //方位角参数范围非法 只支持(0~360)度
#define DOWNTILT_PARAMETER_RANGE_IS_ILLEGAL			STATION_BASE_ERROR+28  //下倾角参数范围非法 只支持(-90~90)度
#define GAIN_PARAMETER_RANGE_IS_ILLEGAL				STATION_BASE_ERROR+29  //天线增益范围非法 只支持(-50~50)dBi
#define LOSS_PARAMETER_RANGE_IS_ILLEGAL				STATION_BASE_ERROR+30  //天线损耗范围非法 只支持(-100~100)dB
#define FREQUENCY_PARAMETER_RANGE_IS_ILLEGAL		STATION_BASE_ERROR+31  //频率范围非法 只支持((1*1e-6)~300000)MHz
#define XML_RXHEIGHT_PARAM_ERROR					STATION_BASE_ERROR+32  //xml中接收高度参数错误
#define SNR_PARAMETER_RANGE_IS_ILLEGAL				STATION_BASE_ERROR+33  //信噪比范围非法 只支持【5,30】dB
#define CONBINETYPE_RANGE_IS_ILLEGAL				STATION_BASE_ERROR+34  //合并类型范围非法，0:叠加,1:取最大值


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
#define NO_TRANSMODEL			TRANSMODEL_BASE_ERROR+13  //未指定计算传播模型

#define TRANSMODEL533_BASE_ERROR   5500
#define TRANS533_IONOS_ERROR TRANSMODEL533_BASE_ERROR+1 //电离层参数读取失败
#define TRANS533_REC_TOO_CLOSE_ERROR TRANSMODEL533_BASE_ERROR+2 //接收点距离发射点过近，基本重合
#define TRANS533_ANT_ELEANGLE_TOO_SMALL_ERROR TRANSMODEL533_BASE_ERROR+3 //天线仰角太小，小于门限值
#define TRANS533_DAY_NOELAYER_ERROR TRANSMODEL533_BASE_ERROR+4 //天线仰角太小，小于门限值

#define TRANSMODEL533_BASE_ERROR   5500
#define TRANS533_IONOS_ERROR TRANSMODEL533_BASE_ERROR+1 //电离层参数读取失败
#define TRANS533_REC_TOO_CLOSE_ERROR TRANSMODEL533_BASE_ERROR+2 //接收点距离发射点过近，基本重合
#define TRANS533_ANT_ELEANGLE_TOO_SMALL_ERROR TRANSMODEL533_BASE_ERROR+3 //天线仰角太小，小于门限值
#define TRANS533_DAY_NOELAYER_ERROR TRANSMODEL533_BASE_ERROR+4 //因晚上或者距离太远，不考虑E层场强
#define TRANS533_RESULTTYPE_NOTSUPPORT TRANSMODEL533_BASE_ERROR+5 //短波模型533只支持场强计算
#define TRANS533_MAP_NOTSUPPORT TRANSMODEL533_BASE_ERROR+6 //短波模型533只支持经纬度地图
#define TRANS533_LATITUDE_OUT TRANSMODEL533_BASE_ERROR+7 //短波模型533计算点纬度超过[-90，90]范围
#define TRANS533_UTCHOUR_OUT TRANSMODEL533_BASE_ERROR+8 //短波模型533计算设置的时间超过[0，24]范围

/************模型校正错误码******************************************************************/
#define CALIBRATION_BASE_ERROR   6000
#define CALIBRATION_FREQ_OUTOFRANGE CALIBRATION_BASE_ERROR+1  //频率超出传播模型适用范围
#define CALIBRATION_FAILED          CALIBRATION_BASE_ERROR+2  //模型校正未能正确执行
#define CALIBRATION_TWO_FEW_POINT   CALIBRATION_BASE_ERROR+3  //模型校正文件中点数太少


/************干扰分析错误码******************************************************************/
#define INTERFERENCE_BASE_ERROR   7000
#define NO_MATCH_FREQ   INTERFERENCE_BASE_ERROR+1  //接收站和发射站频率不匹配
#define NO_NEW_INTSTATION		   INTERFERENCE_BASE_ERROR+4 //没有新增干扰站
#define ON_CALCULATE_INT_TYPE      INTERFERENCE_BASE_ERROR+5 //没有指定计算类型
#define RECT_ERROR                 INTERFERENCE_BASE_ERROR+6 //区域信息错误
#define FREQUENCY_ERROR            INTERFERENCE_BASE_ERROR+7//频率信息错误


/************电磁分布计算错误码******************************************************************/
#define EMCCAL_BASE_ERROR   8000
#define NO_SUPPORTED_RESULT_TYPE  EMCCAL_BASE_ERROR+1  //不支持结果类型
#define NO_STATION_IN_SHAP		  EMCCAL_BASE_ERROR+2  //计算区域内无计算台站，无需计算
#define NUSUPPORT_BAND_NULL		  EMCCAL_BASE_ERROR+3  //0带宽不支持计算功率谱通量密度


/************效能分析计算错误码******************************************************************/
#define PERFROMANCE_BASE_ERROR   9000
#define NO_PERFORMANCE_COVERAGE   PERFROMANCE_BASE_ERROR+3  //无覆盖


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
/* 信号长度太短 */
#define THE_SIGNAL_LENGTH_TOO_SHORT                (SIGNAL_BASE_ERROR + 30)
/* 计算码元宽度失败 */
#define FAIL_TO_CAL_BAUD_WIDTH                     (SIGNAL_BASE_ERROR + 31)

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
/* 该监测站还未创建频谱库*/
#define NO_SPECTRUM_LIB_FILE_IN_MONI_STATION         (SIGNAL_BASE_ERROR + 107)
/*该监测站该时段还未创建频谱库*/
#define NO_SPECTRUM_LIB_FILE_THIS_TIME_RANGE		 (SIGNAL_BASE_ERROR + 108)
/*该频段内未创建频谱库*/
#define NO_SPECTRUM_LIB_FILE_THIS_FREQ_RANGE		 (SIGNAL_BASE_ERROR + 109)
/*此次监管无异常*/
#define NO_ABNORMAL_FREQ							 (SIGNAL_BASE_ERROR + 110)
/*训练过程中发现扫频数据中存在异常频点*/
#define TRAIN_SCAN_FILE_ERROR						 (SIGNAL_BASE_ERROR + 111)
/*训练时扫频数据时间信息有误*/
#define TRAIN_SCAN_FILE_TIME_ERROR					 (SIGNAL_BASE_ERROR + 112)
/*删除训练文件失败*/
#define DELETE_TRAIN_FILE_FAILED					 (SIGNAL_BASE_ERROR + 113)
/*停止训练*/
#define TRAIN_STOP									 (SIGNAL_BASE_ERROR + 114)
/*监管数据少于100条*/
#define SUPERVISE_DATA_SHORT						 (SIGNAL_BASE_ERROR + 115)

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

/************背景频谱库的错误码****************/
#define NG_OPENSPECTRUMDBWRONG						 (SIGNAL_BASE_ERROR + 200)	//打开数据库失败
#define NG_READSPECTRUMDBWRONG						 (SIGNAL_BASE_ERROR + 201) //读背景频谱库失败
#define NG_WRITESPECTRUMDBWRONG						 (SIGNAL_BASE_ERROR + 202) //写背景频谱库失败
#define NG_GETDATABASEERROR							 (SIGNAL_BASE_ERROR + 203) //获取数据库连接失败




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
#define FREQASSIGN_OCCUPYFILE_ERROR  FREQASSIGN_BASE_ERROR+5  //未读取到扫频占用度文件

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
#define BUSINESS_BAND_CONFIG_ERROR PROJECTCONFIG_BASE_ERROR+6 //业务频段路径配置错误
#define BORDER_COORDINATION_CONFIG_ERROR PROJECTCONFIG_BASE_ERROR+7 //协调协议路径配置错误 
#define MAX_COVERAGE_RADIUS_CONFIG_ERROR PROJECTCONFIG_BASE_ERROR+8 //不同功率频率对应的最大半径文件配置错误 
#define LICENSECHECK_PATH_CONFIG_ERROR   PROJECTCONFIG_BASE_ERROR+9   //狗检测文件配置错误


/******************谐波干扰错误码****************************************************/
#define HARMONICSINT_BASE_ERROR  23000
#define HARMONICSPARAM_ERROR  HARMONICSINT_BASE_ERROR+1 //谐波数错误,只支持2,到13

/******************边境协调错误码****************************************************/
#define BoundaryCoordinate_BASE_ERROR  24000
#define NO_INTERFERENCE    BoundaryCoordinate_BASE_ERROR+1 //边界与覆盖轮廓线没有交集，不存在干扰
#define AREA_INCLUDE       BoundaryCoordinate_BASE_ERROR+2 //两区域出于包含与被包含的关系
#define WRONGCLOSEDBOUNDARY BoundaryCoordinate_BASE_ERROR+3 //未找到闭合的边界线
#define CALSITECONTOURWRONG BoundaryCoordinate_BASE_ERROR+4 //计算待协调站轮廓线失败
#define NOT_SUPPORT_FREEMODEL BoundaryCoordinate_BASE_ERROR+5 //自由空间传播模型不适用于边界协调
#define WRONGBORDEREXCELHEADER BoundaryCoordinate_BASE_ERROR+6 //协调文件表头错误

#define CSVWRITE_USE_DATA_TOO_LITTLE BoundaryCoordinate_BASE_ERROR+7   //报表生成用数据量过少
#define CSVFILENETWOKR_TYPE_NOMATCH BoundaryCoordinate_BASE_ERROR+8    //没有匹配的网络制式

/*******************TDOA错误码************************************************************************/
#define TDOA_BASE_ERROR  25000
#define STATIONS_NOT_ENOUGH TDOA_BASE_ERROR+1 //监测站数目不够，必须是3个以上
#define SIGNAL_NO_CROSSRELATION TDOA_BASE_ERROR+2 //信号相关性不够
#define  TIME_NO_MIXED TDOA_BASE_ERROR+3                       //信号时间没有交集，时间同步失败
#define FILE_NUM_NOT_EQUAL_STATION TDOA_BASE_ERROR+4                      //文件数目和监测站数目不等
#define UNSUPPORT_LOCATIONTYPE   TDOA_BASE_ERROR+5                     //不支持的定位方式

#define RESULT_BAD TDOA_BASE_ERROR+6                        //信号太差，定位得到的结果太差

#define SIGNAL_TOO_BAD TDOA_BASE_ERROR+7            //信号啊太差，定位得到的结果准确性太差

#define LESS_3_STATION_RECEIVE_SIGNAL TDOA_BASE_ERROR + 8 //少于3个监测站接收到信号

#define LOCATION_ERROR        TDOA_BASE_ERROR + 10       //监测站经纬度错误

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
#define SITESELECTION_NO_VALIDPOINT      SITESELECTION_BASE_ERROR+2     //预估可用新站址密度已经小于10倍地图分辨率，请检查监测站相关参数设置是否合理
#define SITESELECTION_NO_SITE            SITESELECTION_BASE_ERROR+3           //未设置候选站址
#define SITESELECTION_SITE_FEW           SITESELECTION_BASE_ERROR+4     //拟建站总数小于设定监测类型基本站址数要求


/*******************台站工作情况错误码************************************************************************/
#define SITEWORKSTATUS_BASE_ERROR  30000
#define SITEWORKSTATUS_SUPPORT_ONLY_ONE_STATION SITEWORKSTATUS_BASE_ERROR+1  //目前仅支持一个台站进行工作情况分析
#define NO_TIME_INTERSECTION                    SITEWORKSTATUS_BASE_ERROR+2  //监测文件的监测时间无交集
#define DISMATCH_STATIONS_AND_FILES             SITEWORKSTATUS_BASE_ERROR+3  //监测文件与监测站数目不同
#define NO_FREQUENCY_INTERSECTION               SITEWORKSTATUS_BASE_ERROR+4  //台站频率与监测文件频段无相关性






/*******************频谱分析错误码************************************************************************/
#define SPECTRUMANALYSIS_BASE_ERROR  31000
#define NO_MATCH_RESULTTYPE               SPECTRUMANALYSIS_BASE_ERROR+1  //不匹配的结果类型，只支持功率和场强

/*******************信号压制错误码************************************************************************/
#define SIGNALSUPPERSSION_ERROR  32000
#define NO_MATCH_INTSTATION    SIGNALSUPPERSSION_ERROR+1  //没有一个干扰站与待压制的频段匹配
#define NO_EXIST_INTER			SIGNALSUPPERSSION_ERROR+2 //不存在被压制的信号
#define NO_SUPPORTED_MULTIPLE_FREQ	SIGNALSUPPERSSION_ERROR+3 //不支持多个频段同时压制
#define NO_POWERLIST			SIGNALSUPPERSSION_ERROR+4   //没有候选功率
#define	NUMBER_CROSS_THE_BOUNDARY SIGNALSUPPERSSION_ERROR+5 //台站数越界
#define NO_COVERAGE			   SIGNALSUPPERSSION_ERROR+6  //达不到覆盖
#define NO_EXIST_DEPLOYMENT_AREA  SIGNALSUPPERSSION_ERROR+7   //不存在可部站的区域



/*******************台站统计分析************************************************************************/
#define STATISTICREPORT_ERROR  33000
#define NO_TIMEINFO      STATISTICREPORT_ERROR+1  //没有时间信息 
#define NO_SIMULATORINFO      STATISTICREPORT_ERROR+2  //没有仿真信息 
#define MONITOR_FREQ_TOO_LESS STATISTICREPORT_ERROR+3  //监测文件频点太少
#define NO_COVERED_STATION    STATISTICREPORT_ERROR+4  //无覆盖台站（预估半径筛选）
#define EXCEL_LIB_ERROR       STATISTICREPORT_ERROR+5  //excel库错误

/*******************边界协调错误码************************************************************************/
#define BOUNDARYCORRDINATION_ERROR  34000
#define READ_ROADVECTORFILE_ERROR    BOUNDARYCORRDINATION_ERROR+1  //读取道路矢量文件失败
#define NO_SUPPORTED_CALCULATEAREA   BOUNDARYCORRDINATION_ERROR+2  //不支持的计算区域类型
#define GET_ROADVECTOR_ERROR         BOUNDARYCORRDINATION_ERROR+3  //获取边界矢量失败，可能原因为计算区域与边界线没有交集
#define NO_SUPPORTED_SERVICE_TYPE    BOUNDARYCORRDINATION_ERROR+4  //配置协议文件中无该业务类型协议方案
#define NO_SUPPORTED_FREQ            BOUNDARYCORRDINATION_ERROR+5  //配置协议文件中无某业务类型某业务频点的协议方案

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
#define  INVALID_MONITOR_DATA    MONITORDATAANALYSIS_ERROR+10      //监测文件记录数据无效
#define	 READ_FILE_NEW_MERRORY_ERROR	MONITORDATAANALYSIS_ERROR+11 //读取监测文件申请内存失败


//邻区插值
#define NATURALBASECODE 37000
#define MEMORY_WRONG NATURALBASECODE+2//申请内存失败
#define POINT_CAN_NOT_NULL NATURALBASECODE+3//指针为空
#define PARAM_WRONG NATURALBASECODE+4//参数错误
#define DB_NULL NATURALBASECODE+6//数据库为空
#define FILE_FORM_WRONG NATURALBASECODE+7//文件格式错误
#define TIME_OUT_RANGE NATURALBASECODE+8//超过授权时间
#define NO_SOURCE_FILE NATURALBASECODE+9//没有源文件
#define DRIVER_TEST_POINT_NOT_ENOUGTH NATURALBASECODE+10//路测点太少
#define NO_PARAM NATURALBASECODE +11 //没有输入参数
#define NO_TRAGET_FREQ_FILE NATURALBASECODE + 12 //没有对应的频点文件
#define PATH_NOT_ACCESS NATURALBASECODE +13 //文件夹无访问权限




//台站信号自动分析
#define NG_SIGNAL_DIS_BASECODE 38000
#define NO_TARGET_FREQ NG_SIGNAL_DIS_BASECODE + 1 //无法从台站和扫频中读取该频段信息





/*******************区域干扰分析错误码************************************************************************/
#define AREAINTERFERENCEANANLYSIS_ERROR  39000
#define TX_STATION_NO_COVERAGE    AREAINTERFERENCEANANLYSIS_ERROR+1  //预接收台站对计算区域无覆盖
#define NEW_STATION_NO_COVERAGE    AREAINTERFERENCEANANLYSIS_ERROR+2  //新建台站对计算区域无覆盖
#define NO_COADJ_TXSTATION_COVERAGEAREA AREAINTERFERENCEANANLYSIS_ERROR+3  //新建站覆盖范围内没有预收台，无需计算
#define NEW_STATION_NO_INTER		AREAINTERFERENCEANANLYSIS_ERROR+4  //新建站对计算区域无干扰

/*******************链路干扰分析错误码************************************************************************/
#define LINKINTERFERENCEANANLYSIS_ERROR  39100
#define NO_LINK_TX_STATION				LINKINTERFERENCEANANLYSIS_ERROR+1  //链路干扰无发射站
#define NO_LINK_RE_STATION			    LINKINTERFERENCEANANLYSIS_ERROR+2  //链路干扰无接收站
//#define NO_COADJ_TXSTATION_COVERAGEAREA LINKINTERFERENCEANANLYSIS_ERROR+3  //新建站覆盖范围内没有预收台，无需计算
//#define NEW_STATION_NO_INTER			LINKINTERFERENCEANANLYSIS_ERROR+4  //新建站对计算区域无干扰


//pathloss预处理
#define NG_PATHLOSSPREPROCESS_BASECODE 40000 
#define NG_NOBYPREPROCESS   NG_PATHLOSSPREPROCESS_BASECODE+1  //不走预处理流程，非错误码




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
#define NG_IMPORT_NULLFILE   NG_WRONGFIELDINEXCELS+14//导入文件内容为空
#define NG_IMPORT_FILE_FAIL  NG_WRONGFIELDINEXCELS+15//数据导入失败
#define NG_IMPORT_FILE_PART_FAIL NG_WRONGFIELDINEXCELS+16//部分数据导入失败
#define NG_TABLEHEADERDISMATCHED NG_WRONGFIELDINEXCELS+17//导入文件表头错误
#define NG_IMPORT_FILE_HAS_REPEAT NG_WRONGFIELDINEXCELS+18//部分台站已存在

//设台分析
#define NG_BUILDFREQASSIGN_BASECODE 42000 
#define NG_NO_FREQASSIGN   NG_BUILDFREQASSIGN_BASECODE+1  //不走预处理流程，非错误码


//等值线提取
#define NG_CONTOURLINE_BASECODE 43000 
#define NG_CONTOURLINE_FAILED   NG_CONTOURLINE_BASECODE+1  //等值线提取失败

#define NG_STATION_STATUS_BASECODE 44000
#define NG_STATION_STATUS_NO_MONITOR		NG_STATION_STATUS_BASECODE + 1 //发射站发射覆盖范围内没有监测站
#define NG_STATION_DISTANCE_NO_MONITOR		NG_STATION_STATUS_BASECODE + 2 //发射站一定距离范围内没有监测站


#define NG_FINGERPRINT_BASECODE 45000
#define NG_XML_NO_MONSTATION NG_FINGERPRINT_BASECODE + 1 //输入xml中没有监测站
#define NG_FPRINT_NO_MONSTATION NG_FINGERPRINT_BASECODE + 2 //指纹数据库中没有输入的监测站
#define NG_NO_TX_STATION_FREQRANGE NG_FINGERPRINT_BASECODE + 3 //发射台数据库中没有输入频段的台站
#define NG_NO_TX_STATION_SPECIFIC NG_FINGERPRINT_BASECODE + 4 //发射台数据库中没有指定ID的台站
#define NG_NOT_GIVEN_STATION_SPECIFIC NG_FINGERPRINT_BASECODE + 5 //输出参数xml中没有指定台站ID
#define NG_GIVEN_STATION_NOT_IN_OBJSERVICE NG_FINGERPRINT_BASECODE + 6 //指定台站频率超出指纹库适用频率范围


//网络分析
#define NG_NETANALYSIS_BASECODE 46000 
#define NG_NO_CALTYPE   NG_NETANALYSIS_BASECODE+1  //未定义计算类型
#define NG_NO_COVERAGE  NG_NETANALYSIS_BASECODE+2  //无覆盖，不能计算
#define NG_NO_INT       NG_NETANALYSIS_BASECODE+3  //无干扰，不能计算

//结果错误码，公共库整理过来的，对于所有内存分配失败的错误码,从1~100间设置错误码

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
#define NG_3DR_NOMEMORY RESULT_ERROR_NO_MEMORY+7



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

//电磁环境报告
#define EMEREPORT_ERROR_BASE 48000
#define NO_MONITORFILES EMEREPORT_ERROR_BASE+1//在指定时间和频段范围内无监测数据

//台站监管
#define SITESUPERVISION_ERROR_BASE 49000
#define NO_SPECTRUM_MAP_DATA SITESUPERVISION_ERROR_BASE+1//矢量区域内无频谱地图数据
#define NO_SPECTRUM_MAP_FILE SITESUPERVISION_ERROR_BASE+2//无该频点的预处理文件
#define WRONG_SPECTRUM_FILE_FORMAT SITESUPERVISION_ERROR_BASE+3//预处理文件格式错误
#define TXSTATION_ID_ERROR   SITESUPERVISION_ERROR_BASE+4	//发射台站ID有误（用于生成单个台站监测报告）


#define FINGERPRINT_ERROR_BASE 50000

#define FREQ_NUM_TOO_MUCH FINGERPRINT_ERROR_BASE + 1 //频率监管的频点数目太多
#define NO_TX_SITE_IN_FREQBAND FINGERPRINT_ERROR_BASE + 2 //监管的频段内没有发射台


#define NG_PREPROCESSING_EXE_BASE 51000
#define NG_SERVICEFREQ_DIVISION_XML_READERROR NG_PREPROCESSING_EXE_BASE + 1 //读取频段划分xml时异常
#define NG_PRECAL_XML_READERROR NG_PREPROCESSING_EXE_BASE + 2   //计算参数配置文件读取异常
#define NG_READ_TRANMITTER_RESULTXML_ERROR  NG_PREPROCESSING_EXE_BASE + 3 //读取EMC计算结果索引文件异常
#define NG_PREPROCESS_COMMAND_ERROR NG_PREPROCESSING_EXE_BASE + 4  //命令行参数错误
#define NG_PARAM_NOFREQ_ERROR  NG_PREPROCESSING_EXE_BASE + 5  //没有待计算频段信息
#define NG_PARAM_NOCALPOLYGON_ERROR  NG_PREPROCESSING_EXE_BASE + 6  //没有待计算区域信息
#define NG_CALPOLYGON_XML_READERROR NG_PREPROCESSING_EXE_BASE + 7 //读取计算区域xml时异常
#define NG_NO_CALMAP_ERROR NG_PREPROCESSING_EXE_BASE + 8 //缺少计算地图

//台站工作状态分析
#define NG_STATIONSTATUS_ERROR_BASE 52000
#define NG_ALLSTATIONS_SEARCH_NO_MONITOR	NG_STATIONSTATUS_ERROR_BASE+1 //所有发射站均没有搜到监测站


//二进制结果截取功能
#define NG_RASTERRESULT_CUT_ERROR_BASE 53000
#define NG_ARER_ERROR	NG_RASTERRESULT_CUT_ERROR_BASE+1 //未指定区域
#define NG_NO_IMPORT_COORDSYS NG_RASTERRESULT_CUT_ERROR_BASE+2 //不支持的坐标系，目前只支持经纬度

/*********************************背景噪声提取算法***************************************/
#define EXTRACT_BACKROUND_NOISES_BASE_CODE 54000
#define CALCULATE_SPECTRUM_AVG_ERROR    EXTRACT_BACKROUND_NOISES_BASE_CODE+1 //计算均值频谱失败
#define EIGHTY_PERCENT_METHOD_ERROR     EXTRACT_BACKROUND_NOISES_BASE_CODE+2 //80%方法计算失败
#define NO_VALID_FREQ_ERROR             EXTRACT_BACKROUND_NOISES_BASE_CODE+3 //无有效频率值
#define NOT_INVALID_DELTA_ERROR         EXTRACT_BACKROUND_NOISES_BASE_CODE+4 //超出有效范围的增量值
#define NO_DATA_OF_THE_BAND             EXTRACT_BACKROUND_NOISES_BASE_CODE+5  //无该频段数据

//监测月报
#define NG_MONTH_REPORT_BASECODE 55000
#define NG_TEMPLET_WRONG				NG_MONTH_REPORT_BASECODE + 1 //月报模板格式有误
#define NG_MONITORDATAFILE_ERROR		NG_MONTH_REPORT_BASECODE + 2 //监测文件有误


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
