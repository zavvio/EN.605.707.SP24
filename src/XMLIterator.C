#include "XMLIterator.H"
#include "Document.H"

XMLIterator::XMLIterator()
{
    return;
}

NodeIterator::NodeIterator(dom::Node* root) :
    _root(root), _currentChild(nullptr), _done(false), _state(0),
    _currentChildItr(_root->getChildNodes()->begin()),
    _grandChildrenItr(nullptr), _grandChildren(nullptr), _currentGrandChild(nullptr)
{
}

void NodeIterator::first()
{
    _currentChild = _root;
    _done = false;
    _state = 0;
    _currentChildItr = _root->getChildNodes()->begin();
    _grandChildrenItr = nullptr;
    _grandChildren = nullptr;
    _currentGrandChild = nullptr;
}

dom::Node* NodeIterator::next()
{
    dom::Node* closingTag = nullptr;
    switch (_state)
    {
    case 0: // this
        if (_root->hasChildNodes())
        {
            _state = 1;
            _currentChildItr = _root->getChildNodes()->begin();
            _currentChild = *(_currentChildItr);
            if (_currentChild->hasChildNodes())
            {
                _state = 2;
                _grandChildrenItr = _currentChild->createIterator();
                _grandChildrenItr->first();
                _currentGrandChild = _grandChildrenItr->currentItem();
            }
        }
        else
        {
            _done = true;
        }
        break;
    case 1: // children
        _currentChildItr++;
        if (_currentChildItr == _root->getChildNodes()->end())
        {
            _done = true;
        }
        else
        {
            _currentChild = *(_currentChildItr);
            if (_currentChild->hasChildNodes())
            {
                _state = 2;
                _grandChildrenItr = _currentChild->createIterator();
                _grandChildrenItr->first();
                _currentGrandChild = _grandChildrenItr->currentItem();
            }
        }
        break;
    case 2: // grand children
        closingTag = _grandChildrenItr->next();
        if (_grandChildrenItr->isDone())
        {
            delete _grandChildrenItr;
            closingTag = _currentChild;
            _state = 1;
            // same as state 1 below
            _currentChildItr++;
            if (_currentChildItr == _root->getChildNodes()->end())
            {
                _done = true;
            }
            else
            {
                _currentChild = *(_currentChildItr);
                if (_currentChild->hasChildNodes())
                {
                    _state = 2;
                    _grandChildrenItr = _currentChild->createIterator();
                    _grandChildrenItr->first();
                    _currentGrandChild = _grandChildrenItr->currentItem();
                }
            }
        }
        else
        {
            _currentGrandChild = _grandChildrenItr->currentItem();
        }
        break;
    default:
        break;
    }
    return closingTag;
}

dom::Node* NodeIterator::currentItem()
{
    if (isDone()) return nullptr;

    switch (_state)
    {
    case 0: // this
        return _root;
    case 1: // children
        return _currentChild;
    case 2: // grand children
        return _currentGrandChild;
    default:
            return nullptr;
    }
}

bool NodeIterator::isDone()
{
    return _done;
}