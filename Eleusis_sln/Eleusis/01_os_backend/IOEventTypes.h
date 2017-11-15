 #pragma once

#include "dllexport.h"

#include "event.h"
#include "01_vectoring/Vector.h"
#include "VirtualKey.h"
#include <string>

namespace Eleusis
{
    class Node;

    struct ELEUSIS_API SizeChangedParams
    {
        Vector Size;
    };

    struct ELEUSIS_API KeyboardInputParams
    {
        VirtualKey   VirtualKeyCode = VirtualKey::None;
        std::string  String;
        bool         ShiftDown    = false;
        bool         ControlDown  = false;
        bool         AltDown      = false;
        bool         FunctionDown = false;
    };

    enum class ELEUSIS_API MouseButton
    {
        None,
        Left,
        Middle,
        Right,
        X1,
        X2
    };

    struct ELEUSIS_API MouseInputParams
    {
        int         X = 0;
        int         Y = 0;
        MouseButton Button = MouseButton::None;
        bool        ShiftDown    = false;
        bool        ControlDown  = false;
        bool        AltDown      = false;
        bool        FunctionDown = false;
    };

    enum class ELEUSIS_API MouseScrollType
    {
        Vertical,
        Horizontal
    };

    struct ELEUSIS_API MouseScrollInputParams :
        public MouseInputParams
    {
        MouseScrollType WheelType = MouseScrollType::Vertical;
        short int       WheelMove = 0;
    };

    enum class ELEUSIS_API WindowAppearanceState
    {
        Initializing,
        Normal,
        Maximized,
        Minimized,
        Hidden
    };

    class ELEUSIS_API KeyboardEventArgs :
        public EventArgs,
        public KeyboardInputParams
    {
    public:
        KeyboardEventArgs() {};
        KeyboardEventArgs(KeyboardInputParams & keyboardParams) : KeyboardInputParams(keyboardParams) {};
        Node* PrimarySender = nullptr;
    };

    class ELEUSIS_API MouseEventArgs :
        public EventArgs,
        public MouseInputParams
    {
    public:
        MouseEventArgs() {};
        MouseEventArgs(MouseInputParams & mouseParams) : MouseInputParams(mouseParams) {};
        Node* PrimarySender = nullptr;
    };

    class ELEUSIS_API MouseScrollEventArgs :
        public EventArgs,
        public MouseScrollInputParams
    {
    public:
        MouseScrollEventArgs() {};
        MouseScrollEventArgs(MouseScrollInputParams & mouseWheelParams) : MouseScrollInputParams(mouseWheelParams) {};
        Node* PrimarySender = nullptr;
    };

    class ELEUSIS_API SizeChangedEventArgs :
        public EventArgs,
        public SizeChangedParams
    {
    public:
        SizeChangedEventArgs() {};
        SizeChangedEventArgs(SizeChangedParams & sizeChangedParams) : SizeChangedParams(sizeChangedParams) {};
    };
}

