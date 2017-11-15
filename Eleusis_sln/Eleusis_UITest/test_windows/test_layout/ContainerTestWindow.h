#pragma once

#include "Container.h"
#include "Window.h"

namespace Eleusis
{
    namespace Test
    {
        class ContainerTestWindow :
            public Window
        {
        public:
            ContainerTestWindow();

            Container* _cont;
            Container* _cont2;
            
        };
    }
}