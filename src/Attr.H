#ifndef ATTR_H
#define ATTR_H

#include <string>

#include "Node.H"

namespace dom
{
    class Document;
    class Element;

    // [Factory Method pattern] Product
    //   - defines the interface {Attr, Element, Text} of ConcreteProduct objects {Attr_Impl, Element_Impl, Text_Impl} the Factory Method creates.
    //   - Factory Methods, {createAttribute(), createElement(), createTextNode()} are within the Creator interface (Document),
    //       and realized by the ConcreteCreator (Document_Impl).
    class Attr : public virtual Node
    {
    public:
        virtual ~Attr() {}

        virtual const std::string& getName(void) = 0;
        virtual const std::string& getValue(void) = 0;
        virtual void setValue(const std::string& value) = 0;
        virtual Element* getOwnerElement(void) = 0;
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
class Attr_Impl : public virtual dom::Attr, Node_Impl
{
protected:
    Attr_Impl(const std::string& tagName, dom::Document* document);
    Attr_Impl(const std::string& tagName, const std::string& value, dom::Document* document);
public:
    friend class Document_Impl;
    friend class Element_Impl;

    virtual ~Attr_Impl();

    virtual const std::string& getName(void);
    virtual const std::string& getValue(void);
    virtual void setValue(const std::string& value);
    virtual dom::Element* getOwnerElement(void);
    virtual void serializeMinimal(std::ostream* os, int indentationLevel = 0);
    virtual void serializePretty(std::ostream* os, int indentationLevel = 0);
};

#endif // ATTR_H
