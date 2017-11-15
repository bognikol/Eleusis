#pragma once

#include "dllexport.h"

namespace Eleusis
{
    template <typename Type>
    class ELEUSIS_API ReadOnlyCascadingProperty
    {
    protected:  Type _value;
                bool _isSet = false;

    public:     Type value() const { return _value; }
                bool isSet() const { return _isSet; }

                bool operator == (const ReadOnlyCascadingProperty<Type> & cp)
                {
                    if (_value == cp._value) return true;
                    return false;
                }
    };

    template <typename Type>
    class ELEUSIS_API CascadingProperty :
        public ReadOnlyCascadingProperty<Type>
    {

    public:
        CascadingProperty()
        {
        }

        CascadingProperty(Type v)
        {
            this->_value = v;
        }

        void operator = (Type v)
        {
            this->_value = v;
            this->_isSet = true;
        }

        void setValue(Type value)
        {
            this->_value = value;
            this->_isSet = true;
        }

        void reset()
        {
            this->_isSet = false;
        }

        bool operator == (const CascadingProperty<Type> & cp)
        {
            if (this->_value == cp._value) return true;
            return false;
        }

        const ReadOnlyCascadingProperty<Type>* getReadOnlyProperty() const
        {
            return const_cast<const CascadingProperty<Type>*>(this);
        }

        CascadingProperty<Type> operator + (const CascadingProperty<Type> & cp) const
        {
            if (cp._isSet) return cp;
            return *this;
        }

        void operator += (const CascadingProperty<Type> & cp)
        {
            if (cp._isSet)
            {
                this->_value = cp._value;
                this->_isSet = cp._isSet;
            }
        }
    };
}
