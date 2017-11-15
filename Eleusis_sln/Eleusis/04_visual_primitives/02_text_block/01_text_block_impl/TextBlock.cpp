#include "TextBlock.h"
#include "CairoConverter.h"
#include "pango/pangocairo.h"
#include "Window.h"
#include "Application.h"

#include <string>
#include <sstream>
#include <algorithm>

using namespace Eleusis;
using namespace std;

TextBlock::TextBlock()
{
    _initializeEventHandlers();

    mouseClick       += makeHandler(&TextBlock::_routeMouseClickEvent);
    mouseUp          += makeHandler(&TextBlock::_routeMouseUpEvent);
    mouseDown        += makeHandler(&TextBlock::_routeMouseDownEvent);
    mouseDoubleClick += makeHandler(&TextBlock::_routeMouseDoubleClickEvent);
    mouseScroll      += makeHandler(&TextBlock::_routeMouseScrollEvent);
    mouseMove        += makeHandler(&TextBlock::_routeMouseMoveEvent);
    mouseLeave       += makeHandler(&TextBlock::_routeMouseLeaveEvent);
}

TextBlock::~TextBlock()
{
    for (auto l_paragraph : _paragraphs)
        delete l_paragraph;
}

void TextBlock::_initializeEventHandlers()
{
    _paragraphs_updatedHandler = 
        [this](Paragraph* sender, ParagraphUpdatedEventArgs* e)
    {
        if (e->spanRemoved)
        {
            if (_currentMouseMoveSpan == e->spanRemoved)
            {
                MouseEventArgs e;
                raiseEvent _currentMouseMoveSpan->mouseLeave(_currentMouseMoveSpan, &e);
                _currentMouseMoveSpan = nullptr;
            }
        }

        if (e->stringSizeChanged)
            _enumarateParagraphs();

        _requestGeometryUpdate();
    };

    _spanStyle_changedHandler = 
        [this](SpanStyle* sender, EventArgs* e)
    {
        _requestGeometryUpdate();
    };

    _paragraphStyle_changedHandler = 
        [this](ParagraphStyle* sender, EventArgs* e) 
    {
        _requestGeometryUpdate();
    };

    _textBlockStyle_changedHandler = 
        [this](TextBlockStyle* sender, EventArgs* e) 
    {
        _requestGeometryUpdate();
    };
}

#pragma region SPAN/PARAGRAPH EVENT ROUTERS   

void TextBlock::_routeMouseClickEvent(Node* sender, MouseEventArgs* e)
{
    Vector l_location(e->X - _absoluteOffsetVector.X, e->Y - _absoluteOffsetVector.Y);

    for (auto paragraph : _paragraphs)
        if (paragraph->getExtent().contains(l_location))
        {
            for (auto span : paragraph->getSpans())
            {
                if (span->contains(l_location))
                {
                    raiseEvent span->mouseClick(span, e);
                    break;
                }
            }
            raiseEvent paragraph->mouseClick(paragraph, e);
            break;
        }
}

void TextBlock::_routeMouseUpEvent(Node* sender, MouseEventArgs* e)
{
    Vector l_location(e->X - _absoluteOffsetVector.X, e->Y - _absoluteOffsetVector.Y);

    for (auto paragraph : _paragraphs)
    {
        if (paragraph->getExtent().contains(l_location))
        {
            for (auto span : paragraph->getSpans())
            {
                if (span->contains(l_location))
                {
                    raiseEvent span->mouseUp(span, e);
                    break;
                }
            }
            raiseEvent paragraph->mouseUp(paragraph, e);
            break;
        }
    }
}

void TextBlock::_routeMouseDownEvent(Node* sender, MouseEventArgs* e)
{
    Vector l_location(e->X - _absoluteOffsetVector.X, e->Y - _absoluteOffsetVector.Y);

    for (auto paragraph : _paragraphs)
    {
        if (paragraph->getExtent().contains(l_location))
        {
            for (auto span : paragraph->getSpans())
            {
                if (span->contains(l_location))
                {
                    raiseEvent span->mouseDown(span, e);
                    break;
                }
            }
            raiseEvent paragraph->mouseDown(paragraph, e);
            break;
        }
    }
}

void TextBlock::_routeMouseDoubleClickEvent(Node* sender, MouseEventArgs* e)
{
    Vector l_location(e->X - _absoluteOffsetVector.X, e->Y - _absoluteOffsetVector.Y);

    for (auto paragraph : _paragraphs)
    {
        if (paragraph->getExtent().contains(l_location))
        {
            for (auto span : paragraph->getSpans())
            {
                if (span->contains(l_location))
                {
                    raiseEvent span->mouseDoubleClick(span, e);
                    break;
                }
            }
            raiseEvent paragraph->mouseDoubleClick(paragraph, e);
            break;
        }
    }
}

void TextBlock::_routeMouseMoveEvent(Node* sender, MouseEventArgs* e)
{
    if (sender != e->PrimarySender)
    {
        if (_currentMouseMoveParagraph)
            raiseEvent _currentMouseMoveParagraph->mouseLeave(_currentMouseMoveParagraph, e);
        if (_currentMouseMoveSpan)
            raiseEvent _currentMouseMoveSpan->mouseLeave(_currentMouseMoveSpan, e);
        return;
    }

    Vector l_location(e->X - _absoluteOffsetVector.X, e->Y - _absoluteOffsetVector.Y);

    for (auto paragraph : _paragraphs)
    {
        if (paragraph->getExtent().contains(l_location))
        {
            if (_currentMouseMoveParagraph != paragraph)
            {
                if (_currentMouseMoveParagraph)
                    raiseEvent _currentMouseMoveParagraph->mouseLeave(_currentMouseMoveParagraph, e);
                _currentMouseMoveParagraph = paragraph;
                raiseEvent _currentMouseMoveParagraph->mouseEnter(paragraph, e);
            }
            for (auto span : paragraph->getSpans())
            {
                if (span->contains(l_location))
                {
                    if (_currentMouseMoveSpan != span)
                    {
                        if (_currentMouseMoveSpan)
                            raiseEvent _currentMouseMoveSpan->mouseLeave(_currentMouseMoveSpan, e);
                        _currentMouseMoveSpan = span;
                        raiseEvent _currentMouseMoveSpan->mouseEnter(span, e);
                    }
                    raiseEvent span->mouseMove(span, e);
                    break;
                }
                else
                {
                    if (_currentMouseMoveSpan)
                        raiseEvent _currentMouseMoveSpan->mouseLeave(_currentMouseMoveSpan, e);
                    _currentMouseMoveSpan = nullptr;

                }
            }

            raiseEvent paragraph->mouseMove(paragraph, e);
            break;
        }
        else
        {
            if (_currentMouseMoveSpan)
                raiseEvent _currentMouseMoveSpan->mouseLeave(_currentMouseMoveSpan, e);
            _currentMouseMoveSpan = nullptr;
            if (_currentMouseMoveParagraph)
                raiseEvent _currentMouseMoveParagraph->mouseLeave(_currentMouseMoveParagraph, e);
            _currentMouseMoveParagraph = nullptr;
        }
    }
}

void TextBlock::_routeMouseScrollEvent(Node* sender, MouseScrollEventArgs* e)
{
    Vector l_location(e->X - _absoluteOffsetVector.X, e->Y - _absoluteOffsetVector.Y);

    for (auto paragraph : _paragraphs)
    {
        if (paragraph->getExtent().contains(l_location))
        {
            for (auto span : paragraph->getSpans())
            {
                if (span->contains(l_location))
                {
                    raiseEvent span->mouseScroll(span, e);
                    break;
                }
            }
            raiseEvent paragraph->mouseScroll(paragraph, e);
            break;
        }
    }
}

void TextBlock::_routeMouseLeaveEvent(Node* sender, MouseEventArgs* e)
{
    if (_currentMouseMoveSpan)
    {
        raiseEvent _currentMouseMoveSpan->mouseLeave(_currentMouseMoveSpan, e);
        _currentMouseMoveSpan = nullptr;
    }
    if (_currentMouseMoveParagraph)
    {
        raiseEvent _currentMouseMoveParagraph->mouseLeave(_currentMouseMoveParagraph, e);
        _currentMouseMoveParagraph = nullptr;
    }
}

#pragma endregion

#pragma region PARAGRAPH MANIPULATION

void TextBlock::_enumarateParagraphs()
{
    if (_enumerationSuspended)
        return;

    int l_currentNumberOfCharactersInTextBlock = 0;

    for (auto paragraph : _paragraphs)
    {
        paragraph->_startIndex = l_currentNumberOfCharactersInTextBlock;

        int l_currentNumberOfCharactersInParagraph = 0;

        for (auto span : paragraph->getSpans())
        {
            span->_startIndex = l_currentNumberOfCharactersInParagraph;
            l_currentNumberOfCharactersInParagraph += span->getText().size();
            span->_endIndex = l_currentNumberOfCharactersInParagraph;
        }

        l_currentNumberOfCharactersInTextBlock += l_currentNumberOfCharactersInParagraph;

        if (paragraph != _paragraphs.back())
            l_currentNumberOfCharactersInTextBlock++;

        paragraph->_endIndex = l_currentNumberOfCharactersInTextBlock;
    }

    _numberOfUTF8Bytes = l_currentNumberOfCharactersInTextBlock;
}

void TextBlock::_insertParagraphAround(Paragraph* paragraphToInsert, Paragraph* referentParagraph, bool after)
{
    if (!referentParagraph) return;

    list<Paragraph*>::iterator l_paragraphIter = find(_paragraphs.begin(), _paragraphs.end(), referentParagraph);

    if (l_paragraphIter == _paragraphs.end()) return;

    if (!paragraphToInsert) return;

    _paragraphs.remove(paragraphToInsert);

    if (after) l_paragraphIter++;
    _paragraphs.insert(l_paragraphIter, paragraphToInsert);

    paragraphToInsert->paragraphUpdated += _paragraphs_updatedHandler;
    _enumarateParagraphs();
    _requestGeometryUpdate();
}

void TextBlock::insertParagraph(Paragraph* paragraph)
{
    if (!paragraph || find(_paragraphs.begin(), _paragraphs.end(), paragraph) != _paragraphs.end()) return;

    _paragraphs.push_back(paragraph);
    paragraph->paragraphUpdated += _paragraphs_updatedHandler;
    _enumarateParagraphs();
    _requestGeometryUpdate();
}

void TextBlock::insertParagraphAfter(Paragraph* paragraphToInsert, Paragraph* referentParagraph)
{
    _insertParagraphAround(paragraphToInsert, referentParagraph, true);
}

void TextBlock::insertParagraphBefore(Paragraph* paragraphToInsert, Paragraph* referentParagraph)
{
    _insertParagraphAround(paragraphToInsert, referentParagraph, false);
}

void TextBlock::removeParagraph(Paragraph* paragraph)
{
    if (!paragraph || find(_paragraphs.begin(), _paragraphs.end(), paragraph) == _paragraphs.end()) return;

    if (paragraph == _currentMouseMoveParagraph)
    {
        if (find(paragraph->_spans.begin(), paragraph->_spans.end(), _currentMouseMoveSpan) != paragraph->_spans.end())
        {
            MouseEventArgs e;
            raiseEvent _currentMouseMoveSpan->mouseLeave(_currentMouseMoveSpan, &e);
            _currentMouseMoveSpan = nullptr;
        }

        MouseEventArgs e;
        raiseEvent paragraph->mouseLeave(paragraph, &e);
        _currentMouseMoveParagraph = nullptr;
    }

    _paragraphs.remove(paragraph);

    delete paragraph->_textualLayout;
    paragraph->_textualLayout = nullptr;

    paragraph->paragraphUpdated -= _paragraphs_updatedHandler;
    _enumarateParagraphs();
    _requestGeometryUpdate();
}

#pragma endregion

#pragma region TEXT MANIPUALTION

void TextBlock::setText(std::string text)
{
    for (auto paragraph : _paragraphs)
        delete paragraph;

    _paragraphs.clear();

    _currentMouseMoveParagraph = nullptr;
    _currentMouseMoveSpan      = nullptr;

    if (text.empty())
    {
        insertParagraph(new Paragraph(""));
        return;
    }

    istringstream l_stringStream(text);
    string l_string;

    while (getline(l_stringStream, l_string, '\n'))
        insertParagraph(new Paragraph(l_string));
}

void TextBlock::addText(string text)
{
    istringstream l_stringStream(text);
    string l_string;

    while (getline(l_stringStream, l_string, '\n'))
        insertParagraph(new Paragraph(l_string));
}

void TextBlock::insertText(string text, int startIndex)
{
    if (startIndex < -1 || 
        startIndex > numberOfUTF8Bytes())
        return;

    if (startIndex == -1)
    {
        addText(text);
        return;
    }

    text.erase(std::remove(text.begin(), text.end(), '\n'), text.end());

    Paragraph* l_paragraph = nullptr;
    
    if (_paragraphs.empty() && startIndex == 0)
    {
        l_paragraph = new Paragraph();
        insertParagraph(l_paragraph);
    }
    else
    {
        l_paragraph = _getParagraphWithCharacter(startIndex);
        if (!l_paragraph) return;
    }

    if (l_paragraph->_spans.empty() && startIndex == l_paragraph->_startIndex)
    {
        Span* l_targetSpan = new Span();
        l_paragraph->insertSpan(l_targetSpan);
        l_targetSpan->setText(text);
    }
    else
    {
        Span* l_targetSpan = _getSpanWithCharacter(startIndex, l_paragraph);
        if (!l_targetSpan) return;
        int l_spanRelativeCharacterIndex = startIndex - l_paragraph->_startIndex - l_targetSpan->_startIndex;
        l_targetSpan->setText(l_targetSpan->getText().insert(l_spanRelativeCharacterIndex, text));
    }
}

std::string TextBlock::getText()
{
    string l_text;

    for (auto paragraph : _paragraphs)
        if (paragraph != _paragraphs.back())
            l_text += paragraph->getText() + "\n";
        else
            l_text += paragraph->getText();

    return l_text;
}

void TextBlock::insertNewLine(int index)
{
    Paragraph* l_paragraph = _getParagraphWithCharacter(index);
    _splitParagraph(l_paragraph, index - l_paragraph->_startIndex);
}

#pragma endregion

#pragma region PUBLIC UTILITY FUNCTIONS

Rect TextBlock::getCharacterExtent(int index)
{
    if (index < 0) return Rect();

    Paragraph* l_paragraph = _getParagraphWithCharacter(index);

    if (!l_paragraph) return Rect();

    int l_characterIndexInTLayout = index - l_paragraph->_startIndex;

    PangoRectangle l_rect;
    pango_layout_index_to_pos(l_paragraph->_textualLayout->layout, l_characterIndexInTLayout, &l_rect);

    Rect l_rectRet;
    l_rectRet >> Vector(l_rect.x / PANGO_SCALE, l_rect.y / PANGO_SCALE) + l_paragraph->_textualLayout->offset + _absoluteOffsetVector;
    l_rectRet << Vector(l_rect.width / PANGO_SCALE, l_rect.height / PANGO_SCALE);
    return l_rectRet;
}

Rect TextBlock::getCharacterExtent(Vector coordinates)
{
    int cumulativeCharacterNumber = -1;
    coordinates -= _absoluteOffsetVector;

    int totalCharacters = 0;

    for (auto paragraph : _paragraphs)
    {
        PangoLayoutWrapper* tLayout = paragraph->_textualLayout;
        if (!tLayout) continue;

        totalCharacters = tLayout->paragraph->_startIndex;

        if (tLayout->getExtent().contains(coordinates))
        {
            coordinates -= tLayout->offset;
            int index;
            if (pango_layout_xy_to_index(tLayout->layout, 
                static_cast<int>(coordinates.X * PANGO_SCALE), 
                static_cast<int>(coordinates.Y * PANGO_SCALE), 
                &index, 
                nullptr))
            {
                PangoRectangle l_rect;
                pango_layout_index_to_pos(tLayout->layout, index, &l_rect);

                Rect l_rectRet;
                l_rectRet >> Vector(l_rect.x / PANGO_SCALE, l_rect.y / PANGO_SCALE) + tLayout->offset + _absoluteOffsetVector;
                l_rectRet << Vector(l_rect.width / PANGO_SCALE, l_rect.height / PANGO_SCALE);
                return l_rectRet;
            }
        }
    }

    return Rect();
}

int TextBlock::getCharacterIndex(Vector coordinates)
{
    coordinates -= _absoluteOffsetVector;

    int totalCharacters = 0;

    for (auto paragraph : _paragraphs)
    {
        PangoLayoutWrapper* tLayout = paragraph->_textualLayout;
        if (!tLayout) continue;

        totalCharacters = tLayout->paragraph->_startIndex;

        if (tLayout->getExtent().contains(coordinates))
        {
            coordinates -= tLayout->offset;
            int index;
            if (pango_layout_xy_to_index(tLayout->layout, 
                static_cast<int>(coordinates.X * PANGO_SCALE), 
                static_cast<int>(coordinates.Y * PANGO_SCALE), 
                &index, 
                nullptr))
                return totalCharacters + index;
            else
                return -1;
        }
    }

    return -1;
}

Rect TextBlock::getCarretExtentForCharacter(int index)
{
    if (index < 0) return Rect();

    Paragraph* l_paragraph = _getParagraphWithCharacter(index);

    if (!l_paragraph || !l_paragraph->_textualLayout)
        return Rect();

    int l_characterIndexInTLayout = index - l_paragraph->_startIndex;

    PangoRectangle l_rect;
    pango_layout_get_cursor_pos(l_paragraph->_textualLayout->layout, l_characterIndexInTLayout, &l_rect, nullptr);

    Rect l_rectRet;
    l_rectRet >> Vector(l_rect.x / PANGO_SCALE, l_rect.y / PANGO_SCALE) + l_paragraph->_textualLayout->offset;
    l_rectRet << Vector(l_rect.width / PANGO_SCALE, l_rect.height / PANGO_SCALE);
    return l_rectRet;
}

int TextBlock::numberOfShownCharacters()
{
    int l_numberOfCharacters = 0;

    for (auto paragraph : _paragraphs)
    {
        PangoLayoutWrapper* tLayout = paragraph->_textualLayout;
        if (!tLayout) continue;
        l_numberOfCharacters += tLayout->numberOfShownCharacters();
    }

    return l_numberOfCharacters;
}

int TextBlock::numberOfShownUnknownCharacters()
{
    int l_numberOfUnknownCharacters = 0;

    for (auto paragraph : _paragraphs)
    {
        PangoLayoutWrapper* tLayout = paragraph->_textualLayout;
        if (!tLayout) continue;
        l_numberOfUnknownCharacters += tLayout->numberOfShownUnknownCharacters();
    }

    return l_numberOfUnknownCharacters;
}

int TextBlock::numberOfShownLines()
{
    int l_numberOfLines = 0;

    for (auto paragraph : _paragraphs)
    {
        PangoLayoutWrapper* tLayout = paragraph->_textualLayout;
        if (!tLayout) continue;
        l_numberOfLines += tLayout->numberOfShownLines();
    }

    return l_numberOfLines;
}

#pragma endregion

#pragma region PROTECTED UTILITY FUNCTIONS

int TextBlock::_moveLeft(int index)
{
    if (index == 0) return 0;

    Paragraph* l_paragraph = _getParagraphWithCharacter(index);

    if (l_paragraph->_startIndex == index)
    {
        return index - 1;
    }

    int l_newIndex = 0;
    int l_newTrailing = 0;

    pango_layout_move_cursor_visually(l_paragraph->_textualLayout->layout, true, index - l_paragraph->_startIndex, 0, -1, &l_newIndex, &l_newTrailing);

    return l_newIndex + l_paragraph->_startIndex;
}

int TextBlock::_moveRight(int index)
{
    if (index == _numberOfUTF8Bytes) return index;

    Paragraph* l_paragraph = _getParagraphWithCharacter(index);

    if (l_paragraph->_endIndex - 1 == index)
    {
        return index + 1;
    }

    int l_newIndex = 0;
    int l_newTrailing = 0;

    pango_layout_move_cursor_visually(l_paragraph->_textualLayout->layout, true, index - l_paragraph->_startIndex, 0, 1, &l_newIndex, &l_newTrailing);

    return l_newIndex + l_newTrailing + l_paragraph->_startIndex;
}

int TextBlock::_moveUp(int currentAbsoluteIndex, int desiredIndexWithinLine)
{
    if (currentAbsoluteIndex == 0) return 0;

    Paragraph* l_paragraph = _getParagraphWithCharacter(currentAbsoluteIndex);

    if (!l_paragraph || !l_paragraph->_textualLayout) return 0;

    int l_lineIndex = 0;
    int l_listPosition = 0;

    pango_layout_index_to_line_x(l_paragraph->_textualLayout->layout, currentAbsoluteIndex - l_paragraph->_startIndex, false, &l_lineIndex, &l_listPosition);

    if (l_lineIndex == 0)
    {
        if (l_paragraph == _paragraphs.front())
            return currentAbsoluteIndex;

        l_paragraph = _getPreviousParagraph(l_paragraph);

        PangoLayoutLine* l_pangoUpperLine = pango_layout_get_line(l_paragraph->_textualLayout->layout, l_paragraph->_textualLayout->numberOfShownLines() - 1);

        if (l_pangoUpperLine->length - 1 < desiredIndexWithinLine)
            desiredIndexWithinLine = l_pangoUpperLine->length - 1;

        return l_paragraph->_startIndex + l_pangoUpperLine->start_index + desiredIndexWithinLine;
    }

    PangoLayoutLine* l_pangoUpperLine = pango_layout_get_line(l_paragraph->_textualLayout->layout, l_lineIndex - 1);

    if (l_pangoUpperLine->length - 1 < desiredIndexWithinLine)
        desiredIndexWithinLine = l_pangoUpperLine->length - 1;

    return l_paragraph->_startIndex + l_pangoUpperLine->start_index + desiredIndexWithinLine;
}

int TextBlock::_moveDown(int currentAbsoluteIndex, int desiredIndexWithinLine)
{
    if (currentAbsoluteIndex == numberOfUTF8Bytes()) return numberOfUTF8Bytes();

    Paragraph* l_paragraph = _getParagraphWithCharacter(currentAbsoluteIndex);

    if (!l_paragraph || !l_paragraph->_textualLayout) return 0;

    int l_lineIndex = 0;
    int l_listPosition = 0;

    pango_layout_index_to_line_x(l_paragraph->_textualLayout->layout, currentAbsoluteIndex - l_paragraph->_startIndex, false, &l_lineIndex, &l_listPosition);

    if (l_lineIndex == l_paragraph->_textualLayout->numberOfShownLines() - 1)
    {
        if (l_paragraph == _paragraphs.back())
            return currentAbsoluteIndex;

        l_paragraph = _getNextParagraph(l_paragraph);

        PangoLayoutLine* l_pangoLowerLine = pango_layout_get_line(l_paragraph->_textualLayout->layout, 0);

        if (l_pangoLowerLine->length - 1 < desiredIndexWithinLine)
            desiredIndexWithinLine = l_pangoLowerLine->length - 1;

        return l_paragraph->_startIndex + l_pangoLowerLine->start_index + desiredIndexWithinLine;
    }

    PangoLayoutLine* l_pangoLowerLine = pango_layout_get_line(l_paragraph->_textualLayout->layout, l_lineIndex + 1);

    if (l_pangoLowerLine->length - 1 < desiredIndexWithinLine)
        desiredIndexWithinLine = l_pangoLowerLine->length - 1;

    return l_paragraph->_startIndex + l_pangoLowerLine->start_index + desiredIndexWithinLine;
}

int TextBlock::_positionWithinLine(int currentAbsoluteIndex)
{
    if (currentAbsoluteIndex == 0) return 0;

    Paragraph* l_paragraph = _getParagraphWithCharacter(currentAbsoluteIndex);

    if (!l_paragraph || !l_paragraph->_textualLayout) return 0;

    int l_lineIndex = 0;
    int l_listPosition = 0;

    pango_layout_index_to_line_x(l_paragraph->_textualLayout->layout, currentAbsoluteIndex - l_paragraph->_startIndex, false, &l_lineIndex, &l_listPosition);

    PangoLayoutLine* l_pangoLine = pango_layout_get_line(l_paragraph->_textualLayout->layout, l_lineIndex);

    int l_indexWithinLine = currentAbsoluteIndex - l_paragraph->_startIndex - l_pangoLine->start_index;

    return l_indexWithinLine;
}

void TextBlock::_mergeParagraphs(Paragraph* target, Paragraph* source)
{
    vector<Span*> spans;

    for (Span* span : source->getSpans())
        spans.push_back(span);

    for (Span* span : spans)
        source->removeSpan(span);

    for (Span* span : spans)
        target->insertSpan(span);

    removeParagraph(source);
    delete source;
}

void TextBlock::_splitParagraph(Paragraph* paragraph, int splitIndex)
{
    list<Paragraph*>::iterator l_paragraphIter = find(_paragraphs.begin(), _paragraphs.end(), paragraph);

    if (l_paragraphIter == _paragraphs.end())
        return;

    if (paragraph->_endIndex - paragraph->_startIndex < splitIndex)
        return;

    Span* l_spanToBeSplit = _getSpanWithCharacter(splitIndex + paragraph->_startIndex, paragraph);

    Span* l_newSpan = paragraph->_splitSpan(l_spanToBeSplit, splitIndex - l_spanToBeSplit->_startIndex);

    if (!l_newSpan) return;

    list<Span*>::iterator l_newSpanIter = find(paragraph->_spans.begin(), paragraph->_spans.end(), l_newSpan);

    Paragraph* l_newParagraph = new Paragraph();
    l_newParagraph->spanStyle_set(paragraph->spanStyle_get());
    l_newParagraph->paragraphStyle_set(paragraph->paragraphStyle_get());

    list<Span*> l_spansToBeMoved;

    for (list<Span*>::iterator it = l_newSpanIter; it != paragraph->_spans.end(); it++)
        l_spansToBeMoved.push_back(*it);

    for (Span* span : l_spansToBeMoved)
    {
        paragraph->removeSpan(span);
        l_newParagraph->insertSpan(span);
    }

    insertParagraphAfter(l_newParagraph, paragraph);
}

void TextBlock::_deleteRange(int startIndex, int endIndex)
{
    if (startIndex == endIndex) return;

    _enumerationSuspended = true;

    CharacterRange range = _getCharacterRange(startIndex, endIndex);

    vector<Paragraph*> l_paragraphTrashBin;

    for (Paragraph* paragraph : _paragraphs)
        if (paragraph->_deleteRange(range.start.index - paragraph->_startIndex, range.end.index - paragraph->_startIndex))
            l_paragraphTrashBin.push_back(paragraph);

    for (Paragraph* paragraph : l_paragraphTrashBin)
    {
        removeParagraph(paragraph);
        delete paragraph;
    }

    if (find(l_paragraphTrashBin.begin(), l_paragraphTrashBin.end(), range.start.paragraph) == l_paragraphTrashBin.end() &&
        find(l_paragraphTrashBin.begin(), l_paragraphTrashBin.end(), range.end.paragraph) == l_paragraphTrashBin.end() &&
        range.start.paragraph != range.end.paragraph)
    {
        if ((range.start.role == CharacterRoleInParagraph::Regular && range.end.role == CharacterRoleInParagraph::FirstInParagraph) ||
            (range.start.role == CharacterRoleInParagraph::Regular && range.end.role == CharacterRoleInParagraph::Regular) ||
            (range.start.role == CharacterRoleInParagraph::LastInParagraph && range.end.role == CharacterRoleInParagraph::FirstInParagraph) ||
            (range.start.role == CharacterRoleInParagraph::LastInParagraph && range.end.role == CharacterRoleInParagraph::Regular))
        {
            _mergeParagraphs(range.start.paragraph, range.end.paragraph);
        }
    }

    _enumerationSuspended = false;

    _enumarateParagraphs();
}

void TextBlock::_highlightRange(int startIndex, int endIndex)
{
    if (startIndex < 0) startIndex = 0;
    if (endIndex   < 0) endIndex = 0;

    if (startIndex > endIndex)
        std::swap(startIndex, endIndex);

    Paragraph* l_startParagraph = _getParagraphWithCharacter(startIndex);
    Paragraph* l_endParagraph = _getParagraphWithCharacter(endIndex);

    for (auto paragraph : _paragraphs)
    {
        if (paragraph->_textualLayout) paragraph->_textualLayout->selectionAttribute->start_index = 0;
        if (paragraph->_textualLayout) paragraph->_textualLayout->selectionAttribute->end_index = 0;
    }

    if (l_startParagraph == nullptr) l_startParagraph = _paragraphs.front();
    if (l_endParagraph == nullptr) l_endParagraph = _paragraphs.back();

    startIndex -= l_startParagraph->_startIndex;
    endIndex -= l_endParagraph->_startIndex;

    if (l_startParagraph->_textualLayout)
        l_startParagraph->_textualLayout->selectionAttribute->start_index = startIndex;

    if (l_endParagraph->_textualLayout)
        l_endParagraph->_textualLayout->selectionAttribute->end_index = endIndex;

    if (l_startParagraph != l_endParagraph)
    {
        if (l_startParagraph->_textualLayout)
            l_startParagraph->_textualLayout->selectionAttribute->end_index = l_startParagraph->_numberOfUTF8Characters();
        if (l_endParagraph->_textualLayout)
            l_endParagraph->_textualLayout->selectionAttribute->start_index = 0;

        bool valid = false;

        for (auto paragraph : _paragraphs)
        {
            if (paragraph == l_endParagraph) break;

            if (valid)
            {
                if (paragraph->_textualLayout)
                {
                    paragraph->_textualLayout->selectionAttribute->start_index = 0;
                    paragraph->_textualLayout->selectionAttribute->end_index = paragraph->_numberOfUTF8Characters();
                }

            }

            if (!valid && paragraph == l_startParagraph) valid = true;
        }
    }

    _requestRendering();
}

Paragraph* TextBlock::_getParagraphWithCharacter(int characterIndex)
{
    if (_paragraphs.empty())
        return nullptr;

    if (characterIndex == _paragraphs.back()->_endIndex)
        return _paragraphs.back();

    for (Paragraph* paragraph : _paragraphs)
        if (characterIndex >= paragraph->_startIndex &&
            characterIndex <  paragraph->_endIndex)
            return paragraph;

    return nullptr;
}

Span* TextBlock::_getSpanWithCharacter(int characterIndex, Paragraph* paragraph)
{
    if (!paragraph)
        return nullptr;

    if (characterIndex == paragraph->_endIndex - 1 ||
        (characterIndex == paragraph->_endIndex && paragraph == _paragraphs.back()))
        return paragraph->getSpans().back();

    for (Span* span : paragraph->getSpans())
        if (span->_startIndex <= characterIndex - paragraph->_startIndex &&
            span->_endIndex   >  characterIndex - paragraph->_startIndex)
            return span;

    return nullptr;
}

#pragma endregion

#pragma region PRIVATE UTILITY FUNCTIONS

bool TextBlock::_sanitizeRange(int* startIndex, int* endIndex)
{
    if (*startIndex < 0) *startIndex = 0;
    if (*endIndex < 0) *endIndex = 0;

    if (*startIndex > *endIndex)
        std::swap(*startIndex, *endIndex);

    int l_lastValidIndex = numberOfUTF8Bytes();

    if (*startIndex > l_lastValidIndex)
        *startIndex = l_lastValidIndex;

    if (*endIndex > l_lastValidIndex)
        *endIndex = l_lastValidIndex;

    return true;
}

TextBlock::CharacterRecord TextBlock::_calculateCharacterRecord(int index)
{
    CharacterRecord l_record;

    l_record.index = index;

    l_record.paragraph = _getParagraphWithCharacter(index);

    if (!l_record.paragraph)
        return l_record;

    if (index == l_record.paragraph->_startIndex)
        l_record.role = CharacterRoleInParagraph::FirstInParagraph;
    else if (index == l_record.paragraph->_endIndex - 1)
        l_record.role = CharacterRoleInParagraph::LastInParagraph;
    else
        l_record.role = CharacterRoleInParagraph::Regular;

    return l_record;
}

TextBlock::CharacterRange TextBlock::_getCharacterRange(int startIndex, int endIndex)
{
    _sanitizeRange(&startIndex, &endIndex);

    CharacterRange l_range;

    l_range.start = _calculateCharacterRecord(startIndex);
    l_range.end = _calculateCharacterRecord(endIndex);

    return l_range;
}

Paragraph* TextBlock::_getNextParagraph(Paragraph* paragraph)
{
    bool l_found = false;

    for (auto l_paragraph : _paragraphs)
    {
        if (l_found) return l_paragraph;
        if (paragraph == l_paragraph) l_found = true;
    }

    return nullptr;
}

Paragraph* TextBlock::_getPreviousParagraph(Paragraph* paragraph)
{
    Paragraph* l_previous = nullptr;

    for (auto l_paragraph : _paragraphs)
    {
        if (l_paragraph == paragraph) return l_previous;
        l_previous = l_paragraph;
    }

    return nullptr;
}

#pragma endregion

#pragma region RENDERING PIPELINE FUNCTIONS

Rect TextBlock::getExtent()
{
    Rect l_extent;
    l_extent.lowVector = _absoluteOffsetVector;
    l_extent.highVector = l_extent.lowVector + _size;
    return l_extent;
}

Rect TextBlock::getFullExtent()
{
    Rect l_fullExtent = getExtent();
    Rect l_vpExtent;

    Node* l_child = firstChild();
    if (!l_child) return l_fullExtent;

    Node* l_lastDescendant = lastDescendant();

    while (true)
    {
        if (l_child->isVisualPrimitive())
        {
            l_vpExtent = static_cast<VisualPrimitive*>(l_child)->getExtent();
            if (!l_vpExtent.isZero())
            {
                if (l_fullExtent.isZero())
                    l_fullExtent = static_cast<VisualPrimitive*>(l_child)->getExtent();
                else
                    l_fullExtent |= static_cast<VisualPrimitive*>(l_child)->getExtent();
            }
        }
        if (l_child == l_lastDescendant) break;
        l_child = l_child->next();
        if (!l_child) break;
    }

    return l_fullExtent;
}

void TextBlock::_doCairoDrawing(cairo_t* cairoContext, Region* region)
{
    Region l_effectiveRegion;

    if (region)
    {
        l_effectiveRegion = *region;
    }

    if (!_clippingRect.isZero())
    {
        if (l_effectiveRegion.isEmpty())
            l_effectiveRegion += _clippingRect;
        else
            l_effectiveRegion.clip(_clippingRect);
    }

    if (!l_effectiveRegion.isEmpty())
    {
        Geometry l_windowSpaceClipingPath(&l_effectiveRegion);
        cairo_append_path(cairoContext, l_windowSpaceClipingPath.getCairoPath());
        cairo_clip(cairoContext);
    }

    for (auto paragraph : _paragraphs)
    {
        if (!paragraph->_textualLayout) continue;

        cairo_set_antialias(cairoContext, cairo_antialias_t::CAIRO_ANTIALIAS_DEFAULT);

        if (paragraph->_textualLayout->fillBrush)
        {
            cairo_set_source(cairoContext, paragraph->_textualLayout->fillBrush->getCairoPattern());
            cairo_set_fill_rule(cairoContext, cairo_fill_rule_t::CAIRO_FILL_RULE_WINDING);
            cairo_fill(cairoContext);
        }

        cairo_translate(cairoContext, _absoluteOffsetVector.X + paragraph->_textualLayout->offset.X, _absoluteOffsetVector.Y + paragraph->_textualLayout->offset.Y);
        pango_cairo_update_layout(cairoContext, paragraph->_textualLayout->layout);
        pango_cairo_show_layout(cairoContext, paragraph->_textualLayout->layout);
        cairo_identity_matrix(cairoContext);
    }

    cairo_reset_clip(cairoContext);
}

void TextBlock::_updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector)
{
	// TODO: BUG 
	// This won't work as expected because _absoluteSizeVector does not represent actual size of TextBlock.
	// Obtaining actual size of _absoluteSizeVector for TextBlock is problematic because we cannot have 
	// actual size before updating geometry, but we cannot update geometry before having absolute size vector 
	// which is used as an indicator whether geometry should be updated at all.
	// This implies that we must change our rendering pipeline.

	_updateAbsoluteVectorExecutedOnce = true;

	TextBlockStyle l_textBlockStyle;
	if (this->textBlockStyle_get()) l_textBlockStyle.cascadeFrom(this->textBlockStyle_get().get());

	Vector l_absoluteSizeVector =
	{
		l_textBlockStyle.width_get()->value().getValueRelativeTo(parentAbsoluteSizeVector.X),
		l_textBlockStyle.height_get()->value().getValueRelativeTo(parentAbsoluteSizeVector.Y)
	};

	if (l_absoluteSizeVector != _absoluteSizeVector) *changed = true;
	else *changed = false;

	_absoluteSizeVector = l_absoluteSizeVector;
}

void TextBlock::_render(Region* region)
{
    if (!_uiContext) return;
    if (!visibility_get()) return;

    _doCairoDrawing(_uiContext->getCairoContext(), region);

    Node* l_nextChild = firstChild();

    while (true)
    {
        if (!l_nextChild) break;
        l_nextChild->_render();
        l_nextChild = l_nextChild->nextSibling();
    }
}

#pragma region GEOMETRY UPDATE FUNCTIONS

void TextBlock::_insertSingleAttribute(PangoAttrList* attrList, int startIndex, int endIndex, PangoAttribute* attr)
{
    if (!attr) return;

    attr->start_index = startIndex;
    attr->end_index = endIndex;
    pango_attr_list_insert(attrList, attr);
}

void TextBlock::_applySpanCascadingSheet(SpanStyle* spanStyle, int startIndex, int endIndex, PangoAttrList* attrList)
{
    _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_family_new(spanStyle->fontFamily_get()->value().c_str()));
    _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_style_new(static_cast<PangoStyle>(spanStyle->fontStyle_get()->value())));
    _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_variant_new(static_cast<PangoVariant>(spanStyle->fontVariant_get()->value())));
    _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_stretch_new(static_cast<PangoStretch>(spanStyle->fontStrech_get()->value())));
    _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_weight_new(static_cast<PangoWeight>(spanStyle->fontWeight_get()->value())));
    _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_size_new(static_cast<int>(spanStyle->textSize_get()->value() * PANGO_SCALE)));

    if (spanStyle->foregroundColor_get()->isSet() && spanStyle->foregroundColor_get()->value().A_get() != 0.0)
    {
        _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_foreground_new(
            spanStyle->foregroundColor_get()->value().R16bit_get(),
            spanStyle->foregroundColor_get()->value().G16bit_get(),
            spanStyle->foregroundColor_get()->value().B16bit_get()));

        _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_foreground_alpha_new(spanStyle->foregroundColor_get()->value().A16bit_get()));
    }

    if (spanStyle->backgroundColor_get()->value().A_get() != 0.0)
    {
        _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_background_new(
            spanStyle->backgroundColor_get()->value().R16bit_get(),
            spanStyle->backgroundColor_get()->value().G16bit_get(),
            spanStyle->backgroundColor_get()->value().B16bit_get()));

        _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_background_alpha_new(spanStyle->backgroundColor_get()->value().A16bit_get()));
    }

    if (spanStyle->strikethrough_get()->value())
    {
        _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_strikethrough_new(spanStyle->strikethrough_get()->value()));

        if (spanStyle->backgroundColor_get()->value().A_get() != 0.0)
            _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_strikethrough_color_new(
                spanStyle->strikethroughColor_get()->value().R16bit_get(),
                spanStyle->strikethroughColor_get()->value().G16bit_get(),
                spanStyle->strikethroughColor_get()->value().B16bit_get()));
    }

    if (spanStyle->underline_get()->value() != UnderlineType::None)
    {
        _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_underline_new(static_cast<PangoUnderline>(spanStyle->underline_get()->value())));

        if (spanStyle->underlineColor_get()->value().A_get() != 0.0)
            _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_underline_color_new(
                spanStyle->underlineColor_get()->value().R16bit_get(),
                spanStyle->underlineColor_get()->value().G16bit_get(),
                spanStyle->underlineColor_get()->value().B16bit_get()));
    }

    _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_rise_new(static_cast<int>(spanStyle->characterRise_get()->value() * PANGO_SCALE)));
    _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_gravity_new(static_cast<PangoGravity>(spanStyle->gravity_get()->value())));
    _insertSingleAttribute(attrList, startIndex, endIndex, pango_attr_gravity_hint_new(static_cast<PangoGravityHint>(spanStyle->gravityHint_get()->value())));
}

void TextBlock::_applyParagraphAndTextBlockCascadingSheet(ParagraphStyle* paragraphStyle, TextBlockStyle* textBlockStyle, PangoLayoutWrapper* pangoLayoutWrapper)
{
    pangoLayoutWrapper->fillBrush = paragraphStyle->fillBrush_get()->value();

    pango_layout_set_alignment(pangoLayoutWrapper->layout, convertParagraphAligmentToPangoAligment(paragraphStyle->paragraphAligment_get()->value()));
    pango_layout_set_justify(pangoLayoutWrapper->layout, convertParagraphAlignmentToJustification(paragraphStyle->paragraphAligment_get()->value()));
    pango_layout_set_indent(pangoLayoutWrapper->layout, static_cast<int>(paragraphStyle->firstLineIndent_get()->value() * PANGO_SCALE));

    if (textBlockStyle->width_get()->value() != -1)
    {
        pango_layout_set_width(pangoLayoutWrapper->layout, 
            static_cast<int>((textBlockStyle->width_get()->value().getValueRelativeTo(parent()->getAbsoluteSizeVector().X) - 
             paragraphStyle->leftIndent_get()->value() - paragraphStyle->rightIndent_get()->value())* PANGO_SCALE));
    }

    pango_layout_set_spacing(pangoLayoutWrapper->layout, static_cast<int>(paragraphStyle->lineSpacing_get()->value() * PANGO_SCALE));
}

PangoLayoutWrapper* TextBlock::_createPangoWrapperLayoutFromParagraph(Paragraph* paragraph, TextBlockStyle* textBlockStyle)
{
    if (!uiContext()) return nullptr;

    cairo_t* l_cairoContext = uiContext()->getCairoContext();

    if (!l_cairoContext) return nullptr;

    PangoLayoutWrapper* l_pangoLayoutWrapper = new PangoLayoutWrapper();

    l_pangoLayoutWrapper->layout = pango_cairo_create_layout(l_cairoContext);
    l_pangoLayoutWrapper->paragraph = paragraph;

    l_pangoLayoutWrapper->selectionAttribute = pango_attr_background_new(_highlightColor.R16bit_get(), _highlightColor.G16bit_get(), _highlightColor.B16bit_get());
    l_pangoLayoutWrapper->selectionAttribute->start_index = 0;
    l_pangoLayoutWrapper->selectionAttribute->end_index = 0;

    ParagraphStyle l_paragraphStyle;
    if (this->paragraphStyle_get())      l_paragraphStyle.cascadeFrom(this->paragraphStyle_get().get());
    if (paragraph->paragraphStyle_get()) l_paragraphStyle.cascadeFrom(paragraph->paragraphStyle_get().get());

    SpanStyle l_paragraphSpanStyle;
    if (this->spanStyle_get())      l_paragraphSpanStyle.cascadeFrom(this->spanStyle_get().get());
    if (paragraph->spanStyle_get()) l_paragraphSpanStyle.cascadeFrom(paragraph->spanStyle_get().get());

    PangoAttrList* l_attrList = pango_attr_list_new();

    string l_paragraphString;

    for (auto span : paragraph->getSpans())
    {
        if (span->getText().length() != 0)
        {
            l_paragraphString += span->getText();

            SpanStyle l_spanStyle = l_paragraphSpanStyle;
            if (span->spanStyle_get()) l_spanStyle.cascadeFrom(span->spanStyle_get().get());

            _applySpanCascadingSheet(&l_spanStyle, span->_startIndex, span->_endIndex, l_attrList);
        }
    }

    if (l_paragraphString.empty())
        _applySpanCascadingSheet(&l_paragraphSpanStyle, 0, 1, l_attrList);

    _applyParagraphAndTextBlockCascadingSheet(&l_paragraphStyle, textBlockStyle, l_pangoLayoutWrapper);

    if (paragraph != _paragraphs.back())
        l_paragraphString += " ";

    pango_layout_set_text(l_pangoLayoutWrapper->layout, l_paragraphString.c_str(), -1);
    pango_attr_list_insert(l_attrList, l_pangoLayoutWrapper->selectionAttribute);
    pango_layout_set_attributes(l_pangoLayoutWrapper->layout, l_attrList);
    pango_attr_list_unref(l_attrList);

    l_pangoLayoutWrapper->spaceBefore = l_paragraphStyle.spaceBefore_get()->value();

    int l_height, l_width;
    pango_layout_get_size(l_pangoLayoutWrapper->layout, &l_width, &l_height);

    double l_dblWidth  = static_cast<double>(l_width)  / PANGO_SCALE;
    double l_dblHeight = static_cast<double>(l_height) / PANGO_SCALE;

    l_pangoLayoutWrapper->size.X = textBlockStyle->width_get()->value().getValueRelativeTo(parent()->getAbsoluteSizeVector().X);
    l_pangoLayoutWrapper->size.Y = l_dblHeight;

    l_pangoLayoutWrapper->leftIndent = l_paragraphStyle.leftIndent_get()->value();
    l_pangoLayoutWrapper->spaceAfter = l_paragraphStyle.spaceAfter_get()->value();

    return l_pangoLayoutWrapper;
}

void TextBlock::_updateParagraphOffset(Paragraph* paragraph, double & l_top)
{
    paragraph->_textualLayout->offset.X = paragraph->_textualLayout->leftIndent;

    l_top += paragraph->_textualLayout->spaceBefore;
    paragraph->_textualLayout->offset.Y = l_top;
    l_top += paragraph->_textualLayout->size.Y;
    l_top += paragraph->_textualLayout->spaceAfter;
    paragraph->_extent = paragraph->_textualLayout->getExtent();

    for (auto span : paragraph->getSpans())
    {
        span->_clearRegion();

        Rect l_currentRect;

        for (int i = span->_startIndex; i < span->_endIndex; i++)
        {
            PangoRectangle l_pangoRect;
            pango_layout_index_to_pos(paragraph->_textualLayout->layout, i, &l_pangoRect);
            Rect l_letterRect(l_pangoRect.x / PANGO_SCALE,
                l_pangoRect.y / PANGO_SCALE,
                (l_pangoRect.x + l_pangoRect.width) / PANGO_SCALE,
                (l_pangoRect.y + l_pangoRect.height) / PANGO_SCALE);

            l_letterRect >> paragraph->_textualLayout->offset;

            if (l_currentRect.sizeVector() == Vector(0, 0))
                l_currentRect = l_letterRect;
            else if (l_currentRect.lowVector.Y == l_letterRect.lowVector.Y &&
                l_currentRect.highVector.Y == l_letterRect.highVector.Y)
            {
                l_currentRect.highVector.X = l_letterRect.highVector.X;
            }
            else
            {
                span->_addRectToRegion(l_currentRect);
                l_currentRect = l_letterRect;
            }

            if (i == span->_endIndex - 1) span->_addRectToRegion(l_currentRect);
        }
    }
}

void TextBlock::_updateGeometry()
{
    if (_geometryUpdateExecuted) return;

    if (!uiContext()) return;

    Vector l_size;
    double l_top = 0;


    TextBlockStyle l_textBlockStyle;
    if (this->textBlockStyle_get()) l_textBlockStyle.cascadeFrom(this->textBlockStyle_get().get());

    l_size.X = l_textBlockStyle.width_get()->value().getValueRelativeTo(parent()->getAbsoluteSizeVector().X);

    for (auto paragraph : _paragraphs)
    {
        if (!paragraph->_textualLayout ||
            (paragraph->_textualLayout && paragraph->_stale))
        {
            delete paragraph->_textualLayout;
            paragraph->_textualLayout = _createPangoWrapperLayoutFromParagraph(paragraph, &l_textBlockStyle);
        }
    }

    for (auto paragraph : _paragraphs)
        _updateParagraphOffset(paragraph, l_top);

    if (l_textBlockStyle.height_get()->value() == -1)
        l_size.Y = l_top;
    else
        l_size.Y = l_textBlockStyle.height_get()->value().getValueRelativeTo(parent()->getAbsoluteSizeVector().Y);

    _size = l_size;

    if (_paragraphs.empty())
    {
        l_size.Y = l_textBlockStyle.height_get()->value().getValueRelativeTo(parent()->getAbsoluteSizeVector().Y);
        _size = l_size;
    }

    _size = l_size;

    _geometryUpdateExecuted = true;
}

#pragma endregion

#pragma endregion
