#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "Node.H"

namespace dom
{
	class Document;

	class Text : public virtual Node
	{
	public:
		virtual ~Text()	{}

		//
		// Serialization Data Extraction Strategy
		//
		virtual void serialize(std::fstream * writer, int indentationLevel)	= 0;

		virtual const std::string &	getName(void)							= 0;
		virtual const std::string &	getData(void)							= 0;
		virtual const std::string &	getValue(void)							= 0;
		virtual void			setData(const std::string & value)				= 0;
		virtual void			setValue(const std::string & value)				= 0;
		virtual int			getLength(void)							= 0;
		virtual const std::string &	substringData(int offset, int count)				= 0;
		virtual void			appendData(const std::string & arg)				= 0;
		virtual void			insertData(int offset, const std::string & arg)			= 0;
		virtual void			deleteData(int offset, int count)				= 0;
		virtual void			replaceData(int offset, int count, const std::string & arg)	= 0;
		virtual Text *			splitText(int offset)						= 0;
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
class Text_Impl : public virtual dom::Text, Node_Impl
{
protected:
	Text_Impl(const std::string value, dom::Document * document);
	// [Template method pattern] PrimitiveOperations
	virtual void serialize_indentation(std::fstream* wwriter, int indentationLevel) {}
	virtual void serialize_newLine(std::fstream* wwriter) {}
public:
	friend class Document_Impl;

	virtual ~Text_Impl();

	//
	// Serialization Data Extraction Strategy
	//
	// [Template method pattern] TemplateMethod
	virtual void serialize(std::fstream * writer, int indentationLevel);

	virtual const std::string &	getName(void);
	virtual const std::string &	getData(void);
	virtual const std::string &	getValue(void);
	virtual void			setData(const std::string & value);
	virtual void			setValue(const std::string & value);
	virtual int			getLength(void);
	virtual const std::string &	substringData(int offset, int count);
	virtual void			appendData(const std::string & arg);
	virtual void			insertData(int offset, const std::string & arg);
	virtual void			deleteData(int offset, int count);
	virtual void			replaceData(int offset, int count, const std::string & arg);
	virtual dom::Text *		splitText(int offset);

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
class PrettyText_Impl : public virtual Text_Impl
{
public:
	PrettyText_Impl(const std::string value, dom::Document* document) : Text_Impl(value, document) {}
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

#endif // TEXT_H
