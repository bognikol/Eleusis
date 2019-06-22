#ifdef __APPLE__

#include "Mouse.h"

using namespace Eleusis;

MouseCursor Mouse::_cursor = MouseCursor::Arrow;

void Mouse::setCursor(MouseCursor cursor)
{
    _cursor = cursor;
}

#endif