#include "Document.H"
#include "Element.H"
#include "Text.H"
#include "Attr.H"
#include "NodeList.H"

Document_Impl::Document_Impl(void) : Node_Impl("", dom::Node::DOCUMENT_NODE)
{
    Node_Impl::document = this;
}

Document_Impl::~Document_Impl() {}

dom::Element* Document_Impl::createElement(const std::string& tagName)
{
    return new Element_Impl(tagName, this);
}

CanAddElementElement* Document_Impl::createValidatedElement(const std::string& tagName, std::set<std::string> validElementNames, std::set<std::string> validAttributeNames, bool isTextAllowed)
{
    return new CanAddElementElement(new CanAddTextElement(new CanAddAttributeElement(new Element_Impl(tagName, this), validAttributeNames), isTextAllowed), validElementNames);
}

dom::Text* Document_Impl::createTextNode(const std::string& data)
{
    return new Text_Impl(data, this);
}

dom::Attr* Document_Impl::createAttribute(const std::string& name)
{
    return new Attr_Impl(name, this);
}

dom::Node* Document_Impl::getDocumentElement()
{
    for (dom::NodeList::iterator i = getChildNodes()->begin(); i != getChildNodes()->end(); i++)
        /*if (dynamic_cast<dom::Element*>(*i.operator->()) != 0)
            return dynamic_cast<dom::Element*>(*i.operator->());*/
        if ((*i)->getNodeType() == ELEMENT_NODE)
            return *i;
    return 0;
}

void Document_Impl::serializeMinimal(std::ostream* os, int indentationLevel)
{
    (*os) << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
    this->getDocumentElement()->serializeMinimal(os, indentationLevel);
}

void Document_Impl::serializePretty(std::ostream* os, int indentationLevel)
{
    (*os) << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
    (*os) << "\n";
    this->getDocumentElement()->serializePretty(os, indentationLevel);
}