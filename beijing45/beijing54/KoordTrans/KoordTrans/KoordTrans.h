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

	KT_API bool	ng_IsGeoSystem(long SysNr);				//����ϵ����Ƿ�Ϊ��γ�ȴ������ϵ
	KT_API bool	ng_IsUTMSystem(long SysNr);				//����ϵ����Ƿ�Ϊutm����
	KT_API bool	ng_IsGKZoneSystem(long SysNr);			//����ϵ����Ƿ�Ϊ Gauss-Kruger ����

	//��׼utm��������û������,LS����ת��ʱʹ�õ�utm������Ҫ��������
	//���������������LS utm���Ⱥ� ��׼utm���ȵ�ת��
	KT_API double	ng_LusEasting2UtmEasting(long SysNr, double easting);
	KT_API double	ng_UtmEasting2LusEasting(long SysNr, double easting);

	//Gauss-Kruger ��utmһ������Ҫ��������
	KT_API double	ng_LusEasting2GKZoneEasting(long SysNr, double easting);
	KT_API double	ng_GKZoneEasting2LusEasting(long SysNr, double easting);

	//add by jjj 2012.1.31
	//��ȡ����ϵ�ĵ�����a,��ƽ��f
	KT_API void	ng_GetProjEllipSoid_AF(long SysNr,double *pA,double *pF);

#ifdef __cplusplus
}
#endif

#endif