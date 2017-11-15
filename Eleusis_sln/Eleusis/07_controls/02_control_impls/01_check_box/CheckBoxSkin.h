#pragma once

#include "Skin.h"
#include "Shape.h"
#include "TextBlock.h"

namespace Eleusis
{
    class CheckBox;

    class CheckBoxSkin :
        public Skin
    {
    protected:
        Node* _rect  = nullptr;
        Node* _checkMark = nullptr;
        TextBlock* _text  = nullptr;

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

        Handler<CheckBox*, EventArgs*> _checkChangedHandler;
        Handler<CheckBox*, EventArgs*> _textChangedHandler;


    public:
        virtual ~CheckBoxSkin() { };

        Node* getRectanlge() { return _rect; };
        Node* getCheckMark() { return _checkMark; };
        TextBlock* getTextBlock() { return _text; };

        Handler<Node*, EventArgs*> getGotFocusHandler() { return _gotFocusHandler; };
        Handler<Node*, EventArgs*> getLostFocusHandler() { return _lostFocusHandler; };

        Handler<Node*, KeyboardEventArgs*> getKeyDownHandler() { return _keyDownHandler; };
        Handler<Node*, KeyboardEventArgs*> getKeyUpHandler() { return _keyUpHandler; };

        Handler<Node*, MouseEventArgs*>        getMouseClickHandler() { return _mouseClickHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseDoubleClickHandler() { return _mouseDoubleClickHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseDownHandler() { return _mouseDownHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseUpHandler() { return _mouseUpHandler; };
        Handler<Node*, MouseScrollEventArgs*>  getMouseScrollHandler() { return _mouseScrollHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseMoveHandler() { return _mouseMoveHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseEnterHandler() { return _mouseEnterHandler; };
        Handler<Node*, MouseEventArgs*>        getMouseLeaveHandler() { return _mouseLeaveHandler; };

        Handler<CheckBox*, EventArgs*> getCheckChangedHandler() { return _checkChangedHandler; };
        Handler<CheckBox*, EventArgs*> getTextChangedHandler() { return _textChangedHandler; };

    };
}