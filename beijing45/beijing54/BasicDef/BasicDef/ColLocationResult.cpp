#include "ColLocationResult.h"
#include "MacroDef.h"
#define  CLEAR_RES_OBJECT(x,y){if(x!=NULL) delete []x; x = NULL;y=0; }
#define  CREATE_RES_OBJRCT(n,x,y){ CLEAR_RES_OBJECT(x,y); if(n>0){ x = new _TCoLocationRes[n];y=n;}}

CCoLocationResult::CCoLocationResult(void)
{
	CoAdjInt = NULL;
	nCoadj = 0;
	//
	BlockInt = NULL;
	nBlock = 0;
	//
	IFInt = NULL;
	nIF = 0;
	//
	MFInt = NULL;
	nMF = 0;
	//
	HarmonicsInt = NULL;
	nHarm = 0;
	//
	ModulationInt = NULL;
	nModu = 0;
}

CCoLocationResult::~CCoLocationResult(void)
{

	CLEAR_RES_OBJECT(CoAdjInt,nCoadj);
	//
	CLEAR_RES_OBJECT(BlockInt,nBlock);
	//
	CLEAR_RES_OBJECT(IFInt,nIF);
	//
	CLEAR_RES_OBJECT(MFInt,nMF);
	//
	CLEAR_RES_OBJECT(HarmonicsInt,nHarm);
	//
	CLEAR_RES_OBJECT(ModulationInt,nModu);
}

_TCoLocationRes * CCoLocationResult::GetCoLocationRes( int & num,_TCoLocationRes *& pRes,int & nRes, bool bCreateNew /*= false*/ )
{
	if(bCreateNew)
	{
		CREATE_RES_OBJRCT(num,pRes,nRes);
	}
	num = nRes;
	return pRes;
}

_TCoLocationRes * CCoLocationResult::GetCoAdjRes( int & num,bool bCreateNew /*= false*/ )
{
	return GetCoLocationRes(num,CoAdjInt,nCoadj,bCreateNew);
}

_TCoLocationRes * CCoLocationResult::GetBlockRes( int & num,bool bCreateNew /*= false*/ )
{
	return GetCoLocationRes(num,BlockInt,nBlock,bCreateNew);
}

_TCoLocationRes * CCoLocationResult::GetIFRes( int & num,bool bCreateNew /*= false*/ )
{
	return GetCoLocationRes(num,IFInt,nIF,bCreateNew);
}

_TCoLocationRes * CCoLocationResult::GetMFRes( int & num,bool bCreateNew /*= false*/ )
{
	return GetCoLocationRes(num,MFInt,nMF,bCreateNew);
}

_TCoLocationRes * CCoLocationResult::GetHarmonicsRes( int & num,bool bCreateNew /*= false*/ )
{
	return GetCoLocationRes(num,HarmonicsInt,nHarm,bCreateNew);
}

_TCoLocationRes * CCoLocationResult::GetModulationRes( int & num,bool bCreateNew /*= false*/ )
{
	return GetCoLocationRes(num,ModulationInt,nModu,bCreateNew);
}