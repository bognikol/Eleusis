#pragma once

#include "01_Win32/VirtualKey_Win32.h"
#include "02_macOS/VirtualKey_macOS.h"

namespace Eleusis
{
    enum class ELEUSIS_API KeyState
    {
        Unknown,
        Pressed,
        Released
    };
}