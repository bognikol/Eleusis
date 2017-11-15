#pragma once

#include "Skin.h"
#include "Shape.h"
#include "TextBlock.h"

namespace Eleusis
{
    class ELEUSIS_API SliderSkin :
        public Skin
    {
    protected:
        Node* _thumb = nullptr;
        Line* _track = nullptr;

        Handler<Node*, EventArgs*> _gotFocusHandler;
        Handler<Node*, EventArgs*> _lostFocusHandler;

        Handler<Node*, KeyboardEventArgs*> _keyDownHandler;
        Handler<Node*, KeyboardEventArgs*> _keyUpHandler;

        Handler<Node*, MouseEventArgs*>        _mouseClickHandler;
        Handler<Node*, MouseEventArgs*>        _mouseDoubleClickHandler;
        Handler<Node*, MouseEventArgs*>        _mouseDownHandler;
        Handler<Node*, MouseEventArgs*>        _mouseUpHandler;
        Handler<Node*, MouseScrollEventArgs*>  _mouseScrollHandler;
        Handler<Node*, MouseEventArgs*>        _mouseMoveHandler;
        Handler<Node*, MouseEventArgs*>        _mouseEnterHandler;
        Handler<Node*, MouseEventArgs*>        _mouseLeaveHandler;

    public:
        virtual ~SliderSkin() { };

        Node* getThumb() { return _thumb; }
        Line* getTrack() { return _track; }

        Handler<Node*, EventArgs*> getGotFocusHandler()  { return _gotFocusHandler; };
        Handler<Node*, EventArgs*> getLostFocusHandler() { return _lostFocusHandler; };

        Handler<Node*, KeyboardEventArgs*> getKeyDownHandler() { return _keyDownHandler; };
        Handler<Node*, KeyboardEventArgs*> getKeyUpHandler()   { return _keyUpHandler; };

        Handler<Node*, MouseEventArgs*>        getMouseClickHandler() { return _mouseClickHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseDoubleClickHandler() { return _mouseDoubleClickHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseDownHandler() { return _mouseDownHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseUpHandler() { return _mouseUpHandler; };
        Handler<Node*, MouseScrollEventArgs*>  getMouseScrollHandler() { return _mouseScrollHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseMoveHandler() { return _mouseMoveHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseEnterHandler() { return _mouseEnterHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseLeaveHandler() { return _mouseLeaveHandler; };
    };
}