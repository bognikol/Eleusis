#include "Shape.h"
#include <cmath>

using namespace Eleusis;
using namespace std;

Polygon::Polygon(Length radius, int numberOfVerticies,  PolygonRadiusContext context)
{
    if (numberOfVerticies < 3)   numberOfVerticies = 3;
    if (numberOfVerticies > 100) numberOfVerticies = 100;
    if (radius < 0) radius = 1;

    _radius = radius;
    _numberOfVerticies = numberOfVerticies;
    _context = context;

    _requestLayout();
}

void Polygon::radius_set(Length radius)
{
    if (radius == _radius) return;
    if (radius < 0) radius = 1;
    _radius = radius;

    _requestLayout();
}

void Polygon::_updateGeometry()
{
    if (_geometryUpdateExecuted) return;

    bool l_internalRadius = false;
    if (_context == PolygonRadiusContext::Internal) l_internalRadius = true;

    Rect l_polygonExtent;
    {
        Geometry l_extentGeometry;
        l_extentGeometry.addPolygon(0, 0, _absoluteSizeVector.X / 2.0, _numberOfVerticies, false);
        l_polygonExtent = l_extentGeometry.getExtent();
    }

    delete _geometry; _geometry = new Geometry();
    _geometry->addPolygon(-l_polygonExtent.lowVector.X, -l_polygonExtent.lowVector.Y, _radius, _numberOfVerticies, l_internalRadius);

    _filterCacheIsStale = true;
    _geometryUpdateExecuted = true;
}

void Polygon::_updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector)
{
    //TODO: Absolute size vector is set to bounding box of circumcircle, not polygon itself. This should be fixed.

    _updateAbsoluteVectorExecutedOnce = true;

    double l_effectiveAbsoluteSize = parentAbsoluteSizeVector.X;
    if (parentAbsoluteSizeVector.Y < parentAbsoluteSizeVector.X)
        l_effectiveAbsoluteSize = parentAbsoluteSizeVector.Y;

    double r = _radius.getValueRelativeTo(l_effectiveAbsoluteSize);

    if (_context == PolygonRadiusContext::Internal)
        r = r / (cos(Geometry::const_2pi / _numberOfVerticies));

    Vector l_absoluteSizeVector = { 2 * r, 2 * r };

    if (l_absoluteSizeVector != _absoluteSizeVector) *changed = true;
    else *changed = false;

    _absoluteSizeVector = l_absoluteSizeVector;
}