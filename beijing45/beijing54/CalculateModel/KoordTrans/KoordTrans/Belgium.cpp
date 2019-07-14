/******************************************************************************
 *
 *  Datei: Belgium.c
 *         Subroutines for the belgique coordinate systems:
 *							Lambert 72-50
 *							Lambert 72
 *  Datum: 14.12.98
 *  ?by:  L&S Hochfrequenztechnik GmbH 1993, 1998
 * 
 *****************************************************************************/

#include <math.h>
#include "LS_Koordtrans.h"
#include "koosysteme.h"
#include "Belgium.h"


/*	*****************************************************************************
	* Belgium Lambert 72/50 Projection - Forward Equation						*
	*																			*
	* Eingabe:																	*
	* 			double		longitude	Lgengrad								*
	* 			double		latitude	Breitengrad								*
	* 			KOORDSYSTEM	*psys		Systemparameter							*
	*																			*
	* Ausgabe:																	*
	* 			double		*x7250		Easting									*
	* 			double		*y7250		Northing								*
	*																			*
	* Status:																	*
	* 			In Arbeit	14.12.98		Peter Clevers						*
	*****************************************************************************
*/

void Geo2Belgium72_50 (double longitude, double latitude, const KOORDSYSTEM *psys,
					   double *x7250, double *y7250)
{
/****************************************************************************/
/*   TRANSFORMATION DU SYSTEME GEODESIQUE HAYFORD 24 EN                     */
/*                     SYSTEME CARTOGRAPHIQUE LAMBERT 72 & 72-50  BELGE     */
/****************************************************************************/

 double n,k,e,c,teta2,teta1,gamma,rho,x72,y72,x_72,y_72;
  n = 0.7716421928;
  k = 11565915.812935;
  e = 0.08199188998;      /*  excentricit{                     */
  c = 0.0760429434637049260;  /* longitude de l_origine :4.2124983 en rad  */
  teta2 = 0.0001420426515461963; /* diff. orient. 50-72 :0.00292984 en rad */

  teta1 = n*(longitude-c);
  gamma = LS_PI/2-latitude;
  rho = k*pow(tan(gamma/2.),n)*pow((1.+e*cos(gamma))/(1.-e*cos(gamma)),e*n/2.);
  x72 = 150000.0 + rho*sin(teta1);
  x_72 = x72 - 150000.0;
  y72 = 5400000.0 - rho*cos(teta1);
  y_72 = y72 - 165284.52;

  *x7250 = 149256.456 + x_72*cos(teta2)+y_72*sin(teta2);
  *y7250 = 165373.012 + y_72*cos(teta2)-x_72*sin(teta2);
} /* ***************************Geo_Belgium72_50********************************* */


/*	*****************************************************************************
	* Belgium Lambert 72/50 Projection - Inverse Equation						*
	*																			*
	* Eingabe:																	*
	* 			double		x7250		Easting									*
	* 			double		x7250		Northing								*
	* 			KOORDSYSTEM	*psys		Systemparameter							*
	*																			*
	* Ausgabe:																	*
	* 			double		*plongitude	Longitude								*
	* 			double		*platitude	Latitide								*
	*																			*
	* Status:																	*
	* 			In Arbeit	14.12.1998		Peter Clevers						*
	*****************************************************************************
*/
void Belgium72_50_2GEO (double *plongitude, double *platitude, const KOORDSYSTEM *psys,
						double x7250,     double y7250)
{

/****************************************************************************/
/*   TRANSFORMATION DU SYSTEME CARTOGRAPHIQUE LAMBERT 72 & 72-50  BELGE EN  */
/*                             GEODESIQUE HAYFORD 24                        */
/****************************************************************************/


 double n,k,e,c,g,teta2,teta1,gamma,rho,x72,y72,x_72,y_72;
  n = 0.7716421928;
  k = 11565915.812935;
  e = 0.08199188998;      /*  excentricit{                     */
  c = 0.0760429434637049260;  /* longitude de l_origine :4.2124983 en rad  */
  teta2 = 0.0001420426515461963; /* diff. orient. 50-72 :0.00292984 en rad */

 x_72 = x7250 - 149256.456;
 y_72 = y7250 - 165373.012;
 x72 = 150000 + x_72*cos(teta2) - y_72*sin(teta2);
 y72 = 165284.52 + y_72*cos(teta2) + x_72*sin(teta2);
 *plongitude = c + 1./n*atan((x72-150000.)/(5400000.-y72));
 rho = sqrt((x72-150000.)*(x72-150000.)+(5400000.-y72)*(5400000.-y72));
 teta1 = pow(rho/k,1./n);
 gamma = 2*atan(teta1);
 g = 0;
 while ( fabs(g - gamma) >= 0.0000000000001)
	{
	g=gamma;
	gamma = 2.*atan(teta1*pow((1.-e*cos(g))/(1.+e*cos(g)),e/2.));
	}
*platitude = LS_PI/2. - gamma;
} /* ***************************Belgium72_50_2GEO******************************** */


/*	*****************************************************************************
	* Belgium Lambert 72 Projection - Forward Equation							*
	*																			*
	* Eingabe:																	*
	* 			double		longitude	Lgengrad								*
	* 			double		latitude	Breitengrad								*
	* 			KOORDSYSTEM	*psys		Systemparameter							*
	*																			*
	* Ausgabe:																	*
	* 			double		*x7250		Easting									*
	* 			double		*y7250		Northing								*
	*																			*
	* Status:																	*
	* 			In Arbeit	14.12.98		Peter Clevers						*
	*****************************************************************************
*/
void Geo2Belgium72 (double longitude, double latitude, const KOORDSYSTEM *psys,
					double *px72,     double *py72)
{
	double x7250, y7250;
	double x_72, y_72;
	double theta2 = 0.00014204265154619634; /* versch.Orient. 50-72: 0.00292984 rad */
	
	Geo2Belgium72_50 (longitude, latitude, psys, &x7250, &y7250);
	
	x_72 = x7250 - 149256.456;
	y_72 = y7250 - 165373.012;
	
	*px72 = 150000 + x_72 * cos(theta2) - y_72 * sin(theta2);
	*py72 = 165284.52 + y_72 * cos(theta2) + x_72 * sin(theta2);

} /* ***************************Geo2Belgium72************************************ */


/*	*****************************************************************************
	* Belgium Lambert 72 Projection - Inverse Equation							*
	*																			*
	* Eingabe:																	*
	* 			double		x7250		Easting									*
	* 			double		x7250		Northing								*
	* 			KOORDSYSTEM	*psys		Systemparameter							*
	*																			*
	* Ausgabe:																	*
	* 			double		*plongitude	Longitude								*
	* 			double		*platitude	Latitide								*
	*																			*
	* Status:																	*
	* 			In Arbeit	14.12.1998		Peter Clevers						*
	*****************************************************************************
*/
void Belgium72_2GEO (double *plongitude, double *platitude, const KOORDSYSTEM *psys,
					 double x72,         double y72)
{
	double x7250, y7250;
	double x_72, y_72;
	double theta2 = 0.00014204265154619634; /* versch.Orient. 50-72: 0.00292984 rad */
	double tantheta2, sintheta2, costheta2;
	double h1;
	
	sintheta2 = sin(theta2);
	costheta2 = cos(theta2);
	tantheta2 = tan(theta2);
	
	h1 = costheta2 + tantheta2 * sintheta2;
	x_72 = x72 - 150000.0 + (y72 - 165284.52) * tantheta2;
	x_72 /= h1;
	y_72 = (y72 - 165284.52 + (150000.0 - x72) * tantheta2) / h1;
	
	x7250 = x_72 + 149256.456;
	y7250 = y_72 + 165373.012;
	
	Belgium72_50_2GEO (plongitude, platitude, psys, x7250, y7250);
	
} /* ***************************Belgium72_2GEO*********************************** */




