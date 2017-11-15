#include "TextBlockStyle.h"

using namespace Eleusis;

void TextBlockStyle::cascadeFrom(const TextBlockStyle* source)
{
    if (!source->isApplied()) return;

    _width     += source->_width;
    _height    += source->_height;
    _ellipsize += source->_ellipsize;
}