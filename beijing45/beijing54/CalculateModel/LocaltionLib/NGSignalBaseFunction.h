
#ifndef NG_SIGNAL_BASE_FUNCTION_H
#define NG_SIGNAL_BASE_FUNCTION_H

#include "NGTDOADataStruct.h"



class CNGSignalBaseFunction
{

private:
	CNGSignalBaseFunction(void){};
	~CNGSignalBaseFunction(void){};

public:



	//���ݽ���;�������˫�����ϵĵ�
	static bool GetHypersPoints(const NGPostion& p1 , const NGPostion& p2 ,double distancedif , double dmax, vector<NGPostion>& hypoints);

	//����˫���ߵĽ���

	static bool CalHyperIntersection(const vector<NGPostion>& hypoint1 , const vector<NGPostion>& hypoint2 , vector<NGPostion>& interpoints);

private:
	//��������ľ���
	static inline double Distance(const NGPostion& p1 , const NGPostion& p2);

	//�����������ߺ�X��ļн�
	static double GetPointABToX(const NGPostion& p1 , const NGPostion& p2);


	//��������pos��ԭ����תĳ���ǶȺ�����꣬�Ա�����pos��
	static void CalPointRotate(NGPostion& pos , double d_turnAngle);

	//�ж������߶��Ƿ��ཻ�����ཻ������㽻��
	static bool CalSegmentIntersect(const NGSegment& s1 , const NGSegment& s2 , NGPostion& point);
};

#endif
