#pragma once

#include "Window.h"

namespace Eleusis
{
    namespace Test
    {
        class ClassicLayoutTestWindow :
            public Window
        {
        public:
            ClassicLayoutTestWindow();

        private:
            Rectangle* _rect = nullptr;
            Rectangle* _rect2 = nullptr;
        };
    }
}

