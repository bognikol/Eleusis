#include "SelectEdit.h"

#include <sstream>

using namespace Eleusis;
using namespace std;

SelectEdit::SelectEdit()
{
    enableFocus();

    _caret = new Caret();
    insertChild(_caret);

    mouseDown  += makeHandler(&SelectEdit::_mouseDown);
    mouseLeave += makeHandler(&SelectEdit::_mouseLeave);
    mouseMove  += makeHandler(&SelectEdit::_mouseMove);
    keyDown    += makeHandler(&SelectEdit::_keyDown);
    gotFocus   += makeHandler(&SelectEdit::_gotFocus);
    lostFocus  += makeHandler(&SelectEdit::_lostFocus);

    _mouseUpApplicationHandler = makeHandler(&SelectEdit::_mouseUp);
    Application::mouseUp += _mouseUpApplicationHandler;

    _renderingCycleExecutedHandler = makeHandler(&SelectEdit::_renderingCycleExecuted);
    Application::renderingCycleExecuted += _renderingCycleExecutedHandler;
};

SelectEdit::~SelectEdit()
{
    Application::renderingCycleExecuted -= _renderingCycleExecutedHandler;
    Application::mouseUp -= _mouseUpApplicationHandler;
}

void SelectEdit::setCaretLocation(int index)
{
    if (index < 0) index = 0;
    if (index > numberOfUTF8Bytes()) index = numberOfUTF8Bytes();

    _caretLocation = index;
    _caretLocationWithinLine = _positionWithinLine(_caretLocation);

    _caret->resetTimer();
}; 

void SelectEdit::moveCaretLeft()
{
    setCaretLocation(_moveLeft(_caretLocation));

    _caret->resetTimer();
}

void SelectEdit::moveCaretRight()
{
    setCaretLocation(_moveRight(_caretLocation));

    _caret->resetTimer();
}   

void SelectEdit::moveCaretUp()
{
    _caretLocation = _moveUp(_caretLocation, _caretLocationWithinLine);

    _caret->resetTimer();
}

void SelectEdit::moveCaretDown()
{
    _caretLocation = _moveDown(_caretLocation, _caretLocationWithinLine);

    _caret->resetTimer();
}

void SelectEdit::deleteCharacterLeft()
{
    if (_caretLocation == 0) return;

    int l_left = _moveLeft(_caretLocation);

    _deleteRange(l_left, _caretLocation);
    setCaretLocation(l_left);
    _caret->resetTimer();
}

void SelectEdit::deleteCharacterRight()
{
    _deleteRange(_caretLocation, _moveRight(_caretLocation));
    _caret->resetTimer();
}

void SelectEdit::deleteSelection()
{
    _deleteRange(_selectionStart, _selectionEnd);

    int l_newCaretLocation = _selectionStart;
    if (_selectionEnd < l_newCaretLocation) l_newCaretLocation = _selectionEnd;

    setCaretLocation(l_newCaretLocation);
    setSelection(-1, -1);
}

void SelectEdit::updateSelectionText(std::string text)
{
    int l_selectionRange = _selectionStart;

    deleteSelection();

    insertText(text, l_selectionRange);

    setCaretLocation(l_selectionRange + text.size());
}

void SelectEdit::setSelection(int startIndex, int endIndex)
{
    if (startIndex < -1 || startIndex > numberOfUTF8Bytes() ||
        endIndex   < -1 || endIndex   > numberOfUTF8Bytes())
        return;

    if (startIndex == _selectionStart && 
        endIndex   == _selectionEnd)
        return;

    _selectionStart = startIndex;
    _selectionEnd   = endIndex;
    _highlightRange(_selectionStart, _selectionEnd);
    raiseEvent selectionChanged(this, nullptr);
}

void SelectEdit::clearSelection()
{
    setSelection(-1, -1);
}

std::string SelectEdit::getSelectionText()
{
    if (_selectionStart < 0) return "";
    return getText().substr(_selectionStart, _selectionEnd - _selectionStart);
};

void SelectEdit::selectionColor_set(RgbaColor selectionColor)
{
    _setHighlightColor(selectionColor);
}

RgbaColor SelectEdit::selectionColor_get()
{
    return _getHighlightColor();
}

void SelectEdit::caretColor_set(RgbaColor selectionColor)
{
    _caret->setFillColor(selectionColor);
}

RgbaColor SelectEdit::caretColor_get()
{
    return _caret->getFillColor();
}


#pragma region EXTERNAL EVENT HANDLING

void SelectEdit::_mouseDown(Node* sender, MouseEventArgs* e)
{
    if (e->Button != MouseButton::Left)
        return;

    if (getParagraphs().empty())
    {
        Paragraph* l_paragraph = new Paragraph();
        l_paragraph->insertSpan(new Span());
        insertParagraph(l_paragraph);
        setCaretLocation(0);
        return;
    }

    int l_characterIndex = getCharacterIndex(Vector(e->X, e->Y));
    
    if (l_characterIndex == -1)
    {
        setCaretLocation(0);
        return;

    }

    _leftMouseButtonDown = true;

    _mouseDownCharacterIndex = l_characterIndex;

    setCaretLocation(_mouseDownCharacterIndex);

    if (!_selecting)
        setSelection(-1, -1);
}

void SelectEdit::_mouseUp(void* sender, MouseEventArgs* e)
{
    if (e->Button != MouseButton::Left)
        return;

    _leftMouseButtonDown = false;

    if (_selecting)
    {
        _selecting = false;
        setCaretLocation(_selectionEnd);
        _caret->show();
        raiseEvent selectingEnded(this, nullptr);
    }
}    

void SelectEdit::_mouseMove(Node* sender, MouseEventArgs* e)
{
    if (Mouse::getCursor() != MouseCursor::IBeam)
        Mouse::setCursor(MouseCursor::IBeam);

    if (_leftMouseButtonDown && !_selecting)
    {
        _selecting = true;
        _caret->hide();
        _selectionStart = _mouseDownCharacterIndex;
        _selectionEnd   = _mouseDownCharacterIndex;
        raiseEvent selectingStarted(this, nullptr);
    }

    if (_selecting)
    {
        int l_currentEnd = getCharacterIndex(Vector(e->X, e->Y));

        if (l_currentEnd == -1)
            return;

        if (l_currentEnd >= _selectionStart)
            l_currentEnd++;

        setSelection(_selectionStart, l_currentEnd);
    }
}

void SelectEdit::_mouseLeave(Node* sender, MouseEventArgs* e)
{
    if (!_selecting)
        Mouse::setCursor(MouseCursor::Arrow);
}

void SelectEdit::_keyDown(Node* sender, KeyboardEventArgs* e)
{
    switch (e->VirtualKeyCode)
    {
        case VirtualKey::Delete:
        {
            if (_selectionStart == _selectionEnd)
                deleteCharacterRight();
            else
                deleteSelection();
        }
        break;
        case VirtualKey::Backspace:
        {
            if (_selectionStart == _selectionEnd)
                deleteCharacterLeft();
            else
                deleteSelection();
        }
        break;
        case VirtualKey::Return:
        {
            if (_singleLineMode) break;
            insertNewLine(_caretLocation);
            _caretLocation = _moveRight(_caretLocation);
        }
        break;
        case VirtualKey::Left:
            moveCaretLeft();
            break;
        case VirtualKey::Right:
            moveCaretRight();
            break;
        case VirtualKey::Up:
            moveCaretUp();
            break;
        case VirtualKey::Down:
            moveCaretDown();
            break;
        default:
        {
            if (e->String.empty()) break;

            if ((Application::currentSystem() == System::MacOS && e->CommandDown) ||
                (Application::currentSystem() == System::Win32 && e->ControlDown))
            {
                if (e->String == "x" || e->String == "X")
                {
                    Application::Clipboard::putUnicodeText(getSelectionText());
                    deleteSelection();
                }
                else if (e->String == "c" || e->String == "C")
                {
                    Application::Clipboard::putUnicodeText(getSelectionText());
                }
                else if (e->String == "v" || e->String == "V")
                {
                    insertText(Application::Clipboard::getUnicodeText(), _caretLocation);
                    setCaretLocation(_caretLocation + Application::Clipboard::getUnicodeText().size());
                }
                break;
            }
            
            _deleteRange(_selectionStart, _selectionEnd);

            insertText(e->String, _caretLocation);

            if (_selectionStart != -1 && _selectionEnd != -1)
                setCaretLocation(_selectionStart + e->String.size());
            else
                setCaretLocation(_caretLocation + e->String.size());

            setSelection(-1, -1);
        }
    }
}

void SelectEdit::_gotFocus(Node* sender, EventArgs* e)
{
    _caret->show();
}

void SelectEdit::_lostFocus(Node* sender, EventArgs* e)
{
    _caret->hide();
}

void SelectEdit::_renderingCycleExecuted(void* sender, EventArgs* e)
{
    if (_caretLocation == _actualCaretLocation) return;

    Rect l_carret = getCarretExtentForCharacter(_caretLocation);

    _caret->LayoutGuest.Classic.topLeft(l_carret.lowVector.Y, l_carret.lowVector.X);
    _caret->setWidthAndHeight(1, l_carret.sizeVector().Y);

    _actualCaretLocation = _caretLocation;
    caretChanged(this, nullptr);
}

void SelectEdit::_deleteRange(int startIndex, int endIndex)
{
    TextBlock::_deleteRange(startIndex, endIndex);

    if (getParagraphs().empty())
    {
        Paragraph* l_paragraph = new Paragraph();
        l_paragraph->insertSpan(new Span());
        insertParagraph(l_paragraph);
        setCaretLocation(0);
        return;
    }
}

#pragma endregion
