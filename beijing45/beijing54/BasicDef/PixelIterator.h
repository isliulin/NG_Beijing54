#pragma once

#include "../BasicDef/DataTypes.h"


/************************************************************************/
// CNGRectangle��
// ����:������
/************************************************************************/
class CDoubleRectangle
{
protected:
	// ���½�
	CDoublePoint2D m_ptLeftBottom;
	// ���Ͻ�
	CDoublePoint2D m_ptRightTop;

public:
	CDoubleRectangle(void);
	CDoubleRectangle(CDoublePoint2D ptLeftBottom, CDoublePoint2D ptRightTop);
	CDoubleRectangle(double left, double bottom, double right, double top);

	// ���
	long Width();
	// �߶�
	long Height();


	bool SetPoints(CDoublePoint2D ptLeftBottom, CDoublePoint2D ptRightTop);
	bool SetPoints(double left, double bottom, double right, double top);
	// ����������εĽ�����
	CDoubleRectangle GetIntersectRect(CDoubleRectangle rect);
	// ����Ϊ�������
	bool SetRegular();
	// �жϵ��Ƿ����ھ��ο���
	bool IsPointInRect(const CDoublePoint2D& point);

	CDoublePoint2D GetLeftBottomPoint(){return m_ptLeftBottom;}
	CDoublePoint2D GetRightTopPoint(){return m_ptRightTop;}
	
};


//rectinfo���治��һդ��Ჹ��һ��դ��
class CRectInfo:
	public CDoubleRectangle
{
public://���캯��/��������	
	CRectInfo(double nPixelSize = 0,
		      double nMinEasting = 0,
		      double nMinNorthing = 0,
		      double nMaxEasting = 0,	
		      double nMaxNorthing = 0);

	/// 
	CRectInfo(const CRectInfo& rectInfo);

public:

	/// Assignment operator (doesn't copy the bounding polygon and the intersecting rectangle)
	void operator=(const CRectInfo& rectInfo);
	//
	long GetNoOfPixelsX() const;

	
	long GetNoOfPixelsY() const;

	/// 
	double GetPixelSize() const { return m_nPixelSize; }

	/// 
		/// Coordinate for index
	long GetIndexForXCoord(double x) const;

	/// Coordinate for index
	long GetIndexForYCoord(double y) const;

	/// 
	long GetNoOfPixels() const { return GetNoOfPixelsX()*GetNoOfPixelsY(); }

	/// The left border coordinate in meter
	double GetMinEasting() const {return m_ptLeftBottom.x;}

	/// The right border coordinate in meter
	double GetMaxEasting() const {return m_ptRightTop.x;}

	/// The bottom (south) border coordinate in meter
	double GetMinNorthing() const {return m_ptLeftBottom.y;}

	/// The top (north) border coordinate in meter
	double GetMaxNorthing() const {return m_ptRightTop.y;}


	/// 
	void clear();

	/// 
	CDoubleRectangle GetRect() const { return CDoubleRectangle(*this); }

	//��������ϵͳ
	void SetCoordSys(short nCoord) { m_nCoordSys = nCoord; }

	//���þ���ֵ
	void SetPixelSize(double nPixelSize) { m_nPixelSize = nPixelSize; }

	//��������ϵͳ
	short GetCoordSys() { return m_nCoordSys; }

	//���þ���ֵ
	double GetPixelSize() { return m_nPixelSize; }

protected:

	///����
	double m_nPixelSize;
	
	//���ο������ϵ���
	short m_nCoordSys;
};

class CPixelIterator
{
public:
	// �����ľ��ο�
	CPixelIterator(const CRectInfo& rectInfo);

	//rectInfo �� �������α߽�Ľ���
	CPixelIterator(const CRectInfo& rectInfo,
		double left, double bottom, double right, double top);	

    //���޽���
	bool IsIterator(){return m_bIterator;}

	//������һ�е��к�,���û����һ�и���Ϊ-1
	bool nextRow();

	//������һ�е��к�,���û����һ��,�����Ϊ-1
	bool nextColumn();

	///
	inline long GetCurColPixelNumber() const {return m_nCurColPixelNumber;}

	///
	inline long GetCurRowPixelNumber() const {return m_nCurRowPixelNumber;}

	///
	inline double GetCurColCoord() const {return m_nCurColCoord;}

	///
	inline double GetCurRowCoord() const {return m_nCurRowCoord;}


private:

	///
	void initCurrentValues();

	//����
	double m_nPixelSize;

	///��0������(դ�����ĵ�)
	double m_nZeroColCoord;

	///��0������(դ�����ĵ�)
	double m_nZeroRowCoord;

	///��ߵ���������
	long m_nLeftPixelNumber;

	///�ұ���������
	long m_nRightPixelNumber;

	///�±���������
	long m_nBottomPixelNumber;

	///�ϱ���������
	long m_nTopPixelNumber;

	///��ǰ����������
	long m_nCurColPixelNumber;

	///��ǰ����������
	long m_nCurRowPixelNumber;

	///��ǰ������(դ�����ĵ�)
	double m_nCurColCoord;

	///��ǰ������(դ�����ĵ�)
	double m_nCurRowCoord;

	///
	const CRectInfo& m_rectInfo;

	bool m_bIterator;

	};