#include "PolygonFunction.h"

CPolygonFunction::CPolygonFunction(CGeoPolygon *pRect)
{
 mpPolygon=pRect;
 
}
CPolygonFunction:: ~CPolygonFunction()
{

}
bool CPolygonFunction::GetMaxRect(double &minx,double &miny,double &maxx,double &maxy)
{
 if(mpPolygon==NULL)
 {
   return false;
 }

 minx=maxx=mpPolygon->m_pPointData[0].x;
 miny=maxy=mpPolygon->m_pPointData[0].y;

 for(int i=1;i<mpPolygon->m_nPointsNum;i++)
 {
    minx=minx<mpPolygon->m_pPointData[i].x?minx:mpPolygon->m_pPointData[i].x;
	miny=miny<mpPolygon->m_pPointData[i].y?miny:mpPolygon->m_pPointData[i].y;
    maxx=maxx>mpPolygon->m_pPointData[i].x?maxx:mpPolygon->m_pPointData[i].x;
	maxy=maxy>mpPolygon->m_pPointData[i].y?maxy:mpPolygon->m_pPointData[i].y;
 }

 return true;
 
}

//�ж�һ�����Ƿ��ڶ�����ڲ�
bool CPolygonFunction::PtInPolygon (CDoublePoint p)
{

    if(mpPolygon==NULL)
    {
      return false;
    }
	int nCross = 0;    
	for (int i = 0; i < mpPolygon->m_nPointsNum; i++) 
	{
		CDoublePoint p1 = mpPolygon->m_pPointData[i];  
		CDoublePoint p2 =  mpPolygon->m_pPointData[(i + 1) % mpPolygon->m_nPointsNum];

		// ��� y=p.y �� p1p2 �Ľ���  

		if ( p1.y == p2.y ) 	 // p1p2 �� y=p0.yƽ��
			continue;

		if ( p.y <	((p1.y<p2.y)?p1.y:p2.y))	// ������p1p2�ӳ�����
			continue;
		if ( p.y >= ((p1.y>p2.y)?p1.y:p2.y))	// ������p1p2�ӳ�����
			continue;

		// �󽻵�� X ���� --------------------------------------------------------------
		double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;

		if ( x > p.x ) 
			nCross++;		// ֻͳ�Ƶ��߽���
	}

	// ���߽���Ϊż�������ڶ����֮�� ---
	return (nCross % 2 == 1);
}



