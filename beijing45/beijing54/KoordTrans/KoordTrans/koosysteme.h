/***@#Header******************************************************************
 *
 *  PROJECT:    ls_geo
 *
 *  MODULE:     koosysteme
 *
 *  FILENAME:   koosysteme.h
 *
 *  COPYRIGHT:  L&S Hochfrequenztechnik GmbH
 *              Im Gewerbegebiet 31
 *              77839 Lichtenau
 *              Germany
 *
 *  TOPIC:      ---
 *
 *  AUTHOR:     Thomas Bauer (@TB)
 *
 *  WRITTEN:    @TB010998
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

#ifndef __KOOSYSTEME_H__
#define __KOOSYSTEME_H__


/***@#Include*****************************************************************
 *
 *  INCLUDES
 *
 *****************************************************************************/

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

/* ************************************************************************** */
/* ** Hederfile zu LS_Transkoord.cp und dergleichen                        ** */
/* ** Enth攍t die Nummern der Koordinatensysteme                           ** */
/* ** ㎜&S Hochfrequenztechnik, Lichtenau 1994                             ** */
/* ************************************************************************** */

/* PROJECTIONSMETHODEN Constanten */
#define MAXMETHODE		17

#define NOMETHODE  		0 			/* User definiert */
#define USER1m  		1 			/* User definiert */
#define USER2m  		2 			/* User definiert */
#define GEOm			3 			/* Geo */
#define TRANSMERK_Sm	4 			/* Transversal Merkator (Zylinder) Sphere*/
#define TRANSMERK_Em	5 			/* Transversal Merkator (Zylinder) Ellipsoid*/
#define IREm			6 			/* Ireland Grid */
#define RDm		 		7 			/* Rijksdrihoek (Netherland) */
#define CONLAM2m		8 			/* Conform Lambert Kegel - 2 Parallele */
#define CONLAM1m		9 			/* Conform Lambert Kegel - 1 Parallele */
#define ALBERS_Sm		10 			/* Sphere: Albers - fl攃hentreue Kegel - 2 Parallele */
#define ALBERS_Em		11 			/* Ellipsoid: Albers - fl攃hentreue Kegel - 2 Parallele */
#define OBMERK_SWISSm	12 			/* Oblique Merkator */
#define AUSTRIAm		13			/* Austria - Gauss Krueger */
#define BLAMBERT72_50m	14			/* Belgium Lambert 72/50 */
#define BLAMBERT72m		15			/* Belgium Lambert 72 */
#define EOVm			16			/* Hungary EOV */


/* Transversal Merkator Projectionen */
/*	--- L攏der und Regionen abh攏gig --- */
#define MAXTRANSMERKATORSPHERE 4

#define TMS_USER1p  		1 			/* User definiert */
#define TMS_USER2p  		2 			/* User definiert */
#define TMS_UTMp		3 			/* UTM - n杛dliche Halbkugel */

/*	Based on the ellipsoid */
//edit by jjj 
//#define MAXTRANSMERKATORELL 22
#define MAXTRANSMERKATORELL 23

#define TM_USER1p  		1 			/* User definiert */
#define TM_USER2p  		2 			/* User definiert */
#define TM_UTM_Np		3 			/* UTM - n杛dliche Halbkugel */
#define TM_UTM_Sp		4 			/* UTM - s竏liche Halbkugel */
#define TM_GK_DHDNp		5 			/* Gauss Krueger - 3?breit */
#define TM_GK_PULKp		6 			/* Gauss Krueger - 6?breit */
#define TM_AMGp	 		7 			/* Australian Map Grid */
#define TM_RSAp	 		8 			/* South African */
#define TM_GLUXp		9 			/* Gauss-Luxenburg */
#define TM_CROATIAp		10 			/* CROATIA */
#define TM_CROATIA_CTp	11 			/* Central System: CROATIA */
#define TM_REDp			12 			/* Egypt Red Belt */
#define TM_PURPLEp		13 			/* Egypt Purple Belt */
#define TM_EXT_PURPLEp	14 			/* Egypt Extended Purple Belt */
#define TM_SWEDENp		15 			/* Swedish Grid: RT90 2.5 gon V */
#define TM_AUSTRIAp		16 			/* Bundesmeldenetz - Austria */
#define TM_GAUSSBOGA1p	17 			/* Italy: Gauss-Boaga IGM1940 - Zone 1 */
#define TM_GAUSSBOGA2p	18 			/* Italy: Gauss-Boaga IGM1940 - Zone 2 */
#define TM_UTM_LATVIAp	19 			/* UTM LATVIA */
#define TM_KKJp			20 			/* KKJ Finland */
#define TM_PORTUGALp	21 			/* Portoguese National System */
//add by jjj 2013.7.25
#define TM_UK_NGR		22 			/* UK National Grid Reference*/



/* Albers Projectionen */
/*	--- L攏der und Regionen abh攏gig --- */
#define MAXALBERSSPHERE 4

#define ALS_USER1p  	1 			/* User definiert */
#define ALS_USER2p  	2 			/* User definiert */
#define ALS_800TGERp	3 			/* 1:800T Deutschland */


#define MAXALBERSELL 6

#define AL_USER1p  	1 			/* User definiert */
#define AL_USER2p  	2 			/* User definiert */
#define AL_SAFp		3 			/* S竏 Afrika */
#define AL_SWEDENp	4 			/* Sweden */
#define AL_2MIOAUSTRIAp	5 			/* 1:2Mio Austria */


/* Subarten der Conforme Lambert Projection mit 2 Parallelen (L攏gentreu) */
/*	--- L攏der und Regionen abh攏gig --- */
#define MAXCONLAM2 10

#define CL2_USER1p  			1 		/* User definiert */
#define CL2_USER2p  			2 		/* User definiert */
#define CL2_BELGIENp			3 		/* Belgien */
#define CL2_TPC_H5Ap			4 		/* Flugkarte TPC H-5A */
#define CL2L15P27P63p			5 		/* 1:4Mio Karte f竢 BAPT */
#define CL2L14_5P48_4P51_4p		6 		/* 1:1Mio Karte f竢 BAPT */
#define CL2L10_5P49P56p			7 		/* 1:500T Karte f竢 BAPT */
#define CL2L13_2P46P49p			8 		/* 1:500T Karte f竢 Austria */
#define CL2_AUSTRIAp			9 		/* Austria - Eurokom */

/* Subarten der Conforme Lambert Projection mit 1 Parallelen (L攏gentreu) */
/*	--- L攏der und Regionen abh攏gig --- */
#define MAXCONLAM1 3

#define CL1_USER1p  	1 		/* User definiert */
#define CL1_USER2p  	2 		/* User definiert */


/* Oblique Merkator Projectionen */
/*	--- L攏der und Regionen abh攏gig --- */
#define MAXOBMERK 4

#define OBMERK_USER1p  	1 			/* User definiert */
#define OBMERK_USER2p  	2 			/* User definiert */
#define OBMERK_SWISSp	3 			/* Switzerland */


/* ELLIPSOID Constanten */
#define NOELLIPSOIDe			0
#define	AIRY_1830e				1
#define	MODIFIED_AIRYe			2
#define	AUSTRALIAN_NATIONALe	3
#define	AVER_TERL_SYS_1977e		4
#define	BESSEL_1841e			5
#define	BESSEL_1841_NAMIBIAe	6
#define	BESSEL_DHDNe			7
#define	BESSEL_RT90e			8
#define	BESSEL_NGOe				9
#define	CLARKE_1858e			10
#define	CLARKE_1858_1e			11
#define	CLARKE_1866e			12
#define	CLARKE_1866_MICHIGANe	13
#define	CLARKE_1880e			14
#define	CLARKE_1880_ARC50e		15
#define	CLARKE_1880_IGNe		16
#define	CLARKE_1880_JAMAICAe	17
#define	CLARKE_1880_MERCHICHe	18
#define	CLARKE_1880_PALESTINEe	19
#define	CLARKE_1880_SGA_1922e	20
#define	EVEREST_BRUNEIe			21
#define	EVEREST_TIMBALAIe		22
#define	EVEREST_INDIA_1830e		23
#define	EVEREST_INDIA_1956e		24
#define	EVEREST_1948e			25
#define	EVEREST_1969e			26
#define	EVEREST_PAKISTANe		27
#define	FISCHER_1960e			28
#define	IUGG_67e				29
#define	IUGG_75e				30
#define	KAULAe					31
#define	MOD_FISCHER_1960e		32
#define	FISCHER_1968e			33
#define	GEM_10Ce				34
#define	GRS67e					35
#define	GRS80e					36
#define	HAYFORDe				37
#define	HELMERT_1906e			38
#define	HOUGH_1960e				39
#define	IAG_75e					40
#define	INTERNATIONAL_1924e		41
#define	INDONESIAN_1974e		42
#define	KRASSOVSKY_1940e		43
#define	MERIT_83e				44
#define	NEW_INTERNATIONAL_1967e	45
#define	NWL_9De					46
#define	NWL_10De				47
#define	OSU86Fe					48
#define	OSU91Ae					49
#define	PLESSIS_1817e			50
#define	SGS85e					51
#define	SOUTH_AMERICAN_1969e	52
#define	SOUTHEAST_ASIAe			53
#define	STRUVE_1860e			54
#define	WALBECKe				55
#define	WAR_OFFICEe				56
#define	WGS60e					57
#define	WGS66e					58
#define	WGS72e					59
#define	WGS84e					60
#define USER1e 		61	/* User defined */
#define USER2e 		62	/* User defined */
#define USER3e 		63	/* User defined */
#define USER4e 		64	/* User defined */
#define USER5e 		65	/* User defined */
#define CHINA2000e  66  /*add by CX 2014.12.24*/


/* Methoden fuer den Datumsuebergang */
#define  NONE_DTRANS	0
#define  BURSA_WOLF		1
#define  MOLODONSKIJ	2
#define  TRANS_ROT		3
#define  HELMERT		4

/* Datum Constanten */
/* Methode: Molodenskij */
#define NONEd	0
#define	ADINDAN_BURKINA_FASOd	1
#define	ADINDAN_COMEROONd	2
#define	ADINDAN_ETHIOPIAd	3
#define	ADINDAN_MALId	4
#define	ADINDAN_ETHIOPIA_SUDANd	5
#define	ADINDAN_SENEGALd	6
#define	ADINDAN_SUDANd	7
#define	AFGOOYEd	8
#define	AIN_EL_ABD_1970_BAHRAINd	9
#define	AIN_EL_ABD_1970_SAUDIARABd	10
#define	AMERICAN_SAMOA_1962d	11
#define	ANNA_1_ASTRO_1965d	12
#define	ANTIGUA_ISLAND_ASTRO_1943d	13
#define	ARC_1950_BOTSWANAd	14
#define	ARC_1950_BURUNDId	15
#define	ARC_1950_LESOTHOd	16
#define	ARC_1950_MALAWId	17
#define	ARC_1950_MEANd	18
#define	ARC_1950_SWAZILANDd	19
#define	ARC_1950_ZAIREd	20
#define	ARC_1950_ZAMBIAd	21
#define	ARC_1950_ZIMBABWEd	22
#define	ARC_1960_KENIA_TANZANIAd	23
#define	ARC_1960_KENIAd	24
#define	ARC_1960_TANZANIAd	25
#define	ASCENSION_ISLAND_1958d	26
#define	ASTRO_BEACON_E_1945d	27
#define	ASTRO_DOS_71_4d	28
#define	ASTRO_TERN_ISLAND_FRIG_1961d	29
#define	ASTRONOMICAL_STATION_1952d	30
#define	AUSTRALIAN_GEODETIC_1966d	31
#define	AUSTRALIAN_GEODETIC_1984d	32
#define	AYABELLE_LIGHTHOUSEd	33
#define	BELLEVUE_IGNd	34
#define	BERMUDA_1957d	35
#define	BISSAUd	36
#define	BOGOTA_OBSERVATORYd	37
#define	BUKIT_RIMPAHd	38
#define	CAMP_AREA_ASTROd	39
#define	CAMPO_INCHAUSPEd	40
#define	CANTON_ASTRO_1966d	41
#define	CAPEd	42
#define	CAPE_CANAVERALd	43
#define	CARTHAGEd	44
#define	CHATHAM_ISLAND_ASTRO_1971d	45
#define	CHUA_ASTROd	46
#define	CORREGO_ALEGREd	47
#define	DABOLAd	48
#define	DECEPTION_ISLANDd	49
#define	DJAKARTA_BATAVIAd	50
#define	DOS_1968d	51
#define	EASTER_ISLAND_1967d	52
#define	ESTONIA_COORDINATE_SYSTEM_1937d	53
#define	ED50_CYPRUSd	54
#define	ED50_EGYPTd	55
#define	ED50_CHANNELISLANDSd	56
#define	ED50_ENGLANDd	57
#define	ED50_FINLAND_NORWAYd	58
#define	ED50_GREECEd	59
#define	ED50_IRANd	60
#define	ED50_SARDIANIAd	61
#define	ED50_SICILYd	62
#define	ED50_MALTAd	63
#define	ED50_EUROPEd	64
#define	ED50_CENTRAL_EUROPEd	65
#define	ED50_ARABIAd	66
#define	ED50_PORTUGAL_SPAINd	67
#define	ED50_TUNESIAd	68
#define	EUROPEAN_1979d	69
#define	FORT_THOMAS_1955d	70
#define	GAN_1970d	71
#define	GEODETIC_DATUM_1949d	72
#define	GRACIOSA_BASE_SW_1948d	73
#define	GUAM_1963d	74
#define	GUNUNG_SEGARAd	75
#define	GUX_1_ASTROd	76
#define	HERAT_NORTHd	77
#define	HERMANNSKOGEL_DATUMd	78
#define	HJORSEY_1955d	79
#define	HONG_KONG_1963d	80
#define	HU_TZU_SHANd	81
#define	INDIAN_BANGLADESHd	82
#define	INDIAN_INDIA_NEPALd	83
#define	INDIAN_PAKISTANd	84
#define	INDIAN_1954d	85
#define	INDIAN_1960_CON_SONd	86
#define	INDIAN_1960_VIETNAMd	87
#define	INDIAN_1975d	88
#define	INDONESIAN_1974d	89
#define	IRELAND_1965d	90
#define	ISTS_061_ASTRO_1968d	91
#define	ISTS_073_ASTRO_1969d	92
#define	JOHNSTON_ISLAND_1961d	93
#define	KANDAWALAd	94
#define	KERGUELEN_ISLAND_1949d	95
#define	KERTAU_1948d	96
#define	KUSAIE_ASTRO_1951d	97
#define	KOREAN_GEODETIC_SYSTEMd	98
#define	L_C_5_ASTRO_1961d	99
#define	LEIGONd	100
#define	LIBERIA_1964d	101
#define	LUZON_PHILIPPINESd	102
#define	LUZON_MINDANAOd	103
#define	M_PORALOKOd	104
#define	MAHE_1971d	105
#define	MASSAWAd	106
#define	MERCHICHd	107
#define	MIDWAY_ASTRO_1961d	108
#define	MINNA_CAMEROONd	109
#define	MINNA_NIGERIAd	110
#define	MONTSERRAT_ISLAND_ASTRO_1958d	111
#define	NAHRWAN_OMANd	112
#define	NAHRWAN_SAUDI_ARABIAd	113
#define	NAHRWAN_EMIRATESd	114
#define	NAPARIMA_BWId	115
#define	NAD27_ALASKAd	116
#define	NAD27_ALEUTIAN_EASTd	117
#define	NAD27_ALEUTIAN_WESTd	118
#define	NAD27_BAHAMASd	119
#define	NAD27_SAN_SALVADORd	120
#define	NAD27_CAN_ALBERTAd	121
#define	NAD27_CAN_ONTARIOd	122
#define	NAD27_CAN_QUEBECd	123
#define	NAD27_CAN_NWTERRETORIESd	124
#define	NAD27_CAN_YUKONd	125
#define	NAD27_CANAL_ZONEd	126
#define	NAD27_CUBAd	127
#define	NAD27_GREENLANDd	128
#define	NAD27_CARIBEAN_WESTd	129
#define	NAD27_MIDDLE_AMERIKAd	130
#define	NAD27_CANADAd	131
#define	NAD27_CONUSd	132
#define	NAD27_EAST_MISSISSIPPId	133
#define	NAD27_WEST_MISSISSIPPId	134
#define	NAD27_MEXICOd	135
#define	NAD83_ALASKAd	136
#define	NAD83_ALEUTIANd	137
#define	NAD83_CANADAd	138
#define	NAD83_CONUSd	139
#define	NAD83_HAWAId	140
#define	NAD83_MEXICO_CENTRAL_AMERIKAd	141
#define	NORTH_SAHARA_1959d	142
#define	OBSERVATORIO_METEOROLOGICO_1939d	143
#define	OLD_EGYPTIAN_1907d	144
#define	OLD_HAWAIIAN_HAWAIId	145
#define	OLD_HAWAIIAN_KAUAId	146
#define	OLD_HAWAIIAN_MAUId	147
#define	OLD_HAWAIIANd	148
#define	OLD_HAWAIIAN_OAHUd	149
#define	OMANd	150
#define	GB1936_ENGLANDd	151
#define	GB1936_ENG_WALES_ISLEMANd	152
#define	GB1936_d	153
#define	GB1936_SCOTLAND_SHETLANDd	154
#define	GB1936_WALESd	155
#define	PICO_DE_LAS_NIEVESd	156
#define	PITCAIRN_ASTRO_1967d	157
#define	POINT_58d	158
#define	POINTE_NOIRE_1948d	159
#define	PORTO_SANTO_1936d	160
#define	PROV_S_AMERICAN56_BOLIVIAd	161
#define	PROV_S_AMERICAN56_CHILE_NORTHd	162
#define	PROV_S_AMERICAN56_CHILE_SOUTHd	163
#define	PROV_S_AMERICAN56_COLOMBIAd	164
#define	PROV_S_AMERICAN56_ECUADORd	165
#define	PROV_S_AMERICAN56_GUYANAd	166
#define	PROVISIONAL_SOUTH_AMERICAN_1956d	167
#define	PROV_S_AMERICAN56_PERUd	168
#define	PROV_S_AMERICAN56_VENEZUELAd	169
#define	PROVISIONAL_SOUTH_CHILEAN_1963d	170
#define	PUERTO_RICOd	171
#define	PULKOVO_1942d	172
#define	QATAR_NATIONALd	173
#define	QORNOQd	174
#define	REUNIONd	175
#define	ROME_1940d	176
#define	S42_HUNGARYd	177
#define	S42_POLANDd	178
#define	S42_CZECHOSLOVAKIAd	179
#define	S42_LATVIAd	180
#define	S42_KAZAKHSTANd	181
#define	S42_ALBANIAd	182
#define	S42_ROMANIAd	183
#define	SJTSKd	184
#define	SANTO_DOS_1965d	185
#define	SAO_BRAZd	186
#define	SAPPER_HILL_1943d	187
#define	SCHWARZECKd	188
#define	SELVAGEM_GRANDE_1938d	189
#define	SIERRA_LEONE_1960d	190
#define	S_AMERICAN69_ARGENTINAd	191
#define	S_AMERICAN69_BOLIVIAd	192
#define	S_AMERICAN69_BRAZILd	193
#define	S_AMERICAN69_CHILEd	194
#define	S_AMERICAN69_COLOMBIAd	195
#define	S_AMERICAN69_ECUADORd	196
#define	S_AMERICAN69_BALTRA_GALAPAGOSd	197
#define	S_AMERICAN69_GUYANAd	198
#define	SOUTH_AMERICAN_1969d	199
#define	S_AMERICAN69_PARAGUAYd	200
#define	S_AMERICAN69_PERUd	201
#define	S_AMERICAN69_TINIDAT_TOBAGOd	202
#define	S_AMERICAN69_VENEZUELAd	203
#define	SOUTH_ASIAd	204
#define	TANANARIVE_OBSERVATORY_1925d	205
#define	TIMBALAI_1948d	206
#define	TOKYO_JAPANd	207
#define	TOKYOd	208
#define	TOKYO_OKINAWAd	209
#define	TOKYO_SOUTH_KEREAd	210
#define	TRISTAN_ASTRO_1968d	211
#define	VITI_LEVU_1916d	212
#define	VOIROL_1960d	213
#define	WAKE_ISLAND_ASTRO_1952d	214
#define	WAKE_ENIWETOK_1960d	215
#define	WGS_1972d	216
#define	WGS_1984d	217
#define	YACAREd	218
#define	ZANDERIJd	219
#define	MOZAMBIQUEd	220
#define	DLXd	221
/* Methode: Bursa & Wolf */
#define	AGD84_BWd	301
#define	AMERSFORD_BWd	302
#define	ED1950_LUXEMBOURGd	303
#define	EUROPEAN1950_BWd	304
#define	IGM1940_BWd	305
#define	RT1990_BWd	306
#define	POTSDAM_BWd	307
#define	POTSDAM_AUSTRIAd	308
#define	PULKOVO42_BWd	309
#define	WGS84_BWd	310
#define	HD72_BWd	311
#define	AUSTRIA_AI_BWd	312
#define	KKJ_FINLAND_BWd	313
#define ECS_BCS1954d 314
/* Methode: Helmert 7 Parameter */
#define BD72_7Pd	361
/* Methode: Translation & Rotation */
#define	BERN_CH1903d	401
//增加英国网格Datum add by jjj 2013.7.25
#define	OSGB1936d		402
/* add by CX 2014.12.24 */
#define CHINA2000 403

/* Coordinate Systems */
#define SYS_UNDEF        -1      /*  Absichtlich undefiniert */
#define SYS_GEO           0      /*  Geo */
#define SYS_GK3           1      /*  Gauss-Krueger 3 (L=9)     3?breit */
#define SYS_GK2           2      /*  Gauss-Krueger 2 (L=6)     3?breit */
#define SYS_GK4           3      /*  Gauss-Krueger 4 (L=12)    3?breit */
#define SYS_UTM32_ED50    4      /*  UTM 32 Hayford Ell. */
#define SYS_UTM31_ED50    5      /*  UTM 31 Hayford Ell. */
#define SYS_UTM33_ED50    6      /*  UTM 33 Hayford Ell. */
#define SYS_UTM37_ED50    7      /*  UTM 37 Hayford Ell. */
#define SYS_UTM18_ED50    8      /*  UTM 18 Hayford Ell. */
#define SYS_UTM29_ED50    9      /*  UTM 29 Hayford Ell. */
#define SYS_UTM56_ED50   10      /*  UTM 56 Hayford Ell. */
#define SYS_GK10         11      /*  Gauss-Krueger 10 (L=30)   3?breit */
#define SYS_GK7          12      /*  Gauss-Krueger 7  (L=21)   3?breit */
#define SYS_UTM36_ED50   13      /*  UTM 36 Hayford Ell. */
#define SYS_GK12         14      /*  Gauss-Krueger 12 (L=36)   3?breit */
#define SYS_GK5          15      /*  Gauss-Krueger 5 (L=15)    3?breit */
#define SYS_UTM34_ED50   16      /*  UTM 34 Hayford Ell.  */
#define SYS_UTM49_ED50   17      /*  UTM 49 Hayford Ell.  */
#define SYS_UTM51_ED50   18      /*  UTM 51 Hayford Ell.  */
#define SYS_GK3_6        19      /*  Gauss-Krueger 3 (L=15)    6?breit  */
#define SYS_GK4_6        20      /*  Gauss-Krueger 4 (L=21)    6?breit  */
#define SYS_IRE          21      /*  Ireland Grid */
#define SYS_RD           22      /*  Rijksdrihoek co杛dinaten (Niederlande) */
#define SYS_GK19_6       23      /*  Gauss-Krueger 19 (L=111)  6?breit  */
#define SYS_GK20_6       24      /*  Gauss-Krueger 20 (L=117)  6?breit  */
#define SYS_GK6_6        25      /*  Gauss-Krueger 6  (L=33)   6?breit  */
#define SYS_UTM38_WGS84  26      /*  UTM 38  WGS84 */
#define SYS_Frei27       27      /*  FREI */
#define SYS_GK13_6       28      /*  Gauss-Krueger 13 (L=75)    6?breit  */
#define SYS_AMG49        29      /*  AMG 49  AGD */
#define SYS_AMG50        30      /*  AMG 50  AGD */
#define SYS_AMG51        31      /*  AMG 51  AGD */
#define SYS_AMG52        32      /*  AMG 52  AGD */
#define SYS_AMG53        33      /*  AMG 53  AGD */
#define SYS_AMG54        34      /*  AMG 54  AGD */
#define SYS_AMG55        35      /*  AMG 55  AGD */
#define SYS_AMG56        36      /*  AMG 56  AGD */
#define SYS_AMG57        37      /*  AMG 57  AGD */
#define SYS_UTM30_ED50   38      /*  UTM 30 Hayford Ell.  */
#define SYS_UTM49_WGS84  39      /*  UTM 49  WGS84 */
#define SYS_UTM50_WGS84  40      /*  UTM 50  WGS84 */
#define SYS_UTM51_WGS84  41      /*  UTM 51  WGS84 */
#define SYS_UTM52_WGS84  42      /*  UTM 52  WGS84 */
#define SYS_UTM53_WGS84  43      /*  UTM 53  WGS84 */
#define SYS_UTM54_WGS84  44      /*  UTM 54  WGS84 */
#define SYS_UTM55_WGS84  45      /*  UTM 55  WGS84 */
#define SYS_UTM56_WGS84  46      /*  UTM 56  WGS84 */
#define SYS_UTM57_WGS84  47      /*  UTM 57  WGS84 */
#define SYS_UTM36_CAPE   48      /*  UTM 36  CAPE (Clarke1880) */
#define SYS_UTM36_CL1866 49      /*  UTM 36  (Clarke1866) */
#define SYS_Frei50       50      /*  FREI */
#define SYS_UTM31_WGS84  51      /*  UTM 31  WGS84 */
#define SYS_UTM32_WGS84  52      /*  UTM 32  WGS84 */
#define SYS_UTM33_WGS84  53      /*  UTM 33  WGS84 */
#define SYS_UTM34_WGS84  54      /*  UTM 34  WGS84 */
#define SYS_UTM35_WGS84  55      /*  UTM 35  WGS84 */
#define SYS_UTM36_WGS84  56      /*  UTM 36  WGS84 */
#define SYS_UTM37_WGS84  57      /*  UTM 37  WGS84 */
#define SYS_Frei58       58      /*  FREI */
#define SYS_UTM39_WGS84  59      /*  UTM 39  WGS84 */
#define SYS_AlbersSAF    60      /*  Albers Suedafrika CAPE6 */
#define SYS_Lo13         61      /*  Lo 13 CAPE */
#define SYS_Lo15         62      /*  Lo 15 CAPE */
#define SYS_Lo17         63      /*  Lo 17 CAPE */
#define SYS_Lo19         64      /*  Lo 19 CAPE */
#define SYS_Lo21         65      /*  Lo 21 CAPE */
#define SYS_Lo23         66      /*  Lo 23 CAPE */
#define SYS_Lo25         67      /*  Lo 25 CAPE */
#define SYS_Lo27         68      /*  Lo 27 CAPE */
#define SYS_Lo29         69      /*  Lo 29 CAPE */
#define SYS_Lo31         70      /*  Lo 31 CAPE */
#define SYS_Lo33         71      /*  Lo 33 CAPE */
#define SYS_Lo35         72      /*  Lo 33 CAPE */
#define SYS_CROATIA_15       	                     73      /*  TM Croatia L=15?Croatia_d */
#define SYS_CROATIA_CENTRAL       	                 74      /*  TM Central Croatia L=16.5?Croatia_d */
#define SYS_CROATIA_18       	                     75      /*  TM Croatia L=15?Croatia_d */
#define SYS_CROATIA_21       	                     76      /*  TM Croatia L=15?Croatia_d */
#define SYS_RED_BELT       	                         77      /*  Egypt: Red Belt European1950_Egypt_d */
#define SYS_PURPLE_BELT       	                     78      /*  Egypt: Purple Belt European1950_Egypt_d */
#define SYS_EXT_PURPLE_BELT          	             79      /*  Egypt: Extended Purple Belt European1950_Egypt_d */
#define SYS_CL2_TPC_H5A_WGS84          	             80      /*  TPC_H5A	Flight Map  */
#define SYS_CL2L15P27P63_ED50          	             81      /*  1:4Mio Confom Lambert  f竢 BAPT */
#define SYS_CL2L14_5P48_4P51_4_ED50          	     82      /*  1:1Mio Confom Lambert  f竢 BAPT */
#define SYS_CL2L10_5P49P56_ED50          	         83      /*  1:500T Confom Lambert  f竢 BAPT */
#define SYS_Swiss_CH1903		          	         84      /*  Schweizer Landesprojection */
#define SYS_RT90_SWEDEN		          	             85      /*  RT90 2.5 gon V - Schweden */
#define SYS_ALBL15_8P50P70_SWEDEN		          	 86      /*  Alberssystem - Schweden */
#define SYS_M28_AUSTRIA		          	             87      /*  M28 - Austria */
#define SYS_M31_AUSTRIA		          	             88      /*  M31 - Austria */
#define SYS_M34_AUSTRIA		          	             89      /*  M34 - Austria */
#define SYS_M28_M34_AUSTRIA		          	         90      /*  M28, M31, M34 - Bundesmeldenetz - Austria */
#define SYS_CL2L13_2P46P49_AUSTRIA		          	 91      /*  1:500T Conform Lambert - Austria */
#define SYS_GLUX_ED50	                             92	     /*  Gauss Luxembourg (Luxembourg) */
#define SYS_2MIOAUSTRIA_ED50	                     93	     /*  1:2Mio Austria (ED 50) */
#define SYS_800TGER_WGS84	                     	94	     /*  1:800T Deutschland (WGS 84) */
#define SYS_UTM32_N_Sphere							95	/* UTM 32 - Northern Hemisphere  Sphere*/
#define SYS_GAUSS_BOAGA_1							96	/* Italy: Gauss-Boaga IGM1940 - Zone 1 */
#define SYS_GAUSS_BOAGA_2							97	/* Italy: Gauss-Boaga IGM1940 - Zone 2 */
#define SYS_UTM17_NAD27_ONTARIO						98	/* UTM17 - NAD27 Ontario */
#define SYS_UTM18_NAD27_QUEBEC						99	/* UTM17 - NAD27 Quebec */
#define SYS_GEO_NODTRANS 				100 			/* No Datumstransformation */
#define SYS_GEO_USER1 					101 			/* User definiert */
#define SYS_GEO_USER2 					102 			/* User definiert */
#define SYS_GEO_WGS84						103 			/* World Geodetic System */
#define SYS_GEO_DHDN						104 			/* Deutsches Hauptdreiecksnetz */
#define SYS_GEO_ED50						105 			/* Europ攊sches Datum 1950 */
#define SYS_GEO_PULKOVO					106 			/* Ehemalige Soviet-Union */
#define SYS_GEO_AGD							107 			/* Australien Geodetic Datum 1966 */
#define SYS_GEO_CAPE						108 			/* Cape - S竏 Afrika */
#define SYS_GEO_NAD27						109 			/* North American Datum */
#define SYS_GEO_CH1903					110 			/* Schweizer Datum */
#define SYS_GEO_SWEDEN					111 			/* Schedisches Datum */
#define SYS_GEO_AUSTRIA					112 			/* 鱯terreichisches Datum */
#define SYS_GEO_LUXEMBOURG				113 			/* Luxembourger Datum */
#define SYS_GEO_NETHERLANDS				114 			/* Netherlands - Amersford */
#define SYS_GEO_CROATIA					115 			/* Croatia Bessel 1841 */
#define SYS_GEO_IGM1940					116 			/* Italy: IGM1940 Rome M.Mario */
#define SYS_GEO_IRELAND					117 			/* Ireland 1965 */
#define SYS_GEO_EGYPT					118 			/* Egypt: European Datum 1950 */
#define SYS_GEO_NAD27_ONTARIO			119 			/* NAD27 Ontario */
#define SYS_GEO_NAD27_QUEBEC			120 			/* NAD27 Quebec */
#define SYS_GEO_AINELABD_BAHRAIN		121 			/* Ain El Abd Bahrain */
#define SYS_GEO_ED50_BELGIUM			122 			/* ED50 Belgium */
#define SYS_GEO_HD72					123 			/* Hangary: HD72 */
#define SYS_GEO_KKJ_FINLAND				124 			/* KKJ Finland */
#define SYS_GEO_DLX						125 			/* DLx - Portugal */

//////////////////////////////////////////////////////////////////////////
//add by jjj 2012.9.28 北京1954 6度坐标系
/* Gauss Kruger (PULKOVO) */
#define SYS_GK13_PULKOVO_BCS1954d		130	/* Gauss Kruger BCS1954d 13 (PULKOVO) */
#define SYS_GK14_PULKOVO_BCS1954d		131	/* Gauss Kruger BCS1954d 14 (PULKOVO) */
#define SYS_GK15_PULKOVO_BCS1954d		132	/* Gauss Kruger BCS1954d 15 (PULKOVO) */
#define SYS_GK16_PULKOVO_BCS1954d		133	/* Gauss Kruger BCS1954d 16 (PULKOVO) */
#define SYS_GK17_PULKOVO_BCS1954d		134	/* Gauss Kruger BCS1954d 17 (PULKOVO) */
#define SYS_GK18_PULKOVO_BCS1954d		135	/* Gauss Kruger BCS1954d 18 (PULKOVO) */
#define SYS_GK19_PULKOVO_BCS1954d		136	/* Gauss Kruger BCS1954d 19 (PULKOVO) */
#define SYS_GK20_PULKOVO_BCS1954d		137	/* Gauss Kruger BCS1954d 20 (PULKOVO) */
#define SYS_GK21_PULKOVO_BCS1954d		138	/* Gauss Kruger BCS1954d 21 (PULKOVO) */
#define SYS_GK22_PULKOVO_BCS1954d		139	/* Gauss Kruger BCS1954d 22 (PULKOVO) */
#define SYS_GK23_PULKOVO_BCS1954d		140	/* Gauss Kruger BCS1954d 23 (PULKOVO) */

#define SYS_LAMBERT_BCS1954d			143	/* Lambert ECS_China BCS1954*/
//////////////////////////////////////////////////////////////////////////


#define SYS_UTM39_N_AINELABD_BAHRAIN	149				/* UTM 39 (Ain el Abd Bahrain) */
#define SYS_BELGIUM_LAMBERT72_50		155				/* Belgium Lambert 72/50 */
#define SYS_BELGIUM_LAMBERT72			156				/* Belgium Lambert 72 */
#define SYS_EOV							157 			/* Hungary: EOV */
#define SYS_CL2_AUSTRIA					158 			/* Austria Lambert - Eurokom */
#define SYS_UTM_LATVIA					159 			/* UTM Latvia - Central Meridian 24?*/
#define SYS_Gauss_DLX					160 			/* Protoguese National System - DLx */
/* UTM WGS 84 */
#define SYS_UTM01_N_WGS84	201	/* UTM 1 - Northern Hemisphere (WGS 84) */
#define SYS_UTM02_N_WGS84	202	/* UTM 2 - Northern Hemisphere (WGS 84) */
#define SYS_UTM03_N_WGS84	203	/* UTM 3 - Northern Hemisphere (WGS 84) */
#define SYS_UTM04_N_WGS84	204	/* UTM 4 - Northern Hemisphere (WGS 84) */
#define SYS_UTM05_N_WGS84	205	/* UTM 5 - Northern Hemisphere (WGS 84) */
#define SYS_UTM06_N_WGS84	206	/* UTM 6 - Northern Hemisphere (WGS 84) */
#define SYS_UTM07_N_WGS84	207	/* UTM 7 - Northern Hemisphere (WGS 84) */
#define SYS_UTM08_N_WGS84	208	/* UTM 8 - Northern Hemisphere (WGS 84) */
#define SYS_UTM09_N_WGS84	209	/* UTM 9 - Northern Hemisphere (WGS 84) */
#define SYS_UTM10_N_WGS84	210	/* UTM 10 - Northern Hemisphere (WGS 84) */
#define SYS_UTM11_N_WGS84	211	/* UTM 11 - Northern Hemisphere (WGS 84) */
#define SYS_UTM12_N_WGS84	212	/* UTM 12 - Northern Hemisphere (WGS 84) */
#define SYS_UTM13_N_WGS84	213	/* UTM 13 - Northern Hemisphere (WGS 84) */
#define SYS_UTM14_N_WGS84	214	/* UTM 14 - Northern Hemisphere (WGS 84) */
#define SYS_UTM15_N_WGS84	215	/* UTM 15 - Northern Hemisphere (WGS 84) */
#define SYS_UTM16_N_WGS84	216	/* UTM 16 - Northern Hemisphere (WGS 84) */
#define SYS_UTM17_N_WGS84	217	/* UTM 17 - Northern Hemisphere (WGS 84) */
#define SYS_UTM18_N_WGS84	218	/* UTM 18 - Northern Hemisphere (WGS 84) */
#define SYS_UTM19_N_WGS84	219	/* UTM 19 - Northern Hemisphere (WGS 84) */
#define SYS_UTM20_N_WGS84	220	/* UTM 20 - Northern Hemisphere (WGS 84) */
#define SYS_UTM21_N_WGS84	221	/* UTM 21 - Northern Hemisphere (WGS 84) */
#define SYS_UTM22_N_WGS84	222	/* UTM 22 - Northern Hemisphere (WGS 84) */
#define SYS_UTM23_N_WGS84	223	/* UTM 23 - Northern Hemisphere (WGS 84) */
#define SYS_UTM24_N_WGS84	224	/* UTM 24 - Northern Hemisphere (WGS 84) */
#define SYS_UTM25_N_WGS84	225	/* UTM 25 - Northern Hemisphere (WGS 84) */
#define SYS_UTM26_N_WGS84	226	/* UTM 26 - Northern Hemisphere (WGS 84) */
#define SYS_UTM27_N_WGS84	227	/* UTM 27 - Northern Hemisphere (WGS 84) */
#define SYS_UTM28_N_WGS84	228	/* UTM 28 - Northern Hemisphere (WGS 84) */
#define SYS_UTM29_N_WGS84	229	/* UTM 29 - Northern Hemisphere (WGS 84) */
#define SYS_UTM30_N_WGS84	230	/* UTM 30 - Northern Hemisphere (WGS 84) */
#define SYS_UTM31_N_WGS84	231	/* UTM 31 - Northern Hemisphere (WGS 84) */
#define SYS_UTM32_N_WGS84	232	/* UTM 32 - Northern Hemisphere (WGS 84) */
#define SYS_UTM33_N_WGS84	233	/* UTM 33 - Northern Hemisphere (WGS 84) */
#define SYS_UTM34_N_WGS84	234	/* UTM 34 - Northern Hemisphere (WGS 84) */
#define SYS_UTM35_N_WGS84	235	/* UTM 35 - Northern Hemisphere (WGS 84) */
#define SYS_UTM36_N_WGS84	236	/* UTM 36 - Northern Hemisphere (WGS 84) */
#define SYS_UTM37_N_WGS84	237	/* UTM 37 - Northern Hemisphere (WGS 84) */
#define SYS_UTM38_N_WGS84	238	/* UTM 38 - Northern Hemisphere (WGS 84) */
#define SYS_UTM39_N_WGS84	239	/* UTM 39 - Northern Hemisphere (WGS 84) */
#define SYS_UTM40_N_WGS84	240	/* UTM 40 - Northern Hemisphere (WGS 84) */
#define SYS_UTM41_N_WGS84	241	/* UTM 41 - Northern Hemisphere (WGS 84) */
#define SYS_UTM42_N_WGS84	242	/* UTM 42 - Northern Hemisphere (WGS 84) */
#define SYS_UTM43_N_WGS84	243	/* UTM 43 - Northern Hemisphere (WGS 84) */
#define SYS_UTM44_N_WGS84	244	/* UTM 44 - Northern Hemisphere (WGS 84) */
#define SYS_UTM45_N_WGS84	245	/* UTM 45 - Northern Hemisphere (WGS 84) */
#define SYS_UTM46_N_WGS84	246	/* UTM 46 - Northern Hemisphere (WGS 84) */
#define SYS_UTM47_N_WGS84	247	/* UTM 47 - Northern Hemisphere (WGS 84) */
#define SYS_UTM48_N_WGS84	248	/* UTM 48 - Northern Hemisphere (WGS 84) */
#define SYS_UTM49_N_WGS84	249	/* UTM 49 - Northern Hemisphere (WGS 84) */
#define SYS_UTM50_N_WGS84	250	/* UTM 50 - Northern Hemisphere (WGS 84) */
#define SYS_UTM51_N_WGS84	251	/* UTM 51 - Northern Hemisphere (WGS 84) */
#define SYS_UTM52_N_WGS84	252	/* UTM 52 - Northern Hemisphere (WGS 84) */
#define SYS_UTM53_N_WGS84	253	/* UTM 53 - Northern Hemisphere (WGS 84) */
#define SYS_UTM54_N_WGS84	254	/* UTM 54 - Northern Hemisphere (WGS 84) */
#define SYS_UTM55_N_WGS84	255	/* UTM 55 - Northern Hemisphere (WGS 84) */
#define SYS_UTM56_N_WGS84	256	/* UTM 56 - Northern Hemisphere (WGS 84) */
#define SYS_UTM57_N_WGS84	257	/* UTM 57 - Northern Hemisphere (WGS 84) */
#define SYS_UTM58_N_WGS84	258	/* UTM 58 - Northern Hemisphere (WGS 84) */
#define SYS_UTM59_N_WGS84	259	/* UTM 59 - Northern Hemisphere (WGS 84) */
#define SYS_UTM60_N_WGS84	260	/* UTM 60 - Northern Hemisphere (WGS 84) */

#define SYS_UTM01_S_WGS84	261	/* UTM 1 - Southern Hemisphere (WGS 84) */
#define SYS_UTM02_S_WGS84	262	/* UTM 2 - Southern Hemisphere (WGS 84) */
#define SYS_UTM03_S_WGS84	263	/* UTM 3 - Southern Hemisphere (WGS 84) */
#define SYS_UTM04_S_WGS84	264	/* UTM 4 - Southern Hemisphere (WGS 84) */
#define SYS_UTM05_S_WGS84	265	/* UTM 5 - Southern Hemisphere (WGS 84) */
#define SYS_UTM06_S_WGS84	266	/* UTM 6 - Southern Hemisphere (WGS 84) */
#define SYS_UTM07_S_WGS84	267	/* UTM 7 - Southern Hemisphere (WGS 84) */
#define SYS_UTM08_S_WGS84	268	/* UTM 8 - Southern Hemisphere (WGS 84) */
#define SYS_UTM09_S_WGS84	269	/* UTM 9 - Southern Hemisphere (WGS 84) */
#define SYS_UTM10_S_WGS84	270	/* UTM 10 - Southern Hemisphere (WGS 84) */
#define SYS_UTM11_S_WGS84	271	/* UTM 11 - Southern Hemisphere (WGS 84) */
#define SYS_UTM12_S_WGS84	272	/* UTM 12 - Southern Hemisphere (WGS 84) */
#define SYS_UTM13_S_WGS84	273	/* UTM 13 - Southern Hemisphere (WGS 84) */
#define SYS_UTM14_S_WGS84	274	/* UTM 14 - Southern Hemisphere (WGS 84) */
#define SYS_UTM15_S_WGS84	275	/* UTM 15 - Southern Hemisphere (WGS 84) */
#define SYS_UTM16_S_WGS84	276	/* UTM 16 - Southern Hemisphere (WGS 84) */
#define SYS_UTM17_S_WGS84	277	/* UTM 17 - Southern Hemisphere (WGS 84) */
#define SYS_UTM18_S_WGS84	278	/* UTM 18 - Southern Hemisphere (WGS 84) */
#define SYS_UTM19_S_WGS84	279	/* UTM 19 - Southern Hemisphere (WGS 84) */
#define SYS_UTM20_S_WGS84	280	/* UTM 20 - Southern Hemisphere (WGS 84) */
#define SYS_UTM21_S_WGS84	281	/* UTM 21 - Southern Hemisphere (WGS 84) */
#define SYS_UTM22_S_WGS84	282	/* UTM 22 - Southern Hemisphere (WGS 84) */
#define SYS_UTM23_S_WGS84	283	/* UTM 23 - Southern Hemisphere (WGS 84) */
#define SYS_UTM24_S_WGS84	284	/* UTM 24 - Southern Hemisphere (WGS 84) */
#define SYS_UTM25_S_WGS84	285	/* UTM 25 - Southern Hemisphere (WGS 84) */
#define SYS_UTM26_S_WGS84	286	/* UTM 26 - Southern Hemisphere (WGS 84) */
#define SYS_UTM27_S_WGS84	287	/* UTM 27 - Southern Hemisphere (WGS 84) */
#define SYS_UTM28_S_WGS84	288	/* UTM 28 - Southern Hemisphere (WGS 84) */
#define SYS_UTM29_S_WGS84	289	/* UTM 29 - Southern Hemisphere (WGS 84) */
#define SYS_UTM30_S_WGS84	290	/* UTM 30 - Southern Hemisphere (WGS 84) */
#define SYS_UTM31_S_WGS84	291	/* UTM 31 - Southern Hemisphere (WGS 84) */
#define SYS_UTM32_S_WGS84	292	/* UTM 32 - Southern Hemisphere (WGS 84) */
#define SYS_UTM33_S_WGS84	293	/* UTM 33 - Southern Hemisphere (WGS 84) */
#define SYS_UTM34_S_WGS84	294	/* UTM 34 - Southern Hemisphere (WGS 84) */
#define SYS_UTM35_S_WGS84	295	/* UTM 35 - Southern Hemisphere (WGS 84) */
#define SYS_UTM36_S_WGS84	296	/* UTM 36 - Southern Hemisphere (WGS 84) */
#define SYS_UTM37_S_WGS84	297	/* UTM 37 - Southern Hemisphere (WGS 84) */
#define SYS_UTM38_S_WGS84	298	/* UTM 38 - Southern Hemisphere (WGS 84) */
#define SYS_UTM39_S_WGS84	299	/* UTM 39 - Southern Hemisphere (WGS 84) */
#define SYS_UTM40_S_WGS84	300	/* UTM 40 - Southern Hemisphere (WGS 84) */
#define SYS_UTM41_S_WGS84	301	/* UTM 41 - Southern Hemisphere (WGS 84) */
#define SYS_UTM42_S_WGS84	302	/* UTM 42 - Southern Hemisphere (WGS 84) */
#define SYS_UTM43_S_WGS84	303	/* UTM 43 - Southern Hemisphere (WGS 84) */
#define SYS_UTM44_S_WGS84	304	/* UTM 44 - Southern Hemisphere (WGS 84) */
#define SYS_UTM45_S_WGS84	305	/* UTM 45 - Southern Hemisphere (WGS 84) */
#define SYS_UTM46_S_WGS84	306	/* UTM 46 - Southern Hemisphere (WGS 84) */
#define SYS_UTM47_S_WGS84	307	/* UTM 47 - Southern Hemisphere (WGS 84) */
#define SYS_UTM48_S_WGS84	308	/* UTM 48 - Southern Hemisphere (WGS 84) */
#define SYS_UTM49_S_WGS84	309	/* UTM 49 - Southern Hemisphere (WGS 84) */
#define SYS_UTM50_S_WGS84	310	/* UTM 50 - Southern Hemisphere (WGS 84) */
#define SYS_UTM51_S_WGS84	311	/* UTM 51 - Southern Hemisphere (WGS 84) */
#define SYS_UTM52_S_WGS84	312	/* UTM 52 - Southern Hemisphere (WGS 84) */
#define SYS_UTM53_S_WGS84	313	/* UTM 53 - Southern Hemisphere (WGS 84) */
#define SYS_UTM54_S_WGS84	314	/* UTM 54 - Southern Hemisphere (WGS 84) */
#define SYS_UTM55_S_WGS84	315	/* UTM 55 - Southern Hemisphere (WGS 84) */
#define SYS_UTM56_S_WGS84	316	/* UTM 56 - Southern Hemisphere (WGS 84) */
#define SYS_UTM57_S_WGS84	317	/* UTM 57 - Southern Hemisphere (WGS 84) */
#define SYS_UTM58_S_WGS84	318	/* UTM 58 - Southern Hemisphere (WGS 84) */
#define SYS_UTM59_S_WGS84	319	/* UTM 59 - Southern Hemisphere (WGS 84) */
#define SYS_UTM60_S_WGS84	320	/* UTM 60 - Southern Hemisphere (WGS 84) */

/* UTM (ED 50) */
#define SYS_UTM28_N_ED50	328	/* UTM 28 - Northern Hemisphere (ED 50) */
#define SYS_UTM29_N_ED50	329	/* UTM 29 - Northern Hemisphere (ED 50) */
#define SYS_UTM30_N_ED50	330	/* UTM 30 - Northern Hemisphere (ED 50) */
#define SYS_UTM31_N_ED50	331	/* UTM 31 - Northern Hemisphere (ED 50) */
#define SYS_UTM32_N_ED50	332	/* UTM 32 - Northern Hemisphere (ED 50) */
#define SYS_UTM33_N_ED50	333	/* UTM 33 - Northern Hemisphere (ED 50) */
#define SYS_UTM34_N_ED50	334	/* UTM 34 - Northern Hemisphere (ED 50) */
#define SYS_UTM35_N_ED50	335	/* UTM 35 - Northern Hemisphere (ED 50) */
#define SYS_UTM36_N_ED50	336	/* UTM 36 - Northern Hemisphere (ED 50) */
#define SYS_UTM37_N_ED50	337	/* UTM 37 - Northern Hemisphere (ED 50) */
#define SYS_UTM38_N_ED50	338	/* UTM 38 - Northern Hemisphere (ED 50) */

/* Gauss Kruger (DHDN) */
#define SYS_KKJ1			341	/* KKJ Zone 1 (ED 50) */
#define SYS_KKJ2			342	/* KKJ Zone 2 (ED 50) */
#define SYS_KKJ3			343	/* KKJ Zone 3 (ED 50) */
#define SYS_KKJ4			344	/* KKJ Zone 4 (ED 50) */

/* Gauss Kruger (DHDN) */
#define SYS_GK1_DHDN		351	/* Gauss Kruger 1 (DHDN) */
#define SYS_GK2_DHDN		352	/* Gauss Kruger 2 (DHDN) */
#define SYS_GK3_DHDN		353	/* Gauss Kruger 3 (DHDN) */
#define SYS_GK4_DHDN		354	/* Gauss Kruger 4 (DHDN) */
#define SYS_GK5_DHDN		355	/* Gauss Kruger 5 (DHDN) */

/* Gauss Kruger (PULKOVO) */
#define SYS_GK01_PULKOVO		361	/* Gauss Kruger 1 (PULKOVO) */
#define SYS_GK02_PULKOVO		362	/* Gauss Kruger 2 (PULKOVO) */
#define SYS_GK03_PULKOVO		363	/* Gauss Kruger 3 (PULKOVO) */
#define SYS_GK04_PULKOVO		364	/* Gauss Kruger 4 (PULKOVO) */
#define SYS_GK05_PULKOVO		365	/* Gauss Kruger 5 (PULKOVO) */
#define SYS_GK06_PULKOVO		366	/* Gauss Kruger 6 (PULKOVO) */
#define SYS_GK07_PULKOVO		367	/* Gauss Kruger 7 (PULKOVO) */
#define SYS_GK08_PULKOVO		368	/* Gauss Kruger 8 (PULKOVO) */
#define SYS_GK09_PULKOVO		369	/* Gauss Kruger 9 (PULKOVO) */
#define SYS_GK10_PULKOVO		370	/* Gauss Kruger 10 (PULKOVO) */
#define SYS_GK11_PULKOVO		371	/* Gauss Kruger 11 (PULKOVO) */
#define SYS_GK12_PULKOVO		372	/* Gauss Kruger 12 (PULKOVO) */
#define SYS_GK13_PULKOVO		373	/* Gauss Kruger 13 (PULKOVO) */
#define SYS_GK14_PULKOVO		374	/* Gauss Kruger 14 (PULKOVO) */
#define SYS_GK15_PULKOVO		375	/* Gauss Kruger 15 (PULKOVO) */
#define SYS_GK16_PULKOVO		376	/* Gauss Kruger 16 (PULKOVO) */
#define SYS_GK17_PULKOVO		377	/* Gauss Kruger 17 (PULKOVO) */
#define SYS_GK18_PULKOVO		378	/* Gauss Kruger 18 (PULKOVO) */
#define SYS_GK19_PULKOVO		379	/* Gauss Kruger 19 (PULKOVO) */
#define SYS_GK20_PULKOVO		380	/* Gauss Kruger 20 (PULKOVO) */
#define SYS_GK21_PULKOVO		381	/* Gauss Kruger 21 (PULKOVO) */
#define SYS_GK22_PULKOVO		382	/* Gauss Kruger 22 (PULKOVO) */
#define SYS_GK23_PULKOVO		383	/* Gauss Kruger 23 (PULKOVO) */
#define SYS_GK24_PULKOVO		384	/* Gauss Kruger 24 (PULKOVO) */
#define SYS_GK25_PULKOVO		385	/* Gauss Kruger 25 (PULKOVO) */
#define SYS_GK26_PULKOVO		386	/* Gauss Kruger 26 (PULKOVO) */
#define SYS_GK27_PULKOVO		387	/* Gauss Kruger 27 (PULKOVO) */
#define SYS_GK28_PULKOVO		388	/* Gauss Kruger 28 (PULKOVO) */
#define SYS_GK29_PULKOVO		389	/* Gauss Kruger 29 (PULKOVO) */
#define SYS_GK30_PULKOVO		390	/* Gauss Kruger 30 (PULKOVO) */
#define SYS_GK31_PULKOVO		391	/* Gauss Kruger 31 (PULKOVO) */
#define SYS_GK32_PULKOVO		392	/* Gauss Kruger 32 (PULKOVO) */

/* UTM (NAD27 US) */
#define	SYS_UTM1_N_NAD27_ALASKA	401
#define	SYS_UTM2_N_NAD27_ALASKA	402
#define	SYS_UTM3_N_NAD27_ALASKA	403
#define	SYS_UTM4_N_NAD27_ALASKA	404
#define	SYS_UTM5_N_NAD27_ALASKA	405
#define	SYS_UTM6_N_NAD27_ALASKA	406
#define	SYS_UTM7_N_NAD27_ALASKA	407
#define	SYS_UTM8_N_NAD27_ALASKA	408
#define	SYS_UTM9_N_NAD27_ALASKA	409
#define	SYS_UTM10_N_NAD27_CENTRAL	410
#define	SYS_UTM11_N_NAD27_CENTRAL	411
#define	SYS_UTM12_N_NAD27_CENTRAL	412
#define	SYS_UTM13_N_NAD27_CENTRAL	413
#define	SYS_UTM14_N_NAD27_CENTRAL	414
#define	SYS_UTM15_N_NAD27_CENTRAL	415
#define	SYS_UTM16_N_NAD27_CENTRAL	416
#define	SYS_UTM17_N_NAD27_CENTRAL	417
#define	SYS_UTM18_N_NAD27_CENTRAL	418
#define	SYS_UTM19_N_NAD27_CENTRAL	419

/* UTM (NAD27 Mexico) */
#define	SYS_UTM10_N_NAD27_MEXICO	420
#define	SYS_UTM11_N_NAD27_MEXICO	421
#define	SYS_UTM12_N_NAD27_MEXICO	422
#define	SYS_UTM13_N_NAD27_MEXICO	423
#define	SYS_UTM14_N_NAD27_MEXICO	424
#define	SYS_UTM15_N_NAD27_MEXICO	425
#define	SYS_UTM16_N_NAD27_MEXICO	426

/* UTM (NAD27 Canada) */
#define	SYS_UTM7_N_NAD27_CANADA	437
#define	SYS_UTM8_N_NAD27_CANADA	438
#define	SYS_UTM9_N_NAD27_CANADA	439
#define	SYS_UTM10_N_NAD27_CANADA	440
#define	SYS_UTM11_N_NAD27_CANADA	441
#define	SYS_UTM12_N_NAD27_CANADA	442
#define	SYS_UTM13_N_NAD27_CANADA	443
#define	SYS_UTM14_N_NAD27_CANADA	444
#define	SYS_UTM15_N_NAD27_CANADA	445
#define	SYS_UTM16_N_NAD27_CANADA	446
#define	SYS_UTM17_N_NAD27_CANADA	447
#define	SYS_UTM18_N_NAD27_CANADA	448
#define	SYS_UTM19_N_NAD27_CANADA	449
#define	SYS_UTM20_N_NAD27_CANADA	450
#define	SYS_UTM21_N_NAD27_CANADA	451
#define	SYS_UTM22_N_NAD27_CANADA	452
#define	SYS_UTM23_N_NAD27_CANADA	453
#define	SYS_UTM24_N_NAD27_CANADA	454
#define	SYS_UTM25_N_NAD27_CANADA	455
#define	SYS_UTM26_N_NAD27_CANADA	456
#define	SYS_UTM27_N_NAD27_CANADA	457
#define	SYS_UTM28_N_NAD27_CANADA	458
#define	SYS_UTM29_N_NAD27_CANADA	459

/* UTM (NAD83) */
#define	SYS_UTM1_N_NAD83	461
#define	SYS_UTM2_N_NAD83	462
#define	SYS_UTM3_N_NAD83	463
#define	SYS_UTM4_N_NAD83	464
#define	SYS_UTM5_N_NAD83	465
#define	SYS_UTM6_N_NAD83	466
#define	SYS_UTM7_N_NAD83	467
#define	SYS_UTM8_N_NAD83	468
#define	SYS_UTM9_N_NAD83	469
#define	SYS_UTM10_N_NAD83	470
#define	SYS_UTM11_N_NAD83	471
#define	SYS_UTM12_N_NAD83	472
#define	SYS_UTM13_N_NAD83	473
#define	SYS_UTM14_N_NAD83	474
#define	SYS_UTM15_N_NAD83	475
#define	SYS_UTM16_N_NAD83	476
#define	SYS_UTM17_N_NAD83	477
#define	SYS_UTM18_N_NAD83	478
#define	SYS_UTM19_N_NAD83	479
#define	SYS_UTM20_N_NAD83	480
#define	SYS_UTM21_N_NAD83	481
#define	SYS_UTM22_N_NAD83	482
#define	SYS_UTM23_N_NAD83	483
#define	SYS_UTM24_N_NAD83	484
#define	SYS_UTM25_N_NAD83	485
#define	SYS_UTM26_N_NAD83	486
#define	SYS_UTM27_N_NAD83	487
#define	SYS_UTM28_N_NAD83	488
#define	SYS_UTM29_N_NAD83	489

/* UTM (Corrego Allegre) */
#define	SYS_UTM19_N_CORREGO_ALLEGRE	499
#define	SYS_UTM20_N_CORREGO_ALLEGRE	500
#define	SYS_UTM21_N_CORREGO_ALLEGRE	501
#define	SYS_UTM22_N_CORREGO_ALLEGRE	502
#define	SYS_UTM18_N_CORREGO_ALLEGRE	503
#define	SYS_UTM19_S_CORREGO_ALLEGRE	504
#define	SYS_UTM20_S_CORREGO_ALLEGRE	505
#define	SYS_UTM21_S_CORREGO_ALLEGRE	506
#define	SYS_UTM22_S_CORREGO_ALLEGRE	507
#define	SYS_UTM23_S_CORREGO_ALLEGRE	508
#define	SYS_UTM24_S_CORREGO_ALLEGRE	509
#define	SYS_UTM25_S_CORREGO_ALLEGRE	510

/* UTM (SAD69) */
#define	SYS_UTM17_N_SAD69	517
#define	SYS_UTM18_N_SAD69	518
#define	SYS_UTM19_N_SAD69	519
#define	SYS_UTM20_N_SAD69	520
#define	SYS_UTM21_N_SAD69	521
#define	SYS_UTM22_N_SAD69	522
#define	SYS_UTM17_S_SAD69	523
#define	SYS_UTM18_S_SAD69	524
#define	SYS_UTM19_S_SAD69	525
#define	SYS_UTM20_S_SAD69	526
#define	SYS_UTM21_S_SAD69	527
#define	SYS_UTM22_S_SAD69	528
#define	SYS_UTM23_S_SAD69	529
#define	SYS_UTM24_S_SAD69	530
#define	SYS_UTM25_S_SAD69	531


//////////////////////////////////////////////////////////////////////////
//add by jjj 2013.7.23 
#define  SYS_GEO_NAD27M 532
#define  SYS_GEO_NAD83 533
//增加英国网格坐标系 Great Britain
#define	SYS_UKNGR_OSGB36	534
/* add by cx 2014.12.24*/
#define SYS_GEO_CHINA2000 535


/* Masken f竢 die Koordinatensystemnummer */
#define Datum_Mask      	0x000000FF
#define Projection_Mask   0x0001FF00
#define Methode_Mask 			0x007E0000
#define Zone_Mask  				0x3F800000
#define Frei_Mask       	0xC0000000

///TODO: need to check whether this is PI
#define LS_PI 3.1415926535898
#define LS_PI_4 (12.5663706143592)
#define LS_PI_2 (6.2831853071796)
/* Konstanten f黵 die Koordinatentransformation */
#define  RHOG	(180.0/LS_PI)
#define  RHOS	(648000.0/LS_PI)
#define  Rad2GonSek	(2000000.0/LS_PI)
#define  RAD2GON	(200.0 / LS_PI)
#define  GRAD2GON	(180.0 / 200.0)




/***@#Xternal*****************************************************************
 *
 *  EXTERNALS
 *
 *****************************************************************************/

/* externe globale Variablen (geo) */


/***@#MG_ModulGlobal**********************************************************
 *
 *  MODULE-GLOBAL DECLARATIONS  (variables, types, constants)
 *
 *****************************************************************************/

/* module-global Constants  */

/* module-global Types  */






#endif/*__KOOSYSTEME_H__*/


/*..:....1....:....2....:....3....:....4....:....5....:....6....:....7....:...*/

								/* end of file  */


