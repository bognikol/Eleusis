
#include "Shape.h"
#include <cmath>

using namespace Eleusis;
using namespace std;

void Shape::fillBrush_set(shared_ptr<Brush> brush)
{   
    if (_fillBrush == brush) return;

    _fillBrush = brush;
    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

shared_ptr<Brush> Shape::fillBrush_get()
{
    return _fillBrush;
}

void Shape::strokeBrush_set(shared_ptr<Brush> brush)
{
    if (_strokeBrush == brush) return;

    _strokeBrush = brush;
    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

shared_ptr<Brush> Shape::strokeBrush_get()
{
    return _strokeBrush;
}

void Shape::shadowBrush_set(shared_ptr<Brush> brush)
{
    if (_shadowBrush == brush) return;

    _shadowBrush = brush;
    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

shared_ptr<Brush> Shape::shadowBrush_get()
{
    return _shadowBrush;
}

void Shape::lineThickenss_set(double thickness)
{
    if (_strokeThickness == thickness) return;

    Rect l_rect = getExtent();
    _strokeThickness = thickness;
    l_rect |= getExtent();

    _filterCacheIsStale = true;
    _requestRendering(l_rect);
}

double Shape::lineThickness_get()
{
    return _strokeThickness;
}

void Shape::fillColor_set(RgbaColor color)
{
    _fillBrush = shared_ptr<Brush>(new SolidColorBrush(color));
    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

void Shape::lineColor_set(RgbaColor color)
{
    _strokeBrush = shared_ptr<Brush>(new SolidColorBrush(color));
    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

void Shape::strokeCapStyle_set(StrokeCapStyle capStyle)
{
    if (_strokeCapStyle == capStyle) return;

    //TODO: getExtent() is not good here; it is not the worst possible scenario.
    Rect l_rect = getExtent();

    _strokeCapStyle = capStyle;

    l_rect |= getExtent();
    _filterCacheIsStale = true;
    _requestRendering(l_rect);
}

StrokeCapStyle Shape::strokeCapStype_get()
{
    return _strokeCapStyle;
}

void Shape::strokeJoinStyle_set(StrokeJoinStyle joinStyle)
{
    if (_strokeJoinStyle == joinStyle) return;

    Rect l_rect = getExtent();

    _strokeJoinStyle = joinStyle;

    l_rect |= getExtent();
    _filterCacheIsStale = true;
    _requestRendering(l_rect);
}

StrokeJoinStyle Shape::strokeJoinStype_get()
{
    return _strokeJoinStyle;
}

void Shape::antialiasMode_set(AntialiasingMode mode)
{
    if (_antialiasMode == mode) return;

    _antialiasMode = mode;

    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

AntialiasingMode Shape::antialiasMode_get()
{
    return _antialiasMode;
}

void Shape::fillRule_set(FillRule fillRule)
{
    if (_fillRule == fillRule) return;

    _fillRule = fillRule;

    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

FillRule Shape::fillRule_get()
{
    return _fillRule;
}

void Shape::strokeDashPattern_set(double line, double gap)
{
    _strokeDashPattern[0] = line;
    _strokeDashPattern[1] = gap;
    _strokeDashPatternLength = 2;

    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

void Shape::strokeDashPattern_set(double line1, double gap1, double line2, double gap2)
{
    _strokeDashPattern[0] = line1;
    _strokeDashPattern[1] = gap1;
    _strokeDashPattern[2] = line2;
    _strokeDashPattern[3] = gap2;
    _strokeDashPatternLength = 4;

    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

void Shape::strokeDashPattern_set(double line1, double gap1, double line2, double gap2, double line3, double gap3)
{
    _strokeDashPattern[0] = line1;
    _strokeDashPattern[1] = gap1;
    _strokeDashPattern[2] = line2;
    _strokeDashPattern[3] = gap2;
    _strokeDashPattern[4] = line3;
    _strokeDashPattern[5] = gap3;
    _strokeDashPatternLength = 6;

    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

void Shape::strokeDashPattern_set(double line1, double gap1, double line2, double gap2, double line3, double gap3, double line4, double gap4)
{
    _strokeDashPattern[0] = line1;
    _strokeDashPattern[1] = gap1;
    _strokeDashPattern[2] = line2;
    _strokeDashPattern[3] = gap2;
    _strokeDashPattern[4] = line3;
    _strokeDashPattern[5] = gap3;
    _strokeDashPattern[6] = line4;
    _strokeDashPattern[7] = gap4;
    _strokeDashPatternLength = 8;

    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

void Shape::resetDashPattern()
{
    _strokeDashPatternLength = 0;
    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

void Shape::shadowRadius_set(double radius)
{
    if (radius < 0) radius = 0;
    if (_shadowRadius == radius) return;

    _shadowRadius = radius;
    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

double Shape::shadowRadius_get()
{
    return _shadowRadius;
}

void Shape::shadowDistance_set(double distance, double angle)
{
    _shadowDistance.X = distance * sin(angle);
    _shadowDistance.Y = distance * cos(angle);

    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

void Shape::shadowDistance_set(Vector distance)
{
    _shadowDistance = distance;
    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

Vector Shape::shadowDistance_get()
{
    return _shadowDistance;
}

void Shape::shadowOpacity_set(double opacity)
{
    if      (opacity < 0) opacity = 0;
    else if (opacity > 1) opacity = 1;

    if (_shadowOpacity == opacity) return;

    _shadowOpacity = opacity;
    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

double Shape::shadowOpacity_get()
{
    return _shadowOpacity;
}

void Shape::opacity_set(double opacity)
{
    if      (opacity < 0) opacity = 0;
    else if (opacity > 1) opacity = 1;

    if (_opacity == opacity) return;

    _opacity = opacity;
    _filterCacheIsStale = true;
    _requestRendering(getExtent());
}

double Shape::opacity_get()
{
    return _opacity;
}
