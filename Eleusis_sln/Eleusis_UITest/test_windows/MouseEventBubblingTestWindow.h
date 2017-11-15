#pragma once

#include "Window.h"

namespace Eleusis
{
    namespace Test
    {
        class MouseEventDetailsPseudoControl :
            public Rectangle
        {
        public:
            MouseEventDetailsPseudoControl(Node* listenedNode);

        private:
            Eleusis::Node* eventSender;

            Eleusis::TextualShape* textLine_mouseClick;
            Eleusis::TextualShape* textLine_mouseDoubleClick;
            Eleusis::TextualShape* textLine_mouseDown;
            Eleusis::TextualShape* textLine_mouseUp;
            Eleusis::TextualShape* textLine_mouseWheelRotated;
            Eleusis::TextualShape* textLine_mouseMove;
            Eleusis::TextualShape* textLine_mouseEnter;
            Eleusis::TextualShape* textLine_mouseLeave;

            int count_mouseClick = 0;
            int count_mouseDoubleClick = 0;
            int count_mouseDown = 0;
            int count_mouseUp = 0;
            int count_mouseWheelRotated = 0;
            int count_mouseMove = 0;
            int count_mouseEnter = 0;
            int count_mouseLeave = 0;

            Eleusis::TextualShape* textLine_lastMouseEventArgs;
        };

        class MouseEventBubblingTestWindow :
            public Window
        {
        public:
            MouseEventBubblingTestWindow();
        };
    }
}

