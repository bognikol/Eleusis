#pragma once

#include "dllexport.h"

#include "CascadingProperty.h"
#include "TextualTypes.h"
#include "VisualParameters.h"
#include "Defaults.h"

#include <memory>

namespace Eleusis
{
    class ELEUSIS_API ParagraphStyle
    {
    public:     Event<ParagraphStyle*, EventArgs*> changed;

    private:    CascadingProperty<std::shared_ptr<Brush>> _fillBrush = ELEUSIS_PARAGRAPH_FILL_BRUSH;

                CascadingProperty<ParagraphAlignment> _alignment = ELEUSIS_PARAGRAPH_ALIGMENT;

                CascadingProperty<double> _firstLineIndent = ELEUSIS_PARAGRAPH_FIRST_LINE_INDENT;

                CascadingProperty<double> _leftIndent  = ELEUSIS_PARAGRAPH_LEFT_INDENT;
                CascadingProperty<double> _rightIndent = ELEUSIS_PARAGRAPH_RIGHT_INDENT;

                CascadingProperty<double> _spaceBefore = ELEUSIS_PARAGRAPH_SPACE_BEFORE;
                CascadingProperty<double> _spaceAfter  = ELEUSIS_PARAGRAPH_SPACE_AFTER;

                CascadingProperty<double> _lineSpacing = ELEUSIS_PARAGRAPH_LINE_SPACING;

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
                const ReadOnlyCascadingProperty<Type>* _getProperty(CascadingProperty<Type>* propertyToGet)
                {
                    return propertyToGet->getReadOnlyProperty();
                };

    public:     bool isApplied() const { return _isApplied; };

                void fillBrush_set(std::shared_ptr<Brush> brush) { _setProperty<std::shared_ptr<Brush>>(brush, &_fillBrush); };
                const ReadOnlyCascadingProperty<std::shared_ptr<Brush>>* fillBrush_get() { return _getProperty<std::shared_ptr<Brush>>(&_fillBrush); };

                void fillColor_set(RgbaColor color) { fillBrush_set(std::shared_ptr<Brush>(new SolidColorBrush(color))); }

                void paragraphAligment_set(ParagraphAlignment aligment) { _setProperty<ParagraphAlignment>(aligment, &_alignment); };
                const ReadOnlyCascadingProperty<ParagraphAlignment>* paragraphAligment_get() { return _getProperty<ParagraphAlignment>(&_alignment); };

                void firstLineIndent_set(double indent) { _setProperty<double>(indent, &_firstLineIndent); };
                const ReadOnlyCascadingProperty<double>* firstLineIndent_get() { return _getProperty<double>(&_firstLineIndent); };

                void leftIndent_set(double indent) { _setProperty<double>(indent, &_leftIndent); };
                const ReadOnlyCascadingProperty<double>* leftIndent_get() { return _getProperty<double>(&_leftIndent); };

                void rightIndent_set(double indent) { _setProperty<double>(indent, &_rightIndent); };
                const ReadOnlyCascadingProperty<double>* rightIndent_get() { return _getProperty<double>(&_rightIndent); };

                void spaceBefore_set(double spaceBefore) { _setProperty<double>(spaceBefore, &_spaceBefore); };
                const ReadOnlyCascadingProperty<double>* spaceBefore_get() { return _getProperty<double>(&_spaceBefore); };

                void spaceAfter_set(double spaceAfter) { _setProperty<double>(spaceAfter, &_spaceAfter); };
                const ReadOnlyCascadingProperty<double>* spaceAfter_get() { return _getProperty<double>(&_spaceAfter); };

                void lineSpaceing_set(double lineSpacing) { _setProperty<double>(lineSpacing, &_lineSpacing); };
                const ReadOnlyCascadingProperty<double>* lineSpacing_get() { return _getProperty<double>(&_lineSpacing); };

                void cascadeFrom(const ParagraphStyle* source);
    };
}