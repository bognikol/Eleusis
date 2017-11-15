#pragma once

#include "Window.h"

namespace Eleusis
{
    namespace Test
    {
        class FitChildrenTestWindow :
            public Window
        {
            Rectangle* _cont;

            Rectangle* _child1;
            Rectangle* _child2;
            Rectangle* _child3;
            Rectangle* _child4;
            Rectangle* _child5;
            Rectangle* _child6;
            Rectangle* _child7;

        public:
            FitChildrenTestWindow();
        };
    }
}