#include "Length.h"

using namespace Eleusis;

double Length::getValueRelativeTo(double length)
{
    switch (_pointType)
    {
        case PointType::DeviceIndependent: return _value;
        case PointType::Fraction:          return _value / 100.0 * length;
        case PointType::FitChildren:       
        default:                           return 0;
    }
}

DeviceIndependentLength Eleusis::operator"" _DIPs(long double value)
{
    return Eleusis::DeviceIndependentLength(value);
}

FractionLength Eleusis::operator"" _FPs(long double value)
{
    return Eleusis::FractionLength(value);
}