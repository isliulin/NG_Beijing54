#ifndef __CAL__RESULT__TYPE__H__
#define __CAL__RESULT__TYPE__H__

//���������
typedef enum CalResult_Type
{
	CR_UNKNOWN				= -1,	//δ֪���������
	CR_PATHLOSS				= 0,	//pathloss
	CR_FIELDSTRENGTH		= 1,	//��ǿ
	CR_POWER				= 2,	//���չ���
	CR_SINGAL_STRENGTH		= 3,	//�ź�ǿ��
	CR_POWER_FLUXDENSITY	= 4,	//����ͨ���ܶ�
	CR_SP_POWER_FLUXDENSITY	= 5,	//Ƶ�׹���ͨ���ܶ�
};

#endif	/* __CAL__RESULT__TYPE__H__ */