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
    
    [_windowOSBundle->_nsWindow setStyleMask:NSWindowStyleMaskResizable | NSWindowStyleMaskClosable | NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable];
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
}

void Window::minimize()
{
}

void Window::maximize()
{
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
}

bool Window::isFocused()
{
    return false;
}

void Window::enable()
{
}

void Window::disable()
{
}

bool Window::isEnabled()
{
    return true;
}

void Window::setPosition(Vector position)
{
}

Vector Window::getPosition()
{
    return Vector();
}

void Window::setSize(Vector size)
{
}

Vector Window::getSize()
{
    return {[_windowOSBundle->_nsWindow frame].size.width, [_windowOSBundle->_nsWindow frame].size.height};
}


void Window::onSizeChanged(SizeChangedParams inputParams)
{   
    _root->setAbsoluteSizeVector(inputParams.Size);
    
    SizeChangedEventArgs l_sizeChangedEventArgs(inputParams);
    raiseEvent sizeChanged(this, &l_sizeChangedEventArgs);
}


void Window::_render()
{
    _root->_render(nullptr);
    cairo_surface_flush(_cairoSurface);

    [_windowOSBundle->_nsWindow show:_windowOSBundle->_backbuffer];
}

void Window::_render(Region* region)
{
    NSLog(@"_render");

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