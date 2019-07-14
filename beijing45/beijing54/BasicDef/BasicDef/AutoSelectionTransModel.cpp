#include "AutoSelectionTransModel.h"
#include "../DataModel/TransModelParam.h"



ETransModel GetAutoModelIDEntry(double FreqMHz)
{
	if (FreqMHz>=3 && FreqMHz<=30)
	{
		return eITU533ShortWave;
	} 
	else if(FreqMHz>=150&&FreqMHz<=1500)
	{
		return eCost231Hata1;
	}
	else if(FreqMHz>1500&&FreqMHz<=2400)
	{
		return eCost231Hata2;
	}
	else if(FreqMHz>=30 && FreqMHz<=3000)	
	{
		return eITURP1546;
	}
	else
	{
		return eFreeSpace;
	}

}


void* GetClassicModelParamByModeIDEntry(ETransModel ModelID)
{
	void *Param=0;

	switch(ModelID)
	{
	case eFreeSpace:
		{		
			struct ScmFreeSpacePara *ModelParam=new struct ScmFreeSpacePara;
			ModelParam->mDiffParam.mnDiffractionModel=2;
			Param=(void*)ModelParam;

		}
		break;
	case eCost231Hata1:
		{		
			struct ScmOkuHataPara *ModelParam=new struct ScmOkuHataPara;
			ModelParam->ma0 = 69.55;
			ModelParam->ma1 = 44.9;
			ModelParam->ma2 = 13.82;
			ModelParam->ma3 = 6.55;
			ModelParam->ma4 = 26.16;
			ModelParam->mDiffParam.mnDiffractionModel=2;
			Param=(void*)ModelParam;
		}
		break;
	case eITURP1546:
		{
			struct ScmITU1546Para *ModelParam=new struct ScmITU1546Para;
			Param=(void*)ModelParam;
		}
		break;	
	case eITURP370:
		{
			struct ScmITU370Para *ModelParam=new struct ScmITU370Para;
			Param=(void*)ModelParam;
		}
		break;
	case eLONGLEYRICE:
		{
			struct ScmLonglyRicePara *ModelParam=new struct ScmLonglyRicePara;
			Param=(void*)ModelParam;
		}	
		break;
	case eITU533ShortWave:
		{
			struct ScmShortWavePara *ModelParam=new struct ScmShortWavePara;
			Param=(void*)ModelParam;
		}  
		break;
	case eITU530V10MicWave:
		{
			struct ScmITU530V10Para *ModelParam=new struct ScmITU530V10Para;
			Param=(void*)ModelParam;
		}
		break;
	case eITU618:
		{
			struct ScmITU618Para *ModelParam=new struct ScmITU618Para;
			ModelParam->mDiffParam.mnDiffractionModel=2;
			Param=(void*)ModelParam;
		}
		break;
	case eAeroNautical:
		{
			struct ScmAeronauticalPara *ModelParam=new struct ScmAeronauticalPara;
			Param=(void*)ModelParam;
		}
		break;
	case eLOSModel:
		{
			struct ScmLosPara *ModelParam=new struct ScmLosPara;
			Param=(void*)ModelParam;
		}
		break;
	case eDiffractionModel:
		{

			struct ScmDiffParam *ModelParam=new struct ScmDiffParam;
			Param=(void*)ModelParam;
		}
		break;
	case eIRT3D:
		{
			struct IRTCalPara *ModelParam=new struct IRTCalPara;
			Param=(void*)ModelParam;
		}
		break;
	case eCost231Hata2:
		{
			struct ScmOkuHataPara *ModelParam=new struct ScmOkuHataPara;
			ModelParam->ma0 = 46.3;
			ModelParam->ma1 = 44.9;
			ModelParam->ma2 = 13.82;
			ModelParam->ma3 = 6.55;
			ModelParam->ma4 = 33.9;
			ModelParam->mDiffParam.mnDiffractionModel=2;
			Param=(void*)ModelParam;
		}
		break;
	case eLeeModel:
		{
			struct ScmLeePara *ModelParam=new struct ScmLeePara;
			Param=(void*)ModelParam;
		}
		break;
	case eWalfishIkegami:
		{
			struct ScmWalfishIkegamiPara *ModelParam=new struct ScmWalfishIkegamiPara;
			Param=(void*)ModelParam;
		}
		break;
	case eSUIModel:
		{
			struct SUIParam *ModelParam=new struct SUIParam;
			Param=(void*)ModelParam;
		}
		break;
	case eGroundWave:
		{
			struct ScmGroundWavePara *ModelParam=new struct ScmGroundWavePara;
			Param=(void*)ModelParam;
		}
		break;
	case eSkyWave:
		{
			struct ScmSkyWavePara *ModelParam=new struct ScmSkyWavePara;
			Param=(void*)ModelParam;
		}
		break;
	case eITU452:
		{
			struct ScmITU452ModelPara *ModelParam=new struct ScmITU452ModelPara;
			Param=(void*)ModelParam;
		}
		break;
	case eITU452_10:
		{
			struct ScmITU452V10ModelPara *ModelParam=new struct ScmITU452V10ModelPara;
			Param=(void*)ModelParam;
		}
		break;
	case eFlatEarth:
		{
			struct ScmFlatEarthModelPara *ModelParam=new struct ScmFlatEarthModelPara;
			Param=(void*)ModelParam;
		}
		break;
	case eEgliModel:
		{
			struct ScmEgliModelPara *ModelParam=new struct ScmEgliModelPara;
			Param=(void*)ModelParam;
		}
		break;
	case eITU1812:
		{
			struct ScmITU1812ModelPara *ModelParam=new struct ScmITU1812ModelPara;
			Param=(void*)ModelParam;
		}
		break;
	case eITU567://假的
		{
			//struct ScmITU567ModelPara *ModelParam=new struct ScmITU567ModelPara;
			//Param=(void*)ModelParam;
		}
		break;
	case eITU619://假的
		{
			//struct ScmITU619ModelPara *ModelParam=new struct ScmITU619ModelPara;
			//Param=(void*)ModelParam;
		}
		break;
	case eHCM://假的
		{
			//struct ScmOkuHataPara *ModelParam=new struct ScmOkuHataPara;
			//Param=(void*)ModelParam;
		}
		break;
	case eITU676://假的
		{
			//struct ScmITU676ModelPara *ModelParam=new struct ScmITU676ModelPara;
			//Param=(void*)ModelParam;
		}
		break;
	case eITU526:
		{
			struct ScmITU526ModelPara *ModelParam=new struct ScmITU526ModelPara;
			Param=(void*)ModelParam;
		}
		break;
	case eITU530MicWave:
		{
			struct ScmITU530Para *ModelParam=new struct ScmITU530Para;
			Param=(void*)ModelParam;
		}
		break;
	case eITU1147:
		{
			struct ScmSkyWavePara *ModelParam=new struct ScmSkyWavePara;
			Param=(void*)ModelParam;
		}
		break;
	case eITURP1546_4:
		{
			struct ScmITU1546V4Para *ModelParam=new struct ScmITU1546V4Para;
			Param=(void*)ModelParam;
		}
		break;
	case eIRT3D_CELL: //假的
		{
			// Param=(void*)ModelParam;
		}

		break;
	case eRaytracing: //目前没参数
		{
			// Param=(void*)ModelParam;
		}

		break;


	default:
		break;;


	}

	return Param;

}

void ReleaseClassicModelParamEntry(void* pModelParam)
{
	if(pModelParam)delete pModelParam;
}