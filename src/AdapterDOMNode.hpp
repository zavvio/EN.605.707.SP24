#pragma once

#include "xerces/DOMNode.hpp"
#include "xerces/DOMNodeList.hpp"
#include "Node.H"
#include <stdio.h>

class AdapterDOMDocument;

//
// [Adapter Pattern] Adapter
// - This adapts the interface of Adaptee to the Target interface.
// - There are five independent Adapter implementations here:
//      - XERCES::DOMNode       <- AdapterDOMNode       -> dom::Node
//      - XERCES::DOMDocument   <- AdapterDOMDocument   -> dom::Document
//      - XERCES::DOMElement    <- AdapterDOMElement    -> dom::Element
//      - XERCES::DOMAttr       <- AdapterDOMAttr       -> dom::Attr
//      - XERCES::DOMText       <- AdapterDOMText       -> dom::Text
//
class AdapterDOMNode: public virtual XERCES::DOMNode {
protected:
private:
    dom::Node* _node;
public:
    AdapterDOMNode(dom::Node* node) : _node(node) {}
    virtual ~AdapterDOMNode() {};
    virtual dom::Node* getNode() { return _node; }
    void setNode(dom::Node* node) { _node = node; }

    // Functions from XERCES::DOMNode

    virtual const XERCES::XMLCh*        getNodeName() const;
    virtual const XERCES::XMLCh*        getNodeValue() const;
    virtual void                        setNodeValue(const XERCES::XMLCh* nodeValue);
    virtual XERCES::DOMNode::NodeType   getNodeType() const;
    virtual XERCES::DOMNode*            getParentNode() const;
    virtual XERCES::DOMNodeList*        getChildNodes() const;
    virtual XERCES::DOMNode*            getFirstChild() const;
    virtual XERCES::DOMNode*            getLastChild() const;
    virtual XERCES::DOMNode*            getPreviousSibling() const;
    virtual XERCES::DOMNode*            getNextSibling() const;
    virtual XERCES::DOMDocument*        getOwnerDocument() const;
    virtual XERCES::DOMNode*            insertBefore(XERCES::DOMNode* newChild, XERCES::DOMNode* refChild);
    virtual XERCES::DOMNode*            replaceChild(XERCES::DOMNode* newChild, XERCES::DOMNode* oldChild);
    virtual XERCES::DOMNode*            removeChild(XERCES::DOMNode* oldChild);
    virtual XERCES::DOMNode*            appendChild(XERCES::DOMNode* newChild);
    virtual bool                        hasChildNodes() const;
    virtual const XERCES::XMLCh*        getLocalName() const;

    // Stub functions from XERCES::DOMNode without equivalent implementation in DOM::Node

    virtual XERCES::DOMNamedNodeMap*    getAttributes() const { return nullptr; }
    virtual XERCES::DOMNode*            cloneNode(bool deep) const { return nullptr; }
    virtual void                        normalize() {}
    virtual bool                        isSupported(const XERCES::XMLCh* feature, const XERCES::XMLCh* version) const { return false; }
    virtual const XERCES::XMLCh*        getNamespaceURI() const { return nullptr; }
    virtual const XERCES::XMLCh*        getPrefix() const { return nullptr; }
    virtual void                        setPrefix(const XERCES::XMLCh* prefix) {}
    virtual bool                        hasAttributes() const { return false; }
    virtual bool                        isSameNode(const XERCES::DOMNode* other) const { return false; }
    virtual bool                        isEqualNode(const XERCES::DOMNode* arg) const { return false; }
    virtual void*                       setUserData(const XERCES::XMLCh* key, void* data, XERCES::DOMUserDataHandler* handler) { return nullptr; }
    virtual void*                       getUserData(const XERCES::XMLCh* key) const { return nullptr; }
    virtual const XERCES::XMLCh*        getBaseURI() const { return nullptr; }
    virtual short                       compareDocumentPosition(const XERCES::DOMNode* other) const { return 0; }
    virtual const XERCES::XMLCh*        getTextContent() const { return nullptr; }
    virtual void                        setTextContent(const XERCES::XMLCh* textContent) {}
    virtual const XERCES::XMLCh*        lookupPrefix(const XERCES::XMLCh* namespaceURI) const { return nullptr; }
    virtual bool                        isDefaultNamespace(const XERCES::XMLCh* namespaceURI) const { return false; }
    virtual const XERCES::XMLCh*        lookupNamespaceURI(const XERCES::XMLCh* prefix) const { return nullptr; }
    virtual void*                       getFeature(const XERCES::XMLCh* feature, const XERCES::XMLCh* version) const { return nullptr; }
    virtual void                        release() {}
};