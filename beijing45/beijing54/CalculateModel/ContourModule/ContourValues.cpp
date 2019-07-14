// ContourValues.cpp: implementation of the CContourValues class.
//
//////////////////////////////////////////////////////////////////////

#include "ContourValues.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CContourValues::CContourValues()
{
	//m_Values.RemoveAll();
	m_Values.clear();
}

CContourValues::~CContourValues()
{
}

CContourValues& CContourValues::operator=(const CContourValues& rhs)
{
//	m_Values.RemoveAll();
	m_Values.clear();

	/*POSITION pos = rhs.m_Values.GetHeadPosition();

	while(pos!=NULL)
	{
		m_Values.AddTail(rhs.m_Values.GetNext(pos));
	}*/
	list<float>::iterator iter;
	CValueList val = rhs.m_Values;
	for (iter=val.begin();iter!=val.end();iter++)
	{
		m_Values.push_back(*iter);
	}

	return *this;
	
}

void CContourValues::AddValue(float newValue)
{//按从小到大插入，插入后保证有序
	m_Values.push_back(newValue);
	m_Values.sort();

	/*if( m_Values.empty() )
	{
		m_Values.push_back(newValue);
	}
	else
	{
		list<float>::iterator iter;
		for (iter =m_Values.begin();iter!=m_Values.end();iter++)
		{	
			if (*iter>newValue)
			{
				m_Values.insert(iter,newValue);
			}
			iter++;
			
		}
	}*/
/*
	else
	{
		float val; 
		//POSITION pos = m_Values.GetHeadPosition();
		int pos = 0;
		val = m_Values[pos];
		if( newValue < val )
		{
			//m_Values.AddHead(newValue);
			m_Values.push_front(newValue);
		//	TraceOutValueList();
			return;
		} 

		pos = m_Values.size();
		val = m_Values[pos-1];
		if( newValue > val)
		{
		//	m_Values.AddTail(newValue);
			m_Values.push_back(newValue);
			//TraceOutValueList();
			return;
		}

	//	POSITION nextPos = m_Values.GetHeadPosition();
		int nextPos= 0;
		pos = nextPos;
		float valNext;
		while( nextPos!=m_Values.size() )
		{
			val = m_Values[nextPos+1];
			//val = m_Values.GetNext(nextPos);
			if( val == newValue )
			{
				//TraceOutValueList();
				return;
			}

		//	ASSERT(nextPos!=NULL);
			valNext = m_Values[nextPos];
			if( newValue == valNext )
			{
				//TraceOutValueList();
				return;
			}

			if( val< newValue && newValue < valNext )
			{
				//m_Values.InsertAfter(pos,newValue);
				list<float>::iterator iter;
				int position = 0;
				for (iter=m_Values.begin();iter!=m_Values.end();iter++)
				{
					if (position == pos)
					{
						iter++;
						m_Values.insert(iter,newValue);
						break;
					}
				}
					//TraceOutValueList();
				return;
			}

			pos = nextPos; //watch out here!

			
		}
		
	
	}
*/

	
}

#ifdef _DEBUG
void CContourValues::TraceOutValueList()
{
	
/*
	POSITION pos = m_Values.GetHeadPosition();
	float val;
	while(pos!=NULL)
	{
		val = m_Values.GetNext(pos);
		TRACE1("%f\n",val);
		
	}
*/

}
#endif

void CContourValues::DeleteValue(float oldValue)
{
/*
	POSITION pos = m_Values.GetHeadPosition();
	float val;
	while(pos!=NULL)
	{
		val = m_Values.GetAt(pos);
		if( val == oldValue )
		{
			//m_Values.RemoveAt(pos);
			m_Values.remove(val);
		
		}
		m_Values.GetNext(pos);
		
	}
*/
	list<float>::iterator iter;
	for (iter=m_Values.begin();iter!=m_Values.end();)
	{
		if (*iter==oldValue)
		{
			m_Values.erase(iter);
		}
		else
		{
			iter++;
		}
	}



}

void CContourValues::ReplaceValue(float oldValue, float newValue)
{
	/*POSITION pos = m_Values.GetHeadPosition();
	float val;
	while(pos!=NULL)
	{
		val = m_Values.GetAt(pos);
		if( val == oldValue )
		{
			//m_Values.RemoveAt(pos);
			m_Values.remove(val);
			AddValue(newValue);
		}
		m_Values.GetNext(pos);
		
	}*/
	list<float>::iterator iter;
	iter = find(m_Values.begin(),m_Values.end(),oldValue);
	*iter = newValue;

}

void CContourValues::GenerateValues(int numContours, float rangeStart, float rangeEnd)
{
	float incr;
	
	if (numContours == 1)
    {
		incr = 0;
    }
	else
    {
		incr = (rangeEnd - rangeStart) / (numContours-1);
    }

	float val = rangeStart;
	for (int i=0; i < numContours; i++)
    {
		AddValue(val);
		val+=incr;
    }

}

float CContourValues::GetValue(int i)
{
//	ASSERT( i>=0 && i<GetNumberOfValues() );
	list<float>::iterator iter;
	int pos =0;
	for (iter = m_Values.begin();iter!=m_Values.end();iter++)
	{
		if (pos == i)
		{
			float val = *iter;
			return val;
		}
		pos++;
	}
	return 0;

	//return m_Values.GetAt(m_Values.FindIndex(i));
}

void CContourValues::SetValue(int i, float newValue)
{
	int numCoutr = GetNumberOfValues();
//	ASSERT( i>=0 && i<numCoutr-1 );

	float val = GetValue(i);
	ReplaceValue(val,newValue);
	
}






















