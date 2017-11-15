#include "cairo.h"

namespace Eleusis
{
    static cairo_surface_t* _surface             = cairo_image_surface_create(cairo_format_t::CAIRO_FORMAT_A1, 2000, 500);
           cairo_t*         _cairoUtilityContext = cairo_create(_surface);
}



