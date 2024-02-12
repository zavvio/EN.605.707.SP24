#pragma once

#include <iostream>
#include <string>
#include <set>
#include "Element.H"
#include "Attr.H"
#include "NamedNodeMap.H"

namespace dom
{
    // [Decorator pattern] Decorator
    //    - Defines a reference to a Component object and defines an interface that conforms to Component's interface.
    //    - ConcreteDecorator {canAddTextElement, canAddElementElement, canAddAttributeElement} are used to decorate ConcreteComponent like Element_Impl.
    class ElementDecorator : public virtual Element
    {
    protected:
        Element* component;
    public:
        ElementDecorator(Element* component);
        virtual ~ElementDecorator();
        virtual void setAttribute(const std::string& name, const std::string& value);
        virtual Attr* setAttributeNode(Attr* newAttr);
        virtual Node* appendChild(Node* newChild);

        // Pure forwarding Element functions
        virtual const std::string& getAttribute(const std::string& name) { return component->getAttribute(name); }
        virtual Attr* getAttributeNode(const std::string& name) { return component->getAttributeNode(name); }
        virtual NodeList* getElementsByTagName(const std::string& tagName) { return component->getElementsByTagName(tagName); }
        virtual const std::string& getTagName(void) { return component->getTagName(); }
        virtual bool hasAttribute(const std::string& name) { return component->hasAttribute(name); }
        virtual void removeAttribute(const std::string& name) { return component->removeAttribute(name); }
        virtual Attr* removeAttributeNode(Attr* oldAttr) { return component->removeAttributeNode(oldAttr); }
        virtual dom::NamedNodeMap* getAttributes(void) { return component->getAttributes(); }
        virtual bool hasAttributes(void) { return component->hasAttributes(); }
        // Pure forwarding Node functions
        virtual const std::string& getNodeName(void) { return component->getNodeName(); }
        virtual const std::string& getNodeValue(void) { return component->getNodeValue(); }
        virtual void setNodeValue(const std::string& nodeValue) { return component->setNodeValue(nodeValue); }
        virtual short getNodeType(void) { return component->getNodeType(); }
        virtual Node* getParentNode(void) { return component->getParentNode(); }
        virtual void setParent(dom::Node* parent) { return component->setParent(parent); }
        virtual NodeList* getChildNodes(void) { return component->getChildNodes(); }
        virtual Node* getFirstChild(void) { return component->getFirstChild(); }
        virtual Node* getLastChild(void) { return component->getLastChild(); }
        virtual Node* getPreviousSibling(void) { return component->getPreviousSibling(); }
        virtual Node* getNextSibling(void) { return component->getNextSibling(); }
        virtual Document* getOwnerDocument(void) { return component->getOwnerDocument(); }
        virtual Node* insertBefore(Node* newChild, Node* refChild) { return component->insertBefore(newChild, refChild); }
        virtual Node* replaceChild(Node* newChild, Node* oldChild) { return component->replaceChild(newChild, oldChild); }
        virtual Node* removeChild(Node* oldChild) { return component->removeChild(oldChild); }
        virtual bool hasChildNodes(void) { return component->hasChildNodes(); }
        virtual const std::string& getLocalName(void) { return component->getLocalName(); }
        virtual void prettyIndentation(std::ostream* os, int indentationLevel = 0) { return component->prettyIndentation(os, indentationLevel); }
        virtual void serializeMinimal(std::ostream* os, int indentationLevel = 0) { return component->serializeMinimal(os, indentationLevel); }
        virtual void serializePretty(std::ostream* os, int indentationLevel = 0) { return component->serializePretty(os, indentationLevel); }
    };
};

// [Decorator pattern] ConcreteDecorator
//    - Add or Remove responsibilities from the Component object.
//    - Based on Decorator ElementDecorator for general conformance, it decorates ConcreteComponent like Element_Impl.
//    - This validates the target Attribute (tag/name) is allowed or the add action is cancelled.
class CanAddAttributeElement : public virtual dom::ElementDecorator
{
private:
    std::set<std::string> validAttributeNames;
public:
    CanAddAttributeElement(Element* component, std::set<std::string> validAttributeNames);
    virtual ~CanAddAttributeElement();
    virtual void setAttribute(const std::string& name, const std::string& value);
    virtual dom::Attr* setAttributeNode(dom::Attr* newAttr);
    virtual bool canAddAttribute(std::string name);
};

// [Decorator pattern] ConcreteDecorator
//    - Add or Remove responsibilities from the Component object.
//    - Based on Decorator ElementDecorator for general conformance, it decorates ConcreteComponent like Element_Impl.
//    - This validates the target Element (tag/name) is allowed or the add action is cancelled.
class CanAddElementElement : public virtual dom::ElementDecorator
{
private:
    std::set<std::string> validElementNames;
public:
    CanAddElementElement(Element* component, std::set<std::string> validElementNames);
    virtual ~CanAddElementElement();
    virtual dom::Node* appendChild(dom::Node* newChild);
    virtual bool canAddElement(std::string name);
};

// [Decorator pattern] ConcreteDecorator
//    - Add or Remove responsibilities from the Component object.
//    - Based on Decorator ElementDecorator for general conformance, it decorates ConcreteComponent like Element_Impl.
//    - This validates Text is allowed or the add action is cancelled.
class CanAddTextElement : public virtual dom::ElementDecorator
{
private:
    bool isAllowed;
public:
    CanAddTextElement(Element* component, bool isAllowed);
    virtual ~CanAddTextElement();
    virtual dom::Node* appendChild(dom::Node* newChild);
    virtual bool canAddText(void);
};