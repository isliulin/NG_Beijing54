/* entht alle Parameter und Routinen f die
   Koordinaten - Transformations - Methode: 
   		Transversal Merkator.c             */

#include <stdio.h>
#include <math.h>
#include "LS_Koordtrans.h"
/* @TB010998 #include "LS_KoordStructs.h"*/
#include "koosysteme.h"
#include "Transversal_Merkator.h"
/* //@PC080998 #include "KoordTransINIT.h"  */


/* Umrechnung der Zone in den Zentralmeridian */

static void UTM_2_L0(short Zone, double *lambda0)
{
	if (Zone < 0) Zone = Zone + 60;
	if (Zone >= 60) Zone = Zone - 60;
	*lambda0 = ((Zone - 30.0) * 6.0 - 3.0) / RHOG;
}

static void GK6_2_L0(short Zone, double *lambda0)
{
	if (Zone < 0) Zone = Zone + 60;
	if (Zone >= 60) Zone = Zone - 60;
	*lambda0 = (Zone * 6.0 - 3.0) / RHOG;
}

static void GK3_2_L0(short Zone, double *lambda0)
{
	if (Zone < 0) Zone = Zone + 120;
	if (Zone >= 120) Zone = Zone - 120;
	*lambda0 = (Zone * 3.0) / RHOG;
}

static void AMG_2_L0(short Zone, double *lambda0)
{
	*lambda0 = ((Zone - 30.0) * 6.0 - 3.0) / RHOG;
}

static void RSA_2_L0(short Zone, double *lambda0)
{
	if (Zone < 0) Zone = Zone + 360;
	if (Zone >= 360) Zone = Zone - 360;
	*lambda0 = (double) Zone / RHOG;
}

static void BMN_2_L0(short Zone, double *lambda0)
{
	switch (Zone)
	{
		case 0:
		{
				*lambda0 = 10.3333333333333/RHOG;
				break;
		}
		case 1:
		{
				*lambda0 = 13.3333333333333/RHOG;
				break;
		}
		case 2:
		{
				*lambda0 = 16.3333333333333/RHOG;
				break;
		}
	}
}

static void KKJ_2_L0(short Zone, double *lambda0)
{
	switch (Zone)
	{
		case 1:
		{
				*lambda0 = 21.0/RHOG;
				break;
		}
		case 2:
		{
				*lambda0 = 24.0/RHOG;
				break;
		}
		case 3:
		{
				*lambda0 = 27.0/RHOG;
				break;
		}
		case 4:
		{
				*lambda0 = 30.0/RHOG;
				break;
		}
		default:
				*lambda0 = 27.0/RHOG;
	}
}




/* Initialisierung der projektionsabhgigen Parameter */

/* Based on the Ellipsoid */
static TRANSVERSALMERKATORELL  TransMerkE[MAXTRANSMERKATORELL] =		/* @PC290197 */
{/* 								Lambda0				Phi0				M0_E		M0_N		Off_E		Off_N		KZ_E		KZ_N	PM_E	PM_N 	MIN_ZONE	MAXZONE*/
/* 0: undefiniert */	{NULL,		0.0, 				0.0,				0.0,		0.0,		0.0,		0.0,		0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},		
/* 1: USER1 */			{NULL,		0.0, 				0.0,				1.0,		1.0,		0.0,		0.0,		0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},		
/* 2: USER2 */			{NULL,		0.0, 				0.0,				1.0,		1.0,		0.0,		0.0,		0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},		
/* 3: UTM_N */			{UTM_2_L0,	0.0, 				0.0,				0.9996,		0.9996,		500000.0,	0.0,		1000000.0,	0.0,	+1.0,	+1.0,	1.0,		60.0},		
/* 4: UTM_S */			{UTM_2_L0,	0.0, 				0.0,				0.9996,		0.9996,		500000.0,	10000000.0,	1000000.0,	0.0,	+1.0,	+1.0,	1.0,		60.0},	/*  @PC110696 */	
/* 5: GK 3reit */		{GK3_2_L0,	0.0, 				0.0,				1.0,		1.0,		500000.0,	0.0,		1000000.0,	0.0,	+1.0,	+1.0,	1.0,		120.0},		
/* 6: GK 6reit */		{GK6_2_L0,	0.0, 				0.0,				1.0,		1.0,		500000.0,	0.0,		1000000.0,	0.0,	+1.0,	+1.0,	1.0,		60.0},		
/* 7: AMG */			{AMG_2_L0,	0.0, 				0.0,				0.9996,		0.9996,		500000.0,	10000000.0,	0.0,		0.0,	+1.0,	+1.0,	49.0,		57.0},		
/* 8: S Afrika */		{RSA_2_L0,	0.0, 				0.0,				1.0,		1.0,		0.0,		0.0,		0.0,		0.0,	-1.0,	-1.0,	13.0,		35.0},		
/* 9: GauLuxembourg */{NULL,		6.166666666/RHOG,	49.83333333/RHOG,	1.0,		1.0,		80000.0,	-5422420.139,	0.0,	0.0,	+1.0,	+1.0,	0.0,		0.0},		
/*10: GK3 Croatia */	{GK3_2_L0,	0.0,				0.0,				0.9999,		0.9999,		500000.0,	0.0,		1000000.0,	0.0,	+1.0,	+1.0,	5.0,		7.0},	/*  @PC141096 */		
/*11: Central Croatia */{NULL,		16.5/RHOG,			0.0,				0.9999,		0.9999,		500000.0,	0.0,		5500000.0,	0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  @PC141096 */
//edit by jjj 2013.7.25
//*12: Egypt Red Belt */{NULL,		31.0/RHOG,			30.0/RHOG,			1.0,		1.0,		615000.0,	-2510162.0,	0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:810000  @PC151096 */
//*13: Egypt Purple */	{NULL,		27.0/RHOG,			30.0/RHOG,			1.0,		1.0,		700000.0,	-3120162.0,	0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:200000  @PC151096 */
//*14: Extended Purple*/{NULL,		27.0/RHOG,			30.0/RHOG,			1.0,		1.0,		700000.0,	-2120162.0,	0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:1200000 @PC151096 */
/*12: Egypt Red Belt */	{NULL,		31.0/RHOG,			30.0/RHOG,			1.0,		1.0,		615000.0,	810000,		0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:810000  @PC151096 */
/*13: Egypt Purple */	{NULL,		27.0/RHOG,			30.0/RHOG,			1.0,		1.0,		700000.0,	200000.0,	0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:200000  @PC151096 */
/*14: Extended Purple */{NULL,		27.0/RHOG,			30.0/RHOG,			1.0,		1.0,		700000.0,	1200000.0,	0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:1200000 @PC151096 */
/*15: Sweden: RT90    */{NULL,		15.808277778/RHOG,	0.0/RHOG,			1.0,		1.0,		1500000.0,	0.0,		0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:1200000 @PC151096 */
/*16: Austria         */{BMN_2_L0,	0.0,				0.0/RHOG,			1.0,		1.0,		150000.0,	-5000000.0,	0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:1200000 @PC151096 */
/*17: Italy GaussB1	  */{NULL	,	9.0/RHOG,			0.0/RHOG,			0.9996,		0.9996,		1500000.0,	0.0,		0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:1200000 @PC151096 */
/*18: Italy GaussB2	  */{NULL	,	15.0/RHOG,			0.0/RHOG,			0.9996,		0.9996,		2520000.0,	0.0,		0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:1200000 @PC151096 */
/*19: UTM Latvia	  */{NULL	,	24.0/RHOG,			0.0/RHOG,			0.9996,		0.9996,		500000.0,	0.0,		0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:1200000 @PC151096 */
/*20: KKJ Finland	  */{KKJ_2_L0,	0.0,				0.0/RHOG,			1.0,		1.0,		500000.0,	0.0,		1000000.0,	0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:1200000 @PC151096 */
/*21: Portugal System */{NULL,		-8.1319061111/RHOG,	39.6666666667/RHOG,	1.0,		1.0,		200000.0,	-4092078.317,	0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},	/*  False Origin North:1200000 @PC151096 */
//add by jjj 
/*22: UK */				{NULL,		-2/RHOG,			49.0/RHOG,			0.9996012717,0.9996012717,400000.0,	-100000,	0.0,		0.0,	+1.0,	+1.0,	0.0,		0.0},		

};
/*--------------------------------------------------------------------------------------*/

/* Based on the Sphere */
static TRANSVERSALMERKATORSPHERE  TransMerkS[MAXTRANSMERKATORSPHERE] =		/* @PC110598 */
{/* 								Lambda0		Phi0	M0	Off_E	Off_N	KZ_E	KZ_N 	MIN_ZONE	MAXZONE*/
/* 0: undefiniert */	{NULL,		0.0, 		0.0,	0.0,	0.0,	0.0,	0.0,	0.0,	0.0,		0.0},		
/* 1: USER1 */			{NULL,		0.0, 		0.0,	1.0,	0.0,	0.0,	0.0,	0.0,	0.0,		0.0},		
/* 2: USER2 */			{NULL,		0.0, 		0.0,	1.0,	0.0,	0.0,	0.0,	0.0,	0.0,		0.0},		
/* 3: UTM */			{UTM_2_L0,	0.0, 		0.0,	1.0,	0.0,	0.0,	0.0,	0.0,	1.0,		60.0},		
};




/*	*****************************************************************************
	* Based on the Sphere														*
	*																			*
	* Umrechnung von geographischen Koordinaten in Koordinaten, die auf der 	*
	* transversalen Merkatorprojektion beruhen.									*
	*																			*
	* Eingabe:																	*
	* 			double		longitude	Lgengrad								*
	* 			double		latitude	Breitengrad								*
	* 			KOORDSYSTEM	*psys			Systemparameter						*
	*																			*
	* Ausgabe:																	*
	* 			double		*peasting	Easting									*
	* 			double		*pnorthing	Northing								*
	*																			*
	* Status:																	*
	* 			In Arbeit	18.01.96		Peter Clevers						*
	*****************************************************************************
*/
void Geo2TransMerkSphere (double longitude, double latitude, const KOORDSYSTEM *psys,
						  double *peasting, double *pnorthing)
{
	double R0 = 6371000.0;
/*	double R0 = 1.0;	*/
	double B;
	double deltalambda, atanh_B;
	double R0k0;
	
	/* Berechnung des Mittelmeridians aus der Zonennummer */
	if (TransMerkS[psys->Proj].Zone2L0 != NULL)
		TransMerkS[psys->Proj].Zone2L0 (psys->Zone, &(TransMerkS[psys->Proj].Lambda0));

	deltalambda = longitude - TransMerkS[psys->Proj].Lambda0;
	R0k0 = R0 * TransMerkS[psys->Proj].M0;
	
	B = cos(latitude) * sin(deltalambda);
	
	atanh_B = log((1 + B) / (1 - B));
	*peasting = 0.5 * R0k0 * atanh_B;
	
	*pnorthing = atan(tan(latitude) / cos(deltalambda)) - TransMerkS[psys->Proj].Phi0;
	*pnorthing *= R0k0;
}


/*	*****************************************************************************
	* Based on the Sphere														*
	*																			*
	* Umrechnung von Koordinaten, die auf der transversalen Merkatorprojektion	*
	* beruhen, in geographische Koordinaten.									*
	*																			*
	* Eingabe:																	*
	* 			double		easting		Easting									*
	* 			double		northing	Northing								*
	* 			KOORDSYSTEM	*psys			Systemparameter						*
	*																			*
	* Ausgabe:																	*
	* 			double		*plongitude	Lgengrad								*
	* 			double		*platitude	Breitengrad								*
	*																			*
	* Status:																	*
	* 			In Arbeit	18.01.96		Peter Clevers						*
	*****************************************************************************
*/
void TransMerkSphere2Geo (double *plongitude, double *platitude, const KOORDSYSTEM *psys,
						  double easting,     double northing)
{
	double R0 = 6371000.0;
/*	double R0 = 1.0;	*/
	double D;
	double R0k0;
	
	/* Berechnung des Mittelmeridians aus der Zonennummer */
	if (TransMerkS[psys->Proj].Zone2L0 != NULL)
		TransMerkS[psys->Proj].Zone2L0 (psys->Zone, &(TransMerkS[psys->Proj].Lambda0));

	R0k0 = R0 * TransMerkS[psys->Proj].M0;
	
	D = northing / R0k0 + TransMerkS[psys->Proj].Phi0;
	
	*platitude = asin(sin(D) / cosh(easting / R0k0));
	*plongitude = TransMerkS[psys->Proj].Lambda0 + atan2(sinh(easting / R0k0), cos(D));
}

/*	*****************************************************************************
	* Umrechnung von geographischen Koordinaten in Koordinaten, die auf der 	*
	* transversalen Merkatorprojektion beruhen.									*
	*																			*
	* Eingabe:																	*
	* 			double		longitude	Lgengrad								*
	* 			double		latitude	Breitengrad								*
	* 			KOORDSYSTEM	*psys			Systemparameter						*
	*																			*
	* Ausgabe:																	*
	* 			double		*peasting	Easting									*
	* 			double		*pnorthing	Northing								*
	*																			*
	* Status:																	*
	* 			In Arbeit	18.01.96		Peter Clevers						*
	*****************************************************************************
*/
void Geo2TransMerkEll (double longitude, double latitude, const KOORDSYSTEM *psys,
					   double *peasting, double *pnorthing)
{
	double	sinB, cosB, tanB, tanB2, tanB4;
	double	G, eta2, N, Nt, dl, B;
	double	dlcosB, dlcosB2, dlcosB3, dlcosB4, dlcosB5, dlcosB6, dlcosB7;
	double	hv1, hv2;
	short 	enr;
	ELLIPSOID *ell;
	DATUMSTRANS *datparam;
	//add by jjj 2013.7.23 
	double G0 = 0;
	
	datparam = ls_geo_get_datparam(psys->Datum);
	enr = datparam->RefEll;
	ell = ls_geo_get_ellparam(enr);
	
		B = latitude;
	sinB  = sin(B);                  /* Konstanten und Vorausberechnungen*/
	cosB  = cos(B);
	tanB  = sinB / cosB;
	tanB2 = tanB * tanB;
	tanB4 = tanB2 * tanB2;

	eta2 = ell->E1Q / (1.0 - ell->E1Q) * cosB * cosB;
	N    = ell->A / sqrt(1.0 - ell->E1Q * sinB * sinB);
	Nt   = N * tanB;

	/* Berechnung des Mittelmeridians aus der Zonennummer */
	if (TransMerkE[psys->Proj].Zone2L0 != NULL)
		TransMerkE[psys->Proj].Zone2L0 (psys->Zone, &(TransMerkE[psys->Proj].Lambda0));

	dl      = longitude - TransMerkE[psys->Proj].Lambda0;         	/* Reduktion auf Bezugsmeridian */
	dlcosB  = dl * cosB;
	dlcosB2 = dlcosB  * dlcosB;
	dlcosB3 = dlcosB2 * dlcosB;
	dlcosB4 = dlcosB2 * dlcosB2;
	dlcosB5 = dlcosB3 * dlcosB2;
	dlcosB6 = dlcosB3 * dlcosB3;
	dlcosB7 = dlcosB4 * dlcosB3;

	Geo2Meri(B, &G, ell->A, ell->N);     /* Meridianbogenlaenge */
	//add by jjj 2013.7.23
	Geo2Meri(TransMerkE[psys->Proj].Phi0, &G0, ell->A, ell->N);

	hv1 = (5.0 - tanB2 + 9.0 * eta2 ) * dlcosB4;
	hv2 = (61.0 - 58.0 * tanB2 + tanB4 + 270.0 * eta2
			  - 330.0 * tanB2 * eta2 ) * dlcosB6;

	//edit by jjj 2013.7.23
/*	*pnorthing = psys->Zone * TransMerkE[psys->Proj].KZ_N 
							+ TransMerkE[psys->Proj].Off_N
				       		+ TransMerkE[psys->Proj].M0_N
				       		* (G + Nt / 2.0 * dlcosB2
                  		         + Nt / 24.0 * hv1
                  		         + Nt / 720.0 * hv2);*/

	*pnorthing = psys->Zone * TransMerkE[psys->Proj].KZ_N 
							+ TransMerkE[psys->Proj].Off_N
				       		+ TransMerkE[psys->Proj].M0_N
		* (G - G0 + Nt / 2.0 * dlcosB2
                  		         + Nt / 24.0 * hv1
                  		         + Nt / 720.0 * hv2);


	hv1 = (5.0 - 18 * tanB2 + tanB4 + 14.0 * eta2 - 58 * tanB2 * eta2) * dlcosB5;
	hv2 = (61.0 - 479 * tanB2 + 179 * tanB4 ) * dlcosB7;

	*peasting = psys->Zone * TransMerkE[psys->Proj].KZ_E
						   + TransMerkE[psys->Proj].Off_E
						   + TransMerkE[psys->Proj].M0_E
						   * (N * dlcosB + N / 6.0 * (1.0 - tanB2 + eta2) * dlcosB3
                           				 + N / 120.0 * hv1
                           				 + N / 5040.0 * hv2);

	if (psys->Proj == TM_AUSTRIAp)
		*peasting  += psys->Zone * 300000.0;
		
	*pnorthing *= TransMerkE[psys->Proj].PM_N;
	*peasting  *= TransMerkE[psys->Proj].PM_E;
} /* ************************Geo2TransMerk*************************************** */

/*	*****************************************************************************
	* Umrechnung von Koordinaten, die auf der transversalen Merkatorprojektion	*
	* beruhen, in geographische Koordinaten.									*
	*																			*
	* Eingabe:																	*
	* 			double		easting		Easting									*
	* 			double		northing	Northing								*
	* 			KOORDSYSTEM	*psys			Systemparameter						*
	*																			*
	* Ausgabe:																	*
	* 			double		*plongitude	Lgengrad								*
	* 			double		*platitude	Breitengrad								*
	*																			*
	* Status:																	*
	* 			In Arbeit	18.01.96		Peter Clevers						*
	*****************************************************************************
*/
void TransMerkEll2Geo (double *plongitude, double *platitude, const KOORDSYSTEM *psys,
					   double easting,     double northing)
{
	short 	enr;
	double	B, C, eta2;
	double	sinB, cosB, tanB, tanB2, tanB4;
	double	N, N2, N3, N4, N5, N6, N7;
	ELLIPSOID *ell;
	DATUMSTRANS *datparam;
	//add by jjj 2013.7.23
	double	G0 = 0;
	
	datparam = ls_geo_get_datparam(psys->Datum);
	enr = datparam->RefEll;
	ell = ls_geo_get_ellparam(enr);

	//add by jjj 2013.7.23
	Geo2Meri(TransMerkE[psys->Proj].Phi0, &G0, ell->A, ell->N);

	easting  *= TransMerkE[psys->Proj].PM_E;
	if (psys->Proj == TM_AUSTRIAp)
		easting -= psys->Zone * 300000.0;
	easting = (easting - psys->Zone * TransMerkE[psys->Proj].KZ_E
	                   - TransMerkE[psys->Proj].Off_E) / TransMerkE[psys->Proj].M0_E;
	northing *= TransMerkE[psys->Proj].PM_N;
	northing = (northing - psys->Zone * TransMerkE[psys->Proj].KZ_N
	                     - TransMerkE[psys->Proj].Off_N) / TransMerkE[psys->Proj].M0_N;

	/* Breite des Fusspunktes aus Meridianbogenlaenge */
	//edit by jjj 2013.7.23
	//Meri2Geo(&B, northing, ell->A, ell->N);
	Meri2Geo(&B, northing+G0, ell->A, ell->N);

	sinB = sin(B);          /* Konstanten und Vorausberechnungen */
	cosB = cos(B);
	tanB = sinB / cosB;
	tanB2   = tanB * tanB;
	tanB4   = tanB2 * tanB2;

	eta2 = ell->E1Q / (1.0 - ell->E1Q) * cosB * cosB;
	N    = ell->A / sqrt(1.0 - ell->E1Q * sinB * sinB);
	N  	 = easting / N;
	N2   = N * N;
	N3   = N2 * N;
	N4   = N2 * N2;
	N5   = N3 * N2;
	N6   = N3 * N3;
	N7   = N4 * N3;

	C    = 1.0 / cosB;

	*platitude = B - tanB /   2.0 * (1.0 + eta2) * N2
         		   + tanB /  24.0 * (5.0 + 3.0 * tanB2 + 6.0 * eta2 - 6.0 * tanB2 * eta2) * N4
          	 	   - tanB / 720.0 * (61.0 + 90.0 * tanB2 + 45.0 * tanB4) * N6;

	/* Berechnung des Mittelmeridians aus der Zonennummer */
	if (TransMerkE[psys->Proj].Zone2L0 != NULL)
		TransMerkE[psys->Proj].Zone2L0 (psys->Zone, &(TransMerkE[psys->Proj].Lambda0));

	*plongitude = TransMerkE[psys->Proj].Lambda0
					+ C * N
             		- C /   6.0 * (1.0 + 2.0 * tanB2 + eta2) * N3
               		+ C / 120.0 * (5.0 + 28 * tanB2 + 24.0 * tanB4) * N5
             		- C / 240.0 * (61.0 + 662 * tanB2 + 1320.0 * tanB4 
                                    	+ 720.0 * tanB2 * tanB4) * N7;

} /* ************************TransMerk2Geo*************************************** */

/*	*****************************************************************************
	* Berechnung der Meridianbogenlge aus der geographischen Breite			*
	*																			*
	* Eingabe:																	*
	* 			double		B			Latitude								*
	* 			double		a			Gro Halbachse des Ellipsoiden			*
	* 			double		n			(a-b) / (a+b)							*
	*																			*
	* Ausgabe:																	*
	* 			double		*G			Meridianbogenlge						*
	*																			*
	* Status:																	*
	* 			In Arbeit	18.01.96		Peter Clevers						*
	*****************************************************************************
*/
void Geo2Meri (double B, double *G, double a, double n)

{
   double n2, n3;

   n2  = n * n;
   n3  = n * n2;

   *G = a / (1 + n) * ((1.0 + n * n / 4.0) * B
     		 -  3.0 /  2.0 * (n - n3  / 8.0) * sin(2.0 * B)
      		 + 15.0 / 16.0 * n2              * sin(4.0 * B)
      		 - 35.0 / 48.0 * n3              * sin(6.0 * B));

} /* ******************************Geo2Meri************************************** */


/*	*****************************************************************************
	* Berechnung der geographischen Breite aus der Meridianbogenlge			*
	*																			*
	* Eingabe:																	*
	* 			double		G			Meridianbogenl”nge						*
	* 			double		a			Groþe Halbachse des Ellipsoiden			*
	* 			double		n			(a-b) / (a+b)							*
	*																			*
	* Ausgabe:																	*
	* 			double		*B			Latitude								*
	*																			*
	* Status:																	*
	* 			In Arbeit	18.01.96		Peter Clevers						*
	*****************************************************************************
*/
void Meri2Geo(double *B, double G, double a, double n)

{
   double n2, n3, n4;
   double BB;

   n2  = n  * n;
   n3  = n2 * n;
   n4  = n2 * n2;

   BB = G * (1.0 + n) / (1.0 + n2 / 4.0 + n4 / 64.0) / a;
	/* 1. Nerung */
   *B = BB +   3.0 /  2.0 * (n - 9.0 / 16.0 * n3) * sin(2.0 * BB)
  		   +  21.0 / 16.0 * n2					  * sin(4.0 * BB)
  		   + 151.0 / 96.0 * n3					  * sin(6.0 * BB);

} /* ******************************Meri2Geo************************************** */



/*	*****************************************************************************
	* Gibt die minimale und maximale nutzbare Zonennummer f¸r die benutzte		*
	* Projectionsart zur¸ck.													*
	*																			*
	* Eingabe:																	*
	* 			short		proj		Projectionsart							*
	*																			*
	* Ausgabe:																	*
	* 			double		*MinZone	Minimale Zonennummer					*
	* 			double		*MaxZone	Maximale Zonennummer					*
	*																			*
	* Status:																	*
	* 			In Arbeit	18.01.96		Peter Clevers						*
	*****************************************************************************
*/
void GetZoneRange(short proj, double *MinZone, double *MaxZone)

{
	*MinZone = TransMerkE[proj].MIN_ZONE;
	*MaxZone = TransMerkE[proj].MAX_ZONE;
} /* ******************************Meri2Geo************************************** */


/*	*****************************************************************************
	* Herauslesen der systemspeziefischen Parameter f	die Transversal			*
	* Merkator Projektion														*
	*																			*
	* Status:																	*
	* 			In Arbeit	10.03.97		Peter Clevers						*
	*****************************************************************************
*/
short GetTransMerkParam(short proj, short zone , TRANSVERSALMERKATORELL *transm)
{
	if ((proj < 1) || (proj >= MAXTRANSMERKATORELL))
		return (1); /* Fehler */
		
	if (TransMerkE[proj].Zone2L0 != NULL)
	TransMerkE[proj].Zone2L0 (zone, &(TransMerkE[proj].Lambda0));
	
	transm->Lambda0 = TransMerkE[proj].Lambda0;
	transm->Phi0 = TransMerkE[proj].Phi0;
	transm->M0_E      = TransMerkE[proj].M0_E;
	transm->M0_N      = TransMerkE[proj].M0_N;
	transm->Off_E     = TransMerkE[proj].Off_E;
	transm->Off_N     = TransMerkE[proj].Off_N;
	transm->KZ_E      = TransMerkE[proj].KZ_E;
	transm->KZ_N      = TransMerkE[proj].KZ_N;
	transm->PM_E      = TransMerkE[proj].PM_E;
	transm->PM_N      = TransMerkE[proj].PM_N;
	
	return (0);
} /* ****************************GetTransMerkParam******************************* */


/* 12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
