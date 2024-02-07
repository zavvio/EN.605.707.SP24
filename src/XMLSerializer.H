#pragma once
#include <string>
#include <iostream>

#include "Node.H"

class XMLSerializer
{
private:
    dom::Node* _node;
    std::ostream* _os;

public:
    XMLSerializer(dom::Node* node, std::ostream* os = &std::cout) : _node(node), _os(os) {}
    ~XMLSerializer() {}

    virtual void setNode(dom::Node* node) { _node = node; }
    virtual void setStream(std::ostream* os) { _os = os; }
    virtual void serializeMinimal();
    virtual void serializePretty();
};