#pragma once
#include <string>
#include <fstream>
#include <ios>
#include <stack>
#include "Document.H"

class XMLBuilder
{
private:
	//
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

class NodeXMLBuilder : public virtual XMLBuilder
{
private:
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

class MinimalNodeXMLBuilder : public virtual NodeXMLBuilder
{
public:
	MinimalNodeXMLBuilder() {}
	virtual void BuildDocument();
};

class PrettyNodeXMLBuilder : public virtual NodeXMLBuilder
{
public:
	PrettyNodeXMLBuilder() {}
	virtual void BuildDocument();
};
