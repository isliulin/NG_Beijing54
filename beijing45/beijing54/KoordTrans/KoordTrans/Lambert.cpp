/* *****************************************************************************
 *
 *  Datei:Lambert.c
 *        Unterprogramme zur Koordinatentransformation
 *		  Methode: Conforme Lambert Projection 2 Standardparallele
 *		  		   Conforme Lambert Projection 1 Standardparallele
 *
 *
 *  Datum: 18.06.97
 *  ?by:  L&S Hochfrequenztechnik GmbH 1993, 1997
 *    
 **************************************************************************** */
/* entht alle Parameter und Routinen f die
   Koordinaten - Transformations - Methode: 
   		Lambert             */
   		
#include <math.h>
#include "LS_Koordtrans.h"
/* //@TB010998 #include "LS_KoordStructs.h"*/
#include "koosysteme.h"
#include "Lambert.h"
/* //@PC080998 #include "KoordTransINIT.h"  */


/* Initialisierung der projektionsabhgigen Parameter */
static CONFORMLAMBERT_2P  Lambert2SP[MAXCONLAM2] =
{		/* 				PHI_1			PHI_2			PHI_0			LAMBDA_0		Off_E		Off_N */
/* 0: undefiniert */	{0.0, 			0.0,			0.0,			0.0,			0.0,		0.0     },		
/* 1: USER1 */			{25.0/RHOG,     45.0/RHOG,  	0,			    105.0/RHOG,		0.0,		0.0     },		
/* 2: USER2 */			{33.0/RHOG, 	45.0/RHOG,		23.0/RHOG,		-96.0/RHOG,		0.0,		0.0     },		
/* 3: BELGIEN */		{49.833333333/RHOG,51.1666666667/RHOG,50.7993622222/RHOG,4.3569397222/RHOG,150000.01256,	165372.95628},		
/* 4: TPC_H5A */		{25.3333333/RHOG,30.6666667/RHOG,0.0/RHOG,		33.0/RHOG,		0.0,		0.0},		
/* 5: D 1:4Mio */		{27.0/RHOG,		63.0/RHOG,		0.0/RHOG,		15.0/RHOG,		0.0,		0.0},		
/* 6: D 1:1Mio */		{48.6666667/RHOG,51.6666667/RHOG,0.0/RHOG,		14.5/RHOG,		0.0,		0.0},		
/* 7: D 1:500T */		{49.0/RHOG,		56.0/RHOG,		0.0/RHOG,		10.5/RHOG,		0.0,		0.0},		
/* 8: Austria 1:500T */	{46.0/RHOG,		49.0/RHOG,		47.5/RHOG,		13.333333333/RHOG,400000.0,	400000.0},		
/* 9: Austria ArcInfo */{46.0/RHOG,		49.0/RHOG,		48/RHOG,		13.333333333/RHOG,400000.0,	400000.0}		
};

/*--------------------------------------------------------------------------------------*/



/*	*****************************************************************************
	* Umrechnung von geographischen Koordinaten in Koordinaten, die auf der 	*
	* Lambert-Projektion mit 2 Standartparallelen beruhen.						*
	*																			*
	* Eingabe:																	*
	* 			double		longitude	Lgengrad								*
	* 			double		latitude	Breitengrad								*
	* 			KOORDSYSTEM	*psys		Systemparameter							*
	*																			*
	* Ausgabe:																	*
	* 			double		*peasting	Easting									*
	* 			double		*pnorthing	Northing								*
	*																			*
	* Status:																	*
	* 			In Arbeit	09.06.96		Peter Clevers						*
	*****************************************************************************
*/
void Geo2Lambert2SP (double longitude, double latitude, const KOORDSYSTEM *psys,
				 	 double *peasting, double *pnorthing)
{
	short enr;
	double h1, h2, t;
	double sinPhi, E1sinPhi;
	double rho, theta;
	ELLIPSOID *ell;
	DATUMSTRANS *datparam;
	
	datparam = ls_geo_get_datparam(psys->Datum);
	enr = datparam->RefEll;
	ell = ls_geo_get_ellparam(enr);
	
	sinPhi = sin(latitude);
	E1sinPhi = ell->E1 * sinPhi;
	h1 = tan(LS_PI / 4.0 - latitude / 2.0);
	h2 = (1 - E1sinPhi) / (1 + E1sinPhi);
	t = h1 / pow(h2, ell->E1 / 2.0);
	
	rho = ell->A * Lambert2SP[psys->Proj].F * pow(t, Lambert2SP[psys->Proj].n);
	theta = Lambert2SP[psys->Proj].n * (longitude - Lambert2SP[psys->Proj].Lambda_0);

	*peasting = rho * sin(theta);
	*pnorthing = Lambert2SP[psys->Proj].Rho_0 - rho * cos(theta);
	
	*peasting  += Lambert2SP[psys->Proj].Off_E;
	*pnorthing += Lambert2SP[psys->Proj].Off_N;
	
} /* ****************************Geo2Lambert2SP********************************** */


/*	*****************************************************************************
	* Umrechnung von Koordinaten, die auf der Lambert-Projektion mit			*
	* 2 Standartparallelen beruhen, in GEO-Koordinaten						 	*
	*																			*
	* Eingabe:																	*
	* 			double		easting		Easting									*
	* 			double		northing	Northing								*
	* 			KOORDSYSTEM	*psys		Systemparameter							*
	*																			*
	* Ausgabe:																	*
	* 			double		*plongitude	L”ngengrad								*
	* 			double		*platitude	Breitengrad								*
	*																			*
	* Status:																	*
	* 			In Arbeit	09.06.96		Peter Clevers						*
	*****************************************************************************
*/
void Lambert2SP2Geo (double *plongitude, double *platitude, const KOORDSYSTEM *psys,
				 	 double easting,     double northing)
{
	short enr, err;
	short i = 0;
	double h1, h2, t;
	double sinPhi, E1sinPhi;
	double rho, theta;
	double phi;
	ELLIPSOID *ell;
	DATUMSTRANS *datparam;
	
	datparam = ls_geo_get_datparam(psys->Datum);
	enr = datparam->RefEll;
	ell = ls_geo_get_ellparam(enr);
	
	northing -= Lambert2SP[psys->Proj].Off_N;
	easting  -= Lambert2SP[psys->Proj].Off_E;
	
	h1 = Lambert2SP[psys->Proj].Rho_0 - northing;
	if (Lambert2SP[psys->Proj].n >= 0.0)
		rho = sqrt(easting * easting + h1 * h1);
	else
		rho = -sqrt(easting * easting + h1 * h1);
	
	theta = atan2(easting, h1);
	t = pow((rho / (ell->A * Lambert2SP[psys->Proj].F)), (1.0 / Lambert2SP[psys->Proj].n));
	
	*plongitude = theta / Lambert2SP[psys->Proj].n + Lambert2SP[psys->Proj].Lambda_0;
	
	i = 0;
	*platitude = LS_PI / 2.0 - 2.0 * tan(t);
	do
	{
		i++;
		phi = *platitude;
		sinPhi = sin(phi);
		E1sinPhi = ell->E1 * sinPhi;
		h1 = (1 - E1sinPhi) / (1 + E1sinPhi);
		h2 = t * pow(h1, ell->E1 / 2.0);
		*platitude = LS_PI / 2.0 - 2.0 * atan(h2);
	} while ((fabs(phi - *platitude) > 1.0e-8) && (i < 100));
	
	if (i > 99) err = 4; /* Fehler in der Iteration */

} /* ****************************Lambert2SP2Geo********************************** */


/*	*****************************************************************************
	* Berechnung der Parameter: n, F, Rho0 f die Lambert2SP-Projection	  	*
	*																			*
	* Status:																	*
	* 			In Arbeit	02.10.96		Peter Clevers						*
	*****************************************************************************
*/
void Init_Lambert2SP_Param()
{
	short enr, i, proj;
	short maxcoord;
	double m1, m2, m0;
	double t1, t2, t0;
	ELLIPSOID *ell;
	DATUMSTRANS *datum;
	KOORDSTRUCT *coordsys;
	
	/* Initializing of Datum before connecting to real Datum */
	for (i=1; i<MAXCONLAM2; i++)		/* @PC111198 */
	{
		Lambert2SP[i].Datum = WGS84_BWd;
	}
	
	/* Set Datum */
	ls_geo_get_maxcoord(&maxcoord);
	for (i=1; i<maxcoord; i++)
	{
		coordsys = ls_geo_get_coordparam(i);
		
		if (coordsys->Methode == CONLAM2m)
		{
			proj = coordsys->Proj;
			Lambert2SP[proj].Datum = coordsys->Datum;
		}
	}
	
	for (i=1; i<MAXCONLAM2; i++)		/* @PC021096 */
	{
		datum = ls_geo_get_datparam(Lambert2SP[i].Datum);
		enr = datum->RefEll;
		ell = ls_geo_get_ellparam(enr);
		
		m_und_t(Lambert2SP[i].Phi_0, ell->E1, ell->E1Q, &m0, &t0);
		m_und_t(Lambert2SP[i].Phi_1, ell->E1, ell->E1Q, &m1, &t1);
		m_und_t(Lambert2SP[i].Phi_2, ell->E1, ell->E1Q, &m2, &t2);
				
		/* Berechnug von: n */
		Lambert2SP[i].n = (log(m1) - log(m2)) / (log(t1) - log(t2));
		
		/* Berechnug von: F */
		Lambert2SP[i].F = m1 / (Lambert2SP[i].n * pow(t1,Lambert2SP[i].n));
		
		/* Berechnug von: Rho_0 */
		Lambert2SP[i].Rho_0 = ell->A * Lambert2SP[i].F * pow(t0,Lambert2SP[i].n);
	}
} /* **********************InitLambert2SP_Param********************************** */


/*	*****************************************************************************
	* Berechnung der Parameter m und t										  	*
	*																			*
	* Status:																	*
	* 			In Arbeit	02.10.96		Peter Clevers						*
	*****************************************************************************
*/
void m_und_t(double phi, double E1, double E1Q, double *m, double*t)
{
	double h1, h2;
	double sinPhi;
	double E1sinPhi;
	
	sinPhi = sin(phi);
	E1sinPhi = E1 * sinPhi;	
	
	*m = cos(phi) / sqrt(1 - E1Q * sinPhi * sinPhi);
	
	h1 = tan(LS_PI / 4.0 - phi / 2.0);
	h2 = (1 - E1sinPhi) / (1 + E1sinPhi);
	
	*t = h1 / pow(h2, E1/2.0);
	
} /* ********************************m_und_t************************************ */


/*	*****************************************************************************
	* Herauslesen der systemspeziefischen Parameter f¸r	die Conforme Lambert	*
	* mit 2 Standartparallelen													*
	*																			*
	* Status:																	*
	* 			In Arbeit	10.03.97		Peter Clevers						*
	*****************************************************************************
*/
short GetConLam2SPParam(long proj, CONFORMLAMBERT_2P *conlam2sp)
{
	if ((proj < 1) || (proj >= MAXCONLAM2))
		return (1); /* Fehler */
		
	conlam2sp->Datum    = Lambert2SP[proj].Datum;
	conlam2sp->Phi_1    = Lambert2SP[proj].Phi_1;
	conlam2sp->Phi_2    = Lambert2SP[proj].Phi_2;
	conlam2sp->Phi_0    = Lambert2SP[proj].Phi_0;
	conlam2sp->Lambda_0 = Lambert2SP[proj].Lambda_0;
	conlam2sp->Off_E    = Lambert2SP[proj].Off_E;
	conlam2sp->Off_N    = Lambert2SP[proj].Off_N;
	
	return (0);
} /* ***************************GetConLam2SPParam****************************** */




/* 12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
