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
	int GetContinuColorIndex(double DataValue);	//获取数据值对应的颜色索引

	void ModifyContinuColorTable(ContinuColor **ppContinuColor,int Color_Num);	

	bool ReadFromXMlFile(const char *pFile);
	bool ReadFromXMlFile(XmlDocument* pXmlFile);

	void ClearDataColor();
	int GetColorCount()const;

protected:
	CContinuSectionColorManager& operator=(const CContinuSectionColorManager& ){ return *this;}	//拒绝赋值函数在外部被调用

private:
	enum {ContinuColor_MaxNumber = 128};						//如果不够可以改大
	ContinuColor * m_ContinuColor[ContinuColor_MaxNumber];		//使用数组
	int m_ContinuRealNumer;	

};

#endif