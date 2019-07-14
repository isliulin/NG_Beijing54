/* ���ļ���������������ж�������Ĵ����룬ÿ��ģ��Ķ����������������ڴ˶��壬����ĸ�ʽ���뱣��ͳһ */
#include "NG_CommonDefine.h"

#ifndef _NG_ERROR_CODE_H
#define _NG_ERROR_CODE_H

#pragma once


/**********************����������*******************************/
#define NG_UNKNOWN_ERROR                   -1    //�����Ĵ��󶼷���-1
#define NG_SUCCESS                         0//�ɹ�

#define BASE_ERROR                         100
#define NG_PARAMWRONG                      BASE_ERROR+1 //��������
#define NG_MEMORYWRONG                     BASE_ERROR+2 //�ڴ�����ʧ��
#define POINTER_CAN_NOT_BE_EMPTY           BASE_ERROR+3 // ָ�벻��Ϊ�� 
#define THE_PARAMETER_FORMAT_IS_ILLEGAL    BASE_ERROR+4 // ������ʽ�Ƿ� 
#define THE_PARAMETER_RANGE_IS_ILLEGAL     BASE_ERROR+5 //������Χ�Ƿ� 
#define FAIL_TO_APPLICATION_NEW_MEMORY     BASE_ERROR+6 // �����ڴ�ʧ��
#define NG_NOTGETRESULT                    BASE_ERROR+7 //û�к��ʵķ���
#define NG_NOTCALCULATE                    BASE_ERROR+8 //δ������Ч����
#define NG_NO_CALCULATE_MODEL			   BASE_ERROR+9 //û�м���ģ��
#define GEOSHAPE_ERROR                     BASE_ERROR+10 //GEOSHPAE���ʹ���
#define INVALID_XMLFILE                    BASE_ERROR+11 //xml�ļ���ʽ�ƻ�
#define UNIT_NO_EXIST                      BASE_ERROR+12 //��λ�Ƿ�  ֻ֧��0-9
#define HEIGHT_TYOE_ERROR                  BASE_ERROR+13 //�߶����ͷǷ�  ֻ֧��0-2
#define NG_NO_RESULT_FILE                  BASE_ERROR+14 //û�н���ļ�
#define NG_CLIENTVERSION_NOTRANSMODE   DONGLE_BASE_ERROR+16 //�ͻ��汾δ��Ȩ��ģ��
#define NG_FUNCTIONMODEL_NOTRANSMODE   DONGLE_BASE_ERROR+17 //����ģ�鲻֧�ָô���ģ��
#define NG_DB_ERROR                        BASE_ERROR+18  //���ݿ����
#define NO_AREA_INFO                       BASE_ERROR+19  //û��������Ϣ
#define NO_MATCH_RESULTFILE	              BASE_ERROR+20  //����ļ����ͼ���̨վ����ƥ��
#define NG_FUNCTIONMODEL_UNSUPPORT_FREESPACE  BASE_ERROR+21  //���ܲ�֧�����ɿռ�ģ��
#define NG_FREQUENCY_PARAM_ERROR			BASE_ERROR+22	//���������Ƶ�ʷ�Χ�Ƿ�
#define NG_NULL_PROJECTGUID                 BASE_ERROR+23   //Project GUIDΪ��
#define NG_XML_MARK_ERROR                 BASE_ERROR+24   //xml ������Ҳ�����ļ�
#define NG_USER_TERMINATE                 BASE_ERROR+100   //�û���ֹ




/*********************�ļ�������****************************************/
#define FILE_BASE_ERROR                    1000
#define FAIL_TO_OPEN_FILE                  FILE_BASE_ERROR+1 // ���ļ�ʧ�� 
#define THE_FILE_IS_NOT_EXIST              FILE_BASE_ERROR+2 // �ļ�������
#define THE_FILE_NAME_TOO_LONG             FILE_BASE_ERROR+3 // �ļ���̫��
#define FAIL_TO_GET_FILE_NAME              FILE_BASE_ERROR+4 //�޷���ȡ����ļ���
#define FAIL_TO_WRITE_FILE                 FILE_BASE_ERROR+5 // д�ļ�ʧ�� 
#define FAIL_TO_CREATE_FILE                FILE_BASE_ERROR+6 // �����ļ�ʧ��
#define FILE_PATH_NULL_ERROR               FILE_BASE_ERROR+7 // �ļ�·��Ϊ��
#define FAIL_TO_READ_FILE                  FILE_BASE_ERROR+8 // ���ļ�ʧ�� 
#define FAIL_TO_DELETE_FILE                FILE_BASE_ERROR+9 // ɾ���ļ�ʧ�� 
#define LACK_DATA_FILE                     (FILE_BASE_ERROR+10) //ȱ�����ļ�
#define FILE_DATA_ERROR                     (FILE_BASE_ERROR+11) //�ļ����ݴ���
#define XML_PARAM_WRONG                    FILE_BASE_ERROR+12    //XML�ļ���������
#define CSV_FORMAT_WRONG                   FILE_BASE_ERROR+13    //CSV�ļ���ʽ����
#define INVALID_MSI_OR_PAT_FILE            FILE_BASE_ERROR+14    //��Ч�������ļ�
#define REPEAT_PAT_FILE					   FILE_BASE_ERROR+15	 //����������ͺ����б����Ѵ��ڣ�
#define FILE_FORMAT_ERROR					FILE_BASE_ERROR+16 //���ݸ�ʽ����ȷ


/***********��������*******************************************/
#define DONGLE_BASE_ERROR   2000
#define NG_LICENSEDONGLENOTMATCH  DONGLE_BASE_ERROR+1  //����license�ļ���ƥ��
#define NG_NORIGHTDONGLE          DONGLE_BASE_ERROR+2   //δ������ȷ��Ӳ����
#define NG_NOSERVERDONGLE         DONGLE_BASE_ERROR+3  //������δ����ָ����Ӳ����
#define NG_NOMODELLICENSE         DONGLE_BASE_ERROR+4  //ģ�� δ��Ȩ
#define NG_LICENSEEXPIRED         DONGLE_BASE_ERROR+5  //license �Ѿ�����
#define NG_OPENLICENSEFILEFAIL    DONGLE_BASE_ERROR+6  //��license �ļ�ʧ��
#define NG_TIMEMODIFIED           DONGLE_BASE_ERROR+7  //��ʱ��۸�
#define NG_TRANSMODELWRONG        DONGLE_BASE_ERROR+8  //����ģ��δ��Ȩ
#define NG_LICENSEWRONG           DONGLE_BASE_ERROR+9 //
#define NG_DONGLECHECK_EXCEPTION  DONGLE_BASE_ERROR+10 //Ӳ�����������쳣
#define NG_TRANSMODELPARAMCREATE_ERROE  DONGLE_BASE_ERROR+11 //����ģ�Ͳ�������ʧ��
#define NG_UNKNOWNLICENSECHECK    DONGLE_BASE_ERROR+12 //δ֪���ܷ�ʽ




/***********��ͼ������*******************************************/
#define MAP_BASE_ERROR   3000
#define NG_NOAPPROPRIATEMAP			MAP_BASE_ERROR+1   //û�к�������ϵ�ĵ�ͼ
#define NG_MAPCOORDNOTMATCH			MAP_BASE_ERROR+2 //��ͼ����ϵ�����Ҫ��ƥ��
#define NG_MAPPARAMWRONG			MAP_BASE_ERROR+3 //��ͼ��������ȷ
#define NG_STATIONMAPNOTMATCH		MAP_BASE_ERROR+4 //̨վ���������ͼ�߽�
#define NG_POINTMAPNOTMATCH			MAP_BASE_ERROR+5 //����㲻�ڵ�ͼ��
#define NG_GETPROFILEWRONG			MAP_BASE_ERROR+6 //��ȡprofile���󣬿���ԭ������ռ����ͽ��շ����λ�ü�����ͬ
#define NG_CALCULATE_SHAP_ERROR		MAP_BASE_ERROR+7 //�����������
#define NG_Resolution_NOTMATCH		MAP_BASE_ERROR+8 //�ֱ��ʲ�ƥ��
#define NG_NO_MAP_DATA				MAP_BASE_ERROR+9 //û�е�ͼ����
#define NG_RESULTCOORDINDEX_SAME    MAP_BASE_ERROR+10 //�������ϵһ�£�����ת��
#define NG_NO_VECTOR_MAP_DATA       MAP_BASE_ERROR+11 //ȱ��ʸ����ͼ 
#define NG_MAP_READ_WRONG           MAP_BASE_ERROR+12 //��ͼ��ȡʧ��
#define NG_NO_INDOOR_TEMPLATE_MAP   MAP_BASE_ERROR+13 //ȱ������ģ���ͼ
#define NG_CalculateResolution_Error   MAP_BASE_ERROR+14 //����ֱ�������


/*******************Ƶ�׷���������************************************************************************/
#define SPECTRUMANALYSIS_BASE_ERROR  31000


/*******************�ź�ѹ�ƴ�����************************************************************************/
#define SIGNALSUPPERSSION_ERROR  32000
#define NO_MATCH_INTSTATION    SIGNALSUPPERSSION_ERROR+1  //û��һ������վ���ѹ�Ƶ�Ƶ��ƥ��
#define NO_EXIST_INTER			SIGNALSUPPERSSION_ERROR+2 //�����ڱ�ѹ�Ƶ��ź�
#define NO_SUPPORTED_MULTIPLE_FREQ	SIGNALSUPPERSSION_ERROR+3 //��֧�ֶ��Ƶ��ͬʱѹ��
#define NO_POWERLIST			SIGNALSUPPERSSION_ERROR+4   //û�к�ѡ����
#define	NUMBER_CROSS_THE_BOUNDARY SIGNALSUPPERSSION_ERROR+5 //̨վ��Խ��
#define NO_COVERAGE			   SIGNALSUPPERSSION_ERROR+6  //�ﲻ������



/*******************̨վͳ�Ʒ���************************************************************************/
#define STATISTICREPORT_ERROR  33000
#define NO_TIMEINFO      STATISTICREPORT_ERROR+1  //û��ʱ����Ϣ 
#define NO_SIMULATORINFO      STATISTICREPORT_ERROR+2  //û�з�����Ϣ 
#define MONITOR_FREQ_TOO_LESS STATISTICREPORT_ERROR+3  //����ļ�Ƶ��̫��
#define NO_COVERED_STATION    STATISTICREPORT_ERROR+4  //�޸���̨վ��Ԥ���뾶ɸѡ��

/*******************�߽�Э��������************************************************************************/
#define BOUNDARYCORRDINATION_ERROR  34000
#define READ_ROADVECTORFILE_ERROR    BOUNDARYCORRDINATION_ERROR+1  //��ȡ��·ʸ���ļ�ʧ��
#define NO_SUPPORTED_CALCULATEAREA   BOUNDARYCORRDINATION_ERROR+2  //��֧�ֵļ�����������

/*******************������ȫ������������************************************************************************/
#define HEALTHAREAANANLYSIS_ERROR  35000
#define NO_EXIST_STRONG_RADIATION    HEALTHAREAANANLYSIS_ERROR+1  //������ǿ���䣬û�н�������
//#define    HEALTHAREAANANLYSIS_ERROR+2  //��֧�ֵļ�����������

/************BEGIN: ����ģ�������**************************/


/************������ݴ���ģ��Ĵ�����****************/
#define  MONITORDATAANALYSIS_ERROR  36000
#define  FREQUENCY_OUTOF_MONITORDATA  MONITORDATAANALYSIS_ERROR+1 //���õ�Ƶ�ʷ�Χ���ڼ�����ݵ�Ƶ�η�Χ��
#define  TIME_OUTOF_MONITORDATA  MONITORDATAANALYSIS_ERROR+2 //���õ�ʱ�䷶Χ���ڼ�����ݵ�ʱ�䷶Χ��


#define NATURALBASECODE 37000
#define MEMORY_WRONG NATURALBASECODE+2//�����ڴ�ʧ��
#define POINT_CAN_NOT_NULL NATURALBASECODE+3//ָ��Ϊ��
#define PARAM_WRONG NATURALBASECODE+4//��������
#define DB_NULL NATURALBASECODE+6//���ݿ�Ϊ��
#define FILE_FORM_WRONG NATURALBASECODE+7//�ļ���ʽ����
#define TIME_OUT_RANGE NATURALBASECODE+8//������Ȩʱ��
#define NO_SOURCE_FILE NATURALBASECODE+9//û��Դ�ļ�
#define DRIVER_TEST_POINT_NOT_ENOUGTH NATURALBASECODE+10//·���̫��
#define NO_PARAM NATURALBASECODE +11 //û���������
#define NO_TRAGET_FREQ_FILE NATURALBASECODE + 12 //û�ж�Ӧ��Ƶ���ļ�
#define PATH_NOT_ACCESS NATURALBASECODE +13 //�ļ����޷���Ȩ��

/***********̨վ������*******************************************/
#define STATION_BASE_ERROR   4000
#define ONE_STATION_IS_NOT_EXIST  STATION_BASE_ERROR+1 //ĳ��̨վ������
#define NO_STATION                STATION_BASE_ERROR+2 //û��һ��̨վ
#define NO_TX_STATION             STATION_BASE_ERROR+3 //û��һ�������
#define NO_RX_STATION             STATION_BASE_ERROR+4 //û��һ�����ջ�
#define NO_MONITOR_STATION        STATION_BASE_ERROR+5 //û��һ�����վ
#define TX_RX_SITE_NO_MATCH		  STATION_BASE_ERROR+6 //��·�����н���վ�ͷ���վ��ƥ��
#define NO_INT_STATION            STATION_BASE_ERROR+7 //û��һ�����Ż�
#define NO_ASSIGN_STATION         STATION_BASE_ERROR+8 //û��ָ��վ
#define SQL_STATION_PARAM_ERROR   STATION_BASE_ERROR+9 //���ݿ�̨վ��������
#define XML_STATION_PARAM_ERROR   STATION_BASE_ERROR+10 //xml��̨վ��������

#define LOCATION_PARAMETER_RANGE_IS_ILLEGAL			STATION_BASE_ERROR+21  //̨վλ�ò�����Χ�Ƿ� ֻ֧��(����-180~180 γ��-90~90)m
#define HEIGHT_PARAMETER_RANGE_IS_ILLEGAL			STATION_BASE_ERROR+22  //����߶Ȳ�����Χ�Ƿ� ֻ֧��(0~1000)m
#define POWER_PARAMETER_RANGE_IS_ILLEGAL			STATION_BASE_ERROR+23  //���书�ʲ�����Χ�Ƿ� ֻ֧��(-4~90)dBm
#define THRESHOLDDBM_PARAMETER_RANGE_IS_ILLEGAL		STATION_BASE_ERROR+24  //�������޲�����Χ�Ƿ� ֻ֧��(-120~-50)dBm
#define THRESHOLDDBUVM_PARAMETER_RANGE_IS_ILLEGAL	STATION_BASE_ERROR+25  //�������޲�����Χ�Ƿ� ֻ֧��(20~70)dBuV/m
#define CITHRESHOLD_PARAMETER_RANGE_IS_ILLEGAL		STATION_BASE_ERROR+26  //����CI���޲�����Χ�Ƿ� ֻ֧��(-50~50)dB
#define AZIMUTH_PARAMETER_RANGE_IS_ILLEGAL			STATION_BASE_ERROR+27  //��λ�ǲ�����Χ�Ƿ� ֻ֧��(0~360)��
#define DOWNTILT_PARAMETER_RANGE_IS_ILLEGAL			STATION_BASE_ERROR+28  //����ǲ�����Χ�Ƿ� ֻ֧��(-90~90)��
#define GAIN_PARAMETER_RANGE_IS_ILLEGAL				STATION_BASE_ERROR+29  //�������淶Χ�Ƿ� ֻ֧��(-50~50)dBi
#define LOSS_PARAMETER_RANGE_IS_ILLEGAL				STATION_BASE_ERROR+30  //������ķ�Χ�Ƿ� ֻ֧��(-100~100)dB
#define FREQUENCY_PARAMETER_RANGE_IS_ILLEGAL		STATION_BASE_ERROR+31  //Ƶ�ʷ�Χ�Ƿ� ֻ֧��((1*1e-6)~300000)MHz
#define XML_RXHEIGHT_PARAM_ERROR					STATION_BASE_ERROR+32  //xml�н��ո߶Ȳ�������
#define SNR_PARAMETER_RANGE_IS_ILLEGAL				STATION_BASE_ERROR+33  //����ȷ�Χ�Ƿ� ֻ֧�֡�5,30��dB
#define CONBINETYPE_RANGE_IS_ILLEGAL				STATION_BASE_ERROR+34  //�ϲ����ͷ�Χ�Ƿ���0:����,1:ȡ���ֵ


/***********����ģ�ʹ�����*******************************************/
#define TRANSMODEL_BASE_ERROR   5000
#define TRANSMODEL_NO_EXIST		TRANSMODEL_BASE_ERROR+1 //����ģ�Ͳ�����
#define TRANSMODEL533LIB_EXEC_FAIL TRANSMODEL_BASE_ERROR+2 //533�����ʧ��
#define TRANSMODEL_FREQ_OUTOFRANGE TRANSMODEL_BASE_ERROR+3  //Ƶ�ʳ�������ģ�����÷�Χ
#define TRNAMODEL_HEIGHT_OUTOFRANGE TRANSMODEL_BASE_ERROR+4  //���ն˻�������߸߶ȳ�������ģ�����÷�Χ
#define TRANSMODEL_FREQ_BAND_ERROR	TRANSMODEL_BASE_ERROR+5  //Ƶ�ʴ����������
#define TRANSMODEL_NOT_SAME    TRANSMODEL_BASE_ERROR+6  //�ڲ������ߵĴ���ģ�Ͳ�����һ��
#define NO_TRANSMODEL_PARAM    TRANSMODEL_BASE_ERROR+7  //�ڲ������ߵĴ���ģ�Ͳ���Ϊ��
#define POLYLINE_TOO_FEW_POINT  TRANSMODEL_BASE_ERROR+8  //���ߵ�����2��
#define TRANSMODEL_NOT_SUPPORT_RESULT_TYPE  TRANSMODEL_BASE_ERROR+9 //����ģ�Ͳ�֧�ֵ�ǰ����������
#define STRAIGHT_LINE_IDENTICAL TRANSMODEL_BASE_ERROR+10  //��ʸ���غ�(����ģ��)
#define STRAIGHT_LINE_PARALLEL  TRANSMODEL_BASE_ERROR+11  //��ʸ��ƽ��(����ģ��)
#define STRAIGHT_LINE_VERTICAL  TRANSMODEL_BASE_ERROR+12   //��ʸ����y�ᴹֱ(����ģ��)
#define NO_TRANSMODEL			TRANSMODEL_BASE_ERROR+13  //δָ�����㴫��ģ��

#define TRANSMODEL533_BASE_ERROR   5500
#define TRANS533_IONOS_ERROR TRANSMODEL533_BASE_ERROR+1 //����������ȡʧ��
#define TRANS533_REC_TOO_CLOSE_ERROR TRANSMODEL533_BASE_ERROR+2 //���յ���뷢�������������غ�
#define TRANS533_ANT_ELEANGLE_TOO_SMALL_ERROR TRANSMODEL533_BASE_ERROR+3 //��������̫С��С������ֵ
#define TRANS533_DAY_NOELAYER_ERROR TRANSMODEL533_BASE_ERROR+4 //��������̫С��С������ֵ

#define TRANSMODEL533_BASE_ERROR   5500
#define TRANS533_IONOS_ERROR TRANSMODEL533_BASE_ERROR+1 //����������ȡʧ��
#define TRANS533_REC_TOO_CLOSE_ERROR TRANSMODEL533_BASE_ERROR+2 //���յ���뷢�������������غ�
#define TRANS533_ANT_ELEANGLE_TOO_SMALL_ERROR TRANSMODEL533_BASE_ERROR+3 //��������̫С��С������ֵ
#define TRANS533_DAY_NOELAYER_ERROR TRANSMODEL533_BASE_ERROR+4 //�����ϻ��߾���̫Զ��������E�㳡ǿ
#define TRANS533_RESULTTYPE_NOTSUPPORT TRANSMODEL533_BASE_ERROR+5 //�̲�ģ��533ֻ֧�ֳ�ǿ����
#define TRANS533_MAP_NOTSUPPORT TRANSMODEL533_BASE_ERROR+6 //�̲�ģ��533ֻ֧�־�γ�ȵ�ͼ
#define TRANS533_LATITUDE_OUT TRANSMODEL533_BASE_ERROR+7 //�̲�ģ��533�����γ�ȳ���[-90��90]��Χ
#define TRANS533_UTCHOUR_OUT TRANSMODEL533_BASE_ERROR+8 //�̲�ģ��533�������õ�ʱ�䳬��[0��24]��Χ

/************ģ��У��������******************************************************************/
#define CALIBRATION_BASE_ERROR   6000
#define CALIBRATION_FREQ_OUTOFRANGE CALIBRATION_BASE_ERROR+1  //Ƶ�ʳ�������ģ�����÷�Χ
#define CALIBRATION_FAILED          CALIBRATION_BASE_ERROR+2  //ģ��У��δ����ȷִ��
#define CALIBRATION_TWO_FEW_POINT   CALIBRATION_BASE_ERROR+3  //ģ��У���ļ��е���̫��


/************���ŷ���������******************************************************************/
#define INTERFERENCE_BASE_ERROR   7000
#define NO_MATCH_FREQ   INTERFERENCE_BASE_ERROR+1  //����վ�ͷ���վƵ�ʲ�ƥ��
#define NO_NEW_INTSTATION		   INTERFERENCE_BASE_ERROR+4 //û����������վ
#define ON_CALCULATE_INT_TYPE      INTERFERENCE_BASE_ERROR+5 //û��ָ����������
#define RECT_ERROR                 INTERFERENCE_BASE_ERROR+6 //������Ϣ����
#define FREQUENCY_ERROR            INTERFERENCE_BASE_ERROR+7//Ƶ����Ϣ����


/************��ŷֲ����������******************************************************************/
#define EMCCAL_BASE_ERROR   8000
#define NO_SUPPORTED_RESULT_TYPE  EMCCAL_BASE_ERROR+1  //��֧�ֽ������
#define NO_STATION_IN_SHAP		  EMCCAL_BASE_ERROR+2  //�����������޼���̨վ���������
#define NUSUPPORT_BAND_NULL		  EMCCAL_BASE_ERROR+3  //0����֧�ּ��㹦����ͨ���ܶ�


/************Ч�ܷ������������******************************************************************/
#define PERFROMANCE_BASE_ERROR   9000
#define NO_PERFORMANCE_COVERAGE   PERFROMANCE_BASE_ERROR+3  //�޸���


/************��·���������******************************************************************/
#define LINKPROFILE_BASE_ERROR   10000
#define FRESNELNUM_ERROR           LINKPROFILE_BASE_ERROR+1 //���������Ų�����,ֻ��0~5��Ч
#define LINK_TOO_NEAR              LINKPROFILE_BASE_ERROR+2 //��·����̫������ֵ����
#define NO_LINK_POINTS             LINKPROFILE_BASE_ERROR+3 //û��ָ����·


/************Ƶ��ռ�ü��������******************************************************************/
#define FREQOCCUPY_BASE_ERROR   11000
#define NG_NO_FREQOCCUPY_INTER   FREQOCCUPY_BASE_ERROR+1  //������Ƶ���ϵĸ���




/************�������ѹ�����������*************************************************************/
#define COMPRESS_BASE_ERROR   12000
/* �������ݽ�ѹ�ļ�ʧ�� */
#define FAIL_TO_RESOLVE_DECOMPRESS_FILE    (COMPRESS_BASE_ERROR + 1)
/* ����ѹ��Դ�ļ�δ�� */
#define THE_COMPRESS_SRC_FILE_NOT_OPEN     (COMPRESS_BASE_ERROR + 2)
/* ���ݽ�ѹԴ�ļ�δ�� */
#define THE_DECOMPRESS_SRC_FILE_NOT_OPEN   (COMPRESS_BASE_ERROR + 3)
/* ����ѹ���쳣 */
#define DATE_COMPRESS_ABNORMAL             (COMPRESS_BASE_ERROR + 4)
/* ���ݽ�ѹ�쳣 */
#define DATE_DECOMPRESS_ABNORMAL           (COMPRESS_BASE_ERROR + 5)
/* ���ݽ�ѹ�������� */
#define DATE_DECOMPRESS_NORMAL_END         (COMPRESS_BASE_ERROR + 6)
/* ��ǰ��������ִ������ѹ�����ѹʱδʹ�ý�ѹ�㷨 */
#define DATE_COMPRESS_IS_NOT_NEEDED        (COMPRESS_BASE_ERROR + 7)
/* ��ǰ���ݽ�ѹ���������� */
#define DATE_DECOMPRESS_PARA_UNREASONABLE  (COMPRESS_BASE_ERROR + 8)


/************�ź�ʶ���������******************************************************************/
#define SIGNAL_BASE_ERROR   13000
/************�״�������ȡ ������****************/
/* �״�������̫�̣��޷���ȡ���� */
#define FAIL_TO_GET_RADAR_FEATURE_BY_DATE_SHORT     (SIGNAL_BASE_ERROR + 1)
/* ����teager�������������Ч��������������ֵ */
#define POS_INFO_EXCESS_MAX_NUM_BY_TEA_EN           (SIGNAL_BASE_ERROR + 2)
/* ����˲ʱƵ�ʼ��������Ч��������������ֵ */
#define POS_INFO_EXCESS_MAX_NUM_BY_FREQ             (SIGNAL_BASE_ERROR + 3)
/* �ϲ�����λ����Ϣ�ĸ����������ֵ */
#define COMBINE_POS_NUM_EXCESS_MAX_NUM              (SIGNAL_BASE_ERROR + 4)



/************ͨ��������ȡģ��Ĵ�����****************/
/* IQ���ݸ���Ϊ�� */
#define THE_IQ_DATA_LENGTH_IS_NULL                 (SIGNAL_BASE_ERROR + 20)
/* ���޲���δ����*/
#define THE_THRESHOLD_IS_NOT_SET                   (SIGNAL_BASE_ERROR + 21)
/*�ز�Ƶ�ʻ��߲���Ƶ��δ����*/
#define THE_CARR_OR_SAM_FREQ_IS_NOT_SET            (SIGNAL_BASE_ERROR + 22)
/*��������δ����*/
#define THE_SYMBOL_RATE_IS_NOT_SET                 (SIGNAL_BASE_ERROR + 23)
/*����Ƶ�ʹ���*/
#define THE_SAMPLE_FREQ_IS_ILLEGAL                 (SIGNAL_BASE_ERROR + 24)
/*��ȡCSV�ļ�ͷʧ��*/
#define FAIL_TO_READ_CSV_FILE                      (SIGNAL_BASE_ERROR + 25)
/* δ����FFT�任 */
#define THE_FFT_DATE_IS_NULL                       (SIGNAL_BASE_ERROR + 27) 
/* FFTʧ�� */
#define FAIL_TO_FFT_TRANSFORM                      (SIGNAL_BASE_ERROR + 28) 
/* ����ͨ���ź���������ʧ�� */
#define FAIL_TO_CAL_FEATURE_PARA                   (SIGNAL_BASE_ERROR + 29)
/* �źų���̫�� */
#define THE_SIGNAL_LENGTH_TOO_SHORT                (SIGNAL_BASE_ERROR + 30)
/* ������Ԫ���ʧ�� */
#define FAIL_TO_CAL_BAUD_WIDTH                     (SIGNAL_BASE_ERROR + 31)

/******************ѵ������******************/
/* �״���������������,������ȡ�������޷���ģ ���޷�����  */
#define THE_RADAR_DATA_LENGTH_IS_SHORT             (SIGNAL_BASE_ERROR + 40)
/* �������ļ�·��δ����*/
#define THE_FEATURE_RESULT_FILE_PATH_IS_NOT_SET    (SIGNAL_BASE_ERROR + 41)
/* ���������ļ�ʧ��*/
#define FAIL_TO_OPEN_FEATURE_RESULT_FILE           (SIGNAL_BASE_ERROR + 42)
/* �ļ���·������̫�� */
#define THE_FILE_PATH_IS_TOO_LONG                  (SIGNAL_BASE_ERROR + 43)
/* δ���ò����� */ 
#define THE_SAMPLE_RATE_IS_NULL                    (SIGNAL_BASE_ERROR + 44) 
/* δ�����ź�����  */
#define THE_SIGNAL_TYPE_IS_NULL                    (SIGNAL_BASE_ERROR + 45) 

/******************�ź�ʶ�������**************************************************/
/* �������ļ�·��δ����*/
#define THE_MODEL_FILE_PATH_IS_NOT_SET               (SIGNAL_BASE_ERROR + 60)
/* �ź������ı� ·��δ����*/
#define THE_FEATURE_FILE_PATH_IS_NOT_SET             (SIGNAL_BASE_ERROR + 61)
/* ʶ�����ļ�·��δ����*/
#define THE_RECOGNITION_RESULT_FILE_PATH_IS_NOT_SET  (SIGNAL_BASE_ERROR + 62)
/* ��ʶ�����ļ�ʧ��*/
#define FAIL_TO_OPEN_RECOGNITION_RESULT_FILE         (SIGNAL_BASE_ERROR + 63)
/* ԭʼ�ź��ļ�·��δ����*/
#define THE_SRC_FILE_PATH_IS_NOT_SET                 (SIGNAL_BASE_ERROR + 64)
/* ���������ļ�ʧ�� */
#define FAIL_TO_OPEN_MODEL_FILE                      (SIGNAL_BASE_ERROR + 65)
/* ����̨վ���ͱ�ʧ�� */
#define FAIL_TO_RESOLVE_STATION_TYPE_TABLE           (SIGNAL_BASE_ERROR + 66)
/* ̨վ���ͱ��޶�Ӧ̨վID����ȷ���Ƿ��޸Ĺ�̨վ���ͱ� */
#define NO_SPECIAL_STATION_ID_IN_TYPE_TABLE          (SIGNAL_BASE_ERROR + 67)
/* ̨վ���ͱ�������Ϊ�� */
#define THE_STATION_TABLE_DATA_IS_NULL               (SIGNAL_BASE_ERROR + 68)
/* ̨վ���ͱ������������ݲ�ƥ�� */
#define THE_LIB_AND_STATION_TABLE_NOT_MATCH          (SIGNAL_BASE_ERROR + 69)
/* ��������������ʧ�� */
#define FAIL_TO_RESOLVE_SAMPLE_LIB_FILE              (SIGNAL_BASE_ERROR + 70)
/* ��ȡ̨վ���ݿ�ʧ�� */
#define FAIL_TO_READ_STATION_DATEBASE_INFO           (SIGNAL_BASE_ERROR + 71)
/* �ü��վδѵ��ָ�������� */
#define NO_FP_SAMPLE_LIB_FOR_MONI_STATION            (SIGNAL_BASE_ERROR + 72)





/************Ƶ������ѧϰ �Ĵ�����************************************************************************/
/* �޷�����Ƶ������������ */
#define FAIL_TO_CREATE_SPECTRUM_LIB_DATE             (SIGNAL_BASE_ERROR + 100)
/* �����ɨƵ������ָ��������Ƶ����Ϣ  */
#define FAIL_TO_GET_SPECIAL_SPECTRUM_DATE            (SIGNAL_BASE_ERROR + 101)
/* ��������ڴ治�� */
#define THE_INPUT_PARA_MEMORY_IS_SHORT               (SIGNAL_BASE_ERROR + 102)
/* δ�ҵ�ָ��Ƶ�� */
#define NO_SPECIAL_FREQ_POINT                        (SIGNAL_BASE_ERROR + 103)
/* ʱ�䷶Χ�Ƿ� */
#define ERROR_TO_TIME_RANGE                          (SIGNAL_BASE_ERROR + 104)
/* Ƶ�ʷ�Χ�Ƿ� */
#define ERROR_TO_FREQ_RANGE                          (SIGNAL_BASE_ERROR + 105)
/* ��ȡɨƵ�ļ�ʧ�� */
#define FAIL_TO_READ_SCAN_FILE                       (SIGNAL_BASE_ERROR + 106)
/* �ü��վ��δ����Ƶ�׿�*/
#define NO_SPECTRUM_LIB_FILE_IN_MONI_STATION         (SIGNAL_BASE_ERROR + 107)
/*�ü��վ��ʱ�λ�δ����Ƶ�׿�*/
#define NO_SPECTRUM_LIB_FILE_THIS_TIME_RANGE		 (SIGNAL_BASE_ERROR + 108)
/*��Ƶ����δ����Ƶ�׿�*/
#define NO_SPECTRUM_LIB_FILE_THIS_FREQ_RANGE		 (SIGNAL_BASE_ERROR + 109)
/*�˴μ�����쳣*/
#define NO_ABNORMAL_FREQ							 (SIGNAL_BASE_ERROR + 110)
/*ѵ�������з���ɨƵ�����д����쳣Ƶ��*/
#define TRAIN_SCAN_FILE_ERROR						 (SIGNAL_BASE_ERROR + 111)
/*ѵ��ʱɨƵ����ʱ����Ϣ����*/
#define TRAIN_SCAN_FILE_TIME_ERROR					 (SIGNAL_BASE_ERROR + 112)
/*ɾ��ѵ���ļ�ʧ��*/
#define DELETE_TRAIN_FILE_FAILED					 (SIGNAL_BASE_ERROR + 113)
/*ֹͣѵ��*/
#define TRAIN_STOP									 (SIGNAL_BASE_ERROR + 114)
/*�����������100��*/
#define SUPERVISE_DATA_SHORT						 (SIGNAL_BASE_ERROR + 115)

/************�ı�����֪ʶ�� �Ĵ�����****************/
/* δ������Ч����ϲ��� */
#define NO_VALID_DIAGNOSIS_PARA                      (SIGNAL_BASE_ERROR + 120)
/* ��Ͻ��Ϊ�� */
#define DIAGNOSIS_RESULT_IS_NULL                     (SIGNAL_BASE_ERROR + 121)
/* �ı�����֪ʶ��Ϊ�� */
#define THE_TEXT_DATA_BASE_IS_NULL                   (SIGNAL_BASE_ERROR + 122)
/* ԭʼ��¼��ֵΪ��Чֵ */
#define THE_SRC_RECORD_VALUE_INVALID                 (SIGNAL_BASE_ERROR + 123)
/* �����ļ����ݷǷ� */
#define THE_BATCH_FILE_INVALID                       (SIGNAL_BASE_ERROR + 124)
/* �ֶγ���̫�� */
#define THE_DIAGNOSIS_LEN_TOO_LONG                   (SIGNAL_BASE_ERROR + 125)
/* ��¼�ļ�·������Ϊ�� */
#define THE_SRC_FILE_PATH_IS_NULL                    (SIGNAL_BASE_ERROR + 126)
/* ��¼Ϊ�� */
#define THE_RECORD_DATA_IS_NULL                      (SIGNAL_BASE_ERROR + 127)
/* ��ȡ�ı��������ݿ�ʧ�� */
#define FAIL_TO_READ_TEXT_DATA_BASE                  (SIGNAL_BASE_ERROR + 128)
/* д�ı��������ݿ�ʧ�� */
#define FAIL_TO_WRITE_TEXT_DATA_BASE                 (SIGNAL_BASE_ERROR + 129)
/* ��ֹʱ��Ƿ� */
#define TIME_BGEIN_END_INVALID                       (SIGNAL_BASE_ERROR + 130)
/* ʱ���ʽ�Ƿ� */
#define THE_TIME_FORMAT_INVALID                      (SIGNAL_BASE_ERROR + 131)
/* ʱ��������Ч */
#define THE_TIME_VALUE_INVALID                       (SIGNAL_BASE_ERROR + 132)
/* ��ֹƵ�ʷǷ� */
#define FREQ_BGEIN_END_INVALID                       (SIGNAL_BASE_ERROR + 133)

/************����Ƶ�׿�Ĵ�����****************/
#define NG_OPENSPECTRUMDBWRONG						 (SIGNAL_BASE_ERROR + 200)	//�����ݿ�ʧ��
#define NG_READSPECTRUMDBWRONG						 (SIGNAL_BASE_ERROR + 201) //������Ƶ�׿�ʧ��
#define NG_WRITESPECTRUMDBWRONG						 (SIGNAL_BASE_ERROR + 202) //д����Ƶ�׿�ʧ��
#define NG_GETDATABASEERROR							 (SIGNAL_BASE_ERROR + 203) //��ȡ���ݿ�����ʧ��




/************��������ںϴ��������******************************************************************/
#define FUSION_BASE_ERROR            (14000)               
#define FUSION_INTERPOLATION_ERROR   (FUSION_BASE_ERROR+1) //�����ֵ����
#define FUSION_REVISE_ERROR          (FUSION_BASE_ERROR+2) //��ֵУ������
#define NO_STATIONID_IN_MONITORFILE   (FUSION_BASE_ERROR+3) //��������ļ���û�м��վID


/************����Ƶ�θ��Ŵ��������******************************************************************/
#define FREQPROTECT_BASE_ERROR   15000
#define  NG_NOPROTECTIONINT      FREQPROTECT_BASE_ERROR+1  //���ڱ���Ƶ�ʷ�Χ��





/************Ƶ��ָ�䴦�������******************************************************************/
#define FREQASSIGN_BASE_ERROR   16000
#define FREQASSIGN_TOO_FEW_FREQ   FREQASSIGN_BASE_ERROR+1  //Ƶ��̫��
#define FREQASSIGN_QUALITY_BAD    FREQASSIGN_BASE_ERROR+2  //Ƶ���ź�������
#define FREQASSIGN_FREQOFF_SMALL  FREQASSIGN_BASE_ERROR+3  //Ƶ�������
#define FREQASSIGN_CALORDER_ERROR  FREQASSIGN_BASE_ERROR+4  //Ƶ��ָ������˳�����
#define FREQASSIGN_OCCUPYFILE_ERROR  FREQASSIGN_BASE_ERROR+5  //δ��ȡ��ɨƵռ�ö��ļ�

/***********��Ƶ��ͻ���������******************************************************************/
#define FREQCONFILICT_BASE_ERROR   17000



/***********����������������******************************************************************/
#define DEPOLY_BASE_ERROR     18000
#define PARAM_CLUSTTER_FREQUENCY_WRONG		(DEPOLY_BASE_ERROR+1) //��Ƶ�����;��������ô���
#define PLAN_TIME_ERROR						(DEPOLY_BASE_ERROR+2)  //�ƻ�ʱ�����
#define NOT_COVERAGE						(DEPOLY_BASE_ERROR+3) //���վ��Ҳ�ﲻ������
#define UNSUPPORTED_MAP_COORD 				(DEPOLY_BASE_ERROR+4) //��֧�ֵ�����ϵ����·�߹滮�У�ֻ֧�־�γ������
#define NOT_AVAILABLE_ROAD	 				(DEPOLY_BASE_ERROR+5) //������û�п��еĵ�·
#define NO_COMMAND_DATE_AVAILABLE			(DEPOLY_BASE_ERROR+6) //û�п��õļ��Ҫ�󣬿���ԭ�����õĲ�����������Ҫ����ȡ���ڲ���
#define COMMAND_AND_WORKMODEL_NOT_MATCH		(DEPOLY_BASE_ERROR+7) //���Ҫ�����͹���ģʽ��ƥ��
#define COMMAND_PRIORITY_ERROR              (DEPOLY_BASE_ERROR+8) //������ȼ�����ֻ֧��0~5
#define CAL_PRIORITY_TYPE_ERROR             (DEPOLY_BASE_ERROR+9) //���������ȼ����ʹ���ֻ֧��0~1
#define TIME_TYPEL_NO_EXIST                 (DEPOLY_BASE_ERROR+10) //ʱ���������ʹ���ֻ֧��0~4
#define WORK_MODEL_TYPE_ERROR                (DEPOLY_BASE_ERROR+11) //���վ����ģ�����ʹ���ֻ֧��1~3
#define MAX_SITE_COUNT_ERROR                (DEPOLY_BASE_ERROR+12) //��������վ������ֻ֧��1~200
#define COVERAGE_PER_ERROR                (DEPOLY_BASE_ERROR+13) //Ŀ�긲�Ǵ���ֻ֧��1~3
#define SIGNAL_TYPE_ERROR               (DEPOLY_BASE_ERROR+14) //�ź����ʹ���ֻ֧��1~3
#define MONITOR_TIME_ERROR                (DEPOLY_BASE_ERROR+15) //���ʱ����󣬱��밴ָ����ʽ���룬ʱ�������������
#define RADAR_DETECT_PROB_ERROR           (DEPOLY_BASE_ERROR+16) //�״��������ʲ�������ֻ֧��0-100
#define RADAR_FALSE_PROB_ERROR            (DEPOLY_BASE_ERROR+17) //�״��龯���ʲ�������ֻ֧��0-100
#define RADAR_MINRCS_ERROR		           (DEPOLY_BASE_ERROR+18) //�״���СĿ��������������



/******************�������ļ�****************************************************/
#define  PROTECTION_BASE_ERROR   19000
#define  NONOPROTECTIONFILE      PROTECTION_BASE_ERROR+0  //�������ļ�������
 
/******************��ֵ������ȡ������****************************************************/
#define  ISOSURFACE_BASE_ERROR   20000  




/******************�������Ŵ�����****************************************************/
#define INTERMODULATION_BASE_ERROR  21000
#define INTERMODULATIONORDER_ERROR  INTERMODULATION_BASE_ERROR+1 //������������,ֻ֧��3,5


/******************�������ô�����****************************************************/
#define PROJECTCONFIG_BASE_ERROR  22000
#define DATABASE_CONFIG_ERROR    PROJECTCONFIG_BASE_ERROR+1 //���ݿ����ô���
#define MAP_CONFIG_ERROR         PROJECTCONFIG_BASE_ERROR+2 //��ͼ���ô���
#define USER_CAL_PARAM_ERROR     PROJECTCONFIG_BASE_ERROR+3 //�û����õĲ����ļ�����
#define TRANSMODEL_CONFIG_ERROR  PROJECTCONFIG_BASE_ERROR+4 //����ģ�ͳ�ʼ��ʧ��
#define PATHLOSS_PATH_CONFIG_ERROR PROJECTCONFIG_BASE_ERROR+5 //·�����·�����ô���
#define BUSINESS_BAND_CONFIG_ERROR PROJECTCONFIG_BASE_ERROR+6 //ҵ��Ƶ��·�����ô���
#define BORDER_COORDINATION_CONFIG_ERROR PROJECTCONFIG_BASE_ERROR+7 //Э��Э��·�����ô��� 
#define MAX_COVERAGE_RADIUS_CONFIG_ERROR PROJECTCONFIG_BASE_ERROR+8 //��ͬ����Ƶ�ʶ�Ӧ�����뾶�ļ����ô��� 
#define LICENSECHECK_PATH_CONFIG_ERROR   PROJECTCONFIG_BASE_ERROR+9   //������ļ����ô���


/******************г�����Ŵ�����****************************************************/
#define HARMONICSINT_BASE_ERROR  23000
#define HARMONICSPARAM_ERROR  HARMONICSINT_BASE_ERROR+1 //г��������,ֻ֧��2,��13

/******************�߾�Э��������****************************************************/
#define BoundaryCoordinate_BASE_ERROR  24000
#define NO_INTERFERENCE    BoundaryCoordinate_BASE_ERROR+1 //�߽��븲��������û�н����������ڸ���
#define AREA_INCLUDE       BoundaryCoordinate_BASE_ERROR+2 //��������ڰ����뱻�����Ĺ�ϵ
#define WRONGCLOSEDBOUNDARY BoundaryCoordinate_BASE_ERROR+3 //δ�ҵ��պϵı߽���
#define CALSITECONTOURWRONG BoundaryCoordinate_BASE_ERROR+4 //�����Э��վ������ʧ��
#define NOT_SUPPORT_FREEMODEL BoundaryCoordinate_BASE_ERROR+5 //���ɿռ䴫��ģ�Ͳ������ڱ߽�Э��
#define WRONGBORDEREXCELHEADER BoundaryCoordinate_BASE_ERROR+6 //Э���ļ���ͷ����

#define CSVWRITE_USE_DATA_TOO_LITTLE BoundaryCoordinate_BASE_ERROR+7   //��������������������
#define CSVFILENETWOKR_TYPE_NOMATCH BoundaryCoordinate_BASE_ERROR+8    //û��ƥ���������ʽ

/*******************TDOA������************************************************************************/
#define TDOA_BASE_ERROR  25000
#define STATIONS_NOT_ENOUGH TDOA_BASE_ERROR+1 //���վ��Ŀ������������3������
#define SIGNAL_NO_CROSSRELATION TDOA_BASE_ERROR+2 //�ź�����Բ���
#define  TIME_NO_MIXED TDOA_BASE_ERROR+3                       //�ź�ʱ��û�н�����ʱ��ͬ��ʧ��
#define FILE_NUM_NOT_EQUAL_STATION TDOA_BASE_ERROR+4                      //�ļ���Ŀ�ͼ��վ��Ŀ����
#define UNSUPPORT_LOCATIONTYPE   TDOA_BASE_ERROR+5                     //��֧�ֵĶ�λ��ʽ

#define RESULT_BAD TDOA_BASE_ERROR+6                        //�ź�̫���λ�õ��Ľ��̫��

#define SIGNAL_TOO_BAD TDOA_BASE_ERROR+7            //�źŰ�̫���λ�õ��Ľ��׼ȷ��̫��

#define LESS_3_STATION_RECEIVE_SIGNAL TDOA_BASE_ERROR + 8 //����3�����վ���յ��ź�

#define LOCATION_ERROR        TDOA_BASE_ERROR + 10       //���վ��γ�ȴ���

/*******************AOA������************************************************************************/
#define AOA_BASE_ERROR  26000
#define NO_SOURCE_IN_MONITOR_AREA AOA_BASE_ERROR+1 //��ⷶΧ����ָ��Ƶ�ʷ���Դ
#define AZIMUTH_CALCULATE_EXCEPTION AOA_BASE_ERROR+2 //��λ�Ǽ����쳣



/*******************����Դ�켣׷�ٴ�����************************************************************************/
#define SOURCETRACK_BASE_ERROR  27000
#define STATION_NOT_RECEIVE_SIGNAL SOURCETRACK_BASE_ERROR+1 //�ļ��е��ź�ǿ��Ϊ-150bmһ��



/*******************����Դ������ٷ���������************************************************************************/
#define SOURCEANALYSIS_BASE_ERROR  28000

#define SOURCEAREAR_COMPUTE_PARAM_ERROR   1+SOURCEANALYSIS_BASE_ERROR      //EMC�����������,����Ϊû�ж�ȡ���������
#define SOURCEAREAR_MONITOR_DATA_ERROR    2+SOURCEANALYSIS_BASE_ERROR      //��������ļ���ȡ����
#define SOURCEAREAR_DATA_NO_MATCH_EROR    3+SOURCEANALYSIS_BASE_ERROR     //�޼����������վƥ��
#define SOURCEAREAR_UNSUPPORT_DATATYPE    4+SOURCEANALYSIS_BASE_ERROR     //�������ֻ֧��dbm��λ



/*******************վַѡ�������************************************************************************/
#define SITESELECTION_BASE_ERROR  29000
#define EVALUATECOVERRADIUS_ERROR        SITESELECTION_BASE_ERROR+1     //�������ǰ뾶���󣬿��ܴ���ģ�Ͳ���Ӧ
#define SITESELECTION_NO_VALIDPOINT      SITESELECTION_BASE_ERROR+2     //Ԥ��������վַ�ܶ��Ѿ�С��10����ͼ�ֱ��ʣ�������վ��ز��������Ƿ����
#define SITESELECTION_NO_SITE            SITESELECTION_BASE_ERROR+3           //δ���ú�ѡվַ
#define SITESELECTION_SITE_FEW           SITESELECTION_BASE_ERROR+4     //�⽨վ����С���趨������ͻ���վַ��Ҫ��


/*******************̨վ�������������************************************************************************/
#define SITEWORKSTATUS_BASE_ERROR  30000
#define SITEWORKSTATUS_SUPPORT_ONLY_ONE_STATION SITEWORKSTATUS_BASE_ERROR+1  //Ŀǰ��֧��һ��̨վ���й����������
#define NO_TIME_INTERSECTION                    SITEWORKSTATUS_BASE_ERROR+2  //����ļ��ļ��ʱ���޽���
#define DISMATCH_STATIONS_AND_FILES             SITEWORKSTATUS_BASE_ERROR+3  //����ļ�����վ��Ŀ��ͬ
#define NO_FREQUENCY_INTERSECTION               SITEWORKSTATUS_BASE_ERROR+4  //̨վƵ�������ļ�Ƶ���������






/*******************Ƶ�׷���������************************************************************************/
#define SPECTRUMANALYSIS_BASE_ERROR  31000
#define NO_MATCH_RESULTTYPE               SPECTRUMANALYSIS_BASE_ERROR+1  //��ƥ��Ľ�����ͣ�ֻ֧�ֹ��ʺͳ�ǿ

/*******************�ź�ѹ�ƴ�����************************************************************************/
#define SIGNALSUPPERSSION_ERROR  32000
#define NO_MATCH_INTSTATION    SIGNALSUPPERSSION_ERROR+1  //û��һ������վ���ѹ�Ƶ�Ƶ��ƥ��
#define NO_EXIST_INTER			SIGNALSUPPERSSION_ERROR+2 //�����ڱ�ѹ�Ƶ��ź�
#define NO_SUPPORTED_MULTIPLE_FREQ	SIGNALSUPPERSSION_ERROR+3 //��֧�ֶ��Ƶ��ͬʱѹ��
#define NO_POWERLIST			SIGNALSUPPERSSION_ERROR+4   //û�к�ѡ����
#define	NUMBER_CROSS_THE_BOUNDARY SIGNALSUPPERSSION_ERROR+5 //̨վ��Խ��
#define NO_COVERAGE			   SIGNALSUPPERSSION_ERROR+6  //�ﲻ������
#define NO_EXIST_DEPLOYMENT_AREA  SIGNALSUPPERSSION_ERROR+7   //�����ڿɲ�վ������



/*******************̨վͳ�Ʒ���************************************************************************/
#define STATISTICREPORT_ERROR  33000
#define NO_TIMEINFO      STATISTICREPORT_ERROR+1  //û��ʱ����Ϣ 
#define NO_SIMULATORINFO      STATISTICREPORT_ERROR+2  //û�з�����Ϣ 
#define MONITOR_FREQ_TOO_LESS STATISTICREPORT_ERROR+3  //����ļ�Ƶ��̫��
#define NO_COVERED_STATION    STATISTICREPORT_ERROR+4  //�޸���̨վ��Ԥ���뾶ɸѡ��
#define EXCEL_LIB_ERROR       STATISTICREPORT_ERROR+5  //excel�����

/*******************�߽�Э��������************************************************************************/
#define BOUNDARYCORRDINATION_ERROR  34000
#define READ_ROADVECTORFILE_ERROR    BOUNDARYCORRDINATION_ERROR+1  //��ȡ��·ʸ���ļ�ʧ��
#define NO_SUPPORTED_CALCULATEAREA   BOUNDARYCORRDINATION_ERROR+2  //��֧�ֵļ�����������
#define GET_ROADVECTOR_ERROR         BOUNDARYCORRDINATION_ERROR+3  //��ȡ�߽�ʸ��ʧ�ܣ�����ԭ��Ϊ����������߽���û�н���
#define NO_SUPPORTED_SERVICE_TYPE    BOUNDARYCORRDINATION_ERROR+4  //����Э���ļ����޸�ҵ������Э�鷽��
#define NO_SUPPORTED_FREQ            BOUNDARYCORRDINATION_ERROR+5  //����Э���ļ�����ĳҵ������ĳҵ��Ƶ���Э�鷽��

/*******************������ȫ������������************************************************************************/
#define HEALTHAREAANANLYSIS_ERROR  35000
#define NO_EXIST_STRONG_RADIATION    HEALTHAREAANANLYSIS_ERROR+1  //������ǿ���䣬û�н�������
//#define    HEALTHAREAANANLYSIS_ERROR+2  //��֧�ֵļ�����������


/************������ݴ���ģ��Ĵ�����****************/
#define  MONITORDATAANALYSIS_ERROR  36000
#define  FREQUENCY_OUTOF_MONITORDATA  MONITORDATAANALYSIS_ERROR+1 //���õ�Ƶ�ʷ�Χ���ڼ�����ݵ�Ƶ�η�Χ��
#define  TIME_OUTOF_MONITORDATA  MONITORDATAANALYSIS_ERROR+2 //���õ�ʱ�䷶Χ���ڼ�����ݵ�ʱ�䷶Χ��
#define  TOO_FEW_DATARECORD      MONITORDATAANALYSIS_ERROR+3 //������ݼ�¼̫��
#define  PREPROCESS_ERROR        MONITORDATAANALYSIS_ERROR+4 //�������Ԥ����ʧ��
#define  INVALIDSCANFORMAT       MONITORDATAANALYSIS_ERROR+5 //��Ч�ļ������ɨƵ��ʽ
#define  STANDDATAFREQ_NOTMATCH       MONITORDATAANALYSIS_ERROR+6 //����ɨƵ�ļ���Ƶ����Ϣ��������Ϣ��һ��
#define  FILTER_NOISE_FREQUENCY_ERROR MONITORDATAANALYSIS_ERROR+7 //ȥ��ʱ,ÿ����¼��ӦƵ�㲻ͬ
#define  STANDCHECKCODE_ERROR    MONITORDATAANALYSIS_ERROR+8  //����ɨƵ�ļ�����У�������
#define  NG_MONITORFILE_OPEN_ERROR    MONITORDATAANALYSIS_ERROR+9  //����ļ���ʧ��
#define  INVALID_MONITOR_DATA    MONITORDATAANALYSIS_ERROR+10      //����ļ���¼������Ч
#define	 READ_FILE_NEW_MERRORY_ERROR	MONITORDATAANALYSIS_ERROR+11 //��ȡ����ļ������ڴ�ʧ��


//������ֵ
#define NATURALBASECODE 37000
#define MEMORY_WRONG NATURALBASECODE+2//�����ڴ�ʧ��
#define POINT_CAN_NOT_NULL NATURALBASECODE+3//ָ��Ϊ��
#define PARAM_WRONG NATURALBASECODE+4//��������
#define DB_NULL NATURALBASECODE+6//���ݿ�Ϊ��
#define FILE_FORM_WRONG NATURALBASECODE+7//�ļ���ʽ����
#define TIME_OUT_RANGE NATURALBASECODE+8//������Ȩʱ��
#define NO_SOURCE_FILE NATURALBASECODE+9//û��Դ�ļ�
#define DRIVER_TEST_POINT_NOT_ENOUGTH NATURALBASECODE+10//·���̫��
#define NO_PARAM NATURALBASECODE +11 //û���������
#define NO_TRAGET_FREQ_FILE NATURALBASECODE + 12 //û�ж�Ӧ��Ƶ���ļ�
#define PATH_NOT_ACCESS NATURALBASECODE +13 //�ļ����޷���Ȩ��




//̨վ�ź��Զ�����
#define NG_SIGNAL_DIS_BASECODE 38000
#define NO_TARGET_FREQ NG_SIGNAL_DIS_BASECODE + 1 //�޷���̨վ��ɨƵ�ж�ȡ��Ƶ����Ϣ





/*******************������ŷ���������************************************************************************/
#define AREAINTERFERENCEANANLYSIS_ERROR  39000
#define TX_STATION_NO_COVERAGE    AREAINTERFERENCEANANLYSIS_ERROR+1  //Ԥ����̨վ�Լ��������޸���
#define NEW_STATION_NO_COVERAGE    AREAINTERFERENCEANANLYSIS_ERROR+2  //�½�̨վ�Լ��������޸���
#define NO_COADJ_TXSTATION_COVERAGEAREA AREAINTERFERENCEANANLYSIS_ERROR+3  //�½�վ���Ƿ�Χ��û��Ԥ��̨���������
#define NEW_STATION_NO_INTER		AREAINTERFERENCEANANLYSIS_ERROR+4  //�½�վ�Լ��������޸���

/*******************��·���ŷ���������************************************************************************/
#define LINKINTERFERENCEANANLYSIS_ERROR  39100
#define NO_LINK_TX_STATION				LINKINTERFERENCEANANLYSIS_ERROR+1  //��·�����޷���վ
#define NO_LINK_RE_STATION			    LINKINTERFERENCEANANLYSIS_ERROR+2  //��·�����޽���վ
//#define NO_COADJ_TXSTATION_COVERAGEAREA LINKINTERFERENCEANANLYSIS_ERROR+3  //�½�վ���Ƿ�Χ��û��Ԥ��̨���������
//#define NEW_STATION_NO_INTER			LINKINTERFERENCEANANLYSIS_ERROR+4  //�½�վ�Լ��������޸���


//pathlossԤ����
#define NG_PATHLOSSPREPROCESS_BASECODE 40000 
#define NG_NOBYPREPROCESS   NG_PATHLOSSPREPROCESS_BASECODE+1  //����Ԥ�������̣��Ǵ�����




/***********************************�����̶��ֶδ�����*************************************/
#define NG_WRONGFIELDINEXCELS 41000 
#define NG_RADIO_ASSETS_CLASSIFICATION NG_WRONGFIELDINEXCELS+1//���ߵ��ʲ�����
#define NG_ASSETS_CLASS_NAME NG_WRONGFIELDINEXCELS+2//�ʲ���������
#define NG_ASSETS_SUBCLASS NG_WRONGFIELDINEXCELS+3
#define NG_ACQUISITION_METHOD NG_WRONGFIELDINEXCELS+4//ȡ�÷�ʽ
#define NG_PROCUREMENT_ORGANIZATION_FORM NG_WRONGFIELDINEXCELS+5//�ɹ���֯��ʽ
#define NG_PROPERTY_RIGHTS_FORM NG_WRONGFIELDINEXCELS+6//��Ȩ��ʽ
#define NG_USE_STATUS NG_WRONGFIELDINEXCELS+7//ʹ��״��
#define NG_USE_DIRECTION NG_WRONGFIELDINEXCELS+8//ʹ�÷���
#define NG_VALUE_TYPE NG_WRONGFIELDINEXCELS+9//��ֵ����
#define NG_IMPORT_OR_DOMESTIC NG_WRONGFIELDINEXCELS+10//����/����
#define NG_STATE_FINANCIAL_APPROPRIATION NG_WRONGFIELDINEXCELS+11//���Ҳ����Բ���
#define NG_LOCAL_FINANCIAL_APPROPRIATION NG_WRONGFIELDINEXCELS+12//�ط������Բ���
#define NG_ASSETS_USE_STATUS NG_WRONGFIELDINEXCELS+13//�ʲ�״̬
#define NG_IMPORT_NULLFILE   NG_WRONGFIELDINEXCELS+14//�����ļ�����Ϊ��
#define NG_IMPORT_FILE_FAIL  NG_WRONGFIELDINEXCELS+15//���ݵ���ʧ��
#define NG_IMPORT_FILE_PART_FAIL NG_WRONGFIELDINEXCELS+16//�������ݵ���ʧ��
#define NG_TABLEHEADERDISMATCHED NG_WRONGFIELDINEXCELS+17//�����ļ���ͷ����
#define NG_IMPORT_FILE_HAS_REPEAT NG_WRONGFIELDINEXCELS+18//����̨վ�Ѵ���

//��̨����
#define NG_BUILDFREQASSIGN_BASECODE 42000 
#define NG_NO_FREQASSIGN   NG_BUILDFREQASSIGN_BASECODE+1  //����Ԥ�������̣��Ǵ�����


//��ֵ����ȡ
#define NG_CONTOURLINE_BASECODE 43000 
#define NG_CONTOURLINE_FAILED   NG_CONTOURLINE_BASECODE+1  //��ֵ����ȡʧ��

#define NG_STATION_STATUS_BASECODE 44000
#define NG_STATION_STATUS_NO_MONITOR		NG_STATION_STATUS_BASECODE + 1 //����վ���串�Ƿ�Χ��û�м��վ
#define NG_STATION_DISTANCE_NO_MONITOR		NG_STATION_STATUS_BASECODE + 2 //����վһ�����뷶Χ��û�м��վ


#define NG_FINGERPRINT_BASECODE 45000
#define NG_XML_NO_MONSTATION NG_FINGERPRINT_BASECODE + 1 //����xml��û�м��վ
#define NG_FPRINT_NO_MONSTATION NG_FINGERPRINT_BASECODE + 2 //ָ�����ݿ���û������ļ��վ
#define NG_NO_TX_STATION_FREQRANGE NG_FINGERPRINT_BASECODE + 3 //����̨���ݿ���û������Ƶ�ε�̨վ
#define NG_NO_TX_STATION_SPECIFIC NG_FINGERPRINT_BASECODE + 4 //����̨���ݿ���û��ָ��ID��̨վ
#define NG_NOT_GIVEN_STATION_SPECIFIC NG_FINGERPRINT_BASECODE + 5 //�������xml��û��ָ��̨վID
#define NG_GIVEN_STATION_NOT_IN_OBJSERVICE NG_FINGERPRINT_BASECODE + 6 //ָ��̨վƵ�ʳ���ָ�ƿ�����Ƶ�ʷ�Χ


//�������
#define NG_NETANALYSIS_BASECODE 46000 
#define NG_NO_CALTYPE   NG_NETANALYSIS_BASECODE+1  //δ�����������
#define NG_NO_COVERAGE  NG_NETANALYSIS_BASECODE+2  //�޸��ǣ����ܼ���
#define NG_NO_INT       NG_NETANALYSIS_BASECODE+3  //�޸��ţ����ܼ���

//��������룬��������������ģ����������ڴ����ʧ�ܵĴ�����,��1~100�����ô�����

#define RESULT_ERROR_BASE 47000
#define RESULT_ERROR_NO_MEMORY RESULT_ERROR_BASE+1

/***�����ڴ����ʧ�ܵĴ�����***/
//NGZ�ڴ����ʧ��
#define NGZ_RASTER_NOMEMORY RESULT_ERROR_NO_MEMORY+1
//NGZS�ڴ����ʧ��
#define NGZS_RASTER_NOMEMORY RESULT_ERROR_NO_MEMORY+2
//NGR�ڴ����ʧ��
#define NGR_RASTER_NOMEMORY RESULT_ERROR_NO_MEMORY+3
//NGB�ڴ����ʧ��
#define NGB_RASTER_NOMEMORY RESULT_ERROR_NO_MEMORY+4

//GridResult �ڴ����ʧ��
#define NG_GRID_NOMEMORY RESULT_ERROR_NO_MEMORY+5

//LineResult �ڴ����ʧ��
#define NG_LINE_NOMEMORY RESULT_ERROR_NO_MEMORY+6

// 3DResult �ڴ����ʧ��
#define NG_3DR_NOMEMORY RESULT_ERROR_NO_MEMORY+7



/***��������������***/
#define RESULT_ERROR_OT_BASE RESULT_ERROR_BASE+100

//NGZ���ļ���Ϊ��
#define  NGZ_R_FILENAME_NULL RESULT_ERROR_OT_BASE+1
//NGZ��ȡʧ��
#define NGZ_R_FILE_ERROR RESULT_ERROR_OT_BASE+2
//NGZ�ļ���������
#define NGZ_FILE_NULL_DATA RESULT_ERROR_OT_BASE+3
//NGZȡֵ�㳬����Χ
#define NGZ_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+4
//NGZд�ļ�Ϊ��
#define NGZ_W_FILENAME_NULL RESULT_ERROR_OT_BASE+5
//NGZд�ļ�ʧ��
#define NGZ_W_FILE_ERROR RESULT_ERROR_OT_BASE+6
//NGZ�����ݿ�д
#define NGZ_W_NODATA RESULT_ERROR_OT_BASE+7

//NGZS���ļ���Ϊ��
#define NGZS_R_FILENAME_NULL RESULT_ERROR_OT_BASE+11
//NGZS��ȡʧ��
#define NGZS_R_FILE_ERROR RESULT_ERROR_OT_BASE+12
//NGZS�ļ���������
#define NGZS_FILE_NULL_DATA RESULT_ERROR_OT_BASE+13
//NGZSȡֵ�㳬����Χ
#define NGZS_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+14
//NGZSд�ļ�Ϊ��
#define NGZS_W_FILENAME_NULL RESULT_ERROR_OT_BASE+15
//NGZSд�ļ�ʧ��
#define NGZS_W_FILE_ERROR RESULT_ERROR_OT_BASE+16
//NGZS�����ݿ�д
#define NGZS_W_NODATA RESULT_ERROR_OT_BASE+17

//NGR���ļ���Ϊ��
#define  NGR_R_FILENAME_NULL RESULT_ERROR_OT_BASE+21
//NGR��ȡʧ��
#define NGR_R_FILE_ERROR RESULT_ERROR_OT_BASE+22
//NGR�ļ���������
#define NGR_FILE_NULL_DATA RESULT_ERROR_OT_BASE+23
//NGRȡֵ�㳬����Χ
#define NGR_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+24
//NGRд�ļ�Ϊ��
#define NGR_W_FILENAME_NULL RESULT_ERROR_OT_BASE+25
//NGRд�ļ�ʧ��
#define NGR_W_FILE_ERROR RESULT_ERROR_OT_BASE+26
//NGR�����ݿ�д
#define NGR_W_NODATA RESULT_ERROR_OT_BASE+27

//NGB���ļ���Ϊ��
#define  NGB_R_FILENAME_NULL RESULT_ERROR_OT_BASE+31
//NGB��ȡʧ��
#define NGB_R_FILE_ERROR RESULT_ERROR_OT_BASE+32
//NGB�ļ���������
#define NGB_FILE_NULL_DATA RESULT_ERROR_OT_BASE+33
//NGBȡֵ�㳬����Χ
#define NGB_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+34
//NGBд�ļ�Ϊ��
#define NGB_W_FILENAME_NULL RESULT_ERROR_OT_BASE+35
//NGBд�ļ�ʧ��
#define NGB_W_FILE_ERROR RESULT_ERROR_OT_BASE+36
//NGB�����ݿ�д
#define NGB_W_NODATA RESULT_ERROR_OT_BASE+37


//NG Grid���ļ���Ϊ��
#define  NG_GRID_R_FILENAME_NULL RESULT_ERROR_OT_BASE+41
//NG Grid��ȡʧ��
#define  NG_GRID_R_FILE_ERROR RESULT_ERROR_OT_BASE+42
//NG Grid�ļ���������
#define NG_GRID_FILE_NULL_DATA RESULT_ERROR_OT_BASE+43
//NG Gridȡֵ�㳬����Χ
#define NG_GRID_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+44
//NG Gridд�ļ�Ϊ��
#define NG_GRID_W_FILENAME_NULL RESULT_ERROR_OT_BASE+45
//NG Gridд�ļ�ʧ��
#define NG_GRID_W_FILE_ERROR RESULT_ERROR_OT_BASE+46
//NG Grid�����ݿ�д
#define NG_GRID_W_NODATA RESULT_ERROR_OT_BASE+47


//NG Line���ļ���Ϊ��
#define  NG_LINE_R_FILENAME_NULL RESULT_ERROR_OT_BASE+51
//NG Line��ȡʧ��
#define  NG_LINE_R_FILE_ERROR RESULT_ERROR_OT_BASE+52
//NG Line�ļ���������
#define NG_LINE_FILE_NULL_DATA RESULT_ERROR_OT_BASE+53
//NG Lineȡֵ�㳬����Χ
#define NG_LINE_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+54
//NG Lineд�ļ�Ϊ��
#define NG_LINE_W_FILENAME_NULL RESULT_ERROR_OT_BASE+55
//NG Lineд�ļ�ʧ��
#define NG_LINE_W_FILE_ERROR RESULT_ERROR_OT_BASE+56
//NG Line�����ݿ�д
#define NG_LINE_W_NODATA RESULT_ERROR_OT_BASE+57


//NG 3DR���ļ���Ϊ��
#define  NG_3DR_R_FILENAME_NULL RESULT_ERROR_OT_BASE+61
//NG 3DR��ȡʧ��
#define  NG_3DR_R_FILE_ERROR RESULT_ERROR_OT_BASE+62
//NG 3DR�ļ���������
#define NG_3DR_FILE_NULL_DATA RESULT_ERROR_OT_BASE+63
//NG 3DRȡֵ�㳬����Χ
#define NG_3DR_POSITION_NOTINBOUND RESULT_ERROR_OT_BASE+64
//NG 3DRд�ļ�Ϊ��
#define NG_3DR_W_FILENAME_NULL RESULT_ERROR_OT_BASE+65
//NG 3DRд�ļ�ʧ��
#define NG_3DR_W_FILE_ERROR RESULT_ERROR_OT_BASE+66
//NG 3DR�����ݿ�д
#define NG_3DR_W_NODATA RESULT_ERROR_OT_BASE+67

//��Ż�������
#define EMEREPORT_ERROR_BASE 48000
#define NO_MONITORFILES EMEREPORT_ERROR_BASE+1//��ָ��ʱ���Ƶ�η�Χ���޼������

//̨վ���
#define SITESUPERVISION_ERROR_BASE 49000
#define NO_SPECTRUM_MAP_DATA SITESUPERVISION_ERROR_BASE+1//ʸ����������Ƶ�׵�ͼ����
#define NO_SPECTRUM_MAP_FILE SITESUPERVISION_ERROR_BASE+2//�޸�Ƶ���Ԥ�����ļ�
#define WRONG_SPECTRUM_FILE_FORMAT SITESUPERVISION_ERROR_BASE+3//Ԥ�����ļ���ʽ����
#define TXSTATION_ID_ERROR   SITESUPERVISION_ERROR_BASE+4	//����̨վID�����������ɵ���̨վ��ⱨ�棩


#define FINGERPRINT_ERROR_BASE 50000

#define FREQ_NUM_TOO_MUCH FINGERPRINT_ERROR_BASE + 1 //Ƶ�ʼ�ܵ�Ƶ����Ŀ̫��
#define NO_TX_SITE_IN_FREQBAND FINGERPRINT_ERROR_BASE + 2 //��ܵ�Ƶ����û�з���̨


#define NG_PREPROCESSING_EXE_BASE 51000
#define NG_SERVICEFREQ_DIVISION_XML_READERROR NG_PREPROCESSING_EXE_BASE + 1 //��ȡƵ�λ���xmlʱ�쳣
#define NG_PRECAL_XML_READERROR NG_PREPROCESSING_EXE_BASE + 2   //������������ļ���ȡ�쳣
#define NG_READ_TRANMITTER_RESULTXML_ERROR  NG_PREPROCESSING_EXE_BASE + 3 //��ȡEMC�����������ļ��쳣
#define NG_PREPROCESS_COMMAND_ERROR NG_PREPROCESSING_EXE_BASE + 4  //�����в�������
#define NG_PARAM_NOFREQ_ERROR  NG_PREPROCESSING_EXE_BASE + 5  //û�д�����Ƶ����Ϣ
#define NG_PARAM_NOCALPOLYGON_ERROR  NG_PREPROCESSING_EXE_BASE + 6  //û�д�����������Ϣ
#define NG_CALPOLYGON_XML_READERROR NG_PREPROCESSING_EXE_BASE + 7 //��ȡ��������xmlʱ�쳣
#define NG_NO_CALMAP_ERROR NG_PREPROCESSING_EXE_BASE + 8 //ȱ�ټ����ͼ

//̨վ����״̬����
#define NG_STATIONSTATUS_ERROR_BASE 52000
#define NG_ALLSTATIONS_SEARCH_NO_MONITOR	NG_STATIONSTATUS_ERROR_BASE+1 //���з���վ��û���ѵ����վ


//�����ƽ����ȡ����
#define NG_RASTERRESULT_CUT_ERROR_BASE 53000
#define NG_ARER_ERROR	NG_RASTERRESULT_CUT_ERROR_BASE+1 //δָ������
#define NG_NO_IMPORT_COORDSYS NG_RASTERRESULT_CUT_ERROR_BASE+2 //��֧�ֵ�����ϵ��Ŀǰֻ֧�־�γ��

/*********************************����������ȡ�㷨***************************************/
#define EXTRACT_BACKROUND_NOISES_BASE_CODE 54000
#define CALCULATE_SPECTRUM_AVG_ERROR    EXTRACT_BACKROUND_NOISES_BASE_CODE+1 //�����ֵƵ��ʧ��
#define EIGHTY_PERCENT_METHOD_ERROR     EXTRACT_BACKROUND_NOISES_BASE_CODE+2 //80%��������ʧ��
#define NO_VALID_FREQ_ERROR             EXTRACT_BACKROUND_NOISES_BASE_CODE+3 //����ЧƵ��ֵ
#define NOT_INVALID_DELTA_ERROR         EXTRACT_BACKROUND_NOISES_BASE_CODE+4 //������Ч��Χ������ֵ
#define NO_DATA_OF_THE_BAND             EXTRACT_BACKROUND_NOISES_BASE_CODE+5  //�޸�Ƶ������

//����±�
#define NG_MONTH_REPORT_BASECODE 55000
#define NG_TEMPLET_WRONG				NG_MONTH_REPORT_BASECODE + 1 //�±�ģ���ʽ����
#define NG_MONITORDATAFILE_ERROR		NG_MONTH_REPORT_BASECODE + 2 //����ļ�����


/************BEGIN: ����ģ�������**************************/



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
