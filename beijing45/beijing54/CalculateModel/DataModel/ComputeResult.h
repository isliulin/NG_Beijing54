#ifndef __DATAMODEL_COMPUTERESULT_h
#define __DATAMODEL_COMPUTERESULT_h
//�����һЩ�ṹ��
//�ߵĸ��Ƿ������
class CLineComputeResult
{
public:
	int m_nSize;  //�����С
	int m_nPointsNo; //����е�ĸ���

	//�㼯
	int m_nCoordSys;  //��ʹ�õ�����ϵ���
	CDoublePoint* m_pPointList;  //�㼯
	float* m_pValueList; //ֵ�б�
};

#endif