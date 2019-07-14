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
	//2D�������
	/*
	��������(2D)֮��ľ���
	����: 
	A �㾭γ������ 
	Lat1 γ��	��γΪ������λ ����
	Lon1 γ��	����Ϊ������λ ����

	B �㾭γ������ 
	Lat2 γ��	��γΪ������λ ����
	Lon2 γ��	����Ϊ������λ ����

	A,���򳤰���
	F,�����ƽ��

	���: 
	��λ��(��A��B ʸ������ab),�Ƕȴ���������ʼ����˳ʱ�뷽��ת��ab��
	Az1 ��λ ����

	��λ��(��B��A ʸ������ba),�Ƕȴ���������ʼ����˳ʱ�뷽��ת��ba��
	Az2 ��λ ����

	����
	S ����λ m
	*/
	COORD_API void Distance2D(
		double Lat1,double Lon1,			//��ʼ��A��γ�ȣ�����
		double Lat2,double Lon2,			//��ֹ��B��γ�ȣ�����
		double &Az1,double &Az2,
		double &DistEllip,					//��λ�Ǻ;���
		double A,double F);					

	/*
	����һ����B(Lat2,Lon2) �����꣬�õ�������������:
	����֪��A(Lat1,Lon1) �ľ���Ϊ S����λ��ΪFaz (A-->Bʸ����λ��)

	����: 
	A �㾭γ������ 
	Lat1 γ��	��γΪ������λ ����
	Lon1 γ��	����Ϊ������λ ����

	��λ��(��A��B ʸ������ab),�Ƕȴ���������ʼ����˳ʱ�뷽��ת��ab��
	Az1 ��λ ����

	����
	S ����λ m

	A,���򳤰���
	F,�����ƽ��

	���: 
	B �㾭γ������ 
	Lat2 γ��	��γΪ������λ ����
	Lon2 γ��	����Ϊ������λ ����

	��λ��(��B��A ʸ������ba),�Ƕȴ���������ʼ����˳ʱ�뷽��ת��ba��
	Az2 ��λ ����
	*/
	COORD_API void Direct2D(
		double Lat1,double Lon1,			//��ʼ��A��γ�ȣ�����
		double &Lat2,double &Lon2,			//��ֹ��B��γ�ȣ�����
		double Az1,double &Az2,
		double DistEllip,
		double A,double F);					//��λ�Ǻ;���

	//////////////////////////////////////////////////////////////////////////
	//3D�������
	//��2D������ȣ�����һ���߶�ֵ
	COORD_API void  Distance3D(
		double Lat1,double Lon1,double h1,	//��ʼ��A��γ�ȣ�����
		double Lat2,double Lon2,double h2,	//��ֹ��B��γ�ȣ�����
		double &Az1,double &Az2,			//��λ��
		double &DistEllip,double &Distmm,	//����:EllipSoid distace ,Mark-to-Mark distance
		double A,double F);	

	//3D���
	COORD_API void Direct3D(
		double Lat1,double Lon1,double h1,	//��ʼ��A��γ�ȣ�����
		double &Lat2,double &Lon2,double h2,//��ֹ��B��γ�ȣ�����
		double Az1,double &Az2,
		double DistEllip,double &Distmm,
		double A,double F);

	//3D������㣬���������Ϣ
	COORD_API void  Distance3DExt(
		double Lat1,double Lon1,double h1,	//��ʼ��A��γ�ȣ�����
		double Lat2,double Lon2,double h2,	//��ֹ��B��γ�ȣ�����
		double &Az1,double &Az2,			//��λ��
		double &DistEllip,double &Distmm,	//����:EllipSoid distace ,Mark-to-Mark distance
		double &dx,double &dy,double &dz,	//XYZ��ֵ
		double &dn,double &de,double &du,	//neu
		bool &bZen,double &Zd,double &Zn,	//Zenith��Ϣ
		double A,double F);	

	COORD_API void  Direct3DExt(
		double Lat1,double Lon1,double h1,	//��ʼ��A��γ�ȣ�����
		double &Lat2,double &Lon2,double h2,//��ֹ��B��γ�ȣ�����
		double Az1,double &Az2,				//��λ��
		double DistEllip,double &Distmm,	//����:EllipSoid distace ,Mark-to-Mark distance
		double &dx,double &dy,double &dz,	//XYZ��ֵ
		double &dn,double &de,double &du,	//neu
		bool &bZen,double &Zd,double &Zn,	//Zenith��Ϣ
		double A,double F);	

	//////////////////////////////////////////////////////////////////////////
	//�ȷ��룬���ȣ�ʮ���ƾ�γ�������໥ת������

	/*�������Ķȣ��֣���ת���ɻ���
	����: �ȷ��� 
	d		��
	m		��	
	sec		��
	isign	==true--> ��γ ���� ���� ���� ��λ����ֵ  
	==false-->��γ ���� ���� ���� ��λ�Ǹ�ֵ  

	���: 
	val������
	*/
	COORD_API void DmsToRad(int d,int m,double sec,
		bool isign,double &Radval);

	/*�������Ļ���ת���ɶȣ��֣���
	����: 
	val������

	���: �ȷ��� 
	d		��
	m		��	
	sec		��
	isign	==true-->��γ���߶���  ==false-->��γ��������
	*/
	COORD_API void RadTodms(double Radval,int &d,int &m,double &sec,bool &isign);

	//ʮ���ƾ�γ��ת���ɻ���
	COORD_API void DecimalToRad(double DecimalVal,double &Radval);

	//����ת����ʮ���ƾ�γ��
	COORD_API void RadToDecimal(double Radval,double &DecimalVal);

	//�ȷ���ת����ʮ����
	COORD_API void DmsToDecimal(int d,int m,double sec,
		bool isign,double &DecimalVal);

	//ʮ����ת���ɶȷ���
	COORD_API void DecimalTodms(double DecimalVal,int &d,int &m,double &sec,bool &isign);

	//ȷ���ȷ����ں����������
	//tolΪС�����ȣ���:0.00005,0.0005��
	COORD_API void Fixdms(int &d, int &m, double &sec, double tol);

	//////////////////////////////////////////////////////////////////////////
	//��γ�Ȼ������� (Lat,Lon,Height) ת��XYZ���� (X,Y,Z) 
	/*
	����: 
	A �㾭γ������ 
	Lat1 γ��	��γΪ������λ ����
	Lon1 γ��	����Ϊ������λ ����
	h1   A��߶ȣ� ��λ m

	���:
	x1	X ���꣬��λ m
	y1	T ���꣬��λ m
	z1	Z ���꣬��λ m
	*/
	COORD_API void GeodeticToxyz(
		double Lat1,double Lon1,double h1,
		double &x1,double &y1,double &z1,
		double A,double F);

	//XYZ���� (X,Y,Z) ת�� ��γ�Ȼ������� (Lat,Lon,Height)
	/*
	����: 
	x1	X ���꣬��λ m
	y1	T ���꣬��λ m
	z1	Z ���꣬��λ m

	���:
	A �㾭γ������ 
	Lat1 γ��	��γΪ������λ ����
	Lon1 γ��	����Ϊ������λ ����
	h1   A��߶ȣ� ��λ m
	*/
	COORD_API bool XyzToGeodetic(
		double x1,double y1,double z1,
		double &Lat1,double &Lon1,double &h1,
		double A,double F);

	//neu�������
	/*
	����: 
	A �㾭γ������ 
	Lat1 γ��	��γΪ������λ ����
	Lon1 γ��	����Ϊ������λ ����
	dx X �����ֵ����λ m
	dy Y �����ֵ����λ m
	dz Z �����ֵ����λ m
	
	���:
	dn	n ���꣬��λ m
	de	e ���꣬��λ m
	du	u ���꣬��λ m
	*/
	COORD_API void DeletaXyzToNeu(
		double dx,double dy,double dz,
		double Lat1,double Lon1,
		double &dn,double &de,double &du);

	//XTZ�����ֵ����
	/*
	����: 
	A �㾭γ������ 
	Lat1 γ��	��γΪ������λ ����
	Lon1 γ��	����Ϊ������λ ����
	dn	n ���꣬��λ m
	de	e ���꣬��λ m
	du	u ���꣬��λ m

	���:
	dx X �����ֵ����λ m
	dy Y �����ֵ����λ m
	dz Z �����ֵ����λ m
	*/
	COORD_API void NeuToDeletaXyz(
		double dn,double de,double du,
		double Lat1,double Lon1,
		double &dx,double &dy,double &dz);

	//ͨ��Makr Distance �� Ellip Distance
	/*
	����: 
	Lat1 A��γ������,��γΪ������λ ����
	h1   A��߶ȣ� ��λ m
	Az1  ��λ��,   ��λ ����
	h2   B��߶ȣ� ��λ m
	
	Distmm Mark ���룬��λ m

	���:
	DistEllip EllipSoid���룬��λ m
	*/
	COORD_API void MarkDistToEllipDist(
		double Lat1,double Az1,double h1,double h2,
		double Distmm,double &DistEllip,
		double A,double F);

	//////////////////////////////////////////////////////////////////////////
	//EllipSolid,���򳤰���ͱ�ƽ������
	COORD_API long GetMaxEllipSolid();	//����EllipSolid����
	COORD_API bool Get_EllipSoid(long EllipIndex, char *pName,double&dA,double &dF);
	COORD_API bool Get_EllipSoid_Name(long EllipIndex, char *pName);
	COORD_API bool Get_EllipSoid_AF(long EllipIndex, double&dA,double &dF);


#ifdef __cplusplus
}
#endif

#endif