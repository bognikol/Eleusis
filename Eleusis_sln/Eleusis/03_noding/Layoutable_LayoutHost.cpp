#include "Layoutable.h"

using namespace Eleusis;

void Layoutable::LayoutHost::padding(Length top, Length left, Length bottom, Length right)
{
    _target->_layoutHost_Padding = { top, left, bottom, right };
    _target->_requestLayout();
}

void Layoutable::LayoutHost::paddingTop_set(Length top)
{
    _target->_layoutHost_Padding.Top = top;
    _target->_requestLayout();
}

Length Layoutable::LayoutHost::paddingTop_get()
{
    return _target->_layoutHost_Padding.Top;
}

void Layoutable::LayoutHost::paddingLeft_set(Length left)
{
    _target->_layoutHost_Padding.Left = left;
    _target->_requestLayout();
}

Length Layoutable::LayoutHost::paddingLeft_get()
{
    return _target->_layoutHost_Padding.Left;
}

void Layoutable::LayoutHost::paddingBottom_set(Length bottom)
{
    _target->_layoutHost_Padding.Bottom = bottom;
    _target->_requestLayout();
}

Length Layoutable::LayoutHost::paddingBottom_get()
{
    return _target->_layoutHost_Padding.Bottom;
}

void Layoutable::LayoutHost::paddingRight_set(Length right)
{
    _target->_layoutHost_Padding.Right = right;
    _target->_requestLayout();
}

Length Layoutable::LayoutHost::paddingRight_get()
{
    return _target->_layoutHost_Padding.Right;
}

void Layoutable::LayoutHost::stackOrientation_set(LayoutOrientation orientation)
{
    _target->_layoutHost_Stack_Orientation = orientation;
    _target->_requestLayout();
}

LayoutOrientation Layoutable::LayoutHost::stackOrientation_get()
{
    return _target->_layoutHost_Stack_Orientation;
}

void Layoutable::LayoutHost::stackAlignment_set(LayoutAlignment alignment)
{
    _target->_layoutHost_Stack_Alignment = alignment;
    _target->_requestLayout();
}

LayoutAlignment Layoutable::LayoutHost::stackAlignment_get()
{
    return _target->_layoutHost_Stack_Alignment;
}

void Layoutable::LayoutHost::wrapOrientation_set(LayoutOrientation orientation)
{
    _target->_layoutHost_Wrap_Orientation = orientation;
    _target->_requestLayout();
}

LayoutOrientation Layoutable::LayoutHost::wrapOrientation_get()
{
    return _target->_layoutHost_Wrap_Orientation;

}

