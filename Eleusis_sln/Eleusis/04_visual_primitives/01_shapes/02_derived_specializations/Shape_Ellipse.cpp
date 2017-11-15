#include "Shape.h"

using namespace Eleusis;


Ellipse::Ellipse(Length width, Length height)
{
    if (width < 0) width = 0;
    if (height < 0) height = 0;

    _width  = width;
    _height = height;

    _requestLayout();
}

void Ellipse::width_set(Length width)
{
    if (width < 0) width = 0;
    _width = width;

    _requestLayout();
}

void Ellipse::height_set(Length height)
{
    if (height < 0) height = 0;
    _height = height;

    _requestLayout();
}

void Ellipse::setWidthAndHeight(Length width, Length height)
{
    if (width < 0) width = 0;
    if (height < 0) height = 0;
    _width = width;
    _height = height;

    _requestLayout();
}    

void Ellipse::_updateGeometry()
{
    if (_geometryUpdateExecuted) return;

    delete _geometry; _geometry = new Geometry();
    _geometry->addEllipse(_absoluteSizeVector.X / 2, _absoluteSizeVector.Y / 2, _absoluteSizeVector.X / 2, _absoluteSizeVector.Y / 2);

    _filterCacheIsStale = true;

    _geometryUpdateExecuted = true;
}

void Ellipse::_updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector)
{
    _updateAbsoluteVectorExecutedOnce = true;

    Vector l_absoluteSizeVector = 
    { 
        _width.getValueRelativeTo(parentAbsoluteSizeVector.X), 
        _height.getValueRelativeTo(parentAbsoluteSizeVector.Y) 
    };

    if (l_absoluteSizeVector != _absoluteSizeVector) *changed = true;
    else *changed = false;

    _absoluteSizeVector = l_absoluteSizeVector;
}