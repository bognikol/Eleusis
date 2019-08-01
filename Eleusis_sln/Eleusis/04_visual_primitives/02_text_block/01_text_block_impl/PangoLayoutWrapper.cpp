#pragma once

#include "PangoLayoutWrapper.h"
#include "pango/pangocairo.h"

#include <memory>

using namespace Eleusis;

PangoLayoutWrapper::~PangoLayoutWrapper()
{
    g_object_unref(layout);
};

int PangoLayoutWrapper::numberOfShownCharacters()
{
    return pango_layout_get_character_count(layout);
};

int PangoLayoutWrapper::numberOfShownLines()
{
    return pango_layout_get_line_count(layout);
};

int PangoLayoutWrapper::numberOfShownUnknownCharacters()
{
    return pango_layout_get_unknown_glyphs_count(layout);
};

Rect PangoLayoutWrapper::getExtent()
{
    Rect l_rect;
    l_rect >> offset;
    l_rect << size;
    return l_rect;
}
