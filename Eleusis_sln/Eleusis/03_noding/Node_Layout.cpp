#include "Node.h"
#include "VisualPrimitive.h"

using namespace Eleusis;

void Node::_layout()
{
    if (_layoutingExecuted) return;

    _absoluteOffsetVector = _parent->getApsoluteOffsetVector();

    Vector l_innerParentAbsoluteSize = _parent->_effectiveSizeExcludingPadding();

    bool l_absoluteSizeVectorChanged = false;
    _updateAbsoluteSizeVector(&l_absoluteSizeVectorChanged, l_innerParentAbsoluteSize);

    if (_layoutHost_Stack_Orientation == LayoutOrientation::Vertical)
        _layoutingState._currentStackOffset = _effectivePaddingTop();
    else
        _layoutingState._currentStackOffset = _effectivePaddingLeft();

    _layoutingState._currentWrapOffset = { _effectivePaddingLeft(), _effectivePaddingTop() };

    switch (_layoutGuest_layoutMode)
    {
    case LayoutMode::Classic:
        _updateAbsoluteOffsetVector_classicLayout(); 
        break;
    case LayoutMode::Stack: 
        _updateAbsoluteOffsetVector_stackLayout();
        break;
    case LayoutMode::Wrap:
        _updateAbsoluteOffsetVector_wrapLayout();
        break;
    case LayoutMode::Grid:
        _updateAbsoluteOffsetVector_gridLayout();
        break;
    }

    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_layout();
        l_nextChild = l_nextChild->nextSibling();
    }

    if (l_absoluteSizeVectorChanged && isVisualPrimitive())
        uiContext()->notifyModelChange(static_cast<VisualPrimitive*>(this), false, true, false, nullptr);

    _layoutingExecuted = true;
}

Rect Node::getFullLogicalExtent()
{
    Node* l_lastDescendant = lastDescendant();

    Rect l_extent;

    Node* l_node = _firstChild;

    if (l_node)
        l_extent = l_node->_getLogicalExtent();
    else
        return Rect();

    while (true)
    {
        if (l_node == l_lastDescendant) break;
        l_node = l_node->next();
        l_extent |= l_node->_getLogicalExtent();
    }

    l_extent.highVector += Vector(_effectivePaddingRight(), _effectivePaddingBottom());

    return l_extent;
}

Rect Node::_getLogicalExtent()
{
    Vector l_offset;
    Vector l_size;

    switch (_layoutGuest_layoutMode)
    {
        case Eleusis::LayoutMode::Classic:
        {
            l_offset = _absoluteOffsetVector;
            l_size =   _absoluteSizeVector;
        }
        break;
        case Eleusis::LayoutMode::Stack:
        case Eleusis::LayoutMode::Wrap:
        {
            l_offset = _absoluteOffsetVector - Vector(_effectiveMarginLeft(), _effectiveMarginTop());
            l_size = _effectiveSizeIncludingMargin();
        }
        break;
        default:
            break;
    }

    return l_offset ^ l_size;
}

void Node::_calculateChildrenClippings()
{
    Rect l_childrenClippingRect;

    if (_clipping)
        if (_clippingRect.isZero())
            l_childrenClippingRect = _absoluteOffsetVector ^ _absoluteSizeVector;
        else
            l_childrenClippingRect = _clippingRect && (_absoluteOffsetVector ^ _absoluteSizeVector);
    else
        l_childrenClippingRect = _clippingRect;

    
    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_clippingRect = l_childrenClippingRect;
        l_nextChild->_calculateChildrenClippings();
        l_nextChild = l_nextChild->nextSibling();
    }
}

void Node::_updateAbsoluteOffsetVector_classicLayout()
{
    Vector effectiveParentAbsoluteSize = _parent->_effectiveSizeExcludingPadding();

    Vector l_absoluteAnchorPosition =
    {
        _layoutGuest_Classic_AnchorPosition.X.getValueRelativeTo(_absoluteSizeVector.X),
        _layoutGuest_Classic_AnchorPosition.Y.getValueRelativeTo(_absoluteSizeVector.Y)
    };

    if (_layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::TopRight ||
        _layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::BottomRight)
    {
        l_absoluteAnchorPosition.X = _absoluteSizeVector.X - l_absoluteAnchorPosition.X;
    }

    if (_layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::BottomRight ||
        _layoutGuest_Classic_AnchorReferentSystem == ReferentSystem::BottomLeft)
    {
        l_absoluteAnchorPosition.Y = _absoluteSizeVector.Y - l_absoluteAnchorPosition.Y;
    }

    Vector l_absolutePosition =
    {
        _layoutGuest_Classic_Position.X.getValueRelativeTo(effectiveParentAbsoluteSize.X),
        _layoutGuest_Classic_Position.Y.getValueRelativeTo(effectiveParentAbsoluteSize.Y)
    };

    if (_layoutGuest_Classic_ReferentSystem == ReferentSystem::TopRight ||
        _layoutGuest_Classic_ReferentSystem == ReferentSystem::BottomRight)
    {
        l_absolutePosition.X = effectiveParentAbsoluteSize.X - l_absolutePosition.X - _absoluteSizeVector.X;
    }

    if (_layoutGuest_Classic_ReferentSystem == ReferentSystem::BottomRight ||
        _layoutGuest_Classic_ReferentSystem == ReferentSystem::BottomLeft)
    {
        l_absolutePosition.Y = effectiveParentAbsoluteSize.Y - l_absolutePosition.Y - _absoluteSizeVector.Y;
    }

    _relativeOffsetVector.X = parent()->_effectivePaddingLeft() + l_absolutePosition.X - l_absoluteAnchorPosition.X;
    _relativeOffsetVector.Y = parent()->_effectivePaddingTop() + l_absolutePosition.Y - l_absoluteAnchorPosition.Y;

    _absoluteOffsetVector += _relativeOffsetVector;
}

void Node::_updateAbsoluteOffsetVector_stackLayout()
{
    if (!_parent) return;

    switch (_parent->_layoutHost_Stack_Orientation)
    {
    case LayoutOrientation::Vertical:
    {
        _relativeOffsetVector.Y = parent()->_layoutingState._currentStackOffset + _effectiveMarginTop();

        parent()->_layoutingState._currentStackOffset = _relativeOffsetVector.Y + _absoluteSizeVector.Y + _effectiveMarginBottom();

        switch (_parent->_layoutHost_Stack_Alignment)
        {
        case LayoutAlignment::TopLeft:
            _relativeOffsetVector.X = parent()->_effectivePaddingLeft() + _effectiveMarginLeft();
            break;
        case LayoutAlignment::BottomRight:
            _relativeOffsetVector.X = parent()->_absoluteSizeVector.X - parent()->_effectivePaddingRight() - _effectiveWidthIncludingMargin();
            break;
        case LayoutAlignment::Center:
            _relativeOffsetVector.X = parent()->_effectivePaddingLeft() + (parent()->_effectiveWidthExcludingPadding() - _effectiveWidthIncludingMargin()) / 2;
            break;
        }
    }
    break;
    case LayoutOrientation::Horizontal:
    {
        _relativeOffsetVector.X = parent()->_layoutingState._currentStackOffset + _effectiveMarginLeft();

        parent()->_layoutingState._currentStackOffset = _relativeOffsetVector.X + _absoluteSizeVector.X + _effectiveMarginRight();

        switch (_parent->_layoutHost_Stack_Alignment)
        {
        case LayoutAlignment::TopLeft:
            _relativeOffsetVector.Y = parent()->_effectivePaddingTop() + _effectiveMarginTop();
            break;
        case LayoutAlignment::BottomRight:
            _relativeOffsetVector.Y = parent()->_absoluteSizeVector.Y - parent()->_effectivePaddingBottom() - _effectiveHeightIncludingMargin();
            break;
        case LayoutAlignment::Center:
            _relativeOffsetVector.Y = parent()->_effectivePaddingTop() + (parent()->_effectiveHeightExcludingPadding() - _effectiveHeightIncludingMargin()) / 2;
            break;
        }
    }
    break;
    }

    _absoluteOffsetVector += _relativeOffsetVector;
}

void Node::_updateAbsoluteOffsetVector_wrapLayout()
{
    double l_effectiveHeightWithMargin = _effectiveHeightIncludingMargin();
    double l_effectiveWidthWithMargin = _effectiveWidthIncludingMargin();

    switch (_parent->_layoutHost_Wrap_Orientation)
    {
    case (LayoutOrientation::Horizontal):
    {
        if (_parent->_layoutingState._currentWrapNumberOfRowElements == 0)
        {
            _relativeOffsetVector = _parent->_layoutingState._currentWrapOffset + Vector(_effectiveMarginLeft(), _effectiveMarginTop());

            _parent->_layoutingState._currentWrapNumberOfRowElements++;
            _parent->_layoutingState._currentWrapRowHeight = l_effectiveHeightWithMargin;
            _parent->_layoutingState._currentWrapOffset.X += l_effectiveWidthWithMargin;
        }
        else
        {
            if (_parent->_layoutingState._currentWrapOffset.X + l_effectiveWidthWithMargin > _parent->_effectiveWidthExcludingPadding() + _parent->_effectivePaddingLeft())
            {
                _parent->_layoutingState._currentWrapOffset.Y += _parent->_layoutingState._currentWrapRowHeight;
                _parent->_layoutingState._currentWrapOffset.X = _parent->_effectivePaddingLeft();
                _parent->_layoutingState._currentWrapRowHeight = l_effectiveHeightWithMargin;
                _parent->_layoutingState._currentWrapNumberOfRowElements = 1;

                _relativeOffsetVector = _parent->_layoutingState._currentWrapOffset + Vector(_effectiveMarginLeft(), _effectiveMarginTop());

                _parent->_layoutingState._currentWrapOffset.X += l_effectiveWidthWithMargin;
            }
            else
            {
                _relativeOffsetVector = _parent->_layoutingState._currentWrapOffset + Vector(_effectiveMarginLeft(), _effectiveMarginTop());

                _parent->_layoutingState._currentWrapNumberOfRowElements++;
                _parent->_layoutingState._currentWrapOffset.X += l_effectiveWidthWithMargin;
                if (_parent->_layoutingState._currentWrapRowHeight < l_effectiveHeightWithMargin)
                    _parent->_layoutingState._currentWrapRowHeight = l_effectiveHeightWithMargin;
            }
        }
    }
    break;
    case (LayoutOrientation::Vertical):
    {
        if (_parent->_layoutingState._currentWrapNumberOfRowElements == 0)
        {
            _relativeOffsetVector = _parent->_layoutingState._currentWrapOffset;

            _parent->_layoutingState._currentWrapNumberOfRowElements++;
            _parent->_layoutingState._currentWrapRowHeight = l_effectiveWidthWithMargin;
            _parent->_layoutingState._currentWrapOffset.Y += l_effectiveHeightWithMargin;
        }
        else
        {
            if (_parent->_layoutingState._currentWrapOffset.Y + l_effectiveHeightWithMargin > _parent->_effectiveHeightExcludingPadding() + _parent->_effectivePaddingLeft())
            {
                _parent->_layoutingState._currentWrapOffset.X += _parent->_layoutingState._currentWrapRowHeight;
                _parent->_layoutingState._currentWrapOffset.Y = _parent->_effectivePaddingTop();
                _parent->_layoutingState._currentWrapRowHeight = l_effectiveWidthWithMargin;
                _parent->_layoutingState._currentWrapNumberOfRowElements = 1;

                _relativeOffsetVector = _parent->_layoutingState._currentWrapOffset;

                _parent->_layoutingState._currentWrapOffset.Y += l_effectiveHeightWithMargin;
            }
            else
            {
                _relativeOffsetVector = _parent->_layoutingState._currentWrapOffset;

                _parent->_layoutingState._currentWrapNumberOfRowElements++;
                _parent->_layoutingState._currentWrapOffset.Y += l_effectiveHeightWithMargin;
                if (_parent->_layoutingState._currentWrapRowHeight < l_effectiveWidthWithMargin)
                    _parent->_layoutingState._currentWrapRowHeight = l_effectiveWidthWithMargin;
            }
        }
    }
    break;
    }

    _absoluteOffsetVector += _relativeOffsetVector;
}

void Node::_updateAbsoluteOffsetVector_gridLayout()
{
    //TODO: to be implemented

    _absoluteOffsetVector += _relativeOffsetVector;
}

void Node::_render(Region* region)
{
    if (!visibility_get()) return;
    if (!_uiContext)       return;

    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_render(region);
        l_nextChild = l_nextChild->nextSibling();
    }
}