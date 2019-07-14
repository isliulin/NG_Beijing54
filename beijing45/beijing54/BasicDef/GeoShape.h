#pragma once

#include "DataTypes.h"
#include <vector>

// add by jie-z@2012/06/20
/**
 * ����������״�ĳ���
 * ���޸����е��࣬ʹ��̳���CShape
 */
class CGeoShape
{
public:
	virtual ~CGeoShape(){}
public:
	long m_nCoordSys;   //�����ڵ�����ϵ���
};

//�ռ��е�Ķ���  --Z����ʼ���Ǹ߶���Ϣ��x��y������в�ͬ������ϵ
class CGeoPoint : public CGeoShape //    upd by jie-z@2013/07/20
{
public:
//	long m_nCoordSys;   //�����ڵ�����ϵ���    // del by jie-z@2013/07/20

	CDoublePoint m_Point;
};

//�ռ����ߵĶ��� 
class CGeoLine : public CGeoShape //    upd by jie-z@2013/07/20
{
public:
	//�����ڵ�����ϵ���
//	long m_nCoordSys;       // del by jie-z@2013/07/20

	//��ʼ��
	CDoublePoint m_SPoint;

	//��ֹ��
	CDoublePoint m_EPoint;
};

//��ͼ�о��ο�Ķ���
class CGeoRectangle : public CGeoShape //    upd by jie-z@2013/07/20
{
public:
//	long m_nCoordSys;    // del by jie-z@2013/07/20

	//���θ߶�
	double m_dASLM;

	//һ������
	CDoublePoint2D m_Corner1;

	//�������һ������
	CDoublePoint2D m_Corner2;
};

//��ͼ��Բ�Ķ���
class CGeoCircle : public CGeoShape //    upd by jie-z@2013/07/20
{
public:
//	long m_nCoordSys;   //�����ڵ�����ϵ���    // del by jie-z@2013/07/20

	//���θ߶�
	double m_dASLM;

	//���ĵ�����
	CDoublePoint2D m_Center;

	//�뾶
	double m_dRadiusKM;
};

class CGeoPolygon : public CGeoShape //    upd by jie-z@2013/07/20
{
public:
	CGeoPolygon();

	~CGeoPolygon();

	CGeoPolygon(int nPointNum);

	//copy���캯��
    CGeoPolygon( CGeoPolygon& polygon);

	//��ֵ����
	CGeoPolygon& operator=(CGeoPolygon& polygon);

	//���������С
	bool Resize(int nSize);

	//��0
	void Reset();

	//�ͷſռ�
	void ReleaseData();

	//������д���ļ�
	bool WriteToFile(const char* filename);

	//���ļ��ж�ȡ����
	bool ReadFromFile(const char * filename);

	bool ReadFromTxtFile( const char *filename );
	bool ReadFromStream( std::istream &instream  );

	//�Ƿ���
	bool m_bClosed;

	//��ĸ���
	int m_nPointsNum;

	//�ܴ�С��ָ�洢�ռ�
	int m_nSize;

	//����������ϵ
//	int m_nCoordSys;    // del by jie-z@2013/07/20

	//��ļ���
	CDoublePoint* m_pPointData;
};


// ������״դ�񻯺�Ľ����
class CRasterlizedRst
{
public:
	CRasterlizedRst() {
	}

	~CRasterlizedRst() {
		m_v2dPointData.clear();
	}

	//������
	std::vector<CDoublePoint2D> m_v2dPointData;
};
