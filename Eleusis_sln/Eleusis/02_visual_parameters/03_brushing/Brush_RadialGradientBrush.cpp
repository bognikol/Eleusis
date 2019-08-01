#include "Brush.h"

#include "cairo.h"

using namespace Eleusis;

RadialGradientBrush::RadialGradientBrush()
    : _x1(0), _y1(0), _r1(0), _x2(0), _y2(0), _r2(0), _patternIsStale(false)
{
}

RadialGradientBrush::RadialGradientBrush(double x1, double y1, double r1, double x2, double y2, double r2) :
    _x1(x1),
    _y1(y1),
    _r1(r1),
    _x2(x2),
    _y2(y2),
    _r2(r2),
    _patternIsStale(false)
{
}

RadialGradientBrush::RadialGradientBrush(double x, double y, double r) :
    _x1(x),
    _y1(y),
    _r1(0),
    _x2(x),
    _y2(y),
    _r2(r),
    _patternIsStale(false)
{
}

void RadialGradientBrush::setGradientStrech(double x1, double y1, double r1, double x2, double y2, double r2)
{
    if (_x1 != x1) { _x1 = x1; _patternIsStale = true; }
    if (_y1 != y1) { _y1 = y1; _patternIsStale = true; }
    if (_r1 != r1) { _r1 = r1; _patternIsStale = true; }
    if (_x2 != x2) { _x2 = x2; _patternIsStale = true; }
    if (_y2 != y2) { _y2 = y2; _patternIsStale = true; }
    if (_r2 != r2) { _r2 = r2; _patternIsStale = true; }

    if (_patternIsStale)
        raiseEvent brushUpdated(this, nullptr);
}

void RadialGradientBrush::setGradientStrech(double x, double y, double r)
{
    if (_x1 != x) { _x1 = x; _patternIsStale = true; }
    if (_y1 != y) { _y1 = y; _patternIsStale = true; }
    if (_r1 != 0) { _r1 = 0; _patternIsStale = true; }
    if (_x2 != x) { _x2 = x; _patternIsStale = true; }
    if (_y2 != y) { _y2 = y; _patternIsStale = true; }
    if (_r2 != r) { _r2 = r; _patternIsStale = true; }

    if (_patternIsStale)
        raiseEvent brushUpdated(this, nullptr);
}

void RadialGradientBrush::addGradientStop(RgbaColor color, double offset)
{
    _gradientStops.push_back(GradientStop(color, offset));
    _patternIsStale = true;

    raiseEvent brushUpdated(this, nullptr);
}

void RadialGradientBrush::resetGradientStops()
{
    _gradientStops.clear();
    if (_pattern) cairo_pattern_destroy(_pattern);
    _pattern = nullptr;

    raiseEvent brushUpdated(this, nullptr);
}

cairo_pattern_t* RadialGradientBrush::getCairoPattern()
{
    if (!_patternIsStale)
        return _pattern;

    if (_pattern) cairo_pattern_destroy(_pattern);
    _pattern = cairo_pattern_create_radial(_x1, _y1, _r1, _x2, _y2, _r2);
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

bool RadialGradientBrush::isAffineTransformationApplied()
{
    return _isAffineTranformationApplied;
}

void RadialGradientBrush::resetAffineTransformation()
{
    if (!_isAffineTranformationApplied) return;

    _affineTransformation.setAffineMatrixToIdentity();
    _patternIsStale = true;
    _isAffineTranformationApplied = false;

    raiseEvent brushUpdated(this, nullptr);
}

void RadialGradientBrush::setAffineTransformation(AffineTransformation* affineTransformation)
{
    _affineTransformation = *affineTransformation;
    _patternIsStale = true;
    _isAffineTranformationApplied = true;

    raiseEvent brushUpdated(this, nullptr);
}

void RadialGradientBrush::multiplyAffineTransformation(AffineTransformation* affineTransformation)
{
    _affineTransformation.multiplyAffineTransformation(affineTransformation);
    _patternIsStale = true;
    _isAffineTranformationApplied = true;

    raiseEvent brushUpdated(this, nullptr);
}
