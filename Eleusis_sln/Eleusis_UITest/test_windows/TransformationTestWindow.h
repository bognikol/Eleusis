#pragma once

#include "Window.h"
#include "TextBlock.h"
#include "PseudoSlider.h"

namespace Eleusis
{
    namespace Test
    {
        class TransformationTestWindow :
            public Window
        {
        public:
            TransformationTestWindow();

        private:
            TextualShape* _textualShape;
            TextBlock* _textBlock;

            PseudoControls::PseudoSlider* _topSlider;
            PseudoControls::PseudoSlider* _leftSlider;
            PseudoControls::PseudoSlider* _rotationSlider;
            PseudoControls::PseudoSlider* _shearXSlider;
            PseudoControls::PseudoSlider* _shearYSlider;
        };
    }
}