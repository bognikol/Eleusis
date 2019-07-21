#ifdef __APPLE__

#include "Window.h"
#include "Application.h"
#include "WindowOSBundle_macOS.h"
#include "Timer.h"

#include "cairo.h"
#include "cairo-quartz.h"

using namespace Eleusis;

Window::Window() :
    _windowOSBundle(new WindowOSBundle()),
    _root(new RootNode()),
    _animationManager(new AnimationManager()),
    _lastMouseDownVisualPrimitive(nullptr),
    _lastMouseMoveVisualPrimitive(nullptr)
{
    _windowOSBundle->_nsWindow = [[EleusisNSWindow alloc] initWithOwner:this];
    
    [_windowOSBundle->_nsWindow setStyleMask:NSWindowStyleMaskResizable | NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable];
    [_windowOSBundle->_nsWindow setContentSize:CGSizeMake(3000, 3000)];
    [_windowOSBundle->_nsWindow makeKeyAndOrderFront:_windowOSBundle->_nsWindow];
    
    CGColorSpaceRef l_cs = _windowOSBundle->_nsWindow.colorSpace.CGColorSpace;
    _windowOSBundle->_backbuffer = CGBitmapContextCreate (NULL, 3000, 3000, 8, 3000*4, l_cs, kCGImageAlphaPremultipliedLast);

    NSRect scale = [_windowOSBundle->_nsWindow convertRectToBacking:NSMakeRect(0, 0, 1.0, 1.0)];
    CGContextTranslateCTM (_windowOSBundle->_backbuffer, 0.0, 3000);
    CGContextScaleCTM (_windowOSBundle->_backbuffer, scale.size.width, -scale.size.height);

    _cairoSurface = cairo_quartz_surface_create_for_cg_context (_windowOSBundle->_backbuffer, 3000, 3000);
    _cairoContext = cairo_create(_cairoSurface);

    _root->setContext(static_cast<UIContext*>(this));

    Timer* l_timer = new Timer(1000 / 60, TimerRepetition::Forever);
    l_timer->elapsed += [this](Timer* sender, EventArgs* e)
    {
        this->onRenderingTimer();
        raiseEvent Application::renderingCycleExecuted(nullptr, nullptr);
    };
    l_timer->start();
}

Window::~Window()
{
    delete _root;
    delete _animationManager;
    cairo_destroy(_cairoContext);
    cairo_surface_destroy(_cairoSurface);
    [_windowOSBundle->_nsWindow release];
    delete _windowOSBundle;
}

void Window::show()
{
    [_windowOSBundle->_nsWindow display];
    [_windowOSBundle->_nsWindow orderFront:(_windowOSBundle->_nsWindow)];

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
    [_windowOSBundle->_nsWindow orderOut:(_windowOSBundle->_nsWindow)];
}

void Window::minimize()
{
    [_windowOSBundle->_nsWindow miniaturize:(_windowOSBundle->_nsWindow)];
}

void Window::maximize()
{
    [_windowOSBundle->_nsWindow toggleFullScreen:nil];
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
    [_windowOSBundle->_nsWindow makeKeyWindow];
    [_windowOSBundle->_nsWindow orderFront:(_windowOSBundle->_nsWindow)];
}

bool Window::isFocused()
{
    return static_cast<bool>([_windowOSBundle->_nsWindow isKeyWindow]);
}

void Window::enable()
{
    _enabled = true;
}

void Window::disable()
{
    _enabled = false;
}

bool Window::isEnabled()
{
    return _enabled;
}

void Window::setPosition(Vector position)
{
    NSPoint l_point;;
    l_point.x = position.X;
    l_point.y = position.Y;
    
    [_windowOSBundle->_nsWindow setFrameTopLeftPoint:l_point];
}

Vector Window::getPosition()
{
    NSRect l_frame = [_windowOSBundle->_nsWindow frame];
    double l_screenHeight = [[_windowOSBundle->_nsWindow screen] frame].size.height;
    return {l_frame.origin.x, l_screenHeight - l_frame.size.height - l_frame.origin.y};
}

void Window::setSize(Vector size)
{
    NSRect l_frame = [_windowOSBundle->_nsWindow frame];
    l_frame.size.width = size.X;
    l_frame.size.height = size.Y;
    
    [_windowOSBundle->_nsWindow setFrame:l_frame display: NO];
}

Vector Window::getSize()
{
    NSRect l_frame = [_windowOSBundle->_nsWindow frame];
    return {l_frame.size.width, l_frame.size.height};
}

void Window::_render()
{
    _root->_render(nullptr);
    cairo_surface_flush(_cairoSurface);

    [_windowOSBundle->_nsWindow show:_windowOSBundle->_backbuffer];
}

void Window::_render(Region* region)
{
    _root->_render(region);
    cairo_surface_flush(_cairoSurface);

    [_windowOSBundle->_nsWindow show:_windowOSBundle->_backbuffer];
}

Eleusis::Rect Window::surfaceSize()
{
    return Eleusis::Rect();
}

void* Window::getNativeHandle()
{
    return (void*)(_windowOSBundle->_nsWindow);
}

#endif
