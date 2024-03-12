#include "AdapterDOMDocument.hpp"

AdapterDOMDocument::AdapterDOMDocument() : AdapterDOMNode(new Document_Impl)
{
    _document = dynamic_cast<dom::Document*>(AdapterDOMNode::getNode());
}

// Functions from XERCES::DOMDocument

XERCES::DOMElement*         AdapterDOMDocument::createElement(const XERCES::XMLCh* tagName)
{
    return new AdapterDOMElement(_document->createElement(std::string(tagName)));
}

XERCES::DOMText*            AdapterDOMDocument::createTextNode(const XERCES::XMLCh* data)
{
    return new AdapterDOMText(_document->createTextNode(std::string(data)));
}

XERCES::DOMAttr*            AdapterDOMDocument::createAttribute(const XERCES::XMLCh* name)
{
    return new AdapterDOMAttr(_document->createAttribute(std::string(name)));
}

XERCES::DOMElement*         AdapterDOMDocument::getDocumentElement() const
{
    return new AdapterDOMElement(_document->getDocumentElement());
}