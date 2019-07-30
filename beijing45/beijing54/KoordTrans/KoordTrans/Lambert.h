/* --- Strukturen f¸r Projectionssystem: Lambert --- */
struct _ConformLambert_2P
	{
	double  Phi_1;				/* Latitude des 1. Parallelkreises */
	double  Phi_2;				/* Latitude des 2. Parallelkreises */
	double  Phi_0;				/* Latitude des Nullpunktes */
	double  Lambda_0;			/* Longitude des Nullpunktes */
	double  Off_E;				/* Offset in Nordrichtung */
	double  Off_N;				/* Offset in Ostrichtung */
	short	Datum;				/* Mit Projection verbundes Datum */
				/* abgeleitete Gr–þen */
	double 	n;					/* Kegelkonstante */
	double 	F;					/*  */
	double 	Rho_0;				/* Radius des Breitengrades */
	};
typedef struct _ConformLambert_2P CONFORMLAMBERT_2P;



void Geo2Lambert2SP (double longitude, double latitude, const KOORDSYSTEM *psys,
				 	 double *peasting, double *pnorthing);
void Lambert2SP2Geo (double *plongitude, double *platitude, const KOORDSYSTEM *psys,
				 	 double easting,     double northing);
void Init_Lambert2SP_Param();
void m_und_t(double phi, double E1, double E1Q, double *m, double*t);
short GetConLam2SPParam(long proj, CONFORMLAMBERT_2P *conlam2sp);


/* 12345678901234567890123456789012345678901234567890123456789012345678901234567890
*/
