#ifndef __INCLUDED_EARTHCOORD__COMPUTE__H__
#define __INCLUDED_EARTHCOORD__COMPUTE__H__

#if defined(EATHCOORDCOMPUTE_LIB)
	#define COORD_API
#else
	#if defined(_WIN32) || defined(__WIN32__)
		#ifdef EATHCOORDCOMPUTE_EXPORTS
			#define COORD_API __declspec(dllexport)
		#else
			#define COORD_API __declspec(dllimport)
		#endif 
	#else 
		#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
			#define COORD_API __attribute__ ((visibility("default")))
		#else
			#define COORD_API
		#endif	// __GNUC__		
	#endif		// WIN32 / !WIN32
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	//////////////////////////////////////////////////////////////////////////
	//2D坐标计算
	/*
	计算两点(2D)之间的距离
	输入: 
	A 点经纬度坐标 
	Lat1 纬度	南纬为正，单位 弧度
	Lon1 纬度	东经为正，单位 弧度

	B 点经纬度坐标 
	Lat2 纬度	南纬为正，单位 弧度
	Lon2 纬度	东经为正，单位 弧度

	A,地球长半轴
	F,地球扁平率

	输出: 
	方位角(从A到B 矢量连线ab),角度从正北方向开始，沿顺时针方向转到ab，
	Az1 单位 弧度

	方位角(从B到A 矢量连线ba),角度从正北方向开始，沿顺时针方向转到ba，
	Az2 单位 弧度

	长度
	S ，单位 m
	*/
	COORD_API void Distance2D(
		double Lat1,double Lon1,			//起始点A点纬度，经度
		double Lat2,double Lon2,			//终止点B点纬度，经度
		double &Az1,double &Az2,
		double &DistEllip,					//方位角和距离
		double A,double F);					

	/*
	计算一个点B(Lat2,Lon2) 的坐标，该点满足如下条件:
	和已知点A(Lat1,Lon1) 的距离为 S，方位角为Faz (A-->B矢量方位角)

	输入: 
	A 点经纬度坐标 
	Lat1 纬度	南纬为正，单位 弧度
	Lon1 纬度	东经为正，单位 弧度

	方位角(从A到B 矢量连线ab),角度从正北方向开始，沿顺时针方向转到ab，
	Az1 单位 弧度

	长度
	S ，单位 m

	A,地球长半轴
	F,地球扁平率

	输出: 
	B 点经纬度坐标 
	Lat2 纬度	南纬为正，单位 弧度
	Lon2 纬度	东经为正，单位 弧度

	方位角(从B到A 矢量连线ba),角度从正北方向开始，沿顺时针方向转到ba，
	Az2 单位 弧度
	*/
	COORD_API void Direct2D(
		double Lat1,double Lon1,			//起始点A点纬度，经度
		double &Lat2,double &Lon2,			//终止点B点纬度，经度
		double Az1,double &Az2,
		double DistEllip,
		double A,double F);					//方位角和距离

	//////////////////////////////////////////////////////////////////////////
	//3D坐标计算
	//与2D计算相比，多了一个高度值
	COORD_API void  Distance3D(
		double Lat1,double Lon1,double h1,	//起始点A点纬度，经度
		double Lat2,double Lon2,double h2,	//终止点B点纬度，经度
		double &Az1,double &Az2,			//方位角
		double &DistEllip,double &Distmm,	//距离:EllipSoid distace ,Mark-to-Mark distance
		double A,double F);	

	//3D求点
	COORD_API void Direct3D(
		double Lat1,double Lon1,double h1,	//起始点A点纬度，经度
		double &Lat2,double &Lon2,double h2,//终止点B点纬度，经度
		double Az1,double &Az2,
		double DistEllip,double &Distmm,
		double A,double F);

	//3D距离计算，输出更多信息
	COORD_API void  Distance3DExt(
		double Lat1,double Lon1,double h1,	//起始点A点纬度，经度
		double Lat2,double Lon2,double h2,	//终止点B点纬度，经度
		double &Az1,double &Az2,			//方位角
		double &DistEllip,double &Distmm,	//距离:EllipSoid distace ,Mark-to-Mark distance
		double &dx,double &dy,double &dz,	//XYZ差值
		double &dn,double &de,double &du,	//neu
		bool &bZen,double &Zd,double &Zn,	//Zenith信息
		double A,double F);	

	COORD_API void  Direct3DExt(
		double Lat1,double Lon1,double h1,	//起始点A点纬度，经度
		double &Lat2,double &Lon2,double h2,//终止点B点纬度，经度
		double Az1,double &Az2,				//方位角
		double DistEllip,double &Distmm,	//距离:EllipSoid distace ,Mark-to-Mark distance
		double &dx,double &dy,double &dz,	//XYZ差值
		double &dn,double &de,double &du,	//neu
		bool &bZen,double &Zd,double &Zn,	//Zenith信息
		double A,double F);	

	//////////////////////////////////////////////////////////////////////////
	//度分秒，弧度，十进制经纬度数据相互转换函数

	/*将给定的度，分，秒转换成弧度
	输入: 度分秒 
	d		度
	m		分	
	sec		秒
	isign	==true--> 北纬 或者 东经 或者 方位角正值  
	==false-->南纬 或者 西经 或者 方位角负值  

	输出: 
	val，弧度
	*/
	COORD_API void DmsToRad(int d,int m,double sec,
		bool isign,double &Radval);

	/*将给定的弧度转换成度，分，秒
	输入: 
	val，弧度

	输出: 度分秒 
	d		度
	m		分	
	sec		秒
	isign	==true-->北纬或者东经  ==false-->南纬或者西经
	*/
	COORD_API void RadTodms(double Radval,int &d,int &m,double &sec,bool &isign);

	//十进制经纬度转换成弧度
	COORD_API void DecimalToRad(double DecimalVal,double &Radval);

	//弧度转换成十进制经纬度
	COORD_API void RadToDecimal(double Radval,double &DecimalVal);

	//度分秒转换成十进制
	COORD_API void DmsToDecimal(int d,int m,double sec,
		bool isign,double &DecimalVal);

	//十进制转换成度分秒
	COORD_API void DecimalTodms(double DecimalVal,int &d,int &m,double &sec,bool &isign);

	//确保度分秒在合理的区间内
	//tol为小数精度，如:0.00005,0.0005等
	COORD_API void Fixdms(int &d, int &m, double &sec, double tol);

	//////////////////////////////////////////////////////////////////////////
	//经纬度弧度坐标 (Lat,Lon,Height) 转成XYZ坐标 (X,Y,Z) 
	/*
	输入: 
	A 点经纬度坐标 
	Lat1 纬度	南纬为正，单位 弧度
	Lon1 纬度	东经为正，单位 弧度
	h1   A点高度， 单位 m

	输出:
	x1	X 坐标，单位 m
	y1	T 坐标，单位 m
	z1	Z 坐标，单位 m
	*/
	COORD_API void GeodeticToxyz(
		double Lat1,double Lon1,double h1,
		double &x1,double &y1,double &z1,
		double A,double F);

	//XYZ坐标 (X,Y,Z) 转成 经纬度弧度坐标 (Lat,Lon,Height)
	/*
	输入: 
	x1	X 坐标，单位 m
	y1	T 坐标，单位 m
	z1	Z 坐标，单位 m

	输出:
	A 点经纬度坐标 
	Lat1 纬度	南纬为正，单位 弧度
	Lon1 纬度	东经为正，单位 弧度
	h1   A点高度， 单位 m
	*/
	COORD_API bool XyzToGeodetic(
		double x1,double y1,double z1,
		double &Lat1,double &Lon1,double &h1,
		double A,double F);

	//neu坐标计算
	/*
	输入: 
	A 点经纬度坐标 
	Lat1 纬度	南纬为正，单位 弧度
	Lon1 纬度	东经为正，单位 弧度
	dx X 坐标差值，单位 m
	dy Y 坐标差值，单位 m
	dz Z 坐标差值，单位 m
	
	输出:
	dn	n 坐标，单位 m
	de	e 坐标，单位 m
	du	u 坐标，单位 m
	*/
	COORD_API void DeletaXyzToNeu(
		double dx,double dy,double dz,
		double Lat1,double Lon1,
		double &dn,double &de,double &du);

	//XTZ坐标差值计算
	/*
	输入: 
	A 点经纬度坐标 
	Lat1 纬度	南纬为正，单位 弧度
	Lon1 纬度	东经为正，单位 弧度
	dn	n 坐标，单位 m
	de	e 坐标，单位 m
	du	u 坐标，单位 m

	输出:
	dx X 坐标差值，单位 m
	dy Y 坐标差值，单位 m
	dz Z 坐标差值，单位 m
	*/
	COORD_API void NeuToDeletaXyz(
		double dn,double de,double du,
		double Lat1,double Lon1,
		double &dx,double &dy,double &dz);

	//通过Makr Distance 求 Ellip Distance
	/*
	输入: 
	Lat1 A点纬度坐标,南纬为正，单位 弧度
	h1   A点高度， 单位 m
	Az1  方位角,   单位 弧度
	h2   B点高度， 单位 m
	
	Distmm Mark 距离，单位 m

	输出:
	DistEllip EllipSoid距离，单位 m
	*/
	COORD_API void MarkDistToEllipDist(
		double Lat1,double Az1,double h1,double h2,
		double Distmm,double &DistEllip,
		double A,double F);

	//////////////////////////////////////////////////////////////////////////
	//EllipSolid,地球长半轴和扁平率数据
	COORD_API long GetMaxEllipSolid();	//返回EllipSolid个数
	COORD_API bool Get_EllipSoid(long EllipIndex, char *pName,double&dA,double &dF);
	COORD_API bool Get_EllipSoid_Name(long EllipIndex, char *pName);
	COORD_API bool Get_EllipSoid_AF(long EllipIndex, double&dA,double &dF);


#ifdef __cplusplus
}
#endif

#endif