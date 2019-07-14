/* --- LS_ObliqueMerkator.h --- */

struct _Oblique_Merkator
	{
	short  Datum;				/* Mit Projection verbundes Datum */
	double Phi_0;				/* Breitengrad des Nullpunktes bez. auf den Ellipsoiden */
	double Lambda_0;			/* L”ngengrad des Nullpunktes bez. auf den Ellipsoiden */
	double Off_E;				/* Offset in East-Richtung */
	double Off_N;				/* Offset in North-Richtung */
	double e;					/* Elliptizitaet */
	double eq;					/* Quadrat der Elliptizitaet */
	double alpha;				/* Maþstabsfaktor zischen Kugel und Ellipsoid */
	double phi0;				/* Breitengrad des Nullpunktes bez. auf die Kugel */
	double R;					/* Erdradius der Kugel */
	double K;					/* Konstante */
	double cosphi0;				/* cos(phi0) */
	double sinphi0;				/* sin(phi0) */
	double one_eq;				/* 1 - eq */
	};
typedef struct _Oblique_Merkator OBMERK_T;


void Init_ObMerk_Param();
void Geo2ObMerk(double plongitude, double platitude, const KOORDSYSTEM *psys,
			    double *easting,   double *northing);
void ObMerk2Geo(double *plongitude, double *platitude, const KOORDSYSTEM *psys,
			    double easting,     double northing);
