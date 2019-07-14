/**
 * <!--
 *  Copyright (C) Siemens AG 2006. All Rights Reserved. Confidential.
 *
 *  Distribution only to people who need to know this information in
 *  order to do their job.(Need-to-know principle).
 *  Distribution to persons outside the company, only if these persons
 *  signed a non-disclosure agreement.
 *  Electronic transmission, e.g. via electronic mail, must be made in
 *  encrypted form.
 *  -->
 *  @file         XMLValue.cpp
 *  @version      0.1
 *  @author       Marcin Malczewski
 *  @department   Com SDC NA B3
 *  @mail         marcin.malczewski_ext@siemens.com
 *  @date         22.2.2006
 *
 *  @brief        XMLValue class definition.
 *
 *************************************************************/

#include "XMLValue.h"
// local includes
#include "XmlStringManager.h"

namespace XercesWrapperNS {

//------------------------------------------------------------
XMLValue::XMLValue()
:  m_valid(true)
{

}
//------------------------------------------------------------
XMLValue::XMLValue(const XMLValue& i_XMLValue)
: m_valid(i_XMLValue.m_valid) 
{ 
	*this = i_XMLValue; 
}
//------------------------------------------------------------
XMLValue::~XMLValue()
{
}
//------------------------------------------------------------
XMLValue& XMLValue::operator=(const XMLValue& i_XMLValue)
{
	m_value = i_XMLValue.m_value;
	m_valid = i_XMLValue.m_valid;
	return *this;
}
//------------------------------------------------------------

void  XMLValue::set(const char* i_value,const char * encoding) 
{	
	if(!i_value)
	{
		m_value = "";
		return;
	}
	m_value = i_value;
	if(encoding&&XmlStringManager::IsSameStringNoCase(encoding,"utf-8"))
	{
			XmlStringManager::UTF8ToGBK(m_value,i_value);
	}
	XMLLOGOUT("set value "<< m_value)

}

void XMLValue::set(const std::string& i_value,const char * encoding)
{ 
	set(i_value.c_str(),encoding); 
	XMLLOGOUT("set value"<< m_value)
}

const char * XMLValue::asString() const{ return m_value.c_str(); }

double XMLValue::asDouble() const
{
	std::size_t found ;
	std::string tempValue = m_value;
	while(std::string::npos!=(found=tempValue.find(',')))
	{
		tempValue.erase(found,1);
	}
	std::istringstream in(tempValue);
	double ret((std::numeric_limits<double>::min)());
	in>>ret;
	return ret;
}

double XMLValue::asFloat() const
{
	std::size_t found ;
	std::string tempValue = m_value;
	while(std::string::npos!=(found=tempValue.find(',')))
	{
		tempValue.erase(found,1);
	}
	std::istringstream in(tempValue);
	float ret((std::numeric_limits<float>::min)());
	in>>ret;
	return ret;
}

unsigned int XMLValue::asUInt() const{ return (unsigned int)asInt(); }

int XMLValue::asInt() const
{ 
	XMLLOGOUT("Start to Int "<<m_value)
		std::size_t found ;
	std::string tempValue = m_value;
	while(std::string::npos!=(found=tempValue.find(',')))
	{
		tempValue.erase(found,1);
	}
	XMLLOGOUT("to Int "<<tempValue)
		return ::atoi(tempValue.c_str());
}

bool XMLValue::asBool() const
{
	if(m_value == "true" || m_value == "yes" || m_value == "1") return true;
	if(m_value == "false" || m_value == "no" || m_value == "0") return false;
	return false;
}


bool XMLValue::isValid() { return m_valid; }

/** Checks that XML value is valid (not null) or not */
bool XMLValue::isNull() const { return !m_valid; }

/** Checks that XML value is empty */
bool XMLValue::isEmpty() const { return m_value.empty(); }
/** Set valid of XML value*/
void XMLValue::valid(bool i_valid) { m_valid = i_valid; }

}
