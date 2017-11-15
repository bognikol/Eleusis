#pragma once

#include "TextBlock.h"
#include "Application.h"
#include "Caret.h"

/*

***DEPRICATED***

Overview of Eleusis::SelectEdit
-------------------------------

SelectEdit is a derivate of TextBlock with augumented functionality to respond
to mouse and/or keyboard events and change text and/or formating of base TextBlock.

To achieve editing capability, it is neccessary to introduce constructs which define
postion and scope of editing within TextBlock's text range. These constructs are:

    (1) Caret - single insertion point within SelectEdit; its definition includes 
        containing Paragraph and Span and index within the Span. Such definition is
        needed in order to fully specify in which paragraph and span text will be
        inserted.
    (2) Selection - range of characters within TextBlock. Selection is defined as a
        character range within the TextBlock. As opposed to caret, selection does not
        differentiate between Paragraphs and Spans included in Selection.

Specifying Caret and Selection
------------------------------

Caret is indexed using 0-based indexing of spaces between characters within a Span.
Following example illustrates it:

Character Indexing      0   1   2   3
                        T   E   X   T
Caret Indexing        0   1   2   3   4

Valid caret indices range from 0 to number of character in the Span, including.

Selection is indexed as a character range (view TextBlock prologe) - zero-base 
substring with first cahracter included and last excluded, for example [a, b).

Valid Caret and Selection States
--------------------------------

Following pseudo code represents a sketch for storing Caret and Selection objects.

STRUCT Selection
    INT SelectionStart
    INT SelectionEnd
END STRUCT

STRUCT Caret
    Paragraph* CaretParagraph
    Span* CaretSpan
    INT IndexWithinSpan
END STRUCT

Following convention is introduce which defines valid relationaships between Selection and
Caret objects.

If there is no Caret, CaretParagraph = NULL, CaretSpan = NULL and IndexWithinSpan = -1;
if there is a Caret, then CaretParagraph points to valid Paragraph within the base TextBlock,
CaretSpan points to valid Span within CaretParagraph, and IndexWithinParagraph points to
valid Caret index/position within CaretSpan.
Any other state of Caret object should be treated as invalid.

If there is no Selection, SelectionStart = -1 and SelectionEnd = -1; Caret should not exist.

*** END DEPRICATED ***

*/

namespace Eleusis
{
    class ELEUSIS_API SelectEdit :
        public TextBlock
    {
        bool _singleLineMode = false;

        bool _selecting = false;
        bool _leftMouseButtonDown = false;
     
        int _mouseDownCharacterIndex = -1;

        // Character (selection) range a-b is zero-base substring [a, b)
        // [-1, -1) selection range is default no selection.

        int _selectionStart = -1; 
        int _selectionEnd   = -1;

        int _caretLocation  = -1;
        int _actualCaretLocation = -1;

        Caret* _caret = nullptr;

        int _caretLocationWithinLine = 0;

        Handler<void*, EventArgs*> _renderingCycleExecutedHandler;
        Handler<void*, MouseEventArgs*> _mouseUpApplicationHandler;

        void _mouseDown (Node* sender, MouseEventArgs* e);
        void _mouseLeave(Node* sender, MouseEventArgs* e);
        void _mouseMove (Node* sender, MouseEventArgs* e);
        void _keyDown   (Node* sender, KeyboardEventArgs* e);
        void _gotFocus  (Node* sender, EventArgs* e);
        void _lostFocus (Node* sender, EventArgs* e);
        void _mouseUp   (void* sender, MouseEventArgs* e);
        void _renderingCycleExecuted(void* sender, EventArgs* e);

    public:
        SelectEdit();
        virtual ~SelectEdit();

        Event<SelectEdit*, EventArgs*> selectionChanged;
        Event<SelectEdit*, EventArgs*> selectingStarted;
        Event<SelectEdit*, EventArgs*> selectingEnded;
        Event<SelectEdit*, EventArgs*> caretChanged;

        void setCaretLocation(int index);
        int  getCaretLocation() { return _caretLocation; };

        void moveCaretLeft();
        void moveCaretRight();
        void moveCaretUp();
        void moveCaretDown();

        void deleteCharacterLeft();
        void deleteCharacterRight();

        void deleteSelection();
        void setSelection(int startIndex, int endIndex);
        void clearSelection();
        int getSelectionStart() { return _selectionStart; };
        int getSelectionEnd() { return _selectionEnd; };
        std::string getSelectionText();
        void updateSelectionText(std::string text);

        void selectionColor_set(RgbaColor selectionColor);
        RgbaColor selectionColor_get();

        void caretColor_set(RgbaColor selectionColor);
        RgbaColor caretColor_get();

        void singleLineMode_set(bool mode) { _singleLineMode = mode; }
        bool singleLineMode_get() { return _singleLineMode; }

        void _deleteRange(int startIndex, int endIndex);
    };
}

