#include "KoordTrans.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "koosysteme.h"
#include "LS_Koordtrans.h"
#include "KoordTransINIT.h"
#include "Transversal_Merkator.h"
#include "LS_Datum2Datum.h"
#include "Special_Projection.h"
#include "Lambert.h"
#include "Albers.h"
#include "LS_ObliqueMerkator.h"
#include "Belgium.h"

#pragma warning(disable:4996)

/* Transformationen */
typedef void (*Geo2Proj_t) (double longitude, double latitude, const KOORDSYSTEM *psys,
							double *easting,  double *northing);
typedef void (*Proj2Geo_t) (double *longitude, double *latitude, const KOORDSYSTEM *psys,
							double easting,    double northing);
typedef struct
{
	Geo2Proj_t Geo2Proj;
	Proj2Geo_t Proj2Geo;
} method_t;

static method_t Method[] =
{
	/* Geo -> Proj		Proj -> Geo */

	/* 0: Frei */
	{NULL,				NULL},

	/* 1: USER1 	<-> Grad */
	{NULL,				NULL},

	/* 2: USER2 	<-> Grad */
	{NULL,				NULL},

	/* 3: Radiant 	<-> Grad */
	{Rad2Grad,			Grad2Rad},

	/* 4: GEO 		<-> Transversal Merkator Sphere */
	{Geo2TransMerkSphere,	TransMerkSphere2Geo},

	/* 5: GEO 		<-> Transversal Merkator Ellipsoid*/
	{Geo2TransMerkEll,	TransMerkEll2Geo},

	/* 6: GEO 		<-> Ireland Grid */
	{Geo2IreGrid,		IreGrid2Geo},

	/* 7: GEO 		<-> Rijksdrihoek */
	{Geo2Rd,			Rd2Geo},

	/* 8: GEO 		<-> Conforme Lambert: 2 Standartparallele */
	{Geo2Lambert2SP,	Lambert2SP2Geo},

	/* 9: GEO 		<-> Conforme Lambert: 1 Standartparallel */
	{NULL,				NULL},

	/* 10: GEO 		<-> Albers Sphere */
	{Geo2AlbersSphere,		AlbersSphere2Geo},

	/* 11: GEO 		<-> Albers Ellipsoid */
	{Geo2AlbersEllipsoid,		AlbersEllipsoid2Geo},

	/* 12: GEO 		<-> Switzerland */
	{Geo2ObMerk,		ObMerk2Geo},

	/* 13: GEO 		<-> Bundesmeldenetz Austria */
	{Geo2Bundesmeldenetz,	Bundesmeldenetz2Geo},

	/* 14: GEO 		<-> Belgium Lambert 72/50 */
	{Geo2Belgium72_50,	Belgium72_50_2GEO},

	/* 15: GEO 		<-> Belgium Lambert 72 */
	{Geo2Belgium72,		Belgium72_2GEO},

	/* 16: GEO 		<-> EOV Hangary */
	{Geo2EOV,			EOV2Geo},
};

void ng_geo_init()
{
	static bool init = false;
	if(!init)
	{
		init = true;
		Init_KoordTrans();
	}
}

void ng_geo_trans(long fromSys, long toSys, double fromX, double fromY,double *toX,  double *toY)
{
	NeuGeoTransformC ( fromSys, toSys, fromX, fromY, toX,toY);
}		

/*	*****************************************************************************
* Umrechnung von Grad in Radiant											*
*																			*
* Input:																	*
* 			double		Long_GRAD		Longitude in Grad					*
* 			double		Lat_GRAD		Latitude in Grad					*
* 			KOORDSYSTEM	*psys			Koordinatensystem					*
*																			*
* Output:																	*
* 			double		*Long_RAD		Longitude in Radiant				*
* 			double		*Lat_RAD		Latitude in Radiant					*
*																			*
* Status:																	*
* 			In Arbeit	01.12.99		Peter Clevers						*
*****************************************************************************
*/
void Grad2Rad(double *Long_RAD,  double *Lat_RAD, const KOORDSYSTEM *psys,
			  double  Long_GRAD, double  Lat_GRAD)
{
	(void)psys;
	*Long_RAD = Long_GRAD / RHOG;
	*Lat_RAD  = Lat_GRAD  / RHOG;
} /* *****************************Grad2Rad************************************** */


/*	*****************************************************************************
* Umrechnung von Radiant in Grad											*
*																			*
* Input:																	*
* 			double		Long_RAD		Longitude in Radiant				*
* 			double		Lat_RAD			Latitude in Radiant					*
* 			KOORDSYSTEM	*psys			Koordinatensystem					*
*																			*
* Output:																	*
* 			double		*Long_GRAD		Longitude in Grad					*
* 			double		*Lat_GRAD		Latitude in Grad					*
*																			*
* Status:																	*
* 			In Arbeit	01.12.99		Peter Clevers						*
*****************************************************************************
*/
void Rad2Grad(double  Long_RAD,   double  Lat_RAD, const KOORDSYSTEM *psys,
			  double *Long_GRAD, double *Lat_GRAD)
{
	(void)psys;
	*Long_GRAD = Long_RAD * RHOG;
	*Lat_GRAD  = Lat_RAD  * RHOG;
} /* *****************************Rad2Grad************************************** */

/*	*****************************************************************************
* Umrechnung von einem Koordinatenpaar, das auf dem Quelldatum und der 		*
* Quellprojection beruht, in das Zielkoordinatenpaar, das auf dem Ziel-		*
* datum und der Zielprojection beruht.										*
*																			*
* Input:																	*
* 			double		xq			Easting / Longitude						*
* 			double		yq			Northing /Latitude						*
* 			double		hq			Hoehe 竍er dem Ellipsoiden				*
* 			KOORDSYSTEM *psysq		Systemparameter	Quellsystem				*
* 			KOORDSYSTEM *psysq		Systemparameter	Zielsystem				*
*																			*
* Output:																	*
* 			double		*pxz		Easting / Longitude						*
* 			double		*pyz		Northing /Latitude						*
* 			double		*hq			Hoehe 竍er dem Ellipsoiden				*
*																			*
* Funktionswert:															*
* 			short		0			Kein Fehler								*
* 			short		< 0			Fehler !!!!!							*
*																			*
* Status:																	*
* 			In Arbeit	05.02.96		Peter Clevers						*
*****************************************************************************
*/
short KoordTrans (double   xq, double   yq, double   hq, const KOORDSYSTEM *psysq, 
				  double *pxz, double *pyz, double *phz, const KOORDSYSTEM *psysz)
{
	double Longitude, Latitude;
	short  noerr;

	/* 1. Schritt:	Umrechnung von Koordinaten,
	die auf einer Projection beruhen, in GEO-Koordinaten 		*/
	if ((psysq->Datum   != psysz->Datum)   || 
		(psysq->Methode != psysz->Methode) || 
		(psysq->Proj    != psysz->Proj)    ||
		(psysq->Zone    != psysz->Zone))
	{
		/* 1. Schritt:	Umrechnung von Koordinaten,
		die auf einer Projection beruhen, in GEO-Koordinaten 		*/
		if (Method[psysq->Methode].Proj2Geo != NULL)
			Method[psysq->Methode].Proj2Geo (&Longitude, &Latitude, psysq, xq, yq);
		else
			return (-1); /* !!!!! FEHLER !!!!! */

		/* 2. Schritt:	Umrechnung von Geo-Koordinaten des Quelldatums auf
		GEO-Koordinaten des Zieldatums								*/
		*phz = hq;
		if (psysq->Datum   != psysz->Datum)
		{
			noerr = Datum2Datum (&Longitude, &Latitude, phz, psysq, psysz);
		}

		/* 3. Schritt:	Umrechnung von GEO-Koordinaten in Koordinaten, 
		die auf einer Projection beruhen.					 		*/
		if (Method[psysz->Methode].Geo2Proj != NULL)
			Method[psysz->Methode].Geo2Proj (Longitude, Latitude, psysz, pxz, pyz);
		else
			return (-1); /* !!!!! FEHLER !!!!! */
	}
	else
	{
		*pxz = xq;
		*pyz = yq;
		return (0);
	}

	return (0);

} /* ****************************KoordTrans************************************** */


/*	*****************************************************************************
* Zugriffsfunktion auf die  Koordinatensysteme								*							*
*																			*
* Input:																	*
* 			short		sysnr		Nummer des Koordinatensystems			*
*																			*
* Function:																	*
* 			KOORDSTRUCT				Pointer auf Datumsparameter				*
*																			*
* Status:																	*
* 			Fertig	08.09.98		Peter Clevers							*
*****************************************************************************
*/
KOORDSTRUCT *ls_geo_get_coordparam(short sysnr)
{
	return (&(KoordSys_List[sysnr]));
} /* ***************************ls_geo_get_coordparam**************************** */


/*	*****************************************************************************
* Aufruf der neuen Koordinatentransformationsroutine mit den alten System- 	*
* nummern.																	*
*																			*
* Input:																	*
* 			long		vonsys			Systemnummer des Quellsystems		*
* 			long		nachsys			Systemnummer des Quellsystems		*
* 			double	xq					X-Koordinate des Quellsystems		*
* 			double	yq					Y-Koordinate des Quellsystems		*
*																			*
* Output:																	*
* 			double	*pxz					X-Koordinate des Zielsystems	*
* 			double	*pyz					Y-Koordinate des Zielsystems	*
*																			*
* Status:																	*
* 			In Arbeit	29.01.97		Peter Clevers						*
*****************************************************************************
*/
void NeuGeoTransformC (long vonsys, long nachsys, double   xq, double   yq,
					   double *pxz, double *pyz)
{
	short noerr;
	KOORDSYSTEM sysq, sysz;
	double hq, hz; 			/* Hoehe ueber NN */
	KOORDSTRUCT *coordsysQ, *coordsysZ;

	/* nur fuer testzwecke */
	/* !!!!!!!!!!!!!!!!!! */
	hq = hz = 0.0;
	/* !!!!!!!!!!!!!!!!!! */

	coordsysQ = ls_geo_get_coordparam(vonsys);
	sysq.Datum   = coordsysQ->Datum;
	sysq.Proj    = coordsysQ->Proj;
	sysq.Methode = coordsysQ->Methode;
	sysq.Zone    = coordsysQ->Zone;

	coordsysZ = ls_geo_get_coordparam(nachsys);
	sysz.Datum   = coordsysZ->Datum;
	sysz.Proj    = coordsysZ->Proj;
	sysz.Methode = coordsysZ->Methode;
	sysz.Zone    = coordsysZ->Zone;


	/*	!!! Koordsys = 0 ist jetzt fest mit einem Datum verbunden !!! @PC310398 */
	/*	!!! Wenn Datum == NONEd => keine Datumstransformation !!! */
	if ((sysq.Methode == GEOm) && (sysq.Datum == NONEd))
		sysq.Datum = sysz.Datum;
	if ((sysz.Methode == GEOm) && (sysz.Datum == NONEd))
		sysz.Datum = sysq.Datum;


	/* TEST TEST TEST TEST */
	/*	sysq.Datum = AUSTRIAd;
	sysq.Proj = 0;
	sysq.Methode = GEOm;
	sysq.Zone = 0;

	xq = 10.0;
	yq = 47.0;

	sysz.Datum = WGS84d;
	sysz.Proj = 0;
	sysz.Methode = GEOm;
	sysz.Zone = 0;
	*/
	/* TEST TEST TEST TEST */

	noerr = KoordTrans ( xq,  yq,  hq, &sysq,
		pxz, pyz, &hz, &sysz);

	if ((sysz.Methode == GEOm) && ((fabs(*pxz) > 360.0) || (fabs(*pyz) > 90.0)))	/* @PC 300797 */
	{
		*pxz = 0.0;
		*pyz = 0.0;
	}

} /* ****************************NeuGeoTransformC******************************* */
/*	*****************************************************************************
* Gibt die maxiamle Anzahl der vorhandenen Datume wieder					*							*
*																			*
* Status:																	*
* 			Fertig	08.09.98		Peter Clevers							*
*****************************************************************************
*/
void ls_geo_get_maxdatum(short *maxdat)
{
	*maxdat = MAXDATUM;
} /* **************

  /*	*****************************************************************************
  * Returning the Maximum Number of Coordinate Systems					 	*
  *																			*
  * Status:																	*
  * 			In Arbeit	19.03.98		Peter Clevers						*
  *****************************************************************************
  */
short GetMaxCoord()
{
	return (MAX_KOORDLIST);
} /* ********************************GetMaxCoord******************************** */

/*	*****************************************************************************
* Initialisierung aller Variablen und Felder, die f竢 die Koordinaten-		*
* transformation gebraucht werden.											*
*																			*
* Status:																	*
* 			Fertig	18.02.97		Peter Clevers							*
*****************************************************************************
*/
void Init_KoordTrans()
{
	Init_Ellpar();
	Init_AlbersParam();
	Init_Lambert2SP_Param();	/* PC180297 */
	Init_ObMerk_Param();		/* PC230797 */
} /* *******************************Init_Koordtrans****************************** */


/*	*****************************************************************************
* Initialisierung der Ellipsenparameter										*
*																			*
* Statisches Feld:															*
* 			ELLIPSOID		Ell[]		Feld mit den Systemparametern 		*
*																			*
* Status:																	*
* 			Fertig	06.02.96		Peter Clevers							*
*****************************************************************************
*/
void Init_Ellpar()
{
	short i;
	double h1, h2;

	for (i = 1; i < MAXELL; i++)
	{
		Ell[i].B = Ell[i].A * (1 - 1.0 / Ell[i].f);
		h1 = Ell[i].A - Ell[i].B;
		h2 = Ell[i].A + Ell[i].B;
		Ell[i].E1Q = (h1 / Ell[i].A) * (h2 / Ell[i].A);
		Ell[i].E1  = sqrt(Ell[i].E1Q);
		Ell[i].E2Q = (h1 / Ell[i].B) * (h2 / Ell[i].B);
		Ell[i].N = h1 / h2;
		Ell[i].CZ = (Ell[i].A / Ell[i].B) * Ell[i].A;
		Ell[i].XMIN = Ell[i].CZ * (1 - Ell[i].E1Q);
		Ell[i].XMAX = Ell[i].CZ * (Ell[i].XMIN + 1.8e4);
		Ell[i].XMIN = Ell[i].XMIN * (Ell[i].XMIN - 4.0e3);
	}

} /* ******************************Init_Ellpar*********************************** */


/*	*****************************************************************************
* Zugriffsfunktion auf die  Ellipsenparameter								*							*
*																			*
* Input:																	*
* 			short		ellnr		Nummer des Ellipsoiden					*
*																			*
* Function:																	*
* 			ELLIPSOID				Pointer auf Ellipsoidparameter			*
*																			*
* Status:																	*
* 			Fertig	08.09.98		Peter Clevers							*
*****************************************************************************
*/
ELLIPSOID *ls_geo_get_ellparam(short ellnr)
{
	return (&(Ell[ellnr]));
} /* ***************************ls_geo_get_ellparam**************************** */

/*	*****************************************************************************
* Zugriffsfunktion auf die  Datumsparameter									*							*
*																			*
* Input:																	*
* 			short		datnr		Nummer des Datums						*
*																			*
* Function:																	*
* 			DATUMSTRANS				Pointer auf Datumsparameter				*
*																			*
* Status:																	*
* 			Fertig	08.09.98		Peter Clevers							*
*****************************************************************************
*/
DATUMSTRANS *ls_geo_get_datparam(short datnr)
{
	return (&(DTrans[datnr]));
} /* ***************************ls_geo_get_datparam**************************** */

/*	*****************************************************************************
* Umrechnung von Dezimalgrad in sexagesimale Darstellung					*
*																			*
* Input:																	*
* 			double		dez			Dezimalgrad								*
*																			*
* Output:																	*
* 			double		*sexagesi	GGG,MMSSSS								*
*																			*
* Status:																	*
* 			In Arbeit	18.02.97		Peter Clevers						*
*****************************************************************************
*/
void Dez2Sexa (double dez, double *sexagesi)

{
	double r1;
	double g, m, s;

	r1 = modf(fabs(dez), &g);
	r1 = fabs(r1) * 60.0;
	s = modf(r1, &m);
	s *= 60.0;
	if (s >= 59.999999) 
	{
		s = 0.0;
		m = m +1.0;
	}

	if (m >= 59.999999) 
	{
		m = 0;
		g *= 1.0;
	}

	if (s < 1.0e-10)
	{
		*sexagesi = g + m / 100.0 + 1.0e-10;
	}
	else
	{
		*sexagesi = g + m / 100.0 + s / 10000.0;
	}

	*sexagesi *= signc(dez);

} /* *******************************Dez2GMS************************************** */

/*	*****************************************************************************
* Gibt die maxiamle Anzahl der vorhandenen Koordinatensysteme wieder		*							*
*																			*
* Status:																	*
* 			Fertig	08.09.98		Peter Clevers							*
*****************************************************************************
*/
void ls_geo_get_maxcoord(short *maxcoord)
{
	*maxcoord = MAX_KOORDLIST;
} /* ****************************ls_geo_get_maxcoord***************************** */

/*	*****************************************************************************
* Vorzeichen erkennen		 												*
*																			*
* Input:																	*
* 			double	wert				Eingabewert							*
*																			*
* Funktionswert:															*
* 			double	roundc				Ausgabewert							*
*																			*
* Status:																	*
* 			Fertig 18.06.97				Peter Clevers						*
*****************************************************************************
*/
double signc(double wert)
{	
	if (wert > 0)
		return (1.0);
	else if (wert < 0)
		return (-1.0);
	else
		return (0);
}

//////////////////////////////////////////////////////////////////////////
//2010.10.11

short Get_Coordsystem_Name(long koordsys, char *systemname)
{
	if ((koordsys >= 0) && (koordsys < MAX_KOORDLIST))
	{
		strcpy(systemname,KoordSys_List[koordsys].ShortName);
		return (0);
	}
	else
		return (30);
}

short ng_GetMaxCoord()
{
	return GetMaxCoord();
}

short ng_Get_Coordsystem_Name(long koordsys, char *systemname)
{
	return Get_Coordsystem_Name(koordsys,systemname);
}

//2011.7.12 by jjj
short Get_Coordsystem_LongName(long koordsys, char *systemname)
{
	if ((koordsys >= 0) && (koordsys < MAX_KOORDLIST))
	{
		strcpy(systemname,KoordSys_List[koordsys].LongName);
		return (0);
	}
	else
		return (30);
}
short ng_Get_Coordsystem_LongName(long koordsys, char *systemname)
{
	return Get_Coordsystem_LongName(koordsys,systemname);
}

//2011.8.25 by jjj
short ng_GetCoordNoFromName(const char *systemname)
{
	char strName[128];
	for(int l = 0; l < ng_GetMaxCoord(); l ++ )
	{
		//首先看是否为short name
		ng_Get_Coordsystem_Name(l,strName);
		if(strcmp(strName, systemname)==0)
			return l;

		//如果没有，再看是否为 long name
		ng_Get_Coordsystem_LongName(l,strName);
		if(strcmp(strName, systemname)==0)
			return l;
	}
	return SYS_UNDEF;
}

//////////////////////////////////////////////////////////////////////////
//add by jjj 2012.8.14

/*	*****************************************************************************
* Returns the total number of available categories							*															*
*																			*
* Output:																	*
*			long 	category_item_size	Amount of Categories				*
*																			*
* Status:																	*
* 			In Arbeit	01.10.97		Peter Clevers						*
*****************************************************************************
*/
long ng_GetCategoryItemSize()
{
	return (category_item_size);
} /* *******************************GetCategoryName****************************** */


/*	*****************************************************************************
* Returns the Category name that belongs to the Category number:			*
* CategoryItem																*															*
*																			*
* Input:																	*
* 			LONG	CategoryItem				Internal Number of Category	*
* Output:																	*
*			char 	CategoryItemName[length24]	Name of the Category		*
*																			*
* Status:																	*
* 			In Arbeit	01.10.97		Peter Clevers						*
*****************************************************************************
*/
short ng_GetCategoryItemName(long CategoryItem, char **CategoryItemName)
{
	CATEGORY aCat;
	static 	char tmpstring[length24];

	strcpy(tmpstring, " ");

	*CategoryItemName=(char *) tmpstring;

	if ((CategoryItem >= 0) && (CategoryItem < category_item_size))
	{
		aCat=Category_Item_List[CategoryItem];
		//strncpy_s(tmpstring, aCat.name, sizeof(tmpstring)-1);
		memcpy(tmpstring, aCat.name, sizeof(tmpstring)-1);
		tmpstring[sizeof(tmpstring)-1]	= 0;
		*CategoryItemName=(char *) tmpstring;
		return (0);
	}
	else
		return (80); /*  Fehler */
} /* *******************************GetCategoryName****************************** */


/*	*****************************************************************************
* Returns the total number of available coordinate systems that belong to	*
* a Category with the number: CategoryItem									*
*																			*
* Input:																	*
* 			LONG	CategoryItem	Internal Number for Category			*
*																			*
* Output:																	*
*			long 	categorysize	Amount of available Categories			*
*																			*
* Status:																	*
* 			In Arbeit	01.10.97		Peter Clevers						*
*****************************************************************************
*/
short ng_GetCategorySize(long CategoryItem, long *categorysize)
{
	if ((CategoryItem < 0) || (CategoryItem >= category_item_size))
	{
		return (81);
	}
	else
	{
		*categorysize = Category_Item_List[CategoryItem].CategorySize;
		return (0);
	}

} /* *******************************GetCategorySize****************************** */


/*	*****************************************************************************
* Returns the Coordinate-System-Number that is indicated by the CategoryItem*
* and the ProjectionItem													*
*																			*
* Input:																	*
* 			LONG	CategoryItem	Internal Number for Category			*
* 			LONG	ProjectionItem	 Category List Number of the Projection	*
*																			*
* Output:																	*
*			LONG 	GetCategoryProjNumber	Coordinate System Number		*
*																			*
* Status:																	*
* 			In Arbeit	01.10.97		Peter Clevers						*
*****************************************************************************
*/
short ng_GetCategoryProjNumber(long CategoryItem, long ProjectionItem, long *sysnr)
{
	long 	categorysize;
	short	noerr;

	noerr = ng_GetCategorySize(CategoryItem, &categorysize);
	if (noerr != 0)
		return (82);

	if ((ProjectionItem < 0) || (ProjectionItem >= categorysize))
		return (83);
	else
	{
		*sysnr = Category_Item_List[CategoryItem].ProjNumber[ProjectionItem];
		return (0);
	}
} /* ****************************GetCategoryProjNumber*************************** */



/*	*****************************************************************************
* Returns the short Name of selected Coodinate system of the chosen 		*
* Cotegory																	*
*																			*
* Input:																	*
* 			LONG	CategoryItem	Internal Number for Category			*
* 			LONG	ProjectionItem	 Category List Number of the Projection	*
*																			*
* Output:																	*
*			char 	*ShortName		Short Displayname der Coordinate System	*
*																			*
* Status:																	*
* 			In Arbeit	06.10.97		Peter Clevers						*
*****************************************************************************
*/
short ng_GetCategoryProjName(long CategoryItem, long ProjectionItem, char **ShortName)
{
	long	sysnr;
	short	noerr;
	static char    tmpstring[length24];
	strcpy(tmpstring," ");
	*ShortName=(char *) tmpstring;
	noerr = ng_GetCategoryProjNumber(CategoryItem, ProjectionItem, &sysnr);
	if (noerr != 0)
		return (84);



	if ((sysnr < 0) || (sysnr >= MAX_KOORDLIST))
		return (85);
	else
	{
		strcpy(/*ShortName*/tmpstring, KoordSys_List[sysnr].ShortName);
		*ShortName=(char *) tmpstring;
		return (0);
	}
} /* *****************************GetCategoryProjName**************************** */


/*	*****************************************************************************
* Returns the Long Name of selected Coodinate system of the chosen 			*
* Cotegory																	*
*																			*
* Input:																	*
* 			LONG	CategoryItem	Internal Number for Category			*
* 			LONG	ProjectionItem	Category List Number of the Projection	*
*																			*
* Output:																	*
*			char 	*LongName		Long Displayname der Coordinate System	*
*																			*
* Status:																	*
* 			In Arbeit	06.10.97		Peter Clevers						*
*****************************************************************************
*/
short ng_GetCategoryProjLongName(long CategoryItem, long ProjectionItem, char **LongName)
{
	long	sysnr;
	short	noerr;
	static char    tmpstring[length48];

	noerr = ng_GetCategoryProjNumber(CategoryItem, ProjectionItem, &sysnr);
	if (noerr != 0)
		return (86);



	if ((sysnr < 0) || (sysnr >= MAX_KOORDLIST))
		return (87);
	else
	{
		strcpy(tmpstring, KoordSys_List[sysnr].LongName);
		*LongName=(char *) tmpstring;
		return (0);
	}
} /* ****************************GetCategoryDatumName*************************** */


bool ng_IsGeoSystem(long SysNr)
{
	long methode;

	methode = KoordSys_List[SysNr].Methode;

	if (methode == GEOm)
		return true;
	else
		return false;
}

bool ng_IsUTMSystem(long SysNr)
{
	if ((KoordSys_List[SysNr].Methode == TRANSMERK_Em) &&
		((KoordSys_List[SysNr].Proj == TM_UTM_Np) ||
		(KoordSys_List[SysNr].Proj == TM_UTM_Sp)))
		return true;
	else
		return false;
} 

bool ng_IsGKZoneSystem(long SysNr)
{
	if ((KoordSys_List[SysNr].Methode == TRANSMERK_Em) &&
		((KoordSys_List[SysNr].Proj == TM_GK_PULKp) ||
		(KoordSys_List[SysNr].Proj == TM_GK_DHDNp)))
		return true;
	else
		return false;
} 
/*	*****************************************************************************
* L&S-Eastings for UTM-System have an unusual Baumann-number (Zone-number)  *
* in front of the easting value. This function converts the L&S-easting  	*
* into the usual Format without Baumann number.                         	*
*																			*
* Input:																	*
* 			LONG	SysNr			Internal number for Coordsystem			*
*																			*
*																			*
* Funktionswert:															*
* 			double	LuSeasting		L&S easting with Baumann number		    *
* 					easting			Easting without Baumann number          *
*																			*
* Status:																	*
* 			In Arbeit	14.04.99		Peter Clevers						*
*****************************************************************************
*/
double ng_LusEasting2UtmEasting(long SysNr, double easting)
{
	if (ng_IsUTMSystem(SysNr))
		return (easting - KoordSys_List[SysNr].Zone * 1.0e6);
	else
		return (easting);
} /* ******************************IsTransMerkSystem***************************** */


/*	*****************************************************************************
* L&S-Eastings for UTM-System have an unusual Baumann-number (Zone-number)  *
* in front of the easting value. This function converts the usual       	*
* UTM easting into the L&S Format with Baumann number added to the easting  *
*																			*
* Input:																	*
* 			LONG	SysNr			Internal number for Coordsystem			*
*																			*
*																			*
* Funktionswert:															*
* 			double	easting			Easting without Baumann number          *
* 					LuSeasting		L&S Easting with Baumann number added   *
*																			*
* Status:																	*
* 			In Arbeit	14.04.99		Peter Clevers						*
*****************************************************************************
*/
double ng_UtmEasting2LusEasting(long SysNr, double easting)
{
	if (ng_IsUTMSystem(SysNr))
		return (easting + KoordSys_List[SysNr].Zone * 1.0e6);
	else
		return (easting);
} /* ******************************IsTransMerkSystem***************************** */


double ng_LusEasting2GKZoneEasting(long SysNr, double easting)
{
	if (ng_IsGKZoneSystem(SysNr))
		return (easting - KoordSys_List[SysNr].Zone * 1.0e6);
	else
		return (easting);
}

double ng_GKZoneEasting2LusEasting(long SysNr, double easting)
{
	if (ng_IsGKZoneSystem(SysNr))
		return (easting + KoordSys_List[SysNr].Zone * 1.0e6);
	else
		return (easting);
}

void	ng_GetProjEllipSoid_AF(long SysNr,double *pA,double *pF)
{
	KOORDSTRUCT *pCoord = ls_geo_get_coordparam(SysNr);			//坐标系信息
	DATUMSTRANS *pDatum = ls_geo_get_datparam(pCoord->Datum);	//大地基准信息
	ELLIPSOID *pEllip = ls_geo_get_ellparam(pDatum->RefEll);	//地球椭球体

	*pA = pEllip->A;
	*pF = pEllip->f;
}