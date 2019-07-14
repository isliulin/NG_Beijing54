/* --- ALbers.h --- */

struct _Albers
	{
	double Phi_1;				/* 1. Standartparallel */
	double Phi_2;				/* 2. Standartparallel */
	double Phi_0;				/* Breitengrad des Nullpunktes */
	double Lambda_0;			/* L”ngengrad des Nullpunktes */
	double Off_E;				/* Offset in East-Richtung */
	double Off_N;				/* Offset in North-Richtung */
	short  Datum;				/* Mit Projection verbundes Datum */
	double n;					/* Kegelkonstante */
	double C;					/*  */
	double Rho_0;				/* Erdradius am Nullpunkt */
	};
typedef struct _Albers ALBERS_T;


void Geo2AziAlbersSphere (double longitude, double latitude, const KOORDSYSTEM *psys,
					   double *peasting, double *pnorthing);

void AziAlbersSphere2Geo (double *plongitude, double *platitude, const KOORDSYSTEM *psys,
					   double easting,     double northing);

void Geo2AlbersSphere (double longitude, double latitude, const KOORDSYSTEM *psys,
					   double *peasting, double *pnorthing);

void AlbersSphere2Geo (double *plongitude, double *platitude, const KOORDSYSTEM *psys,
					   double easting,     double northing);

void Geo2AlbersEllipsoid (double longitude, double latitude, const KOORDSYSTEM *psys,
				 		  double *peasting, double *pnorthing);

void AlbersEllipsoid2Geo (double *plongitude, double *platitude, const KOORDSYSTEM *psys,
						  double easting,     double northing);

void Init_AlbersParam();

void M_und_Q(double phi, double E1, double E1Q, double *m, double*q);

short GetAlbersParam(long proj, ALBERS_T *albers);


/* 12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
