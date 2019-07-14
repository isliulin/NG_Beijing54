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
 *  @file         XMLValue.h
 *  @version      0.1
 *  @author       Marcin Malczewski
 *  @department   Com SDC NA B3
 *  @mail         marcin.malczewski_ext@siemens.com
 *  @date         16.3.2006
 *
 *  @brief        XMLValue class declaration.
 *
 *************************************************************/

#ifndef INCLUDED_XMLVALUE_H
#define INCLUDED_XMLVALUE_H
//add by jjj 2013.5.16
#include "XMLPlatform.h"
// system includes
#include <stdlib.h>     //add by jjj Linux for
#include <string>
#include <limits>
#include <sstream>
// local includes
#include "XMLDefs.h"

namespace XercesWrapperNS {

class XMLCallTrace;
/**
	XMLValue class.
*/
class XML_API XMLValue
{
public:
	/** Default constructor */
	XMLValue();
	/** Copy constructor */
	XMLValue(const XMLValue& i_XMLValue);
	/** Destructor */
	~XMLValue();
	/** Operator of assignment */
	XMLValue& operator=(const XMLValue& i_XMLValue);

	/** Returns value of XML node as string value */
	//edit by jjj
	const char * asString() const ;

	/** Returns value of XML node as double number */
	double asDouble() const;

	double asFloat() const;
	
	/** Returns value of XML node as integer number */
	int asInt() const;
	unsigned int asUInt() const;
	/** Returns value of XML node as bool value */
	bool asBool() const;

	/** Checks that given value of XML node is not empty */
	bool isValid() ;

	/** Set given XML value */
	void set(const char* i_value,const char * encoding=0) ;
	void set(const std::string& i_value,const char * encoding=0);

	/** Checks that XML value is valid (not null) or not */
	bool isNull() const;

	/** Checks that XML value is empty */
	bool isEmpty() const;
	/** Set valid of XML value*/
	void valid(bool i_valid);

protected:
	std::string m_value;
private:
	bool m_valid;
};

}

#endif
