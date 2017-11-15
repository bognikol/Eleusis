#include "ParagraphStyle.h"

using namespace Eleusis;

void ParagraphStyle::cascadeFrom(const ParagraphStyle* source)
{
    if (!source->isApplied()) return;

    _fillBrush       += source->_fillBrush;
    _alignment       += source->_alignment;
    _firstLineIndent += source->_firstLineIndent;
    _leftIndent      += source->_leftIndent;
    _rightIndent     += source->_rightIndent;
    _spaceBefore     += source->_spaceBefore;
    _spaceAfter      += source->_spaceAfter;
    _lineSpacing     += source->_lineSpacing;
}