#pragma once

#include "dllexport.h"

#include "01_vectoring/IAffineTransformable.h"
#include "RgbaColor.h"
#include "event.h"
#include <string>
#include <vector>

#include "cairo.h"

namespace Eleusis
{

    class ELEUSIS_API Brush :
        public IAffineTransformable
    {
    protected:  cairo_pattern_t* _pattern = nullptr;

    public:              Brush() { };
                virtual ~Brush() { if (_pattern) cairo_pattern_destroy(_pattern); _pattern = nullptr; };
                virtual cairo_pattern_t* getCairoPattern() = 0;
                Event<Brush*, EventArgs*> brushUpdated;
    };

    class ELEUSIS_API NoBrush :
        public Brush 
    {
    public:     virtual cairo_pattern_t* getCairoPattern() { return nullptr; }

                virtual bool isAffineTransformationApplied() { return false; };

                virtual void resetAffineTransformation() { };
                virtual void setAffineTransformation(AffineTransformation* affineTransformation) { };
                virtual void multiplyAffineTransformation(AffineTransformation* affineTransformation) { };
                virtual AffineTransformation getAffineTransformation() { return AffineTransformation(); };
    };

    class ELEUSIS_API SolidColorBrush :
        public Brush
    {
    private:    void _initializeEventHandlers();
                void _doObjectConstruction();

                std::function<void(RgbaColor*, EventArgs*)> _colorUpdatedHandler;

    public:     SolidColorBrush();

                SolidColorBrush(double R, double G, double B);
                SolidColorBrush(double R, double G, double B, double A);

                SolidColorBrush(int R, int G, int B);
                SolidColorBrush(int R, int G, int B, int A);

                SolidColorBrush(RgbaColor color);

                RgbaColor Color;

                virtual cairo_pattern_t* getCairoPattern();

                //affine transformation of solid color brush is the same solid color brush; thus, we do not need implementations of these methods
                virtual bool isAffineTransformationApplied() { return false; }; 
                
                virtual void resetAffineTransformation() { };
                virtual void setAffineTransformation(AffineTransformation* affineTransformation) { };
                virtual void multiplyAffineTransformation(AffineTransformation* affineTransformation) { };
                virtual AffineTransformation getAffineTransformation() { return AffineTransformation(); };
    };

    class ELEUSIS_API GradientStop
    {
    private:    RgbaColor _color;
                double    _offset;

    public:     GradientStop();
                GradientStop(RgbaColor & color, double offset);

                void        color_set(RgbaColor & color);
                RgbaColor   color_get();

                void    offset_set(double offset);
                double  offset_get();
    };

    class ELEUSIS_API LinearGradientBrush :
        public Brush
    {
    private:    double _x1, _y1, _x2, _y2;
                bool _patternIsStale;
                std::vector<GradientStop> _gradientStops;
                AffineTransformation _affineTransformation;
                bool _isAffineTranformationApplied;

    public:     LinearGradientBrush();
                LinearGradientBrush(double x1, double y1, double x2, double y2);

                void setGradientStrech(double x1, double y1, double x2, double y2);
                void addGradientStop(RgbaColor color, double offset);
                void resetGradientStops();

                virtual cairo_pattern_t* getCairoPattern();

                virtual bool isAffineTransformationApplied();

                virtual void resetAffineTransformation();
                virtual void setAffineTransformation(AffineTransformation* affineTransformation);
                virtual void multiplyAffineTransformation(AffineTransformation* affineTransformation);
                virtual AffineTransformation getAffineTransformation() { return _affineTransformation; };
    };

    class ELEUSIS_API RadialGradientBrush :
        public Brush
    {
    private:    double _x1, _y1, _r1, 
                       _x2, _y2, _r2;
                bool _patternIsStale;
                std::vector<GradientStop> _gradientStops;
                AffineTransformation _affineTransformation;
                bool _isAffineTranformationApplied;

    public:     RadialGradientBrush();
                RadialGradientBrush(double x1, double y1, double r1, double x2, double y2, double r2);
                RadialGradientBrush(double x, double y, double r);

                void setGradientStrech(double x1, double y1, double r1, double x2, double y2, double r2);
                void setGradientStrech(double x, double y, double r);
                void addGradientStop(RgbaColor color, double offset);
                void resetGradientStops();

                virtual cairo_pattern_t* getCairoPattern();

                virtual bool isAffineTransformationApplied();

                virtual void resetAffineTransformation();
                virtual void setAffineTransformation(AffineTransformation* affineTransformation);
                virtual void multiplyAffineTransformation(AffineTransformation* affineTransformation);
                virtual AffineTransformation getAffineTransformation() { return _affineTransformation; };
    };

    // It seems that cairo supports meshes only on 64bit binaries
    // View: https://bugs.launchpad.net/inkscape/+bug/1335954
    // Note: Inscape uses Cairo for rendering 
    
    class ELEUSIS_API MeshGradientBrush :
        public Brush
    {
    public:     virtual cairo_pattern_t* getCairoPattern() { return nullptr; } //not implemented yet

                virtual bool isAffineTransformationApplied() { return false; };

                virtual void resetAffineTransformation() { };
                virtual void setAffineTransformation(AffineTransformation* affineTransformation) { };
                virtual void multiplyAffineTransformation(AffineTransformation* affineTransformation) { };
                virtual AffineTransformation getAffineTransformation() { return AffineTransformation(); };
    };

    enum class ELEUSIS_API BitmapBrushExtension
    {
        None,
        Pad,
        Repeat,
        Reflect
     };

    class ELEUSIS_API BitmapBrush :
        public Brush
    {
        private:    cairo_surface_t* _sourceSurface = nullptr;
                    cairo_pattern_t* _pattern = nullptr;
                    cairo_extend_t _extend = cairo_extend_t::CAIRO_EXTEND_NONE;
                    AffineTransformation _affineTransformation;
                    bool _isAffineTransformationApplied = false;

        public:             BitmapBrush(std::string imagePath);
                    virtual~BitmapBrush();
        
                    void extension_set(BitmapBrushExtension extension);
                    BitmapBrushExtension extension_get();

                    virtual cairo_pattern_t* getCairoPattern() { return _pattern; }
        
                    virtual bool isAffineTransformationApplied() { return _isAffineTransformationApplied; };
        
                    virtual void resetAffineTransformation();
                    virtual void setAffineTransformation(AffineTransformation* affineTransformation);
                    virtual void multiplyAffineTransformation(AffineTransformation* affineTransformation);
        
                    virtual AffineTransformation getAffineTransformation() { return _affineTransformation; }
    };

}
