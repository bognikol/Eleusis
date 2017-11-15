#include "Span.h"
#include <string>

using namespace Eleusis;
using namespace std;

Span::Span()
{
    _initializeEventHandlers();
}

Span::Span(std::string text)
{
    _initializeEventHandlers();
    _text = text;
}

void Span::_initializeEventHandlers()
{
    _spanStyle_changedHandler =
        [this](SpanStyle* spanStyle, EventArgs* e)
    {
        SpanUpdatedEventArgs l_eventArgs;
        raiseEvent spanUpdated(this, &l_eventArgs);
    };
}

void Span::setText(string text)
{
    _text = text;

    SpanUpdatedEventArgs l_eventArgs;
    l_eventArgs.stringSizeChanged = true;
    raiseEvent spanUpdated(this, &l_eventArgs);
}

void Span::addText(string text)
{
    _text += text;

    SpanUpdatedEventArgs l_eventArgs;
    l_eventArgs.stringSizeChanged = true;
    raiseEvent spanUpdated(this, &l_eventArgs);
}

bool Span::_deleteRange(int startIndex, int endIndex)
{
    int l_textSize = static_cast<int>(_text.size());

    if (startIndex > endIndex)
        return false;

    if (endIndex < 0)
        return false;

    if (startIndex >= l_textSize)
        return false;

    if (startIndex <= 0 && endIndex >= l_textSize)
        return true;

    if (startIndex < 0)
        startIndex = 0;

    if (endIndex > l_textSize)
        endIndex = l_textSize;

    if (startIndex <= l_textSize)
        setText(_text.erase(startIndex, endIndex - startIndex));

    return false;
}

bool Span::contains(Vector v)
{
    return _region.contains(v);
}

void Span::_addRectToRegion(Rect rect)
{
    _region += rect;
}

void Span::_clearRegion()
{
    _region.clearRects();
}


