#pragma once

#include "Window.h"
#include "Slider.h"

namespace Eleusis
{
    namespace Test
    {
        class SliderTestWindow :
            public Window
        {
            Slider* _slider = nullptr;

        public:
            SliderTestWindow();
        };
    }
}