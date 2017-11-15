#pragma once

#include "dllexport.h"

#include "Span.h"
#include "ParagraphStylable.h"
#include "PangoLayoutWrapper.h"

namespace Eleusis
{
    class ParagraphUpdatedEventArgs :
        public EventArgs
    {
    public:
        bool stringSizeChanged = false;
        Span* spanRemoved = nullptr;
    };

    class ELEUSIS_API Paragraph :
        public SpanStylable,
        public ParagraphStylable
    {
        friend class TextBlock;

    public:
        Paragraph();
        Paragraph(std::string text);
        virtual ~Paragraph();

        void insertSpan(Span* span);
        void insertSpanAfter (Span* spanToInsert, Span* referentSpan);
        void insertSpanBefore(Span* spanToInsert, Span* referentSpan);
        void removeSpan(Span* span);

        const std::list<Span*> & getSpans() { return _spans; };

        void        setText(std::string text);
        std::string getText();
        void        addText(std::string text);

        Rect getExtent() { return _extent; }

        Event<Paragraph*, ParagraphUpdatedEventArgs*> paragraphUpdated;

        Event<Paragraph*, MouseEventArgs*>        mouseClick;
        Event<Paragraph*, MouseEventArgs*>        mouseDoubleClick;
        Event<Paragraph*, MouseEventArgs*>        mouseDown;
        Event<Paragraph*, MouseEventArgs*>        mouseUp;
        Event<Paragraph*, MouseScrollEventArgs*>  mouseScroll;
        Event<Paragraph*, MouseEventArgs*>        mouseMove;
        Event<Paragraph*, MouseEventArgs*>        mouseEnter;
        Event<Paragraph*, MouseEventArgs*>        mouseLeave;

    private:
        void _initializeEventHandlers();
        void _insertSpanAround(Span* spanToInsert, Span* referentSpan, bool after);

        Handler<Span*, SpanUpdatedEventArgs*> _spans_updatedHandler;

        std::list<Span*> _spans;
        Rect _extent;

        bool _deleteRange(int startIndex, int endIndex);
        Span* _splitSpan(Span* span, int splitIndex);

        // Following fields do not represent state of Paragraph.
        // Paragraph is used as an easy place to cache data which refers to Paragraph.

        PangoLayoutWrapper* _textualLayout = nullptr;

        bool _stale = true;

        int _startIndex = 0;
        int _endIndex   = 0;

        int _numberOfUTF8Characters() { return _endIndex - _startIndex; };
    };
}