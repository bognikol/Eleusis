#pragma once

#include "dllexport.h"

#include "01_vectoring/Vector.h"
#include "01_vectoring/Rect.h"
#include "01_vectoring/Region.h"
#include "01_vectoring/IAffineTransformable.h"
#include "02_geometry/Geometry.h"
#include "03_brushing/Brush.h"
#include "03_brushing/RgbaColor.h"

namespace Eleusis
{
    enum class ELEUSIS_API AntialiasingMode { Default, None, Gray, Subpixel, Fast, Good, Best };
    enum class ELEUSIS_API StrokeCapStyle   { Butt, Round, Square };
    enum class ELEUSIS_API StrokeJoinStyle  { Mitter, Round, Bevel };
    enum class ELEUSIS_API FillRule         { Winding, EvenOdd };
    enum class ELEUSIS_API BlendingMode     { Normal, Multiply, Darken, Screen, Lighten, ColorDodge, ColorBurn, HardLight, SoftLight };
}
