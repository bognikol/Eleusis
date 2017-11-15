#pragma once

#include "dllexport.h"

enum class MouseCursor
{
    Arrow,
    IBeam,
    Wait
};

namespace Eleusis
{
    class ELEUSIS_API Mouse
    {
    private:
        static MouseCursor _cursor;

    public:
        static void setCursor(MouseCursor cursor);
        static MouseCursor getCursor() { return _cursor; };
    };
}