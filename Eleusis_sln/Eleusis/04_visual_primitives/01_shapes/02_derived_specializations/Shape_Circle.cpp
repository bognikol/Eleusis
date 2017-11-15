#include "Shape.h"
#include <cmath>

using namespace Eleusis;


Circle::Circle(Length radius)
{
    if (radius < 0) radius = 0;
    _radius = radius;

    _requestLayout();
}

void Circle::radius_set(Length radius)
{
    if (radius < 0) radius = 0;
    _radius = radius;

    _requestParentLayout();
}

void Circle::_updateGeometry() 
{
    if (_geometryUpdateExecuted) return;

    double l_radius = std::fmin(_absoluteSizeVector.X / 2, _absoluteSizeVector.Y / 2);

    delete _geometry; _geometry = new Geometry();
    _geometry->addCircle(l_radius, l_radius, l_radius);

    _filterCacheIsStale = true;

    _geometryUpdateExecuted = true;
}

void Circle::_updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector)
{
    _updateAbsoluteVectorExecutedOnce = true;

    Vector l_absoluteSizeVector;
    switch (_radius.getType())
    {
    case PointType::DeviceIndependent:
    {
        l_absoluteSizeVector.X = 2 * _radius;
        l_absoluteSizeVector.Y = 2 * _radius;
        break;
    }
    case PointType::Fraction:
    {
        double l_effectiveAbsoluteSize = parentAbsoluteSizeVector.X;
        if (parentAbsoluteSizeVector.Y < parentAbsoluteSizeVector.X)
            l_effectiveAbsoluteSize = parentAbsoluteSizeVector.Y;
        l_absoluteSizeVector.X = 2 * _radius / 100 * l_effectiveAbsoluteSize; 
        l_absoluteSizeVector.Y = l_absoluteSizeVector.X;
        break;
    }
    }

    if (l_absoluteSizeVector != _absoluteSizeVector) *changed = true;
    else *changed = false;

    _absoluteSizeVector = l_absoluteSizeVector;
}
