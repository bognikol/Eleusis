#include "Layoutable.h"

using namespace Eleusis;

void Layoutable::LayoutGuest::Classic::setMode()
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_requestParentLayout();
}

void Layoutable::LayoutGuest::Classic::position_set(Length vertical, Length horizontal)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_Position.Y = vertical;
    _target->_layoutGuest_Classic_Position.X = horizontal;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::positionVertical_set(Length vertical)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_Position.Y = vertical;
    _target->_requestLayout();
}

Length Layoutable::LayoutGuest::Classic::positionVertical_get()
{
    return _target->_layoutGuest_Classic_Position.Y;
}

void Layoutable::LayoutGuest::Classic::positionHorizontal_set(Length horizontal)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_Position.X = horizontal;
    _target->_requestLayout();
}

Length Layoutable::LayoutGuest::Classic::positionHorizontal_get()
{
    return _target->_layoutGuest_Classic_Position.X;
}

void Layoutable::LayoutGuest::Classic::positionReferentSystem_set(ReferentSystem system)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_ReferentSystem = system;
    _target->_requestLayout();
}

ReferentSystem Layoutable::LayoutGuest::Classic::positionReferentSystem_get()
{
    return _target->_layoutGuest_Classic_ReferentSystem;
}

void Layoutable::LayoutGuest::Classic::anchorPosition_set(Length vertical, Length horizontal)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorPosition.Y = vertical;
    _target->_layoutGuest_Classic_AnchorPosition.X = horizontal;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::anchorPositionVertical_set(Length vertical)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorPosition.Y = vertical;
    _target->_requestLayout();
}

Length Layoutable::LayoutGuest::Classic::anchorPositionVertical_get()
{
    return _target->_layoutGuest_Classic_AnchorPosition.Y;
}

void Layoutable::LayoutGuest::Classic::anchorPositionHorizontal_set(Length horizontal)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorPosition.X = horizontal;
    _target->_requestLayout();
}
Length Layoutable::LayoutGuest::Classic::anchorPositionHorizontal_get()
{
    return _target->_layoutGuest_Classic_AnchorPosition.X;
}

void Layoutable::LayoutGuest::Classic::anchorPositionReferentSystem_set(ReferentSystem system)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorReferentSystem = system;
    _target->_requestLayout();
}

ReferentSystem Layoutable::LayoutGuest::Classic::anchorPositionReferentSystem_get()
{
    return _target->_layoutGuest_Classic_AnchorReferentSystem;
}

void Layoutable::LayoutGuest::Classic::topLeft(Length top, Length left)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_Position.Y = top;
    _target->_layoutGuest_Classic_Position.X = left;
    _target->_layoutGuest_Classic_ReferentSystem = ReferentSystem::TopLeft;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::topRight(Length top, Length right)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_Position.Y = top;
    _target->_layoutGuest_Classic_Position.X = right;
    _target->_layoutGuest_Classic_ReferentSystem = ReferentSystem::TopRight;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::bottomLeft(Length bottom, Length left)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_Position.Y = bottom;
    _target->_layoutGuest_Classic_Position.X = left;
    _target->_layoutGuest_Classic_ReferentSystem = ReferentSystem::BottomLeft;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::bottomRight(Length bottom, Length right)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_Position.Y = bottom;
    _target->_layoutGuest_Classic_Position.X = right;
    _target->_layoutGuest_Classic_ReferentSystem = ReferentSystem::BottomRight;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::top(Length top)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_Position.Y = top;
    if (_target->_layoutGuest_Classic_ReferentSystem == ReferentSystem::BottomLeft)       _target->_layoutGuest_Classic_ReferentSystem = ReferentSystem::TopLeft;
    else if (_target->_layoutGuest_Classic_ReferentSystem == ReferentSystem::BottomRight) _target->_layoutGuest_Classic_ReferentSystem = ReferentSystem::TopRight;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::left(Length left)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_Position.X = left;
    if      (_target->_layoutGuest_Classic_ReferentSystem == ReferentSystem::TopRight)         
             _target->_layoutGuest_Classic_ReferentSystem =  ReferentSystem::TopLeft;
    else if (_target->_layoutGuest_Classic_ReferentSystem == ReferentSystem::BottomRight) 
             _target->_layoutGuest_Classic_ReferentSystem =  ReferentSystem::BottomLeft;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::bottom(Length bottom)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_Position.Y = bottom;
    if      (_target->_layoutGuest_Classic_ReferentSystem == ReferentSystem::TopLeft)  
             _target->_layoutGuest_Classic_ReferentSystem = ReferentSystem::BottomLeft;
    else if (_target->_layoutGuest_Classic_ReferentSystem == ReferentSystem::TopRight) 
             _target->_layoutGuest_Classic_ReferentSystem = ReferentSystem::BottomRight;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::right(Length right)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_Position.X = right;
    if      (_target->_layoutGuest_Classic_ReferentSystem == ReferentSystem::TopLeft)    
             _target->_layoutGuest_Classic_ReferentSystem = ReferentSystem::TopRight;
    else if (_target->_layoutGuest_Classic_ReferentSystem == ReferentSystem::BottomLeft) 
             _target->_layoutGuest_Classic_ReferentSystem = ReferentSystem::BottomRight;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::anchorTopLeft(Length top, Length left)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorPosition.Y = top;
    _target->_layoutGuest_Classic_AnchorPosition.X = left;
    _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::TopLeft;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::anchorTopRight(Length top, Length right)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorPosition.Y = top;
    _target->_layoutGuest_Classic_AnchorPosition.X = right;
    _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::TopRight;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::anchorBottomLeft(Length bottom, Length left)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorPosition.Y = bottom;
    _target->_layoutGuest_Classic_AnchorPosition.X = left;
    _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::BottomLeft;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::anchorBottomRight(Length bottom, Length right)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorPosition.Y = bottom;
    _target->_layoutGuest_Classic_AnchorPosition.X = right;
    _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::BottomRight;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::anchorTop(Length top)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorPosition.Y = top;
    if      (_target->_layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::BottomLeft)  
             _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::TopLeft;
    else if (_target->_layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::BottomRight) 
             _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::TopRight;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::anchorLeft(Length left)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorPosition.X = left;
    if      (_target->_layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::TopRight)    
             _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::TopLeft;
    else if (_target->_layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::BottomRight) 
             _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::BottomLeft;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::anchorBottom(Length bottom)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorPosition.Y = bottom;
    if      (_target->_layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::TopLeft) 
             _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::BottomLeft;
    else if (_target->_layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::TopRight) 
             _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::BottomRight;
    _target->_requestLayout();
}

void Layoutable::LayoutGuest::Classic::anchorRight(Length right)
{
    _target->_layoutGuest_layoutMode = LayoutMode::Classic;
    _target->_layoutGuest_Classic_AnchorPosition.X = right;
    if      (_target->_layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::TopLeft)    
             _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::TopRight;
    else if (_target->_layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::BottomLeft) 
             _target->_layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::BottomRight;
    _target->_requestLayout();
}
