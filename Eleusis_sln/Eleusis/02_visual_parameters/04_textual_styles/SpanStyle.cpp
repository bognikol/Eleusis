#include "SpanStyle.h"

using namespace Eleusis;

void SpanStyle::cascadeFrom(const SpanStyle* source)
{
    if (!source->isApplied()) return;

    _textSize           += source->_textSize;
    _fontFamily         += source->_fontFamily;
    _fontVariant        += source->_fontVariant;
    _fontStyle          += source->_fontStyle;
    _fontStretch        += source->_fontStretch;
    _fontWeight         += source->_fontWeight;
    _fontFallback       += source->_fontFallback;
    _foregroundColor    += source->_foregroundColor;
    _backgroundColor    += source->_backgroundColor;
    _strikethrough      += source->_strikethrough;
    _strikethroughColor += source->_strikethroughColor;
    _underline          += source->_underline;
    _underlineColor     += source->_underlineColor;
    _characterRise      += source->_characterRise;
    _characterSpacing   += source->_characterSpacing;
    _gravity            += source->_gravity;
    _gravityHint        += source->_gravityHint;
}

