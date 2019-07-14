#ifndef __CONTINUSECTION__COLOR_MANAGER__H__
#define __CONTINUSECTION__COLOR_MANAGER__H__

#include "ColorManagerBase.h"



class CContinuSectionColorManager: public CColorManagerBase
{
public:
	CContinuSectionColorManager();
	CContinuSectionColorManager(const CContinuSectionColorManager &pr);
	virtual ~CContinuSectionColorManager();

public:
	COLORGBA GetDataColor(double dataValue);

	int GetContinuColorRealNumer() const { return m_ContinuRealNumer;}	
	const ContinuColor * GetContinuColorItem(int nIndex);
	int GetContinuColorIndex(double DataValue);	//��ȡ����ֵ��Ӧ����ɫ����

	void ModifyContinuColorTable(ContinuColor **ppContinuColor,int Color_Num);	

	bool ReadFromXMlFile(const char *pFile);
	bool ReadFromXMlFile(XmlDocument* pXmlFile);

	void ClearDataColor();
	int GetColorCount()const;

protected:
	CContinuSectionColorManager& operator=(const CContinuSectionColorManager& ){ return *this;}	//�ܾ���ֵ�������ⲿ������

private:
	enum {ContinuColor_MaxNumber = 128};						//����������ԸĴ�
	ContinuColor * m_ContinuColor[ContinuColor_MaxNumber];		//ʹ������
	int m_ContinuRealNumer;	

};

#endif