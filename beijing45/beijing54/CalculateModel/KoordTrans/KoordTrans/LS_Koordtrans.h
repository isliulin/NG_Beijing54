/* Headerfile zu LS_KoordTrans.c             */
#ifndef __LSKOORDTRANS__
#define __LSKOORDTRANS__

#define LS_geo_Export 


#if __cplusplus && !TRANSLATE_AS_CPLUSPLUS
extern "C" {
#endif


#define length48 48
#define length40 40
#define length32 36
#define length24 24
#define length16 16
#define length8  8


/* Typdefinitionen f¸r die Koordinatentransformationsroutinen */
struct _KoordSystem
	{
	short Datum;				/* Datum */
	short Proj;					/* Projection */
	short Methode;				/* Transformationsmethode */
	short Zone;					/* Projectionszone */
	};
typedef struct _KoordSystem KOORDSYSTEM;

struct _KoordStruct
	{
	short Datum;				/* Datum */
	short Proj;					/* Projection */
	short Methode;				/* Transformationsmethode */
	short Zone;					/* Projectionszone */
	char ShortName[length32];	/* Short Name of Coordinate System */
	char LongName[length48];	/* Long Name of Coordinate System */
	};
typedef struct _KoordStruct KOORDSTRUCT;

struct _Ellipsoid
	{
	double A;				/* Groþe Halbachse */
	double f;				/* Abflachung */
	double B;				/* Kleine Halbachse */
	double E1Q;				/* Quadrat der 1. numerische Exzentrizit”t */
	double E1;				/* 1. numerische Exzentrizit”t */
	double E2Q;				/* Quadrat der 2. numerische Exzentrizit”t */
	double N;				/* 	(A - B) / (A + B) 	*/
	double CZ;				/* Polkr¸mmungshalbmesser */
	double XMIN;			/* Hilfsvariable */
	double XMAX;			/* Hilfsvariable */
	char*  EllName;			/* Name des Ellipsoiden */
	};
typedef struct _Ellipsoid ELLIPSOID;


struct _DATUMSTRANS
	{
	short Methode; 		/* Transformationsparameter vorhanden */
	short RefEll; 		/* Dazugeh–riger Ellipsoid */
	double Tx;			/* Translation in X-Richtung */
	double Ty;			/* Translation in Y-Richtung */
	double Tz;			/* Translation in Z-Richtung */
	double Rx;			/* Rotation um die X-Achse */
	double Ry;			/* Rotation um die X-Achse */
	double Rz;			/* Rotation um die X-Achse */
	double Sc;			/* Skalierungsfaktor */
	double Hell;		/* Hight Ellipsoid -> Sea Level */
	char TrafoName[254];/* Name der Transformation */
	};
typedef struct _DATUMSTRANS DATUMSTRANS;


/* Structures for Display-Menu of Coordinate-Systems */
struct _Category
	{
	char name[length24];		/* Name of Category*/
	long CategorySize;			/* Number of Projections */
	long *ProjNumber;			/* Array with the different Coordinate System Numbers */
	};
typedef struct _Category CATEGORY;

typedef CATEGORY CATEGORYARRAY[];

struct _CategoryList
	{
	long     	  CategoryItemSize		;		/* Number of different Categories */
	CATEGORYARRAY *CategoryItemList		;		/* Array with different Categories */
	};
typedef struct _CategoryList CATEGORY_LIST;


/* MapInfo Co-orinate System Structure */
struct _MAPINFOPARAMS
	{
		long		Msys;			/* MapInfo Systemnummer			*/
		long		Mdatum;			/* MapInfo Datumnummer			*/
		long		Munit;			/* MapInfo Unitangabe			*/
		double		Mlambda0;		/* Origin Longitude				*/
		double		Mphi0;			/* Origin Latitude				*/
		double		Mstp1;			/* 1. Standard Parallel			*/
		double		Mstp2;			/* 2. Standard Parallel			*/
		double		Mazi;			/* Azimuth						*/
		double		Mscale;			/* Scale Factor					*/
		double		Meast;			/* False Easting				*/
		double		Mnorth;			/* False Northing				*/
									/* Needed to define Datum		*/
		long		MEll;			/* Ellypsoid					*/
		double		Mdx;			/* Shift of Origin				*/
		double		Mdy;			/* Shift of Origin				*/
		double		Mdz;			/* Shift of Origin				*/
		double		Mex;			/* Rotation around Origin		*/
		double		Mey;			/* Rotation around Origin		*/
		double		Mez;			/* Rotation around Origin		*/
		double		Msc;			/* Scaling factor in 10e-6		*/
		double		Mpmeri;			/* Shift of Prime Meridian		*/

	};
typedef struct _MAPINFOPARAMS MAPINFOPARAMS;







/* Deklaration der Funktionen */
/*@TT260398 added DLL export*/
LS_geo_Export void Init_KoordTrans();
LS_geo_Export void Init_Ellpar();
LS_geo_Export void ls_geo_get_maxell(short maxell);
LS_geo_Export ELLIPSOID *ls_geo_get_ellparam(short ellnr);
LS_geo_Export void ls_geo_get_maxdatum(short *maxdat);
LS_geo_Export DATUMSTRANS *ls_geo_get_datparam(short datnr);
LS_geo_Export void ls_geo_get_maxcoord(short *maxcoord);
LS_geo_Export KOORDSTRUCT *ls_geo_get_coordparam(short sysnr);
LS_geo_Export double roundc(double wert);
LS_geo_Export double signc(double wert);
LS_geo_Export short SetGeoSystemNULL (long Reference);
LS_geo_Export void GeoTransformC (short vonsys, short nachsys, double xq, double yq,
	 									double *xz, double *yz);
LS_geo_Export void NeuGeoTransformC (long vonsys, long nachsys, double   xq, double   yq,
	 							                                double *pxz, double *pyz);
LS_geo_Export short GeoTransformC_Err (long vonsys, long nachsys, double   xq, double   yq,
	 											                  double *pxz, double *pyz);
short GeoTransformHeight_Err (long vonsys, long nachsys, double   xq, double   yq, double   hq,
	 											         double *pxz, double *pyz, double *phz);
LS_geo_Export short KoordTrans (double   xq, double   yq, double   hq, const KOORDSYSTEM *psysq, 
				  double *pxz, double *pyz, double *phz, const KOORDSYSTEM *psysz);
void Grad2Rad(double *Long_R, double *Lat_R, const KOORDSYSTEM *psys,
			  double  Long_G, double  Lat_G);
void Rad2Grad(double  Long_R, double  Lat_R, const KOORDSYSTEM *psys,
			  double *Long_G, double *Lat_G);

LS_geo_Export void Grad_2_Rad(double  Long_GRAD, double  Lat_GRAD, double *Long_RAD,  double *Lat_RAD);
LS_geo_Export void Rad_2_Grad(double  Long_RAD,  double  Lat_RAD, double *Long_GRAD, double *Lat_GRAD);
LS_geo_Export void Grad_2_Gon(double  Long_GRAD, double  Lat_GRAD, double *Long_GON,  double *Lat_GON);
LS_geo_Export void Gon_2_Grad(double  Long_GON,  double  Lat_GON, double *Long_GRAD, double *Lat_GRAD);
LS_geo_Export void Gon_2_Rad(double  Long_GON, double  Lat_GON,  double *Long_RAD, double *Lat_RAD);
LS_geo_Export void Rad_2_Gon(double  Long_RAD, double  Lat_RAD, double *Long_GON, double *Lat_GON);

LS_geo_Export void Dez2GMS (double dez, double *eg, double *em, double *es);
LS_geo_Export void GMS2Dez (double eg, double em, double es, double *dez);
LS_geo_Export void Dez2Sexa (double dez, double *sexagesi);
LS_geo_Export void Sexa2Dez (double sexagesi, double *dez);
LS_geo_Export void GMS2Sexa (double eg, double em, double es, double *sexagesi);
LS_geo_Export void Sexa2GMS (double sexagesi, double *eg, double *em, double *es);
LS_geo_Export void Check_Koord(double east, double north, const KOORDSYSTEM *psys,
 								 short *noerrE, short *noerrN);
LS_geo_Export void Check_Koord2(double east, double north, const KOORDSYSTEM *psys,
 								 	 short *noerrE, short *noerrN);
LS_geo_Export short RangeTest(double x, double min, double max);
LS_geo_Export void Set_UTM_North_South(short NorthHemis);
LS_geo_Export double UTM_Zone2L0(short Zone);
LS_geo_Export double GK3_Zone2L0(short Zone);
LS_geo_Export double GK6_Zone2L0(short Zone);
LS_geo_Export double RSA_Zone2L0(short Zone);
LS_geo_Export short UTM_L02Zone(double Lambda0_E);
LS_geo_Export short GK3_L02Zone(double Lambda0_E);
LS_geo_Export short GK6_L02Zone(double Lambda0_E);
LS_geo_Export short RSA_L02Zone(double Lambda0_E);
LS_geo_Export short Get_Coordsystem_Name(long koordsys, char *systemname);
LS_geo_Export short Get_Coordsys_NameP(long koordsys, char **systemname);
LS_geo_Export short Get_Coordsystem_LongName(long koordsys, char *longname);
LS_geo_Export short Get_Coordsys_LongNameP(long koordsys, char **longname);

LS_geo_Export long GetCategoryItemSize();
LS_geo_Export short GetCategoryItemName(long CategoryItem, char **CategoryItemName);
LS_geo_Export short GetCategorySize(long CategoryItem, long *categorysize);
LS_geo_Export short GetCategoryProjNumber(long CategoryItem, long ProjectionItem, long *sysnr);
LS_geo_Export short GetCategoryProjName(long CategoryItem, long ProjectionItem, char **ShortName);
LS_geo_Export short GetCategoryProjLongName(long CategoryItem, long ProjectionItem, char **LongName);
LS_geo_Export short FindGeoSystem_NULL(long *SysNr);
LS_geo_Export short SysNr2Items(long SysNr,long *CategoryItem, long *ProjectionItem);
LS_geo_Export short IsGeoSystem(long SysNr);
LS_geo_Export short IsTransMerkSystem(long SysNr);
LS_geo_Export short IsUTMSystem(long SysNr);
LS_geo_Export double LusEasting2UtmEasting(long SysNr, double easting);
LS_geo_Export double UtmEasting2LusEasting(long SysNr, double easting);

LS_geo_Export void ls_geo_get_maxcoord(short *maxcoord);
LS_geo_Export KOORDSTRUCT *ls_geo_get_coordparam(short sysnr);

LS_geo_Export short DeleteSpaceInString(char *SpaceStr, char *WithoutStr);
LS_geo_Export short CoordsysName2Number(long *SysNr, char CoordsysName[length32]);
LS_geo_Export short GetZoneNr(long ZoneNr, long SysNr);
LS_geo_Export short EqualCoordSys(long Sys1, long Sys2);
LS_geo_Export short GetMaxCoord();
LS_geo_Export short LuSCoordNr_2_MIparam(long Sysnr, MAPINFOPARAMS *MIparam);
LS_geo_Export short LuSCoordNr_2_MIparamText(long Sysnr, char *MIparamText);
LS_geo_Export short LuSCoordNr_2_MIparamText_P(long Sysnr, char **MIparamText);
LS_geo_Export short MIparam_2_LuSCoordNr(long *Sysnr, MAPINFOPARAMS *MIParam);
LS_geo_Export short MIparamText_2_LuSCoordNr(long *Sysnr, char *MIparamText);
LS_geo_Export short MIparamText_2_LuSCoordNr_P(long *Sysnr, char **MIparamText);


#if __cplusplus && !TRANSLATE_AS_CPLUSPLUS
}

#endif

#endif /* __LSKOORDTRANS__ */

/*
12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/


