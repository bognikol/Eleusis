#include "Brush.h"

#include "cairo.h"

using namespace Eleusis;

LinearGradientBrush::LinearGradientBrush() :
    _x1(0),
    _y1(0),
    _x2(100),
    _y2(100),
    _patternIsStale(false)
{
}

LinearGradientBrush::LinearGradientBrush(double x1, double y1, double x2, double y2) :
    _x1(x1),
    _y1(y1),
    _x2(x2),
    _y2(y2),
    _patternIsStale(false)
{
}

void LinearGradientBrush::setGradientStrech(double x1, double y1, double x2, double y2)
{
    if (_x1 != x1) { _x1 = x1; _patternIsStale = true; }
    if (_y1 != y1) { _y1 = y1; _patternIsStale = true; }
    if (_x2 != x2) { _x2 = x2; _patternIsStale = true; }
    if (_y2 != y2) { _y2 = y2; _patternIsStale = true; }

    if (_patternIsStale)
        raiseEvent brushUpdated(this, nullptr);
}

void LinearGradientBrush::addGradientStop(RgbaColor color, double offset)
{
    _gradientStops.push_back(GradientStop(color, offset));
    _patternIsStale = true;

    raiseEvent brushUpdated(this, nullptr);
}

void LinearGradientBrush::resetGradientStops()
{
    _gradientStops.clear();
    if (_pattern) cairo_pattern_destroy(_pattern);
    _pattern = nullptr;

    raiseEvent brushUpdated(this, nullptr);
}

cairo_pattern_t* LinearGradientBrush::getCairoPattern()
{
    if (!_patternIsStale)
        return _pattern;

    if (_pattern) cairo_pattern_destroy(_pattern);
    _pattern = cairo_pattern_create_linear(_x1, _y1, _x2, _y2);
    for (auto gradientStop : _gradientStops)
        cairo_pattern_add_color_stop_rgba(_pattern,
            gradientStop.offset_get(),
            gradientStop.color_get().R_get(),
            gradientStop.color_get().G_get(),
            gradientStop.color_get().B_get(),
            gradientStop.color_get().A_get());
    cairo_matrix_t l_affineMatrix = *_affineTransformation.getAffineMatrix();
    cairo_matrix_invert(&l_affineMatrix);
    cairo_pattern_set_matrix(_pattern, &l_affineMatrix);
    _patternIsStale = false;
    return _pattern;
}

bool LinearGradientBrush::isAffineTransformationApplied()
{
    return _isAffineTranformationApplied;
}

void LinearGradientBrush::resetAffineTransformation()
{
    _affineTransformation.setAffineMatrixToIdentity();
    _isAffineTranformationApplied = false;

    raiseEvent brushUpdated(this, nullptr);
}

void LinearGradientBrush::setAffineTransformation(AffineTransformation* affineTransformation)
{
    _affineTransformation = *affineTransformation;
    _isAffineTranformationApplied = true;

    raiseEvent brushUpdated(this, nullptr);
}

void LinearGradientBrush::multiplyAffineTransformation(AffineTransformation* affineTransformation)
{
    _affineTransformation.multiplyAffineTransformation(affineTransformation);
    _isAffineTranformationApplied = true;

    raiseEvent brushUpdated(this, nullptr);
}
