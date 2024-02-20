#ifndef ATTR_H
#define ATTR_H

#include <string>
#include <fstream>

#include "Node.H"

namespace dom
{
	class Document;
	class Element;

	class Attr : public virtual Node
	{
	public:
		virtual ~Attr() {}

		//
		// Serialization Data Extraction Strategy
		//
		virtual void serialize(std::fstream * writer, int indentationLevel)	= 0;

		virtual const std::string &	getName(void)				= 0;
		virtual const std::string &	getValue(void)				= 0;
		virtual void			setValue(const std::string & value)	= 0;
		virtual Element *		getOwnerElement(void)			= 0;
	};
};

//
// [Template method pattern] AbstractClass
// - This declares abstract primitive operations (despite having default implementations)
//   that concrete subclasses define/override {serialize_indentation, serialize_newLine} with customized algorithm.
// - It also implements a template method {serialize} defining the skeleton of the serialization algorithm;
//   it performs some fixed actions, and calls the customizable primitive operations in a predefined order;
//   it also calls serialize operation from other Node objects.
//
// [Abstract Factory pattern] AbstractProduct (Also ConcreteProduct here with the default implmentations)
// - It defines an interface for a type of product object.
//
class Attr_Impl : public virtual dom::Attr, Node_Impl
{
protected:
	Attr_Impl(const std::string & tagName, dom::Document * document);
	Attr_Impl(const std::string & tagName, const std::string & value, dom::Document * document);
	// [Template method pattern] PrimitiveOperations
	virtual void serialize_indentation(std::fstream* wwriter, int indentationLevel) {}
	virtual void serialize_newLine(std::fstream* wwriter) {}
public:
	friend class Document_Impl;
	friend class Element_Impl;

	virtual ~Attr_Impl();

	//
	// Serialization Data Extraction Strategy
	//
	// [Template method pattern] TemplateMethod
	virtual void serialize(std::fstream * writer, int indentationLevel);

	virtual const std::string &	getName(void);
	virtual const std::string &	getValue(void);
	virtual void			setValue(const std::string & value);
	virtual dom::Element *		getOwnerElement(void);

	//
	// Overridden functions for conforming to Composite Leaf node behavior.
	//
	virtual Node *			insertBefore(Node * newChild, Node * refChild)	{ return 0; }
	virtual Node *			replaceChild(Node * newChild, Node * oldChild)	{ return 0; }
	virtual Node *			removeChild(Node * oldChild)			{ return 0; }
	virtual Node *			appendChild(Node * newChild)			{ return 0; }
};

//
// [Template method pattern] ConcreteClass
// - This implements the primitive operations to carry out subclass-specific steps of the algorithm.
//
// [Abstract Factory pattern] ConcreteProduct
// - It defines a product object to be created by the corresponding ConcreteFactory.
//
class PrettyAttr_Impl : public virtual Attr_Impl
{
public:
	PrettyAttr_Impl(const std::string& tagName, dom::Document* document) : Attr_Impl(tagName, document) {}
	PrettyAttr_Impl(const std::string& tagName, const std::string& value, dom::Document* document) : Attr_Impl(tagName, value, document) {}
protected:
	// [Template method pattern] PrimitiveOperation
	virtual void serialize_indentation(std::fstream* wwriter, int indentationLevel)
	{
		for (int i = 0; i < indentationLevel; i++)
			*wwriter << "\t";
	}
	// [Template method pattern] PrimitiveOperation
	virtual void serialize_newLine(std::fstream* wwriter) { *wwriter << "\n"; }
};

#endif // ATTR_H
