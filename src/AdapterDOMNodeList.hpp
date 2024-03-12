#pragma once

#include "xerces/DOMNodeList.hpp"
#include "NodeList.H"

class AdapterDOMNodeList: public XERCES::DOMNodeList {
private:
    dom::NodeList* _nodeList;
public:
    AdapterDOMNodeList(dom::NodeList* nodeList) : _nodeList(nodeList) {}
    virtual void displayNodes()
    {
        printf("[Child Nodes]: ");
        for (auto itr = _nodeList->begin(); itr != _nodeList->end(); itr++)
        {
            printf("%s | ", (*itr)->getNodeValue().c_str());
        } printf("\n");
    }
};