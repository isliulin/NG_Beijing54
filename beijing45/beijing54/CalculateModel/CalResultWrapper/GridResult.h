#ifndef __CAL__GRID__RESULT__H__
#define __CAL__GRID__RESULT__H__

#include "CalResultWrapper.h"
#include "../BasicDef/DataTypes.h"


//���񻯵�3D���
class RESULT_API GridResult
{
public:
	static GridResult* Create();
	static GridResult* Create(int nSize);
	static void	Destroy(GridResult*);

public:
	GridResult(void);
	GridResult(int nSize);
	~GridResult(void);

public:
	//���������С
	int ReSize(int nSize);

	//�ռ�����
	void Reset();

	//����ռ�
	void Clear();

	//���ø����������ĵ�
	int SetPoint(int nIndex, CDoublePoint& point, float fValue);

	//��ȡ�����������ĵ�
	int GetPoint(int nIndex, CDoublePoint& point, float& fValue);

	//��ȡ����ϵ
	int GetCoordSys(){ return m_nCoordSys; }

	//��������ϵ
	void SetCoordSys(int inSys) { m_nCoordSys = inSys; }

	//��ȡ�ռ�Ĵ�С
	void Size(int& nSize) { nSize = m_nSize; };

	//��ȡʵ�ʵ�ĸ���
	void GetPointsNum(int& nPointsNum){ nPointsNum = m_nPointsNum; }

	int WriteToFile(const char* filename);
	int ReadFromFile(const char * filename);

private:
	//�����С
	int m_nSize;

	//����е�ĸ���
	int m_nPointsNum;

	//�㼯
	//��ʹ�õ�����ϵ���
	int m_nCoordSys;

	//�㼯
	CDoublePoint* m_p3DPoints;
	float* m_pValues;
protected:
	void SwapData();
};


#endif
