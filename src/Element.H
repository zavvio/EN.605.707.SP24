#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

#include "Node.H"
#include "NamedNodeMap.H"

namespace dom
{
    class Attr;
    class NodeList;
    class Document;

    // [Factory Method pattern] Product
    //   - defines the interface {Attr, Element, Text} of ConcreteProduct objects {Attr_Impl, Element_Impl, Text_Impl} the Factory Method creates.
    //   - Factory Methods, {createAttribute(), createElement(), createTextNode()} are within the Creator interface (Document),
    //       and realized by the ConcreteCreator (Document_Impl).
    // [Decorator pattern] Component
    //      - Defines the object interface which can have responsibilities added or removed from it dynamically.
    //      - ConcreteComponent is Element_Impl, to be decorated by ConcreteDecorator {canAddTextElement, canAddElementElement, canAddAttributeElement}
    class Element : public virtual Node
    {
    public:
        virtual ~Element() {}

        virtual const std::string& getAttribute(const std::string& name) = 0;
        virtual Attr* getAttributeNode(const std::string& name) = 0;
        virtual NodeList* getElementsByTagName(const std::string& tagName) = 0;
        virtual const std::string& getTagName(void) = 0;
        virtual bool hasAttribute(const std::string& name) = 0;
        virtual void removeAttribute(const std::string& name) = 0;
        virtual Attr* removeAttributeNode(Attr* oldAttr) = 0;
        virtual void setAttribute(const std::string& name, const std::string& value) = 0;
        virtual Attr* setAttributeNode(Attr* newAttr) = 0;

        virtual dom::NamedNodeMap* getAttributes(void) = 0;
        virtual bool hasAttributes(void) = 0;
    };
};

// [Factory Method pattern] ConcreteProduct
//   - Implements one of the Product interface, {Attr, Element, Text}
//   - Forms the actual object to be returned by the ConcreteCreator (Document_Impl) via one of the Factory Method {createAttribute(), createElement(), createTextNode()}
// [Strategy pattern] ConcreteStrategy
//   - This implements the algorithm using the Strategy (Node) interface.
//   -   algorithms includes a bundle of {serializeMinimal, serializePretty}
//   - Context (XMLSerializer) maintains reference to one such ConcreteStrategies,
//   -   and defers interface calls to the algorithm implemented here.
//   - From {Document_Impl, Element_Impl, Attr_Impl, Text_Impl}, these ConcreteStrategies provide output content differently.
// [Decorator pattern] ConcreteComponent
//      - Defines the object with responsibilities to be added or removed.
//      - Based on Component interface Node, to be decorated by ConcreteDecorator {canAddTextElement, canAddElementElement, canAddAttributeElement}
class Element_Impl : public virtual dom::Element, Node_Impl
{
private:
    NamedNodeMap_Impl attributes;
protected:
    Element_Impl(const std::string& tagName, dom::Document* document);
public:
    friend class Document_Impl;

    virtual ~Element_Impl();

    virtual const std::string& getAttribute(const std::string& name);
    virtual dom::Attr* getAttributeNode(const std::string& name);
    virtual dom::NodeList* getElementsByTagName(const std::string& tagName);
    virtual const std::string& getTagName(void);
    virtual bool hasAttribute(const std::string& name);
    virtual void removeAttribute(const std::string& name);
    virtual dom::Attr* removeAttributeNode(dom::Attr* oldAttr);
    virtual void setAttribute(const std::string& name, const std::string& value);
    virtual dom::Attr* setAttributeNode(dom::Attr* newAttr);

    virtual dom::NamedNodeMap* getAttributes(void) { return &attributes; }
    virtual bool hasAttributes(void) { return attributes.size() > 0; }

    virtual void serializeMinimal(std::ostream* os, int indentationLevel = 0);
    virtual void serializePretty(std::ostream* os, int indentationLevel = 0);
};

#endif // ELEMENT_H
