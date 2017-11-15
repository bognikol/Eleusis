#pragma once

#include "dllexport.h"

namespace Eleusis
{
    enum class PointType
    {
        DeviceIndependent,
        Fraction,
        FitChildren
    };

    class ELEUSIS_API Length
    {
    protected: PointType _pointType = PointType::DeviceIndependent;
               double    _value = 0;

    public:    Length() { };
               Length(double value) { _value = value; };
               void operator = (double value) { _value = value; };
               PointType getType() { return _pointType; };
               double getValue() { return _value; };
               double getValueRelativeTo(double length);
               operator double() { return _value; };
    };

    class DeviceIndependentLength
        : public Length
    {
    public:     DeviceIndependentLength(double value) :
                    Length(value)
                {
                };
    };

    class FractionLength
        : public Length
    {
    public:     FractionLength(double value) :
                    Length(value)
                {
                    _pointType = PointType::Fraction;
                };
    };

    // FitChildren functionality not implemented yet.

    class FitChildrenLength :
        public Length
    {
    public:     FitChildrenLength()
                {
                    _pointType = PointType::FitChildren;
                }
    };

    const FitChildrenLength FitChildren;

    ELEUSIS_API DeviceIndependentLength operator"" _DIPs(long double value); // _DIPs is short for DeviceIndependentPoints
    ELEUSIS_API FractionLength operator"" _FPs(long double value); // _FPs is short for FractionPoints

}