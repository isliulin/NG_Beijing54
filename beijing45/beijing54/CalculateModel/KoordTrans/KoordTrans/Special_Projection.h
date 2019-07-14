/* --- Special_Projection.h --- */


void Geo2IreGrid(double  LONG_PT, double  LAT_PT, const KOORDSYSTEM *psys,
                 double *EASTING, double *NORHING);
void IreGrid2Geo(double *LONG_PT, double *LAT_PT, const KOORDSYSTEM *psys,
                 double  EASTING, double  NORHING);

void Geo2Rdalt(double  longitude, double  latitude, const KOORDSYSTEM *psys,
			double *peasting,  double *pnorthing);
void Geo2Rd(double  longitude, double  latitude, const KOORDSYSTEM *psys,
			 double *peasting,  double *pnorthing);
void Rd2Geo(double *plongitude, double *platitude, const KOORDSYSTEM *psys,
			double  easting,    double  northing);

void Geo2Bundesmeldenetz(double  longitude, double  latitude, const KOORDSYSTEM *psys,
			             double *peasting,  double *pnorthing);
void Bundesmeldenetz2Geo(double *plongitude, double *platitude, const KOORDSYSTEM *psys,
			             double  easting,    double  northing);

void Geo2EOV(double  longitude, double  latitude, const KOORDSYSTEM *psys,
			 double *peasting,  double *pnorthing);
void EOV2Geo(double *plongitude, double *platitude, const KOORDSYSTEM *psys,
			 double  easting,    double  northing);
