#ifndef _NG_KOORD_TRANS
#define _NG_KOORD_TRANS

#if defined(KOORDTRANS_LIB)
#define KT_API
#else
	#if defined(_WIN32) || defined(__WIN32__)
		#ifdef KOORDTRANS_EXPORTS
			#define KT_API __declspec(dllexport)
		#else
			#define KT_API __declspec(dllimport)
		#endif 
	#else 
#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#define KT_API __attribute__ ((visibility("default")))
#else
#define KT_API
#endif		// __GNUC__		
#endif		// WIN32 / !WIN32
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	KT_API void ng_geo_init();
	KT_API void ng_geo_trans( long fromSys, long toSys, 
		double fromX, double fromY,
		double *toX,  double *toY );

	//2010.10.11
	KT_API short ng_GetMaxCoord();
	KT_API short ng_Get_Coordsystem_Name(long koordsys, char *systemname);
	KT_API short ng_Get_Coordsystem_LongName(long koordsys, char *systemname);	//add by jjj 2011.7.12
	KT_API short ng_GetCoordNoFromName(const char *systemname);			//add by jjj 2011.8.25

	//add by jjj 2012.8.15
	KT_API long	ng_GetCategoryItemSize();
	KT_API short	ng_GetCategoryItemName(long CategoryItem, char **CategoryItemName);
	KT_API short	ng_GetCategorySize(long CategoryItem, long *categorysize);
	KT_API short	ng_GetCategoryProjNumber(long CategoryItem, long ProjectionItem, long *sysnr);
	KT_API short	ng_GetCategoryProjName(long CategoryItem, long ProjectionItem, char **ShortName);
	KT_API short	ng_GetCategoryProjLongName(long CategoryItem, long ProjectionItem, char **LongName);

	KT_API bool	ng_IsGeoSystem(long SysNr);				//坐标系编号是否为经纬度大地坐标系
	KT_API bool	ng_IsUTMSystem(long SysNr);				//坐标系编号是否为utm坐标
	KT_API bool	ng_IsGKZoneSystem(long SysNr);			//坐标系编号是否为 Gauss-Kruger 坐标

	//标准utm经度坐标没有区号,LS坐标转换时使用的utm坐标需要加上区号
	//下面两个函数完成LS utm经度和 标准utm经度的转换
	KT_API double	ng_LusEasting2UtmEasting(long SysNr, double easting);
	KT_API double	ng_UtmEasting2LusEasting(long SysNr, double easting);

	//Gauss-Kruger 和utm一样，需要加上区号
	KT_API double	ng_LusEasting2GKZoneEasting(long SysNr, double easting);
	KT_API double	ng_GKZoneEasting2LusEasting(long SysNr, double easting);

	//add by jjj 2012.1.31
	//获取坐标系的地球长轴a,扁平率f
	KT_API void	ng_GetProjEllipSoid_AF(long SysNr,double *pA,double *pF);

#ifdef __cplusplus
}
#endif

#endif