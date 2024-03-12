#pragma once

#include "xerces/DOMAttr.hpp"
#include "AdapterDOMNode.hpp"
#include "Attr.H"

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
class AdapterDOMAttr : public virtual XERCES::DOMAttr, public AdapterDOMNode
{
protected:
private:
    dom::Attr* _node;
public:
    AdapterDOMAttr();
    AdapterDOMAttr(dom::Attr* node) : _node(node), AdapterDOMNode(node) {}
    virtual ~AdapterDOMAttr() {}
    virtual dom::Node* getNode() { return _node; }

    // Functions from XERCES::DOMNode

    virtual const XERCES::XMLCh*        getNodeName() const { return AdapterDOMNode::getNodeName(); }
    virtual const XERCES::XMLCh*        getNodeValue() const { return AdapterDOMNode::getNodeValue(); }
    virtual void                        setNodeValue(const XERCES::XMLCh* nodeValue) { return AdapterDOMNode::setNodeValue(nodeValue); }
    virtual XERCES::DOMNode::NodeType   getNodeType() const { return AdapterDOMNode::getNodeType(); }
    virtual XERCES::DOMNode*            getParentNode() const { return AdapterDOMNode::getParentNode(); }
    virtual XERCES::DOMNodeList*        getChildNodes() const { return AdapterDOMNode::getChildNodes(); }
    virtual XERCES::DOMNode*            getFirstChild() const { return AdapterDOMNode::getFirstChild(); }
    virtual XERCES::DOMNode*            getLastChild() const { return AdapterDOMNode::getLastChild(); }
    virtual XERCES::DOMNode*            getPreviousSibling() const { return AdapterDOMNode::getPreviousSibling(); }
    virtual XERCES::DOMNode*            getNextSibling() const { return AdapterDOMNode::getNextSibling(); }
    virtual XERCES::DOMDocument*        getOwnerDocument() const { return AdapterDOMNode::getOwnerDocument(); }
    virtual XERCES::DOMNode*            insertBefore(XERCES::DOMNode* newChild, XERCES::DOMNode* refChild) { return AdapterDOMNode::insertBefore(newChild, refChild); }
    virtual XERCES::DOMNode*            replaceChild(XERCES::DOMNode* newChild, XERCES::DOMNode* oldChild) { return AdapterDOMNode::replaceChild(newChild, oldChild); }
    virtual XERCES::DOMNode*            removeChild(XERCES::DOMNode* oldChild) { return AdapterDOMNode::removeChild(oldChild); }
    virtual XERCES::DOMNode*            appendChild(XERCES::DOMNode* newChild) { return AdapterDOMNode::appendChild(newChild); }
    virtual bool                        hasChildNodes() const { return AdapterDOMNode::hasChildNodes(); }
    virtual const XERCES::XMLCh*        getLocalName() const { return AdapterDOMNode::getLocalName(); }

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