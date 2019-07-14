#include "ReadClutterINFO.h"


CReadClutterINFO::CReadClutterINFO(void)
{
	mClatterList.clear();
}

CReadClutterINFO::~CReadClutterINFO(void)
{
	mClatterList.clear();
}

bool CReadClutterINFO::ReadFromXml(const char* szCalParam,int streamOrFile)
{
	XmlDocument Xml;
	try
	{
		if(streamOrFile==0)
			Xml.parseMemory(szCalParam);
		else if(streamOrFile==1)
			Xml.readFile(szCalParam);
		else
			return false;// NG_PARAMWRONG;
	}
	catch (...)
	{
		return false;//INVALID_XMLFILE;
	}
	//////////////////////////////////////////////////////////////////////////

	if(Xml.hasChild("ClutterINFOList"))
	{
		Xml.gotoChild("ClutterINFOList");
		if(Xml.hasChild())
		{
			Xml.gotoFirstChild();
			while(true)
			{
				if(Xml.getLabel()=="INFO")
				{
					int info = Xml.getAttribute("value").asInt();
					mClatterList.push_back(info);
				}
				if(Xml.isLastSibling())
					break;
				Xml.gotoNextSibling();
			}
			Xml.gotoFather();
		}
	}

	return true;
}
