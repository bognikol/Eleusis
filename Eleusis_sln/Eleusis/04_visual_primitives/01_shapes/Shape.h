#pragma once

#include "dllexport.h"

#include "VisualParameters.h"
#include "VisualPrimitive.h"
#include "Animatable.h"
#include "04_textual_styles/TextualTypes.h"
#include "Defaults.h"

#include <memory>

namespace Eleusis
{  

#pragma region "SHAPE"

    class ELEUSIS_API Shape :
        public VisualPrimitive
    {
    public:     Shape();
                Shape(Brush* interiorBrush, Brush* borderBrush, Brush* shadowBrush);

               ~Shape();

                void fillBrush_set(std::shared_ptr<Brush> brush);
                std::shared_ptr<Brush> fillBrush_get();

                void strokeBrush_set(std::shared_ptr<Brush> brush);
                std::shared_ptr<Brush> strokeBrush_get();

                void shadowBrush_set(std::shared_ptr<Brush> brush);
                std::shared_ptr<Brush> shadowBrush_get();

                void fillColor_set(Eleusis::RgbaColor color);
                void lineColor_set(Eleusis::RgbaColor color);

                void shadowRadius_set(double radius);
                double shadowRadius_get();

                void shadowDistance_set(double distance, double angle);
                void shadowDistance_set(Vector distance);
                Vector shadowDistance_get();

                void shadowOpacity_set(double opacity);
                double shadowOpacity_get();

                void lineThickenss_set(double thickness);
                double lineThickness_get();

                void strokeCapStyle_set(StrokeCapStyle capStyle);
                StrokeCapStyle strokeCapStype_get();

                void strokeJoinStyle_set(StrokeJoinStyle joinStyle);
                StrokeJoinStyle strokeJoinStype_get();

                void antialiasMode_set(AntialiasingMode mode);
                AntialiasingMode antialiasMode_get();

                void fillRule_set(FillRule fillRule);
                FillRule fillRule_get();

                void strokeDashPattern_set(double line,  double gap);
                void strokeDashPattern_set(double line1, double gap1, double line2, double gap2);
                void strokeDashPattern_set(double line1, double gap1, double line2, double gap2, double line3, double gap3);
                void strokeDashPattern_set(double line1, double gap1, double line2, double gap2, double line3, double gap3, double line4, double gap4);
                void resetDashPattern();

                void   opacity_set(double opacity);
                double opacity_get();

                Rect getExtent();
                Rect getFullExtent();
                Rect getGeometryExtent();
                Rect getLineExtent();
                Rect getFillExtent();

                bool contains(Vector vector);
                bool contains(double x, double y);

    protected:  Geometry* _geometry = nullptr;

                bool _filterCacheIsStale = true;
               
                virtual void _updateGeometry();
                virtual void _applyAbsoluteOffset();

    private:    virtual void _render(Region* region);
        
                void _doCairoDrawing(cairo_t* cairoContext);
                void _doCairoDrawing(cairo_t* cairoContext, Region* region);

                cairo_surface_t* _filterCacheCairoSurface = nullptr;
                cairo_t*         _filterCacheCairoContext = nullptr;

                void _prepeareFilterCache();
                void  _destroyFilterCache();

                std::shared_ptr<Brush> _fillBrush;
                std::shared_ptr<Brush> _strokeBrush;
                std::shared_ptr<Brush> _shadowBrush;

                double _shadowRadius = 0;
                Vector _shadowDistance;
                double _shadowOpacity = 0;

                double _opacity = 1.0;

                double          _strokeThickness = 2;
                StrokeCapStyle  _strokeCapStyle  = StrokeCapStyle::Butt;
                StrokeJoinStyle _strokeJoinStyle = StrokeJoinStyle::Mitter;

                double _strokeDashPattern[8];
                int    _strokeDashPatternLength = 0;

                FillRule _fillRule = FillRule::Winding;

                AntialiasingMode _antialiasMode = AntialiasingMode::Default;

                Rect _extent;
};

#pragma endregion



#pragma region "SHAPES"

    class ELEUSIS_API Rectangle : 
        public Shape, 
        public Animatable<RectangleDefaultAnimation, Rectangle>
    {
    public:     Rectangle(Length width = 0, Length height = 0, Length cornerRadius = 0);

                void    width_set(Length width);
                Length  width_get() { return _width; };

                void    height_set(Length height);
                Length  height_get() { return _height; };

                void    cornerRadius_set(Length cornerRadius);
                Length  cornerRadius_get() { return _cornerRadius; };

                void setWidthAndHeight(Length width, Length height);

    private:    Length _width;
                Length _height;
                Length _cornerRadius;

                virtual void _updateGeometry();
                virtual void _updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector);
    };

    class ELEUSIS_API Line : 
        public Shape, 
        public Animatable<LineDefaultAnimation, Line>
    {
    public:     Line(Length x = 0, Length y = 0);

                void   endPointX_set(Length secondPointX);
                Length endPointX_get() { return _endPointX; };

                void   endPointY_set(Length secondPointY);
                Length endPointY_get() { return _endPointY; };

                void setPoints(Length x, Length y);

    private:    Length _endPointX;
                Length _endPointY;

                virtual void _updateGeometry();
                virtual void _updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector);
    };

    class ELEUSIS_API Circle : 
        public Shape,
        public Animatable<CircleDefaultAnimation, Circle>
    {
    public:     Circle(Length radius = 0);
              
                void    radius_set(Length radius);
                Length  radius_get() { return _radius; };

    private:    Length _radius;

                virtual void _updateGeometry();
                virtual void _updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector);
    };

    class ELEUSIS_API Ellipse : 
        public Shape, 
        public Animatable<EllipseDefaultAnimation, Ellipse>
    {
    public:     Ellipse(Length width = 0, Length height = 0);

                void    width_set(Length width);
                Length  width_get() { return _width; };

                void    height_set(Length height);
                Length  height_get() { return _height; };

                void setWidthAndHeight(Length width, Length height);

    private:    Length _width;
                Length _height;

                virtual void _updateGeometry();
                virtual void _updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector);
    };

    class ELEUSIS_API Polygon : 
        public Shape, 
        public Animatable<PolygonDefaultAnimation, Polygon>
    {
    public:     enum class PolygonRadiusContext { Internal, External };

    public:     Polygon(Length radius, int numberOfVerticie = 6, PolygonRadiusContext context = PolygonRadiusContext::External);

                void    radius_set(Length radius);
                Length  radius_get() { return _radius; };

                int     numberOfVerticies_get() { return _numberOfVerticies; };
                PolygonRadiusContext radiusContext_get() { return _context; };

    private:    Length _radius;
                int    _numberOfVerticies;
                PolygonRadiusContext _context;

                virtual void _updateGeometry();
                virtual void _updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector);
    };

    class ELEUSIS_API GenericShape : 
        public Shape, 
        public Animatable<GenericShapeDefaultAnimation, GenericShape>
    {
    public:     GenericShape();

                void moveTo(double x, double y);
                void lineTo(double x, double y);
                void curveTo(double x, double y, double x1, double y1, double x2, double y2);
                void closeLine();

                void updateShape();

    private:    virtual void _updateGeometry();
                virtual void _updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector);
    };

    class ELEUSIS_API TextualShape :
        public Shape,
        public Animatable<TextualShapeDefaultAnimation, TextualShape>
    {
    public:     TextualShape();
                TextualShape(std::string text);
        
                void text_set(std::string text);
                std::string text_get() { return _text; };
        
                void fontFamily_set(std::string family);
                std::string fontFamily_get() { return _fontFamily; };

                void fontStyle_set(FontStyle style);
                FontStyle fontStyle_get() { return _fontStyle; };

                void fontWeight_set(FontWeight weight);
                FontWeight fontWeight_get() { return _fontWeight; };

                void fontVariant_set(FontVariant fontVariant);
                FontVariant fontvariant_get() { return _fontVariant; };

                void fontStrech_set(FontStretch fontStrech);
                FontStretch fontStrech_get() { return _fontStretch; };

                void fontFallback_set(bool fallback);
                bool fontFallback_get() { return _fontFallback; };

                void textSize_set(Length size);
                Length textSize_get() { return _textSize; };

                void letterSpacing_set(Length spacing);
                double letterSpacing_get() { return _letterSpacing; };

                void lineSpacing_set(Length spacing);
                double lineSpacing_get() { return _lineSpacing; };

                void underline_set(UnderlineType underline);
                UnderlineType underline_get() { return _underline; };

                void strikeThrough_set(bool strikeThrough);
                bool strikeThrough_get() { return _strikeThrough; };

                void gravity_set(CharacterGravity gravity);
                CharacterGravity gravity_get() { return _gravity; };

                void gravityHint_set(CharacterGravityHint gravityHint);
                CharacterGravityHint gravityHint_get() { return _gravityHint; };

                void italic();
                void unitalic();

                void bold();
                void unbold();

                virtual void _updateGeometry();
                virtual void _updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector);


    private:    std::string _text;

                std::string _fontFamily  = ELEUSIS_SPAN_FONT_FAMILY;
                FontStyle _fontStyle     = ELEUSIS_SPAN_FONT_STYLE;
                FontWeight _fontWeight   = ELEUSIS_SPAN_FONT_WEIGHT;
                FontVariant _fontVariant = ELEUSIS_SPAN_FONT_VARIANT;
                FontStretch _fontStretch = ELEUSIS_SPAN_FONT_STRETCH;
                bool _fontFallback       = ELEUSIS_SPAN_FONT_FALLBACK;


                Length _textSize      = ELEUSIS_SPAN_TEXT_SIZE;
                Length _letterSpacing = ELEUSIS_SPAN_CHARACTER_SPACING;
                Length _lineSpacing   = ELEUSIS_PARAGRAPH_LINE_SPACING;


                CharacterGravity _gravity         = ELEUSIS_SPAN_GRAVITY;
                CharacterGravityHint _gravityHint = ELEUSIS_SPAN_GRAVITY_HINT;
                UnderlineType _underline          = ELEUSIS_SPAN_UNDERLINE;
                bool _strikeThrough               = ELEUSIS_SPAN_STRIKETHROUGH;

                bool _boldApplied   = false;
                bool _italicApplied = false;
    };
}

#pragma endregion


