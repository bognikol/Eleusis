#include "Layoutable.h"

using namespace Eleusis;

void Layoutable::LayoutGuest::Wrap::setMode()
{
    _target->_layoutGuest_layoutMode = LayoutMode::Wrap;
    _target->_requestParentLayout();
}

void Layoutable::LayoutGuest::Wrap::margin(Length top, Length left, Length bottom, Length right)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Wrap;
    _target->_layoutGuest_StackWrap_Margin = { top, left, bottom, right };
    _target->_requestParentLayout();
}

void Layoutable::LayoutGuest::Wrap::marginTop_set(Length top)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Wrap;
    _target->_layoutGuest_StackWrap_Margin.Top = top;
    _target->_requestParentLayout();
}

Length Layoutable::LayoutGuest::Wrap::marginTop_get()
{
    return _target->_layoutGuest_StackWrap_Margin.Top;
}

void Layoutable::LayoutGuest::Wrap::marginLeft_set(Length left)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Wrap;
    _target->_layoutGuest_StackWrap_Margin.Left = left;
    _target->_requestParentLayout();
}

Length Layoutable::LayoutGuest::Wrap::marginLeft_get()
{
    return _target->_layoutGuest_StackWrap_Margin.Left;
}

void Layoutable::LayoutGuest::Wrap::marginBottom_set(Length bottom)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Wrap;
    _target->_layoutGuest_StackWrap_Margin.Bottom = bottom;
    _target->_requestParentLayout();
}

Length Layoutable::LayoutGuest::Wrap::marginBottom_get()
{
    return _target->_layoutGuest_StackWrap_Margin.Bottom;
}

void Layoutable::LayoutGuest::Wrap::marginRight_set(Length right)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Wrap;
    _target->_layoutGuest_StackWrap_Margin.Right = right;
    _target->_requestParentLayout();
}

Length Layoutable::LayoutGuest::Wrap::marginRight_get()
{
    return _target->_layoutGuest_StackWrap_Margin.Right;
}