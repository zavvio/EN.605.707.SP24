#pragma once
#include <string>
#include <fstream>
#include <ios>
#include <stack>
#include "Document.H"
#include "Observer.H"

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
// [Observer pattern] ConcreteSubject
// - This is subclass of the Subject, so it's already capable of attaching/detaching Observer objects.
// - This store state of interest to ConcreteObserver objects {TitleBar, TabBar, Canvas, StatusBar}
// - It sends a notification to its observers when its state change; which is when it parses a new XML file.
// - Note: This is also the Builder from the Builder pattern
//
// [Mediator pattern] Colleague classes
// - The Mediator object keeps track of these Colleague classes.
// - The colleagues communicate with the Mediator whenever it would have otherwise communicated with another colleague.
// - The colleagues are both the Subject and Observer objects from the Observer pattern.
//
class NodeXMLBuilder : public virtual XMLBuilder, public virtual Subject
{
protected:
    Document_Impl* _currentDOM;
    std::stack<dom::Element*> hierarchyProbe;
	std::string _state;
public:
    NodeXMLBuilder();
    virtual void BuildDocument() = 0;
    virtual void BuildElement(const std::string& tagName);
    virtual void BuildAttribute(const std::string& name, const std::string& value);
    virtual void BuildText(const std::string& data);
    virtual DOM* GetDOM() { return _currentDOM; }
    virtual void popProbe();
    virtual std::string getState() { return ""; };
};

//
// [Observer pattern] ConcreteSubject
// - subclass of (ConcreteSubject) NodeXMLBuilder
//
// [Mediator pattern] Colleague classes
// - The Mediator object keeps track of these Colleague classes.
// - The colleagues communicate with the Mediator whenever it would have otherwise communicated with another colleague.
// - The colleagues are both the Subject and Observer objects from the Observer pattern.
//
class MinimalNodeXMLBuilder : public virtual NodeXMLBuilder
{
public:
    MinimalNodeXMLBuilder(ChangeManager* changeManager = nullptr) : Subject(changeManager) {}
    virtual void BuildDocument();
	virtual std::string getState();
};

//
// [Observer pattern] ConcreteSubject
// - subclass of (ConcreteSubject) NodeXMLBuilder
//
// [Mediator pattern] Colleague classes
// - The Mediator object keeps track of these Colleague classes.
// - The colleagues communicate with the Mediator whenever it would have otherwise communicated with another colleague.
// - The colleagues are both the Subject and Observer objects from the Observer pattern.
//
class PrettyNodeXMLBuilder : public virtual NodeXMLBuilder
{
public:
    PrettyNodeXMLBuilder(ChangeManager* changeManager = nullptr) : Subject(changeManager) {}
    virtual void BuildDocument();
	virtual std::string getState();
};
