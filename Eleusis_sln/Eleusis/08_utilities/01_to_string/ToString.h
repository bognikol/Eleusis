#pragma once

#include "dllexport.h"

#include <string>

namespace Eleusis
{
    enum class MouseButton;
    std::string ELEUSIS_API toString(MouseButton);

    enum class MouseScrollType;
    std::string ELEUSIS_API toString(MouseScrollType);

    class MouseEventArgs;
    std::string ELEUSIS_API toString(MouseEventArgs*);

    class MouseScrollEventArgs;
    std::string ELEUSIS_API toString(MouseScrollEventArgs*);
};