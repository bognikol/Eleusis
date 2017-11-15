#include "RootNode.h"

using namespace Eleusis;


void RootNode::setContext(UIContext* uiContext)
{
    _uiContext = uiContext;

    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_obtainContext();
        l_nextChild = l_nextChild->nextSibling();
    }
}

void RootNode::_layout()
{
    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_layout();
        l_nextChild = l_nextChild->nextSibling();
    }
}

void RootNode::_render(Region* region)
{
    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_render(region);
        l_nextChild = l_nextChild->nextSibling();
    }
}

void RootNode::_applyAbsoluteOffset()
{
    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_applyAbsoluteOffset();
        l_nextChild = l_nextChild->nextSibling();
    }
}

Rect RootNode::getFullExtent() 
{
    Rect l_extent;

    Node* l_child = firstChild();
    if (!l_child) return Rect();

    while (true)
    {
        l_extent |= l_child->getFullExtent();
        l_child = l_child->nextSibling();
        if (!l_child) break;
    }

    return l_extent;
}