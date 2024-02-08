#include "ElementDecorator.H"
#include "Attr.H"
#include "Element.H"
#include "Text.H"

/// 
/// [Decorator pattern] Decorator
/// ElementDecorator
/// 
dom::ElementDecorator::ElementDecorator(Element* component) : component(component)
{
}

dom::ElementDecorator::~ElementDecorator()
{
}

void dom::ElementDecorator::setAttribute(const std::string& name, const std::string& value)
{
    return component->setAttribute(name, value);
}

dom::Attr* dom::ElementDecorator::setAttributeNode(Attr* newAttr)
{
    return component->setAttributeNode(newAttr);
}

dom::Node* dom::ElementDecorator::appendChild(Node* newChild)
{
    return component->appendChild(newChild);
}

CanAddAttributeElement::CanAddAttributeElement(Element* component, std::set<std::string> validAttributeNames) : ElementDecorator(component), validAttributeNames(validAttributeNames)
{
}

CanAddAttributeElement::~CanAddAttributeElement()
{
}

/// 
/// [Decorator pattern] ConcreteDecorator
/// CanAddAttributeElement
/// 
void CanAddAttributeElement::setAttribute(const std::string& name, const std::string& value)
{
    if (canAddAttribute(name))
        return component->setAttribute(name, value);
    std::cout << "\tUnable to add Attribute: " << name << std::endl;
    return;
}

dom::Attr* CanAddAttributeElement::setAttributeNode(dom::Attr* newAttr)
{
    if (newAttr->getNodeType() != ATTRIBUTE_NODE)
        return component->setAttributeNode(newAttr);
    else if (canAddAttribute(newAttr->getName()))
        return component->setAttributeNode(newAttr);
    std::cout << "\tUnable to add Attribute Node: " << newAttr->getName() << std::endl;
    return nullptr;
}

bool CanAddAttributeElement::canAddAttribute(std::string name)
{
    return (validAttributeNames.find(name) != validAttributeNames.end()) ? true : false;
}

/// 
/// [Decorator pattern] ConcreteDecorator
/// CanAddElementElement
/// 
CanAddElementElement::CanAddElementElement(Element* component, std::set<std::string> validElementNames) : ElementDecorator(component), validElementNames(validElementNames)
{
}

CanAddElementElement::~CanAddElementElement()
{
}

dom::Node* CanAddElementElement::appendChild(Node* newChild)
{
    if (newChild->getNodeType() != ELEMENT_NODE)
        return component->appendChild(newChild);
    else if (canAddElement(newChild->getNodeName()))
        return component->appendChild(newChild);
    std::cout << "\tUnable to add Element: " << newChild->getNodeName() << std::endl;
    return nullptr;
}

bool CanAddElementElement::canAddElement(std::string name)
{
    return (validElementNames.find(name) != validElementNames.end()) ? true : false;
}

/// 
/// [Decorator pattern] ConcreteDecorator
/// CanAddTextElement
/// 
CanAddTextElement::CanAddTextElement(Element* component, bool isAllowed) : ElementDecorator(component), isAllowed(isAllowed)
{
}

CanAddTextElement::~CanAddTextElement()
{
}

dom::Node* CanAddTextElement::appendChild(Node* newChild)
{
    if (newChild->getNodeType() != TEXT_NODE)
        return component->appendChild(newChild);
    else if (canAddText())
        return component->appendChild(newChild);
    std::cout << "\tUnable to add Text: " << newChild->getNodeValue() << std::endl;
    return nullptr;
}

bool CanAddTextElement::canAddText()
{
    return isAllowed ? true : false;
}