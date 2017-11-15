#include "Container.h"
#include "VisualPrimitive.h"

using namespace Eleusis;
using namespace std;

Container::Container(Length width, Length height)
{
    if (width < 0)  width = 0;
    _width = width;
    if (height < 0) height = 0;
    _height = height;

    _requestLayout();
}

void Container::width_set(Length width)
{
    if (width < 0)  width = 0;
    _width = width;

    _requestLayout();
}

void Container::height_set(Length height)
{
    if (height < 0) height = 0;
    _height = height;

    _requestLayout();
}

void Container::setWidthAndHeight(Length width, Length height)
{
    if (width < 0)  width = 0;
    _width = width;
    if (height < 0) height = 0;
    _height = height;

    _requestLayout();
}

void Container::clipping_set(bool clipping)
{
    if (_clipping != clipping) _clipping = clipping;

    _requestLayout();
}

Rect Container::getFullExtent()
{
    Rect l_fullExtent;

    Node* l_child = firstChild();

    Rect l_childFullExtent;

    while (true)
    {
        if (!l_child) break;

        l_childFullExtent = l_child->getFullExtent();
        if (!l_childFullExtent.isZero())
        {
            if (l_fullExtent.isZero())
                l_fullExtent = l_child->getFullExtent();
            else
                l_fullExtent |= l_child->getFullExtent();
        }

        l_child = l_child->nextSibling();
    }

    return l_fullExtent;
}

void Container::_updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector)
{
    Vector l_absoluteSizeVector = 
    { 
        _width.getValueRelativeTo(parentAbsoluteSizeVector.X), 
        _height.getValueRelativeTo(parentAbsoluteSizeVector.Y) 
    };

    if (l_absoluteSizeVector != _absoluteSizeVector) *changed = true;
    else *changed = false;

    _absoluteSizeVector = l_absoluteSizeVector;
}