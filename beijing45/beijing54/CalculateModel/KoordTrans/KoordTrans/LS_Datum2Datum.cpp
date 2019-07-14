
/* *****************************************************************************
 *
 *  Datei: LS_KoordTrans.c
 *         Unterprogramme zur Koordinatentransformation
 *  Datum: 23.01.1999
 *  ?by:  L&S Hochfrequenztechnik GmbH 1993, 1997
 *    
 **************************************************************************** */

#include <math.h>
#include "LS_Koordtrans.h"
/* //@TB010998 #include "LS_KoordStructs.h"*/
#include "koosysteme.h"
#include "LS_Datum2Datum.h"
/* //@PC080998 #include "KoordTransINIT.h"  */


/*	*****************************************************************************
	* Transformation von Geo-Koordinaten, die auf dem Datum1 beruhen, in Geo-	*
	* Koordinaten, die auf dem Datum2 beruhen.									*
	*																			*
	* Eingabe:																	*
	* 			KOORDSYSTEM *psysq			Systemparameter	Quellsystem			*
	* 			KOORDSYSTEM *psysq			Systemparameter	Zielsystem			*
	* 			double		*pHQ			Height Sea Level above Ellipsoid	*
	* 			double		*pHZ			Height Sea Level above Ellipsoid	*
	*																			*
	* Eingabe / Ausgabe:														*
	* 			double		*pLonongitude	Longitude des Quelldatums			*
	* 			double		*pLatitude		Latitude des Quelldatums			*
	* 			double		*phight			Height above Ellipsoid				*
	*																			*
	* Funktionswert:															*
	* 			short		0				Kein Fehler							*
	* 			short		< 0				Fehler in der Umrechnung			*
	*																			*
	* Status:																	*
	* 			In Arbeit	23.01.99		Peter Clevers						*
	*****************************************************************************
*/
short Datum2Datum (double  *pLongitude, double *pLatitude, double *phight,
				   const KOORDSYSTEM *psysq, const KOORDSYSTEM *psysz)
{
	short noerr = 0;
	ELLIPSOID *ellq, *ellz, *ellWGS84;
	DATUMSTRANS DatumTrans;
	DATUMSTRANS *DatumQ, *DatumZ, *DatumWGS84;

	DatumQ = ls_geo_get_datparam(psysq->Datum);
	DatumZ = ls_geo_get_datparam(psysz->Datum);

	if (DatumQ->Methode == DatumZ->Methode)
	{
		ellq = ls_geo_get_ellparam(DatumQ->RefEll);
		ellz = ls_geo_get_ellparam(DatumZ->RefEll);
		
		/* Berechnen der Transformationsparameter f den Datums¸bergang */
		DatumTrans.Tx = DatumQ->Tx - DatumZ->Tx;
		DatumTrans.Ty = DatumQ->Ty - DatumZ->Ty;
		DatumTrans.Tz = DatumQ->Tz - DatumZ->Tz;
		DatumTrans.Rx = DatumQ->Rx - DatumZ->Rx;
		DatumTrans.Ry = DatumQ->Ry - DatumZ->Ry;
		DatumTrans.Rz = DatumQ->Rz - DatumZ->Rz;
		DatumTrans.Sc = 1 + (DatumQ->Sc - DatumZ->Sc);
		
		switch (DatumQ->Methode)
		{
			case(BURSA_WOLF):
				noerr = Bursa_Wolf(pLongitude, pLatitude, phight, ellq, ellz, &DatumTrans,
								   &DatumQ->Hell, &DatumZ->Hell);
				break;	/* Bursa-Wolf */
			case(MOLODONSKIJ):
				noerr = MolDatumsTrans(pLongitude, pLatitude, phight, ellq, ellz, &DatumTrans,
								   	   &DatumQ->Hell, &DatumZ->Hell);
				break;	/* Molodonskij */
			case(TRANS_ROT):
				noerr = Trans_Rot(pLongitude, pLatitude, phight, ellq, ellz, &DatumTrans,
				                  &DatumQ->Hell, &DatumZ->Hell);
				break;	/* Translation&Rotation */
			case(HELMERT):
				noerr = Helmert7P(pLongitude, pLatitude, phight, ellq, ellz, &DatumTrans,
								  &DatumQ->Hell, &DatumZ->Hell);
				break;	/* HELMERT 7 Parameter */
			default:
				break;
		}	/* switch */
				
		if (noerr != 0)
			return (noerr);

	}	/* psysq->Methode == psysz->Methode */
	else
	{
		ellWGS84 = ls_geo_get_ellparam(WGS84e);
		DatumWGS84 = ls_geo_get_datparam(WGS84_BWd);
		
		/* 1 Schritt: Quelldatum -> WGS84 */
		if (psysq->Datum != WGS84_BWd)
		{
			ellq = ls_geo_get_ellparam(DatumQ->RefEll);

			DatumTrans.Tx = DatumQ->Tx;
			DatumTrans.Ty = DatumQ->Ty;
			DatumTrans.Tz = DatumQ->Tz;
			DatumTrans.Rx = DatumQ->Rx;
			DatumTrans.Ry = DatumQ->Ry;
			DatumTrans.Rz = DatumQ->Rz;
			DatumTrans.Sc = 1 + DatumQ->Sc;
			
			switch (DatumQ->Methode)
			{
				case(BURSA_WOLF):
					noerr = Bursa_Wolf(pLongitude, pLatitude, phight, ellq, ellWGS84, &DatumTrans,
									   &DatumQ->Hell, &DatumWGS84->Hell);
					break;	/* Bursa-Wolf */
				case(MOLODONSKIJ):
					noerr = MolDatumsTrans(pLongitude, pLatitude, phight, ellq, ellWGS84, &DatumTrans,
									   	  &DatumQ->Hell, &DatumWGS84->Hell);
					break;	/* Molodonskij */
				case(TRANS_ROT):
					noerr = Trans_Rot(pLongitude, pLatitude, phight, ellq, ellWGS84, &DatumTrans,
					                  &DatumQ->Hell, &DatumWGS84->Hell);
					break;	/* Translation&Rotation */
				case(HELMERT):
					noerr = Helmert7P(pLongitude, pLatitude, phight, ellq, ellWGS84, &DatumTrans,
								      &DatumQ->Hell, &DatumWGS84->Hell);
					break;	/* HELMERT 7 Parameter */
				default:
					break;
			}	/* switch */
				
		if (noerr != 0)
			return (noerr);

		} /* if (psysq->Datum != WGS84d) */

		/* 2 Schritt: WGS84 -> Zieldatum */
		if (psysz->Datum != WGS84_BWd)
		{
			ellz = ls_geo_get_ellparam(DatumZ->RefEll);
			
			/* Berechnen der Transformationsparameter f den Datumsergang */
			DatumTrans.Tx = - DatumZ->Tx;
			DatumTrans.Ty = - DatumZ->Ty;
			DatumTrans.Tz = - DatumZ->Tz;
			DatumTrans.Rx = - DatumZ->Rx;
			DatumTrans.Ry = - DatumZ->Ry;
			DatumTrans.Rz = - DatumZ->Rz;
			DatumTrans.Sc = 1 - DatumZ->Sc;

			switch (DatumZ->Methode)
			{
				case(BURSA_WOLF):
					noerr = Bursa_Wolf(pLongitude, pLatitude, phight, ellWGS84, ellz, &DatumTrans,
								       &DatumWGS84->Hell, &DatumZ->Hell);
					break;	/* Bursa-Wolf */
				case(MOLODONSKIJ):
					noerr = MolDatumsTrans(pLongitude, pLatitude, phight, ellWGS84, ellz, &DatumTrans,
									   	   &DatumWGS84->Hell, &DatumZ->Hell);
					break;	/* Molodonskij */
				case(TRANS_ROT):
					noerr = Trans_Rot(pLongitude, pLatitude, phight, ellWGS84, ellz, &DatumTrans,
					                  &DatumWGS84->Hell, &DatumZ->Hell);
					break;	/* Translation&Rotation */
				case(HELMERT):
					noerr = Helmert7P(pLongitude, pLatitude, phight, ellWGS84, ellz, &DatumTrans,
								      &DatumWGS84->Hell, &DatumZ->Hell);
					break;	/* HELMERT 7 Parameter */
				default:
					break;
			}	/* switch */
				
		if (noerr != 0)
			return (noerr);

		} /* if (psysq->Datum != WGS84d) */
	}
	return (noerr);
} /* ******************************Datum2Datum*********************************** */


/*	*****************************************************************************
	* Umrechnung von Geo-Koordinaten von Datum 1 nach Datum 2.				 	*
	*																			*
	* Transformation nach Molodensky											*
	*																			*
	* Eingabe:																	*
	* 			double		*pLongitude		Longitude							*
	* 			double		*pLatitude		Latitude							*
	* 			double		*phight			Hoehe ueber NN						*
	* 			MOLTRANSPAR *pDTrans		Benigte Parameter					*
	* 			double		*pHQ			Height Sea Level above Ellipsoid	*
	* 			double		*pHZ			Height Sea Level above Ellipsoid	*
	*																			*
	* Ausgabe:																	*
	* 			double	*pLongitude			Longitude							*
	* 			double	*pLatitude			Latitude							*
	* 			double	*ph					He er NN						*
	*																			*
	* Status:																	*
	* 			In Arbeit	23.01.99		Peter Clevers						*
	*****************************************************************************
*/
short MolDatumsTrans(double *pLongitude, double *pLatitude, double *phight,
				     ELLIPSOID *pEllQ, ELLIPSOID *pEllZ, DATUMSTRANS *pDTrans,
				     const double *pHQ, double *pHZ)
{
	double	sinPhi, cosPhi, sinPhi2;
	double	sinLambda, cosLambda;
	double	Rn, Rm;
	double	bda;
	double	deltaPhi, deltaLambda, deltaH;
	double	h1, h2, h3;
	double	da, df;
	double	fQ, fZ;
	double	hell;
	
	fQ = 1.0 / pEllQ->f;
	fZ = 1.0 / pEllZ->f;
	
	sinPhi = sin(*pLatitude);
	cosPhi = cos(*pLatitude);
	sinPhi2 = sinPhi * sinPhi;
	sinLambda = sin(*pLongitude);
	cosLambda = cos(*pLongitude);
	
	da = pEllZ->A - pEllQ->A;
	df = fZ - fQ;
	
	hell = *phight + *pHQ;
	
	h1 = 1.0 - pEllQ->E1Q * sinPhi2;
	Rn = pEllQ->A / sqrt(h1);
	Rm = pEllQ->A * (1.0 - pEllQ->E1Q) / pow(h1, 1.5);
	
	bda = 1 - fQ;	/*Polarradius geteilt durch den Aequatorialradius*/
	
	h1  = - pDTrans->Tx * sinPhi * cosLambda - pDTrans->Ty * sinPhi * sinLambda;
	h1 += pDTrans->Tz * cosPhi;
	h2  = da * (Rn * pEllQ->E1Q * sinPhi * cosPhi);
	h2 /= pEllQ->A;
	h3  = df * (Rm / bda + Rn * bda) * sinPhi * cosPhi;
	deltaPhi = (h1 + h2 + h3) / (Rm + hell);
	
	deltaLambda = -pDTrans->Tx * sinLambda + pDTrans->Ty * cosLambda;
	deltaLambda /= (Rn + hell) * cosPhi;

	deltaH  = pDTrans->Tx * cosPhi * cosLambda;
	deltaH += pDTrans->Ty * cosPhi * sinLambda;
	deltaH += pDTrans->Tz * sinPhi;
	deltaH -= da * (pEllQ->A / Rn);
	deltaH += df * bda *Rn *sinPhi2;
	
	*pLatitude += deltaPhi;
	*pLongitude += deltaLambda;
	*phight += deltaH - *pHZ;
	
	return (0);
} /* ******************************MolDatumsTrans******************************** */


/*	*****************************************************************************
	* Transformation von Geo-Koordinaten, die auf dem Datum1 beruhen, in Geo-	*
	* Koordinaten, die auf dem Datum2 beruhen.									*
	* Methode: Translation & Rotation											*
	*																			*
	* Eingabe:																	*
	* 			ELLIPSOID	*pEllQ			Quell-Ellipsoid						*
	* 			ELLIPSOID	*pEllZ			Ziel-Ellipsoid						*
	* 			DATUMSTRANS *pDTrans		Transformationsprarameter			*
	* 			double		*pHQ			Height Sea Level above Ellipsoid	*
	* 			double		*pHZ			Height Sea Level above Ellipsoid	*
	*																			*
	* Eingabe / Ausgabe:														*
	* 			double		*Lonongitude	Longitude des Quelldatums			*
	* 			double		*Latitude		Latitude des Quelldatums			*
	* 			double		*phight			Height above Ellipsoid				*
	*																			*
	* Funktionswert:															*
	* 			short		0			Kein Fehler								*
	* 			short		< 0			Fehler in der Umrechnung				*
	*																			*
	* Status:																	*
	* 			In Arbeit	23.01.99		Peter Clevers						*
	*****************************************************************************
*/
short Trans_Rot(double *pLongitude, double *pLatitude, double *phight,
				  ELLIPSOID *pEllQ, ELLIPSOID *pEllZ, DATUMSTRANS *pDTrans,
				  const double *pHq, const double *pHz)
{
	double x1, y1, z1;
	double x2, y2, z2;
	double cos_alpha, sin_alpha;
	double cos_beta, sin_beta;
	double cos_gamma, sin_gamma;
	double r11, r21, r31, r12, r22, r32, r13, r23 , r33;
	short  noerr;
	
	noerr = 0;

	/* Umrechnung der elliptischen Koordinaten in dreidimensionale karthesische
	 Koordinaten im System 1.
	*/
	LatLong_2_XYZ(pLongitude, pLatitude, phight, pEllQ, pDTrans, pHq, &x1, &y1, &z1);

	 
	
	/* Transformation der dreidimensionalen karthesischen Koordianten aus dem
	   System 1 in das System 2												
	*/
	
	/* Berechnung der Rotationsparameter */
	cos_alpha = cos(pDTrans->Rx);
	sin_alpha = sin(pDTrans->Rx);
	cos_beta = cos(pDTrans->Ry);
	sin_beta = sin(pDTrans->Ry);
	cos_gamma = cos(pDTrans->Rz);
	sin_gamma = sin(pDTrans->Rz);
	
	r11 = cos_beta * cos_gamma;
	r21 = -cos_beta * sin_gamma;
	r31 = sin_beta;
	
	r12 = cos_alpha * sin_gamma + sin_alpha * sin_beta * cos_gamma;
	r22 = cos_alpha * cos_gamma - sin_alpha * sin_beta * sin_gamma;
	r32 = -sin_alpha * cos_beta;
	
	r13 = sin_alpha * sin_gamma - cos_alpha * sin_beta * cos_gamma;
	r23 = sin_alpha * cos_gamma + cos_alpha * sin_beta * sin_gamma;
	r33 = cos_alpha * cos_beta;

	/* Berechnung der dreidimensionalen karthesischen Koordinaten im System 2 */
	x2 = pDTrans->Tx + pDTrans->Sc*( x1 * r11 + y1 * r12 + z1 * r13);
	y2 = pDTrans->Ty + pDTrans->Sc*( x1 * r21 + y1 * r22 + z1 * r23);
	z2 = pDTrans->Tz + pDTrans->Sc*( x1 * r31 + y1 * r32 + z1 * r33);
	
	
	
	/* Umrechnung der dreidimensionalen karthesischen Koordinaten in 
	   elliptischen Koordinaten im System 2.
	*/
	noerr = XYZ_2_LatLong(pLongitude, pLatitude, phight, pEllZ, pDTrans, pHz, &x2, &y2, &z2);
	
	return (noerr);
	
} /* ******************************Trans_Rot*********************************** */


/*	*****************************************************************************
	* Transformation von Geo-Koordinaten, die auf dem Datum1 beruhen, in Geo-	*
	* Koordinaten, die auf dem Datum2 beruhen.									*
	* Methode: BURSA  WOLF														*
	*																			*
	* Eingabe:																	*
	* 			ELLIPSOID	*pEllQ			Quell-Ellipsoid						*
	* 			ELLIPSOID	*pEllZ			Ziel-Ellipsoid						*
	* 			DATUMSTRANS *pDTrans		Transformationsprarameter			*
	* 			double		*pHight			Height above Sea Level				*
	* 			double		*pHQ			Height Sea Level above Ellipsoid	*
	* 			double		*pHZ			Height Sea Level above Ellipsoid	*
	*																			*
	* Eingabe / Ausgabe:														*
	* 			double		*Lonongitude	Longitude des Quelldatums			*
	* 			double		*Latitude		Latitude des Quelldatums			*
	*																			*
	* Funktionswert:															*
	* 			short		0			Kein Fehler								*
	* 			short		< 0			Fehler in der Umrechnung				*
	*																			*
	* Status:																	*
	* 			In Arbeit	23.01.99		Peter Clevers						*
	*****************************************************************************
*/
short Bursa_Wolf(double *pLongitude, double *pLatitude, double *phight,
				 ELLIPSOID *pEllQ, ELLIPSOID *pEllZ, DATUMSTRANS *pDTrans,
				 const double *pHQ, double *pHZ)
{
	double x1, y1, z1;
	double x2, y2, z2;
	short  noerr;

	/* Umrechnung der elliptischen Koordinaten in dreidimensionale karthesische
	 Koordinaten im System 1.
	*/
	LatLong_2_XYZ(pLongitude, pLatitude, phight, pEllQ, pDTrans, pHQ, &x1, &y1, &z1);
	 
	/* Transformation der dreidimensionalen karthesischen Koordianten aus dem
	   System 1 in das System 2												
	*/
	x2 = pDTrans->Tx + pDTrans->Sc*( x1             + y1*pDTrans->Rz - z1*pDTrans->Ry);
	y2 = pDTrans->Ty + pDTrans->Sc*(-x1*pDTrans->Rz + y1             + z1*pDTrans->Rx);
	z2 = pDTrans->Tz + pDTrans->Sc*( x1*pDTrans->Ry - y1*pDTrans->Rx + z1);
	
	/* Umrechnung der dreidimensionalen karthesischen Koordinaten in 
	   elliptischen Koordinaten im System 2.
	*/
	noerr = XYZ_2_LatLong(pLongitude, pLatitude, phight, pEllZ, pDTrans, pHZ, &x2, &y2, &z2);
	
	return (noerr);
	
} /* ******************************Bursa_Wolf*********************************** */


/*	*****************************************************************************
	* Transformation von Geo-Koordinaten, die auf dem Datum1 beruhen, in Geo-	*
	* Koordinaten, die auf dem Datum2 beruhen.									*
	* Methode: Helmert 7 Parameter Transformation								*
	*																			*
	* Eingabe:																	*
	* 			ELLIPSOID	*pEllQ			Quell-Ellipsoid						*
	* 			ELLIPSOID	*pEllZ			Ziel-Ellipsoid						*
	* 			DATUMSTRANS *pDTrans		Transformationsprarameter			*
	* 			double		*pHight			Height above Sea Level				*
	* 			double		*pHQ			Height Sea Level above Ellipsoid	*
	* 			double		*pHZ			Height Sea Level above Ellipsoid	*
	*																			*
	* Eingabe / Ausgabe:														*
	* 			double		*Lonongitude	Longitude des Quelldatums			*
	* 			double		*Latitude		Latitude des Quelldatums			*
	*																			*
	* Funktionswert:															*
	* 			short		0			Kein Fehler								*
	* 			short		< 0			Fehler in der Umrechnung				*
	*																			*
	* Status:																	*
	* 			In Arbeit	23.01.99		Peter Clevers						*
	*****************************************************************************
*/
short Helmert7P(double *pLongitude, double *pLatitude, double *phight,
			    ELLIPSOID *pEllQ, ELLIPSOID *pEllZ, DATUMSTRANS *pDTrans,
			    const double *pHQ, double *pHZ)
{
	double x1, y1, z1;
	double x2, y2, z2;
	short  noerr;

	/* Umrechnung der elliptischen Koordinaten in dreidimensionale karthesische
	 Koordinaten im System 1.
	*/
	LatLong_2_XYZ(pLongitude, pLatitude, phight, pEllQ, pDTrans, pHQ, &x1, &y1, &z1);
	 
	/* Transformation der dreidimensionalen karthesischen Koordianten aus dem
	   System 1 in das System 2												
	*/
	x2 = pDTrans->Tx + ( x1*pDTrans->Sc + y1*pDTrans->Rz - z1*pDTrans->Ry);
	y2 = pDTrans->Ty + (-x1*pDTrans->Rz + y1*pDTrans->Sc + z1*pDTrans->Rx);
	z2 = pDTrans->Tz + ( x1*pDTrans->Ry - y1*pDTrans->Rx + z1*pDTrans->Sc);
	
	/* Umrechnung der dreidimensionalen karthesischen Koordinaten in 
	   elliptischen Koordinaten im System 2.
	*/
	noerr = XYZ_2_LatLong(pLongitude, pLatitude, phight, pEllZ, pDTrans, pHZ, &x2, &y2, &z2);
	
	return (noerr);
	
} /* ******************************Helmert*********************************** */


/*	*****************************************************************************
	* Transformation von elliptischen Geo-Koordinaten, in geozentrische 		*
	* karthesische Koordinaten.													*
	*																			*
	* Eingabe:																	*
	* 			double		*pLongitude		Longitude des Quelldatums			*
	* 			double		*pLatitude		Latitude des Quelldatums			*
	* 			double		*pHight			Height above Sea Level				*
	* 			ELLIPSOID	*pEllQ			Quell-Ellipsoid						*
	* 			DATUMSTRANS *pDTrans		Transformationsprarameter			*
	* 			double		*pHq			Height Ellipsoid -> Sea Level		*
	*																			*
	* Eingabe / Ausgabe:														*
	* 			double		*pX				X: geozentrische karth. Koordinaten *
	* 			double		*pY				Y: geozentrische karth. Koordinaten *
	* 			double		*pZ				Z: geozentrische karth. Koordinaten *
	*																			*
	*																			*
	* Status:																	*
	* 			In Arbeit	25.07.97		Peter Clevers						*
	*****************************************************************************
*/
void LatLong_2_XYZ(const double *pLongitude, const double *pLatitude, const double *pHeight,
				   ELLIPSOID *pEllQ, DATUMSTRANS *pDTrans, const double *pHq,
				   double *pX, double *pY, double *pZ)
{
	double coslat, sinlat;
	double xn;
	double hell;

	/* Umrechnung der elliptischen Koordinaten in dreidimensionale karthesische
	 Koordinaten im System 1.
	*/
	coslat = cos(*pLatitude);	
	sinlat = sin(*pLatitude);
	hell = *pHeight + *pHq;
	xn = pEllQ->A / sqrt(1.0 - pEllQ->E1Q * sinlat * sinlat);
	
	*pX = (xn + hell) * coslat * cos(*pLongitude);
	*pY = (xn + hell) * coslat * sin(*pLongitude);
	*pZ = (xn * (1.0 - pEllQ->E1Q) + hell) * sinlat;
	 
} /* ******************************LatLong_2_XYZ*********************************** */


/*	*****************************************************************************
	* Transformation von geozentrischen karthesische Koordinaten in				*
	* elliptischen Geo-Koordinaten.												*
	*																			*
	* Eingabe:																	*
	* 			double		*pX				X: geozentrische karth. Koordinaten *
	* 			double		*pY				Y: geozentrische karth. Koordinaten *
	* 			double		*pZ				Z: geozentrische karth. Koordinaten *
	* 			ELLIPSOID	*pEllZ			Ziel-Ellipsoid						*
	* 			DATUMSTRANS *pDTrans		Transformationsprarameter			*
	* 			double		*pHz			Height Ellipsoid -> Sea Level		*
	*																			*
	* Eingabe / Ausgabe:														*
	* 			double		*pLongitude		Longitude des Zieldatums			*
	* 			double		*pLatitude		Latitude des Zieldatums				*
	* 			double		*phight			Height above Sea Level				*
	*																			*
	*																			*
	* Status:																	*
	* 			In Arbeit	25.07.97		Peter Clevers						*
	*****************************************************************************
*/
short XYZ_2_LatLong(double *pLongitude, double *pLatitude, double *phight, 
					ELLIPSOID *pEllZ, DATUMSTRANS *pDTrans, const double *pHz,
					double *pX, double *pY, double *pZ)
{
	double coslat, sinlat;
	double p, pp, q;
	double lat, H, xn;
	double hell;
	short i;

	p = *pX * *pX + *pY * *pY;
	q = p + *pZ * *pZ;
	
	/* 1. Test der Karthesischen Koordianten */
	if ((q < pEllZ->XMIN) || (q > pEllZ->XMAX))
	{
		return (-10);
	}
	
	/* 2. Ellipsoidische L”nge */
	if ((fabs(*pX) + fabs(*pY)) > 0.0)
	{
		*pLongitude = atan2(*pY,*pX);
	}
	else
	{
		*pLongitude = 0.0;
	}
	
	/* 3. Ellipsoidische Breite */
	p = sqrt(p);
	*pLatitude = atan2(*pZ,p);
	
	/* Iterative Berechnung der elliptischen Breite */
	i= 0;
	do
	{
		i++;
		lat = *pLatitude;
		coslat = cos(lat);
		xn = pEllZ->CZ / sqrt(1.0 + coslat * coslat * pEllZ->E2Q);
		
		if (p > fabs(*pZ))
		{
			H = p / coslat - xn;
		}
		else
		{
			H = *pZ / sin(*pLatitude) - xn * (1.0 - pEllZ->E1Q);
		}
			
		pp = p * (1.0 - pEllZ->E1Q * xn / (xn + H));
		*pLatitude = atan2(*pZ,pp);

	} while ((fabs(*pLatitude-lat) > 1.0e-9) && (i < 100));
	
	if (i > 99)
	{
		*pLatitude = 0.0;
		return (-11);
	}
	else
	{
		/* 4. Hight above Sea Level */
		sinlat = sin(*pLatitude);
		xn = pEllZ->A / sqrt(1.0 - pEllZ->E1Q * sinlat * sinlat);
		hell = p / cos(*pLatitude) - xn;
		
		*phight = hell - *pHz;

		return (0);
	}
	 
} /* ******************************XYZ_2_LatLong*********************************** */
