#pragma once

#include <Windows.h>

namespace Eleusis
{
    struct WindowOSBundle
    {
        HWND        _hwnd;
        PAINTSTRUCT _ps;
        HDC         _hdc;
        HBITMAP     _backgroundBuffer;
        HANDLE      _hOld;
    };
}