#include "INGRasterResult.h"
#include "../StringManager/StringManager.h"
#include "../KoordTrans/KoordTrans/KoordTrans.h"
#include "NGBRasterResult.h"
#include "NGZRasterResult.h"
#include "NGRRasterResult.h"
#include "NGZSRasterResult.h"
#include <math.h>

void INGRaterResult::DestroyRaster( INGRaterResult*& pRaster )
{
	NG_DELETE_SINGLE(pRaster) 
}

INGRaterResult * INGRaterResult::CreateRaster( NGRasterResultFormat format )
{
	switch(format)
	{
	case RASTER_NGZ:
		return new NGZRasterResult();
	case RASTER_NGZS:
		return new NGZSRasterResult();
	case RASTER_NGB:
		return  new NGBRasterResult();
	case RASTER_NGR:
		return new NGRRasterResult();
	default:
		return 0;
	}
}

NGRasterResultFormat INGRaterResult::CheckRasterFileFormat( const char * file )
{
	if(!NGStringManager::CheckFileAccess(file))
		return RASTER_NULL;
	if(NGBRasterResult::CheckFile(file))
		return RASTER_NGB;
	if(NGZSRasterResult::CheckFile(file)) //要先于NGZ判断,否则容易错误
		return RASTER_NGZS;
	if(NGZRasterResult::CheckFile(file))
		return RASTER_NGZ;
	if(NGRRasterResult::CheckFile(file))
		return RASTER_NGR;

	return RASTER_NULL;
}

bool INGRaterResult::GetValueByPos( double posX,double posY,double& val ) const
{
	double leftPos,bottomPos;
	GetLowerLeftCorner(leftPos,bottomPos);
	if((posX<leftPos)||(posY<bottomPos))
		return false;
	double xResolution = GetResolutionX();
	double yResolution = GetResolutionY();
	unsigned w = GetWidth();
	unsigned h = GetHeight();
	unsigned int x = (unsigned int)((posX-leftPos)/xResolution);
	if(x>=w)
		return false;
	unsigned int y = (unsigned int)((posY-bottomPos)/yResolution);
	if(y>=h)
		return false;
	val = GetValueAsDouble(x,y);
	return true;
}

#define AVREAGE_FUN(fun) \
	for(unsigned iy=startYindex;iy<=endYindex;iy++)     \
	{													\
		for(unsigned ix=startXindex;ix<=endXindex;ix++) \
		{												\
			double iv = GetValueAsDouble(ix,iy);        \
			if(IS_VALID_RASTER_VALUE(iv))              \
			{											\
				fun;									\
			}											\
		}												\
	}													\

bool INGRaterResult::GetValueByPos( double posX,double posY,double xRes,double yRes,EValueAverageType averageType, double &val ) const
{
	val = UNCALCULATE;
	double leftPos,bottomPos;
	GetLowerLeftCorner(leftPos,bottomPos);
	if((posX<leftPos)||(posY<bottomPos))
		return false;
	double xResolution = GetResolutionX();
	double yResolution = GetResolutionY();
	unsigned w = GetWidth();
	unsigned h = GetHeight();
	unsigned int x = (unsigned int)((posX-leftPos)/xResolution);
	if(x>=w)
		return false;
	unsigned int y = (unsigned int)((posY-bottomPos)/yResolution);
	if(y>=h)
		return false;
	unsigned int xsize = (int)(xRes/xResolution-1+0.5);
	unsigned int ysize = (int)(yRes/yResolution-1+0.5);
	if(xsize<2&&ysize<2)
	{
		val = GetValueAsDouble(x,y); 
	}
	else
	{
		double totalvalue=0;
		double maxvalue = UNCALCULATE;
		unsigned int totalcount = 0;
		unsigned startXindex = x;
		unsigned startYindex = y;
		unsigned endXindex = x+xsize>=w?w-1:x+xsize;
		unsigned endYindex = y+ysize>=h?h-1:y+ysize;
		
		switch(averageType)
		{
		case RANGE_MAX:
			{
				AVREAGE_FUN(if(maxvalue<iv) maxvalue=iv;)
				val = maxvalue;
			}
			break;
		case RANGE_AVERAGE_POW:
			{
				AVREAGE_FUN(totalvalue+=pow(10,iv/10);totalcount++;)
				val = (totalcount <= 0)? UNCALCULATE:(10*log10l(totalvalue/totalcount));
			}
			break;
		case RANGE_AVERAGE_POW2:
			{
				AVREAGE_FUN(totalvalue+=pow(10,iv/20);totalcount++;)
				val = (totalcount <= 0)? UNCALCULATE:(20*log10l(totalvalue/totalcount));
			}
			break;
		case RANGE_AVERAGE:
		default:
			{
				AVREAGE_FUN(totalvalue+=iv;totalcount++;)
				val =  (totalcount <= 0)? UNCALCULATE:(totalvalue/totalcount);
			}
			break;
		}
	}
	return true;
}

bool INGRaterResult::GetValueByPos( double posX,double posY,double xRes,double yRes,EValueAverageType averageType,int sys, double &val ) const
{
	int geoSys = GetCoordSysNumber();
	if((sys==0)||(sys == geoSys))
		return GetValueByPos(posX,posY,xRes,yRes,averageType,val);
	else
	{
		ng_geo_init();
		ng_geo_trans(sys,geoSys,posX,posY,&posX,&posY);
		bool inIsGeo = ng_IsGeoSystem(sys);
		bool curIsGeo = ng_IsGeoSystem(geoSys);
		if(inIsGeo == curIsGeo)
			return GetValueByPos(posX,posY,xRes,yRes,averageType,val);
		else if(inIsGeo)
		{
			double txRes = xRes * C_DEGREE2M;
			double tyRes = yRes * C_DEGREE2M;
			return GetValueByPos(posX,posY,txRes,tyRes,averageType,val);
		}
		else
		{
			double txRes = xRes / C_DEGREE2M;
			double tyRes = yRes / C_DEGREE2M;
			return GetValueByPos(posX,posY,txRes,tyRes,averageType,val);
		}
		
	}

}

bool INGRaterResult::GetDataByPos( double xpos,double ypos, int sys,double &val ) const
{
	int geoSys = GetCoordSysNumber();
	if((sys!=0)&&(sys!=geoSys))
	{
		ng_geo_init();
		ng_geo_trans(sys,geoSys,xpos,ypos,&xpos,&ypos);
	}
	return GetValueByPos(xpos,ypos,val);
}

void INGRaterResult::GetBound( double &l,double &b, double &r, double &t, int sys/*=0*/ ) const
{
	double leftPos,bottomPos;
	GetLowerLeftCorner(leftPos,bottomPos);
	double xResolution = GetResolutionX();
	double yResolution = GetResolutionY();
	unsigned w = GetWidth();
	unsigned h = GetHeight();
	int geoSys = GetCoordSysNumber();

	l = leftPos;
	b = bottomPos;
	r = l+ w * xResolution;
	t = b + h * yResolution;
	if((sys != 0)&&(sys != geoSys))
	{
		ng_geo_init();
		ng_geo_trans(geoSys,sys,l,b,&l,&b);
		ng_geo_trans(geoSys,sys,r,t,&r,&t);
	}
}

void INGRaterResult::SetDefaultValue( double defaltValue )
{
	unsigned w = GetWidth();
	unsigned h = GetHeight();
	
	for (unsigned i = 0; i < w; i++)
	{
		for (unsigned j = 0; j < h; j++)
		{
			SetValue(i,j,defaltValue);
		}
	}
}




