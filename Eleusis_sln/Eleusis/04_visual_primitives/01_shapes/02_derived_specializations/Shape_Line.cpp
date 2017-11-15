#include "Shape.h"

using namespace Eleusis;
// TODO: line extents not calculated correctly; line leaves traces on rendering surface when moved quickly

Line::Line(Length x, Length y) :
    _endPointX (x),
    _endPointY (y)
{
    _requestLayout();
}

void Line::endPointX_set(Length secondPointX)
{
    _endPointX = secondPointX;

    _requestLayout();
}

void Line::endPointY_set(Length secondPointY)
{
    _endPointY = secondPointY;

    _requestLayout();
}

void Line::setPoints(Length x, Length y)
{
    _endPointX = x;
    _endPointY = y;

    _requestLayout();
}

void Line::_updateGeometry()
{
    if (_geometryUpdateExecuted) return;

    delete _geometry; _geometry = new Geometry();
    _geometry->addPoint_moveTo(0, 0);
    _geometry->addPoint_lineTo(_absoluteSizeVector.X, _absoluteSizeVector.Y);

    _filterCacheIsStale = true;
    _geometryUpdateExecuted = true;
}

void Line::_updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector)
{
    _updateAbsoluteVectorExecutedOnce = true;

    Vector l_absoluteSizeVector = { _endPointX.getValueRelativeTo(parentAbsoluteSizeVector.X), _endPointY.getValueRelativeTo(parentAbsoluteSizeVector.Y) };

    if (l_absoluteSizeVector != _absoluteSizeVector) *changed = true;
    else *changed = false;

    _absoluteSizeVector = l_absoluteSizeVector;
}