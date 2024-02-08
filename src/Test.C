#include <iostream>
#include <sstream>
#include <stdio.h>
#include "Node.H"
#include "Attr.H"
#include "Document.H"
#include "Element.H"
#include "Text.H"
#include "NodeDecorator.H"
#include "XMLTokenizer.H"
#include "XMLSerializer.H"
#include "XMLValidator.H"

void testTokenizer(int argc, char** argv);
void testSerializer(int argc, char** argv);
void testValidator(int argc, char** argv);
void testDecorator(int argc, char** argv);

void printUsage(void)
{
    printf("Usage:\n");
    printf("\tTest t [file] ...\n");
    printf("\tTest s [file1] [file2]\n");
    printf("\tTest v [file]\n");
    printf("\tTest d [file]\n");
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printUsage();
        exit(0);
    }

    switch (argv[1][0])
    {
    case 'T':
    case 't':
        testTokenizer(argc, argv);
        break;
    case 'S':
    case 's':
        testSerializer(argc, argv);
        break;
    case 'V':
    case 'v':
        testValidator(argc, argv);
        break;
    case 'D':
    case 'd':
        testDecorator(argc, argv);
        break;
    }
}

void testTokenizer(int argc, char** argv)
{
    dom::Document* document = new Document_Impl();

    dom::Element* element = document->createElement("NewElement");
    dom::Text* text = document->createTextNode("Text Data");
    dom::Attr* attr = document->createAttribute("NewAttribute");

    printf("Element Tag = '%s'\n", element->getTagName().c_str());
    printf("Text Data = '%s'\n", text->getValue().c_str());
    printf("Attr Name = '%s'\n", attr->getName().c_str());

    element->setAttributeNode(attr);
    printf("Element attribute '%s'='%s'\n", element->getTagName().c_str(), element->getAttribute("NewAttribute").c_str());

    delete element;
    delete text;
    delete attr;
    delete document;

    for (int i = 2; i < argc; i++)
    {
        XMLTokenizer tokenizer(argv[i]);

        XMLTokenizer::XMLToken* token = 0;

        printf("File:  '%s'\n", argv[i]);

        do
        {
            delete token;
            token = tokenizer.getNextToken();

            printf("\tLine %d:  %s = '%s'\n", tokenizer.getLineNumber(),
                token->toString(), token->getToken().size() == 0 ? "" : token->getToken().c_str());

        } while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);

        delete token;
    }
}

void testSerializer(int argc, char** argv)
{
    if (argc < 4)
    {
        printUsage();
        exit(0);
    }

    //
    // Create tree of this document:
    // <? xml version="1.0" encoding="UTF-8"?>
    // <document>
    //   <element attribute="attribute value"/>
    //   <element/>
    //   <element attribute="attribute value" attribute2="attribute2 value">
    //     Element Value
    //   </element>
    //   <element>
    //   </element>
    // </document>
    //
    dom::Document* document = new Document_Impl();
    dom::Element* root = document->createElement("document");
    document->appendChild(root);

    dom::Element* child = document->createElement("element");
    dom::Attr* attr = document->createAttribute("attribute");
    attr->setValue("attribute value");
    child->setAttributeNode(attr);
    root->appendChild(child);

    child = document->createElement("element");
    root->appendChild(child);

    child = document->createElement("element");
    child->setAttribute("attribute", "attribute value");
    child->setAttribute("attribute2", "attribute2 value");
    dom::Text* text = document->createTextNode("Element Value");
    child->appendChild(text);
    root->appendChild(child);

    child = document->createElement("element");
    root->appendChild(child);

    //
    // Serialize
    //
    std::ofstream fout(argv[2], std::ios_base::out);
    std::ofstream fout2(argv[3], std::ios_base::out);
    std::ostringstream sout(std::ostringstream::ate); // "ate" appends to the end of stream
    XMLSerializer xmlSerializer(document, &fout);
    std::cout << "### Serialize to ofstream: " << argv[2] << std::endl;
    xmlSerializer.serializePretty();
    std::cout << "### Serialize to stdout:" << std::endl;
    xmlSerializer.setStream(&std::cout);
    xmlSerializer.serializePretty();
    std::cout << std::endl << "### Serialize to stringstream, which contains:" << std::endl;
    xmlSerializer.setStream(&sout);
    xmlSerializer.serializePretty();
    std::cout << sout.str() << std::endl << std::endl;
    std::cout << "### Serialize to ofstream: " << argv[3] << std::endl;
    xmlSerializer.setStream(&fout2);
    xmlSerializer.serializeMinimal();

    // delete Document and tree.
}

void testValidator(int argc, char** argv)
{
    if (argc < 3)
    {
        printUsage();
        exit(0);
    }

    //
    // Create tree of this document:
    // <? xml version="1.0" encoding="UTF-8"?>
    // <document>
    //   <element attribute="attribute value"/>
    //   <element/>
    //   <element attribute="attribute value" attribute2="attribute2 value">
    //     Element Value
    //   </element>
    //   <element>
    //   </element>
    // </document>
    //
    // Schema for this document:
    // document contains:  element
    // element contains:  element
    // element contains attributes:  attribute, attribute2
    //
    XMLValidator xmlValidator;
    ValidChildren* schemaElement = xmlValidator.addSchemaElement("");
    schemaElement->addValidChild("document", false);
    schemaElement = xmlValidator.addSchemaElement("document");
    schemaElement->addValidChild("element", false);
    schemaElement = xmlValidator.addSchemaElement("element");
    schemaElement->addValidChild("element", false);
    schemaElement->addValidChild("attribute", true);
    schemaElement->addValidChild("attribute2", true);
    schemaElement->setCanHaveText(true);

    dom::Document* document = new Document_Impl;
    dom::Element* root = 0;
    dom::Element* child = 0;
    dom::Attr* attr = 0;

    if (xmlValidator.canRootElement("document"))
    {
        root = document->createElement("document");
        document->appendChild(root);
    }
    else
    {
        printf("Attempted invalid schema operation.");
        exit(0);
    }

    if (xmlValidator.canAddElement(root, "element"))
    {
        child = document->createElement("element");

        if (xmlValidator.canAddAttribute(child, "attribute"))
        {
            attr = document->createAttribute("attribute");
            attr->setValue("attribute value");
            child->setAttributeNode(attr);
        }
        else
        {
            printf("Attempted invalid schema operation.");
            exit(0);
        }

        root->appendChild(child);
    }
    else
    {
        printf("Attempted invalid schema operation.");
        exit(0);
    }

    if (xmlValidator.canAddElement(root, "element"))
    {
        child = document->createElement("element");
        root->appendChild(child);
    }
    else
    {
        printf("Attempted invalid schema operation.");
        exit(0);
    }

    if (xmlValidator.canAddElement(root, "element"))
    {
        child = document->createElement("element");

        if (xmlValidator.canAddAttribute(child, "attribute"))
            child->setAttribute("attribute", "attribute value");
        else
        {
            printf("Attempted invalid schema operation.");
            exit(0);
        }

        if (xmlValidator.canAddAttribute(child, "attribute2"))
            child->setAttribute("attribute2", "attribute2 value");
        else
        {
            printf("Attempted invalid schema operation.");
            exit(0);
        }

        if (xmlValidator.canAddText(child))
        {
            dom::Text* text = document->createTextNode("Element Value");
            child->appendChild(text);
        }
        else
        {
            printf("Attempted invalid schema operation.");
            exit(0);
        }

        root->appendChild(child);
    }
    else
    {
        printf("Attempted invalid schema operation.");
        exit(0);
    }

    if (xmlValidator.canAddElement(root, "element"))
    {
        child = document->createElement("element");
        root->appendChild(child);
    }
    else
    {
        printf("Attempted invalid schema operation.");
        exit(0);
    }

    //
    // Serialize
    //
    std::ofstream fout(argv[2], std::ios_base::out);
    XMLSerializer xmlSerializer(document, &fout);
    xmlSerializer.serializePretty();

    // delete Document and tree.
}

void testDecorator(int argc, char** argv)
{
    if (argc < 3)
    {
        printUsage();
        exit(0);
    }
    dom::Document* document = new Document_Impl();
    CanAddElementDocument* rootDocument = new CanAddElementDocument(new CanAddTextDocument(document, false), std::set<std::string>({ "document" }));
    dom::Element* invalidElement = document->createElement("invalidElementName");
    printf("Attempt to add invalid Element to Document...\n");
    rootDocument->appendChild(invalidElement);

    CanAddElementElement* documentElement = document->createValidatedElement("document", std::set<std::string>({ "element" }), std::set<std::string>({}), false);
    rootDocument->appendChild(documentElement);
    printf("Attempt to insert invalid Element to Element...\n");
    documentElement->appendChild(invalidElement);
    documentElement->appendChild(document->createElement("element"));

    dom::Text* text = document->createTextNode("Hello World");
    printf("Attempt to add Text to Element which does not allow it...\n");
    documentElement->appendChild(text);
    printf("Attempt to add invalid Attribute to Element...\n");
    documentElement->setAttribute("invalidAttribute", "invalidAttributeValue");
    dom::Attr* invalidAttr = document->createAttribute("invalidAttribute2");
    invalidAttr->setValue("invalid attribute2 value");
    printf("Attempt to add invalid Attribute Node to Element...\n");
    documentElement->setAttributeNode(invalidAttr);

    CanAddElementElement* canTextAttrElement = document->createValidatedElement("element", std::set<std::string>({}), std::set<std::string>({ "attribute", "attribute2" }), true);
    canTextAttrElement->appendChild(text);
    canTextAttrElement->setAttribute("attribute", "valid attribute value");
    dom::Attr* attr = document->createAttribute("attribute2");
    attr->setValue("valid attribute2 value");
    canTextAttrElement->setAttributeNode(attr);
    documentElement->appendChild(canTextAttrElement);

    printf("\n===== Serializing =====\n");
    XMLSerializer xmlSerializer(documentElement);
    xmlSerializer.serializePretty();
}