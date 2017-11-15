#pragma once

#include "Window.h"
#include "TextBlock.h"

namespace Eleusis
{
    namespace Test
    {
        class MouseEventTextBlockTestWindow :
            public Window
        {
        private:
            Span* _tb1p1s1;
            Span* _tb1p1s2;
            Span* _tb1p1s3;

            Paragraph* _tb1p1;

            Span* _tb1p2s1;
            Span* _tb1p2s2;
            Span* _tb1p2s3;

            Paragraph* _tb1p2;

            TextBlock* _tb1;

        public:
            MouseEventTextBlockTestWindow();

        };
    }
}