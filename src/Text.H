#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "Node.H"

namespace dom
{
    class Document;

    // [Factory Method pattern] Product
    //   - defines the interface {Attr, Element, Text} of ConcreteProduct objects {Attr_Impl, Element_Impl, Text_Impl} the Factory Method creates.
    //   - Factory Methods, {createAttribute(), createElement(), createTextNode()} are within the Creator interface (Document),
    //       and realized by the ConcreteCreator (Document_Impl).
    class Text : public virtual Node
    {
    public:
        virtual ~Text() {}

        virtual const std::string& getName(void) = 0;
        virtual const std::string& getData(void) = 0;
        virtual const std::string& getValue(void) = 0;
        virtual void setData(const std::string& value) = 0;
        virtual void setValue(const std::string& value) = 0;
        virtual int getLength(void) = 0;
        virtual const std::string& substringData(int offset, int count) = 0;
        virtual void appendData(const std::string& arg) = 0;
        virtual void insertData(int offset, const std::string& arg) = 0;
        virtual void deleteData(int offset, int count) = 0;
        virtual void replaceData(int offset, int count, const std::string& arg) = 0;
        virtual Text* splitText(int offset) = 0;
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
class Text_Impl : public virtual dom::Text, Node_Impl
{
protected:
    Text_Impl(const std::string value, dom::Document* document);
public:
    friend class Document_Impl;

    virtual ~Text_Impl();

    virtual const std::string& getName(void);
    virtual const std::string& getData(void);
    virtual const std::string& getValue(void);
    virtual void setData(const std::string& value);
    virtual void setValue(const std::string& value);
    virtual int getLength(void);
    virtual const std::string& substringData(int offset, int count);
    virtual void appendData(const std::string& arg);
    virtual void insertData(int offset, const std::string& arg);
    virtual void deleteData(int offset, int count);
    virtual void replaceData(int offset, int count, const std::string& arg);
    virtual dom::Text* splitText(int offset);
    virtual void serializeMinimal(std::ostream* os, int indentationLevel = 0);
    virtual void serializePretty(std::ostream* os, int indentationLevel = 0);
};

#endif // TEXT_H
