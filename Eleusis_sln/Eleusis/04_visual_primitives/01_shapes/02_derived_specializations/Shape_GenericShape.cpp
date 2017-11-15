#include "Shape.h"

using namespace Eleusis;

GenericShape::GenericShape()
{
    _geometry = new Geometry();
}

void GenericShape::moveTo(double x, double y)
{
    _geometry->addPoint_moveTo(x, y);
}

void GenericShape::lineTo(double x, double y)
{
    _geometry->addPoint_lineTo(x, y);
}

void GenericShape::curveTo(double x, double y, double x1, double y1, double x2, double y2)
{
    _geometry->addPoint_curveTo(x, y, x1, y1, x2, y2);
}

void GenericShape::closeLine()
{
    _geometry->addPoint_closePath();
}

void GenericShape::updateShape()
{
    _filterCacheIsStale = true;

    _requestGeometryUpdate();
}

void GenericShape::_updateGeometry()
{
    if (_geometryUpdateExecuted) return;

    _geometryUpdateExecuted = true;
}

void GenericShape::_updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector)
{
    //TODO: We should specify geometry points in Length not in double; also
    // we should add logic for scaling GenericShape vertically and horizontally.

    _updateAbsoluteVectorExecutedOnce = true;

    _absoluteSizeVector = _geometry->getExtent().sizeVector();

    if (_geometry == nullptr) *changed = true;
    else                      *changed = false;
}
