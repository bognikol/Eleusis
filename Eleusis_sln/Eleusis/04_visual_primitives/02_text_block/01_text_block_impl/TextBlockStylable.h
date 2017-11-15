#pragma once

#include "dllexport.h"

#include "TextualStyles.h"
#include "01_vectoring/Length.h"

namespace Eleusis
{
    class ELEUSIS_API TextBlockStylable
    {
    protected:
        Handler<TextBlockStyle*, EventArgs*>  _textBlockStyle_changedHandler;

    private:
        std::shared_ptr<TextBlockStyle> _textBlockStyle;
        bool _isSpanStyleShared = false;

        template <typename Type>
        void _setProperty(Type value,
            void(TextBlockStyle::* setter)(Type),
            const ReadOnlyCascadingProperty<Type>*(TextBlockStyle::* getter)(void))
        {
            if (_textBlockStyle)
            {
                if ((_textBlockStyle.get()->*getter)()->value() == value &&
                    (_textBlockStyle.get()->*getter)()->isSet() == true) return;
                if (_isSpanStyleShared)
                {
                    TextBlockStyle* l_textBlockStyle = new TextBlockStyle();
                    l_textBlockStyle->cascadeFrom(_textBlockStyle.get());

                    _textBlockStyle->changed -= _textBlockStyle_changedHandler;
                    _textBlockStyle = std::shared_ptr<TextBlockStyle>(l_textBlockStyle);
                    _textBlockStyle->changed += _textBlockStyle_changedHandler;
                }
            }
            else
            {
                _textBlockStyle = std::shared_ptr<TextBlockStyle>(new TextBlockStyle());
                _textBlockStyle->changed += _textBlockStyle_changedHandler;
            }

            _isSpanStyleShared = false;

            (_textBlockStyle.get()->*setter)(value);

            // textBlockUpdated event will be raised automatically from _spanStyle_changedHandler
        }

        template <typename Type>
        const ReadOnlyCascadingProperty<Type>* _getProperty
        (const ReadOnlyCascadingProperty<Type>*(TextBlockStyle::* getter)(void)) const
        {
            if (!_textBlockStyle) return nullptr;
            return (_textBlockStyle.get()->*getter)();
        }

    public:

        void textBlockStyle_set(std::shared_ptr<TextBlockStyle> textBlockStyle)
        {

            if (_textBlockStyle == textBlockStyle) return;

            if (_textBlockStyle)
                _textBlockStyle->changed -= _textBlockStyle_changedHandler;

            _textBlockStyle = textBlockStyle;

            if (_textBlockStyle)
                _textBlockStyle->changed += _textBlockStyle_changedHandler;

            _isSpanStyleShared = true;

            _textBlockStyle_changedHandler(_textBlockStyle.get(), nullptr);

        }


        std::shared_ptr<TextBlockStyle> textBlockStyle_get() { return _textBlockStyle; };

        // setters and getters

        void width_set(Length width) { _setProperty<Length>(width, &TextBlockStyle::width_set, &TextBlockStyle::width_get); };
        const ReadOnlyCascadingProperty<Length>* width_get() { return _getProperty<Length>(&TextBlockStyle::width_get); };

        void height_set(Length height) { _setProperty<Length>(height, &TextBlockStyle::height_set, &TextBlockStyle::height_get); };
        const ReadOnlyCascadingProperty<Length>* height_get() { return _getProperty<Length>(&TextBlockStyle::height_get); };

        void ellipsize_set(EllipsizeType ellipsizeType) { _setProperty<EllipsizeType>(ellipsizeType, &TextBlockStyle::ellipsize_set, &TextBlockStyle::ellipsize_get); };
        const ReadOnlyCascadingProperty<EllipsizeType>* ellipsize_get() { return _getProperty<EllipsizeType>(&TextBlockStyle::ellipsize_get); };
    };
}