
#ifndef NG_DATA_PROCESS_ERROR_CODE_H
#define NG_DATA_PROCESS_ERROR_CODE_H

#define SUCCESS 0//�ɹ�
#define BASECODE 100
#define FAIL_TO_OPEN_FILE BASECODE+1//���ļ�ʧ��
#define MEMORY_WRONG BASECODE+2//�����ڴ�ʧ��
#define POINT_CAN_NOT_NULL BASECODE+3//ָ��Ϊ��
#define PARAM_WRONG BASECODE+4//��������
#define FAIL_TO_WRITE_FILE BASECODE+5//д�ļ�ʧ��
#define DB_NULL BASECODE+6//���ݿ�Ϊ��
#define FILE_FORM_WRONG BASECODE+7//�ļ���ʽ����
#define TIME_OUT_RANGE BASECODE+8//������Ȩʱ��
#define NO_SOURCE_FILE BASECODE+9//û��Դ�ļ�
#define DRIVER_TEST_POINT_NOT_ENOUGTH BASECODE+10//·���̫��
#define NO_PARAM BASECODE +11 //û���������
#define NO_TRAGET_FREQ_FILE BASECODE + 12 //û�ж�Ӧ��Ƶ���ļ�
#define NG_COLOR_RANGE BASECODE + 13    //��ȡ��ɫ����ʧ��
#define FAIL_TO_READ_FILE BASECODE +14    //���ļ�ʧ��
#define DILUTE_BAND_SMALLER BASECODE +15 //ϡ��Ƶ��С��ԭƵ��
#endif