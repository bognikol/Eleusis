#pragma once

#include "dllexport.h"

#include "TextualTypes.h"
#include "CascadingProperty.h"
#include "Colors.h"
#include "Defaults.h"

#include <string>

namespace Eleusis
{
    class ELEUSIS_API SpanStyle
    {
    public:     Event<SpanStyle*, EventArgs*> changed;

    private:    CascadingProperty<double>      _textSize     = ELEUSIS_SPAN_TEXT_SIZE;

                CascadingProperty<std::string> _fontFamily   = ELEUSIS_SPAN_FONT_FAMILY;
                CascadingProperty<FontStyle>   _fontStyle    = ELEUSIS_SPAN_FONT_STYLE;
                CascadingProperty<FontVariant> _fontVariant  = ELEUSIS_SPAN_FONT_VARIANT;
                CascadingProperty<FontStretch> _fontStretch  = ELEUSIS_SPAN_FONT_STRETCH;
                CascadingProperty<FontWeight>  _fontWeight   = ELEUSIS_SPAN_FONT_WEIGHT;
                CascadingProperty<bool>        _fontFallback = ELEUSIS_SPAN_FONT_FALLBACK;

                CascadingProperty<RgbaColor> _foregroundColor = ELEUSIS_SPAN_FOREGROUND_COLOR;
                CascadingProperty<RgbaColor> _backgroundColor = ELEUSIS_SPAN_BACKGROUND_COLOR;

                CascadingProperty<bool>      _strikethrough      = ELEUSIS_SPAN_STRIKETHROUGH;
                CascadingProperty<RgbaColor> _strikethroughColor = ELEUSIS_SPAN_STRIKETHROUGH_COLOR;

                CascadingProperty<UnderlineType> _underline      = ELEUSIS_SPAN_UNDERLINE;
                CascadingProperty<RgbaColor>     _underlineColor = ELEUSIS_SPAN_UNDERLINE_COLOR;

                CascadingProperty<double> _characterRise    = ELEUSIS_SPAN_CHARACTER_RISE;
                CascadingProperty<double> _characterSpacing = ELEUSIS_SPAN_CHARACTER_SPACING;

                CascadingProperty<CharacterGravity>     _gravity     = ELEUSIS_SPAN_GRAVITY;
                CascadingProperty<CharacterGravityHint> _gravityHint = ELEUSIS_SPAN_GRAVITY_HINT;

                bool _isApplied = false;

                template<typename Type>
                void _setProperty(Type value, CascadingProperty<Type>* propertyToSet)
                {
                    _isApplied = true;
                    if (propertyToSet->value() == value && propertyToSet->isSet() == true) return;
                    propertyToSet->setValue(value);
                    raiseEvent changed(this, nullptr);
                }

                template<typename Type>
                const ReadOnlyCascadingProperty<Type>* _getProperty (CascadingProperty<Type>* propertyToGet) const
                {
                    return propertyToGet->getReadOnlyProperty();
                };

    public:     bool isApplied() const { return _isApplied; };

                void textSize_set(double size) { _setProperty<double>(size, &_textSize); };
                const ReadOnlyCascadingProperty<double>* textSize_get() { return _getProperty<double>(&_textSize); };

                void fontFamily_set(std::string fontFamily) { _setProperty<std::string>(fontFamily, &_fontFamily); };
                const ReadOnlyCascadingProperty<std::string>* fontFamily_get() { return _getProperty<std::string>(&_fontFamily); };

                void fontStyle_set(FontStyle fontStyle) { _setProperty<FontStyle>(fontStyle, &_fontStyle); };
                const ReadOnlyCascadingProperty<FontStyle>* fontStyle_get() { return _getProperty<FontStyle>(&_fontStyle); };

                void fontVariant_set(FontVariant fontVariant) { _setProperty<FontVariant>(fontVariant, &_fontVariant); };
                const ReadOnlyCascadingProperty<FontVariant>* fontVariant_get() { return _getProperty<FontVariant>(&_fontVariant); };

                void fontStrech_set(FontStretch fontStrech) { _setProperty<FontStretch>(fontStrech, &_fontStretch); };
                const ReadOnlyCascadingProperty<FontStretch>* fontStrech_get() { return _getProperty<FontStretch>(&_fontStretch); };

                void fontWeight_set(FontWeight fontWeight) { _setProperty<FontWeight>(fontWeight, &_fontWeight); };
                const ReadOnlyCascadingProperty<FontWeight>* fontWeight_get() { return _getProperty<FontWeight>(&_fontWeight); };

                void fontFallback_set(bool fallback) { _setProperty<bool>(fallback, &_fontFallback); };
                const ReadOnlyCascadingProperty<bool>* fontFallback_get() { return _getProperty<bool>(&_fontFallback); };

                void foregroundColor_set(RgbaColor color) { _setProperty<RgbaColor>(color, &_foregroundColor); };
                const ReadOnlyCascadingProperty<RgbaColor>* foregroundColor_get() { return _getProperty<RgbaColor>(&_foregroundColor); };

                void backgroundColor_set(RgbaColor color) { _setProperty<RgbaColor>(color, &_backgroundColor); };
                const ReadOnlyCascadingProperty<RgbaColor>* backgroundColor_get() { return _getProperty<RgbaColor>(&_backgroundColor); };

                void strikethrough_set(bool strikethrough) { _setProperty<bool>(strikethrough, &_strikethrough); };
                const ReadOnlyCascadingProperty<bool>* strikethrough_get() { return _getProperty<bool>(&_strikethrough); };

                void strikethroughColor_set(RgbaColor color) { _setProperty<RgbaColor>(color, &_strikethroughColor); };
                const ReadOnlyCascadingProperty<RgbaColor>* strikethroughColor_get() { return _getProperty<RgbaColor>(&_strikethroughColor); };

                void underline_set(UnderlineType set) { _setProperty<UnderlineType>(set, &_underline); };
                const ReadOnlyCascadingProperty<UnderlineType>* underline_get() { return _getProperty<UnderlineType>(&_underline);; };

                void underlineColor_set(RgbaColor color) { _setProperty<RgbaColor>(color, &_underlineColor); };
                const ReadOnlyCascadingProperty<RgbaColor>* underlineColor_get() { return _getProperty<RgbaColor>(&_underlineColor); };

                void characterRise_set(double characterRise) { _setProperty<double>(characterRise, &_characterRise); };
                const ReadOnlyCascadingProperty<double>* characterRise_get() { return _getProperty<double>(&_characterRise); };

                void characterSpacing_set(double spacing) { _setProperty<double>(spacing, &_characterSpacing); };
                const ReadOnlyCascadingProperty<double>* characterSpacing_get() { return _getProperty<double>(&_characterSpacing); };

                void gravity_set(CharacterGravity gravity) { _setProperty<CharacterGravity>(gravity, &_gravity); };
                const ReadOnlyCascadingProperty<CharacterGravity>* gravity_get() { return _getProperty<CharacterGravity>(&_gravity); };

                void gravityHint_set(CharacterGravityHint gravityHint) { _setProperty<CharacterGravityHint>(gravityHint, &_gravityHint); };
                const ReadOnlyCascadingProperty<CharacterGravityHint>* gravityHint_get() { return _getProperty<CharacterGravityHint>(&_gravityHint); };

                void cascadeFrom(const SpanStyle* source);
    };

}