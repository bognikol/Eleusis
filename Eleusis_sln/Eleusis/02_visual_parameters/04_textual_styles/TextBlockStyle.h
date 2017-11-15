#pragma once

#include "dllexport.h"

#include "TextualTypes.h"
#include "CascadingProperty.h"
#include "event.h"
#include "Defaults.h"
#include "01_vectoring/Length.h"

#include <string>

namespace Eleusis
{
    class ELEUSIS_API TextBlockStyle
    {
    public:     Event<TextBlockStyle*, EventArgs*> changed;

    private:    CascadingProperty<Length> _width  = ELEUSIS_TEXT_BLOCK_WIDTH;
                CascadingProperty<Length> _height = ELEUSIS_TEXT_BLOCK_HEIGHT;

                CascadingProperty<EllipsizeType> _ellipsize = ELEUSIS_TEXT_BLOCK_ELLIPSIZE;

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

                void width_set(Length width) { _setProperty<Length>(width, &_width); };
                const ReadOnlyCascadingProperty<Length>* width_get() { return _getProperty<Length>(&_width); };

                void height_set(Length height) { _setProperty<Length>(height, &_height); };
                const ReadOnlyCascadingProperty<Length>* height_get() { return _getProperty<Length>(&_height); };

                void ellipsize_set(EllipsizeType ellipsizeType) { _setProperty<EllipsizeType>(ellipsizeType, &_ellipsize); };
                const ReadOnlyCascadingProperty<EllipsizeType>* ellipsize_get() { return _getProperty<EllipsizeType>(&_ellipsize); };

                void cascadeFrom(const TextBlockStyle* source);
    };
}