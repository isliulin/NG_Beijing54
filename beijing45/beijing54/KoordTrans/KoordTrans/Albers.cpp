/* entht alle Parameter und Routinen f die
   Koordinaten - Transformations - Methode: 
   		Transversal Merkator.c             */

#include <math.h>
#include "LS_Koordtrans.h"
/* //@TB010998 #include "LS_KoordStructs.h"*/
#include "koosysteme.h"
#include "Albers.h"
/* //@PC080998 #include "KoordTransINIT.h"  */



/* Initialisierung der projektionsabhgigen Parameter */
/* Albers based on the Sphere */
static ALBERS_T  AlbersS[MAXALBERSSPHERE] =
{		/* 				PHI_1				PHI_2				PHI_0			LAMBDA_0			Off_E		Off_N */
/* 0: undefiniert */	{0.0, 				0.0,				0.0,			0.0,				0.0,		0.0},		
/* 1: USER1 */			{29.5/RHOG, 		45.5/RHOG,			23.0/RHOG,		-96.0/RHOG,			0.0,		0.0},		
/* 2: USER2 */			{0.0, 				1.0,				1.0,			1.0,				0.0,		0.0},		
/* 3: 1:800T BRD */		{53.6666666667/RHOG, 48.6666666667/RHOG, 0.0/RHOG,	10.61884/RHOG,		0.0,		0.0},	
};

/* Albers based on the Ellipsoid */
static ALBERS_T  AlbersE[MAXALBERSELL] =
{		/* 				PHI_1			PHI_2			PHI_0			LAMBDA_0			Off_E		Off_N */
/* 0: undefiniert */	{0.0, 			0.0,			0.0,			0.0,				0.0,		0.0},		
/* 1: USER1 */			{29.5/RHOG, 	45.5/RHOG,		23.0/RHOG,		-96.0/RHOG,			0.0,		0.0},		
/* 2: USER2 */			{0.0, 			1.0,			1.0,			1.0,				0.0,		0.0},		
/* 3: Sued Afrika */	{-18.0/RHOG, 	-32.0/RHOG,		0.0/RHOG,		24.0/RHOG,			0.0,		0.0},		
/* 4: Sweden */			{50.0/RHOG, 	70.0/RHOG,		0.0/RHOG,		15.808277777/RHOG,	0.0,		0.0},		
/* 5: 1:2Mio Austria */	{35.0/RHOG, 	55.0/RHOG,		52.3809583/RHOG,13.0663166667/RHOG,	0.0,		0.0},		
};
/*--------------------------------------------------------------------------------------*/



/*	*****************************************************************************
	* Albers Conical Equal Area Projection - SPHERE - Forward Equation			*
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
	* 			In Arbeit	09.04.98		Peter Clevers						*
	*****************************************************************************
*/
void Geo2AlbersSphere (double longitude, double latitude, const KOORDSYSTEM *psys,
					   double *peasting, double *pnorthing)
{
	short enr;
	double rho, theta;
	double R0 = 6371000.0;
	DATUMSTRANS *datparam;
	
	datparam = ls_geo_get_datparam(psys->Datum);
	enr = datparam->RefEll;

	rho = R0 * sqrt(AlbersS[psys->Proj].C - 2.0 *AlbersS[psys->Proj].n * sin(latitude));
	rho /= AlbersS[psys->Proj].n;
	
	theta = AlbersS[psys->Proj].n * (longitude - AlbersS[psys->Proj].Lambda_0);
	
	*peasting = rho * sin(theta);
	*pnorthing = AlbersS[psys->Proj].Rho_0 - rho * cos(theta);
	
} /* ****************************Geo2Albers*************************************** */


/*	*****************************************************************************
	* Albers Conical Equal Area Projection - SPHERE - Inverse Equation			*
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
	* 			In Arbeit	09.04.98		Peter Clevers						*
	*****************************************************************************
*/
void AlbersSphere2Geo (double *plongitude, double *platitude, const KOORDSYSTEM *psys,
					   double easting,     double northing)
{
	double hv1;
	double rho, theta;
	double R0 = 6371000.0;
	
	hv1 = AlbersS[psys->Proj].Rho_0 - northing;
	rho = sqrt(easting * easting + hv1 * hv1);
	
	theta = atan2(easting, hv1);
	
	*plongitude = AlbersS[psys->Proj].Lambda_0 + theta / AlbersS[psys->Proj].n;
	
	hv1 = rho * AlbersS[psys->Proj].n / R0;
	hv1 = AlbersS[psys->Proj].C - hv1 * hv1;
	*platitude = asin(hv1 / (2.0 * AlbersS[psys->Proj].n));
} /* ****************************Geo2Albers*************************************** */



/*	*****************************************************************************
	* Albers Conical Equal Area Projection - ELLIPSOID - Forward Equation		*
	*																			*
	* Eingabe:																	*
	* 			double		longitude	L”ngengrad								*
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
void Geo2AlbersEllipsoid (double longitude, double latitude, const KOORDSYSTEM *psys,
						  double *peasting, double *pnorthing)
{
	short enr;
	double m, q;
	double sinPhi, E1sinPhi, hv;
	double rho, theta;
	ELLIPSOID *ell;
	DATUMSTRANS *datparam;
	
	datparam = ls_geo_get_datparam(psys->Datum);
	enr = datparam->RefEll;
	ell = ls_geo_get_ellparam(enr);

	M_und_Q(latitude, ell->E1, ell->E1Q, &m, &q);
	sinPhi = sin(latitude);	
	
	E1sinPhi = ell->E1 * sinPhi;
	hv  = 1.0 - ell->E1Q * sinPhi * sinPhi;
	q  = sinPhi / hv;
	q -= log((1.0 - E1sinPhi) / (1.0 + E1sinPhi)) / (2.0 * ell->E1);
	q *= (1.0 - ell->E1Q);
	
	rho = ell->A;
	rho*= sqrt(AlbersE[psys->Proj].C - AlbersE[psys->Proj].n * q) / AlbersE[psys->Proj].n;	
	theta = AlbersE[psys->Proj].n * (longitude - AlbersE[psys->Proj].Lambda_0);
	
	*peasting = rho * sin(theta);
	*pnorthing = AlbersE[psys->Proj].Rho_0 - rho * cos(theta);
	
} /* ****************************Geo2Albers*************************************** */


/*	*****************************************************************************
	* Albers Conical Equal Area Projection - ELLIPSOID - Inverse Equation		*
	*																			*
	* Eingabe:																	*
	* 			double		easting		Easting									*
	* 			double		northing	Northing								*
	* 			KOORDSYSTEM	*psys		Systemparameter							*
	*																			*
	* Ausgabe:																	*
	* 			double		*plongitude	Lgengrad								*
	* 			double		*platitude	Breitengrad								*
	*																			*
	* Status:																	*
	* 			In Arbeit	09.06.96		Peter Clevers						*
	*****************************************************************************
*/
void AlbersEllipsoid2Geo (double *plongitude, double *platitude, const KOORDSYSTEM *psys,
						  double easting,     double northing)
{
	short enr;
	short err = 0, i = 0;
	double hv1, hv2;
	double q, sinPhi;
	double rho, theta;
	double phi;
	ELLIPSOID *ell;
	DATUMSTRANS *datparam;
	
	datparam = ls_geo_get_datparam(psys->Datum);
	enr = datparam->RefEll;
	ell = ls_geo_get_ellparam(enr);
	
	hv1 = AlbersE[psys->Proj].Rho_0 - northing;
	rho = sqrt(easting * easting + hv1 * hv1);
	theta = atan(easting / hv1);

	hv1 = rho * AlbersE[psys->Proj].n / ell->A;
	q   = (AlbersE[psys->Proj].C - hv1 * hv1) / AlbersE[psys->Proj].n;
	
	*plongitude = AlbersE[psys->Proj].Lambda_0 + theta / AlbersE[psys->Proj].n;
	
	/* Bestimmung des Breitengrades durch Iteration */
	/* Startwert der Iteration */;
	*platitude = asin(q / 2.0);
	do
	{
		i++;
		phi = *platitude;
		sinPhi = sin(phi);
		
		hv1 = 1 - ell->E1Q * sinPhi *sinPhi;
		
		hv2  = q / (1 - ell->E1Q);
		hv2 -= sinPhi / hv1;
		hv2 += log((1 - ell->E1 * sinPhi) / (1 + ell->E1 * sinPhi)) / (2 * ell->E1);

		*platitude = phi + hv1 * hv1 / (2.0 * cos(phi)) * hv2;
	} while((fabs(phi-*platitude) > 1.0e-8) && (i < 100));
	
	if (i >= 100)
		err = -1;
} /* ****************************Geo2Albers*************************************** */


/*	*****************************************************************************
	* Berechnung der Parameter: n, C, Rho_0 f die Albersprojection			*
	*																			*
	* Status:																	*
	* 			In Arbeit	09.04.98		Peter Clevers						*
	*****************************************************************************
*/
void Init_AlbersParam()
{
	short enr, i, proj;
	short maxcoord;
	double cosn;
	double R0 = 6371000.0; 
	double m0, m1, m2;
	double q0, q1, q2;
	ELLIPSOID *ell;
	DATUMSTRANS *datum;
	KOORDSTRUCT *coordsys;
	
	/* Initializing of Datum before connecting to real Datum */
	for (i=1; i<MAXALBERSSPHERE; i++)		/* @PC111198 */
	{
		AlbersS[i].Datum = WGS84_BWd;
	}
	
	/* Initializing of Datum before connecting to real Datum */
	for (i=1; i<MAXALBERSELL; i++)		/* @PC111198 */
	{
		AlbersE[i].Datum = WGS84_BWd;
	}
	
	/* Set Datum */
	ls_geo_get_maxcoord(&maxcoord);
	for (i=1; i<maxcoord; i++)
	{
		coordsys = ls_geo_get_coordparam(i);
		
		if (coordsys->Methode == ALBERS_Sm)
		{
			proj = coordsys->Proj;
			AlbersS[proj].Datum = coordsys->Datum;
		}
		else if (coordsys->Methode == ALBERS_Em)
		{
			proj = coordsys->Proj;
			AlbersE[proj].Datum = coordsys->Datum;
		}
	}
	
	/* Albers based on a Sphere */
	for (i=1; i<MAXALBERSSPHERE; i++)		/* @PC290197 */
	{
		datum = ls_geo_get_datparam(AlbersS[i].Datum);
		enr = datum->RefEll;
		ell = ls_geo_get_ellparam(enr);
		
		/* Berechnug von: n */
		AlbersS[i].n = (sin(AlbersS[i].Phi_1) + sin(AlbersS[i].Phi_2)) / 2.0;
		
		/* Berechnug von: C */
		cosn = cos(AlbersS[i].Phi_1);
		AlbersS[i].C = cosn * cosn + 2.0 * AlbersS[i].n * sin(AlbersS[i].Phi_1);
		
		/* Berechnug von: Rho_0 */
		AlbersS[i].Rho_0 = R0 * sqrt(AlbersS[i].C - 2.0 *AlbersS[i].n * sin(AlbersS[i].Phi_0));
		AlbersS[i].Rho_0 /= AlbersS[i].n;
	}
	
	/* Albers based on an Ellipsoid */
	for (i=1; i<MAXALBERSELL; i++)		/* @PC290197 */
	{
		datum = ls_geo_get_datparam(AlbersE[i].Datum);
		enr = datum->RefEll;
		ell = ls_geo_get_ellparam(enr);
		
		M_und_Q(AlbersE[i].Phi_0, ell->E1, ell->E1Q, &m0, &q0);
		M_und_Q(AlbersE[i].Phi_1, ell->E1, ell->E1Q, &m1, &q1);
		M_und_Q(AlbersE[i].Phi_2, ell->E1, ell->E1Q, &m2, &q2);
				
		/* Berechnug von: n */
		AlbersE[i].n = (m1 * m1 - m2 * m2) / (q2 - q1);
		
		/* Berechnug von: C */
		AlbersE[i].C = m1 * m1 + AlbersE[i].n * q1;
		
		/* Berechnug von: Rho_0 */
		AlbersE[i].Rho_0 = ell->A * sqrt(AlbersE[i].C - AlbersE[i].n * q0) / AlbersE[i].n;
	}
} /* ************************InitAlbersParam************************************ */


/*	*****************************************************************************
	* Berechnung der Parameter m und q		  	*
	*																			*
	* Status:																	*
	* 			In Arbeit	09.06.96		Peter Clevers						*
	*****************************************************************************
*/
void M_und_Q(double phi, double E1, double E1Q, double *m, double*q)
{
	double hv, E1sinPhi;
	double sinPhi;
	double cosPhi;
	
	sinPhi = sin(phi);	
	cosPhi = cos(phi);
	
	E1sinPhi = E1 * sinPhi;
	hv  = 1.0 - E1Q * sinPhi * sinPhi;
	
	*m  = cosPhi / sqrt(hv);
	
	*q  = sinPhi / hv;
	*q -= log((1.0 - E1sinPhi) / (1.0 + E1sinPhi)) / (2.0 * E1);
	*q *= (1.0 - E1Q);
} /* ************************InitAlbersParam************************************ */


/*	*****************************************************************************
	* Herauslesen der systemspeziefischen Parameter f	die Albers Projektion	*
	*																			*
	* Status:																	*
	* 			In Arbeit	10.03.97		Peter Clevers						*
	*****************************************************************************
*/
short GetAlbersParam(long proj, ALBERS_T *albers)
{
	if ((proj < 1) || (proj >= MAXALBERSELL))
		return (1); /* Fehler */
		
	albers->Datum    = AlbersE[proj].Datum;
	albers->Phi_1    = AlbersE[proj].Phi_1;
	albers->Phi_2    = AlbersE[proj].Phi_2;
	albers->Phi_0    = AlbersE[proj].Phi_0;
	albers->Lambda_0 = AlbersE[proj].Lambda_0;
	albers->Off_E    = AlbersE[proj].Off_E;
	albers->Off_N    = AlbersE[proj].Off_N;
	
	return (0);
} /* *****************************GetAlbersParam******************************** */





/* 12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
