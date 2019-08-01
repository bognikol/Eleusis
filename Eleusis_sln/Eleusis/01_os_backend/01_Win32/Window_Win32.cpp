#ifdef _WIN32

#include "Window.h"
#include "Application.h"

#include "cairo.h"
#include "cairo-win32.h"

#include "Windows.h"
#include "WindowOSBundle_Win32.h"

using namespace Eleusis;

Window::Window() :
    _windowOSBundle(new WindowOSBundle()),
    _root(new RootNode()),
    _animationManager(new AnimationManager())
{
    _windowOSBundle->_hwnd = CreateWindowW(ELEUSIS_WINDOW_CLASS, nullptr, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, GetModuleHandle(nullptr), this);

    HDC l_hdc = GetDC(_windowOSBundle->_hwnd);

    _windowOSBundle->_hdc                = CreateCompatibleDC     (l_hdc);
    _windowOSBundle->_backgroundBuffer   = CreateCompatibleBitmap (l_hdc, 1920, 1200); //TODO: Give meaningful values here
    _windowOSBundle->_hOld               = SelectObject           (_windowOSBundle->_hdc, _windowOSBundle->_backgroundBuffer);

    ReleaseDC(_windowOSBundle->_hwnd, l_hdc);

    _cairoSurface = cairo_win32_surface_create(_windowOSBundle->_hdc);
    _cairoContext = cairo_create(_cairoSurface);
    _root->setContext(static_cast<UIContext*>(this));
}

Window::~Window()
{
    delete _root;
    delete _animationManager;
    cairo_destroy(_cairoContext);
    cairo_surface_destroy(_cairoSurface);
    SelectObject(_windowOSBundle->_hdc, _windowOSBundle->_hOld);
    DeleteObject(_windowOSBundle->_backgroundBuffer);
    DeleteDC(_windowOSBundle->_hdc);
    DestroyWindow(_windowOSBundle->_hwnd);
    delete _windowOSBundle;
}

void Window::show()
{
      ShowWindow(_windowOSBundle->_hwnd, SW_SHOWNORMAL);
    UpdateWindow(_windowOSBundle->_hwnd);

    _root->setAbsoluteSizeVector(getSize());

    _layout();
    _calculateClippings();
    _updateGeometryAndApplyAbsoluteOffset();
    _render();

    _cleanUpForFollowingRenderingIteration();
}

void Window::showModal()
{
    // TODO: To be implemented
}

void Window::hide()
{
    ShowWindow(_windowOSBundle->_hwnd, SW_HIDE);
}

void Window::minimize()
{
    ShowWindow(_windowOSBundle->_hwnd, SW_MINIMIZE);
}

void Window::maximize()
{
    ShowWindow(_windowOSBundle->_hwnd, SW_MAXIMIZE);
}

bool Window::isModal()
{
    // TODO: To be implemented
    return false;
}

WindowAppearanceState Window::getWindowState()
{
    // TODO: To be implemented
    return WindowAppearanceState::Normal;
}

void Window::focus()
{
    SetFocus(_windowOSBundle->_hwnd);
}

bool Window::isFocused()
{
    HWND l_focusWindowHanlde = GetFocus();
    if (l_focusWindowHanlde && _windowOSBundle->_hwnd == l_focusWindowHanlde) return true;
    return false;
}

void Window::enable()
{
    EnableWindow(_windowOSBundle->_hwnd, true);
}

void Window::disable()
{
    EnableWindow(_windowOSBundle->_hwnd, false);
}

bool Window::isEnabled()
{
    return IsWindowEnabled(_windowOSBundle->_hwnd) != 0;
}

void Window::setPosition(Vector position)
{
    Vector l_size = getSize();

    MoveWindow(_windowOSBundle->_hwnd, 
        static_cast<int>(position.X), 
        static_cast<int>(position.Y), 
        static_cast<int>(l_size.X),
        static_cast<int>(l_size.Y),
        false);
}

Vector Window::getPosition()
{
    RECT l_rectange; 
    GetClientRect(_windowOSBundle->_hwnd, &l_rectange);
    return Vector(l_rectange.left, l_rectange.top);
}

void Window::setSize(Vector size)
{
    Vector l_position = getPosition();

    MoveWindow(_windowOSBundle->_hwnd,
        static_cast<int>(l_position.X),
        static_cast<int>(l_position.Y),
        static_cast<int>(size.X),
        static_cast<int>(size.Y),
        false);
}

Vector Window::getSize()
{
    RECT l_rectange; 
    GetClientRect(_windowOSBundle->_hwnd, &l_rectange);
    return Vector(l_rectange.right, l_rectange.bottom);
}

void Window::_render()
{
    _root->_render(nullptr);

    cairo_surface_flush(_cairoSurface);

    HDC l_hdc = GetDC(_windowOSBundle->_hwnd);
    RECT l_rectange; GetClientRect(_windowOSBundle->_hwnd, &l_rectange);
    BitBlt(l_hdc, 0, 0, l_rectange.right, l_rectange.bottom, _windowOSBundle->_hdc, 0, 0, SRCCOPY);
    ReleaseDC(_windowOSBundle->_hwnd, l_hdc);
}

void Window::_render(Region* region)
{
    _root->_render(region);

    cairo_surface_flush(_cairoSurface);

    HDC l_hdc = GetDC(_windowOSBundle->_hwnd);

    Vector l_rectSize;
    for (auto rect : region->getRects())
    {
        l_rectSize = rect.sizeVector();
        BitBlt(
            l_hdc,
            static_cast<int>(rect.lowVector.X),
            static_cast<int>(rect.lowVector.Y),
            static_cast<int>(l_rectSize.X),
            static_cast<int>(l_rectSize.Y),
            _windowOSBundle->_hdc,
            static_cast<int>(rect.lowVector.X),
            static_cast<int>(rect.lowVector.Y),
            SRCCOPY);
    }

    ReleaseDC(_windowOSBundle->_hwnd, l_hdc);
}

Rect Window::surfaceSize()
{
    // TODO: TO be implemented
    return Rect();
}

void* Window::getNativeHandle()
{
    return (void*)_windowOSBundle->_hwnd;
}

#endif