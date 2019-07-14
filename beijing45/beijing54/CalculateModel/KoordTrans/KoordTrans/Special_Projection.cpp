/* *****************************************************************************
 *
 *  Datei: Special_projection.c
 *         Unterprogramme zur Koordinatentransformation
 *  Datum: 09.07.97
 *  ?by:  L&S Hochfrequenztechnik GmbH 1993, 1997
 *    
 **************************************************************************** */
#include <math.h>
#include "LS_Koordtrans.h"
/* //@TB010998 #include "LS_KoordStructs.h"*/
#include "koosysteme.h"
#include "Special_Projection.h"
/* //@PC080998 #include "KoordTransINIT.h"  */

/*****************************************************************************/
/*  Routine : void Geo2IreGrid                                               */
/*---------------------------------------------------------------------------*/
/*  Beschreibung :  Rechnet Koordinaten vom Ireland Grid in Geo-System um    */
/*                                                                           */
/*      Author   : Caitriona Quinn                                           */
/*      Date     : 16th June, 1994                                           */
/*      Note     : All calculations are taken from:                          */      
/*               : Series D, Geophysical Bulletin No. 35.                    */
/*               : 'The Geographical and Rectangular Coordinates in use in   */
/*               :  Ireland and their Transformations' by THOMAS MURPHY.     */
/*               : The Dublin Institute for Advanced Studies, 1982.          */
/*     Accuracy  : +/- 0.01m.                                                */
/*---------------------------------------------------------------------------*/
/*  erstellt         : Peter Clevrs                     Datum : 13-02-1995   */
/*  letzte Aenderung :                                  Datum :              */
/*---------------------------------------------------------------------------*/
/*  Eingabe-variable :                                                       */
/*    double      LAT_PT    : LAT_PT. A similar process is used for          */
/*                              the Longitude.                               */
/*    double      LONG_PT   : Longitude of a point measured East             */
/*                              (+) or West (-) of Greenwich                 */
/*                                                                           */
/*  Ausgabe-variable :                                                       */
/*    double      *EAST       Irish Grid Easting (metres)                    */
/*    double      *NORTH      Irish Grid Northing (metres)                   */
/*                                                                           */
/*  interne Routinenaufrufe :                                                */
/*                                                                           */
/*****************************************************************************/

/*-----------------------Spheroid = Airy (modified)------------------------*/

void Geo2IreGrid(double  LONG_PT,  double  LAT_PT, const KOORDSYSTEM *psys,
				 double *pEASTING, double *pNORTHING)
{
   /*------------------Declare Variables to be Calculated------------------*/
   double     P;            /* (0.36x (Lat.pt degs - Lat.origin degs))   */
   double     P2;           /* P squared                                 */
   double     P3;           /* P cubed                                   */
   double     P4;           /* P power 4                                 */
   double     P5;           /* P power 5                                 */

   double     LAT_50_DEG;   /*Lat of pt in degrees - 50                  */
   double     LAT_50_DEG2;  /*LAT_50_DEG squared                         */
   double     LAT_50_DEG3;  /*LAT_50_DEG cubed                           */

   /*----------------------Calculations------------------------------------*/
	(void)psys;


   /* Umrechnung von Bogenmain Grad */
   LONG_PT *= RHOG;
   LAT_PT  *= RHOG;

   LAT_50_DEG=(LAT_PT-50.0);
   LAT_50_DEG2=(LAT_50_DEG*LAT_50_DEG);
   LAT_50_DEG3=(LAT_50_DEG2*LAT_50_DEG);

   P=0.36*(LONG_PT+8.0);
   P2=(P*P);
   P3=(P2*P);
   P4=(P3*P);
   P5=(P4*P);

   *pEASTING=((P*(199135.366-(4130.362*LAT_50_DEG)-(30.68*LAT_50_DEG2)+(0.22*LAT_50_DEG3)))
             -(P3*(13.4378+(2.4304*LAT_50_DEG)-(0.07304*LAT_50_DEG2)))-(P5*(0.026))+200000.0);

   *pNORTHING=(-139384.421+(111219.253*LAT_50_DEG)+(9.666*LAT_50_DEG2)-(0.032*LAT_50_DEG3))
               +(P2*(3697.809-(22.5126*LAT_50_DEG)-(2.27085*LAT_50_DEG2)+(0.007633*LAT_50_DEG3)))
               +(P4*(1.0807-(0.0839*LAT_50_DEG)+(0.00067*LAT_50_DEG2)));
}
/*****************************************************************************/
/*  Ende: void Geo2IreGrid                                                   */
/*****************************************************************************/

/*****************************************************************************/
/*  Routine : void IreGrid2Geo                                               */
/*---------------------------------------------------------------------------*/
/*  Beschreibung :  Rechnet Koordinaten vom Ireland Grid in Geo-System um    */
/*                                                                           */
/*      Author   : Caitriona Quinn                                           */
/*      Date     : 16th June, 1994                                           */
/*      Note     : All calculations are taken from:                          */      
/*               : Series D, Geophysical Bulletin No. 35.                    */
/*               : 'The Geographical and Rectangular Coordinates in use in   */
/*               :  Ireland and their Transformations' by THOMAS MURPHY.     */
/*               : The Dublin Institute for Advanced Studies, 1982.          */
/*     Accuracy  : +/- 0.01m.                                                */
/*---------------------------------------------------------------------------*/
/*  erstellt         : Peter Clevrs                     Datum : 13-02-1995   */
/*  letzte Aenderung :                                  Datum :              */
/*---------------------------------------------------------------------------*/
/*  Eingabe-variable :                                                       */
/*    double      LAT_PT    : LAT_PT. A similar process is used for          */
/*                              the Longitude.                               */
/*    double      LONG_PT   : Longitude of a point measured East             */
/*                              (+) or West (-) of Greenwich                 */
/*                                                                           */
/*  Ausgabe-variable :                                                       */
/*    double      *EAST       Irish Grid Easting (metres)                    */
/*    double      *NORTH      Irish Grid Northing (metres)                   */
/*                                                                           */
/*  interne Routinenaufrufe :                                                */
/*                                                                           */
/*****************************************************************************/

/*-----------------------Spheroid = Airy (modified)------------------------*/

void IreGrid2Geo(double *LONG_PT, double *LAT_PT, const KOORDSYSTEM *psys,
                 double  EASTING, double  NORTHING)
{
   /*------------------Declare Variables to be Calculated------------------*/
   double       Q, Q2, Q3, Q4, Q5, Q6;      /* Q, Q squared, Q cubed etc.*/

   double     L1;               /*Must be determined before calculating L*/
   double     L;                /*Used in the calcs for LAT and LONG     */
   double     L2;               /*L squared*/
   double     L3;               /*L cubed*/
   double     L50;              /*L - 50 in degrees*/
   double     L50rads;          /*L - 50 in radians*/

   double     a, b, c, d, e, f; /*Declared to clarify calcs for LAT/LONG */
   double     x, y;             /*Variables also used to clarify calcs   */

   /*---------------Declare known calculation parameters-------------------*/
   double       TEN_BASE_MINUS6 = 0.000001;
   double       TEN_BASE_MINUS9 = 0.000000001;

   /*----------------------Calculations-----------------------------------*/

	(void)psys;

   Q =((EASTING*TEN_BASE_MINUS6)-0.2);
   Q2 = Q*Q;
   Q3 = Q2*Q;
   Q4 = Q3*Q;
   Q5 = Q4*Q;
   Q6 = Q5*Q;

   L1=((3.016298902*TEN_BASE_MINUS9*(NORTHING+139384.421))+1);
   L1=(sqrt(L1));
   L1=(5961.716828*(L1-1));

   L =(NORTHING+139384.421-(111219.253*L1)-(9.666*L1*L1)+(0.032*L1*L1*L1));
   L =(L1+(0.00000896*L));
   L2 = (L*L);
   L3 = (L*L*L);
   L50 = (L+50);
   L50rads = (L50/RHOG);

   /*------- a, b and c are used in the calcs for Latitude ----------------*/
   a=(3018.138+(106.584*L)+(2.0705*L2)+(0.0815*L3));
   b=(57.2+(3.489*L)+(0.281*L2));
   c=(1.34+(0.24*L));

   *LAT_PT=(L50+(0.000277777*(-(Q2*a)+(Q4*b)-(Q6*c))));

   /*------- x, y, d, e and f are used in the calcs for Longitude ---------*/
   x=(tan(L50rads));
   y = ((0.99332946*(x*x))+1);

   d=(sqrt(y));
   e=(786.98+(58.579*L)+(2.4*L2)+(0.2109*L3));
   f=(24.1+(2.2*L)+(0.4*L2));

   *LONG_PT=(-8+(0.000277777*((32342.25885*Q*d)-(Q3*e)+(Q5*f))));

   /* Umrechnung von Grad in Bogenma?*/
   *LONG_PT /= RHOG;
   *LAT_PT  /= RHOG;
}
/*****************************IreGrid2Geo***************************************/



/*	*****************************************************************************
	* Konvertierung von Geo-Koordinaten in Rijksdriehoek-Koordinaten			*
	*																			*
	* Eingabe:																	*
	* 			double		longitude		Lonigtude							*
	* 			double		latitude		Latitude							*
	*																			*
	* Ausgabe:																	*
	* 			double		*peasting		Easting								*
	* 			double		*pnorthing		Northing							*
	*																			*
	* Status:																	*
	* 			In Arbeit	18.01.96		Peter Clevers						*
	*****************************************************************************
*/
void Geo2Rdalt(double  longitude, double  latitude, const KOORDSYSTEM *psys,
			double *peasting,  double *pnorthing)
{
   double x, y, xd, yd;
   double x1, al1, b1;
   double r, r2, r3;
   double s, s2, s3;
   double t, t1;

	(void)psys;
		 
   /* Umrechnung von Bogenma?in Grad */
   x   = longitude * RHOG;
   y   = latitude * RHOG;
   
   
   /* Umrechnung von Geo-Dezimal in Sexagesimal */
	 Dez2Sexa (x, &x);
	 Dez2Sexa (y, &y);
	
   xd  = x - floor(x);
   yd  = y - floor(y);

   x1  = (3.0 * floor(x) / 5.0 + xd) * 100.0;
   al1 = 3.0 * floor(x1) / 5.0 + (x1 - floor(x1));

   x1  = (3.0 * floor(y) / 5.0 + yd) * 100.0;
   b1  = 3.0 * floor(x1) / 5.0 + (x1 - floor(x1));

   r   = (al1 - 193.9550) / 100.0;
   r2  = r*r;
   r3  = r2*r;

   s   = (b1 - 1877.621780) / 100.0;
   s2  = s*s;
   s3  = s2*s;

   t   = 190066.910 * r;
   t  -=  11831.0   * r * s;
   t  -=    114.20  * s2 * r;
   t  -=     32.390 * r3;
   t  -=      2.330 * s3 * r;
   t  -=      0.610 * s * r3;

   t1  = 309020.340 * s;
   t1 +=   3638.360 * r2;
   t1 +=     72.920 * s2;
   t1 -=    157.970 * s * r2;
   t1 +=     59.770 * s3;
   t1 +=      0.090 * r2 * r2;
   t1 -=      6.450 * r2 * s2;
   t1 +=      0.070 * s2 * s2;

/* Ausgabe in Kilometer
   *peasting = t  / 1000.0 + 155.0;
   *pnorthing = t1 / 1000.0 + 463.0;
*/

	 /* Ausgabe in Meter */
   *peasting = t   + 155000.0;
   *pnorthing = t1 + 463000.0;

} /* ********************************Geo2Rdalt*********************************** */



/*	*****************************************************************************
	* Konvertierung von Geo-Koordinaten in Rijksdriehoek-Koordinaten			*
	*																			*
	* Eingabe:																	*
	* 			double		longitude		Lonigtude							*
	* 			double		latitude		Latitude							*
	*																			*
	* Ausgabe:																	*
	* 			double		*peasting		Easting								*
	* 			double		*pnorthing		Northing							*
	*																			*
	* Status:																	*
	* 			In Arbeit	02.07.97		Peter Clevers						*
	*****************************************************************************
*/
void Geo2Rd(double  longitude, double  latitude, const KOORDSYSTEM *psys,
			double *peasting,  double *pnorthing)
{
   double x, y;
   double al1, b1;
   double r, r2, r3;
   double s, s2, s3;
   double t, t1;

	(void)psys;
	
   /* Umrechnung von Bogenmain Grad */
   x   = longitude * RHOG;
   y   = latitude * RHOG;
   
   
   al1 = x * 36.0;
   b1  = y * 36.0;
   
   r   = (al1 - 193.9550) / 100.0;
   r2  = r*r;
   r3  = r2*r;

   s   = (b1 - 1877.621780) / 100.0;
   s2  = s*s;
   s3  = s2*s;

   t   = 190066.910 * r;
   t  -=  11831.0   * r * s;
   t  -=    114.20  * s2 * r;
   t  -=     32.390 * r3;
   t  -=      2.330 * s3 * r;
   t  -=      0.610 * s * r3;

   t1  = 309020.340 * s;
   t1 +=   3638.360 * r2;
   t1 +=     72.920 * s2;
   t1 -=    157.970 * s * r2;
   t1 +=     59.770 * s3;
   t1 +=      0.090 * r2 * r2;
   t1 -=      6.450 * r2 * s2;
   t1 +=      0.070 * s2 * s2;

/* Ausgabe in Kilometer
   *peasting = t  / 1000.0 + 155.0;
   *pnorthing = t1 / 1000.0 + 463.0;
*/

	 /* Ausgabe in Meter */
   *peasting = t   + 155000.0;
   *pnorthing = t1 + 463000.0;

} /* ********************************Geo2Rd************************************** */



/*	*****************************************************************************
	* Konvertierung von Rijksdriehoek-Koordinaten in Geo-Koordinaten			*
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
	* 			fertig		06.02.96		Peter Clevers						*
	*****************************************************************************
*/
void Rd2Geo(double *plongitude, double *platitude, const KOORDSYSTEM *psys,
			double  easting,    double  northing)
{
   double x1, x2, x3;
   double y1, y2, y3;
   double rh, rh1;

	(void)psys;

	/* Umrechnung in Kilometer */
	 easting  /= 1000.0;
	 northing /= 1000.0;
	 
   x1 = (easting-155.0)/100.0;
   x2 = x1*x1;
   x3 = x2*x1;

   y1 = (northing-463.0)/100.0;
   y2 = y1*y1;
   y3 = y2*y1;

   rh  = 3236.0330*y1;
   rh -= 32.5920*x2;
   rh -= 0.2470*y2;
   rh -= 0.850*x2*y1;
   rh -= 0.0650*y3;
   rh += x2*x2*0.0050;
   rh -= 0.0170*x2*y2;

   rh1  = 5261.3050*x1;
   rh1 += 105.9790*x1*y1;
   rh1 += 2.4580*x1*y2;
   rh1 -= 0.8190*x3;
   rh1 += 0.0560*x1*y3;
   rh1 -= 0.0560*x3*y1;

   *plongitude =  5.3876388890 + rh1 / 3600.0;
   *platitude  = 52.156160560  + rh  / 3600.0;

   /* Umrechnung von Grad in Bogenma?*/
   *plongitude /=  RHOG;
   *platitude  /= RHOG;

} /* ********************************Rd2Geo************************************** */



#define  e2 0.0067192187732591
#define  cc  6398786.84799183



/*	*****************************************************************************
	* Konvertierung von Geo-Koordinaten in           							*
	* terreichische Bundesmeldenetzkoordinaten								*
	*																			*
	* 			double		longitude		Lonigtude							*
	* 			double		latitude		Latitude							*
	*																			*
	* Ausgabe:																	*
	* 			double		*peasting		Easting								*
	* 			double		*pnorthing		Northing							*
	*																			*
	* Status:																	*
	* 			In Arbeit	22.09.97		Peter Clevers						*
	*****************************************************************************
*/
void Geo2Bundesmeldenetz(double  longitude, double  latitude, const KOORDSYSTEM *psys,
			             double *peasting,  double *pnorthing)
{
	double V, S;
	double l;
	double x, y;
	double CB, t, nu2, N;
	int mer;

	(void)psys;
	
	V = latitude;
	CB = cos(V);
	t = sin(V) / CB;
	nu2 = e2 * CB * CB;
	N = cc / sqrt(1.0 + nu2);
	l = longitude * RHOG;
	l = l - (31.0 / 3.0);
	
	mer = 3;
	if (l <= 1.5)
		mer = 0;
	if (l > 4.5)
		mer = 6;
		
	l = l - mer;
	
	/* y */
	y = (l * N * CB / RHOG) +
	    (l * l * l * N * CB * CB * CB) * (1.0 - t * t + nu2) / (6.0 * RHOG * RHOG * RHOG);
	    
	if (y > 120000.0)
	{
		mer = mer + 3;
		l = l - 3.0;
		y = (l * N * CB / RHOG) +
		    (l * l * l * N * CB * CB * CB) * (1.0 - t * t + nu2) / (6.0 * RHOG * RHOG * RHOG);
	}
	else if (y < -110000.0)
	{
		mer = mer - 3;
		l = l + 3.0;
		y = (l * N * CB / RHOG) +
		    (l * l * l * N * CB * CB * CB) * (1.0 - t * t + nu2) / (6.0 * RHOG * RHOG * RHOG);
	};
	
	/* x */
	S = 111120.619608 * latitude * RHOG - 15988.6383 * sin(2.0 * V)
	                      + 16.73 * sin(4.0 * V)
	                      - 0.0218 * sin(6.0 * V);
	
	x = S + (l * l * N * CB * CB * t) / (2.0 * RHOG * RHOG)
	      + (l * l * l * l * N * CB * CB * CB * CB * t)
	        * (5.0 - t * t + 9.0 * nu2)
	        / (24.0 * RHOG * RHOG * RHOG * RHOG);
	        
	*peasting = y + mer * 100000 + 150000;
	*pnorthing = x - 5000000;
	
} /* ***************************Geo2Bundesmeldenetz****************************** */


/*	*****************************************************************************
	* Konvertierung von terreicischen Bundesmeldenetzkoordinaten in           *
	* Geo-Koordinaten															*
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
	* 			fertig		06.02.96		Peter Clevers						*
	*****************************************************************************
*/
void Bundesmeldenetz2Geo(double *plongitude, double *platitude, const KOORDSYSTEM *psys,
			             double  easting,    double  northing)
{
	double x, y;
	double BF, NF, rl;
	double sigma, tF, nuF2;
	double sinBF, cosBF;
	int mer;

	(void)psys;
	
	mer = 3;
	if ( easting <= 300000.0)
		mer = 0;
	if ( easting >= 600000.0)
		mer = 6;
	
	x = northing + 5000000.0;
	y = easting - 150000.0 - mer * 100000.0;
	
	/* inverse northing */
	sigma = x /111120.619608;
	BF = sigma + 0.143885358 * sin(2.0 * sigma / RHOG)
	           + 0.000210779 * sin(4.0 * sigma / RHOG)
	           + 0.000000423 * sin(6.0 * sigma / RHOG);
	sinBF = sin(BF / RHOG);
	cosBF = cos(BF / RHOG);
	tF = sinBF / cosBF;
	nuF2 = e2 * cosBF * cosBF;
	NF = cc / sqrt(1.0 + nuF2);
	*platitude = BF - (RHOG * tF * (1.0 + nuF2) * y * y / (2.0 * NF * NF));
	
	/* inverse easting */
	rl = y * RHOG / (NF * cosBF);
	rl = rl - y * y * y * RHOG * (1.0 + 2.0 * tF * tF + nuF2)
	                       / (6.0 * NF * NF * NF * cosBF);
	*plongitude = rl + mer + (31.0 / 3.0);
	
	/* Umrechnung in Bogenma*/
	*plongitude /= RHOG;
	*platitude  /= RHOG;
	

} /* **************************Bundesmeldenetz2Geo******************************* */



/*	*****************************************************************************
	* Konvertierung von Geo-Koordinaten in           							*
	* Ungarissche EOV-Koordinaten												*
	*																			*
	* 			double		longitude		Lonigtude							*
	* 			double		latitude		Latitude							*
	*																			*
	* Ausgabe:																	*
	* 			double		*peasting		Easting								*
	* 			double		*pnorthing		Northing							*
	*																			*
	* Status:																	*
	* 			In Arbeit	03.05.99		Peter Clevers						*
	*****************************************************************************
*/
void Geo2EOV(double  longitude, double  latitude, const KOORDSYSTEM *psys,
			 double *peasting,  double *pnorthing)
{
	const double k2=1.0007197049;
	const double Lambda0=68574.858;
	const double I1=0.99844601;
	const double I2=2.4323e-8;
	const double PhiN=169640.06;
	const double Phi0=0.82205008;
	const double Rho2=648000/LS_PI;
	const double Rm0=6379743.001*0.99993;
	const double I4=1.001556;
	const double I5=2.44e-8;
	const double east0=650000.0;
	const double north0=200000.0;

	
	short enr;
	double lambda, phi, phi2;
	double lambdas, phis;
	double east, north;
	double dphi, dphi2;
	ELLIPSOID *ell;
	DATUMSTRANS *datparam;
	
	datparam = ls_geo_get_datparam(psys->Datum);
	enr = datparam->RefEll;
	ell = ls_geo_get_ellparam(enr);

	/* Step1: from ellipsoid to best fitting Gauss-sphere */
	lambda = k2 * (longitude*Rho2 - Lambda0);
	phi = latitude * Rho2;
	dphi2 = phi - 169800.0;
	dphi = I1 * dphi2 + I2 * dphi2 * dphi2;
	phi2 = dphi + PhiN;
	phi = phi2 / Rho2;
	lambda /= Rho2;
	phis = asin(cos(Phi0) * sin(phi) - sin(Phi0) * cos(phi) * cos(lambda));
	lambdas = asin(cos(phi) * sin(lambda) / cos(phis));
	
	east = Rm0 * lambdas;
	north = Rm0 * log(tan(LS_PI_4 + phis * 0.5));
	
	*peasting  = east + east0;
	*pnorthing = north + north0;

} /* ***********************************Geo2EOV********************************** */


/*	*****************************************************************************
	* Konvertierung von ungarischen EOV-Koordinaten in Geo-Koordinaten          *
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
	* 			fertig		03.05.99		Peter Clevers						*
	*****************************************************************************
*/
void EOV2Geo(double *plongitude, double *platitude, const KOORDSYSTEM *psys,
			 double  easting,    double  northing)
{
	const double k2=1.0007197049;
	const double Lambda0=68574.858;
	const double I1=0.99844601;
	const double I2=2.4323e-8;
	const double PhiN=169640.06;
	const double Phi0=0.82205008;
	const double Rho2=648000/LS_PI;
	const double Rm0=6379743.001*0.99993;
	const double I4=1.001556;
	const double I5=2.44e-8;
	const double east0=650000.0;
	const double north0=200000.0;

	
	short enr;
	double lambda, phi;
	double lambdas, phis;
	double east, north;
	double dphi, dphi2;
	ELLIPSOID *ell;
	DATUMSTRANS *datparam;
	
	datparam = ls_geo_get_datparam(psys->Datum);
	enr = datparam->RefEll;
	ell = ls_geo_get_ellparam(enr);

	/* Step1: from EOV to best fitting Gauss-sphere */
	east = easting - east0;
	north = northing - north0;
	
	lambdas = east / Rm0;
	phis = (atan(exp(north / Rm0)) - LS_PI_4) * 2.0;
	
	phi = asin(cos(Phi0) * sin(phis) + sin(Phi0) * cos(phis) * cos(lambdas));
	lambda = asin(sin(lambdas) * cos(phis) / cos(phi));
	
	/* Step2: from best fitting Gauss-sphere to ellipsoid */
	phi *= Rho2;
	dphi2 = phi - PhiN;
	dphi = I4 * dphi2 - I5 * dphi2 * dphi2;
	*platitude = (dphi + 169800.0) / Rho2;
	
	lambda *= Rho2;
	*plongitude = (lambda / k2 + Lambda0) / Rho2;
	
	
} /* ***********************************EOV2Geo********************************** */



