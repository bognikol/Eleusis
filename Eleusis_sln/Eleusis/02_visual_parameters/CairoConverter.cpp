#include "CairoConverter.h"


using namespace Eleusis;

cairo_antialias_t CairoConverter::AntialiasingModeTo_cairo_antialias_t(AntialiasingMode mode)
{
    switch (mode)
    {
    case AntialiasingMode::Best:     
        return cairo_antialias_t::CAIRO_ANTIALIAS_BEST;
    case AntialiasingMode::Default:  
        return cairo_antialias_t::CAIRO_ANTIALIAS_DEFAULT;
    case AntialiasingMode::Fast:     
        return cairo_antialias_t::CAIRO_ANTIALIAS_FAST;
    case AntialiasingMode::Good:     
        return cairo_antialias_t::CAIRO_ANTIALIAS_GOOD;
    case AntialiasingMode::Gray:     
        return cairo_antialias_t::CAIRO_ANTIALIAS_GRAY;
    case AntialiasingMode::None:     
        return cairo_antialias_t::CAIRO_ANTIALIAS_NONE;
    case AntialiasingMode::Subpixel: 
        return cairo_antialias_t::CAIRO_ANTIALIAS_SUBPIXEL;
    default:                         
        return cairo_antialias_t::CAIRO_ANTIALIAS_DEFAULT;
    }
}

AntialiasingMode CairoConverter::cairo_antialias_t_ToAntialiasingMode(cairo_antialias_t mode)
{
    switch (mode)
    {
    case cairo_antialias_t::CAIRO_ANTIALIAS_BEST:     
        return AntialiasingMode::Best;
    case cairo_antialias_t::CAIRO_ANTIALIAS_DEFAULT:  
        return AntialiasingMode::Default;
    case cairo_antialias_t::CAIRO_ANTIALIAS_FAST:     
        return AntialiasingMode::Fast;
    case cairo_antialias_t::CAIRO_ANTIALIAS_GOOD:     
        return AntialiasingMode::Good;
    case cairo_antialias_t::CAIRO_ANTIALIAS_GRAY:     
        return AntialiasingMode::Gray;
    case cairo_antialias_t::CAIRO_ANTIALIAS_NONE:     
        return AntialiasingMode::None;
    case cairo_antialias_t::CAIRO_ANTIALIAS_SUBPIXEL: 
        return AntialiasingMode::Subpixel;
    default:                                          
        return AntialiasingMode::Default;
    }
}

cairo_line_cap_t CairoConverter::StrokeCapStyleTo_cairo_line_cap_t(StrokeCapStyle mode)
{
    switch (mode)
    {
    case StrokeCapStyle::Butt:
        return cairo_line_cap_t::CAIRO_LINE_CAP_BUTT;
    case StrokeCapStyle::Round:
        return cairo_line_cap_t::CAIRO_LINE_CAP_ROUND;
    case StrokeCapStyle::Square:
        return cairo_line_cap_t::CAIRO_LINE_CAP_SQUARE;
    default:
        return cairo_line_cap_t::CAIRO_LINE_CAP_BUTT;
    }
}

StrokeCapStyle CairoConverter::cairo_line_cap_t_ToStrokeCapStyle(cairo_line_cap_t mode)
{
    switch (mode)
    {
    case cairo_line_cap_t::CAIRO_LINE_CAP_BUTT:
        return StrokeCapStyle::Butt;
    case cairo_line_cap_t::CAIRO_LINE_CAP_ROUND:
        return StrokeCapStyle::Round;
    case cairo_line_cap_t::CAIRO_LINE_CAP_SQUARE:
        return StrokeCapStyle::Square;
    default:
        return StrokeCapStyle::Butt;
    }
}

cairo_line_join_t CairoConverter::StrokeJoinStyleTo_cairo_line_join_t(StrokeJoinStyle mode)
{
    switch (mode)
    {
    case StrokeJoinStyle::Bevel:
        return cairo_line_join_t::CAIRO_LINE_JOIN_BEVEL;
    case StrokeJoinStyle::Mitter:
        return cairo_line_join_t::CAIRO_LINE_JOIN_MITER;
    case StrokeJoinStyle::Round:
        return cairo_line_join_t::CAIRO_LINE_JOIN_ROUND;
    default:
        return cairo_line_join_t::CAIRO_LINE_JOIN_BEVEL;
    }
}

StrokeJoinStyle CairoConverter::cairo_line_join_t_ToStrokeJoinStyle(cairo_line_join_t mode)
{
    switch (mode)
    {
    case cairo_line_join_t::CAIRO_LINE_JOIN_BEVEL:
        return StrokeJoinStyle::Bevel;
    case cairo_line_join_t::CAIRO_LINE_JOIN_MITER:
        return StrokeJoinStyle::Mitter;
    case cairo_line_join_t::CAIRO_LINE_JOIN_ROUND:
        return StrokeJoinStyle::Round;
    default:
        return StrokeJoinStyle::Bevel;
    }
}

cairo_fill_rule_t CairoConverter::FillRuleTo_cairo_fill_rule_t(FillRule mode)
{
    switch (mode)
    {
    case FillRule::Winding: return cairo_fill_rule_t::CAIRO_FILL_RULE_WINDING;
    case FillRule::EvenOdd: return cairo_fill_rule_t::CAIRO_FILL_RULE_EVEN_ODD;
    default:                return cairo_fill_rule_t::CAIRO_FILL_RULE_WINDING;
    }
}

FillRule CairoConverter::cairo_fill_rule_t_ToFillRule(cairo_fill_rule_t mode)
{
    switch (mode)
    {
    case cairo_fill_rule_t::CAIRO_FILL_RULE_WINDING:
        return FillRule::Winding;
    case cairo_fill_rule_t::CAIRO_FILL_RULE_EVEN_ODD:
        return FillRule::EvenOdd;
    default:
        return FillRule::Winding;
    }
}