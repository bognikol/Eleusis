#pragma once

#include "dllexport.h"

#include "TextualStyles.h"

namespace Eleusis
{
    class ELEUSIS_API SpanStylable
    {
    protected:
        Handler<SpanStyle*, EventArgs*> _spanStyle_changedHandler;

    private:
        std::shared_ptr<SpanStyle> _spanStyle;
        bool _isSpanStyleShared = false;

        template <typename Type>
        void _setProperty(Type value,
            void(SpanStyle::* setter)(Type),
            const ReadOnlyCascadingProperty<Type>*(SpanStyle::* getter)(void))
        {
            if (_spanStyle)
            {
                if ((_spanStyle.get()->*getter)()->value() == value &&
                    (_spanStyle.get()->*getter)()->isSet() == true) return;
                if (_isSpanStyleShared)
                {
                    SpanStyle* l_spanStyle = new SpanStyle();
                    l_spanStyle->cascadeFrom(_spanStyle.get());

                    _spanStyle->changed -= _spanStyle_changedHandler;
                    _spanStyle = std::shared_ptr<SpanStyle>(l_spanStyle);
                    _spanStyle->changed += _spanStyle_changedHandler;
                }
            }
            else
            {
                _spanStyle = std::shared_ptr<SpanStyle>(new SpanStyle());
                _spanStyle->changed += _spanStyle_changedHandler;
            }

            _isSpanStyleShared = false;

            (_spanStyle.get()->*setter)(value);

            // spanUpdated event will be raised automatically from _spanStyle_changedHandler
        }

        template <typename Type>
        const ReadOnlyCascadingProperty<Type>* _getProperty
        (const ReadOnlyCascadingProperty<Type>*(SpanStyle::* getter)(void)) const
        {
            if (!_spanStyle) return nullptr;
            return (_spanStyle.get()->*getter)();
        }

    public:

        void spanStyle_set(std::shared_ptr<SpanStyle> spanStyle)
        {
       
                if (_spanStyle == spanStyle) return;

                if (_spanStyle)
                    _spanStyle->changed -= _spanStyle_changedHandler;

                _spanStyle = spanStyle;

                if (_spanStyle)
                    _spanStyle->changed += _spanStyle_changedHandler;

                _isSpanStyleShared = true;

                _spanStyle_changedHandler(_spanStyle.get(), nullptr);
            
        }

        std::shared_ptr<SpanStyle> spanStyle_get() { return _spanStyle; };

        //setter and getters

        void textSize_set(double size) { _setProperty<double>(size, &SpanStyle::textSize_set, &SpanStyle::textSize_get); };
        const ReadOnlyCascadingProperty<double>* textSize_get() { return _getProperty<double>(&SpanStyle::textSize_get); };

        void fontFamily_set(std::string fontFamily) { _setProperty<std::string>(fontFamily, &SpanStyle::fontFamily_set, &SpanStyle::fontFamily_get); };
        const ReadOnlyCascadingProperty<std::string>* fontFamily_get() { return _getProperty<std::string>(&SpanStyle::fontFamily_get); };

        void fontStyle_set(FontStyle fontStyle) { _setProperty<FontStyle>(fontStyle, &SpanStyle::fontStyle_set, &SpanStyle::fontStyle_get); };
        const ReadOnlyCascadingProperty<FontStyle>* fontStyle_get() { return _getProperty<FontStyle>(&SpanStyle::fontStyle_get); };

        void fontVariant_set(FontVariant fontVariant) { _setProperty<FontVariant>(fontVariant, &SpanStyle::fontVariant_set, &SpanStyle::fontVariant_get); };
        const ReadOnlyCascadingProperty<FontVariant>* fontVariant_get() { return _getProperty<FontVariant>(&SpanStyle::fontVariant_get); };

        void fontStrech_set(FontStretch fontStrech) { _setProperty<FontStretch>(fontStrech, &SpanStyle::fontStrech_set, &SpanStyle::fontStrech_get); };
        const ReadOnlyCascadingProperty<FontStretch>* fontStrech_get() { return _getProperty<FontStretch>(&SpanStyle::fontStrech_get); };

        void fontWeight_set(FontWeight fontWeight) { _setProperty<FontWeight>(fontWeight, &SpanStyle::fontWeight_set, &SpanStyle::fontWeight_get); };
        const ReadOnlyCascadingProperty<FontWeight>* fontWeight_get() { return _getProperty<FontWeight>(&SpanStyle::fontWeight_get); };

        void fontFallback_set(bool fallback) { _setProperty<bool>(fallback, &SpanStyle::fontFallback_set, &SpanStyle::fontFallback_get); };
        const ReadOnlyCascadingProperty<bool>* fontFallback_get() { return _getProperty<bool>(&SpanStyle::fontFallback_get); };

        void foregroundColor_set(RgbaColor color) { _setProperty<RgbaColor>(color, &SpanStyle::foregroundColor_set, &SpanStyle::foregroundColor_get); };
        const ReadOnlyCascadingProperty<RgbaColor>* foregroundColor_get() { return _getProperty<RgbaColor>(&SpanStyle::foregroundColor_get); };

        void backgroundColor_set(RgbaColor color) { _setProperty<RgbaColor>(color, &SpanStyle::backgroundColor_set, &SpanStyle::backgroundColor_get); };
        const ReadOnlyCascadingProperty<RgbaColor>* backgroundColor_get() { return _getProperty<RgbaColor>(&SpanStyle::backgroundColor_get); };

        void strikethrough_set(bool strikethrough) { _setProperty<bool>(strikethrough, &SpanStyle::strikethrough_set, &SpanStyle::strikethrough_get); };
        const ReadOnlyCascadingProperty<bool>* strikethrough_get() { return _getProperty<bool>(&SpanStyle::strikethrough_get); };

        void strikethroughColor_set(RgbaColor color) { _setProperty<RgbaColor>(color, &SpanStyle::strikethroughColor_set, &SpanStyle::strikethroughColor_get); };
        const ReadOnlyCascadingProperty<RgbaColor>* strikethroughColor_get() { return _getProperty<RgbaColor>(&SpanStyle::strikethroughColor_get); };

        void underline_set(UnderlineType set) { _setProperty<UnderlineType>(set, &SpanStyle::underline_set, &SpanStyle::underline_get); };
        const ReadOnlyCascadingProperty<UnderlineType>* underline_get() { return _getProperty<UnderlineType>(&SpanStyle::underline_get);; };

        void underlineColor_set(RgbaColor color) { _setProperty<RgbaColor>(color, &SpanStyle::underlineColor_set, &SpanStyle::underlineColor_get); };
        const ReadOnlyCascadingProperty<RgbaColor>* underlineColor_get() { return _getProperty<RgbaColor>(&SpanStyle::underlineColor_get); };

        void characterRise_set(double characterRise) { _setProperty<double>(characterRise, &SpanStyle::characterRise_set, &SpanStyle::characterRise_get); };
        const ReadOnlyCascadingProperty<double>* characterRise_get() { return _getProperty<double>(&SpanStyle::characterRise_get); };

        void characterSpacing_set(double spacing) { _setProperty<double>(spacing, &SpanStyle::characterSpacing_set, &SpanStyle::characterRise_get); };
        const ReadOnlyCascadingProperty<double>* characterSpacing_get() { return _getProperty<double>(&SpanStyle::characterSpacing_get); };

        void gravity_set(CharacterGravity gravity) { _setProperty<CharacterGravity>(gravity, &SpanStyle::gravity_set, &SpanStyle::gravity_get); };
        const ReadOnlyCascadingProperty<CharacterGravity>* gravity_get() { return _getProperty<CharacterGravity>(&SpanStyle::gravity_get); };

        void gravityHint_set(CharacterGravityHint gravityHint) { _setProperty<CharacterGravityHint>(gravityHint, &SpanStyle::gravityHint_set, &SpanStyle::gravityHint_get); };
        const ReadOnlyCascadingProperty<CharacterGravityHint>* gravityHint_get() { return _getProperty<CharacterGravityHint>(&SpanStyle::gravityHint_get); };
    };
}