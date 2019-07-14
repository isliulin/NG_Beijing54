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
 *  @file         XMLNode.cpp
 *  @version      0.1
 *  @author       Marcin Malczewski
 *  @department   Com SDC NA B3
 *  @mail         marcin.malczewski_ext@siemens.com
 *  @date         22.2.2006
 *
 *  @brief        XMLNode class definition.
 *
 *************************************************************/

#include "XMLNode.h"
// system includes
#include <iomanip>

#include "tinyxml.h"

#include "XmlStringManager.h"

namespace XercesWrapperNS {

//------------------------------------------------------------	
XMLNode::XMLNode() : m_node(0)
{
}
//------------------------------------------------------------
XMLNode::XMLNode(DOMNode* i_node) 
: m_node(i_node) 
{
}
//------------------------------------------------------------	
XMLNode::XMLNode(const XMLNode& i_XMLNode) : m_node(0)
{
	m_node = i_XMLNode.m_node;
	m_value = i_XMLNode.m_value;

}
//------------------------------------------------------------	
XMLNode& XMLNode::operator=( XMLNode & i_XMLNode )
{
	m_node = i_XMLNode.m_node;
	m_value = i_XMLNode.m_value;
	return (*this);
}

//------------------------------------------------------------
std::string XMLNode::getLabel()
{
	if(m_node) 
		return std::string(m_node->Value());

	return std::string("");
}
//------------------------------------------------------------
int XMLNode::numberOfChildren() const 
{
	return numberOfChildren("");
}
//------------------------------------------------------------
int XMLNode::numberOfChildren(const std::string& i_name) const 
{
	return numberOfChildren(i_name.c_str());
}

int XMLNode::numberOfChildren(const char * i_name) const 
{
	XMLLOGOUT("Find Element :"<<i_name);
	if(!m_node) return 0;
	int elements = 0;
	DOMNode * childnode = 0;
	if(i_name&& i_name[0]!='\0')
	{
		for(childnode = m_node->FirstChildElement(i_name);
			childnode;
			childnode = childnode->NextSiblingElement(i_name))
		{
			elements++;
		}
	}
	else
	{
		for(childnode = m_node->FirstChildElement();
			childnode;
			childnode = childnode->NextSiblingElement())
		{
			elements++;
		}
	}
	XMLLOGOUT("Find Element :"<<i_name<<" count ="<<elements);
	return elements;
}

bool XMLNode::hasChild() const
{ 
	return numberOfChildren() > 0; 
}
bool XMLNode::hasChild(const std::string& i_name) const 
{
	return numberOfChildren(i_name) > 0; 
}
bool XMLNode::hasChild(const char* i_name) const 
{ 
	return numberOfChildren(i_name) > 0;
}
//------------------------------------------------------------
XMLNode XMLNode::getChild(const std::string& i_name, const int i_number)
{

	return getChild(i_name.c_str(),i_number); 
}


XMLNode  XMLNode::getChild(const char* i_name, const int i_number) 
{ 

	if(!m_node) return XMLNode();;
	int elements = 0;
	DOMNode * childnode = 0;
	if(i_name && (i_name[0]!='\0'))
	{
		for(childnode = m_node->FirstChildElement(i_name);
			childnode;
			childnode = childnode->NextSiblingElement(i_name))
		{
			if(i_number==elements)
				return XMLNode(childnode);
			elements++;
		}
	}
	else
	{
		for(childnode = m_node->FirstChildElement();
			childnode;
			childnode = childnode->NextSiblingElement())
		{
			if(i_number==elements)
				return XMLNode(childnode);
			elements++;
		}
	}

	return XMLNode(); // return null (not valid) document
	//if(!found)
	//throw XMLDataException(0,"Node has no child nodes","XMLNode::getChild()");
}
XMLNode  XMLNode::getChild(const std::string& i_name) { return getChild(i_name,0); }
XMLNode  XMLNode::getChild(const char* i_name) { return getChild(i_name,0); }
XMLNode  XMLNode::getChild(const int i_number) { return getChild("",i_number); }
XMLNode  XMLNode::getChild() { return getChild("",0); }

//------------------------------------------------------------
XMLNode XMLNode::getNextSibling()
{
	if(!m_node) return XMLNode();
	DOMNode * nextnode = m_node->NextSiblingElement();
	return XMLNode(nextnode);
}
//------------------------------------------------------------
XMLNode XMLNode::getPreviousSibling()
{

	if(!m_node) return XMLNode();
	TiXmlNode * nextnode = 0;
	for(nextnode = m_node->PreviousSibling();
		nextnode;
		nextnode = nextnode->PreviousSibling())
	{
		if(nextnode->ToElement())
			return XMLNode(nextnode->ToElement());
	}
	return XMLNode();


}
//------------------------------------------------------------
int XMLNode::numberOfAttributes() const
{
	if(!m_node) return 0;
	int attributes = 0;
	TiXmlAttribute * att = 0;
	for(att = m_node->FirstAttribute();
		att;
		att = att->Next())
	{
		attributes ++;
	}
	return attributes;
	
}
//------------------------------------------------------------
bool XMLNode::hasAttribute(const std::string& i_name) const
{
	return hasAttribute(i_name.c_str());
}

bool XMLNode::hasAttributes() const { return numberOfAttributes() > 0; }

bool XMLNode::hasAttribute(const char* i_name) const { 
	if(!m_node || !i_name) return 0;
	return m_node->Attribute(i_name)!=0; 
}


//------------------------------------------------------------
const XMLValue& XMLNode::getAttribute(const int i_number)
{
	m_value.set("");
	m_value.valid(false);
	if(!m_node) return m_value;
	int attributes = 0;
	TiXmlAttribute * att = 0;
	const char* temp = 0;
	for(att = m_node->FirstAttribute();
		att;
		att = att->Next())
	{
		if(attributes == i_number)
		{
			temp = att->Value();
			break;
		}
		attributes ++;
	}
	
	const char * encoding = GetEncodingString();
	m_value.set(temp,encoding);
	return m_value;

}

const XMLValue& XMLNode::getAttribute(const char* i_name)
{

	XMLLOGOUT("Start Get att "<<i_name)
		m_value.set("");
	m_value.valid(false);
	if(!m_node || !i_name) 
		return m_value;
	const char * temp = m_node->Attribute(i_name);
	XMLLOGOUT("End Get att "<<i_name)
		const char * encoding = GetEncodingString();
	XMLLOGOUT("End Get encoding "<<encoding)
		m_value.set(temp,encoding);
	XMLLOGOUT("Set value "<<i_name<<" as "<<m_value.asString())
		return m_value;
	
}
//------------------------------------------------------------
const XMLValue& XMLNode::getAttribute(const std::string& i_name)
{
	return getAttribute(i_name.c_str());
}
//------------------------------------------------------------
std::string XMLNode::getAttributeName(const int i_number)
{
	if(!m_node) return "";
	int attributes = 0;
	TiXmlAttribute * att = 0;
	const char* temp = 0;
	for(att = m_node->FirstAttribute();
		att;
		att = att->Next())
	{
		if(attributes == i_number)
		{
			temp = att->Name();
			return std::string(temp);
		}
		attributes ++;
	}
	return "";
	
}
//------------------------------------------------------------
bool  XMLNode::hasParent() const
{
	return hasFather();
}
bool XMLNode::hasFather() const
{
	if(!m_node)return false;
	return m_node->Parent()!=0;
}
//------------------------------------------------------------
XMLNode XMLNode::getParent() const 
{
	return getFather();
}
XMLNode XMLNode::getFather() const
{
	if(!m_node)return XMLNode();
	DOMNode *parent =  m_node->Parent()->ToElement();
	return XMLNode(parent);
}
//------------------------------------------------------------
const XMLValue& XMLNode::getValue()
{
	m_value.set("");
	m_value.valid(false);
	if(!m_node)return m_value;
	const char * temp = m_node->GetText();
	const char * encoding = GetEncodingString();
	m_value.set(temp,encoding);
	return m_value;
}
// from XMLDocument
//------------------------------------------------------------
int XMLNode::numberOfSiblings() const
{
	return getFather().numberOfChildren();
}
//------------------------------------------------------------
int XMLNode::numberOfSiblings(const std::string& i_name) const
{
	return numberOfSiblings(i_name.c_str()); 
}
int XMLNode::numberOfSiblings(const char* i_name) const 
{ 
	XMLNode father = getFather();
	return father.numberOfChildren(i_name);
}
//------------------------------------------------------------
bool XMLNode::gotoFirstSibling()
{

	if(!m_node)
		return false;
	TiXmlNode * parent = m_node->Parent();
	if(parent)
	{
		DOMNode* node =  parent->FirstChildElement();
		if(node)
		{
			m_node = node;
			return true;
		}
		
	}

	return false;

}
//------------------------------------------------------------
bool XMLNode::gotoSibling(const std::string& i_name, const int i_number)
{
	return gotoSibling(i_name.c_str(),i_number);

}

bool XMLNode::gotoSibling(const int i_number) { return gotoSibling("",i_number); }

bool XMLNode::gotoSibling(const char* i_name,const int i_number)
{ 
	
	if(!m_node)
		return false;
	XMLNode tempnode = getFather().getChild(i_name,i_number);
	if(tempnode.m_node)
	{
		m_node = tempnode.m_node;
		return true;
	}

	return false;
}

//------------------------------------------------------------
bool XMLNode::gotoParent() { return gotoFather(); }
bool XMLNode::gotoFather()
{
	if(!m_node)
		return false;
	XMLLOGOUT("start goto xml father")
	TiXmlNode * parent = m_node->Parent();
	if(parent)
	{
		m_node = parent->ToElement();
		XMLLOGOUT("end goto xml father OK")
		return true;
	}
	XMLLOGOUT("end goto xml father false")
	return false;
}
//------------------------------------------------------------
bool XMLNode::gotoFirstChild()
{
	XMLLOGOUT("Start Goto first Element")
	if(!m_node)
		return false;

	DOMNode* node = m_node->FirstChildElement();
	if(node)
	{
		m_node = node;
		XMLLOGOUT("End Goto first Element OK")
		return true;
	}
	XMLLOGOUT("End Goto first Element")
	return false;

}
//------------------------------------------------------------
bool XMLNode::gotoFirstChild(const char* i_name) {
	
	XMLLOGOUT("Start Goto Element :"<<i_name)
		if(!m_node)
			return false;
	DOMNode* node = 0;
	if(i_name &&(i_name[0] != '\0'))
		node = m_node->FirstChildElement(i_name);
	else
		node = m_node->FirstChildElement();
	if(node)
	{
		m_node = node;
		XMLLOGOUT("Go to Element :"<<i_name<<"OK");
		return true;
	}
	XMLLOGOUT("Go to Element :"<<i_name<<"false");
	return false;
}

bool XMLNode::gotoFirstChild(const std::string& i_name)
{
	return gotoFirstChild(i_name.c_str());
}
//------------------------------------------------------------
bool XMLNode::gotoNextSibling() { return gotoNextSibling(""); }

bool XMLNode::gotoNextSibling(const char* i_name) {

	if(!m_node)
		return false;
	DOMNode* node = 0;
	if(i_name&&i_name[0]!= '\0')
		node = m_node->NextSiblingElement(i_name);
	else
		node = m_node->NextSiblingElement();

	if(node)
	{
		m_node = node;
		return true;
	}

	return false;
}

bool XMLNode::gotoNextSibling(const std::string& i_name)
{
	return gotoNextSibling(i_name.c_str());
}
//------------------------------------------------------------

bool XMLNode::gotoChild(const char* i_name, const int i_number) { 


	DOMNode* node = 0;
	node = getChild(i_name,i_number).m_node;
	if(node)
	{
		m_node = node;
		return true;
	}
	return false;
}

bool XMLNode::gotoChild(const std::string& i_name, const int i_number)
{
	return gotoChild(i_name.c_str(),i_number); 
}
//------------------------------------------------------------
bool XMLNode::gotoChild(const int i_number)
{
	DOMNode* node = 0;
	XMLNode xnode = getChild(i_number);
	node = xnode.m_node;
	if(node)
	{
		m_node = node;
		return true;
	}
	return false;

}
//------------------------------------------------------------
bool XMLNode::gotoDocumentElement()
{
	if(!m_node)
		return false;
	DOMNode* node = 0;
	TiXmlDocument * doc = m_node->GetDocument();
	if(doc)
		node = doc->RootElement();
	if(node)
	{
		m_node = node;
		return true;
	}
	return false;

}
//------------------------------------------------------------

bool XMLNode::isLastSibling() const { return isLastSibling(""); }

bool XMLNode::isLastSibling(const char* i_name) const
{
	
	if(!m_node)
		return true;
	XMLLOGOUT("Start Is Last element")
		DOMNode* node= 0;
	if(i_name &&(i_name[0]!='\0'))
		node = m_node->NextSiblingElement(i_name);
	else
		node = m_node->NextSiblingElement();
	XMLLOGOUT("End Is Last element")
	return (node==0);
}


bool XMLNode::isLastSibling(const std::string& i_name) const
{
	return isLastSibling(i_name.c_str());

}
//------------------------------------------------------------

bool XMLNode::setAttribute(const char* i_name, const char* i_value) { 

	if(!m_node ||!i_value || !i_name)
		return false;
	if(XmlStringManager::IsAllAscii(i_value))
		m_node->SetAttribute(i_name,i_value);
	else
	{
		if(XmlStringManager::IsSameStringNoCase(GetEncodingString(),"utf-8"))
		{
			string temp_val;
			XmlStringManager::GBKToUTF8(temp_val,i_value);
			m_node->SetAttribute(i_name,temp_val);
		}
	}
	return true;
	
	
}

bool XMLNode::setAttribute(const std::string& i_name, const std::string& i_value)
{
	return setAttribute(i_name.c_str(),i_value.c_str());
}
//------------------------------------------------------------

bool XMLNode::setAttribute(const char* i_name, const bool i_value) 
{ 

	if(!m_node)
		return false;
	if(i_value)
		m_node->SetAttribute(i_name,"true");
	else
		m_node->SetAttribute(i_name,"false");

	return true;
}

bool XMLNode::setAttribute(const std::string& i_name, const bool i_value)
{

	return setAttribute(i_name.c_str(),i_value); 

}
//------------------------------------------------------------

bool XMLNode::setAttribute(const char* i_name, const int i_value) {
	
	if(!m_node)
		return false;
	m_node->SetAttribute(i_name,i_value);
	return true;

}

bool XMLNode::setAttribute(const std::string& i_name, const int i_value)
{
	return setAttribute(i_name.c_str(),i_value); 

}
//------------------------------------------------------------
bool XMLNode::setAttribute(const char* i_name, const float i_value, const int i_prec ) {
	//std::ostringstream temp;
	//temp << std::setprecision(i_prec) << i_value;
	//std::size_t found ;
	//std::string tempValue = temp.str();
	//while(std::string::npos!=(found=tempValue.find(',')))
	//{
	//	tempValue.erase(found,1);
	//}
	char prec[20];
	sprintf(prec,"%%.%df",i_prec);
	char tempv [50] = {0};
	sprintf(tempv,prec,i_value);
	for(int i=48;i>=0;i--)
	{
		if(tempv[i]!='\0'&&tempv[i]!='0')
	{
		if(tempv[i]=='.')
			tempv[i] = '\0';
		else
			tempv[i+1]='\0';
			break;
		}
	}

	return setAttribute(i_name,tempv);

}
bool XMLNode::setAttribute(const std::string& i_name, const float i_value, const int i_prec)
{
	return setAttribute(i_name.c_str(),i_value,i_prec);
	//return setAttribute(i_name,temp.str());
}
//------------------------------------------------------------

bool XMLNode::setAttribute(const char* i_name, const double i_value, const int i_prec )
{
	/*std::ostringstream temp;
	temp << std::setprecision(i_prec) << i_value;
	std::size_t found ;
	std::string tempValue = temp.str();
	while(std::string::npos!=(found=tempValue.find(',')))
	{
		tempValue.erase(found,1);
	}*/
	char prec[20];
	sprintf(prec,"%%.%dlf",i_prec);
	char tempv [50] = {0};
	sprintf(tempv,prec,i_value);
	for(int i=48;i>0;i--)
	{
		if(tempv[i]!='\0'&&tempv[i]!='0')
		{	
			if(tempv[i]=='.')
				tempv[i] = '\0';
			else
				tempv[i+1]='\0';
			break;
		}
	}
	return setAttribute(i_name,tempv);

}

bool XMLNode::setAttribute(const std::string& i_name, const double i_value, const int i_prec)
{
	return setAttribute(i_name.c_str(),i_value,i_prec); 
	//return setAttribute(i_name,temp.str());
}
//------------------------------------------------------------



void  XMLNode::setValue(const char* i_value) 
{

	if(m_node && i_value)
	{

		const char * pText = i_value;
		string temp_val;
		if(!XmlStringManager::IsAllAscii(pText))
		{
			if(XmlStringManager::IsSameStringNoCase(GetEncodingString(),"utf-8"))
			{
				XmlStringManager::GBKToUTF8(temp_val,i_value);
				pText = temp_val.c_str();
			}
		}
		TiXmlText text( pText);
		TiXmlNode *child = m_node->FirstChild();
		if(child)
		{
			if(child->ToText())
				m_node->ReplaceChild(child,text);
			else
				m_node->InsertBeforeChild(child,text);
		}
		else
			m_node->InsertEndChild(text);
	}
}

void XMLNode::setValue(const std::string& i_value)
{
	setValue(i_value.c_str());

}
//------------------------------------------------------------
void XMLNode::setValue(bool i_value)
{
	const char *temp = (i_value ? "true" : "false");
	setValue(temp);
}
//------------------------------------------------------------
void XMLNode::setValue(int i_value)
{
	std::ostringstream temp;
	temp << i_value;
	std::size_t found ;
	std::string tempValue = temp.str();
	while(std::string::npos!=(found=tempValue.find(',')))
	{
		tempValue.erase(found,1);
	}
	setValue(tempValue.c_str());
	//setValue(temp.str());
}
//------------------------------------------------------------
void XMLNode::setValue(float i_value, int i_prec)
{
	//std::ostringstream temp;
	//temp << std::setprecision(i_prec) << i_value;
	//std::size_t found ;
	//std::string tempValue = temp.str();
	//while(std::string::npos!=(found=tempValue.find(',')))
	//{
	//	tempValue.erase(found,1);
	//}
	char prec[20];
	sprintf(prec,"%%.%df",i_prec);
	char tempv [50] = {0};
	sprintf(tempv,prec,i_value);
	for(int i=48;i>=0;i++)
	{
		if(tempv[i]!='\0'&&tempv[i]!='0')
	{
		if(tempv[i]=='.')
			tempv[i] = '\0';
		else
			tempv[i+1]='\0';
			break;
		}
	}
	setValue(tempv);
	//setValue(temp.str());

}
//------------------------------------------------------------
XMLNode XMLNode::cloneNode(bool deep)
{
	if(!m_node) return XMLNode();
	DOMNode * node =m_node->Clone()->ToElement();

	return XMLNode(node);

}
//------------------------------------------------------------


void XMLNode::addChild(const char* i_name) {
	
	if(i_name&&(i_name[0]!='\0'))
	{
		TiXmlElement element(i_name);
		DOMNode * temp = element.Clone()->ToElement();
		if(m_node)
			m_node->LinkEndChild(temp);
		m_node = temp;
	}
}

void XMLNode::addChild(XMLNode& i_node, bool deep)
{
	if(i_node.m_node)
	{
		DOMNode * temp = i_node.m_node->Clone()->ToElement();
		if(m_node)
			m_node->LinkEndChild(temp);
		m_node = temp;
	}
}


bool XMLNode::addChild(const std::string& i_name)
{
	if(i_name!="")
	{
		TiXmlElement element(i_name.c_str());
		DOMNode * temp = element.Clone()->ToElement();
		if(m_node)
			m_node->LinkEndChild(temp);
		m_node = temp;
		return true;
	}
	return false;
}
//------------------------------------------------------------
bool XMLNode::appendChild(const XMLNode& i_newChild)
{
	if(!m_node)
		return false;
	if(i_newChild.m_node)
	{
		m_node->InsertEndChild(*(i_newChild.m_node));
		return true;
	}

	return false;

}
//------------------------------------------------------------
bool XMLNode::removeNode()
{
	if(gotoParent())
	{	
		try
		{
			m_node->Clear();
			return true;
		}
		catch(...)
		{
			return false;
		}
	}
	else
		return false;

}
//------------------------------------------------------------

bool  XMLNode::replaceNode(const char* i_name) { 
	TiXmlElement newChild(i_name);
	DOMNode* temp = m_node;
	if(gotoParent())
	{
		m_node =m_node->ReplaceChild(temp,newChild)->ToElement();
		return true;
	}
	return false;
	
}

bool XMLNode::replaceNode(const std::string& i_name)
{
	return replaceNode(i_name.c_str());
}

const char * XMLNode::GetEncodingString() const
{
	if(!m_node)
		return "";
	TiXmlDeclaration *dec =	m_node->GetDocument()->FirstChild()->ToDeclaration();
	if(dec)
	{
		return dec->Encoding();
	}
	return "";
}

DOMNode*  XMLNode::getDOMNode(){ return m_node; };

/** Checks that node is empty */
bool  XMLNode::isNull() const { return !m_node; }
}
