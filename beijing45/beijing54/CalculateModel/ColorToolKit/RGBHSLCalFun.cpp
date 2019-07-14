#include "ColorToolKit.h"
#include "RGBHSLCalFun.h"

double max_value(double R, double G, double B)
{
	if(R>G)
	{
		if(R>B)
			return R;
		else
			return B;
	}
	else
	{
		if(G>B)
			return G;
		else
			return B;
	}
}

double min_value(double R, double G, double B)
{
	if(R<G)
	{
		if(R<B)
			return R;
		else
			return B;
	}
	else
	{
		if(G<B)
			return G;
		else
			return B;
	}
}

inline double Hue_2_RGB( double v1, double v2, double vH )             //Function Hue_2_RGB
{
	if ( vH < 0 )
	{
		vH += 1;
	}
	if ( vH > 1 )
	{
		vH -= 1;
	}
	if ( ( 6 * vH ) < 1 )
	{
		return ( v1 + ( v2 - v1 ) * 6 * vH );
	}
	if ( ( 2 * vH ) < 1 )
	{
		return ( v2 );
	}

	if ( ( 3 * vH ) < 2 )
	{
		return ( v1 + ( v2 - v1 ) * ( ( 2 / 3.0 ) - vH ) * 6 );
	}

	return ( v1 );
}

//////////////////////////////////////////////////////////////////////////
//RGB µ½ HSLµÄ×ª»»
void RGB2HSL(BYTE R, BYTE G, BYTE B, BYTE& H, BYTE& S, BYTE& L)
{
	double var_R = ( R / 255.0 );						//RGB from 0 to 255
	double var_G = ( G / 255.0 );
	double var_B = ( B / 255.0 );

	double var_Min = min_value( var_R, var_G, var_B );  //Min. value of RGB
	double var_Max = max_value( var_R, var_G, var_B );  //Max. value of RGB
	double del_Max = var_Max - var_Min;					//Delta RGB value
	double dL = 0.0;
	double dH = 0.0;
	double dS = 0.0;

	dL = ( var_Max + var_Min ) / 2;

	if ( del_Max == 0 )									//This is a gray, no chroma...
	{
		dH = 0;											//HSL results from 0 to 1
		dS = 0;
	}
	else												//Chromatic data...
	{
		if ( dL < 0.5 ) 
		{
			dS = del_Max / ( var_Max + var_Min );
		}
		else
		{
			dS = del_Max / ( 2 - var_Max - var_Min );
		}

		double del_R = ( ( ( var_Max - var_R ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
		double del_G = ( ( ( var_Max - var_G ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
		double del_B = ( ( ( var_Max - var_B ) / 6 ) + ( del_Max / 2 ) ) / del_Max;

		if( var_R == var_Max )
		{
			dH = del_B - del_G;
		}
		else if ( var_G == var_Max )
		{
			dH = ( 1 / 3.0 ) + del_R - del_B;
		}
		else if ( var_B == var_Max )
		{
			dH = ( 2 / 3.0 ) + del_G - del_R;
		}
		if ( dH < 0 )
		{
			dH += 1;
		}
		else if ( dH > 1 )
		{
			dH -= 1;
		}		
	}

	H = (BYTE)(dH*240);
	L = (BYTE)(dL*240);
	S = (BYTE)(dS*240);
}

void HSL2RGB(BYTE H, BYTE S, BYTE L, BYTE& R, BYTE& G, BYTE&B)
{
	double dH = H / 240.0;
	double dS = S / 240.0;
	double dL = L / 240.0;

	double var_2 = 0.0;
	double var_1 = 0.0;

	if ( dS == 0 )                       //HSL from 0 to 1
	{
		R = (BYTE)(dL * 255);            //RGB results from 0 to 255
		G = (BYTE)(dL * 255);
		B = (BYTE)(dL * 255);
	}
	else
	{
		if ( dL < 0.5 ) 
		{
			var_2 = dL * ( 1 + dS );
		}
		else 
		{
			var_2 = ( dL + dS ) - ( dS * dL );
		}

		var_1 = 2 * dL - var_2;

		R = (BYTE)(255 * Hue_2_RGB( var_1, var_2, dH + ( 1 / 3.0 ))); 
		G = (BYTE)(255 * Hue_2_RGB( var_1, var_2, dH ));
		B = (BYTE)(255 * Hue_2_RGB( var_1, var_2, dH - ( 1 / 3.0 )));

	} 
}
