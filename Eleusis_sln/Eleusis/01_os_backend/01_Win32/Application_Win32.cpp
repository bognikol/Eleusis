#ifdef _WIN32

#include "Application.h"
#include "Window.h"

#include "Windowsx.h"
#include <Windows.h>
#include <list>
#include <codecvt>
#include <chrono>

using namespace Eleusis;
using namespace std;
using namespace std::chrono;


static BYTE*      keyboardState = new BYTE[256];
static const UINT const_renderingTimerID = 0xE1E9819;

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static list<HWND> windowHandles = list<HWND>();

static Window* obtainWindowPointer(HWND);
static void    populateKeyboardInputParams(WPARAM, KeyboardInputParams*);
static void    populateMouseInputParams(WPARAM, LPARAM, MouseInputParams*);
static void    raise_WM_HOVER_and_WM_LEAVE(HWND);

static LRESULT handle___WM_CREATE       (HWND, UINT, WPARAM, LPARAM);
static LRESULT handle___WM_CLOSE        (HWND, UINT, WPARAM, LPARAM);

static LRESULT handle___WM_SETCURSOR    (HWND, UINT, WPARAM, LPARAM);

static LRESULT dispatch_WM_TIMER        (HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_PAINT        (HWND, UINT, WPARAM, LPARAM);

static LRESULT dispatch_WM_SIZE         (HWND, UINT, WPARAM, LPARAM);

static LRESULT dispatch_WM_KEYDOWN      (HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_KEYUP        (HWND, UINT, WPARAM, LPARAM);

static LRESULT dispatch_WM_LBUTTONDBLCLK(HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_LBUTTONDOWN  (HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_LBUTTONUP    (HWND, UINT, WPARAM, LPARAM);

static LRESULT dispatch_WM_MBUTTONDBLCLK(HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_MBUTTONDOWN  (HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_MBUTTONUP    (HWND, UINT, WPARAM, LPARAM);

static LRESULT dispatch_WM_RBUTTONDBLCLK(HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_RBUTTONDOWN  (HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_RBUTTONUP    (HWND, UINT, WPARAM, LPARAM);

static LRESULT dispatch_WM_XBUTTONDBLCLK(HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_XBUTTONDOWN  (HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_XBUTTONUP    (HWND, UINT, WPARAM, LPARAM);

static LRESULT dispatch_WM_MOUSEMOVE    (HWND, UINT, WPARAM, LPARAM);

static LRESULT dispatch_WM_MOUSEWHEEL   (HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_MOUSEHWHEEL  (HWND, UINT, WPARAM, LPARAM);

static LRESULT dispatch_WM_MOUSEHOVER   (HWND, UINT, WPARAM, LPARAM);
static LRESULT dispatch_WM_MOUSELEAVE   (HWND, UINT, WPARAM, LPARAM);

Event<void*, EventArgs*>      Application::renderingCycleExecuted = Event<void*, EventArgs*>();
Event<void*, MouseEventArgs*> Application::mouseUp                = Event<void*, MouseEventArgs*>();


void Application::registerInstance()
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.lpfnWndProc    = WndProc;
    wcex.hInstance      = GetModuleHandle(nullptr);
    wcex.lpszClassName  = ELEUSIS_WINDOW_CLASS;

    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.style          = CS_DBLCLKS;

    wcex.hbrBackground  = 0;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hIcon          = 0;
    wcex.lpszMenuName   = 0;
    wcex.hIconSm        = 0;

    RegisterClassExW(&wcex);
}

int Application::run(Window* startupWindow)
{
    startupWindow->show();

    const int IDC_ELEUSIS = 109;

    HACCEL hAccelTable = LoadAccelerators(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDC_ELEUSIS));
    MSG msg;

    SetTimer((HWND)startupWindow->getNativeHandle(), const_renderingTimerID, 30, nullptr);

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
             DispatchMessage(&msg);
        }
    }

    return static_cast<int>(msg.wParam);
}

long long Application::timestamp()
{
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

System Application::currentSystem()
{
    return System::Win32;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:         return handle___WM_CREATE        (hWnd, message, wParam, lParam);
        case WM_CLOSE:          return handle___WM_CLOSE         (hWnd, message, wParam, lParam);

        case WM_SETCURSOR:      return handle___WM_SETCURSOR     (hWnd, message, wParam, lParam);

        case WM_TIMER:          return dispatch_WM_TIMER         (hWnd, message, wParam, lParam);
        case WM_PAINT:          return dispatch_WM_PAINT         (hWnd, message, wParam, lParam);

        case WM_SIZE:           return dispatch_WM_SIZE          (hWnd, message, wParam, lParam);

        case WM_KEYDOWN:        return dispatch_WM_KEYDOWN       (hWnd, message, wParam, lParam);
        case WM_KEYUP:          return dispatch_WM_KEYUP         (hWnd, message, wParam, lParam);

        case WM_LBUTTONDBLCLK:  return dispatch_WM_LBUTTONDBLCLK (hWnd, message, wParam, lParam);
        case WM_LBUTTONDOWN:    return dispatch_WM_LBUTTONDOWN   (hWnd, message, wParam, lParam);
        case WM_LBUTTONUP:      return dispatch_WM_LBUTTONUP     (hWnd, message, wParam, lParam);

        case WM_MBUTTONDBLCLK:  return dispatch_WM_MBUTTONDBLCLK (hWnd, message, wParam, lParam);
        case WM_MBUTTONDOWN:    return dispatch_WM_MBUTTONDOWN   (hWnd, message, wParam, lParam);
        case WM_MBUTTONUP:      return dispatch_WM_MBUTTONUP     (hWnd, message, wParam, lParam);
            
        case WM_RBUTTONDBLCLK:  return dispatch_WM_RBUTTONDBLCLK (hWnd, message, wParam, lParam);
        case WM_RBUTTONDOWN:    return dispatch_WM_RBUTTONDOWN   (hWnd, message, wParam, lParam);
        case WM_RBUTTONUP:      return dispatch_WM_RBUTTONUP     (hWnd, message, wParam, lParam);

        case WM_XBUTTONDBLCLK:  return dispatch_WM_XBUTTONDBLCLK (hWnd, message, wParam, lParam);
        case WM_XBUTTONDOWN:    return dispatch_WM_XBUTTONDOWN   (hWnd, message, wParam, lParam);
        case WM_XBUTTONUP:      return dispatch_WM_XBUTTONUP     (hWnd, message, wParam, lParam);

        case WM_MOUSEMOVE:      return dispatch_WM_MOUSEMOVE     (hWnd, message, wParam, lParam);

        case WM_MOUSEWHEEL:     return dispatch_WM_MOUSEWHEEL    (hWnd, message, wParam, lParam);
        case WM_MOUSEHWHEEL:    return dispatch_WM_MOUSEHWHEEL   (hWnd, message, wParam, lParam);

        case WM_MOUSEHOVER:     return dispatch_WM_MOUSEHOVER    (hWnd, message, wParam, lParam);
        case WM_MOUSELEAVE:     return dispatch_WM_MOUSELEAVE    (hWnd, message, wParam, lParam);

        default:                return DefWindowProc             (hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT handle___WM_CREATE(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
    Window*       win     = reinterpret_cast<Window*>(pCreate->lpCreateParams);

    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)win);

    windowHandles.push_back(hWnd);

    return 0;
}

LRESULT handle___WM_CLOSE(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    windowHandles.remove(hWnd);
    delete obtainWindowPointer(hWnd);

    if (windowHandles.empty()) PostQuitMessage(0);

    return 0;
}

extern HCURSOR _currentWin32Cursor;

LRESULT handle___WM_SETCURSOR(HWND, UINT, WPARAM, LPARAM)
{
    SetCursor(_currentWin32Cursor);

    return 0;
}

Window* obtainWindowPointer(HWND hWnd)
{
    LONG_PTR l_longptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
    Window*  l_window  = reinterpret_cast<Window*>(l_longptr);
    
    return l_window;
}

LRESULT dispatch_WM_TIMER(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //TODO: Rendering throtling to be implemented here
    if ((UINT)wParam == const_renderingTimerID)
    {
        for (auto handle : windowHandles)
            obtainWindowPointer(handle)->onRenderingTimer();

        raiseEvent Application::renderingCycleExecuted(nullptr, nullptr);
    }

    return 0;
}

LRESULT dispatch_WM_PAINT(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
                EndPaint(hWnd, &ps);

    Rect rect;
    rect.lowVector = { static_cast<double>(ps.rcPaint.left), static_cast<double>(ps.rcPaint.top) };
    rect.highVector = { static_cast<double>(ps.rcPaint.right), static_cast<double>(ps.rcPaint.bottom) };
    obtainWindowPointer(hWnd)->onRedrawRequested(rect);

    return 0;
}

LRESULT dispatch_WM_SIZE(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SizeChangedParams l_sizeCahangedParams;
    RECT l_rectange; GetClientRect(hWnd, &l_rectange);
    l_sizeCahangedParams.Size.X = l_rectange.right;
    l_sizeCahangedParams.Size.Y = l_rectange.bottom;
    obtainWindowPointer(hWnd)->onSizeChanged(l_sizeCahangedParams);

    return 0;
}

#pragma region KEYBOARD_INPUT

KeyState Application::getVirtualKeyState(VirtualKey key)
{
    SHORT l_keyState = GetKeyState((int)key);

    if (l_keyState == 0) return KeyState::Unknown;
    if (l_keyState  < 0) return KeyState::Pressed;

    return KeyState::Released;
}

void populateKeyboardInputParams(WPARAM wParam, KeyboardInputParams* inputParams)
{
    // TODO: What happens when wParam cannot be casted to VirtualKey enum?
    // Undefined behaviour :-) We need a conversion function here.
    // View more at: https://stackoverflow.com/questions/18195312/what-happens-if-you-static-cast-invalid-value-to-enum-class

    inputParams->VirtualKeyCode = static_cast<VirtualKey>(wParam);

    if (Application::getVirtualKeyState(VirtualKey::Shift)   == KeyState::Pressed) inputParams->ShiftDown   = true;
    if (Application::getVirtualKeyState(VirtualKey::Menu)    == KeyState::Pressed) inputParams->AltDown     = true;
    if (Application::getVirtualKeyState(VirtualKey::Control) == KeyState::Pressed) inputParams->ControlDown = true;

    GetKeyboardState(keyboardState);
    WCHAR l_outputBuffer[10];

    int   l_retToUni = ToUnicode(wParam,
                                 MapVirtualKey(wParam, MAPVK_VK_TO_VSC),
                                 keyboardState,
                                 l_outputBuffer,
                                 10,
                                 0);

    wchar_t l_wDest[2];
    l_wDest[0] = l_outputBuffer[0];
    l_wDest[1] = 0;

    inputParams->String = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(l_wDest);
}

LRESULT dispatch_WM_KEYDOWN(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    KeyboardInputParams l_keyboardInputParams;
    populateKeyboardInputParams(wParam, &l_keyboardInputParams);  
    obtainWindowPointer(hWnd)->onKeyDown(l_keyboardInputParams);  

    return 0;
}

LRESULT dispatch_WM_KEYUP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    KeyboardInputParams l_keyboardInputParams;
    populateKeyboardInputParams(wParam, &l_keyboardInputParams);
    obtainWindowPointer(hWnd)->onKeyUp(l_keyboardInputParams);

    return 0;
}

#pragma endregion

#pragma region MOUSE_INPUT

void populateMouseInputParams(WPARAM wParam, LPARAM lParam, MouseInputParams* inputParams)
{
    inputParams->X = static_cast<int>(GET_X_LPARAM(lParam));
    inputParams->Y = static_cast<int>(GET_Y_LPARAM(lParam));

    if (wParam & MK_CONTROL) inputParams->ControlDown = true;
    if (wParam & MK_SHIFT)   inputParams->ShiftDown   = true;
    if (Application::getVirtualKeyState(VirtualKey::Menu) == KeyState::Pressed) inputParams->AltDown = true;
}

void raise_WM_HOVER_and_WM_LEAVE(HWND hWnd)
{
    TRACKMOUSEEVENT l_trackMouseEvent;

    l_trackMouseEvent.cbSize        = sizeof(l_trackMouseEvent);
    l_trackMouseEvent.hwndTrack     = hWnd;
    l_trackMouseEvent.dwFlags       = TME_LEAVE | TME_HOVER;
    l_trackMouseEvent.dwHoverTime   = HOVER_DEFAULT;

    TrackMouseEvent(&l_trackMouseEvent);
}

LRESULT dispatch_WM_LBUTTONDBLCLK(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    l_mouseInputParams.Button = MouseButton::Left;
    obtainWindowPointer(hWnd)->onMouseButtonDoubleClick(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_LBUTTONDOWN(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    l_mouseInputParams.Button = MouseButton::Left;
    obtainWindowPointer(hWnd)->onMouseButtonDown(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_LBUTTONUP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    l_mouseInputParams.Button = MouseButton::Left;
    Application::mouseUp(nullptr, &MouseEventArgs(l_mouseInputParams));
    obtainWindowPointer(hWnd)->onMouseButtonUp(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_MBUTTONDBLCLK(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    l_mouseInputParams.Button = MouseButton::Middle;
    obtainWindowPointer(hWnd)->onMouseButtonDoubleClick(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_MBUTTONDOWN(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    l_mouseInputParams.Button = MouseButton::Middle;
    obtainWindowPointer(hWnd)->onMouseButtonDown(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_MBUTTONUP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    l_mouseInputParams.Button = MouseButton::Middle;
    Application::mouseUp(nullptr, &MouseEventArgs(l_mouseInputParams));
    obtainWindowPointer(hWnd)->onMouseButtonUp(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_RBUTTONDBLCLK(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    l_mouseInputParams.Button = MouseButton::Right;
    obtainWindowPointer(hWnd)->onMouseButtonDoubleClick(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_RBUTTONDOWN(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    l_mouseInputParams.Button = MouseButton::Right;
    obtainWindowPointer(hWnd)->onMouseButtonDown(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_RBUTTONUP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    l_mouseInputParams.Button = MouseButton::Right;
    Application::mouseUp(nullptr, &MouseEventArgs(l_mouseInputParams));
    obtainWindowPointer(hWnd)->onMouseButtonUp(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_XBUTTONDBLCLK(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    if (GET_XBUTTON_WPARAM(wParam) == MK_XBUTTON1) l_mouseInputParams.Button = MouseButton::X1;
    if (GET_XBUTTON_WPARAM(wParam) == MK_XBUTTON2) l_mouseInputParams.Button = MouseButton::X2;
    obtainWindowPointer(hWnd)->onMouseButtonDoubleClick(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_XBUTTONDOWN(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    if (GET_XBUTTON_WPARAM(wParam) == MK_XBUTTON1) l_mouseInputParams.Button = MouseButton::X1;
    if (GET_XBUTTON_WPARAM(wParam) == MK_XBUTTON2) l_mouseInputParams.Button = MouseButton::X2;
    obtainWindowPointer(hWnd)->onMouseButtonDown(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_XBUTTONUP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    if (GET_XBUTTON_WPARAM(wParam) == MK_XBUTTON1) l_mouseInputParams.Button = MouseButton::X1;
    if (GET_XBUTTON_WPARAM(wParam) == MK_XBUTTON2) l_mouseInputParams.Button = MouseButton::X2;
    Application::mouseUp(nullptr, &MouseEventArgs(l_mouseInputParams));
    obtainWindowPointer(hWnd)->onMouseButtonUp(l_mouseInputParams);

    return 0;
}

LRESULT dispatch_WM_MOUSEMOVE(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseInputParams l_mouseInputParams;
    populateMouseInputParams(wParam, lParam, &l_mouseInputParams);
    l_mouseInputParams.Button = MouseButton::None;
    obtainWindowPointer(hWnd)->onMouseMove(l_mouseInputParams);

    raise_WM_HOVER_and_WM_LEAVE(hWnd);

    return 0;
}

LRESULT dispatch_WM_MOUSEWHEEL(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseScrollInputParams l_mouseWheelInputParams;
    l_mouseWheelInputParams.WheelType = MouseScrollType::Vertical;
    l_mouseWheelInputParams.WheelMove = HIWORD(wParam);
    l_mouseWheelInputParams.Button = MouseButton::None;
    populateMouseInputParams(wParam, lParam, &l_mouseWheelInputParams);

    POINT l_coordinates;
    l_coordinates.x = l_mouseWheelInputParams.X;
    l_coordinates.y = l_mouseWheelInputParams.Y;
    ScreenToClient(hWnd, &l_coordinates);
    l_mouseWheelInputParams.X = l_coordinates.x;
    l_mouseWheelInputParams.Y = l_coordinates.y;

    obtainWindowPointer(hWnd)->onMouseWheel(l_mouseWheelInputParams);

    return 0;
}

LRESULT dispatch_WM_MOUSEHWHEEL(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MouseScrollInputParams l_mouseWheelInputParams;
    l_mouseWheelInputParams.WheelType = MouseScrollType::Horizontal;
    l_mouseWheelInputParams.WheelMove = HIWORD(wParam);
    l_mouseWheelInputParams.Button = MouseButton::None;
    populateMouseInputParams(wParam, lParam, &l_mouseWheelInputParams);
    
    POINT l_coordinates;
    l_coordinates.x = l_mouseWheelInputParams.X;
    l_coordinates.y = l_mouseWheelInputParams.Y;
    ScreenToClient(hWnd, &l_coordinates);
    l_mouseWheelInputParams.X = l_coordinates.x;
    l_mouseWheelInputParams.Y = l_coordinates.y;

    obtainWindowPointer(hWnd)->onMouseWheel(l_mouseWheelInputParams);

    return 0;
}

LRESULT dispatch_WM_MOUSEHOVER(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    obtainWindowPointer(hWnd)->onMouseEnter();
    return 0;
}

LRESULT dispatch_WM_MOUSELEAVE(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //!!!!!!!!!!!!!!!!!!!!!
    //TODO: THIS SUBROUTINE DOEN NOT WORK AS EXPECTED
    //!!!!!!!!!!!!!!!!!!!!!

    obtainWindowPointer(hWnd)->onMouseLeave();
    return 0;
}

#pragma endregion

#pragma region CLIPBOARD

/*
TODO: MultiByteToWideChar() and WideCharToMultiByte() are not safe functions.
This part of code needs systematic and thorough review.

---

Static class Clipboard needs to be implemented in this translation unit in order to 
get access to existing window handles. This is because Win32 implementation of clipboard
demands that cliboard data must be owned by a window, even if no memory clean-up needs to
take place.
*/

void Application::Clipboard::putUnicodeText(string text)
{
    if (windowHandles.empty())
        return;

    if (!OpenClipboard(windowHandles.front()))
        return;

    EmptyClipboard();

    size_t l_wcBufferSize = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, nullptr, 0) * sizeof(wchar_t);

    HGLOBAL l_hGlobalMem = GlobalAlloc(GMEM_MOVEABLE, l_wcBufferSize);

    if (l_hGlobalMem == NULL)
    {
        CloseClipboard();
        return;
    }

    LPWSTR l_lpstrMem = (LPWSTR)GlobalLock(l_hGlobalMem);

    MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, l_lpstrMem, l_wcBufferSize);
    
    GlobalUnlock(l_hGlobalMem);

    SetClipboardData(CF_UNICODETEXT, l_hGlobalMem);

    CloseClipboard();
}

std::string Application::Clipboard::getUnicodeText()
{
    string l_clipboardString;

    if (!IsClipboardFormatAvailable(CF_UNICODETEXT))
        return "";

    if (!OpenClipboard(nullptr))
        return "";

    HGLOBAL l_hGlobalMem = GetClipboardData(CF_UNICODETEXT);

    if (l_hGlobalMem == NULL)
    {
        CloseClipboard();
        return "";
    }

    LPWSTR lpstrMem = (LPWSTR)GlobalLock(l_hGlobalMem);

    if (lpstrMem != NULL)
    {
        size_t l_mbcBufferSize = WideCharToMultiByte(CP_UTF8, 0, lpstrMem, -1, nullptr, 0, nullptr, nullptr) * sizeof(char);

        l_clipboardString = string(l_mbcBufferSize - 1, (char)0xCD);

        WideCharToMultiByte(CP_UTF8, 0, lpstrMem, -1, (LPSTR)&l_clipboardString[0], l_mbcBufferSize - 1, nullptr, nullptr);

        GlobalUnlock(l_hGlobalMem);
    }

    CloseClipboard();

    return l_clipboardString;
}

#pragma endregion

#pragma region MESSAGE BOX

void Application::nativeMsgBox(string message, string title)
{
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    MessageBox(nullptr, converter.from_bytes(message).c_str(), converter.from_bytes(title).c_str(), MB_TASKMODAL);
}

void Application::nativeLog(string message)
{

}


#pragma endregion

#endif
