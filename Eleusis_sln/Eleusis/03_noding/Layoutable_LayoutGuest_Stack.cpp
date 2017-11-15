#include "Layoutable.h"

using namespace Eleusis;

void Layoutable::LayoutGuest::Stack::setMode()
{
    _target->_layoutGuest_layoutMode = LayoutMode::Stack;
    _target->_requestParentLayout();
}

void Layoutable::LayoutGuest::Stack::margin(Length top, Length left, Length bottom, Length right)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Stack;
    _target->_layoutGuest_StackWrap_Margin = { top, left, bottom, right };
    _target->_requestParentLayout();
}

void Layoutable::LayoutGuest::Stack::marginTop_set(Length top)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Stack;
    _target->_layoutGuest_StackWrap_Margin.Top = top;
    _target->_requestParentLayout();
}

Length Layoutable::LayoutGuest::Stack::marginTop_get()
{
    return _target->_layoutGuest_StackWrap_Margin.Top;
}

void Layoutable::LayoutGuest::Stack::marginLeft_set(Length left)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Stack;
    _target->_layoutGuest_StackWrap_Margin.Left = left;
    _target->_requestParentLayout();
}

Length Layoutable::LayoutGuest::Stack::marginLeft_get()
{
    return _target->_layoutGuest_StackWrap_Margin.Left;
}

void Layoutable::LayoutGuest::Stack::marginBottom_set(Length bottom)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Stack;
    _target->_layoutGuest_StackWrap_Margin.Bottom = bottom;
    _target->_requestParentLayout();
}

Length Layoutable::LayoutGuest::Stack::marginBottom_get()
{
    return _target->_layoutGuest_StackWrap_Margin.Bottom;
}

void Layoutable::LayoutGuest::Stack::marginRight_set(Length right)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Stack;
    _target->_layoutGuest_StackWrap_Margin.Right = right;
    _target->_requestParentLayout();
}

Length Layoutable::LayoutGuest::Stack::marginRight_get()
{
    return _target->_layoutGuest_StackWrap_Margin.Right;
}