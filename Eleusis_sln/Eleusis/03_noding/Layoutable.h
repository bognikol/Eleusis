#pragma once

#include "dllexport.h"
#include "01_vectoring/Vector.h"
#include "01_vectoring/Length.h"
#include "01_vectoring/Rect.h"

namespace Eleusis
{
    enum class LayoutMode
    {
        Classic,
        Stack,
        Wrap,
        Grid
    };

    enum class ReferentSystem
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    enum class LayoutOrientation
    {
        Horizontal,
        Vertical
    };

    enum class LayoutAlignment
    {
        TopLeft,
        BottomRight,
        Center
    };

    class ELEUSIS_API Layoutable 
    {
        friend class Window;

    public:
        struct ELEUSIS_API LayoutGuest
        {
            struct ELEUSIS_API Classic
            {
                Classic(Layoutable* target) { _target = target; };

                void setMode();

                void position_set(Length vertical, Length horizontal);
                
                void   positionVertical_set(Length vertical);
                Length positionVertical_get();

                void   positionHorizontal_set(Length horizontal);
                Length positionHorizontal_get();

                void           positionReferentSystem_set(ReferentSystem system);
                ReferentSystem positionReferentSystem_get();

                void anchorPosition_set(Length vertical, Length horizontal);

                void   anchorPositionVertical_set(Length vertical);
                Length anchorPositionVertical_get();

                void   anchorPositionHorizontal_set(Length horizontal);
                Length anchorPositionHorizontal_get();

                void           anchorPositionReferentSystem_set(ReferentSystem system);
                ReferentSystem anchorPositionReferentSystem_get();

                void topLeft     (Length top,    Length left);
                void topRight    (Length top,    Length right);
                void bottomLeft  (Length bottom, Length left);
                void bottomRight (Length bottom, Length right);

                void top    (Length top);
                void left   (Length left);
                void bottom (Length bottom);
                void right  (Length right);

                void anchorTopLeft     (Length top,    Length left);
                void anchorTopRight    (Length top,    Length right);
                void anchorBottomLeft  (Length bottom, Length left);
                void anchorBottomRight (Length bottom, Length right);

                void anchorTop    (Length top);
                void anchorLeft   (Length left);
                void anchorBottom (Length bottom);
                void anchorRight  (Length right);

            private:
                Layoutable* _target;
                void operator = (Classic &) { };
            };

            struct ELEUSIS_API Stack
            {
                Stack(Layoutable* target) { _target = target; };

                void setMode();

                void margin(Length top = 0, Length left = 0, Length bottom = 0, Length right = 0);

                void   marginTop_set(Length top);
                Length marginTop_get();

                void   marginLeft_set(Length left);
                Length marginLeft_get();

                void   marginBottom_set(Length bottom);
                Length marginBottom_get();

                void   marginRight_set(Length right);
                Length marginRight_get();

            private:
                Layoutable* _target;
                void operator = (Stack &) { };
            };

            struct ELEUSIS_API Wrap
            {
                Wrap(Layoutable* target) { _target = target; };

                void setMode();

                void margin(Length top = 0, Length left = 0, Length bottom = 0, Length right = 0);

                void   marginTop_set(Length top);
                Length marginTop_get();

                void   marginLeft_set(Length left);
                Length marginLeft_get();

                void   marginBottom_set(Length bottom);
                Length marginBottom_get();

                void   marginRight_set(Length right);
                Length marginRight_get();

            private:
                Layoutable* _target;
                void operator = (Wrap &) { };
            };

            LayoutGuest(Layoutable* parent) :
                Classic(parent),
                Stack(parent),
                Wrap(parent)
            {
            };

            Classic Classic;
            Stack   Stack;
            Wrap    Wrap;

        private:
            void operator = (LayoutGuest &) { };
        };

        struct ELEUSIS_API LayoutHost
        {
            LayoutHost(Layoutable* parent)
            {
                _target = parent;
            }

            void padding(Length top = 0, Length left = 0, Length bottom = 0, Length right = 0);

            void   paddingTop_set(Length top);
            Length paddingTop_get();

            void   paddingLeft_set(Length left);
            Length paddingLeft_get();

            void   paddingBottom_set(Length bottom);
            Length paddingBottom_get();

            void   paddingRight_set(Length right);
            Length paddingRight_get();

            void              stackOrientation_set(LayoutOrientation orientation);
            LayoutOrientation stackOrientation_get();

            void            stackAlignment_set(LayoutAlignment alignment);
            LayoutAlignment stackAlignment_get();

            void              wrapOrientation_set(LayoutOrientation orientation);
            LayoutOrientation wrapOrientation_get();

        private:
            Layoutable* _target = nullptr;
            void operator = (LayoutHost &) { };
        };


    public:     Layoutable() :
                LayoutGuest(this),
                LayoutHost(this)
                {
                }

                virtual void _layout() = 0;


    protected:  struct LayoutRectOffset
                {
                    LayoutRectOffset() {};
                    LayoutRectOffset(Length top, Length left, Length bottom, Length right) :
                        Top(top),
                        Left(left),
                        Bottom(bottom),
                        Right(right)
                    {
                    };

                    Length Top = 0;
                    Length Bottom = 0;
                    Length Left = 0;
                    Length Right = 0;
                };

                struct LayoutPosition
                {
                    Length X = 0;
                    Length Y = 0;
                };
        
                struct LayoutingStateData
                {
                    double _currentStackOffset = 0;
                    Vector _currentWrapOffset;
                    double _currentWrapRowHeight = 0;
                    int    _currentWrapNumberOfRowElements = 0;
                };
        
                Vector _absoluteOffsetVector;
                Vector _absoluteSizeVector;
                Vector _relativeOffsetVector;

                LayoutRectOffset        _layoutHost_Padding;
                LayoutOrientation       _layoutHost_Stack_Orientation = LayoutOrientation::Vertical;
                LayoutAlignment         _layoutHost_Stack_Alignment   = LayoutAlignment::TopLeft;
                LayoutOrientation       _layoutHost_Wrap_Orientation  = LayoutOrientation::Horizontal;

                LayoutMode              _layoutGuest_layoutMode                   = LayoutMode::Classic;
                ReferentSystem          _layoutGuest_Classic_ReferentSystem       = ReferentSystem::TopLeft;
                ReferentSystem          _layoutGuest_Classic_AnchorReferentSystem = ReferentSystem::TopLeft;
                LayoutPosition          _layoutGuest_Classic_Position;
                LayoutPosition          _layoutGuest_Classic_AnchorPosition;
                LayoutRectOffset        _layoutGuest_StackWrap_Margin;

                bool _layoutingExecuted = false;
                bool _absoluteOffsetApplicationExecuted = false;
                bool _geometryUpdateExecuted = false;

                LayoutingStateData _layoutingState;

                virtual void _requestRendering() = 0;
                virtual void _requestRendering(Rect rect) = 0;
                virtual void _requestLayout() = 0;
                virtual void _requestParentLayout() = 0;
                virtual void _requestGeometryUpdate() = 0;

                double _effectivePaddingTop()
                {
                    return _layoutHost_Padding.Top.getValueRelativeTo(_absoluteSizeVector.Y);
                }
                double _effectivePaddingLeft()
                {
                    return _layoutHost_Padding.Left.getValueRelativeTo(_absoluteSizeVector.Y);
                }
                double _effectivePaddingBottom()
                {
                    return _layoutHost_Padding.Bottom.getValueRelativeTo(_absoluteSizeVector.Y);
                }
                double _effectivePaddingRight()
                {
                    return _layoutHost_Padding.Right.getValueRelativeTo(_absoluteSizeVector.Y);
                }

                double _effectiveMarginTop()
                {
                    return _layoutGuest_StackWrap_Margin.Top.getValueRelativeTo(_absoluteSizeVector.Y);
                }

                double _effectiveMarginLeft()
                {
                    return _layoutGuest_StackWrap_Margin.Left.getValueRelativeTo(_absoluteSizeVector.Y);
                }

                double _effectiveMarginBottom()
                {
                    return _layoutGuest_StackWrap_Margin.Bottom.getValueRelativeTo(_absoluteSizeVector.Y);
                }

                double _effectiveMarginRight()
                {
                    return _layoutGuest_StackWrap_Margin.Right.getValueRelativeTo(_absoluteSizeVector.Y);
                }

                double _effectiveWidthExcludingPadding()
                {
                    return _absoluteSizeVector.X - _effectivePaddingLeft() - _effectivePaddingRight();
                }

                double _effectiveHeightExcludingPadding()
                {
                    return _absoluteSizeVector.Y - _effectivePaddingTop() - _effectivePaddingBottom();
                }

                Vector _effectiveSizeExcludingPadding()
                {
                    return{ _effectiveWidthExcludingPadding(), _effectiveHeightExcludingPadding() };
                }

                double _effectiveWidthIncludingMargin()
                {
                    return _effectiveMarginLeft() + _absoluteSizeVector.X + _effectiveMarginRight();
                }

                double _effectiveHeightIncludingMargin()
                {
                    return _effectiveMarginTop() + _absoluteSizeVector.Y + _effectiveMarginBottom();
                }

                Vector _effectiveSizeIncludingMargin()
                {
                    return{ _effectiveWidthIncludingMargin(), _effectiveHeightIncludingMargin() };
                }

                bool _updateAbsoluteVectorExecutedOnce = false;
                Rect _childrenBounds;

    public:     LayoutGuest LayoutGuest;
                LayoutHost  LayoutHost;

                LayoutMode layoutMode() { return _layoutGuest_layoutMode; };

                virtual void _updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector = { 0,0 }) { _absoluteSizeVector = { 0,0 }; };

                Vector getApsoluteOffsetVector() { return _absoluteOffsetVector; };
                Vector getAbsoluteSizeVector()   { return _absoluteSizeVector;   };
                Vector getRelativeOffsetVector() { return _relativeOffsetVector; };
    };
}


/*

=======================
ELEUSIS RENDERING CYCLE
=======================

'Ui tree' is a tree made of Nodes.
Each UiContext has exactly one ui tree.
Root of ui tree is a RootNode.

'Ui tree' deffinition.
'Ui bitmap' definition.
'UIContext' definition.
'Node' definition.

Eleusis is maintaining ui tree as a coneptual model of UI.
How ui tree is parsed in order to render a bitmap on UiContext, which actually represent UI.

Each Node has multiple functions which change its state. 

Eleusis rendering pipeline contains 5 stages:
(1) Registring changes in ui tree
(2) Layouting nodes that registered for layouting
(3) Updating geometry of nodes that registered for geometry update
(4) Applying absolute offset to nodes that for absolute offset application
(5) Rendering region of ui bitmap that needs to be rerendered



There are two initiators of activity in Eleusis:

(1) External events
    For example mouse, keyboard or network events. Application subscribes to some of these events and provides appropriate callbacks.
    When event happens, a callback is executed modifying ui tree. Changes in ui tree are registered at UIContext.
    Some of these events are natively supported by Eleusis, for example keyboard or mouse events, while some, like network events, 
    are not natively supported so another library must be used.

(2) Rendering timer
    Rendering timer is repeatidly elapsing, checking for changes in ui tree, and rerendering regions of ui bitmap to reflect these changes.
    Frequency of rendering timer represents requested frame rate. Actual frame rate is different because some rendering timers will not
    execute due to synchronius blocks (for example slow synchronius functions).

These initiators are synchronus, i.e. they are all executing on the same, rendering (main) thread.

Conceptually, external events (1) modify ui tree, while rendering timer (2) reads ui tree and updates ui bitmap.

Eleusis rendering pipeline or rendering cycle conist of following phases:

    REGISTRING CHANGES --> LAYOUTING --> GEOMETRY UPDATE --> ABSOLUTE OFFSET APPLICATION --> RENDERING
            /\                                                                                  |
            |                                                                                  \/
            +-----------------------------------------------------------------------------------+

(1) Registring changes

(2) Layouting is a process of obtaining of absolute offset vector (AOF) and absolute size vector (ASV).

(3) Geometry update is a process where VisualPrimitives update its internal cairo/pango model.
    This model is read by cairo/pango for rendering.

(4) Absolute offset application is a process where AOF is applyed to cairo/pango model (geometry).
    In other words, VisualPrimitive's geometry is translated at appropriate place.

(5) Rendering

We can remove ABSOLUTE OFFSET APPLICATION and move it to be applied immidiatelly before rendering

REGISTRING CHANGES --> LAYOUTING --> GEOMETRY UPDATE --> RENDERING
        /\                                                   |
        |                                                   \/
        +--------------------------------------------------- +
        
(1) Registring changes

(2) Layouting is a process of obtaining of absolute offset vector (AOF) and absolute size vector (ASV).

(3) Geometry update is a process where VisualPrimitives update its internal cairo/pango model.
This model is read by cairo/pango for rendering.

(4) Rendering

Functions of Node and its descendants may request some of following:
(1) Layouting, if functions change ui model in such way that AOF or ASV may be changed.
(2) Geometry update, if geometry params changed.
(3) Rendering, if rendering params changed.

IF LAYOUTING IS REQUESTED
    DO LAYOUTING
IF ASV IS CHANGED OR GEOMETRY UPDATE IS REQUESTED
    DO GEOMETRY UPDATE
IF LAYOUTING IS EXECUTED OR GEOMETRY UPDATE IS EXECUTED OR RENDERING IS REQUESTED
    DO RENDERING

    (1)

    LAYOUT

    IF ASV IS CHANGED
        DO GEOMETRY UPDATE

    RENDER

    (2)

    DO GEOMETRY UPDATE

    RENDER

    (3)

    RENDER


































*/