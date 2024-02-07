#include "XMLSerializer.H"

void XMLSerializer::serializeMinimal()
{
    _node->serializeMinimal(_os);
}

void XMLSerializer::serializePretty()
{
    _node->serializePretty(_os);
}