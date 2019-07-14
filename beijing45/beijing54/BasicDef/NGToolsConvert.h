#ifndef _Convert_Tool_WAP_
#define _Convert_Tool_WAP_

class  CNGToolsConvert
{
public:
	CNGToolsConvert();
	virtual ~CNGToolsConvert();

public:
	static double Convert_dBuV_dBmW(double fs_dBuV, double Frequenz_Mhz);
	static double Convert_dBmW_dBuV(double power_dBmW, double Frequenz_Mhz);

	static double Convert_EIRP_ERP(double powerdBx);
	static double Convert_ERP_EIRP(double powerdBx);
	
	static double Convert_W_dBm(double powerW);
};

#endif
