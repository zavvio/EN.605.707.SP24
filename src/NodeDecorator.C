#include "NodeDecorator.H"
#include <iostream>

/// 
/// [Decorator pattern] Decorator
/// NodeDecorator
/// 
dom::NodeDecorator::NodeDecorator(Node* component) : component(component)
{
}

dom::NodeDecorator::~NodeDecorator()
{
}

dom::Node* dom::NodeDecorator::appendChild(Node* newChild)
{
    return component->appendChild(newChild);
}

/// 
/// [Decorator pattern] ConcreteDecorator
/// CanAddElementDocument
/// 
CanAddElementDocument::CanAddElementDocument(Node* component, std::set<std::string> validElementNames) : NodeDecorator(component), validElementNames(validElementNames)
{
}

CanAddElementDocument::~CanAddElementDocument()
{
}

dom::Node* CanAddElementDocument::appendChild(Node* newChild)
{
    if (newChild->getNodeType() != ELEMENT_NODE)
        return component->appendChild(newChild);
    else if (canAddElement(newChild->getNodeName()))
        return component->appendChild(newChild);
    std::cout << "\tUnable to add Element: " << newChild->getNodeName() << std::endl;
    return nullptr;
}

bool CanAddElementDocument::canAddElement(std::string name)
{
    return (validElementNames.find(name) != validElementNames.end()) ? true : false;
}

/// 
/// [Decorator pattern] ConcreteDecorator
/// CanAddTextDocument
///
CanAddTextDocument::CanAddTextDocument(Node* component, bool isAllowed) : NodeDecorator(component), isAllowed(isAllowed)
{
}

CanAddTextDocument::~CanAddTextDocument()
{
}

dom::Node* CanAddTextDocument::appendChild(Node* newChild)
{
    if (newChild->getNodeType() != TEXT_NODE)
        return component->appendChild(newChild);
    else if (canAddText())
        return component->appendChild(newChild);
    std::cout << "\tUnable to add Text: " << newChild->getNodeValue() << std::endl;
    return nullptr;
}

bool CanAddTextDocument::canAddText()
{
    return isAllowed ? true : false;
}