#include "XMLBuilder.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

NodeXMLBuilder::NodeXMLBuilder() : _currentDOM(nullptr)
{
}

void MinimalNodeXMLBuilder::BuildDocument()
{
    if (_currentDOM == nullptr)
        _currentDOM = new Document_Impl;
}

void PrettyNodeXMLBuilder::BuildDocument()
{
    if (_currentDOM == nullptr)
        _currentDOM = new PrettyDocument_Impl;
}

void NodeXMLBuilder::BuildElement(const std::string& tagName)
{
    dom::Element* element = _currentDOM->createElement(tagName);
    if (hierarchyProbe.size() == 0)
        _currentDOM->appendChild(element);
    else
    {
        hierarchyProbe.top()->appendChild(element);
    }
    hierarchyProbe.push(element);
}

void NodeXMLBuilder::BuildAttribute(const std::string& name, const std::string& value)
{
    // dom::Attr* attr = _currentDOM->createAttribute(name);
    if (hierarchyProbe.size() != 0)
    {
        hierarchyProbe.top()->setAttribute(name, value);
    }
    // Silently ignored if trying to build Attr when there is no Element.
}

void NodeXMLBuilder::BuildText(const std::string& data)
{
    dom::Text* text = _currentDOM->createTextNode(data);
    if (hierarchyProbe.size() != 0)
    {
        hierarchyProbe.top()->appendChild(text);
    }
    // Silently ignored if trying to build Text when there is no Element.
}

void NodeXMLBuilder::popProbe()
{
    if (!hierarchyProbe.empty())
        hierarchyProbe.pop();
}