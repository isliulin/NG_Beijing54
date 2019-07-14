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
 *  @file         XMLDocument.cpp
 *  @version      0.1
 *  @author       Marcin Malczewski
 *  @department   Com SDC NA B3
 *  @mail         marcin.malczewski_ext@siemens.com
 *  @date         16.2.2006
 *
 *  @brief        XMLDocument class definition.
 *
 *************************************************************/

#include "XMLDocument.h"
#include "XMLDataException.h"
#include "stdio.h"
#include "tinyxml.h"


namespace XercesWrapperNS {


//------------------------------------------------------------
XmlDocument::XmlDocument(XmlDocument& io_XMLDocument)
	: XMLNode(0),m_validation(false)
{

	m_document = new TiXmlDocument(*(io_XMLDocument.m_document));
	m_filename = io_XMLDocument.m_filename;
	m_schema = io_XMLDocument.m_schema;
	m_validation = io_XMLDocument.m_validation;
}

//------------------------------------------------------------
XmlDocument::XmlDocument(const char* i_filename, const char* i_rootNode,const char* encoding, const char* i_namespaceURI)
	: XMLNode(0),m_validation(false)
{
	m_document = new TiXmlDocument();
	if(i_filename)
	{
		m_filename = std::string(i_filename);
	}
	try
	{
		XMLLOGOUT("Start Xml Encoding:"<<(encoding?encoding:""));
		if(encoding)
		{
			char des[100] = "";
			sprintf(des,"<?xml version='1.0' encoding='%s'?>",encoding);
			TiXmlDeclaration dec;
			dec.Parse(des , 0, TIXML_ENCODING_UNKNOWN );
			m_document->InsertEndChild(dec);
		}
		XMLLOGOUT("End Xml Encoding");
		//////////////////////////////////////////////////////////////////////
		XMLLOGOUT("Start Xml Root"<<(i_rootNode?i_rootNode:""))
		if(i_rootNode)
		{
			TiXmlElement root(i_rootNode);
			m_node = m_document->InsertEndChild(root)->ToElement();
		}
		else
		{	
			TiXmlElement root("root");
			m_node = m_document->InsertEndChild(root)->ToElement();
		}
		XMLLOGOUT("End Xml Root")
		if(i_namespaceURI)
		{
			setAttribute("xmlns",i_namespaceURI);
		}

	}
	catch(...)
	{

	}
	XMLLOGOUT("Create OK");

}
//------------------------------------------------------------
XmlDocument::~XmlDocument()
{
	release();
	delete m_document;
}
//------------------------------------------------------------
void XmlDocument::initXerces()
{

}
//------------------------------------------------------------
void XmlDocument::terminateXerces()
{
	
}
//------------------------------------------------------------
void XmlDocument::initParser()
{
	

}
//------------------------------------------------------------
void XmlDocument::release()
{
	XMLLOGOUT("Start Release")
	m_document->Clear();
	m_document->ClearError();
	m_node = 0;

	XMLLOGOUT("END Release")
}

//------------------------------------------------------------
void XmlDocument::setValidation(bool i_validation)
{
	m_validation = i_validation;
}
//------------------------------------------------------------
std::string XmlDocument::getEncoding()
{
	TiXmlNode * node = m_document->FirstChild();
	if(node)
	{
		TiXmlDeclaration *dec = node->ToDeclaration();
		if(dec)
		{
			return dec->Encoding();
		}
	}

	return "";
}
//------------------------------------------------------------
void XmlDocument::parseMemory(const char* i_memBuff)
{
	release();
	m_document->Parse(i_memBuff);
	m_node = m_document->RootElement();
}
//------------------------------------------------------------
void XmlDocument::readFile(bool i_validation)
{
	if(m_filename.empty())
		throw XMLDataException(XMLDataException::XML_EMPTY_FILE,"XML file path is empty","XMLDocument::readFile()");
		//return;
	readFile(m_filename,i_validation);
}
//------------------------------------------------------------

void XmlDocument::readFile(const char* i_filename, bool i_validation) 
{
	XMLLOGOUT("Start XML first:"<<i_filename)
		release();
	XMLLOGOUT("Start XML:"<<i_filename)
		if(!i_filename||(i_filename[0]=='\0'))
		{
			XMLLOGOUT(" XML filename is empty")
				throw XMLDataException(XMLDataException::XML_EMPTY_FILE,"XML file path is empty","XMLDocument::readFile()");
		}

		m_filename = i_filename;
		m_validation = i_validation;

		XMLLOGOUT("Start Load XML:"<<m_filename)
			if(!m_document->LoadFile(m_filename))
			{
				XMLLOGOUT(m_filename<<m_document->ErrorDesc())
					throw XMLDataException(XMLDataException::XML_FIND_FILE,"Unable to find XML file","XMLDocument::readFile()");
			}
			m_node = m_document->RootElement();
			XMLLOGOUT("End Load XML:"<<m_filename)
	 
}

void XmlDocument::readFile(const std::string& i_filename, bool i_validation)
{
	readFile(i_filename.c_str(),i_validation);
}

const std::string XmlDocument::getFilename() const { return m_filename; }
//------------------------------------------------------------
void XmlDocument::readStream(std::istream* i_istream)
{

	release();
	if(i_istream)
	{
		(*i_istream)>>(*m_document);
	}
	m_node = m_document->RootElement();
}
//------------------------------------------------------------
void XmlDocument::writeFile()
{
	if(m_filename.empty())
		throw XMLDataException(XMLDataException::XML_EMPTY_FILE,"XML file path is empty","XMLDocument::writeFile()");
		//return;
	writeFile(m_filename);
}
//------------------------------------------------------------
void XmlDocument::writeFile(const std::string& i_filename)
{
	writeFile(i_filename.c_str()); 
}
//------------------------------------------------------------
void XmlDocument::writePlainFile(const std::string& i_filename)
{
	writeFile(i_filename.c_str());
}
//------------------------------------------------------------
void XmlDocument::writeStream(std::ostream& io_stream)
{
	if(m_node)
		io_stream<<(*m_document);
}

void  XmlDocument::writeFile(const char* i_filename) {
	
	if(!i_filename||(i_filename[0]=='\0'))
		throw XMLDataException(XMLDataException::XML_EMPTY_FILE,"XML file path is empty","XMLDocument::writeFile()");

	m_document->SaveFile(i_filename);
}
void  XmlDocument::writePlainFile(const char* i_filename) { writePlainFile(std::string(i_filename)); }

void  XmlDocument::setSchemaLocation(const std::string& i_schemaLocation) { m_schema = i_schemaLocation; }

}
