#pragma once

#include "Shape.h"
#include "Timer.h"

namespace Eleusis
{
    class ELEUSIS_API Caret :
        public Rectangle
    {
        Timer* _timer = nullptr;

        bool _isTransparent = false;

        RgbaColor _fillColor = Colors::Black;

    public:
        Caret();
        ~Caret();

        void resetTimer();

        void hide();
        void show();

        void setFillColor(RgbaColor fillColor) { _fillColor = fillColor; fillColor_set(_fillColor);  };
        RgbaColor getFillColor() { return _fillColor; };
    };
}

