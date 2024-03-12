#include "AdapterDOMNode.hpp"
#include "AdapterDOMNodeList.hpp"

// Functions from XERCES::DOMNode

const XERCES::XMLCh*        AdapterDOMNode::getNodeName() const
{
    return _node->getNodeName().c_str();
}

const XERCES::XMLCh*        AdapterDOMNode::getNodeValue() const
{
    return _node->getNodeValue().c_str();
}

void                        AdapterDOMNode::setNodeValue(const XERCES::XMLCh* nodeValue)
{
    _node->setNodeValue(std::string(nodeValue));
}

XERCES::DOMNode::NodeType   AdapterDOMNode::getNodeType() const
{
    short nodeType = _node->getNodeType();
    switch(nodeType)
    {
    case dom::Node::ATTRIBUTE_NODE:
        return XERCES::DOMNode::ATTRIBUTE_NODE;
    case dom::Node::DOCUMENT_NODE:
        return XERCES::DOMNode::DOCUMENT_NODE;
    case dom::Node::ELEMENT_NODE:
        return XERCES::DOMNode::ELEMENT_NODE;
    case dom::Node::TEXT_NODE:
        return XERCES::DOMNode::TEXT_NODE;
    default: // Shouldn't be this case for the dom framework
        return XERCES::DOMNode::DOCUMENT_NODE;
    }
}

XERCES::DOMNode*            AdapterDOMNode::getParentNode() const
{
    dom::Node* node = _node->getParentNode();
    if (node == nullptr)
        return nullptr;
    else
        return new AdapterDOMNode(node);
}

XERCES::DOMNodeList*        AdapterDOMNode::getChildNodes() const
{
    return new AdapterDOMNodeList(_node->getChildNodes());
}

XERCES::DOMNode*            AdapterDOMNode::getFirstChild() const
{
    dom::Node* node = _node->getFirstChild();
    if (node == nullptr)
        return nullptr;
    else
        return new AdapterDOMNode(node);
}

XERCES::DOMNode*            AdapterDOMNode::getLastChild() const
{
    dom::Node* node = _node->getLastChild();
    if (node == nullptr)
        return nullptr;
    else
        return new AdapterDOMNode(node);
}

XERCES::DOMNode*            AdapterDOMNode::getPreviousSibling() const
{
    dom::Node* node = _node->getPreviousSibling();
    if (node == nullptr)
        return nullptr;
    else
        return new AdapterDOMNode(node);
}

XERCES::DOMNode*            AdapterDOMNode::getNextSibling() const
{
    dom::Node* node = _node->getNextSibling();
    if (node == nullptr)
        return nullptr;
    else
        return new AdapterDOMNode(node);
}

XERCES::DOMDocument*        AdapterDOMNode::getOwnerDocument() const
{
    // dom::Document* node = _node->getOwnerDocument();
    // if (node == nullptr)
    //     return nullptr;
    // else
    //     return new AdapterDOMDocument(node);
    return nullptr;
}

XERCES::DOMNode*            AdapterDOMNode::insertBefore(XERCES::DOMNode* newChild, XERCES::DOMNode* refChild)
{
    if (dynamic_cast<AdapterDOMNode*>(newChild) == 0 || dynamic_cast<AdapterDOMNode*>(refChild) == 0)
    {
        // Shouldn't be given a real XERCES::DOMNode
        return nullptr;
    }
    AdapterDOMNode* newAdapter = dynamic_cast<AdapterDOMNode*>(newChild);
    AdapterDOMNode* refAdapter = dynamic_cast<AdapterDOMNode*>(refChild);
    dom::Node* newNode = newAdapter->getNode();
    dom::Node* refNode = refAdapter->getNode();
    _node->insertBefore(newNode, refNode);
    return newChild;
}

XERCES::DOMNode*            AdapterDOMNode::replaceChild(XERCES::DOMNode* newChild, XERCES::DOMNode* oldChild)
{
    if (dynamic_cast<AdapterDOMNode*>(newChild) == 0 || dynamic_cast<AdapterDOMNode*>(oldChild) == 0)
    {
        // Shouldn't be given a real XERCES::DOMNode
        return nullptr;
    }
    AdapterDOMNode* newAdapter = dynamic_cast<AdapterDOMNode*>(newChild);
    AdapterDOMNode* oldAdapter = dynamic_cast<AdapterDOMNode*>(oldChild);
    dom::Node* newNode = newAdapter->getNode();
    dom::Node* oldNode = oldAdapter->getNode();
    _node->replaceChild(newNode, oldNode);
    return oldChild;
}

XERCES::DOMNode*            AdapterDOMNode::removeChild(XERCES::DOMNode* oldChild)
{
    if (dynamic_cast<AdapterDOMNode*>(oldChild) != 0)
    {
        AdapterDOMNode* adapter = dynamic_cast<AdapterDOMNode*>(oldChild);
        dom::Node* childNode = adapter->getNode();
        _node->removeChild(childNode);
        return oldChild;
    }
    else
    {
        // Shouldn't be given a real XERCES::DOMNode
        return nullptr;
    }
}

XERCES::DOMNode*            AdapterDOMNode::appendChild(XERCES::DOMNode* newChild)
{
    if (dynamic_cast<AdapterDOMNode*>(newChild) != 0)
    {
        AdapterDOMNode* adapter = dynamic_cast<AdapterDOMNode*>(newChild);
        dom::Node* childNode = adapter->getNode();
        _node->appendChild(childNode);
        return newChild;
    }
    else
    {
        // Shouldn't be given a real XERCES::DOMNode
        return nullptr;
    }
}

bool                        AdapterDOMNode::hasChildNodes() const
{
    return _node->hasChildNodes();
}

const XERCES::XMLCh*        AdapterDOMNode::getLocalName() const
{
    return _node->getLocalName().c_str();
}