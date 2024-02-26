#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

#include "Node.H"
#include "NamedNodeMap.H"
#include "ValidChildren.H"
#include "Director.H"
#include "Builder.H"

//class Director;

namespace dom
{
    class Attr;
    class NodeList;
    class Document;

    class Element : public virtual Node
    {
    public:
        virtual ~Element() {}

        //
        // Serialization Data Extraction Strategy
        //
        virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace)		= 0;

        virtual const std::string &	getAttribute(const std::string & name)					= 0;
        virtual Attr *			getAttributeNode(const std::string & name)				= 0;
        virtual NodeList *		getElementsByTagName(const std::string & tagName)			= 0;
        virtual const std::string &	getTagName(void)							= 0;
        virtual bool			hasAttribute(const std::string & name)					= 0;
        virtual void			removeAttribute(const std::string & name)				= 0;
        virtual Attr *			removeAttributeNode(Attr * oldAttr)					= 0;
        virtual void			setAttribute(const std::string & name, const std::string & value)	= 0;
        virtual Attr *			setAttributeNode(Attr * newAttr)					= 0;

        virtual dom::NamedNodeMap *	getAttributes(void)							= 0;
        virtual bool			hasAttributes(void)							= 0;
    };
};

class Element_Impl : public virtual dom::Element, Node_Impl
{
private:
    NamedNodeMap_Impl	attributes;
protected:
public:
    friend class Document_Impl;

    Element_Impl(const std::string & tagName, dom::Document * document);
    virtual ~Element_Impl();

    //
    // Serialization Data Extraction Strategy
    //
    virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace);

    virtual const std::string &	getAttribute(const std::string & name);
    virtual dom::Attr *		getAttributeNode(const std::string & name);
    virtual dom::NodeList *		getElementsByTagName(const std::string & tagName);
    virtual const std::string &	getTagName(void);
    virtual bool			hasAttribute(const std::string & name);
    virtual void			removeAttribute(const std::string & name);
    virtual dom::Attr *		removeAttributeNode(dom::Attr * oldAttr);
    virtual void			setAttribute(const std::string & name, const std::string & value);
    virtual dom::Attr *		setAttributeNode(dom::Attr * newAttr);

    virtual dom::NamedNodeMap *	getAttributes(void)	{ return &attributes; }
    virtual bool			hasAttributes(void)	{ return attributes.size() > 0; }
};

// This is a virtual proxy for Element to delay parsing of children elements
class ElementProxy : public virtual dom::Element, Node_Impl
{
private:
    Element* element;
    bool isChildInitialized;
    std::streampos streamPosition;
    Director* pDirector;
protected:
    ElementProxy(const std::string& tagName, dom::Document* document);
public:
    friend class Document_Impl;
    virtual ~ElementProxy() {}

    virtual void parseChildNodes();
    virtual void setIsChildInitialized(bool flag) { isChildInitialized = flag; }
    virtual void setElementInitPoint(std::streampos pos) { streamPosition = pos; }
    virtual void setDirector(Director* director) { pDirector = director; }

    // functions from Node
    virtual const std::string&  getNodeName(void)           { return element->getNodeName(); }
    virtual const std::string&  getNodeValue(void)          { return element->getNodeValue(); }
    virtual void                setNodeValue(const std::string& nodeValue) { return element->setNodeValue(nodeValue); }
    virtual short               getNodeType(void)           { return element->getNodeType(); }
    virtual Node*               getParentNode(void)         { return element->getParentNode(); }
    virtual Node*               getPreviousSibling(void)    { return element->getPreviousSibling(); }
    virtual Node*               getNextSibling(void)        { return element->getNextSibling(); }
    virtual dom::Document*      getOwnerDocument(void)      { return element->getOwnerDocument(); }
    virtual const std::string&  getLocalName(void)          { return element->getLocalName(); }
    virtual void                setParent(dom::Node* parent) { return element->setParent(parent); }

    // child related functions from Node
    virtual void                serialize(std::fstream* writer, WhitespaceStrategy* whitespace);
    virtual dom::NodeList*      getChildNodes(void);
    virtual Node*               getFirstChild(void);
    virtual Node*               getLastChild(void);
    virtual Node*               insertBefore(Node* newChild, Node* refChild);
    virtual Node*               replaceChild(Node* newChild, Node* oldChild);
    virtual Node*               removeChild(Node* oldChild);
    virtual Node*               appendChild(Node* newChild);
    virtual bool                hasChildNodes(void);

    // functions from Element
    virtual const std::string&  getAttribute(const std::string& name)               { return element->getAttribute(name); }
    virtual dom::Attr*          getAttributeNode(const std::string& name)           { return element->getAttributeNode(name); }
    virtual dom::NodeList*      getElementsByTagName(const std::string& tagName)    { return element->getElementsByTagName(tagName); }
    virtual const std::string&  getTagName(void)                                    { return element->getTagName(); }
    virtual bool                hasAttribute(const std::string& name)               { return element->hasAttribute(name); }
    virtual void                removeAttribute(const std::string& name)            { return element->removeAttribute(name); }
    virtual dom::Attr*          removeAttributeNode(dom::Attr* oldAttr)             { return element->removeAttributeNode(oldAttr); }
    virtual void                setAttribute(const std::string& name, const std::string& value) { return element->setAttribute(name, value); }
    virtual dom::Attr*          setAttributeNode(dom::Attr* newAttr)                { return element->setAttributeNode(newAttr); }
    virtual dom::NamedNodeMap*  getAttributes(void)                                 { return element->getAttributes(); }
    virtual bool                hasAttributes(void)                                 { return element->hasAttributes(); }
};

class ElementDecorator : public virtual dom::Element
{
};

class XMLValidator;
namespace dom
{
    class NodeList;
};

class ElementValidator : public virtual ElementDecorator, public virtual Node_Impl
{
private:
    dom::Element *	parent;
    ValidChildren *	schemaElement;
public:
    ElementValidator(dom::Element * _parent, XMLValidator * xmlValidator);

    //
    // Serialization Data Extraction Strategy
    //
    virtual void serialize(std::fstream * writer, WhitespaceStrategy * whitespace)
      { parent->serialize(writer, whitespace); }

    //
    // Undecorated pass-through methods.
    //
    virtual const std::string &	getAttribute(const std::string & name)		{ return parent->getAttribute(name); }
    virtual dom::Attr *		getAttributeNode(const std::string & name)	{ return parent->getAttributeNode(name); }
    virtual dom::NodeList *		getElementsByTagName(const std::string & tagName)
      { return parent->getElementsByTagName(tagName); }
    virtual const std::string &	getTagName(void)				{ return parent->getTagName(); }
    virtual bool			hasAttribute(const std::string & name)		{ return parent->hasAttribute(name); }
    virtual void			removeAttribute(const std::string & name)	{ parent->removeAttribute(name); }
    virtual dom::Attr *		removeAttributeNode(dom::Attr * oldAttr) { return parent->removeAttributeNode(oldAttr); }

    //
    // Decorated Methods
    //
    virtual void			setAttribute(const std::string & name, const std::string & value);
    virtual dom::Attr *		setAttributeNode(dom::Attr * newAttr);
    virtual dom::Node *		insertBefore(dom::Node * newChild, dom::Node * refChild);
    virtual dom::Node *		replaceChild(dom::Node * newChild, dom::Node * oldChild);
    virtual dom::Node *		appendChild(dom::Node * newChild);

    //
    // Reimplemented Node members
    //
    virtual dom::NamedNodeMap *	getAttributes(void)				{ return parent->getAttributes(); }
    virtual bool			hasAttributes(void)				{ return parent->hasAttributes(); }
    virtual const std::string &	getNodeName(void)				{ return parent->getNodeName(); }
    virtual const std::string &	getNodeValue(void)				{ return parent->getNodeValue(); }
    virtual void			setNodeValue(const std::string & nodeValue)	{ parent->setNodeValue(nodeValue); }
    virtual short			getNodeType(void)				{ return parent->getNodeType(); }
    virtual dom::Node *		getParentNode(void)				{ return parent->getParentNode(); }
    virtual dom::NodeList *		getChildNodes(void)				{ return parent->getChildNodes(); }
    virtual dom::Node *		getFirstChild(void)				{ return parent->getFirstChild(); }
    virtual dom::Node *		getLastChild(void)				{ return parent->getLastChild(); }
    virtual dom::Node *		getPreviousSibling(void)			{ return parent->getPreviousSibling(); }
    virtual dom::Node *		getNextSibling(void)				{ return parent->getNextSibling(); }
    virtual dom::Document *		getOwnerDocument(void)				{ return parent->getOwnerDocument(); }
    virtual dom::Node *		removeChild(Node * oldChild)			{ return parent->removeChild(oldChild); }
    virtual bool			hasChildNodes(void)				{ return parent->hasChildNodes(); }
    virtual const std::string &	getLocalName(void)				{ return parent->getLocalName(); }
};

#endif // ELEMENT_H
