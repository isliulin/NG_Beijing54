/* *****************************************************************************
 *
 *  Datei: LS_ObliqueMerkator.c
 *         Unterprogramme zur Koordinatentransformation
 *  Datum: 23.07.97
 *  ?by:  L&S Hochfrequenztechnik GmbH 1993, 1997
 *    
 **************************************************************************** */

#include <math.h>
#include "LS_Koordtrans.h"
/* //@TB010998 #include "LS_KoordStructs.h"*/
#include "koosysteme.h"
#include "LS_ObliqueMerkator.h"
/* //@PC080998 #include "KoordTransINIT.h"  */


/* Initialisierung der projektionsabhgigen Parameter */
static OBMERK_T  ObMerk[MAXOBMERK] =
{		/* 				Datum		PHI_0			LAMBDA_0		Off_E		Off_N */
/* 0: undefiniert */	{0,			0.0, 			0.0,			0.0,		0.0},		
/* 1: User1 */			{BERN_CH1903d,	46.9521944/RHOG,7.43958333/RHOG,600000.0,	200000.0},		
/* 2: User2 */			{BERN_CH1903d,	46.9521944/RHOG,7.43958333/RHOG,600000.0,	200000.0},		
/* 3: Switzerland */	{BERN_CH1903d,	46.9524055/RHOG,7.43958333/RHOG,600000.0,	200000.0},		
};
/*--------------------------------------------------------------------------------------*/


/*	*****************************************************************************
	* Berechnung der Parameter: phi_0_kugel, K, R, alpha, e und eq f die	  	*
	* "Schiefachsige Merkator" Projektion										*
	*																			*
	* Status:																	*
	* 			In Arbeit	23.07.97		Peter Clevers						*
	*****************************************************************************
*/
void Init_ObMerk_Param()
{
	short enr, i, proj;
	short maxcoord;
	double cosB0, cos2B0, cos4B0;
	double e_sinPhi_0;
	ELLIPSOID *ell;
	DATUMSTRANS *datum;
	KOORDSTRUCT *coordsys;
	
	/* Initializing of Datum before connecting to real Datum */
	for (i=1; i<MAXOBMERK; i++)		/* @PC111198 */
	{
		ObMerk[i].Datum = WGS84_BWd;
	}
	/* Set Datum */
	ls_geo_get_maxcoord(&maxcoord);
	for (i=1; i<maxcoord; i++)
	{
		coordsys = ls_geo_get_coordparam(i);
		
		if (coordsys->Methode == OBMERK_SWISSm)
		{
			proj = coordsys->Proj;
			ObMerk[proj].Datum = coordsys->Datum;
		}
	}
	
	for (i=1; i<MAXOBMERK; i++)		/* @PC290197 */
	{
		datum = ls_geo_get_datparam(ObMerk[i].Datum);
		enr = datum->RefEll;
		ell = ls_geo_get_ellparam(enr);
		
		ObMerk[i].e  = ell->E1;
		ObMerk[i].eq = ell->E1Q;
		
		ObMerk[i].one_eq = 1 - ObMerk[i].eq;

		cosB0 = cos(ObMerk[i].Phi_0);
		cos2B0 = cosB0 * cosB0;
		cos4B0 = cos2B0 * cos2B0;
		ObMerk[i].alpha = 1 + ObMerk[i].eq / ObMerk[i].one_eq * cos4B0;
		ObMerk[i].alpha = sqrt(ObMerk[i].alpha);
		if (i == OBMERK_SWISSp) ObMerk[i].alpha = 1.00072913843;

		ObMerk[i].phi0 = asin(sin(ObMerk[i].Phi_0) / ObMerk[i].alpha);
		
		e_sinPhi_0 = ObMerk[i].e * sin(ObMerk[i].Phi_0);
		ObMerk[i].R = ell->A * sqrt(ObMerk[i].one_eq) / (1.0 - e_sinPhi_0 * e_sinPhi_0);
		
		ObMerk[i].K  = log(tan(LS_PI_4 + 0.5 * ObMerk[i].phi0));
		ObMerk[i].K -= ObMerk[i].alpha * log(tan(LS_PI_4 + 0.5 * ObMerk[i].Phi_0));
		ObMerk[i].K += 0.5 * ObMerk[i].alpha * ObMerk[i].e *log((1 + e_sinPhi_0) / (1 - e_sinPhi_0));
		
		ObMerk[i].cosphi0 = cos(ObMerk[i].phi0);

		ObMerk[i].sinphi0 = sin(ObMerk[i].phi0);
	}
	
	/* Genauere Parameter f das schweizer System */
	ObMerk[OBMERK_SWISSp].K     = 0.0030667323770;
	ObMerk[OBMERK_SWISSp].phi0  = 0.8186943585800;
	ObMerk[OBMERK_SWISSp].alpha = 1.0007291384300;
	ObMerk[OBMERK_SWISSp].R     = 6378815.9036000;
	
} /* ************************Init_ObMerk_Param*********************************** */


/*	*****************************************************************************
	* Konvertierung von Geo-Koordinaten in Schweizer Landeskoordinaten 			*
	*																			*
	* Eingabe:																	*
	* 			double		longitude		Lonigtude							*
	* 			double		latitude		Latitude							*
	*																			*
	* Ausgabe:																	*
	* 			double		*peasting		Easting								*
	* 			double		*ppnorthing		Northing							*
	*																			*
	* Status:																	*
	* 			In Arbeit	23.07.97		Peter Clevers						*
	*****************************************************************************
*/
void Geo2ObMerk(double longitude, double latitude, const KOORDSYSTEM *psys,
			    double *peasting, double *pnorthing)
{
	double h1, h2, h3;
	double l, b;
	double sinBstrich;
	double lquer, bquer;
	short proj;
	
	proj = psys->Proj;
	
	/* Konforme Abbildung des Ellipsoids auf die Kugel */
	sinBstrich = ObMerk[proj].e * sin(latitude);
	h1 = ObMerk[proj].alpha * log(tan(LS_PI_4 + 0.5 * latitude));
	h2 = 0.5 * ObMerk[proj].alpha * ObMerk[proj].e * log((1 + sinBstrich) / (1 - sinBstrich));
	h3 = atan(exp(h1 - h2 + ObMerk[proj].K));
	
	/* Kugelkoordinaten */
	b = 2.0 * h3 - LS_PI_2;
	l = ObMerk[proj].alpha * (longitude - ObMerk[proj].Lambda_0);
	
	
	/* Konforme Abbildung der Kugel auf einen schiefachsigen Zylinder */
	bquer = asin(ObMerk[proj].cosphi0 * sin(b) - ObMerk[proj].sinphi0 * cos(b) * cos(l));
	lquer = asin((cos(b) * sin(l)) / cos(bquer));
	
	*peasting = ObMerk[proj].R * lquer;
	*pnorthing = ObMerk[proj].R * log(tan(LS_PI_4 + bquer/2.0));

	*peasting  += ObMerk[proj].Off_E;
	*pnorthing += ObMerk[proj].Off_N;
	
	
} /* ********************************Geo2ObMerk********************************** */



/*	*****************************************************************************
	* Konvertierung von Schweizer Landeskoordinaten in Geo-Koordinaten			*
	*																			*
	* Eingabe:																	*
	* 			double		easting			Easting								*
	* 			double		pnorthing		Northing							*
	*																			*
	* Ausgabe:																	*
	* 			double		*plongitude		Lonigtude							*
	* 			double		*platitude		Latitude							*
	*																			*
	* Status:																	*
	* 			In Arbeit	23.07.97		Peter Clevers						*
	*****************************************************************************
*/
void ObMerk2Geo(double *plongitude, double *platitude, const KOORDSYSTEM *psys,
			    double easting,     double northing)
{
	double northquer;
	double l, b;
	double lquer, bquer;
	double hilf1, hilf2;
	double bstrich;
	short i, proj;

	proj = psys->Proj;
	
	easting  -= ObMerk[proj].Off_E;
	northing -= ObMerk[proj].Off_N;

	lquer = easting / ObMerk[proj].R;
	northquer = exp(northing / ObMerk[proj].R);
	bquer = 2.0 * (atan2(northquer,1.0) - LS_PI_4);
	
	b = asin(ObMerk[proj].cosphi0 * sin(bquer) + ObMerk[proj].sinphi0 * cos(bquer) * cos(lquer));
	l = asin(cos(bquer) * sin(lquer) / cos(b));
	
	/* Berechnung der elliptischen Laenge */
	*plongitude = ObMerk[proj].Lambda_0 + l/ObMerk[proj].alpha;
	
	/* Iterative Berechnung der elliptischen Breite */
	hilf1 = (ObMerk[proj].K - log(tan(LS_PI_4 + 0.5 * b))) / ObMerk[proj].alpha;
	i= 0;
	do
	{
		i++;
		bstrich = ObMerk[proj].e * sin(b);
		
		hilf2  = hilf1 + log(tan(LS_PI_4 + 0.5 * b));
		hilf2 -= 0.5 * ObMerk[proj].e *log((1.0 + bstrich)/(1.0 - bstrich));
		hilf2 *= (1 - bstrich * bstrich) * cos(b) / (1 - ObMerk[proj].eq);
		
		b -= hilf2;
	} while ((fabs(hilf2) > 1.0e-9) && (i < 10));
	
	if (i > 9)
	{
		*platitude = 0.0;
	}
	else
	{
		*platitude = b;
	}

} /* ********************************ObMerk2Geo********************************** */


