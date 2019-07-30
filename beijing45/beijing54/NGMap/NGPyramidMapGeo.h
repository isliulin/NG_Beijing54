#ifndef __NG__PYRAMID_MAP_GEO__H__
#define __NG__PYRAMID_MAP_GEO__H__

#include "INGMapGeo.h"
#include <map>

class CNGPyramiMapGeo:public IPyramidMapGeo
{
public:
	CNGPyramiMapGeo();
	virtual ~CNGPyramiMapGeo();

	enum {NameBytes = 64};
	enum {MAX_FILE_PATH = 260};

public:
	virtual bool ReadPyramidMap(const char *pFilePath);						//��ȡդ���ͼ
	
	virtual unsigned int GetLayers(){return m_Maps.size();}					//��ȡ����������
	virtual bool SetActiveLayer(unsigned int lay);							//���ûͼ��
	virtual unsigned int GetActiveLayer(){return m_AcitveLayer;}
	virtual INGMapGeo* GetActiveLayerPtr(){return m_pAcitvieLayerMap;}		//��ȡ����ͼ��ĵ�ͼ�ӿڶ���

	//��������ͼ������ͼ�����½���ͬ����ͼ�����ͬ,����ϵ��ͬ,ȱʡֵ��ͬ
	virtual double GetMapLowerLeftXCoord(){return m_XLowLeft;}				//��ͼ���½����� 
	virtual double GetMapLowerLeftYCoord(){return m_YLowLeft;}				
	virtual int	GetMapDataType() { return m_MapDataType;}					//��ͼ�������MT_TOPO��MT_MORPH��
	virtual const char *GetCoordShortName(){return szCoordShortName;}
	virtual short GetDefaultValue(){return m_DefaultValue;}

	virtual double Get_Layer0_ResolutionX(){return m_Xspacing0;}			//ÿ������֮��ľ���
	virtual double Get_Layer0_ResolutionY(){return m_Yspacing0;}

protected:
	void ClearAllData();

protected:
	short m_DefaultValue;								//��ͼȱʡֵ
	int m_MapDataType;
	double	m_XLowLeft;
	double	m_YLowLeft;									//���½�����ֵ
	double m_Xspacing0;
	double m_Yspacing0;	
	char szCoordShortName[NameBytes];

	std::map<unsigned int,INGMapGeo *> m_Maps;
	INGMapGeo *m_pAcitvieLayerMap;
	unsigned int m_AcitveLayer;

};



#endif