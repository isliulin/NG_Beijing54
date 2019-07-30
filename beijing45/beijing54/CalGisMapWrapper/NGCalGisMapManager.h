#ifndef __NG__CAL__GIS_MANAGER__H__
#define __NG__CAL__GIS_MANAGER__H__

#include "../NGMap/INGMapGeo.h"
#include "ICalGisMapManager.h"

class CNGCalGisMapManger:public ICalGis_MapManger
{
public:
	CNGCalGisMapManger();
	~CNGCalGisMapManger();

public:
	virtual void EnableMap_Topo(bool bEnale);
	virtual bool IsEnableMap_Topo() { return m_bTopoNeeded;}

	virtual void EnableMap_Conduct(bool bEnale);
	virtual bool IsEnableMap_Conduct() { return m_bConductNeeded;}

	virtual void EnableMap_Clutter(bool bEnale);
	virtual bool IsEnableMap_Clutter() { return m_bMorphoNeeded;}

	const bool HasMapType(CalMapType mapType);

	//��ͼ����:dsm,dem,dhm,dom,pop,con,����ʹ�õ�ͼ����
	virtual bool SetCalMapFilePath(CalMapType mapType,const char *pFilePath);		//dsm
	virtual const char *GetCalMapFilePath(CalMapType mapType) { return m_szCalMapFilePath[mapType];}
	virtual void DeleteCalMap(CalMapType mapType);
	virtual void DeleteAllCalMap();
	virtual void ReleaseCalMapData(CalMapType mapType);	//���ͷŵ�ͼ�ڴ�����
	virtual void ReleaseAllCalMapData();
	
	//���ü���ʹ�õ�ͼ��
	virtual unsigned int GetCalLayers();				//��ȡ����������
	virtual bool SetActiveCalLayer(unsigned int lay);	//���ü���ͼ��
	virtual unsigned int GetActiveCalLayer();

	//��ȡ��ͼ���е�һЩ��Ϣ
	virtual short GetMapCoordSys(){ return m_nCoordSys; }
	virtual long GetMapWidth(){ return m_nWidth; }				//��ȡ���
	virtual long GetMapHeight(){ return m_nHeight; }			//��ȡ�߶�
	virtual double GetResolutionX(){ return m_Xspacing; }		//��ȡˮƽ����
	virtual double GetResolutionY(){ return m_Yspacing; }		//��ȡ��ֱ���򾫶�
	virtual double GetMapLowerLeftXCoord(){ return m_XLowLeft;}	//��ͼ���½����� 
	virtual double GetMapLowerLeftYCoord(){ return m_YLowLeft;}

	//////////////////////////////////////////////////////////////////////////
	//��ȡprofile��صĺ���
	//��ȡ���������յ�֮���profile�����������յ������Ϊ���������ݵ�ͼ��ʼ��ͷֱ��ʻ�ȡ���������
	virtual CalGis_Profile* GetProfile(long xBegin, long yBegin, long xEnd, long yEnd,CalGis_Profile *pProfile);

	//ָ����ȡ��profile�����profile��������������ƽ�������ȡ��Ӧ�����棬���յ�ͼ�ķֱ���
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType,CalGis_Profile *pProfile);

	//��ȡָ���ֱ��ʵ�profile,profile��������������ƽ�������ȡ��Ӧ�����棬����ָ���ķֱ���
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType, 
		double xRes, double yRes, CalGis_Profile *pProfile);

	//ָ����ȡ��profile��𣬲���ָ��profile�п��ǵĵ�ĸ���
	virtual CalGis_Profile* GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, EProfilerType eProfileType, 
		int noPoints,CalGis_Profile *pProfile);
	//////////////////////////////////////////////////////////////////////////

	//��ȡ����ͼ�ĸ߶�
	virtual short GetTopoValue(long x, long y);

	//��ȡDEMͼ�ĸ߶�
	virtual short GetDemHeight(long x, long y);

	//��ȡ�������潨����͵��εĸ߶�ֵ
	virtual short GetDsmHeight(long x, long y);

	//��ȡ������߶ȣ����û�е�ͼ����-1��
	virtual short GetDhmHeight(long x,long y);

	//��ȡclutter���ݣ����û��clutter��ͼ���򷵻�-1��
	virtual short GetClutterValue(long x, long y);

	virtual short GetTopoValue(double x, double y);			//��ȡ����ͼ�ĸ߶�

	//��ȡDEMͼ�ĸ߶�
	virtual short GetDemHeight(double x, double y);

	//�ͷż��ص��ڴ��еĵ�ͼ����,���ǵ�ͼ��Ϣ����

	//�ж�x,yλ�ô���ֵ�Ƿ�����Чֵ
	virtual bool isInvalidValue(int x, int y);
	//�жϸ����ĵ��Ƿ��ڵ�ͼ����
	virtual bool IsPointOutofMap(long xPoint, long yPoint, long nCoordSys);
	//�жϸ����ĵ��Ƿ��ڵ�ͼ����
	virtual bool IsPointOutofMap(double xPoint, double yPoint, long nCoordSys);

	//����ת��
	//��ȡ���ڵ�ͼ���������
	virtual bool GetMapCoordinate(double xPoint, double yPoint, int nCoordSys, long& xOut, long& yOut);
	//��ȡ���ͼ����ϵ��ͬ������
	virtual bool GetMapCoordinate(double xPoint, double yPoint, int nCoordSys, double& xOut, double& yOut);
	//���ݵ�ͼ����������ȡ��Ӧ����ϵ������
	virtual bool GetCoordinateFromMap(long xPoint, long yPoint, double& xOut, double& yOut, int nCoordSys);
	virtual bool MapCoordTrans( long fromSys, long toSys, double fromX, double fromY,double *toX,  double *toY);

protected:
	void UpdateMap();

	//��ȡƽ������ϵ��ָ���ֱ��ʵ���·
	CalGis_Profile* GetProfileNG(double xBegin, double yBegin, double xEnd, double yEnd,
		double xRes, double yRes, CalGis_Profile *pProfile);

	//��ȡ��������ϵ��ָ���ֱ��ʵ���·
	CalGis_Profile* GetProfileGeo(double xBegin, double yBegin, double xEnd, double yEnd,
		double xRes, double yRes, CalGis_Profile *pProfile);

	CalGis_Profile* GetProfileLocal(int nBSPosX, int nBSPosY, int nCurPosX, int nCurPosY, 
		double dxRes, double dyRes, CalGis_Profile *pProfile);

	//��ȡ������ʼ�����ֹ��֮�������ͼ��Ϣ����ʼ�����ֹ�������ϵ���ͼ����ϵ��ͬ
	//˵���� �ú���ֻ���ڵ�ͼ����ϵΪgeo map��ʱ��ʹ�ã������ͼ����ϵ����geo��ʹ�øú���
	//����Ը�
	//�ú����������profile�еľ�γ�����꣬ (xBegin, yBegin) ����ʼ�����꣬��xEnd,yEnd)
	//����ֹ������
	bool GetProfile(double xBegin, double yBegin, double xEnd, double yEnd,CalGis_Profile *pProfile);	

	bool GetProfile(double xBegin, double yBegin, double xEnd, double yEnd, double xRes, double yRes, CalGis_Profile *pProfile);

	CalGis_Profile* GetMapProfile(double xBegin, double yBegin, double xEnd, double yEnd,CalGis_Profile *pProfile);

protected:
	IPyramidMapGeo *m_pCalMap[CALMAP_ALL];
	IPyramidMapGeo *m_pTopoMap;

	enum {MAX_FILE_PATH = 260};
	char m_szCalMapFilePath[CALMAP_ALL][MAX_FILE_PATH];

	ICalGis_MapManger::EProfilerType eProfileType;

	bool m_bTopoNeeded;				//�Ƿ���Ҫ�߳�ͼ
	bool m_bMorphoNeeded;
	bool m_bConductNeeded;			//�Ƿ���Ҫ�絼��ͼ

	//��ͼ�Ĺ�����Ϣ
	int m_nCoordSys;				//��ʼ�����������ϵ��Ϣ
	double m_XLowLeft;
	double m_YLowLeft;
	double m_Xspacing;
	double m_Yspacing;				//�ֱ��ʣ�ÿ�������ص�֮��ľ���;	
	long m_nWidth;
	long m_nHeight;

};

#endif