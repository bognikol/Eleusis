#pragma once

#include "dllexport.h"

#include "cairo.h"

namespace Eleusis
{
    struct Vector;
    struct Rect;
    class Region;

    class ELEUSIS_API AffineTransformation
    {
    private:    static constexpr double _const_2pi = 6.28318530717958647692;

    private:    cairo_matrix_t _affineMatrix;

    public:     AffineTransformation();
                AffineTransformation(cairo_matrix_t* affineMatrix);

                cairo_matrix_t*  getAffineMatrix();

                AffineTransformation setAffineMatrixToIdentity();

                AffineTransformation applyRotation(double degrees);

                AffineTransformation applyScale(Vector scaleVector);
                AffineTransformation applyTranslation(Vector translationVector);
                AffineTransformation applyShear(Vector shearVector);

                AffineTransformation multiplyAffineTransformation(AffineTransformation* affineTransformation, bool thisAffineTransformationIsFirstFactor = true);

                AffineTransformation transformVector(double* x, double* y);
                AffineTransformation transformVector(Vector* vector);
                AffineTransformation transformRect(Rect* rect);
                AffineTransformation transformRegion(Region* region);

                AffineTransformation invert();
                AffineTransformation getInverse();
       };
}
