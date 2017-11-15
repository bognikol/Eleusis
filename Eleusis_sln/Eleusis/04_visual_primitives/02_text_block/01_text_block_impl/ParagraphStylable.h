#pragma once

#include "dllexport.h"

#include "TextualStyles.h"

namespace Eleusis
{
    class ELEUSIS_API ParagraphStylable
    {
    protected:
        Handler<ParagraphStyle*, EventArgs*> _paragraphStyle_changedHandler;

    private:
        std::shared_ptr<ParagraphStyle> _paragraphStyle;
        bool _isSpanStyleShared = false;

        template <typename Type>
        void _setProperty(Type value,
            void(ParagraphStyle::* setter)(Type),
            const ReadOnlyCascadingProperty<Type>*(ParagraphStyle::* getter)(void))
        {
            if (_paragraphStyle)
            {
                if (getter)
                    if ((_paragraphStyle.get()->*getter)()->value() == value && 
                        (_paragraphStyle.get()->*getter)()->isSet() == true) return;

                if (_isSpanStyleShared)
                {
                    ParagraphStyle* l_paragraphStyle = new ParagraphStyle();
                    l_paragraphStyle->cascadeFrom(_paragraphStyle.get());

                    _paragraphStyle->changed -= _paragraphStyle_changedHandler;
                    _paragraphStyle = std::shared_ptr<ParagraphStyle>(l_paragraphStyle);
                    _paragraphStyle->changed += _paragraphStyle_changedHandler;
                }
            }
            else
            {
                _paragraphStyle = std::shared_ptr<ParagraphStyle>(new ParagraphStyle());
                _paragraphStyle->changed += _paragraphStyle_changedHandler;
            }

            _isSpanStyleShared = false;

            (_paragraphStyle.get()->*setter)(value);

            // paragraphUpdated event will be raised automatically from _paragrapStyle_changedHandler
        }

        template <typename Type>
        const ReadOnlyCascadingProperty<Type>* _getProperty
        (const ReadOnlyCascadingProperty<Type>*(ParagraphStyle::* getter)(void)) const
        {
            if (!_paragraphStyle) return nullptr;
            return (_paragraphStyle.get()->*getter)();
        }

    public:

        void paragraphStyle_set(std::shared_ptr<ParagraphStyle> paragraphStyle)
        {

            if (_paragraphStyle == paragraphStyle) return;

            if (_paragraphStyle)
                _paragraphStyle->changed -= _paragraphStyle_changedHandler;

            _paragraphStyle = paragraphStyle;

            if (_paragraphStyle)
                _paragraphStyle->changed += _paragraphStyle_changedHandler;

            _isSpanStyleShared = true;

            _paragraphStyle_changedHandler(_paragraphStyle.get(), nullptr);

        }

        std::shared_ptr<ParagraphStyle> paragraphStyle_get() { return _paragraphStyle; };

        // setters and getters

        void fillBrush_set(std::shared_ptr<Brush> brush) { _setProperty<std::shared_ptr<Brush>>(brush, &ParagraphStyle::fillBrush_set, &ParagraphStyle::fillBrush_get); };
        const ReadOnlyCascadingProperty<std::shared_ptr<Brush>>* fillBrush_get() { return _getProperty<std::shared_ptr<Brush>>(&ParagraphStyle::fillBrush_get); };

        void fillColor_set(RgbaColor color) { _setProperty<RgbaColor>(color, &ParagraphStyle::fillColor_set, nullptr); }

        void paragraphAligment_set(ParagraphAlignment aligment) { _setProperty<ParagraphAlignment>(aligment, &ParagraphStyle::paragraphAligment_set, &ParagraphStyle::paragraphAligment_get); };
        const ReadOnlyCascadingProperty<ParagraphAlignment>* paragraphAligment_get() { return _getProperty<ParagraphAlignment>(&ParagraphStyle::paragraphAligment_get); };

        void firstLineIndent_set(double indent) { _setProperty<double>(indent, &ParagraphStyle::firstLineIndent_set, &ParagraphStyle::firstLineIndent_get); };
        const ReadOnlyCascadingProperty<double>* firstLineIndent_get() { return _getProperty<double>(&ParagraphStyle::firstLineIndent_get); };

        void leftIndent_set(double indent) { _setProperty<double>(indent, &ParagraphStyle::leftIndent_set, &ParagraphStyle::leftIndent_get); };
        const ReadOnlyCascadingProperty<double>* leftIndent_get() { return _getProperty<double>(&ParagraphStyle::leftIndent_get); };

        void rightIndent_set(double indent) { _setProperty<double>(indent, &ParagraphStyle::rightIndent_set, &ParagraphStyle::rightIndent_get); };
        const ReadOnlyCascadingProperty<double>* rightIndent_get() { return _getProperty<double>(&ParagraphStyle::rightIndent_get); };

        void spaceBefore_set(double spaceBefore) { _setProperty<double>(spaceBefore, &ParagraphStyle::spaceBefore_set, &ParagraphStyle::spaceBefore_get); };
        const ReadOnlyCascadingProperty<double>* spaceBefore_get() { return _getProperty<double>(&ParagraphStyle::spaceBefore_get); };

        void spaceAfter_set(double spaceAfter) { _setProperty<double>(spaceAfter, &ParagraphStyle::spaceAfter_set, &ParagraphStyle::spaceAfter_get); };
        const ReadOnlyCascadingProperty<double>* spaceAfter_get() { return _getProperty<double>(&ParagraphStyle::spaceAfter_get); };

        void lineSpaceing_set(double lineSpacing) { _setProperty<double>(lineSpacing, &ParagraphStyle::lineSpaceing_set, &ParagraphStyle::lineSpacing_get); };
        const ReadOnlyCascadingProperty<double>* lineSpacing_get() { return _getProperty<double>(&ParagraphStyle::lineSpacing_get); };

    };
}
