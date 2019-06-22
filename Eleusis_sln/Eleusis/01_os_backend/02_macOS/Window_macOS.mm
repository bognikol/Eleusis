#ifdef __APPLE__

#include "Window.h"
#include "Application.h"
#include "WindowOSBundle_macOS.h"

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
    [_windowOSBundle->_nsWindow setContentSize:CGSizeMake(3000, 2000)];
    [_windowOSBundle->_nsWindow makeKeyAndOrderFront:_windowOSBundle->_nsWindow];
    
    CGContextRef l_cgContext = [[_windowOSBundle->_nsWindow graphicsContext] CGContext];
    
    CGContextTranslateCTM (l_cgContext, 0.0, (unsigned int)[_windowOSBundle->_nsWindow frame].size.height - 20);
    CGContextScaleCTM (l_cgContext, 1.0, -1.0);
    
    _cairoSurface = cairo_quartz_surface_create_for_cg_context(l_cgContext, 3000, 3000);
    _cairoContext = cairo_create(_cairoSurface);

    cairo_set_source_rgb (_cairoContext, 255, 0, 255);
    cairo_rectangle (_cairoContext, 0, 0, 200, 200);
    cairo_fill (_cairoContext);

    cairo_surface_flush(_cairoSurface);
    [[_windowOSBundle->_nsWindow graphicsContext] flushGraphics];

    Application::nativeMsgBox("Cairo drawn");

    _root->setContext(static_cast<UIContext*>(this));
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
    
    _layout();
    _updateGeometryAndApplyAbsoluteOffset();
    _render();
    
    _prepeareForFollowingRenderingIteration();
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
    /*cairo_destroy(_cairoContext);
    cairo_surface_destroy(_cairoSurface);
    
    CGContextRef l_cgContext = [[_windowOSBundle->_nsWindow graphicsContext] CGContext];
    
    CGAffineTransform l_ctm = CGContextGetCTM(l_cgContext);
    CGAffineTransform l_inverseCtm = CGAffineTransformInvert(l_ctm);
    CGContextConcatCTM(l_cgContext, l_inverseCtm);
    
    CGContextTranslateCTM (l_cgContext, 0.0, inputParams.Size.Y - 20);
    CGContextScaleCTM (l_cgContext, 1.0, -1.0);
    
    _cairoSurface = cairo_quartz_surface_create_for_cg_context(l_cgContext, inputParams.Size.X, inputParams.Size.Y);
    _cairoContext = cairo_create(_cairoSurface);
    _root->setContext(static_cast<UIContext*>(this));*/
    
    _root->setAbsoluteSizeVector(inputParams.Size);
    
    SizeChangedEventArgs l_sizeChangedEventArgs(inputParams);
    raiseEvent sizeChanged(this, &l_sizeChangedEventArgs);
}


void Window::_render()
{
    _root->_render(nullptr);
    
    cairo_surface_flush(_cairoSurface);
    
    [[_windowOSBundle->_nsWindow graphicsContext] flushGraphics];
}

void Window::_render(Region* region)
{
    _root->_render(region);
    
    cairo_surface_flush(_cairoSurface);
    
    [[_windowOSBundle->_nsWindow graphicsContext] flushGraphics];
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