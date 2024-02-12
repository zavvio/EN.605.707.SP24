#pragma once

#include <string>
#include <set>
#include "Node.H"

namespace dom
{
    // [Decorator pattern] Decorator
    //    - Defines a reference to a Component object and defines an interface that conforms to Component's interface.
    //    - ConcreteDecorator {canAddTextDocument, canAddElementDocument} are used to decorate ConcreteComponent like Document_Impl.
    class NodeDecorator : public virtual Node
    {
    protected:
        Node* component;
    public:
        NodeDecorator(Node* component);
        virtual ~NodeDecorator();
        virtual Node* appendChild(Node* newChild);

        // Pure forwarding
        virtual const std::string& getNodeName(void) { return component->getNodeName(); }
        virtual const std::string& getNodeValue(void) { return component->getNodeValue(); }
        virtual void setNodeValue(const std::string& nodeValue) { return component->setNodeValue(nodeValue); }
        virtual short getNodeType(void) { return component->getNodeType(); }
        virtual Node* getParentNode(void) { return component->getParentNode(); }
        virtual void setParent(dom::Node* parent) { return component->setParent(parent); }
        virtual NodeList* getChildNodes(void) { return component->getChildNodes(); }
        virtual Node* getFirstChild(void) { return component->getFirstChild(); }
        virtual Node* getLastChild(void) { return component->getLastChild(); }
        virtual Node* getPreviousSibling(void) { return component->getPreviousSibling(); }
        virtual Node* getNextSibling(void) { return component->getNextSibling(); }
        virtual Document* getOwnerDocument(void) { return component->getOwnerDocument(); }
        virtual Node* insertBefore(Node* newChild, Node* refChild) { return component->insertBefore(newChild, refChild); }
        virtual Node* replaceChild(Node* newChild, Node* oldChild) { return component->replaceChild(newChild, oldChild); }
        virtual Node* removeChild(Node* oldChild) { return component->removeChild(oldChild); }
        virtual bool hasChildNodes(void) { return component->hasChildNodes(); }
        virtual const std::string& getLocalName(void) { return component->getLocalName(); }
        virtual void prettyIndentation(std::ostream* os, int indentationLevel = 0) { return component->prettyIndentation(os, indentationLevel); }
        virtual void serializeMinimal(std::ostream* os, int indentationLevel = 0) { return component->serializeMinimal(os, indentationLevel); }
        virtual void serializePretty(std::ostream* os, int indentationLevel = 0) { return component->serializePretty(os, indentationLevel); }
    };
};

// [Decorator pattern] ConcreteDecorator
//    - Add or Remove responsibilities from the Component object.
//    - Based on Decorator NodeDecorator for general conformance, it decorates ConcreteComponent like Document_Impl.
//    - This validates the target Element (tag/name) is allowed or the add action is cancelled.
class CanAddElementDocument : public virtual dom::NodeDecorator
{
private:
    std::set<std::string> validElementNames;
public:
    CanAddElementDocument(Node* component, std::set<std::string> validElementNames);
    virtual ~CanAddElementDocument();
    virtual dom::Node* appendChild(dom::Node* newChild);
    virtual bool canAddElement(std::string name);
};

// [Decorator pattern] ConcreteDecorator
//    - Add or Remove responsibilities from the Component object.
//    - Based on Decorator NodeDecorator for general conformance, it decorates ConcreteComponent like Document_Impl.
//    - This validates Text is allowed or the add action is cancelled.
class CanAddTextDocument : public virtual dom::NodeDecorator
{
private:
    bool isAllowed;
public:
    CanAddTextDocument(Node* component, bool isAllowed);
    virtual ~CanAddTextDocument();
    virtual dom::Node* appendChild(dom::Node* newChild);
    virtual bool canAddText(void);
};