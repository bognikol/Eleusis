#pragma once

#include "dllexport.h"

#include <string>
#include <memory>
#include <list>

#include "SpanStylable.h"
#include "Window.h"

namespace Eleusis
{
    class SpanUpdatedEventArgs :
        public EventArgs
    {
    public:
        bool stringSizeChanged = false;
    };

    class ELEUSIS_API Span :
        public SpanStylable
    {
        friend class TextBlock;
        friend class Paragraph;

    public:
        Span();
        Span(std::string text);
        virtual ~Span() { };

        void        setText(std::string text);
        std::string getText() { return _text; };
        void        addText(std::string text);
        
        bool isEmpty() { return _text.empty(); }

        Event<Span*, SpanUpdatedEventArgs*> spanUpdated;

        std::list<Rect> & getRects() { return _region.getRects(); }

        bool contains(Vector v);

        Event<Span*, MouseEventArgs*>        mouseClick;
        Event<Span*, MouseEventArgs*>        mouseDoubleClick;
        Event<Span*, MouseEventArgs*>        mouseDown;
        Event<Span*, MouseEventArgs*>        mouseUp;
        Event<Span*, MouseScrollEventArgs*>  mouseScroll;
        Event<Span*, MouseEventArgs*>        mouseMove;
        Event<Span*, MouseEventArgs*>        mouseEnter;
        Event<Span*, MouseEventArgs*>        mouseLeave;

    private:
        void _initializeEventHandlers();

        std::string _text;
        Region _region;

        // Session-specific members

        int _startIndex = 0;
        int _endIndex = 0;

        bool _deleteRange(int startIndex, int endIndex);

        void _addRectToRegion(Rect rect);
        void _clearRegion();
    };
}

