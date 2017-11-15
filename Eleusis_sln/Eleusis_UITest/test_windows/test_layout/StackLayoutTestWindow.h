#pragma once

#include "Window.h"

namespace Eleusis
{
    namespace Test
    {
        class StackLayoutTestWindow :
            public Window
        {
        public:
            StackLayoutTestWindow();

        private:
            Rectangle* _rect = nullptr;
            Rectangle* _rect1 = nullptr;
            Rectangle* _rect2 = nullptr;
            Rectangle* _rect3 = nullptr;
            Rectangle* _rect4 = nullptr;
            Rectangle* _rect5 = nullptr;
        };
    }
}