#include "AffineTransformation.h"

#include "Vector.h"
#include "Rect.h"
#include "Region.h"

#include "cairo.h"

#include <cmath>

using namespace Eleusis;
using namespace std;

AffineTransformation::AffineTransformation()
{
    setAffineMatrixToIdentity();
};

AffineTransformation::AffineTransformation(cairo_matrix_t* affineMatrix)
: xx(affineMatrix->xx), yx(affineMatrix->yx), xy(affineMatrix->xy),
  yy(affineMatrix->yy), x0(affineMatrix->x0), y0(affineMatrix->y0)
{
}

cairo_matrix_t* AffineTransformation::getAffineMatrix()
{
    return reinterpret_cast<cairo_matrix_t*>(this);
};

AffineTransformation AffineTransformation::setAffineMatrixToIdentity()
{
    xx = 1; yx = 0;
    xy = 0; yy = 1;
    x0 = 0; y0 = 0;

    return *this;
};

AffineTransformation AffineTransformation::applyRotation(double degrees)
{
    double l_angleInRadians = degrees * _const_2pi / 360.0;

    double l_sine = sin(l_angleInRadians);
    double l_cosine = cos(l_angleInRadians);

    double l_xx = xx;
    double l_xy = xy;
    double l_yx = yx;
    double l_yy = yy;

    xx = l_cosine * l_xx + l_sine * l_xy;
    xy = -l_sine * l_xx + l_cosine * l_xy;
    yx = l_cosine * l_yx + l_sine * l_yy;
    yy = -l_sine * l_yx + l_cosine * l_yy;

    return *this;
};

AffineTransformation AffineTransformation::applyScale(Vector scaleVector)
{
    xx *= scaleVector.X;
    xy *= scaleVector.Y;
    yx *= scaleVector.X;
    yy *= scaleVector.Y;

    return *this;
};

AffineTransformation AffineTransformation::applyTranslation(Vector translationVector)
{
    x0 = xx * translationVector.X + xy * translationVector.Y + x0;
    y0 = yx * translationVector.X + yy * translationVector.Y + y0;

    return *this;
};

AffineTransformation AffineTransformation::applyShear(Vector shearVector)
{
    double l_xx = xx;
    double l_xy = xy;
    double l_yx = yx;
    double l_yy = yy;

    xx = l_xx + shearVector.Y * l_xy;
    xy = shearVector.X * l_xx + l_xy;
    yx = l_yx + shearVector.Y * l_yy;
    yy = shearVector.X * l_yx + l_yy;

    return *this;
}

AffineTransformation AffineTransformation::multiplyAffineTransformation(AffineTransformation* affineTransformation, bool thisAffineTransformationIsFirstFactor)
{
    cairo_matrix_t l_m1 = *(affineTransformation->getAffineMatrix());
    cairo_matrix_t l_m2 = *getAffineMatrix();

    if (thisAffineTransformationIsFirstFactor) swap(l_m1, l_m2);

    xx = l_m1.xx * l_m2.xx + l_m1.xy * l_m2.yx;
    xy = l_m1.xx * l_m2.xy + l_m1.xy * l_m2.yy;
    x0 = l_m1.xx * l_m2.x0 + l_m1.xy * l_m2.y0 + l_m1.x0;
    yx = l_m1.yx * l_m2.xx + l_m1.yy * l_m2.yx;
    yy = l_m1.yx * l_m2.xy + l_m1.yy * l_m2.yy;
    y0 = l_m1.yx * l_m2.x0 + l_m1.yy * l_m2.y0 + l_m1.y0;

    return *this;
};

AffineTransformation AffineTransformation::transformVector(double* x, double* y)
{
    cairo_matrix_transform_point(getAffineMatrix(), x, y);

    return *this;
}

AffineTransformation AffineTransformation::transformVector(Vector* vector)
{
    cairo_matrix_transform_point(getAffineMatrix(), &(vector->X), &(vector->Y));

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
    cairo_matrix_invert(getAffineMatrix());
    
    return *this;
}

AffineTransformation AffineTransformation::getInverse()
{
    cairo_matrix_t l_affineMatrix = *getAffineMatrix();
    cairo_matrix_invert(&l_affineMatrix);
    return AffineTransformation(&l_affineMatrix);
}
