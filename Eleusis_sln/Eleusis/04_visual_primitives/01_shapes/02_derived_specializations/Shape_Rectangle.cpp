#include "Shape.h"
#include <algorithm>

using namespace Eleusis;
using namespace std;

Rectangle::Rectangle(Length width, Length height, Length cornerRadius)
{
    if (width < 0)  width = 0;
    _width = width;
    if (height < 0) height = 0;
    _height = height;
    if (cornerRadius < 0) cornerRadius = 0;
    _cornerRadius = cornerRadius;

    if (_cornerRadius.getType() == PointType::Fraction)
        if (_cornerRadius > 100)
            _cornerRadius = 100;
     
    _requestLayout();
}

void Rectangle::width_set(Length width)
{
    if (width < 0)  width = 0;
    _width = width;
    
	_requestParentLayout();
}

void Rectangle::height_set(Length height)
{
    if (height < 0) height = 0;
    _height = height;

    _requestParentLayout();
}

void Rectangle::setWidthAndHeight(Length width, Length height)
{
    if (width < 0)  width = 0;
    _width = width;
    if (height < 0) height = 0;
    _height = height;

    _requestLayout();
}

void Rectangle::cornerRadius_set(Length cornerRadius)
{
    if (cornerRadius < 0) cornerRadius = 0;
    _cornerRadius = cornerRadius;

    if (_cornerRadius.getType() == PointType::Fraction)
        if (_cornerRadius > 100)
            _cornerRadius = 100;

    _requestGeometryUpdate();
}

void Rectangle::_updateGeometry()
{
    if (_geometryUpdateExecuted) return;

    double l_effectiveCornerRadius = 0;

    if (_cornerRadius.getType() == PointType::Fraction)
    {
        l_effectiveCornerRadius = min(_absoluteSizeVector.Y, _absoluteSizeVector.X)  / 2.0 * _cornerRadius / 100.0;
    }
    else
    {
        l_effectiveCornerRadius = _cornerRadius;
        if (l_effectiveCornerRadius >= min(_absoluteSizeVector.Y, _absoluteSizeVector.X) / 2.0)
            l_effectiveCornerRadius  = min(_absoluteSizeVector.Y, _absoluteSizeVector.X) / 2.0;            
    }



    delete _geometry; _geometry = new Geometry();
    _geometry->addRectangle(0, 0, _absoluteSizeVector.X, _absoluteSizeVector.Y, l_effectiveCornerRadius);
   
    _filterCacheIsStale = true;
    _geometryUpdateExecuted = true;
}

void Rectangle::_updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector)
{
    _updateAbsoluteVectorExecutedOnce = true;

    double l_width = _width.getValueRelativeTo(parentAbsoluteSizeVector.X);
    double l_height = _height.getValueRelativeTo(parentAbsoluteSizeVector.Y);

    Vector l_absoluteSizeVector = { l_width, l_height };

    if (l_absoluteSizeVector != _absoluteSizeVector) *changed = true;
    else *changed = false;

    _absoluteSizeVector = l_absoluteSizeVector;
}