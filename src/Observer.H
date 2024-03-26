#pragma once

#include <map>
#include <set>
#include <utility>
#include "Observer.H"

class Subject;
class Observer;

//
// [Mediator pattern] Mediator
// - It defines an interface for communicating with Colleague objects.
//
class ChangeManager
{
private:
    std::set<std::pair<Subject*, Observer*>> _mappings;
protected:
public:
    ChangeManager();
    void Register(Subject* subject, Observer* observer);
    void Unregister(Subject* subject, Observer* observer);
    void Notify();
    void Notify(Subject* subject);
};

//
// [Mediator pattern] ConcreteMediator
// - It implements cooperative behavior by coordinating Colleague objects.
// - It knows an maintains its colleagues.
//
class SimpleChangeManager : public ChangeManager
{
};

//
// [Observer pattern] Subject
// - It knows its Observers. Any number of Observer objects may observe a Subject; or the ConcreteSubject {XMLTokenizer, MinimalNodeXMLBuilder, PrettyNodeXMLBuilder}
// - It provides an interface for attaching and detaching Observer objects; or ConcreteObserver objects {TitleBar, TabBar, Canvas, StatusBar}.
//
// [Mediator pattern] Colleague classes
// - The Mediator object keeps track of these Colleague classes.
// - The colleagues communicate with the Mediator whenever it would have otherwise communicated with another colleague.
// - The colleagues are both the Subject and Observer objects from the Observer pattern.
//
class Subject
{
private:
    ChangeManager* _changeManager;
protected:
    //Subject(ChangeManager* changeManager);
public:
    Subject(ChangeManager* changeManager);
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify();
    virtual std::string getState();
};

//
// [Observer pattern] Observer
// - It defines an updating interface for objects that should be notified of changes in a Subject; or the ConcreteSubject {XMLTokenizer, MinimalNodeXMLBuilder, PrettyNodeXMLBuilder}
//
// [Mediator pattern] Colleague classes
// - The Mediator object keeps track of these Colleague classes.
// - The colleagues communicate with the Mediator whenever it would have otherwise communicated with another colleague.
// - The colleagues are both the Subject and Observer objects from the Observer pattern.
//
class Observer
{
private:
    Subject* _subject = nullptr;
protected:
    //Observer(Subject* subject) : _subject(subject) {}
public:
    Observer() {}
    virtual void update(Subject* subject);
};

//
// [Observer pattern] ConcreteObserver
// - It stores state that should stay consistent with the Subjects.
// - It implements the Observer updating interface to keep its state consistent with the Subjects'.
//
// [Mediator pattern] Colleague classes
// - The Mediator object keeps track of these Colleague classes.
// - The colleagues communicate with the Mediator whenever it would have otherwise communicated with another colleague.
// - The colleagues are both the Subject and Observer objects from the Observer pattern.
//
class TitleBar : public Observer
{
private:
    std::string filename;
public:
    virtual void update(Subject* subject);
};

//
// [Observer pattern] ConcreteObserver
// - It stores state that should stay consistent with the Subjects.
// - It implements the Observer updating interface to keep its state consistent with the Subjects'.
//
// [Mediator pattern] Colleague classes
// - The Mediator object keeps track of these Colleague classes.
// - The colleagues communicate with the Mediator whenever it would have otherwise communicated with another colleague.
// - The colleagues are both the Subject and Observer objects from the Observer pattern.
//
class TabBar : public Observer
{
private:
    std::string filename;
public:
    virtual void update(Subject* subject);
};

//
// [Observer pattern] ConcreteObserver
// - It stores state that should stay consistent with the Subjects.
// - It implements the Observer updating interface to keep its state consistent with the Subjects'.
//
// [Mediator pattern] Colleague classes
// - The Mediator object keeps track of these Colleague classes.
// - The colleagues communicate with the Mediator whenever it would have otherwise communicated with another colleague.
// - The colleagues are both the Subject and Observer objects from the Observer pattern.
//
class Canvas : public Observer
{
private:
    std::string componentName;
public:
    virtual void update(Subject* subject);
};

//
// [Observer pattern] ConcreteObserver
// - It stores state that should stay consistent with the Subjects.
// - It implements the Observer updating interface to keep its state consistent with the Subjects'.
//
// [Mediator pattern] Colleague classes
// - The Mediator object keeps track of these Colleague classes.
// - The colleagues communicate with the Mediator whenever it would have otherwise communicated with another colleague.
// - The colleagues are both the Subject and Observer objects from the Observer pattern.
//
class StatusBar : public Observer
{
private:
    std::string componentName;
public:
    virtual void update(Subject* subject);
};