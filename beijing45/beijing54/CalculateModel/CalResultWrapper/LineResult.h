#ifndef __CAL__LINE__RESULT__H__
#define __CAL__LINE__RESULT__H__

#include "CalResultWrapper.h"
#include "../BasicDef/DataTypes.h"
#include "../DataModel/EnumDef.h"

class RESULT_API LineResult
{
public:
	static LineResult* Create();
	static LineResult* Create(int inSize);
	static bool	Destroy(LineResult* pDestroy);

public://������������
	LineResult(long noPoints);
	LineResult();
	~LineResult();

public:

	//���������С
	int ReSize(int nSize);

	//�ռ�����
	void Reset();

	//����ռ�
	void Clear();
	//��ȡֵ�б�
	float* GetValueList(){return m_pValueList;}

	//���õ�index���ֵ
	int SetPointValue(int index, CDoublePoint& point, float value);

	//��ȡ��index���ֵ
	int GetPointValue(int index, CDoublePoint& point, float& value);

	//��ȡ����ϵ
	int GetCoordSys(){ return m_nCoordSys; }

	//��������ϵ
	void SetCoordSys(int inSys) { m_nCoordSys = inSys; }

	//��ȡ�ռ�Ĵ�С
	long Size() {return m_nSize; }

	//��ȡʵ�ʵ�ĸ���
	long GetPointsNum(){ return m_nNoPoints; }

	//��ȡ�������ĵ�λ���
	CalResult_Unit GetCalResultDataUnit() { return m_eDataUnit;}

	//���ü������ĵ�λ���
	void SetCalResultDataUnit(CalResult_Unit inUnit) { m_eDataUnit = inUnit; }

private:
	//�����С
	long m_nSize; 

	//����е�ĸ���
	long m_nNoPoints;

	//�㼯
	//��ʹ�õ�����ϵ���
	int m_nCoordSys;  

	//�㼯
	CDoublePoint* m_pPointList;  

	//ֵ�б�
	float* m_pValueList; 

	//����ĵ�λ���
	CalResult_Unit m_eDataUnit;
	//��Ϊ�������ʱ�轻���ֽ���
protected:
	void SwapData();

public:
	int ReadFromFile(const char * file);
	int WriteToFile(const char* file); 
};
#endif