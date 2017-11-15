#pragma once
#pragma once

#include "dllexport.h"

#include "cairo.h"
#include "event.h"
#include "UIContext.h"
#include "VisualParameters.h"
#include "Layoutable.h"
#include "IOEventTypes.h"


namespace Eleusis
{
    class MouseEventArgs;
    class MouseScrollEventArgs;

    class ELEUSIS_API UIContextual
    {
    protected:  UIContext* _uiContext = nullptr;

    public:     virtual ~UIContextual() { };
                inline UIContext* uiContext() { return _uiContext; };
    };

    class ELEUSIS_API IRenderable
    {
    public:     virtual ~IRenderable() { };
                virtual void _render(Region* region) = 0;
    };

    class ELEUSIS_API Node :
        public IRenderable,
        public UIContextual,
        public Layoutable
    {
        friend class Node; 
        friend class RootNode;

    private:   unsigned int  _zCoordinate = 0;

               Node* _firstChild      = nullptr;
               Node* _lastChild       = nullptr;
               Node* _parent          = nullptr;
               Node* _nextSibling     = nullptr;
               Node* _previousSibling = nullptr;

               bool _inFocus     = false;
               bool _isFocusable = false;

               bool _visibility = true;

               void  _obtainContext();

    protected: bool _isVisualPrimitive = false;

               bool _clipping = false;
               Rect _clippingRect;

               virtual void _requestRendering();
               virtual void _requestRendering(Rect rect);
               virtual void _requestLayout();
               virtual void _requestParentLayout();
               virtual void _requestGeometryUpdate();

    public:             Node();
               virtual ~Node();

               bool isVisualPrimitive() { return _isVisualPrimitive; }

               void enableFocus()  { _isFocusable = true; }
               void disableFocus() { _isFocusable = false; }
               bool isFocusable()  { return _isFocusable; }
               bool inFocus()      { return _inFocus; };
               void focus();

               void visibility_set(bool visibility);
               bool visibility_get();

             //void         zCoordinate_set(std::string  zCoordinate);
               void         zCoordinate_set(unsigned int zCoordinate);
               unsigned int zCoordinate_get();

               void insertAfter (Node* node);
               void insertBefore(Node* node);
               void insertChild (Node* node);
               void insertChild (Node* node, unsigned int zCoordinate);
               void remove();
               void removeChild (Node* node);
               void removeAndDeleteChild(Node* node);


               Node* next();
               Node* previous();

               Node* nextSibling();
               Node* previousSibling();

               Node* firstChild();
               Node* lastChild();

               Node* firstDescendant();
               Node* lastDescendant();

               Node* parent();

               bool isDescendantOf(Node* node);
               bool isAncestorOf  (Node* node);

               static Node* youngestCommonAncestor(Node* node1, Node* node2);

               virtual Rect getFullExtent() = 0;

               Event<Node*, EventArgs*>  gotFocus;
               Event<Node*, EventArgs*> lostFocus;

               Event<Node*, KeyboardEventArgs*> keyDown;
               Event<Node*, KeyboardEventArgs*> keyUp;

               Event<Node*, MouseEventArgs*>        mouseClick;
               Event<Node*, MouseEventArgs*>        mouseDoubleClick;
               Event<Node*, MouseEventArgs*>        mouseDown;
               Event<Node*, MouseEventArgs*>        mouseUp;
               Event<Node*, MouseScrollEventArgs*>  mouseScroll;
               Event<Node*, MouseEventArgs*>        mouseMove;
               Event<Node*, MouseEventArgs*>        mouseEnter;
               Event<Node*, MouseEventArgs*>        mouseLeave;

               Rect getFullLogicalExtent();


    private:   void _updateAbsoluteOffsetVector_classicLayout();
               void _updateAbsoluteOffsetVector_stackLayout();
               void _updateAbsoluteOffsetVector_wrapLayout();
               void _updateAbsoluteOffsetVector_gridLayout();

               Rect _getLogicalExtent();

               void  _gotFocus_thisHandler (Node* sender, EventArgs* e);
               void _lostFocus_thisHandler (Node* sender, EventArgs* e);


    public:    virtual void _layout();
               void _calculateChildrenClippings();

               // _render() and _applyAbsoluteOffset() and _updateAbsoluteSizeVector should be overriden 
               // by children classes in odred to control apperiance and layout of Node
               // Additionally, VisualPrimitive::_updateGeometry() should be overriden

               virtual void _render(Region* region = nullptr);
               virtual void _applyAbsoluteOffset();
    };
}
