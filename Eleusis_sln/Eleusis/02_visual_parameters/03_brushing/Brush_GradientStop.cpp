#include "Brush.h"

using namespace Eleusis;

GradientStop::GradientStop() { }

GradientStop::GradientStop(RgbaColor & color, double offset) : _color(color), _offset(offset) { }

void GradientStop::color_set(RgbaColor & color) { _color = color; }

RgbaColor GradientStop::color_get() { return _color; }

void GradientStop::offset_set(double offset)
{
    if (offset <= 0.0 && _offset != 0.0)
    {
        _offset = 0.0;
        return;
    }
    if (offset >= 1.0 && _offset != 1.0)
    {
        _offset = 1.0;
        return;
    }
    _offset = offset;
}

double GradientStop::offset_get() { return _offset; }




