#pragma once

#include "dllexport.h"

#include "VisualPrimitive.h"
#include "Paragraph.h"
#include "TextBlockStylable.h"
#include "PangoLayoutWrapper.h"


/*
==============================
Overview of Eleusis::TextBlock
==============================

Conceptual Model of TextBlock
=============================

TextBlock conisists of Paragraphs; Paragraph consists of Spans; Span contians a character string.
This way a TextBlock, Paragraphs and Spans build a tree with the TextBlock as the root.
This tree represents a conceptual model of a TextBlock. 

Eleusis use Pango for general-purpose text rendering. 
Pango is a multiplatform text-rendering library from GTK family. 
For more info about Pango, please view: http://www.pango.org/

In order to utilize Pango as a renderer, Eleusis needs to translate TextBlock-Paragraph-Span model (TPS model)
to Pango model (P model).

The cleanest and simplest way is to use functional approach: at the moment when geometry update needs to happen
(view Eleusis::VisualPrimitive::_updateGeometry()) - which is initiated by rendering timer - full TPS tree
is translated to new collection of PangoLayouts which can be passed to Pango and Cairo for rendering. This
translation is stateless, meaning that no PangoLayouts are persisted for following renderings, but are built from
scretch. Naturally, this translation (call to _updateGeometry()) will happen only when a change in TPS
model is noticed / registered; otherwise, Pango will use existing P model for redrawing the surface.

Although the cleanest, functional approach is inefficient. If just single letter changes color in one of
200 paragraphs of TextBlock, whole P model needs to be rebuild. As single Paragraph in TPS model corresponds 
to single PangoLayout to P model (1-1 mapping), P model is persisted during TPS model changes, and only PangoLayouts
which correspond to changed Paragraphs are build from beggining. Paragraph to PangoLayout translation still
has functional flavor because of complexities of PangoLayout and coresponding structures.

Ideally, Paragraphs and Spans should not have any knowledge of Pango existance; they should just represent a pure model
and should not contain TextBlock-specific or session-specific caches. However, in order to prevent proliferation of 
number of types, Paragraphs and Spans contains session-specific caches. Thus, a Paragraph holds a pointer to 
an instance of PangoLayoutWrapper which is a very transparent wrapper around PangoLayout. This way TPC and P model
unfortunatelly fuse.

Lifecycle of PangoLayoutWrapper
-------------------------------

(1) PangoLayoutWrapper is nullptr when Paragraph is created.
(2) If Paragraph does not have parent TextBlock, PangoLayoutWrapper must be nullptr.
(3) If Paragraph have parent TextBlock, PangoLayoutWrapper must always be a valid instance representing current Paragraph.
(4) If Paragraph is changed so that its current PangoLayoutWrapper is invalid, current instance of PangoLayoutWrapper
    must be destroyed and new one should be instanciated and assigned to Paragraph.
(5) If Paragraph is removed from TextBlock, its instance of PangoLayoutWrapper must be destroyed.
(6) If Paragraph is destroyed, its instance of PangoLayoutWrapper must be destroyed.

Implementation of Lifecycle
---------------------------

TextBlock::_updateGeometry() iterates through all Paragraphs; if it decides that:
    - PangoLayoutWrapper is nullptr, or
    - Paragraph is changed
it will destroy existing instance of PangoLayoutWrapper, intantiate new PangoLayoutWrapper and assign it to
Paragraph. This way all Paragraphs in TextBlock are assigned. 
PangoLayoutWrapper can be created and assigned to Paragraph only in TextBlock::_updateGeometry().
If Paragraph already have assigned ParagraphLayoutWrapper, then it is destroyed.

Character Indexing
==================

TextBlock, Paragraph and Span have getText() function which returns std::string.
Span::getText() returns actual character string that Span contains.
Paragraph::getText() calls Span::getText() for all Spans it contains; concatinates these strings; and returns the result.
TextBlock::getText() calls Paragraph::getText() for all paragraphs it contains; appens new-line character '\n' to every except last
paragraph string; concatinates these strings; and returns the result.

Paragraph::getText() and Span::getText() should never return character string which contains new-line character(s).
Span's character string should never contain new-line character.
If Span's text is set to string which contians new-line characters, new-line characters should be ignored (removed from the string).

Character Indices
-----------------

We can talk about ***index*** of a character inside TextBlock, Paragraph or Span.
For TextBlock and Span, index is zero-based position of a character in the string returned by appropriate getText() function.
For Paragraph, index is zero-based position of a character in the string returned by Paragraph::getText() function with appended new-line character.
Each character has three separate indicies: index within Span, Paragraph and TextBlock.

Character Ranges
----------------

Character range is a zero-base substring [a, b) where a and b represent character indicies within a string;
character with index a is included in a range while character with index b is not.

Each Span has character range which describes its position within parent Paragraph.
Each Paragraph has character range which describes its position within parent TextBlock.
If a Paragraph is not the last Paragraph in a TextBlock, its character range SHOULD inclde hypotethical new-line character.
It means that Paragraphs's character range has one more character then in a string returned by Paragraph::getText().

Thus, TextBlock can be represented as a collection of character ranges where each character range represents a single Paragraph:

[0, p1) [p1, p2) [p2, p3) ... [p&n-1, pn).

Every last character in these character ranges except last is a new-line character.
Note that there is pn characters in this text block.

Paragraph can be represented as a collection of character ranges where each character range represents a Span:

[0, s1) [s1, s2) [s2, s3) ... [s&n-1, s&n) [s&n, s&n + 1)

where range [s&n, s&n + 1) represents a new-line character.
There is s&n + 1 character in this paragraph, but getText() function will return s&n characters as it ommits new-line.
Note: New-line character is an orphan - it belongs to Paragraph, but there is no parent Span.

Index Conversions
-----------------

Let we are given a character with span-index 'is'.
Character is located in span [s1, s2) which is located in paragraph [p1, p2).
What are the the indicies of this character within its Paragraph and TextBlock ('ip' and 'it')?

ip = is + s1; 
it = ip + p1 = is + s1 + p1;

is = ip - s1 - p1;
ip = it - p1;
*/

namespace Eleusis
{
    class ELEUSIS_API TextBlock :
        public VisualPrimitive, 
        public SpanStylable,
        public ParagraphStylable,
        public TextBlockStylable
    {
    public:
        TextBlock();
        virtual ~TextBlock();

        void insertParagraph(Paragraph* paragraph);
        void insertParagraphAfter(Paragraph* paragraphToInsert, Paragraph* referentParagraph);
        void insertParagraphBefore(Paragraph* paragraphToInsert, Paragraph* referentParagraph);
        void removeParagraph(Paragraph* paragraph);
        const std::list<Paragraph*> & getParagraphs() { return _paragraphs; };

        void setText(std::string text);
        std::string getText();
        void addText(std::string text);
        void insertText(std::string text, int startIndex = -1);
        void insertNewLine(int index);
        
        Rect getCharacterExtent(int index);
        Rect getCharacterExtent(Vector coordinates);
        Rect getCarretExtentForCharacter(int index);

        int getCharacterIndex(Vector coordinates);

        int numberOfShownCharacters();
        int numberOfShownUnknownCharacters();
        int numberOfUTF8Bytes() { return _numberOfUTF8Bytes; };
        int numberOfShownLines();

        virtual Rect getExtent();
        virtual Rect getFullExtent();

        virtual bool contains(Vector vector) { return getExtent().contains(vector); };
        virtual bool contains(double x, double y) { return getExtent().contains({ x, y }); };

    protected:
        int _moveLeft(int index);
        int _moveRight(int index);
        int _moveUp(int currentAbsoluteIndex, int desiredIndexWithinLine);
        int _moveDown(int currentAbsoluteIndex, int desiredIndexWithinLine);
        int _positionWithinLine(int currentAbsoluteIndex);

        void _mergeParagraphs(Paragraph* target, Paragraph* source);
        void _splitParagraph(Paragraph* paragraph, int splitIndex);

        Paragraph* _getParagraphWithCharacter(int characterIndex);
        Span* _getSpanWithCharacter(int characterIndex, Paragraph* paragraph);

        void _deleteRange   (int startIndex, int endIndex);
        void _highlightRange(int startIndex, int endIndex);

        void      _setHighlightColor(RgbaColor highlightColor) { _highlightColor = highlightColor; };
        RgbaColor _getHighlightColor()                         { return _highlightColor; };

    private:
        std::list<Paragraph*> _paragraphs;

        Vector _size;
        int _numberOfUTF8Bytes = 0;

        void _initializeEventHandlers();
        Handler<Paragraph*, ParagraphUpdatedEventArgs*> _paragraphs_updatedHandler;

        Span*      _currentMouseMoveSpan      = nullptr;
        Paragraph* _currentMouseMoveParagraph = nullptr;

        void _routeMouseClickEvent      (Node* sender, MouseEventArgs* e);
        void _routeMouseUpEvent         (Node* sender, MouseEventArgs* e);
        void _routeMouseDownEvent       (Node* sender, MouseEventArgs* e);
        void _routeMouseDoubleClickEvent(Node* sender, MouseEventArgs* e);
        void _routeMouseMoveEvent       (Node* sender, MouseEventArgs* e);
        void _routeMouseScrollEvent     (Node* sender, MouseScrollEventArgs* e);
        void _routeMouseLeaveEvent      (Node* sender, MouseEventArgs* e);

        bool _enumerationSuspended = false;

        void _enumarateParagraphs();
        void _insertParagraphAround(Paragraph* paragraphToInsert, Paragraph* referentParagraph, bool after);

        virtual void _render(Region* region);
        virtual void _applyAbsoluteOffset() { };
        virtual void _updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector);
        virtual void _updateGeometry();

        void _doCairoDrawing(cairo_t* cairoContext, Region* region);

        void _insertSingleAttribute(PangoAttrList* attrList, int startIndex, int endIndex, PangoAttribute* attr);
        void _applySpanCascadingSheet(SpanStyle* spanCS, int startIndex, int endIndex, PangoAttrList* attrList);
        void _applyParagraphAndTextBlockCascadingSheet(ParagraphStyle* paragraphCS, TextBlockStyle* textBlockStyle, PangoLayoutWrapper* layout);
        PangoLayoutWrapper* _createPangoWrapperLayoutFromParagraph(Paragraph* paragraph, TextBlockStyle* textBlockStyle);
        void _updateParagraphOffset(Paragraph* paragraph, double & currentTop);

        enum class CharacterRoleInParagraph
        {
            Regular,
            LastInParagraph,
            FirstInParagraph
        };

        struct CharacterRecord
        {
            int index = -1;
            CharacterRoleInParagraph role = CharacterRoleInParagraph::Regular;
            Paragraph* paragraph = nullptr;

            int paragraphRelativeIndex() 
            { 
                return index - paragraph->_startIndex;
            }
        };

        struct CharacterRange
        {
            CharacterRecord start;
            CharacterRecord end;
        };
        
        CharacterRange _getCharacterRange(int startIndex, int endIndex);
        bool _sanitizeRange(int* startIndex, int* endIndex);
        CharacterRecord _calculateCharacterRecord(int characterIndex);

        Paragraph* _getNextParagraph(Paragraph* paragraph);
        Paragraph* _getPreviousParagraph(Paragraph* previous);

        RgbaColor _highlightColor = Colors::LightBlue;

    };
}
