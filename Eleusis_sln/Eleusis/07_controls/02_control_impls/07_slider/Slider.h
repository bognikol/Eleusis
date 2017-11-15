#pragma once

#include "SkinableControl.h"
#include "SliderSkin.h"

namespace Eleusis
{
    class ELEUSIS_API Slider :
        public SkinableControl<SliderSkin>
    {
    private:
        double _minValue = 0;
        double _maxValue = 100;
        double _value = 0;

        virtual void _applySkin();

    public:
        Slider();
        virtual ~Slider() { };

        void minValue_set(double value);
        double minValue_get();

        void maxValue_set(double value);
        double maxValue_get();

        void value_set(double value);
        double value_get();
        
        Event<Slider*, EventArgs*> valueChanged;
    };
}