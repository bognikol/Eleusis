#pragma once

#include "VisualParameters.h"
#include "pango/pangocairo.h"

#include <memory>

namespace Eleusis
{
    class Paragraph;

    class PangoLayoutWrapper
    {
    public:
        PangoLayoutWrapper()
        {
        }

        ~PangoLayoutWrapper()
        {
            g_object_unref(layout);
        }; 

        PangoLayout* layout = nullptr;
        Paragraph* paragraph = nullptr;

        Vector offset;
        Vector size;

        double spaceBefore = 0;
        double spaceAfter = 0;
        double leftIndent = 0;

        bool ellipsize = false;
        std::shared_ptr<Brush> fillBrush;

        PangoAttribute* selectionAttribute = nullptr;

        int numberOfShownCharacters()
        {
            return pango_layout_get_character_count(layout);
        };

        int numberOfShownLines()
        {
            return pango_layout_get_line_count(layout);
        };

        int numberOfShownUnknownCharacters()
        {
            return pango_layout_get_unknown_glyphs_count(layout);
        };

        Rect getExtent()
        {
            Rect l_rect;
            l_rect >> offset;
            l_rect << size;
            return l_rect;
        }
    };
}

