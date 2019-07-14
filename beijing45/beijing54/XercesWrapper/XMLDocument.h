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
 *  @file         XMLDocument.h
 *  @version      0.1
 *  @author       Marcin Malczewski
 *  @department   Com SDC NA B3
 *  @mail         marcin.malczewski@siemens.com
 *  @date         16.2.2006
 *
 *  @brief        XMLDocument class declaration.
 *
 *************************************************************/

#ifndef INCLUDED_XMLDOCUMENT_H
#define INCLUDED_XMLDOCUMENT_H
//add by jjj 2013.5.16
#include "XMLPlatform.h"
// system includes
#include <string>
#include <sstream>
// project includes
// local includes
#include "XMLNode.h"
#include "XMLDefs.h"



class TiXmlDocument;

namespace XercesWrapperNS {

/** 
	XMLDocument class. 
*/
class XML_API XmlDocument : public XMLNode
{
public:

	/** Constructors */
	XmlDocument(XmlDocument& io_XMLDocument);
	XmlDocument(const char* i_filename = 0,
				const char* i_rootNode = "root", 
				const char* encoding="UTF-8",
				const char* i_namespaceURI = 0);
	
	/** Destructor */
	virtual ~XmlDocument();
	/** 
		Set validation for parser.
		Three modes are possible: parsing without validation, parsing with validation
		and auto validation (document is parsed two times - first time with validation on,
		if some errors occur the second parsing is done without validation)
	*/
	void setValidation(bool i_validation);
	/** Get encoding of XML document */
	std::string getEncoding();
	/** Read xml document from memory (from char* buffor).*/
	void parseMemory(const char* i_memBuffer);
	/** Read xml document from file input file. */
	void readFile(bool i_validation = false);
	void readFile(const std::string& i_filename, bool i_validation = false);
	void readFile(const char* i_filename, bool i_validation = false);
		


	/** Return name of file. */
	const std::string getFilename() const;

	/** 
		Write document to file.
		If no filename is specified, document will be saved with the same input filename.
	*/
	void writeFile();
	void writeFile(const std::string& i_filename); 
	void writeFile(const char* i_filename);
	void writePlainFile(const std::string& i_filename); 
	void writePlainFile(const char* i_filename);

	void setSchemaLocation(const std::string& i_schemaLocation);
		

protected:
	/** Read data from standard input stream (istream) */	
	void readStream(std::istream* i_stream);
	/** Write data to standard output stream (ostream) */
	void writeStream(std::ostream& io_stream);
	
private:
	/** Initialize Xerces and create DOM implementation. */
	void initXerces();
	/** Terminate Xerces */
	void terminateXerces();
	/** Create and initialize DOM builder. */
	void initParser();
	/** Release memory (open documents, DOM builder, etc.). */
	void release();

	std::string m_filename;
	TiXmlDocument* m_document;
	std::string m_schema;
	bool m_validation;
};

}

#endif