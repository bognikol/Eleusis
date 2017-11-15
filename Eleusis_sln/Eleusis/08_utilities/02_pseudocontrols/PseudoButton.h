#pragma once

#include "dllexport.h"

#include "Shape.h"
#include "TextBlock.h"


namespace Eleusis
{
    namespace PseudoControls
    {
        class ELEUSIS_API PseudoButton :
            public Eleusis::Rectangle
        {
        public:     PseudoButton();

                    void setText(std::string text);
                    std::string getText();

                    void setWidth(double width);

        private:    TextBlock* _textBlock;

        };
    }
}
