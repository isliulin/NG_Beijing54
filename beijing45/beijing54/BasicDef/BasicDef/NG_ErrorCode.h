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
#define HEIGHT_TYOE_ERROR                 BASE_ERROR+13 //�߶����ͷǷ�  ֻ֧��0-2
#define NG_NO_RESULT_FILE                  BASE_ERROR+14 //û�н���ļ�
#define NG_CLIENTVERSION_NOTRANSMODE   DONGLE_BASE_ERROR+16 //�ͻ��汾δ��Ȩ��ģ��
#define NG_FUNCTIONMODEL_NOTRANSMODE   DONGLE_BASE_ERROR+17 //����ģ�鲻֧�ָô���ģ��
#define NG_DB_ERROR                        BASE_ERROR+18  //���ݿ����
#define NO_AREA_INFO                       BASE_ERROR+19  //û��������Ϣ
#define NO_MATCH_RESULTFILE	              BASE_ERROR+20  //����ļ����ͼ���̨վ����ƥ��
#define NG_FUNCTIONMODEL_UNSUPPORT_FREESPACE  BASE_ERROR+21  //���ܲ�֧�����ɿռ�ģ��
#define NG_FREQUENCY_PARAM_ERROR			BASE_ERROR+22	//���������Ƶ�ʷ�Χ�Ƿ�
#define NG_NULL_PROJECTGUID                 BASE_ERROR+23   //Project GUIDΪ��
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
#define NG_NO_RIGHT_CMDONGLE      DONGLE_BASE_ERROR+13 //Codemeter����������Ҫ����־




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

#define NG_STATIONPREPROCESS_ERROR		43000
#define READ_RESOLUTION_FAILED			NG_STATIONPREPROCESS_ERROR+11  //��ȡ�ֱ���ʧ��
#define CREATE_PREPROCESSFILE_FAILED    NG_STATIONPREPROCESS_ERROR+12  //����Ԥ�����ļ�ʧ��
#define READ_PREPROCESS_STATION_FAILED	NG_STATIONPREPROCESS_ERROR+13  //��ȡԤ����̨վʧ��
#define TOOMUCH_PREPROCESS_STATION		NG_STATIONPREPROCESS_ERROR+14  //Ԥ����̨վ����
#define INPUT_PARAM_WRONG				NG_STATIONPREPROCESS_ERROR+15  //Ԥ���������������
#define UPDATE_TXSTATION_NO_FAILED		NG_STATIONPREPROCESS_ERROR+16  //����Ԥ�����Ŵ���
#define UPDATE_PREPROCESSPATH_FAILED	NG_STATIONPREPROCESS_ERROR+17  //����Ԥ����·������
#define PREPROCESS_LICENSE_ERROR		NG_STATIONPREPROCESS_ERROR+18  //Ԥ����������
#define READ_PRECALC_PARAM_FAILED		NG_STATIONPREPROCESS_ERROR+19  //��ȡ�ֱ���ʧ��
#define READ_LAST_PRECALCID_FAILED		NG_STATIONPREPROCESS_ERROR+20  //��ȡ�ϴμ����IDʧ��
#define UPDATE_PROC_STATUS_I_FAILED		NG_STATIONPREPROCESS_ERROR+21  //���´�����̱���Ի�ʧ��
#define UPDATE_PROC_STATUS_S_FAILED		NG_STATIONPREPROCESS_ERROR+22  //���´�����̱�ʼʧ��
#define CONFIG_READDEM_PATH_FAILED		NG_STATIONPREPROCESS_ERROR+23  //��ȡDEM·��ʧ��
#define CHECK_CALC_FUNC_NOT_MATCH		NG_STATIONPREPROCESS_ERROR+24  //��������ú����ʹ���ĺ������Ͳ�ƥ��
#define READ_POPU_INFO_MAP_FAILED		NG_STATIONPREPROCESS_ERROR+25  //��ȡ�˿�Ԥ��������Ϣʧ��
#define UPDATE_PROC_STATUS_F_FAILED		NG_STATIONPREPROCESS_ERROR+26  //���´�����̱�״̬���ʧ��
#define READ_PATHLOSS_PREPROC_FAILED    NG_STATIONPREPROCESS_ERROR+27  //��ȡ·��Ԥ�����ļ�ʧ��
#define CALCPROCESS_LICENSE_ERROR		NG_STATIONPREPROCESS_ERROR+28 //���㴦����̹�������
#define PREPROCESS_STASTION_SKIPPED     NG_STATIONPREPROCESS_ERROR+29  //Ԥ������̲��ֻ�ȫ��̨վʧ��
#define NO_VALIDE_GRID                  NG_STATIONPREPROCESS_ERROR+29  //��������Ч��դ�񣬿����Ǹ���bestserver��ȡ��̨վ��û����ȷ�����ݿ����


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

#define NG_PropModel_NOProjPath TRANSMODEL_BASE_ERROR + 301                   //����ģ�ͼ���δ������Ŀ·��

#define NG_POINTER_CAN_NOT_BE_EMPTY   TRANSMODEL_BASE_ERROR + 325  //ITU���ӵ�ͼ·��Ϊ��
#define NG_FAIL_TO_READ_FILE   TRANSMODEL_BASE_ERROR + 326       //��ȡ���ӵ�ͼʧ��

#define TRANSMODEL533_BASE_ERROR   5500
#define TRANS533_IONOS_ERROR TRANSMODEL533_BASE_ERROR+1 //����������ȡʧ��
#define TRANS533_REC_TOO_CLOSE_ERROR TRANSMODEL533_BASE_ERROR+2 //���յ���뷢�������������غ�
#define TRANS533_ANT_ELEANGLE_TOO_SMALL_ERROR TRANSMODEL533_BASE_ERROR+3 //��������̫С��С������ֵ
#define TRANS533_DAY_NOELAYER_ERROR TRANSMODEL533_BASE_ERROR+4 //�����ϻ��߾���̫Զ��������E�㳡ǿ
#define TRANS533_RESULTTYPE_NOTSUPPORT TRANSMODEL533_BASE_ERROR+5 //�̲�ģ��533ֻ֧�ֳ�ǿ����


/************ģ��У��������******************************************************************/
#define CALIBRATION_BASE_ERROR   6000
#define CALIBRATION_FREQ_OUTOFRANGE CALIBRATION_BASE_ERROR+1  //Ƶ�ʳ�������ģ�����÷�Χ
#define CALIBRATION_FAILED          CALIBRATION_BASE_ERROR+2  //ģ��У��δ����ȷִ��
#define CALIBRATION_TOO_FEW_POINT   CALIBRATION_BASE_ERROR+3  //ģ��У���ļ��е���̫��


/************���ŷ���������******************************************************************/
#define INTERFERENCE_BASE_ERROR   7000
#define NO_MATCH_FREQ   INTERFERENCE_BASE_ERROR+1  //����վ�ͷ���վƵ�ʲ�ƥ��
#define NO_NEW_INTSTATION		   INTERFERENCE_BASE_ERROR+4 //û����������վ



/************��ŷֲ����������******************************************************************/
#define EMCCAL_BASE_ERROR   8000
#define NO_SUPPORTED_RESULT_TYPE  EMCCAL_BASE_ERROR+1  //��֧�ֽ������



/************Ч�ܷ������������******************************************************************/
#define PERFROMANCE_BASE_ERROR   9000



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
/* �ü��վ��δ����Ƶ�׿� */
#define NO_SPECTRUM_LIB_FILE_IN_MONI_STATION         (SIGNAL_BASE_ERROR + 107)

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
#define FREQASSIGN_NO_CANDIDATEPREQ FREQASSIGN_BASE_ERROR+5 //̨վȱʧ��ѡƵ��


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
#define  CANNOTEXTRACTCONTOUR    ISOSURFACE_BASE_ERROR+1 //�޷���ȡ��ֵ��




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
#define USER_TERMINATED_ERROR    PROJECTCONFIG_BASE_ERROR+6 //�û�ȡ������
#define POPULATION_FILE_ERROR    PROJECTCONFIG_BASE_ERROR+7 //�˿��ļ����ô���

/******************г�����Ŵ�����****************************************************/
#define HARMONICSINT_BASE_ERROR  23000
#define HARMONICSPARAM_ERROR  HARMONICSINT_BASE_ERROR+1 //г��������,ֻ֧��2,��13

/******************�߾�Э��������****************************************************/
#define BoundaryCoordinate_BASE_ERROR  24000
#define NO_INTERFERENCE    BoundaryCoordinate_BASE_ERROR+1 //�߽��븲��������û�н����������ڸ���
#define AREA_INCLUDE       BoundaryCoordinate_BASE_ERROR+2 //��������ڰ����뱻�����Ĺ�ϵ


/*******************TDOA������************************************************************************/
#define TDOA_BASE_ERROR  25000
#define STATIONS_NOT_ENOUGH TDOA_BASE_ERROR+1 //���վ��Ŀ������������3������
#define SIGNAL_NO_CROSSRELATION TDOA_BASE_ERROR+2 //�ź�����Բ���
#define  TIME_NO_MIXED TDOA_BASE_ERROR+3                       //�ź�ʱ��û�н�����ʱ��ͬ��ʧ��
#define FILE_NUM_NOT_EQUAL_STATION TDOA_BASE_ERROR+4                      //�ļ���Ŀ�ͼ��վ��Ŀ����
#define UNSUPPORT_LOCATIONTYPE   TDOA_BASE_ERROR+5                     //��֧�ֵĶ�λ��ʽ

#define RESULT_BAD TDOA_BASE_ERROR+6                        //�ź�̫���λ�õ��Ľ��̫��

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
#define SITESELECTION_NO_VALIDPOINT      SITESELECTION_BASE_ERROR+2     //���ʵĺ�ѡλ��̫�٣�����ˮ��̫��



/*******************̨վ�������������************************************************************************/
#define SITEWORKSTATUS_BASE_ERROR  30000






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
#define GET_ROADVECTOR_ERROR         BOUNDARYCORRDINATION_ERROR+3  //��ȡ�߽�ʸ��ʧ�ܣ�����ԭ��Ϊ����������߽���û�н���

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

#define NATURALBASECODE 37000
#define DRIVER_TEST_POINT_NOT_ENOUGTH NATURALBASECODE+10//·���̫��


//̨վ�ź��Զ�����
#define NG_SIGNAL_DIS_BASECODE 38000
#define NO_TARGET_FREQ NG_SIGNAL_DIS_BASECODE + 1 //�޷���̨վ��ɨƵ�ж�ȡ��Ƶ����Ϣ





/*******************������ŷ���������************************************************************************/
#define AREAINTERFERENCEANANLYSIS_ERROR  39000
#define TX_STATION_NO_COVERAGE    AREAINTERFERENCEANANLYSIS_ERROR+1  //Ԥ����̨վ�Լ��������޸���
#define NEW_STATION_NO_COVERAGE    AREAINTERFERENCEANANLYSIS_ERROR+2  //�½�̨վ�Լ��������޸���


//pathlossԤ����
#define NG_PATHLOSSPREPROCESS_BASECODE 40000 
#define NG_NOBYPREPROCESS   NG_PATHLOSSPREPROCESS_BASECODE+1  //����Ԥ�������̣��Ǵ�����
#define PATHLOSS_NO_FILE_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+2  //��ȡ�ļ�ʧ�ܣ��ļ�������
#define PATHLOSS_NO_MATCHED_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+3  //С��λ��û��ƥ��Ԥ������
#define PATHLOSS_NOT_MATCH_CELLAZ_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+4  //��վ��λ�ǲ�ƥ��
#define PATHLOSS_NOT_MATCH_CELLEL_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+5  //��վ�����ǲ�ƥ��
#define PATHLOSS_NOT_MATCH_ANT_HEIGHT_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+6  //���߸߶Ȳ�ƥ��
#define PATHLOSS_NOT_MATCH_TRAN_MODEL_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+7  //����ģ�Ͳ�ƥ��
#define PATHLOSS_NOT_MATCH_FREQ_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+8  //Ƶ�ʲ�ƥ��
#define PATHLOSS_NOT_MATCH_RADIUS_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+9  //����뾶��ƥ��
#define PATHLOSS_NOT_MATCH_RECV_HEIGHT_ERROR    NG_PATHLOSSPREPROCESS_BASECODE+10  //���ո߶Ȳ�ƥ��


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


/*******************̨վ�������������************************************************************************/
#define NG_STATIONLISTIMPORT_ERROR  42000
#define READ_STATIONFILE_FAILED    NG_STATIONLISTIMPORT_ERROR+1  //��ȡ̨վ�ļ�ʧ��
#define NO_STSTION_IN_FILE    NG_STATIONLISTIMPORT_ERROR+2  //̨վ�ļ���δ����̨վ����

/*******************���ݿ��������************************************************************************/
#define NG_DATABASE_ACCESS_ERROR  44000
#define NG_UPDATE_THREAD_STATUS_ERROR   NG_DATABASE_ACCESS_ERROR + 1	// ���½���״̬����
#define NG_READ_CALC_PARAMETER_ERROR   NG_DATABASE_ACCESS_ERROR + 2		// ��ȡ���ݿ��������
#define NG_UPDATE_FEEDER_STATUS_ERROR   NG_DATABASE_ACCESS_ERROR + 3	// ���·���״̬����
#define NG_UPDATE_PROCESS_STATUS_ERROR   NG_DATABASE_ACCESS_ERROR + 4	// ���¼������״̬����
#define NG_UPDATE_FUNC_DEFINITION_ERROR   NG_DATABASE_ACCESS_ERROR + 5	// ���¼�������������

/*******************������̴���************************************************************************/
#define NG_PROCESSING_ERROR  45000
#define NG_PROC_CREATE_PREDICTOR_ERROR   NG_PROCESSING_ERROR + 1	// �������㵥Ԫʧ��
#define NG_PROC_GEN_CALCAREA_ERROR    NG_PROCESSING_ERROR+2  //��ȡ�����������
#define NG_PROC_NET_TYPE_NOTVALID_ERROR    NG_PROCESSING_ERROR+3  //����ģ�鲻֧�ֵ���ʽ���ʹ���
#define NG_PROC_POPU_TOTAL_ZERO_ERROR    NG_PROCESSING_ERROR+4  //�������������˿�Ϊ��
#define NG_PROC_TRANSCAP_EQUA_NOT_SOLVED    NG_PROCESSING_ERROR+5  //UMTS����ʽ������
#define NG_PROC_RESTATCL_TOO_MANY_CLASSES   NG_PROCESSING_ERROR+6  //���¼��㸲�ǵȼ����೬�������

/*******************������������************************************************************************/
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
#define NG_3DR_NOMEMORY RESULT_ERROR_NO_MEMORY+6

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

/************************************************************************/
/* �����滮������                                                                     */
/************************************************************************/
#define NG_NEIGHBORPLAN_ERROR  48000
#define NG_NO_CELL_STATION             NG_NEIGHBORPLAN_ERROR + 1	//�����滮���޴��滮̨վ
#define NG_NO_NEIGHBOR_CELL_STATION    NG_NEIGHBORPLAN_ERROR + 2	//�����滮���޴��滮����̨վ
#define NG_READVECTORFROMDB_ERROR      NG_NEIGHBORPLAN_ERROR + 3	//��ȡ�����滮ʸ������
#define NG_AUTOMANUAL_PARAM_ERROR      NG_NEIGHBORPLAN_ERROR + 4	//�����滮�ֶ��Զ���������
#define NG_MANUALSITENEIGHBORXML_ERROR NG_NEIGHBORPLAN_ERROR + 5	//�ֶ������滮����xml���ô���
#define NG_NEIGHBORNETTYPE_ERROR       NG_NEIGHBORPLAN_ERROR + 6	//�����滮̨վ���ʹ���
#define NG_NEIGHBORGAINLOSS_ERROR      NG_NEIGHBORPLAN_ERROR + 7	//�Զ������滮�н���������Ĳ�������
#define NG_NEIGHBORMAXNUM_ERROR        NG_NEIGHBORPLAN_ERROR + 8	//�Զ������滮���������������������
#define NG_READANTENNA_ERROR		   NG_NEIGHBORPLAN_ERROR + 9	//�Զ������滮�д����ݿ��ȡ��������


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
