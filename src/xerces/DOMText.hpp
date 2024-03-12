#pragma once

#include "DOMNode.hpp"

namespace XERCES
{
    //
    // [Adapter Pattern] Target
    // - This defines the domain-specific interface that Client uses.
    // - There are five independent Adapter implementations here:
    //      - XERCES::DOMNode       <- AdapterDOMNode       -> dom::Node
    //      - XERCES::DOMDocument   <- AdapterDOMDocument   -> dom::Document
    //      - XERCES::DOMElement    <- AdapterDOMElement    -> dom::Element
    //      - XERCES::DOMAttr       <- AdapterDOMAttr       -> dom::Attr
    //      - XERCES::DOMText       <- AdapterDOMText       -> dom::Text
    //
    class  DOMText: public DOMNode {
    protected:
        DOMText() {};
    private:
    public:
        virtual ~DOMText() {};
    };
}; // namespace XERCES