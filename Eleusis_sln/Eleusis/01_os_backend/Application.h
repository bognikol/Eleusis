#pragma once

#include "dllexport.h"

#include <string>

#include "event.h"
#include "VirtualKey.h"

#define ELEUSIS_WINDOW_CLASS L"Eleusis_alpha_E159F67AEE26A7AA29FB8F4B329465A1328F6D2C"

namespace Eleusis
{
    class Window;
    class MouseEventArgs;

    class ELEUSIS_API Application
    {
    public:
        static void      registerInstance();
        static int       run(Window*);
        static long long timestamp();

        static Event<void*, EventArgs*> renderingCycleExecuted;
        static Event<void*, MouseEventArgs*> mouseUp; // TODO: This needs handle trully global mouse event.

        static void nativeMsgBox(std::string message = "", std::string title = "");
        static void nativeLog(std::string message);

        static KeyState getVirtualKeyState(VirtualKey key);

        class Clipboard
        {
        public:
            static void putUnicodeText(std::string text);
            static std::string getUnicodeText();
        };

    };
}