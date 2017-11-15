#pragma once

#include "dllexport.h"

#include "Node.h"

namespace Eleusis
{
    class ELEUSIS_API VisualPrimitive :
        public Node
    {
    public:     virtual ~VisualPrimitive() { };
        
                VisualPrimitive() { _isVisualPrimitive = true; };

                virtual Rect getExtent() = 0;
                virtual Rect getFullExtent() = 0;

                virtual bool contains(Vector vector) { return false; };
                virtual bool contains(double x, double y) { return false; };

                //virtual void _applyAbsoluteOffset();
                virtual void _updateGeometry() = 0;
    };
}
