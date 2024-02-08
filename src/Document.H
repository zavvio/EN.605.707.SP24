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
// [Strategy pattern] ConcreteStrategy
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
