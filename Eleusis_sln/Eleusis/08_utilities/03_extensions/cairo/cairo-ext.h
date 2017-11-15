#pragma once

#include "cairo.h"

void cairo_ext_blur_surface(cairo_surface_t *surface, double radius);

//Resets all pixels on surface to Rgba(0,0,0,0); applicable only to image surfaces
void cairo_ext_reset_surface(cairo_surface_t* surface);
