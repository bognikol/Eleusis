#include "Mouse.h"
#include "Windows.h"

using namespace Eleusis;

HCURSOR _currentWin32Cursor = LoadCursor(nullptr, IDC_ARROW);

LPCTSTR _getCursorName(MouseCursor cursor)
{
    switch (cursor)
    {
    case(MouseCursor::Arrow): return IDC_ARROW;
    case(MouseCursor::IBeam): return IDC_IBEAM;
    case(MouseCursor::Wait):  return IDC_WAIT;
    }

    return NULL;
}

MouseCursor Mouse::_cursor = MouseCursor::Arrow;

void Mouse::setCursor(MouseCursor cursor)
{
    _cursor = cursor;
    _currentWin32Cursor = LoadCursor(nullptr, _getCursorName(_cursor));
    SetCursor(_currentWin32Cursor);
}