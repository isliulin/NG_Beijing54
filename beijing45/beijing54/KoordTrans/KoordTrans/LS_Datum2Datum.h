/* --- LS_Datum2Datum.h --- */

short Datum2Datum (double  *pLongitude, double *pLatitude, double *phight,
				   const KOORDSYSTEM *psysq, const KOORDSYSTEM *psysz);
				   
short Bursa_Wolf(double *pLongitude, double *pLatitude, double *phight,
				 ELLIPSOID *pEllQ, ELLIPSOID *pEllZ, DATUMSTRANS *pDTrans,
				 const double *pHQ, double *pHZ);
				 
short Helmert7P(double *pLongitude, double *pLatitude, double *phight,
			    ELLIPSOID *pEllQ, ELLIPSOID *pEllZ, DATUMSTRANS *pDTrans,
			    const double *pH0, double *pHZ);
			  
short MolDatumsTrans(double *pLongitude, double *pLatitude, double *phight,
				 ELLIPSOID *pEllQ, ELLIPSOID *pEllZ, DATUMSTRANS *pDTrans,
				 const double *pH0, double *pHZ);
				 
short Trans_Rot(double *pLongitude, double *pLatitude, double *phight,
				  ELLIPSOID *pEllQ, ELLIPSOID *pEllZ, DATUMSTRANS *pDTrans,
				  const double *pHq, const double *phz);
				  
void LatLong_2_XYZ(const double *pLongitude, const double *pLatitude, const double *pHeight,
				   ELLIPSOID *pEllQ, DATUMSTRANS *pDTrans, const double *pHq,
				   double *pX, double *pY, double *pZ);
				   
short XYZ_2_LatLong(double *pLongitude, double *pLatitude, double *pHeight, 
					ELLIPSOID *pEllZ, DATUMSTRANS *pDTrans, const double *pHz,
					double *pX, double *pY, double *pZ);









/* 12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
