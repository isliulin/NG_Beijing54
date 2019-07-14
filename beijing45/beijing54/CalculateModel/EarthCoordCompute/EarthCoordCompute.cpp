#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "EarthCoordCompute.h"

#pragma warning(disable:4996)

// 圆周率
#ifndef PI
#define PI 3.141592653589793
#endif

//一弧度对应的度数 = 180.0/PI
#define RAD 57.295779513082325

//EllipSoid信息
typedef struct _EllipStruct
{
	char EllipName[64];	//Ellip 名称
	double A;			//地球长半轴
	double F;			//地球扁平率
}ELLIPSTRUCT;

static ELLIPSTRUCT  EllipSolid_List[] =
{
	{"GRS80 / WGS84  (NAD83)",	6378137.000,3.352810681183668E-3},
	{"Clarke 1866    (NAD27)",	6378206.400,3.390075303929919E-3},
	{"Airy 1858",				6377563.396,3.340850641497077E-3},
	{"Airy Modified",			6377340.189,3.340850641497077E-3},
	{"Australian National",		6378160.000,3.352891869237217E-3},
	{"Bessel 1841",				6377397.155,3.342773182174806E-3},
	{"Clarke 1880",				6378249.145,3.407561378699334E-3},
	{"Everest 1830",			6377276.345,3.324449296662885E-3},
	{"Everest Modified",		6377304.063,3.324449296662885E-3},
	{"Fisher 1960",				6378166.000,3.352329869259135E-3},
	{"Fisher 1968",				6378150.000,3.352329869259135E-3},
	{"Hough 1956",				6378270.000,3.367003367003367E-3},
	{"International (Hayford)",	6378388.000,3.367003367003367E-3},
	{"Krassovsky 1938",			6378245.000,3.352329869259135E-3},
	{"NWL-9D (WGS 66)",			6378145.000,3.352891869237217E-3},
	{"South American 1969",		6378160.000,3.352891869237217E-3},
	{"Soviet Geod. System 1985",6378136.000,3.352813177896914E-3},
	{"WGS 72",					6378135.000,3.352779454167505E-3}
};
#define MAX_ELLIPLIST (sizeof(EllipSolid_List) / sizeof(ELLIPSTRUCT))

 void GpnArc(double P1,double P2,double &ARC,double A,double ESQ);
 void GpnLoa(double DL,double &AZ1,double &AZ2,double &AO,double &BO,double &SMS,double A,double F,double ESQ);
 void Gpn2Xyz (int N,double X,double Y,double Z,double &T1,double &T2,double &T3,double A,double F,double ESQ);


//点坐标计算
void Direct2D(double Lat1,double Lon1,
			  double &Lat2,double &Lon2,
			  double Az1,double &Az2,
			  double DistEllip,
			  double A,double F)
{
	double EPS= 5E-13;

	double R=1.0-F;
	double TU=R*sin(Lat1)/cos(Lat1);
	double SF=sin(Az1);
	double CF=cos(Az1);
	Az2=0.0;
	if (CF != 0.0)		//不等于0 ??
		Az2=atan2(TU,CF)*2.0;
	double CU=1.0/sqrt(TU*TU+1.0);
	double SU=TU*CU;
	double SA=CU*SF;
	double C2A=-SA*SA+1.0;
	double X=sqrt((1.0/R/R-1.0)*C2A+1.0)+1.0;
	X=(X-2.0)/X;
	double C=1.0-X;
	C=(X*X/4.+1.0)/C;
	double D=(0.375*X*X-1.0)*X;
	TU=DistEllip/R/A/C;
	double Y=TU;

	double SY=0;
	double CY=0;
	double CZ=0;
	double E=0;

_Loop1:
	SY=sin(Y);
	CY=cos(Y);
	CZ=cos(Az2+Y);
	E=CZ*CZ*2.0-1.0;
	C=Y;
	X=E*CY;
	Y=E+E-1.0;
	Y=(((SY*SY*4.0-3.0)*Y*CZ*D/6.0+X)*D/4.0-CZ)*SY*D+TU;

	if((fabs(Y-C) > EPS))	//高精度判断,差值的绝对值小于 5E-14
		goto _Loop1;

	Az2=CU*CY*CF-SU*SY;
	C=R*sqrt(SA*SA+Az2*Az2);
	D=SU*CY+CU*SY*CF;
	Lat2=atan2(D,C);
	C=CU*CY-SU*SY*CF;
	X=atan2(SY*SF,C);
	C=((-3.*C2A+4.)*F+4.)*C2A*F/16.0;
	D=((E*CY*C+CZ)*SY*C+Y)*SA;
	Lon2=Lon1+X-(1.-C)*D*F;
	Az2=atan2(SA,Az2)+PI;
}


void Distance2D(double Lat1,double Lon1,
				double Lat2,double Lon2,
				double &Az1,double &Az2,
				double &DistEllip,
				double A,double F)
{
	double tol0 =5.0E-15;
	double tol1 =5.0E-14;
	double tol2 =7.0E-03;
	double r2,r1;
	double arc;
	double esq = F*(2.0-F);

	double twopi = 2.0*PI;
	double 	ss = Lon2-Lon1;
	if( fabs(ss) < tol1 )
	{
		Lon2 = Lon2+tol1;
		r2 = Lat2;
		r1 = Lat1;
		GpnArc (r1, r2, arc,A,esq);
		DistEllip  = fabs( arc );
		if( Lat2 > Lat1 )
		{
			Az1 = 0.0;
			Az2 = PI;
		}
		else
		{
			Az1 = PI;
			Az2 = 0.0;
		}

		return;
	}

	double dlon = Lon2-Lon1;
	if( dlon >= 0.0)
	{
		if(PI<= dlon && dlon < twopi)
			dlon = dlon-twopi;
	}
	else
	{
		ss = fabs(dlon);
		if(PI<= ss &&  ss < twopi )
			dlon = dlon+twopi;
	}
	ss = fabs(dlon);
	if(ss> PI)
		ss = twopi-ss;

	double alimit = PI*(1.0-F);
	if(ss >= alimit )
	{
		r1 = fabs(Lat1);
		r2 = fabs(Lat2);

		if(r1>tol2 && r2>tol2 )
			goto _60;
		if( r1< tol1 && r2>tol2 )
			goto _60;
		if( r2<tol1 && r1>tol2 )
			goto _60;
		if( r1>tol1 || r2>tol1 )
		{
			Az1 = 0.0;
			Az2 = 0.0;
			DistEllip   = 0.0;
			return ;
		};

		double aa = 0;
		double bb = 0;
		double sms = 0;
		GpnLoa (dlon,Az1,Az2,aa,bb,sms,A,F,esq);
		double equ = A*fabs(dlon);
		DistEllip = equ-sms;

		return ;
	}

_60:
	double f0   = (1.0-F);
	double b    = A*f0;
	double epsq = esq/(1.0-esq);
	double f2   = F*F;
	double f3   = F*f2;
	double f4   = F*f3;
	dlon  =		Lon2-Lon1;
	double ab   = dlon ;
	double kount = 0 ;
	double u1    = f0*sin(Lat1)/cos(Lat1);
	double u2    = f0*sin(Lat2)/cos(Lat2);
	u1    = atan(u1);
	u2    = atan(u2);
	double su1   = sin(u1) ;
	double cu1   = cos(u1);
	double su2   = sin(u2);
	double cu2   = cos(u2);

	double clon = 0;
	double slon = 0;
	double csig = 0;
	double ssig = 0;
	double sinalf = 0;
	double sig = 0;
	double w = 0;
	double t4 = 0;
	double t6 = 0;
	double ao = 0;
	double a2 = 0;
	double a4 = 0;
	double a6 = 0;
	double qo = 0;
	double q2 = 0;
	double q4 = 0;
	double q6 = 0;
	double r3 = 0;
	double xy = 0;
	double xz = 0;
	double z  = 0;
	double bo = 0;
	double b2 = 0;
	double b4 = 0;
	double b6 = 0;

_1:
	kount = kount+1 ;
	clon  = cos(ab);
	slon  = sin(ab);
	csig  = su1*su2+cu1*cu2*clon;
	ssig  = sqrt((slon*cu2)*(slon*cu2)+(su2*cu1-su1*cu2*clon)*(su2*cu1-su1*cu2*clon));
	sig   = atan2(ssig,csig);
	sinalf=cu1*cu2*slon/ssig;
	w   = (1.0-sinalf*sinalf);
	t4  = w*w  ;
	t6  = w*t4 ;
	ao  = F-f2*(1.0+F+f2)*w/4.0+3.0*f3*(1.0+9.0*F/4.0)*t4/16.0-25.0*f4*t6/128.0;
	a2  = f2*(1.0+F+f2)*w/4.0-f3*(1.0+9.0*F/4.0)*t4/4.0+75.0*f4*t6/256.0;
	a4  = f3*(1.0+9.0*F/4.0)*t4/32.0-15.0*f4*t6/256.0;
	a6  = 5.0*f4*t6/768.0;
	qo  = 0.0;
	if( w>tol0 )
		qo = -2.0*su1*su2/w;
	q2  = csig+qo;
	q4  = 2.0*q2*q2-1.0;
	q6  = q2*(4.0*q2*q2-3.0) ;
	r2  = 2.0*ssig*csig;
	r3  = ssig*(3.0-4.0*ssig*ssig);
	DistEllip   = sinalf*(ao*sig+a2*ssig*q2+a4*r2*q4+a6*r3*q6);
	xz  = dlon+DistEllip;
	xy  = fabs(xz-ab);
	ab  = dlon+DistEllip;

	if( xy< 0.5E-13 )
		goto _4;

	if( kount <=7 )
		goto _1;

_4:
	z   = epsq*w;
	bo  = 1.0+z*(1.0/4.0+z*(-3.0/64.0+z*(5.0/256.0-z*175.0/16384.0)));
	b2  = z*(-1.0/4.0+z*(1.0/16.0+z*(-15.0/512.0+z*35.0/2048.0)));
	b4  = z*z*(-1.0/128.0+z*(3.0/512.0-z*35.0/8192.0));
	b6  = z*z*z*(-1.0/1536.0+z*5.0/6144.0);
	DistEllip   = b*(bo*sig+b2*ssig*q2+b4*r2*q4+b6*r3*q6);

	if( dlon>PI)
		dlon = (dlon-2.0*PI);
	if( fabs(dlon)>PI)
		dlon = (dlon+2.0*PI);
	Az1 = PI/2.0;
	if( dlon <0 )
		Az1 = 3.0*Az1;
	Az2 = Az1+PI;
	if( Az2 >2.0*PI)
		Az2 = Az2-2.0*PI;

	if(!(fabs(su1)<tol0 && fabs(su2)<tol0))
	{
		double tana1 =  slon*cu2/(su2*cu1-clon*su1*cu2) ;
		double tana2 =  slon*cu1/(su1*cu2-clon*su2*cu1);
		double sina1 =  sinalf/cu1;
		double sina2 = -sinalf/cu2;
		Az1   = atan2(sina1,sina1/tana1);
		Az2   = PI-atan2(sina2,sina2/tana2);
	}
	if( Az1< 0.0)
		Az1 = Az1+2.0*PI;
	if( Az2<0.0 )
		Az2 = Az2+2.0*PI;
}


void Distance3D(double Lat1,double Lon1,double h1,
				double Lat2,double Lon2,double h2,
				double &Az1,double &Az2,
				double &DistEllip,double &Distmm,
				double A,double F)
{
	Distance2D(Lat1,Lon1,Lat2,Lon2,Az1,Az2,DistEllip,A,F);
	if(DistEllip<0.00005 )
	{
		Az1 = 0.0;
		Az2 = 0.0;
	}

	double x1,y1,z1;
	double x2,y2,z2;
	double dx,dy,dz;

	GeodeticToxyz(Lat1,Lon1,h1,x1,y1,z1,A,F);		//X,Y,Z坐标
	GeodeticToxyz(Lat2,Lon2,h2,x2,y2,z2,A,F);

	dx = x2-x1;
	dy = y2-y1;
	dz = z2-z1;
	Distmm = sqrt(dx*dx +dy*dy +dz*dz);		//Mark-to-Mark distance
}


void Distance3DExt(double Lat1,double Lon1,double h1,
				   double Lat2,double Lon2,double h2,
				   double &Az1,double &Az2,
				   double &DistEllip,double &Distmm,
				   double &dx,double &dy,double &dz,
				   double &dn,double &de,double &du,
				   bool &bZen,double &Zd,double &Zn,
				   double A,double F)
{
	Distance2D(Lat1,Lon1,Lat2,Lon2,Az1,Az2,DistEllip,A,F);
	if(DistEllip<0.00005 )
	{
		Az1 = 0.0;
		Az2 = 0.0;
	}

	double x1,y1,z1;
	double x2,y2,z2;
	double ss;
	int nq;
	double refr;
	double raz;
	double r1,r2;

	GeodeticToxyz(Lat1,Lon1,h1,x1,y1,z1,A,F);		//X,Y,Z坐标
	GeodeticToxyz(Lat2,Lon2,h2,x2,y2,z2,A,F);

	dx = x2-x1;
	dy = y2-y1;
	dz = z2-z1;
	Distmm = sqrt(dx*dx +dy*dy +dz*dz);				//Mark-to-Mark distance

	DeletaXyzToNeu(dx,dy,dz,Lat1,Lon1,dn,de,du);	//XYZ差值转 neu坐标

	bZen = false;
	if( Distmm < 289682.5 )
	{
		ss = fabs(du/Distmm);
		if(ss>0.99985)
			bZen = false;
		else
			bZen = true;
		Zd = asin(du/Distmm);
		Zd = PI/2.0 - Zd;					//Zenith <mk-to-mk> ZD
		nq = 0;
		ss = 0.0;
		double ESQ = F*(2-F);
		Gpn2Xyz(nq,Lat1,Az1,ss,r1,r2,raz,A,F,ESQ);
		refr = (( DistEllip/raz )/2.0)/7.0;
		Zn  = Zd-refr;						//Apparent Zenith Distance
	}
}

void Direct3D(double Lat1,double Lon1,double h1,
			  double &Lat2,double &Lon2,double h2,
			  double Az1,double &Az2,
			  double DistEllip,double &Distmm,
			  double A,double F)
{
	double x1,y1,z1;
	double x2,y2,z2;
	double dx,dy,dz;

	Direct2D(Lat1,Lon1,Lat2,Lon2,Az1,Az2,DistEllip,A,F);

	GeodeticToxyz(Lat1,Lon1,h1,x1,y1,z1,A,F);
	GeodeticToxyz(Lat2,Lon2,h2,x2,y2,z2,A,F);

	dx = x2-x1;
	dy = y2-y1;
	dz = z2-z1;
	Distmm=sqrt(dx*dx+dy*dy+dz*dz);
}

void Direct3DExt(double Lat1,double Lon1,double h1,
				 double &Lat2,double &Lon2,double h2,
				 double Az1,double &Az2,
				 double DistEllip,double &Distmm,
				 double &dx,double &dy,double &dz,
				 double &dn,double &de,double &du,
				 bool &bZen,double &Zd,double &Zn,
				 double A,double F)
{
	double x1,y1,z1;
	double x2,y2,z2;

	Direct2D(Lat1,Lon1,Lat2,Lon2,Az1,Az2,DistEllip,A,F);

	GeodeticToxyz(Lat1,Lon1,h1,x1,y1,z1,A,F);
	GeodeticToxyz(Lat2,Lon2,h2,x2,y2,z2,A,F);

	dx = x2-x1;
	dy = y2-y1;
	dz = z2-z1;
	Distmm=sqrt(dx*dx+dy*dy+dz*dz);
	DeletaXyzToNeu(dx,dy,dz,Lat1,Lon1,dn,de,du);	//XYZ差值转 neu坐标

	double ss;
	int nq;
	double refr;
	double raz;
	double r1,r2;
	bZen = false;
	if( Distmm < 289682.5 )
	{
		ss = fabs(du/Distmm);
		if(ss>0.99985)
			bZen = false;
		else
			bZen = true;
		Zd = asin(du/Distmm);
		Zd = PI/2.0 - Zd;					//Zenith <mk-to-mk> ZD
		nq = 0;
		ss = 0.0;
		double ESQ = F*(2-F);
		Gpn2Xyz(nq,Lat1,Az1,ss,r1,r2,raz,A,F,ESQ);
		refr = (( DistEllip/raz )/2.0)/7.0;
		Zn  = Zd-refr;						//Apparent Zenith Distance
	}
}
//////////////////////////////////////////////////////////////////////////
void GeodeticToxyz(double Lat1,double Lon1,double h1,
				   double &x1,double &y1,double &z1,
				   double A,double F)
{
	double slat=sin(Lat1);
	double clat=cos(Lat1);
	double e2 = F*(2.0-F);
	double w=sqrt(1.0-e2*slat*slat);
	double en=A/w;

	x1=(en+h1)*clat*cos(Lon1);
	y1=(en+h1)*clat*sin(Lon1);
	z1=(en*(1.0-e2)+h1)*slat;
}

bool XyzToGeodetic(double x1,double y1,double z1,
				   double &Lat1,double &Lon1,double &h1,
				   double A,double F)
{
	double tol=1E-13;
	double p=sqrt(x1*x1+y1*y1);
	if (p<tol)				//x,y,z均为0
	{
		Lat1=0.0;
		Lon1=0.0;
		h1=0.0;

		return false;
	}

	bool bRet = false;
	double e2 = F*(2.0-F);
	double ae2=A*e2;
	double tgla=z1/p/(1.0-e2);
	double tglax=0;
	double slat=0;
	double clat=0;
	double w=0;
	double en=0;

	int maxint=10;
	int icount=0;

_1:
	if(icount<= maxint)
	{
		tglax=tgla;
		tgla=z1/(p-(ae2/sqrt(1.0+(1.0-e2)*tgla*tgla)));
		icount=icount+1;
		if(fabs(tgla-tglax) >tol)
			goto _1;

		bRet=true;
		Lat1=atan(tgla);
		slat=sin(Lat1);
		clat=cos(Lat1);
		Lon1=atan2(y1,x1);
		w=sqrt(1.0-e2*slat*slat);
		en=A/w;
		if(fabs(Lat1)<=0.7854)
			h1=p/clat-en;
		else
			h1=z1/slat-en+e2*en;

		Lon1=atan2(y1,x1);
	}
	else
	{
		bRet=false;
		Lat1=0.0;
		Lon1=0.0;
		h1=0.0;
	}

	return bRet;
}

void DeletaXyzToNeu(double dx, double dy, double dz,
					double Lat1, double Lon1,
					double &dn, double &de, double &du )
{
	double x=dx*cos(Lon1)+dy*sin(Lon1);
	double y=dy*cos(Lon1)-dx*sin(Lon1);
	double z=dz;

	double ds=x*cos(PI/2.0-Lat1)-z*sin(PI/2.0-Lat1);
	de=y;
	du=z*cos(PI/2.0-Lat1)+x*sin(PI/2.0-Lat1);

	dn=-ds;
}

void NeuToDeletaXyz(double dn,double de,double du,
					double Lat1,double Lon1,
					double &dx,double &dy,double &dz)
{
	double ds = -dn;
	double s  = Lat1-PI/2.0;
	double x  = ds*cos(s)-du*sin(s);
	double y  = de;
	double z  = du*cos(s)+ds*sin(s);
	s  = -Lon1;
	dx = x*cos(s)+y*sin(s);
	dy = y*cos(s)-x*sin(s);
	dz = z;
}

void MarkDistToEllipDist(double glat,double az,double ht1,double ht2,
						 double Distmm,double &DistEllip,
						 double A,double F)
{
	double cl2=cos(glat)*cos(glat);
	double ca2=cos(az)*cos(az);
	double b=A*(1.0-F);
	double c=A*A/b;
	double ep2 = F*(2.0-F);
	double n=c/sqrt(1.0+ep2*cl2);
	double r=n/(1.0+ep2*cl2*ca2);
	double dh=ht2-ht1;
	double d7=sqrt((Distmm*Distmm-dh*dh)/((1.0+ht1/r)*(1.0+ht2/r)));
	DistEllip=2.0*r*(asin(d7/(2.0*r)));
}

//////////////////////////////////////////////////////////////////////////
//度分秒转换成弧度
void DmsToRad(int d,int m,double sec, bool isign,double &Radval)
{
	if(d < 0)
		d = -d;	//确保度分秒为正值
	if (m <  0)
		m = -m;
	if (sec < 0)
		sec = -sec;

	Radval=(d+m/60.0+sec/3600.0)/RAD;
	if (!isign)
		Radval=-Radval;
}

//弧度转换成度分秒
void RadTodms(double Radval,int &d,int &m,double &sec,bool &isign)
{
_Loop1:
	if(Radval > PI)
	{
		Radval=Radval-PI-PI;
		goto _Loop1;
	}

_Loop2:
	if(Radval< (-PI))
	{
		Radval=Radval+PI+PI;
		goto _Loop2;
	}

	if(Radval < 0.0)
		isign=false;
	else
		isign=true;

	sec=fabs(Radval*RAD);
	d=int(sec);
	sec=(sec-d)*60.0;
	m=int(sec);
	sec=(sec-m)*60.0;

	int is=int(sec*1E5);	//*10的5次方比较大小
	if(is >= 6000000)
	{
		sec=0.0;
		m=m+1;
	}

	if (m >= 60)
	{
		m=0;
		d=d+1;
	}
}

void DecimalToRad(double DecimalVal,double &Radval)
{
	Radval=DecimalVal/RAD;
}

void RadToDecimal(double Radval,double &DecimalVal)
{
	DecimalVal = Radval*RAD;
}

void DmsToDecimal(int d,int m,double sec, bool isign,double &DecimalVal)
{
	double RadValue = 0;
	DmsToRad(d,m,sec,isign,RadValue);
	RadToDecimal(RadValue,DecimalVal);
}

void DecimalTodms(double DecimalVal,int &d,int &m,double &sec,bool &isign)
{
	double RadValue = 0;
	DecimalToRad(DecimalVal,RadValue);
	RadTodms(RadValue,d,m,sec,isign);
}

//确保度分秒在合理的区间内
void Fixdms(int &ideg, int &min, double &sec, double tol)
{
	if(sec >= (60.0-tol))
	{
		sec  = 0.0;
		min  = min+1;
	}

	if(min >= 60 )
	{
		min  = 0;
		ideg = ideg+1;
	}

	if(ideg >= 360)
		ideg = 0;
}

//////////////////////////////////////////////////////////////////////////
long GetMaxEllipSolid()
{
	return (MAX_ELLIPLIST);
}
bool Get_EllipSoid(long EllipIndex, char *pName,double&dA,double &dF)
{
	if ((EllipIndex >= 0) && (EllipIndex < MAX_ELLIPLIST))
	{
		strcpy(pName,EllipSolid_List[EllipIndex].EllipName);
		dA = EllipSolid_List[EllipIndex].A;
		dF = EllipSolid_List[EllipIndex].F;

		return true;
	}
	else
		return false;
}
bool Get_EllipSoid_Name(long EllipIndex, char *pName)
{
	if ((EllipIndex >= 0) && (EllipIndex < MAX_ELLIPLIST))
	{
		strcpy(pName,EllipSolid_List[EllipIndex].EllipName);
		return true;
	}
	else
		return false;
}

bool Get_EllipSoid_AF(long EllipIndex, double&dA,double &dF)
{
	if ((EllipIndex >= 0) && (EllipIndex < MAX_ELLIPLIST))
	{
		dA = EllipSolid_List[EllipIndex].A;
		dF = EllipSolid_List[EllipIndex].F;

		return true;
	}
	else
		return false;
}

/*long Get_CurrentEllipSoid_Index()
{
	return global_EllipIndex;
}

bool Set_CurrentEllipSoid_Index(long EllipIndex)
{
	if ((EllipIndex >= 0) && (EllipIndex < MAX_ELLIPLIST))
	{
		A = EllipSolid_List[EllipIndex].A;
		F = EllipSolid_List[EllipIndex].F;
		global_ESQ = F*(2-F);

		return true;
	}
	else
		return false;
}

void Get_CurrentEllipSoid_AF(double &dA,double &dF)
{
	dA = A;
	dF = F;
}
bool Set_CurrentEllipSoid_AF(double dA,double dF)
{
	double ss = 1.0/dF;
	if(200.0 <= ss && ss <= 310.0)
	{
		A = dA;
		F = dF;
		global_EllipIndex = -1;

		return true;
	}
	else
		return false;
}
*/
//////////////////////////////////////////////////////////////////////////
void GpnArc(double P1,double P2,double &ARC,double A,double ESQ)
{
	double TT=5E-15;
	bool   FLAG = false;
	double S1 = fabs(P1);
	double S2 = fabs(P2);

	if((PI/2.0-TT) < S2 && S2 < (PI/2.0+TT))
		FLAG = true;
	if( S1 >TT )
		FLAG = false;

	double DA = (P2-P1);
	S1 = 0.0;
	S2 = 0.0;
	double E2 = ESQ;
	double E4 = E2*E2;
	double E6 = E4*E2;
	double E8 = E6*E2;
	double EX = E8*E2;
	double T1 = E2*(003.0/4.0);
	double T2 = E4*(015.0/64.0);
	double T3 = E6*(035.0/512.0);
	double T4 = E8*(315.0/16384.0);
	double T5 = EX*(693.0/131072.0);
	double AA  = 1.0+T1+3.0*T2+10.0*T3+35.0*T4+126.0*T5;
    double B  = 0;
	double C  = 0;
	double D  = 0;
	double E  = 0;
	double DB = 0;
	double DC = 0;
	double DD = 0;
	double DE = 0;
	double DF = 0;

	if(FLAG)
		goto _1;

	B  = T1+4.0*T2+15.0*T3+56.0*T4+210.0*T5;
	C  = T2+06.0*T3+28.0*T4+120.0*T5;
	D  = T3+08.0*T4+045.0*T5;
	E  = T4+010.0*T5;
	DB = sin(P2*2.0)-sin(P1*2.0);
	DC = sin(P2*4.0)-sin(P1*4.0);
	DD = sin(P2*6.0)-sin(P1*6.0);
	DE = sin(P2*8.0)-sin(P1*8.0);
	DF = sin(P2*10.0)-sin(P1*10.0);
	S2 = -DB*B/2.0+DC*C/4.0-DD*D/6.0+DE*E/8.0-DF*T5/10.0;

_1:
	S1 = DA*AA;
	ARC = A*(1.0-ESQ)*(S1+S2);
}


void GpnLoa(double DL,double &AZ1,double &AZ2,
			double &AO,double &BO,double &SMS,
			double A,double F,double ESQ)
{
	double TT= 5E-13;
	double DLON = fabs(DL);
	double CONS = (PI-DLON)/(PI*F);
	double AZ   = asin(CONS);
	double T1   =    1.0;
	double T2   =  (-1.0/4.0)*F*(1.0+F+F*F);
	double T4   =    3.0/16.0*F*F*(1.0+(9.0/4.0)*F);
	double T6   = (-25.0/128.0)*F*F*F;
	double T8;
	int	ITER = 0;
	double DistEllip;
	double C2;
	double CS1;
	double ESQP;
	double U2;
	double U4;
	double U6;
	double U8;
_1:
	ITER = ITER+1;
	DistEllip  = cos(AZ);
	C2   = DistEllip*DistEllip;
	AO   = T1 + T2*C2 + T4*C2*C2 + T6*C2*C2*C2;
	CS1   = CONS/AO;
	DistEllip    = asin(CS1);
	if( fabs(DistEllip-AZ)<TT )
		goto _2;

	AZ   = DistEllip;
	if( ITER < 6 )
		goto _1;

_2:
	AZ1  = DistEllip;
	if( DL<0.0 )
		AZ1 = 2.0*PI-AZ1;
	AZ2  = 2.0*PI-AZ1;
	ESQP = ESQ/(1.0-ESQ);
	DistEllip    = cos(AZ1);
	U2   = ESQP*DistEllip*DistEllip;
	U4   = U2*U2;
	U6   = U4*U2;
	U8   = U6*U2;
	T1   =     1.0;
	T2   =    (1.0/4.0)*U2;
	T4   =   (-3.0/64.0)*U4;
	T6   =    (5.0/256.0)*U6;
	T8   = (-175.0/16384.0)*U8;
	BO   = T1 + T2 + T4 + T6 + T8;
	DistEllip    = sin(AZ1);
	SMS  = A*PI*(1.0 - F*fabs(DistEllip)*AO - BO*(1.0-F));
}

void Gpn2Xyz(int N,
			 double X,double Y,double Z,
			 double &T1,double &T2,double &T3,
			 double A,double F,double ESQ)
{
	double TOL =1.0E-13;
	double E = (1.0-ESQ);

	double P1 = 0;
	double E1 = 0;
	double H  = 0;
	double W  = 0;
	double R  = 0;
	double EH = 0;
	double DistEllip  = 0;
	double C  = 0;
	double T  = 0;

	if(N != 2 )
	{
		P1 = X;
		E1 = Y;
		H  = sin(P1);
		W  = sqrt(1.0-ESQ*H*H);
		R  = A/W;
		if( N==1 )
		{
			if( E1<0)
				E1 = 2.0*PI+E1;
			EH = Z;
			W  = (R+EH)*cos(P1);
			T1 = W*cos(E1);
			T2 = W*sin(E1);
			T3 = H*(R*E+EH);
		}
		else
		{
			DistEllip  = cos(E1);
			H  = A*E/(W*W*W);
			W  = sin(E1);
			T1 = R;
			T2 = H;
			T3 = (T1*T2)/(T1*DistEllip*DistEllip+T2*W*W);
		}
	}
	else
	{
		N  = 1;
		W  = sqrt(X*X+Y*Y);
		C  = Z/W;
		W  = C/E;
		T2 = atan2(Y,X);
		DistEllip  = atan(W);
_1:
		H  = sin(DistEllip);
		W  = sqrt(1.0-ESQ*H*H);
		R  = A/W;
		T  = C*(1.0+(R*ESQ*H)/Z);
		T  = atan(T);
		if( fabs(DistEllip-T)>TOL )
		{
			DistEllip = T;
			N = N+1;
			if( N<=10 )
				goto _1;
		}

		T1 = T;
		T3 = Z/H-R*E;
	}
}
