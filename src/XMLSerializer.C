#include "XMLSerializer.H"

#include <iostream>

#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

void XMLSerializer::serializePretty(dom::Node * node)
{
	WhitespaceStrategy *	ws	= new PrettyWhitespaceStrategy;
	// node->serialize(file, ws);

	NodeIterator* nIt = node->createIterator();
	dom::Node* closingTag = nullptr;
	for(nIt->first(); !nIt->isDone(); closingTag = nIt->next())
	{
		if (closingTag != nullptr)
		{
			closingTag->serialize_end(file, ws);
			closingTag = nullptr;
		}
		nIt->currentItem()->serialize(file, ws);
	}
	if (closingTag != nullptr)
	{
		closingTag->serialize_end(file, ws);
	}
	delete ws;
}

void XMLSerializer::serializeMinimal(dom::Node * node)
{
	WhitespaceStrategy *	ws	= new MinimalWhitespaceStrategy;
	// node->serialize(file, ws);

	NodeIterator* nIt = node->createIterator();
	dom::Node* closingTag = nullptr;
	for (nIt->first(); !nIt->isDone(); closingTag = nIt->next())
	{
		if (closingTag != nullptr)
		{
			closingTag->serialize_end(file, ws);
			closingTag = nullptr;
		}
		nIt->currentItem()->serialize(file, ws);
	}
	if (closingTag != nullptr)
	{
		closingTag->serialize_end(file, ws);
	}
	delete ws;
}
