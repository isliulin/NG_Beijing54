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
 *  @file         XMLNode.h
 *  @version      0.1
 *  @author       Marcin Malczewski
 *  @department   Com SDC NA B3
 *  @mail         marcin.malczewski_ext@siemens.com
 *  @date         22.2.2006
 *
 *  @brief        XMLNode class declaration.
 *
 *************************************************************/

#ifndef INCLUDED_XMLNODE_H
#define INCLUDED_XMLNODE_H
//add by jjj 2013.5.16
#include "XMLPlatform.h"
// system includes
#include <string>
// project includes

// local includes
#include "XMLValue.h"
//#include "XMLCallTrace.h"
#include "XMLDefs.h"



class TiXmlElement;
typedef TiXmlElement DOMNode;


namespace XercesWrapperNS {
/**
	XMLNode class.
*/
class XML_API XMLNode
{
public:
	/** Constructor. */
	XMLNode();
	XMLNode(DOMNode* i_node);
	XMLNode(const XMLNode& i_XMLNode);

	/** Destructor. */
	virtual ~XMLNode() {}

	/** operator =. */
	XMLNode& operator=( XMLNode & i_XMLNode );


	// get methods
	/** Get name (label) of the XML element. */
	std::string getLabel();

	/** Return number of children for XML element. */
	int numberOfChildren() const;
	int numberOfChildren(const std::string& i_name) const;
	int numberOfChildren(const char* i_name) const;

	/** Return true if XML element has childs, otherwise return false. */
	bool hasChild() const;
	bool hasChild(const std::string& i_name) const; 
	bool hasChild(const char* i_name) const;

	/** Return child of XML element. */
	XMLNode getChild(const std::string& i_name, const int i_number);
	XMLNode getChild(const char* i_name, const int i_number); 
	XMLNode getChild(const std::string& i_name); 
	XMLNode getChild(const char* i_name);
	XMLNode getChild(const int i_number); 
	XMLNode getChild();

	XMLNode getNextSibling();
	XMLNode getPreviousSibling();

	/** Return number of attributes of XML element. */
	int numberOfAttributes() const;

	/** Return true if XML element has attributes, otherwise return false. */
	bool hasAttributes() const;
	bool hasAttribute(const std::string& i_name) const;
	bool hasAttribute(const char* i_name) const ;

	/** Return attribute of XML element. */
	const XMLValue& getAttribute(const int i_number);
	const XMLValue& getAttribute(const std::string& i_name);
	const XMLValue& getAttribute(const char* i_name) ;

	/** Return name of attribute with given number. */
	std::string getAttributeName(const int i_number);

	/** Return true if XML element has father, otherwise return false. */
	bool hasParent() const; 
	bool hasFather() const;


	/** Return father of XML element. */
	XMLNode getParent() const;
	XMLNode getFather() const;

	/** Return value (text) of XML element. */
	const XMLValue& getValue();

	/** Return number of siblings of XML element. */
	int numberOfSiblings() const;
	int numberOfSiblings(const std::string& i_name) const;
	int numberOfSiblings(const char* i_name) const;

	// goto functions
	/** Go to first sibling of XML element. */
	bool gotoFirstSibling();

	/** Go to sibling of XML element. */
	bool gotoSibling(const int i_number);
	bool gotoSibling(const std::string& i_name, const int i_number);
	bool gotoSibling(const char* i_name,const int i_number);

	/** Go to father of XML element. */
	bool gotoParent();
	bool gotoFather();

	/** Go to first child of XML element. */
	bool gotoFirstChild();
	bool gotoFirstChild(const std::string& i_name);
	bool gotoFirstChild(const char* i_name);

	/** Go to next sibling of XML element. */
	bool gotoNextSibling();
	bool gotoNextSibling(const std::string& i_name);
	bool gotoNextSibling(const char* i_name);

	/** Go to child of XML element. */
	bool gotoChild(const std::string& i_name, const int i_number = 0);
	bool gotoChild(const char* i_name, const int i_number = 0);
	bool gotoChild(const int i_number = 0);

	/** Go to main element (document element) */
	bool gotoDocumentElement();

	/** Return true if XML element is last sibling. */
	bool isLastSibling() const ;
	bool isLastSibling(const std::string& i_name) const;
	bool isLastSibling(const char* i_name) const;

	// set methods
	/** Set attribute of XML element. */
	bool setAttribute(const std::string& i_name, const std::string& i_value);
	bool setAttribute(const char* i_name, const char* i_value);
	bool setAttribute(const std::string& i_name, const bool i_value);
	bool setAttribute(const char* i_name, const bool i_value) ;
	bool setAttribute(const std::string& i_name, const int i_value);
	bool setAttribute(const char* i_name, const int i_value);
	bool setAttribute(const std::string& i_name, const float i_value, const int i_prec = 7);
	bool setAttribute(const char* i_name, const float i_value, const int i_prec = 7) ;
	bool setAttribute(const std::string& i_name, const double i_value, const int i_prec = 7);
	bool setAttribute(const char* i_name, const double i_value, const int i_prec = 7) ;

	/** Set value (text) of XML element. */
	void setValue(const std::string& i_value);
	void setValue(const char* i_value);
	void setValue(bool i_value);
	void setValue(int i_value);
	void setValue(float i_value, int i_prec = 7);

	/** Add child to XML element. */
	void addChild(XMLNode& i_node, bool deep = true);
	//void addChild(const std::string& i_name);
	bool addChild(const std::string& i_name);
	void addChild(const char* i_name) ;

	/** Append child */
	bool appendChild(const XMLNode& i_newChild);

	/** Remove node from XML element. */
	bool removeNode();

	/** Replace one XML node with other. */
	bool replaceNode(const std::string& i_name);
	bool replaceNode(const char* i_name);

	XMLNode cloneNode(bool deep = true);
	DOMNode* getDOMNode();

	/** Checks that node is empty */
	bool isNull() const;

	const char * GetEncodingString() const;

protected:

	DOMNode* m_node;

private:
	XMLValue m_value;

};
}

#endif
