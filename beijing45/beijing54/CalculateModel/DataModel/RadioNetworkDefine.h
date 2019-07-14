//����ṹ�嶨��
#ifndef __RADIO__NETWORK__DEFINE__H__
#define __RADIO__NETWORK__DEFINE__H__

#include "DataGuidDefine.h"

/*
����
һ���������һ�����̨վ,��Щ̨վ��ͬһʱ��ֻ����һ��̨վ�ڷ��������ź�,
����,һ�������ڲ���̨վ������ڸ���
һ�������ڲ���̨վʹ����ͬ��Ƶ��,һ���������Ҫ���ݰ���:
	���缶��
	�����ڵ�����̨վid
	����̨վid
	������Ƶ��,������Ƶ��
	���÷���Ƶ��,���ý���Ƶ��
*/
typedef struct tagRN_RadioNetwork
{
	EMC_Base	baseInfo;					//������Ϣ
	EMC_DATA_GUID	masterStationInNetId;	//����վid
	bool	isTemplate;						//�Ƿ�Ϊģ������
	bool	isPrioritised;					//�Ƿ����ȵ�
	bool	useMainFrequencies;				//�Ƿ�ʹ����Ƶ��
	double	mainHailingTxFq;				//������Ƶ��
	double	mainHailingRxFq;				//������Ƶ��
	double	reserveHailingTxFq;				//���÷���Ƶ��
	double	reserveHailingRxFq;				//���ý���Ƶ��
	double	frequencyBandStartTxFq;			//����Ƶ������
	double	frequencyBandStopTxFq;			//����Ƶ������
	double	frequencyBandStartRxFq;			//����Ƶ������
	double	frequencyBandStopRxFq;			//����Ƶ������
	int		stationClassCount;				//�������̨վ������
	EMC_DATA_GUID StationClassId;			//̨վ���ָ��
	int		stationCount;					//�������ڵ�����̨վ
	EMC_DATA_GUID *pStatinId;				//̨վid
}RN_RadioNetwork;


#endif	/* __RADIO__NETWORK__DEFINE__H__ */