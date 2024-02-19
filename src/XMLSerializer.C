#include "XMLSerializer.H"

#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

void XMLSerializer::serializePretty(dom::Node * node)
{
	WhitespaceStrategy *	ws	= new PrettyWhitespaceStrategy;
	node->serialize(file, 0);
	delete ws;
}

void XMLSerializer::serializeMinimal(dom::Node * node)
{
	WhitespaceStrategy *	ws	= new MinimalWhitespaceStrategy;
	node->serialize(file, 0);
	delete ws;
}
