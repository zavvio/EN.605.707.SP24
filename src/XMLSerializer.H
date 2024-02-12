#pragma once
#include <string>
#include <iostream>

#include "Node.H"

// [Strategy pattern] Context
//   - This composition consists of two different type of Strategy
//   -   Node (for serialization of different content), with ConcreteStrategy {Document_Impl, Element_Impl, Attr_Impl, Text_Impl}
//   -      different algorithms for {serializeMinimal, serializePretty}
//   -   std::ostream (for different output medium), with ConcreteStrategy {iostream, ostringstream, ofstream}
//   -      different algorithms for writing to stream {operator<<}
//   - Context maintains reference to the two ConcreteStrategies, and defers interface calls to those customized algorithms.
class XMLSerializer
{
private:
    dom::Node* _node;   // [Strategy pattern] Strategy
    std::ostream* _os;  // [Strategy pattern] Strategy

public:
    XMLSerializer(dom::Node* node, std::ostream* os = &std::cout) : _node(node), _os(os) {}
    ~XMLSerializer() {}

    virtual void setNode(dom::Node* node) { _node = node; }
    virtual void setStream(std::ostream* os) { _os = os; }
    virtual void serializeMinimal();
    virtual void serializePretty();
};