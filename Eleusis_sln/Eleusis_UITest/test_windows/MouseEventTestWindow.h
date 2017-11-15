#pragma once

#include "Window.h"
#include "event.h"

namespace Eleusis
{
    namespace Test
    {
        class MouseEventTestPseudoControl :
            public Eleusis::Rectangle
        {
        public:
            MouseEventTestPseudoControl(Node* node);
            ~MouseEventTestPseudoControl();

            void setTextColor(RgbaColor color);

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

        class MouseEventTestWindow
            : public Eleusis::Window
        {
        public:
            MouseEventTestWindow();
            MouseEventTestPseudoControl* _mouseEventChecker = nullptr;
            std::function<void(Node*, MouseEventArgs*)> _clickHandler;
        };
    }
}
