#include "cairo-ext.h"
#include "cairo.h"
#include <cstdint>

void cairo_ext_reset_surface(cairo_surface_t* surface)
{
    cairo_surface_flush(surface);  
    
    cairo_format_t l_surfaceFormat = cairo_image_surface_get_format(surface);
    if (l_surfaceFormat != CAIRO_FORMAT_ARGB32) return;

    unsigned char* l_surfaceBuffer = cairo_image_surface_get_data(surface);
    if (!l_surfaceBuffer) return;

    int l_surfaceWidth        = cairo_image_surface_get_width (surface);
    int l_surfaceHeight       = cairo_image_surface_get_height(surface);
    int l_surfaceBufferStride = cairo_image_surface_get_stride(surface);

    for (int i = 0; i < l_surfaceHeight; i++)
    {       
        int32_t* l_surfaceBufferInt = (int32_t*)l_surfaceBuffer;
        for (int j = 0; j < l_surfaceWidth; j++)
        {
            *l_surfaceBufferInt = 0x00000000;
            l_surfaceBufferInt++;
        }
        l_surfaceBuffer += l_surfaceBufferStride;
    }

    cairo_surface_mark_dirty(surface);
}
