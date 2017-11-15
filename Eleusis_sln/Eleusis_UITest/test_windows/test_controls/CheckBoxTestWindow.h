#pragma once

#include "Window.h"
#include "CheckBox.h"

namespace Eleusis
{
    namespace Test
    {
        class CheckBoxTestWindow :
            public Window
        {
            CheckBox* _checkBox = nullptr;

        public:
            CheckBoxTestWindow();
        };
    }
}


