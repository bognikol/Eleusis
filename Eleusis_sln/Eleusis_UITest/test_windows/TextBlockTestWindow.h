#pragma once

#include "Window.h"
#include "TextBlock.h"
#include "PseudoButton.h"

namespace Eleusis
{
    namespace Test
    {
        class TextBlockTestWindow :
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

            PseudoControls::PseudoButton* _btn1;
            PseudoControls::PseudoButton* _btn2;
            PseudoControls::PseudoButton* _btn3;
            PseudoControls::PseudoButton* _btn4;
            PseudoControls::PseudoButton* _btn5;

            Rectangle* _rect;
            TextBlock* txt[100];
        public:
            TextBlockTestWindow();

        };
    }
}