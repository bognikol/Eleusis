#include "ToString.h"
#include "Window.h"

using namespace Eleusis;
using namespace std;

string Eleusis::toString(MouseButton button)
{
    switch (button)
    {
    case MouseButton::Left:     return "MouseButton::Left";
    case MouseButton::Middle:   return "MouseButton::Middle";
    case MouseButton::None:     return "MouseButton::None";
    case MouseButton::Right:    return "MouseButton::Right";
    case MouseButton::X1:       return "MouseButton::X1";
    case MouseButton::X2:       return "MouseButton::X2";
    default:                    return "Mouse button could not be identified.";
    }
}

string Eleusis::toString(MouseScrollType wheelType)
{
    switch (wheelType)
    {
    case MouseScrollType::Horizontal:    return "MouseScrollType::Horizontal";
    case MouseScrollType::Vertical:      return "MouseScrollType::Vertical";
    default:                             return "Mouse wheel type could not be identified.";
    }
}

string Eleusis::toString(MouseEventArgs* e)
{
    string l_string;

    l_string += "X=" + to_string(e->X) + "\n";
    l_string += "Y=" + to_string(e->Y) + "\n";
    l_string += "Button=" + toString(e->Button) + "\n";

    return l_string;
}

string Eleusis::toString(MouseScrollEventArgs* e)
{
    string l_string;

    l_string += "X=" + to_string(e->X) + "\n";
    l_string += "Y=" + to_string(e->Y) + "\n";
    l_string += "Button=" + toString(e->Button) + "\n";
    l_string += "Wheel Type=" + toString(e->WheelType) + "\n";
    l_string += "Wheel Move=" + to_string(e->WheelMove) + "\n";

    return l_string;
}


