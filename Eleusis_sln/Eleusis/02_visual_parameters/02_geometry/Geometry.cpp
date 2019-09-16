#include "Geometry.h"
#include <vector>
#include <utility>
#include <cmath>

#include "cairo.h"

using namespace Eleusis;
using namespace std;

namespace Eleusis { extern cairo_t* _cairoUtilityContext; }

const int Geometry::_const_numberOfBytesPerRect = 9 * sizeof(cairo_path_data_t);

Geometry::Geometry() :
    _allocatedBufferSize(_const_initialPathBufferSize)
{
    _originalPath = new cairo_path_t;
    _affineTransformedPath = new cairo_path_t;

    _originalPath->data = new cairo_path_data_t[_const_initialPathBufferSize];
    _originalPath->num_data = 0;
    _originalPath->status = cairo_status_t::CAIRO_STATUS_SUCCESS;
    
    _affineTransformedPath->data = nullptr;
    _affineTransformedPath->num_data = 0;
    _affineTransformedPath->status = cairo_status_t::CAIRO_STATUS_SUCCESS;

	_extentsAreStale = true;
}

Geometry::Geometry(size_t dataSize) :
    _allocatedBufferSize(dataSize)
{
    _originalPath = new cairo_path_t;
    _affineTransformedPath = new cairo_path_t;
    
    _originalPath->data = new cairo_path_data_t[dataSize];
    _originalPath->num_data = 0;
    _originalPath->status = cairo_status_t::CAIRO_STATUS_SUCCESS;

    _affineTransformedPath->data = nullptr;
    _affineTransformedPath->num_data = 0;
    _affineTransformedPath->status = cairo_status_t::CAIRO_STATUS_SUCCESS;

	_extentsAreStale = true;
}

Geometry::Geometry(Region* region) :
    _allocatedBufferSize(region->getRects().size() * _const_numberOfBytesPerRect)
{
    _originalPath = new cairo_path_t;
    _affineTransformedPath = new cairo_path_t;
    
    _originalPath->data = new cairo_path_data_t[_allocatedBufferSize];
    _originalPath->num_data = 0;
    _originalPath->status = cairo_status_t::CAIRO_STATUS_SUCCESS;

    _affineTransformedPath->data = nullptr;
    _affineTransformedPath->num_data = 0;
    _affineTransformedPath->status = cairo_status_t::CAIRO_STATUS_SUCCESS;

	for (auto rect : region->getRects())
	{
		// Adding rects to path
		// Using _appendHeader and _appendPoint for efficiency

		_appendHeader(CAIRO_PATH_MOVE_TO);
		_appendPoint(rect.lowVector.X, rect.lowVector.Y);
		_appendHeader(CAIRO_PATH_LINE_TO);
		_appendPoint(rect.lowVector.X, rect.highVector.Y);
		_appendHeader(CAIRO_PATH_LINE_TO);
		_appendPoint(rect.highVector.X, rect.highVector.Y);
		_appendHeader(CAIRO_PATH_LINE_TO);
		_appendPoint(rect.highVector.X, rect.lowVector.Y);
		_appendHeader(CAIRO_PATH_CLOSE_PATH);
	}

	_extentsAreStale = true;
}

Geometry::Geometry(cairo_path_t* cairoPath)
{
    _originalPath = new cairo_path_t;
    _affineTransformedPath = new cairo_path_t;
    
    _allocatedBufferSize = cairoPath->num_data;
    _originalPath->num_data = cairoPath->num_data;
    _originalPath->data = new cairo_path_data_t[_allocatedBufferSize];
    _originalPath->status = cairoPath->status;

	memcpy(_originalPath->data, cairoPath->data, cairoPath->num_data * sizeof(cairo_path_data_t));

    _affineTransformedPath->data = nullptr;
    _affineTransformedPath->num_data = 0;
    _affineTransformedPath->status = cairo_status_t::CAIRO_STATUS_SUCCESS;

	_extentsAreStale = true;
}

Geometry::~Geometry()
{
    if (_affineTransformedPath->data)
        delete[] _affineTransformedPath->data;
    
    delete[] _originalPath->data;
    
    delete _originalPath;
    delete _affineTransformedPath;

}

void Geometry::_realocateBuffer()
{
    _allocatedBufferSize += _const_pathBufferSizeIncrease;

    cairo_path_data_t* oldData;

    oldData = _originalPath->data;
    _originalPath->data = new cairo_path_data_t[_allocatedBufferSize];
	memcpy(_originalPath->data, oldData, _originalPath->num_data * sizeof(cairo_path_data_t));

    delete[] oldData;

    if (!isAffineTransformationApplied()) return;
 
    oldData = _affineTransformedPath->data;
    _affineTransformedPath->data = new cairo_path_data_t[_allocatedBufferSize];
	memcpy(_affineTransformedPath->data, oldData, _originalPath->num_data * sizeof(cairo_path_data_t));
    delete[] oldData;  
}

void Geometry::_appendPoint(double x, double y)
{
    _originalPath->data[_originalPath->num_data].point.x = x;
    _originalPath->data[_originalPath->num_data].point.y = y;
    _originalPath->num_data++;

    if (!isAffineTransformationApplied()) return;

    _affineTransformedPath->data[_originalPath->num_data].point.x = x;
    _affineTransformedPath->data[_originalPath->num_data].point.x = y;
    _affineTransformation.transformVector(&(_affineTransformedPath->data[_originalPath->num_data].point.x),
		                                  &(_affineTransformedPath->data[_originalPath->num_data].point.y));
    _affineTransformedPath->num_data++;
}

void Geometry::_appendHeader(int type)
{
    cairo_path_data_type_t l_actualType = static_cast<cairo_path_data_type_t>(type);
    
    auto setHeaderHelperFunction = 
        [](cairo_path_t* path, cairo_path_data_type_t l_actualType)
        {
            path->data[path->num_data].header.type = l_actualType;
            switch (l_actualType)
            {
                case cairo_path_data_type_t::CAIRO_PATH_MOVE_TO: 
                    path->data[path->num_data].header.length = 2;
                    break;
                case cairo_path_data_type_t::CAIRO_PATH_LINE_TO:
                    path->data[path->num_data].header.length = 2;
                    break;
                case cairo_path_data_type_t::CAIRO_PATH_CURVE_TO:
                    path->data[path->num_data].header.length = 4;
                    break;
                case cairo_path_data_type_t::CAIRO_PATH_CLOSE_PATH:
                    path->data[path->num_data].header.length = 1;
                    break;
                default:
                    return;
            }
            path->num_data++;
        };

    setHeaderHelperFunction(_originalPath, l_actualType);

    if (!isAffineTransformationApplied()) return;
    
    setHeaderHelperFunction(_affineTransformedPath, l_actualType);
}

void Geometry::_reapplyAffineTransformation()
{
    if (!_affineTransformedPath->data)
         _affineTransformedPath->data = new cairo_path_data_t[_allocatedBufferSize];

    for (int i = 0; i <= _originalPath->num_data - 1; i++)
        _affineTransformedPath->data[i] = _originalPath->data[i];

    _affineTransformedPath->num_data = _originalPath->num_data;

    for (int i = 0; i <= _affineTransformedPath->num_data - 1; i += _affineTransformedPath->data[i].header.length)
    {
        cairo_path_data_t* l_pathData = &(_affineTransformedPath->data[i]);
        switch (l_pathData->header.type)
        {
            case CAIRO_PATH_MOVE_TO:
                _affineTransformation.transformVector(&(l_pathData[1].point.x), &(l_pathData[1].point.y));
                break;
            case CAIRO_PATH_LINE_TO:
                _affineTransformation.transformVector(&(l_pathData[1].point.x), &(l_pathData[1].point.y));
                break;
            case CAIRO_PATH_CURVE_TO:
            {
                _affineTransformation.transformVector(&(l_pathData[1].point.x), &(l_pathData[1].point.y));
                _affineTransformation.transformVector(&(l_pathData[2].point.x), &(l_pathData[2].point.y));
                _affineTransformation.transformVector(&(l_pathData[3].point.x), &(l_pathData[3].point.y));
                break;
            }
            case CAIRO_PATH_CLOSE_PATH:
            default:
                break;
        }
    }
}

void Geometry::_disposeAffineTransformation()
{
    if (!_affineTransformedPath->data) return;
    
    _affineTransformation.setAffineMatrixToIdentity();
    delete[] _affineTransformedPath->data;
    _affineTransformedPath->data = nullptr;
    _affineTransformedPath->num_data = 0;
}

void Geometry::_calculateExtents()
{
    cairo_append_path(_cairoUtilityContext, getOriginalCairoPath());
    cairo_path_extents(_cairoUtilityContext, 
        &(_originalPathExtent.lowVector.X), 
        &(_originalPathExtent.lowVector.Y),
        &(_originalPathExtent.highVector.X), 
        &(_originalPathExtent.highVector.Y));
    cairo_new_path(_cairoUtilityContext);

	if (isAffineTransformationApplied())
	{
		cairo_append_path(_cairoUtilityContext, getCairoPath());
		cairo_path_extents(_cairoUtilityContext,
            &(_affineTransformedPathExtent.lowVector.X),
            &(_affineTransformedPathExtent.lowVector.Y),
            &(_affineTransformedPathExtent.highVector.X),
            &(_affineTransformedPathExtent.highVector.Y));
		cairo_new_path(_cairoUtilityContext);
	}

	_extentsAreStale = false;
}

cairo_path_t* Geometry::getCairoPath()
{
    if (isAffineTransformationApplied()) return _affineTransformedPath;
    return _originalPath;
}

cairo_path_t* Geometry::getOriginalCairoPath()
{
    return _originalPath;
}

Rect Geometry::getExtent()
{
	if (_extentsAreStale)
		_calculateExtents();

    if (isAffineTransformationApplied()) return _affineTransformedPathExtent;
    return _originalPathExtent;
}

Rect Geometry::getOriginalExtent()
{
	if (_extentsAreStale)
		_calculateExtents();

    return _originalPathExtent;
}

int Geometry::addPoint_moveTo(double x, double y)
{
    if (_originalPath->num_data + 2 > _allocatedBufferSize - 1)
        _realocateBuffer();

    int index = _originalPath->num_data;

    _appendHeader(CAIRO_PATH_MOVE_TO);
    _appendPoint (x, y);
	_extentsAreStale = true;

    return index;
}

int Geometry::addPoint_lineTo(double x, double y)
{
    if (_originalPath->num_data + 2 > _allocatedBufferSize - 1)
        _realocateBuffer();

    int index = _originalPath->num_data;

    _appendHeader(CAIRO_PATH_LINE_TO);
    _appendPoint (x, y);
	_extentsAreStale = true;

    return index;
}

int Geometry::addPoint_curveTo(double x1, double y1, double x2, double y2, double x, double y)
{
    if (_originalPath->num_data + 4 > _allocatedBufferSize - 1)
        _realocateBuffer();

    int index = _originalPath->num_data;

    _appendHeader(CAIRO_PATH_CURVE_TO);
    _appendPoint (x1, y1);
    _appendPoint (x2, y2);
    _appendPoint (x, y);
	_extentsAreStale = true;

    return index;
}

int Geometry::addPoint_closePath()
{
    if (_originalPath->num_data + 1 > _allocatedBufferSize - 1)
        _realocateBuffer();

    int index = _originalPath->num_data;

    _appendHeader(CAIRO_PATH_CLOSE_PATH);
	_extentsAreStale = true;

    return index;
}

void Geometry::updatePoint(int index, double x, double y)
{
    _originalPath->data[index].point.x = x;
    _originalPath->data[index].point.y = y;

    if (isAffineTransformationApplied())
    {
        _affineTransformedPath->data[index].point.x = x;
        _affineTransformedPath->data[index].point.x = y;
        _affineTransformation.transformVector(&(_affineTransformedPath->data[index].point.x),
                                              &(_affineTransformedPath->data[index].point.y));
    }

	_extentsAreStale = true;
}

void Geometry::addRectangle(double x_low, double y_low, double x_high, double y_high, double r)
{
    if (r == 0)
    {
        addPoint_moveTo(x_low, y_low);
        addPoint_lineTo(x_low, y_high);
        addPoint_lineTo(x_high, y_high);
        addPoint_lineTo(x_high, y_low);
        addPoint_closePath();
    }
    else
    {
        double l_p = r * _const_semicircleBezier;

        addPoint_moveTo (x_low, y_low + r);
        addPoint_curveTo(x_low, y_low + r - l_p, x_low + r - l_p, y_low, x_low + r, y_low);
        addPoint_lineTo (x_high - r, y_low);
        addPoint_curveTo(x_high - r + l_p, y_low, x_high, y_low + r - l_p, x_high, y_low + r);
        addPoint_lineTo (x_high, y_high - r);
        addPoint_curveTo(x_high, y_high - r + l_p, x_high - r + l_p, y_high, x_high - r, y_high);
        addPoint_lineTo (x_low + r, y_high);
        addPoint_curveTo(x_low + r - l_p, y_high, x_low, y_high - r + l_p, x_low, y_high - r);
        addPoint_closePath();
    }

	_extentsAreStale = true;
}

void Geometry::addCircle(double x, double y, double r)
{
    double l_p = r * _const_semicircleBezier;

    addPoint_moveTo(x, y - r);
    addPoint_curveTo(x + l_p, y - r,   x + r,   y - l_p, x + r, y    );
    addPoint_curveTo(x + r,   y + l_p, x + l_p, y + r,   x,     y + r);
    addPoint_curveTo(x - l_p, y + r,   x - r,   y + l_p, x - r, y    );
    addPoint_curveTo(x - r,   y - l_p, x - l_p, y - r,   x,     y - r);

	_extentsAreStale = true;
}

void Geometry::addEllipse(double x, double y, double rx, double ry)
{
    double l_px = rx / _const_ellipseBezier;

    addPoint_moveTo(x, y - ry);
    addPoint_curveTo(x + l_px, y - ry, x + l_px, y + ry, x, y + ry);
    addPoint_curveTo(x - l_px, y + ry, x - l_px, y - ry, x, y - ry);

	_extentsAreStale = true;
}

void Geometry::addPolygon(double x, double y, double r, int numberOfVerticies, bool internalRadius)
{
    double l_n = static_cast<double>(numberOfVerticies);

    if (internalRadius) r = r / (cos(const_2pi / l_n));

    int l_lowIndex = -(numberOfVerticies / 2);
    int l_highIndex = numberOfVerticies / 2 + numberOfVerticies % 2 - 1;

    {
        double l_x = sin((1 - 2 * l_lowIndex) * Geometry::const_pi / l_n) * r + x;
        double l_y = cos((1 - 2 * l_lowIndex) * Geometry::const_pi / l_n) * r + y;

        addPoint_moveTo(l_x, l_y);
    }

    for (int i = l_lowIndex + 1; i <= l_highIndex; i++)
    {
        double l_x = sin((1 - 2 * i) * Geometry::const_pi / l_n) * r + x;
        double l_y = cos((1 - 2 * i) * Geometry::const_pi / l_n) * r + y;

        addPoint_lineTo(l_x, l_y);
    }

    addPoint_closePath();

	_extentsAreStale = true;
}

bool Geometry::isAffineTransformationApplied()
{
    if (_affineTransformedPath->data) return true;
    return false;
}

void Geometry::resetAffineTransformation()
{
    _disposeAffineTransformation();
	_extentsAreStale = true;
}

void Geometry::setAffineTransformation(AffineTransformation* affineTransformation)
{
    _affineTransformation = *affineTransformation;
    _reapplyAffineTransformation();
	_extentsAreStale = true;
}

void Geometry::multiplyAffineTransformation(AffineTransformation* affineTransformation)
{
    _affineTransformation.multiplyAffineTransformation(affineTransformation);
    _reapplyAffineTransformation();
	_extentsAreStale = true;
}
