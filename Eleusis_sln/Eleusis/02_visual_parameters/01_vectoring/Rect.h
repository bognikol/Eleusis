#pragma once

#include "dllexport.h"

#include "Vector.h"

namespace Eleusis
{
    struct ELEUSIS_API Rect
    {
        Vector lowVector;
        Vector highVector;

        Rect();
        Rect(Vector lowVector, Vector highVector);
        Rect(double x_low, double y_low, double x_high, double y_high);

        bool contains(Vector vector);
        bool contains(double x, double y);

        Vector sizeVector();
        double width();
        double height();
        bool   isPositive();
        void   format();
		void   integral();

        bool wellFormed() { return lowVector < highVector; };
        bool isZero()     { return lowVector.isZero() && highVector.isZero(); };

        bool   operator ==   (const Rect r) const;
        bool   operator !=   (const Rect r) const { return !(*this == r); };

        Rect   operator &    (Rect r);
        Rect   operator |    (Rect r);
        void   operator &=   (Rect r);
        void   operator |=   (Rect r);

        Rect   operator &&   (Rect r);

        void   operator >>   (Vector v);
        void   operator <<   (Vector v);

        bool   operator %    (Rect r);
    };
}

