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
 *  @file         XMLDataException.h
 *  @version      0.1
 *  @author       Marcin Malczewski
 *  @department   Com SDC NA B3
 *  @mail         marcin.malczewski_ext@siemens.com
 *  @date         16.2.2006
 *
 *  @brief        XMLDataException class declaration.
 *
 *************************************************************/

#ifndef INCLUDED_XMLDATAEXCEPTION_H
#define INCLUDED_XMLDATAEXCEPTION_H
//add by jjj 2013.5.16
#include "XMLPlatform.h"
// system includes
#include <string>

/** 
	XMLDataException class. 
*/
class XML_API XMLDataException
{
public:
	enum EErrorCodes
	{
		XML_XERCES_INIT, //"Error during Xerces-c initialization"
		XML_DOC_INIT, //"Error during initializing XML document"
		XML_EMPTY_FILE, //"XML file path is empty"
		XML_FIND_FILE, //"Unable to find XML file: <filename>"
		XML_WRITE_FILE, //"Unable to serialize XML document"
		XML_PARSING, //"Unexpected error during parsing XML file"
		XML_VALIDATION,
		XML_NULL_DOC //"XML null pointer document"
	};
	
	XMLDataException(const int i_errorCode, const std::string i_errorMessage, 
					 const std::string i_module, const std::string& i_errorDesc = "")
		: m_errorCode(i_errorCode),m_errorMessage(i_errorMessage),m_module(i_module)
	{ 
		if(i_errorDesc == "")
			m_errorDesc = m_errorMessage;
		else 
			m_errorDesc = i_errorDesc;
	}
	~XMLDataException() {}
	int getErrorCode() const { return m_errorCode; }
	std::string getErrorMessage() const { return m_errorMessage; }
	std::string getErrorDescription() const { return m_errorDesc; }
	std::string getModule() const { return m_module; }
	

private:
	int m_errorCode;
	std::string m_errorMessage;
	std::string m_errorDesc;
	std::string m_module;
};

#endif