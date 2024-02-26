#ifndef BUILDER_H
#define BUILDER_H

#include <stack>
#include <string>

namespace dom
{
    class Document;
    class Element;
    class Attr;
};

class Director;

class Builder
{
private:
    static dom::Document* factory;
    static dom::Element* currentElement;
    static dom::Element* parentElement;
    dom::Attr* currentAttr;

    virtual const std::string	trim(const std::string & s) const;
public:
    Builder(dom::Document* _factory);

    virtual dom::Document *	getDocument(void)	{ return factory; }	// aka getResult

    virtual void		addValue(const std::string & text);
    virtual void		confirmElement(const std::string & tag);
    virtual void		createAttribute(const std::string & attribute);
    virtual void		valueAttribute(const std::string & value);
    virtual void		createElement(const std::string& tag);
    virtual void		createProlog(void);
    virtual void		endProlog(void);
    virtual void		identifyProlog(const std::string & id);
    virtual void setDocumentUnderConstruction(dom::Document* newDocument) { factory = newDocument; }
    virtual void setCurrentElement(dom::Element* currElement) { currentElement = currElement; }
    virtual void setParentElement(dom::Element* parentElm) { parentElement = parentElm; }
    virtual dom::Element* getParentElement() { return parentElement; }
    virtual void setElementAsInitialized();
    virtual void setElementInitPoint(std::streampos pos);
    virtual void setDirector(Director* director);
};

#endif // BUILDER_H
