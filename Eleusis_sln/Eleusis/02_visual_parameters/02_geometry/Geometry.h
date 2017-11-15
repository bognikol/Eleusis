#pragma once

#include "dllexport.h"

#include "01_vectoring/Region.h"
#include "01_vectoring/IAffineTransformable.h"
#include "cairo.h"

namespace Eleusis
{
    class ELEUSIS_API Geometry :
        public IAffineTransformable
    {

    private:    static constexpr int    _const_initialPathBufferSize  = 36;
                static constexpr int    _const_pathBufferSizeIncrease = 18;

                static constexpr double _const_semicircleBezier = 0.5522847498307934;
                static constexpr double _const_ellipseBezier    = 0.75;

				static constexpr int    _const_numberOfBytesPerRect = 9 * sizeof(cairo_path_data_t);

    public:     static constexpr double const_pi     = 3.14159265358979323846;
                static constexpr double const_2pi    = 2 * const_pi;
                static constexpr double const_piHalf = const_pi / 2;


    private:    cairo_path_t _originalPath;

                cairo_path_t _affineTransformedPath;
                AffineTransformation _affineTransformation;

				bool _extentsAreStale = true;

                int _allocatedBufferSize = 0;
       
                void _realocateBuffer();
                void _appendPoint (double x, double y);
                void _appendHeader(cairo_path_data_type_t type);
                void _reapplyAffineTransformation();
                void _disposeAffineTransformation();
                
                Rect _affineTransformedPathExtent;
                Rect _originalPathExtent;
                void _calculateExtents();

    public:     Geometry();
                Geometry(size_t dataSize);
                Geometry(Region* region);
                Geometry(cairo_path_t* cairoPath);

                virtual ~Geometry();

                cairo_path_t* getCairoPath();
                cairo_path_t* getOriginalCairoPath();

                Rect getExtent();
                Rect getOriginalExtent();

                int addPoint_moveTo (double x, double y);
                int addPoint_lineTo (double x, double y);
                int addPoint_curveTo(double x, double y, double x1, double y1, double x2, double y2);
                int addPoint_closePath();

                void addRectangle(double x_low, double y_low, double x_high, double y_high, double r);
                void addCircle(double x, double y, double r);
                void addEllipse(double x, double y, double rx, double ry);
                void addPolygon(double x, double y, double r, int numberOfVerticies, bool internalRadius);

                void updatePoint(int index, double x, double y);

                virtual bool isAffineTransformationApplied();

                virtual void resetAffineTransformation();
                virtual void setAffineTransformation(AffineTransformation* affineTransformation);
                virtual void multiplyAffineTransformation(AffineTransformation* affineTransformation);
                virtual AffineTransformation getAffineTransformation() { return _affineTransformation; };
    };

}
