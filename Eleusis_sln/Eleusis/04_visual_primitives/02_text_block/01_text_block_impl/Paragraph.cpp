#include "Paragraph.h"

using namespace Eleusis;
using namespace std;

Paragraph::Paragraph()
{
    _initializeEventHandlers();
}

Paragraph::Paragraph(string text)
{
    _initializeEventHandlers();

    Span* span = new Span(text);
    insertSpan(span);
}

Paragraph::~Paragraph()
{
    delete _textualLayout;
    _textualLayout = nullptr;

    for (auto l_span : _spans)
        delete l_span;
}

void Paragraph::_initializeEventHandlers()
{
    _spans_updatedHandler = 
        [this](Span* sender, SpanUpdatedEventArgs* e) 
    {
        _stale = true;

        ParagraphUpdatedEventArgs l_eventArgs;
        l_eventArgs.stringSizeChanged = e->stringSizeChanged;
        raiseEvent paragraphUpdated(this, &l_eventArgs);
    };

    _spanStyle_changedHandler = 
        [this](SpanStyle* sender, EventArgs* e)
    {
        _stale = true;

        ParagraphUpdatedEventArgs l_eventArgs;
        raiseEvent paragraphUpdated(this, &l_eventArgs);
    };

    _paragraphStyle_changedHandler = 
        [this](ParagraphStyle* sender, EventArgs* e)
    {
        _stale = true;    

        ParagraphUpdatedEventArgs l_eventArgs;
        raiseEvent paragraphUpdated(this, &l_eventArgs);
    };
}

void Paragraph::insertSpan(Span* span)
{
    if (!span || find(_spans.begin(), _spans.end(), span) != _spans.end())
        return;

    _spans.push_back(span);
    span->spanUpdated += _spans_updatedHandler;

    _stale = true;

    ParagraphUpdatedEventArgs l_eventArgs;
    l_eventArgs.stringSizeChanged = true;
    raiseEvent paragraphUpdated(this, &l_eventArgs);
}

void Paragraph::insertSpanAfter(Span* spanToInsert, Span* referentSpan)
{
    _insertSpanAround(spanToInsert, referentSpan, true);
}

void Paragraph::insertSpanBefore(Span* spanToInsert, Span* referentSpan)
{
    _insertSpanAround(spanToInsert, referentSpan, false);
}

void Paragraph::_insertSpanAround(Span* spanToInsert, Span* referentSpan, bool after)
{
    if (!referentSpan || !spanToInsert) return;

    list<Span*>::iterator l_spanIter = find(_spans.begin(), _spans.end(), referentSpan);

    if (l_spanIter == _spans.end()) return;

    if (find(_spans.begin(), _spans.end(), spanToInsert) != _spans.end()) return;

    if (after) l_spanIter++;
    _spans.insert(l_spanIter, spanToInsert);
    spanToInsert->spanUpdated += _spans_updatedHandler;

    _stale = true;

    ParagraphUpdatedEventArgs l_eventArgs;
    l_eventArgs.stringSizeChanged = true;
    raiseEvent paragraphUpdated(this, &l_eventArgs);
}


void Paragraph::removeSpan(Span* span)
{
    if (!span || find(_spans.begin(), _spans.end(), span) == _spans.end()) 
        return;

    _spans.remove(span);
    span->spanUpdated -= _spans_updatedHandler;

    _stale = true;

    ParagraphUpdatedEventArgs l_eventArgs;
    l_eventArgs.stringSizeChanged = true;
    l_eventArgs.spanRemoved = span;
    raiseEvent paragraphUpdated(this, &l_eventArgs);
}

Span* Paragraph::_splitSpan(Span* span, int splitIndex)
{
    if (!span) return nullptr;
    if (splitIndex < 0 || span->getText().size() < static_cast<size_t>(splitIndex)) return nullptr;

    list<Span*>::iterator l_spanIter = find(_spans.begin(), _spans.end(), span);

    if (l_spanIter == _spans.end()) return nullptr;

    Span* l_newSpan = new Span(span->getText().substr(splitIndex, span->getText().size() - splitIndex));
    l_newSpan->spanStyle_set(span->spanStyle_get());

    span->setText(span->getText().substr(0, splitIndex));

    insertSpanAfter(l_newSpan, span);

    return l_newSpan;
}

void Paragraph::setText(std::string text)
{
    for (auto span : _spans)
        delete span;

    _spans.clear();

    Span* l_span = new Span(text);
    l_span->spanUpdated += _spans_updatedHandler;
    _spans.push_back(l_span);

    _stale = true;

    ParagraphUpdatedEventArgs l_eventArgs;
    l_eventArgs.stringSizeChanged = true;
    raiseEvent paragraphUpdated(this, &l_eventArgs);
}

void Paragraph::addText(std::string text)
{
    if (_spans.empty())
    {
        Span* l_span = new Span();
        _spans.push_back(l_span);
    }

    Span* l_lastSpan = _spans.back();
    l_lastSpan->setText(l_lastSpan->getText() + text);

    _stale = true;

    ParagraphUpdatedEventArgs l_eventArgs;
    l_eventArgs.stringSizeChanged = true;
    raiseEvent paragraphUpdated(this, &l_eventArgs);
}

bool Paragraph::_deleteRange(int startIndex, int endIndex)
{
    int l_textSize = static_cast<int>(_endIndex - _startIndex);

    if (startIndex > endIndex)
        return false;

    if (endIndex < 0)
        return false;

    if (startIndex >= l_textSize)
        return false;

    if (startIndex <= 0 && endIndex >= l_textSize)
        return true;

    vector<Span*> l_spanTrashBin;

    for (Span* span : _spans)
        if (span->_deleteRange(startIndex - span->_startIndex, endIndex - span->_startIndex))
            l_spanTrashBin.push_back(span);

    for (Span* span : l_spanTrashBin)
    {
        removeSpan(span);
        delete span;
    }

    return false;
}

std::string Paragraph::getText()
{
    string l_text;
    
    for (auto span : _spans)
        l_text += span->getText();

    return l_text;
}