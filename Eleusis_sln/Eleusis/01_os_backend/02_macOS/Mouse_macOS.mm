#ifdef __APPLE__

#include "Mouse.h"
#import <Cocoa/Cocoa.h>

using namespace Eleusis;

MouseCursor Mouse::_cursor = MouseCursor::Arrow;

void Mouse::setCursor(MouseCursor cursor)
{
    _cursor = cursor;
    switch (cursor)
    {
    case(MouseCursor::Arrow): [[NSCursor arrowCursor] set]; return;
    case(MouseCursor::IBeam): [[NSCursor IBeamCursor] set]; return;
    case(MouseCursor::Wait):  /*do nothing, macOS does*/    return;
    }
}

#endif