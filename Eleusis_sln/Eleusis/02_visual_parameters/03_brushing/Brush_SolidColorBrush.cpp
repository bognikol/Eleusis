#include "Brush.h"

#include "cairo.h"

using namespace Eleusis;

Brush::~Brush()
{
    if (_pattern) cairo_pattern_destroy(_pattern);
    _pattern = nullptr;
}

SolidColorBrush::SolidColorBrush() :
    Color()
{
    _doObjectConstruction();
}

SolidColorBrush::SolidColorBrush(double R, double G, double B) :
    Color(R, G, B)
{
    _doObjectConstruction();
}

SolidColorBrush::SolidColorBrush(double R, double G, double B, double A) :
    Color(R, G, B, A)
{
    _doObjectConstruction();
}

SolidColorBrush::SolidColorBrush(int R, int G, int B) :
    Color(R, G, B)
{
    _doObjectConstruction();
}

SolidColorBrush::SolidColorBrush(int R, int G, int B, int A) :
    Color(R, G, B, A)
{
    _doObjectConstruction();
}

SolidColorBrush::SolidColorBrush(RgbaColor color) :
    Color(color)
{
    _doObjectConstruction();
}

void SolidColorBrush::_initializeEventHandlers()
{
    _colorUpdatedHandler =
        [this](RgbaColor* sender, EventArgs* e)
    {
        if (_pattern) cairo_pattern_destroy(_pattern);
        _pattern = cairo_pattern_create_rgba(sender->R_get(),
                                             sender->G_get(),
                                             sender->B_get(),
                                             sender->A_get());

        raiseEvent brushUpdated(this, nullptr);
    };
}

void SolidColorBrush::_doObjectConstruction()
{
    _initializeEventHandlers();
    Color.colorUpdated += _colorUpdatedHandler;
    _pattern = cairo_pattern_create_rgba(Color.R_get(),
                                         Color.G_get(),
                                         Color.B_get(),
                                         Color.A_get());
}

cairo_pattern_t* SolidColorBrush::getCairoPattern()
{
    return _pattern;
}
