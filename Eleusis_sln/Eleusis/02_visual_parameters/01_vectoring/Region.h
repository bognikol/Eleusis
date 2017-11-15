#pragma once

#include "dllexport.h"

#include "Rect.h"
#include "IAffineTransformable.h"
#include <list>


namespace Eleusis
{
    class ELEUSIS_API Region
    {
    private:    std::list<Rect> _rects;

			    Rect _extent;
			    bool _extentIsStale = true;

    public:     void operator += (Rect rect);
                std::list<Rect> & getRects();

                void clearRects();
                bool contains(Vector v);

                void clip(Rect rect);
                void normalize();

                Rect getExtent();

                bool isEmpty() { return _rects.empty(); }
    };
}
