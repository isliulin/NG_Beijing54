#pragma once
//#include "CalculateParam.h"
#include <vector>
#include "../../XercesWrapper/XercesWrapper.h"

using namespace std;
using namespace XercesWrapperNS;

class CReadClutterINFO {
public:
	CReadClutterINFO(void);
	virtual ~CReadClutterINFO(void);
public:
	bool ReadFromXml(const char* szCalParam,int streamOrFile);
	int GetClatterINFOCount(){return mClatterList.size();}
	int GetAt(int index){return mClatterList[index];}
public:
	std::vector<int> mClatterList;

};
