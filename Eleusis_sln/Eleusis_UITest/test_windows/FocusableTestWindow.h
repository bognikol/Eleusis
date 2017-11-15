#pragma once

#include "Window.h"
#include "Shape.h"

namespace Eleusis
{
    namespace Test
    {
        class FocusableTestWindow :
            public Window
        {
            Rectangle* _rect = nullptr;


        public:
            FocusableTestWindow()
            {
                _rect = new Rectangle();
                _rect->setWidthAndHeight(200, 200);
                _rect->LayoutGuest.Classic.topLeft(20, 20);
                _rect->fillColor_set(Colors::Magenta);
                _rect->enableFocus();
                insertChild(_rect);

                _rect->mouseClick +=
                    [this](Node* sender, MouseEventArgs* e)
                {
                    if (_rect->inFocus())
                    {
                        _rect->fillColor_set(Colors::Magenta);
                        setFocus(nullptr);
                    }
                    else
                    {
                        _rect->fillColor_set(Colors::YellowGreen);
                        _rect->focus();
                    }
                };

                _rect->keyDown +=
                    [this](Node* sender, KeyboardEventArgs* e)
                {
                    _rect->fillColor_set(Colors::Ivory);
                };
            }
        };
    }
}