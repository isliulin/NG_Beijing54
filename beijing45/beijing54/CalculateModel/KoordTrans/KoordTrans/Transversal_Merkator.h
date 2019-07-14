/* --- Transversal_Merkator.h --- */

/* Transversal Merkator Projectionen */

typedef void (*Zone2L0_T) (short zone, double *lambda0);

struct _TransversalMerkatorSphere
	{
	Zone2L0_T Zone2L0;			/* Berechnung des Mittelmeridians aus der Zonennummer */
	double Lambda0;				/* Mittelmeridian der geographischen L”nge */
	double Phi0;				/* Nullpunktbreite */
	double M0;					/* Skalierungsfaktor k0 */
	double Off_E;				/* Offset in East-Richtung */
	double Off_N;				/* Offset in North-Richtung */
	double KZ_E;				/* Kennzahl in East-Richtung */
	double KZ_N;				/* Kennzahl in North-Richtung */
	double MIN_ZONE;			/* Kleinste Zonennummer */
	double MAX_ZONE;			/* Groesste Zonennummer */
	};
typedef struct _TransversalMerkatorSphere TRANSVERSALMERKATORSPHERE;


struct _TransversalMerkatorEllipsoid
	{
	Zone2L0_T Zone2L0;			/* Berechnung des Mittelmeridians aus der Zonennummer */
	double Lambda0;				/* Mittelmeridian der geographischen L”nge */
	double Phi0;				/* Nullpunktbreite */
	double M0_E;				/* Skalierungsfaktor in East-Richtung */
	double M0_N;				/* Skalierungsfaktor in North-Richtung */
	double Off_E;				/* Offset in East-Richtung */
	double Off_N;				/* Offset in North-Richtung */
	double KZ_E;				/* Kennzahl in East-Richtung */
	double KZ_N;				/* Kennzahl in North-Richtung */
	double PM_E;				/* Umkehrung des Vorzeichens des East-Wertes */
	double PM_N;				/* Umkehrung des Vorzeichens des East-Wertes */
	double MIN_ZONE;			/* Kleinste Zonennummer */
	double MAX_ZONE;			/* Groesste Zonennummer */
	};
typedef struct _TransversalMerkatorEllipsoid TRANSVERSALMERKATORELL;







void Geo2TransMerkSphere(double longitude, double latitude, const KOORDSYSTEM *psys,
						 double *peasting, double *pnorthing);

void TransMerkSphere2Geo(double *plongitude, double *platitude, const KOORDSYSTEM *psys,
						 double easting,     double northing);

void Geo2TransMerkEll(double longitude, double latitude, const KOORDSYSTEM *psys,
					  double *peasting, double *pnorthing);

void TransMerkEll2Geo(double *plongitude, double *platitude, const KOORDSYSTEM *psys,
					  double easting,     double northing);

void Geo2Meri (double B, double *G, double a, double n);

void Meri2Geo(double *B, double G, double a, double n);

void GetZoneRange(short proj, double *MinZone, double *MaxZone);

short GetTransMerkParam(short proj, short zone, TRANSVERSALMERKATORELL *transm);


/* 12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
