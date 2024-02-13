#pragma once

#include "NodeList.H"

class dom::Node;

//
// [Iterator pattern] Iterator
// - XMLIterator defines an interface for accessing and traversing elements.
//
class XMLIterator
{
protected:
    XMLIterator(void);
public:
    ~XMLIterator() {}
    virtual void first() = 0;
    virtual dom::Node* next() = 0;
    virtual bool isDone() = 0;
    virtual dom::Node* currentItem() = 0;
};

//
// [Iterator pattern] ConcreteIterator
// - NodeIterator implements the Iterator (XMLIterator) interface.
// - It keeps track of the current position in the traversal of the Aggregate.
//
class NodeIterator : public virtual XMLIterator
{
private:
    dom::Node* _root;
    dom::Node* _currentChild;
    dom::Node* _currentGrandChild;
    dom::NodeList::iterator _currentChildItr;
    dom::NodeList* _grandChildren;
    NodeIterator* _grandChildrenItr;
    bool _done;
    int _state;
protected:
public:
    NodeIterator(dom::Node* root);
    ~NodeIterator() {}
    virtual void first();
    virtual dom::Node* next();
    virtual bool isDone();
    virtual dom::Node* currentItem();
};
