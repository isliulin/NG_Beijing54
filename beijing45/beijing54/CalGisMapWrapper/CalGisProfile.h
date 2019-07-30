#ifndef __CAL__GIS_PROFILE__H__
#define __CAL__GIS_PROFILE__H__

#include "CalGisMapWrapper.h"

/*
����profile
profile ��Ҫ����������:
	height			(dem or dsm) �߶�
	clutter			��ò
	building		������߶�
	conductivity	�絼��
	������Ϣ
*/
//����profile
class GISMAP_API CalGis_Profile 
{
public:	
	static CalGis_Profile* Create();
	static CalGis_Profile* Create(int inSize);
	static bool	Destroy(CalGis_Profile* pDestroy);

public:
	CalGis_Profile(long noPoints);
	CalGis_Profile();
	CalGis_Profile(const CalGis_Profile& that);		//add by jjj 2013.8.8 ���ƹ���	
	CalGis_Profile& operator=(const CalGis_Profile& that);
	~CalGis_Profile();	

	//���������С
	bool ReSize(int nSize);

	//�ռ�����
	void Reset();

	//����ռ�
	void Clear();

public:
	long nSize;              //profile�Ĵ�С
	long noPoints;           //Profile �е�ĸ��� --��ʽ����ֵ

	//���һ����ʼ���������ֹ������
	double xStart;
	double yStart;
	double xEnd;
	double yEnd;

	long* xIndex;            //����ڵ�ͼ��ʼ�������
	long* yIndex;
	double* xPathCoord;      //·���е��ڵ�ͼ�еľ�������(UTM����WGS84)
	double* yPathCoord;
	double* distance;        //���㵽����վ�ľ���
	double* height;          //����ĸ߶�(dem����dsm)
	double* building;        //������߶�
	short* clutter;          //�����clutterֵ	
	short* zones;            //·���ϸ��������������0��A1���غ�½�� ��1��A2����½ ��2��B����
	double* adaptedHeight;   //�������ʺ�ĸ߶�
	double* conductivity;	 //�絼��
	double* lineOfSight;     //��ͨ���
	double* refractionIndex0m;
	double* refractionIndex1km;  //
	double* fieldSth;         
	short* gerechnet;
	double* RainRate;
	double* diffLoss;
	//double* RainRate;
};

#endif