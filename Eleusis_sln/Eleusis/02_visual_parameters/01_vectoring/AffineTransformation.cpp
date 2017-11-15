#include "AffineTransformation.h"

#include "Vector.h"
#include "Rect.h"
#include "Region.h"

#include <cmath>

using namespace Eleusis;
using namespace std;

AffineTransformation::AffineTransformation()
{
    setAffineMatrixToIdentity();
};

AffineTransformation::AffineTransformation(cairo_matrix_t* affineMatrix)
{
    _affineMatrix = *affineMatrix;
}

cairo_matrix_t* AffineTransformation::getAffineMatrix()
{
    return &_affineMatrix;
};

AffineTransformation AffineTransformation::setAffineMatrixToIdentity()
{
    _affineMatrix.xx = 1;
    _affineMatrix.xy = 0;
    _affineMatrix.x0 = 0;
    _affineMatrix.yx = 0;
    _affineMatrix.yy = 1;
    _affineMatrix.y0 = 0;

    return *this;
};

AffineTransformation AffineTransformation::applyRotation(double degrees)
{
    double l_angleInRadians = degrees * _const_2pi / 360.0;

    double l_sine = std::sin(l_angleInRadians);
    double l_cosine = std::cos(l_angleInRadians);

    double l_xx = _affineMatrix.xx;
    double l_xy = _affineMatrix.xy;
    double l_yx = _affineMatrix.yx;
    double l_yy = _affineMatrix.yy;

    _affineMatrix.xx = l_cosine * l_xx + l_sine * l_xy;
    _affineMatrix.xy = -l_sine * l_xx + l_cosine * l_xy;
    _affineMatrix.yx = l_cosine * l_yx + l_sine * l_yy;
    _affineMatrix.yy = -l_sine * l_yx + l_cosine * l_yy;

    return *this;
};

AffineTransformation AffineTransformation::applyScale(Vector scaleVector)
{
    _affineMatrix.xx *= scaleVector.X;
    _affineMatrix.xy *= scaleVector.Y;
    _affineMatrix.yx *= scaleVector.X;
    _affineMatrix.yy *= scaleVector.Y;

    return *this;
};

AffineTransformation AffineTransformation::applyTranslation(Vector translationVector)
{
    _affineMatrix.x0 = _affineMatrix.xx * translationVector.X + _affineMatrix.xy * translationVector.Y + _affineMatrix.x0;
    _affineMatrix.y0 = _affineMatrix.yx * translationVector.X + _affineMatrix.yy * translationVector.Y + _affineMatrix.y0;

    return *this;
};

AffineTransformation AffineTransformation::applyShear(Vector shearVector)
{
    double l_xx = _affineMatrix.xx;
    double l_xy = _affineMatrix.xy;
    double l_yx = _affineMatrix.yx;
    double l_yy = _affineMatrix.yy;

    _affineMatrix.xx = l_xx + shearVector.Y * l_xy;
    _affineMatrix.xy = shearVector.X * l_xx + l_xy;
    _affineMatrix.yx = l_yx + shearVector.Y * l_yy;
    _affineMatrix.yy = shearVector.X * l_yx + l_yy;

    return *this;
}

AffineTransformation AffineTransformation::multiplyAffineTransformation(AffineTransformation* affineTransformation, bool thisAffineTransformationIsFirstFactor)
{
    cairo_matrix_t l_m1 = *affineTransformation->getAffineMatrix();
    cairo_matrix_t l_m2 = _affineMatrix;

    if (thisAffineTransformationIsFirstFactor)
    {
        l_m1 = _affineMatrix;
        l_m2 = *affineTransformation->getAffineMatrix();
    }

    _affineMatrix.xx = l_m1.xx * l_m2.xx + l_m1.xy * l_m2.yx;
    _affineMatrix.xy = l_m1.xx * l_m2.xy + l_m1.xy * l_m2.yy;
    _affineMatrix.x0 = l_m1.xx * l_m2.x0 + l_m1.xy * l_m2.y0 + l_m1.x0;
    _affineMatrix.yx = l_m1.yx * l_m2.xx + l_m1.yy * l_m2.yx;
    _affineMatrix.yy = l_m1.yx * l_m2.xy + l_m1.yy * l_m2.yy;
    _affineMatrix.y0 = l_m1.yx * l_m2.x0 + l_m1.yy * l_m2.y0 + l_m1.y0;

    return *this;
};

AffineTransformation AffineTransformation::transformVector(double* x, double* y)
{
    cairo_matrix_transform_point(&_affineMatrix, x, y);

    return *this;
}

AffineTransformation AffineTransformation::transformVector(Vector* vector)
{
    cairo_matrix_transform_point(&_affineMatrix, &(vector->X), &(vector->Y));

    return *this;
}

AffineTransformation AffineTransformation::transformRect(Rect* rect)
{
    transformVector(&(rect->lowVector));
    transformVector(&(rect->highVector));

    return *this;
}

AffineTransformation AffineTransformation::transformRegion(Region* region)
{
    for (auto & rect : region->getRects())
        transformRect(&rect);

    return *this;
}

AffineTransformation AffineTransformation::invert()
{
    cairo_matrix_invert(&_affineMatrix);

    return *this;
}

AffineTransformation AffineTransformation::getInverse()
{
    cairo_matrix_t l_matrix = _affineMatrix;
    cairo_matrix_invert(&l_matrix);
    return AffineTransformation(&l_matrix);
}