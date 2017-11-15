#pragma once

#include "dllexport.h"

#include "03_brushing/RgbaColor.h"

namespace Eleusis
{
    template <typename Type>
    class AnimationComponent
    {

    private:    Type   _startValue;
                bool   _startValueIsExplicitlySet = false;
                Type   _endValue;
                bool   _active = false;

    public:     void   startValue(Type startValue) { _startValue = startValue; _startValueIsExplicitlySet = true; };
                Type   startValue() { return _startValue; };

                void   endValue(Type endValue) { _endValue = endValue; _active = true; };
                Type   endValue() { return _endValue; };

                void   setActive() { _active = true; };
                void   setInactive() { _active = false; };
                bool   isActive() { return _active; }

				void   clear() { _active = false; _startValueIsExplicitlySet = false; }

                bool   isUsingDefaultStartValue() { return !_startValueIsExplicitlySet; };
    };

    /*  
    Specialization of AnimationComponenet for RgbaColor is needed. Generic AnimationComponent uses current value of the animated property
    for start value if start value is not explicitely set. VisualPrimitives can be animated only if they use SolidColorBrush;
    animation of other brushes are currently not supported. Because RgbaColor can be animated on a Shape that is rendered 
    using different Brush then SolidColorBrush, it is neccessary to specify start value for RgbaColor as start value cannot be immplicitelly
    deduced.
    */

    template <>
    class AnimationComponent<RgbaColor>
    {
    private:    RgbaColor   _startValue;
                bool        _startValueIsExplicitlySet = false;;
                RgbaColor   _endValue;
                bool        _endValueIsExplicitlySet = false;
                bool        _active = false;

    public:     void        startValue(RgbaColor startValue) { _startValue = startValue; _startValueIsExplicitlySet = true; };
                RgbaColor   startValue() { return _startValue; };

                void        endValue(RgbaColor endValue) { _endValue = endValue; _endValueIsExplicitlySet = true; _active = true; };
                RgbaColor   endValue() { return _endValue; };

                void        setActive() { _active = true; };
                void        setInactive() { _active = false; };
                bool        isActive() { return _active && _startValueIsExplicitlySet && _endValueIsExplicitlySet; }

                void        clear() { _active = false; _startValueIsExplicitlySet = false; _endValueIsExplicitlySet = false; }

                bool        isUsingDefaultStartValue() { return false; };
    };
}


