#include "Control.h"
#include "VisualPrimitive.h"

using namespace Eleusis;

void Control::_render() 
{
    if (!_uiContext) return;

    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_render();
        l_nextChild = l_nextChild->nextSibling();
    }
}

void Control::_render(Region* region)
{
    if (!region)     return;
    if (!_uiContext) return;

    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_render(region);
        l_nextChild = l_nextChild->nextSibling();
    }
}

Rect Control::getFullExtent() 
{
    Rect l_fullExtent = Rect();

    Node* l_child = firstChild();
    if (!l_child) return l_fullExtent;

    Node* l_lastDescendant = lastDescendant();

    while (true)
    {
        if (l_child->isVisualPrimitive())
            if (l_fullExtent.isZero())
                l_fullExtent = static_cast<VisualPrimitive*>(l_child)->getExtent();
            else
                l_fullExtent |= static_cast<VisualPrimitive*>(l_child)->getExtent();
        if (l_child == l_lastDescendant) break;
        l_child = l_child->next();
    }

    return l_fullExtent;
}
