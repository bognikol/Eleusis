#pragma once

#include "Window.h"
#include "TextBlock.h"

namespace Eleusis
{
    class TextualsTestWindow :
        public Window
    {
    public:
        TextualsTestWindow();
        std::shared_ptr<SpanStyle> ss3;
        TextBlock* tb1;
    };
}

