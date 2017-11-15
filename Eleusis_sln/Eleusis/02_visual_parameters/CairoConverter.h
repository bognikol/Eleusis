#pragma once

#include "VisualParameters.h"

namespace Eleusis
{
    class CairoConverter
    {
    public:
        static cairo_antialias_t AntialiasingModeTo_cairo_antialias_t(AntialiasingMode mode);
        static AntialiasingMode cairo_antialias_t_ToAntialiasingMode(cairo_antialias_t mode);

        static cairo_line_cap_t StrokeCapStyleTo_cairo_line_cap_t(StrokeCapStyle mode);
        static StrokeCapStyle cairo_line_cap_t_ToStrokeCapStyle(cairo_line_cap_t mode);

        static cairo_line_join_t StrokeJoinStyleTo_cairo_line_join_t(StrokeJoinStyle mode);
        static StrokeJoinStyle cairo_line_join_t_ToStrokeJoinStyle(cairo_line_join_t mode);

        static cairo_fill_rule_t FillRuleTo_cairo_fill_rule_t(FillRule mode);
        static FillRule cairo_fill_rule_t_ToFillRule(cairo_fill_rule_t mode);
    };
}