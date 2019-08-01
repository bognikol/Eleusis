#pragma once

#include "VisualParameters.h"

#include <memory>

typedef struct _PangoLayout PangoLayout;
typedef struct _PangoAttribute PangoAttribute;

namespace Eleusis
{
    class Paragraph;

    class PangoLayoutWrapper
    {
    public:
        ~PangoLayoutWrapper();

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

        int numberOfShownCharacters();
        int numberOfShownLines();
        int numberOfShownUnknownCharacters();
        
        Rect getExtent();
    };
}

