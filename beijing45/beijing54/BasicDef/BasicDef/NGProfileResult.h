#pragma once
#include <string.h>
#include <vector>
#include <string>
typedef std::vector<double> stdDoubleVector;
typedef std::string STDtring;
class CNGProfileResult
{
public:
	CNGProfileResult(void);
	virtual ~CNGProfileResult(void);
public:
	STDtring m_field_unit;
	int m_map_coordindex;
	int m_MaxBarrierPer_Index;//��ͨ�����ĵ��±�
	stdDoubleVector m_longitude_v;//���ȼ�
	stdDoubleVector m_latitude_v;//γ�ȼ�
	stdDoubleVector m_distance_v;//���뼯
	stdDoubleVector m_height_v;//�߶ȼ�
	stdDoubleVector m_clutter_v;//��ò��
	stdDoubleVector m_conductivity_v;//�絼�ʼ�
	stdDoubleVector m_field_v;//��ǿ��
	stdDoubleVector m_fresnel_up_v;//���������޼�
	stdDoubleVector m_fresnel_down_v;//���������޼�
	stdDoubleVector m_BarrierPer_v;//�ϰ��ٷֱȼ�
    double m_RxAngle;//�����ڱν�
	double m_TxAngle;//�����ڱν�

	//����̨�Ĳ���  �߶� ��γ�� ����Ƶ��
	double mFromlongitude;
	double mFromlatitude;
	double mStartheight;//���������θ߶�
	double mFrequencyMhz;
	//����̨�Ĳ��� �߶� ��γ��
	double mTolongitude;
	double mTolatitude;
	double mEndheight;//���������θ߶�

public: 
	void Clear();
	bool IsValid() const;
	unsigned int GetSize() const;
};

class CNGShortWaveResult
{
public:
	CNGShortWaveResult(void)
	{
		mnYear = 2013;
		mnMonth = 1;
		memset(mpBMUF, 0, 24*sizeof(float));
		memset(mpBLUF, 0, 24*sizeof(float));
		memset(mpOperMUF, 0, 24*sizeof(float));
		memset(mpOptMUF, 0, 24*sizeof(float));
	}
	virtual ~CNGShortWaveResult(void){}
public:
	int mnYear;         //��
	int mnMonth;        //�·�
	float mpBMUF[24];   //����������Ƶ������ 24��Сʱ
	float mpBLUF[24];   //������С����Ƶ������ 24��Сʱ
	float mpOperMUF[24];//����MUF���� 24��Сʱ
	float mpOptMUF[24]; //��ѹ���Ƶ�� 24��Сʱ

};