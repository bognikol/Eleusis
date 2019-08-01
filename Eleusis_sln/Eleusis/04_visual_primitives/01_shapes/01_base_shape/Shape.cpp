#include "Shape.h"
#include "03_extensions/cairo/cairo-ext.h"

#include "cairo.h"

#include <algorithm>

using namespace Eleusis;
using namespace std;

namespace Eleusis { extern cairo_t* _cairoUtilityContext; }

namespace Eleusis
{
    class CairoConverter
    {
    public:
        static cairo_antialias_t AntialiasingModeTo_cairo_antialias_t(AntialiasingMode mode);
        static AntialiasingMode cairo_antialias_t_ToAntialiasingMode(cairo_antialias_t mode);
        
        static cairo_line_cap_t StrokeCapStyleTo_cairo_line_cap_t(StrokeCapStyle mode);
        static StrokeCapStyle cairo_line_cap_t_ToStrokeCapStyle(cairo_line_cap_t mode);
        
        static cairo_line_join_t StrokeJoinStyleTo_cairo_line_join_t(StrokeJoinStyle mode);
        static StrokeJoinStyle cairo_line_join_t_ToStrokeJoinStyle(cairo_line_join_t mode);
        
        static cairo_fill_rule_t FillRuleTo_cairo_fill_rule_t(FillRule mode);
        static FillRule cairo_fill_rule_t_ToFillRule(cairo_fill_rule_t mode);
    };
}

Shape::Shape()
{
}

Shape::Shape(Brush* interiorBrush, Brush* borderBrush, Brush* shadowBrush) :
    _fillBrush      (interiorBrush),
    _strokeBrush    (borderBrush),
    _shadowBrush    (shadowBrush)
{
}

Shape::~Shape()
{
    delete _geometry;
    _destroyFilterCache();
}

Rect Shape::getExtent()
{
    if (!_geometry || !_geometry->isAffineTransformationApplied()) return Rect();

    Rect l_extent;

    l_extent = _geometry->getExtent();

    double l_lineHalfThickness = _strokeThickness / 2;

    if (_shadowBrush)
    {
        l_extent.lowVector.X  -= max(static_cast<int>(l_lineHalfThickness), static_cast<int>(l_lineHalfThickness + _shadowRadius - _shadowDistance.X));
        l_extent.lowVector.Y  -= max(static_cast<int>(l_lineHalfThickness), static_cast<int>(l_lineHalfThickness + _shadowRadius - _shadowDistance.Y));
        l_extent.highVector.X += max(static_cast<int>(l_lineHalfThickness), static_cast<int>(l_lineHalfThickness + _shadowRadius + _shadowDistance.X));
        l_extent.highVector.Y += max(static_cast<int>(l_lineHalfThickness), static_cast<int>(l_lineHalfThickness + _shadowRadius + _shadowDistance.Y));
    }
    else
    {
        l_extent.lowVector.X  -= l_lineHalfThickness;
        l_extent.lowVector.Y  -= l_lineHalfThickness;
        l_extent.highVector.X += l_lineHalfThickness;
        l_extent.highVector.Y += l_lineHalfThickness;
    }

    return l_extent;
}

Rect Shape::getFullExtent()
{
    Rect l_fullExtent = getExtent();
    Rect l_vpExtent;

    Node* l_child = firstChild();
    if (!l_child) return l_fullExtent;

    Node* l_lastDescendant = lastDescendant();

    while (true)
    {
        if (l_child->isVisualPrimitive())
        {
            l_vpExtent = static_cast<VisualPrimitive*>(l_child)->getExtent();
            if (!l_vpExtent.isZero())
            {
                if (l_fullExtent.isZero())
                    l_fullExtent = static_cast<VisualPrimitive*>(l_child)->getExtent();
                else
                    l_fullExtent |= static_cast<VisualPrimitive*>(l_child)->getExtent();
            }
        }
        if (l_child == l_lastDescendant) break;
        l_child = l_child->next();
        if (!l_child) break;
    }

    return l_fullExtent;
}

Rect Shape::getGeometryExtent()
{
    if (!_geometry) return Rect(0, 0, 0, 0);
    return _geometry->getExtent();
}

Rect Shape::getLineExtent()
{
    if (!_geometry)          return Rect(0, 0, 0, 0);

    Rect l_rectExtent;

    cairo_append_path       (_cairoUtilityContext, _geometry->getCairoPath());
    cairo_set_line_cap      (_cairoUtilityContext, CairoConverter::StrokeCapStyleTo_cairo_line_cap_t(_strokeCapStyle));
    cairo_set_line_join     (_cairoUtilityContext, CairoConverter::StrokeJoinStyleTo_cairo_line_join_t(_strokeJoinStyle));
    cairo_set_line_width    (_cairoUtilityContext, _strokeThickness);
    cairo_set_dash          (_cairoUtilityContext, _strokeDashPattern, _strokeDashPatternLength, 0);
    cairo_stroke_extents    (_cairoUtilityContext, &(l_rectExtent.lowVector.X), &(l_rectExtent.lowVector.Y), &(l_rectExtent.highVector.X), &(l_rectExtent.highVector.Y));
    cairo_new_path          (_cairoUtilityContext);

    return l_rectExtent;
}

Rect Shape::getFillExtent()
{
    if (!_geometry)          return Rect(0, 0, 0, 0);

    Rect l_rectExtent;

    cairo_append_path       (_cairoUtilityContext, _geometry->getCairoPath());
    cairo_set_fill_rule     (_cairoUtilityContext, CairoConverter::FillRuleTo_cairo_fill_rule_t(_fillRule));
    cairo_fill_extents      (_cairoUtilityContext, &(l_rectExtent.lowVector.X), &(l_rectExtent.lowVector.Y), &(l_rectExtent.highVector.X), &(l_rectExtent.highVector.Y));
    cairo_new_path          (_cairoUtilityContext);

    return l_rectExtent;
}

bool Shape::contains(Vector vector)
{
    return contains(vector.X, vector.Y);
}

bool Shape::contains(double x, double y)
{
    if (!getExtent().contains(x, y)) return false;
    if (!_clippingRect.isZero() && !_clippingRect.contains(x, y)) return false;

    cairo_append_path       (_cairoUtilityContext, _geometry->getCairoPath());
    cairo_set_line_cap      (_cairoUtilityContext, CairoConverter::StrokeCapStyleTo_cairo_line_cap_t(_strokeCapStyle));
    cairo_set_line_join     (_cairoUtilityContext, CairoConverter::StrokeJoinStyleTo_cairo_line_join_t(_strokeJoinStyle));
    cairo_set_line_width    (_cairoUtilityContext, _strokeThickness);
    cairo_set_dash          (_cairoUtilityContext, _strokeDashPattern, _strokeDashPatternLength, 0);
    cairo_set_fill_rule     (_cairoUtilityContext, CairoConverter::FillRuleTo_cairo_fill_rule_t(_fillRule));
    
    if (_fillBrush)
    {
        cairo_set_source    (_cairoUtilityContext, _fillBrush->getCairoPattern());
        if (cairo_in_fill   (_cairoUtilityContext, x, y))
        {
            cairo_new_path  (_cairoUtilityContext);
            return true;
        }
    }
        
    if (_strokeBrush)
    {
        cairo_set_source    (_cairoUtilityContext, _strokeBrush->getCairoPattern());
        if (cairo_in_stroke (_cairoUtilityContext, x, y))
        {
            cairo_new_path  (_cairoUtilityContext);
            return true;
        }
    }

    return false;
}

void Shape::_prepeareFilterCache()
{
    Rect l_visualPrimitiveExtent = getExtent();

    if (!_filterCacheCairoSurface)
    {

        // TODO: What if l_visualPrimitiveExtent.width() and/or l_visualPrimitiveExtent.height() are substantially larger then rendering surface?
        // In that case we will spare memory by allocating too large _filterCacheCairoSurface. 
        _filterCacheCairoSurface = cairo_image_surface_create(cairo_format_t::CAIRO_FORMAT_ARGB32, static_cast<int>(l_visualPrimitiveExtent.width()), static_cast<int>(l_visualPrimitiveExtent.height()));
        _filterCacheCairoContext = cairo_create(_filterCacheCairoSurface);
    }
    else
    {
        if (cairo_image_surface_get_width (_filterCacheCairoSurface) != l_visualPrimitiveExtent.width()  || 
            cairo_image_surface_get_height(_filterCacheCairoSurface) != l_visualPrimitiveExtent.height())
        {
            _destroyFilterCache();
            _filterCacheCairoSurface = cairo_image_surface_create(cairo_format_t::CAIRO_FORMAT_ARGB32, static_cast<int>(l_visualPrimitiveExtent.width()), static_cast<int>(l_visualPrimitiveExtent.height()));
            _filterCacheCairoContext = cairo_create(_filterCacheCairoSurface);
        }
    }
}

void  Shape::_destroyFilterCache()
{
    if (_filterCacheCairoContext) cairo_destroy         (_filterCacheCairoContext);
    if (_filterCacheCairoSurface) cairo_surface_destroy (_filterCacheCairoSurface);
}

void Shape::_doCairoDrawing(cairo_t* cairoContext)
{
    Region l_region;

    if (!_clippingRect.isZero())
    {

    }

    bool l_cacheNeeded = false;

    if (_shadowBrush) l_cacheNeeded = true;
    else
        if (_opacity != 0 && _opacity != 1) l_cacheNeeded = true;

    if (l_cacheNeeded)
    {
        _prepeareFilterCache();
        if (_filterCacheIsStale)
        {
            _filterCacheIsStale = false;

            Vector l_offsetVector = getApsoluteOffsetVector() - getExtent().lowVector;
            cairo_translate(_filterCacheCairoContext, l_offsetVector.X, l_offsetVector.Y);

            cairo_ext_reset_surface   (_filterCacheCairoSurface);

            cairo_set_antialias     (_filterCacheCairoContext, CairoConverter::AntialiasingModeTo_cairo_antialias_t(_antialiasMode));

            if (_shadowBrush)
            {
                cairo_translate         (_filterCacheCairoContext, _shadowDistance.X, _shadowDistance.Y);
                cairo_append_path       (_filterCacheCairoContext, _geometry->getOriginalCairoPath());
                cairo_translate         (_filterCacheCairoContext, -_shadowDistance.X, -_shadowDistance.Y);
                cairo_set_source        (_filterCacheCairoContext, _shadowBrush->getCairoPattern()); 
                cairo_set_line_cap      (_filterCacheCairoContext, CairoConverter::StrokeCapStyleTo_cairo_line_cap_t(_strokeCapStyle));
                cairo_set_line_join     (_filterCacheCairoContext, CairoConverter::StrokeJoinStyleTo_cairo_line_join_t(_strokeJoinStyle));
                cairo_set_line_width    (_filterCacheCairoContext, _strokeThickness);
                cairo_set_dash          (_filterCacheCairoContext, _strokeDashPattern, _strokeDashPatternLength, 0);
                cairo_set_fill_rule     (_filterCacheCairoContext, cairo_fill_rule_t::CAIRO_FILL_RULE_WINDING);
                cairo_fill_preserve     (_filterCacheCairoContext);
                cairo_stroke            (_filterCacheCairoContext);

                cairo_ext_blur_surface  (_filterCacheCairoSurface, _shadowRadius); //TODO: cairo_ext_blur_surface() to be implemented

                if (_shadowOpacity != 1)
                {
                    cairo_set_operator      (_filterCacheCairoContext, cairo_operator_t::CAIRO_OPERATOR_DEST_IN);
                    cairo_set_source_rgba   (_filterCacheCairoContext, 0, 0, 0, _shadowOpacity);
                    cairo_paint             (_filterCacheCairoContext);
                    cairo_set_operator      (_filterCacheCairoContext, cairo_operator_t::CAIRO_OPERATOR_OVER);
                }
            }   

            if (_fillBrush)
            {
                cairo_append_path   (_filterCacheCairoContext, _geometry->getOriginalCairoPath());
                cairo_set_source    (_filterCacheCairoContext, _fillBrush->getCairoPattern());
                cairo_set_fill_rule (_filterCacheCairoContext, CairoConverter::FillRuleTo_cairo_fill_rule_t(_fillRule));
                cairo_fill          (_filterCacheCairoContext);
            }

            if (_strokeBrush)
            {
                cairo_append_path   (_filterCacheCairoContext, _geometry->getOriginalCairoPath());
                cairo_set_source    (_filterCacheCairoContext, _strokeBrush->getCairoPattern());
                cairo_set_line_cap  (_filterCacheCairoContext, CairoConverter::StrokeCapStyleTo_cairo_line_cap_t(_strokeCapStyle));
                cairo_set_line_join (_filterCacheCairoContext, CairoConverter::StrokeJoinStyleTo_cairo_line_join_t(_strokeJoinStyle));
                cairo_set_line_width(_filterCacheCairoContext, _strokeThickness);
                cairo_set_dash      (_filterCacheCairoContext, _strokeDashPattern, _strokeDashPatternLength, 0);
                cairo_stroke        (_filterCacheCairoContext);
            }

            cairo_set_operator      (_filterCacheCairoContext, cairo_operator_t::CAIRO_OPERATOR_DEST_IN);
            cairo_set_source_rgba   (_filterCacheCairoContext, 0, 0, 0, _opacity);
            cairo_paint             (_filterCacheCairoContext);
            cairo_set_operator      (_filterCacheCairoContext, cairo_operator_t::CAIRO_OPERATOR_OVER);

            cairo_identity_matrix   (_filterCacheCairoContext);
        }

        Rect l_visualPrimitiveExtent = getExtent();
        
        cairo_set_source_surface    (cairoContext, _filterCacheCairoSurface, l_visualPrimitiveExtent.lowVector.X, 
                                                                             l_visualPrimitiveExtent.lowVector.Y);
        cairo_rectangle             (cairoContext, l_visualPrimitiveExtent.lowVector.X,
                                                   l_visualPrimitiveExtent.lowVector.Y,
                                                   l_visualPrimitiveExtent.width(), 
                                                   l_visualPrimitiveExtent.height());
        cairo_fill                  (cairoContext);
    }
    else
    {
        _destroyFilterCache();

        cairo_set_antialias         (cairoContext, CairoConverter::AntialiasingModeTo_cairo_antialias_t(_antialiasMode));

        if (_fillBrush)
        {
            cairo_append_path       (cairoContext, _geometry->getCairoPath());
            cairo_set_source        (cairoContext, _fillBrush->getCairoPattern());
            cairo_set_fill_rule     (cairoContext, CairoConverter::FillRuleTo_cairo_fill_rule_t(_fillRule));
            cairo_fill              (cairoContext);
        }

        if (_strokeBrush)
        {
            cairo_append_path       (cairoContext, _geometry->getCairoPath());
            cairo_set_source        (cairoContext, _strokeBrush->getCairoPattern());
            cairo_set_line_cap      (cairoContext, CairoConverter::StrokeCapStyleTo_cairo_line_cap_t(_strokeCapStyle));
            cairo_set_line_join     (cairoContext, CairoConverter::StrokeJoinStyleTo_cairo_line_join_t(_strokeJoinStyle));
            cairo_set_line_width    (cairoContext, _strokeThickness);
            cairo_set_dash          (cairoContext, _strokeDashPattern, _strokeDashPatternLength, 0);
            cairo_stroke            (cairoContext);
        }
    }
}

void Shape::_doCairoDrawing(cairo_t* cairoContext, Region* region)
{
    Region l_effectiveRegion;

    if (region)
    {
        l_effectiveRegion = *region;
    }

    if (!_clippingRect.isZero())
    {
        if (l_effectiveRegion.isEmpty())
            l_effectiveRegion += _clippingRect;
        else
            l_effectiveRegion.clip(_clippingRect);
    }
    else
        return;

    if (l_effectiveRegion.isEmpty())
    {
        _doCairoDrawing(cairoContext);
        return;
    }

    Geometry l_windowSpaceClipingPath(&l_effectiveRegion);

    bool l_cacheNeeded = false;

    if (_shadowBrush) l_cacheNeeded = true;
    else
        if (_opacity != 0 && _opacity != 1) l_cacheNeeded = true;

    if (l_cacheNeeded)
    {
        _prepeareFilterCache();      
        if (_filterCacheIsStale)
        {   
            _filterCacheIsStale = false;

            Region l_region = l_effectiveRegion;
            AffineTransformation l_transformation;
            l_transformation.applyTranslation(-getExtent().lowVector);
            l_transformation.transformRegion(&l_region);
            Geometry l_filterSpaceClipingPath(&l_region);

            cairo_set_antialias     (_filterCacheCairoContext, CairoConverter::AntialiasingModeTo_cairo_antialias_t(_antialiasMode));

            cairo_append_path       (_filterCacheCairoContext, l_filterSpaceClipingPath.getCairoPath());
            cairo_clip              (_filterCacheCairoContext);

            Vector l_offsetVector = getApsoluteOffsetVector() - getExtent().lowVector;
            cairo_translate         (_filterCacheCairoContext, l_offsetVector.X, l_offsetVector.Y);

            cairo_ext_reset_surface(_filterCacheCairoSurface);

            if (_shadowBrush)
            {
                cairo_translate         (_filterCacheCairoContext, _shadowDistance.X, _shadowDistance.Y);
                cairo_append_path       (_filterCacheCairoContext, _geometry->getOriginalCairoPath());
                cairo_translate         (_filterCacheCairoContext, -_shadowDistance.X, -_shadowDistance.Y);
                cairo_set_source        (_filterCacheCairoContext, _shadowBrush->getCairoPattern());
                cairo_set_line_cap      (_filterCacheCairoContext, CairoConverter::StrokeCapStyleTo_cairo_line_cap_t(_strokeCapStyle));
                cairo_set_line_join     (_filterCacheCairoContext, CairoConverter::StrokeJoinStyleTo_cairo_line_join_t(_strokeJoinStyle));
                cairo_set_line_width    (_filterCacheCairoContext, _strokeThickness);
                cairo_set_dash          (_filterCacheCairoContext, _strokeDashPattern, _strokeDashPatternLength, 0);
                cairo_set_fill_rule     (_filterCacheCairoContext, cairo_fill_rule_t::CAIRO_FILL_RULE_WINDING);
                cairo_fill_preserve     (_filterCacheCairoContext);
                cairo_stroke            (_filterCacheCairoContext);

                cairo_ext_blur_surface  (_filterCacheCairoSurface, static_cast<int>(_shadowRadius)); //TODO: cairo_ext_blur_surface() to be implemented

                if (_shadowOpacity != 1)
                {
                    cairo_set_operator      (_filterCacheCairoContext, cairo_operator_t::CAIRO_OPERATOR_DEST_IN);
                    cairo_set_source_rgba   (_filterCacheCairoContext, 0, 0, 0, _shadowOpacity);
                    cairo_paint             (_filterCacheCairoContext);
                    cairo_set_operator      (_filterCacheCairoContext, cairo_operator_t::CAIRO_OPERATOR_OVER);
                }
            }

            if (_fillBrush)
            {
                cairo_append_path   (_filterCacheCairoContext, _geometry->getOriginalCairoPath());
                cairo_set_source    (_filterCacheCairoContext, _fillBrush->getCairoPattern());
                cairo_set_fill_rule (_filterCacheCairoContext, CairoConverter::FillRuleTo_cairo_fill_rule_t(_fillRule));
                cairo_fill          (_filterCacheCairoContext);
            }

            if (_strokeBrush)
            {
                cairo_append_path   (_filterCacheCairoContext, _geometry->getOriginalCairoPath());
                cairo_set_source    (_filterCacheCairoContext, _strokeBrush->getCairoPattern());
                cairo_set_line_cap  (_filterCacheCairoContext, CairoConverter::StrokeCapStyleTo_cairo_line_cap_t(_strokeCapStyle));
                cairo_set_line_join (_filterCacheCairoContext, CairoConverter::StrokeJoinStyleTo_cairo_line_join_t(_strokeJoinStyle));
                cairo_set_line_width(_filterCacheCairoContext, _strokeThickness);
                cairo_set_dash      (_filterCacheCairoContext, _strokeDashPattern, _strokeDashPatternLength, 0);
                cairo_stroke        (_filterCacheCairoContext);
            }

            cairo_set_operator      (_filterCacheCairoContext, cairo_operator_t::CAIRO_OPERATOR_DEST_IN);
            cairo_set_source_rgba   (_filterCacheCairoContext, 0, 0, 0, _opacity);
            cairo_paint             (_filterCacheCairoContext);
            cairo_set_operator      (_filterCacheCairoContext, cairo_operator_t::CAIRO_OPERATOR_OVER);
            
            cairo_reset_clip        (_filterCacheCairoContext);
            cairo_identity_matrix   (_filterCacheCairoContext);
        }

        cairo_append_path           (cairoContext, l_windowSpaceClipingPath.getCairoPath());
        cairo_clip                  (cairoContext);

        Rect l_visualPrimitiveExtent = getExtent();

        cairo_set_source_surface    (cairoContext, _filterCacheCairoSurface, l_visualPrimitiveExtent.lowVector.X,
                                                                             l_visualPrimitiveExtent.lowVector.Y);
        cairo_rectangle             (cairoContext, l_visualPrimitiveExtent.lowVector.X,
                                                   l_visualPrimitiveExtent.lowVector.Y,
                                                   l_visualPrimitiveExtent.width(),
                                                   l_visualPrimitiveExtent.height());
        cairo_fill                  (cairoContext);
        cairo_reset_clip            (cairoContext);
    }
    else
    {
        cairo_set_antialias         (cairoContext, CairoConverter::AntialiasingModeTo_cairo_antialias_t(_antialiasMode));

        cairo_append_path(cairoContext, l_windowSpaceClipingPath.getCairoPath());
        cairo_clip(cairoContext);
    
        if (_fillBrush)
        {
            cairo_append_path       (cairoContext, _geometry->getCairoPath());
            cairo_set_source        (cairoContext, _fillBrush->getCairoPattern());
            cairo_set_fill_rule     (cairoContext, CairoConverter::FillRuleTo_cairo_fill_rule_t(_fillRule));
            cairo_fill              (cairoContext);
        }

        if (_strokeBrush)
        {
            cairo_append_path       (cairoContext, _geometry->getCairoPath());
            cairo_set_source        (cairoContext, _strokeBrush->getCairoPattern());
            cairo_set_line_cap      (cairoContext, CairoConverter::StrokeCapStyleTo_cairo_line_cap_t(_strokeCapStyle));
            cairo_set_line_join     (cairoContext, CairoConverter::StrokeJoinStyleTo_cairo_line_join_t(_strokeJoinStyle));
            cairo_set_line_width    (cairoContext, _strokeThickness);
            cairo_set_dash          (cairoContext, _strokeDashPattern, _strokeDashPatternLength, 0);
            cairo_stroke            (cairoContext);
        }

        cairo_reset_clip            (cairoContext);
    }
}

void Shape::_render(Region* region)
{
    if (!visibility_get()) return;
    if (!_uiContext)       return;

    _doCairoDrawing(_uiContext->getCairoContext(), region);

    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_render(region);
        l_nextChild = l_nextChild->nextSibling();
    }
}

void Shape::_updateGeometry()
{
}

void Shape::_applyAbsoluteOffset()
{
    if (_absoluteOffsetApplicationExecuted) return;

    AffineTransformation l_geometryAT;

    l_geometryAT.applyTranslation(_absoluteOffsetVector);

    if (_geometry)
        _geometry->setAffineTransformation(&l_geometryAT);

    if (_strokeBrush)
    {
        AffineTransformation l_lineBrushAT = _strokeBrush->getAffineTransformation();
        l_lineBrushAT.multiplyAffineTransformation(&l_geometryAT);
        _strokeBrush->setAffineTransformation(&l_lineBrushAT);
    }

    if (_fillBrush)
    {
        AffineTransformation l_interiorBrushAT = _fillBrush->getAffineTransformation();
        l_interiorBrushAT.multiplyAffineTransformation(&l_geometryAT);
        _fillBrush->setAffineTransformation(&l_interiorBrushAT);
    }

    if (_shadowBrush)
    {
        AffineTransformation l_shadowBrushAT = _shadowBrush->getAffineTransformation();
        l_shadowBrushAT.multiplyAffineTransformation(&l_geometryAT);
        _shadowBrush->setAffineTransformation(&l_shadowBrushAT);
    }

    Node::_applyAbsoluteOffset();    
    
    _absoluteOffsetApplicationExecuted = true;
}
