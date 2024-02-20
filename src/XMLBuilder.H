#pragma once
#include <string>
#include <fstream>
#include <ios>
#include <stack>
#include "Document.H"

// 
// [Abstract Factory pattern] AbstractFactory
// - It declares an interface for Build operations that create abstract Node product objects
//   {Document_Impl, Element_Impl, Attr_Impl, Text_Impl}.
//
// [Builder pattern] Builder
// - It specifies an abstract interface for creating parts {Node types} of a Product {DOM} object.
//
class XMLBuilder
{
protected:
    XMLBuilder() {}
public:
    virtual void BuildDocument() {}
    virtual void BuildElement(const std::string& tagName) {}
    virtual void BuildAttribute(const std::string& name, const std::string& value) {}
    virtual void BuildText(const std::string& data) {}
    virtual DOM* GetDOM() { return nullptr; }
    virtual void popProbe() {}
};

// 
// [Abstract Factory pattern] (partial) ConcreteFactory
// - It implements the Build operations to create concrete Node product objects.
// - In this scenario, there are actually two true ConcreteFactory subclasses {MinimalNodeXMLBuilder, PrettyNodeXMLBuilder}.
//
// [Builder pattern] (partial) ConcreteBuilder
// - It constructs and assembles parts {Node types} of the product by implementing the Builder interface {XMLBuilder}.
// - It keeps track of the object representation / hierarchy.
// - It provide an interface to retrieve the final product {DOM}.
// - {MinimalNodeXMLBuilder, PrettyNodeXMLBuilder} are the two true ConcreteBuilder,
//   which creates Node objects from the "minimal" or "pretty" families respectively.
//
class NodeXMLBuilder : public virtual XMLBuilder
{
protected:
    Document_Impl* _currentDOM;
    std::stack<dom::Element*> hierarchyProbe;
public:
    NodeXMLBuilder();
    virtual void BuildDocument() = 0;
    virtual void BuildElement(const std::string& tagName);
    virtual void BuildAttribute(const std::string& name, const std::string& value);
    virtual void BuildText(const std::string& data);
    virtual DOM* GetDOM() { return _currentDOM; }
    virtual void popProbe();
};

// 
// [Abstract Factory pattern] ConcreteFactory
// - It implements the Build operations to create concrete Node product objects.
// - Specialized to create ConcreteProduct of {Document_Impl, Element_Impl, Attr_Impl, Text_Impl}.
//
// [Builder pattern] ConcreteBuilder
// - It constructs and assembles parts {Node types} of the product by implementing the Builder interface {XMLBuilder}.
// - It keeps track of the object representation / hierarchy.
// - It provide an interface to retrieve the final product {DOM}.
// - {MinimalNodeXMLBuilder} is a true ConcreteBuilder which creates Node objects from the "minimal" family.
//   {Document_Impl, Element_Impl, Attr_Impl, Text_Impl}
//
class MinimalNodeXMLBuilder : public virtual NodeXMLBuilder
{
public:
    MinimalNodeXMLBuilder() {}
    virtual void BuildDocument();
};

// 
// [Abstract Factory pattern] ConcreteFactory
// - It implements the Build operations to create concrete Node product objects.
// - Specialized to create ConcreteProduct of {PrettyDocument_Impl, PrettyElement_Impl, PrettyAttr_Impl, PrettyText_Impl}.
//
// [Builder pattern] ConcreteBuilder
// - It constructs and assembles parts {Node types} of the product by implementing the Builder interface {XMLBuilder}.
// - It keeps track of the object representation / hierarchy.
// - It provide an interface to retrieve the final product {DOM}.
// - {PrettyNodeXMLBuilder} is a true ConcreteBuilder which creates Node objects from the "pretty" family.
//   {PrettyDocument_Impl, PrettyElement_Impl, PrettyAttr_Impl, PrettyText_Impl}
//
class PrettyNodeXMLBuilder : public virtual NodeXMLBuilder
{
public:
    PrettyNodeXMLBuilder() {}
    virtual void BuildDocument();
};
