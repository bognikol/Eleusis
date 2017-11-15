#pragma once

#include "dllexport.h"

#include <utility>

namespace Eleusis
{
    struct Rect;

    struct ELEUSIS_API Vector
    {
        double X = 0;
        double Y = 0;

        Vector() { };
        Vector(double X, double Y);

        bool isZero();

        Vector operator -    ();

        bool   operator ==   (const Vector v) const;
        bool   operator <    (Vector v);
        bool   operator >    (Vector v);
        bool   operator <=   (Vector v);
        bool   operator >=   (Vector v);
        bool   operator !=   (Vector v);

        Vector operator +    (Vector v);
        Vector operator -    (Vector v);
        void   operator +=   (Vector v);
        void   operator -=   (Vector v);

        Vector operator &    (Vector v);
        Vector operator |    (Vector v);
        void   operator &=   (Vector v);
        void   operator |=   (Vector v);

        Rect   operator *    (Vector v);
        Rect   operator ^    (Vector v);
    };
}
