#pragma once

#include "dllexport.h"

#include "AffineTransformation.h"

namespace Eleusis
{
    class ELEUSIS_API IAffineTransformable
    {
    public:     virtual bool isAffineTransformationApplied() = 0;

                virtual void resetAffineTransformation() = 0;
                virtual void setAffineTransformation(AffineTransformation* affineTransformation) = 0;
                virtual void multiplyAffineTransformation(AffineTransformation* affineTransformation) = 0;
                virtual AffineTransformation getAffineTransformation() = 0;
    };
}

