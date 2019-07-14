#ifndef __CAL__RESULT__TYPE__H__
#define __CAL__RESULT__TYPE__H__

//计算结果类别
typedef enum CalResult_Type
{
	CR_UNKNOWN				= -1,	//未知计算结果类别
	CR_PATHLOSS				= 0,	//pathloss
	CR_FIELDSTRENGTH		= 1,	//场强
	CR_POWER				= 2,	//接收功率
	CR_SINGAL_STRENGTH		= 3,	//信号强度
	CR_POWER_FLUXDENSITY	= 4,	//功率通量密度
	CR_SP_POWER_FLUXDENSITY	= 5,	//频谱功率通量密度
};

#endif	/* __CAL__RESULT__TYPE__H__ */