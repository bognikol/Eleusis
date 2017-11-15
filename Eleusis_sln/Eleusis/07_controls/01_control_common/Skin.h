#pragma once

#include "Node.h"

namespace Eleusis
{
    class ELEUSIS_API Skin
    {
    public:
        virtual ~Skin() { };

        virtual Handler<Node*, EventArgs*> getGotFocusHandler()  = 0;
        virtual Handler<Node*, EventArgs*> getLostFocusHandler() = 0;

        virtual Handler<Node*, KeyboardEventArgs*> getKeyDownHandler() = 0;
        virtual Handler<Node*, KeyboardEventArgs*> getKeyUpHandler()   = 0;

        virtual Handler<Node*, MouseEventArgs*>        getMouseClickHandler()  = 0;
        virtual Handler<Node*, MouseEventArgs*>        getMouseDoubleClickHandler() = 0;
        virtual Handler<Node*, MouseEventArgs*>        getMouseDownHandler()   = 0;
        virtual Handler<Node*, MouseEventArgs*>        getMouseUpHandler()     = 0;
        virtual Handler<Node*, MouseScrollEventArgs*>  getMouseScrollHandler() = 0;
        virtual Handler<Node*, MouseEventArgs*>        getMouseMoveHandler()   = 0;
        virtual Handler<Node*, MouseEventArgs*>        getMouseEnterHandler()  = 0;
        virtual Handler<Node*, MouseEventArgs*>        getMouseLeaveHandler()  = 0;
    };
}

 