/***@#Header******************************************************************
 *
 *  PROJECT:    ls_geo
 *
 *  MODULE:     KoordTransINIT
 *
 *  FILENAME:   KoordTransINIT.h
 *
 *  COPYRIGHT:  L&S Hochfrequenztechnik GmbH
 *              Im Gewerbegebiet 31
 *              77839 Lichtenau
 *              Germany
 *
 *  TOPIC:      ---
 *
 *  AUTHOR:     Peter Clevers (@'PC)
 *
 *  WRITTEN:    @PC010998
 *
 *  MODIFIED:   
 *
 *****************************************************************************
 *
 *  ABSTRACT    (geo):
 *
 *     ---
 *
 ***@#End*********************************************************************/

#ifndef __KOORDTRANSINIT_H__
#define __KOORDTRANSINIT_H__


/***@#Include*****************************************************************
 *
 *  INCLUDES
 *
 *****************************************************************************/

/*#include	<.h>*/

/***@#Version*****************************************************************
 *
 *  VERSION - CODE
 *
 *****************************************************************************/

/***@#MACRO*******************************************************************
 *
 *  MACROS & PREPROCESSOR_CONSTANTS
 *
 *****************************************************************************/

/* #define */
/* ************************************************************************** */
/* ** Hederfile zu LS_Transkoord.cp und dergleichen                        ** */
/* ** Initialisiert verschiedene Felder zur Koordinatentransfromation      ** */
/* ** ㎜&S Hochfrequenztechnik, Lichtenau 1994                             ** */
/* ************************************************************************** */
/* Initialisierung der Parameter fuer den Datumsuebergang */
static ELLIPSOID  Ell[] =
{
/* 00 */	{1.0,			1	,			0,	0,	0,	0,	0,	0,	0,	0},	/* No Ellipsoid */
/* 01 */	{6377563.396,	299.3249646,	0,	0,	0,	0,	0,	0,	0,	0},  /* AIRY_1830e */		
/* 02 */	{6377340.189,	299.3249646,	0,	0,	0,	0,	0,	0,	0,	0},  /* MODIFIED_AIRYe */		
/* 03 */	{6378160,		298.25,			0,	0,	0,	0,	0,	0,	0,	0},  /* AUSTRALIAN_NATIONALe */	
/* 04 */	{6378135,		298.257,		0,	0,	0,	0,	0,	0,	0,	0},  /* AVERAGE_TERRESTRIAL_SYSTEM_1977e */	
/* 05 */	{6377397.155,	299.1528128,	0,	0,	0,	0,	0,	0,	0,	0},  /* BESSEL_1841e -  "Ethiopia,Indonesia,Japan,Korea */		
/* 06 */	{6377483.865,	299.1528128,	0,	0,	0,	0,	0,	0,	0,	0},  /* BESSEL_1841_NAMIBIAe */		
/* 07 */	{6377397.155,	299.1528154,	0,	0,	0,	0,	0,	0,	0,	0},  /* BESSEL_DHDNe */		
/* 08 */	{6377397.154,	299.1528129,	0,	0,	0,	0,	0,	0,	0,	0},  /* BESSEL_RT90e */		
/* 09 */	{6377492.018,	299.15281,		0,	0,	0,	0,	0,	0,	0,	0},  /* BESSEL_NGOe */		
/* 10 */	{6378294,		294.3,			0,	0,	0,	0,	0,	0,	0,	0},  /* CLARKE_1858e */	
/* 11 */	{6378293.639,	294.26068,		0,	0,	0,	0,	0,	0,	0,	0},  /* CLARKE_1858-1e */		
/* 12 */	{6378206.4,		294.9786982,	0,	0,	0,	0,	0,	0,	0,	0},  /* CLARKE_1866e */		
/* 13 */	{6378450.047,	294.9786982,	0,	0,	0,	0,	0,	0,	0,	0},  /* CLARKE_1866_MICHIGANe */		
/* 14 */	{6378249.145,	293.465,		0,	0,	0,	0,	0,	0,	0,	0},  /* CLARKE_1880e */	
/* 15 */	{6378249.145,	293.4666308,	0,	0,	0,	0,	0,	0,	0,	0},  /* CLARKE_1880_ARC50e */		
/* 16 */	{6378249.2,		293.4660213,	0,	0,	0,	0,	0,	0,	0,	0},  /* CLARKE_1880_IGNe */		
/* 17 */	{6378249.136,	293.46631,		0,	0,	0,	0,	0,	0,	0,	0},  /* CLARKE_1880_JAMAICAe */		
/* 18 */	{6378249.2,		293.46598,		0,	0,	0,	0,	0,	0,	0,	0},  /* CLARKE_1880_MERCHICHe */		
/* 19 */	{6378300.79,	293.46623,		0,	0,	0,	0,	0,	0,	0,	0},  /* CLARKE_1880_PALESTINEe */		
/* 20 */	{6378249.2,		293.46598,		0,	0,	0,	0,	0,	0,	0,	0},  /* CLARKE_1880_SGA_1922e */		
/* 21 */	{6377298.556,	300.8017,		0,	0,	0,	0,	0,	0,	0,	0},  /* EVEREST_BRUNEIe */		
/* 22 */	{6377298.561,	300.8017,		0,	0,	0,	0,	0,	0,	0,	0},  /* EVEREST_TIMBALAIe */		
/* 23 */	{6377276.345,	300.8017,		0,	0,	0,	0,	0,	0,	0,	0},  /* EVEREST_1830e - India */		
/* 24 */	{6377301.243,	300.8017,		0,	0,	0,	0,	0,	0,	0,	0},  /* EVEREST_1956e - India */		
/* 25 */	{6377304.063,	300.8017,		0,	0,	0,	0,	0,	0,	0,	0},  /* EVEREST_1948e -  West Malaysia and Singapore */		
/* 26 */	{6377295.664,	300.8017,		0,	0,	0,	0,	0,	0,	0,	0},  /* EVEREST_1969e -  West Malaysia */		
/* 27 */	{6377309.613,	300.8017,		0,	0,	0,	0,	0,	0,	0,	0},  /* EVEREST_PAKISTANe */		
/* 28 */	{6378166,		298.3,			0,	0,	0,	0,	0,	0,	0,	0},  /* FISCHER_1960e */	
/* 29 */	{6378160,		298.25,			0,	0,	0,	0,	0,	0,	0,	0},  /* IUGG_67e */	
/* 30 */	{6378140,		298.257,		0,	0,	0,	0,	0,	0,	0,	0},  /* IUGG_75e */	
/* 31 */	{6378165,		292.3,			0,	0,	0,	0,	0,	0,	0,	0},  /* KAULAe */	
/* 32 */	{6378155,		298.3,			0,	0,	0,	0,	0,	0,	0,	0},  /* MOD_FISCHER_1966e */	
/* 33 */	{6378150,		298.3,			0,	0,	0,	0,	0,	0,	0,	0},  /* FISCHER_1968e */	
/* 34 */	{6378137,		298.25722,		0,	0,	0,	0,	0,	0,	0,	0},  /* GEM_10Ce */	
/* 35 */	{6378160,		298.2471674,	0,	0,	0,	0,	0,	0,	0,	0},  /* GRS67e */	
/* 36 */	{6378137,		298.2572221,	0,	0,	0,	0,	0,	0,	0,	0},  /* GRS80e */	
/* 37 */	{6378388,		297	,			0,	0,	0,	0,	0,	0,	0,	0},  /* HAYFORDe */
/* 38 */	{6378200,		298.3,			0,	0,	0,	0,	0,	0,	0,	0},  /* HELMERT_1906e */	
/* 39 */	{6378270,		297	,			0,	0,	0,	0,	0,	0,	0,	0},  /* HOUGHe */
/* 40 */	{6378140,		298.257222,		0,	0,	0,	0,	0,	0,	0,	0},  /* IAG_75e */	
/* 41 */	{6378388,		297	,			0,	0,	0,	0,	0,	0,	0,	0},  /* INTERNATIONAL_1924e */
/* 42 */	{6378160,		298.247,		0,	0,	0,	0,	0,	0,	0,	0},  /* INDONESIAN_1974e */	
/* 43 */	{6378245,		298.3,			0,	0,	0,	0,	0,	0,	0,	0},  /* KRASSOVSKY_1940e */	
/* 44 */	{6378137,		298.257,		0,	0,	0,	0,	0,	0,	0,	0},  /* MERIT_83e */	
/* 45 */	{6378157.5,		298.25,			0,	0,	0,	0,	0,	0,	0,	0},  /* NEW_INTERNATIONAL_1967e */	
/* 46 */	{6378145,		298.25,			0,	0,	0,	0,	0,	0,	0,	0},  /* NWL_9De */	
/* 47 */	{6378135,		298.26,			0,	0,	0,	0,	0,	0,	0,	0},  /* NWL_10De */	
/* 48 */	{6378136.2,		298.25722,		0,	0,	0,	0,	0,	0,	0,	0},  /* OSU86Fe */		
/* 49 */	{6378136.3,		298.25722,		0,	0,	0,	0,	0,	0,	0,	0},  /* OSU91Ae */		
/* 50 */	{6376523,		308.64,			0,	0,	0,	0,	0,	0,	0,	0},  /* PLESSIS_1817e */	
/* 51 */	{6378136,		298.5839688,	0,	0,	0,	0,	0,	0,	0,	0},  /* SGS85e */	
/* 52 */	{6378160,		298.25,			0,	0,	0,	0,	0,	0,	0,	0},  /* SOUTH_AMERICAN_1969e */	
/* 53 */	{6378155,		298.3000002,	0,	0,	0,	0,	0,	0,	0,	0},  /* SOUTHEAST_ASIAe */	
/* 54 */	{6378297,		294.73,			0,	0,	0,	0,	0,	0,	0,	0},  /* STRUVE_1860e */	
/* 55 */	{6376896,		302.78,			0,	0,	0,	0,	0,	0,	0,	0},  /* WALBECKe */	
/* 56 */	{6378300.583,	296	,			0,	0,	0,	0,	0,	0,	0,	0},  /* WAR_OFFICEe */	
/* 57 */	{6378165,		298.3,			0,	0,	0,	0,	0,	0,	0,	0},  /* WGS60e */	
/* 58 */	{6378145,		298.25,			0,	0,	0,	0,	0,	0,	0,	0},  /* WGS66e */	
/* 59 */	{6378135,		298.26,			0,	0,	0,	0,	0,	0,	0,	0},  /* WGS72e */	
/* 60 */	{6378137,		298.2572236,	0,	0,	0,	0,	0,	0,	0,	0},  /* WGS84e */	
/* 61 */	{6378137,		298.2572236,	0,	0,	0,	0,	0,	0,	0,	0},  /* USER1e */	
/* 62 */	{6378137,		298.2572236,	0,	0,	0,	0,	0,	0,	0,	0},  /* USER2e */	
/* 63 */	{6378137,		298.2572236,	0,	0,	0,	0,	0,	0,	0,	0},  /* USER3e */	
/* 64 */	{6378137,		298.2572236,	0,	0,	0,	0,	0,	0,	0,	0},  /* USER4e */	
/* 65 */	{6378137,		298.2572236,	0,	0,	0,	0,	0,	0,	0,	0},   /* USER5e */	
/*add by CX 2014.12.24*/
/* 66 */	{6378137,		298.257222101,	0,	0,	0,	0,	0,	0,	0,	0},  /* China2000e */	
};
#define MAXELL (sizeof(Ell) / sizeof(ELLIPSOID))


/* Initialisierung der Parameter fuer den Datumsuebergang */
static DATUMSTRANS  DTrans[] =
{/*Methode	Ellipsoid							dX		dY		dZ 		eX 		eY		eZ 		Hoehe		Region of use 	definenamen */
/* 0 */		{NONE_DTRANS,		NOELLIPSOIDe,		0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /* NONEd */
/* 1 */		{MOLODONSKIJ,	CLARKE_1880e,	-118,	-14,	218,	25,	25,	25,	0.0,	0.0,"Burkina Faso"},	  /* ADINDAN_BURKINA_FASOd */
/* 2 */		{MOLODONSKIJ,	CLARKE_1880e,	-134,	-2,	210,	25,	25,	25,	0.0,	0.0,"Cameroon"},	  /* ADINDAN_COMEROONd */
/* 3 */		{MOLODONSKIJ,	CLARKE_1880e,	-165,	-11,	206,	3,	3,	3,	0.0,	0.0,"Ethiopia"},	  /* ADINDAN_ETHIOPIAd */
/* 4 */		{MOLODONSKIJ,	CLARKE_1880e,	-123,	-20,	220,	25,	25,	25,	0.0,	0.0,"Mali"},	  /* ADINDAN_MALId */
/* 5 */		{MOLODONSKIJ,	CLARKE_1880e,	-166,	-15,	204,	5,	5,	3,	0.0,	0.0,"MEAN FOR Ethiopia; Sudan"},	  /* ADINDAN_ETHIOPIA_SUDANd */
/* 6 */		{MOLODONSKIJ,	CLARKE_1880e,	-128,	-18,	224,	25,	25,	25,	0.0,	0.0,"Senegal"},	  /* ADINDAN_SENEGALd */
/* 7 */		{MOLODONSKIJ,	CLARKE_1880e,	-161,	-14,	205,	3,	5,	3,	0.0,	0.0,"Sudan"},	  /* ADINDAN_SUDANd */
/* 8 */		{MOLODONSKIJ,	KRASSOVSKY_1940e,	-43,	-163,	45,	25,	25,	25,	0.0,	0.0,"Somalia"},	  /* AFGOOYEd */
/* 9 */		{MOLODONSKIJ,	INTERNATIONAL_1924e,	-150,	-250,	-1,	25,	25,	25,	0.0,	0.0,"Bahrain"},	  /* AIN_EL_ABD_1970_BAHRAINd */
/* 10 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-143,	-236,	7,	10,	10,	10,	0.0,	0.0,"Saudi Arabia"},	  /* AIN_EL_ABD_1970_SAUDIARABd */
/* 11 */	{MOLODONSKIJ,	CLARKE_1866e,	-115,	118,	426,	25,	25,	25,	0.0,	0.0,"American Samoa Islands"},	  /* AMERICAN_SAMOA_1962d */
/* 12 */	{MOLODONSKIJ,	AUSTRALIAN_NATIONALe,	-491,	-22,	435,	25,	25,	25,	0.0,	0.0,"Cocos Islands"},	  /* ANNA_1_ASTRO_1965d */
/* 13 */	{MOLODONSKIJ,	CLARKE_1880e,	-270,	13,	62,	25,	25,	25,	0.0,	0.0,"Antigua (Leeward Islands)"},	  /* ANTIGUA_ISLAND_ASTRO_1943d */
/* 14 */	{MOLODONSKIJ,	CLARKE_1880e,	-138,	-105,	-289,	3,	5,	3,	0.0,	0.0,"Botswana"},	  /* ARC_1950_BOTSWANAd */
/* 15 */	{MOLODONSKIJ,	CLARKE_1880e,	-153,	-5,	-292,	20,	20,	20,	0.0,	0.0,"Burundi"},	  /* ARC_1950_BURUNDId */
/* 16 */	{MOLODONSKIJ,	CLARKE_1880e,	-125,	-108,	-295,	3,	3,	8,	0.0,	0.0,"Lesotho"},	  /* ARC_1950_LESOTHOd */
/* 17 */	{MOLODONSKIJ,	CLARKE_1880e,	-161,	-73,	-317,	9,	24,	8,	0.0,	0.0,"Malawi"},	  /* ARC_1950_MALAWId */
/* 18 */	{MOLODONSKIJ,	CLARKE_1880e,	-143,	-90,	-294,	20,	33,	20,	0.0,	0.0,"MEAN FOR Botswana; Lesotho; Malawi; Swaziland; Zaire; Zambia; Zimbabwe"},	  /* ARC_1950_MEANd */
/* 19 */	{MOLODONSKIJ,	CLARKE_1880e,	-134,	-105,	-295,	15,	15,	15,	0.0,	0.0,"Swaziland"},	  /* ARC_1950_SWAZILANDd */
/* 20 */	{MOLODONSKIJ,	CLARKE_1880e,	-169,	-19,	-278,	25,	25,	25,	0.0,	0.0,"Zaire"},	  /* ARC_1950_ZAIREd */
/* 21 */	{MOLODONSKIJ,	CLARKE_1880e,	-147,	-74,	-283,	21,	21,	27,	0.0,	0.0,"Zambia"},	  /* ARC_1950_ZAMBIAd */
/* 22 */	{MOLODONSKIJ,	CLARKE_1880e,	-142,	-96,	-293,	5,	8,	11,	0.0,	0.0,"Zimbabwe"},	  /* ARC_1950_ZIMBABWEd */
/* 23 */	{MOLODONSKIJ,	CLARKE_1880e,	-160,	-6,	-302,	20,	20,	20,	0.0,	0.0,"MEAN FOR Kenya; Tanzania"},	  /* ARC_1960_KENIA_TANZANIAd */
/* 24 */	{MOLODONSKIJ,	CLARKE_1880e,	-157,	-2,	-299,	4,	3,	3,	0.0,	0.0,"Kenya"},	  /* ARC_1960_KENIAd */
/* 25 */	{MOLODONSKIJ,	CLARKE_1880e,	-175,	-23,	-303,	6,	9,	10,	0.0,	0.0,"Taanzania"},	  /* ARC_1960_TANZANIAd */
/* 26 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-205,	107,	53,	25,	25,	25,	0.0,	0.0,"Ascension Island"},	  /* ASCENSION_ISLAND_1958d */
/* 27 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	145,	75,	-272,	25,	25,	25,	0.0,	0.0,"Iwo Jima"},	  /* ASTRO_BEACON_E_1945d */
/* 28 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-320,	550,	-494,	25,	25,	25,	0.0,	0.0,"St Helena Island"},	  /* ASTRO_DOS_71/4d */
/* 29 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	114,	-116,	-333,	25,	25,	25,	0.0,	0.0,"Tern Island"},	  /* ASTRO_TERN_ISLAND_FRIG_1961d */
/* 30 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	124,	-234,	-25,	25,	25,	25,	0.0,	0.0,"Marcus Island"},	  /* ASTRONOMICAL_STATION_1952d */
/* 31 */	{MOLODONSKIJ,	AUSTRALIAN_NATIONALe,	-133,	-48,	148,	3,	3,	3,	0.0,	0.0,"Australia; Tasmania"},	  /* AUSTRALIAN_GEODETIC_1966d */
/* 32 */	{MOLODONSKIJ,	AUSTRALIAN_NATIONALe,	-134,	-48,	149,	2,	2,	2,	0.0,	0.0,"Australia; Tasmania"},	  /* AUSTRALIAN_GEODETIC_1984d */
/* 33 */	{MOLODONSKIJ,	CLARKE_1880e,	-79,	-129,	145,	25,	25,	25,	0.0,	0.0,"Djibouti"},	  /* AYABELLE_LIGHTHOUSEd */
/* 34 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-127,	-769,	472,	20,	20,	20,	0.0,	0.0,"Efate & Erromango Islands"},	  /* BELLEVUE_IGNd */
/* 35 */	{MOLODONSKIJ,	CLARKE_1866e,	-73,	213,	296,	20,	20,	20,	0.0,	0.0,"Bermuda"},	  /* BERMUDA_1957d */
/* 36 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-173,	253,	27,	25,	25,	25,	0.0,	0.0,"Guinea-Bissau"},	  /* BISSAUd */
/* 37 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	307,	304,	-318,	6,	5,	6,	0.0,	0.0,"Colombia"},	  /* BOGOTA_OBSERVATORYd */
/* 38 */	{MOLODONSKIJ,	BESSEL_1841e,	-384,	664,	-48,	-1,	-1,	-1,	0.0,	0.0,"Indonesia (Bangka & Belitung Ids)"},	  /* BUKIT_RIMPAHd */
/* 39 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-104,	-129,	239,	-1,	-1,	-1,	0.0,	0.0,"Antarctica (McMurdo Camp Area)"},	  /* CAMP_AREA_ASTROd */
/* 40 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-148,	136,	90,	5,	5,	5,	0.0,	0.0,"Argentina"},	  /* CAMPO_INCHAUSPEd */
/* 41 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	298,	-304,	-375,	15,	15,	15,	0.0,	0.0,"Phoenix Islands"},	  /* CANTON_ASTRO_1966d */
/* 42 */	{MOLODONSKIJ,	CLARKE_1880e,	-136,	-108,	-292,	3,	6,	6,	0.0,	0.0,"South Africa"},	  /* CAPEd */
/* 43 */	{MOLODONSKIJ,	CLARKE_1866e,	-2,	151,	181,	3,	3,	3,	0.0,	0.0,"Bahamas; Florida"},	  /* CAPE_CANAVERALd */
/* 44 */	{MOLODONSKIJ,	CLARKE_1880e,	-263,	6,	431,	6,	9,	8,	0.0,	0.0,"Tunisia"},	  /* CARTHAGEd */
/* 45 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	175,	-38,	113,	15,	15,	15,	0.0,	0.0,"New Zealand (Chatham Island)"},	  /* CHATHAM_ISLAND_ASTRO_1971d */
/* 46 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-134,	229,	-29,	6,	9,	5,	0.0,	0.0,"Paraguay"},	  /* CHUA_ASTROd */
/* 47 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-206,	172,	-6,	5,	3,	5,	0.0,	0.0,"Brazil"},	  /* CORREGO_ALEGREd */
/* 48 */	{MOLODONSKIJ,	CLARKE_1880e,	-83,	37,	124,	15,	15,	15,	0.0,	0.0,"Guinea"},	  /* DABOLAd */
/* 49 */	{MOLODONSKIJ,	CLARKE_1880e,	260,	12,	-147,	20,	20,	20,	0.0,	0.0,"Deception Island; Antarctia"},	  /* DECEPTION_ISLANDd */
/* 50 */	{MOLODONSKIJ,	BESSEL_1841e,	-377,	681,	-50,	3,	3,	3,	0.0,	0.0,"Indonesia (Sumatra)"},	  /* DJAKARTA_BATAVIAd */
/* 51 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	230,	-199,	-752,	25,	25,	25,	0.0,	0.0,"New Georgia Islands (Gizo Island)"},	  /* DOS_1968d */
/* 52 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	211,	147,	111,	25,	25,	25,	0.0,	0.0,"Easter Island"},	  /* EASTER_ISLAND_1967d */
/* 53 */	{MOLODONSKIJ,	BESSEL_1841e,	374,	150,	588,	2,	3,	3,	0.0,	0.0,"Estonia"},	  /* ESTONIA_COORDINATE_SYSTEM_1937d */
/* 54 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-104,	-101,	-140,	15,	15,	15,	0.0,	0.0,"Cyprus"},	  /* ED50_CYPRUSd */
/* 55 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-130,	-117,	-151,	6,	8,	8,	0.0,	0.0,"Egypt"},	  /* ED50_EGYPTd */
/* 56 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-86,	-96,	-120,	3,	3,	3,	0.0,	0.0,"England; Channel Islands; Scotland; Shetland Islands"},	  /* ED50_CHANNELISLANDSd */
/* 57 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-86,	-96,	-120,	3,	3,	3,	0.0,	0.0,"England; Ireland; Scotland; Shetland Islands"},	  /* ED50_ENGLANDd */
/* 58 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-87,	-95,	-120,	3,	5,	3,	0.0,	0.0,"Finland; Norway"},	  /* ED50_FINLAND_NORWAYd */
/* 59 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-84,	-95,	-130,	25,	25,	25,	0.0,	0.0,"Greece"},	  /* ED50_GREECEd */
/* 60 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-117,	-132,	-164,	9,	12,	11,	0.0,	0.0,"Iran"},	  /* ED50_IRANd */
/* 61 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-97,	-103,	-120,	25,	25,	25,	0.0,	0.0,"Italy (Sardinia)"},	  /* ED50_SARDIANIAd */
/* 62 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-97,	-88,	-135,	20,	20,	20,	0.0,	0.0,"Italy (Sicily)"},	  /* ED50_SICILYd */
/* 63 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-107,	-88,	-149,	25,	25,	25,	0.0,	0.0,"Malta"},	  /* ED50_MALTAd */
/* 64 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-87,	-98,	-121,	3,	8,	5,	0.0,	0.0,"MEAN FOR Austria; Belgium; Denmark; Finland; France; W Germany; Gibraltar; Greece; Italy; Luxembourg; Netherlands; Norway; Portugal; Spain; Sweden; Switzerland"},	  /* ED50_EUROPEd */
/* 65 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-87,	-96,	-120,	3,	3,	3,	0.0,	0.0,"MEAN FOR Austria; Denmark; France; W Germany; Netherlands; Switzerland"},	  /* ED50_CENTRAL_EUROPEd */
/* 66 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-103,	-106,	-141,	-1,	-1,	-1,	0.0,	0.0,"MEAN FOR Iraq; Israel; Jordan; Lebanon; Kuwait; Saudi Arabia; Syria"},	  /* ED50_ARABIAd */
/* 67 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-84,	-107,	-120,	5,	6,	3,	0.0,	0.0,"Portugal; Spain"},	  /* ED50_PORTUGAL_SPAINd */
/* 68 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-112,	-77,	-145,	25,	25,	25,	0.0,	0.0,"Tunisia"},	  /* ED50_TUNESIAd */
/* 69 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-86,	-98,	-119,	3,	3,	3,	0.0,	0.0,"MEAN FOR Austria; Finland; Netherlands; Norway; Spain; Sweden; Switzerland"},	  /* EUROPEAN_1979d */
/* 70 */	{MOLODONSKIJ,	CLARKE_1880e,	-7,	215,	225,	25,	25,	25,	0.0,	0.0,"Nevis; St. Kitts (Leeward Islands)"},	  /* FORT_THOMAS_1955d */
/* 71 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-133,	-321,	50,	25,	25,	25,	0.0,	0.0,"Republic of Maldives"},	  /* GAN_1970d */
/* 72 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	84,	-22,	209,	5,	3,	5,	0.0,	0.0,"New Zealand"},	  /* GEODETIC_DATUM_1949d */
/* 73 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-104,	167,	-38,	3,	3,	3,	0.0,	0.0,"Azores (Faial; Graciosa; Pico; Sao Jorge; Terceira)"},	  /* GRACIOSA_BASE_SW_1948d */
/* 74 */	{MOLODONSKIJ,	CLARKE_1866e,	-100,	-248,	259,	3,	3,	3,	0.0,	0.0,"Guam"},	  /* GUAM_1963d */
/* 75 */	{MOLODONSKIJ,	BESSEL_1841e,	-403,	684,	41,	-1,	-1,	-1,	0.0,	0.0,"Indonesia (Kalimantan)"},	  /* GUNUNG_SEGARAd */
/* 76 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	252,	-209,	-751,	25,	25,	25,	0.0,	0.0,"Guadalcanal Island"},	  /* GUX_1_ASTROd */
/* 77 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-333,	-222,	114,	-1,	-1,	-1,	0.0,	0.0,"Afghanistan"},	  /* HERAT_NORTHd */
/* 78 */	{MOLODONSKIJ,	BESSEL_1841_NAMIBIAe,	653,	-212,	449,	-1,	-1,	-1,	0.0,	0.0,"Croatia -Serbia, Bosnia-Herzegovina "},	  /* HERMANNSKOGEL_DATUMd */
/* 79 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-73,	46,	-86,	3,	3,	6,	0.0,	0.0,"Iceland"},	  /* HJORSEY_1955d */
/* 80 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-156,	-271,	-189,	25,	25,	25,	0.0,	0.0,"Hong Kong"},	  /* HONG_KONG_1963d */
/* 81 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-637,	-549,	-203,	15,	15,	15,	0.0,	0.0,"Taiwan"},	  /* HU_TZU_SHANd */
/* 82 */	{MOLODONSKIJ,	EVEREST_INDIA_1956e,	282,	726,	254,	10,	8,	12,	0.0,	0.0,"Bangladesh"},	  /* INDIAN_BANGLADESHd */
/* 83 */	{MOLODONSKIJ,	EVEREST_INDIA_1956e,	295,	736,	257,	12,	10,	15,	0.0,	0.0,"India; Nepal"},	  /* INDIAN_INDIA_NEPALd */
/* 84 */	{MOLODONSKIJ,	EVEREST_PAKISTANe,	283,	682,	231,	-1,	-1,	-1,	0.0,	0.0,"Pakistan"},	  /* INDIAN_PAKISTANd */
/* 85 */	{MOLODONSKIJ,	EVEREST_INDIA_1956e,	217,	823,	299,	15,	6,	12,	0.0,	0.0,"Thailand"},	  /* INDIAN_1954d */
/* 86 */	{MOLODONSKIJ,	EVEREST_INDIA_1956e,	182,	915,	344,	25,	25,	25,	0.0,	0.0,"Vietnam (Con Son Island)"},	  /* INDIAN_1960_CON_SONd */
/* 87 */	{MOLODONSKIJ,	EVEREST_INDIA_1956e,	198,	881,	317,	25,	25,	25,	0.0,	0.0,"Vietnam (Near 16鳱)"},	  /* INDIAN_1960_VIETNAMd */
/* 88 */	{MOLODONSKIJ,	EVEREST_INDIA_1956e,	210,	814,	289,	3,	2,	3,	0.0,	0.0,"Thailand"},	  /* INDIAN_1975d */
/* 89 */	{MOLODONSKIJ,	INDONESIAN_1974e,	-24,	-15,	5,	25,	25,	25,	0.0,	0.0,"Indonesia"},	  /* INDONESIAN_1974d */
/* 90 */	{MOLODONSKIJ,	MODIFIED_AIRYe,	506,	-122,	611,	3,	3,	3,	0.0,	0.0,"Ireland"},	  /* IRELAND_1965d */
/* 91 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-794,	119,	-298,	25,	25,	25,	0.0,	0.0,"South Georgia Islands"},	  /* ISTS_061_ASTRO_1968d */
/* 92 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	208,	-435,	-229,	25,	25,	25,	0.0,	0.0,"Diego Garcia"},	  /* ISTS_073_ASTRO_1969d */
/* 93 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	189,	-79,	-202,	25,	25,	25,	0.0,	0.0,"Johnston Island"},	  /* JOHNSTON_ISLAND_1961d */
/* 94 */	{MOLODONSKIJ,	EVEREST_INDIA_1956e,	-97,	787,	86,	20,	20,	20,	0.0,	0.0,"Sri Lanka"},	  /* KANDAWALAd */
/* 95 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	145,	-187,	103,	25,	25,	25,	0.0,	0.0,"Kerguelen Island"},	  /* KERGUELEN_ISLAND_1949d */
/* 96 */	{MOLODONSKIJ,	EVEREST_1948e,	-11,	851,	5,	10,	8,	6,	0.0,	0.0,"West Malaysia & Singapore"},	  /* KERTAU_1948d */
/* 97 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	647,	1777,	-1124,	25,	25,	25,	0.0,	0.0,"Caroline Islands"},	  /* KUSAIE_ASTRO_1951d */
/* 98 */	{MOLODONSKIJ,	GRS80e,	0,	0,	0,	2,	2,	2,	0.0,	0.0,"South Korea"},	  /* KOREAN_GEODETIC_SYSTEMd */
/* 99 */	{MOLODONSKIJ,	CLARKE_1866e,	42,	124,	147,	25,	25,	25,	0.0,	0.0,"Cayman Brac Island"},	  /* L._C_5_ASTRO_1961d */
/* 100 */	{MOLODONSKIJ,	CLARKE_1880e,	-130,	29,	364,	2,	3,	2,	0.0,	0.0,"Ghana"},	  /* LEIGONd */
/* 101 */	{MOLODONSKIJ,	CLARKE_1880e,	-90,	40,	88,	15,	15,	15,	0.0,	0.0,"Liberia"},	  /* LIBERIA_1964d */
/* 102 */	{MOLODONSKIJ,	CLARKE_1866e,	-133,	-77,	-51,	8,	11,	9,	0.0,	0.0,"Philippines (Excluding Mindanao)"},	  /* LUZON_PHILIPPINESd */
/* 103 */	{MOLODONSKIJ,	CLARKE_1866e,	-133,	-79,	-72,	25,	25,	25,	0.0,	0.0,"Philippines (Mindanao)"},	  /* LUZON_MINDANAOd */
/* 104 */	{MOLODONSKIJ,	CLARKE_1880e,	-74,	-130,	42,	25,	25,	25,	0.0,	0.0,"Gabon"},	  /* M_PORALOKOd */
/* 105 */	{MOLODONSKIJ,	CLARKE_1880e,	41,	-220,	-134,	25,	25,	25,	0.0,	0.0,"Mahe Island"},	  /* MAHE_1971d */
/* 106 */	{MOLODONSKIJ,	BESSEL_1841e,	639,	405,	60,	25,	25,	25,	0.0,	0.0,"Ethiopia (Eritrea)"},	  /* MASSAWAd */
/* 107 */	{MOLODONSKIJ,	CLARKE_1880e,	31,	146,	47,	5,	3,	3,	0.0,	0.0,"Morocco"},	  /* MERCHICHd */
/* 108 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	912,	-58,	1227,	25,	25,	25,	0.0,	0.0,"Midway Islands"},	  /* MIDWAY_ASTRO_1961d */
/* 109 */	{MOLODONSKIJ,	CLARKE_1880e,	-81,	-84,	115,	25,	25,	25,	0.0,	0.0,"Cameroon"},	  /* MINNA_CAMEROONd */
/* 110 */	{MOLODONSKIJ,	CLARKE_1880e,	-92,	-93,	122,	3,	6,	5,	0.0,	0.0,"Nigeria"},	  /* MINNA_NIGERIAd */
/* 111 */	{MOLODONSKIJ,	CLARKE_1880e,	174,	359,	365,	25,	25,	25,	0.0,	0.0,"Montserrat (Leeward Islands)"},	  /* MONTSERRAT_ISLAND_ASTRO_1958d */
/* 112 */	{MOLODONSKIJ,	CLARKE_1880e,	-247,	-148,	369,	25,	25,	25,	0.0,	0.0,"Oman (Masirah Island)"},	  /* NAHRWAN_OMANd */
/* 113 */	{MOLODONSKIJ,	CLARKE_1880e,	-243,	-192,	477,	20,	20,	20,	0.0,	0.0,"Saudi Arabia"},	  /* NAHRWAN_SAUDI_ARABIAd */
/* 114 */	{MOLODONSKIJ,	CLARKE_1880e,	-249,	-156,	381,	25,	25,	25,	0.0,	0.0,"United Arab Emirates"},	  /* NAHRWAN_EMIRATESd */
/* 115 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-10,	375,	165,	15,	15,	15,	0.0,	0.0,"Trinidad & Tobago"},	  /* NAPARIMA_BWId */
/* 116 */	{MOLODONSKIJ,	CLARKE_1866e,	-5,	135,	172,	5,	9,	5,	0.0,	0.0,"Alaska (Excluding Aleutian Ids)"},	  /* NAD27_ALASKAd */
/* 117 */	{MOLODONSKIJ,	CLARKE_1866e,	-2,	152,	149,	6,	8,	10,	0.0,	0.0,"Alaska (Aleutian Ids East of 180鳺)"},	  /* NAD27_ALEUTIAN_EASTd */
/* 118 */	{MOLODONSKIJ,	CLARKE_1866e,	2,	204,	105,	10,	10,	10,	0.0,	0.0,"Alaska (Aleutian Ids West of 180鳺)"},	  /* NAD27_ALEUTIAN_WESTd */
/* 119 */	{MOLODONSKIJ,	CLARKE_1866e,	-4,	154,	178,	5,	3,	5,	0.0,	0.0,"Bahamas (Except San Salvador Id)"},	  /* NAD27_BAHAMASd */
/* 120 */	{MOLODONSKIJ,	CLARKE_1866e,	1,	140,	165,	25,	25,	25,	0.0,	0.0,"Bahamas (San Salvador Island)"},	  /* NAD27_SAN_SALVADORd */
/* 121 */	{MOLODONSKIJ,	CLARKE_1866e,	-7,	162,	188,	8,	8,	6,	0.0,	0.0,"Canada (Alberta; British Columbia)"},	  /* NAD27_CAN_ALBERTAd */
/* 122 */	{MOLODONSKIJ,	CLARKE_1866e,	-9,	157,	184,	9,	5,	5,	0.0,	0.0,"Canada (Manitoba; Ontario)"},	  /* NAD27_CAN_ONTARIOd */
/* 123 */	{MOLODONSKIJ,	CLARKE_1866e,	-22,	160,	190,	6,	6,	3,	0.0,	0.0,"Canada (New Brunswick; Newfoundland; Nova Scotia; Quebec)"},	  /* NAD27_CAN_QUEBECd */
/* 124 */	{MOLODONSKIJ,	CLARKE_1866e,	4,	159,	188,	5,	5,	3,	0.0,	0.0,"Canada (Northwest Territories; Saskatchewan)"},	  /* NAD27_CAN_NWTERRETORIESd */
/* 125 */	{MOLODONSKIJ,	CLARKE_1866e,	-7,	139,	181,	5,	8,	3,	0.0,	0.0,"Canada (Yukon)"},	  /* NAD27_CAN_YUKONd */
/* 126 */	{MOLODONSKIJ,	CLARKE_1866e,	0,	125,	201,	20,	20,	20,	0.0,	0.0,"Canal Zone"},	  /* NAD27_CANAL_ZONEd */
/* 127 */	{MOLODONSKIJ,	CLARKE_1866e,	-9,	152,	178,	25,	25,	25,	0.0,	0.0,"Cuba"},	  /* NAD27_CUBAd */
/* 128 */	{MOLODONSKIJ,	CLARKE_1866e,	11,	114,	195,	25,	25,	25,	0.0,	0.0,"Greenland (Hayes Peninsula)"},	  /* NAD27_GREENLANDd */
/* 129 */	{MOLODONSKIJ,	CLARKE_1866e,	-3,	142,	183,	3,	9,	12,	0.0,	0.0,"MEAN FOR Antigua; Barbados; Barbuda; Caicos Islands; Cuba; Dominican Republic; Grand Cayman; Jamaica; Turks Islands"},	  /* NAD27_CARIBEAN_WESTd */
/* 130 */	{MOLODONSKIJ,	CLARKE_1866e,	0,	125,	194,	8,	3,	5,	0.0,	0.0,"MEAN FOR Belize; Costa Rica; El Salvador; Guatemala; Honduras; Nicaragua"},	  /* NAD27_MIDDLE_AMERIKAd */
/* 131 */	{MOLODONSKIJ,	CLARKE_1866e,	-10,	158,	187,	15,	11,	6,	0.0,	0.0,"MEAN FOR Canada"},	  /* NAD27_CANADAd */
/* 132 */	{MOLODONSKIJ,	CLARKE_1866e,	-8,	160,	176,	5,	5,	6,	0.0,	0.0,"MEAN FOR CONUS"},	  /* NAD27_CONUSd */
/* 133 */	{MOLODONSKIJ,	CLARKE_1866e,	-9,	161,	179,	5,	5,	8,	0.0,	0.0,"MEAN FOR CONUS (East of Mississippi; River Including Louisiana; Missouri; Minnesota)"},	  /* NAD27_EAST_MISSISSIPPId */
/* 134 */	{MOLODONSKIJ,	CLARKE_1866e,	-8,	159,	175,	5,	3,	3,	0.0,	0.0,"MEAN FOR CONUS (West of Mississippi; River Excluding Louisiana; Minnesota; Missouri)"},	  /* NAD27_WEST_MISSISSIPPId */
/* 135 */	{MOLODONSKIJ,	CLARKE_1866e,	-12,	130,	190,	8,	6,	6,	0.0,	0.0,"Mexico"},	  /* NAD27_MEXICOd */
/* 136 */	{MOLODONSKIJ,	GRS80e,	0,	0,	0,	2,	2,	2,	0.0,	0.0,"Alaska (Excluding Aleutian Ids)"},	  /* NAD83_ALASKAd */
/* 137 */	{MOLODONSKIJ,	GRS80e,	-2,	0,	4,	5,	2,	5,	0.0,	0.0,"Aleutian Ids"},	  /* NAD83_ALEUTIANd */
/* 138 */	{MOLODONSKIJ,	GRS80e,	0,	0,	0,	2,	2,	2,	0.0,	0.0,"Canada"},	  /* NAD83_CANADAd */
/* 139 */	{MOLODONSKIJ,	GRS80e,	0,	0,	0,	2,	2,	2,	0.0,	0.0,"CONUS"},	  /* NAD83_CONUSd */
/* 140 */	{MOLODONSKIJ,	GRS80e,	1,	1,	-1,	2,	2,	2,	0.0,	0.0,"Hawaii"},	  /* NAD83_HAWAId */
/* 141 */	{MOLODONSKIJ,	GRS80e,	0,	0,	0,	2,	2,	2,	0.0,	0.0,"Mexico; Central America"},	  /* NAD83_MEXICO_CENTRAL_AMERIKAd */
/* 142 */	{MOLODONSKIJ,	CLARKE_1880e,	-186,	-93,	310,	25,	25,	25,	0.0,	0.0,"Algeria"},	  /* NORTH_SAHARA_1959d */
/* 143 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-425,	-169,	81,	20,	20,	20,	0.0,	0.0,"Azores (Corvo & Flores Islands)"},	  /* OBSERVATORIO_METEOROLOGICO_1939d */
/* 144 */	{MOLODONSKIJ,	HELMERT_1906e,	-130,	110,	-13,	3,	6,	8,	0.0,	0.0,"Egypt"},	  /* OLD_EGYPTIAN_1907d */
/* 145 */	{MOLODONSKIJ,	CLARKE_1866e,	89,	-279,	-183,	25,	25,	25,	0.0,	0.0,"Hawaii"},	  /* OLD_HAWAIIAN_HAWAIId */
/* 146 */	{MOLODONSKIJ,	CLARKE_1866e,	45,	-290,	-172,	20,	20,	20,	0.0,	0.0,"Kauai"},	  /* OLD_HAWAIIAN_KAUAId */
/* 147 */	{MOLODONSKIJ,	CLARKE_1866e,	65,	-290,	-190,	25,	25,	25,	0.0,	0.0,"Maui"},	  /* OLD_HAWAIIAN_MAUId */
/* 148 */	{MOLODONSKIJ,	CLARKE_1866e,	61,	-285,	-181,	25,	20,	20,	0.0,	0.0,"MEAN FOR Hawaii; Kauai; Maui; Oahu"},	  /* OLD_HAWAIIANd */
/* 149 */	{MOLODONSKIJ,	CLARKE_1866e,	58,	-283,	-182,	10,	6,	6,	0.0,	0.0,"Oahu"},	  /* OLD_HAWAIIAN_OAHUd */
/* 150 */	{MOLODONSKIJ,	CLARKE_1880e,	-346,	-1,	224,	3,	3,	9,	0.0,	0.0,"Oman"},	  /* OMANd */
/* 151 */	{MOLODONSKIJ,	AIRY_1830e,	371,	-112,	434,	5,	5,	6,	0.0,	0.0,"England"},	  /* GB1936_ENGLANDd */
/* 152 */	{MOLODONSKIJ,	AIRY_1830e,	371,	-111,	434,	10,	10,	15,	0.0,	0.0,"England; Isle of Man; Wales"},	  /* GB1936_ENG_WALES_ISLEMANd */
/* 153 */	{MOLODONSKIJ,	AIRY_1830e,	375,	-111,	431,	10,	10,	15,	0.0,	0.0,"MEAN FOR England; Isle of Man; Scotland; Shetland Islands; Wales"},	  /* GB1936d */
/* 154 */	{MOLODONSKIJ,	AIRY_1830e,	384,	-111,	425,	10,	10,	10,	0.0,	0.0,"Scotland; Shetland Islands"},	  /* GB1936_SCOTLAND_SHETLANDd */
/* 155 */	{MOLODONSKIJ,	AIRY_1830e,	370,	-108,	434,	20,	20,	20,	0.0,	0.0,"Wales"},	  /* GB1936_WALESd */
/* 156 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-307,	-92,	127,	25,	25,	25,	0.0,	0.0,"Canary Islands"},	  /* PICO_DE_LAS_NIEVESd */
/* 157 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	185,	165,	42,	25,	25,	25,	0.0,	0.0,"Pitcairn Island"},	  /* PITCAIRN_ASTRO_1967d */
/* 158 */	{MOLODONSKIJ,	CLARKE_1880e,	-106,	-129,	165,	25,	25,	25,	0.0,	0.0,"MEAN FOR Burkina Faso & Niger"},	  /* POINT_58d */
/* 159 */	{MOLODONSKIJ,	CLARKE_1880e,	-148,	51,	-291,	25,	25,	25,	0.0,	0.0,"Congo"},	  /* POINTE_NOIRE_1948d */
/* 160 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-499,	-249,	314,	25,	25,	25,	0.0,	0.0,"Porto Santo; Madeira Islands"},	  /* PORTO_SANTO_1936d */
/* 161 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-270,	188,	-388,	5,	11,	14,	0.0,	0.0,"Bolivia"},	  /* PROV_S_AMERICAN56_BOLIVIAd */
/* 162 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-270,	183,	-390,	25,	25,	25,	0.0,	0.0,"Chile (Northern; Near 19鳶)"},	  /* PROV_S_AMERICAN56_CHILE_NORTHd */
/* 163 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-305,	243,	-442,	20,	20,	20,	0.0,	0.0,"Chile (Southern; Near 43鳶)"},	  /* PROV_S_AMERICAN56_CHILE_SOUTHd */
/* 164 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-282,	169,	-371,	15,	15,	15,	0.0,	0.0,"Colombia"},	  /* PROV_S_AMERICAN56_COLOMBIAd */
/* 165 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-278,	171,	-367,	3,	5,	3,	0.0,	0.0,"Ecuador"},	  /* PROV_S_AMERICAN56_ECUADORd */
/* 166 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-298,	159,	-369,	6,	14,	5,	0.0,	0.0,"Guyana"},	  /* PROV_S_AMERICAN56_GUYANAd */
/* 167 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-288,	175,	-376,	17,	27,	27,	0.0,	0.0,"MEAN FOR Bolivia; Chile; Colombia; Ecuador; Guyana; Peru; Venezuela"},	  /* PROVISIONAL_SOUTH_AMERICAN_1956d */
/* 168 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-279,	175,	-379,	6,	8,	12,	0.0,	0.0,"Peru"},	  /* PROV_S_AMERICAN56_PERUd */
/* 169 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-295,	173,	-371,	9,	14,	15,	0.0,	0.0,"Venezuela"},	  /* PROV_S_AMERICAN56_VENEZUELAd */
/* 170 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	16,	196,	93,	25,	25,	25,	0.0,	0.0,"Chile (Near 53鳶) (Hito XVIII)"},	  /* PROVISIONAL_SOUTH_CHILEAN_1963d */
/* 171 */	{MOLODONSKIJ,	CLARKE_1866e,	11,	72,	-101,	3,	3,	3,	0.0,	0.0,"Puerto Rico; Virgin Islands"},	  /* PUERTO_RICOd */
/* 172 */	{MOLODONSKIJ,	KRASSOVSKY_1940e,	28,	-130,	-95,	-1,	-1,	-1,	0.0,	0.0,"Russia"},	  /* PULKOVO_1942d */
/* 173 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-128,	-283,	22,	20,	20,	20,	0.0,	0.0,"Qatar"},	  /* QATAR_NATIONALd */
/* 174 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	164,	138,	-189,	25,	25,	32,	0.0,	0.0,"Greenland (South)"},	  /* QORNOQd */
/* 175 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	94,	-948,	-1262,	25,	25,	25,	0.0,	0.0,"Mascarene Islands"},	  /* REUNIONd */
/* 176 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-225,	-65,	9,	25,	25,	25,	0.0,	0.0,"Italy (Sardinia)"},	  /* ROME_1940d */
/* 177 */	{MOLODONSKIJ,	KRASSOVSKY_1940e,	28,	-121,	-77,	2,	2,	2,	0.0,	0.0,"Hungary"},	  /* S_42_HUNGARYd */
/* 178 */	{MOLODONSKIJ,	KRASSOVSKY_1940e,	23,	-124,	-82,	4,	2,	4,	0.0,	0.0,"Poland"},	  /* S_42_POLANDd */
/* 179 */	{MOLODONSKIJ,	KRASSOVSKY_1940e,	26,	-121,	-78,	3,	3,	2,	0.0,	0.0,"Czechoslavakia"},	  /* S_42_CZECHOSLOVAKIAd */
/* 180 */	{MOLODONSKIJ,	KRASSOVSKY_1940e,	24,	-124,	-82,	2,	2,	2,	0.0,	0.0,"Latvia"},	  /* S_42_LATVIAd */
/* 181 */	{MOLODONSKIJ,	KRASSOVSKY_1940e,	15,	-130,	-84,	25,	25,	25,	0.0,	0.0,"Kazakhstan"},	  /* S_42_KAZAKHSTANd */
/* 182 */	{MOLODONSKIJ,	KRASSOVSKY_1940e,	24,	-130,	-92,	3,	3,	3,	0.0,	0.0,"Albania"},	  /* S_42_ALBANIAd */
/* 183 */	{MOLODONSKIJ,	KRASSOVSKY_1940e,	28,	-121,	-77,	3,	5,	3,	0.0,	0.0,"Romania"},	  /* S_42_ROMANIAd */
/* 184 */	{MOLODONSKIJ,	BESSEL_1841e,	589,	76,	480,	4,	2,	3,	0.0,	0.0,"Czechoslavakia (Prior 1 JAN 1993)"},	  /* S_JTSKd */
/* 185 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	170,	42,	84,	25,	25,	25,	0.0,	0.0,"Espirito Santo Island"},	  /* SANTO_DOS_1965d */
/* 186 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-203,	141,	53,	25,	25,	25,	0.0,	0.0,"Azores (Sao Miguel; Santa Maria Ids)"},	  /* SAO_BRAZd */
/* 187 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-355,	21,	72,	1,	1,	1,	0.0,	0.0,"East Falkland Island"},	  /* SAPPER_HILL_1943d */
/* 188 */	{MOLODONSKIJ,	BESSEL_1841_NAMIBIAe,	616,	97,	-251,	20,	20,	20,	0.0,	0.0,"Namibia"},	  /* SCHWARZECKd */
/* 189 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-289,	-124,	60,	25,	25,	25,	0.0,	0.0,"Salvage Islands"},	  /* SELVAGEM_GRANDE_1938d */
/* 190 */	{MOLODONSKIJ,	CLARKE_1880e,	-88,	4,	101,	15,	15,	15,	0.0,	0.0,"Sierra Leone"},	  /* SIERRA_LEONE_1960d */
/* 191 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-62,	-1,	-37,	5,	5,	5,	0.0,	0.0,"Argentina"},	  /* S_AMERICAN69_ARGENTINAd */
/* 192 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-61,	2,	-48,	15,	15,	15,	0.0,	0.0,"Bolivia"},	  /* S_AMERICAN69_BOLIVIAd */
/* 193 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-60,	-2,	-41,	3,	5,	5,	0.0,	0.0,"Brazil"},	  /* S_AMERICAN69_BRAZILd */
/* 194 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-75,	-1,	-44,	15,	8,	11,	0.0,	0.0,"Chile"},	  /* S_AMERICAN69_CHILEd */
/* 195 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-44,	6,	-36,	6,	6,	5,	0.0,	0.0,"Colombia"},	  /* S_AMERICAN69_COLOMBIAd */
/* 196 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-48,	3,	-44,	3,	3,	3,	0.0,	0.0,"Ecuador"},	  /* S_AMERICAN69_ECUADORd */
/* 197 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-47,	26,	-42,	25,	25,	25,	0.0,	0.0,"Ecuador (Baltra; Galapagos)"},	  /* S_AMERICAN69_BALTRA_GALAPAGOSd */
/* 198 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-53,	3,	-47,	9,	5,	5,	0.0,	0.0,"Guyana"},	  /* S_AMERICAN69_GUYANAd */
/* 199 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-57,	1,	-41,	15,	6,	9,	0.0,	0.0,"MEAN FOR Argentina; Bolivia; Brazil; Chile; Colombia; Ecuador; Guyana; Paraguay; Peru; Trinidad & Tobago; Venezuela"},	  /* SOUTH_AMERICAN_1969d */
/* 200 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-61,	2,	-33,	15,	15,	15,	0.0,	0.0,"Paraguay"},	  /* S_AMERICAN69_PARAGUAYd */
/* 201 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-58,	0,	-44,	5,	5,	5,	0.0,	0.0,"Peru"},	  /* S_AMERICAN69_PERUd */
/* 202 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-45,	12,	-33,	25,	25,	25,	0.0,	0.0,"Trinidad & Tobago"},	  /* S_AMERICAN69_TINIDAT_TOBAGOd */
/* 203 */	{MOLODONSKIJ,	SOUTH_AMERICAN_1969e,	-45,	8,	-33,	3,	6,	3,	0.0,	0.0,"Venezuela"},	  /* S_AMERICAN69_VENEZUELAd */
/* 204 */	{MOLODONSKIJ,	MOD_FISCHER_1960e,	7,	-10,	-26,	25,	25,	25,	0.0,	0.0,"Singapore"},	  /* SOUTH_ASIAd */
/* 205 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-189,	-242,	-91,	-1,	-1,	-1,	0.0,	0.0,"Madagascar"},	  /* TANANARIVE_OBSERVATORY_1925d */
/* 206 */	{MOLODONSKIJ,	EVEREST_BRUNEIe,	-679,	669,	-48,	10,	10,	12,	0.0,	0.0,"Brunei; E. Malaysia (Sabah Sarawak)"},	  /* TIMBALAI_1948d */
/* 207 */	{MOLODONSKIJ,	BESSEL_1841e,	-148,	507,	685,	8,	5,	8,	0.0,	0.0,"Japan"},	  /* TOKYO_JAPANd */
/* 208 */	{MOLODONSKIJ,	BESSEL_1841e,	-148,	507,	685,	20,	5,	20,	0.0,	0.0,"MEAN FOR Japan; South Korea; Okinawa"},	  /* TOKYOd */
/* 209 */	{MOLODONSKIJ,	BESSEL_1841e,	-158,	507,	676,	20,	5,	20,	0.0,	0.0,"Okinawa"},	  /* TOKYO_OKINAWAd */
/* 210 */	{MOLODONSKIJ,	BESSEL_1841e,	-147,	506,	687,	2,	2,	2,	0.0,	0.0,"South Korea"},	  /* TOKYO_SOUTH_KEREAd */
/* 211 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-632,	438,	-609,	25,	25,	25,	0.0,	0.0,"Tristan da Cunha"},	  /* TRISTAN_ASTRO_1968d */
/* 212 */	{MOLODONSKIJ,	CLARKE_1880e,	51,	391,	-36,	25,	25,	25,	0.0,	0.0,"Fiji (Viti Levu Island)"},	  /* VITI_LEVU_1916d */
/* 213 */	{MOLODONSKIJ,	CLARKE_1880e,	-123,	-206,	219,	25,	25,	25,	0.0,	0.0,"Algeria"},	  /* VOIROL_1960d */
/* 214 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	276,	-57,	149,	25,	25,	25,	0.0,	0.0,"Wake Atoll"},	  /* WAKE_ISLAND_ASTRO_1952d */
/* 215 */	{MOLODONSKIJ,	HOUGH_1960e,	102,	52,	-38,	3,	3,	3,	0.0,	0.0,"Marshall Islands"},	  /* WAKE_ENIWETOK_1960d */
/* 216 */	{MOLODONSKIJ,	WGS72e,	0,	0,	0,	-1,	-1,	-1,	0.0,	0.0,"Global Definition"},	  /* WGS_1972_MOL_d */
/* 217 */	{MOLODONSKIJ,	WGS84e,	0,	0,	0,	-1,	-1,	-1,	0.0,	0.0,"Global Definition"},	  /* WGS_1984_MOL_d */
/* 218 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-155,	171,	37,	-1,	-1,	-1,	0.0,	0.0,"Uruguay"},	  /* YACAREd */
/* 219 */	{MOLODONSKIJ,	INTERNATIONAL_1924e,	-265,	120,	-358,	5,	5,	8,	0.0,	0.0,"Suriname"},	  /* ZANDERIJd */
/* 220 */	{MOLODONSKIJ,	CLARKE_1866e	,	0	,	0	,	0	,	0	,	0	,	0	,	0.0	,	0.0	,"Mozambique"},	  /* MOZAMBIQUEd */
/* 221 */	{MOLODONSKIJ,	BESSEL_1841e,	-304.046,	-60.576,	-103.64,	0,	0,	0,	0.0,	0.0,"DLx - Lisboa"},	  /* DLx - Portugal */
/* 222 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 223 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 224 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 225 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 226 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 227 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 228 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 229 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 230 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 231 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 232 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 233 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 234 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 235 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 236 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 237 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 238 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 239 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 240 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 241 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 242 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 243 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 244 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 245 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 246 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 247 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 248 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 249 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 250 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 251 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 252 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 253 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 254 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 255 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 256 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 257 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 258 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 259 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 260 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 261 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 262 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 263 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 264 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 265 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 266 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 267 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 268 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 269 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 270 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 271 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 272 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 273 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 274 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 275 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 276 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 277 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 278 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 279 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 280 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 281 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 282 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 283 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 284 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 285 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 286 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 287 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 288 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 289 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 290 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 291 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 292 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 293 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 294 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 295 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 296 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 297 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 298 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 299 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 300 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
			/*			dX		dY		dZ		rX		rY		rZ		Sc		Ellipsoide Hoehe,"Region of use"},	    */
/* 301 */	{BURSA_WOLF,	AUSTRALIAN_NATIONALe,	-116,	-50.47,	141.69,	-0.23/RHOS,	-0.39/RHOS,	-0.344/RHOS,	0.00000098,	0.0,"Australia"},	  /* AGD84_BWd */
/* 302 */	{BURSA_WOLF,	BESSEL_1841e,	565.04,	49.91,	465.84,	0.0000019848,	-0.0000017439,	0.0000090587,	0.0000040772,	0.0,"Netherlands"},	  /* AMERSFORD_BWd */
/* 303 */	{BURSA_WOLF,	INTERNATIONAL_1924e,	-185.836,	13.479,	-14.527,	0.441203/RHOS,	3.027399/RHOS,	-2.6077685/RHOS,	0.0,	0.0,"Luxembourg"},	  /* ED1950_LUXEMBOURGd */
/* 304 */	{BURSA_WOLF,	INTERNATIONAL_1924e,	-80.5,	-82.3,	-110.2,	-0.215/RHOS,	-0.028/RHOS,	0.358/RHOS,	-0.0000011,	0.0,"Europe"},	  /* EUROPEAN1950_BWd */
/* 305 */	{BURSA_WOLF,	INTERNATIONAL_1924e,	-169.5,	-79,	-12.9,	-0.6/RHOS,	1.5/RHOS,	-1.2/RHOS,	-0.0000028,	0.0,"Italy"},	  /* IGM1940_BWd */
/* 306 */	{BURSA_WOLF,	BESSEL_1841e,	419.3836,	99.3335,	591.3451,	-0.850389/RHOS,	-1.817277/RHOS,	7.862238/RHOS,	-0.0000099496,	0.0,"Sweden"},	  /* RT1990_BWd */
/* 307 */	{BURSA_WOLF,	BESSEL_1841e,	585.7,	87.0,	409.2,	-0.524/RHOS,	-0.155/RHOS,	2.822/RHOS,	0.00000878,	0.0,"Germany;Croatia"},	  /* POTSDAM_BWd */
/* 308 */	{BURSA_WOLF,	BESSEL_1841e,	586.15,	88.63,	468.23,	-5.1/RHOS,	-1.4/RHOS,	-5.4/RHOS,	0.0000011,	0.0,"Austria"},	  /* POTSDAM_AUSTRIAd */
/* 309 */	{BURSA_WOLF,	KRASSOVSKY_1940e,	24.5,	-122.7,	-94.0,	-0.025/RHOS,	0.254/RHOS,	0.126/RHOS,	0.00000108,	0.0,"East Germany; Hungary; Lithuania; Poland; CIS; Estonia; Bulgaria; Latvia;Romania;"},	  /* PULKOVO42_BWd */
/* 310 */	{BURSA_WOLF,	WGS84e,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,"Worldwide"},	  /* WGS84_BWd */
/* 311 */	{BURSA_WOLF,	GRS67e,	14.52,	-1.37,	-3.78,	-1.3/RHOS,	-1.04/RHOS,	2.05/RHOS,	-0.00000116,	0.0,"Hungary"},	  /* HD72_BWd */
/* 312 */	{BURSA_WOLF,	BESSEL_1841e,	563.88,	82.3,	463.41,	-4.85/RHOS,	-1.88/RHOS,	-4.46/RHOS,	0.000004,	0.0,"Austria"},	  /* AUSTRIA_AI_BWd */
/* 313 */	{BURSA_WOLF,	INTERNATIONAL_1924e,	-89.611,	-104.626,	-118.241,	-4.224/RHOS,	-0.248/RHOS,	0.852/RHOS,	0.0000011,	0.0,"Finland"},	  /* ED50 - Finland KKJ */
/* 314 */	{BURSA_WOLF,	KRASSOVSKY_1940e,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 315 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 316 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 317 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 318 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 319 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 320 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 321 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 322 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 323 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 324 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 325 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 326 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 327 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 328 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 329 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 330 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 331 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 332 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 333 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 334 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 335 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 336 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 337 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 338 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 339 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 340 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 341 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 342 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 343 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 344 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 345 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 346 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 347 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 348 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 349 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 350 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 351 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 352 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 353 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 354 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 355 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 356 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 357 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 358 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 359 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 360 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 361 */	{HELMERT,	INTERNATIONAL_1924e,	-113.758268943,	59.16560528050,	-98.3911345127,	-0.5150079386/RHOS,	0.1735134265/RHOS,	-1.7079754953/RHOS,	-0.0000012795,	0.0,"Belgium"},	  /* ED1950_BELGIUM_BWd */
/* 362 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 363 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 364 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 365 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 366 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 367 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 368 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 369 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 370 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 371 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 372 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 373 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 374 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 375 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 376 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 377 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 378 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 379 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 380 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 381 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 382 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 383 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 384 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 385 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 386 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 387 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 388 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 389 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 390 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 391 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 392 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 393 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 394 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 395 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 396 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 397 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 398 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 399 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
/* 400 */	{NONE_DTRANS,	NOELLIPSOIDe,	0,	0,	0,	0,	0,	0,	0.0,	0.0,""},	  /*  */
				/*		dX		dY		dZ		rX		rY		rZ		Sc		Ellipsoide Hoehe		Region of use		    */
/* 401 */	{TRANS_ROT,	BESSEL_1841e,	660.077,	13.551,	369.344,	2.484/Rad2GonSek,	1.783/Rad2GonSek,	2.939/Rad2GonSek,	0.00000566,	0.0,"Switzerland"},	  /* BERN_CH1903d */
//add by jjj 2013.7.24
//Proj4中OSGB的参数是:towgs84=446.448,-125.157,542.060,0.1502,0.2470,0.8421,-20.4894
//需要转换到LS定义的
/* 402 */	{HELMERT,	AIRY_1830e,		446.458307742,	-125.158136462,	542.070480944,	-0.150203077571/RHOS,	-0.247005060985/RHOS,	- 0.842117254477/RHOS,-0.0000204898198241,0.0,"OSGB1936"},	  /* OSGB1936d */
/*add by cx 2014.12.24*/
/*403*/{BURSA_WOLF,	CHINA2000e,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,"China2000"},	  /* China_2000 */

};
#define MAXDATUM (sizeof(DTrans) / sizeof(DATUMSTRANS))


/* Initialisierung der alten, nummerierten Koordinatensysteme */
static KOORDSTRUCT  KoordSys_List[] =
{		/* 	Datum		Proj		Methode		Zone	Shortname			Longname */
/* 0 */		{WGS84_BWd,	0,	GEOm,	0,"Geo  -WGS 84-","Geo  -WGS 84-"  },
/* 1 */		{POTSDAM_BWd,	TM_GK_DHDNp, 	TRANSMERK_Em,	3,"GK 3 -Potsdam-","Gauss-Kruger Zone 3  -Potsdam-"  },
/* 2 */		{POTSDAM_BWd,	TM_GK_DHDNp, 	TRANSMERK_Em,	2,"GK 2 -Potsdam-","Gauss-Kruger Zone 2  -Potsdam-"  },
/* 3 */		{POTSDAM_BWd,	TM_GK_DHDNp, 	TRANSMERK_Em,	4,"GK 4 -Potsdam-","Gauss-Kruger Zone 3  -Potsdam-"  },
/* 4 */		{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	32,"UTM 32 -ED 50-","UTM Zone 32  -ED 50-"  },
/* 5 */		{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	31,"UTM 31 -ED 50-","UTM Zone 31  -ED 50-"  },
/* 6 */		{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	33,"UTM 33 -ED 50-","UTM Zone 33  -ED 50-"  },
/* 7 */		{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	37,"UTM 37 -ED 50-","UTM Zone 37  -ED 50-"  },
/* 8 */		{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	18,"UTM 18 -ED 50-","UTM Zone 18  -ED 50-"  },
/* 9 */		{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	29,"UTM 29 -ED 50-","UTM Zone 29  -ED 50-"  },
/* 10 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	56,"UTM 56 -ED 50-","UTM Zone 56  -ED 50-"  },
/* 11 */	{POTSDAM_BWd,	TM_GK_DHDNp, 	TRANSMERK_Em,	10,"GK 10 -Potsdam-","Gauss-Kruger Zone 10  -Potsdam-"  },
/* 12 */	{POTSDAM_BWd,	TM_GK_DHDNp, 	TRANSMERK_Em,	7,"GK 7 -Potsdam-","Gauss-Kruger Zone 7  -Potsdam-"  },
/* 13 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	36,"UTM 36 -ED 50-","UTM Zone 36  -ED 50-"  },
/* 14 */	{POTSDAM_BWd,	TM_GK_DHDNp, 	TRANSMERK_Em,	12,"GK 12 -Potsdam-","Gauss-Kruger Zone 12  -Potsdam-"  },
/* 15 */	{POTSDAM_BWd,	TM_GK_DHDNp, 	TRANSMERK_Em,	5,"GK 5 -Potsdam-","Gauss-Kruger Zone 5  -Potsdam-"  },
/* 16 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	34,"UTM 34 -ED 50-","UTM Zone 34  -ED 50-"  },
/* 17 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	49,"UTM 49 -ED 50-","UTM Zone 49  -ED 50-"  },
/* 18 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	51,"UTM 51 -ED 50-","UTM Zone 51  -ED 50-"  },
/* 19 */	{PULKOVO42_BWd,	TM_GK_PULKp, 	TRANSMERK_Em,	3,"GK 3 -PULKOVO42-","Gauss-Kruger Zone 3  -PULKOVO42-"  },
/* 20 */	{PULKOVO42_BWd,	TM_GK_PULKp, 	TRANSMERK_Em,	4,"GK 4 -PULKOVO42-","Gauss-Kruger Zone 4  -PULKOVO42-"  },
/* 21 */	{IRELAND_1965d,	0, 	IREm,	0,"Ireland Grid","Ireland Grid"  },
/* 22 */	{AMERSFORD_BWd,	0, 	RDm,	0,"Rijksdriehoek","Rijksdriehoek"  },
/* 23 */	{PULKOVO42_BWd,	TM_GK_PULKp, 	TRANSMERK_Em,	19,"GK 19 -PULKOVO42-","Gauss-Kruger Zone 19  -PULKOVO42-"  },
/* 24 */	{PULKOVO42_BWd,	TM_GK_PULKp, 	TRANSMERK_Em,	20,"GK 20 -PULKOVO42-","Gauss-Kruger Zone 20  -PULKOVO42-"  },
/* 25 */	{PULKOVO42_BWd,	TM_GK_PULKp, 	TRANSMERK_Em,	6,"GK 6 -PULKOVO42-","Gauss-Kruger Zone 6  -PULKOVO42-"  },
/* 26 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	38,"UTM 38 -WGS 84-","UTM Zone 38  -WGS 84-"  },
/* 27 */	{EUROPEAN1950_BWd,	CL2_BELGIENp,	CONLAM2m,	0,"Belgium","Belgium Conform Lambert"  },
/* 28 */	{PULKOVO42_BWd,	TM_GK_PULKp, 	TRANSMERK_Em,	13,"GK 13 -PULKOVO42-","Gauss-Kruger Zone 13  -PULKOVO42-"  },
/* 29 */	{AGD84_BWd,	TM_AMGp, 	TRANSMERK_Em,	49,"AMG 49","Australian-Map_Grid Zone 49  -AGD 66-"  },
/* 30 */	{AGD84_BWd,	TM_AMGp, 	TRANSMERK_Em,	50,"AMG 50","Australian-Map_Grid Zone 50  -AGD 66-"  },
/* 31 */	{AGD84_BWd,	TM_AMGp, 	TRANSMERK_Em,	51,"AMG 51","Australian-Map_Grid Zone 51  -AGD 66-"  },
/* 32 */	{AGD84_BWd,	TM_AMGp, 	TRANSMERK_Em,	52,"AMG 52","Australian-Map_Grid Zone 52  -AGD 66-"  },
/* 33 */	{AGD84_BWd,	TM_AMGp, 	TRANSMERK_Em,	53,"AMG 53","Australian-Map_Grid Zone 53  -AGD 66-"  },
/* 34 */	{AGD84_BWd,	TM_AMGp, 	TRANSMERK_Em,	54,"AMG 54","Australian-Map_Grid Zone 54  -AGD 66-"  },
/* 35 */	{AGD84_BWd,	TM_AMGp, 	TRANSMERK_Em,	55,"AMG 55","Australian-Map_Grid Zone 55  -AGD 66-"  },
/* 36 */	{AGD84_BWd,	TM_AMGp, 	TRANSMERK_Em,	56,"AMG 56","Australian-Map_Grid Zone 56  -AGD 66-"  },
/* 37 */	{AGD84_BWd,	TM_AMGp, 	TRANSMERK_Em,	57,"AMG 57","Australian-Map_Grid Zone 57  -AGD 66-"  },
/* 38 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 39 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	49,"UTM 49 -WGS 84-","UTM Zone 49  -WGS 84-"  },
/* 40 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	50,"UTM 50 -WGS 84-","UTM Zone 50  -WGS 84-"  },
/* 41 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	51,"UTM 51 -WGS 84-","UTM Zone 51  -WGS 84-"  },
/* 42 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	52,"UTM 52 -WGS 84-","UTM Zone 52  -WGS 84-"  },
/* 43 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	53,"UTM 53 -WGS 84-","UTM Zone 53  -WGS 84-"  },
/* 44 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	54,"UTM 54 -WGS 84-","UTM Zone 54  -WGS 84-"  },
/* 45 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	55,"UTM 55 -WGS 84-","UTM Zone 55  -WGS 84-"  },
/* 46 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	56,"UTM 56 -WGS 84-","UTM Zone 56  -WGS 84-"  },
/* 47 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	57,"UTM 57 -WGS 84-","UTM Zone 57  -WGS 84-"  },
/* 48 */	{CAPEd,	TM_UTM_Sp,	TRANSMERK_Em,	36,"UTM 36 -Cape-","UTM Zone 36  -CAPE-"  },
/* 49 */	{MOZAMBIQUEd,	TM_UTM_Sp,	TRANSMERK_Em,	36,"UTM 36 -MOZAMBIQUE-","UTM Zone 36  -Clarke 1866-"  },
/* 50 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 51 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	31,"UTM 31 -WGS 84-","UTM Zone 31  -WGS 84-"  },
/* 52 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	32,"UTM 32 -WGS 84-","UTM Zone 32  -WGS 84-"  },
/* 53 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	33,"UTM 33 -WGS 84-","UTM Zone 33  -WGS 84-"  },
/* 54 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	34,"UTM 34 -WGS 84-","UTM Zone 34  -WGS 84-"  },
/* 55 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	35,"UTM 35 -WGS 84-","UTM Zone 35  -WGS 84-"  },
/* 56 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	36,"UTM 36 -WGS 84-","UTM Zone 36  -WGS 84-"  },
/* 57 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	37,"UTM 37 -WGS 84-","UTM Zone 37  -WGS 84-"  },
/* 58 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 59 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	39,"UTM 39 -WGS 84-","UTM Zone 39  -WGS 84-"  },
/* 60 */	{CAPEd,	AL_SAFp,	ALBERS_Em,	0,"South-Africa Albers","South Africa - Albers  -CAPE-"  },
/* 61 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	13,"Lo 13","Lo 13  -CAPE-"  },
/* 62 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	15,"Lo 15","Lo 15  -CAPE-"  },
/* 63 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	17,"Lo 17","Lo 17  -CAPE-"  },
/* 64 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	19,"Lo 19","Lo 19  -CAPE-"  },
/* 65 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	21,"Lo 21","Lo 21  -CAPE-"  },
/* 66 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	23,"Lo 23","Lo 23  -CAPE-"  },
/* 67 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	25,"Lo 25","Lo 25  -CAPE-"  },
/* 68 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	27,"Lo 27","Lo 27  -CAPE-"  },
/* 69 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	29,"Lo 29","Lo 29  -CAPE-"  },
/* 70 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	31,"Lo 31","Lo 31  -CAPE-"  },
/* 71 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	33,"Lo 33","Lo 33  -CAPE-"  },
/* 72 */	{CAPEd,	TM_RSAp, 	TRANSMERK_Em,	35,"Lo 35","Lo 35  -CAPE-"  },
/* 73 */	{POTSDAM_BWd,	TM_CROATIAp, 	TRANSMERK_Em,	5,"Croatia 15","Croatia L=15  -CROATIA-"  },
/* 74 */	{POTSDAM_BWd,	TM_CROATIA_CTp,	 TRANSMERK_Em,	1,"Central Croatia","Central-Croatia L=16.5  -CROATIA-"  },
/* 75 */	{POTSDAM_BWd,	TM_CROATIAp, 	TRANSMERK_Em,	6,"Croatia 18","Croatia L=18  -CROATIA-"  },
/* 76 */	{POTSDAM_BWd,	TM_CROATIAp, 	TRANSMERK_Em,	7,"Croatia 21","Croatia L=21  -CROATIA-"  },
/* 77 */	{ED50_EGYPTd,	TM_REDp, 	TRANSMERK_Em,	1,"Egypt Red Belt","Egypt: Red-Belt  -ED 50-"  },
/* 78 */	{ED50_EGYPTd,	TM_PURPLEp, 	TRANSMERK_Em,	1,"Egypt Purple Belt","Egypt: Purple-Belt  -ED 50-"  },
/* 79 */	{ED50_EGYPTd,	TM_EXT_PURPLEp,	 TRANSMERK_Em,	1,"Egypt Ext.Purple Belt","Egypt: Extended-Purple-Belt  -ED 50-"  },
/* 80 */	{WGS84_BWd,	CL2_TPC_H5Ap,	CONLAM2m,	0,"TCP H5A","TCP H5A -WGS 84-"  },
/* 81 */	{EUROPEAN1950_BWd,	CL2L15P27P63p,	CONLAM2m,	0,"1:4Mio - Lambert","Germany 1:4Mio - Lambert  -ED 50-"  },
/* 82 */	{EUROPEAN1950_BWd,	CL2L14_5P48_4P51_4p,	CONLAM2m,	0,"1:1Mio - Lambert","Germany 1:1Mio - Lambert  -ED 50-"  },
/* 83 */	{EUROPEAN1950_BWd,	CL2L10_5P49P56p,	CONLAM2m,	0,"1:500T - Lambert","Germany 1:500T - Lambert  -ED 50-"  },
/* 84 */	{BERN_CH1903d,	OBMERK_SWISSp,	OBMERK_SWISSm,	0,"Swiss National Grid","Swiss National Grid  -CH1903-"  },
/* 85 */	{RT1990_BWd,	TM_SWEDENp,	TRANSMERK_Em,	0,"Swedish National Grid","Swedish-National-Grid  -RT 90-"  },
/* 86 */	{RT1990_BWd,	AL_SWEDENp,	ALBERS_Em,	0,"Sweden - Albers","Sweden - Albers  -RT 90-"  },
/* 87 */	{POTSDAM_AUSTRIAd,	TM_AUSTRIAp,	TRANSMERK_Em,	0,"M 28","M 28  -AUSTRIA-"  },
/* 88 */	{POTSDAM_AUSTRIAd,	TM_AUSTRIAp,	TRANSMERK_Em,	1,"M 31","M 31  -AUSTRIA-"  },
/* 89 */	{POTSDAM_AUSTRIAd,	TM_AUSTRIAp,	TRANSMERK_Em,	2,"M 34","M 34  -AUSTRIA-"  },
/* 90 */	{POTSDAM_AUSTRIAd,	0,	AUSTRIAm,	0,"Bundesmeldenetz","Bundesmeldenetz  -AUSTRIA-"  },
/* 91 */	{POTSDAM_AUSTRIAd,	CL2L13_2P46P49p,	CONLAM2m,	0,"1:500T-Lambert","Austia 1:500T - Lambert  -AUSTRIA-"  },
/* 92 */	{ED1950_LUXEMBOURGd,	TM_GLUXp,	TRANSMERK_Em,	0,"Gauss Luxembourg","Gauss Luxembourg  -Luxembourg-"  },
/* 93 */	{EUROPEAN1950_BWd,	AL_2MIOAUSTRIAp,	ALBERS_Em,	0,"1:2Mio Austria","1:2Mio Austria  -ED 50-"  },
/* 94 */	{WGS84_BWd,	ALS_800TGERp,	ALBERS_Sm,	0,"1:800T Deutschland","1:800T Deutschland Sphere  -WGS 84-"  },
/* 95 */	{WGS84_BWd,	TMS_UTMp, 	TRANSMERK_Sm,	32,"UTM 32-N.Hemis Sphere","UTM Zone 32 Sphere - North. Hemisphere -WGS 84-"  },
/* 96 */	{IGM1940_BWd,	TM_GAUSSBOGA1p,	TRANSMERK_Em,	1,"Gauss-Boaga Zone 1","Gauss-Boaga Zone 1  -IGM 1940-"  },
/* 97 */	{IGM1940_BWd,	TM_GAUSSBOGA2p,	TRANSMERK_Em,	1,"Gauss-Boaga Zone 2","Gauss-Boaga Zone 2  -IGM 1940-"  },
/* 98 */	{NAD27_CAN_ONTARIOd,	TM_UTM_Np, 	TRANSMERK_Em,	17,"UTM 17  -NAD27 Ontario-","UTM Zone 17 - N. Hemisphere  -NAD27 Ontario-"  },
/* 99 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np, 	TRANSMERK_Em,	18,"UTM 18  -NAD27 Quebec-","UTM Zone 18 - N. Hemisphere  -NAD27 Quebec-"  },
/* 100 */	{NONEd,	0,	GEOm,	0,"Geo","Geo"  },
/* 101 */	{WGS84_BWd,	0,	GEOm,	0,"Long - Lat  -USER1-","Longitude - Latitude  -USER1-"  },
/* 102 */	{WGS84_BWd,	0,	GEOm,	0,"Long - Lat  -USER2-","Longitude - Latitude -USER2-"  },
/* 103 */	{WGS84_BWd,	0,	GEOm,	0,"Long - Lat  -WGS 84-","Longitude - Latitude -WGS 84-"  },
/* 104 */	{POTSDAM_BWd,	0,	GEOm,	0,"Long - Lat  -DHDN-","Longitude - Latitude -DHDN-"  },
/* 105 */	{EUROPEAN1950_BWd,	0,	GEOm,	0,"Long - Lat  -ED50-","Longitude - Latitude -ED50-"  },
/* 106 */	{PULKOVO42_BWd,	0,	GEOm,	0,"Long - Lat  -PULKOVO-","Longitude - Latitude -PULKOVO-"  },
/* 107 */	{AGD84_BWd,	0,	GEOm,	0,"Long - Lat  -AGD 66-","Longitude - Latitude -AGD 66-"  },
/* 108 */	{CAPEd,	0,	GEOm,	0,"Long - Lat  -CAPE-","Longitude - Latitude -CAPE-"  },
/* 109 */	{MOZAMBIQUEd,	0,	GEOm,	0,"Long - Lat  -Mozambique-","Longitude - Latitude -Mozambique-"  },
/* 110 */	{BERN_CH1903d,	0,	GEOm,	0,"Long - Lat  -CH 1903-","Longitude - Latitude -CH 1903-"  },
/* 111 */	{RT1990_BWd,	0,	GEOm,	0,"Long - Lat  -RT 90-","Longitude - Latitude -RT 90-"  },
/* 112 */	{POTSDAM_AUSTRIAd,	0,	GEOm,	0,"Long - Lat  -AUSTRIA-","Longitude - Latitude -AUSTRIA-"  },
/* 113 */	{ED1950_LUXEMBOURGd,	0,	GEOm,	0,"Long - Lat  -LUXEMBOURG-","Longitude - Latitude -LUXEMBOURG-"  },
/* 114 */	{AMERSFORD_BWd,	0,	GEOm,	0,"Long - Lat  -NETHERLANDS-","Longitude - Latitude -NETHERLANDS-"  },
/* 115 */	{POTSDAM_BWd,	0,	GEOm,	0,"Long - Lat  -CROATIA-","Longitude - Latitude -CROATIA-"  },
/* 116 */	{IGM1940_BWd,	0,	GEOm,	0,"Long - Lat  -IGM1940-","Longitude - Latitude -IGM1940-"  },
/* 117 */	{IRELAND_1965d,	0,	GEOm,	0,"Long - Lat  -Ireland-","Longitude - Latitude -Ireland 1965-"  },
/* 118 */	{ED50_EGYPTd,	0,	GEOm,	0,"Long - Lat  -Egypt-","Longitude - Latitude -ED50 Egypt-"  },
/* 119 */	{NAD27_CAN_ONTARIOd,	0,	GEOm,	0,"Long - Lat  -Ontario-","Longitude - Latitude -NAD27 Ontario-"  },
/* 120 */	{NAD27_CAN_QUEBECd,	0,	GEOm,	0,"Long - Lat  -Quebec-","Longitude - Latitude -NAD27 Quebec-"  },
/* 121 */	{AIN_EL_ABD_1970_BAHRAINd,	0,	GEOm,	0,"Long - Lat  -BAHRAIN-","Longitude - Latitude -BAHRAIN-"  },
/* 122 */	{BD72_7Pd,	0,	GEOm,	0,"Long - Lat  -Belgium Datum 72-","Longitude - Latitude -Belgium Datum 72-"  },
/* 123 */	{HD72_BWd,	0,	GEOm,	0,"Long - Lat -Hungarian Datum 72-","Longitude - Latitude -Hungarian Datum 72-"  },
/* 124 */	{KKJ_FINLAND_BWd,	0,	GEOm,	0,"Long - Lat -KKJ Finland-","Longitude - Latitude -KKJ Finland-"  },
/* 125 */	{DLXd,	0,	GEOm,	0,"Long - Lat -DLx-","Longitude - Latitude -DLx-"  },
/* 126 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 127 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 128 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 129 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 130 */	{ECS_BCS1954d,	TM_GK_PULKp,	TRANSMERK_Em,	13, "ECS_GK13 -BCS1954-","ECS_GK ZONE 13 -BCS1954-"  },
/* 131 */	{ECS_BCS1954d,	TM_GK_PULKp,	TRANSMERK_Em,	14, "ECS_GK14 -BCS1954-","ECS_GK ZONE 14 -BCS1954-"  },
/* 132 */	{ECS_BCS1954d,	TM_GK_PULKp,	TRANSMERK_Em,	15, "ECS_GK15 -BCS1954-","ECS_GK ZONE 15 -BCS1954-"  },
/* 133 */	{ECS_BCS1954d,	TM_GK_PULKp,	TRANSMERK_Em,	16, "ECS_GK16 -BCS1954-","ECS_GK ZONE 16 -BCS1954-"  },
/* 134 */	{ECS_BCS1954d,	TM_GK_PULKp,	TRANSMERK_Em,	17, "ECS_GK17 -BCS1954-","ECS_GK ZONE 17 -BCS1954-"  },
/* 135 */	{ECS_BCS1954d,	TM_GK_PULKp,	TRANSMERK_Em,	18, "ECS_GK18 -BCS1954-","ECS_GK ZONE 18 -BCS1954-"  },
/* 136 */	{ECS_BCS1954d,	TM_GK_PULKp,	TRANSMERK_Em,	19, "ECS_GK19 -BCS1954-","ECS_GK ZONE 19 -BCS1954-"  },
/* 137 */	{ECS_BCS1954d,	TM_GK_PULKp,	TRANSMERK_Em,	20, "ECS_GK20 -BCS1954-","ECS_GK ZONE 20 -BCS1954-"  },
/* 138 */	{ECS_BCS1954d,	TM_GK_PULKp,	TRANSMERK_Em,	21, "ECS_GK21 -BCS1954-","ECS_GK ZONE 21 -BCS1954-"  },
/* 139 */	{ECS_BCS1954d,	TM_GK_PULKp,	TRANSMERK_Em,	22, "ECS_GK22 -BCS1954-","ECS_GK ZONE 22 -BCS1954-"  },
/* 140 */	{ECS_BCS1954d,	TM_GK_PULKp,	TRANSMERK_Em,	23, "ECS_GK23 -BCS1954-","ECS_GK ZONE 23 -BCS1954-"  },
/* 141 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 142 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 143 */	{ECS_BCS1954d,	CL2_USER1p,     CONLAM2m,	0, "ECS_China_Lambert-1954","ECS_China_Lambert -BCS1954-"  },
/* 144 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 145 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 146 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 147 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 148 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 149 */	{AIN_EL_ABD_1970_BAHRAINd,	TM_UTM_Np, 	TRANSMERK_Em,	39,"UTM 39 -BAHRAIN-","UTM Zone 39  -AINELABD_BAHRAIN-"  },
/* 150 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 151 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 152 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 153 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 154 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 155 */	{BD72_7Pd,	0, 	BLAMBERT72_50m,	39,"Lambert 72/50 -BD72-","Belgium Lambert 72/50 -BD72-"  },
/* 156 */	{BD72_7Pd,	0, 	BLAMBERT72m,	39,"Lambert 72 -BD72-","Belgium Lambert 72 -BD72-"  },
/* 157 */	{HD72_BWd,	0, 	EOVm,	0,"EOV -HD72-","EOV Hungary -HD72-"  },
/* 158 */	{POTSDAM_AUSTRIAd,	CL2_AUSTRIAp,	CONLAM2m,	0,"Lambert -AUSTRIA_BESSEL-","Lambert  -AUSTRIA_BESSEL-"  },
/* 159 */	{WGS84_BWd,	TM_UTM_LATVIAp,TRANSMERK_Em,	0,"UTM Latvia -WGS 84-","UTM Latvia -WGS 84-"  },
/* 160 */	{DLXd,	TM_PORTUGALp,	TRANSMERK_Em,	0,"Portugal System -DLx-","Portuguese National System -DLx-"  },
/* 161 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 162 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 163 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 164 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 165 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 166 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 167 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 168 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 169 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 170 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 171 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 172 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 173 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 174 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 175 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 176 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 177 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 178 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 179 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 180 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 181 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 182 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 183 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 184 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 185 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 186 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 187 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 188 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 189 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 190 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 191 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 192 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 193 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 194 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 195 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 196 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 197 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 198 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 199 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 200 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 201 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	1,"UTM 1-N.Hemis  -WGS 84-","UTM Zone 1 - North.Hemis.  -WGS 84-"  },
/* 202 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	2,"UTM 2-N.Hemis  -WGS 84-","UTM Zone 2 - North.Hemis.  -WGS 84-"  },
/* 203 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	3,"UTM 3-N.Hemis  -WGS 84-","UTM Zone 3 - North.Hemis.  -WGS 84-"  },
/* 204 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	4,"UTM 4-N.Hemis  -WGS 84-","UTM Zone 4 - North.Hemis.  -WGS 84-"  },
/* 205 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	5,"UTM 5-N.Hemis  -WGS 84-","UTM Zone 5 - North.Hemis.  -WGS 84-"  },
/* 206 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	6,"UTM 6-N.Hemis  -WGS 84-","UTM Zone 6 - North.Hemis.  -WGS 84-"  },
/* 207 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	7,"UTM 7-N.Hemis  -WGS 84-","UTM Zone 7 - North.Hemis.  -WGS 84-"  },
/* 208 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	8,"UTM 8-N.Hemis  -WGS 84-","UTM Zone 8 - North.Hemis.  -WGS 84-"  },
/* 209 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	9,"UTM 9-N.Hemis  -WGS 84-","UTM Zone 9 - North.Hemis.  -WGS 84-"  },
/* 210 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	10,"UTM 10-N.Hemis  -WGS 84-","UTM Zone 10 - North.Hemis.  -WGS 84-"  },
/* 211 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	11,"UTM 11-N.Hemis  -WGS 84-","UTM Zone 11 - North.Hemis.  -WGS 84-"  },
/* 212 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	12,"UTM 12-N.Hemis  -WGS 84-","UTM Zone 12 - North.Hemis.  -WGS 84-"  },
/* 213 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	13,"UTM 13-N.Hemis  -WGS 84-","UTM Zone 13 - North.Hemis.  -WGS 84-"  },
/* 214 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	14,"UTM 14-N.Hemis  -WGS 84-","UTM Zone 14 - North.Hemis.  -WGS 84-"  },
/* 215 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	15,"UTM 15-N.Hemis  -WGS 84-","UTM Zone 15 - North.Hemis.  -WGS 84-"  },
/* 216 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	16,"UTM 16-N.Hemis  -WGS 84-","UTM Zone 16 - North.Hemis.  -WGS 84-"  },
/* 217 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	17,"UTM 17-N.Hemis  -WGS 84-","UTM Zone 17 - North.Hemis.  -WGS 84-"  },
/* 218 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	18,"UTM 18-N.Hemis  -WGS 84-","UTM Zone 18 - North.Hemis.  -WGS 84-"  },
/* 219 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	19,"UTM 19-N.Hemis  -WGS 84-","UTM Zone 19 - North.Hemis.  -WGS 84-"  },
/* 220 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	20,"UTM 20-N.Hemis  -WGS 84-","UTM Zone 20 - North.Hemis.  -WGS 84-"  },
/* 221 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	21,"UTM 21-N.Hemis  -WGS 84-","UTM Zone 21 - North.Hemis.  -WGS 84-"  },
/* 222 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	22,"UTM 22-N.Hemis  -WGS 84-","UTM Zone 22 - North.Hemis.  -WGS 84-"  },
/* 223 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	23,"UTM 23-N.Hemis  -WGS 84-","UTM Zone 23 - North.Hemis.  -WGS 84-"  },
/* 224 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	24,"UTM 24-N.Hemis  -WGS 84-","UTM Zone 24 - North.Hemis.  -WGS 84-"  },
/* 225 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	25,"UTM 25-N.Hemis  -WGS 84-","UTM Zone 25 - North.Hemis.  -WGS 84-"  },
/* 226 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	26,"UTM 26-N.Hemis  -WGS 84-","UTM Zone 26 - North.Hemis.  -WGS 84-"  },
/* 227 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	27,"UTM 27-N.Hemis  -WGS 84-","UTM Zone 27 - North.Hemis.  -WGS 84-"  },
/* 228 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	28,"UTM 28-N.Hemis  -WGS 84-","UTM Zone 28 - North.Hemis.  -WGS 84-"  },
/* 229 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	29,"UTM 29-N.Hemis  -WGS 84-","UTM Zone 29 - North.Hemis.  -WGS 84-"  },
/* 230 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	30,"UTM 30-N.Hemis  -WGS 84-","UTM Zone 30 - North.Hemis.  -WGS 84-"  },
/* 231 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	31,"UTM 31-N.Hemis  -WGS 84-","UTM Zone 31 - North.Hemis.  -WGS 84-"  },
/* 232 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	32,"UTM 32-N.Hemis  -WGS 84-","UTM Zone 32 - North.Hemis.  -WGS 84-"  },
/* 233 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	33,"UTM 33-N.Hemis  -WGS 84-","UTM Zone 33 - North.Hemis.  -WGS 84-"  },
/* 234 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	34,"UTM 34-N.Hemis  -WGS 84-","UTM Zone 34 - North.Hemis.  -WGS 84-"  },
/* 235 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	35,"UTM 35-N.Hemis  -WGS 84-","UTM Zone 35 - North.Hemis.  -WGS 84-"  },
/* 236 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	36,"UTM 36-N.Hemis  -WGS 84-","UTM Zone 36 - North.Hemis.  -WGS 84-"  },
/* 237 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	37,"UTM 37-N.Hemis  -WGS 84-","UTM Zone 37 - North.Hemis.  -WGS 84-"  },
/* 238 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	38,"UTM 38-N.Hemis  -WGS 84-","UTM Zone 38 - North.Hemis.  -WGS 84-"  },
/* 239 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	39,"UTM 39-N.Hemis  -WGS 84-","UTM Zone 39 - North.Hemis.  -WGS 84-"  },
/* 240 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	40,"UTM 40-N.Hemis  -WGS 84-","UTM Zone 40 - North.Hemis.  -WGS 84-"  },
/* 241 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	41,"UTM 41-N.Hemis  -WGS 84-","UTM Zone 41 - North.Hemis.  -WGS 84-"  },
/* 242 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	42,"UTM 42-N.Hemis  -WGS 84-","UTM Zone 42 - North.Hemis.  -WGS 84-"  },
/* 243 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	43,"UTM 43-N.Hemis  -WGS 84-","UTM Zone 43 - North.Hemis.  -WGS 84-"  },
/* 244 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	44,"UTM 44-N.Hemis  -WGS 84-","UTM Zone 44 - North.Hemis.  -WGS 84-"  },
/* 245 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	45,"UTM 45-N.Hemis  -WGS 84-","UTM Zone 45 - North.Hemis.  -WGS 84-"  },
/* 246 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	46,"UTM 46-N.Hemis  -WGS 84-","UTM Zone 46 - North.Hemis.  -WGS 84-"  },
/* 247 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	47,"UTM 47-N.Hemis  -WGS 84-","UTM Zone 47 - North.Hemis.  -WGS 84-"  },
/* 248 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	48,"UTM 48-N.Hemis  -WGS 84-","UTM Zone 48 - North.Hemis.  -WGS 84-"  },
/* 249 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	49,"UTM 49-N.Hemis  -WGS 84-","UTM Zone 49 - North.Hemis.  -WGS 84-"  },
/* 250 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	50,"UTM 50-N.Hemis  -WGS 84-","UTM Zone 50 - North.Hemis.  -WGS 84-"  },
/* 251 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	51,"UTM 51-N.Hemis  -WGS 84-","UTM Zone 51 - North.Hemis.  -WGS 84-"  },
/* 252 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	52,"UTM 52-N.Hemis  -WGS 84-","UTM Zone 52 - North.Hemis.  -WGS 84-"  },
/* 253 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	53,"UTM 53-N.Hemis  -WGS 84-","UTM Zone 53 - North.Hemis.  -WGS 84-"  },
/* 254 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	54,"UTM 54-N.Hemis  -WGS 84-","UTM Zone 54 - North.Hemis.  -WGS 84-"  },
/* 255 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	55,"UTM 55-N.Hemis  -WGS 84-","UTM Zone 55 - North.Hemis.  -WGS 84-"  },
/* 256 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	56,"UTM 56-N.Hemis  -WGS 84-","UTM Zone 56 - North.Hemis.  -WGS 84-"  },
/* 257 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	57,"UTM 57-N.Hemis  -WGS 84-","UTM Zone 57 - North.Hemis.  -WGS 84-"  },
/* 258 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	58,"UTM 58-N.Hemis  -WGS 84-","UTM Zone 58 - North.Hemis.  -WGS 84-"  },
/* 259 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	59,"UTM 59-N.Hemis  -WGS 84-","UTM Zone 59 - North.Hemis.  -WGS 84-"  },
/* 260 */	{WGS84_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	60,"UTM 60-N.Hemis  -WGS 84-","UTM Zone 60 - North.Hemis.  -WGS 84-"  },
/* Suedliche Hemisphere */
/* 261 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	1,"UTM 1-S.Hemis  -WGS 84-","UTM Zone 1 - South.Hemis.  -WGS 84-"  },
/* 262 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	2,"UTM 2-S.Hemis  -WGS 84-","UTM Zone 2 - South.Hemis.  -WGS 84-"  },
/* 263 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	3,"UTM 3-S.Hemis  -WGS 84-","UTM Zone 3 - South.Hemis.  -WGS 84-"  },
/* 264 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	4,"UTM 4-S.Hemis  -WGS 84-","UTM Zone 4 - South.Hemis.  -WGS 84-"  },
/* 265 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	5,"UTM 5-S.Hemis  -WGS 84-","UTM Zone 5 - South.Hemis.  -WGS 84-"  },
/* 266 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	6,"UTM 6-S.Hemis  -WGS 84-","UTM Zone 6 - South.Hemis.  -WGS 84-"  },
/* 267 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	7,"UTM 7-S.Hemis  -WGS 84-","UTM Zone 7 - South.Hemis.  -WGS 84-"  },
/* 268 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	8,"UTM 8-S.Hemis  -WGS 84-","UTM Zone 8 - South.Hemis.  -WGS 84-"  },
/* 269 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	9,"UTM 9-S.Hemis  -WGS 84-","UTM Zone 9 - South.Hemis.  -WGS 84-"  },
/* 270 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	10,"UTM 10-S.Hemis  -WGS 84-","UTM Zone 10 - South.Hemis.  -WGS 84-"  },
/* 271 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	11,"UTM 11-S.Hemis  -WGS 84-","UTM Zone 11 - South.Hemis.  -WGS 84-"  },
/* 272 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	12,"UTM 12-S.Hemis  -WGS 84-","UTM Zone 12 - South.Hemis.  -WGS 84-"  },
/* 273 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	13,"UTM 13-S.Hemis  -WGS 84-","UTM Zone 13 - South.Hemis.  -WGS 84-"  },
/* 274 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	14,"UTM 14-S.Hemis  -WGS 84-","UTM Zone 14 - South.Hemis.  -WGS 84-"  },
/* 275 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	15,"UTM 15-S.Hemis  -WGS 84-","UTM Zone 15 - South.Hemis.  -WGS 84-"  },
/* 276 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	16,"UTM 16-S.Hemis  -WGS 84-","UTM Zone 16 - South.Hemis.  -WGS 84-"  },
/* 277 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	17,"UTM 17-S.Hemis  -WGS 84-","UTM Zone 17 - South.Hemis.  -WGS 84-"  },
/* 278 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	18,"UTM 18-S.Hemis  -WGS 84-","UTM Zone 18 - South.Hemis.  -WGS 84-"  },
/* 279 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	19,"UTM 19-S.Hemis  -WGS 84-","UTM Zone 19 - South.Hemis.  -WGS 84-"  },
/* 280 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	20,"UTM 20-S.Hemis  -WGS 84-","UTM Zone 20 - South.Hemis.  -WGS 84-"  },
/* 281 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	21,"UTM 21-S.Hemis  -WGS 84-","UTM Zone 21 - South.Hemis.  -WGS 84-"  },
/* 282 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	22,"UTM 22-S.Hemis  -WGS 84-","UTM Zone 22 - South.Hemis.  -WGS 84-"  },
/* 283 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	23,"UTM 23-S.Hemis  -WGS 84-","UTM Zone 23 - South.Hemis.  -WGS 84-"  },
/* 284 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	24,"UTM 24-S.Hemis  -WGS 84-","UTM Zone 24 - South.Hemis.  -WGS 84-"  },
/* 285 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	25,"UTM 25-S.Hemis  -WGS 84-","UTM Zone 25 - South.Hemis.  -WGS 84-"  },
/* 286 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	26,"UTM 26-S.Hemis  -WGS 84-","UTM Zone 26 - South.Hemis.  -WGS 84-"  },
/* 287 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	27,"UTM 27-S.Hemis  -WGS 84-","UTM Zone 27 - South.Hemis.  -WGS 84-"  },
/* 288 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	28,"UTM 28-S.Hemis  -WGS 84-","UTM Zone 28 - South.Hemis.  -WGS 84-"  },
/* 289 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	29,"UTM 29-S.Hemis  -WGS 84-","UTM Zone 29 - South.Hemis.  -WGS 84-"  },
/* 290 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	30,"UTM 30-S.Hemis  -WGS 84-","UTM Zone 30 - South.Hemis.  -WGS 84-"  },
/* 291 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	31,"UTM 31-S.Hemis  -WGS 84-","UTM Zone 31 - South.Hemis.  -WGS 84-"  },
/* 292 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	32,"UTM 32-S.Hemis  -WGS 84-","UTM Zone 32 - South.Hemis.  -WGS 84-"  },
/* 293 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	33,"UTM 33-S.Hemis  -WGS 84-","UTM Zone 33 - South.Hemis.  -WGS 84-"  },
/* 294 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	34,"UTM 34-S.Hemis  -WGS 84-","UTM Zone 34 - South.Hemis.  -WGS 84-"  },
/* 295 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	35,"UTM 35-S.Hemis  -WGS 84-","UTM Zone 35 - South.Hemis.  -WGS 84-"  },
/* 296 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	36,"UTM 36-S.Hemis  -WGS 84-","UTM Zone 36 - South.Hemis.  -WGS 84-"  },
/* 297 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	37,"UTM 37-S.Hemis  -WGS 84-","UTM Zone 37 - South.Hemis.  -WGS 84-"  },
/* 298 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	38,"UTM 38-S.Hemis  -WGS 84-","UTM Zone 38 - South.Hemis.  -WGS 84-"  },
/* 299 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	39,"UTM 39-S.Hemis  -WGS 84-","UTM Zone 39 - South.Hemis.  -WGS 84-"  },
/* 300 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	40,"UTM 40-S.Hemis  -WGS 84-","UTM Zone 40 - South.Hemis.  -WGS 84-"  },
/* 301 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	41,"UTM 41-S.Hemis  -WGS 84-","UTM Zone 41 - South.Hemis.  -WGS 84-"  },
/* 302 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	42,"UTM 42-S.Hemis  -WGS 84-","UTM Zone 42 - South.Hemis.  -WGS 84-"  },
/* 303 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	43,"UTM 43-S.Hemis  -WGS 84-","UTM Zone 43 - South.Hemis.  -WGS 84-"  },
/* 304 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	44,"UTM 44-S.Hemis  -WGS 84-","UTM Zone 44 - South.Hemis.  -WGS 84-"  },
/* 305 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	45,"UTM 45-S.Hemis  -WGS 84-","UTM Zone 45 - South.Hemis.  -WGS 84-"  },
/* 306 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	46,"UTM 46-S.Hemis  -WGS 84-","UTM Zone 46 - South.Hemis.  -WGS 84-"  },
/* 307 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	47,"UTM 47-S.Hemis  -WGS 84-","UTM Zone 47 - South.Hemis.  -WGS 84-"  },
/* 308 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	48,"UTM 48-S.Hemis  -WGS 84-","UTM Zone 48 - South.Hemis.  -WGS 84-"  },
/* 309 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	49,"UTM 49-S.Hemis  -WGS 84-","UTM Zone 49 - South.Hemis.  -WGS 84-"  },
/* 310 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	50,"UTM 50-S.Hemis  -WGS 84-","UTM Zone 50 - South.Hemis.  -WGS 84-"  },
/* 311 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	51,"UTM 51-S.Hemis  -WGS 84-","UTM Zone 51 - South.Hemis.  -WGS 84-"  },
/* 312 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	52,"UTM 52-S.Hemis  -WGS 84-","UTM Zone 52 - South.Hemis.  -WGS 84-"  },
/* 313 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	53,"UTM 53-S.Hemis  -WGS 84-","UTM Zone 53 - South.Hemis.  -WGS 84-"  },
/* 314 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	54,"UTM 54-S.Hemis  -WGS 84-","UTM Zone 54 - South.Hemis.  -WGS 84-"  },
/* 315 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	55,"UTM 55-S.Hemis  -WGS 84-","UTM Zone 55 - South.Hemis.  -WGS 84-"  },
/* 316 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	56,"UTM 56-S.Hemis  -WGS 84-","UTM Zone 56 - South.Hemis.  -WGS 84-"  },
/* 317 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	57,"UTM 57-S.Hemis  -WGS 84-","UTM Zone 57 - South.Hemis.  -WGS 84-"  },
/* 318 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	58,"UTM 58-S.Hemis  -WGS 84-","UTM Zone 58 - South.Hemis.  -WGS 84-"  },
/* 319 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	59,"UTM 59-S.Hemis  -WGS 84-","UTM Zone 59 - South.Hemis.  -WGS 84-"  },
/* 320 */	{WGS84_BWd,	TM_UTM_Sp, 	TRANSMERK_Em,	60,"UTM 60-S.Hemis  -WGS 84-","UTM Zone 60 - South.Hemis.  -WGS 84-"  },
/* 321 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 322 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 323 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 324 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 325 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 326 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 327 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 328 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	28,"UTM 28-N.Hemis  -ED 50-","UTM Zone 28 - North.Hemis.  -ED 50-"  },
/* 329 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	29,"UTM 29-N.Hemis  -ED 50-","UTM Zone 29 - North.Hemis.  -ED 50-"  },
/* 330 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	30,"UTM 30-N.Hemis  -ED 50-","UTM Zone 30 - North.Hemis.  -ED 50-"  },
/* 331 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	31,"UTM 31-N.Hemis  -ED 50-","UTM Zone 31 - North.Hemis.  -ED 50-"  },
/* 332 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	32,"UTM 32-N.Hemis  -ED 50-","UTM Zone 32 - North.Hemis.  -ED 50-"  },
/* 333 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	33,"UTM 33-N.Hemis  -ED 50-","UTM Zone 33 - North.Hemis.  -ED 50-"  },
/* 334 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	34,"UTM 34-N.Hemis  -ED 50-","UTM Zone 34 - North.Hemis.  -ED 50-"  },
/* 335 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	35,"UTM 35-N.Hemis  -ED 50-","UTM Zone 35 - North.Hemis.  -ED 50-"  },
/* 336 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	36,"UTM 36-N.Hemis  -ED 50-","UTM Zone 36 - North.Hemis.  -ED 50-"  },
/* 337 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	37,"UTM 37-N.Hemis  -ED 50-","UTM Zone 37 - North.Hemis.  -ED 50-"  },
/* 338 */	{EUROPEAN1950_BWd,	TM_UTM_Np, 	TRANSMERK_Em,	38,"UTM 38-N.Hemis  -ED 50-","UTM Zone 38 - North.Hemis.  -ED 50-"  },
/* 339 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 340 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* KKJ Finland */
/* 341 */	{KKJ_FINLAND_BWd,	TM_KKJp,	TRANSMERK_Em ,	1,"KKJ Zone 1","KKJ ZONE 1 -ED 50-"  },
/* 342 */	{KKJ_FINLAND_BWd,	TM_KKJp,	TRANSMERK_Em ,	2,"KKJ Zone 2","KKJ ZONE 2 -ED 50-"  },
/* 343 */	{KKJ_FINLAND_BWd,	TM_KKJp,	TRANSMERK_Em ,	3,"KKJ Zone 3","KKJ ZONE 3 -ED 50-"  },
/* 344 */	{KKJ_FINLAND_BWd,	TM_KKJp,	TRANSMERK_Em ,	4,"KKJ Zone 4","KKJ ZONE 4 -ED 50-"  },
/* 345 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 346 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 347 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 348 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 349 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 350 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 351 */	{POTSDAM_BWd,	TM_GK_DHDNp,	TRANSMERK_Em,	1,"GK 1 -DHDN-","Gauss-Kruger Zone 1  -DHDN-"  },
/* 352 */	{POTSDAM_BWd,	TM_GK_DHDNp,	TRANSMERK_Em,	2,"GK 2 -DHDN-","Gauss-Kruger Zone 2  -DHDN-"  },
/* 353 */	{POTSDAM_BWd,	TM_GK_DHDNp,	TRANSMERK_Em,	3,"GK 3 -DHDN-","Gauss-Kruger Zone 3  -DHDN-"  },
/* 354 */	{POTSDAM_BWd,	TM_GK_DHDNp,	TRANSMERK_Em,	4,"GK 4 -DHDN-","Gauss-Kruger Zone 4  -DHDN-"  },
/* 355 */	{POTSDAM_BWd,	TM_GK_DHDNp,	TRANSMERK_Em,	5,"GK 5 -DHDN-","Gauss-Kruger Zone 5  -DHDN-"  },
/* 356 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 357 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 358 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 359 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 360 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 361 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	1,"GK 1 -PULKOVO-","Gauss-Kruger Zone 1  -PULKOVO-"  },
/* 362 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	2,"GK 2 -PULKOVO-","Gauss-Kruger Zone 2  -PULKOVO-"  },
/* 363 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	3,"GK 3 -PULKOVO-","Gauss-Kruger Zone 3  -PULKOVO-"  },
/* 364 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	4,"GK 4 -PULKOVO-","Gauss-Kruger Zone 4  -PULKOVO-"  },
/* 365 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	5,"GK 5 -PULKOVO-","Gauss-Kruger Zone 5  -PULKOVO-"  },
/* 366 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	6,"GK 6 -PULKOVO-","Gauss-Kruger Zone 6  -PULKOVO-"  },
/* 367 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	7,"GK 7 -PULKOVO-","Gauss-Kruger Zone 7  -PULKOVO-"  },
/* 368 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	8,"GK 8 -PULKOVO-","Gauss-Kruger Zone 8  -PULKOVO-"  },
/* 369 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	9,"GK 9 -PULKOVO-","Gauss-Kruger Zone 9  -PULKOVO-"  },
/* 370 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	10,"GK 10 -PULKOVO-","Gauss-Kruger Zone 10  -PULKOVO-"  },
/* 371 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	11,"GK 11 -PULKOVO-","Gauss-Kruger Zone 11  -PULKOVO-"  },
/* 372 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	12,"GK 12 -PULKOVO-","Gauss-Kruger Zone 12  -PULKOVO-"  },
/* 373 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	13,"GK 13 -PULKOVO-","Gauss-Kruger Zone 13  -PULKOVO-"  },
/* 374 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	14,"GK 14 -PULKOVO-","Gauss-Kruger Zone 14  -PULKOVO-"  },
/* 375 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	15,"GK 15 -PULKOVO-","Gauss-Kruger Zone 15  -PULKOVO-"  },
/* 376 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	16,"GK 16 -PULKOVO-","Gauss-Kruger Zone 16  -PULKOVO-"  },
/* 377 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	17,"GK 17 -PULKOVO-","Gauss-Kruger Zone 17  -PULKOVO-"  },
/* 378 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	18,"GK 18 -PULKOVO-","Gauss-Kruger Zone 18  -PULKOVO-"  },
/* 379 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	19,"GK 19 -PULKOVO-","Gauss-Kruger Zone 19  -PULKOVO-"  },
/* 380 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	20,"GK 20 -PULKOVO-","Gauss-Kruger Zone 20  -PULKOVO-"  },
/* 381 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	21,"GK 21 -PULKOVO-","Gauss-Kruger Zone 21  -PULKOVO-"  },
/* 382 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	22,"GK 22 -PULKOVO-","Gauss-Kruger Zone 22  -PULKOVO-"  },
/* 383 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	23,"GK 23 -PULKOVO-","Gauss-Kruger Zone 23  -PULKOVO-"  },
/* 384 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	24,"GK 24 -PULKOVO-","Gauss-Kruger Zone 24  -PULKOVO-"  },
/* 385 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	25,"GK 25 -PULKOVO-","Gauss-Kruger Zone 25  -PULKOVO-"  },
/* 386 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	26,"GK 26 -PULKOVO-","Gauss-Kruger Zone 26  -PULKOVO-"  },
/* 387 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	27,"GK 27 -PULKOVO-","Gauss-Kruger Zone 27  -PULKOVO-"  },
/* 388 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	28,"GK 28 -PULKOVO-","Gauss-Kruger Zone 28  -PULKOVO-"  },
/* 389 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	29,"GK 29 -PULKOVO-","Gauss-Kruger Zone 29  -PULKOVO-"  },
/* 390 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	30,"GK 30 -PULKOVO-","Gauss-Kruger Zone 30  -PULKOVO-"  },
/* 391 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	31,"GK 31 -PULKOVO-","Gauss-Kruger Zone 31  -PULKOVO-"  },
/* 392 */	{PULKOVO42_BWd,	TM_GK_PULKp,	TRANSMERK_Em,	32,"GK 32 -PULKOVO-","Gauss-Kruger Zone 32  -PULKOVO-"  },
/* 393 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 394 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 395 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 396 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 397 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 398 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 399 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 400 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 401 */	{NAD27_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	1,	"UTM 1-N.Hemis  -NAD27_ALASKA-",	"UTM Zone 1 - North.Hemis.  -NAD27_ALASKA-"	},
/* 402 */	{NAD27_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	2,	"UTM 2-N.Hemis  -NAD27_ALASKA-",	"UTM Zone 2 - North.Hemis.  -NAD27_ALASKA-"	},
/* 403 */	{NAD27_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	3,	"UTM 3-N.Hemis  -NAD27_ALASKA-",	"UTM Zone 3 - North.Hemis.  -NAD27_ALASKA-"	},
/* 404 */	{NAD27_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	4,	"UTM 4-N.Hemis  -NAD27_ALASKA-",	"UTM Zone 4 - North.Hemis.  -NAD27_ALASKA-"	},
/* 405 */	{NAD27_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	5,	"UTM 5-N.Hemis  -NAD27_ALASKA-",	"UTM Zone 5 - North.Hemis.  -NAD27_ALASKA-"	},
/* 406 */	{NAD27_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	6,	"UTM 6-N.Hemis  -NAD27_ALASKA-",	"UTM Zone 6 - North.Hemis.  -NAD27_ALASKA-"	},
/* 407 */	{NAD27_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	7,	"UTM 7-N.Hemis  -NAD27_ALASKA-",	"UTM Zone 7 - North.Hemis.  -NAD27_ALASKA-"	},
/* 408 */	{NAD27_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	8,	"UTM 8-N.Hemis  -NAD27_ALASKA-",	"UTM Zone 8 - North.Hemis.  -NAD27_ALASKA-"	},
/* 409 */	{NAD27_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	9,	"UTM 9-N.Hemis  -NAD27_ALASKA-",	"UTM Zone 9 - North.Hemis.  -NAD27_ALASKA-"	},
/* 410 */	{NAD27_CONUSd,	TM_UTM_Np,	TRANSMERK_Em,	10,	"UTM 10-N.Hemis  -NAD27_CONUS-",	"UTM Zone 10 - North.Hemis.  -NAD27_CONUS-"	},
/* 411 */	{NAD27_CONUSd,	TM_UTM_Np,	TRANSMERK_Em,	11,	"UTM 11-N.Hemis  -NAD27_CONUS-",	"UTM Zone 11 - North.Hemis.  -NAD27_CONUS-"	},
/* 412 */	{NAD27_CONUSd,	TM_UTM_Np,	TRANSMERK_Em,	12,	"UTM 12-N.Hemis  -NAD27_CONUS-",	"UTM Zone 12 - North.Hemis.  -NAD27_CONUS-"	},
/* 413 */	{NAD27_CONUSd,	TM_UTM_Np,	TRANSMERK_Em,	13,	"UTM 13-N.Hemis  -NAD27_CONUS-",	"UTM Zone 13 - North.Hemis.  -NAD27_CONUS-"	},
/* 414 */	{NAD27_CONUSd,	TM_UTM_Np,	TRANSMERK_Em,	14,	"UTM 14-N.Hemis  -NAD27_CONUS-",	"UTM Zone 14 - North.Hemis.  -NAD27_CONUS-"	},
/* 415 */	{NAD27_CONUSd,	TM_UTM_Np,	TRANSMERK_Em,	15,	"UTM 15-N.Hemis  -NAD27_CONUS-",	"UTM Zone 15 - North.Hemis.  -NAD27_CONUS-"	},
/* 416 */	{NAD27_CONUSd,	TM_UTM_Np,	TRANSMERK_Em,	16,	"UTM 16-N.Hemis  -NAD27_CONUS-",	"UTM Zone 16 - North.Hemis.  -NAD27_CONUS-"	},
/* 417 */	{NAD27_CONUSd,	TM_UTM_Np,	TRANSMERK_Em,	17,	"UTM 17-N.Hemis  -NAD27_CONUS-",	"UTM Zone 17 - North.Hemis.  -NAD27_CONUS-"	},
/* 418 */	{NAD27_CONUSd,	TM_UTM_Np,	TRANSMERK_Em,	18,	"UTM 18-N.Hemis  -NAD27_CONUS-",	"UTM Zone 18 - North.Hemis.  -NAD27_CONUS-"	},
/* 419 */	{NAD27_CONUSd,	TM_UTM_Np,	TRANSMERK_Em,	19,	"UTM 19-N.Hemis  -NAD27_CONUS-",	"UTM Zone 19 - North.Hemis.  -NAD27_CONUS-"	},
/* 420 */	{NAD27_MEXICOd,	TM_UTM_Np,	TRANSMERK_Em,	10,	"UTM 10-N.Hemis  -NAD27_MEXICO-",	"UTM Zone 10 - North.Hemis.  -NAD27_MEXICO-"	},
/* 421 */	{NAD27_MEXICOd,	TM_UTM_Np,	TRANSMERK_Em,	11,	"UTM 11-N.Hemis  -NAD27_MEXICO-",	"UTM Zone 11 - North.Hemis.  -NAD27_MEXICO-"	},
/* 422 */	{NAD27_MEXICOd,	TM_UTM_Np,	TRANSMERK_Em,	12,	"UTM 12-N.Hemis  -NAD27_MEXICO-",	"UTM Zone 12 - North.Hemis.  -NAD27_MEXICO-"	},
/* 423 */	{NAD27_MEXICOd,	TM_UTM_Np,	TRANSMERK_Em,	13,	"UTM 13-N.Hemis  -NAD27_MEXICO-",	"UTM Zone 13 - North.Hemis.  -NAD27_MEXICO-"	},
/* 424 */	{NAD27_MEXICOd,	TM_UTM_Np,	TRANSMERK_Em,	14,	"UTM 14-N.Hemis  -NAD27_MEXICO-",	"UTM Zone 14 - North.Hemis.  -NAD27_MEXICO-"	},
/* 425 */	{NAD27_MEXICOd,	TM_UTM_Np,	TRANSMERK_Em,	15,	"UTM 15-N.Hemis  -NAD27_MEXICO-",	"UTM Zone 15 - North.Hemis.  -NAD27_MEXICO-"	},
/* 426 */	{NAD27_MEXICOd,	TM_UTM_Np,	TRANSMERK_Em,	16,	"UTM 16-N.Hemis  -NAD27_MEXICO-",	"UTM Zone 16 - North.Hemis.  -NAD27_MEXICO-"	},
/* 427 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 428 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 429 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 430 */	{NONEd,	0,	0,	0,"Undefined",""  },	//add by jjj 少了一个 2011.12.13
/* 431 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 432 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 433 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 434 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 435 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 436 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 437 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	7,	"UTM 7-N.Hemis  -NAD27_CANADA-",	"UTM Zone 7 - North.Hemis.  -NAD27_CANADA-"	},
/* 438 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	8,	"UTM 8-N.Hemis  -NAD27_CANADA-",	"UTM Zone 8 - North.Hemis.  -NAD27_CANADA-"	},
/* 439 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	9,	"UTM 9-N.Hemis  -NAD27_CANADA-",	"UTM Zone 9 - North.Hemis.  -NAD27_CANADA-"	},
/* 440 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	10,	"UTM 10-N.Hemis  -NAD27_CANADA-",	"UTM Zone 10 - North.Hemis.  -NAD27_CANADA-"	},
/* 441 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	11,	"UTM 11-N.Hemis  -NAD27_CANADA-",	"UTM Zone 11 - North.Hemis.  -NAD27_CANADA-"	},
/* 442 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	12,	"UTM 12-N.Hemis  -NAD27_CANADA-",	"UTM Zone 12 - North.Hemis.  -NAD27_CANADA-"	},
/* 443 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	13,	"UTM 13-N.Hemis  -NAD27_CANADA-",	"UTM Zone 13 - North.Hemis.  -NAD27_CANADA-"	},
/* 444 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	14,	"UTM 14-N.Hemis  -NAD27_CANADA-",	"UTM Zone 14 - North.Hemis.  -NAD27_CANADA-"	},
/* 445 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	15,	"UTM 15-N.Hemis  -NAD27_CANADA-",	"UTM Zone 15 - North.Hemis.  -NAD27_CANADA-"	},
/* 446 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	16,	"UTM 16-N.Hemis  -NAD27_CANADA-",	"UTM Zone 16 - North.Hemis.  -NAD27_CANADA-"	},
/* 447 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	17,	"UTM 17-N.Hemis  -NAD27_CANADA-",	"UTM Zone 17 - North.Hemis.  -NAD27_CANADA-"	},
/* 448 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	18,	"UTM 18-N.Hemis  -NAD27_CANADA-",	"UTM Zone 18 - North.Hemis.  -NAD27_CANADA-"	},
/* 449 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	19,	"UTM 19-N.Hemis  -NAD27_CANADA-",	"UTM Zone 19 - North.Hemis.  -NAD27_CANADA-"	},
/* 450 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	20,	"UTM 20-N.Hemis  -NAD27_CANADA-",	"UTM Zone 20 - North.Hemis.  -NAD27_CANADA-"	},
/* 451 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	21,	"UTM 21-N.Hemis  -NAD27_CANADA-",	"UTM Zone 21 - North.Hemis.  -NAD27_CANADA-"	},
/* 452 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	22,	"UTM 22-N.Hemis  -NAD27_CANADA-",	"UTM Zone 22 - North.Hemis.  -NAD27_CANADA-"	},
/* 453 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	23,	"UTM 23-N.Hemis  -NAD27_CANADA-",	"UTM Zone 23 - North.Hemis.  -NAD27_CANADA-"	},
/* 454 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	24,	"UTM 24-N.Hemis  -NAD27_CANADA-",	"UTM Zone 24 - North.Hemis.  -NAD27_CANADA-"	},
/* 455 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	25,	"UTM 25-N.Hemis  -NAD27_CANADA-",	"UTM Zone 25 - North.Hemis.  -NAD27_CANADA-"	},
/* 456 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	26,	"UTM 26-N.Hemis  -NAD27_CANADA-",	"UTM Zone 26 - North.Hemis.  -NAD27_CANADA-"	},
/* 457 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	27,	"UTM 27-N.Hemis  -NAD27_CANADA-",	"UTM Zone 27 - North.Hemis.  -NAD27_CANADA-"	},
/* 458 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	28,	"UTM 28-N.Hemis  -NAD27_CANADA-",	"UTM Zone 28 - North.Hemis.  -NAD27_CANADA-"	},
/* 459 */	{NAD27_CAN_QUEBECd,	TM_UTM_Np,	TRANSMERK_Em,	29,	"UTM 29-N.Hemis  -NAD27_CANADA-",	"UTM Zone 29 - North.Hemis.  -NAD27_CANADA-"	},
/* 460 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 461 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	1,	"UTM 1-N.Hemis  -NAD83-",	"UTM Zone 1 - North.Hemis.  -NAD83-"	},
/* 462 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	2,	"UTM 2-N.Hemis  -NAD83-",	"UTM Zone 2 - North.Hemis.  -NAD83-"	},
/* 463 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	3,	"UTM 3-N.Hemis  -NAD83-",	"UTM Zone 3 - North.Hemis.  -NAD83-"	},
/* 464 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	4,	"UTM 4-N.Hemis  -NAD83-",	"UTM Zone 4 - North.Hemis.  -NAD83-"	},
/* 465 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	5,	"UTM 5-N.Hemis  -NAD83-",	"UTM Zone 5 - North.Hemis.  -NAD83-"	},
/* 466 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	6,	"UTM 6-N.Hemis  -NAD83-",	"UTM Zone 6 - North.Hemis.  -NAD83-"	},
/* 467 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	7,	"UTM 7-N.Hemis  -NAD83-",	"UTM Zone 7 - North.Hemis.  -NAD83-"	},
/* 468 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	8,	"UTM 8-N.Hemis  -NAD83-",	"UTM Zone 8 - North.Hemis.  -NAD83-"	},
/* 469 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	9,	"UTM 9-N.Hemis  -NAD83-",	"UTM Zone 9 - North.Hemis.  -NAD83-"	},
/* 470 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	10,	"UTM 10-N.Hemis  -NAD83-",	"UTM Zone 10 - North.Hemis.  -NAD83-"	},
/* 471 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	11,	"UTM 11-N.Hemis  -NAD83-",	"UTM Zone 11 - North.Hemis.  -NAD83-"	},
/* 472 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	12,	"UTM 12-N.Hemis  -NAD83-",	"UTM Zone 12 - North.Hemis.  -NAD83-"	},
/* 473 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	13,	"UTM 13-N.Hemis  -NAD83-",	"UTM Zone 13 - North.Hemis.  -NAD83-"	},
/* 474 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	14,	"UTM 14-N.Hemis  -NAD83-",	"UTM Zone 14 - North.Hemis.  -NAD83-"	},
/* 475 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	15,	"UTM 15-N.Hemis  -NAD83-",	"UTM Zone 15 - North.Hemis.  -NAD83-"	},
/* 476 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	16,	"UTM 16-N.Hemis  -NAD83-",	"UTM Zone 16 - North.Hemis.  -NAD83-"	},
/* 477 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	17,	"UTM 17-N.Hemis  -NAD83-",	"UTM Zone 17 - North.Hemis.  -NAD83-"	},
/* 478 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	18,	"UTM 18-N.Hemis  -NAD83-",	"UTM Zone 18 - North.Hemis.  -NAD83-"	},
/* 479 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	19,	"UTM 19-N.Hemis  -NAD83-",	"UTM Zone 19 - North.Hemis.  -NAD83-"	},
/* 480 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	20,	"UTM 20-N.Hemis  -NAD83-",	"UTM Zone 20 - North.Hemis.  -NAD83-"	},
/* 481 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	21,	"UTM 21-N.Hemis  -NAD83-",	"UTM Zone 21 - North.Hemis.  -NAD83-"	},
/* 482 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	22,	"UTM 22-N.Hemis  -NAD83-",	"UTM Zone 22 - North.Hemis.  -NAD83-"	},
/* 483 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	23,	"UTM 23-N.Hemis  -NAD83-",	"UTM Zone 23 - North.Hemis.  -NAD83-"	},
/* 484 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	24,	"UTM 24-N.Hemis  -NAD83-",	"UTM Zone 24 - North.Hemis.  -NAD83-"	},
/* 485 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	25,	"UTM 25-N.Hemis  -NAD83-",	"UTM Zone 25 - North.Hemis.  -NAD83-"	},
/* 486 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	26,	"UTM 26-N.Hemis  -NAD83-",	"UTM Zone 26 - North.Hemis.  -NAD83-"	},
/* 487 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	27,	"UTM 27-N.Hemis  -NAD83-",	"UTM Zone 27 - North.Hemis.  -NAD83-"	},
/* 488 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	28,	"UTM 28-N.Hemis  -NAD83-",	"UTM Zone 28 - North.Hemis.  -NAD83-"	},
/* 489 */	{NAD83_ALASKAd,	TM_UTM_Np,	TRANSMERK_Em,	29,	"UTM 29-N.Hemis  -NAD83-",	"UTM Zone 29 - North.Hemis.  -NAD83-"	},
/* 490 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 491 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 492 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 493 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 494 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 495 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 496 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 497 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 498 */	{CORREGO_ALEGREd,	TM_UTM_Np,	TRANSMERK_Em,	18,	"UTM 18-N.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 18 - North.Hemis.  -CORREGO_ALEGRE-"	},
/* 499 */	{CORREGO_ALEGREd,	TM_UTM_Np,	TRANSMERK_Em,	19,	"UTM 19-N.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 19 - North.Hemis.  -CORREGO_ALEGRE-"	},
/* 500 */	{CORREGO_ALEGREd,	TM_UTM_Np,	TRANSMERK_Em,	20,	"UTM 20-N.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 20 - North.Hemis.  -CORREGO_ALEGRE-"	},
/* 501 */	{CORREGO_ALEGREd,	TM_UTM_Np,	TRANSMERK_Em,	21,	"UTM 21-N.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 21 - North.Hemis.  -CORREGO_ALEGRE-"	},
/* 502 */	{CORREGO_ALEGREd,	TM_UTM_Np,	TRANSMERK_Em,	22,	"UTM 22-N.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 22 - North.Hemis.  -CORREGO_ALEGRE-"	},
/* 503 */	{CORREGO_ALEGREd,	TM_UTM_Sp,	TRANSMERK_Em,	23,	"UTM 23-S.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 23 - South.Hemis.  -CORREGO_ALEGRE-"	},
/* 504 */	{CORREGO_ALEGREd,	TM_UTM_Sp,	TRANSMERK_Em,	24,	"UTM 24-S.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 24 - South.Hemis.  -CORREGO_ALEGRE-"	},
/* 505 */	{CORREGO_ALEGREd,	TM_UTM_Sp,	TRANSMERK_Em,	25,	"UTM 25-S.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 25 - South.Hemis.  -CORREGO_ALEGRE-"	},
/* 506 */	{CORREGO_ALEGREd,	TM_UTM_Sp,	TRANSMERK_Em,	26,	"UTM 26-S.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 26 - South.Hemis.  -CORREGO_ALEGRE-"	},
/* 507 */	{CORREGO_ALEGREd,	TM_UTM_Sp,	TRANSMERK_Em,	27,	"UTM 27-S.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 27 - South.Hemis.  -CORREGO_ALEGRE-"	},
/* 508 */	{CORREGO_ALEGREd,	TM_UTM_Sp,	TRANSMERK_Em,	28,	"UTM 28-S.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 28 - South.Hemis.  -CORREGO_ALEGRE-"	},
/* 509 */	{CORREGO_ALEGREd,	TM_UTM_Sp,	TRANSMERK_Em,	29,	"UTM 29-S.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 29 - South.Hemis.  -CORREGO_ALEGRE-"	},
/* 510 */	{CORREGO_ALEGREd,	TM_UTM_Sp,	TRANSMERK_Em,	30,	"UTM 30-S.Hemis  -CORREGO_ALEGRE-",	"UTM Zone 30 - South.Hemis.  -CORREGO_ALEGRE-"	},
/* 511 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 512 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 513 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 514 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 515 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 516 */	{NONEd,	0,	0,	0,"Undefined",""  },
/* 517 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Np,	TRANSMERK_Em,	17,	"UTM 17-N.Hemis  -SAD69-",	"UTM Zone 17 - North.Hemis.  -SAD69-"	},
/* 518 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Np,	TRANSMERK_Em,	18,	"UTM 18-N.Hemis  -SAD69-",	"UTM Zone 18 - North.Hemis.  -SAD69-"	},
/* 519 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Np,	TRANSMERK_Em,	19,	"UTM 19-N.Hemis  -SAD69-",	"UTM Zone 19 - North.Hemis.  -SAD69-"	},
/* 520 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Np,	TRANSMERK_Em,	20,	"UTM 20-N.Hemis  -SAD69-",	"UTM Zone 20 - North.Hemis.  -SAD69-"	},
/* 521 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Np,	TRANSMERK_Em,	21,	"UTM 21-N.Hemis  -SAD69-",	"UTM Zone 21 - North.Hemis.  -SAD69-"	},
/* 522 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Np,	TRANSMERK_Em,	22,	"UTM 22-N.Hemis  -SAD69-",	"UTM Zone 22 - North.Hemis.  -SAD69-"	},
/* 523 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Sp,	TRANSMERK_Em,	17,	"UTM 17-S.Hemis  -SAD69-",	"UTM Zone 17 - South.Hemis.  -SAD69-"	},
/* 524 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Sp,	TRANSMERK_Em,	18,	"UTM 18-S.Hemis  -SAD69-",	"UTM Zone 18 - South.Hemis.  -SAD69-"	},
/* 525 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Sp,	TRANSMERK_Em,	19,	"UTM 19-S.Hemis  -SAD69-",	"UTM Zone 19 - South.Hemis.  -SAD69-"	},
/* 526 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Sp,	TRANSMERK_Em,	20,	"UTM 20-S.Hemis  -SAD69-",	"UTM Zone 20 - South.Hemis.  -SAD69-"	},
/* 527 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Sp,	TRANSMERK_Em,	21,	"UTM 21-S.Hemis  -SAD69-",	"UTM Zone 21 - South.Hemis.  -SAD69-"	},
/* 528 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Sp,	TRANSMERK_Em,	22,	"UTM 22-S.Hemis  -SAD69-",	"UTM Zone 22 - South.Hemis.  -SAD69-"	},
/* 529 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Sp,	TRANSMERK_Em,	23,	"UTM 23-S.Hemis  -SAD69-",	"UTM Zone 23 - South.Hemis.  -SAD69-"	},
/* 530 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Sp,	TRANSMERK_Em,	24,	"UTM 24-S.Hemis  -SAD69-",	"UTM Zone 24 - South.Hemis.  -SAD69-"	},
/* 531 */	{SOUTH_AMERICAN_1969d,	TM_UTM_Sp,	TRANSMERK_Em,	25,	"UTM 25-S.Hemis  -SAD69-",	"UTM Zone 25 - South.Hemis.  -SAD69-"	},

//add by jjj 2011.12.13
//NAD27 NAD83 America LongLat
/* 532 */	{NAD27_MIDDLE_AMERIKAd,	0,	GEOm,	0,	"Long-Lat  -NAD27 Middle America-","Long-Lat  -NAD27 Middle America-"	},
/* 533 */	{NAD83_MEXICO_CENTRAL_AMERIKAd,		0,	GEOm,	0,	"Long-Lat  -NAD83 Cent.America-",	"Long-Lat  -NAD83 Cent.America-"	},
//add by jjj 2013.7.23
/* 534 */	{OSGB1936d,				TM_UK_NGR,	TRANSMERK_Em,	0,	"British NatinalGrid -OSGB36-",	"British NatinalGrid -OSGB36-"		},
/*add by CX 2014.12.24*/
/*535*/		{CHINA2000, 0, GEOm, 0, "Long - Lat  -CHINA 2000-","Longitude - Latitude -CHINA 2000-"   }

};
#define MAX_KOORDLIST (sizeof(KoordSys_List) / sizeof(KOORDSTRUCT))

//add by jjj 2012.8.14
/* Category: Longitude / Latitude */			/* @PC300997 */
static long  Long_Lat_List[] =
{		/* 	No */
	/*  1 */	SYS_GEO_WGS84,
	/*  2 */	SYS_GEO_AGD,
	/*  3 */	SYS_GEO_AINELABD_BAHRAIN,
	/*  4 */	SYS_GEO_AUSTRIA,
	/*  5 */	SYS_GEO_CAPE,
	/*  6 */	SYS_GEO_DHDN,
	/*  7 */	SYS_GEO_ED50,
	/*  8 */	SYS_GEO_ED50_BELGIUM,
	/*  9 */	SYS_GEO_KKJ_FINLAND,
	/* 10 */	SYS_GEO_EGYPT,
	/* 11 */	SYS_GEO_HD72,
	/* 12 */	SYS_GEO_IGM1940,
	/* 13 */	SYS_GEO_IRELAND,
	/* 14 */	SYS_GEO_LUXEMBOURG,
	/* 15 */	SYS_GEO_NETHERLANDS,
	/* 16 */	SYS_GEO_NAD27,
	/* 17 */	SYS_GEO_NAD27_ONTARIO,
	/* 18 */	SYS_GEO_NAD27_QUEBEC,
	/* 19 */	SYS_GEO_PULKOVO,
	/* 20 */	SYS_GEO_SWEDEN,
	/* 21 */	SYS_GEO_CH1903,
/* add by cx 2014.12.24 */
	/* 22 */    SYS_GEO_NAD27M,
	/* 23 */	SYS_GEO_NAD83,
	/* 24 */	SYS_GEO_CHINA2000
};
#define LongLatSize (sizeof(Long_Lat_List) / sizeof(long))

/* Category: Australien Map Grid */			/* @PC300997 */
static long  AMG66_List[] =
{		/* 	No */
	/*  0 */	SYS_AMG49,
	/*  1 */	SYS_AMG50,
	/*  2 */	SYS_AMG51,
	/*  3 */	SYS_AMG52,
	/*  4 */	SYS_AMG53,
	/*  5 */	SYS_AMG54,
	/*  6 */	SYS_AMG55,
	/*  7 */	SYS_AMG56,
	/*  8 */	SYS_AMG57
};
#define AMG66Size (sizeof(AMG66_List) / sizeof(long))

/* Category: Belgium Coordinate systems */			/* @PC141298 */
static long  Belgium_List[] =
{		/* 	No */
	/*  0 */	SYS_BELGIUM_LAMBERT72_50,
	/*  1 */	SYS_BELGIUM_LAMBERT72
};
#define BELGIUMSize (sizeof(Belgium_List) / sizeof(long))

/* Category: Gauss Kruger (DHDN) */			/* @PC061097 */
static long  GK_DHDN_List[] =
{		/* 	No */
	/*  0 */	SYS_GK1_DHDN,
	/*  1 */	SYS_GK2_DHDN,
	/*  2 */	SYS_GK3_DHDN,
	/*  3 */	SYS_GK4_DHDN,
	/*  4 */	SYS_GK5_DHDN,
	/*  5 */	SYS_GK7,
	/*  6 */	SYS_GK10,
	/*  7 */	SYS_GK12
};
#define GK_DHDNSize (sizeof(GK_DHDN_List) / sizeof(long))

/* Category: Gauss Kruger (PULKOVO 42) */			/* @PC061097 */
static long  GK_PULKOVO_List[] =
{		/* 	No */
	/*  0 */	SYS_GK01_PULKOVO,
	/*  1 */	SYS_GK02_PULKOVO,
	/*  2 */	SYS_GK3_6,	/* Alte Nummer 19 */
	/*  3 */	SYS_GK4_6,	/* Alte Nummer 20 */
	/*  4 */	SYS_GK05_PULKOVO,
	/*  5 */	SYS_GK6_6,	/* Alte Nummer 25 */
	/*  6 */	SYS_GK07_PULKOVO,
	/*  7 */	SYS_GK08_PULKOVO,
	/*  8 */	SYS_GK09_PULKOVO,
	/*  9 */	SYS_GK10_PULKOVO,
	/* 10 */	SYS_GK11_PULKOVO,
	/* 11 */	SYS_GK12_PULKOVO,
	/* 12 */	SYS_GK13_6,	/* Alte Nummer 28 */
	/* 13 */	SYS_GK14_PULKOVO,
	/* 14 */	SYS_GK15_PULKOVO,
	/* 15 */	SYS_GK16_PULKOVO,
	/* 16 */	SYS_GK17_PULKOVO,
	/* 17 */	SYS_GK18_PULKOVO,
	/* 18 */	SYS_GK19_6,	/* Alte Nummer 23 */
	/* 19 */	SYS_GK20_6,	/* Alte Nummer 24 */
	/* 20 */	SYS_GK21_PULKOVO,
	/* 21 */	SYS_GK22_PULKOVO,
	/* 22 */	SYS_GK23_PULKOVO,
	/* 23 */	SYS_GK24_PULKOVO,
	/* 24 */	SYS_GK25_PULKOVO,
	/* 25 */	SYS_GK26_PULKOVO,
	/* 26 */	SYS_GK27_PULKOVO,
	/* 27 */	SYS_GK28_PULKOVO,
	/* 28 */	SYS_GK29_PULKOVO,
	/* 29 */	SYS_GK30_PULKOVO,
	/* 30 */	SYS_GK31_PULKOVO,
	/* 31 */	SYS_GK32_PULKOVO
};
#define GK_PULKOVOSize (sizeof(GK_PULKOVO_List) / sizeof(long))

/* Category: Projections of Africa */			/* @PC300997 */
static long  Africa_List[] =
{		/* 	No */
	/*  0 */	SYS_Lo13,
	/*  1 */	SYS_Lo15,
	/*  2 */	SYS_Lo17,
	/*  3 */	SYS_Lo19,
	/*  4 */	SYS_Lo21,
	/*  5 */	SYS_Lo23,
	/*  6 */	SYS_Lo25,
	/*  7 */	SYS_Lo27,
	/*  8 */	SYS_Lo29,
	/*  9 */	SYS_Lo31,
	/* 10 */	SYS_Lo33,
	/* 11 */	SYS_Lo35,
	/* 12 */	SYS_UTM39_N_AINELABD_BAHRAIN,
	/* 12 */	SYS_UTM39_WGS84,
	/* 13 */	SYS_UTM36_CAPE,
	/* 14 */	SYS_UTM36_CL1866,
	/* 15 */	SYS_RED_BELT,
	/* 16 */	SYS_PURPLE_BELT,
	/* 17 */	SYS_EXT_PURPLE_BELT
};
#define AfricaSize (sizeof(Africa_List) / sizeof(long))

/* Category: Projections of Europe */			/* @PC300997 */
static long  Europe_List[] =
{		/* 	No */
	/*  0 */	SYS_CL2_AUSTRIA,
	/*  1 */	SYS_M28_M34_AUSTRIA,
	/*  2 */	SYS_M28_AUSTRIA,
	/*  3 */	SYS_M31_AUSTRIA,
	/*  4 */	SYS_M34_AUSTRIA,
	/*  5 */	SYS_CL2L13_2P46P49_AUSTRIA,
	/*  6 */	SYS_2MIOAUSTRIA_ED50,
	/*  7 */	SYS_CROATIA_CENTRAL,
	/*  8 */	SYS_CROATIA_15,
	/*  9 */	SYS_CROATIA_18,
	/* 10 */	SYS_CROATIA_21,
	/* 11 */	SYS_EOV,
	/* 12 */	SYS_GLUX_ED50,
	/* 13 */	SYS_CL2L15P27P63_ED50,
	/* 14 */	SYS_CL2L14_5P48_4P51_4_ED50,
	/* 15 */	SYS_CL2L10_5P49P56_ED50,
	/* 16 */	SYS_IRE,
	/* 17 */	SYS_Gauss_DLX,
	/* 18 */	SYS_RD,
	/* 19 */	SYS_RT90_SWEDEN,
	/* 20 */	SYS_ALBL15_8P50P70_SWEDEN,
	/* 21 */	SYS_Swiss_CH1903,
	/* 22 */	SYS_GAUSS_BOAGA_1,
	/* 23 */	SYS_GAUSS_BOAGA_2,
	/*add by cx 2014.12.24*/
	/*24*/		SYS_UKNGR_OSGB36
};
#define EuropeSize (sizeof(Europe_List) / sizeof(long))

/* Category: KKJ Finland (ED 50) */			/* @PC991117 */
static long  KKJ_List[] =
{		/* 	No */
	/*  0 */	SYS_KKJ1,
	/*  1 */	SYS_KKJ2,
	/*  2 */	SYS_KKJ3,
	/*  3 */	SYS_KKJ4
};
#define KKJSize (sizeof(KKJ_List) / sizeof(long))


static long  NAmerica_List[] =
{		/* 	No */
	/*  0 */	SYS_UTM17_NAD27_ONTARIO,
	/*  1 */	SYS_UTM18_NAD27_QUEBEC,
};
#define NAmericaSize (sizeof(NAmerica_List) / sizeof(long))


/* Category: UTM (ED 50) */			/* @PC300997 */
static long  UTM_ED50_List[] =
{		/* 	No */
	/*  0 */	SYS_UTM28_N_ED50,
	/*  1 */	SYS_UTM29_ED50,
	/*  2 */	SYS_UTM30_N_ED50,
	/*  3 */	SYS_UTM31_ED50,
	/*  4 */	SYS_UTM32_ED50,
	/*  5 */	SYS_UTM33_ED50,
	/*  6 */	SYS_UTM34_ED50,
	/*  7 */	SYS_UTM35_N_ED50,
	/*  8 */	SYS_UTM36_ED50,
	/*  9 */	SYS_UTM37_ED50,
	/* 10 */	SYS_UTM38_N_ED50,
	/* 11 */	SYS_UTM18_ED50,
	/* 12 */	SYS_UTM49_ED50,
	/* 13 */	SYS_UTM51_ED50,
	/* 14 */	SYS_UTM56_ED50
};
#define UTM_ED50Size (sizeof(UTM_ED50_List) / sizeof(long))


/* Category: UTM (ED 50) */			/* @PC300997 */
static long  LATVIA_List[] =
{		/* 	No */
	/*  0 */	SYS_UTM_LATVIA,
};
#define LATVIASize (sizeof(LATVIA_List) / sizeof(long))


/* Category: UTM (NAD27 US) */			/* @PC110899 */
static long  UTM_NAD27_US_List[] =
{		/* 	No */
	/*  1 */	SYS_UTM1_N_NAD27_ALASKA,
	/*  2 */	SYS_UTM2_N_NAD27_ALASKA,
	/*  3 */	SYS_UTM3_N_NAD27_ALASKA,
	/*  4 */	SYS_UTM4_N_NAD27_ALASKA,
	/*  5 */	SYS_UTM5_N_NAD27_ALASKA,
	/*  6 */	SYS_UTM6_N_NAD27_ALASKA,
	/*  7 */	SYS_UTM7_N_NAD27_ALASKA,
	/*  8 */	SYS_UTM8_N_NAD27_ALASKA,
	/*  9 */	SYS_UTM9_N_NAD27_ALASKA,
	/* 10 */	SYS_UTM10_N_NAD27_CENTRAL,
	/* 11 */	SYS_UTM11_N_NAD27_CENTRAL,
	/* 12 */	SYS_UTM12_N_NAD27_CENTRAL,
	/* 13 */	SYS_UTM13_N_NAD27_CENTRAL,
	/* 14 */	SYS_UTM14_N_NAD27_CENTRAL,
	/* 15 */	SYS_UTM15_N_NAD27_CENTRAL,
	/* 16 */	SYS_UTM16_N_NAD27_CENTRAL,
	/* 17 */	SYS_UTM17_N_NAD27_CENTRAL,
	/* 18 */	SYS_UTM18_N_NAD27_CENTRAL,
	/* 19 */	SYS_UTM19_N_NAD27_CENTRAL
};
#define UTM_NAD27_USSize (sizeof(UTM_NAD27_US_List) / sizeof(long))

/* Category: UTM (NAD27 MEXICO) */			/* @PC110899 */
static long  UTM_NAD27_MEXICO_List[] =
{		/* 	No */
	/* 1 */	SYS_UTM10_N_NAD27_MEXICO,
	/* 2 */	SYS_UTM11_N_NAD27_MEXICO,
	/* 3 */	SYS_UTM12_N_NAD27_MEXICO,
	/* 4 */	SYS_UTM13_N_NAD27_MEXICO,
	/* 5 */	SYS_UTM14_N_NAD27_MEXICO,
	/* 6 */	SYS_UTM15_N_NAD27_MEXICO,
	/* 7 */	SYS_UTM16_N_NAD27_MEXICO
};
#define UTM_NAD27_MEXICOSize (sizeof(UTM_NAD27_MEXICO_List) / sizeof(long))

/* Category: UTM (NAD27Canada) */			/* @PC110899 */
static long  UTM_NAD27_CANADA_List[] =
{		/* 	No */
	/*  1 */	SYS_UTM7_N_NAD27_CANADA,
	/*  2 */	SYS_UTM8_N_NAD27_CANADA,
	/*  3 */	SYS_UTM9_N_NAD27_CANADA,
	/*  4 */	SYS_UTM10_N_NAD27_CANADA,
	/*  5 */	SYS_UTM11_N_NAD27_CANADA,
	/*  6 */	SYS_UTM12_N_NAD27_CANADA,
	/*  7 */	SYS_UTM13_N_NAD27_CANADA,
	/*  8 */	SYS_UTM14_N_NAD27_CANADA,
	/*  9 */	SYS_UTM15_N_NAD27_CANADA,
	/* 10 */	SYS_UTM16_N_NAD27_CANADA,
	/* 11 */	SYS_UTM17_N_NAD27_CANADA,
	/* 12 */	SYS_UTM18_N_NAD27_CANADA,
	/* 13 */	SYS_UTM19_N_NAD27_CANADA,
	/* 14 */	SYS_UTM20_N_NAD27_CANADA,
	/* 15 */	SYS_UTM21_N_NAD27_CANADA,
	/* 16 */	SYS_UTM22_N_NAD27_CANADA,
	/* 17 */	SYS_UTM23_N_NAD27_CANADA,
	/* 18 */	SYS_UTM24_N_NAD27_CANADA,
	/* 19 */	SYS_UTM25_N_NAD27_CANADA,
	/* 20 */	SYS_UTM26_N_NAD27_CANADA,
	/* 21 */	SYS_UTM27_N_NAD27_CANADA,
	/* 22 */	SYS_UTM28_N_NAD27_CANADA,
	/* 23 */	SYS_UTM29_N_NAD27_CANADA
};
#define UTM_NAD27_CANADASize (sizeof(UTM_NAD27_CANADA_List) / sizeof(long))

/* Category: UTM (NAD83) */			/* @PC110899 */
static long  UTM_NAD83_List[] =
{		/* 	No */
	/*  1 */	SYS_UTM1_N_NAD83,
	/*  2 */	SYS_UTM2_N_NAD83,
	/*  3 */	SYS_UTM3_N_NAD83,
	/*  4 */	SYS_UTM4_N_NAD83,
	/*  5 */	SYS_UTM5_N_NAD83,
	/*  6 */	SYS_UTM6_N_NAD83,
	/*  7 */	SYS_UTM7_N_NAD83,
	/*  8 */	SYS_UTM8_N_NAD83,
	/*  9 */	SYS_UTM9_N_NAD83,
	/* 10 */	SYS_UTM10_N_NAD83,
	/* 11 */	SYS_UTM11_N_NAD83,
	/* 12 */	SYS_UTM12_N_NAD83,
	/* 13 */	SYS_UTM13_N_NAD83,
	/* 14 */	SYS_UTM14_N_NAD83,
	/* 15 */	SYS_UTM15_N_NAD83,
	/* 16 */	SYS_UTM16_N_NAD83,
	/* 17 */	SYS_UTM17_N_NAD83,
	/* 18 */	SYS_UTM18_N_NAD83,
	/* 19 */	SYS_UTM19_N_NAD83,
	/* 20 */	SYS_UTM20_N_NAD83,
	/* 21 */	SYS_UTM21_N_NAD83,
	/* 22 */	SYS_UTM22_N_NAD83,
	/* 23 */	SYS_UTM23_N_NAD83,
	/* 24 */	SYS_UTM24_N_NAD83,
	/* 25 */	SYS_UTM25_N_NAD83,
	/* 26 */	SYS_UTM26_N_NAD83,
	/* 27 */	SYS_UTM27_N_NAD83,
	/* 28 */	SYS_UTM28_N_NAD83,
	/* 29 */	SYS_UTM29_N_NAD83
};
#define UTM_NAD83Size (sizeof(UTM_NAD83_List) / sizeof(long))

/* Category: UTM (Corrego Allegre) */			/* @PC110899 */
static long  UTM_COR_ALLEGRE_List[] =
{		/* 	No */
	/*  1 */	SYS_UTM19_N_CORREGO_ALLEGRE,
	/*  2 */	SYS_UTM20_N_CORREGO_ALLEGRE,
	/*  3 */	SYS_UTM21_N_CORREGO_ALLEGRE,
	/*  4 */	SYS_UTM22_N_CORREGO_ALLEGRE,
	/*  5 */	SYS_UTM18_N_CORREGO_ALLEGRE,
	/*  6 */	SYS_UTM19_S_CORREGO_ALLEGRE,
	/*  7 */	SYS_UTM20_S_CORREGO_ALLEGRE,
	/*  8 */	SYS_UTM21_S_CORREGO_ALLEGRE,
	/*  9 */	SYS_UTM22_S_CORREGO_ALLEGRE,
	/* 10 */	SYS_UTM23_S_CORREGO_ALLEGRE,
	/* 11 */	SYS_UTM24_S_CORREGO_ALLEGRE,
	/* 12 */	SYS_UTM25_S_CORREGO_ALLEGRE
};
#define UTM_COR_ALLEGRESize (sizeof(UTM_COR_ALLEGRE_List) / sizeof(long))

/* Category: UTM (SAD49) */			/* @PC110899 */
static long  UTM_SAD69_List[] =
{		/* 	No */
	/*  1 */	SYS_UTM17_N_SAD69,
	/*  2 */	SYS_UTM18_N_SAD69,
	/*  3 */	SYS_UTM19_N_SAD69,
	/*  4 */	SYS_UTM20_N_SAD69,
	/*  5 */	SYS_UTM21_N_SAD69,
	/*  6 */	SYS_UTM22_N_SAD69,
	/*  7 */	SYS_UTM17_S_SAD69,
	/*  8 */	SYS_UTM18_S_SAD69,
	/*  9 */	SYS_UTM19_S_SAD69,
	/* 10 */	SYS_UTM20_S_SAD69,
	/* 11 */	SYS_UTM21_S_SAD69,
	/* 12 */	SYS_UTM22_S_SAD69,
	/* 13 */	SYS_UTM23_S_SAD69,
	/* 14 */	SYS_UTM24_S_SAD69,
	/* 15 */	SYS_UTM25_S_SAD69
};
#define UTM_SAD69Size (sizeof(UTM_SAD69_List) / sizeof(long))

/* Category: UTM (WGS 84) */			/* @PC300997 */
static long  UTM_WGS84_List[] =
{		/* 	No */
	/*  0 */	SYS_UTM01_N_WGS84,
	/*  1 */	SYS_UTM02_N_WGS84,
	/*  2 */	SYS_UTM03_N_WGS84,
	/*  3 */	SYS_UTM04_N_WGS84,
	/*  4 */	SYS_UTM05_N_WGS84,
	/*  5 */	SYS_UTM06_N_WGS84,
	/*  6 */	SYS_UTM07_N_WGS84,
	/*  7 */	SYS_UTM08_N_WGS84,
	/*  8 */	SYS_UTM09_N_WGS84,
	/*  9 */	SYS_UTM10_N_WGS84,
	/* 10 */	SYS_UTM11_N_WGS84,
	/* 11 */	SYS_UTM12_N_WGS84,
	/* 12 */	SYS_UTM13_N_WGS84,
	/* 13 */	SYS_UTM14_N_WGS84,
	/* 14 */	SYS_UTM15_N_WGS84,
	/* 15 */	SYS_UTM16_N_WGS84,
	/* 16 */	SYS_UTM17_N_WGS84,
	/* 17 */	SYS_UTM18_N_WGS84,
	/* 18 */	SYS_UTM19_N_WGS84,
	/* 19 */	SYS_UTM20_N_WGS84,
	/* 20 */	SYS_UTM21_N_WGS84,
	/* 21 */	SYS_UTM22_N_WGS84,
	/* 22 */	SYS_UTM23_N_WGS84,
	/* 23 */	SYS_UTM24_N_WGS84,
	/* 24 */	SYS_UTM25_N_WGS84,
	/* 25 */	SYS_UTM26_N_WGS84,
	/* 26 */	SYS_UTM27_N_WGS84,
	/* 27 */	SYS_UTM28_N_WGS84,
	/* 28 */	SYS_UTM29_N_WGS84,
	/* 29 */	SYS_UTM30_N_WGS84,
	/* 30 */	SYS_UTM31_N_WGS84,
	/* 31 */	SYS_UTM32_N_WGS84,
	/* 32 */	SYS_UTM33_N_WGS84,
	/* 33 */	SYS_UTM34_N_WGS84,
	/* 34 */	SYS_UTM35_N_WGS84,
	/* 35 */	SYS_UTM36_N_WGS84,
	/* 36 */	SYS_UTM37_N_WGS84,
	/* 37 */	SYS_UTM38_N_WGS84,
	/* 38 */	SYS_UTM39_N_WGS84,
	/* 39 */	SYS_UTM40_N_WGS84,
	/* 40 */	SYS_UTM41_N_WGS84,
	/* 41 */	SYS_UTM42_N_WGS84,
	/* 42 */	SYS_UTM43_N_WGS84,
	/* 43 */	SYS_UTM44_N_WGS84,
	/* 44 */	SYS_UTM45_N_WGS84,
	/* 45 */	SYS_UTM46_N_WGS84,
	/* 46 */	SYS_UTM47_N_WGS84,
	/* 47 */	SYS_UTM48_N_WGS84,
	/* 48 */	SYS_UTM49_N_WGS84,
	/* 49 */	SYS_UTM50_N_WGS84,
	/* 50 */	SYS_UTM51_N_WGS84,
	/* 51 */	SYS_UTM52_N_WGS84,
	/* 52 */	SYS_UTM53_N_WGS84,
	/* 53 */	SYS_UTM54_N_WGS84,
	/* 54 */	SYS_UTM55_N_WGS84,
	/* 55 */	SYS_UTM56_N_WGS84,
	/* 56 */	SYS_UTM57_N_WGS84,
	/* 57 */	SYS_UTM58_N_WGS84,
	/* 58 */	SYS_UTM59_N_WGS84,
	/* 59 */	SYS_UTM60_N_WGS84,
	/* 60 */	SYS_UTM01_S_WGS84,
	/* 61 */	SYS_UTM02_S_WGS84,
	/* 62 */	SYS_UTM03_S_WGS84,
	/* 63 */	SYS_UTM04_S_WGS84,
	/* 64 */	SYS_UTM05_S_WGS84,
	/* 65 */	SYS_UTM06_S_WGS84,
	/* 66 */	SYS_UTM07_S_WGS84,
	/* 67 */	SYS_UTM08_S_WGS84,
	/* 68 */	SYS_UTM09_S_WGS84,
	/* 69 */	SYS_UTM10_S_WGS84,
	/* 70 */	SYS_UTM11_S_WGS84,
	/* 71 */	SYS_UTM12_S_WGS84,
	/* 72 */	SYS_UTM13_S_WGS84,
	/* 73 */	SYS_UTM14_S_WGS84,
	/* 74 */	SYS_UTM15_S_WGS84,
	/* 75 */	SYS_UTM16_S_WGS84,
	/* 76 */	SYS_UTM17_S_WGS84,
	/* 77 */	SYS_UTM18_S_WGS84,
	/* 78 */	SYS_UTM19_S_WGS84,
	/* 79 */	SYS_UTM20_S_WGS84,
	/* 70 */	SYS_UTM21_S_WGS84,
	/* 81 */	SYS_UTM22_S_WGS84,
	/* 82 */	SYS_UTM23_S_WGS84,
	/* 83 */	SYS_UTM24_S_WGS84,
	/* 84 */	SYS_UTM25_S_WGS84,
	/* 85 */	SYS_UTM26_S_WGS84,
	/* 86 */	SYS_UTM27_S_WGS84,
	/* 87 */	SYS_UTM28_S_WGS84,
	/* 88 */	SYS_UTM29_S_WGS84,
	/* 89 */	SYS_UTM30_S_WGS84,
	/* 90 */	SYS_UTM31_S_WGS84,
	/* 91 */	SYS_UTM32_S_WGS84,
	/* 92 */	SYS_UTM33_S_WGS84,
	/* 93 */	SYS_UTM34_S_WGS84,
	/* 94 */	SYS_UTM35_S_WGS84,
	/* 95 */	SYS_UTM36_S_WGS84,
	/* 96 */	SYS_UTM37_S_WGS84,
	/* 97 */	SYS_UTM38_S_WGS84,
	/* 98 */	SYS_UTM39_S_WGS84,
	/* 99 */	SYS_UTM40_S_WGS84,
	/*100 */	SYS_UTM41_S_WGS84,
	/*101 */	SYS_UTM42_S_WGS84,
	/*102 */	SYS_UTM43_S_WGS84,
	/*103 */	SYS_UTM44_S_WGS84,
	/*104 */	SYS_UTM45_S_WGS84,
	/*105 */	SYS_UTM46_S_WGS84,
	/*106 */	SYS_UTM47_S_WGS84,
	/*107 */	SYS_UTM48_S_WGS84,
	/*108 */	SYS_UTM49_S_WGS84,
	/*109 */	SYS_UTM50_S_WGS84,
	/*110 */	SYS_UTM51_S_WGS84,
	/*111 */	SYS_UTM52_S_WGS84,
	/*112 */	SYS_UTM53_S_WGS84,
	/*113 */	SYS_UTM54_S_WGS84,
	/*114 */	SYS_UTM55_S_WGS84,
	/*115 */	SYS_UTM56_S_WGS84,
	/*116 */	SYS_UTM57_S_WGS84,
	/*117 */	SYS_UTM58_S_WGS84,
	/*118 */	SYS_UTM59_S_WGS84,
	/*119 */	SYS_UTM60_S_WGS84
};
#define UTM_WGS84Size (sizeof(UTM_WGS84_List) / sizeof(long))

/* Category: Projections on the Sphere*/			/* @PC300997 */
static long  Sphere_List[] =
{		/* 	No */
	/*  0 */	SYS_800TGER_WGS84,
	/*  1 */	SYS_UTM32_N_Sphere
};
#define SPHERESize (sizeof(Sphere_List) / sizeof(long))

//////////////////////////////////////////////////////////////////////////
//add by jjj 2012.9.28 北京1954 			
static long  BCS1954_List[] =
{		/* 	No */
	
	/* 0 */		SYS_GK13_PULKOVO_BCS1954d,
	/* 1 */		SYS_GK14_PULKOVO_BCS1954d,
	/* 2 */		SYS_GK15_PULKOVO_BCS1954d,
	/* 3 */		SYS_GK16_PULKOVO_BCS1954d,
	/* 4 */		SYS_GK17_PULKOVO_BCS1954d,
	/* 5 */		SYS_GK18_PULKOVO_BCS1954d,
	/* 6 */		SYS_GK19_PULKOVO_BCS1954d,
	/* 7 */		SYS_GK20_PULKOVO_BCS1954d,
	/* 8 */		SYS_GK21_PULKOVO_BCS1954d,
	/* 9 */		SYS_GK22_PULKOVO_BCS1954d,
	/* 10 */	SYS_GK23_PULKOVO_BCS1954d,
	/* 11 */	SYS_LAMBERT_BCS1954d
};
#define BCS1954Size (sizeof(BCS1954_List) / sizeof(long))

//add by jjj 2013.7.23 GreatBritain
static long  GreatBritain_List[] =
{		/* 	No */

	/* 0 */		SYS_UKNGR_OSGB36,
};
#define GREATBRITAINSize (sizeof(GreatBritain_List) / sizeof(long))

static long  Egypt_List[] =
{		/* 	No */

	/* 0 */		SYS_RED_BELT,
	/* 1 */		SYS_PURPLE_BELT,
	/* 2 */		SYS_EXT_PURPLE_BELT,
};
#define EGYPTSize (sizeof(Egypt_List) / sizeof(long))

static long  Portugal_List[] =
{		/* 	No */

	/* 0 */		SYS_Gauss_DLX,
};
#define PORTUGALSize (sizeof(Portugal_List) / sizeof(long))

//////////////////////////////////////////////////////////////////////////

static CATEGORYARRAY  Category_Item_List =
{		/* 		name 					CategorySize	ProjNumber[]*/
	/*  0 */	{"Longitude-Latitude", 		LongLatSize,			Long_Lat_List		},
	/*  1 */	{"Australian Map Grid", 	AMG66Size,				AMG66_List			},
	/*  2 */	{"Belgium -BD72-", 			BELGIUMSize,			Belgium_List		},
	/*  3 */	{"Gauss-Kruger -DHDN-", 	GK_DHDNSize,			GK_DHDN_List		},
	/*  4 */	{"Gauss-Kruger -PULKOVO-",	GK_PULKOVOSize,			GK_PULKOVO_List		},
	/*  5 */	{"Africa", 					AfricaSize,				Africa_List			},
	/*  6 */	{"Europe", 					EuropeSize,				Europe_List			},
	/* 10 */	{"Finland", 				KKJSize,				KKJ_List			},
	/*  7 */	{"Latvia-", 				LATVIASize,				LATVIA_List         },
	/*  8 */	{"North America", 			NAmericaSize,			NAmerica_List		},
	/*  9 */	{"UTM -Corrego Allegre-", 	UTM_COR_ALLEGRESize,	UTM_COR_ALLEGRE_List},
	/* 10 */	{"UTM -ED 50-", 			UTM_ED50Size,			UTM_ED50_List		},
	/* 11 */	{"UTM -NAD27 Canada-", 		UTM_NAD27_CANADASize,	UTM_NAD27_CANADA_List},
	/* 12 */	{"UTM -NAD27 Mexico-", 		UTM_NAD27_MEXICOSize,	UTM_NAD27_MEXICO_List},
	/* 13 */	{"UTM -NAD27 US-", 			UTM_NAD27_USSize,		UTM_NAD27_US_List	},
	/* 14 */	{"UTM -NAD83-", 			UTM_NAD83Size,			UTM_NAD83_List		},
	/* 15 */	{"UTM -SAD69-", 			UTM_SAD69Size,			UTM_SAD69_List		},
	/* 16 */	{"UTM -WGS 84-", 			UTM_WGS84Size,			UTM_WGS84_List		},
	/* 17 */	{"Sphere -WGS 84-", 		SPHERESize,				Sphere_List			},

	//add by jjj 2012.9.28  北京1954 	
	/* 18 */	{"BCS1954-", 				BCS1954Size,			BCS1954_List		},
	//add by jjj 2013.7.23 GreatBritain 	
	/* 19 */	{"Great Britain", 			GREATBRITAINSize,		GreatBritain_List	},
	/* 20 */	{"Egypt", 					EGYPTSize,				Egypt_List			},
	/* 20 */	{"Portugal", 				PORTUGALSize,			Portugal_List		},
};
#define category_item_size (sizeof(Category_Item_List) / sizeof(CATEGORY))


#endif
