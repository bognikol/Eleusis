#pragma once

#include "dllexport.h"

#include "Shape.h"
#include "TextBlock.h"


namespace Eleusis
{
    namespace PseudoControls
    {
        class ELEUSIS_API PseudoSlider :
            public Rectangle
        {
        public:
            PseudoSlider();

            void setValue(double value);
            double getValue();

            void setMin(double min);
            double getMin();

            void setMax(double max);
            double getMax();

            void setText(std::string text);
            std::string getText();

            Event<PseudoSlider*, EventArgs*> valueChanged;

        private:
            double _value = 50;
            double _min = 0;
            double _max = 100;

            std::string _text = "Slider";

            bool _mouseDownOnHandle = false;

            TextBlock* _valueTextBlock;
            Rectangle* _sliderRect;
            Rectangle* _handleRect;
        };
    }
}