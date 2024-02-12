#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "Node.H"
#include "NodeDecorator.H"
#include "ElementDecorator.H"

namespace dom
{
    class Element;  // [Factory Method pattern] Product
    class Text;     // [Factory Method pattern] Product
    class Attr;     // [Factory Method pattern] Product
    class NodeList;

    // [Factory Method pattern] Creator
    //   - declares the Factory Method {createAttribute(), createElement(), createTextNode()},
    //     which returns a ConcreteProduct object {Attr_Impl, Element_Impl, Text_Impl}.
    //   - Note that the three Factory Methods here are independent of each other,
    //     and for this application, only one ConcreteProduct is implemented for each Product type, there could be more if applicable.
    //   - There is no default implementation of any Factory Method here, only those in the ConcreteCreator (Document_Impl).
    class Document : public virtual Node
    {
    public:
        // [Factory Method pattern] FactoryMethod
        virtual Element* createElement(const std::string& tagName) = 0;
        virtual CanAddElementElement* createValidatedElement(const std::string& tagName, std::set<std::string> validElementNames, std::set<std::string> validAttributeNames, bool isTextAllowed) = 0;
        // [Factory Method pattern] FactoryMethod
        virtual Text* createTextNode(const std::string& data) = 0;
        // [Factory Method pattern] FactoryMethod
        virtual Attr* createAttribute(const std::string& name) = 0;
        virtual Node* getDocumentElement() = 0;
    };
};

// [Factory Method pattern] ConcreteCreator
//   - Could override default Factory Method defined in the Creator (Document), if any, none here.
//   - Defines the actual implementation of the Factory Methods {createAttribute(), createElement(), createTextNode()}
//   - Client with access to these Factory Methods can call them to create an instance of ConcreteProduct {Attr_Impl, Element_Impl, Text_Impl}.
// [Strategy pattern] ConcreteStrategy
//   - This implements the algorithm using the Strategy (Node) interface.
//   -   algorithms includes a bundle of {serializeMinimal, serializePretty}
//   - Context (XMLSerializer) maintains reference to one such ConcreteStrategies,
//   -   and defers interface calls to the algorithm implemented here.
//   - From {Document_Impl, Element_Impl, Attr_Impl, Text_Impl}, these ConcreteStrategies provide output content differently.
// [Decorator pattern] ConcreteComponent
//      - Defines the object with responsibilities to be added or removed.
//      - Based on Component interface Node, to be decorated by ConcreteDecorator {canAddTextDocument, canAddElementDocument}
class Document_Impl : public virtual dom::Document, public virtual Node_Impl
{
public:
    Document_Impl(void);

    virtual ~Document_Impl();

    virtual dom::Element* createElement(const std::string& tagName);
    virtual CanAddElementElement* createValidatedElement(const std::string& tagName, std::set<std::string> validElementNames, std::set<std::string> validAttributeNames, bool isTextAllowed);
    virtual dom::Text* createTextNode(const std::string& data);
    virtual dom::Attr* createAttribute(const std::string& name);
    virtual dom::Node* getDocumentElement();
    virtual void serializeMinimal(std::ostream* os, int indentationLevel = 0);
    virtual void serializePretty(std::ostream* os, int indentationLevel = 0);
};

#endif // DOCUMENT_H
